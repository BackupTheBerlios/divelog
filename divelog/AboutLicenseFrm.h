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
* Filename : AboutLicenseFrm.h                                                *
* CVS Id   : $Id: AboutLicenseFrm.h,v 1.1 2002/06/02 09:56:57 grunwalm Exp $  *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for AboutLicenseFrm.cpp                      *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Wed May 29 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#ifndef ABOUTLICENSEFRM_H
#define ABOUTLICENSEFRM_H
#include "AboutLicenseBaseFrm.h"

class AboutLicenseFrm : public AboutLicenseBaseFrm
{ 
    Q_OBJECT

public:
    AboutLicenseFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~AboutLicenseFrm();

protected slots:
    void showHelp();

};

#endif // ABOUTLICENSEFRM_H
