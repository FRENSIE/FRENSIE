//---------------------------------------------------------------------------//
// \file    TypeTestingPolicy.hpp
// \author  Alex Robinson
// \brief   Policy specializations for testing basic types
//---------------------------------------------------------------------------//

#ifndef TYPE_TESTING_POLICY_HPP
#define TYPE_TESTING_POLICY_HPP

// FACEMC Includes
#include "TypeTestingPolicyDecl.hpp"
#include "Tuple.hpp"

namespace FACEMC{

template<>
struct TypeTestingPolicy<double>
{
  static inline void initialize( double &data ) { data = 3.14159265359; }
  static inline void zero( double &data ) { data = 0.0; }
};

template<>
struct TypeTestingPolicy<unsigned int>
{
  static inline void initialize( unsigned int &data ) { data = 511u; }
  static inline void zero( unsigned int &data ) { data = 0u; }
};

template<typename T, typename T2>
struct TypeTestingPolicy<FACEMC::Pair<T,T2> >
{
  static inline void initialize( FACEMC::Pair<T,T2> &data )
  {
    TypeTestingPolicy<T>::initialize( data.first );
    TypeTestingPolicy<T2>::initialize( data.second );
  }
  static inline void zero( FACEMC::Pair<T,T2> &data )
  {
    TypeTestingPolicy<T>::zero( data.first );
    TypeTestingPolicy<T2>::zero( data.second );
  }
};

template<typename T, typename T2, typename T3>
struct TypeTestingPolicy<FACEMC::Trip<T,T2,T3> >
{
  static inline void initialize( FACEMC::Trip<T,T2,T3> &data )
  {
    TypeTestingPolicy<T>::initialize( data.first );
    TypeTestingPolicy<T2>::initialize( data.second );
    TypeTestingPolicy<T3>::initialize( data.third );
  }
  static inline void zero( FACEMC::Trip<T,T2,T3> &data )
  {
    TypeTestingPolicy<T>::zero( data.first );
    TypeTestingPolicy<T2>::zero( data.second );
    TypeTestingPolicy<T3>::zero( data.third );
  }
};

template<typename T, typename T2, typename T3, typename T4>
struct TypeTestingPolicy<FACEMC::Quad<T,T2,T3,T4> >
{
  static inline void initialize( FACEMC::Quad<T,T2,T3,T4> &data )
  {
    TypeTestingPolicy<T>::initialize( data.first );
    TypeTestingPolicy<T2>::initialize( data.second );
    TypeTestingPolicy<T3>::initialize( data.third );
    TypeTestingPolicy<T4>::initialize( data.fourth );
  } 
  static inline void zero( FACEMC::Quad<T,T2,T3,T4> &data )
  {
    TypeTestingPolicy<T>::zero( data.first );
    TypeTestingPolicy<T2>::zero( data.second );
    TypeTestingPolicy<T3>::zero( data.third );
    TypeTestingPolicy<T4>::zero( data.fourth );
  }
};

} // end FACEMC namespace

#endif // end TYPE_TESTING_POLICY_HPP

//---------------------------------------------------------------------------//
// end TypeTestingPolicy.hpp
//---------------------------------------------------------------------------//
