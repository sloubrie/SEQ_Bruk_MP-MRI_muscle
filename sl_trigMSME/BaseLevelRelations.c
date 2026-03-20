/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/MSME/BaseLevelRelations.c,v $
 *
 * Copyright (c) 2002-2009
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: BaseLevelRelations.c,v 1.53 2013/05/08 08:39:45 sako Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: BaseLevelRelations.c,v 1.53 2013/05/08 08:39:45 sako Exp $(C) 2002-2009 Bruker BioSpin MRI GmbH";

#define DEBUG		1
#define DB_MODULE	0
#define DB_LINE_NR	0


#include "method.h"

void SetBaseLevelParam( void )
{

  DB_MSG(("-->SetBaseLevelParam\n"));
 
 
  SetBasicParameters();
    
  SetFrequencyParameters();
 
  SetPpgParameters();
   
  SetGradientParameters();
  
  SetInfoParameters();
 
  SetMachineParameters();
    
  /* setting baselevel parameters used by modules */
  ATB_SetFatSupBaselevel();
  ATB_SetMagTransBaseLevel();
  ATB_SetFovSatBaseLevel();
  ATB_SetFlowSaturationBaseLevel();
  ATB_SetSelIrBaseLevel(GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices ));
  
  #if DEBUG
  printTiming(); 
  #endif

  DB_MSG(("<--SetBaseLevelParam\n"));
  
}


void SetBasicParameters( void )
{
  int spatDim, specDim;
  int nSlices;
  int echo;
  
  DB_MSG(("-->SetBasicParameters\n"));
  
  /* ACQ_dim */
  
  spatDim = PTB_GetSpatDim();

  
  specDim = PTB_GetSpecDim();

  
  ACQ_dim = spatDim + specDim;
  ParxRelsParRelations("ACQ_dim",Yes);

  /* ACQ_dim_desc */
  
  ATB_SetAcqDimDesc( specDim, spatDim, NULL );

  
  /* ACQ_size */

  ATB_SetAcqSize( Spatial, spatDim, PVM_EncMatrix, NULL, No );
    
  /* NSLICES */
  
  nSlices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );

  ATB_SetNSlices( nSlices );

  
  /* NR */
  
  ATB_SetNR( PVM_NRepetitions * PVM_EvolutionCycles );

  
  /* NI */
  
  ATB_SetNI( nSlices * PVM_NEchoImages );

    
  /* AVERAGING */

  switch(PVM_MotionSupOnOff)
  {
  default:
  case Off:
    ATB_SetNA( PVM_NAverages );
    ATB_SetNAE( 1 );
    break;
  case On:
    ATB_SetNAE( PVM_NAverages );
    ATB_SetNA( 1 );
    break;
  }
  
  
  /* ACQ_ns */
  
  ACQ_ns_list_size = PVM_NEchoImages;

  ParxRelsParRelations("ACQ_ns_list_size",Yes);
  for(echo=0; echo<PVM_NEchoImages; echo++)
  {
    ACQ_ns_list[echo] = NEchoesPerEchoImage[echo];
  }
  
  NS = ACQ_ns = ACQ_ns_list[0];
  
  
  
  /* NECHOES */
  
  NECHOES = NEchoes;
  
  
  /* ACQ_obj_order */
  
  PARX_change_dims("ACQ_obj_order",NI);
  
  ATB_SetAcqObjOrder( nSlices, PVM_ObjOrderList, PVM_NEchoImages, 1 );

  
  /* DS */
  
  DS = PVM_DummyScans;
  ACQ_DS_enabled = Yes;
    
  /* ACQ_user_filter for Frequency Drift Correction*/
  if(PVM_FreqDriftYN == Yes)
  {
    ACQ_user_filter = Yes;
    ParxRelsParRelations("ACQ_user_filter", Yes);

    ACQ_user_filter_mode = Standard;  
    
    ACQ_user_filter_memory = For_one_scan;
    sprintf(ACQ_user_filter_name,"FreqDriftCorr");

    sprintf(ACQ_user_filter_setup_name[0],"NoOperation");

    ParxRelsParRelations("ACQ_user_filter_mode", Yes);
  }
  else
  {
    ATB_DisableAcqUserFilter();
  }

  ATB_SetAcqScanSize( One_scan );

  
  DB_MSG(("<--SetBasicParameters\n"));
}

void SetFrequencyParameters( void )
{
  int nslices;
  
  DB_MSG(("-->SetFrequencyParameters\n"));
  
  
  ATB_SetNuc1(PVM_Nucleus1);
  
  sprintf(NUC2,"off");
  sprintf(NUC3,"off");
  sprintf(NUC4,"off");
  sprintf(NUC5,"off");
  sprintf(NUC6,"off");
  sprintf(NUC7,"off");
  sprintf(NUC8,"off");
  
  ATB_SetNucleus(PVM_Nucleus1);
  
  /* setting of SW_h, DIGMOD, DSPFIRM and AQ_mod */

  ATB_SetDigPars();

  
  ACQ_O1_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O1_mode",Yes);
  
  ACQ_O2_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O2_mode",Yes);
  
  ACQ_O3_mode = BF_plus_Offset_list;
  ParxRelsParRelations("ACQ_O3_mode",Yes);
  
  O1 = 0.0;
  O2 = 0.0;
  O3 = 0.0;
  O4 = 0.0;
  O5 = 0.0;
  O6 = 0.0;
  O7 = 0.0;
  O8 = 0.0;

  /* Set BF's to working freuncies on used channels */
  ACQ_BF_enable = No;
  BF1 = PVM_FrqWork[0];
  BF2 = PVM_FrqWork[1];
  /* call relations of BF1 (no need for other BF's) */
  ParxRelsParRelations("BF1", Yes); 

  
  nslices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );

  
  ATB_SetAcqO1List( nslices,
                    PVM_ObjOrderList,
                    PVM_SliceOffsetHz );

  
  ATB_SetAcqO1BList( nslices,
                     PVM_ObjOrderList,
                     PVM_ReadOffsetHz);
  
    
  DB_MSG(("<--SetFrequencyParameters\n"));
}

void SetGradientParameters( void )
{
  int spatDim, dim;

  DB_MSG(("-->SetGradientParameters\n"));
   
  ATB_SetAcqPhaseFactor( 1 );
  
  spatDim = PTB_GetSpatDim();
  
  dim = PARX_get_dim("ACQ_phase_encoding_mode", 1 );
  PARX_change_dims("ACQ_phase_encoding_mode", spatDim );
  PARX_change_dims("ACQ_phase_enc_start", spatDim );
  switch(spatDim)
  {
    case 3:
      ACQ_phase_encoding_mode[2] = User_Defined_Encoding;
      ACQ_phase_enc_start[2] = -1; /* set, but no used */
      ACQ_spatial_size_2 = PVM_EncMatrix[2];
      ParxRelsCopyPar("ACQ_spatial_phase_2","PVM_EncValues2");
      /* no break */
    case 2:
      ACQ_phase_encoding_mode[1] = User_Defined_Encoding;;
      ACQ_phase_enc_start[1] = -1.0; /* set, but no used */
      ACQ_spatial_size_1 = PVM_EncMatrix[1];
      ParxRelsCopyPar("ACQ_spatial_phase_1","PVM_EncValues1");
      /* no break */
    default:
      ACQ_phase_encoding_mode[0] = Read;
      ACQ_phase_enc_start[0] = -1;
  }
  ParxRelsParRelations("ACQ_phase_encoding_mode",Yes);

   
  ATB_SetAcqGradMatrix( PVM_NSPacks, PVM_SPackArrNSlices,
			PtrType3x3 PVM_SPackArrGradOrient[0],
			PVM_ObjOrderList );
    
  ACQ_scaling_read  = 1.0;
  ACQ_scaling_phase = 1.0;
  ACQ_scaling_slice = 1.0;
  
  ACQ_rare_factor = 1;
  
  ACQ_grad_str_X = 0.0;
  ACQ_grad_str_Y = 0.0;
  ACQ_grad_str_Z = 0.0;
  
  strcpy(GRDPROG, "");
  
  ACQ_gradient_amplitude[0] = ExcSliceGrad;
  ACQ_gradient_amplitude[1] = RepetitionSpoiler.ampl;
  ACQ_gradient_amplitude[2] = ReadDephGrad + ReadSpoilGradL;
  ACQ_gradient_amplitude[3] = SliceRephGrad + SliceSpoilGradR;
  ACQ_gradient_amplitude[4] = Phase2DGrad;
  ACQ_gradient_amplitude[5] = ReadGrad;
  ACQ_gradient_amplitude[6] = Phase3DGrad;
  ACQ_gradient_amplitude[7] = SliceSpoilGradL;
  ACQ_gradient_amplitude[8] = ReadSpoilGradR;
  
  DB_MSG(("<--SetGradientParameters\n"));
}

void SetInfoParameters( void )
{
  int slices, i, spatDim;

  DB_MSG(("-->SetInfoParameters\n"));
  
  // initialize ACQ_n_echo_images ACQ_echo_descr
  //            ACQ_n_movie_frames ACQ_movie_descr
  ATB_ResetEchoDescr();
  ATB_ResetMovieDescr();

  spatDim = PTB_GetSpatDim();
  
  ATB_SetAcqMethod();
  
  ATB_SetAcqFov( Spatial, spatDim, PVM_Fov, PVM_AntiAlias );
  
  ACQ_flip_angle = ExcPulse1.Flipangle;

  ACQ_n_echo_images = PVM_NEchoImages;
  ACQ_n_movie_frames = 1;
  
  PARX_change_dims("ACQ_echo_time",PVM_NEchoImages);
  for(i=0; i<PVM_NEchoImages; i++)
    ACQ_echo_time[i] = EffectiveTE[i];
  
  PARX_change_dims("ACQ_inter_echo_time",1);
  ACQ_inter_echo_time[0] = PVM_EchoTime;
  
  PARX_change_dims("ACQ_repetition_time",1);
  ACQ_repetition_time[0] = PVM_RepetitionTime;
  
  PARX_change_dims("ACQ_recov_time",1);
  ACQ_recov_time[0] =  PVM_RepetitionTime - 
	PVM_EchoTime * ((double)NEchoes - 0.5);

  /* calculation of ACQ_time_points */
  ATB_EvolutionSetTimePoints(PVM_NRepetitions, OneRepTime);
  
  PARX_change_dims("ACQ_inversion_time",1);
  ACQ_inversion_time[0] = PVM_InversionTime;

  strcpy(ACQ_fit_function_name,"t2vtr");
  
  ATB_SetAcqSliceAngle( PtrType3x3 PVM_SPackArrGradOrient[0],
			PVM_NSPacks );
  
  ACQ_slice_orient = Arbitrary_Oblique;
  
  ACQ_slice_thick = PVM_SliceThick;
  
  slices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  
  PARX_change_dims("ACQ_slice_offset",slices);
  PARX_change_dims("ACQ_read_offset",slices);
  PARX_change_dims("ACQ_phase1_offset",slices);
  PARX_change_dims("ACQ_phase2_offset",slices);
  
  for(i=0;i<slices;i++)
  {
    ACQ_slice_offset[i]  = PVM_SliceOffset[i];
    ACQ_read_offset[i]   = PVM_ReadOffset[i];
    ACQ_phase1_offset[i] = PVM_Phase1Offset[i];
    ACQ_phase2_offset[i] = PVM_Phase2Offset[i];
  }

  ACQ_read_ext = (int)PVM_AntiAlias[0];
  
  PARX_change_dims("ACQ_slice_sepn", slices==1 ? 1 : slices-1);
  
  if( slices == 1 )
  {
    ACQ_slice_sepn[0] = 0.0;
  }
  else
  {
    for( i=1; i<slices;i++ )
    {
      ACQ_slice_sepn[i-1]=PVM_SliceOffset[i]-PVM_SliceOffset[i-1];
    }
  }
  
  ATB_SetAcqSliceSepn( PVM_SPackArrSliceDistance,
                       PVM_NSPacks );
  
  
  
  ATB_SetAcqPatientPosition();
  
  ACQ_n_t1_points = 1;
  
  if( ParxRelsParHasValue("ACQ_transmitter_coil") == No )
  {
    ACQ_transmitter_coil[0] = '\0';
  }
  
  if( ParxRelsParHasValue("ACQ_contrast_agent") == No )
  {
    ACQ_contrast_agent[0] = '\0';
  }

  if( ParxRelsParHasValue("ACQ_contrast") == No )
  {
    ACQ_contrast.volume = 0.0;
    ACQ_contrast.dose = 0.0;
    ACQ_contrast.route[0] = '\0';
    ACQ_contrast.start_time[0] = '\0';
    ACQ_contrast.stop_time[0] = '\0';
  }
  
  ParxRelsParRelations("ACQ_contrast_agent",Yes);
  
  ACQ_position_X = 0.0;
  ACQ_position_Y = 0.0;
  ACQ_position_Z = 0.0;
  
  PARX_change_dims("ACQ_temporal_delay",1);
  ACQ_temporal_delay[0] = 0.0;
  
  ACQ_RF_power = 0;
  
  ACQ_flipback = No;
  
  ACQ_n_echo_images = PVM_NEchoImages;
  ACQ_n_movie_frames = 1;
  
  
  DB_MSG(("<--SetInfoParameters\n"));
  
}

void SetMachineParameters( void )
{
  
  DB_MSG(("-->SetMachineParameters\n"));

  
  if( ParxRelsParHasValue("ACQ_word_size") == No )
  {
    ACQ_word_size = _32_BIT;
  }
  

  DEOSC = (PVM_AcquisitionTime  + (D[6]+D[5]-40e-6)*1e3 )*1000.0;
  ACQ_scan_shift = -1;
  ParxRelsParRelations("ACQ_scan_shift",Yes);
  
  DE = DE < 6.0 ? 6.0: DE;
  PAPS = QP;
  
   /* ACQ_experiment _mode and ACQ_ReceiverSelect: */

  ATB_SetMultiRec();
 
  DB_MSG(("<--SetMachineParameters\n"));
}

void SetPpgParameters( void )
{
  DB_MSG(("-->SetPpgParameters\n"));
    
  ACQ_vd_list_size=1;
  PARX_change_dims("ACQ_vd_list",1);
  ACQ_vd_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vd_list",Yes);
  
  ACQ_vp_list_size=1;
  PARX_change_dims("ACQ_vp_list",1);
  ACQ_vp_list[0] = 1e-6;
  ParxRelsParRelations("ACQ_vp_list",Yes);
    
  ATB_SetPulprog("sl_trigMSME.ppg");

  double igwt = CFG_InterGradientWaitTime();
  double ramp = CFG_GradientRampTime() + igwt;
  double rise = CFG_GradientRiseTime();
   
  if(PVM_SelIrOnOff)
  {
    D[0] = igwt / 1000.0;
    D[10] = SliceSegEndDelay/1000.0;
  }
  else
  {
    D[0]  = ((PVM_RepetitionTime - PVM_MinRepetitionTime)/NSLICES 
	     + igwt - RRDelay) / 1000.0;
    D[10] = 0.00001;
  }

  D[1]  = (ramp + TeFillDelay1)/1000;
  D[3]  = rise / 1000.0;
  D[5]  = EncGradDur/1000.0;
  D[6]  = (ramp + TeFillDelay2)/1000.0;
  D[2]  = ReadDephDur / 1000.0;
  D[8]  = CFG_AmplifierEnable()/1000.0;
  D[9]  = RepetitionSpoiler.dur/1000.0;
  D[11] = ReadDephDur/1000.0;
 
  /* set shapes and durations of RF pulses     */
  ATB_SetRFPulse("ExcPulse1","ACQ_RfShapes[0]","P[0]");
  ATB_SetRFPulse("RefPulse1","ACQ_RfShapes[1]","P[1]");

  
  DB_MSG(("<--SetPpgParameters\n"));
}


#if DEBUG
#define d(n) (D[n]*1e3)
#define p(n) (P[n]*1e-3)

void printTiming(void)
{
  double te1,te2,aqq=PVM_DigDur, tr;


  /* 90 - 180 */
  te1 = p(0)/2 + d(11) + d(1) + d(3) + p(1)/2;

  /* 180 - 180 */
  te2 = p(1) + aqq + 2*d(3) + 2*d(5) + 2*d(6);


  DB_MSG(("te1: %f should be %f diff %f\n"
	        "te2: %f should be %f diff %f\n",
	  te1,PVM_EchoTime/2,te1-PVM_EchoTime/2,
	  te2,PVM_EchoTime,te2-PVM_EchoTime));

  /* TR */
  tr = 0.02 +                                   /*reload B0*/
       0.02 + d(9) + 2*d(3) + d(8)+             /* before 90 */ 
       p(0) + d(11) + d(1) +                    /* 90 - loopstart */
       NECHOES * te2  +                         /* echo loop */
       d(0);

  if(PVM_FlipBackOnOff == On)
  {
    double tail; /* sequence under "if" in ppg */
 
    tail = d(3) + p(1) + d(1) + d(11) + p(0) + d(3);

    tr+= tail;
  }

  tr *= NSLICES;

  DB_MSG(("TR: %f, should be %f, diff %f", tr, PVM_RepetitionTime, tr-PVM_RepetitionTime));

  return;
}

#undef d
#undef p
#endif
