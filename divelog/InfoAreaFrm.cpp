/* Copyright (C) 2002 Markus Grunwald */
/* Copyright (C) 1995-2000 Trolltech AS.  All rights reserved. */
/* Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB */

/*************************************************************************
This file is part of divelog.

divelog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

divelog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with divelog; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/

/******************************************************************************
* Filename : infoareafrm.cpp                                                                 *
* CVS Id   : $Id: InfoAreaFrm.cpp,v 1.6 2002/06/02 09:55:13 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Supply a main info-field for the application             *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Nov  6 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *infoareafrm_cvs_id="$Id: InfoAreaFrm.cpp,v 1.6 2002/06/02 09:55:13 grunwalm Exp $";
#include "InfoAreaFrm.h"

/* 
 *  Constructs a InfoAreaFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
InfoAreaFrm::InfoAreaFrm( QWidget* parent,  const char* name, WFlags fl )
    : InfoAreaBaseFrm( parent, name, fl )
{
}

// -------------------------------------------------
// Use : Common initialisation for different constructors
// -------------------------------------------------
void InfoAreaFrm::init()
{
    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    infoareafrm_cvs_id+=0;
}



/*  
 *  Destroys the object and frees any allocated resources
 */
InfoAreaFrm::~InfoAreaFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

