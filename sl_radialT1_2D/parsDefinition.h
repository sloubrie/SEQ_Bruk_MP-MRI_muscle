/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/UTE/parsDefinition.h,v $
 *
 * Copyright (c) 2004
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsDefinition.h,v 1.17 2013/08/29 12:31:35 sako Exp $
 *
 * ***************************************************************/



/****************************************************************/
/* INCLUDE FILES						*/
/****************************************************************/

int    parameter {editable false;}RampPoints;
int    parameter {editable false;}ReadDephPoints;
double parameter {editable false;}RampCompTime;
double parameter {editable false;}GrShapeT1;
double parameter {editable false;}GrShapeT2;
double parameter {editable false;}GrShapeT3;
double parameter {editable false;}GrShapeG2;
double parameter {editable false;}GradAmpR[];
double parameter {editable false;}GradAmpP[];
double parameter {editable false;}GradShape1[];
double parameter {editable false;}GradShape2[];
double parameter {editable false;}GrShape1Time;
double parameter {editable false;}GrShape2Time;
double parameter {editable false;}GradRes;
double parameter {editable false;}Grid;

double parameter {editable false;}ReadDephTime;
double parameter {editable false;}ReadDephGrad;
double parameter {editable false;}PhaseDephGrad;
double parameter ReadDephGradLim;
double parameter ReadGradLim; 
double parameter {editable false;}ReadGrad;
double parameter {editable false;}PhaseGrad;
double parameter {editable false;}TeFillDelay;

int parameter 
{
  relations backbone;
}GradShape1Size;

int parameter 
{
  relations backbone;
}GradShape2Size;

ACQ_MODE parameter
{
  display_name "Acquisition Mode";
  relations backbone;
} AcqMode;

int parameter
{
  display_name "Projections";
  format "%d";
  relations backbone;
}NPro;

double parameter
{
  display_name "RRDelay";
  relations backbone;
}RRDelay;

double parameter
{
  display_name "Polar Undersampling";
  format "%.2f";
  relations ProUnderRel;
}ProUndersampling;

YesNo parameter
{
  display_name "Minimize TE";
  relations backbone;
}YesNoMinEchoTime;

YesNo parameter
{
  display_name "Gradient Synchronization";
  relations backbone;
}GradSync;

YesNo parameter
{
  display_name "Ramp Sampling Compensation";
  short_description "Compensation of resolution loss caused by ramp sampling.";
  relations backbone;
}RampCompYN;

YesNo parameter 
{
  display_name "B0 Correction";
}B0Corr;

double parameter
{
  display_name "Read Spoiling";
  short_description "Readout gradient spoiling after acquisition.";
  units "{cycles}/{pixel}";
  format "%.1f";
  minimum 0.0;
  maximum 100.0;
  relations backbone;
} ReadSpoiling;

double parameter ReadSpoilDur;

// slice selection parameters
double parameter ExcSliceGradLim;
double parameter ExcSliceRephGradLim;
double parameter ExcSliceGrad;

PVM_SPOILER_TYPE parameter 
{
  display_name "Slice Spoiler";
  relations SliceSpoilerRel;
}SliceSpoiler;

RAMP_MODE parameter
{
  display_name "Ramp Mode";
  relations    RampModeRel;
} RampMode;

double parameter
{
  display_name "Effective Slew Rate";
  relations RampModeRel;
  units "%";
  format "%f";
}EffSlewRate;

double parameter
{
  display_name "Ramp Time";
  relations RampModeRel;
  units "ms";
  format "%.3f";
}Ramptime;

YesNo parameter
{
  display_name "Slice Gradient Alternation";
  relations backbone;
}SliceAlter;

// excitation pulse parameters
PV_PULSE_LIST parameter
{
  display_name "Excitation Pulse Shape";
  relations    ExcPulse1EnumRel;
}ExcPulse1Enum;


PVM_RF_PULSE parameter
{
  display_name "Excitation Pulse";
  relations    ExcPulse1Rel;
}ExcPulse1;

PVM_RF_PULSE_AMP_TYPE parameter
{
  display_name "RF Pulse Amplitude";
  relations ExcPulse1AmplRel;
}ExcPulse1Ampl;

double parameter
{
  relations backbone;
}ExcPulse1Shape[];

/***********************MP2RAGE UTE****************************/
int parameter
{
  display_name "GreLength";
  short_description "Echoes per train.";
  format "%d";
  relations backbone;
}NRegroup;

int parameter
{
  display_name "IrNumber";
  short_description "Number of repetitions NPro/GreLength.";
  format "%d";
  relations backbone;
}IrNumber;

int parameter
{
  display_name "Projections";
  short_description "Ideal NPro, without UnderSampling.";
  format "%d";
  relations backbone;
}NyquistPro;

double parameter
{
  short_description "Time between two inversions.";
  format "%.2f";
  relations backbone;
}MP2RAGE_TR;

double parameter
{
  
  format "%.2f";
  relations backbone;
}MinMP2RAGE_TR;

/*SelIr*/
double parameter SliceSegDur;

// Mp2rage delays
double parameter
{
  display_name "TI";
  short_description "Mean inverion time.";
  format "%.2f";
  units "ms";
  relations backbone;
}EffectiveTI[];

double parameter
{
  display_name "IRVarDelay";
  short_description "Delay before next GRE train.";
  format "%.2f";
  units "s";
  relations backbone;
}IRVarDelay[];  
  
Anglemode parameter
{
 display_name "Angle Mode";
 relations backbone;
}AngleMode;

double parameter
{
  display_name "Angle";
  short_description "Angle value.";
  units "deg";
}Angle[];

/*********************** Composite Pulse 20180323****************/

PVM_RF_PULSE parameter
{
  display_name "Excitation Pulse Binomial 1";
  relations    ExcPulseBinRelation;
}ExcPulseBin1;

PV_PULSE_LIST parameter
{
  display_name "Excitation Shape Binomial 1";
  short_description "Shape of excitation pulse.";
  relations ExcPulseBinEnumRelation;
} ExcPulseBinEnum1;

PVM_RF_PULSE_AMP_TYPE parameter
{
  display_name "Excitation Pulse Amplitude Binomial 1";
  relations ExcPulseBinAmplRelation;
} ExcPulseBinAmpl1;

int parameter Nbpulse;

YesNo parameter
{
  display_name "BinOnOff";
  relations backbone;
}BinOnOff;

double parameter
{
  editable false;
} ExcPulseBinShape1[];

/*********************** RF Spoiling     ************************/

YesNo parameter RFSpoiling;

double parameter
{
  short_description "Phase for RF spoiling.";
  units "deg";
}RFPhaseList[];

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/


