//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDInterpolationType.hpp
//! \author Luke Kersting
//! \brief  TwoDInterpolation type enumeration and helper declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTECARLO_TWO_D_INTERPOLATION_TYPE_HPP
#define MONTECARLO_TWO_D_INTERPOLATION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The two d interpolation types
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum TwoDInterpolationType{
  LINLINLIN_INTERPOLATION = 1,
  LINLINLOG_INTERPOLATION = 2,
  LINLOGLIN_INTERPOLATION = 3,
  LOGLINLIN_INTERPOLATION = 4,
  LOGLOGLIN_INTERPOLATION = 5,
  LOGLINLOG_INTERPOLATION = 6,
  LINLOGLOG_INTERPOLATION = 7,
  LOGLOGLOG_INTERPOLATION = 8,
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::TwoDInterpolationType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::TwoDInterpolationType>
{
  //! Convert a MonteCarlo::TwoDInterpolationType to a string
  static std::string toString( const MonteCarlo::TwoDInterpolationType type );

  //! Place the MonteCarlo::TwoDInterpolationType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::TwoDInterpolationType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing TwoDInterpolationType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::TwoDInterpolationType type )
{
  os << Utility::toString( type );

  return os;
}
  
} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::TwoDInterpolationType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::TwoDInterpolationType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LINLINLIN_INTERPOLATION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LINLINLOG_INTERPOLATION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LINLOGLIN_INTERPOLATION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LOGLINLIN_INTERPOLATION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LOGLOGLIN_INTERPOLATION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LOGLINLOG_INTERPOLATION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LINLOGLOG_INTERPOLATION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::LOGLOGLOG_INTERPOLATION, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw two-d "
                         "interpolation type to its corresponding enum "
                         "value!" );
      }
    }
  }
}
  
} // end serialization namespace

} // end boost namespace

#endif // end MONTECARLO_TWO_D_INTERPOLATION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDInterpolationType.hpp
//---------------------------------------------------------------------------//
