/******************************************************************************
* Filename : newfillingstationfrm.cpp                                         *
* CVS Id   : $Id: NewFillingStationFrm.cpp,v 1.3 2001/11/19 19:37:05 markus Exp $                                                             *
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
static const char *newfillingstationfrm_cvs_id="$Id: NewFillingStationFrm.cpp,v 1.3 2001/11/19 19:37:05 markus Exp $";
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

