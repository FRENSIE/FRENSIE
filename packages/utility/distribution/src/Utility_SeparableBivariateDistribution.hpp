//---------------------------------------------------------------------------//
//!
//! \file   Utility_SeparableBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The separable bivariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_HPP
#define UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_BivariateDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! The unit-aware separable bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename PrimaryDependentUnit,
         typename SecondaryIndependentUnit,
         typename SecondaryDependentUnit>
class UnitAwareSeparableBivariateDistribution : public UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,typename UnitTraits<PrimaryDependentUnit>::template GetMultipliedUnitType<SecondaryDependentUnit>::type>
{
  // The base type
  typedef UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,typename UnitTraits<PrimaryDependentUnit>::template GetMultipliedUnitType<SecondaryDependentUnit>::type> BaseType;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::PrimaryIndepQuantity> PIQT;

  // Typedef for QuantityTraits<SecondaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::SecondaryIndepQuantity> SIQT;

  // Typedef for QuantityTraits<InversePrimaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::InversePrimaryIndepQuantity> IPIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseSecondaryIndepQuantity> ISIQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

public:

  //! This type
  typedef UnitAwareSeparableBivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit,SecondaryIndependentUnit,SecondaryDependentUnit> ThisType;

  //! The dependent unit type
  typedef typename BaseType::DepUnit DepUnit;

  //! The primary independent quantity type
  typedef typename BaseType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename BaseType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse primary independent quantity type
  typedef typename BaseType::InversePrimaryIndepQuantity InversePrimaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename BaseType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  UnitAwareSeparableBivariateDistribution(
       const std::shared_ptr<const UnitAwareUnivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit> >& primary_distribution,
       const std::shared_ptr<const UnitAwareUnivariateDistribution<SecondaryIndependentUnit,SecondaryDependentUnit> >& secondary_distribution );

  //! Destructor
  ~UnitAwareSeparableBivariateDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the joint PDF
  InverseIndepQuantity evaluateJointPDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the primary marginal PDF
  InversePrimaryIndepQuantity evaluatePrimaryMarginalPDF(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Evaluate the secondary marginal PDF
  InverseSecondaryIndepQuantity evaluateSecondaryMarginalPDF(
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the primary conditional PDF
  InversePrimaryIndepQuantity evaluatePrimaryConditionalPDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
       const PrimaryIndepQuantity primary_indep_var_value,
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return a random sample from the primary marginal PDF
  PrimaryIndepQuantity samplePrimaryMarginal() const override;

  //! Return a random sample and record the number of trials
  PrimaryIndepQuantity samplePrimaryMarginalAndRecordTrials(
                          DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the secondary marginal PDF
  SecondaryIndepQuantity sampleSecondaryMarginal() const override;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryMarginalAndRecordTrials(
                          DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the primary conditional PDF
  PrimaryIndepQuantity samplePrimaryConditional(
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return a random sample and record the number of trials
  PrimaryIndepQuantity samplePrimaryConditionalAndRecordTrials(
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                          const PrimaryIndepQuantity primary_indep_var_value,
                          DistributionTraits::Counter& trials ) const override;

  //! Return the upper bound of the distribution primary independent variable
  PrimaryIndepQuantity getUpperBoundOfPrimaryIndepVar() const override;

  //! Return the lower bound of the distribution primary independent variable
  PrimaryIndepQuantity getLowerBoundOfPrimaryIndepVar() const override;

  //! Return the upper bound of the distribution secondary independent variable
  SecondaryIndepQuantity getUpperBoundOfSecondaryIndepVar() const override;

  //! Return the lower bound of the distribution secondary independent variable
  SecondaryIndepQuantity getLowerBoundOfSecondaryIndepVar() const override;

  //! Return the upper bound of the primary conditional distribution
  PrimaryIndepQuantity getUpperBoundOfPrimaryConditionalIndepVar(
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return the lower bound of the primary conditional distribution
  PrimaryIndepQuantity getLowerBoundOfPrimaryConditionalIndepVar(
       const SecondaryIndepQuantity secondary_indep_var_value ) const override;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfSecondaryConditionalIndepVar(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfSecondaryConditionalIndepVar(
           const PrimaryIndepQuantity primary_indep_var_value ) const override;

  //! Test if the distribution is tabular in the primary dimension
  bool isPrimaryDimensionTabular() const override;

  //! Test if the distribution is continuous in the primary dimension
  bool isPrimaryDimensionContinuous() const override;

  //! Test if the distribution is tabular in the secondary dimension
  bool isSecondaryDimensionTabular() const override;

  //! Test if the distribution is continuous in the secondary dimension
  bool isSecondaryDimensionContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

private:

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The primary distribution
  std::shared_ptr<const UnitAwareUnivariateDistribution<PrimaryIndependentUnit,PrimaryDependentUnit> > d_primary_distribution;

  // The secondary distribution
  std::shared_ptr<const UnitAwareUnivariateDistribution<SecondaryIndependentUnit,SecondaryDependentUnit> > d_secondary_distribution;
};

/*! The separable bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareSeparableBivariateDistribution<void,void,void,void> SeparableBivariateDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION4_VERSION( UnitAwareSeparableBivariateDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION4_EXPORT_STANDARD_KEY( SeparableBivariateDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_SeparableBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // UTILITY_SEPARABLE_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_SeparableBivariateDistribution.hpp
//---------------------------------------------------------------------------//
