//---------------------------------------------------------------------------//
//!
//! \file   HistogramDistribution.hpp
//! \author Alex Robinson
//! \brief  Histogram distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef HISTOGRAM_DISTRIBUTION_HPP
#define HISTOGRAM_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "Tuple.hpp"
#include "SearchAlgorithms.hpp"
#include "ContractException.hpp"

namespace FACEMC{

//! Histogram distribution class
class HistogramDistribution : public OneDDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  HistogramDistribution( const Teuchos::Array<double>& bin_boundaries,
			 const Teuchos::Array<double>& bin_values );

  //! Destructor
  ~HistogramDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a sample from the distribution given two random numbers
  double sample( const double random_number_1,
		 const double random_number_2 ) const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;
  
private:

  // The distribution (first = bin_min, second = bin_max, third = bin_PDF,
  // fourth = bin_CDF )
  Teuchos::Array<Quad<double,double,double,double> > d_distribution;
  
  // The normalization constant
  double d_norm_constant;
};

// Return a sample from the distribution given two random numbers
inline double HistogramDistribution::sample( 
					   const double random_number_1,
					   const double random_number_2 ) const
{
  // Make sure that the random numbers are in [0,1]
  testPrecondition( random_number_1 >= 0.0 );
  testPrecondition( random_number_1 <= 1.0 );
  testPrecondition( random_number_2 >= 0.0 );
  testPrecondition( random_number_2 <= 1.0 );
  
  // Sample the bin
  Teuchos::Array<Quad<double,double,double,double> >::const_iterator bin = 
    Search::binarySearchDiscreteData<FOURTH>( d_distribution.begin(),
					      d_distribution.end(),
					      random_number_1 );
  
  // Sample the value within the bin
  return random_number_2*(bin->second-bin->first) + bin->first;
}

} // end FACEMC namespace

#endif // end HISTOGRAM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end HistogramDistribution.hpp
//---------------------------------------------------------------------------//
