//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DiscretizableParticleHistoryObserver.hpp
//! \author Philip Britt
//! \brief  Particle observer discretization interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DISCRETIZABLE_PARTICLE_HISTORY_OBSERVER_HPP
#define MONTE_CARLO_DISCRETIZABLE_PARTICLE_HISTORY_OBSERVER_HPP

// FRENSIE includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDiscretization.hpp"
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

// Boost Includes
#include <boost/any.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace MonteCarlo{

//! The particle observer discretization interface base class
class DiscretizableParticleHistoryObserver : public ParticleHistoryObserver
{

protected:

  //! Typedef for map of dimension values
  typedef ObserverPhaseSpaceDiscretization::DimensionValueMap DimensionValueMap;

  //! Typedef for observer phase space dimension discretization pair type
  typedef ObserverPhaseSpaceDiscretization::BinIndexWeightPairArray BinIndexWeightPairArray;

public: 

  //! Constructor
  DiscretizableParticleHistoryObserver();

  //! Destructor
  ~DiscretizableParticleHistoryObserver()
  {/* ... */}

  //! Check if a discretization has been set for a dimension of the phase space
  bool doesDimensionHaveDiscretization( const ObserverPhaseSpaceDimension dimension ) const;

  //! Set the discretization for a dimension of the phase space
  template<ObserverPhaseSpaceDimension dimension, typename InputDataType>
  void setDiscretization( const InputDataType& input_bin_data );

  //! Set the discretization for a dimension of the phase space
  void setDiscretization( const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>& bins );

  //! Set a discretization for the direction dimension
  void setDirectionDiscretization( const ObserverDirectionDimensionDiscretization::ObserverDirectionDiscretizationType discretization_type,
                                   const unsigned quadrature_order,
                                   const bool forward_binning = true);

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

  size_t calculateDiscretizationIndex(const std::unordered_map<ObserverPhaseSpaceDimension, size_t> dimension_bin_indices) const;

private:

  // The observer phase space discretization
  ObserverPhaseSpaceDiscretization d_phase_space_discretization;

protected:

  std::string getBinName(const size_t bin_index ) const;

  void calculateBinIndicesAndWeightsOfRange( const ObserverParticleStateWrapper& particle_state_wrapper,
                                             BinIndexWeightPairArray& bin_indices_and_weights ) const;

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

  void print( std::ostream& os,
              const ObserverPhaseSpaceDimension dimension,
              const size_t index ) const;

  template<typename PointType>
  void calculateBinIndicesOfPoint( const PointType& phase_space_point,
                                   ObserverPhaseSpaceDimensionDiscretization::BinIndexArray& bin_indices) const;

  // Serialize the observer discretization
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistoryObserver );
    ar & BOOST_SERIALIZATION_NVP( d_phase_space_discretization ); 
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( DiscretizableParticleHistoryObserver , MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( DiscretizableParticleHistoryObserver, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, DiscretizableParticleHistoryObserver);

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_DiscretizableParticleHistoryObserver_def.hpp"

#endif // end MONTE_CARLO_DISCRETIZABLE_PARTICLE_HISTORY_OBSERVER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DiscretizableParticleHistoryObserver.hpp
//---------------------------------------------------------------------------//
