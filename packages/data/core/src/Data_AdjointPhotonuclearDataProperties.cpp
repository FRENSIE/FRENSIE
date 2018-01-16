//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointPhotonuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The adjoint nuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_AdjointPhotonuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default constructor
AdjointPhotonuclearDataProperties::AdjointPhotonuclearDataProperties()
{ /* ... */ }
  
} // end Data namespace

namespace Utility{

//  Convert a Data::AdjointPhotonuclearDataProperties::FileType to a string
std::string ToStringTraits<Data::AdjointPhotonuclearDataProperties::FileType>::toString(
                      const Data::AdjointPhotonuclearDataProperties::FileType type )
{
  switch( type )
  {
  case Data::AdjointPhotonuclearDataProperties::Native_FILE: return "Native";
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "Unknown adjoint nuclear data file type encountered!" );
  }
  }
}

// Place the Data::AdjointPhotonuclearDataProperties::FileType in a stream
void ToStringTraits<Data::AdjointPhotonuclearDataProperties::FileType>::toStream(
    std::ostream& os, const Data::AdjointPhotonuclearDataProperties::FileType type )
{
  os << ToStringTraits<Data::AdjointPhotonuclearDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_AdjointPhotonuclearDataProperties.cpp
//---------------------------------------------------------------------------//
