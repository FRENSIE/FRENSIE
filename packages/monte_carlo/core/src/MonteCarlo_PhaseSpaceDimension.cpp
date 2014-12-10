//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension helper functiond definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Convert the PhaseSpaceDimension to a string
std::string convertPhaseSpaceDimensionToString(
					  const PhaseSpaceDimension dimension )
{
  switch( dimension )
  {
  case COSINE_DIMENSION:
    return PhaseSpaceDimensionTraits<COSINE_DIMENSION>::name();
  case ENERGY_DIMENSION:
    return PhaseSpaceDimensionTraits<ENERGY_DIMENSION>::name();
  case TIME_DIMENSION:
    return PhaseSpaceDimensionTraits<TIME_DIMENSION>::name();
  case COLLISION_NUMBER_DIMENSION:
    return PhaseSpaceDimensionTraits<COLLISION_NUMBER_DIMENSION>::name();
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: PhaseSpaceDimension " << dimension <<
		     " cannot be converted to a string!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
