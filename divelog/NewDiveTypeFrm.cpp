#include "newdivetypefrm.h"

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
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewDiveTypeFrm::~NewDiveTypeFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * protected slot
 */
void NewDiveTypeFrm::showHelp()
{
    qWarning( "NewDiveTypeFrm::showHelp() not yet implemented!" ); 
}

