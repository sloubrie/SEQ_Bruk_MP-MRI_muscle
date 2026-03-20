/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/UTE/callbackDefs.h,v $
 *
 * Copyright (c) 2001 - 2004
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: callbackDefs.h,v 1.16.2.1 2014/08/19 14:12:14 sako Exp $
 *
 * ***************************************************************/

/* ************************************************************
 * redirection of global parameter groups 
 * ***********************************************************/

/* react on changes of system configuration */
relations PVM_SysConfigHandler backbone;

/* geometry */
relations PVM_ImageGeometryHandler  backbone;

/* nuclei */

relations PVM_NucleiHandler    backbone; 

/* digitizer parameter group */
relations PVM_DigHandler       backbone;

/* ************************************************************
 * redirection of frequency encoding handler
 * to handle the following list of parameters 
 * o PVM_EchoPosition
 * o PVM_AcqStartWaitTime
 * with this approach global default relations and
 * range checkers are used, but the group relations are
 * located in local code:
 * ***********************************************************/
relations PVM_FreqEncodingHandler     backbone;

/* ************************************************************
 *
 * relation redirection of single global parameters used in
 * this method:
 *
 * ***********************************************************/

relations PVM_RepetitionTime          RepetitionTimeRel;
relations PVM_NAverages               AveragesRel;
relations PVM_MotionSupOnOff          backbone;
relations PVM_EchoTime                backbone;
relations PVM_MinEchoTime             backbone;

relations PVM_AcquisitionTime         backbone;
relations PVM_DeriveGains             backbone;
relations PVM_EffSWh                  EffSWhRel;
relations PVM_TriggerHandler          backbone;
relations PVM_FovSatHandler           backbone;
relations PVM_FatSupHandler           backbone;
relations PVM_MagTransHandler         backbone;
relations PVM_NMovieFrames            backbone;
relations PVM_DummyScansHandler       backbone;
relations PVM_SelIrHandler            backbone;

/* 
 * parameters that are used but not shown in editor
 * only the method may change these parameters, they
 * are redirected to the backbone routine.
 */

relations PVM_NRepetitions            backbone;     
relations PVM_MinRepetitionTime       backbone;
relations PVM_NEchoImages             backbone;

/* relation redirection of method specific reconstruction */
relations RecoUserUpdate        RecoDerive;

/* Encoding */
relations PVM_EncodingHandler backbone;

/* Redirect relation for visu creation */
relations VisuDerivePars        deriveVisu;

/* Adjustment related redirections */
relations PVM_TrajHandler             backbone;
relations PVM_TrajRecoHandler         SetRecoParam;
relations PVM_AdjHandler              STB_TrajHandleAdjustmentRequests;
relations PVM_AdjResultHandler        ATB_TrajHandleAdjustmentResults;

/* relations for mapshim parameter group*/
relations PVM_MapShimHandler backbone;
