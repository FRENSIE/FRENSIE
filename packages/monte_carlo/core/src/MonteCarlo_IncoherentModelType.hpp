//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentModelType.hpp
//! \author Alex Robinson
//! \brief  Incoherent model types and helper functions decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_MODEL_TYPE_HPP
#define MONTE_CARLO_INCOHERENT_MODEL_TYPE_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The incoherent model enumeration
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum IncoherentModelType
{
  KN_INCOHERENT_MODEL = 0,
  WH_INCOHERENT_MODEL,
  IMPULSE_INCOHERENT_MODEL,
  DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
  FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::IncoherentModelType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::IncoherentModelType>
{
  //! Convert a MonteCarlo::IncoherentModelType to a string
  static std::string toString( const MonteCarlo::IncoherentModelType type );

  //! Place the MonteCarlo::IncoherentModelType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::IncoherentModelType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing IncoherentModelType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::IncoherentModelType incoherent_model )
{
  os << Utility::toString( incoherent_model );
  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::IncoherentModelType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::IncoherentModelType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::KN_INCOHERENT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::WH_INCOHERENT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::IMPULSE_INCOHERENT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::DECOUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::COUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw incoherent "
                         "model type to its corresponding enum value!" )//
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_INCOHERENT_MODEL_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonDopplerBroadeningModellType.hpp
//---------------------------------------------------------------------------//
