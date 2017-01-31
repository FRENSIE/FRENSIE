//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  Unordered typed observer phase space dimension discretization decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

// Std Lib Includes
#include <set>
#include <unordered_set>
#include <vector>

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_TypedObserverPhaseSpaceDimensionDiscretization.hpp"

namespace MonteCarlo{

/*! The unordered typed observer phase space dimension discretization class
 * 
 * This is a dummy class that will cause a compilation error if the dimension 
 * value type associated with a dimension is not an integral type.
 */
template<ObserverPhaseSpaceDimension dimension, typename Enabled = void>
class UnorderedTypeObserverPhaseSpaceDimensionDiscretization
{ /* ... */ };

//! The unordered typed observer phase space dimension discretization class
template<ObserverPhaseSpaceDimension dimension>
class UnorderedTypedObserverPhaseSpaceDimensionDiscretization<dimension,typename boost::enable_if<boost::is_integral<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType> >::type> : public TypedObserverPhaseSpaceDimensionDiscretization<dimension>
{

public:

  //! Typedef for the dimension value type
  typedef typename TypedObserverPhaseSpaceDimensionDiscretization<dimension>::DimensionValueType DimensionValueType;

  //! Typedef for the bin set
  typedef std::set<DimensionValueType> BinSet;
  
  //! Typedef for the bin set array
  typedef std::vector<BinSet> BinSetArray;

  //! Constructor
  UnorderedTypedObserverPhaseSpaceDimensionDiscretization(
                                           const BinSetArray& dimension_bins );

  //! Destructor
  virtual ~UnorderedTypedObserverPhaseSpaceDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  size_t getNumberOfBins() const override;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
                             const size_t bin_index ) const override;

  //! Print the dimension discretization
  void print( std::ostream& os ) const override;

  //! Export the bin boundaries
  void exportData( const ParticleHistoryObserver::idType estimator_id,
                   EstimatorHDF5FileHandler& hdf5_file ) const override;

protected:

  //! Check if the value is contained in the discretization
  bool isValueInDiscretization( const DimensionValueType value ) const override;

  //! Check if the value range intersects the discretization
  bool doesRangeIntersectDiscretization(
                           const DimensionValueType range_start,
                           const DimensionValueType range_end ) const override;

  //! Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const DimensionValueType value,
                                   BinIndexArray& bin_indices ) const override;

  //! Calculate the index of bins that the range falls in
  void calculateBinIndicesOfRange(
             const DimensionValueType range_start,
             const DimensionValueType range_end,
             BinIndexWeightPairArray& bin_indices_and_weights ) const override;

private:

  //! Calculate the set of bin indices that the value falls in
  void calculateSetOfBinIndicesOfValue(const DimensionValueType value,
                                       std::set<size_t>& bin_index_set ) const;

  // The bin set array
  BinSetArray d_dimension_bins;

  // The set of values in all bins (for fast lookup)
  BinSet d_merged_bin_set;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_UNORDERED_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UnorderedTypedObserverPhaseSpaceDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
