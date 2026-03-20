/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/MSME/initMeth.c,v $
 *
 * Copyright (c) 2002-2005
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: initMeth.c,v 1.41 2013/05/22 11:09:44 sako Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: initMeth.c,v 1.41 2013/05/22 11:09:44 sako Exp $(C) 2002 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	1
#define DB_LINE_NR	0


#include "method.h"

/*:=MPB=:=======================================================*
 *
 * Global Function: initMeth
 *
 * Description: This procedure is implicitly called when this
 *	method is selected.
 *
 * Error History: 
 *
 * Interface:							*/

void initMeth()
/*:=MPE=:=======================================================*/
{
  int dimRange[2]   = {2,3};
  int lowMat[3]     = {32, 32, 8};
  int upMat[3]      = {2048, 2048, 512};
  int defaultMat[3] = {256, 256, 64};
  
  DB_MSG(( "-->initMeth\n" ));
  
  /* which version of toolboxes should be active */
  PTB_VersionRequirement( Yes,20100101,""); 
  
  STB_InitFreqDriftCorr();
  
  /*  initialize local and redirected parameters */
  NAveragesRange();
  if(ParxRelsParHasValue("PVM_NRepetitions") == No)
    PVM_NRepetitions = 1;
  if(ParxRelsParHasValue("PVM_RepetitionTime") == No)
    PVM_RepetitionTime = 1000.0;
  if(ParxRelsParHasValue("PVM_EchoTime") == No)
    PVM_EchoTime = 20.0;
  if(ParxRelsParHasValue("PVM_DeriveGains") == No)
    PVM_DeriveGains = Yes;
    
 
  /* encoding group */
  STB_InitEncoding( 2, dimRange, lowMat, upMat, defaultMat);  
  
  

  /* Initialisation of rf pulse parameters */

  STB_InitRFPulse("ExcPulse1",      // name of pulse structure
                  "ExcPulse1Enum",  // name of pulse list parameter
                  "ExcPulse1Ampl",  // name of pulse amplitude parameter
                  "ExcPulse1Shape", // name of pulse shape (for calc. pulses)
                  0,                // used for excitation
                  "Calculated",     // default shape
                  2000.0,           // default bandwidth
                  90.0);            // default pulse angle

  // check valid range for this specific pulse see parsRelations.c
  ExcPulse1Range();

  STB_InitRFPulse("RefPulse1",      // name of pulse structure
                  "RefPulse1Enum",  // name of pulse list parameter
                  "RefPulse1Ampl",  // name of pulse amplitude parameter
                  "RefPulse1Shape", // name of pulse shape (for calc. pulses)
                  1,                // used for refocusing
                  "Calculated",     // default shape
                  2000.0,           // default bandwidth
                  180.0);           // default pulse angle

  RefPulse1Range();
 
 
  /* Initialisation of nucleus and frequency */  
  STB_InitNuclei(1);
 
  
  /* Initialisation of spoilers */
  MRT_InitSpoiler("RepetitionSpoiler");  
  if (!ParxRelsParHasValue("EchoSpoilingAuto"))
    EchoSpoilingAuto = Yes;
  
  /* Initialisation of geometry parameters */
  STB_InitImageGeometry();
  
  /* initialize digitizer parameter */

  STB_InitDigPars();
  EffSWhRange();

  /* echo parameters */ 

  if (ParxRelsParHasValue("ConstNEchoes") == 0)
    ConstNEchoes = Yes;
  if (ParxRelsParHasValue("PVM_NEchoImages") == 0)
    PVM_NEchoImages = 1;
  if(ParxRelsParHasValue("PVM_FlipBackOnOff") == No)
    PVM_FlipBackOnOff = Off;

  ParxRelsMakeNonEditable("NEchoes");
  ParxRelsMakeNonEditable("PVM_MinEchoTime");
  ParxRelsMakeNonEditable("EncGradDur");  
  ParxRelsMakeNonEditable("PVM_EchoPosition");  
  
  /* not a csi experiment */
  PTB_SetSpectrocopyDims( 0, 0 );
  
  /* Initialisation of modules */
  STB_InitFatSupModule();
  STB_InitMagTransModule();
  STB_InitFovSatModule();
  STB_InitFlowSaturationModule();
  STB_InitTriggerModule();
  STB_InitEvolutionModule();
  STB_InitSelIrModule();
  STB_InitDummyScans(1000.0);
  
  /* initialize mapshim parameter class */
  STB_InitMapShim();
  
  /* 
   * Once all parameters have initial values, the backbone is called
   * to assure they are consistent 
   */
 if(ParxRelsParHasValue("NSegments") == No)
    NSegments=1;
  
 if(ParxRelsParHasValue("RRDelay") == No)
    RRDelay=333.0;
  
  backbone();
  

  DB_MSG(( "<--initMeth\n" ));

}





/****************************************************************/
/*		E N D   O F   F I L E				*/
/****************************************************************/

