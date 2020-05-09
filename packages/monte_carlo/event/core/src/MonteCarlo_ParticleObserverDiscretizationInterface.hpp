//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleObserverDiscretizationInterface.hpp
//! \author Philip Britt
//! \brief  Particle observer discretization interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_OBSERVER_DISCRETIZATION_INTERFACE_HPP
#define MONTE_CARLO_PARTICLE_OBSERVER_DISCRETIZATION_INTERFACE_HPP

// FRENSIE includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"

namespace MonteCarlo{

//! The particle observer discretization interface base class
class ParticleObserverDiscretizationInterface : public ParticleHistoryObserver
{

protected:

  //! Typedef for map of dimension values
  typedef ObserverPhaseSpaceDiscretization::DimensionValueMap
  DimensionValueMap;

public: 

  //! Constructor
  ParticleObserverDiscretizationInterface();

  //! Destructor
  ~ParticleObserverDiscretizationInterface()
  {/* ... */}

  //! Check if a discretization has been set for a dimension of the phase space
  bool doesDimensionHaveDiscretization( const ObserverPhaseSpaceDimension dimension ) const;

  //! Set the discretization for a dimension of the phase space
  template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
  void setDiscretization( const InputDataType& input_bin_data );

  //! Set the discretization for a dimension of the phase space
  void setDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins );

  //! Return the number of bins for a dimension of the phase space
  size_t getNumberOfBins( const ObserverPhaseSpaceDimension dimension ) const;

  //! Return the total number of bins
  size_t getNumberOfBins() const;

  //! Return the discretization for a dimension of the phase space
  template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
  void getDiscretization( InputDataType& bin_data );

  //! Return the dimensions that have been discretized
  void getDiscretizedDimensions(
      std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const;

protected:

  //! Assign discretization to an observer dimension
  virtual void assignDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins,
                                     const bool range_dimension );

  //! Check if the point is in the observer phase space
  template<typename PointType>
  bool isPointInObserverPhaseSpace( const PointType& phase_space_point ) const;

  //! Check if the range intersects the observer phase space
  bool doesRangeIntersectObserverPhaseSpace(
            const ObserverParticleStateWrapper& particle_state_wrapper ) const;

  //! Print the observer discretization
  void printObserverDiscretization( std::ostream& os ) const;

  // The observer phase space discretization
  ObserverPhaseSpaceDiscretization d_phase_space_discretization;

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleObserverDiscretizationInterface_def.hpp"

#endif // end MONTE_CARLO_PARTICLE_OBSERVER_DISCRETIZATION_INTERFACE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleObserverDiscretizationInterface.hpp
//---------------------------------------------------------------------------//
