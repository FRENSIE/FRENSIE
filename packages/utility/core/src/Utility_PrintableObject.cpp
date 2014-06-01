//---------------------------------------------------------------------------//
//!
//! \file   Utility_PrintableObject.hpp
//! \author Alex Robinson
//! \brief  Printable object base class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_PrintableObject.hpp"

namespace Utility{

// Constructor
PrintableObject::PrintableObject( const std::string &label,
				  const bool print_label_on_output  )
  : d_label( label ),
    d_print_label_on_output( print_label_on_output )
{ /* ... */ }

// Print method for placing the printable object in an output stream.
void PrintableObject::print( std::ostream &os ) const
{
  os << d_label << std::endl;
}

// Get the printable object label
std::string PrintableObject::getLabel() const
{
  return d_label;
}

// Check if the label will be printed
bool PrintableObject::isLabelPrinted() const
{
  return d_print_label_on_output;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_PrintableObject.cpp
//---------------------------------------------------------------------------//
