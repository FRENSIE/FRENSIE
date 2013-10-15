//---------------------------------------------------------------------------//
//!
//! \file   PrintableObject.hpp
//! \author Alex Robinson
//! \brief  Printable object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PRINTABLE_OBJECT_HPP
#define PRINTABLE_OBJECT_HPP

// Std Lib Includes
#include <string>
#include <ostream>

namespace FACEMC{

//! The base class for printable objects
class PrintableObject
{

public:
  
  //! Constructor
  PrintableObject( const std::string &label = "PrintableObject" )
    : d_label( label )
  { /* ... */ }

  //! Destructor
  virtual ~PrintableObject()
  { /* ... */ }

  //! Print method for placing the printable object in an output stream.
  virtual void print( std::ostream &os ) const
  { os << d_label << std::endl; }

  //! Set the printable object label
  void setLabel( const std::string &label )
  { d_label = label; }

  //! Get the printable object label
  std::string getLabel() const
  { return d_label; }

private:
  
  // Printable object label
  std::string d_label;
};

//! Stream operator for printing all printable objects
inline std::ostream& operator<<( std::ostream &os, 
				 const FACEMC::PrintableObject &obj )
{ 
  os << obj.getLabel() << std::endl;
  obj.print( os );

  return os;
}

} // end FACEMC namespace

#endif // end PRINTABLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end PrintableObject.hpp
//---------------------------------------------------------------------------//
