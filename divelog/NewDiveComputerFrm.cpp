#include "newdivecomputerfrm.h"

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
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewDiveComputerFrm::~NewDiveComputerFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * protected slot
 */
void NewDiveComputerFrm::showHelp()
{
    qWarning( "NewDiveComputerFrm::showHelp() not yet implemented!" ); 
}

