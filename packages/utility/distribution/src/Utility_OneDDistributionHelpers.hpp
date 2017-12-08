//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionHelpers.hpp
//! \author Alex Robinson
//! \brief  One-dimensional distribution helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_HELPERS_HPP
#define UTILITY_ONE_D_DISTRIBUTION_HELPERS_HPP

// Boost Includes
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>

// FRENSIE Includes
#include "Utility_UnitTraits.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

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
typedef typename std::enable_if<std::is_same<typename Utility::UnitTraits<Unit>::Dimension,boost::units::Dim>::value || std::is_same<typename Utility::UnitTraits<Unit>::Dimension,void>::value>::type __unit_has_invalid_dimension_if_visible__

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
 * distribution header file, but only once per dimension. It is
 * safe to place it anywhere in the distribution class declaration.
 * \ingroup one_d_distributions
 */
#define RESTRICT_UNIT_FROM_BOOST_DIMENSION( Unit, Dim )\
typedef typename std::enable_if<!std::is_same<typename Utility::UnitTraits<Unit>::Dimension,boost::units::Dim>::value>,Unit>::type __unit_has_invalid_ ## Dim ## _if_visible__

/*! Declare an external explicit instantiation of a OneDDistribution class

 * This macro must be called in the global namespace
 * \ingroup one_d_distributions
 */
#define EXTERN_EXPLICIT_DISTRIBUTION_INST( ... ) \
namespace boost{                               \
namespace archive{                           \
  class text_oarchive;                       \
  class text_iarchive;                       \
  class xml_oarchive;                        \
  class xml_iarchive;                        \
  class binary_oarchive;                     \
  class binary_iarchive;                     \
}                                            \
}                                            \
                                             \
namespace Utility{                          \
  EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( \
                                      __VA_ARGS__\
                                       );        \
                                            \
  class HDF5OArchive;                       \
  class HDF5IArchive;                       \
                                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const \
                                          );                            \
                                                                        \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) \
                                          );                            \
}

/*! Declare an explicit instantiation of a OneDDistribution class

 * This macro must be called in the Utility namespace within a .cpp file.
 * Since the boost::archive::text_oarchive, boost::archive::text_iarchive,
 * boost::archive::xml_oarchive, boost::archive::xml_iarchive, 
 * boost::archive::binary_oarchive, boost::archive::binary_iarchive,
 * Utility::HDF5OArchive and the Utility::HDF5IArchive are only forward
 * declared in the extern EXPLICIT_DISTRIBUTION_INST macro, they must be
 * included in the .cpp file where this macro is called.
 * \ingroup one_d_distributions
 */
#define EXPLICIT_DISTRIBUTION_INST( ... ) \
  EXPLICIT_TEMPLATE_CLASS_INST(                                         \
                               __VA_ARGS__                              \
                                );                                      \
                                                                        \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const \
                                   );                                   \
                                                                        \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) \
                                   )

/*! Declare that a distribution class is an abstract base class
 *
 * This macro must be called from the global namespace. In order to serialize 
 * base distribution class pointers (e.g. 
 * std::shared_ptr<Utility::OneDDistribution>, 
 * std::unique_ptr<Utility::TabularOneDDistribution>, etc.) we need to register
 * them as abstract base classes with the boost::serialization extended
 * RTTI system. Calling this macro handles the registration.
 * \ingroup one_d_distributions
 */
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

#define __BOOST_DISTRIBUTION_CLASS_VERSION_IMPL__( _N, ... )    \
namespace boost{                                      \
namespace serialization{                            \
                                                    \
  __VA_ARGS__                                                           \
  {                                                                     \
    typedef mpl::int_<_N> type;                                         \
    typedef mpl::integral_c_tag tag;                                    \
    BOOST_STATIC_CONSTANT(int, value = version::type::value);           \
    BOOST_MPL_ASSERT((                                                  \
                      boost::mpl::less<                                 \
                      boost::mpl::int_<_N>,                             \
                      boost::mpl::int_<256> >                           \
                    ));                                                 \
  };                                                                    \
}                                                                       \
} 

/*! Declare the version of the distribution class
 *
 * The boost::serialization system allows for versioning of serializable
 * classes. As the classes change, the version number can be used to 
 * provide backwards compatibility with older archives.
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_VERSION( FullName, Version ) \
  __BOOST_DISTRIBUTION_CLASS_VERSION_IMPL__( Version,                   \
            template<typename IndependentUnit, typename DependentUnit> \
            struct version<Utility::FullName<IndependentUnit,DependentUnit> > )

/*! Declare the version of the distribution class
 *
 * Use this macro to declare the distribution class version number instead
 * of the BOOST_DISTRIBUTION_CLASS_VERSION macro when the distribution class
 * has an extra template parameter (e.g. Utility::TabularDistribution).
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_VERSION_EXTRA( FullName, ExtraType, ExtraName, Version ) \
  __BOOST_DISTRIBUTION_CLASS_VERSION_IMPL__( Version,                   \
            template<ExtraType __##ExtraName##__, typename IndependentUnit, typename DependentUnit> \
            struct version<Utility::FullName<__##ExtraName##__,IndependentUnit,DependentUnit> > )

#define __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__( ... ) \
namespace boost{                                              \
namespace serialization{                                              \
  __VA_ARGS__ : public boost::mpl::true_                                  \
  { /* ... */ };                                                        \
}                                                                       \
}

#define __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( GUID, ... )     \
namespace boost{                                              \
namespace serialization{                                    \
namespace ext{                                                        \
  __VA_ARGS__                                                           \
  {                                                                     \
    static inline const char* call()                                    \
    { return (GUID).c_str(); }                                          \
  };                                                                    \
}  \
}  \
}  
  
/*! Declare the GUID (key) of a distribution class
 *
 * The GUID or key must be declared for a concrete distribution class
 * when support for serializing instances of it through a base class pointer
 * is required. The GUID declared will be used by the 
 * boost::serialization extended RTTI system.
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( BaseName )                \
  __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__(                       \
     template<typename IndependentUnit, typename DependentUnit> \
     struct guid_defined<Utility::UnitAware##BaseName<IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string( "UnitAware"#BaseName"<" )+Utility::typeName<IndependentUnit>()+","+Utility::typeName<DependentUnit>()+">", \
                 template<typename IndependentUnit, typename DependentUnit> \
                 struct guid_impl<Utility::UnitAware##BaseName<IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string(#BaseName),       \
                 template<>                    \
                 struct guid_impl<Utility::UnitAware##BaseName<void,void> > )

/*! Declare the GUID (key) of a distribution class
 *
 * This macro should be used instead of the 
 * BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2 macro when a distribution class
 * has an extra template parameter (e.g. Utility::TabularDistribution).
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2_EXTRA( BaseName, ExtraType, ExtraName  ) \
  __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__(                       \
     template<ExtraType ExtraName, typename IndependentUnit, typename DependentUnit> \
     struct guid_defined<Utility::UnitAware##BaseName<ExtraName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string( "UnitAware"#BaseName"<" )+(Utility::typeName<ExtraName,IndependentUnit,DependentUnit>())+">", \
     template<ExtraType ExtraName, typename IndependentUnit, typename DependentUnit> \
     struct guid_impl<Utility::UnitAware##BaseName<ExtraName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string(#BaseName"<")+Utility::typeName<ExtraName>()+">", \
         template<ExtraType ExtraName>                    \
         struct guid_impl<Utility::UnitAware##BaseName<ExtraName,void,void> > )

/*! Declare the GUID (key) of a distribution class
 *
 * This macro should be used instead of the 
 * BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2 macro when a distribution class
 * has an extra integer template parameter (e.g. Utility::PowerDistribution).
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2_EXTRA_INT( BaseName, ExtraIntType, ExtraIntName  ) \
  __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__(                       \
     template<ExtraIntType ExtraIntName, typename IndependentUnit, typename DependentUnit> \
     struct guid_defined<Utility::UnitAware##BaseName<ExtraIntName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string( "UnitAware"#BaseName"<" )+Utility::toString(ExtraIntName)+","+(Utility::typeName<IndependentUnit,DependentUnit>())+">", \
     template<ExtraIntType ExtraIntName, typename IndependentUnit, typename DependentUnit> \
     struct guid_impl<Utility::UnitAware##BaseName<ExtraIntName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string(#BaseName"<")+Utility::toString(ExtraIntName)+">", \
         template<ExtraIntType ExtraIntName>                    \
         struct guid_impl<Utility::UnitAware##BaseName<ExtraIntName,void,void> > )


#define __BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_IMPL__( DistributionType, ... ) \
namespace boost{                                              \
namespace archive{                                          \
namespace detail{                                         \
namespace extra_detail{ \
  __VA_ARGS__                                                           \
  struct init_guid<DistributionType>                                    \
  {                                                                     \
    static const guid_initializer<DistributionType>& g;                 \
  };                                                                    \
                                                                        \
  __VA_ARGS__                                                           \
  const guid_initializer<DistributionType>& init_guid<DistributionType>::g = \
    ::boost::serialization::singleton<guid_initializer<DistributionType> >::get_mutable_instance().export_guid(); \
}                                                                       \
}                                                                       \
}                                                                       \
}

#define __ONE_D_DIST_FORWARD_AS_SINGLE_ARG__( ... ) __VA_ARGS__        \

/*! Register the distribution class GUID
 * 
 * This macro must be called after calling one of the
 * BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2 macros. The 
 * BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2 macros simply declare the GUID
 * associated with a distribution type while this macro actually registers
 * the GUID with the boost::serialization extended RTTI system.
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( FullName )   \
  __BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_IMPL__(               \
    __ONE_D_DIST_FORWARD_AS_SINGLE_ARG__(Utility::FullName<IndependentUnit,DependentUnit>),\
    template<typename IndependentUnit, typename DependentUnit> )

/*! Register the distribution class GUID
 *
 * This macro should be called instead of the 
 * BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT when the distribution class
 * has an extra template parameter.
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_EXTRA( FullName, ExtraType, ExtraName  ) \
  __BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_IMPL__(               \
    __ONE_D_DIST_FORWARD_AS_SINGLE_ARG__(Utility::FullName<ExtraName,IndependentUnit,DependentUnit>), \
    template<ExtraType ExtraName, typename IndependentUnit, typename DependentUnit> )

/*! Finalize the registration of the distribution class GUID
 *
 * This macro must be called from the constructors of the distribution class
 * to finalize the GUID registration process. Because the distribution
 * classes are templates the GUID registration singleton that is used
 * in the registration process won't get instantiated until the first
 * instance of the distribution has been created.
 * \ingroup one_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ... )  \
  const auto& __guid_initializer__ = boost::archive::detail::extra_detail::init_guid<__VA_ARGS__>::g

#endif // end UTILITY_ONE_D_DISTRIBUTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
