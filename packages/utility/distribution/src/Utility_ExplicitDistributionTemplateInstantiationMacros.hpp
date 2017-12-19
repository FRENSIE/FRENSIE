//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExplicitDistributionTemplateInstantiationMacros.hpp
//! \author Alex Robinson
//! \brief  Distribution template class explicit instantiation macros
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPLICIT_DISTRIBUTION_TEMPLATE_INSTANTIATION_MACROS_HPP
#define UTILITY_EXPLICIT_DISTRIBUTION_TEMPLATE_INSTANTIATION_MACROS_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

/*! Declare an external explicit instantiation of a distribution class

 * This macro must be called in the global namespace
 * \ingroup explicit_instantiation_macros
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
  class polymorphic_oarchive;                \
  class polymorphic_iarchive;                \
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
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST(                               \
                                         void __VA_ARGS__::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST(                               \
                                         void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const \
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
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST(                               \
                                         void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST(                               \
                                         void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) \
                                          );                            \
  EXTERN_EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                         void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) \
                                          );                            \
}

/*! Declare an explicit instantiation of a distribution class

 * This macro must be called in the Utility namespace within a .cpp file.
 * Since the boost::archive::text_oarchive, boost::archive::text_iarchive,
 * boost::archive::xml_oarchive, boost::archive::xml_iarchive, 
 * boost::archive::binary_oarchive, boost::archive::binary_iarchive,
 * Utility::HDF5OArchive and the Utility::HDF5IArchive are only forward
 * declared in the extern EXPLICIT_DISTRIBUTION_INST macro, they must be
 * included in the .cpp file where this macro is called.
 * \ingroup explicit_instantiation_macros
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
                                  void __VA_ARGS__::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const \
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
  EXPLICIT_TEMPLATE_FUNCTION_INST(                                      \
                                  void __VA_ARGS__::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST(                                      \
                                  void __VA_ARGS__::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) \
                                   );                                   \
  EXPLICIT_TEMPLATE_FUNCTION_INST( \
                                  void __VA_ARGS__::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) \
                                   )

#endif // end UTILITY_EXPLICIT_DISTRIBUTION_TEMPLATE_INSTANTIATION_MACROS_HPP

//---------------------------------------------------------------------------//
// end Utility_ExplicitDistributionTemplateInstantiationMacros.hpp
//---------------------------------------------------------------------------//
