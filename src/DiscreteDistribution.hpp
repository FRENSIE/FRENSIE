//---------------------------------------------------------------------------//
//!
//! \file   DiscreteDistribution.hpp
//! \author Alex Robinson
//! \brief  Discrete distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DISCRETE_DISTRIBUTION_HPP
#define DISCRETE_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "SearchAlgorithms.hpp"
#include "Tuple.hpp"
#include "ContractException.hpp"

namespace FACEMC{

//! Discrete distribution class
class DiscreteDistribution : public OneDDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  DiscreteDistribution( const Teuchos::Array<double>& independent_values,
			const Teuchos::Array<double>& dependent_values );

  //! Destructor
  ~DiscreteDistribution()
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

  //! Return the lower bound of the independent variable
  double getLowerBoundOfIndepVar() const;

private:

  // The distribution (first = independent value, second = CDF)
  Teuchos::Array<Pair<double,double> > d_distribution;
};

} // end FACEMC namespace

#endif // end DISCRETE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end DiscreteDistribution.hpp
//---------------------------------------------------------------------------//
