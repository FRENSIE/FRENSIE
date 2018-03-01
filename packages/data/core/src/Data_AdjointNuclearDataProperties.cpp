//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointNuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The adjoint nuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_AdjointNuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default constructor
AdjointNuclearDataProperties::AdjointNuclearDataProperties()
{ /* ... */ }

// Get the adjoint nuclear data evaluation temperature (Kelvin)
auto AdjointNuclearDataProperties::evaluationTemperature() const -> Temperature
{
  return this->evaluationTemperatureInMeV()/Utility::PhysicalConstants::boltzmann_constant_q;
}

// Get the nuclear data file major version
unsigned AdjointNuclearDataProperties::fileMajorVersion() const
{
  return this->fileVersion();
}
  
} // end Data namespace

namespace Utility{

//  Convert a Data::AdjointNuclearDataProperties::FileType to a string
std::string ToStringTraits<Data::AdjointNuclearDataProperties::FileType>::toString(
                      const Data::AdjointNuclearDataProperties::FileType type )
{
  switch( type )
  {
  case Data::AdjointNuclearDataProperties::Native_FILE: return "Native";
  default:
  {
    THROW_EXCEPTION( std::logic_error,
                     "Unknown adjoint nuclear data file type encountered!" );
  }
  }
}

// Place the Data::AdjointNuclearDataProperties::FileType in a stream
void ToStringTraits<Data::AdjointNuclearDataProperties::FileType>::toStream(
    std::ostream& os, const Data::AdjointNuclearDataProperties::FileType type )
{
  os << ToStringTraits<Data::AdjointNuclearDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_AdjointNuclearDataProperties.cpp
//---------------------------------------------------------------------------//
