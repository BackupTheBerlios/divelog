/* Copyright 2002 Markus Grunwald */
/* All other Copyrights (especially Qt and mysql) belong to their owners */

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
* Filename : newdivetypefrm.cpp                                               *
* CVS Id   : $Id: NewDiveTypeFrm.cpp,v 1.4 2002/05/15 09:27:51 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Provide a Dialog for entering information about a dive   *
*                    type (Deepdive/Drift/Wreck/...)                          *                                                         *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Nov  6 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *newdivetypefrm_cvs_id="$Id: NewDiveTypeFrm.cpp,v 1.4 2002/05/15 09:27:51 grunwalm Exp $";
#include "NewDiveTypeFrm.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>


/* 
 *  Constructs a NewDiveTypeFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NewDiveTypeFrm::NewDiveTypeFrm( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : NewDiveTypeBaseFrm( parent, name, modal, fl )
{
    init();
}

// -------------------------------------------------
// Use : Enter create dialog to enter data about filling stations
// Parameters  : stationName - prefill dialog with that name
// Side-Effects: stationName must not be null on return
// -------------------------------------------------
NewDiveTypeFrm::NewDiveTypeFrm( const QString& diveType, QWidget* parent = 0, const char* name = 0)
		: NewDiveTypeBaseFrm( parent, name, TRUE )
{
    init();
    m_DiveType->setText( diveType );
}

// -------------------------------------------------
// Use : Common initialisation for different constructors
// -------------------------------------------------
void NewDiveTypeFrm::init()
{
    /*
    || Change keyvalue-labels to red
    */

    QPalette pal = m_DiveTypeLbl->palette();
    pal.setColor( QColorGroup::Foreground, red );
    m_DiveTypeLbl->setPalette( pal );

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    newdivetypefrm_cvs_id+=0;
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewDiveTypeFrm::~NewDiveTypeFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

// -------------------------------------------------
// Use : Called on "Ok"-click. Ensure, all data is
//       correct.
// -------------------------------------------------
void NewDiveTypeFrm::accept()
{
    if ( m_DiveType->text().isEmpty() )
    {

        // FIXME : Dont match \&
        QString fieldName = m_DiveTypeLbl->text().replace( QRegExp( "&" ), "" );

        QMessageBox::information( this, "Empty Field",
                                        "The field \""+fieldName+"\" must not be empty!" );
    }
    else
    {
        NewDiveTypeBaseFrm::accept();
    }
}
/* 
 * protected slot
 */
void NewDiveTypeFrm::showHelp()
{
    qWarning( "NewDiveTypeFrm::showHelp() not yet implemented!" ); 
}

