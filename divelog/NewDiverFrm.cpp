/******************************************************************************
* Filename : newdiverfrm.cpp                                                  *
* CVS Id 	 : $Id: NewDiverFrm.cpp,v 1.5 2001/11/08 08:35:17 markus Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : Form for entering information about a diver.             *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Wed Oct 17 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *newdiverfrm_cvs_id="$Id: NewDiverFrm.cpp,v 1.5 2001/11/08 08:35:17 markus Exp $";
#include "newdiverfrm.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>

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
    newdiverfrm_cvs_id+=0;
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

