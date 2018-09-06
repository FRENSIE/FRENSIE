//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularBasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The tabular bivariate distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Constructor
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::UnitAwareTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
  : d_distribution( primary_indep_grid.size() ),
    d_extend_beyond_primary_limits( false )
{
  // Check that the distribution data is valid
  this->verifyValidData( primary_indep_grid, secondary_distributions );

  // Initialize the distribution
  this->initialize( primary_indep_grid, secondary_distributions );
}

// Extend the distribution beyond the primary independent variable limits
/*! \details The default behavior of this class when evaluating the
 * the distribution outside of the primary independent variable limits is
 * to return zero. After calling this function that behavior will instead
 * be to use the appropriate limiting secondary distribution for all
 * primary values beyond the defined primary limits.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::extendBeyondPrimaryIndepLimits()
{
  d_extend_beyond_primary_limits = true;
}

// Limit the distribution to the primary independent variable limits
/*! \details The default behavior of this class when evaluating the
 * the distribution outside of the primary independent variable limits is
 * to return zero. This method does not need to be called unless
 * the extendDistributionBeyondPrimaryIndepLimits method has been called
 * (this method will restore the default behavior).
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::limitToPrimaryIndepLimits()
{
  d_extend_beyond_primary_limits = false;
}

// Check if the distribution is being extended beyond the primary limits
/*! \details The default behavior of this class when evaluating the
 * the distribution outside of the primary independent variable limits is
 * to return zero. When the limits have been extended that behavior will
 * instead be to use the appropriate limiting secondary distribution for all
 * primary values beyond the defined primary limits.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
bool UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::arePrimaryLimitsExtended() const
{
  return d_extend_beyond_primary_limits;
}

// Return the upper bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
auto UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::getUpperBoundOfPrimaryIndepVar() const -> PrimaryIndepQuantity
{
  return Utility::get<0>(d_distribution.back());
}

// Return the lower bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
auto UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::getLowerBoundOfPrimaryIndepVar() const -> PrimaryIndepQuantity
{
  return Utility::get<0>(d_distribution.front());
}

// Test if the distribution is tabular in the primary dimension
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
bool UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::isPrimaryDimensionTabular() const
{
  return true;
}

// Set the distribution
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::setDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
{
  // Check that the distribution data is valid
  this->verifyValidData( primary_indep_grid, secondary_distributions );

  // Initialize the distribution
  this->initialize( primary_indep_grid, secondary_distributions );
}

// Find the bin boundaries
/*! \details The lower and upper boundary will only be equal when the
 * primary_independent_var_value is outside of the primary grid limits.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
inline void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::findBinBoundaries(
          const PrimaryIndepQuantity primary_independent_var_value,
          DistributionDataConstIterator& lower_bin_boundary,
          DistributionDataConstIterator& upper_bin_boundary ) const
{
  if( primary_independent_var_value < Utility::get<0>(d_distribution.front()) )
  {
    lower_bin_boundary = d_distribution.begin();
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( primary_independent_var_value > Utility::get<0>(d_distribution.back()) )
  {
    lower_bin_boundary = d_distribution.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( primary_independent_var_value == Utility::get<0>(d_distribution.back()) )
  {
    lower_bin_boundary = d_distribution.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;

    --lower_bin_boundary;
  }
  else
  {
    lower_bin_boundary = d_distribution.begin();
    upper_bin_boundary = d_distribution.end();

    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>(
					       lower_bin_boundary,
                                               upper_bin_boundary,
					       primary_independent_var_value );
    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;
  }
}

// Calculate the index of the desired bin
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
inline size_t UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::calculateBinIndex(
                      const DistributionDataConstIterator& bin_boundary ) const
{
  return std::distance( d_distribution.begin(), bin_boundary );
}

// Check that all secondary distributions are continuous
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
bool UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::areSecondaryDistributionsContinuous() const
{
  bool all_continuous = true;

  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( !Utility::get<1>(d_distribution[i])->isContinuous() )
    {
      all_continuous = false;

      break;
    }
  }

  return all_continuous;
}

// Add tabular distribution data to the stream
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
template<typename... Types>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::toStreamTabularDistImpl(
                                                   std::ostream& os,
                                                   const std::string& name,
                                                   const Types&... data ) const
{
  // Extract the primary grid and secondary distribution strings
  std::vector<PrimaryIndepQuantity> primary_indep_grid( d_distribution.size() );
  std::vector<std::string> secondary_dist_strings( d_distribution.size() );

  for( size_t i = 0; i < primary_indep_grid.size(); ++i )
  {
    primary_indep_grid[i] = Utility::get<0>( d_distribution[i] );

    secondary_dist_strings[i] =
      Utility::toString( *Utility::get<1>( d_distribution[i] ) );
  }

  this->toStreamDistImpl( os,
                          name,
                          std::make_pair( "primary grid", primary_indep_grid ),
                          std::make_pair( "secondary dists", secondary_dist_strings ),
                          data... );
}

// Initialize the distribution
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::initialize(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
{
  d_distribution.resize( primary_indep_grid.size() );

  for( size_t i = 0; i < primary_indep_grid.size(); ++i )
  {
    Utility::get<0>( d_distribution[i] ) = primary_indep_grid[i];
    Utility::get<1>( d_distribution[i] ) = secondary_distributions[i];
  }
}

// Verify that the distribution data is valid
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::verifyValidData(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
{
  // Make sure that the primary grid is valid
  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( primary_indep_grid.begin(),
                                                primary_indep_grid.end() ),
                      Utility::BadBivariateDistributionParameter,
                      "The tabular basic bivariate distribution cannot be "
                      "created because the primary grid is not sorted!" );

  // Make sure that the secondary distributions are valid
  TEST_FOR_EXCEPTION( primary_indep_grid.size() != secondary_distributions.size(),
                      Utility::BadBivariateDistributionParameter,
                      "The tabular basic bivariate distribution cannot be "
                      "created because the number of primary grid points ("
                      << primary_indep_grid.size() << ") does not match the "
                      "number of provided secondary distributions ("
                      << secondary_distributions.size() << ")!" );

  typename std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >::const_iterator bad_secondary_dist =
    std::find_if( secondary_distributions.begin(),
                  secondary_distributions.end(),
                  [](const std::shared_ptr<const BaseUnivariateDistributionType>& dist){ return dist.get() == NULL; } );

  TEST_FOR_EXCEPTION( bad_secondary_dist != secondary_distributions.end(),
                      Utility::BadBivariateDistributionParameter,
                      "The tabular basic bivariate distribution cannot be "
                      "created because the secondary distribution at index "
                      << std::distance( secondary_distributions.begin(), bad_secondary_dist ) <<
                      " is NULL!" );
}

// Save the distribution to an archive
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
template<typename Archive>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_extend_beyond_primary_limits );
}

// Load the distribution from an archive
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         template<typename...> class BaseUnivariateDistribution>
template<typename Archive>
void UnitAwareTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,BaseUnivariateDistribution>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_extend_beyond_primary_limits );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareUnivariateDistribution> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareUnivariateDistribution> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareTabularUnivariateDistribution> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareTabularUnivariateDistribution> );

#endif // end UTILITY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularBasicBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
