//---------------------------------------------------------------------------//
//!
//! \file   Utility_SampleMomentCollectionSnapshots_def.hpp
//! \author Alex Robinson
//! \brief  The sample moment collection snapshots definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_DEF_HPP
#define UTILITY_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_DEF_HPP

// Std Lib Includes
#include <iterator>

// Boost Includes
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

namespace Details{

/*! \brief Specialization of the sample moment collection snapshots data
 * extractor class for const types
 */
template<size_t N, typename T>
struct SampleMomentCollectionSnapshotsDataExtractor<N,const T> : public SampleMomentCollectionSnapshotsDataExtractor<N,T>
{ /* ... */ };

/*! \brief Specialization of the sample moment collection snapshots data
 * extractor class for volatile types
 */
template<size_t N, typename T>
struct SampleMomentCollectionSnapshotsDataExtractor<N,volatile T> : public SampleMomentCollectionSnapshotsDataExtractor<N,T>
{ /* ... */ };

/*! \brief Specialization of the sample moment collection snapshots data
 * extractor class for const volatile types
 */
template<size_t N, typename T>
struct SampleMomentCollectionSnapshotsDataExtractor<N,const volatile T> : public SampleMomentCollectionSnapshotsDataExtractor<N,T>
{ /* ... */ };

/*! \brief Specialization of sample moment collection snapshots data 
 * extractor class for SampleMomemtCollectionSnapshots types
 */
template<size_t N, typename T, template<typename,typename...> class Container, size_t M, size_t... Ms>
struct SampleMomentCollectionSnapshotsDataExtractor<N,SampleMomentCollectionSnapshots<T,Container,M,Ms...>,typename std::enable_if<N==M>::type>
{
  //! This type
  typedef SampleMomentCollectionSnapshotsDataExtractor<N,SampleMomentCollectionSnapshots<T,Container,M,Ms...>,typename std::enable_if<N==M>::type> ThisType;
  
  //! The collection snapshots type
  typedef Utility::SampleMomentCollectionSnapshots<T,Container,M,Ms...> CollectionSnapshotsType;

  //! The container type
  typedef Container<typename Utility::SampleMoment<M,T>::ValueType> ContainerType;

  //! The sample moment type
  typedef Utility::SampleMoment<M,T> MomentType;

  //! The value type
  typedef typename MomentType::ValueType ValueType;

  //! Get the moment snapshots from the collection
  static inline const ContainerType& getScoreSnapshots(
                                     const CollectionSnapshotsType& collection,
                                     const size_t i )
  { return collection.d_score_snapshots[i]; }

  //! Get the score snapshot from the collection
  static inline const ValueType& getScoreSnapshot(
                                     const CollectionSnapshotsType& collection,
                                     const size_t i,
                                     const size_t snapshot_index )
  {
    auto score_snapshot_it = collection.d_score_snapshots[i].begin();
    std::advance( score_snapshot_it, snapshot_index );

    return *score_snapshot_it;
  }
  
  //! Get the moment snapshot from the collection
  static inline MomentType getMomentSnapshot(
                                     const CollectionSnapshotsType& collection,
                                     const size_t i,
                                     const size_t snapshot_index )
  { return MomentType( ThisType::getScoreSnapshot(collection, i, snapshot_index) ); }
};

/*! \brief Specialization of sample moment collection snapshots data 
 * extractor class for SampleMomemtCollectionSnapshots types
 */
template<size_t N, typename T, template<typename,typename...> class Container, size_t M, size_t... Ms>
struct SampleMomentCollectionSnapshotsDataExtractor<N,SampleMomentCollectionSnapshots<T,Container,M,Ms...>,typename std::enable_if<N!=M>::type>
{
  //! This type
  typedef SampleMomentCollectionSnapshotsDataExtractor<N,SampleMomentCollectionSnapshots<T,Container,M,Ms...>,typename std::enable_if<N!=M>::type> ThisType;
  
  //! The collection snapshots type
  typedef Utility::SampleMomentCollectionSnapshots<T,Container,M,Ms...> CollectionSnapshotsType;

  //! The base collection type
  typedef Utility::SampleMomentCollectionSnapshots<T,Container,Ms...> BaseCollectionSnapshotsType;

  //! The container type
  typedef Container<typename Utility::SampleMoment<N,T>::ValueType> ContainerType;

  //! The sample moment type
  typedef Utility::SampleMoment<N,T> MomentType;

  //! The value type
  typedef typename MomentType::ValueType ValueType;

  //! Get the moment snapshots from the collection
  static inline const ContainerType& getScoreSnapshots(
                                     const CollectionSnapshotsType& collection,
                                     const size_t i )
  { return SampleMomentCollectionSnapshotsDataExtractor<N,BaseCollectionSnapshotsType>::getScoreSnapshots( collection, i ); }

  //! Get the score snapshot from the collection
  static inline const ValueType& getScoreSnapshot(
                                     const CollectionSnapshotsType& collection,
                                     const size_t i,
                                     const size_t snapshot_index )
  { return SampleMomentCollectionSnapshotsDataExtractor<N,BaseCollectionSnapshotsType>::getScoreSnapshot( collection, i, snapshot_index ); }
  
  //! Get the moment snapshot from the collection
  static inline MomentType getMomentSnapshot(
                                     const CollectionSnapshotsType& collection,
                                     const size_t i,
                                     const size_t snapshot_index )
  { return SampleMomentCollectionSnapshotsDataExtractor<N,BaseCollectionSnapshotsType>::getMomentSnapshot( collection, i, snapshot_index ); }
};
  
} // end Details namespace

// The sample moment collection snapshots (default)
template<typename T, template<typename,typename...> class SnapshotContainer, size_t... Ns>
class SampleMomentCollectionSnapshots
{

public:

  //! The snapshot indices container type
  typedef SnapshotContainer<uint64_t> SummationIndexContainerType;

  //! The snapshot sampling time container type
  typedef SnapshotContainer<double> SamplingTimeContainerType;

  //! The summation index type
  typedef typename SummationIndexContainerType::value_type SummationIndexType;

  //! Default Constructor
  SampleMomentCollectionSnapshots()
  { /* ... */ }

  //! Constructor
  SampleMomentCollectionSnapshots( const size_t i )
  { /* ... */ }

  //! Copy Constructor
  SampleMomentCollectionSnapshots( const SampleMomentCollectionSnapshots& other_collection_snapshots )
    : d_snapshot_indices( other_collection_snapshots.d_snapshot_indices ),
      d_snapshot_sampling_times( other_collection_snapshots.d_snapshot_sampling_times )
  { /* ... */ }

  //! Assignment Operator
  SampleMomentCollectionSnapshots& operator=( const SampleMomentCollectionSnapshots& other_collection_snapshots )
  {
    if( this != &other_collection_snapshots )
    {
      d_snapshot_indices = other_collection_snapshots.d_snapshot_indices;
      d_snapshot_sampling_times = other_collection_snapshots.d_snapshot_sampling_times;
    }

    return *this;
  }

  //! Destructor
  virtual ~SampleMomentCollectionSnapshots()
  { /* ... */ }

  //! Clear the collection snapshots
  void clear()
  {
    d_snapshot_indices.clear();
    d_snapshot_sampling_times.clear();
  }

  //! Reset the collection snapshots
  void reset()
  {
    d_snapshot_indices.clear();
    d_snapshot_sampling_times.clear();
  }

  //! Resize the collection snapshots (number of bins)
  void resize( const size_t i )
  { /* ... */ }

  //! Get the size of the collection (number of bins)
  size_t size() const
  { /* ... */ }

  //! Get the number of snapshots
  size_t getNumberOfSnapshots() const
  { return d_snapshot_indices.size(); }

  //! Take a snapshot of a sample moment collection
  void takeSnapshot( const uint64_t number_of_additional_samples,
                     const double sampling_time_from_last_snapshot,
                     const SampleMomentCollection<T,Ns...>& )
  {
    uint64_t summation_index = number_of_additional_samples;
    double sampling_time = sampling_time_from_last_snapshot;
    
    if( !d_snapshot_indices.empty() )
    {
      summation_index += d_snapshot_indices.back();
      sampling_time += d_snapshot_sampling_times.back();
    }

    d_snapshot_indices.push_back( summation_index );
    d_snapshot_sampling_times.push_back( sampling_time );
  }

  //! Merge the snapshots
  void mergeSnapshots( const SampleMomentCollectionSnapshots& collection )
  {
    const typename SummationIndexContainerType::value_type& max_summation_index =
      d_snapshot_indices.back();
    
    for( auto&& other_summation_index : collection.d_snapshot_indices )
      d_snapshot_indices.push_back( max_summation_index + other_summation_index );

    const typename SamplingTimeContainerType::value_type& max_sampling_time =
      d_snapshot_sampling_times.back();

    for( auto&& other_sampling_times : collection.d_snapshot_sampling_times )
      d_snapshot_sampling_times.push_back( max_sampling_time + other_sampling_times );
  }

  //! Get the snapshot indices (summation indices)
  const SummationIndexContainerType& getSnapshotIndices() const
  { return d_snapshot_indices; }

  //! Get the snapshot sampling times (sampling times)
  const SamplingTimeContainerType& getSnapshotSamplingTimes() const
  { return d_snapshot_sampling_times; }

private:

  // Make all moment collections friends
  template<typename U, template<typename,typename...> class V, size_t... Ms>
  friend class SampleMomentCollectionSnapshots;

  // Make the boost::serialization::access class a friend
  friend class boost::serialization::access;

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Save the collection data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  {
    ar & BOOST_SERIALIZATION_NVP( d_snapshot_indices );
    ar & BOOST_SERIALIZATION_NVP( d_snapshot_sampling_times );
  }

  // Load the collection data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_NVP( d_snapshot_indices );
    ar & BOOST_SERIALIZATION_NVP( d_snapshot_sampling_times );
  }

  // The snapshot indices
  SummationIndexContainerType d_snapshot_indices;

  // The snapshot sampling times
  SamplingTimeContainerType d_snapshot_sampling_times;
};

// Default Constructor
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::SampleMomentCollectionSnapshots()
  : BaseType()
{ /* ... */ }

// Constructor
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::SampleMomentCollectionSnapshots( const size_t i )
  : BaseType( i ),
    d_score_snapshots( i )
{ /* ... */ }

// Copy Constructor
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::SampleMomentCollectionSnapshots( const SampleMomentCollectionSnapshots& other_collection_snapshots )
  : BaseType( other_collection_snapshots ),
    d_score_snapshots( other_collection_snapshots.d_score_snapshots )
{ /* ... */ }

// Assignment Operator
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>& SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::operator=( const SampleMomentCollectionSnapshots& other_collection_snapshots )
{
  BaseType::operator=( other_collection_snapshots );
  
  if( this != &other_collection_snapshots )
    d_score_snapshots = other_collection_snapshots.d_score_snapshots;

  return *this;
}

// Clear the collection snapshots
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
void SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::clear()
{
  BaseType::clear();
  
  d_score_snapshots.clear();
}

// Reset the collection snapshots
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
void SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::reset()
{
  BaseType::reset();
  
  for( auto&& snapshot_container : d_score_snapshots )
    snapshot_container.clear();
}

// Resize the collection snapshots (number of bins)
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
void SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::resize( const size_t i )
{
  BaseType::resize( i );

  d_score_snapshots.resize( i );
}

// Get the size of the collection (number of bins)
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
size_t SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::size() const
{
  return d_score_snapshots.size();
}

// Get the number of snapshots
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
size_t SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::getNumberOfSnapshots() const
{
  return BaseType::getNumberOfSnapshots();
}

// Take a snapshot of a sample moment collection
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
void SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::takeSnapshot(
                          const uint64_t number_of_additional_samples,
                          const double sampling_time_from_last_snapshot,
                          const SampleMomentCollection<T,N,Ns...>& collection )
{
  // Make sure that the snapshot collection and the collection have the same
  // size
  testPrecondition( this->size() == collection.size() );
  
  BaseType::takeSnapshot( number_of_additional_samples,
                          sampling_time_from_last_snapshot,
                          collection );

  for( size_t i = 0; i < collection.size(); ++i )
  {
    d_score_snapshots[i].push_back( Utility::getCurrentScore<N>(collection, i) );
  }
}

// Merge the snapshots
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
void SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::mergeSnapshots( const SampleMomentCollectionSnapshots& collection )
{
  // Make sure the the collections have the same size
  testPrecondition( this->size() == collection.size() );

  BaseType::mergeSnapshots( collection );

  for( size_t i = 0; i < d_score_snapshots.size(); ++i )
  {
    const MomentValueType& last_score = d_score_snapshots[i].back();

    for( auto&& other_score : collection.d_score_snapshots[i] )
      d_score_snapshots[i].push_back( last_score + other_score );
  }
}

// Get the snapshot indices (summation indices)
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
auto SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::getSnapshotIndices() const -> const SummationIndexContainerType&
{
  return BaseType::getSnapshotIndices();
}

// Get the snapshot sampling times (sampling times)
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
auto SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::getSnapshotSamplingTimes() const -> const SamplingTimeContainerType&
{
  return BaseType::getSnapshotSamplingTimes();
}

// Save the collection data to an archive
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
template<typename Archive>
void SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local data
  std::string name = "moment_";
  name += Utility::toString( N );
  name += "_snapshots";

  ar & boost::serialization::make_nvp( name.c_str(), d_score_snapshots );
}

// Load the collection data from an archive
template<typename T, template<typename,typename...> class SnapshotContainer, size_t N, size_t... Ns>
template<typename Archive>
void SampleMomentCollectionSnapshots<T,SnapshotContainer,N,Ns...>::load( Archive& ar, const unsigned version )
{
  // Load the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local data
  std::string name = "moment_";
  name += Utility::toString( N );
  name += "_snapshots";

  ar & boost::serialization::make_nvp( name.c_str(), d_score_snapshots );
}

// Get the moment snapshots from the collection
template<size_t N, typename T, template<typename,typename...> class Container, size_t... Ms>
inline const Container<typename Utility::SampleMoment<N,T>::ValueType>& getScoreSnapshots(
                      const SampleMomentCollectionSnapshots<T,Container,Ms...>&
                      collection_snapshots,
                      const size_t i )
{
  return Details::SampleMomentCollectionSnapshotsDataExtractor<N,SampleMomentCollectionSnapshots<T,Container,Ms...> >::getScoreSnapshots( collection_snapshots, i );
}

// Get a score snapshot from the collection
template<size_t N, typename T, template<typename,typename...> class Container, size_t... Ms>
inline const typename SampleMoment<N,T>::ValueType& getScoreSnapshot(
                      const SampleMomentCollectionSnapshots<T,Container,Ms...>&
                      collection_snapshots,
                      const size_t i,
                      const size_t snapshot_index )
{
  return Details::SampleMomentCollectionSnapshotsDataExtractor<N,SampleMomentCollectionSnapshots<T,Container,Ms...> >::getScoreSnapshot( collection_snapshots, i, snapshot_index );
}

// Get a moment snapshot from the collection
template<size_t N, typename T, template<typename,typename...> class Container, size_t... Ms>
inline SampleMoment<N,T> getMomentSnapshot(
                      const SampleMomentCollectionSnapshots<T,Container,Ms...>&
                      collection_snapshots,
                      const size_t i,
                      const size_t snapshot_index )
{
  return Details::SampleMomentCollectionSnapshotsDataExtractor<N,SampleMomentCollectionSnapshots<T,Container,Ms...> >::getMomentSnapshot( collection_snapshots, i, snapshot_index );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,1,2> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollectionSnapshots<double,std::list,1,2> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,2,1> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollectionSnapshots<double,std::list,2,1> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,1,2,3,4> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollectionSnapshots<double,std::list,1,2,3,4> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::SampleMomentCollectionSnapshots<double,std::list,4,3,2,1> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, SampleMomentCollectionSnapshots<double,std::list,4,3,2,1> );

#endif // end UTILITY_SAMPLE_MOMENT_COLLECTION_SNAPSHOTS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SampleMomentCollectionSnapshots_def.hpp
//---------------------------------------------------------------------------//
