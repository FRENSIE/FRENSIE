//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

//! Convert the ObserverPhaseSpaceDimension enum to a string
#define OBSERVER_PHASE_SPACE_DIMENSION_STRING( dim ) #dim

namespace MonteCarlo{

// Convert the ObserverPhaseSpaceDimension to a string (basic)
std::string convertObserverPhaseSpaceDimensionToStringBasic(
				  const ObserverPhaseSpaceDimension dimension )
{
  switch( dimension )
  {
  case OBSERVER_COSINE_DIMENSION:
    return OBSERVER_PHASE_SPACE_DIMENSION_STRING( OBSERVER_COSINE_DIMENSION );
  case OBSERVER_SOURCE_ENERGY_ODIMENSION:
    return OBSERVER_PHASE_SPACE_DIMENSION_STRING( OBSERVER_SOURCE_ENERGY_DIMENSION );
  case OBSERVER_ENERGY_DIMENSION:
    return OBSERVER_PHASE_SPACE_DIMENSION_STRING( OBSERVER_ENERGY_DIMENSION );
  case OBSERVER_SOURCE_TIME_DIMENSION:
    return OBSERVER_PHASE_SPACE_DIMENSION_STRING( OBSERVER_SOURCE_TIME_DIMENSION );
  case OBSERVER_TIME_DIMENSION:
    return OBSERVER_PHASE_SPACE_DIMENSION_STRING( OBSERVER_TIME_DIMENSION );
  case OBSERVER_COLLISION_NUMBER_DIMENSION:
    return OBSERVER_PHASE_SPACE_DIMENSION_STRING( OBSERVER_COLLISION_NUMBER_DIMENSION );
  case OBSERVER_SOURCE_ID_DIMENSION:
    return OBSERVER_PHASE_SPACE_DIMENSION_STRING( OBSERVER_SOURCE_ID_DIMENSION );
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: ObserverPhaseSpaceDimension "
                     << (unsigned)dimension <<
		     " cannot be converted to a string!" );
  }
}

// Convert the ObserverPhaseSpaceDimension to a string
std::string convertObserverPhaseSpaceDimensionToString(
				  const ObserverPhaseSpaceDimension dimension )
{
  switch( dimension )
  {
  case OBSERVER_COSINE_DIMENSION:
    return ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>::name();
  case OBSERVER_SOURCE_ENERGY_DIMENSION:
    return ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>::name();
  case OBSERVER_ENERGY_DIMENSION:
    return ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>::name();
  case OBSERVER_SOURCE_TIME_DIMENSION:
    return ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>::name();
  case OBSERVER_TIME_DIMENSION:
    return ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>::name();
  case OBSERVER_COLLISION_NUMBER_DIMENSION:
    return ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>::name();
  case OBSERVER_SOURCE_ID_DIMENSION:
    return ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>::name();
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: ObserverPhaseSpaceDimension "
                     << (unsigned)dimension <<
		     " cannot be converted to a string!" );
  }
}

// Convert an unsigned to an ObserverPhaseSpaceDimension
ObserverPhaseSpaceDimension convertUnsignedToObserverPhaseSpaceDimensionEnum(
                                                     const unsigned dimension )
{
  switch( dimension )
  {
  case (unsigned)OBSERVER_COSINE_DIMENSION:
    return OBSERVER_COSINE_DIMENSION;
  case (unsigned)OBSERVER_SOURCE_ENERGY_DIMENSION:
    return OBSERVER_SOURCE_ENERGY_DIMENSION;
  case (unsigned)OBSERVER_ENERGY_DIMENSION:
    return OBSERVER_ENERGY_DIMENSION;
  case (unsigned)OBSERVER_SOURCE_TIME_DIMENSION:
    return OBSERVER_SOURCE_TIME_DIMENSION;
  case (unsigned)OBSERVER_TIME_DIMENSION:
    return OBSERVER_TIME_DIMENSION;
  case (unsigned)OBSERVER_COLLISION_NUMBER_DIMENSION:
    return OBSERVER_COLLISION_NUMBER_DIMENSION;
  case (unsigned)OBSERVER_SOURCE_ID_DIMENSION:
    return OBSERVER_SOURCE_ID_DIMENSION;
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: the raw dimension value " << dimension <<
                     " cannot be converted to an ObserverPhaseSpaceDimension "
                     "enum!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
