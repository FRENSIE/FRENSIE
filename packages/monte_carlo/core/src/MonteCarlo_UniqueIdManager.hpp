//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UniqueIdManager.hpp
//! \author Alex Robinson
//! \brief  Unique id manager class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNIQUE_ID_MANAGER_HPP
#define MONTE_CARLO_UNIQUE_ID_MANAGER_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>

// FRENSIE Includes
#include "Utility_SerializationHelpers.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The unique id manager base class
template<typename OwnerType,
         typename IdType = size_t,
         template<typename,typename...> class SetType = std::set>
class UniqueIdManager
{

public:
  
  //! Constructor
  UniqueIdManager( const IdType id );

  //! Destructor
  ~UniqueIdManager();

  //! Return the id
  IdType getId() const;

  //! Return the id
  operator IdType() const;

private:

  // Verify that the id is unique
  void verifyUniqueId( const IdType id );

  // Save the id to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;
  
  // Load the id from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();
  
  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The unique id set
  static SetType<IdType> s_unique_ids;

  // The id
  IdType d_id;
};
  
} // end MonteCarlo namespace

#define BOOST_SERIALIZATION_UNIQUE_ID_MANAGER_VERSION( version )        \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_VERSION_IMPL(                      \
    UniqueIdManager, MonteCarlo, version,                                 \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename OwnerType, typename IdType, template<typename,typename...> class SetType ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( OwnerType, IdType, SetType ) )

BOOST_SERIALIZATION_UNIQUE_ID_MANAGER_VERSION( 0 );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_UniqueIdManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_UNIQUE_ID_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UniqueIdManager.hpp
//---------------------------------------------------------------------------//
