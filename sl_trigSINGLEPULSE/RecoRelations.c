#/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/SINGLEPULSE/RecoRelations.c,v $
 *
 * Copyright (c) 2001 - 2003
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: RecoRelations.c,v 1.10.2.1 2014/12/17 18:17:31 josh Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: RecoRelations.c,v 1.1.2.2 2001/01/11 MAWI ";

#define DEBUG           0
#define DB_MODULE       0
#define DB_LINE_NR      0

#include "method.h"

void SetRecoParam( void )
{


  DB_MSG(("-->SetRecoParam\n"));

  /* set baselevel reconstruction parameter */
  /* default initialization of reco based on acqp pars allready set */
  
  ATB_InitUserModeReco(
      1,
      0,
      PVM_SpecMatrix, // acq size
      PVM_SpecMatrix, // image size
      NULL, //effAntiAlias=1,
      NULL, //effPftOverscans=halfsize,
      1,
      NULL,
      1,
      NULL,  //linear order,
      NULL,  //linear order (not used)
      NULL,  //linear order (not used)
      PVM_EncNReceivers,
      PVM_EncChanScaling,
      0,
      1);

  /* complex channel combination: */
  RecoCombineMode = AddImages;

  /* configure information available during setup mode */

  GS_info_dig_filling     = Yes;
  ParxRelsParRelations("GS_info_dig_filling",Yes); 
  GS_info_normalized_area = Of_raw_data;
  ParxRelsParRelations("GS_info_normalized_area",Yes); 

  /* Setting phase offsets for multi RX channel combination */
  ATB_ArrayPhaseSetRecoPhase();    

 DB_MSG(("<--SetRecoParam\n"));
}



void DeriveReco(void)
{
  DB_MSG(("-->DeriveReco"));

  if (RecoUserUpdate == No)
  {
    DB_MSG(("<--RecoDerive: no update"));
    return;
  }

  /* standard settings for reconstruction */  
  if(RecoPrototype == No)
    SetRecoParam();

  ParxRelsParRelations("RecoUserUpdate", Yes);

  DB_MSG(("<--DeriveReco"));
}
