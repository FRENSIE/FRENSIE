//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollectionSnapshots.hpp
//! \author Alex Robinson
//! \brief  The sample moment collection snapshots declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_HPP
#define UTILITY_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_HPP

// Std Lib Includes
#include <type_traits>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/access.hpp>

// FRENSIE Includes
#include "Utility_SampleMomentCollection.hpp"
#include "Utility_List.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Utility{

namespace Details{
  
//! The sample moment collection snapshots data extractor class
template<size_t N, typename T, typename Enabled = void>
struct SampleMomentCollectionSnapshotsDataExtractor;
  
} // end Details namespace

/*! The sample moment collection snapshots
 * \details This represents the empty collection. It cannot be instantiated
 * directly - only the non-empty collections can instantiate it. Note that
 * this class is a variadic template class and is designed in a very similar
 * way to the std::tuple class. 
 */
template<typename T, template<typename,typename...> class SnapshotContainer, size_t... Ns>
class SampleMomentCollectionSnapshots;

//! The specialization of the sample moment collection with snapshots for the desired moments
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
class SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...> : public SampleMomentCollectionSnapshots<T,SnapshotContainer,Ns...>
{
  // The base type
  typedef SampleMomentCollectionSnapshots<T,SnapshotContainer,Ns...> BaseType;

public:

  // The snapshot moment container type
  typedef SnapshotContainer<typename Utility::SampleMoment<N,T>::ValueType> MomentSnapshotContainerType;

  //! The snapshot indices container type
  typedef SnapshotContainer<uint64_t> SummationIndexContainerType;

  //! The snapshot sampling time container type
  typedef SnapshotContainer<double> SamplingTimeContainerType;

  //! The moment value type
  typedef typename MomentSnapshotContainerType::value_type MomentValueType;

  //! The summation index type
  typedef typename SummationIndexContainerType::value_type SummationIndexType;

  //! Default Constructor
  SampleMomentCollectionSnapshots();

  //! Constructor
  SampleMomentCollectionSnapshots( const size_t i );

  //! Copy Constructor
  SampleMomentCollectionSnapshots( const SampleMomentCollectionSnapshots& other_collection_snapshots );

  //! Assignment Operator
  SampleMomentCollectionSnapshots& operator=( const SampleMomentCollectionSnapshots& other_collection_snapshots );

  //! Destructor
  virtual ~SampleMomentCollectionSnapshots()
  { /* ... */ }

  //! Clear the collection snapshots
  void clear();

  //! Reset the collection snapshots
  void reset();

  //! Resize the collection snapshots (number of bins)
  void resize( const size_t i );

  //! Get the size of the collection (number of bins)
  size_t size() const;

  //! Get the number of snapshots
  size_t getNumberOfSnapshots() const;

  //! Take a snapshot of a sample moment collection
  void takeSnapshot( const uint64_t number_of_additional_samples,
                     const double sampling_time_from_last_snapshot,
                     const SampleMomentCollection<T,N,Ns...>& collection );

  //! Merge the snapshots
  void mergeSnapshots( const SampleMomentCollectionSnapshots& collection );

  //! Get the snapshot indices (summation indices)
  const SummationIndexContainerType& getSnapshotIndices() const;

  //! Get the snapshot sampling times (sampling times)
  const SamplingTimeContainerType& getSnapshotSamplingTimes() const;

private:

  // Make the data extractor class a friend
  template<size_t M, typename Collection, typename Enabled>
  friend class Details::SampleMomentCollectionSnapshotsDataExtractor;

  // Make all moment collections friends
  template<typename U, template<typename,typename...> class V, size_t... Ms>
  friend class SampleMomentCollectionSnapshots;

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
  std::vector<MomentSnapshotContainerType> d_score_snapshots;
};

//! Get the moment snapshots from the collection
template<size_t N, typename T, template<typename,typename...> class Container, size_t... Ms>
const Container<typename Utility::SampleMoment<N,T>::ValueType>& getScoreSnapshots(
                      const SampleMomentCollectionSnapshots<T,Container,Ms...>&
                      collection_snapshots,
                      const size_t i );

//! Get a score snapshot from the collection
template<size_t N, typename T, template<typename,typename...> class Container, size_t... Ms>
const typename SampleMoment<N,T>::ValueType& getScoreSnapshot(
                      const SampleMomentCollectionSnapshots<T,Container,Ms...>&
                      collection_snapshots,
                      const size_t i,
                      const size_t snapshot_index );

//! Get a moment snapshot from the collection
template<size_t N, typename T, template<typename,typename...> class Container, size_t... Ms>
SampleMoment<N,T> getMomentSnapshot(
                      const SampleMomentCollectionSnapshots<T,Container,Ms...>&
                      collection_snapshots,
                      const size_t i,
                      const size_t snapshot_index );
  
} // end Utility namespace

#define BOOST_SERIALIZATION_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_VERSION( VERSION ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL( \
    SampleMomentCollectionSnapshots, Utility, VERSION, \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename T, template<typename,typename...> class Container, size_t... Ns ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( T, Container, Ns... ) )

BOOST_SERIALIZATION_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_SampleMomentCollectionSnapshots_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollectionSnapshots.hpp
//---------------------------------------------------------------------------//
