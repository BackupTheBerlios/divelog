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
* Filename : AboutLicenseFrm.cpp                                              *
* CVS Id   : $Id: AboutLicenseFrm.cpp,v 1.1 2002/06/02 09:56:57 grunwalm Exp $  *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for AboutLicenseFrm.cpp                      *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Wed May 29 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#include "AboutLicenseFrm.h"

/* 
 *  Constructs a AboutLicenseFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AboutLicenseFrm::AboutLicenseFrm( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : AboutLicenseBaseFrm( parent, name, modal, fl )
{
}

/*  
 *  Destroys the object and frees any allocated resources
 */
AboutLicenseFrm::~AboutLicenseFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * protected slot
 */
void AboutLicenseFrm::showHelp()
{
    qWarning( "AboutLicenseFrm::showHelp() not yet implemented!" ); 
}

