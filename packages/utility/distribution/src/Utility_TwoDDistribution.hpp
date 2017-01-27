//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The two-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_DISTRIBUTION_HPP
#define UTILITY_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_ComparePolicy.hpp"

/*! \defgroup two_d_distributions Two-Dimensinal Distributions
 */

namespace Utility{

/*! The unit-aware two-dimensional distribution
 * \ingroup two_d_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareTwoDDistribution
{

protected:

  //! The primary independent unit traits typedef
  typedef UnitTraits<PrimaryIndependentUnit> PrimaryIndepUnitTraits;

  //! The secondary independent unit traits typedef
  typedef UnitTraits<SecondaryIndependentUnit> SecondaryIndepUnitTraits;

  //! The inverse primary independent unit traits typedef
  typedef UnitTraits<typename UnitTraits<PrimaryIndependentUnit>::InverseUnit> InversePrimaryIndepUnitTraits;

  //! The inverse secondary independent unit traits typedef
  typedef UnitTraits<typename UnitTraits<SecondaryIndependentUnit>::InverseUnit> InverseSecondaryIndepUnitTraits;

  //! The inverse independent unit traits typedef
  typedef UnitTraits<typename UnitTraits<typename UnitTraits<PrimaryIndependentUnit>::InverseUnit>::template GetMultipliedUnitType<typename UnitTraits<SecondaryIndependentUnit>::InverseUnit>::type> InverseIndepUnitTraits;

  //! The dependent unit traits typedef
  typedef UnitTraits<DependentUnit> DepUnitTraits;

public:

  //! The primary independent unit type
  typedef PrimaryIndependentUnit PrimaryIndepUnit;

  //! The secondary independent unit type
  typedef SecondaryIndependentUnit SecondaryIndepUnit;

  //! The dependent unit type
  typedef DependentUnit DepUnit;

  //! The primary independent quantity type
  typedef typename PrimaryIndepUnitTraits::template GetQuantityType<double>::type PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename SecondaryIndepUnitTraits::template GetQuantityType<double>::type SecondaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename InverseSecondaryIndepUnitTraits::template GetQuantityType<double>::type InverseSecondaryIndepQuantity;

  //! The dependent quantity type
  typedef typename DepUnitTraits::template GetQuantityType<double>::type DepQuantity;

  //! Constructor
  UnitAwareTwoDDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareTwoDDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual DepQuantity evaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Evaluate the secondary conditional PDF
  virtual InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const = 0;

  //! Return a random sample from the secondary conditional PDF
  virtual SecondaryIndepQuantity sampleSecondaryConditional(
                const PrimaryIndepQuantity primary_indep_var_value ) const = 0;

  //! Return a random sample and record the number of trials
  virtual SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            DistributionTraits::Counter& trials ) const = 0;

  //! Return the upper bound of the distribution primary independent variable
  virtual PrimaryIndepQuantity getUpperBoundOfPrimaryIndepVar() const = 0;

  //! Return the lower bound of the distribution primary independent variable
  virtual PrimaryIndepQuantity getLowerBoundOfPrimaryIndepVar() const = 0;

  //! Return the upper bound of the conditional distribution
  virtual SecondaryIndepQuantity getUpperBoundOfConditionalIndepVar(
                const PrimaryIndepQuantity primary_indep_var_value ) const = 0;

  //! Return the lower bound of the conditional distribution
  virtual SecondaryIndepQuantity getLowerBoundOfConditionalIndepVar(
                const PrimaryIndepQuantity primary_indep_var_value ) const = 0;

  //! Test if the distribution is tabular in the primary dimension
  virtual bool isPrimaryDimensionTabular() const = 0;

  //! Test if the distribution is continuous in the primary dimension
  virtual bool isPrimaryDimensionContinuous() const = 0;

  //! Test if the distribution has the same primary bounds
  bool hasSamePrimaryBounds( const UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>& distribution ) const;
};

// Test if the distribution has the same primary bounds
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
inline bool UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::hasSamePrimaryBounds( const UnitAwareTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>& distribution ) const
{
  return
    Policy::relError(
              getRawQuantity( this->getUpperBoundOfPrimaryIndepVar() ),
              getRawQuantity( distribution.getUpperBoundOfPrimaryIndepVar() ) )
    < 1e-9 &&
    Policy::relError(
              getRawQuantity( this->getLowerBoundOfPrimaryIndepVar() ),
              getRawQuantity( distribution.getLowerBoundOfPrimaryIndepVar() ) )
    < 1e-9;
                                                                        
                                                                        
}

/*! The two-dimensional distribution (unit-agnostic)
 * \ingroup two_d_distributions
 */
typedef UnitAwareTwoDDistribution<void,void,void> TwoDDistribution;
  
} // end Utility namespace

#endif // end UTILITY_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDDistribution.hpp
//---------------------------------------------------------------------------//
