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

} // end FACEMC namespace

#endif // end HISTOGRAM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end HistogramDistribution.hpp
//---------------------------------------------------------------------------//
