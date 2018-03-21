//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleModeType.hpp
//! \author Alex Robinson
//! \brief  Particle mode type enum and helper function delcarations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_MODE_TYPE_HPP
#define MONTE_CARLO_PARTICLE_MODE_TYPE_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The particle transport mode enumeration
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum ParticleModeType
{
  NEUTRON_MODE = 0,
  PHOTON_MODE,
  ELECTRON_MODE,
  NEUTRON_PHOTON_MODE,
  PHOTON_ELECTRON_MODE,
  NEUTRON_PHOTON_ELECTRON_MODE,
  ADJOINT_NEUTRON_MODE,
  ADJOINT_PHOTON_MODE,
  ADJOINT_ELECTRON_MODE
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::ParticleModeType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::ParticleModeType>
{
  //! Convert a MonteCarlo::ParticleModeType to a string
  static std::string toString( const MonteCarlo::ParticleModeType type );

  //! Place the MonteCarlo::ParticleModeType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::ParticleModeType type );
};

} // end Utility namespace

namespace std{
  
//! Stream operator for printing ParticleModeType enums
inline std::ostream& operator<<( std::ostream& os,
				 const MonteCarlo::ParticleModeType particle_mode )
{
  os << Utility::toString( particle_mode );
  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::ParticleModeType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::ParticleModeType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::NEUTRON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::PHOTON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ELECTRON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::NEUTRON_PHOTON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::PHOTON_ELECTRON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ADJOINT_NEUTRON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ADJOINT_PHOTON_MODE, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ADJOINT_ELECTRON_MODE, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw particle mode "
                         "type to its corresponding enum value!" );
      }
    }
  }
}
  
} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_PARTICLE_MODE_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeType.hpp
//---------------------------------------------------------------------------//
