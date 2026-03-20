/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/SINGLEPULSE/parsLayout.h,v $
 *
 * Copyright (c) 1999-2003
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsLayout.h,v 1.23 2013/06/21 14:21:45 josh Exp $
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
  DeadTime;
  PVM_FreqDriftYN;
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
  PVM_TriggerModule;
  Trigger_Parameters;
  
  Method;
  PVM_RepetitionTime;
  PVM_NAverages;
  PVM_NRepetitions;
  DummyScans_Parameters;
  PVM_ScanTimeStr;
  PVM_ScanTime;
  PVM_DeriveGains;
  RF_Pulses;
  Nuclei;
  Spectroscopy;
  Encoding;
  Sequence_Details;
  PVM_ArrayPhase;
  MapShim;
} MethodClass;

// parameters that should be tested after any editing
conflicts
{
  PVM_RepetitionTime;
};

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/



