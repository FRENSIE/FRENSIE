//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointThermalNuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The adjoint thermal nuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_AdjointThermalNuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default constructor
AdjointThermalNuclearDataProperties::AdjointThermalNuclearDataProperties()
{ /* ... */ }

// Get the nuclear data evaluation temperature (Kelvin)
auto AdjointThermalNuclearDataProperties::evaluationTemperature() const -> Temperature
{
  return this->evaluationTemperatureInMeV()/Utility::PhysicalConstants::boltzmann_constant_q;
}

// Get the nuclear data file major version
unsigned AdjointThermalNuclearDataProperties::fileMajorVersion() const
{
  return this->fileVersion();
}

} // end Data namespace

namespace Utility{

//  Convert a Data::AdjointThermalNuclearDataProperties::FileType to a string
std::string ToStringTraits<Data::AdjointThermalNuclearDataProperties::FileType>::toString(
                             const Data::AdjointThermalNuclearDataProperties::FileType type )
{
  switch( type )
  {
    case Data::AdjointThermalNuclearDataProperties::Native_FILE: return "Native";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown adjoint thermal nuclear data file type encountered!" );
    }
  }
}

// Place the Data::AdjointThermalNuclearDataProperties::FileType in a stream
void ToStringTraits<Data::AdjointThermalNuclearDataProperties::FileType>::toStream(
               std::ostream& os,
               const Data::AdjointThermalNuclearDataProperties::FileType type )
{
  os << ToStringTraits<Data::AdjointThermalNuclearDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_AdjointThermalNuclearDataProperties.cpp
//---------------------------------------------------------------------------//
