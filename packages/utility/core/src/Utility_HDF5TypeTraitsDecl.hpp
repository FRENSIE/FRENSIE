//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5TypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  HDF5 Type Traits declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_TYPE_TRAITS_DECL_HPP
#define UTILITY_HDF5_TYPE_TRAITS_DECL_HPP

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"
#include "FRENSIE_config.hpp"


/*! \defgroup hdf5_type_traits HDF5 Type Traits
 * \ingroup traits
 *
 * The Utility::HDF5FileHandler has many templated member functions. To allow
 * these functions to read and write a variety of data types, a type traits
 * class is needed. The HDF5TypeTraits struct is the struct that defines the
 * type of traits that must be known (static members). To allow for both simple
 * and complex data types, the Utility::HDF5TypeTraits struct must be
 * specialized. Attempting to use the class without a specialization will
 * result in a compile time error. The compile time error message is defined by
 * the Utility::UndefinedTypeTraits struct.
 */

namespace Utility{

/*! \brief This structure defines the traits that are needed by the
 * Utility::HDF5FileHandler class member functions.
 *
 * This structure defines some basic traits for types to be used in
 * HDF5. The HDF5 C++ API function calls request a DataType object
 * corresponding to the type to write to an HDF5 file. A C++ type will map to
 * the desired HDF5 DataType object using this HDF5TypeTraits struct. The
 * functions in the templated base unspecialized struct are designed not to
 * compile (giving a nice compile-time error message) and therefore
 * specializations must be written for each type to be written to HDF5
 * \note The default defined specializations are provided for int, uint and
 * double. The tuple structs will also provide their own specializations.
 * \ingroup hdf5_type_traits
 */
template<typename T, typename Enabled = void>
struct HDF5TypeTraits
{
  //! Typedef for the type that will be used outside of HDF5 files
  typedef T ExternalType;

  //! Typedef for the type that will be stored in HDF5 files
  typedef T InternalType;

  //! Check if the type has a type traits specialization
  typedef std::false_type IsSpecialized;

  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;

  //! Check if the type uses a custom internal type
  typedef std::false_type UsesCustomInternalType;

  //! Returns the HDF5 data type object corresponding to the type
  static inline const HDF5_ENABLED_DISABLED_SWITCH(H5::DataType,int)& dataType()
  { return UndefinedTraits<T>::notDefined(); }

  /*! Initialize internal data
   *
   * If necessary new memory will be allocated for the internal type data.
   * Always call freeInternalData once the returned pointer is no longer
   * needed.
   */
  static inline InternalType* initializeInternalData(
                                            const ExternalType* raw_data,
                                            const size_t size )
  { (void)UndefinedTraits<T>::notDefined(); return NULL; }

  /*! Convert external type data to internal type data
   *
   * The memory for the InternalType data must already be allocated.
   */
  static inline void convertExternalDataToInternalData(
                                           const ExternalType* raw_data,
                                           const size_t size,
                                           InternalType* converted_data )
  { (void)UndefinedTraits<T>::notDefined(); }

  /*! Convert internal type data to external type data
   *
   * The memory for the ExternalType data must already be allocated.
   */
  static inline void convertInternalDataToExternalData(
                                              const InternalType* raw_data,
                                              const size_t size,
                                              ExternalType* converted_data )
  { (void)UndefinedTraits<T>::notDefined(); }

  //! Calculate the size of an internal array of data
  static inline size_t calculateInternalDataSize( const size_t external_size )
  { (void)UndefinedTraits<T>::notDefined(); return 0; }

  //! Calculate the size of an external array of data
  static inline size_t calculateExternalDataSize( const size_t internal_size )
  { (void)UndefinedTraits<T>::notDefined(); return 0; }

  //! Free the inner data created from outer data
  static inline void freeInternalData( InternalType*& data )
  { (void)UndefinedTraits<T>::notDefined(); }
};

} // end Utility namespace

#endif // end UTILITY_HDF5_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
