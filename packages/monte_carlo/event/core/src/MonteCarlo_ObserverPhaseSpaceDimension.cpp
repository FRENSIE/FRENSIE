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
#include "MonteCarlo_ObserverDirectionDimensionDiscretization.hpp"

namespace Utility{

// Convert a MonteCarlo::ObserverPhaseSpaceDimension to a string
std::string ToStringTraits<MonteCarlo::ObserverPhaseSpaceDimension>::toString(
                      const MonteCarlo::ObserverPhaseSpaceDimension dimension )
{
  switch( dimension )
  {
    case MonteCarlo::OBSERVER_COSINE_DIMENSION:
      return MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_COSINE_DIMENSION>::name();
    case MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION:
      return MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION>::name();
    case MonteCarlo::OBSERVER_ENERGY_DIMENSION:
      return MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_ENERGY_DIMENSION>::name();
    case MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION:
      return MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION>::name();
    case MonteCarlo::OBSERVER_TIME_DIMENSION:
      return MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_TIME_DIMENSION>::name();
    case MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION:
      return MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>::name();
    case MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION:
      return MonteCarlo::ObserverPhaseSpaceDimensionTraits<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>::name();
    case MonteCarlo::OBSERVER_DIRECTION_DIMENSION:
      return MonteCarlo::ObserverDirectionDimensionDiscretization::name();
    default:
    {
      THROW_EXCEPTION( std::logic_error,
                       "ObserverPhaseSpaceDimension "
                       << (unsigned)dimension <<
                       " cannot be converted to a string!" );
    }
  }
}

// Place the MonteCarlo::ObserverPhaseSpaceDimension in a stream
void ToStringTraits<MonteCarlo::ObserverPhaseSpaceDimension>::toStream(
                      std::ostream& os,
                      const MonteCarlo::ObserverPhaseSpaceDimension dimension )
{
  os << ToStringTraits<MonteCarlo::ObserverPhaseSpaceDimension>::toString( dimension );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
