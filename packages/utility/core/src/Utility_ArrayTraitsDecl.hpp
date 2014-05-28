//---------------------------------------------------------------------------//
//! 
//! \file   Utility_ArrayTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Array traits class declaration
//! 
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARRAY_TRAITS_DECL_HPP
#define UTILITY_ARRAY_TRAITS_DECL_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_OrdinalTraits.hpp>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"
#include "Utility_ContractException.hpp"

/*! \defgroup array_traits Array Traits
 * \ingroup traits
 *
 * The Utility::HDF5FileHandler has many templated member functions 
 * with a template template parameter (Array). Because the Teuchos array 
 * classes have slightly different interfaces, a traits class is needed to 
 * homogenize the interfaces (bridge pattern). The 
 * Utility::Traits::ArrayTraits struct defines the interface. Because of the 
 * slightly different interfaces for each array type, the 
 * Utility::Traits::HDF5ArrayTraits class must be specialized. Attempting to 
 * use the class without a specialization will result in a compile time error. 
 * The compile time error message is defined by the 
 * Utility::Traits::UndefinedTraits struct.
 */

namespace Utility{

namespace Traits{

/*! \brief Default array traits struct.
 * 
 * This struct should allow use of any Teuchos::Array when dealing with the
 * HDF5 interface and DataProcessor interface. The std::vector is also 
 * supported. The functions in the templated base unspecialized struct are 
 * designed not to compile (giving a nice compile-time error message) and 
 * therefore specializations must be written for each array type. The design 
 * pattern that is implemented with the templated class is the bridge pattern. 
 * Every array type has a slightly different interface and this struct 
 * homogenizes the interfaces so that they can all be used inside of the other 
 * templated functions used by Utility. It should be noted that even though the
 * class name implies that this is a traits class, some behavioral functions 
 * are also defined indicating that it is not a true traits class (it is also 
 * a policies class). The traits name was used to conform with the standard 
 * library convention (see std::char_traits which is also a hybrid traits and 
 * policies class). It must be noted that one need not interact with the 
 * behavioral functions directly through the traits class. Several policy
 * functions have been written that hide the traits class.
 * \tparam T An array of types.
 * \note The default defined specializations are provided for Teuchos::Array,
 * Teuchos::ArrayRCP, Teuchos::ArrayView and Teuchos::TwoDArray, and 
 * std::vector
 * \ingroup traits
 */
template<typename T>
struct ArrayTraits
{
  //! The size type of the array
  typedef typename T::size_type size_type;
  //! The type contained in the array
  typedef typename T::value_type value_type;
  //! The pointer type of the array
  typedef typename T::pointer pointer;
  //! The const pointer type of the array
  typedef typename T::const_pointer const_pointer;
  //! The iterator type of the array
  typedef typename T::iterator iterator;
  //! The const iterator type of the array
  typedef typename T::const_iterator const_iterator;
  
  //! The head pointer of the array
  static inline pointer headPtr( T &array )
  { (void)UndefinedTraits<T>::notDefined(); return 0; }
  
  //! The head pointer of a const array
  static inline const_pointer headPtr( const T &array)
  { (void)UndefinedTraits<T>::notDefined(); return 0; }

  //! A view of the array
  static inline Teuchos::ArrayView<value_type> view( 
	  T &array, 
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { (void)UndefinedTraits<T>::notDefined(); return 0; }
  
  //! A view of the const array
  static inline Teuchos::ArrayView<const value_type> view(
	  const T &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { (void)UndefinedTraits<T>::notDefined(); return 0; }
  
  //! The size of the array
  static inline size_type size(const T &array)
  { (void)UndefinedTraits<T>::notDefined(); return 0; }
  
  //! Resize the array
  static inline void resize( T &array, size_type n )
  { (void)UndefinedTraits<T>::notDefined(); }
  
  //! Copy the ArrayView object
  static inline void copyView( T &array,
			       const Teuchos::ArrayView<T> &view )
  { (void)UndefinedTraits<T>::notDefined(); }

  //! Copy the ArrayView of const object
  static inline void copyView( T &array,
			       const Teuchos::ArrayView<const T> &view )
  { (void)UndefinedTraits<T>::notDefined(); }
};

} // end Traits namespace

/*! This function allows access to the headPtr ArrayTraits function.
 *
 * This function is simply a more concise way to access the getRawPtr static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to get a raw pointer to the associated Utility::Traits::ArrayTraits 
 * class. It is important to note that the array type will be deduced by
 * the function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename Traits::ArrayTraits<Array>::pointer
getHeadPtr( Array &array )
{ return Traits::ArrayTraits<Array>::headPtr( array ); }

/*! This function allows access to the headPtr ArrayTraits function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename Traits::ArrayTraits<Array>::const_pointer
getHeadPtr( const Array &array )
{ return Traits::ArrayTraits<Array>::headPtr( array ); }

/*! This function allows access to the size ArrayTraits function.
 * 
 * This function is simply a more concise way to access the size static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to get the size of an array to the associated 
 * Utility::Traits::ArrayTraits class. It is important to note that the array
 * type will be deduced by the function.
 * \ingroup array_traits
 */
template<typename Array>
inline typename Traits::ArrayTraits<Array>::size_type
getArraySize( const Array &array )
{ return Traits::ArrayTraits<Array>::size( array ); }

/*! This function allows access to the resize ArrayTraits function.
 *
 * This function is simply a more concise way to access the resize static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to resize an array to the assocaited Utility::Traits::ArrayTraits 
 * class. It is important to note that the array type will be deduced by the
 * function.
 * \ingroup array_traits
 */
template<typename Array>
inline void
resizeArray( Array &array, typename Traits::ArrayTraits<Array>::size_type n )
{ return Traits::ArrayTraits<Array>::resize( array, n ); }

/*! This function allows access to the view ArrayTriats function.
 *
 * This function is simply a more concise way to access the view static
 * member function associated with the ArrayTraits class. It simply forwards
 * calls to get a view of the array to the associated
 * Utility::Traits::ArrayTraits class. It is important to note that the array
 * type will be deduced by the function.
 * \ingroup array_traits
 */
template<typename Array>
inline Teuchos::ArrayView<typename Traits::ArrayTraits<Array>::value_type>
getArrayView( Array &array,
	      const typename Traits::ArrayTraits<Array>::size_type offset = Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::zero(),
	      typename Traits::ArrayTraits<Array>::size_type size = Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::invalid() )
{ 
  // make sure the offset and size supplied are acceptable
  remember( typename Traits::ArrayTraits<Array>::size_type array_size =
	    getArraySize( array ) );
  testPrecondition( offset < array_size );
  testPrecondition( size == Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::invalid() || ( size > Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::zero() && size <= array_size-offset ) );
  
  return Traits::ArrayTraits<Array>::view( array, offset, size ); 
}

/*! This function allows access to the view ArrayTraits function.
 * \ingroup array_traits
 */
template<typename Array>
inline 
Teuchos::ArrayView<const typename Traits::ArrayTraits<Array>::value_type>
getArrayView( const Array &array,
	      const typename Traits::ArrayTraits<Array>::size_type offset = Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::zero(),
	      const typename Traits::ArrayTraits<Array>::size_type size = Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::invalid() )
{ 
  // make sure the offset and size supplied are acceptable
  remember( typename Traits::ArrayTraits<Array>::size_type array_size =
	    getArraySize( array ) );
  testPrecondition( offset < array_size );
  testPrecondition( size == Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::invalid() || ( size > Teuchos::OrdinalTraits<typename Traits::ArrayTraits<Array>::size_type>::zero() && size <= array_size-offset ) );
  
  return Traits::ArrayTraits<Array>::view( array, offset, size ); 
}

/*! This function allows access to the copyView ArrayTraits function
 *
 * This function is simply a more concise way to access the copyView
 * static member function associated with the ArrayTraits class. It simply
 * forwards calls to copy the ArrayView object to the associated 
 * Utility::Traits::ArrayTraits class. It is important to note that the array
 * type will be deduced by the function.
 * \ingroup array_traits
 */
template<typename Array>
inline void copyArrayView( Array &array,
			   const Teuchos::ArrayView<typename Traits::ArrayTraits<Array>::value_type> &array_view )
{ Traits::ArrayTraits<Array>::copyView( array, array_view ); } 

/*! This function allows access to the copyView ArrayTraits function
 * \ingroup array_traits
 */
template<typename Array>
inline void copyArrayView( Array &array,
			   const Teuchos::ArrayView<const typename Traits::ArrayTraits<Array>::value_type> &array_view )
{ Traits::ArrayTraits<Array>::copyView( array, array_view ); }

} // end Utility namespace

#endif // end UTILITY_ARRAY_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayTraitsDecl.hpp
//---------------------------------------------------------------------------//

