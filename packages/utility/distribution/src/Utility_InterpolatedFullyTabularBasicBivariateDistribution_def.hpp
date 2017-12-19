//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularBasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular basic bivariate dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_SERIALIZATION_DISTRIBUTION4_EXPORT_IMPLEMENT( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution );

namespace Utility{

namespace Details{

//! Helper class used to construct a cdf interpolation policy
template<typename YProcessingTag, typename XProcessingTag>
struct CDFInterpolationHelper
{ /* ... */ };

//! Helper class used to construct a LinLinLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLinLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLog CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLog CDFInterpPolicy;
};
  
} // end Details namespace

// Default constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution()
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}
  
// Constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
  : BaseType( primary_indep_grid, secondary_distributions )
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Grid constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularBasicBivariateDistribution(
       const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
       const std::vector<std::vector<SecondaryIndepQuantity> >& secondary_indep_grids,
       const std::vector<std::vector<DepQuantity> >& dependent_values )
{
  TEST_FOR_EXCEPTION( primary_indep_grid.size() != secondary_indep_grids.size(),
                      Utility::BadBivariateDistributionParameter,
                      "The interpolated fully tabular basic bivariate "
                      "distribution cannot be constructed because the number "
                      "of primary grid points ("
                      << primary_indep_grid.size() << ") does not match the "
                      "number of secondary indep grids ("
                      << secondary_indep_grids.size() << ")!" );

  TEST_FOR_EXCEPTION( primary_indep_grid.size() != dependent_values.size(),
                      Utility::BadBivariateDistributionParameter,
                      "The interpolated fully tabular basic bivariate "
                      "distribution cannot be constructed because the number "
                      "of primary grid points ("
                      << primary_indep_grid.size() << ") does not match the "
                      "number of dependent value grids ("
                      << dependent_values.size() << ")!" );
  
  // Construct the univariate distributions
  std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >
    secondary_distributions( primary_indep_grid.size() );
  
  for( size_t i = 0; i < primary_indep_grid.size(); ++i )
  {
    secondary_distributions[i].reset(
          new UnitAwareTabularDistribution<typename TwoDInterpPolicy::SecondaryBasePolicy,SecondaryIndependentUnit,DependentUnit>(
                                                      secondary_indep_grids[i],
                                                      dependent_values[i] ) );
  }

  // Set the distribution data
  this->setDistribution( primary_indep_grid, secondary_distributions );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  typedef typename Details::CDFInterpolationHelper<typename TwoDInterpPolicy::SecondIndepVarProcessingTag,typename TwoDInterpPolicy::FirstIndepVarProcessingTag>::CDFInterpPolicy CDFInterpPolicy;
  
  return this->template evaluateImpl<CDFInterpPolicy,double>(
                                  primary_indep_var_value,
                                  secondary_indep_var_value,
                                  &BaseUnivariateDistributionType::evaluateCDF,
                                  0.0,
                                  1.0 );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the sample.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Dummy variable
  SecondaryIndepQuantity dummy_raw_sample;
  
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                      &BaseUnivariateDistributionType::sampleAndRecordBinIndex,
                      std::placeholders::_1,
                      std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   dummy_raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the raw_sample. The raw_sample is the original sample
 * that was made before the scaling operation was done.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            size_t& primary_bin_index,
                            size_t& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseUnivariateDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseUnivariateDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseUnivariateDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value ) );
  
  // Generate a random number
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value ) );
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  SecondaryIndepQuantity intermediate_grid_upper_bound =
    this->getUpperBoundOfSecondaryConditionalIndepVar( primary_indep_var_value );

  // Generate a sample in the subrange
  if( max_secondary_indep_var_value < intermediate_grid_upper_bound )
  {
    // Find the bin boundaries
    DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;
  
    this->findBinBoundaries( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

    DistributionDataConstIterator sampled_bin_boundary =
      this->sampleBinBoundary( primary_indep_var_value,
                               lower_bin_boundary,
                               upper_bin_boundary );

    // Calculate the limit on the sampled bin boundary
    typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
         Utility::get<1>( *sampled_bin_boundary )->getLowerBoundOfIndepVar(),
         Utility::get<1>( *sampled_bin_boundary )->getUpperBoundOfIndepVar() );

    SecondaryIndepQuantity intermediate_grid_lower_bound =
    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value );
                                                                         
    typename QuantityTraits<SecondaryIndepQuantity>::RawType
      intermediate_grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                                               intermediate_grid_lower_bound,
                                               intermediate_grid_upper_bound );
    
    typename QuantityTraits<SecondaryIndepQuantity>::RawType eta =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                                                 max_secondary_indep_var_value,
                                                 intermediate_grid_lower_bound,
                                                 intermediate_grid_length );
    
    SecondaryIndepQuantity max_secondary_indep_var_value_bin_bound =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
           eta,
           Utility::get<1>( *sampled_bin_boundary )->getLowerBoundOfIndepVar(),
           grid_length );

    // Sample in the bin's subrange
    SecondaryIndepQuantity raw_sample =
      Utility::get<1>(*sampled_bin_boundary)->sampleWithRandomNumberInSubrange(
                                     random_number,
                                     max_secondary_indep_var_value_bin_bound );

    // Scale the sample
    eta = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
           raw_sample,
           Utility::get<1>( *sampled_bin_boundary )->getLowerBoundOfIndepVar(),
           grid_length );

    return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                                                 eta,
                                                 intermediate_grid_lower_bound,
                                                 intermediate_grid_length );
  }
  // Generate a sample in the full range
  else
  {
    return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
  }
}

// Return a random sample from the secondary conditional PDF
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumber(
                                      primary_indep_var_value, random_number );
}

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  
  // Find the bin boundaries
  DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDInterpPolicy::calculateIntermediateGridLimit(
         Utility::get<0>( *lower_bin_boundary ),
         Utility::get<0>( *upper_bin_boundary ),
         primary_indep_var_value,
         Utility::get<1>( *lower_bin_boundary )->sampleWithRandomNumber( random_number ),
         Utility::get<1>( *upper_bin_boundary )->sampleWithRandomNumber( random_number ) );
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return Utility::get<1>( *lower_bin_boundary )->sampleWithRandomNumber(random_number);
    else
    {
      THROW_EXCEPTION( std::logic_error,
                       "Error: Sampling beyond the primary grid boundaries "
                       "cannot be done unless the grid has been extended ("
                       << primary_indep_var_value << " not in ["
                       << this->getLowerBoundOfPrimaryIndepVar() << ","
                       << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
    }
  }
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value ) );

  SecondaryIndepQuantity intermediate_grid_upper_bound =
    this->getUpperBoundOfSecondaryConditionalIndepVar( primary_indep_var_value );

  // Generate a sample in the subrange
  if( max_secondary_indep_var_value < intermediate_grid_upper_bound )
  {
    // Find the bin boundaries
    DistributionDataConstIterator lower_bin_boundary, upper_bin_boundary;
  
    this->findBinBoundaries( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

    if( lower_bin_boundary != upper_bin_boundary )
    {
      // Calculate the limits on the bin boundaries
      typename QuantityTraits<SecondaryIndepQuantity>::RawType L0 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
           Utility::get<1>( *lower_bin_boundary )->getLowerBoundOfIndepVar(),
           Utility::get<1>( *lower_bin_boundary )->getUpperBoundOfIndepVar() );

      typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
           Utility::get<1>( *upper_bin_boundary )->getLowerBoundOfIndepVar(),
           Utility::get<1>( *upper_bin_boundary )->getUpperBoundOfIndepVar() );

      SecondaryIndepQuantity intermediate_grid_lower_bound =
        this->getLowerBoundOfSecondaryConditionalIndepVar( primary_indep_var_value );

      typename QuantityTraits<SecondaryIndepQuantity>::RawType
        intermediate_grid_length =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                                               intermediate_grid_lower_bound,
                                               intermediate_grid_upper_bound );

      typename QuantityTraits<SecondaryIndepQuantity>::RawType eta =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                                                 max_secondary_indep_var_value,
                                                 intermediate_grid_lower_bound,
                                                 intermediate_grid_length );

      SecondaryIndepQuantity max_secondary_indep_var_value_0 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
             eta,
             Utility::get<1>( *lower_bin_boundary )->getLowerBoundOfIndepVar(),
             L0 );

      SecondaryIndepQuantity max_secondary_indep_var_value_1 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
             eta,
             Utility::get<1>( *upper_bin_boundary )->getLowerBoundOfIndepVar(),
             L1 );
      
      return TwoDInterpPolicy::calculateIntermediateGridLimit(
         Utility::get<0>( *lower_bin_boundary ),
         Utility::get<0>( *upper_bin_boundary ),
         primary_indep_var_value,
         Utility::get<1>( *lower_bin_boundary )->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value_0 ),
         Utility::get<1>( *upper_bin_boundary )->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value_1 ) );
    }
    else
    {
      if( this->arePrimaryLimitsExtended() )
        return Utility::get<1>( *lower_bin_boundary )->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value );
      else
      {
        THROW_EXCEPTION( std::logic_error,
                         "Error: Sampling beyond the primary grid boundaries "
                         "cannot be done unless the grid has been extended ("
                         << primary_indep_var_value << " not in ["
                         << this->getLowerBoundOfPrimaryIndepVar() << ","
                         << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
      }
    }
  }
  // Generate a sample in the full range
  else
  {
    return this->sampleSecondaryConditionalExactWithRandomNumber(
                                      primary_indep_var_value, random_number );
  }
}

// Method for placing the object in an output stream
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamTabularDistImpl( os,
                                 "InterpolatedFullyTabularBasicBivariateDistribution",
                                 std::make_pair( "interp", TwoDInterpPolicy::name() ) );
}

// Save the distribution to an archive
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLinLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLogLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLinLog,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLogLog,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLinLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLogLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLinLog,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLogLog,void,void,void> );

#endif // UTILITY_INTERPOLATED_FULLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularBasicBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
