//---------------------------------------------------------------------------//
//!
//! \file   Utility_SeparableBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The separable bivariate distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

BOOST_SERIALIZATION_DISTRIBUTION4_EXPORT_IMPLEMENT( UnitAwareSeparableBivariateDistribution );

namespace Utility{

// Constructor
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::UnitAwareSeparableBivariateDistribution(
       const std::shared_ptr<const UnitAwareUnivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit> >& primary_distribution,
       const std::shared_ptr<const UnitAwareUnivariateDistribution<SecondaryIndependentUnit,SecondaryDependentUnit> >& secondary_distribution )
  : d_primary_distribution( primary_distribution ),
    d_secondary_distribution( secondary_distribution )
{
  TEST_FOR_EXCEPTION( primary_distribution.get() == NULL,
                      Utility::BadBivariateDistributionParameter,
                      "The separable distribution cannot be constructed "
                      "because the primary distribution is NULL!" );

  TEST_FOR_EXCEPTION( secondary_distribution.get() == NULL,
                      Utility::BadBivariateDistributionParameter,
                      "The separable distribution cannot be constructed "
                      "because the secondary distribution is NULL!" );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Evaluate the distribution
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
DepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return d_primary_distribution->evaluate( primary_indep_var_value )*
    d_secondary_distribution->evaluate( secondary_indep_var_value );
}

// Evaluate the joint PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
InverseIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluateJointPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return d_primary_distribution->evaluatePDF( primary_indep_var_value )*
    d_secondary_distribution->evaluatePDF( secondary_indep_var_value );
}

// Evaluate the primary marginal PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
InversePrimaryIndepQuantity evaluatePrimaryMarginalPDF(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
{
  return d_primary_distribution->evaluatePDF( primary_indep_var_value );
}

// Evaluate the secondary marginal PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
InverseSecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluateSecondaryMarginalPDF(
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return d_secondary_distribution->evaluatePDF( secondary_indep_var_value );
}

// Evaluate the primary conditional PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
InversePrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluatePrimaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity ) const
{
  return d_primary_distribution->evaluatePDF( primary_indep_var_value );
}

// Evaluate the secondary conditional PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
InverseSecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return d_secondary_distribution->evaluatePDF( secondary_indep_var_value );
}

// Return a random sample from the primary marginal PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryMarginal() const
{
  return d_primary_distribution->sample();
}

// Return a random sample and record the number of trials
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryMarginalAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  return d_primary_distribution->sampleAndRecordTrials( trials );
}

// Return a random sample from the secondary marginal PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryMarginal() const
{
  return d_secondary_distribution->sample();
}

// Return a random sample and record the number of trials
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryMarginalAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  return d_secondary_distribution->sampleAndRecordTrails( trials );
}

// Return a random sample from the primary conditional PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryConditional(
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  if( secondary_indep_var_value <
      d_secondary_distribution->getLowerBoundOfIndepVar() ||
      secondary_indep_var_value >
      d_secondary_distribution->getUpperBoundOfIndepVar() )
    return PIQT::zero();
  else
    return d_primary_distribution->sample();
}

// Return a random sample and record the number of trials
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryConditionalAndRecordTrials(
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        DistributionTraits::Counter& trials ) const
{
  if( secondary_indep_var_value <
      d_secondary_distribution->getLowerBoundOfIndepVar() ||
      secondary_indep_var_value >
      d_secondary_distribution->getUpperBoundOfIndepVar() )
  {
    ++trials;
    return PIQT::zero();
  }
  else
    d_primary_distribution->sampleAndRecordTrials( trials );
}

// Return a random sample from the secondary conditional PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
{
  if( primary_indep_var_value <
      d_primary_distribution->getLowerBoundOfIndepVar() ||
      primary_indep_var_value >
      d_primary_distribution->getUpperBoundOfIndepVar() )
    return SIQT::zero();
  else
    return d_secondary_distribution->sample();
}

// Return a random sample and record the number of trials
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            DistributionTraits::Counter& trials ) const
{
  if( primary_indep_var_value <
      d_primary_distribution->getLowerBoundOfIndepVar() ||
      primary_indep_var_value >
      d_primary_distribution->getUpperBoundOfIndepVar() )
  {
    ++trials;

    return SIQT::zero();
  }
  else
    return d_secondary_distribution->sampleAndRecordTrials( trials );
}

// Return the upper bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getUpperBoundOfPrimaryIndepVar() const
{
  return d_primary_distribution->getUpperBoundOfIndepVar();
}

// Return the lower bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getLowerBoundOfPrimaryIndepVar() const
{
  return d_primary_distribution->getLowerBoundOfIndepVar();
}

// Return the upper bound of the distribution secondary independent variable
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getUpperBoundOfSecondaryIndepVar() const
{
  return d_secondary_distribution->getUpperBoundOfIndepVar();
}

// Return the lower bound of the distribution secondary independent variable
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getLowerBoundOfSecondaryIndepVar() const
{
  return d_secondary_distribution->getLowerBoundOfIndepVar();
}

// Return the upper bound of the conditional distribution
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getUpperBoundOfSecondaryConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
{
  if( primary_indep_var_value <
      d_primary_distribution->getLowerBoundOfIndepVar() ||
      primary_indep_var_value >
      d_primary_distribution->getUpperBoundOfIndepVar() )
    return SIQT::zero();
  else
    return d_secondary_distribution->getUpperBoundOfIndepVar();
}

// Return the lower bound of the conditional distribution
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getLowerBoundOfSecondaryConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
{
  if( primary_indep_var_value <
      d_primary_distribution->getLowerBoundOfIndepVar() ||
      primary_indep_var_value >
      d_primary_distribution->getUpperBoundOfIndepVar() )
    return SIQT::zero();
  else
    return d_secondary_distribution->getLowerBoundOfIndepVar();
}

// Return the upper bound of the primary conditional distribution
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getUpperBoundOfPrimaryConditionalIndepVar(
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  if( secondary_indep_var_value <
      d_secondary_distribution->getLowerBoundOfIndepVar() ||
      secondary_indep_var_value >
      d_secondary_distribution->getUpperBoundOfIndepVar() )
    return PIQT::zero();
  else
    return d_primary_distribution->getUpperBoundOfIndepVar();
}

// Return the lower bound of the primary conditional distribution
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getLowerBoundOfPrimaryConditionalIndepVar(
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  if( secondary_indep_var_value <
      d_secondary_distribution->getLowerBoundOfIndepVar() ||
      secondary_indep_var_value >
      d_secondary_distribution->getUpperBoundOfIndepVar() )
    return PIQT::zero();
  else
    return d_primary_distribution->getLowerBoundOfIndepVar();
}

// Test if the distribution is tabular in the primary dimension
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
bool UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::isPrimaryDimensionTabular() const
{
  return d_primary_distribution.isTabular();
}

// Test if the distribution is continuous in the primary dimension
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
bool UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::isPrimaryDimensionContinuous() const
{
  return d_primary_distribution.isContinuous();
}

// Test if the distribution is tabular in the secondary dimension
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
bool UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::isSecondaryDimensionTabular() const
{
  return d_secondary_distribution.isTabular();
}

// Test if the distribution is continuous in the secondary dimension
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
bool UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::isSecondaryDimensionContinuous() const
{
  return d_primary_distribution.isContinuous();
}

// Save the distribution to an archive
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
template<typename Archive>
void UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_primary_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_secondary_distribution );
}

// Load the distribution from an archive
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
template<typename Archive>
void UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_primary_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_secondary_distribution );
}

// Method for placing the object in an output stream
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
void UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamDistImpl(
                    "Separable Bivariate Distribution",
                    std::make_pair( "primary", *d_primary_distribution ),
                    std::make_pair( "secondary", *d_secondary_distribution ) );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareSeparableBivariateDistribution<void,void,void,void> );

#endif // end UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SeparableBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
