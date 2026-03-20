/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/UTE/parsRelations.c,v $
 *
 * Copyright (c) 2004
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: parsRelations.c,v 1.17 2012/11/19 12:30:36 sako Exp $
 *
 * ***************************************************************/


static const char resid[] = "$Id: parsRelations.c,v 1.17 2012/11/19 12:30:36 sako Exp $ (C) 2004 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	0
#define DB_LINE_NR	0

#include "method.h"


/*===============================================================
 * ExcPulse1EnumRel
 * Relation of ExcPulse1Enum (a dynamic enmueration parameter which
 * allows to select one of the existing  pulses)
 *===============================================================*/

void ExcPulse1EnumRel(void)
{
  DB_MSG(("-->ExcPulse1EnumRel"));

  UT_SetRequest("ExcPulse1Enum");
  backbone();
  
  DB_MSG(("<--ExcPulse1EnumRel"));                                       
}

/*===============================================================
 * ExcPulse1AmplRel
 * Relation of ExcPulseAmpl 
 * This parameter is used in the setup parameter card to adjust
 * the RF pulse amplitude manually
 *===============================================================*/

void ExcPulse1AmplRel(void)
{
  DB_MSG(("-->ExcPulse1AmplRel"));
  UT_SetRequest("ExcPulse1Ampl");
  HandleRFPulseAmplitude();
  DB_MSG(("-->ExcPulse1AmplRel"));
}

void HandleRFPulseAmplitude(void)
{
  DB_MSG(("-->HandleRFPulseAmplitude"));

  STB_UpdateRFShapeAmplitude("ExcPulse1Ampl",No);
  ATB_SetRFPulse("ExcPulse1","ACQ_RfShapes[0]");

  DB_MSG(("<--HandleRFPulseAmplitude"));
}


/* ===================================================================
 * Relation of ExcPulse
 * 
 * All pulses of type PVM_RF_PULSE must have relations like this.
 * However, if you clone this funtion for a different pulse parameter
 * remember to replace the param name in the call to UT_SetRequest!
 *
 * IMPORTANT: this function should not be invoked in the backbone!
 ====================================================================*/

void ExcPulse1Rel(void)
{
  DB_MSG(("-->ExcPulse1Rel"));
  
  /*
   * Tell the request handling system that the parameter
   * ExcPulse has been edited 
   */
  
  UT_SetRequest("ExcPulse1");
  
  /* Check the values of ExcPulse */
  
  ExcPulse1Range();
  
  /* 
   * call the backbone; further handling will take place there
   * (by means of STB_UpdateRFPulse)  
   */
  
  backbone();
  
  DB_MSG(("<--ExcPulse1Rel"));
}

void ExcPulse1Range(void)
{
  DB_MSG(("-->ExcPulse1Range"));
  
  // range checker fields to be controlled may be
  // .Length  
  // .Bandwidth
  // .Flipangle
  // .Calculated
  // .Sharpness
  // .Flatness   
 double dval=ExcPulse1.Flipangle;
  
 ExcPulse1.Flipangle = MIN_OF(90.0,MAX_OF(dval,1.0));

 DB_MSG(("<--ExcPulseRange")); 
}

/*--------------------------------------------------------
 *
 * single parameter range checkers and relations
 *
 *-------------------------------------------------------*/


void RepetitionTimeRange(void)
{
  
  DB_MSG(("-->RepetitionTimeRange"));

  if(ParxRelsParHasValue("PVM_RepetitionTime")==No)
  {
    PVM_RepetitionTime = 30.0;
  }
  else
  {
    PVM_RepetitionTime = MAX_OF(1e-3,PVM_RepetitionTime);
  }

  
  DB_MSG(("<--RepetitionTimeRange"));
  return;
}

void RepetitionTimeRel(void)
{
  DB_MSG(("-->RepetitionTimeRel"));

  RepetitionTimeRange();
  backbone();

  DB_MSG(("<--RepetitionTimeRel"));
  return;
}

void AveragesRange(void)
{
  
  DB_MSG(("-->AveragesRange"));

  if(ParxRelsParHasValue("PVM_NAverages")==No)
  {
    PVM_NAverages = 1;
  }

  if (PVM_NAverages > 1)
  {
    ParxRelsShowInEditor("PVM_MotionSupOnOff");
  }
  else
  {
    ParxRelsHideInEditor("PVM_MotionSupOnOff");
  } 

  DB_MSG(("<--AveragesRange"));
  return;
}

void AveragesRel(void)
{
  DB_MSG(("-->AveragesRel"));

  AveragesRange();
  backbone();

  DB_MSG(("<--AveragesRel"));
  return;
}

/*==============================================================
 * method specific range checkers and relations
 *==============================================================*/


void ProUnderRel(void)
{
  DB_MSG(("-->ProUnderRel"));

  ProUnderRange();
  backbone();

  DB_MSG(("<--ProUnderRel"));
  return;
}

void ProUnderRange(void)
{
  DB_MSG(("-->ProUnderRange"));

  if(!ParxRelsParHasValue("ProUndersampling"))
  {
    ProUndersampling = 1.0;
  }
  else
  {
    ProUndersampling = MAX_OF(MIN_OF(512.0,ProUndersampling),1.0);
  }

  DB_MSG(("<--ProUnderRange"));
  return;
}


void RampModeRel (void)
{

  RampModeInitRel();
  backbone();
}

void RampModeInitRel (void)
{
  if(ParxRelsParHasValue("RampMode") == No)
    RampMode = constant_slope;
  
  SlewRateRange();
  ConstantTimeRange();
  
  switch(RampMode)
  {
  default:
  case constant_time:
    ParxRelsHideInEditor("EffSlewRate");
    ParxRelsHideInFile("EffSlewRate");
    ParxRelsShowInEditor("Ramptime");
    ParxRelsShowInFile("Ramptime");
    break;
  case constant_slope:
    ParxRelsHideInEditor("Ramptime");
    ParxRelsHideInFile("Ramptime");
    ParxRelsShowInEditor("EffSlewRate");
    ParxRelsShowInFile("EffSlewRate");
    break;
  }
}

void SlewRateRel(void)
{
  SlewRateRange();
  backbone();
}

void SlewRateRange(void)
{
  DB_MSG(("-->EffSlewRateRange"));

  if(ParxRelsParHasValue("EffSlewRate") == 0)
  {
    EffSlewRate = 100.0;
  }
  else
  {
    EffSlewRate = MIN_OF(MAX_OF(10.0,EffSlewRate),100.0);
  }

  DB_MSG(("<--EffSlewRateRange"));
  return;
}

void ConstantTimeRange(void)
{
  double rampT = CFG_GradientRampTime();

  DB_MSG(("-->ConstantTimeRange"));
 
  if(ParxRelsParHasValue("Ramptime") == 0)
  {
    Ramptime = rampT;
  }
  else
  {
    Ramptime = MIN_OF(MAX_OF(rampT, Ramptime), 4.0*rampT);
  }

  DB_MSG(("<--ConstantTimeRange"));
  return;
}

void UpdateAdjustments(void)
{
  DB_MSG(("-->UpdateAdjustments"));
  
  PTB_ClearAdjustments();
  STB_TrajAppendAdjustment("");
  PTB_AppendConfiguredAdjustment(per_scan, RCVR);
  
  DB_MSG(("<--UpdateAdjustments"));
}

// slice selection
void SliceSpoilerRel(void)
{
  DB_MSG(("-->SliceSpoilerRel"));
  UT_SetRequest("SliceSpoiler");
  backbone();
  DB_MSG(("<--SliceSpoilerRel"));
}

void EchoPositionRange(void)
{
  DB_MSG(("-->EchoPositionRange"));

  if(ParxRelsParHasValue("PVM_EchoPosition")==No)
  {
    PVM_EchoPosition=50.0;
  }
  else
  {
    PVM_EchoPosition = MAX_OF(MIN_OF(PVM_EchoPosition,50),20.0);
  }

  DB_MSG(("<--EchoPositionRange"));

}


void EffSWhRange(void)
{
  DB_MSG(("-->EffSWhRange"));

  if(!ParxRelsParHasValue("PVM_EffSWh"))
  {
    PVM_EffSWh=100000;
  }
  else
  {
    double dval;
    /* constrain */
    dval = PVM_EffSWh;
    PVM_EffSWh=MAX_OF(MIN_OF(1000000.0,dval),2000.0);
  }

  DB_MSG(("<--EffSWhRange"));
}

void EffSWhRel(void)
{
  DB_MSG(("-->EffSWhRel"));

  EffSWhRange();
  backbone();

  DB_MSG(("<--EffSWhRel"));
}

/*===============================================================
  *********************** Composite Pulse 20180323****************
  *===============================================================
  */


void BinomialFunc(void)
{
YesNo refPowAvailable=No;
double refpow=5.0;
refPowAvailable=STB_GetRefPower(1,&refpow);
double angleelement;  

/*
angleelement = 90;
Nbpulse=3;
*/
angleelement = 180;
Nbpulse=1;

PVM_ppgPowerList1Size = Nbpulse;
ParxRelsParRelations("PVM_ppgPowerList1Size",Yes);
PVM_ppgPowerList1[0] = MRT_RFPulsePower(ExcPulseBin1.Sint,
                                     angleelement,
                                     ExcPulseBin1.Length,
                                     refpow);
/*
PVM_ppgPowerList1[1] = MRT_RFPulsePower(ExcPulseBin1.Sint,
                                     angleelement*2,
                                     ExcPulseBin1.Length,
                                     refpow);
PVM_ppgPowerList1[2] = MRT_RFPulsePower(ExcPulseBin1.Sint,
                                     angleelement,
                                     ExcPulseBin1.Length,
                                     refpow);
*/
}

void ExcPulseBinEnumRelation(void)
{
    UT_SetRequest("ExcPulseBinEnum1");
  backbone();

  DB_MSG(("<--ExcPulseBinEnumRelation"));
}

void ExcPulseBinRange(void)
{
  DB_MSG(("-->ExcPulRange"));

  ExcPulseBin1.Flipangle = MIN_OF(180.0, ExcPulseBin1.Flipangle);

  DB_MSG(("<--ExcPulRange"));
}

void ExcPulseBinRelation(void)
{

  UT_SetRequest("ExcPulseBin1");
  ExcPulseBinRange();  
  backbone();

  DB_MSG(("<--ExcPulseBinRelation"));
}

void ExcPulseBinAmplRelation(void)
{
  UT_SetRequest("ExcPulseBinAmpl1");
  HandleRFPulseBinAmplitudes();  
  backbone();

  DB_MSG(("<--ExcPulseBinAmplRelation"));
}

void HandleRFPulseBinAmplitudes(void)
{
  DB_MSG(("-->HandleRFPulseBinAmplitude"));

  STB_UpdateRFShapeAmplitude("ExcPulseBinAmpl1", No);
  ATB_SetRFPulse("ExcPulseBin1", "ACQ_RfShapes[2]");
  
  DB_MSG(("<--HandleRFPulseBinAmplitude"));
}

/*===============================================================
  *********************** Variable Flip Angle 20180913****************
  *===============================================================
  */
void VariableFlipAngle(void)
{
YesNo refPowAvailable=No;
double refpow=0.0;
refPowAvailable=STB_GetRefPower(1,&refpow);

if(refPowAvailable==Yes)  // important to assure nonzero value of refpow
{
    PVM_ppgPowerList2Size = PVM_NEchoImages;
    ParxRelsParRelations("PVM_ppgPowerList2Size",Yes);

    for (int i = 0; i<PVM_NEchoImages; i++) 
    PVM_ppgPowerList2[i] = MRT_RFPulsePower(ExcPulse1.Sint,
                                         Angle[i],
                                         ExcPulse1.Length,
                                         refpow);
}

}