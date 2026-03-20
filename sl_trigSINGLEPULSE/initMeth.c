/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/SINGLEPULSE/initMeth.c,v $
 *
 * Copyright (c) 2001 - 2010
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: initMeth.c,v 1.34 2013/07/03 12:03:41 josh Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: initMeth.c,v 1.34 2013/07/03 12:03:41 josh Exp $ (C) 2001-2004 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	0
#define DB_LINE_NR 0


/****************************************************************/
/****************************************************************/
/*		I N T E R F A C E   S E C T I O N		*/
/****************************************************************/
/****************************************************************/

/****************************************************************/
/*		I N C L U D E   F I L E S			*/
/****************************************************************/

#include "method.h"

/****************************************************************/
/*	I M P L E M E N T A T I O N   S E C T I O N		*/
/****************************************************************/


/****************************************************************/
/*		G L O B A L   F U N C T I O N S			*/
/****************************************************************/


/*:=MPB=:=======================================================*
 *
 * Global Function: initMeth
 *
 * Description: This procedure is implicitly called when this
 *	method is selected.
 *
 * Error History: 
 *
 * Interface:							*/

void initMeth()
/*:=MPE=:=======================================================*/
{


  DB_MSG(( "-->initMeth()" ));

  /* which version of toolboxes should be active */
  PTB_VersionRequirement( Yes,20100101,"");
  
 
  /*  Initialize PVM_NAverages PVM_NRepetitions */
  Local_NAveragesRange();

  if(ParxRelsParHasValue("PVM_NRepetitions") == No)
  PVM_NRepetitions = 1;


  /* Initialisation of rf pulse parameters */

  /*
   * 1: pulses declared in parDefinitions.h 
   * in this case - ExcPulse1. We initalise it to default name, 
   * 5000.0 Hz, and 30 deg flip angle
   * In addition we declare ExcPulse1Enum ExcPulse1Ampl and ExcPulse1Shape
   * to be handled together with pulse struct ExcPulse1. Only if a double
   * array parameter is provided as shape, the pulse supports calculated 
   * shapes.
   */
  
  STB_InitRFPulse("ExcPulse1",      // name of pulse structure
                  "ExcPulse1Enum",  // name of pulse list parameter
                  "ExcPulse1Ampl",  // name of pulse amplitude parameter
                  0,                // name of pulse shape (for calc. pulses)
                  0,                // used for excitation
                  "bp.exc",         // default shape
                  10000.0,          // default bandwidth
                  20.0);            // default pulse angle

  // check valid range for this specific pulse see parsRelations.c
  ExcPulse1Range();

  /* Initialisation PVM_DeriveGains */
  if(ParxRelsParHasValue("PVM_DeriveGains") == No)
    PVM_DeriveGains = Yes;

  /*Initialisation of repetition time*/
  if(ParxRelsParHasValue("PVM_RepetitionTime") == No)
    PVM_RepetitionTime = 1000.0;

  /* Initialisation of nucleus */  
  if (ParxRelsParHasValue("PVM_Nucleus1") == 0)
    PVM_Nucleus1Enum = (STANDARD_NUCLEUS_TYPE)0;

   STB_InitNuclei(1);

  /* initialisation of spectroscopy */
  STB_InitSpectroscopy( 1, 1, 1 ,  PVM_Nucleus1 , 200.0, 1000000 );

  /* Initialize multi receiver parameters */
  
  STB_InitEncoding();
  STB_InitDummyScans(0);

  /* Initialize triggering parameters */
  STB_InitTriggerModule();

    
  /* initialisation of DeadTime */
  DeadTimeRange();
 
  // support of manually adjusted frequency offset

  if(!ParxRelsParHasValue("O1"))
  {
    O1=0.0;
  }

  /* initialisation of FreqDrift */
  STB_InitFreqDriftCorr();

  /* initialize mapshim parameter class */
  STB_InitMapShim();

  /* Once all parameters have initial values, the backbone is called
     to assure they are consistent */
  backbone();
 

  DB_MSG(( "<--initMeth()" ));

}



/****************************************************************/
/*		E N D   O F   F I L E				*/
/****************************************************************/









