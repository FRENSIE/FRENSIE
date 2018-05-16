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
#include <string>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"

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

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::PhaseSpaceDimensionClass
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::PhaseSpaceDimensionClass>
{
  //! Convert a MonteCarlo::PhaseSpaceDimension to a string
  static std::string toString( const MonteCarlo::PhaseSpaceDimensionClass _class );

  //! Place the MonteCarlo::PhaseSpaceDimension in a stream
  static void toStream( std::ostream& os, const MonteCarlo::PhaseSpaceDimensionClass _class );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing dimension type enums
inline std::ostream& operator<<(
                   std::ostream& os,
                   const MonteCarlo::PhaseSpaceDimensionClass dimension_class )
{
  os << Utility::toString( dimension_class );
  return os;
}

} // end std namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_CLASS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionClass.hpp
//---------------------------------------------------------------------------//
