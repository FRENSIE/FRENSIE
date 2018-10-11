//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerializationHelpers.hpp
//! \author Alex Robinson
//! \brief  Serialization helper macro definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SERIALIZATION_HELPERS_HPP
#define UTILITY_SERIALIZATION_HELPERS_HPP

// Boost Includes
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>

/*! \defgroup boost_serialization_helpers Boost Serialization Helpers
 */

namespace Utility{
namespace Details{

/*!  \brief Indirection layer for assigning a std::string guid instead of a
 * const char*
 * \ingroup boost_serialization_helpers
 */
template<typename T>
struct GuidStringWrapper
{ /* ... */ };

} // end Detail namespace
} // end Utility namespace

/*! Note that swig doesn't like the extern template declaration
 * so these macros will be turned off when SWIG is processing files.
 */
#if !defined SWIG

/*! Forward a complicated argument to another macro as a single argument
 * \ingroup boost_serialization_helpers
 */
#define __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( ... ) __VA_ARGS__

/*! Declare the version of a template class
 *
 * The boost::serialization package allows for versioning of serializable
 * classes. As the classes change, the version number can be used to provide
 * backwards compatibility with older archives.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL( ClassName, Namespace, Version, TemplateParamPackDecl, TemplateParamPack ) \
namespace boost{                                      \
namespace serialization{                            \
                                                    \
  template<TemplateParamPackDecl>                                       \
  struct version<Namespace::ClassName<TemplateParamPack> >              \
  {                                                                     \
    typedef mpl::int_<Version> type;                                         \
    typedef mpl::integral_c_tag tag;                                    \
    BOOST_STATIC_CONSTANT(int, value = version::type::value);           \
    BOOST_MPL_ASSERT((                                                  \
                      boost::mpl::less<                                 \
                      boost::mpl::int_<Version>,                             \
                      boost::mpl::int_<256> >                           \
                    ));                                                 \
  };                                                                    \
}                                                                       \
}

/*! Declare the version of a class with no template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS_VERSION( ClassName, Namespace, Version ) \
  BOOST_CLASS_VERSION( Namespace::ClassName, Version )

/*! Declare the version of a class with a single template parameter
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS1_VERSION( ClassName, Namespace, Version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    ClassName, Namespace, Version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T ),        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T ) )

/*! Declare the version of a class with two template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS2_VERSION( ClassName, Namespace, Version ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    ClassName, Namespace, Version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U ) )

/*! Declare the version of a class with three template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS3_VERSION( ClassName, Namespace, Version )      \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    ClassName, Namespace, Version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V ) )

/*! Declare the version of a class with four template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS4_VERSION( ClassName, Namespace, Version )      \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    ClassName, Namespace, Version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, typename W ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W ) )

/*! Declare the version of a class with five template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS5_VERSION( ClassName, Namespace, Version )      \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    ClassName, Namespace, Version, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, typename W, typename X ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W, X ) )

/*! Declare that a template class is abstract
 *
 * In order to serialize base class pointers we need to register the base class
 * as an abstract base class with the boost::serialization extended RTTI
 * system. Calling this macro handles the registration.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_TEMPLATE_CLASS_IMPL( ClassName, Namespace, TemplateParamPackDecl, TemplateParamPack ) \
namespace boost{                                                      \
namespace serialization{                                              \
                                                                      \
  template<TemplateParamPackDecl>                                     \
  struct is_abstract<Namespace::ClassName<TemplateParamPack> > : boost::true_type \
  { /* ... */ };                                                       \
                                                                       \
  template<TemplateParamPackDecl>                                      \
  struct is_abstract<const Namespace::ClassName<TemplateParamPack> > : boost::true_type \
  { /* ... */ };                                                       \
}                                                                      \
}

/*! Declare that a class with no template parameters is abstract
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ClassName, Namespace ) \
  BOOST_SERIALIZATION_ASSUME_ABSTRACT( Namespace::ClassName )

/*! Declare that a class with a single template parameter is abstract
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( ClassName, Namespace ) \
  BOOST_SERIALIZATION_ASSUME_ABSTRACT_TEMPLATE_CLASS_IMPL(           \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T ),        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T ) )

/*! Declare that a class with two template parameters is abstract
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS2( ClassName, Namespace ) \
  BOOST_SERIALIZATION_ASSUME_ABSTRACT_TEMPLATE_CLASS_IMPL(              \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U ) )

/*! Declare that a class with three template parameters is abstract
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS3( ClassName, Namespace ) \
  BOOST_SERIALIZATION_ASSUME_ABSTRACT_TEMPLATE_CLASS_IMPL(              \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V ) )

/*! Declare that a class with four template parameters is abstract
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS4( ClassName, Namespace ) \
  BOOST_SERIALIZATION_ASSUME_ABSTRACT_TEMPLATE_CLASS_IMPL(              \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, typename W ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W ) )

/*! Delcare that the GUID of a template class is defined
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_DECL_GUID_DEFINED_IMPL( ClassName, Namespace, TemplateParamPackDecl, TemplateParamPack ) \
namespace boost{                                              \
namespace serialization{                                              \
  template<TemplateParamPackDecl>                                       \
  struct guid_defined<Namespace::ClassName<TemplateParamPack> > : public boost::mpl::true_ \
  { /* ... */ };                                                        \
}                                                                       \
}

/*! Define the template class GUID registration method
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_GUID_IMPL( ClassName, Namespace, GUID, TemplateParamPackDecl, TemplateParamPack ) \
namespace Utility{                                                      \
namespace Details{                                                      \
  template<TemplateParamPackDecl>                                       \
  struct GuidStringWrapper<Namespace::ClassName<TemplateParamPack> >    \
  {                                                                     \
    bool isGuidAssigned() const                                         \
    { return !d_guid.empty(); }                                         \
                                                                        \
    void assignGuid( const std::string& guid )                          \
    { d_guid = guid; }                                                  \
                                                                        \
    const char* getGuid() const                                         \
    { return d_guid.c_str(); }                                          \
                                                                        \
  private:                                                              \
    std::string d_guid;                                                 \
  };                                                                    \
}                                                                       \
}                                                                       \
namespace boost{                                                        \
namespace serialization{                                                \
namespace ext{                                                          \
  template<TemplateParamPackDecl>                                       \
  struct guid_impl<Namespace::ClassName<TemplateParamPack> >            \
  {                                                                     \
    typedef boost::serialization::singleton<Utility::Details::GuidStringWrapper<Namespace::ClassName<TemplateParamPack> > > WrappedGuid; \
                                                                        \
    static inline const char* call()                                    \
    {                                                                   \
      if( !WrappedGuid::get_const_instance().isGuidAssigned() )         \
      {                                                                 \
        WrappedGuid::get_mutable_instance().assignGuid( GUID );         \
      }                                                                 \
                                                                        \
      return WrappedGuid::get_const_instance().getGuid();               \
    }                                                                   \
  };                                                                    \
}                                                                       \
}                                                                       \
}

/*! Define the template class GUID registration method
 *
 * A standard GUID will be generated using the ClassName and the
 * Utility::typeName method for the template parameters.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_STANDARD_GUID_IMPL( ClassName, Namespace, TemplateParamPackDecl, TemplateParamPack ) \
   BOOST_SERIALIZATION_TEMPLATE_CLASS_GUID_IMPL(                       \
    ClassName, Namespace,                         \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( #ClassName"<" ) + Utility::typeName<TemplateParamPack>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPackDecl ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPack ) )

/*! Declare the GUID (key) of a template class
 *
 * This macro must be called from the global namespace. The GUID or key must be
 * declared for a concrete class type when support for serializing instances of
 * it through a base class pointer is required. The GUID declared will be used
 * by the boost::serialization extended RTTI system.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL( ClassName, Namespace, GUID, TemplateParamPackDecl, TemplateParamPack ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_DECL_GUID_DEFINED_IMPL(          \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPackDecl ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPack ) ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_GUID_IMPL(                      \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( GUID ),              \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPackDecl ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPack ) )

/*! Declare the GUID (key) of a template class
 *
 * This macro must be called from the global namespace. The GUID will be
 * generated from the class name and the template parameters. The GUID or key
 * must be declared for a concrete class type when support for serializing
 * instances of it through a base class pointer is required. The GUID declared
 * will be used by the boost::serialization extended RTTI system.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_STANDARD_KEY_IMPL( ClassName, Namespace, TemplateParamPackDecl, TemplateParamPack ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_DECL_GUID_DEFINED_IMPL(          \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPackDecl ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPack ) ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_STANDARD_GUID_IMPL(             \
    ClassName, Namespace, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPackDecl ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( TemplateParamPack ) )

/*! Declare the GUID (key) of a class with no template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ClassName, Namespace ) \
  BOOST_CLASS_EXPORT_KEY2( Namespace::ClassName, #ClassName )

/*! Declare the GUID (key) of a class with a single template parameter
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS1_EXPORT_STANDARD_KEY( ClassName, Namespace )  \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_STANDARD_KEY_IMPL( \
    ClassName, Namespace,                                        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T ) )

/*! Declare the GUID (key) of a class with two template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS2_EXPORT_STANDARD_KEY( ClassName, Namespace )   \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_STANDARD_KEY_IMPL( \
    ClassName, Namespace,                                        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U ) )

/*! Declare the GUID (key) of a class with three template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS3_EXPORT_STANDARD_KEY( ClassName, Namespace )   \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_STANDARD_KEY_IMPL( \
    ClassName, Namespace,                                        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V ) )

/*! Declare the GUID (key) of a class with four template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS4_EXPORT_STANDARD_KEY( ClassName, Namespace )   \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_STANDARD_KEY_IMPL( \
    ClassName, Namespace,                                        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, typename W ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W ) )

/*! Declare the GUID (key) of a class with five template parameters
 *
 * This macro must be called from the global namespace.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS5_EXPORT_STANDARD_KEY( ClassName, Namespace )   \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_STANDARD_KEY_IMPL( \
    ClassName, Namespace,                                        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, typename W, typename X ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W, X ) )

/*! Register the class GUID
 *
 * The BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY macros simply declare the GUID
 * associated with a class type while this macro actually registers the GUID
 * with the boost::serialization extended RTTI system.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL( ClassName, Namespace, TemplateParamPackDecl, TemplateParamPack ) \
namespace boost{                                              \
namespace archive{                                          \
namespace detail{                                         \
namespace extra_detail{ \
  template<TemplateParamPackDecl>                                \
  struct init_guid<Namespace::ClassName<TemplateParamPack> >            \
  {                                                                     \
    static const guid_initializer<Namespace::ClassName<TemplateParamPack> >& g; \
  };                                                                    \
                                                                        \
  template<TemplateParamPackDecl>                                       \
  const guid_initializer<Namespace::ClassName<TemplateParamPack> >& init_guid<Namespace::ClassName<TemplateParamPack> >::g = \
  ::boost::serialization::singleton<guid_initializer<Namespace::ClassName<TemplateParamPack> > >::get_mutable_instance().export_guid(); \
}                                                                       \
}                                                                       \
}                                                                       \
}

/*! Register the GUID of a class with no template parameters
 *
 * This macro must be called after calling the
 * BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY macro. It is recommended
 * that the call be made in the .cpp file associated with the class definition.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ClassName, Namespace ) \
  BOOST_CLASS_EXPORT_IMPLEMENT( Namespace::ClassName )

/*! Register the GUID of a class with a single template parameter
 *
 * This macro must be called after calling the
 * BOOST_SERIALIZATION_CLASS1_EXPORT_STANDARD_KEY.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS1_EXPORT_IMPLEMENT( ClassName, Namespace ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL( \
    ClassName, Namespace,                                     \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T ),        \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T ) )

/*! Register the GUID of a class with two template parameters
 *
 * This macro must be called after calling the
 * BOOST_SERIALIZATION_CLASS2_EXPORT_STANDARD_KEY.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS2_EXPORT_IMPLEMENT( ClassName, Namespace )      \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL( \
    ClassName, Namespace,                                     \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U ) )

/*! Register the GUID of a class with three template parameters
 *
 * This macro must be called after calling the
 * BOOST_SERIALIZATION_CLASS3_EXPORT_STANDARD_KEY.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS3_EXPORT_IMPLEMENT( ClassName, Namespace )      \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL( \
    ClassName, Namespace,                                     \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V ) )

/*! Register the GUID of a class with four template parameters
 *
 * This macro must be called after calling the
 * BOOST_SERIALIZATION_CLASS4_EXPORT_STANDARD_KEY.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS4_EXPORT_IMPLEMENT( ClassName, Namespace )      \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL( \
    ClassName, Namespace,                                     \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, typename W ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W ) )

/*! Register the GUID of a class with five template parameters
 *
 * This macro must be called after calling the
 * BOOST_SERIALIZATION_CLASS5_EXPORT_STANDARD_KEY.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS5_EXPORT_IMPLEMENT( ClassName, Namespace )      \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL( \
    ClassName, Namespace,                                     \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, typename U, typename V, typename W, typename X ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, U, V, W, X ) )

/*! Finalize the registration of the template class GUID
 *
 * This macro must be called from the constructors of a template class
 * to finalize the GUID registration process. Because the classes are templates
 * the GUID registration singleton that is used in the registration process
 * won't get instantiated until the first instance of the template class has
 * been created.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ... )  \
  const auto& __guid_initializer__ = boost::archive::detail::extra_detail::init_guid<__VA_ARGS__>::g

/*! Deserialize an enum within a case statement
 *
 * This macro can be used to help deserialize an enum value. This macro call
 * replaces the normal case statement within a switch block for a specific
 * enum value.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ENUM_CASE( enum_value, RawEnumType, deserialized_value ) \
  case (RawEnumType)enum_value:                                         \
    deserialized_value = enum_value;                                      \
    break

/*! Serialize a base class object in a different namespace
 *
 * The BOOST_SERIALIZATION_BASE_OBJECT_NVP macro only works when the derived
 * class is in the same namespace as the base class. This macro will work
 * in all cases.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_BASE_OBJECT_NVP2( base_namespace, name )    \
  boost::serialization::make_nvp(                                       \
      BOOST_PP_STRINGIZE(name),                                             \
      boost::serialization::base_object<base_namespace::name >(*this)     \
  )

/*! Allow shared from this
 *
 * This macro must be called from the global namespace. This macro must be 
 * called if a class that can be serialized inherits from 
 * std::enable_shared_from_this.
 * \ingroup boost_serialization_helpers
 */
#define BOOST_SERIALIZATION_ENABLE_SHARED_FROM_THIS( type )     \
  namespace boost{                                              \
  namespace serialization{                                      \
  template<class Archive>                                       \
  inline void load_construct_data( Archive& ar, type* obj, const unsigned int file_version ) \
  {                                                                     \
    std::shared_ptr<type> shared_obj;                                     \
    access::construct( obj );                                           \
                                                                        \
    boost::serialization::shared_ptr_helper<std::shared_ptr> & h =      \
      ar.template get_helper<shared_ptr_helper<std::shared_ptr> >(      \
                                                shared_ptr_helper_id ); \
    h.reset( shared_obj, obj );                                         \
  }                                                                     \
  }                                                                     \
  }

#else // defined SWIG

#define __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( ... )
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL( ... )

#define BOOST_SERIALIZATION_CLASS_VERSION( ... )
#define BOOST_SERIALIZATION_CLASS1_VERSION( ... )
#define BOOST_SERIALIZATION_CLASS2_VERSION( ... )
#define BOOST_SERIALIZATION_CLASS3_VERSION( ... )
#define BOOST_SERIALIZATION_CLASS4_VERSION( ... )
#define BOOST_SERIALIZATION_CLASS5_VERSION( ... )
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ... )
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( ... )
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS2( ... )
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS3( ... )
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS4( ... )

#define BOOST_SERIALIZATION_TEMPLATE_CLASS_DECL_GUID_DEFINED_IMPL( ... )
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_GUID_IMPL( ... )
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_STANDARD_GUID_IMPL( ... )
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL( ... )
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_STANDARD_KEY_IMPL( ... )
#define BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ... )
#define BOOST_SERIALIZATION_CLASS1_EXPORT_STANDARD_KEY( ... )
#define BOOST_SERIALIZATION_CLASS2_EXPORT_STANDARD_KEY( ... )
#define BOOST_SERIALIZATION_CLASS3_EXPORT_STANDARD_KEY( ... )
#define BOOST_SERIALIZATION_CLASS4_EXPORT_STANDARD_KEY( ... )
#define BOOST_SERIALIZATION_CLASS5_EXPORT_STANDARD_KEY( ... )
#define BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_IMPLEMENT_IMPL( ... )
#define BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ... )
#define BOOST_SERIALIZATION_CLASS1_EXPORT_IMPLEMENT( ... )
#define BOOST_SERIALIZATION_CLASS2_EXPORT_IMPLEMENT( ... )
#define BOOST_SERIALIZATION_CLASS3_EXPORT_IMPLEMENT( ... )
#define BOOST_SERIALIZATION_CLASS4_EXPORT_IMPLEMENT( ... )
#define BOOST_SERIALIZATION_CLASS5_EXPORT_IMPLEMENT( ... )
#define BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ... )
#define BOOST_SERIALIZATION_ENUM_CASE( ... )
#define BOOST_SERIALIZATION_BASE_OBJECT_NVP2( ... )
#define BOOST_SERIALIZATION_ENABLE_SHARED_FROM_THIS( ... )

#endif // end !defined SWIG


#endif // end UTILITY_SERIALIZATION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_SerializationHelpers.hpp
//---------------------------------------------------------------------------//
