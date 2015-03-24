//---------------------------------------------------------------------------//
//!
//! \file   Utility_HydrogenFormFactorDistribution.hpp
//! \author Alex Robinson
//! \brief  The Hydrogen form factor distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HYDROGEN_FORM_FACTOR_DISTRIBUTION_HPP
#define UTILITY_HYDROGEN_FORM_FACTORY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Hydrogen form factor distribution class
class HydrogenFormFactorDistribution : public OneDDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  HydrogenFormFactorDistribution();

  //! Destructor
  ~HydrogenFormFactorDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;  

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;
};

} // end Utility namespace

#endif // end UTILITY_HYDROGEN_FORM_FACTOR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HydrogenFormFactorDistribution.hpp
//---------------------------------------------------------------------------//
