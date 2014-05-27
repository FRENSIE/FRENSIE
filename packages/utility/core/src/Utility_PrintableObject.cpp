//---------------------------------------------------------------------------//
//!
//! \file   Utility_PrintableObject.hpp
//! \author Alex Robinson
//! \brief  Printable object base class definition.
//!
//---------------------------------------------------------------------------//

// FRNECS Includes
#include "Utility_PrintableObject.hpp"

namespace Utility{

// Constructor
PrintableObject::PrintableObject( const std::string &label )
  : d_label( label )
{ /* ... */ }

// Print method for placing the printable object in an output stream.
void PrintableObject::print( std::ostream &os ) const
{
  os << d_label << std::endl;
}

// Set the printable object label
void PrintableObject::setLabel( const std::string& label )
{ 
  d_label = label; 
}

// Get the printable object label
std::string PrintableObject::getLabel() const
{
  return d_label;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PrintableObject.cpp
//---------------------------------------------------------------------------//
