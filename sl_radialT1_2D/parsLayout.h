/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/UTE/parsLayout.h,v $
 *
 * Copyright (c) 2002-2004
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsLayout.h,v 1.22 2013/05/22 10:55:58 sako Exp $
 *
 * ***************************************************************/

/* ***************************************************************/
/*	PARAMETER CLASS	               			       	 */
/* ***************************************************************/


/*--------------------------------------------------------------*
 * Definition of the PV class...
 *--------------------------------------------------------------*/
parclass
{	 
  RampMode; 
  EffSlewRate;
  Ramptime;
  SliceAlter;	 
  /*********************** Composite Pulse 20180323****************/
  ExcPulseBin1;
  ExcPulseBinAmpl1;
  ExcPulseBinEnum1;
  ExcPulseBinShape1;
  BinOnOff;
  Nbpulse;
/********************End Composite Pulse 20180323****************/
}SliceSelection;

parclass
{
  PVM_EffSWh;
  PVM_AcquisitionTime;
  SliceSelection;
  ReadSpoiling;
  SliceSpoiler;
  RampCompYN;
  RampPoints;
  ReadDephPoints;
  GradSync;
  PVM_MinFov;
  PVM_MinSliceThick;
  GradShape2;
  GradRes;
  DigitizerPars;
  RRDelay;
}
attributes
{
  display_name "Sequence Details";
} Sequence_Details;

parclass
{
  ExcPulse1Enum;
  ExcPulse1;
  ExcPulse1Ampl;
} 
attributes
{
  display_name "RF Pulses";
} RF_Pulses;

parclass
{
  DummyScans_Parameters;
  PVM_TriggerModule;
  Trigger_Parameters;
  PVM_FovSatOnOff;
  Fov_Sat_Parameters;
  PVM_FatSupOnOff;
  Fat_Sup_Parameters;
  PVM_MagTransOnOff;
  Magn_Transfer_Parameters;
  PVM_NMovieFrames;
  PVM_MotionSupOnOff;
  PVM_SelIrOnOff;
  Selective_IR_Parameters;
}Preparation;

parclass
{
  Method;
  YesNoMinEchoTime;
  PVM_EchoTime;
  PVM_MinEchoTime;
  AcqMode;
  PVM_RepetitionTime;
  NPro;
  ProUndersampling;
  PVM_NAverages;
  PVM_NRepetitions;
  PVM_ScanTimeStr;
  PVM_ScanTime;
  PVM_DeriveGains;
  RF_Pulses;
  Nuclei;
  Encoding;
  Sequence_Details;
  ImageGeometry;
  Preparation;
  TrajParameters;
  MapShim;
  /***********************MP2RAGE UTE****************************/
    IrNumber;
    NRegroup;
    MP2RAGE_TR;
    EffectiveTI;
    PVM_NEchoImages;
    AngleMode;
    PVM_DummyScans;
    ReadDephGradLim;
    ReadGradLim;
    
    //VFA
    PVM_ppgPowerList2;
    Angle;
    
    //Spoiler
    RFSpoiling;
    RFPhaseList;
/*********************End MP2RAGE UTE**************************/
  
} MethodClass;

parclass
{
  B0Corr;
  TrajRecoParameters;
}
attributes
{
  display_name "Reconstruction Options";
}MethodRecoGroup;

/*--------------------------------------------------------------*
 * Conflicts
 *--------------------------------------------------------------*/
conflicts
{
  PVM_EchoTime;
  PVM_RepetitionTime;
  PVM_Fov;
  PVM_SliceThick;
};

/* ***************************************************************/
/*	E N D   O F   F I L E					 */
/* ***************************************************************/

