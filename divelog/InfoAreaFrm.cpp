/******************************************************************************
* Filename : infoareafrm.cpp                                                                 *
* CVS Id   : $Id: InfoAreaFrm.cpp,v 1.4 2001/11/19 19:37:04 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Supply a main info-field for the application             *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Nov  6 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *infoareafrm_cvs_id="$Id: InfoAreaFrm.cpp,v 1.4 2001/11/19 19:37:04 markus Exp $";
#include "InfoAreaFrm.h"

/* 
 *  Constructs a InfoAreaFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
InfoAreaFrm::InfoAreaFrm( QWidget* parent,  const char* name, WFlags fl )
    : InfoAreaBaseFrm( parent, name, fl )
{
}

// -------------------------------------------------
// Use : Common initialisation for different constructors
// -------------------------------------------------
void InfoAreaFrm::init()
{
    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    infoareafrm_cvs_id+=0;
}



/*  
 *  Destroys the object and frees any allocated resources
 */
InfoAreaFrm::~InfoAreaFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

