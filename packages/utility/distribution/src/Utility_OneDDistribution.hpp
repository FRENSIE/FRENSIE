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

/*! \defgroup one_d_distributions One-Dimensional Distributions
 */

namespace Utility{

/*! The unit-aware one-dimensional distribution
 * \details When the IndependentUnit type and/or the DependentUnit type 
 * resolves to void, the IndepQuantity and/or the DepQuantity type reduces to 
 * double respectively.
 * \ingroup one_d_distributions
 */
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

/*! The one-dimensional distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareOneDDistribution<void,void> OneDDistribution;

//! The invalid distribution string name error
class InvalidDistributionStringName : public std::logic_error
{

public:

  InvalidDistributionStringName( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

/*! The invalid distribution string representation error
 * \ingroup one_d_distributions
 */
class InvalidDistributionStringRepresentation : public std::logic_error
{

public:
  
  InvalidDistributionStringRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg ) 
  { /* ... */ }
};

/*! Macro for defining the unitless copy constructor
 *
 * \details This is a convenience macro for defining the unitless copy
 * constructor, which is a bit messy to define properly (and safely!!!). This
 * constructor will be defined inline as it is a template function. Place it
 * in the same location of the header file as you would any other public
 * constructor. It will only compile if the members packDataInString and 
 * unpackDataFromString are defined for the distribution class of interest 
 * (see ParameterListCompatibleObject). The constructor defined relies on 
 * SFINAE and the Boost disable_if object to prevent a duplicate copy 
 * constructor when the distribution template parameters are both void 
 * (unitless distribution). It also ensures that units can only be added to 
 * completely unitless distributions and not removed (one-way construction)
 * so that we don't undermine the safety provided by keeping track of units
 * in the first place.
 * \ingroup one_d_distributions
 */
#define UNITLESS_COPY_CONSTRUCTOR( Distribution, DistIndepUnit, DistDepUnit ) \
template<typename InputIndepUnit, typename InputDepUnit> \
Distribution( const Distribution<InputIndepUnit,InputDepUnit>& unitless_dist_instance,	\
  typename boost::disable_if<boost::mpl::or_<boost::mpl::and_<typename boost::is_same<DistIndepUnit,void>::type,typename boost::is_same<DistDepUnit,void>::type>,boost::mpl::not_<typename boost::is_same<InputIndepUnit,void>::type>,boost::mpl::not_<typename boost::is_same<InputDepUnit,void>::type> > >::type* dummy = 0 ) \
{ this->unpackDataFromString( unitless_dist_instance.packDataInString() ); } \
void __need_semicolin__() const

/*! Macro for defining the default unitless copy constructor
 *
 * \details This macro is the same as the ENABLE_UNITLESS_COPY_CONSTRUCTOR
 * macro except that default template parameters are used.
 * \ingroup one_d_distributions
 */
#define UNITLESS_COPY_CONSTRUCTOR_DEFAULT( Distribution ) \
  UNITLESS_COPY_CONSTRUCTOR( Distribution, IndependentUnit, DependentUnit )

/*! Macro for restricting distribution units to a certain dimension
 *
 * \details Certain distributions only make sense when defined on a certain
 * dimension (e.g. energy). This macro will prevent improper use of a 
 * distribution by preventing the distribution template instance from
 * compiling when the template parameter has the incorrect dimension. Void
 * will also be allowed (needed for creating unit-agnostic distribution). If
 * the compiler shows "__unit_has_invalid_dimension_if_visible__" then you
 * know that an attempt to use a unit with a restricted dimension was made, 
 * which should help remedy the error faster (given that boost::units
 * template errors can be intimidating!). This macro can only be used
 * once - using it multiple times in the same header will prevent your 
 * distribution from working with any dimension! It is safe to place it
 * anywhere in the distribution class declaration.
 * \ingroup one_d_distributions
 */
#define RESTRICT_UNIT_TO_BOOST_DIMENSION( Unit, Dim )\
typedef typename boost::enable_if<boost::mpl::or_<typename boost::is_same<typename UnitTraits<Unit>::Dimension,boost::units::Dim>::type,typename boost::is_same<typename UnitTraits<Unit>::Dimension,void>::type> >::type __unit_has_invalid_dimension_if_visible__

/*! Macro for excluding a unit from a certain dimension
 *
 * \details Certain distributions do not make sense when defined on a 
 * certain dimension. This macro will prevent improper use of a distribution
 * by preventing the distribution template instance from compiling when
 * the template parameter has the incorrect dimension. If the compiler shows
 * "__unit_has_invalid_dimension_if_visible__" then you know that an attempt
 * to use a unit with a restricted dimension was made, which should help remedy
 * the error faster (given that boost::units template errors can be
 * intimidating!). This macro can be used as many times as desired in a
 * distribution header file, but only once per dimension (obviously). It is
 * safe to place it anywhere in the distribution class declaration.
 * \ingroup one_d_distributions
 */
#define RESTRICT_UNIT_FROM_BOOST_DIMENSION( Unit, Dim )\
typedef typename boost::disable_if<typename boost::is_same<typename UnitTraits<Unit>::Dimension,boost::units::Dim>::type>,Unit>::type __unit_has_invalid_ ## Dim ## _if_visible__

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution.hpp
//---------------------------------------------------------------------------//

