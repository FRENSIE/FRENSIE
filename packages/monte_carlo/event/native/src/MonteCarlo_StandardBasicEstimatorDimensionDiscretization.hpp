//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardBasicEstimatorDimensionDiscretization.hpp
//! \author Alex Robinson
//! \brief  The standard basic estimator dimension discretization declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP
#define MONTE_CARLO_STANDARD_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>

// FRENSIE Includes
#include "MonteCarlo_BasicEstimatorDimensionDiscretization.hpp"

namespace MonteCarlo{

/*! The standard basic estimator dimension discretization class
 * \details This class must be specialized for floating point types and
 * integer types (the default will be empty).
 */
template<typename T, typename Enabled = void>
class StandardBasicEstimatorDimensionDiscretization : public BasicEstimatorDimensionDiscretization<T>
{ /* ... */ };

/*! The standard basic estimator dimension discretization class partial 
 * specialization for floating point types (continuous dimensions)
 */
template<typename T>
class StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_floating_point<T> >::type> : public BasicEstimatorDimensionDiscretization<T>
{
  
public:

  //! Constructor
  StandardBasicEstimatorDimensionDiscretization(
                           const PhaseSpaceDimension dimension, 
                           const Teuchos::Array<T>& dimension_bin_boundaries );

  //! Destructor
  virtual ~StandardBasicEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  unsigned getNumberOfBins() const;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os, 
                             const unsigned bin_index ) const;

protected:

  //! Check if the value is contianed in the discretization
  bool isValueInDiscretization( const T value ) const;

  //! Calculate the index of the bin that the value falls in
  unsigned calculateBinIndex( const T value ) const;
};

/*! The standard basic estimator dimension discretization class parial
 * specialization for integral types (discrete dimensions)
 */
template<typename T>
class StandardBasicEstimatorDimensionDiscretization<T,typename boost::enable_if<boost::is_integral<T> >::type> : public BasicEstimatorDimensionDiscretization<T>
{

  public:

  //! Constructor
  StandardBasicEstimatorDimensionDiscretization(
                           const PhaseSpaceDimension dimension, 
                           const Teuchos::Array<T>& dimension_bin_boundaries );

  //! Destructor
  virtual ~StandardBasicEstimatorDimensionDiscretization()
  { /* ... */ }

  //! Return the number of bins in the discretization
  unsigned getNumberOfBins() const;

  //! Print the boundaries of a bin
  void printBoundariesOfBin( std::ostream& os, 
                             const unsigned bin_index ) const;

protected:

  //! Check if the value is contianed in the discretization
  bool isValueInDiscretization( const T value ) const;

  //! Calculate the index of the bin that the value falls in
  unsigned calculateBinIndex( const T value ) const;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardBasicEstimatorDimensionDiscretization_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_BASIC_ESTIMATOR_DIMENSION_DISCRETIZATION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardBasicEstimatorDimensionDiscretization.hpp
//---------------------------------------------------------------------------//
