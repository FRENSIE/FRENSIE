//---------------------------------------------------------------------------//
//!
//! \file   Data_PhotonuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The photonuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_PhotonuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{
  
// Default constructor
PhotonuclearDataProperties::PhotonuclearDataProperties()
{ /* ... */ }

} // end Data namespace

namespace Utility{

//  Convert a Data::PhotonuclearDataProperties::FileType to a string
std::string ToStringTraits<Data::PhotonuclearDataProperties::FileType>::toString(
                             const Data::PhotonuclearDataProperties::FileType type )
{
  switch( type )
  {
    case Data::PhotonuclearDataProperties::ACE_FILE: return "ACE";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown nuclear data file type encountered!" );
    }
  }
}

// Place the Data::PhotonuclearDataProperties::FileType in a stream
void ToStringTraits<Data::PhotonuclearDataProperties::FileType>::toStream(
           std::ostream& os, const Data::PhotonuclearDataProperties::FileType type )
{
  os << ToStringTraits<Data::PhotonuclearDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_PhotonuclearDataProperties.cpp
//---------------------------------------------------------------------------//
