//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectroatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The electroatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ElectroatomicDataProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{
  
// Default constructor
ElectroatomicDataProperties::ElectroatomicDataProperties()
{ /* ... */ }

} // end Data namespace

namespace Utility{

//  Convert a Data::ElectroatomicDataProperties::FileType to a string
std::string ToStringTraits<Data::ElectroatomicDataProperties::FileType>::toString(
                             const Data::ElectroatomicDataProperties::FileType type )
{
  switch( type )
  {
    case Data::ElectroatomicDataProperties::ACE_EPR_FILE: return "ACE EPR";
    case Data::ElectroatomicDataProperties::Native_FILE: return "Native";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown electroatomic data file type encountered!" );
    }
  }
}

// Place the Data::ElectroatomicDataProperties::FileType in a stream
void ToStringTraits<Data::ElectroatomicDataProperties::FileType>::toStream(
     std::ostream& os, const Data::ElectroatomicDataProperties::FileType type )
{
  os << ToStringTraits<Data::ElectroatomicDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_ElectroatomicDataProperties.cpp
//---------------------------------------------------------------------------//
