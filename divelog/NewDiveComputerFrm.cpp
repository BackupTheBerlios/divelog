/******************************************************************************
* Filename : newdivecomputerfrm.cpp                                           *
* CVS Id   : $Id: NewDiveComputerFrm.cpp,v 1.6 2001/11/23 15:59:06 markus Exp $                                                             *
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
static const char *newdivecomputerfrm_cvs_id="$Id: NewDiveComputerFrm.cpp,v 1.6 2001/11/23 15:59:06 markus Exp $";
#include "NewDiveComputerFrm.h"
#include "DivelogDAO.h"
#include "DiverVO.h"

#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qcombobox.h>

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

    // TODO: Get divers from database -> QComboBox m_Owner
    DivelogDAO db;
    try
    {
        vector<DiverVO> db_DiverList =db.diverList();

        vector<DiverVO>::iterator i;

        indexCoder.clear();
        for ( i=db_DiverList.begin(); i!=db_DiverList.end(); i++ )
        {
            DiverVO diver( *i );

            indexCoder.push_back( diver.number() );
            m_Owner->insertItem( ( diver.first_name()+" "+diver.last_name() ).c_str() );

            qDebug(" Diver = %s", diver.first_name().c_str() );
        }
    }
    catch(...)
    {
        qDebug("Exception");
    }


    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    newdivecomputerfrm_cvs_id+=0;
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
    else
    {
        NewDiveComputerBaseFrm::accept();
    }
}

/* 
 * protected slot
 */
void NewDiveComputerFrm::showHelp()
{
    qWarning( "NewDiveComputerFrm::showHelp() not yet implemented!" ); 
}

