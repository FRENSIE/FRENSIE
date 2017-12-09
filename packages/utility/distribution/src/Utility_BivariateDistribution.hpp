//---------------------------------------------------------------------------//
//!
//! \file   Utility_BivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The bivariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_DISTRIBUTION_HPP
#define UTILITY_TWO_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <stdexcept>

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_OStreamableObject.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_BivariateDistributionHelpers.hpp"

/*! \defgroup bivariate_distributions Bivariate Distributions
 */

namespace Utility{

/*! The unit-aware bivariate distribution
 * \ingroup bivariate_distributions
 */
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareBivariateDistribution : public OStreamableObject
{

  // Typedef for this type
  typedef UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> ThisType;

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
  UnitAwareBivariateDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareBivariateDistribution()
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
  bool hasSamePrimaryBounds( const UnitAwareBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>& distribution ) const;

private:

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { /* ... */ }

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { /* ... */ }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

/*! The bivariate distribution (unit-agnostic)
 * \ingroup bivariate_distributions
 */
typedef UnitAwareBivariateDistribution<void,void,void> BivariateDistribution;

/*! \brief Exception thrown by BivariateDistribution objects when an invalid
 * parameter is encountered.
 * \ingroup bivariate_distributions
 */
class BadBivariateDistributionParameter : public std::logic_error
{
public:
  BadBivariateDistributionParameter( const std::string& msg )
    : std::logic_error( msg )
  { /* ... */ }

  ~BadBivariateDistributionParameter() throw()
  { /* ... */ }
};
  
} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION2( UnitAwareBivariateDistribution );
BOOST_DISTRIBUTION2_CLASS_VERSION( UnitAwareBivariateDistribution, 0 );

#endif // end UTILITY_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_BivariateDistribution.hpp
//---------------------------------------------------------------------------//
