//---------------------------------------------------------------------------//
// \file   HDF5ArrayTraits.hpp
// \author Alex Robinson
// \brief  HDF5 Array Traits specializations
//---------------------------------------------------------------------------//

#ifndef HDF5_ARRAY_TRAITS_HPP
#define HDF5_ARRAY_TRAITS_HPP

// Std Lib Includes
#include <vector>
#include <cmath>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "HDF5ArrayTraitsDecl.hpp"
#include "FACEMC_Assertion.hpp"


namespace FACEMC{

template<typename T>
struct HDF5ArrayTraits<T,Teuchos::Array>
{
  static inline T* getRawPtr(Teuchos::Array<T> array) { return array.getRawPtr(); }
  static inline void resize(Teuchos::Array<T> array, typename Teuchos::Array<T>::size_type n) { array.resize( n ); }
  static inline typename Teuchos::Array<T>::size_type size(Teuchos::Array<T> array) { return array.size(); }
};

template<typename T>
struct HDF5ArrayTraits<T,Teuchos::ArrayRCP>
{
  static inline T* getRawPtr(Teuchos::ArrayRCP<T> array) { return array.getRawPtr(); }
  static inline void resize(Teuchos::ArrayRCP<T> array, typename Teuchos::ArrayRCP<T>::size_type n) { array.resize( n ); }
  static inline typename Teuchos::ArrayRCP<T>::size_type size(Teuchos::ArrayRCP<T> array) { return array.size(); } 
};

template<typename T>
struct HDF5ArrayTraits<T,Teuchos::ArrayView>
{
  static inline T* getRawPtr(Teuchos::ArrayView<T> array) { return array.getRawPtr(); }
  static inline void resize(Teuchos::ArrayView<T> array, typename Teuchos::ArrayView<T>::size_type n) { array.resize( n ); }
  static inline typename Teuchos::ArrayView<T>::size_type size(Teuchos::ArrayView<T> array) { return array.size(); } 
};

template<typename T>
struct HDF5ArrayTraits<T,Teuchos::TwoDArray>
{
  static inline T* getRawPtr(Teuchos::TwoDArray<T> array) { return array[0].getRawPtr(); }
  // Assumes that the number of columns is > 0
  static void resize(Teuchos::TwoDArray<T> array, typename Teuchos::TwoDArray<T>::size_type n) 
  { 
    FACEMC_ASSERT_ALWAYS( array.getNumCols() > 0 );
    array.resizeRows( ceil( n/array.getNumCols() ) ); 
  }
  static inline typename Teuchos::TwoDArray<T>::size_type size(Teuchos::TwoDArray<T> array) { return array.getNumRows()*array.getNumCols(); };
};

} // end FACEMC namespace

#endif // end HDF5_ARRAY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end HDF5ArrayTraits.hpp
//---------------------------------------------------------------------------//
