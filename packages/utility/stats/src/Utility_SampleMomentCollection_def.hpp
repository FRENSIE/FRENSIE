//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollection_def.hpp
//! \author Alex Robinson
//! \brief  The sample moment collection class template definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_COLLECTION_DEF_HPP
#define UTILITY_SAMPLE_MOMENT_COLLECTION_DEF_HPP

// Boost Includes
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

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

//! The default sample moment collection
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

private:

  // Make all moment collections friend
  template<typename U, size_t... Ms>
  friend class SampleMomentCollection;

  // Make the boost::serialization::access class a friend
  friend class boost::serialization::access;

  // Save the collection data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { /* ... */ }

  // Load the collection data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { /* ... */ }

  BOOST_SERIALIZATION_SPLIT_MEMBER();
};

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

// Reset the collection (sets all scores to zero)
template<typename T, size_t N, size_t... Ns>
void SampleMomentCollection<T,N,Ns...>::reset()
{
  SampleMomentCollection<T,Ns...>::reset();

  for( size_t i = 0; i < d_current_scores.size(); ++i )
    d_current_scores[i] = QuantityTraits<ValueType>::zero();
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

// Save the collection data to an archive
template<typename T, size_t N, size_t... Ns>
template<class Archive>
void SampleMomentCollection<T,N,Ns...>::save( Archive & ar, const unsigned int version ) const
{
  // Save the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local data
  std::string name = "moment_";
  name += Utility::toString( N );
  
  ar & boost::serialization::make_nvp( name.c_str(), d_current_scores );
}

// Load the collection data to an archive
template<typename T, size_t N, size_t... Ns>
template<class Archive>
void SampleMomentCollection<T,N,Ns...>::load( Archive & ar, const unsigned int version )
{
  // Load the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local data
  std::string name = "moment_";
  name += Utility::toString( N );
  
  ar & boost::serialization::make_nvp( name.c_str(), d_current_scores );
}

//! Get the scores from the collection
template<size_t N, typename T, size_t... Ms>
inline const typename SampleMoment<N,T>::ValueType*
getCurrentScores( const SampleMomentCollection<T,Ms...>& collection )
{
  return Details::SampleMomentCollectionDataExtractor<N,SampleMomentCollection<T,Ms...> >::getCurrentScores( collection );
}

//! Get the scores from the collection
template<size_t N, typename T, size_t... Ms>
inline typename SampleMoment<N,T>::ValueType* getCurrentScores( SampleMomentCollection<T,Ms...>& collection )
{
  return Details::SampleMomentCollectionDataExtractor<N,SampleMomentCollection<T,Ms...> >::getCurrentScores( collection );
}

//! Get the desired score from the collection
template<size_t N, typename T, size_t... Ms>
inline const typename SampleMoment<N,T>::ValueType&
getCurrentScore( const SampleMomentCollection<T,Ms...>& collection,
                 const size_t i )
{
  return Details::SampleMomentCollectionDataExtractor<N,SampleMomentCollection<T,Ms...> >::getCurrentScore( collection, i );
}

//! Get the desired score from the collection
template<size_t N, typename T, size_t... Ms>
inline typename SampleMoment<N,T>::ValueType&
getCurrentScore( SampleMomentCollection<T,Ms...>& collection, const size_t i )
{
  return Details::SampleMomentCollectionDataExtractor<N,SampleMomentCollection<T,Ms...> >::getCurrentScore( collection, i );
}

//! Get the desired moment from the collection
template<size_t N, typename T, size_t... Ms>
inline SampleMoment<N,T>
getMoment( const SampleMomentCollection<T,Ms...>& collection, const size_t i )
{
  return Details::SampleMomentCollectionDataExtractor<N,SampleMomentCollection<T,Ms...> >::getMoment( collection, i );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,1,2> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollection<double,1,2> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,2,1> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollection<double,2,1> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,1,2,3,4> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollection<double,1,2,3,4> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollection<double,4,3,2,1> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollection<double,4,3,2,1> );

#endif // end UTILITY_SAMPLE_MOMENT_COLLECTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollection_def.hpp
//---------------------------------------------------------------------------//
