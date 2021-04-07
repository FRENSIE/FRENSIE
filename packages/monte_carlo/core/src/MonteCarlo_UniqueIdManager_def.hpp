//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UniqueIdManager_def.hpp
//! \author Alex Robinson
//! \brief  Unique id manager class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNIQUE_ID_MANAGER_DEF_HPP
#define MONTE_CARLO_UNIQUE_ID_MANAGER_DEF_HPP

// FRENSIE Includes
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Initialize the static member data
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
SetType<IdType> UniqueIdManager<OwnerType,IdType,SetType>::s_unique_ids;

// Constructor
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
UniqueIdManager<OwnerType,IdType,SetType>::UniqueIdManager( const IdType id )
  : d_id( id )
{
  this->verifyUniqueId( id );
}

// Destructor
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
UniqueIdManager<OwnerType,IdType,SetType>::~UniqueIdManager()
{
  s_unique_ids.erase( d_id );
}

// Return the id
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
IdType UniqueIdManager<OwnerType,IdType,SetType>::getId() const
{
  return d_id;
}

// Return the id
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
UniqueIdManager<OwnerType,IdType,SetType>::operator IdType() const
{
  return d_id;
}

// Verify that the id is unique
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
void UniqueIdManager<OwnerType,IdType,SetType>::verifyUniqueId( const IdType id )
{
  TEST_FOR_EXCEPTION( s_unique_ids.find( id ) != s_unique_ids.end(),
                      std::runtime_error,
                      "The " << Utility::typeName<OwnerType>() << " id "
                      << id << " is already in use!" );

  s_unique_ids.insert( id );
}

// Save the id to an archive
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
template<typename Archive>
void UniqueIdManager<OwnerType,IdType,SetType>::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_id );
}
  
// Load the id from an archive
template<typename OwnerType,
         typename IdType,
         template<typename,typename...> class SetType>
template<typename Archive>
void UniqueIdManager<OwnerType,IdType,SetType>::load( Archive& ar, const unsigned version )
{
  s_unique_ids.erase( d_id );
  
  ar & BOOST_SERIALIZATION_NVP( d_id );

  this->verifyUniqueId( d_id );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_UNIQUE_ID_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UniqueIdManager_def.hpp
//---------------------------------------------------------------------------//
