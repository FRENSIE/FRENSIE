//---------------------------------------------------------------------------//
// \file   ArrayTestingPolicy.hpp
// \author Alex Robinson
// \brief  Policy specializations for running tests on arrays
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

template<typename T>
struct ArrayTestingPolicy<T,Teuchos::Array>
{
  static inline Teuchos::ArrayView<T> view( Teuchos::Array<T> &array ) { return array(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::Array<T> &array ) { return array(); }
  static inline void initialize( Teuchos::Array<T> &array, const T &data ) 
  { 
    array.clear(); 
    array.resize( 10, data );
  }
  static inline void resize( Teuchos::Array<T> &array, const typename Teuchos::Array<T>::size_type size ) { array.resize( size ); }
};

template<typename T>
struct ArrayTestingPolicy<T,Teuchos::ArrayRCP>
{
  static inline Teuchos::ArrayView<T> view( Teuchos::ArrayRCP<T> &array ) { return array(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::ArrayRCP<T> &array ) { return array(); }
  static inline void initialize( Teuchos::ArrayRCP<T> &array, const T &data )
  {
    array.clear();
    array.resize( 10, data );
  }
  static inline void resize( Teuchos::Array<T> &array, const typename Teuchos::ArrayRCP<T>::size_type size ) { array.resize( size ); }    
    
};

template<typename T>
struct ArrayTestingPolicy<T,Teuchos::ArrayView>
{
  static inline Teuchos::ArrayView<T> view( Teuchos::ArrayView<T> &array ) { return array(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::ArrayView<T> &array ) { return array(); }
  static inline void initialize( Teuchos::ArrayView<T> &array, const T &data )
  {
    Teuchos::ArrayRCP<T> dummy_array( 10, data );
    array = dummy_array();
  }
  static inline void resize( Teuchos::ArrayView<T> &array, const typename Teuchos::ArrayView<T>::size_type size )
  {
    Teuchos::Array<T> dummy_array( array );
    dummy_array.resize( size );
    array = dummy_array();
  }
};

template<typename T>
struct ArrayTestingPolicy<T,Teuchos::TwoDArray>
{
  static inline Teuchos::ArrayView<const T> view( Teuchos::TwoDArray<T> &array ) { return array.getDataArray()(); }
  static inline Teuchos::ArrayView<const T> view( const Teuchos::TwoDArray<T> &array ) { return array.getDataArray()(); }
  static inline void initialize( Teuchos::TwoDArray<T> &array, const T &data )
  {
    Teuchos::TwoDArray<T> dummy_array( 2, 5, data );
    array = dummy_array;
  }
  static inline void resize( Teuchos::TwoDArray<T> &array, const typename Teuchos::TwoDArray<T>::size_type size )
  {
    array.resizeRows( 1 );
    array.resizeCols( size );
  }
};

} // end FACEMC namespace

#endif // end ARRAY_TESTING_POLICY_HPP

//---------------------------------------------------------------------------//
// end ArrayTestingPolicy.hpp
//---------------------------------------------------------------------------//
