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

#define PHASE_SPACE_DIMENSION_STRING( dim ) #dim

namespace MonteCarlo{

// Convert the PhaseSpaceDimension to a string (basic)
std::string convertPhaseSpaceDimensionToStringBasic(
					  const PhaseSpaceDimension dimension )
{
  switch( dimension )
  {
  case COSINE_DIMENSION:
    return PHASE_SPACE_DIMENSION_STRING( COSINE_DIMENSION );
  case ENERGY_DIMENSION:
    return PHASE_SPACE_DIMENSION_STRING( ENERGY_DIMENSION );
  case TIME_DIMENSION:
    return PHASE_SPACE_DIMENSION_STRING( TIME_DIMENSION );
  case COLLISION_NUMBER_DIMENSION:
    return PHASE_SPACE_DIMENSION_STRING( COLLISION_NUMBER_DIMENSION );
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: PhaseSpaceDimension " << (unsigned)dimension <<
		     " cannot be converted to a string!" );
  }
}

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
		     "Error: PhaseSpaceDimension " << (unsigned)dimension <<
		     " cannot be converted to a string!" );
  }
}

// Convert an unsigned to a PhaseSpaceDimension
PhaseSpaceDimension convertUnsignedToPhaseSpaceDimensionEnum(
                                                     const unsigned dimension )
{
  switch( dimension )
  {
  case (unsigned)COSINE_DIMENSION:
    return COSINE_DIMENSION;
  case (unsigned)ENERGY_DIMENSION:
    return ENERGY_DIMENSION;
  case (unsigned)TIME_DIMENSION:
    return TIME_DIMENSION;
  case (unsigned)COLLISION_NUMBER_DIMENSION:
    return COLLISION_NUMBER_DIMENSION;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: the raw dimension value " << dimension << 
                     " cannot be converted to a PhaseSpaceDimension enum!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
