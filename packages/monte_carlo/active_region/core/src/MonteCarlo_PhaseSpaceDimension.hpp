//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension enum and helper function decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_SpatialDimensionType.hpp"
#include "Utility_DirectionalDimensionType.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

//! The phase space dimension type enumeration
enum PhaseSpaceDimension
{
  PRIMARY_SPATIAL_DIMENSION = 0,
  SECONDARY_SPATIAL_DIMENSION,
  TERTIARY_SPATIAL_DIMENSION,
  PRIMARY_DIRECTIONAL_DIMENSION,
  SECONDARY_DIRECTIONAL_DIMENSION,
  TERTIARY_DIRECTIONAL_DIMENSION,
  ENERGY_DIMENSION,
  TIME_DIMENSION,
  WEIGHT_DIMENSION,
  SOURCE_ENERGY_DIMENSION,
  SOURCE_TIME_DIMENSION,
  SOURCE_WEIGHT_DIMENSION
};

//! Convert the spatial dimension to the equivalent phase space dimension
PhaseSpaceDimension convertSpatialDimensionToPhaseSpaceDimension(
                       const Utility::SpatialDimensionType spatial_dimension );

//! Convert the directional dimension to the equivalent phase space dimension
PhaseSpaceDimension convertDirectionalDimensionToPhaseSpaceDimension(
               const Utility::DirectionalDimensionType directional_dimension );

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::PhaseSpaceDimension
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::PhaseSpaceDimension>
{
  //! Convert a MonteCarlo::PhaseSpaceDimension to a string
  static std::string toString( const MonteCarlo::PhaseSpaceDimension dimension );

  //! Place the MonteCarlo::PhaseSpaceDimension in a stream
  static void toStream( std::ostream& os, const MonteCarlo::PhaseSpaceDimension dimension );
};

} // end Utility namespace

namespace std{

//! Stream operator for printing dimension type enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::PhaseSpaceDimension dimension )
{
  os << Utility::toString( dimension );
  return os;
}
  
} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::PhaseSpaceDimension enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::PhaseSpaceDimension& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::PRIMARY_SPATIAL_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::SECONDARY_SPATIAL_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::TERTIARY_SPATIAL_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ENERGY_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::TIME_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::WEIGHT_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::SOURCE_ENERGY_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::SOURCE_TIME_DIMENSION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::SOURCE_WEIGHT_DIMENSION, int, type );

      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw phase space "
                         "dimension type to its corresponding enum value!" );
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
