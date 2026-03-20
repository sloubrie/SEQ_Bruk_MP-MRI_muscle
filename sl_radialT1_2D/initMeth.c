/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/UTE/initMeth.c,v $
 *
 * Copyright (c) 2002-2004
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: initMeth.c,v 1.32 2013/05/22 10:55:58 sako Exp $
 *
 * ***************************************************************/

static const char resid[] = "$Id: initMeth.c,v 1.32 2013/05/22 10:55:58 sako Exp $ (C) 2004 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE       0
#define DB_LINE_NR	0

#include "method.h"


void initMeth()
/*:=MPE=:=======================================================*/
{
  int dimRange[2]   = {2, 2};
  int lowMat[3]     = {16, 16, 16};
  int upMat[3]      = {1024, 1024, 1024};
  int defaultMat[3] = {128, 128, 128}; 


  DB_MSG(( "--> initMeth" ));


  /* which version of toolboxes should be active */
  PTB_VersionRequirement( Yes,20100101,"");


  /* Initialisation of nucleus */  
  STB_InitNuclei(1);
  
  /* initialize rf pulse parameters */  
  STB_InitRFPulse("ExcPulse1",      // name of pulse structure
                  "ExcPulse1Enum",  // name of pulse list parameter
                  "ExcPulse1Ampl",  // name of pulse amplitude parameter
                  "ExcPulse1Shape", // name of pulse shape (for calc. pulses)
                  0,                // used for excitation
                  "Calculated",     // default shape
                  8000.0,           // default bandwidth
                  7.0,              // default pulse angle
                  2);               // default pulse sharpness
  
  /*********************** Composite Pulse 20180323****************/
  STB_InitRFPulse("ExcPulseBin1",
                  "ExcPulseBinEnum1",
                  "ExcPulseBinAmpl1",
                  "ExcPulseBinShape1",
                  1,
                  "bp",
                  4000.0,
                  180.0);
/********************End Composite Pulse 20180323****************/

  // check valid range for this specific pulse 
  ExcPulse1Range();
  
  if(ParxRelsParHasValue("PVM_DeriveGains") == No)
    PVM_DeriveGains = Yes;
  
  /* initialize digitizer parameter */
  EffSWhRange(); 
  STB_InitDigPars();

  /* encoding group */
  STB_InitEncoding(2, dimRange, lowMat, upMat, defaultMat);  

  /* initialize local parameters */
  if(!ParxRelsParHasValue("RampCompYN"))
    RampCompYN=Yes;

  if(ParxRelsParHasValue("AcqMode") == No)
    AcqMode = FID;

  if(ParxRelsParHasValue("SliceAlter") == 0)
    SliceAlter = No;

  if(ParxRelsParHasValue("GradSync") == 0)
    GradSync = No;

  if(!ParxRelsParHasValue("B0Corr"))
    B0Corr=Yes;

  ProUnderRange();
  EchoPositionRange();
  RampModeInitRel();

  GradRes = MAX_OF(0.005,CFG_GradientShapeResolution());
    
  /* init geometry parameters */
  STB_InitImageGeometry();
  
  /* geometry editor */
  GTB_GeoObjFreezePos0("PVM_SliceGeoObj", No);
  GTB_GeoObjFreezePos1("PVM_SliceGeoObj", No);
  PTB_SetGeoObjShape("PVM_SliceGeoObj", Cylinder_In_GobjShape);

  /* init spectroscopy parameters (no csi) */
  PTB_SetSpectrocopyDims( 0, 0 );

  /* initialize standard imaging parameters NA TR TE */
  if(ParxRelsParHasValue("PVM_NMovieFrames") == No)
    PVM_NMovieFrames = 1;
 
  if(ParxRelsParHasValue("PVM_NRepetitions") == No)
    PVM_NRepetitions = 1;

  if(ParxRelsParHasValue("YesNoMinEchoTime") == 0)
    YesNoMinEchoTime = Yes;

  if (ParxRelsParHasValue("PVM_MotionSupOnOff") == 0)
     PVM_MotionSupOnOff = Off;

  /***********************MP2RAGE UTE****************************/
if(!ParxRelsParHasValue("IrNumber"))
    IrNumber = 1;
  
if(!ParxRelsParHasValue("NRegroup"))
    NRegroup = 128;
  
if(!ParxRelsParHasValue("PVM_NEchoImages"))
    PVM_NEchoImages = 20;

      /* Angles init */
if(ParxRelsParHasValue("Angle") == No)
  {   
      PARX_change_dims("Angle", PVM_NEchoImages);
      Angle[0]=7;
      if (PVM_NEchoImages>1)
        Angle[1]=7;
  }
  
if(!ParxRelsParHasValue("ReadDephGradLim"))
    ReadDephGradLim = 30;
  
if(!ParxRelsParHasValue("ReadGradLim"))
    ReadGradLim = 30; 
  /***********************RF spoiling****************************/   
  
  if(!ParxRelsParHasValue("RFSpoiling"))
    RFSpoiling = Yes;
/***********************End MP2RAGE UTE************************/
  
  RepetitionTimeRange();
  AveragesRange();

  /* Initialisation of spoilers */
  if(!ParxRelsParHasValue("ReadSpoiling"))
    ReadSpoiling = 1.0;
  MRT_InitSpoiler("SliceSpoiler");



  /* Initialization of trajectory module */
  STB_InitTraj(1, 1, 1, 1, No, 2, Yes, 0, NULL, No, 0,
    "GradShape2", NULL, NULL,
    "GradAmpR","GradAmpP");

  /* Initialisation of modules */
  STB_InitTriggerModule();
  STB_InitFovSatModule();
  STB_InitFatSupModule();
  STB_InitMagTransModule();
  STB_InitDummyScans(1000.0);
  STB_InitSelIrModule();

  /* initialize mapshim parameter class */
  STB_InitMapShim();

  ParxRelsMakeNonEditable("PVM_MinEchoTime,NPro,PVM_AntiAlias");

  /* 
   * Once all parameters have initial values, the backbone is called
   * to assure they are consistent 
   */
  if(ParxRelsParHasValue("RRDelay") == No)
  RRDelay=333.0;
  
  backbone();
 

  DB_MSG(( "<-- initMeth" ));

}

/****************************************************************/
/*		E N D   O F   F I L E				*/
/****************************************************************/


