//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl.hpp
//! \author Alex Robinson
//! \brief  The detailed observer phase space discretization impl. class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP
#define MONTE_CARLO_DETAILED_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionDiscretization.hpp"

namespace MonteCarlo{

//! The detailed observer phase space discretization implementation
class DetailedObserverPhaseSpaceDiscretizationImpl : public ObserverPhaseSpaceDiscretizationImpl
{
  
public:

  //! Typedef for the dimension value map
  typedef ObserverPhaseSpaceDiscretizationImpl::DimensionValueMap DimensionValueMap;

  //! Typedef for the bin index array
  typedef ObserverPhaseSpaceDiscretizationImpl::BinIndexArray BinIndexArray;

  //! Typedef for the bin index and weight array
  typedef ObserverPhaseSpaceDiscretizationImpl::BinIndexWeightPairArray BinIndexWeightPairArray;

  //! Constructor
  DetailedObserverPhaseSpaceDiscretizationImpl()
  { /* ... */ }

  //! Destructor
  ~DetailedObserverPhaseSpaceDiscretizationImpl()
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

private:

  // The range intersects discretization method
  typedef std::function<bool(const ObserverParticleStateWrapper&)> RangeIntersectionMethod;

  // The calculate indices of range method type
  typedef std::function<void(const ObserverParticleStateWrapper&,BinIndexWeightPairArray&)> CalculateLocalBinIndicesOfRangeMethod;

  size_t calculateDiscretizationIndex( const std::vector<std::pair<ObserverPhaseSpaceDimension, size_t>>& dimension_bin_indices) const;

  // Create a range intersection method
  static RangeIntersectionMethod createRangeIntersectionMethodObject(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const bool is_range_dimension );
  
  // Create a calculate range method object
  static CalculateLocalBinIndicesOfRangeMethod createCalculateRangeMethodObject(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const bool is_range_dimension );

  // Check if the dimension value map is valid
  bool isDimensionValueMapValid(
                             const DimensionValueMap& dimension_values ) const;

  // Check if the bin index array is valid
  bool isBinIndexArrayValid( const BinIndexArray& bin_indices ) const;

  // Check if the bin index weight pair array is valid
  bool isBinIndexWeightPairArrayValid(
                const BinIndexWeightPairArray& bin_indices_and_weights ) const;

  // Check if the point is in the discretization (implementation)
  template<typename DimensionValueContainer>
  bool isPointInDiscretizationImpl(
              const DimensionValueContainer& dimension_value_container ) const;

  // Check if the value is in the dimension discretization
  bool isValueInDimensionDiscretization(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const DimensionValueMap& dimension_values ) const;

  // Check if the value is in the dimension discretization
  bool isValueInDimensionDiscretization(
     const ObserverPhaseSpaceDimensionDiscretization& dimension_discretization,
     const ObserverParticleStateWrapper& particle_state_wrapper ) const;

  // Calculate the local bin indices of the point (implementation)
  template<typename DimensionValueContainer>
  void calculateBinIndicesOfPointImpl(
                      const DimensionValueContainer& dimension_value_container,
                      BinIndexArray& bin_indices ) const;

  // Calculate the local bin indices of the value
  void calculateLocalBinIndicesOfValue(
                                  const ObserverPhaseSpaceDimension dimension,
                                  const DimensionValueMap& dimension_values,
                                  BinIndexArray& local_bin_indices ) const;

  // Calculate the local bin indices of the value
  void calculateLocalBinIndicesOfValue(
                   const ObserverPhaseSpaceDimension dimension,
                   const ObserverParticleStateWrapper& particle_state_wrapper,
                   BinIndexArray& local_bin_indices ) const;
  
  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The observer phase space dimension discretizations
  std::map<ObserverPhaseSpaceDimension,std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization> >
  d_dimension_discretization_map;

  // The observer phase space dimension range map
  std::map<ObserverPhaseSpaceDimension,bool>
  d_dimension_use_range_map;

  // The observer phase space dimension range method map
  std::map<ObserverPhaseSpaceDimension,std::pair<RangeIntersectionMethod,CalculateLocalBinIndicesOfRangeMethod> >
  d_dimension_range_method_map;

  // The observer phase space dimension index step size map
  std::map<ObserverPhaseSpaceDimension,size_t>
  d_dimension_index_step_size_map;

  // The observer phase space dimension ordering
  std::vector<ObserverPhaseSpaceDimension> d_dimension_ordering;
};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::DetailedObserverPhaseSpaceDiscretizationImpl, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DETAILED_OBSERVER_PHASE_SPACE_DISCRETIZATION_IMPL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedObserverPhaseSpaceDiscretizationImpl.hpp
//---------------------------------------------------------------------------//
