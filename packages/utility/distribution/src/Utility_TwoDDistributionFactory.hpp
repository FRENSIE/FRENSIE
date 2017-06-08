//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDDistributionFactory.hpp
//! \author Alex Robinson
//! \brief  The two-dimensional distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_DISTRIBUTION_FACTORY_HPP
#define UTILITY_TWO_D_DISTRIBUTION_FACTORY_HPP

// Std Lib Includes
#include <memory>
#include <map>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Utility_TwoDDistribution.hpp"

namespace Utility{

//! The two-dimensional distribution factory class
class TwoDDistributionFactory
{

public:

  //! Default constructor
  TwoDDistributionFactory();

  //! Constructor
  TwoDDistributionFactory( const Teuchos::RCP<const Teuchos::ParameterList>&
                           raw_one_d_distributions );

  //! Destructor
  ~TwoDDistributionFactor()
  { /* ... */ }

  //! Create the two-dimensional distribution
  std::shared_ptr<TwoDDistribution> createDistribution(
                  const Teuchos::ParameterList& raw_two_d_distribution ) const;

private:

  // Validate the two-d distribution representation
  void validateTwoDDistributionRep(
                  const Teuchos::ParameterList& raw_two_d_distribution ) const;

  // Validate the secondary distribution names
  void validateSecondaryDistributionNames(
       const Teuchos::Array<std::string>& secondary_distribution_names ) const;

  // Check if the type is tabular
  static bool isTabular( const std::string& type );

  // Create a tabular distribution
  std::shared_ptr<TwoDDistribution> createTabularDistribution(
                  const std::string& type,
                  const Teuchos::ParameterList& raw_two_d_distribution ) const;

  // Create a histogram tabular distribution
  std::shared_ptr<TwoDDistribution> createHistogramTabularDistribution(
       const Teuchos::Array<double>& primary_grid,
       const Teuchos::Array<std::string>& secondary_distribution_names ) const;

  // Create an interpolated tabular distribution
  std::shared_ptr<TwoDDistribution> createInterpolatedTabularDistribution(
       const std::string& type,
       const Teuchos::Array<double>& primary_grid,
       const Teuchos::Array<std::string>& secondary_distribution_names ) const;

  // Check if the tabular distribution is fully tabular
  bool isTabularDistributionFullyTabular(
       const Teuchos::Array<std::string>& secondary_distribution_names ) const;

  // The one-dimensional distributions
  std::map<std::string,std::shared_ptr<const Utility::OneDDistribution> >
  OneDDistributionNameMap;

  OneDDisistributionNameMap d_one_d_distribution_name_map;
};
  
} // end Utility namespace

#endif // end UTILITY_TWO_D_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDDistributionFactory.hpp
//---------------------------------------------------------------------------//
