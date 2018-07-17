//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_RangedSingleObserverPhaseSpaceDiscretizationImpl.hpp
//! \author Alex Robinson
//! \brief  The ranged single observer phase space discretization impl. class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_RANGED_SINGLE_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP
#define MONTE_CARLO_RANGED_SINGLE_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

// FRENSIE Includes
#include "MonteCarlo_SingleObserverPhaseSpaceDiscretizationImpl.hpp"

namespace MonteCarlo{

//! The ranged single observer phase space discretization implementation
class RangedSingleObserverPhaseSpaceDiscretizationImpl : public SingleObserverPhaseSpaceDiscretizationImpl
{
  
public:

  //! Typedef for the dimension value map
  typedef SingleObserverPhaseSpaceDiscretizationImpl::DimensionValueMap DimensionValueMap;

  //! Typedef for the bin index array
  typedef SingleObserverPhaseSpaceDiscretizationImpl::BinIndexArray BinIndexArray;

  //! Typedef for the bin index and weight array
  typedef SingleObserverPhaseSpaceDiscretizationImpl::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Constructor
  RangedSingleObserverPhaseSpaceDiscretizationImpl()
  { /* ... */ }

  //! Destructor
  ~RangedSingleObserverPhaseSpaceDiscretizationImpl()
  { /* ... */ }

  //! Assign a discretization to a dimension
  void assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension ) override;

  //! Return the dimensions that have been discretized
  void getDiscretizedDimensions( std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> >& discretized_dimensions ) const override;

  //! Check if the range intersects the phase space discretization
  bool doesRangeIntersectDiscretization(
   const ObserverParticleStateWrapper& particle_state_wrapper ) const override;

  //! Calculate the bin indices and weights of a range
  void calculateBinIndicesAndWeightsOfRange(
             const ObserverParticleStateWrapper& particle_state_wrapper,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

private:
  
  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SingleObserverPhaseSpaceDiscretizationImpl );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The discretized dimension
  std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>
  d_dimension_discretization;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::RangedSingleObserverPhaseSpaceDiscretizationImpl, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( RangedSingleObserverPhaseSpaceDiscretizationImpl, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, RangedSingleObserverPhaseSpaceDiscretizationImpl );

#endif // end MONTE_CARLO_RANGED_SINGLE_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_RangedSingleObserverPhaseSpaceDiscretizationImpl.hpp
//---------------------------------------------------------------------------//
