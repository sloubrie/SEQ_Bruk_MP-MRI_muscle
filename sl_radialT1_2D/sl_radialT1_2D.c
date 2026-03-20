/* ***************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/UTE/UTE.c,v $
 *
 * Copyright (c) 1999-2004
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 * $Id: UTE.c,v 1.4 2009/07/09 09:54:26 sako Exp $
 *
 * ***************************************************************/

method sl_radialT1_2D
{

/****************************************************************/
/*	TYPE DEFINITIONS					*/
/****************************************************************/



#include "bruktyp.h"
#include "Visu/VisuTypes.h"
#include "acqutyp.h"
#include "acqumtyp.h"
#include "recotyp.h" 
#include "subjtyp.h" 
#include "ta_config.h" 
#include "methodTypes.h"
#include "adjManagerDefs.h"
#include "adjManagerTypes.h"

/****************************************************************/
/*	PARAMETER DEFINITIONS					*/
/****************************************************************/


/*--------------------------------------------------------------*
 * Include external definitions for parameters in the parclass
 * ACQU ACQP GO GS RECO RECI PREEMP CONFIG
 *--------------------------------------------------------------*/
#include "proto/config_extern.h"
#include "proto/acq_extern.h"
#include "proto/subj_extern.h"
#include "proto/visu_extern.h"

/*--------------------------------------------------------------*
 * Include references to the standard method parameters
 *--------------------------------------------------------------*/
#include "proto/pvm_extern.h"
#include "proto/adj_extern.h"
/*--------------------------------------------------------------*
 * Include references to any method specific parameters
 *--------------------------------------------------------------*/

#include "methodFormat.h"
#include "parsTypes.h"
#include "parsDefinition.h"

/****************************************************************/
/*	RE-DEFINITION OF RELATIONS				*/
/****************************************************************/

#include "callbackDefs.h"

/****************************************************************/
/*	PARAMETER CLASSES					*/
/****************************************************************/
#include "methodClassDefs.h"
#include "seqApiClassDefs.h"
#include "modulesClassDefs.h"
#include "parsLayout.h"

};

/****************************************************************/
/*	E N D   O F   F I L E					*/
/****************************************************************/
