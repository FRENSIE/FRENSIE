//---------------------------------------------------------------------------//
//!
//! \file   ThirtyTwoEquiprobableBinDistribution.hpp
//! \author Alex Robinson
//! \brief  Thirty-two equiprobable bin distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP
#define THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"

namespace FACEMC{

//! The 32 equiprobable bin distribution class
class ThirtyTwoEquiprobableBinDistribution : public OneDDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  ThirtyTwoEquiprobableBinDistribution( const Teuchos::Array<double>& bin_boundaries);

  //! Destructor
  ~ThirtyTwoEquiprobableBinDistribution()
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

private:

  // The disribution type
  static const OneDDistributionType distribution_type = 
    THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION;

  // The distribution
  Teuchos::Array<double> d_bin_boundaries;
};
  
} // end FACEMC namespace

#endif // end THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end 32EquiprobableBinDistribution.hpp
//---------------------------------------------------------------------------//
