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
* Filename : newdiverfrm.cpp                                                  *
* CVS Id 	 : $Id: NewDiverFrm.cpp,v 1.9 2002/09/16 17:08:11 grunwalm Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : Form for entering information about a diver.             *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Wed Oct 17 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static  char newdiverfrm_cvs_id[]="$Id: NewDiverFrm.cpp,v 1.9 2002/09/16 17:08:11 grunwalm Exp $";
#include "NewDiverFrm.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qregexp.h>

/*
 *  Constructs a NewDiverFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NewDiverFrm::NewDiverFrm( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : NewDiverBaseFrm( parent, name, modal, fl )
{
    init();
}

// -------------------------------------------------
// Use : Enter create dialog to enter data about divers
// Parameters  : firstName - prefill dialog with that name
// Side-Effects: firstName must not be null on return
// -------------------------------------------------
NewDiverFrm::NewDiverFrm( const QString& firstName, QWidget* parent = 0, const char* name = 0)
		: NewDiverBaseFrm( parent, name, TRUE )
{
    init();
    m_FirstName->setText( firstName );
}

// -------------------------------------------------
// Use : Common initialisation for different constructors
// -------------------------------------------------
void NewDiverFrm::init()
{
    /*
    || Change keyvalue-labels to red
    */

    QPalette pal = m_FirstNameLbl->palette();
    pal.setColor( QColorGroup::Foreground, red );
    m_FirstNameLbl->setPalette( pal );

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    newdiverfrm_cvs_id[0]+=0;
}

// -------------------------------------------------
// Use : Called on "Ok"-click. Ensure, all data is
//       correct.
// -------------------------------------------------
void NewDiverFrm::accept()
{
    if ( m_FirstName->text().isEmpty() )
    {
        // FIXME : Dont match \&
        QString fieldName = m_FirstNameLbl->text().replace( QRegExp( "&" ), "" );

        QMessageBox::information( this, "Empty Field",
                                        "The field \""+fieldName+"\" must not be empty!" );
    }
    else
    {
        NewDiverBaseFrm::accept();
    }
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewDiverFrm::~NewDiverFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * protected slot
 */
void NewDiverFrm::showHelp()
{
    qWarning( "NewDiverFrm::showHelp() not yet implemented!" );
}

