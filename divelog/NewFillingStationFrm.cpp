#include "newfillingstationfrm.h"

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
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewFillingStationFrm::~NewFillingStationFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * protected slot
 */
void NewFillingStationFrm::showHelp()
{
    qWarning( "NewFillingStationFrm::showHelp() not yet implemented!" ); 
}

