//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollection_def.hpp
//! \author Alex Robinson
//! \brief  The sample moment collection class template definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_COLLECTION_DEF_HPP
#define UTILITY_SAMPLE_MOMENT_COLLECTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
template<typename T, size_t N, size_t... Ns>
SampleMomentCollection<T,N,Ns...>::SampleMomentCollection()
  : SampleMomentCollection<T,Ns...>()
{ /* ... */ }

// Constructor
template<typename T, size_t N, size_t... Ns>
SampleMomentCollection<T,N,Ns...>::SampleMomentCollection( const size_t i )
  : SampleMomentCollection<T,Ns...>( i ),
    d_current_scores( i, Utility::QuantityTraits<ValueType>::zero() )
{ /* ... */ }

// Constructor
template<typename T, size_t N, size_t... Ns>
template<typename InputValueType, typename... OtherInputValueTypes>
SampleMomentCollection<T,N,Ns...>::SampleMomentCollection(
                         const size_t i,
                         const InputValueType& starting_score,
                         const OtherInputValueTypes&... other_starting_scores )
  : SampleMomentCollection<T,Ns...>( i, other_starting_scores... ),
    d_current_scores( i, starting_score )
{ /* ... */ }

// Copy constructor
template<typename T, size_t N, size_t... Ns>
SampleMomentCollection<T,N,Ns...>::SampleMomentCollection(
                               const SampleMomentCollection& other_collection )
  : SampleMomentCollection<T,Ns...>( other_collection ),
    d_current_scores( other_collection.d_current_scores )
{ /* ... */ }

// Assignment operator
template<typename T, size_t N, size_t... Ns>
SampleMomentCollection<T,N,Ns...>&
SampleMomentCollection<T,N,Ns...>::operator=(
                               const SampleMomentCollection& other_collection )
{
  SampleMomentCollection<T,Ns...>::operator=( other_collection );
  
  if( this != &other_collection )
    d_current_scores = other_collection.d_current_scores;

  return *this;
}

// Clear the collection
template<typename T, size_t N, size_t... Ns>
void SampleMomentCollection<T,N,Ns...>::clear()
{
  SampleMomentCollection<T,Ns...>::clear();
  
  d_current_scores.clear();
} 

// Resize the collection
template<typename T, size_t N, size_t... Ns>
void SampleMomentCollection<T,N,Ns...>::resize( const size_t i )
{
  SampleMomentCollection<T,Ns...>::resize( i );
  
  d_current_scores.resize( i );
}

// Resize and set the collection
template<typename T, size_t N, size_t... Ns>
template<typename InputValueType, typename... OtherInputValueTypes>
void SampleMomentCollection<T,N,Ns...>::resize(
                         const size_t i,
                         const InputValueType& starting_score,
                         const OtherInputValueTypes&... other_starting_scores )
{
  SampleMomentCollection<T,Ns...>::resize( i, other_starting_scores... );

  d_current_scores.resize( i, starting_score );
}

// Get the size of the collection
template<typename T, size_t N, size_t... Ns>
size_t SampleMomentCollection<T,N,Ns...>::size() const
{
  return d_current_scores.size();
}

// Get the raw scores
template<typename T, size_t N, size_t... Ns>
auto SampleMomentCollection<T,N,Ns...>::getRawScores() const -> const ValueType*
{
  return &d_current_scores[0];
}

// Get the raw scores
template<typename T, size_t N, size_t... Ns>
auto SampleMomentCollection<T,N,Ns...>::getRawScores() -> ValueType*
{
  return &d_current_scores[0];
}

// Return the moment
/*! \details The returned moment is only a copy of the moment in the 
 * collection.
 */
template<typename T, size_t N, size_t... Ns>
SampleMoment<N,T> SampleMomentCollection<T,N,Ns...>::getMoment(
                                                         const size_t i ) const
{
  // Make sure the the index is valid
  testPrecondition( i < this->size() );
  
  return SampleMoment<N,T>( d_current_scores[i] );
}

// Add a raw score
template<typename T, size_t N, size_t... Ns>
void SampleMomentCollection<T,N,Ns...>::addRawScore( const size_t i,
                                                     const T& raw_score )
{
  // Make sure the the index is valid
  testPrecondition( i < this->size() );

  SampleMomentCollection<T,Ns...>::addRawScore( i, raw_score );

  d_current_scores[i] += SampleMoment<N,T>::processRawScore( raw_score );
}

// Add a raw score to all moments in the collection
template<typename T, size_t N, size_t... Ns>
void SampleMomentCollection<T,N,Ns...>::addRawScore( const T& raw_score )
{
  SampleMomentCollection<T,Ns...>::addRawScore( raw_score );
  
  ValueType processed_score = SampleMoment<N,T>::processRawScore( raw_score );
  
  for( size_t i = 0; i < d_current_scores.size(); ++i )
    d_current_scores[i] += processed_score;
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SampleMomentCollection<double,1,2> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( SampleMomentCollection<double,1,2,3,4> );
  
} // end Utility namespace

#endif // end UTILITY_SAMPLE_MOMENT_COLLECTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollection_def.hpp
//---------------------------------------------------------------------------//
