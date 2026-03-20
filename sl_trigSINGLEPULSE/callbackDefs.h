/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/SINGLEPULSE/callbackDefs.h,v $
 *
 * Copyright (c) 1999-2001
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: callbackDefs.h,v 1.21 2013/06/21 14:21:45 josh Exp $
 *
 ****************************************************************/

/* react on changes of system configuration */
relations PVM_SysConfigHandler backbone;

/* digitizer group */
relations PVM_DigHandler        backbone;

/* spectroscopy group */
relations PVM_SpecHandler       backbone;

/* mapshim */
relations PVM_MapShimHandler    backbone;

/* other parameters */
relations PVM_TriggerHandler    backbone;
relations PVM_NucleiHandler     backbone;
relations PVM_DeriveGains       backbone;
relations PVM_RepetitionTime    backbone;
relations PVM_NAverages         Local_NAveragesHandler;
relations PVM_NRepetitions      backbone;    
relations PVM_EncodingHandler   backbone;
relations PVM_DummyScansHandler backbone;
relations PVM_FreqDriftHandler  backbone;
/* react to adjustment start */
relations PVM_AdjHandler        LocalAdjHandler;
/* react on parameter adjustments */
relations PVM_AdjResultHandler backbone;

/* reconstruction */
relations RecoUserUpdate        DeriveReco;
/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/







