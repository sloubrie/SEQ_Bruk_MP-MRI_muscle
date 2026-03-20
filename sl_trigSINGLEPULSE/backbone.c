/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/SINGLEPULSE/backbone.c,v $
 *
 * Copyright (c) 2002 -2011
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: backbone.c,v 1.8 2013/06/21 14:21:45 josh Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: backbone.c,v 1.8 2013/06/21 14:21:45 josh Exp $ (C) 2002 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	1
#define DB_LINE_NR	0


/****************************************************************/
/****************************************************************/
/*		I N T E R F A C E   S E C T I O N		*/
/****************************************************************/
/****************************************************************/

/****************************************************************/
/*		I N C L U D E   F I L E S			*/
/****************************************************************/

#include "method.h"

/****************************************************************/
/*	I M P L E M E N T A T I O N   S E C T I O N		*/
/****************************************************************/


/****************************************************************/
/*		G L O B A L   F U N C T I O N S			*/
/****************************************************************/


/* ------------------------------------------------------------ 
  backbone 
  The main part of method code. The consitency of all parameters is checked
  chere, relations between them are resolved and, finally, functions setting
  the base level parameters are called.
  --------------------------------------------------------------*/
void backbone( void )
{
  DB_MSG(("--->backbone"));


  /* Nucleus and  PVM_GradCalConst
     are handled by this funtion: */
  STB_UpdateNuclei(Yes);

  /* handle RF pulse */   

  UpdateRFPulses();

  PVM_NEchoImages = 1;

  /* ------------- spectroscopy part ----------------------- */
  STB_UpdateSpectroscopy( PVM_Nucleus1 );

  /* --------------handling decoupling modules ------------- */

  /* update Encoding parclass for multi receiver experiment */

  STB_UpdateEncoding();

  /* DeadTime */
  updateDeadTime();

  /* repetition time */
  repetitionTimeRels();

  /* set up adjustment list */
  SetAdjustments();

  /* update mapshim parameter class */
  STB_UpdateMapShim(PVM_Nucleus1,"");

  /* set GS parameters */
  SetGSparameters();

  /* set baselevel acquisition parameter */
  SetBaseLevelParam();

  /* set baselevel reconstruction parameter */
  SetRecoParam();

  DB_MSG(("BF1 = %.7f", BF1));
  DB_MSG(("<---backbone"));
}


void UpdateRFPulses(void)
{
  DB_MSG(("--->UpdateRFPulses"));

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

  DB_MSG(("<---UpdateRFPulses"));

  return;
}


void repetitionTimeRels( void )
{
  int i,dim;
  double TotalTime,amplifierenable;

  //  DB_MSG(("--> minRepetitionTimeRels"));

  TotalTime = 0.0;
  amplifierenable = CFG_AmplifierEnable();
  
  PVM_MinRepetitionTime =

    0.02                     +  /* reload B0 */
    amplifierenable          +  /* d8: time before RF-Pulse */
    ExcPulse1.Length         +  
    DeadTime                 +  /* d1 */
    PVM_SpecAcquisitionTime  +
    6.0                      +  
    1.0                      +   /* min d0 */  
    0.01;

  PVM_RepetitionTime = ( PVM_RepetitionTime < PVM_MinRepetitionTime ? 
			 PVM_MinRepetitionTime : PVM_RepetitionTime );
  
  /** Calculate Total Scan Time and Set for Scan Editor **/ 

  dim = PTB_GetSpecDim();
  TotalTime = PVM_RepetitionTime*PVM_NAverages;
  for(i=1; i<dim; i++)
     TotalTime *= PVM_SpecMatrix[i];

  /* updating Dummy Scans afte RepetitionTime and before TotalScanTime */
  STB_UpdateDummyScans(PVM_RepetitionTime);  

  /* updqting triggering*/
  STB_UpdateTriggerModule();

  TotalTime *= (PVM_NRepetitions+PVM_DummyScans);

  PVM_ScanTime = TotalTime;
  UT_ScanTimeStr(PVM_ScanTimeStr,TotalTime);
 

  ParxRelsShowInEditor("PVM_ScanTimeStr");
  ParxRelsMakeNonEditable("PVM_ScanTimeStr");

  //  DB_MSG(("<-- repetitionTimeRels"));
}

void SetAdjustments(void )
{
  DB_MSG(("-->SetAdjustments"));

  PTB_ClearAdjustments();
  STB_ArrayPhaseAppendAdjustment(PVM_EncNReceivers, No);
  PTB_AppendConfiguredAdjustment(per_scan, RCVR);

  DB_MSG(("<--SetAdjustments"));

}

/****************************************************************/
/*		E N D   O F   F I L E				*/
/****************************************************************/








