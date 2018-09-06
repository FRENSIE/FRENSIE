//---------------------------------------------------------------------------//
//!
//! \file   Utility_TypeNameTraits.hpp
//! \author Alex Robinson
//! \brief  Type name traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TYPE_NAME_TRAITS_HPP
#define UTILITY_TYPE_NAME_TRAITS_HPP

// Std Lib Includes
#include <string>
#include <complex>

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_TypeNameTraitsDecl.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace boost{
namespace archive{

class xml_oarchive;
class xml_iarchive;
class text_oarchive;
class text_iarchive;
class binary_oarchive;
class binary_iarchive;
class polymorphic_oarchive;
class polymorphic_iarchive;
  
} // end archive namespace
} // end boost namespace

namespace Utility{

TYPE_NAME_TRAITS_QUICK_DECL( void );
TYPE_NAME_TRAITS_QUICK_DECL( void* );
TYPE_NAME_TRAITS_QUICK_DECL( float );
TYPE_NAME_TRAITS_QUICK_DECL( double );
TYPE_NAME_TRAITS_QUICK_DECL( long double );
TYPE_NAME_TRAITS_QUICK_DECL( bool );
TYPE_NAME_TRAITS_QUICK_DECL( char );
TYPE_NAME_TRAITS_QUICK_DECL( unsigned char );
TYPE_NAME_TRAITS_QUICK_DECL( signed char );
TYPE_NAME_TRAITS_QUICK_DECL( wchar_t );
TYPE_NAME_TRAITS_QUICK_DECL( short );
TYPE_NAME_TRAITS_QUICK_DECL( unsigned short );
TYPE_NAME_TRAITS_QUICK_DECL( int );
TYPE_NAME_TRAITS_QUICK_DECL( unsigned int );
TYPE_NAME_TRAITS_QUICK_DECL( long int );
TYPE_NAME_TRAITS_QUICK_DECL( unsigned long int );
TYPE_NAME_TRAITS_QUICK_DECL( long long int );
TYPE_NAME_TRAITS_QUICK_DECL( unsigned long long int );
TYPE_NAME_TRAITS_QUICK_DECL( std::complex<float> );
TYPE_NAME_TRAITS_QUICK_DECL( std::complex<double> );
TYPE_NAME_TRAITS_QUICK_DECL( std::string );
TYPE_NAME_TRAITS_QUICK_DECL( std::wstring );

/*! \brief Partial specialization of Utility::TypeNameTraits for 
 * std::integral_constant types
 * \ingroup type_name_traits
 */
template<typename T, T v>
struct TypeNameTraits<std::integral_constant<T,v> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return Utility::toString( v ); }
};

/*! \brief Partial specialization of Utility::TypeNameTraits for
 * boost::units::unit types
 * \ingroup type_name_traits
 */
template<typename Dim, typename Sys>
struct TypeNameTraits<boost::units::unit<Dim,Sys> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return Utility::UnitTraits<boost::units::unit<Dim,Sys> >::name(); }
};

/*! \brief Partial specialization of Utility::TypeNameTraits for 
 * boost::units::quantity types
 * \ingroup type_name_traits
 */
template<typename Unit, typename T>
struct TypeNameTraits<boost::units::quantity<Unit,T> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return std::string("boost::units::quantity<") +
      Utility::UnitTraits<Unit>::symbol() + "," +
      TypeNameTraits<T>::name() +">";
  }
};
  
/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::xml_oarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::xml_oarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::xml_oarchive"; }
};

/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::xml_iarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::xml_iarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::xml_iarchive"; }
};

/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::text_oarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::text_oarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::text_oarchive"; }
};

/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::text_iarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::text_iarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::text_iarchive"; }
};

/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::binary_oarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::binary_oarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::binary_oarchive"; }
};

/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::binary_iarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::binary_iarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::binary_iarchive"; }
};

/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::polymorphic_oarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::polymorphic_oarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::polymorphic_oarchive"; }
};

/*! \brief Specialization of Utility::TypeNameTraits for 
 * boost::archive::polymorphic_iarchive 
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<boost::archive::polymorphic_iarchive>
{
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "boost::archive::polymorphic_iarchive"; }
};

/*! Partial specialization of Utility::TypeNameTraits for const types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<std::is_const<T>::value && !std::is_volatile<T>::value && !std::is_pointer<T>::value && !std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_const<T>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return std::string("const ") + TypeNameTraits<typename std::remove_const<T>::type>::name(); }
};

/*! Partial specialization of Utility::TypeNameTraits for volatile types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<!std::is_const<T>::value && std::is_volatile<T>::value && !std::is_pointer<T>::value && !std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_volatile<T>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return std::string("volatile ") + TypeNameTraits<typename std::remove_volatile<T>::type>::name(); }
};

/*! Partial specialization of Utility::TypeNameTraits for const volatile types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T, typename std::enable_if<std::is_const<T>::value && std::is_volatile<T>::value && !std::is_pointer<T>::value && !std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_cv<T>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return std::string("const volatile ") + TypeNameTraits<typename std::remove_cv<T>::type>::name(); }
};

/*! Partial specialization of Utility::TypeNameTraits for pointer types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<!std::is_const<T>::value && !std::is_volatile<T>::value && std::is_pointer<T>::value && !IsPointerToConst<T>::value && !std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_pointer<T>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return TypeNameTraits<typename std::remove_pointer<T>::type>::name() + "*"; }
};

/*! Partial specialization of Utility::TypeNameTraits for const pointer types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<std::is_const<T>::value && !std::is_volatile<T>::value && std::is_pointer<T>::value && !IsPointerToConst<T>::value && !std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_pointer<T>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return TypeNameTraits<typename std::remove_pointer<T>::type>::name() + "* const"; }
};

/*! \brief Partial specialization of Utility::TypeNameTraits for 
 * pointer-to-const types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<!std::is_const<T>::value && !std::is_volatile<T>::value && std::is_pointer<T>::value && IsPointerToConst<T>::value && !std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return std::string("const ")+TypeNameTraits<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::name()+"*"; }
};

/*! \brief Partial specialization of Utility::TypeNameTraits for 
 * const pointer-to-const types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<std::is_const<T>::value && !std::is_volatile<T>::value && std::is_pointer<T>::value && IsPointerToConst<T>::value && !std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return std::string("const ")+TypeNameTraits<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::name()+"* const"; }
};

/*! Partial specialization of Utility::TypeNameTraits for reference types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<!std::is_const<T>::value && !std::is_volatile<T>::value && !std::is_pointer<T>::value && std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_reference<T>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return TypeNameTraits<typename std::remove_reference<T>::type>::name() + "&"; }
};

/*! Partial specialization of Utility::TypeNameTraits for const reference types
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<T,typename std::enable_if<std::is_const<T>::value && !std::is_volatile<T>::value && !std::is_pointer<T>::value && std::is_reference<T>::value>::type>
{
  //! Check if the type has a specialization
  typedef typename TypeNameTraits<typename std::remove_const<typename std::remove_reference<T>::type>::type>::IsSpecialized IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return std::string("const ")+TypeNameTraits<typename std::remove_const<typename std::remove_reference<T>::type>::type>::name()+"&"; }
};

namespace Details{

/*! The type name parameter pack helper class
 * \ingroup type_name_traits
 */
template<typename... Types>
struct TypeNameParameterPackHelper;

/*! \brief Partial specialization of the TypeNameParameterPackHelper class for
 * a single template parameter
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameParameterPackHelper<T>
{
  //! Append the type name to the end of the string
  static void appendName( std::string& parameter_pack_name )
  { parameter_pack_name += Utility::TypeNameTraits<T>::name(); }
};

/*! \brief Partial specialization of the TypeNameParameterPackHelper class for
 * peeling off the first parameter
 * \ingroup type_name_traits
 */
template<typename T, typename... Types>
struct TypeNameParameterPackHelper<T,Types...>
{
  //! Append all type names to the end of the string
  static void appendName( std::string& parameter_pack_name )
  {
    parameter_pack_name += Utility::TypeNameTraits<T>::name();
    parameter_pack_name += ",";

    TypeNameParameterPackHelper<Types...>::appendName( parameter_pack_name );
  }
};
  
} // end Details namespace

// Return the type name
template<typename T>
inline std::string typeName()
{
  return Utility::TypeNameTraits<T>::name();
}

// Return the type name
template<typename... Types>
inline typename std::enable_if<(sizeof...(Types)>1),std::string>::type
typeName()
{
  std::string parameter_pack_name;
  
  Details::TypeNameParameterPackHelper<Types...>::appendName( parameter_pack_name );

  return parameter_pack_name;
}
  
} // end Utility namespace

#endif // end UTILITY_TYPE_NAME_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_TypeNameTraits.hpp
//---------------------------------------------------------------------------//
