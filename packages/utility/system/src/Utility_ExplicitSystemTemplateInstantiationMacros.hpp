//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExplicitSystemTemplateInstantiationMacros.hpp
//! \author Alex Robinson
//! \brief  System template explicit instantiation macros
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPLICIT_SYSTEM_TEMPLATE_INSTANTIATION_MACROS_HPP
#define UTILITY_EXPLICIT_SYSTEM_TEMPLATE_INSTANTIATION_MACROS_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

#if !defined SWIG

#define __EXTERN_EXPLICIT_SYSTEM_ARCHIVE_FORWARD_DECLARES__()   \
namespace boost{                                           \
namespace archive{                                           \
  class text_oarchive;                       \
  class text_iarchive;                       \
  class xml_oarchive;                        \
  class xml_iarchive;                        \
  class binary_oarchive;                     \
  class binary_iarchive;                     \
  class polymorphic_oarchive;                \
  class polymorphic_iarchive;                \
}                                            \
}                                            \
                                             \
namespace Utility{                          \
  class HDF5OArchive;                       \
  class HDF5IArchive;                       \
}

/*! Declare an external explicit instantiation of a system class's serialize method
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_SYSTEM_CLASS_SERIALIZE_INST( ... )      \
  __EXTERN_EXPLICIT_SYSTEM_ARCHIVE_FORWARD_DECLARES__();        \
                                                                \
namespace Utility{                                            \
 EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) ); \
}

/*! Declare an explicit instantiation of a system class's serialize method
 *
 * This macro can be called from the global namespace or from the utility
 * namespace. If it is called from the global, qualify the class name with
 * the Utility namespace. Only call this macro within a .cpp file.
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_SYSTEM_CLASS_SERIALIZE_INST( ... )     \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::serialize<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) )

/*! Declare an external explicit instantiation of a system class's save/load methods
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_SYSTEM_CLASS_SAVE_LOAD_INST( ... )      \
  __EXTERN_EXPLICIT_SYSTEM_ARCHIVE_FORWARD_DECLARES__();        \
                                                                \
namespace Utility{                                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const ); \
                                                                        \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) ); \
}

/*! Declare an explicit instantiation of a system class's save/load methods
 *
 * This macro can be called from the global namespace or from the utility
 * namespace. If it is called from the global, qualify the class name with
 * the Utility namespace. Only call this macro within a .cpp file.
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_SYSTEM_CLASS_SAVE_LOAD_INST( ... )     \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const ); \
                                                                        \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) )

#else // !defined SWIG

#define EXTERN_EXPLICIT_SYSTEM_CLASS_SERIALIZE_INST( ... )
#define EXPLICIT_SYSTEM_CLASS_SERIALIZE_INST( ... )
#define EXTERN_EXPLICIT_SYSTEM_CLASS_SAVE_LOAD_INST( ... )
#define EXPLICIT_SYSTEM_CLASS_SAVE_LOAD_INST( ... )

#endif // end !defined SWIG

#endif // end UTILITY_EXPLICIT_SYSTEM_TEMPLATE_INSTANTIATION_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExplicitSystemTemplateInstantiationMacros.hpp
//---------------------------------------------------------------------------//
