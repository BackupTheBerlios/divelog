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
* Filename : newfillingstationfrm.cpp                                         *
* CVS Id   : $Id: NewFillingStationFrm.cpp,v 1.5 2002/06/02 09:55:13 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Profide a dialog for entering information about a filling*
*                    station.                                                 *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Nov  6 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *newfillingstationfrm_cvs_id="$Id: NewFillingStationFrm.cpp,v 1.5 2002/06/02 09:55:13 grunwalm Exp $";
#include "NewFillingStationFrm.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>

/*
 *  Constructs a NewFillingStationFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NewFillingStationFrm::NewFillingStationFrm( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : NewFillingStationBaseFrm( parent, name, modal, fl )
{
    init();
}

// -------------------------------------------------
// Use : Enter create dialog to enter data about filling stations
// Parameters  : stationName - prefill dialog with that name
// Side-Effects: stationName must not be null on return
// -------------------------------------------------
NewFillingStationFrm::NewFillingStationFrm( const QString& stationName, QWidget* parent = 0, const char* name = 0)
		: NewFillingStationBaseFrm( parent, name, TRUE )
{
    init();
    m_StationName->setText( stationName );
}

// -------------------------------------------------
// Use : Common initialisation for different constructors
// -------------------------------------------------
void NewFillingStationFrm::init()
{
    /*
    || Change keyvalue-labels to red
    */

    QPalette pal = m_StationNameLbl->palette();
    pal.setColor( QColorGroup::Foreground, red );
    m_StationNameLbl->setPalette( pal );

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    newfillingstationfrm_cvs_id+=0;
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewFillingStationFrm::~NewFillingStationFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

// -------------------------------------------------
// Use : Called on "Ok"-click. Ensure, all data is
//       correct.
// -------------------------------------------------
void NewFillingStationFrm::accept()
{
    if ( m_StationName->text().isEmpty() )
    {

        // FIXME : Dont match \&
        QString fieldName = m_StationNameLbl->text().replace( QRegExp( "&" ), "" );

        QMessageBox::information( this, "Empty Field",
                                        "The field \""+fieldName+"\" must not be empty!" );
    }
    else
    {
        NewFillingStationBaseFrm::accept();
    }
}



/* 
 * protected slot
 */
void NewFillingStationFrm::showHelp()
{
    qWarning( "NewFillingStationFrm::showHelp() not yet implemented!" ); 
}

