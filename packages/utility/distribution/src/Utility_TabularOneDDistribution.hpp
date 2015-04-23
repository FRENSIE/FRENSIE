//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularOneDDistribution.hpp
//! \author Alex Robinson
//! \brief  Tabular one-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_ONE_D_DISTRIBUTION_HPP
#define UTILITY_TABULAR_ONE_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace Utility{

//! The tabular one-dimensional distribution declaration
class TabularOneDDistribution : public OneDDistribution
{

public:

  //! Constructor
  TabularOneDDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~TabularOneDDistribution()
  { /* ... */ }

  //! Evaluate the CDF
  virtual double evaluateCDF( const double indep_var_value ) const = 0;

  //! Return a random sample from the distribution and the sampled index 
  virtual double sampleAndRecordBinIndex( 
				       unsigned& sampled_bin_index ) const = 0;

  //! Return a random sample from the distribution at the given CDF value
  virtual double sampleWithRandomNumber( const double random_number ) const = 0;

  //! Return a random sample from the distribution in a subrange
  virtual double sampleInSubrange( const double max_indep_var ) const = 0;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  virtual double sampleWithRandomNumberInSubrange( 
					const double random_number,
					const double max_indep_var ) const = 0;

  //! Test if the distribution is tabular
  bool isTabular() const;
};

// Test if the distribution is tabular
inline bool TabularOneDDistribution::isTabular() const
{
  return true;
}

} // end Utility namespace

#endif // end UTILITY_TABULAR_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularOneDDistribution.hpp
//---------------------------------------------------------------------------//
