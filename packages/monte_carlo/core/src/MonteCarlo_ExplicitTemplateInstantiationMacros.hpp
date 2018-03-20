//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ExplicitTemplateInstantiationMacros.hpp
//! \author Alex Robinson
//! \brief  MonteCarlo class template function explicit instantiation macros
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP
#define MONTE_CARLO_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

#define __EXTERN_EXPLICIT_MONTE_CARLO_FORWARD_DECLARES__()      \
namespace boost{                                              \
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

#define EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( ... ) \
  __EXTERN_EXPLICIT_MONTE_CARLO_FORWARD_DECLARES__();           \
                                                                      \
namespace MonteCarlo{                                                 \
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

#define EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( ... )    \
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

#define EXTERN_EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( ... ) \
  __EXTERN_EXPLICIT_MONTE_CARLO_FORWARD_DECLARES__();           \
                                                                \
namespace MonteCarlo{                        \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) ); \
                                                                        \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) ); \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) ); \
}

#define EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( ... )    \
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

#endif // end MONTE_CARLO_EXPLICIT_TEMPLATE_INSTANTIATION_MACROS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ExplicitTemplateInstantiationMacros.hpp
//---------------------------------------------------------------------------//
