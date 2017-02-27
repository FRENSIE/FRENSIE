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

namespace Details{

//! The sample moment collection data extractor class
template<size_t N, typename T, typename Enabled = void>
struct SampleMomentCollectionDataExtractor
{ /* ... */ };
  
} // end Details namespace
  
/*! The sample moment collection
 * \details This represents the empty collection. It cannot be instantiated
 * directly - only the non-empty collections can instantiate it. Note that
 * this class is a variadic template class and it designed in a very similar
 * way to the std::tuple class. The 
 * Utility::Details::SampleMomentCollectionDataExtractor class is used to
 * extract the data relating to a specific moment from the collection. This
 * extractor class should never be used directly. Instead the standalone
 * getter methods should be used. Properties relating to the entire collection
 * (e.g. the collection size) and not a specific moment can be accessed 
 * direclty.
 */
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

  //! Reset the collection (sets all scores to zero)
  void reset()
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

  // The underlying container type
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

  //! Reset the collection (sets all scores to zero)
  void reset();

  //! Resize the collection
  void resize( const size_t i );

  //! Resize and set the collection
  template<typename InputValueType, typename... OtherInputValueTypes>
  void resize( const size_t i,
               const InputValueType& starting_score,
               const OtherInputValueTypes&... other_starting_scores );

  //! Get the size of the collection
  size_t size() const;

  //! Add a raw score
  void addRawScore( const size_t i, const T& raw_score );

  //! Add a raw score to all moments in the collection
  void addRawScore( const T& raw_score );

private:

  // Make the data extractor class a friend
  template<size_t M, typename Collection, typename Enabled>
  friend class Details::SampleMomentCollectionDataExtractor;

  // The current scores
  ContainerType d_current_scores;
};

namespace Details{

/*! \brief Specialization of the sample moment collection data extractor class
 * for const types
 */
template<size_t N, typename T>
struct SampleMomentCollectionDataExtractor<N,const T> : public SampleMomentCollectionDataExtractor<N,T>
{ /* ... */ };

/*! \brief Specialization of the sample moment collection data extractor class
 * for volatile types
 */
template<size_t N, typename T>
struct SampleMomentCollectionDataExtractor<N,volatile T> : public SampleMomentCollectionDataExtractor<N,T>
{ /* ... */ };

/*! \brief Specialization of the sample moment collection data extractor class
 * for const volatile types
 */
template<size_t N, typename T>
struct SampleMomentCollectionDataExtractor<N,const volatile T> : public SampleMomentCollectionDataExtractor<N,T>
{ /* ... */ };

/*! \brief Specialization of sample moment collection data extractor class
 * for SampleMomentCollection types
 */
template<size_t N, typename T, size_t M, size_t... Ms>
struct SampleMomentCollectionDataExtractor<N,SampleMomentCollection<T,M,Ms...>,typename std::enable_if<N==M>::type>
{
  //! The collection type
  typedef Utility::SampleMomentCollection<T,M,Ms...> CollectionType;

  //! The sample moment type
  typedef Utility::SampleMoment<M,T> MomentType;

  //! The value type
  typedef typename MomentType::ValueType ValueType;
  
  //! Get the current scores
  static inline const ValueType* getCurrentScores(
                                             const CollectionType& collection )
  { return &collection.d_current_scores[0]; }

  //! Get the current scores
  static inline ValueType* getCurrentScores( CollectionType& collection )
  { return &collection.d_current_scores[0]; }

  //! Get the current score
  static inline const ValueType& getCurrentScore(
                                              const CollectionType& collection,
                                              const size_t i )
  { return collection.d_current_scores[i]; }

  //! Get the current score
  static inline ValueType& getCurrentScore( CollectionType& collection,
                                            const size_t i )
  { return collection.d_current_scores[i]; }

  //! Return the moment
  static inline MomentType getMoment( const CollectionType& collection,
                                      const size_t i )
  { return MomentType( collection.d_current_scores[i] ); }
};

/*! \brief Specialization of sample moment collection data extractor class
 * for SampleMomentCollection types
 */
template<size_t N, typename T, size_t M, size_t... Ms>
struct SampleMomentCollectionDataExtractor<N,SampleMomentCollection<T,M,Ms...>,typename std::enable_if<N!=M>::type>
{
  //! The collection type
  typedef Utility::SampleMomentCollection<T,M,Ms...> CollectionType;

  //! The moment type
  typedef SampleMoment<N,T> MomentType;

  //! The value type
  typedef typename MomentType::ValueType ValueType;

  //! The base collection type
  typedef Utility::SampleMomentCollection<T,Ms...> BaseCollectionType;
  
  //! Get the current scores
  static inline const ValueType* getCurrentScores(
                                             const CollectionType& collection )
  { return SampleMomentCollectionDataExtractor<N,BaseCollectionType>::getCurrentScores( collection ); }

  //! Get the current scores
  static inline ValueType* getCurrentScores( CollectionType& collection )
  { return SampleMomentCollectionDataExtractor<N,BaseCollectionType>::getCurrentScores( collection ); }

  //! Get the current score
  static inline const ValueType& getCurrentScore(
                                              const CollectionType& collection,
                                              const size_t i )
  { return SampleMomentCollectionDataExtractor<N,BaseCollectionType>::getCurrentScore( collection, i ); }

  //! Get the current score
  static inline ValueType& getCurrentScore( CollectionType& collection,
                                            const size_t i )
  { return SampleMomentCollectionDataExtractor<N,BaseCollectionType>::getCurrentScore( collection, i ); }

  //! Return the moment
  static inline MomentType getMoment( const CollectionType& collection,
                                      const size_t i )
  { return SampleMomentCollectionDataExtractor<N,BaseCollectionType>::getMoment( collection, i ); }
};

} // end Details namespace

//! Get the scores from the collection
template<size_t N, typename T>
inline const typename Details::SampleMomentCollectionDataExtractor<N,T>::ValueType*
getCurrentScores( const T& collection )
{
  return Details::SampleMomentCollectionDataExtractor<N,T>::getCurrentScores( collection );
}

//! Get the scores from the collection
template<size_t N, typename T>
inline typename Details::SampleMomentCollectionDataExtractor<N,T>::ValueType*
getCurrentScores( T& collection )
{
  return Details::SampleMomentCollectionDataExtractor<N,T>::getCurrentScores( collection );
}

//! Get the desired score from the collection
template<size_t N, typename T>
inline const typename Details::SampleMomentCollectionDataExtractor<N,T>::ValueType&
getCurrentScore( const T& collection, const size_t i )
{
  return Details::SampleMomentCollectionDataExtractor<N,T>::getCurrentScore( collection, i );
}

//! Get the desired score from the collection
template<size_t N, typename T>
inline typename Details::SampleMomentCollectionDataExtractor<N,T>::ValueType&
getCurrentScore( T& collection, const size_t i )
{
  return Details::SampleMomentCollectionDataExtractor<N,T>::getCurrentScore( collection, i );
}

//! Get the desired moment from the collection
template<size_t N, typename T >
inline typename Details::SampleMomentCollectionDataExtractor<N,T>::MomentType
getMoment( const T& collection, const size_t i )
{
  return Details::SampleMomentCollectionDataExtractor<N,T>::getMoment( collection, i );
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
