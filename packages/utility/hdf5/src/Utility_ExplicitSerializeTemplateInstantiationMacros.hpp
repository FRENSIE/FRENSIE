//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExplicitSerializeTemplateInstantiationMacros.hpp
//! \author Alex Robinson
//! \brief  Serialize template instantiation macros
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPLICIT_SERIALIZE_TEMPLATE_INSTANTIATION_MACROS_HPP
#define UTILITY_EXPLICIT_SERIALIZE_TEMPLATE_INSTANTIATION_MACROS_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

#define __EXTERN_EXPLICIT_ARCHIVE_FORWARD_DECLARES__()    \
namespace boost{                                              \
namespace archive{                                           \
  class text_oarchive;                                                   \
  class text_iarchive;                                                  \
  class xml_oarchive;                                                   \
  class xml_iarchive;                                                   \
  class binary_oarchive;                                                \
  class binary_iarchive;                                                \
  class polymorphic_oarchive;                                           \
  class polymorphic_iarchive;                                           \
}                                                                       \
}                                                                       \
                                                                        \
namespace Utility{                                                     \
  class HDF5OArchive;                                                  \
  class HDF5IArchive;                                                  \
}

#define __SERIALIZE_INST_IMPL__( INST_MACRO, ... )   \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) ); \
                                                                        \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) )

#define __SAVE_LOAD_INST_IMPL__( INST_MACRO, ... )      \
  INST_MACRO( void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const ); \
                                                                        \
  INST_MACRO( void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) )

/*! Declare an external explicit instantiation of a class's serialization method
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Namespace, ... )   \
  __EXTERN_EXPLICIT_ARCHIVE_FORWARD_DECLARES__();       \
                                                        \
namespace Namespace{                                  \
  __SERIALIZE_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST, __VA_ARGS__ );
}

/*! Declare an explicit instantiation of a class's serialization method
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_CLASS_SERIALIZE_INST( ... ) \
  __SERIALIZE_INST_IMPL__( EXPLICIT_TEMPLATE_FUNCTION_INST, __VA_ARGS__ )

/*! Declare an external explicit instantiation of a class's serialization method
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_CLASS_SERIALIZE_INST_ALWAYS( Namespace, ... )   \
  __EXTERN_EXPLICIT_ARCHIVE_FORWARD_DECLARES__();       \
                                                        \
namespace Namespace{                                  \
  __SERIALIZE_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS, __VA_ARGS__ );
}

/*! Declare an explicit instantiation of a classes serialization method
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_CLASS_SERIALIZE_INST_ALWAYS( ... ) \
  __SERIALIZE_INST_IMPL__( EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS, __VA_ARGS__ );

/*! Declare an external explicit instantiation of a class's save and load methods
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Namespace, ... )   \
  __EXTERN_EXPLICIT_ARCHIVE_FORWARD_DECLARES__();       \
                                                        \
namespace Namespace{                                  \
  __SAVE_LOAD_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST, __VA_ARGS__ );
}

/*! Declare an explicit instantiation of a class's save and load methods
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_CLASS_SAVE_LOAD_INST( ... )   \
  __SAVE_LOAD_INST_IMPL__( EXPLICIT_TEMPLATE_FUNCTION_INST, __VA_ARGS__ )

/*! Declare an external explicit instantiation of a class's save and load methods
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST_ALWAYS( Namespace, ... )   \
  __EXTERN_EXPLICIT_ARCHIVE_FORWARD_DECLARES__();       \
                                                        \
namespace Namespace{                                  \
  __SAVE_LOAD_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS, __VA_ARGS__ );
}

/*! Declare an explicit instantiation of a class's save and load methods
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_CLASS_SAVE_LOAD_INST_ALWAYS( ... )   \
  __SAVE_LOAD_INST_IMPL__( EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS, __VA_ARGS__ );

#endif // end UTILITY_EXPLICIT_SERIALIZE_TEMPLATE_INSTANTIATION_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExplicitSerializeTemplateInstantiationMacros.hpp
//---------------------------------------------------------------------------//
