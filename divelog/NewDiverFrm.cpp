/******************************************************************************
* Filename : newdiverfrm.cpp                                                  *
* CVS Id 	 : $Id: NewDiverFrm.cpp,v 1.1 2001/10/17 13:31:26 markus Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : Form for entering information about a diver.             *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Wed Oct 17 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *newdiverfrm_cvs_id="$Id: NewDiverFrm.cpp,v 1.1 2001/10/17 13:31:26 markus Exp $";
#include "newdiverfrm.h"

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
}

/*  
 *  Destroys the object and frees any allocated resources
 */
NewDiverFrm::~NewDiverFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

