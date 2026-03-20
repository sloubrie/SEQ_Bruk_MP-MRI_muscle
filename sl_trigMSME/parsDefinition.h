/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/MSME/parsDefinition.h,v $
 *
 * Copyright (c) 1999-2003
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: parsDefinition.h,v 1.22 2013/05/08 08:39:45 sako Exp $
 *
 ****************************************************************/



/****************************************************************/
/* INCLUDE FILES						*/
/****************************************************************/
double parameter ExcSliceGrad;
double parameter ReadDephGrad;
double parameter SliceRephGrad;
double parameter ReadGrad;
double parameter Phase2DGrad;
double parameter Phase3DGrad;
double parameter TeFillDelay1;
double parameter TeFillDelay2;
double parameter ReadDephDur;
double parameter OneRepTime;
double parameter SliceSpoilGradL;
double parameter SliceSpoilGradR;
double parameter ReadSpoilGradL;
double parameter ReadSpoilGradR;

int parameter LoopListe[];
double parameter DelayListe[];

int parameter 
{
    display_name "NSegments";
    relations backbone;
} NSegments;

int parameter 
{
    display_name "NEchoPerSegment";
    relations backbone;
} NEchoPerSegment;

double parameter 
{
    display_name "SegmentTime";
    relations backbone;
} SegmentTime;

double parameter 
{
    display_name "RRDelay";
    relations backbone;
} RRDelay;

double parameter
{
  display_name "Required Slice Spoiling";
  short_description "Required dephasing of slice spoiler.";
  relations backbone;
  units "{cycles}";
  format "%.3f";
  minimum 0.0 outofrange nearestval;
  maximum 20.0 outofrange nearestval;
} EchoSpoilingSlice;

double parameter
{
  display_name "Effective Slice Spoiling";
  short_description "Effective dephasing of slice spoiler.";
  relations backbone;
  units "{cycles}";
  format "%.3f";
} EchoSpoilingSliceEff;

double parameter
{
  display_name "Required Read Spoiling";
  short_description "Required dephasing by read spoiler.";
  relations backbone;
  units "{cycles}";
  format "%.3f";
  minimum 0.0 outofrange nearestval;
  maximum 20.0 outofrange nearestval;
} EchoSpoilingRead;

double parameter
{
  display_name "Effective Read Spoiling";
  short_description "Effective dephasing by read spoiler.";
  relations backbone;
  units "{cycles}";
  format "%.3f";
} EchoSpoilingReadEff;

YesNo parameter
{
  display_name "Auto Echo Spoiler";
  short_description "Automatic setting of echo spoiler.";
  relations backbone;
} EchoSpoilingAuto;

double parameter
{
  display_name "Encoding Duration";
  short_description "The duration of the encoding gradient.";
  relations backbone;
  units "ms";
  format "%.3f";
}EncGradDur;

double parameter
{
  display_name "Effective Echo Time";
  format "%.2f";
  units "ms";
  relations effTErels; 
} EffectiveTE[];

PVM_SPOILER_TYPE parameter 
{
  display_name "Repetition Spoiler";
  relations RepetitionSpoilerRel;
}RepetitionSpoiler;



PV_PULSE_LIST parameter
{
  display_name "Excitation Pulse Shape";
  relations    ExcPulse1EnumRelation;
}ExcPulse1Enum;


PVM_RF_PULSE parameter
{
  display_name "Excitation Pulse";
  relations    ExcPulse1Relation;
}ExcPulse1;

PVM_RF_PULSE_AMP_TYPE parameter
{
  display_name "Exc Pulse Amplitude";
  relations ExcPulse1AmplRel;
}ExcPulse1Ampl;

double parameter
{
  relations backbone;
}ExcPulse1Shape[];

PV_PULSE_LIST parameter
{
  display_name "Refocusing Pulse Shape";
  relations    RefPulse1EnumRelation;
}RefPulse1Enum;


PVM_RF_PULSE parameter
{
  display_name "Refocusing Pulse";
  relations    RefPulse1Relation;
}RefPulse1;

PVM_RF_PULSE_AMP_TYPE parameter
{
  display_name "Rfc Pulse Amplitude";
  relations RefPulse1AmplRel;
}RefPulse1Ampl;

double parameter
{
  relations backbone;
}RefPulse1Shape[];



int parameter
{
  display_name "Echo Averages";
  format "%d";
  relations backbone;
} NEchoesPerEchoImage[];

YesNo parameter 
{
  display_name "Equal Averaging";
  relations backbone;
} ConstNEchoes;

int parameter
{
  display_name "Number of Echoes";
} NEchoes;

double parameter
{
  display_name "Inter Slice Delay";
  relations backbone;
  units "ms";
  format "%.2f";
}SliceSegDur;

double parameter SliceSegDelay;
double parameter MinSliceSegDur;

double parameter SliceSegEndDelay;

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/

