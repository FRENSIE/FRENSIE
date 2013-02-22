//---------------------------------------------------------------------------//
// \file   HDF5ArrayTraitsDecl.hpp
// \author Alex Robinson
// \brief  HDF5 Array Traits declaration
//---------------------------------------------------------------------------//

#ifndef HDF5_ARRAY_TRAITS_DECL_HPP
#define HDF5_ARRAY_TRAITS_DECL_HPP

namespace FACEMC{

/*!
 * \brief This is the default structure used by ArrayTraits<Array> to produce
 * a compile time error when the specialization does not exist for array type
 * Array
 */
template<typename T, template<typename> class Array>
struct UndefinedArrayTraits
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return Array<T>::this_type_is_missing_a_specialization(); }
};

/*!
 * \brief This structure defines some basic traits for Arrays to be used in 
 * FACEMC. This struct should allow use of any Teuchos::Array anywhere in 
 * FACEMC. Any other arrays will not be supported. The functions in the 
 * templated base unspecialized struct are designed not to compile (giving a 
 * nice compile-time error message) and therefore specializations must be 
 * written for each array type.
 * \note <ol>
 * <li> The default defined specializations are provided for \c Teuchos::Array,  * \c Teuchos::ArrayRCP, \c Teuchos::ArrayView, \c Teuchos::TwoDArray
 * </ol>
 */
template<typename T, template<typename> class Array>
struct HDF5ArrayTraits
{
  //! Return a raw pointer to the head of the array
  static inline T* getRawPtr(Array<T> array) { (void)UndefinedArrayTraits<T,Array>::notDefined(); return 0; }
  //! Resize the array
  static inline void resize(Array<T> array, typename Array<T>::size_type n) { (void)UndefinedArrayTraits<T,Array>::notDefined(); return 0; }
  //! Return the size of the array
  static inline typename Array<T>::size_type size(Array<T> array){ (void)UndefinedArrayTraits<T,Array>::notDefined(); return 0; }
};

} // end FACEMC namespace

#endif // end HDF5_ARRAY_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end HDF5ArrayTraitsDecl.hpp
//---------------------------------------------------------------------------//

