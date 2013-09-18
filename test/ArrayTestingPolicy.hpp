//---------------------------------------------------------------------------//
//!
//! \file   ArrayTestingPolicy.hpp
//! \author Alex Robinson
//! \brief  Policy specializations for running tests on arrays
//!
//---------------------------------------------------------------------------//

#ifndef ARRAY_TESTING_POLICY_HPP
#define ARRAY_TESTING_POLICY_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "ArrayTestingPolicyDecl.hpp"

namespace FACEMC{

/*! \brief The partial specialization of the FACEMC::ArrayTestingPolicy for the
 * Teuchos::Array class
 * \ingroup array_testing_policy
 */
template<typename T>
struct ArrayTestingPolicy<T,Teuchos::Array>
{
  static inline Teuchos::ArrayView<T> view( Teuchos::Array<T> &array ) { return array(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::Array<T> &array ) { return array(); }
  static inline Teuchos::Array<T> createArrayFromView( const Teuchos::ArrayView<T> &array_view ) 
  { 
    Teuchos::Array<T> dummy_array( array_view );
    return dummy_array;
  }
  static inline void resize( Teuchos::Array<T> &array, const typename Teuchos::Array<T>::size_type size ) { array.resize( size ); }
  static inline typename Teuchos::Array<T>::size_type size( const Teuchos::Array<T> &array ) { return array.size(); }
};

/*! \brief The partial specialization of the FACEMC::ArrayTestingPolicy for the 
 * Teuchos::ArrayRCP class.
 * \ingroup array_testing_policy
 */
template<typename T>
struct ArrayTestingPolicy<T,Teuchos::ArrayRCP>
{
  static inline Teuchos::ArrayView<T> view( Teuchos::ArrayRCP<T> &array ) { return array(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::ArrayRCP<T> &array ) { return array(); }
  static inline Teuchos::ArrayRCP<T> createArrayFromView( const Teuchos::ArrayView<T> &array_view ) { return arcpFromArrayView( array_view ); }
  static inline void resize( Teuchos::ArrayRCP<T> &array, const typename Teuchos::ArrayRCP<T>::size_type size ) { array.resize( size ); }    
  static inline typename Teuchos::ArrayRCP<T>::size_type size( const Teuchos::ArrayRCP<T> &array ) { return array.size(); }
};

/*! \brief The partial specialization of the FACEMC::ArrayTestingPolicy for the
 * Teuchos::ArrayView class.
 * \ingroup array_testing_policy
 */
template<typename T>
struct ArrayTestingPolicy<T,Teuchos::ArrayView>
{
  static inline Teuchos::ArrayView<T> view( Teuchos::ArrayView<T> &array ) { return array(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::ArrayView<T> &array ) { return array(); }
  static inline Teuchos::ArrayView<T> createArrayFromView( const Teuchos::ArrayView<T> &array_view ) { return array_view; }
  static inline void resize( Teuchos::ArrayRCP<T> &array, const typename Teuchos::ArrayRCP<T>::size_type size ) { array.resize( size ); }    
  static inline typename Teuchos::ArrayRCP<T>::size_type size( const Teuchos::ArrayRCP<T> &array ) { return array.size(); }
};

/*! \brief The partial specialization of the FACEMC::ArrayTestingPolicy for the
 * Teuchos::ArrayView class.
 * \ingroup array_testing_policy
 */
template<typename T>
struct ArrayTestingPolicy<T,Teuchos::TwoDArray>
{
  static inline Teuchos::ArrayView<const T> view( Teuchos::TwoDArray<T> &array ) { return array.getDataArray()(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::TwoDArray<T> &array ) { return array.getDataArray()(); }
  static inline Teuchos::TwoDArray<T> createArrayFromView( const Teuchos::ArrayView<T> &array_view )
  {
    Teuchos::TwoDArray<T> dummy_array( 1, array_view.size() );
    dummy_array[0] = array_view;
    return dummy_array;
  }
  /*! \details Becuase only one size parameter is allowed in the interface, the
   * Teuchos::TwoDArray will simply be resized to a 1D array with <em> size
   * </em> columns.
   */
  static inline void resize( Teuchos::TwoDArray<T> &array, const typename Teuchos::TwoDArray<T>::size_type size )
  {
    array.resizeRows( 1 );
    array.resizeCols( size );
  }
  static inline typename Teuchos::TwoDArray<T>::size_type size( const Teuchos::TwoDArray<T> &array ) { return array.getNumRows()*array.getNumCols(); }
};

} // end FACEMC namespace

#endif // end ARRAY_TESTING_POLICY_HPP

//---------------------------------------------------------------------------//
// end ArrayTestingPolicy.hpp
//---------------------------------------------------------------------------//
