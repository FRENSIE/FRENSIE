//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExplicitSerializationTemplateInstantiationMacros.hpp
//! \author Alex Robinson
//! \brief  Serialize template instantiation macros
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPLICIT_SERIALIZATION_TEMPLATE_INSTANTIATION_MACROS_HPP
#define UTILITY_EXPLICIT_SERIALIZATION_TEMPLATE_INSTANTIATION_MACROS_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

#ifdef HAVE_FRENSIE_HDF5
#define __EXTERN_EXPLICIT_HDF5_ARCHIVE_FORWARD_DECLARES__()     \
namespace Utility{                                            \
  class HDF5IArchive;                                           \
  class HDF5OArchive;                                           \
}
#else // HAVE_FRENSIE_HDF5
#define __EXTERN_EXPLICIT_HDF5_ARCHIVE_FORWARD_DECLARES__()
#endif // end HAVE_FRENSIE_HDF5

#ifdef HAVE_FRENSIE_MPI
#define __EXTERN_EXPLICIT_MPI_ARCHIVE_FORWARD_DECLARES__()      \
namespace boost{                                              \
namespace mpi{                                            \
  class packed_oarchive;                                     \
  class packed_iarchive;                                     \
  class packed_skeleton_oarchive;                            \
  class packed_skeleton_iarchive;                            \
namespace detail{                                            \
 class content_oarchive;                                     \
 class mpi_datatype_oarchive;                                \
}                                                            \
}                                                            \
}
#else // HAVE_FRENSIE_MPI
#define __EXTERN_EXPLICIT_MPI_ARCHIVE_FORWARD_DECLARES__()
#endif // end HAVE_FRENSIE_MPI

#define __EXTERN_EXPLICIT_ARCHIVE_FORWARD_DECLARES__()    \
namespace boost{                                              \
namespace archive{                                           \
  class text_oarchive;                                                   \
  class text_iarchive;                                                  \
  class xml_oarchive;                                                   \
  class xml_iarchive;                                                   \
  class binary_oarchive;                                                \
  class binary_iarchive;                                                \
}                                                                       \
}                                                                       \
                                                                        \
__EXTERN_EXPLICIT_HDF5_ARCHIVE_FORWARD_DECLARES__();                     \
__EXTERN_EXPLICIT_MPI_ARCHIVE_FORWARD_DECLARES__()

#ifdef HAVE_FRENSIE_HDF5
#define __SERIALIZE_INST_HDF5_IMPL__( INST_MACRO, ... ) \
  INST_MACRO( void __VA_ARGS__::serialize<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) )
#else // HAVE_FRENSIE_HDF5
#define __SERIALIZE_INST_HDF5_IMPL__( INST_MACRO, ... )
#endif // end HAVE_FRENSIE_HDF5

#ifdef HAVE_FRENSIE_MPI
#define __SERIALIZE_INST_MPI_IMPL__( INST_MACRO, ... )     \
  INST_MACRO( void __VA_ARGS__::serialize<boost::mpi::detail::content_oarchive>( boost::mpi::detail::content_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::mpi::detail::mpi_datatype_oarchive>( boost::mpi::detail::mpi_datatype_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::mpi::packed_oarchive>( boost::mpi::packed_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::mpi::packed_skeleton_oarchive>( boost::mpi::packed_skeleton_oarchive& ar, const unsigned version ) ); \
                                                                        \
  INST_MACRO( void __VA_ARGS__::serialize<boost::mpi::packed_iarchive>( boost::mpi::packed_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::mpi::packed_skeleton_iarchive>( boost::mpi::packed_skeleton_iarchive& ar, const unsigned version ) )
#else // HAVE_FRENSIE_MPI
#define __SERIALIZE_INST_MPI_IMPL__( INST_MACRO, ... )
#endif // end HAVE_FRENSIE_MPI

#define __SERIALIZE_INST_IMPL__( INST_MACRO, ... )   \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) ); \
                                                                        \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::serialize<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
                                                                        \
  __SERIALIZE_INST_HDF5_IMPL__( INST_MACRO, __VA_ARGS__ );              \
  __SERIALIZE_INST_MPI_IMPL__( INST_MACRO, __VA_ARGS__ )

#ifdef HAVE_FRENSIE_HDF5
#define __SAVE_LOAD_HDF5_IMPL__( INST_MACRO, ... )      \
  INST_MACRO( void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) )
#else // HAVE_FRENSIE_HDF5
#define __SAVE_LOAD_HDF5_IMPL__( INST_MACRO, ... )
#endif // end HAVE_FRENSIE_HDF5

#ifdef HAVE_FRENSIE_MPI
#define __SAVE_LOAD_MPI_IMPL__( INST_MACRO, ... )       \
  INST_MACRO( void __VA_ARGS__::save<boost::mpi::detail::content_oarchive>( boost::mpi::detail::content_oarchive&, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::mpi::detail::mpi_datatype_oarchive>( boost::mpi::detail::mpi_datatype_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::mpi::packed_oarchive>( boost::mpi::packed_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::mpi::packed_skeleton_oarchive>( boost::mpi::packed_skeleton_oarchive& ar, const unsigned version ) const ); \
                                                                        \
  INST_MACRO( void __VA_ARGS__::load<boost::mpi::packed_iarchive>( boost::mpi::packed_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::load<boost::mpi::packed_skeleton_iarchive>( boost::mpi::packed_skeleton_iarchive& ar, const unsigned version ) )
#else // HAVE_FRENSIE_MPI
#define __SAVE_LOAD_MPI_IMPL__( INST_MACRO, ... )
#endif // end HAVE_FRENSIE_MPI

#define __SAVE_LOAD_INST_IMPL__( INST_MACRO, ... )      \
  INST_MACRO( void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const ); \
  INST_MACRO( void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const ); \
                                                                        \
  INST_MACRO( void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  INST_MACRO( void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
                                                                        \
  __SAVE_LOAD_HDF5_IMPL__( INST_MACRO, __VA_ARGS__ );                   \
  __SAVE_LOAD_MPI_IMPL__( INST_MACRO, __VA_ARGS__ )

/*! Declare an external explicit instantiation of a class's serialization method
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Namespace, ... )   \
  __EXTERN_EXPLICIT_ARCHIVE_FORWARD_DECLARES__();       \
                                                        \
namespace Namespace{                                  \
  __SERIALIZE_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST, __VA_ARGS__ ); \
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
  __SERIALIZE_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS, __VA_ARGS__ ); \
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
  __SAVE_LOAD_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST, __VA_ARGS__ ); \
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
  __SAVE_LOAD_INST_IMPL__( EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS, __VA_ARGS__ ); \
}

/*! Declare an explicit instantiation of a class's save and load methods
 *
 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
 */
#define EXPLICIT_CLASS_SAVE_LOAD_INST_ALWAYS( ... )   \
  __SAVE_LOAD_INST_IMPL__( EXPLICIT_TEMPLATE_FUNCTION_INST_ALWAYS, __VA_ARGS__ );

#endif // end UTILITY_EXPLICIT_SERIALIZATION_TEMPLATE_INSTANTIATION_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExplicitSerializationTemplateInstantiationMacros.hpp
//---------------------------------------------------------------------------//
