//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SingleObserverPhaseSpaceDiscretizationImpl.hpp
//! \author Alex Robinson
//! \brief  The single observer phase space discretization impl. class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SINGLE_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP
#define MONTE_CARLO_SINGLE_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.hpp"

namespace MonteCarlo{

//! The single observer phase space discretization implementation
class SingleObserverPhaseSpaceDiscretizationImpl : public ObserverPhaseSpaceDiscretizationImpl
{
  
public:

  //! Typedef for the dimension value map
  typedef ObserverPhaseSpaceDiscretizationImpl::DimensionValueMap DimensionValueMap;

  //! Typedef for the bin index array
  typedef ObserverPhaseSpaceDiscretizationImpl::BinIndexArray BinIndexArray;

  //! Typedef for the bin index and weight array
  typedef ObserverPhaseSpaceDiscretizationImpl::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Constructor
  SingleObserverPhaseSpaceDiscretizationImpl()
  { /* ... */ }

  //! Destructor
  ~SingleObserverPhaseSpaceDiscretizationImpl()
  { /* ... */ }

  //! Assign a discretization to a dimension
  void assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension ) override;

  //! Get a dimension discretization
  const ObserverPhaseSpaceDimensionDiscretization& getDimensionDiscretization(
                  const ObserverPhaseSpaceDimension dimension ) const override;

  //! Check if a dimension has a discretization
  bool doesDimensionHaveDiscretization(
                  const ObserverPhaseSpaceDimension dimension ) const override;

  //! Get the number of discretized dimensions
  size_t getNumberOfDiscretizedDimensions() const override;

  //! Return the dimensions that have been discretized
  void getDiscretizedDimensions( std::set<ObserverPhaseSpaceDimension>& discretized_dimensions ) const override;

  //! Return the dimensions that have been discretized
  void getDiscretizedDimensions( std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const override;

  //! Return the dimensions that have been discretized
  void getDiscretizedDimensions( std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> >& discretized_dimensions ) const override;

  //! Return the total number of bins in the discretization
  size_t getNumberOfBins() const override;

  //! Return the number of bins for a phase space dimension
  size_t getNumberOfBins( const ObserverPhaseSpaceDimension dimension ) const override;

  //! Return the bin name
  std::string getBinName( const size_t bin_index ) const override;

  //! Print the discretization
  void print( std::ostream& os ) const override;

  //! Print a dimension discretization
  void print( std::ostream& os,
              const ObserverPhaseSpaceDimension dimension ) const override;

  //! Print a single bin of a dimension discretization
  void print( std::ostream& os,
              const ObserverPhaseSpaceDimension dimension,
              const size_t index ) const override;

  //! Check if the point is in the phase space discretization
  bool isPointInDiscretization(
                    const DimensionValueMap& dimension_values ) const override;

  //! Check if the point is in the phase space discretization
  bool isPointInDiscretization(
   const ObserverParticleStateWrapper& particle_state_wrapper ) const override;

  //! Check if the range intersects the phase space discretization
  bool doesRangeIntersectDiscretization(
   const ObserverParticleStateWrapper& particle_state_wrapper ) const override;

  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint( const DimensionValueMap& dimension_values,
                                   BinIndexArray& bin_indices ) const override;
  
  //! Calculate the bin indices of a point
  void calculateBinIndicesOfPoint(
                    const ObserverParticleStateWrapper& particle_state_wrapper,
                    BinIndexArray& bin_indices ) const override;

  //! Calculate the bin indices and weights of a range
  void calculateBinIndicesAndWeightsOfRange(
             const ObserverParticleStateWrapper& particle_state_wrapper,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;
  
  size_t calculateDiscretizationIndex( const std::unordered_map<ObserverPhaseSpaceDimension, size_t>& dimension_bin_indices) const override;

protected:

  //! Set the dimension discretization
  void setDimensionDiscretization(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization );

  //! Get the dimension discretization
  const ObserverPhaseSpaceDimensionDiscretization&
  getDimensionDiscretization() const;
  
private:
  
  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ObserverPhaseSpaceDiscretizationImpl );
    ar & BOOST_SERIALIZATION_NVP( d_dimension_discretization );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The discretized dimension
  std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>
  d_dimension_discretization;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::SingleObserverPhaseSpaceDiscretizationImpl, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( SingleObserverPhaseSpaceDiscretizationImpl, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, SingleObserverPhaseSpaceDiscretizationImpl );

#endif // end MONTE_CARLO_SINGLE_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SingleObserverPhaseSpaceDiscretizationImpl.hpp
//---------------------------------------------------------------------------//
