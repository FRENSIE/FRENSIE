//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDDistributionFactory_def.hpp
//! \author Alex Robinson
//! \brief  The two-dimensional distribution factory class template definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Create a histogram tabular distribution
template<typename ChildTwoDDistribution>
std::shared_ptr<TwoDDistribution>
TwoDDistributionFactory::createHistogramTabularDistribution(
        const Teuchos::Array<double>& primary_grid,
        const Teuchos::Array<std::string>& secondary_distribution_names ) const
{
  // Make sure that there is a secondary distribution for every grid point
  // except the last
  TEST_FOR_EXCEPTION(
                  secondary_distribution_names.size() == primary_grid.size() ||
                  secondary_distribution_names.size() == primary_grid.size()-1,
                  std::runtime_error,
                  "A two-d histogram distribution must have a secondary "
                  "distribution for every primary grid point except for the "
                  "last!" );
  
  Teuchos::Array<std::shared_ptr<const typename ChildTwoDDistribution::BaseOneDDistributionType> >
    secondary_distributions( primary_grid.size() - 1 );

  for( size_t i = 0; i < secondary_distributions.size(); ++i )
  {
    secondary_distributions[i] =
      std::dynamic_pointer_cast<const typename ChildTwoDDistribution::BaseOneDDistributionType>(
            d_one_d_distribution_name_map.find( secondary_distribution_names[i] )->second );
  }

  return std::shared_ptr<TwoDDistribution>(
                      new HistogramFullyTabularTwoDDistribution(
                                     primary_grid, secondary_distributions ) );
}
  
// Create an interpolated tabular distribution
template<template<typename,typename...> class ChildTwoDDistribution>
std::shared_ptr<TwoDDistribution>
TwoDDistributionFactory::createInterpolatedTabularDistribution(
        const std::string& type,
        const Teuchos::Array<double>& primary_grid,
        const Teuchos::Array<std::string>& secondary_distribution_names ) const
{
  // Make sure that there is a secondary distribution for every grid point
  TEST_FOR_EXCEPTION(
                  secondary_distribution_names.size() == primary_grid.size(),
                  std::runtime_error,
                  "A two-d interpolated distribution must have a secondary "
                  "distribution for every primary grid point!" );

  Teuchos::Array<std::shared_ptr<const typename ChildTwoDDistribution<LinLinLin>::BaseOneDDistributionType> >
      secondary_distributions( primary_grid.size() );

  for( size_t i = 0; i < secondary_distributions.size(); ++i )
  {
    secondary_distributions[i] =
      std::dynamic_pointer_cast<const typename ChildTwoDDistribution<LinLinLin>::BaseOneDDistributionType>(
            d_one_d_distribution_name_map.find( secondary_distribution_names[i] )->second );
  }

  if( type.find( "LinLinLin" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LinLinLin>(
                                     primary_grid, secondary_distributions ) );
  }
  else if( type.find( "LinLinLog" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LinLinLog>(
                                     primary_grid, secondary_distributions ) );
  }
  else if( type.find( "LinLogLin" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LinLogLin>(
                                     primary_grid, secondary_distributions ) );
  }
  else if( type.find( "LinLogLog" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LinLogLog>(
                                     primary_grid, secondary_distributions ) );
  }
  else if( type.find( "LogLinLin" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LogLinLin>(
                                     primary_grid, secondary_distributions ) );
  }
  else if( type.find( "LogLinLog" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LogLinLog>(
                                     primary_grid, secondary_distributions ) );
  }
  else if( type.find( "LogLogLin" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LogLogLin>(
                                     primary_grid, secondary_distributions ) );
  }
  else if( type.find( "LogLogLog" ) < type.size() )
  {
    return std::shared_ptr<TwoDDistribution>(
                      new ChildTwoDDistribution<Utility::LogLogLog>(
                                     primary_grid, secondary_distributions ) );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "The interpolation type (e.g. LinLinLin) must be "
                     "specified along with the type name with an "
                     "interpolated two-d distribution!" );
    return std::shared_ptr<TwoDDistribution>();
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TwoDDistributionFactory_def.hpp
//---------------------------------------------------------------------------//
