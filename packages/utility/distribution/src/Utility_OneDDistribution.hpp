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
#include <type_traits>

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/mpl/and.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>

// FRENSIE Includes
#include "Utility_OneDDistributionType.hpp"
#include "Utility_PropertyTreeCompatibleObject.hpp"
#include "Utility_StreamableObject.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ComparisonTraits.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

/*! \defgroup one_d_distributions One-Dimensional Distributions
 */

namespace Utility{

/*! The unit-aware one-dimensional distribution
 * \details When the IndependentUnit type and/or the DependentUnit type
 * resolves to void, the IndepQuantity and/or the DepQuantity type reduces to
 * double respectively.
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareOneDDistribution : public PropertyTreeCompatibleObject,
                                  public StreamableObject
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
  virtual IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const = 0;

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

  //! Test if the distribution is compatible with the interpolation type
  template<typename InterpPolicy>
  bool isCompatibleWithInterpType() const;

  //! Test if the distribution has the same bounds
  bool hasSameBounds( const UnitAwareOneDDistribution<IndependentUnit,DependentUnit>& distribution ) const;

  //! Check if data is inlined by default when converting to a property tree
  bool isDataInlinedByDefault() const override;

  //! Method for initializing the object from an input stream
  using IStreamableObject::fromStream;
  
  //! Method for placing an object in the desired property tree node
  using PropertyTreeCompatibleObject::toPropertyTree;

  //! Method for initializing the object from a property tree
  using PropertyTreeCompatibleObject::fromPropertyTree;

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

  //! Test if the dependent variable is compatible with Lin processing
  virtual bool isDepVarCompatibleWithProcessingType(
                                          const LinDepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Log processing
  virtual bool isDepVarCompatibleWithProcessingType(
                                          const LogDepVarProcessingTag ) const;

private:

  // Archive the distribution
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Test if the distribution is tabular
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isTabular() const
{
  return false;
}

// Test if the distribution is compatible with the interpolation type
/*! \details Some higher-level classes use the output of the OneDDistribution
 * methods to do interpolations. This method can be used to check that the
 * requested interpolation policy can be safetly used with the distribution's
 * output.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InterpPolicy>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isCompatibleWithInterpType() const
{
  // Check if interpolation can be used
  if( this->canInterpolationBeUsed() )
  {
    return
      this->isIndepVarCompatibleWithProcessingType(
                               typename InterpPolicy::IndepVarProcessingTag() )
         &&
      this->isDepVarCompatibleWithProcessingType(
                               typename InterpPolicy::DepVarProcessingTag() );
  }
  else
    return false;
}

// Test if interpolation can ever be used
/*! \details This can be used as an override if intepolation should never
 * be used with a particular distribution (e.g. Utility::DeltaDistribution).
 * In general, only continuous distributions should be used with an
 * interpolation scheme.
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::canInterpolationBeUsed() const
{
  if( this->isContinuous() )
    return true;
  else
    return false;
}

// Test if the independent variable is compatible with Lin processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return true;
}
  
// Test if the independent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return LogLog::isIndepVarInValidRange( this->getLowerBoundOfIndepVar() ) &&
    LogLog::isIndepVarInValidRange( this->getUpperBoundOfIndepVar() );
}

// Test if the dependent variable is compatible with Lin processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return true;
}

// Test if the dependent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return !this->canDepVarBeZeroInIndepBounds();
}

// Test if the distribution has the same bounds
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::hasSameBounds(
	const UnitAwareOneDDistribution<IndependentUnit,DependentUnit>& distribution ) const
{
  return
    (RelativeErrorComparisonPolicy::compare( this->getUpperBoundOfIndepVar(),
                                             distribution.getUpperBoundOfIndepVar(),
                                             1e-9 ) ||
     CloseComparisonPolicy::compare( this->getUpperBoundOfIndepVar(),
                                     distribution.getUpperBoundOfIndepVar(),
                                     1e-9 )) &&
    (RelativeErrorComparisonPolicy::compare( this->getLowerBoundOfIndepVar(),
                                             distribution.getLowerBoundOfIndepVar(),
                                             1e-9 ) ||
     CloseComparisonPolicy::compare( this->getLowerBoundOfIndepVar(),
                                     distribution.getLowerBoundOfIndepVar(),
                                     1e-9 ));
}

// Check if data is inlined by default when converting to a property tree
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDataInlinedByDefault() const
{
  return false;
}

/*! The one-dimensional distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareOneDDistribution<void,void> OneDDistribution;

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareOneDDistribution<void,void> );

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

namespace boost{

namespace property_tree{

/*! \brief Partial specialization of boost::property_tree::translator_between
 * for Utility::OneDDistribution
 *
 * This translator only allows put operators. Get operations must be done
 * through a complete distribution type.
 * \ingroup ptree
 */
template<typename IndependentUnit, typename DependentUnit>
struct translator_between<Utility::Variant,Utility::UnitAwareOneDDistribution<IndependentUnit,DependentUnit> >
{
  //! The translator
  struct translator
  {
    typedef Utility::Variant internal_type;
    typedef void external_type;

    //! Convert a distribution to a Utility::Variant
    static inline boost::optional<internal_type> put_value( const Utility::UnitAwareOneDDistribution<IndependentUnit,DependentUnit>& obj )
    { return Utility::Variant( obj ); }
  };

  //! The translator type
  typedef translator type;
};
  
} // end property_tree namespace

} // end boost namespace

#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION( FullName ) \
namespace boost{                                                      \
namespace serialization{                                            \
                                                                        \
  template<typename IndependentUnit, typename DependentUnit>            \
  struct is_abstract<Utility::FullName<IndependentUnit,DependentUnit> > : boost::true_type \
  { /* ... */ };                                                        \
                                                                        \
  template<typename IndependentUnit, typename DependentUnit>            \
  struct is_abstract<const Utility::FullName<IndependentUnit,DependentUnit> > : boost::true_type \
  { /* ... */ };                                                        \
}                                                                       \
}

#define BOOST_DISTRIBUTION_CLASS_VERSION( FullName, N ) \
namespace boost{                                      \
namespace serialization{                            \
                                                    \
  template<typename IndependentUnit, typename DependentUnit>            \
  struct version<Utility::FullName<IndependentUnit,DependentUnit> >     \
  {                                                                     \
    typedef mpl::int_<N> type;                                          \
    typedef mpl::integral_c_tag tag;                                    \
    BOOST_STATIC_CONSTANT(int, value = version::type::value);           \
    BOOST_MPL_ASSERT((                                                  \
        boost::mpl::less<                                              \
            boost::mpl::int_<N>,                                       \
            boost::mpl::int_<256>                                      \
        >                                                              \
    ));    \
  };       \
}          \
}

#define BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( BaseName )  \
namespace boost{                                              \
namespace serialization{                                    \
                                                            \
  template<typename IndependentUnit, typename DependentUnit> \
  struct guid_defined<Utility::UnitAware##BaseName<IndependentUnit,DependentUnit> > : boost::mpl::true_ \
  { /* ... */ };                                                        \
                                                                        \
namespace ext{                                                        \
                                                                        \
  template<typename IndependentUnit, typename DependentUnit>            \
  struct guid_impl<Utility::UnitAware##BaseName<IndependentUnit,DependentUnit> > \
  {                                                                     \
    static inline const char* call()                                    \
    {                                                                   \
      std::string guid( "UnitAware"#BaseName"<" );                        \
      guid += Utility::typeName<IndependentUnit,DependentUnit>();       \
      guid += ">";                                                     \
                                                                       \
      return guid.c_str();                                              \
    }                                                                   \
  };                                                                    \
}                                                                       \
                                                                        \
  template<>                                                            \
  inline const char* guid<Utility::UnitAware##BaseName<void,void> >()   \
  { return #BaseName; }                                                 \
} \
}

#define BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( FullName )   \
namespace boost{                                              \
namespace archive{                                          \
namespace detail{                                         \
namespace extra_detail{ \
                        \
  template<typename IndependentUnit, typename DependentUnit>            \
  struct init_guid<Utility::FullName<IndependentUnit,DependentUnit> >   \
  {                                                                     \
    static const guid_initializer<Utility::FullName<IndependentUnit,DependentUnit> >& g; \
  };                                                                    \
                                                                        \
  template<typename IndependentUnit, typename DependentUnit>            \
  const guid_initializer<Utility::FullName<IndependentUnit,DependentUnit> >& init_guid<Utility::FullName<IndependentUnit,DependentUnit> >::g =\
    ::boost::serialization::singleton<guid_initializer<Utility::FullName<IndependentUnit,DependentUnit> > >::get_mutable_instance().export_guid(); \
}                                                                       \
}                                                                       \
}                                                                       \
}

//! Call this macro from the constructor
#define BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ... )  \
  const auto& __guid_initializer__ = boost::archive::detail::extra_detail::init_guid<__VA_ARGS__>::g
  
BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION( UnitAwareOneDDistribution );
BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwareOneDDistribution, 0 );

#endif // end UTILITY_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution.hpp
//---------------------------------------------------------------------------//

