//---------------------------------------------------------------------------//
//!
//! \file   Utility_BivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The bivariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BIVARIATE_DISTRIBUTION_HPP
#define UTILITY_BIVARIATE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_BasicBivariateDistribution.hpp"

namespace Utility{

/*! The unit-aware bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareBivariateDistribution : public UnitAwareBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>
{

  // Typedef for this type
  typedef UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;

  // Typedef for base type
  typedef UnitAwareBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> BaseType;

protected:

  //! The primary independent unit traits typedef
  typedef typename BaseType::PrimaryIndepUnitTraits PrimaryIndepUnitTraits;

  //! The secondary independent unit traits typedef
  typedef typename BaseType::SecondaryIndepUnitTraits SecondaryIndepUnitTraits;

  //! The inverse primary independent unit traits typedef
  typedef typename BaseType::InversePrimaryIndepUnitTraits InversePrimaryIndepUnitTraits;

  //! The inverse secondary independent unit traits typedef
  typedef typename BaseType::InverseSecondaryIndepUnitTraits InverseSecondaryIndepUnitTraits;

  //! The inverse independent unit traits typedef
  typedef typename BaseType::InverseIndepUnitTraits InverseIndepUnitTraits;

  //! The dependent unit traits typedef
  typedef typename BaseType::DepUnitTraits DepUnitTraits;

public:

  //! The primary independent unit type
  typedef typename BaseType::PrimaryIndepUnit PrimaryIndepUnit;

  //! The secondary independent unit type
  typedef typename BaseType::SecondaryIndepUnit SecondaryIndepUnit;

  //! The dependent unit type
  typedef typename BaseType::DepUnit DepUnit;

  //! The primary independent quantity type
  typedef typename BaseType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The inverse primary independent quantity type
  typedef typename InversePrimaryIndepUnitTraits::template GetQuantityType<double>::type InversePrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename BaseType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename BaseType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The inverse independent quantity type
  typedef typename InverseIndepUnitTraits::template GetQuantityType<double>::type InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  UnitAwareBivariateDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareBivariateDistribution()
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
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

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
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Return a random sample and record the number of trials
  virtual PrimaryIndepQuantity samplePrimaryConditionalAndRecordTrials(
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        DistributionTraits::Counter& trials ) const = 0;

  //! Return the upper bound of the distribution secondary independent variable
  virtual SecondaryIndepQuantity getUpperBoundOfSecondaryIndepVar() const = 0;

  //! Return the lower bound of the distribution secondary independent variable
  virtual SecondaryIndepQuantity getLowerBoundOfSecondaryIndepVar() const = 0;

  //! Return the upper bound of the primary conditional distribution
  virtual PrimaryIndepQuantity getUpperBoundOfPrimaryConditionalIndepVar(
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Return the lower bound of the primary conditional distribution
  virtual PrimaryIndepQuantity getLowerBoundOfPrimaryConditionalIndepVar(
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Test if the distribution is tabular in the secondary dimension
  virtual bool isSecondaryDimensionTabular() const = 0;

  //! Test if the distribution is continuous in the secondary dimension
  virtual bool isSecondaryDimensionContinuous() const = 0;

  //! Test if the distribution has the same secondary bounds
  bool hasSameSecondaryBounds( const UnitAwareBivariateDistribution& distribution ) const;

private:

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION3( UnitAwareBivariateDistribution );
BOOST_SERIALIZATION_DISTRIBUTION3_VERSION( UnitAwareBivariateDistribution, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_BivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_BIVARIATE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_BivariateDistribution.hpp
//---------------------------------------------------------------------------//
