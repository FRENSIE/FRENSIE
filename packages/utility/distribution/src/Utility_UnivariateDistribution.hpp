//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  Univariate distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_HPP
#define UTILITY_ONE_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <stdexcept>

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_UnivariateDistributionType.hpp"
#include "Utility_OStreamableObject.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_CosineInterpolationPolicy.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_DistributionSerializationHelpers.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

/*! \defgroup univariate_distributions Univariate Distributions
 */

namespace Utility{

/*! The unit-aware univariate distribution
 * \details When the IndependentUnit type and/or the DependentUnit type
 * resolves to void, the IndepQuantity and/or the DepQuantity type reduces to
 * double respectively.
 * \ingroup univariate_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareUnivariateDistribution : public OStreamableObject
{
  // Typedef for this type
  typedef UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit> ThisType;

protected:

  //! The independent unit traits typedef
  typedef UnitTraits<IndependentUnit> IndepUnitTraits;

  //! The inverse independent unit traits typedef
  typedef UnitTraits<typename UnitTraits<IndependentUnit>::InverseUnit> InverseIndepUnitTraits;

  //! The dependent unit traits typedef
  typedef UnitTraits<DependentUnit> DepUnitTraits;

  //! The distribution normalization unit traits typedef
  typedef UnitTraits<typename UnitTraits<typename UnitTraits<DependentUnit>::InverseUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::InverseUnit>::type> DistNormUnitTraits;

  //! The distribution normalization quantity type
  typedef typename DistNormUnitTraits::template GetQuantityType<double>::type DistNormQuantity;

public:

  //! The independent unit type
  typedef IndependentUnit IndepUnit;

  //! The dependent unit type
  typedef DependentUnit DepUnit;

  //! The independent quantity type
  typedef typename IndepUnitTraits::template GetQuantityType<double>::type IndepQuantity;

  //! The inverse independent quantity type
  typedef typename InverseIndepUnitTraits::template GetQuantityType<double>::type InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename DepUnitTraits::template GetQuantityType<double>::type DepQuantity;

  //! Constructor
  UnitAwareUnivariateDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareUnivariateDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual DepQuantity evaluate( const IndepQuantity indep_var_value ) const = 0;

  //! Evaluate the PDF
  virtual InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const = 0;

  //! Return a random sample from the distribution
  virtual IndepQuantity sample() const = 0;

  //! Return a random sample and record the number of trials
  virtual IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const = 0;

  //! Return the upper bound of the distribution independent variable
  virtual IndepQuantity getUpperBoundOfIndepVar() const = 0;

  //! Return the lower bound of the distribution independent variable
  virtual IndepQuantity getLowerBoundOfIndepVar() const = 0;

  //! Return the distribution type
  virtual UnivariateDistributionType getDistributionType() const = 0;

  //! Test if the distribution is tabular
  virtual bool isTabular() const;

  //! Test if the distribution is continuous
  virtual bool isContinuous() const = 0;

  //! Test if the distribution is compatible with the interpolation type
  template<typename InterpPolicy>
  bool isCompatibleWithInterpType() const;

  //! Test if the distribution has the same bounds
  bool hasSameBounds( const UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>& distribution ) const;

protected:

  //! Test if the dependent variable can be zero within the indep bounds
  virtual bool canDepVarBeZeroInIndepBounds() const = 0;

  //! Test if interpolation can ever be used
  virtual bool canInterpolationBeUsed() const;

  //! Test if the independent variable is compatible with Lin processing
  virtual bool isIndepVarCompatibleWithProcessingType(
                                        const LinIndepVarProcessingTag ) const;

  //! Test if the independent variable is compatible with Log processing
  virtual bool isIndepVarCompatibleWithProcessingType(
                                        const LogIndepVarProcessingTag ) const;

  //! Test if the independent variable is compatible with LogCos processing
  virtual bool isIndepVarCompatibleWithProcessingType(
                                     const NudgedLogCosIndepVarProcessingTag ) const;

  //! Test if the independent variable is compatible with LogCos processing
  virtual bool isIndepVarCompatibleWithProcessingType(
                                     const LogCosIndepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Lin processing
  virtual bool isDepVarCompatibleWithProcessingType(
                                          const LinDepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Log processing
  virtual bool isDepVarCompatibleWithProcessingType(
                                          const LogDepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with LogCos processing
  virtual bool isDepVarCompatibleWithProcessingType(
                                       const NudgedLogCosDepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with LogCos processing
  virtual bool isDepVarCompatibleWithProcessingType(
                                       const LogCosDepVarProcessingTag ) const;

  //! Add distribution data to the stream
  template<typename... Types>
  void toStreamDistImpl( std::ostream& os, const Types&... data ) const;

  //! Add distribution data (including the dist limits) to the stream
  template<typename... Types>
  void toStreamWithLimitsDistImpl( std::ostream& os, const Types&... data ) const;

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

/*! The univariate distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
typedef UnitAwareUnivariateDistribution<void,void> UnivariateDistribution;

/*! \brief Exception thrown by UnivariateDistribution objects when an invalid
 * parameter is encountered.
 * \ingroup univariate_distributions
 */
class BadUnivariateDistributionParameter : public std::logic_error
{
public:
  BadUnivariateDistributionParameter( const std::string& msg )
    : std::logic_error( msg )
  { /* ... */ }

  ~BadUnivariateDistributionParameter() throw()
  { /* ... */ }
};

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION2( UnitAwareUnivariateDistribution );
BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwareUnivariateDistribution, 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_UnivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_UnivariateDistribution.hpp
//---------------------------------------------------------------------------//

