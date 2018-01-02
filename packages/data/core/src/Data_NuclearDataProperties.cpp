//---------------------------------------------------------------------------//
//!
//! \file   Data_NuclearDataProperties.cpp
//! \author Alex Robinson
//! \brief  The nuclear data properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_NuclearDataProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{
  
// Default constructor
NuclearDataProperties::NuclearDataProperties()
{ /* ... */ }

// Get the nuclear data evaluation temperature (Kelvin)
double NuclearDataProperties::evaluationTemperatureInKelvin() const
{
  return this->evaluationTemperatureInMeV()/Utility::PhysicalConstants::boltzmann_constant;
}

} // end Data namespace

namespace Utility{

//  Convert a Data::NuclearDataProperties::FileType to a string
std::string ToStringTraits<Data::NuclearDataProperties::FileType>::toString(
                             const Data::NuclearDataProperties::FileType type )
{
  switch( type )
  {
    case Data::NuclearDataProperties::ACE_FILE: return "ACE";
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "Unknown nuclear data file type encountered!" );
    }
  }
}

// Place the Data::NuclearDataProperties::FileType in a stream
void ToStringTraits<Data::NuclearDataProperties::FileType>::toStream(
           std::ostream& os, const Data::NuclearDataProperties::FileType type )
{
  os << ToStringTraits<Data::NuclearDataProperties::FileType>::toString( type );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Data_NuclearDataProperties.cpp
//---------------------------------------------------------------------------//
