//---------------------------------------------------------------------------//
// \file   HDF5ArrayPolicy.hpp
// \author Alex Robinson
// \brief  HDF5 Array Policy specializations
//---------------------------------------------------------------------------//

#ifndef HDF5_ARRAY_POLICY_HPP
#define HDF5_ARRAY_POLICY_HPP

// Std Lib Includes
#include <vector>
#include <cmath>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "HDF5ArrayPolicyDecl.hpp"
#include "FACEMC_Assertion.hpp"
#include "ContractException.hpp"


namespace FACEMC{

template<typename T>
struct HDF5ArrayPolicy<T,Teuchos::Array>
{
  static inline T* getRawPtr(Teuchos::Array<T> &array) { return array.getRawPtr(); }
  static inline const T* getRawPtr(const Teuchos::Array<T> &array) { return array.getRawPtr(); }
  static inline void resize(Teuchos::Array<T> &array, typename Teuchos::Array<T>::size_type n) { array.resize( n ); }
  static inline typename Teuchos::Array<T>::size_type size(const Teuchos::Array<T> &array) { return array.size(); }
};

template<typename T>
struct HDF5ArrayPolicy<T,Teuchos::ArrayRCP>
{
  static inline T* getRawPtr(Teuchos::ArrayRCP<T> &array) { return array.getRawPtr(); }
  static inline const T* getRawPtr(const Teuchos::ArrayRCP<T> &array) { return array.getRawPtr(); }
  static inline void resize(Teuchos::ArrayRCP<T> &array, typename Teuchos::ArrayRCP<T>::size_type n) { array.resize( n ); }
  static inline typename Teuchos::ArrayRCP<T>::size_type size(const Teuchos::ArrayRCP<T> &array) { return array.size(); } 
};

template<typename T>
struct HDF5ArrayPolicy<T,Teuchos::ArrayView>
{
  static inline T* getRawPtr(Teuchos::ArrayView<T> &array) { return array.getRawPtr(); }
  static inline const T* getRawPtr(const Teuchos::ArrayView<T> &array) { return array.getRawPtr(); }
  static inline void resize(Teuchos::ArrayView<T> &array, typename Teuchos::ArrayView<T>::size_type n) { /* Can't resize ArrayView */ }
  static inline typename Teuchos::ArrayView<T>::size_type size(const Teuchos::ArrayView<T> &array) { return array.size(); } 
};

template<typename T>
struct HDF5ArrayPolicy<T,Teuchos::TwoDArray>
{
  static inline T* getRawPtr(Teuchos::TwoDArray<T> &array) { return array[0].getRawPtr(); }
  static inline const T* getRawPtr(const Teuchos::TwoDArray<T> &array) { return array[0].getRawPtr(); }
  static void resize(Teuchos::TwoDArray<T> &array, typename Teuchos::TwoDArray<T>::size_type n) 
  { 
    if( array.getNumCols() == 0 )
    {
      array.resizeRows( 1 );
      array.resizeCols( n );
    }
    else
      array.resizeRows( ceil( n/array.getNumCols() ) ); 
  }
  static inline typename Teuchos::TwoDArray<T>::size_type size(const Teuchos::TwoDArray<T> &array) { return array.getNumRows()*array.getNumCols(); };
};

} // end FACEMC namespace

#endif // end HDF5_ARRAY_POLICY_HPP

//---------------------------------------------------------------------------//
// end HDF5ArrayPolicy.hpp
//---------------------------------------------------------------------------//
