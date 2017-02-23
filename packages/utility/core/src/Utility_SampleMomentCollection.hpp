//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollection.hpp
//! \author Alex Robinson
//! \brief  The sample moment collection class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_COLLECTION_HPP
#define UTILITY_SAMPLE_MOMENT_COLLECTION_HPP

// Std Lib Includes
#include <type_traits>

// FRENSIE Includes
#include "Utility_SampleMoment.hpp"

namespace Utility{

//! The sample moment collection
template<typename T, size_t... Ns>
class SampleMomentCollection
{

protected:

  //! Default constructor
  SampleMomentCollection()
  { /* ... */ }

  //! Constructor
  SampleMomentCollection( const size_t i )
  { /* ... */ }
  
  //! Constructor
  template<typename InputValueType>
  SampleMomentCollection( const size_t i,
                          const InputValueType starting_scores )
  { /* ... */ }

  //! Copy constructor
  SampleMomentCollection( const SampleMomentCollection& other_collection )
  { /* ... */ }

  //! Assignment operator
  SampleMomentCollection& operator=( const SampleMomentCollection& other_collection )
  { /* ... */ }

  //! Destructor
  virtual ~SampleMomentCollection()
  { /* ... */ }

  //! Clear the collection
  void clear()
  { /* ... */ }

  //! Resize the collection
  void resize( const size_t i ) const
  { /* ... */ }

  //! Resize and set the collection
  template<typename InputValueType>
  void resize( const size_t i, const InputValueType& starting_scores )
  { /* ... */ }

  //! Add a raw score
  void addRawScore( const size_t i, const T& raw_score )
  { /* ... */ }

  //! Add a raw score to all moments in the collection
  void addRawScore( const T& raw_score )
  { /* ... */ }
};

//! The specialization of the sample moment collection for the desired moments
template<typename T, size_t N, size_t... Ns>
class SampleMomentCollection<T,N,Ns...> : public SampleMomentCollection<T,Ns...>
{

private:

  //! The underlying container type
  typedef std::vector<typename SampleMoment<N,T>::ValueType> ContainerType;
  
public:
  
  //! The starting moment value type
  typedef typename ContainerType::value_type ValueType;
  
  //! Default constructor
  SampleMomentCollection();

  //! Constructor
  SampleMomentCollection( const size_t i );
  
  //! Constructor
  template<typename InputValueType, typename... OtherInputValueTypes>
  SampleMomentCollection( const size_t i,
                          const InputValueType& starting_score,
                          const OtherInputValueTypes&... other_starting_scores );

  //! Copy constructor
  SampleMomentCollection( const SampleMomentCollection& other_collection );

  //! Assignment operator
  SampleMomentCollection& operator=( const SampleMomentCollection& other_collection );

  //! Destructor
  virtual ~SampleMomentCollection()
  { /* ... */ }

  //! Clear the collection
  void clear();

  //! Resize the collection
  void resize( const size_t i );

  //! Resize and set the collection
  template<typename InputValueType, typename... OtherInputValueTypes>
  void resize( const size_t i,
               const InputValueType& starting_score,
               const OtherInputValueTypes&... other_starting_scores );

  //! Get the size of the collection
  size_t size() const;

  //! Get the raw scores
  const ValueType* getRawScores() const;

  //! Get the raw scores
  ValueType* getRawScores();

  //! Return the moment
  SampleMoment<N,T> getMoment( const size_t i ) const;

  //! Add a raw score
  void addRawScore( const size_t i, const T& raw_score );

  //! Add a raw score to all moments in the collection
  void addRawScore( const T& raw_score );

private:

  // The current scores
  ContainerType d_current_scores;
};

//! Get the desired moment from the collection
template<size_t N, typename T, size_t M, size_t... Ms>
inline typename std::enable_if<N==M, SampleMoment<N,T> >::type
getMoment( const SampleMomentCollection<T,M,Ms...>& collection,
           const size_t i )
{
  return collection.getMoment( i );
}

//! Get the desired moment from the collection
template<size_t N, typename T, size_t M, size_t... Ms>
inline typename std::enable_if<N!=M, SampleMoment<N,T> >::type
getMoment( const SampleMomentCollection<T,M,Ms...>& collection,
           const size_t i )
{
  return getMoment<N,T,Ms...>( collection, i );
}

//! Get the desire raw scores from the collection
template<size_t N, typename T, size_t M, size_t... Ms>
inline typename std::enable_if<N==M, const typename SampleMoment<N,T>::ValueType*>::type
getRawScores( const SampleMomentCollection<T,M,Ms...>& collection )
{
  return collection.getRawScores();
}

//! Get the desire raw scores from the collection
template<size_t N, typename T, size_t M, size_t... Ms>
inline typename std::enable_if<N!=M, const typename SampleMoment<N,T>::ValueType*>::type
getRawScores( const SampleMomentCollection<T,M,Ms...>& collection )
{
  return getRawScores<N,T,Ms...>( collection );
}

//! Get the desire raw scores from the collection
template<size_t N, typename T, size_t M, size_t... Ms>
inline typename std::enable_if<N==M, typename SampleMoment<N,T>::ValueType*>::type
getRawScores( SampleMomentCollection<T,M,Ms...>& collection )
{
  return collection.getRawScores();
}

//! Get the desire raw scores from the collection
template<size_t N, typename T, size_t M, size_t... Ms>
inline typename std::enable_if<N!=M, typename SampleMoment<N,T>::ValueType*>::type
getRawScores( SampleMomentCollection<T,M,Ms...>& collection )
{
  return getRawScores<N,T,Ms...>( collection );
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_SampleMomentCollection_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_SAMPLE_MOMENT_COLLECTION_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollection.hpp
//---------------------------------------------------------------------------//
