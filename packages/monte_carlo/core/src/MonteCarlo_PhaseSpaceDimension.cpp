//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension helper functiond definitions.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

//! Stream operator for printing PhaseSpaceDimension enums
std::ostream& operator<<( std::ostream& os,
			  const PhaseSapceDimension dimension )
{
  switch( dimension )
  {
  case COSINE_DIMENSION:
    os << PhaseSpaceDimensionTraits<COSINE_DIMENSION>::name();
    break;
  case ENERGY_DIMENSION:
    os << PhaseSpaceDimensionTraits<ENERGY_DIMENSION>::name();
    break;
  case TIME_DIMENSION:
    os << PhaseSpaceDimensionTraits<TIME_DIMENSION>::name();
    break;
  case COLLISION_NUMBER_DIMENSION:
    os << PhaseSpaceDimensionTraits<COLLISION_NUMBER_DIMENSION>::name();
    break;
  default:
    os << "Unknown(" << static_cast<unsigned>( dimension ) << ")";
  }

  return os;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
