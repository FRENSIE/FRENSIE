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
    case Data::ElectroatomicDataProperties::ACE_FILE: return "ACE";
    case Data::ElectroatomicDataProperties::ACE_EPR_FILE: return "ACE EPR";
    case Data::ElectroatomicDataProperties::Native_ENDL_FILE: return "Native ENDL";
    case Data::ElectroatomicDataProperties::Native_Moment_Preserving_FILE: return "Native Moment Preserving";
    case Data::ElectroatomicDataProperties::Native_EPR_FILE: return "Native EPR";
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
