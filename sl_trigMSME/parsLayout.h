/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/MSME/parsLayout.h,v $
 *
 * Copyright (c) 1999-2002
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsLayout.h,v 1.32 2013/05/22 11:09:44 sako Exp $
 *
 ****************************************************************/

/****************************************************************/
/*	PARAMETER CLASSES				       	*/
/****************************************************************/


/*--------------------------------------------------------------*
 * Definition of the PV class...
 *--------------------------------------------------------------*/

parclass
{
  PVM_EffSWh;
  EncGradDur;
  PVM_AcquisitionTime;
  PVM_MinEchoTime;
  PVM_MinFov;
  PVM_MinSliceThick;
  RepetitionSpoiler;
  DigitizerPars;
  EchoSpoilingAuto;
  EchoSpoilingSlice;
  EchoSpoilingSliceEff;                         
  EchoSpoilingRead;
  EchoSpoilingReadEff;     
  LoopListe;
  DelayListe;
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
  RefPulse1Enum;
  RefPulse1;
  RefPulse1Ampl;
} 
attributes
{
  display_name "RF Pulses";
} RF_Pulses;

parclass
{
  PVM_NEchoImages;
  ConstNEchoes;
  NEchoesPerEchoImage;
  NEchoes;
  RRDelay;
  EffectiveTE;
  NSegments;
  NEchoPerSegment;
  SegmentTime;
} Echoes;

parclass
{

  DummyScans_Parameters;
  PVM_FreqDriftYN;
  
  PVM_TriggerModule;
  Trigger_Parameters;

  PVM_EvolutionOnOff;
  Evolution_Parameters;

  PVM_SelIrOnOff;
  Selective_IR_Parameters;

  PVM_FatSupOnOff;
  Fat_Sup_Parameters;
 
  PVM_MagTransOnOff;
  Magn_Transfer_Parameters;
 
  PVM_FovSatOnOff;
  Fov_Sat_Parameters;
 
  PVM_InFlowSatOnOff;
  Flow_Sat_Parameters;

  PVM_MotionSupOnOff;
  PVM_FlipBackOnOff;
 
} Preparation;

parclass
{
  Method;
  PVM_EchoTime;
  EffectiveTE;
  PVM_RepetitionTime;
  PVM_NAverages;
  PVM_NRepetitions;
  PVM_ScanTimeStr;
  PVM_ScanTime;
  PVM_DeriveGains;
  RF_Pulses;
  Nuclei;
  Encoding;
  Echoes;
  Sequence_Details;
  ImageGeometry;
  Preparation;
  MapShim;
} MethodClass;

conflicts
{
  PVM_EchoTime;
  PVM_RepetitionTime;
  PVM_Fov;
  PVM_SliceThick;
};

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/



