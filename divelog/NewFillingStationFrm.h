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

#ifndef NEWFILLINGSTATIONFRM_H
#define NEWFILLINGSTATIONFRM_H
#include "NewFillingStationBaseFrm.h"

class NewFillingStationFrm : public NewFillingStationBaseFrm
{ 
    Q_OBJECT

public:
    NewFillingStationFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    NewFillingStationFrm( const QString& stationName , QWidget* parent = 0, const char* name = 0);
    ~NewFillingStationFrm();

protected slots:
    void showHelp();

private slots:
    void accept();

private:
    void init();
};

#endif // NEWFILLINGSTATIONFRM_H
