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

#ifndef NEWDIVECOMPUTERFRM_H
#define NEWDIVECOMPUTERFRM_H
#include "NewDiveComputerBaseFrm.h"
#include <vector>

using namespace std;

class NewDiveComputerFrm : public NewDiveComputerBaseFrm
{ 
    Q_OBJECT

public:
    NewDiveComputerFrm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    NewDiveComputerFrm( const QString& serialNumber,
                        const QString& computerName=0,
                        QWidget* parent = 0, const char* name = 0);
    ~NewDiveComputerFrm();

    unsigned int diver_number() const;

protected slots:
    void showHelp();
    void addDiverDlg();

private slots:
    void accept();

private:
    void init();
    void initDiverCombo();

    vector< int > indexCoder;
};

#endif // NEWDIVECOMPUTERFRM_H
