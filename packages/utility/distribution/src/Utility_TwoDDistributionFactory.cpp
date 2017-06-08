//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  The two-dimensional distribution factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TwoDDistributionFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{
  
// Default constructor
TwoDDistributionFactory::TwoDDistributionFactory()
  : d_one_d_distribution_name_map()
{ /* ... */ }

// Constructor
TwoDDistributionFactory::TwoDDistributionFactory(
                              const Teuchos::RCP<const Teuchos::ParameterList>&
                              raw_one_d_distributions )
  : d_one_d_distribution_name_map()
{
  // Extract the one-d distributions
  Teuchos::ParameterList::ConstIterator one_d_dist_it, one_d_dist_end;
  one_d_dist_it = raw_one_d_distributions.begin();
  one_d_dist_end = raw_one_d_distributions.end();

  while( one_d_dist_it != one_d_dist_end )
  {
    // Make sure that no parameters are lists
    TEST_FOR_EXCEPTION( one_d_dist_it->second.isList(),
                        std::runtime_error,
                        "All one-d distributions must be specified as simple "
                        "parameters (not parameter lists)!" );

    Teuchos::RCP<const Teuchos::ParameterEntry>
      entry( &one_d_dist_it->second, false );

    d_one_d_distribution_name_map[one_d_dist_it->first] =
      Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
        
    ++one_d_dist_it;
  }
}

// Create the two-dimensional distribution
std::shared_ptr<TwoDDistribution> TwoDDistributionFactory::createDistribution(
                   const Teuchos::ParameterList& raw_two_d_distribution ) const
{
  // Validate the two-d distribution representation
  this->validateTwoDDistributionRep( raw_two_d_distribution );

  // Extract the type
  std::string type = raw_two_d_distribution.get<std::string>( "Type" );

  if( this->isTabular( type ) )
    return this->createTabularDistribution( raw_two_d_distribution );
  else
    return std::shared_ptr<TwoDDistribution>();
}

// Validate the two-d distribution representation
void TwoDDistributionFactory::validateTwoDDistributionRep(
                   const Teuchos::ParameterList& raw_two_d_distribution ) const
{
  TEST_FOR_EXCEPTION( !raw_two_d_distribution.isParameter( "Type" ),
                      std::runtime_error,
                      "A two-d distribution type must be specified!" );

  std::string type = raw_two_d_distribution.get<std::string>( "Type" );

  if( this->isTabular( type ) )
  {
    TEST_FOR_EXCEPTION(
      !( (raw_two_d_distribution.isParameter( "Primary Grid" ) &&
          raw_two_d_distribution.isParameter( "Secondary Distributions" )) ||
         raw_two_d_distribution.isParameter( "Combined Grid Distributions" ) ),
      std::runtime_error,
      "A tabular two-d distribution must have the primary grid and secondary "
      "distributions specified!" );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Two-d distribution type " << type <<
                     " is not supported!" );
  }
}

// Check if the type is tabular
bool TwoDDistributionFactory::isTabular( const std::string& type )
{
  return type == "Histogram Distribution" ||
    type == "Interpolated LinLinLin Distribution" ||
    type == "Interpolated LinLinLog Distribution" ||
    type == "Interpolated LinLogLin Distribution" ||
    type == "Interpolated LinLogLog Distribution" ||
    type == "Interpolated LogLinLin Distribution" ||
    type == "Interpolated LogLinLog Distribution" ||
    type == "Interpolated LogLogLin Distribution" ||
    type == "Interpolated LogLogLog Distribution";
}

// Create a tabular distribution
std::shared_ptr<TwoDDistribution>
TwoDDistributionFactory::createTabularDistribution(
                   const std::string& type,
                   const Teuchos::ParameterList& raw_two_d_distribution ) const
{
  // Extract the primary grid and secondary distribution names
  Teuchos::Array<double> primary_grid;
  Teuchos::Array<std::string> secondary_dist_names;
  
  if( raw_two_d_distribution.isParameter( "Combined Grid Distributions" ) )
  {
    const Utility::ArrayString& array_string =
      raw_two_d_distribution.get<Utility::ArrayString>( "Combined Grid Distributions" );

    Teuchos::Array<Utility::Tuple<double,std::string> >
      combined_grid_dist_names;

    try{
      combined_grid_dist_names =
        array_string.getConcreteArray<Utility::Tuple<double,std::string> >();
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                std::runtime_error,
                                "Error: The combined grid distributions for "
                                "two-d distribution "
                                << raw_two_d_distribution.name() << "are not "
                                "valid!" );

    primary_grid.resize( combined_grid_dist_names.size() );
    secondary_dist_names.resize( combined_grid_dist_names.size() );
    
    for( size_t i = 0; i < combined_grid_dist_names.size(); ++i )
    {
      primary_grid[i] = Utility::get<0>( combined_grid_dist_names[i] );
      secondary_dist_names[i] = Utility::get<1>( combined_grid_dist_names[i] );
    }
  }
  else
  {
    {
      const Utility::ArrayString& array_string =
        raw_two_d_distribution.get<Utility::ArrayString>( "Primary Grid" );

      try{
        primary_grid = array_string.getConcreteArray<double>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                  std::runtime_error,
                                  "Error: The primary grid for two-d "
                                  "distribution "
                                  << raw_two_d_distribution.name() << "is not "
                                  "valid!" );
    }
    {
      const Utility::ArrayString& array_string =
        raw_two_d_distribution.get<Utility::ArrayString>( "Secondary Distributions" );
      
      try{
        secondary_dist_names = array_string.getConcreteArray<std::string>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                  std::runtime_error,
                                  "Error: The secondary distribution names "
                                  "for two-d distribution "
                                  << raw_two_d_distribution.name() << " are "
                                  "not valid!" );      
    }
  }

  // Validate the secondary distribution names
  this->validateSecondaryDistributionNames( secondary_dist_names );

  if( type == "Histogram Distribution" )
  {
    return this->createHistogramTabularDistribution( primary_grid,
                                                     secondary_dist_names );
  }
  else if( type.find( "Interpolated" ) < type.size() )
  {
    return this->createInterpolatedTabularDistribution( type,
                                                        primary_grid,
                                                        secondary_dist_names );
  }
  else
    return std::shared_ptr<TwoDDistribution>();
}

// Validate the secondary distribution names
void TwoDDistributionFactory::validateSecondaryDistributionNames(
        const std::string& two_d_distribution_rep_name,
        const Teuchos::Array<std::string>& secondary_distribution_names ) const
{
  for( int i = 0; i < secondary_distribution_names.size(); ++i )
  {
    const std::string& one_d_dist_name = secondary_distribution_names[i];
    
    TEST_FOR_EXCEPTION( d_one_d_distribution_name_map.find( one_d_dist_name )==
                        d_one_d_distribution_name_map.end(),
                        std::runtime_error,
                        "Unknown one-d distribution name specified in two-d "
                        "distribution " << two_d_distribution_rep_name <<
                        " (" << one_d_dist_name << ")!" );
  }
}

// Create a histogram tabular distribution
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

  // Check if the distribution is fully tabular
  if( this->isTabularDistributionFullyTabular( secondary_distribution_names ) )
  {
    Teuchos::Array<std::shared_ptr<const Utility::TabularOneDDistribution> >
      secondary_distributions( primary_grid.size() - 1 );

    for( size_t i = 0; i < secondary_distributions.size(); ++i )
    {
      secondary_distributions[i] =
        std::dynamic_pointer_cast<const Utility::TabularOneDDistribution>(
            d_one_d_distribution_name_map.find( secondary_distribution_names[i] )->second );
    }

    return std::shared_ptr<TwoDDistribution>(
              new HistogramFullyTabularTwoDDistribution(
                                     primary_grid, secondary_distributions ) );
  }
  else
  {
    Teuchos::Array<std::shared_ptr<const Utility::OneDDistribution> >
      secondary_distributions( primary_grid.size() - 1 );

    for( size_t i = 0; i < secondary_distributions.size(); ++i )
    {
      secondary_distributions[i] = d_one_d_distribution_name_map.find( secondary_distribution_names[i] )->second;
    }

    return std::shared_ptr<TwoDDistribution>(
              new HistogramPartiallyTabularTwoDDistribution(
                                     primary_grid, secondary_distributions ) );
  }
}

// Create an interpolated tabular distribution
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

  // Check if the distribution is fully tabular
  if( this->isTabularDistributionFullyTabular( secondary_distribution_names ) )
  {
    Teuchos::Array<std::shared_ptr<const Utility::TabularOneDDistribution> >
      secondary_distributions( primary_grid.size() );

    for( size_t i = 0; i < secondary_distributions.size(); ++i )
    {
      secondary_distributions[i] =
        std::dynamic_pointer_cast<const Utility::TabularOneDDistribution>(
            d_one_d_distribution_name_map.find( secondary_distribution_names[i] )->second );
    }

    return std::shared_ptr<TwoDDistribution>(
              new InterpolatedFullyTabularTwoDDistribution(
                                     primary_grid, secondary_distributions ) );
  }
  else
  {
    Teuchos::Array<std::shared_ptr<const Utility::OneDDistribution> >
      secondary_distributions( primary_grid.size() );

    for( size_t i = 0; i < secondary_distributions.size(); ++i )
    {
      secondary_distributions[i] = d_one_d_distribution_name_map.find( secondary_distribution_names[i] )->second;
    }

    return std::shared_ptr<TwoDDistribution>(
              new InterpolatedPartiallyTabularTwoDDistribution(
                                     primary_grid, secondary_distributions ) );
  }
}

// Check if the tabular distribution is fully tabular
bool TwoDDistributionFactory::isTabularDistributionFullyTabular(
        const Teuchos::Array<std::string>& secondary_distribution_names ) const
{
  const bool fully_tabular = true;
  
  for( size_t i = 0; i < secondary_distribution_names.size(); ++i )
  {
    std::shared_ptr<const Utility::OneDDistribution>& one_d_distribution =
      d_one_d_distribution_name_map.find( secondary_distribution_names[i] )->second;
    
    if( !one_d_distribution->isTabular() )
    {
      fully_tabular = false;
      break;
    }
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TwoDDistributionFactory.cpp
//---------------------------------------------------------------------------//