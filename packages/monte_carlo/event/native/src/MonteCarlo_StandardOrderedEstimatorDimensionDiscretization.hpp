//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardOrderedEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  The standard ordered estimator dimension discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_STANDARD_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>

// FRENSIE Includes
#include "MonteCarlo_OrderedEstimatorDimensionDiscretization.hpp"

namespace MonteCarlo{

/*! The standard ordered estimator dimension discretization class
 * \details This class must be specialized for floating point types and
 * integer types (the default will be empty).
 */
template<typename T, typename Enabled = void>
class StandardOrderedEstimatorDimensionDiscretization : public OrderedEstimatorDimensionDiscretization<T>
{ /* ... */ };

/*! The standard ordered estimator dimension discretization class partial
 * specialization for floating point types (continuous dimensions)
 */
template<typename T>
class StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type> : public OrderedEstimatorDimensionDiscretization<T>
{

public:

  //! Constructor
  StandardOrderedEstimatorDimensionDiscretization(
                           const ObserverPhaseSpaceDimension dimension,
                           const BinBoundaryArray& dimension_bin_boundaries );

  //! Destructor
  virtual ~StandardOrderedEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  size_t getNumberOfBins() const;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
                             const size_t bin_index ) const;

protected:

  //! Check if the value is contianed in the discretization
  bool isValueInDiscretization( const T value ) const;

  //! Check if the value range intersects the discretization
  bool doesRangeIntersectDiscretization( const T range_start,
                                         const T range_end ) const;

private:

  // Calculate the index of the bin that the value falls in
  size_t calculateBinIndexOfValue( const T value ) const;

  // Calculate the size of a bin
  double calculateBinSize( const size_t bin_index ) const;

  // Calculate the size of a bin intersection
  double calculateBinIntersectionSize( const size_t bin_index,
                                       const T range_start,
                                       const T range_end ) const;
};

/*! The standard ordered estimator dimension discretization class parial
 * specialization for integral types (discrete dimensions)
 */
template<typename T>
class StandardOrderedEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type> : public OrderedEstimatorDimensionDiscretization<T>
{

  public:

  //! Constructor
  StandardOrderedEstimatorDimensionDiscretization(
                           const ObserverPhaseSpaceDimension dimension,
                           const BinBoundaryArray& dimension_bin_boundaries );

  //! Destructor
  virtual ~StandardOrderedEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  size_t getNumberOfBins() const override;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os,
                             const size_t bin_index ) const override;

protected:

  //! Check if the value is contianed in the discretization
  bool isValueInDiscretization( const T value ) const;

  //! Check if the value range intersects the discretization
  bool doesRangeIntersectDiscretization( const T range_start,
                                         const T range_end ) const;

private:

  // Calculate the index of bins that the value falls in
  void calculateBinIndicesOfValue( const T value,
                                   BinIndexArray& bin_indices ) const;

  // Calculate the index of bins that the range falls in
  void calculateBinIndicesOfRange(
                      const T range_start,
                      const T range_end,
                      BinIndexWeightPairArray& bin_indices_and_weights ) const;

  //! Calculate the index of the bin that the value falls in
  size_t calculateBinIndexOfValue( const T value ) const;

  //! Calculate the size of a bin
  double calculateBinSize( const size_t bin_index ) const;

  //! Calculate the size of a bin intersection
  double calculateBinIntersectionSize( const size_t bin_index,
                                       const T range_start,
                                       const T range_end ) const;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardOrderedEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ORDERED_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardOrderedEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
