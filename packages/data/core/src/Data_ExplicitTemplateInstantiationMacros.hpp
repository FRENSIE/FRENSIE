//---------------------------------------------------------------------------//
//!
//! \file   Data_ExplicitTemplateInstantiationMacros.hpp"
//! \author Alex Robinson
//! \brief  Data class template function explicit instantiation macros
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP
#define DATA_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

#if !defined SWIG

#define EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ... )    \
namespace boost{                                              \
namespace archive{                           \
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
}                                           \
                                            \
namespace Data{                        \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::detail::content_oarchive>(boost::mpi::detail::content_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::detail::mpi_datatype_oarchive>(boost::mpi::detail::mpi_datatype_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::packed_oarchive>(boost::mpi::packed_oarchive& ar, const unsigned version ) const ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::packed_skeleton_oarchive>(boost::mpi::packed_skeleton_oarchive& ar, const unsigned version ) const ); \
                                                                        \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::mpi::packed_iarchive>(boost::mpi::packed_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::mpi::packed_skeleton_iarchive>(boost::mpi::packed_skeleton_iarchive& ar, const unsigned version ) ); \
}

#define EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ... )    \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::detail::content_oarchive>(boost::mpi::detail::content_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::detail::mpi_datatype_oarchive>(boost::mpi::detail::mpi_datatype_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::packed_oarchive>(boost::mpi::packed_oarchive& ar, const unsigned version ) const ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::mpi::packed_skeleton_oarchive>(boost::mpi::packed_skeleton_oarchive& ar, const unsigned version ) const ); \
                                                                        \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::mpi::packed_iarchive>(boost::mpi::packed_iarchive& ar, const unsigned version ) ); \
  EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::mpi::packed_skeleton_iarchive>(boost::mpi::packed_skeleton_iarchive& ar, const unsigned version ) )

#else // !defined SWIG

#define EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ... )
#define EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ... )

#endif // end !defined SWIG

#endif // end DATA_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP

//---------------------------------------------------------------------------//
// end Data_ExplicitTemplateInstantiationMacros.hpp"
//---------------------------------------------------------------------------//
