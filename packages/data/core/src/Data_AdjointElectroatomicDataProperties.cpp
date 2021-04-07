//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectroatomicDataProperties.cpp
//! \author Alex Robinson
//! \brief  The adjoint electroatomic data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_AdjointElectroatomicDataProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{
  
// Default constructor
AdjointElectroatomicDataProperties::AdjointElectroatomicDataProperties()
{ /* ... */ }

} // end Data namespace

namespace Utility{

//  Convert a Data::AdjointElectroatomicDataProperties::FileType to a string
std::string ToStringTraits<Data::AdjointElectroatomicDataProperties::FileType>::toString(
                const Data::AdjointElectroatomicDataProperties::FileType type )
{
  switch( type )
  {
  case Data::AdjointElectroatomicDataProperties::Native_EPR_FILE: return "Native EPR";
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "Unknown adjoint electroatomic data file type "
                     "encountered!" );
  }
  }
}

// Place the Data::AdjointElectroatomicDataProperties::FileType in a stream
void ToStringTraits<Data::AdjointElectroatomicDataProperties::FileType>::toStream(
                std::ostream& os,
                const Data::AdjointElectroatomicDataProperties::FileType type )
{
  os << ToStringTraits<Data::AdjointElectroatomicDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_AdjointElectroatomicDataProperties.cpp
//---------------------------------------------------------------------------//
