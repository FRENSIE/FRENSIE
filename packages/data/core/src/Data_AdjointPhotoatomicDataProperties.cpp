//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointPhotoatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{
  
// Default constructor
AdjointPhotoatomicDataProperties::AdjointPhotoatomicDataProperties()
{ /* ... */ }

} // end Data namespace

namespace Utility{

//  Convert a Data::AdjointPhotoatomicDataProperties::FileType to a string
std::string ToStringTraits<Data::AdjointPhotoatomicDataProperties::FileType>::toString(
                  const Data::AdjointPhotoatomicDataProperties::FileType type )
{
  switch( type )
  {
    case Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE: return "Native EPR";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown adjoint photoatomic data file type "
                       "encountered!" );
    }
  }
}

// Place the Data::AdjointPhotoatomicDataProperties::FileType in a stream
void ToStringTraits<Data::AdjointPhotoatomicDataProperties::FileType>::toStream(
                  std::ostream& os,
                  const Data::AdjointPhotoatomicDataProperties::FileType type )
{
  os << ToStringTraits<Data::AdjointPhotoatomicDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_AdjointPhotoatomicDataProperties.cpp
//---------------------------------------------------------------------------//
