/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/UTE/backbone.c,v $
 *
 * Copyright (c) 2004
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: backbone.c,v 1.36.2.1 2014/02/26 15:14:08 sako Exp $
 *
 * ***************************************************************/


static const char resid[] = "$Id: backbone.c,v 1.36.2.1 2014/02/26 15:14:08 sako Exp $ (C) 2004 Bruker BioSpin MRI GmbH";

#define DEBUG		1
#define DB_MODULE	0
#define DB_LINE_NR	0

#include "method.h"


void backbone(void)
{

  double minFov[3];
  double minSliceThick;
  double minte1, minte2;
  double pi;
  int dim;


  DB_MSG(("-->backbone"));


  STB_UpdateNuclei(No);
  
  if(AcqMode == FID)
    ParxRelsShowInEditor("RampCompYN");
  else
    ParxRelsHideInEditor("RampCompYN"); 

  dim = PTB_GetSpatDim();

  /* constrain AntiAlias for radial acquisition */
  PVM_AntiAlias[0] = PVM_AntiAlias[1] = 1.0;

  /* encoding */
  STB_UpdateEncodingSpecial(2, 2, Yes);   
  
  /* set limits for read, phase and slice gradients            */
  ControlGradientLimits();

   
  minFov[0] = EncodingLimits( AcqMode == ECHO ? PVM_EncMatrix[0] : PVM_EncMatrix[0]/2,
			      PVM_AntiAlias,
			      PVM_GradCalConst);

  /* radial projection constraint  */
  minFov[1] = minFov[0];
  
  /* update excitation pulse */   
  UpdateRFPulses();
  
  /* Variable Flip angle */
  VariableFlipAngle();

  minSliceThick =  ExcPulse1.Bandwidth /
                  (1e-2*ExcSliceGradLim * PVM_GradCalConst);

  
  /* update geometry parameters */
  UpdateGeometry(minFov,minSliceThick);

      
  /* calculate number of projections */
  pi=M_PI;
  // ******************UTE2D MP2RAGE 19/12/2017****************************
  NyquistPro = ((pi/2) * PVM_EncMatrix[0]*(AcqMode == ECHO ? 1:2));
  NPro = IrNumber*NRegroup;

  if(NPro < 4)
      NPro = 4;
  
  if(NPro%2) 
      NPro++;  
    
  ProUndersampling = NyquistPro/double(NPro);
// ****************** End UTE2D MP2RAGE 19/12/2017*************************



  EncodingGradients(PVM_Fov[0], PVM_Fov[1],PVM_GradCalConst);


  UpdateSliceSelectionGradients(PVM_SliceThick,
                                ExcPulse1.Bandwidth,
				PVM_GradCalConst);


  if(RampCompYN==Yes)
  {
    double points= CFG_GradientRampTime()/(2.0*PVM_DigDw);
    RampPoints = (int) (0.5 + points);
    RampCompTime = RampPoints * PVM_DigDw;
    ParxRelsShowInEditor("RampPoints");
  }
  else
  {
    RampPoints = 0;
    RampCompTime = 0.0;
    ParxRelsHideInEditor("RampPoints");
  }


  /* update slice spoiler */
  double mindurSlice = 2.5*CFG_GradientRiseTime();
  MRT_UpdateSpoiler("SliceSpoiler",2.0,ExcSliceGradLim,mindurSlice,PVM_GradCalConst,PVM_SliceThick);

  /* handling of modules */
  STB_UpdateFatSupModule(PVM_Nucleus1, PVM_DeriveGains, PVM_SliceThick);
  STB_UpdateMagTransModule(PVM_DeriveGains);
  STB_UpdateFovSatModule(PVM_Nucleus1, PVM_DeriveGains);
  STB_UpdateTriggerModule();
  
  UpdateRFPulsesBin();                              // Composite Pulse 20180323
  BinomialFunc();                                   // Composite Pulse 20180323
  
  UpdateRFSpoiling();                               // RF Spoiling 20180709
  
  /* calculate frequency offsets */
  LocalFrequencyOffsetRels();

  /* update sequence timing */

  UpdateIr();                                       //MP2RAGE 19-12-2017
  UpdateEchoTime(&minte1,&minte2);
  UpdateRepetitionTime();
  UpdateMP2RAGE_TR();
  
  STB_UpdateDummyScans(PVM_RepetitionTime, PVM_MotionSupOnOff==On ? 1:PVM_NAverages);
  //PVM_DummyScans = 0;                               //MP2RAGE 19-12-2017

  /* calculate dephasing gradients */
  EncodingDephGradients();

  //PVM_NEchoImages = 1;                            //MP2RAGE 19-12-2017

  /* update mapshim parameter class */
  STB_UpdateMapShim(PVM_Nucleus1,"PVM_SliceGeoObj");

  SetBaseLevelParam();

  /* update trajectory module */

  double gradAmp[2]={ReadGrad, PhaseGrad};
  double gradMax[2]={ReadGrad, PhaseGrad};
  int nPoints = PVM_EncMatrix[0]/2 + RampPoints;
  int nJunk = 0;

  if(AcqMode==ECHO)
  {
    gradMax[0] = MAX_OF(ReadGrad, ReadDephGrad);
    gradMax[1] = MAX_OF(PhaseGrad, PhaseDephGrad);
    nPoints = PVM_EncMatrix[0];
    nJunk = ReadDephPoints;
  }
  STB_UpdateTraj(PVM_SpatResol, PVM_EncZf, PVM_Fov, 2, NPro, nPoints+nJunk, 0, PVM_DigDw, gradMax, 
                 PtrType3x3 PVM_SPackArrGradOrient[0], PVM_TriggerModule, GradSync, 0.5, 0.0, GradRes, gradAmp); 

  UpdateAdjustments();

  SetRecoParam();
  

  DB_MSG(("<--backbone"));
  return;
}

/*-------------------------------------------------------
 * local utility routines to simplify the backbone 
 *------------------------------------------------------*/
void UpdateIr()
{
    double minSliceSegDur, IrInitDelay;
    double fixedTime = CFG_AmplifierEnable() 
                        + ExcPulse1.Length/2.0;
    int nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices);
    
    //PVM_SelIrD0 = 0.020;
    
    IrInitDelay =
        (
        PVM_SelIrP0/1000.0/1000.0/2 + // IrPulse /2
        PVM_SelIrD4                 + //grad_ramp
        PVM_SelIrD0                 + //Additionnal delay
        PVM_SelIrD2                 + //IR spoiler : not used (except for repetitions)
        PVM_SelIrD4                 + //grad_ramp
        PVM_SelIrD1                   
        )*1000;

/*
     minSliceSegDur = 
             (
             PVM_SelIrD4    +
             PVM_SelIrD3    +
             //PVM_SelIrD0    +
             PVM_SelIrD4
             )*1000.0       +
             PVM_SelIrP0/1000.0;
     
     SliceSegDur = minSliceSegDur+1.0+0.020;
*/

    minSliceSegDur = 0;
    
    SliceSegDur=
            MAX_OF(SliceSegDur,minSliceSegDur);
    PVM_SelIrInvTime=0;
/*
    SliceSegDur = MP2RAGE_TR;
*/
    
    STB_UpdateSelIrModule(PVM_SliceThick,PVM_SliceOffset,nSlices,&SliceSegDur,0,fixedTime,PVM_DeriveGains);
    
    if(PVM_SelIrOnOff==On)
      ParxRelsCopyPar("PVM_InversionTime","PVM_SelIrInvTime");    
}

void UpdateEchoTime(double *const minte1, double *const minte2)
{  

  DB_MSG(("-->UpdateEchoTime"));

  double del = CFG_InstrumentType() == Avance_II ? 0.005:0.0;

   *minte1 = 
    ExcPulse1.Length*ExcPulse1.Rpfac/100    +
    GrShapeT1                               +
    2.0*GrShapeT2                           +
    GrShapeT3                               +
    del;

   *minte2 = 
    ExcPulse1.Length*ExcPulse1.Rpfac/100    +
    GrShapeT1                               +
    2.0*GrShapeT2                           +
    GrShapeT3                               +
    ReadDephTime                            +
    PVM_AcquisitionTime * PVM_EchoPosition / 100.0;


   if(AcqMode == FID)
   {
     PVM_MinEchoTime = *minte1;
   }
   else
   {
     PVM_MinEchoTime = *minte2;
   }

   PVM_EchoTime = MAX_OF(PVM_MinEchoTime,PVM_EchoTime);

  
   if(AcqMode == ECHO)
   {
     double extension=0.0;
     if(YesNoMinEchoTime==No)
     {
       double extensionPossible = PVM_EchoTime - PVM_MinEchoTime;
       double max = 2*PVM_AcquisitionTime;
       extension = MIN_OF(extensionPossible,max);
       extension = MAX_OF(extension, 0);
     }
     
     /* ReadDephTime should be a multiple of Grid */ 
     double dephaseT = ReadDephTime + extension;
     int gradres = (GradRes*1000+0.5);
     int dwell = (PVM_DigDw*1000+0.5);
     Grid = lcm(gradres,dwell)/1000.0; 
     int points = (int)(dephaseT/Grid+0.5);
     dephaseT = points*Grid;
     if(dephaseT<ReadDephTime)
     {
       points = points+1;
       dephaseT = points*Grid;
     }
     double fill = MAX_OF((dephaseT - ReadDephTime),0);
     ReadDephTime = dephaseT;
     ReadDephPoints = (int)(ReadDephTime/PVM_DigDw+0.5);
     PVM_MinEchoTime += fill;
     PVM_EchoTime = MAX_OF(PVM_MinEchoTime,PVM_EchoTime);
   }
  
   if(YesNoMinEchoTime==Yes)
   {
     TeFillDelay=0.0 + del;
     PVM_EchoTime = PVM_MinEchoTime;
     ParxRelsMakeNonEditable("PVM_EchoTime");
   }
   else
   {
     TeFillDelay = PVM_EchoTime - PVM_MinEchoTime + del;
     ParxRelsMakeEditable("PVM_EchoTime");
   }

  DB_MSG(("<--UpdateEchoTime"));
  return;
}



void UpdateRepetitionTime(void)
{
  int dim;
  double rephaseT;

  DB_MSG(("-->UpdateRepetitionTime"));

  /* adapt timing for sufficient spoiling */
  ReadSpoilDur = 1e5*ReadSpoiling/(ReadGrad*PVM_GradCalConst*PVM_SpatResol[0]);

  if(AcqMode == FID)
  {  
    rephaseT = CFG_GradientRampTime() + 2*CFG_GradientRiseTime() + PVM_AcquisitionTime + RampCompTime + ReadSpoilDur;
  }
  else
  {
    rephaseT = PVM_AcquisitionTime * (1-PVM_EchoPosition / 100.0) + ReadSpoilDur +CFG_GradientRiseTime();
  }

  PVM_MinRepetitionTime = 
      //PVM_FovSatModuleTime                             +//    SA2RAGE 20180913
      PVM_FatSupModuleTime                             +
      PVM_MagTransModuleTime                           +
      0.02                                             +
      SliceSpoiler.dur                                 +
      2.0*CFG_GradientRiseTime()                       +
      CFG_AmplifierEnable()                            +      
      ExcPulse1.Length*(1 - ExcPulse1.Rpfac/100)       +
      PVM_EchoTime                                     +
      rephaseT                                         +
      CFG_InterGradientWaitTime();

  PVM_RepetitionTime=MAX_OF(PVM_MinRepetitionTime,PVM_RepetitionTime);

  dim = PTB_GetSpatDim();

  if(SliceAlter == Yes)
  {
    NECHOES = 2;
  }
  else
  {
    NECHOES = 1;
  }

/*
  TotalTime = PVM_RepetitionTime 
              * NPro
              * NECHOES
              * PVM_NMovieFrames
              * nslices
              * PVM_NAverages
              * PVM_NRepetitions;
    
  PVM_ScanTime = TotalTime;
  UT_ScanTimeStr(PVM_ScanTimeStr,TotalTime);
  ParxRelsShowInEditor("PVM_ScanTimeStr");
  ParxRelsMakeNonEditable("PVM_ScanTimeStr");
*/

  DB_MSG(("<--UpdateRepetitionTime"));
  return;
}

void UpdateMP2RAGE_TR(void)
{
    DB_MSG(("UpdateMP2RAGE_TR-->"));
    double TotalTime;
    double IrModuleTime;
    int nslices;
    
    nslices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );

    double IrInitDelay;
    //see : /opt/PV6.0.1/exp/stan/nmr/lists/pp/SelSliceIrDef.mod
    if (BinOnOff)
    {
/*
        IrInitDelay = 
                1.5*P[2]/1000.0             +
                CFG_AmplifierEnable()       +
                10.0/1000.0;
*/
        IrInitDelay = 
                P[2]/1000.0             +
                5.0/1000.0;
        
    }
    else
    {
      IrInitDelay =
              (
                PVM_SelIrP0/1000.0/1000.0/2 + // IrPulse /2
                PVM_SelIrD4                 + //grad_ramp
                PVM_SelIrD0                 + //Additionnal delay
                PVM_SelIrD2                 + //IR spoiler : not used (except for repetitions)
                PVM_SelIrD4                 + //grad_ramp
                PVM_SelIrD1                   
              )*1000;  
    }

      double RfInitDelay = (D[6]+2.0*D[1]+D[2])*1000.0+P[0]/2.0/1000.0;
              
    DB_MSG(("IRInitDelay = %f",IrInitDelay));
      
    double minTI[PVM_NEchoImages];
    PARX_change_dims("EffectiveTI", PVM_NEchoImages);
    PARX_change_dims("IRVarDelay", PVM_NEchoImages);

/*
      minTI[0] = 
            IrInitDelay                          +
            PVM_RepetitionTime  		 +
            PVM_RepetitionTime*(int)(NRegroup/2) +
            PVM_EchoTime;              
*/
      minTI[0] = 
            //IrInitDelay                         +
            RfInitDelay                         +
            PVM_FovSatModuleTime                +    // SA2RAGE 20180913
            PVM_RepetitionTime*(int)(NRegroup/2);   
      

    

      EffectiveTI[0]=
            MAX_OF(minTI[0],EffectiveTI[0]);  

      IRVarDelay[0] = 
            (
              EffectiveTI[0]	-
              minTI[0]
            )/1000.0;

    for (int i=1;i<PVM_NEchoImages;i++)
    {
        minTI[i]=
            EffectiveTI[i-1]	+
            PVM_RepetitionTime	*
                (int)(NRegroup);
        
        EffectiveTI[i]=
            EffectiveTI[0] + i*RRDelay;
            
        Angle[i]=Angle[0];
      
        IRVarDelay[i] = 
            (
              EffectiveTI[i]	-
              minTI[i]
            )/1000.0;   
          
    /*  EffectiveTI[i]=
            MAX_OF(minTI[i],EffectiveTI[i]);  

        IRVarDelay[i] = 
            (
              EffectiveTI[i]	-
              minTI[i]
            )/1000.0;   */
    }
      
    
    if (BinOnOff)
    {
/*
        IrModuleTime = 3.0*(
                P[2]/1000.0                  +
                CFG_AmplifierEnable()        +
                5.0/1000.0);
*/
        
        IrModuleTime = 
                2.0*P[2]/1000.0              +
                CFG_AmplifierEnable()        +
                2.0*5.0/1000.0;
    }
    else
        IrModuleTime = PVM_SelIrModuleTime;
      
  MinMP2RAGE_TR =           // SA2RAGE 20180913
      IrModuleTime                                    +
      EffectiveTI[PVM_NEchoImages-1]                  +
        (double)(NRegroup/2)*PVM_RepetitionTime     -
        PVM_EchoTime;//                                -
        //IrInitDelay; 
  
    if (PVM_SelIrOnOff==On)
      MinMP2RAGE_TR -= IrInitDelay;
  

  MP2RAGE_TR=MAX_OF(MinMP2RAGE_TR,MP2RAGE_TR);


  TotalTime = MP2RAGE_TR 
              * nslices
              * IrNumber;
    
  PVM_ScanTime = TotalTime;
  UT_ScanTimeStr(PVM_ScanTimeStr,TotalTime);
  ParxRelsShowInEditor("PVM_ScanTimeStr");
  ParxRelsMakeNonEditable("PVM_ScanTimeStr");

  DB_MSG(("<--UpdateMP2RAGE_TR"));
  return;
}


// RF Spoiling
void UpdateRFSpoiling(void)
{
  DB_MSG(("-->UpdateRFSpoiling"));

  if(RFSpoiling==No)
  {
    PARX_change_dims("RFPhaseList",1);
    RFPhaseList[0] = 0;
  }
                
  else
  {
    int max = NRegroup;
    int size = MAX_OF(256,max);
    PARX_change_dims("RFPhaseList",size);
    //MRT_RFSpoilPhaseList(117,size,RFPhaseList,Yes);
    MRT_RFSpoilPhaseList(90,size,RFPhaseList,Yes);
  }

  DB_MSG(("<--UpdateRFSpoiling"));
}


void LocalFrequencyOffsetRels( void )
{
  int spatDim;
  int i,nslices;

  spatDim = PTB_GetSpatDim();
  nslices = GTB_NumberOfSlices(PVM_NSPacks,PVM_SPackArrNSlices);

  MRT_FrequencyOffsetList(nslices,
			  PVM_EffReadOffset,
			  ReadGrad,
			  PVM_GradCalConst,
			  PVM_ReadOffsetHz );

  MRT_FrequencyOffsetList(nslices,
			  PVM_EffSliceOffset,
			  ExcSliceGrad,
			  PVM_GradCalConst,
			  PVM_SliceOffsetHz );

  if(spatDim == 3)
  {
    for(i=0;i<nslices;i++)
      PVM_EffPhase2Offset[i] = -PVM_EffSliceOffset[i];
  }


}


void UpdateGeometry(double *minFov, double minSliceThick)
{
  
  PVM_SPackArrPhase1Offset[0] = PVM_SPackArrReadOffset[0] = 0.0;

  ParxRelsMakeNonEditable("PVM_SPackArrReadOffset");
  ParxRelsMakeNonEditable("PVM_SPackArrPhase1Offset");
  ParxRelsMakeNonEditable("PVM_SPackArrReadOrient");

  STB_UpdateImageGeometry(2, PVM_Matrix, minFov, 0, 1, 0, minSliceThick, 1);
}

/*------------------------------------------------------
 * routines for parameter group initialization and 
 * update
 *-----------------------------------------------------*/

double EncodingLimits( int dpoints, 
		       double *antiAlias,
		       double gradCalConst) 
{
  double minFovRead = 0.0;

  DB_MSG(("-->EncodingLimits"));

  STB_UpdateDigPars(&PVM_EffSWh,dpoints,antiAlias,&PVM_AcquisitionTime);
 
  /* minimum field of view in the read direction */
  minFovRead = PVM_EffSWh/(1e-2*ReadGradLim * gradCalConst);

  DB_MSG(("<--EncodingLimits"));

  return minFovRead;
}


void EncodingGradients(double readFov,
		       double phaseFov,
		       double gradCalConst)
{
  DB_MSG(("-->EncodingGradients"));

  ReadGrad  = MRT_ReadGrad(PVM_EffSWh,readFov,gradCalConst);

  PhaseGrad = MRT_ReadGrad(PVM_EffSWh,phaseFov,gradCalConst);

  if((ReadGrad - ReadGradLim) > 1.0e-3)
  {
    UT_ReportError("ReadGrad exceeds its limits\n");
  }

  if((PhaseGrad - ReadGradLim) > 1.0e-3)
  {
    UT_ReportError("PhaseGrad exceeds its limits\n");
  }

  ReadGrad = MIN_OF(ReadGrad,ReadGradLim);
  PhaseGrad = MIN_OF(PhaseGrad,ReadGradLim);

  /* Part of the echo to be refocused */
  double EchoDelay = PVM_AcquisitionTime * PVM_EchoPosition / 100;

  double minDephRead  = MRT_DephaseTime(EchoDelay, 
                                 CFG_GradientRiseTime(),
                                 ReadGrad,
                                 ReadDephGradLim);

  double minDephPhase  = MRT_DephaseTime(EchoDelay, 
                                 CFG_GradientRiseTime(),
				 PhaseGrad,
                                 ReadDephGradLim);

  double max = MAX_OF(minDephRead,minDephPhase);
  ReadDephTime = MAX_OF(max+CFG_GradientRiseTime(),2.5*CFG_GradientRiseTime());

  DB_MSG(("<--EncodingGradients"));
  return;
}

void EncodingDephGradients(void)
{
  
  DB_MSG(("-->EncodingDephGradients"));
   
  double EchoDelay = PVM_AcquisitionTime * PVM_EchoPosition / 100;
  double riseT = CFG_GradientRiseTime();

  ReadDephGrad =  MRT_DephaseGrad(ReadDephTime-riseT, EchoDelay, riseT, ReadGrad);
  
  PhaseDephGrad = MRT_DephaseGrad(ReadDephTime-riseT, EchoDelay, riseT, PhaseGrad);

  DB_MSG(("<--EncodingDephGradients"));
  return;
}


YesNo UpdateSliceSelectionGradients(const double slthk,
				    const double excPulseBW,
				    double gradCalConst)
{

  double gradslope=0;

  DB_MSG(("-->UpdateSliceSelectionGradients"));

  /* range check of arguments */

  if(slthk <= 0.0)
  {
    UT_ReportError("UpdateSliceSelectionGradients: "
		   "Illegal value of argument 1\n");
    return No;

  }


  if(excPulseBW < 0.0)
  {
    UT_ReportError("UpdateSliceSelectionGradients: "
		   "Illegal value of argument 3\n");
    return No;

  }
    
  if(gradCalConst <= 0.0)
  {
    UT_ReportError("UpdateSliceSelectionGradients: "
		   "Illegal value of argument 4\n");
    return No;

  }

  /* update of slice gradient */
  ExcSliceGrad     = MRT_SliceGrad(excPulseBW,slthk,gradCalConst);
  

  if((ExcSliceGrad - ExcSliceGradLim)>1.0e-3)
  {
    UT_ReportError("UpdateSliceSelectionGradients: "
		   "ExcSliceGrad exceeded maximum!\n");
    return No;

  }

  ExcSliceGrad = MIN_OF(ExcSliceGrad,ExcSliceGradLim);

  /* calculate shape parameters for slice refocusing */  
  if(RampMode == constant_time)
  {
    GrShapeT1 = Ramptime;
    gradslope = ExcSliceGrad/GrShapeT1;
  }
  else
  {
    gradslope = EffSlewRate/CFG_GradientRampTime(); 
    GrShapeT1 = ExcSliceGrad/gradslope;
  }

  GrShapeT2 = sqrt(ExcSliceGrad*(0.5*GrShapeT1+ExcPulse1.Length*ExcPulse1.Rpfac/100.0)/gradslope);
  GrShapeG2 = -gradslope*GrShapeT2;

  if(GrShapeG2 < -100.0)
  {
    GrShapeG2 = -100.0;
    GrShapeT2 = -GrShapeG2/gradslope;
    GrShapeT3 = -(ExcSliceGrad*(0.5*GrShapeT1+ExcPulse1.Length*ExcPulse1.Rpfac/100.0)+GrShapeG2*GrShapeT2)/GrShapeG2;
  }
  else 
  {
    GrShapeT3 = 0.0;
  }

  GrShape1Time = CFG_GradientRiseTime() +CFG_AmplifierEnable() +  ExcPulse1.Length + GrShapeT1 + 2*GrShapeT2 + GrShapeT3;

  DB_MSG(("<--UpdateSliceSelectionGradients"));
  return Yes;
}

/*--------------------------------------------------------
 * Routine to update RF pulse parameters
 *-------------------------------------------------------*/

void UpdateRFPulses(void)
{

  /* Updates all parameters that belong to ExcPulse1 pulse structure
     (as initialized by STB_InitRFPulse see initMeth.c)
  */

  STB_UpdateRFPulse("ExcPulse1",1,PVM_DeriveGains,Conventional);


  if(PVM_DeriveGains==Yes)
  {
    ParxRelsHideInEditor("ExcPulse1Ampl");
  }
  else
  {
    ParxRelsShowInEditor("ExcPulse1Ampl");
  }

  ParxRelsShowInFile("ExcPulse1Ampl");

  DB_MSG(("<--UpdateRFPulses"));

  return;
}


void ControlGradientLimits(void)
{
  DB_MSG(("-->ControlGradientLimits"));

  ExcSliceRephGradLim = ExcSliceGradLim = 100.0;
  
  if(AcqMode == FID)
  {
    ReadGradLim = ReadDephGradLim = 100.0;
  }
/*
  else
  {
    //ReadGradLim = ReadDephGradLim = 50.0;
    ReadGradLim = ReadDephGradLim = 30.0;//20180227
  }
*/

  DB_MSG(("<--ControlGradientLimits"));
}

int lcm(int count1, int count2)
//lowest common multiple
{
  return (count1*count2)/gcd(count1,count2);
}

int gcd(int count1, int count2)
// greatest common divisor
{
  if(count2 == 0)
  {
    return count1;
  }
  return gcd(count2, count1%count2);
}

/*********************** Composite Pulse 20180323****************/
void UpdateRFPulsesBin(void)
{
  DB_MSG(("-->UpdateRFPulsesBin"));

  /* RF pulse */

  STB_UpdateRFPulse("ExcPulseBin1", 1, PVM_DeriveGains);


  /* visibility */
  if (PVM_DeriveGains == Yes)
  {
    ParxRelsHideInEditor("ExcPulseBinAmpl1");
  }
  else
  {
    ParxRelsShowInEditor("ExcPulseBinAmpl1");
  }
  
  DB_MSG(("<--UpdateRFPulsesBin"));
}
/********************End Composite Pulse 20180323****************/