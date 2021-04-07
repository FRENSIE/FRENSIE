//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_HPP

// Std Lib Includes
#include <iostream>
#include <string>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

//! The observer phase space dimension enumeration
enum ObserverPhaseSpaceDimension{
  OBSERVER_COSINE_DIMENSION = 0,
  OBSERVER_SOURCE_ENERGY_DIMENSION,
  OBSERVER_ENERGY_DIMENSION,
  OBSERVER_SOURCE_TIME_DIMENSION,
  OBSERVER_TIME_DIMENSION,
  OBSERVER_COLLISION_NUMBER_DIMENSION,
  OBSERVER_SOURCE_ID_DIMENSION,
  OBSERVER_DIRECTION_DIMENSION
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::ObserverPhaseSpaceDimension
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::ObserverPhaseSpaceDimension>
{
  //! Convert a MonteCarlo::ObserverPhaseSpaceDimension to a string
  static std::string toString( const MonteCarlo::ObserverPhaseSpaceDimension dimension );

  //! Place the MonteCarlo::ObserverPhaseSpaceDimension in a stream
  static void toStream( std::ostream& os, const MonteCarlo::ObserverPhaseSpaceDimension dimension );
};

} // end Utility namespace

namespace std{

//! Stream operator for printing MonteCarlo::ObserverPhaseSpaceDimension enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::ObserverPhaseSpaceDimension dimension )
{
  os << Utility::toString( dimension );

  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::ObserverPhaseSpaceDimension enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::ObserverPhaseSpaceDimension& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_COSINE_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_ENERGY_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_TIME_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OBSERVER_DIRECTION_DIMENSION, int, type );

      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot conver the deserialized raw observer phase "
                         "space dimension type to its corresponding enum "
                         "value!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimension.hpp
//---------------------------------------------------------------------------//
