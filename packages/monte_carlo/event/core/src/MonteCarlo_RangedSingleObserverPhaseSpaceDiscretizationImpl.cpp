//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_RangedSingleObserverPhaseSpaceDiscretizationImpl.cpp
//! \author Alex Robinson
//! \brief  The ranged single observer phase space discretization impl. class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_RangedSingleObserverPhaseSpaceDiscretizationImpl.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Assign a discretization to a dimension
void RangedSingleObserverPhaseSpaceDiscretizationImpl::assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension )
{
  // Make sure that the discretization pointer is valid
  testPrecondition( discretization.get() );
  // Make sure the discretization is not for a range dimension
  testPrecondition( range_dimension );

  this->setDimensionDiscretization( discretization );
}

// Return the dimensions that have been discretized
void RangedSingleObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions( std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> >& discretized_dimensions ) const
{
  SingleObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions( discretized_dimensions );

  discretized_dimensions.begin()->second.second = true;
}

// Check if the range intersects the phase space discretization
bool RangedSingleObserverPhaseSpaceDiscretizationImpl::doesRangeIntersectDiscretization(
             const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return this->getDimensionDiscretization().doesRangeIntersectDiscretization( particle_state_wrapper );
}

// Calculate the bin indices and weights of a range
void RangedSingleObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesAndWeightsOfRange(
                    const ObserverParticleStateWrapper& particle_state_wrapper,
                    BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  this->getDimensionDiscretization().calculateBinIndicesOfRange(
                                                     particle_state_wrapper,
                                                     bin_indices_and_weights );
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::RangedSingleObserverPhaseSpaceDiscretizationImpl );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::RangedSingleObserverPhaseSpaceDiscretizationImpl );

//---------------------------------------------------------------------------//
// end MonteCarlo_RangedSingleObserverPhaseSpaceDiscretizationImpl.cpp
//---------------------------------------------------------------------------//
