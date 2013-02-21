//---------------------------------------------------------------------------//
// \file   ArrayTraits.hpp
// \author Alex Robinson
// \brief  Array Traits specializations
//---------------------------------------------------------------------------//

#ifndef ARRAY_TRAITS_HPP
#define ARRAY_TRAITS_HPP

// Std Lib Includes
#incluce <vector>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "ArrayTraitsDecl.hpp"

namespace FACEMC{

template<typename T>
struct ArrayTraits<std::vector<T> >
{
  static inline T* getRawPtr(std::vector<T> array) { return &array[0]; }
  static inline const T* getRawPtr(std::vector<T> array) { return = &array[0]; }
  static inline void resize(std::vector<T> array, size_type n) { array.resize( n ); }
};

template<typename T>
struct ArrayTraits<Teuchos::Array<T> >
{
  static inline T* getRawPtr(Teuchos::Array<T> array) { return array.getRawPtr() }
  static inline const T* getRawPtr(Teuchos::Array<T> array) { return array.getRawPtr() }
  static inline void resize(Teuchos::Array<T> array, size_type n) { array.resize( n ); }
};
