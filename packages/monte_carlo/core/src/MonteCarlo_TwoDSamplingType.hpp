//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TwoDSamplingType.hpp
//! \author Luke Kersting
//! \brief  TwoDSampling type enumeration and helper declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTECARLO_TWO_D_SAMPLING_TYPE_HPP
#define MONTECARLO_TWO_D_SAMPLING_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

//! The two d Sampling types
enum TwoDSamplingType{
  CORRELATED_SAMPLING = 1,
  UNIT_BASE_CORRELATED_SAMPLING = 2,
  DIRECT_SAMPLING = 3,
  UNIT_BASE_SAMPLING = 4,
  CUMULATIVE_POINTS_SAMPLING = 5
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::TwoDSamplingType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::TwoDSamplingType>
{
  //! Convert a MonteCarlo::TwoDSamplingType to a string
  static std::string toString( const MonteCarlo::TwoDSamplingType type );

  //! Place the MonteCarlo::TwoDSamplingType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::TwoDSamplingType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing TwoDSamplingType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::TwoDSamplingType type )
{
  os << Utility::toString( type );

  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::TwoDSamplingPolicy enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::TwoDSamplingType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::CORRELATED_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::DIRECT_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::UNIT_BASE_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::CUMULATIVE_POINTS_SAMPLING, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw two-d "
                         "sampling type to its corresponding enum value!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTECARLO_TWO_D_SAMPLING_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_TwoDSamplingType.hpp
//---------------------------------------------------------------------------//
