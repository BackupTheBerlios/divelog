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
* Filename : newdivecomputerfrm.cpp                                           *
* CVS Id   : $Id: NewDiveComputerFrm.cpp,v 1.14 2002/09/16 17:08:11 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Provide a Dialog for entering information about a dive   *
*                    computer (EON/Aladin/...)                                *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Nov  6 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static char newdivecomputerfrm_cvs_id[]="$Id: NewDiveComputerFrm.cpp,v 1.14 2002/09/16 17:08:11 grunwalm Exp $";
#include "NewDiveComputerFrm.h"
#include "DivelogDAO.h"
#include "DiverVO.h"
#include "DiverNotFoundException.h"
#include "NewDiverFrm.h"

#include "MainWidget.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qcombobox.h>
#include <qregexp.h>

/*
 *  Constructs a NewDiveComputerFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NewDiveComputerFrm::NewDiveComputerFrm( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : NewDiveComputerBaseFrm( parent, name, modal, fl )
{
    init();
}

// -------------------------------------------------
// Use : Enter create dialog to enter data about dive computers
// Parameters  : 
// Side-Effects: 
// -------------------------------------------------
NewDiveComputerFrm::NewDiveComputerFrm( const QString& serialNumber, 
                        								const QString& computerName=0,
                        								QWidget* parent = 0, const char* name = 0)
		: NewDiveComputerBaseFrm( parent, name, TRUE )
{
    init();
    m_SerialNumber->setText( serialNumber );
    m_ComputerName->setText( computerName );
}

// -------------------------------------------------
// Use : Common initialisation for different constructors
// -------------------------------------------------
void NewDiveComputerFrm::init()
{
    /*
    || Change keyvalue-labels to red
    */

    QPalette pal = m_SerialNumberLbl->palette();
    pal.setColor( QColorGroup::Foreground, red );
    m_SerialNumberLbl->setPalette( pal );

    initDiverCombo();

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    newdivecomputerfrm_cvs_id[0]+=0;
}

void NewDiveComputerFrm::initDiverCombo()
{
    /*
    || Get divers from database -> QComboBox m_Owner
    */
    DivelogDAO db;
    try
    {
        DiverSO search;

        search.number( 0 );
        vector<DiverVO> db_DiverList =db.searchDiver( search );  // dump the whole table

        vector<DiverVO>::iterator i;

        indexCoder.clear();
        m_Owner->clear();
        for ( i=db_DiverList.begin(); i!=db_DiverList.end(); i++ )
        {
            DiverVO diver( *i );
            indexCoder.push_back( diver.number() );
            m_Owner->insertItem( ( diver.first_name()+" "+diver.last_name() ) );

            qDebug(" Diver = %s", diver.first_name().latin1() );
        }
    }
    catch( DiverNotFoundException e )
    {
        cerr << e << endl;
        // FIXME: open messagebox, maybe even better: open diver input dialog
    }
}

unsigned int NewDiveComputerFrm::diver_number() const
{
    return indexCoder[ m_Owner->currentItem() ];
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewDiveComputerFrm::~NewDiveComputerFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

// -------------------------------------------------
// Use : Called on "Ok"-click. Ensure, all data is
//       correct.
// -------------------------------------------------
void NewDiveComputerFrm::accept()
{
    if ( m_SerialNumber->text().isEmpty() )
    {

        // FIXME : Dont match \&
        QString fieldName = m_SerialNumberLbl->text().replace( QRegExp( "&" ), "" );

        QMessageBox::information( this, "Empty Field",
                                        "The field \""+fieldName+"\" must not be empty!" );
    }
    else if ( m_Owner->currentText().isEmpty() )
    {

        // FIXME : Dont match \&
        QString fieldName = m_OwnerLbl->text().replace( QRegExp( "&" ), "" );

        QMessageBox::information( this, "Empty Field",
                                        "The field \""+fieldName+"\" must not be empty!" );
    }
    else
    {
        NewDiveComputerBaseFrm::accept();
    }
}

/* 
 * protected slots
 */

void NewDiveComputerFrm::showHelp()
{
    qWarning( "NewDiveComputerFrm::showHelp() not yet implemented!" ); 
}

void NewDiveComputerFrm::addDiverDlg()
{
    // ((MainWidget)(this->parent())).dbNewDiver(); // This doesn't work (see below)

    /*
    || This is a cut-and-paste job from MainWidget. Ugly, so there has to be a better way ?
    */
    int result=0;
    NewDiverFrm newDiverFrm( this, "newDiverFrm", true ); // parent, name, modal

    result=newDiverFrm.exec();
    if ( result )
    {
        /*
        || Insert the diver into the database
        */
				DiverVO diver( 0, // Auto increment
                       newDiverFrm.m_FirstName->text().latin1(),
                       newDiverFrm.m_LastName->text().latin1(),
                       newDiverFrm.m_Brevet->text().latin1(),
                       newDiverFrm.m_Street->text().latin1(),
                       newDiverFrm.m_HouseNumber->text().latin1(),
                       newDiverFrm.m_Zip->text().toUInt(),
                       newDiverFrm.m_Place->text().latin1(),
                       newDiverFrm.m_Phone->text().latin1(),
                       newDiverFrm.m_EMail->text().latin1()
                     );

        DivelogDAO db;
        try
        {
            db.insertDiver( diver );
        }
        catch( DivelogDAOException e )
        {
            cerr << e << endl;
        }
    }
    initDiverCombo();
}

