//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionClass.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension class enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_CLASS_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_CLASS_HPP

// Std Lib Includes
#include <iostream>
#include <string>

namespace MonteCarlo{

//! The particle source dimension type enumeration
enum PhaseSpaceDimensionClass
{
  SPATIAL_DIMENSION_CLASS = 0,
  DIRECTIONAL_DIMENSION_CLASS,
  ENERGY_DIMENSION_CLASS,
  TIME_DIMENSION_CLASS,
  WEIGHT_DIMENSION_CLASS
};

//! Convert the dimension class type enum to a string
std::string convertPhaseSpaceDimensionClassEnumToString(
                      const PhaseSpaceDimensionClass dimension_class );

//! Stream operator for printing dimension type enums
inline std::ostream& operator<<(
                               std::ostream& os,
                               const PhaseSpaceDimensionClass dimension_class )
{
  os << convertPhaseSpaceDimensionClassEnumToString( dimension_class );
  return os;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_CLASS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionClass.hpp
//---------------------------------------------------------------------------//
