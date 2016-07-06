//---------------------------------------------------------------------------//
//!
//! \file   Utility_SeparableTwoDDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The separable two-dimensional distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::UnitAwareSeparableTwoDDistribution(
       const std::shared_ptr<const UnitAwareOneDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit> >& primary_distribution,
       const std::shared_ptr<const UnitAwareOneDDistribution<SecondaryIndependentUnit,SecondaryDependentUnit> >& secondary_distribution )
  : d_primary_distribution( primary_distribution ),
    d_secondary_distribution( secondary_distribution )
{
  // Make sure the distributions are valid
  testPrecondition( primary_distribution.get() );
  testPrecondition( secondary_distribution.get() );
}

// Evaluate the distribution
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
DepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluate(
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
InverseIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluateJointPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return d_primary_distribution->evaluatePDF( primary_indep_var_value ),
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
InverseSecondaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::evaluateSecondaryMarginalPDF(
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return d_secondary_distribution->evaluatePDF( secondary_indep_var_value );
}

// Return a random sample from the primary marginal PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryMarginal() const
{
  return d_primary_distribution->sample();
}

// Return a random sample and record the number of trials
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryMarginalAndRecordTrials( unsigned& trials ) const
{
  return d_primary_distribution->sampleAndRecordTrials( trials );
}

// Return a random sample from the secondary marginal PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondarIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryMarginal() const
{
  return d_secondary_distribution->sample();
}

// Return a random sample and record the number of trials
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondarIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryMarginal( unsigned& trials ) const
{
  return d_secondary_distribution->sampleAndRecordTrails( trials );
}

// Return a random sample from the primary conditional PDF
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryConditional(
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
PrimaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::samplePrimaryConditionalAndRecordTrials(
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        unsigned& trials ) const
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
SecondaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryConditional(
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
SecondaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
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
PrimaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getUpperBoundOfPrimaryIndepVar() const
{
  return d_primary_distribution->getUpperBoundOfIndepVar();
}

// Return the lower bound of the distribution primary independent variable
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
PrimaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getLowerBoundOfPrimaryIndepVar() const
{
  return d_primary_distribution->getLowerBoundOfIndepVar();
}

// Return the upper bound of the distribution secondary independent variable
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getUpperBoundOfSecondaryIndepVar() const
{
  return d_secondary_distribution->getUpperBoundOfIndepVar();
}

// Return the lower bound of the distribution secondary independent variable
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getLowerBoundOfSecondaryIndepVar() const
{
  return d_secondary_distribution->getLowerBoundOfIndepVar();
}

// Return the upper bound of the conditional distribution
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
SecondaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getUpperBoundOfConditionalIndepVar(
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
SecondaryIndepQuantity UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::getLowerBoundOfConditionalIndepVar(
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

// Test if the distribution is tabular in the primary dimension
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
bool UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::isPrimaryDimensionTabular() const
{
  return d_primary_distribution.isTabular();
}

// Test if the distribution is condinuous in the primary dimension
bool UnitAwareSeparableTwoDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit>::isPrimaryDimensionContinuous() const
{
  return d_primary_distribution.isContinuous();
}
  
} // end Utility namespace

#endif // end UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SeparableTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
