//---------------------------------------------------------------------------//
//!
//! \file   Data_ThermalNuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The thermal nuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_ThermalNuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default constructor
ThermalNuclearDataProperties::ThermalNuclearDataProperties()
{ /* ... */ }

// Get the nuclear data evaluation temperature (Kelvin)
auto ThermalNuclearDataProperties::evaluationTemperature() const -> Temperature
{
  return this->evaluationTemperatureInMeV()/Utility::PhysicalConstants::boltzmann_constant_q;
}

// Get the file major version
unsigned ThermalNuclearDataProperties::fileMajorVersion() const
{
  return this->fileVersion();
}

} // end Data namespace

namespace Utility{

//  Convert a Data::ThermalNuclearDataProperties::FileType to a string
std::string ToStringTraits<Data::ThermalNuclearDataProperties::FileType>::toString(
                             const Data::ThermalNuclearDataProperties::FileType type )
{
  switch( type )
  {
    case Data::ThermalNuclearDataProperties::STANDARD_ACE_FILE: return "Standard ACE";
    case Data::ThermalNuclearDataProperties::MCNP6_ACE_FILE: return "MCNP6 ACE";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown thermal nuclear data file type encountered!" );
    }
  }
}

// Place the Data::ThermalNuclearDataProperties::FileType in a stream
void ToStringTraits<Data::ThermalNuclearDataProperties::FileType>::toStream(
           std::ostream& os, const Data::ThermalNuclearDataProperties::FileType type )
{
  os << ToStringTraits<Data::ThermalNuclearDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_ThermalNuclearDataProperties.cpp
//---------------------------------------------------------------------------//
