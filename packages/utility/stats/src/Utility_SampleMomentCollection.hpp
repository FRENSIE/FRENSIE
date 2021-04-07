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

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/access.hpp>

// FRENSIE Includes
#include "Utility_SampleMoment.hpp"
#include "Utility_Vector.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Utility{

namespace Details{

//! The sample moment collection data extractor class
template<size_t N, typename T, typename Enabled = void>
struct SampleMomentCollectionDataExtractor;

} // end Details namespace

/*! The sample moment collection
 * \details This represents the empty collection. It cannot be instantiated
 * directly - only the non-empty collections can instantiate it. Note that
 * this class is a variadic template class and is designed in a very similar
 * way to the std::tuple class. The
 * Utility::Details::SampleMomentCollectionDataExtractor class is used to
 * extract the data relating to a specific moment from the collection. This
 * extractor class should never be used directly. Instead the standalone
 * getter methods should be used. Properties relating to the entire collection
 * (e.g. the collection size) and not a specific moment can be accessed
 * directly.
 */
template<typename T, size_t... Ns>
class SampleMomentCollection;

//! The specialization of the sample moment collection for the desired moments
template<typename T, size_t N, size_t... Ns>
class SampleMomentCollection<T,N,Ns...> : public SampleMomentCollection<T,Ns...>
{
  // The base type
  typedef SampleMomentCollection<T,Ns...> BaseType;
  
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

  // Make all moment collections friend
  template<typename U, size_t... Ms>
  friend class SampleMomentCollection;

  // Make the boost::serialization::access class a friend
  friend class boost::serialization::access;

  // Save the collection data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the collection data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // The current scores
  ContainerType d_current_scores;
};

//! Get the scores from the collection
template<size_t N, typename T, size_t... Ms>
const typename SampleMoment<N,T>::ValueType* getCurrentScores( const SampleMomentCollection<T,Ms...>& collection );

//! Get the scores from the collection
template<size_t N, typename T, size_t... Ms>
typename SampleMoment<N,T>::ValueType* getCurrentScores( SampleMomentCollection<T,Ms...>& collection );

//! Get the desired score from the collection
template<size_t N, typename T, size_t... Ms>
const typename SampleMoment<N,T>::ValueType&
getCurrentScore( const SampleMomentCollection<T,Ms...>& collection,
                 const size_t i );

//! Get the desired score from the collection
template<size_t N, typename T, size_t... Ms>
typename SampleMoment<N,T>::ValueType&
getCurrentScore( SampleMomentCollection<T,Ms...>& collection, const size_t i );

//! Get the desired moment from the collection
template<size_t N, typename T, size_t... Ms>
SampleMoment<N,T> getMoment( const SampleMomentCollection<T,Ms...>& collection,
                             const size_t i );

} // end Utility namespace

#define BOOST_SERIALIZATION_SAMPLE_MOMENT_COLLECTION_VERSION( VERSION ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    SampleMomentCollection, Utility, VERSION,                             \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, size_t... Ns ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, Ns... ) )

BOOST_SERIALIZATION_SAMPLE_MOMENT_COLLECTION_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_SampleMomentCollection_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_SAMPLE_MOMENT_COLLECTION_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollection.hpp
//---------------------------------------------------------------------------//
