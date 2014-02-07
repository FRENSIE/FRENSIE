//---------------------------------------------------------------------------//
//!
//! \file   UniformDistribution.hpp
//! \author Alex Robinson
//! \brief  Uniform distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UNIFORM_DISTRIBUTION_HPP
#define UNIFORM_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"

namespace FACEMC{

//! Uniform distribution class
class UniformDistribution : public OneDDistribution
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
 
  //! Constructor
  UniformDistribution( const double min_independent_value, 
		       const double max_independent_value,
		       const double dependent_value );
  
  //! Destructor
  ~UniformDistribution()
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

  // The min independent value
  double d_min_independent_value;
  
  // The max independent value
  double d_max_independent_value;

  // The uniform distribution dependent value
  double d_dependent_value;

  // The uniform distribution PDF value
  double d_pdf_value;
};

} // end FACEMC namespace 

#endif // end UNIFORM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end UniformDistribution.hpp
//---------------------------------------------------------------------------//
