//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution.hpp
//! \author Alex Robinson
//! \brief  One-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_HPP
#define UTILITY_ONE_D_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>
#include <stdexcept>
#include <iostream>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

// FRENSIE Includes
#include "Utility_OneDDistributionType.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

//! The unit-aware one-dimensional distribution
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareOneDDistribution
{

protected:

  //! The independent unit traits typedef
  typedef UnitTraits<IndependentUnit> IndepUnitTraits;

  //! The inverse independent unit traits typedef
  typedef UnitTraits<typename UnitTraits<IndependentUnit>::InverseUnit> InverseIndepUnitTraits;

  //! The dependent unit traits typedef
  typedef UnitTraits<DependentUnit> DepUnitTraits;

public:

  //! The independent quantity type
  typedef typename IndepUnitTraits::template GetQuantityType<double>::value IndepQuantity;

  //! The inverse independent quantity type
  typedef typename InverseIndepUnitTraits::template GetQuantityType<double>::value InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename DepUnitTraits::template GetQuantityType<double>::value DepQuantity;

  //! Constructor
  UnitAwareOneDDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareOneDDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual DepQuantity evaluate( const IndepQuantity indep_var_value ) const = 0;

  //! Evaluate the PDF
  virtual InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const = 0;

  //! Return a random sample from the distribution
  virtual IndepQuantity sample() const = 0;

  //! Return a random sample and record the number of trials
  virtual IndepQuantity sampleAndRecordTrials( unsigned& trials ) const = 0;

  //! Return the upper bound of the distribution independent variable
  virtual IndepQuantity getUpperBoundOfIndepVar() const = 0;

  //! Return the lower bound of the distribution independent variable
  virtual IndepQuantity getLowerBoundOfIndepVar() const = 0;

  //! Return the distribution type
  virtual OneDDistributionType getDistributionType() const = 0;

  //! Test if the distribution is tabular
  virtual bool isTabular() const;

  //! Test if the distribution is continuous
  virtual bool isContinuous() const = 0;

  //! Test if the distribution has the same bounds
  bool hasSameBounds( const UnitAwareOneDDistribution<IndependentUnit,DependentUnit>& distribution ) const;
};

// Test if the distribution is tabular
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isTabular() const
{
  return false;
}

// Test if the distribution has the same bounds
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::hasSameBounds( 
	const UnitAwareOneDDistribution<IndependentUnit,DependentUnit>& distribution ) const
{
  return
    Policy::relError( getRawQuantity( this->getUpperBoundOfIndepVar() ),
		      getRawQuantity( distribution.getUpperBoundOfIndepVar() ))
    < 1e-9 &&
    Policy::relError( getRawQuantity( this->getLowerBoundOfIndepVar() ),
		      getRawQuantity( distribution.getLowerBoundOfIndepVar() ))
    < 1e-9;
}

//! The one-dimensional distribution (unit-agnostic)
typedef UnitAwareOneDDistribution<void,void> OneDDistribution;

//! The invalid distribution string name error
class InvalidDistributionStringName : public std::logic_error
{

public:

  InvalidDistributionStringName( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

//! The invalid distribution string representation error
class InvalidDistributionStringRepresentation : public std::logic_error
{

public:
  
  InvalidDistributionStringRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg ) 
  { /* ... */ }
};

/*! Macro for defining the unitless copy constructor
 *
 * /details This is a convenience macro for defining the unitless copy
 * constructor, which is a bit messy to define properly (and safely!!!). This
 * constructor will be defined inline as it is a template function. It will
 * only compile if the members packDataInString and unpackDataFromString are 
 * defined for the distribution class of interest (see 
 * ParameterListCompatibleObject). The constructor defined relies on SFINAE and
 * the Boost disable_if object to prevent a duplicate copy constructor when the
 * distribution template parameters are both void (unitless distribution).
 */
#define ENABLE_UNITLESS_COPY_CONSTRUCTOR( Distribution, DistIndepUnit, DistDepUnit ) \
template<typename InputIndepUnit, typename InputDepUnit> \
Distribution( const Distribution<InputIndepUnit,InputDepUnit>& unitless_dist_instance,	\
  typename boost::disable_if<boost::mpl::or_<boost::mpl::and_<typename boost::is_same<DistIndepUnit,void>::type,typename boost::is_same<DistDepUnit,void>::type>,boost::mpl::not_<typename boost::is_same<InputIndepUnit,void>::type>,boost::mpl::not_<typename boost::is_same<InputDepUnit,void>::type> > >::type* dummy = 0 ) \
{ this->unpackDataFromString( unitless_dist_instance.packDataInString() ); } \
void __need_semicolin__() const

/*! Macro for defining the default unitless copy constructor
 *
 * \details This macro is the same as the ENABLE_UNITLESS_COPY_CONSTRUCTOR
 * macro except that default template parameters are used.
 */
#define ENABLE_UNITLESS_COPY_CONSTRUCTOR_DEFAULT( Distribution ) \
  ENABLE_UNITLESS_COPY_CONSTRUCTOR( Distribution, IndependentUnit, DependentUnit )

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution.hpp
//---------------------------------------------------------------------------//

