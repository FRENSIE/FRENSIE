//---------------------------------------------------------------------------//
//!
//! \file   Utility_SeparableTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The separable two-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_HPP
#define UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_TwoDDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! The unit-aware separable two-dimensional distribution
 * \ingroup two_d_distributions
 */
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
class UnitAwareSeparableTwoDDistribution : public UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,typename UnitTraits<PrimaryDependentUnit>::template GetMultipliedUnitType<SecondaryDependentUnit>::type>
{
  
private:

  // The parent type
  typedef UnitAwareCompleteTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,typename UnitTraits<PrimaryDependentUnit>::template GetMultipliedUnitType<SecondaryDependentUnit>::type> ParentType;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::PrimaryIndepQuantity> PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::SecondaryIndepQuantity> SIQT;

  // Typedef for QuantityTraits<InversePrimaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::InversePrimaryIndepQuantity> IPIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef QuantityTraits<typename ParentType::InverseSecondaryIndepQuantity> ISIQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename ParentType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename ParentType::DepQuantity> DQT;

public:

  //! The dependent unit type
  typedef typename ParentType::DepUnit DepUnit;

  //! The primary independent quantity type
  typedef typename ParentType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename ParentType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse primary independent quantity type
  typedef typename ParentType::InversePrimaryIndepQuantity InversePrimaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename ParentType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity

  //! The inverse independent quantity type
  typedef typename ParentType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename ParentType::DepQuantity DepQuantity;

  //! Constructor
  UnitAwareSeparableTwoDDistribution(
       const std::shared_ptr<const UnitAwareOneDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit> >& primary_distribution,
       const std::shared_ptr<const UnitAwareOneDDistribution<SecondaryIndependentUnit,SecondaryDependentUnit> >& secondary_distribution );

  //! Destructor
  ~UnitAwareTwoDDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the joint PDF
  InverseIndepQuantity evaluateJointPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the primary marginal PDF
  InversePrimaryIndepQuantity evaluatePrimaryMarginalPDF(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Evaluate the secondary marginal PDF
  InverseSecondaryIndepQuantity evaluateSecondaryMarginalPDF(
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the primary marginal PDF
  PrimaryIndepQuantity samplePrimaryMarginal() const;

  //! Return a random sample and record the number of trials
  PrimaryIndepQuantity samplePrimaryMarginalAndRecordTrials(
                                                      unsigned& trials ) const;

  //! Return a random sample from the secondary marginal PDF
  SecondarIndepQuantity sampleSecondaryMarginal() const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryMarginalAndRecordTrials(
                                                      unsigned& trials ) const;

  //! Return a random sample from the primary conditional PDF
  PrimaryIndepQuantity samplePrimaryConditional(
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  PrimaryIndepQuantity samplePrimaryConditionalAndRecordTrials(
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        unsigned& trials ) const;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const;

  //! Return the upper bound of the distribution primary independent variable
  PrimaryIndepQuantity getUpperBoundOfPrimaryIndepVar() const;

  //! Return the lower bound of the distribution primary independent variable
  PrimaryIndepQuantity getLowerBoundOfPrimaryIndepVar() const;

  //! Return the upper bound of the distribution secondary independent variable
  SecondaryIndepQuantity getUpperBoundOfSecondaryIndepVar() const;

  //! Return the lower bound of the distribution secondary independent variable
  SecondaryIndepQuantity getLowerBoundOfSecondaryIndepVar() const;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Test if the distribution is tabular in the primary dimension
  bool isPrimaryDimensionTabular() const;

  //! Test if the distribution is condinuous in the primary dimension
  bool isPrimaryDimensionContinuous() const;

private:

  // The primary distribution
  std::shared_ptr<const UnitAwareOneDDistribution<PrimaryIndependentUnit,PrimaryDependentUnit> > d_primary_distribution;

  // The secondary distribution
  std::shared_ptr<const UnitAwareOneDDistribution<SecondaryIndependentUnit,SecondaryDependentUnit> > d_secondary_distribution;
};

/*! The separable two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwareSeparableTwoDDistribution<void,void,void,void> SeparableTwoDDistribution;
  
} // end Utility namespace

#endif // UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_SeparableTwoDDistribution.hpp
//---------------------------------------------------------------------------//
