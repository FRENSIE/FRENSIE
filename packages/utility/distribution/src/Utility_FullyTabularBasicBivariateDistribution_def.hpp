//---------------------------------------------------------------------------//
//!
//! \file   Utility_FullyTabularBasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The fully tabular basic bivariate distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

namespace Utility{

// Constructor
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareFullyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
  : BaseType( primary_indep_grid, secondary_distributions )
{ /* ... */ }

// Return a random sample from the secondary conditional PDF
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditional( primary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details When the secondary conditional sampling method is stochastic it
 * is common to sample from one of the distributions on the bin boundaries
 * and then to scale the sample so that it preserves intermediate grid limits.
 * Certain methods require the unscaled (or raw) sample, which can be 
 * acquired with this method.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  raw_sample = this->sampleSecondaryConditionalAndRecordBinIndices(
                                                       primary_indep_var_value,
                                                       primary_bin_index,
                                                       secondary_bin_index );

  return raw_sample;
}

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalInSubrange(
                                               primary_indep_var_value,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). Ideally the 
 * "non-exact" method will be faster and stochastically correct.
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Save the distribution to an archive
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareFullyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> );

#endif // end UTILITY_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_FullyTabularBasicBivariateDistribution_def.hpp