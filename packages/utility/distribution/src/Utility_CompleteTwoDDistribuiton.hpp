//---------------------------------------------------------------------------//
//!
//! \file   Utility_CompleteTwoDDistribuiton.hpp
//! \author Alex Robinson
//! \brief  The complete two-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMPLETE_TWO_D_DISTRIBUITON_HPP
#define UTILITY_COMPLETE_TWO_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <utility>

// FRENSIE Includes
#include "Utility_TwoDDistribution.hpp"

namespace Utility{

/*! The unit-aware complete two-dimensional distribution
 * \ingroup two_d_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareCompleteTwoDDistribution : public UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

private:

  // The parent class type
  typedef UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ParentType;

public:

  //! The inverse primary independent quantity type
  typedef typename ParentType::InversePrimaryIndepUnitTraits::template GetQuantityType<double>::type InversePrimaryIndepQuantity;

  //! The inverse independent quantity type
  typedef typename ParentType::InverseIndepUnitTraits::template GetQuantityType<double>::type InverseIndepQuantity;

  //! Constructor
  UnitAwareCompleteTwoDDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareCompleteTwoDDistribution()
  { /* ... */ }

  //! Evaluate the joint PDF
  virtual InverseIndepQuantity evaluateJointPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Evaluate the primary marginal PDF
  virtual InversePrimaryIndepQuantity evaluatePrimaryMarginalPDF(
                const PrimaryIndepQuantity primary_indep_var_value ) const = 0;

  //! Evaluate the secondary marginal PDF
  virtual InverseSecondaryIndepQuantity evaluateSecondaryMarginalPDF(
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Evaluate the primary conditional PDF
  virtual InversePrimaryIndepQuantity evaluatePrimaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  virtual InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
               const PrimaryIndepQuantity primary_indep_var_value,
               const SecondaryIndepQuantity secondary_indep_var_value ) const

  //! Return a random sample from the distribution
  virtual std::pair<PrimaryIndepQuantity,SecondaryIndepQuantity>
  sample() const;

  //! Return a random sample and record the number of trials
  virtual std::pair<PrimaryIndepQuantity,SecondaryIndepQuantity>
  sampleAndRecordTrials( DistributionTraits::Counter& trials ) const;

  //! Return a random sample from the primary marginal PDF
  virtual PrimaryIndepQuantity samplePrimaryMarginal() const = 0;

  //! Return a random sample and record the number of trials
  virtual PrimaryIndepQuantity samplePrimaryMarginalAndRecordTrials(
                                                  DistributionTraits::Counter& trials ) const = 0;

  //! Return a random sample from the secondary marginal PDF
  virtual SecondaryIndepQuantity sampleSecondaryMarginal() const = 0;

  //! Return a random sample and record the number of trials
  virtual SecondaryIndepQuantity sampleSecondaryMarginalAndRecordTrials(
                                                  DistributionTraits::Counter& trials ) const = 0;

  //! Return a random sample from the primary conditional PDF
  virtual PrimaryIndepQuantity samplePrimaryConditional(
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  virtual PrimaryIndepQuantity samplePrimaryConditionalAndRecordTrials(
                         const SecondaryIndepQuantity seconary_indep_var_value,
                         DistributionTraits::Counter& trials ) const;

  //! Return the upper bound of the distribution secondary independent variable
  virtual SecondaryIndepQuantity getUpperBoundOfSecondaryIndepVar() const = 0;

  //! Return the lower bound of the distribution secondary independent variable
  virtual SecondaryIndepQuantity getLowerBoundOfSecondaryIndepVar() const = 0;

  //! Test if the distribution has the same bounds
  bool hasSameBounds( const UnitAwareFullyContinuousTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>& distribution ) const;
};

// Evaluate the primary conditional PDF
/*! \details p(x|y=b) = p(x,b)/p_y(b)
 */ 
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
InversePrimaryIndepQuantity UnitAwareCompleteTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluatePrimaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->evaluateJointPDF( primary_indep_var_value,
                                 secondary_indep_var_value )/
    this->evaluateSecondaryMarginalPDF( secondary_indep_var_value );
}

// Evaluate the secondary conditional PDF
/*! \details p(y|x=a) = p(a,y)/p_x(a)
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
InverseSecondaryIndepQuantity UnitAwareCompleteTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->evaluateJointPDF( primary_indep_var_value,
                                 secondary_indep_var_value )/
    this->evaluatePrimaryMarginalPDF( primary_indep_var_value );
}

// Return a random sample from the distribution
/*! \details p(x,y) = p_x(x)*p(y|x)
 */ 
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
std::pair<PrimaryIndepQuantity,SecondaryIndepQuantity>
UnitAwareCompleteTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sample() const
{
  PrimaryIndepQuantity primary_indep_sample = this->samplePrimaryMarginal();

  SecondaryIndepQuantity secondary_indep_sample =
    this->sampleSecondaryConditional( primary_indep_sample );

  return std::make_pair( primary_indep_sample, secondary_indep_sample );
}

// Return a random sample and record the number of trials
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
std::pair<PrimaryIndepQuantity,SecondaryIndepQuantity>
UnitAwareCompleteTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  PrimaryIndepQuantity primary_indep_sample =
    this->samplePrimaryMarginalAndRecordTrials( trials );

  SecondaryIndepQuantity secondary_indep_sample =
    this->sampleSecondaryConditionalAndRecordTrials( primary_indep_sample,
                                                     trials );

  return std::make_pair( primary_indep_sample, secondary_indep_sample );
}

// Test if the distribution has the same bounds
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline bool UnitAwareCompleteTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::hasSameBounds( const UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>& distribution ) const
{
  return this->hasSamePrimaryBounds( distribution ) &&
    Policy::relError(
            getRawQuantity( this->getUpperBoundOfSecondaryIndepVar() ),
            getRawQuantity( distribution.getUpperBoundOfSecondaryIndepVar() ) )
    < 1e-9 &&
    Policy::relError(
            getRawQuantity( this->getLowerBoundOfSecondaryIndepVar() ),
            getRawQuantity( distribution.getLowerBoundOfSecondaryIndepVar() ) )
    < 1e-9;
}

/*! The complete two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwareCompleteTwoDDistribution<void,void,void> CompleteTwoDDistribution;

} // end Utility namespace

#endif // end UTILITY_COMPLETE_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_CompleteTwoDDistribution.hpp
//---------------------------------------------------------------------------//
