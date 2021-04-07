//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleType.hpp
//! \author Alex Robinson
//! \brief  Particle type enumeration and helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_TYPE_HPP
#define MONTE_CARLO_PARTICLE_TYPE_HPP

// FRENSIE Includes
#include "Geometry_ParticleType.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The particle type enum
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum ParticleType{
  ParticleType_START = 0,
  PHOTON = ParticleType_START,
  NEUTRON,
  ELECTRON,
  POSITRON,
  ADJOINT_PHOTON,
  ADJOINT_NEUTRON,
  ADJOINT_ELECTRON,
  ADJOINT_POSITRON,
  ParticleType_END
};

//! Convert the geometry particle type enum to a ParticleType enum
ParticleType convertGeometryParticleTypeEnumToParticleTypeEnum(
                                  const Geometry::ParticleType particle_type );

//! Convert shorthand particle type name to a particle type
ParticleType convertShortParticleTypeNameToParticleTypeEnum(
                                 const std::string& short_particle_type_name );

//! Get the particle type enum from an int
ParticleType convertIntToParticleType( const int raw_particle_type );

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::ParticleType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::ParticleType>
{
  //! Convert a MonteCarlo::ParticleType to a string
  static std::string toString( const MonteCarlo::ParticleType type );

  //! Place the MonteCarlo::ParticleType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::ParticleType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for print ParticleType enums
inline std::ostream& operator<<( std::ostream& os,
				 const MonteCarlo::ParticleType particle_type )
{
  os << Utility::toString( particle_type );
  return os;
}
  
} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::ParticleType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::ParticleType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::PHOTON, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::NEUTRON, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ELECTRON, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::POSITRON, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ADJOINT_PHOTON, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ADJOINT_NEUTRON, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ADJOINT_ELECTRON, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw particle type "
                         "to its corresponding enum value!" );
      }
    }
  }    
}
  
} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_PARTICLE_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleType.hpp
//---------------------------------------------------------------------------//
