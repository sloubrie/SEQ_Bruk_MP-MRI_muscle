/****************************************************************
 *
 * $Source: /pv/CvsTree/pv/gen/src/prg/methods/SINGLEPULSE/loadMeth.c,v $
 *
 * Copyright (c) 1999-2010
 * Bruker BioSpin MRI GmbH
 * D-76275 Ettlingen, Germany
 *
 * All Rights Reserved
 *
 *
 * $Id: loadMeth.c,v 1.3 2010/06/28 15:04:06 anba Exp $
 *
 ****************************************************************/

static const char resid[] = "$Id: loadMeth.c,v 1.3 2010/06/28 15:04:06 anba Exp $ (C) 1999-2010 Bruker BioSpin MRI GmbH";

#define DEBUG		0
#define DB_MODULE	1
#define DB_LINE_NR	0

/*:=INFO=:*******************************************************
 *
 * Description :
 *   it contains functions necessary for responding to a 'load'
 *	of this method. This function will be automatically
 *	called in response to a method file for this method
 *	having been read.
 *
 *::=info=:******************************************************/

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
 * Global Function: loadMeth
 *
 * Description: This procedure is automatically called in
 *	response to a method file for this method being read.
 *
 * Error History: 
 *
 * Interface:							*/

void loadMeth
  (
  const char *	className
  )

/*:=MPE=:=======================================================*/
{
  DB_MSG(( "-->SINGLEPULSE:loadMeth( %s )", className ));


  if (0 != className)
  {
      if (0 == strcmp( className, "MethodClass"))
      {
          DB_MSG(( "...responding to loadMeth call - I know this class" ));
          initMeth();
      }
      else if (0 == strcmp(className, "MethodRecoGroup"))
      {
          DB_MSG(("...responding to loadMeth call for MethodRecoGroup."));
      }
  }
  else
  {
      DB_MSG(( "...ignoring loadMeth call - I don't know this class" ));
  }

  DB_MSG(( "<--SINGLEPULSE:loadMeth( %s )", className ));
}

/****************************************************************/
/*		E N D   O F   F I L E				*/
/****************************************************************/


