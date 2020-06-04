//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DiscretizableParticleHistoryObserver_def.hpp
//! \author Philip Britt
//! \brief  Particle observer discretization interface base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DISCRETIZABLE_PARTICLE_HISTORY_OBSERVER_DEF_HPP
#define MONTE_CARLO_DISCRETIZABLE_PARTICLE_HISTORY_OBSERVER_DEF_HPP

// FRENSIE includes
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Set the discretization for a dimension of the phase space
/*! \details This method is a factory method that will create
 * a phase space dimension discretization and assign it to the underlying
 * phase space discretization. Before it is added to the phase space 
 * discretization the object will determine if discretizations of the
 * phase space dimension are supported (e.g. cosine binning is not supported
 * in cell observers).
 */
template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
void DiscretizableParticleHistoryObserver::setDiscretization( const InputDataType& bin_data )
{
  // Make sure the DimensionType matches the type associated with the dimension
  testStaticPrecondition((boost::is_same<typename DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension>::InputDataType,InputDataType>::value));

  std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>
    dimension_discretization(
          new DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension>(
                                                                  bin_data ) );

  this->setDiscretization( dimension_discretization );
}

// Get the discretization for a dimension of the phase space
/*! \details This method will extract the discretization data from a 
 * previously set dimension discretization.
 */
template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
void DiscretizableParticleHistoryObserver::getDiscretization( InputDataType& bin_data )
{
  // Make sure the DimensionType matches the type associated with the dimension
  testStaticPrecondition((boost::is_same<typename DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension>::InputDataType,InputDataType>::value));

  const ObserverPhaseSpaceDimensionDiscretization& base_discretization =
    d_phase_space_discretization.getDimensionDiscretization( dimension );

  bin_data = dynamic_cast<const DefaultTypedObserverPhaseSpaceDimensionDiscretization<dimension>&>( base_discretization ).getBinBoundaries();
}

// Check if the point is in the observer phase space
/*! \details The PointType should be either observerParticleStateWrapper or
 * ObserverPhaseSpaceDiscretization::DimensionValueMap.
 */
template<typename PointType>
inline bool DiscretizableParticleHistoryObserver::isPointInObserverPhaseSpace(
		              const PointType& phase_space_point ) const
{
  return d_phase_space_discretization.isPointInDiscretization(
                                                           phase_space_point );
}

template<typename PointType>
void DiscretizableParticleHistoryObserver::calculateBinIndicesOfPoint( const PointType& phase_space_point,
                                  ObserverPhaseSpaceDimensionDiscretization::BinIndexArray& bin_indices) const
{
  d_phase_space_discretization.calculateBinIndicesOfPoint(phase_space_point,
                                                          bin_indices);
}

}; // End MonteCarlo namespace

#endif // end MONTE_CARLO_DISCRETIZABLE_PARTICLE_HISTORY_OBSERVER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DiscretizableParticleHistoryObserver_def.hpp
//---------------------------------------------------------------------------//