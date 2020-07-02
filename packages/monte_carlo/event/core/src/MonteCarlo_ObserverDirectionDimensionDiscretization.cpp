//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverDirectionDimensionDiscretization.cpp
//! \author Philip Britt
//! \brief  Direction dimension discretization specialization 
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ObserverDirectionDimensionDiscretization.hpp"

namespace MonteCarlo{

ObserverPhaseSpaceDimension ObserverDirectionDimensionDiscretization::getDimension() const final override
{
  return ObserverPhaseSpaceDimension::OBSERVER_DIRECTION_DIMENSION;
}

std::string ObserverDirectionDimensionDiscretization::getDimensionName() const final override
{
  return "Direction";
}

// Presumably this will only be called after other dimensions are checked for intersection, so this should always return true.
bool ObserverDirectionDimensionDiscretization::isValueInDiscretization( const ObserverParticleStateWrapper& particle_state_wrapper ) const final override
{
  return true;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverDirectionDimensionDiscretization.cpp
//---------------------------------------------------------------------------//