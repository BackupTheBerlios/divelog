#include "infoareafrm.h"

/* 
 *  Constructs a InfoareaFrm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
InfoAreaFrm::InfoAreaFrm( QWidget* parent,  const char* name, WFlags fl )
    : Form1( parent, name, fl )
{
}

/*  
 *  Destroys the object and frees any allocated resources
 */
InfoAreaFrm::~InfoAreaFrm()
{
    // no need to delete child widgets, Qt does it all for us
}

