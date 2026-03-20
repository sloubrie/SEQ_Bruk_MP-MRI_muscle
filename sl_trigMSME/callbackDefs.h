/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/MSME/callbackDefs.h,v $
 *
 * Copyright (c) 1999-2002
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: callbackDefs.h,v 1.24.2.1 2014/08/19 14:12:14 sako Exp $
 *
 ****************************************************************/

/* react on changes of system configuration                  */
relations PVM_SysConfigHandler backbone;

/* Encoding */
relations PVM_EncodingHandler backbone;

/* geometry */
relations PVM_ImageGeometryHandler  backbone;

/* digitizer pars and bandwidth  */
relations PVM_DigHandler backbone;
relations PVM_EffSWh     EffSWhRel;


/* modules */
relations PVM_FatSupHandler     backbone;
relations PVM_MagTransHandler   backbone;
relations PVM_FovSatHandler     backbone;
relations PVM_FlowSatHandler    backbone; 
relations PVM_TriggerHandler    backbone;
relations PVM_EvolutionHandler  backbone;
relations PVM_SelIrHandler      backbone;
relations PVM_DummyScansHandler backbone;

/* other parameters */
relations PVM_NucleiHandler    backbone; 
relations PVM_DeriveGains      backbone;
relations PVM_EchoTime         backbone;
relations PVM_NAverages        NAveragesRels;
relations PVM_MotionSupOnOff   backbone;
relations PVM_RepetitionTime   backbone;
relations PVM_FlipBackOnOff    backbone;
relations PVM_NRepetitions     backbone;
relations PVM_InversionTime    localInversionRel;
relations PVM_NEchoImages      backbone;
relations PVM_EchoPosition     backbone;
relations PVM_FreqDriftHandler backbone;

/* react on parameter adjustments */
relations PVM_AdjResultHandler backbone;

/* relations for mapshim parameter group*/
relations PVM_MapShimHandler backbone;

/* redirection of method specific reconstruction */
relations RecoUserUpdate        RecoDerive;
/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/






