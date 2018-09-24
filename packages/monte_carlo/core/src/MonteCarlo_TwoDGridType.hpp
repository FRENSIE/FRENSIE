//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDGridType.hpp
//! \author Luke Kersting
//! \brief  TwoDGrid type enumeration and helper declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTECARLO_TWO_D_GRID_TYPE_HPP
#define MONTECARLO_TWO_D_GRID_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

//! The two d grid types
enum TwoDGridType{
  INVALID_GRID = -1,
  CORRELATED_GRID = 0,
  UNIT_BASE_CORRELATED_GRID = 1,
  DIRECT_GRID = 2,
  UNIT_BASE_GRID = 3
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for MonteCarlo::TwoDGridType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::TwoDGridType>
{
  //! Convert a MonteCarlo::TwoDGridType to a string
  static std::string toString( const MonteCarlo::TwoDGridType type );

  //! Place the MonteCarlo::TwoDGridType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::TwoDGridType type );
};

// /*! Specialization of Utility::IsHashable for MonteCarlo::TwoDGridType
//  * \ingroup type_traits
//  */
// template<>
// struct IsHashable<MonteCarlo::TwoDGridType> : public std::true_type
// { /* ... */ };

} // end Utility namespace

namespace std{

//! Stream operator for printing Subshell enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::TwoDGridType grid_type )
{
  Utility::ToStringTraits<MonteCarlo::TwoDGridType>::toStream( os, grid_type );

  return os;
}

// //! Specialization of std::hash for MonteCarlo::TwoDGridType
// template<>
// struct hash<MonteCarlo::TwoDGridType> : public hash<unsigned>
// { /* ... */ };

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::TwoDGridType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::TwoDGridType& type,
                const unsigned version )
{
  if( Archive::is_saving::value )
    archive & (int)type;
  else
  {
    int raw_type;

    archive & raw_type;

    switch( raw_type )
    {
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::CORRELATED_GRID, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::UNIT_BASE_CORRELATED_GRID, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::DIRECT_GRID, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::UNIT_BASE_GRID, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw two-d "
                         "grid type to its corresponding enum value!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTECARLO_TWO_D_GRID_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDGridType.hpp
//---------------------------------------------------------------------------//
