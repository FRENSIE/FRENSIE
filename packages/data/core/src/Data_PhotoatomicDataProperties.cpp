//---------------------------------------------------------------------------//
//!
//! \file   Data_PhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The photoatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_PhotoatomicDataProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{
  
// Default constructor
PhotoatomicDataProperties::PhotoatomicDataProperties()
{ /* ... */ }

} // end Data namespace

namespace Utility{

//  Convert a Data::PhotoatomicDataProperties::FileType to a string
std::string ToStringTraits<Data::PhotoatomicDataProperties::FileType>::toString(
                         const Data::PhotoatomicDataProperties::FileType type )
{
  switch( type )
  {
    case Data::PhotoatomicDataProperties::ACE_FILE: return "ACE";
    case Data::PhotoatomicDataProperties::ACE_EPR_FILE: return "ACE EPR";
    case Data::PhotoatomicDataProperties::Native_ENDL_FILE: return "Native ENDL";
    case Data::PhotoatomicDataProperties::Native_EPR_FILE: return "Native EPR";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown photoatomic data file type encountered!" );
    }
  }
}

// Place the Data::PhotoatomicDataProperties::FileType in a stream
void ToStringTraits<Data::PhotoatomicDataProperties::FileType>::toStream(
       std::ostream& os, const Data::PhotoatomicDataProperties::FileType type )
{
  os << ToStringTraits<Data::PhotoatomicDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_PhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
