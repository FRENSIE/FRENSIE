//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointModelType.hpp
//! \author Alex Robinson
//! \brief  Incoherent adjoint model types and helper functions decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_MODEL_TYPE_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_MODEL_TYPE_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The incoherent adjoint model enumeration
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum IncoherentAdjointModelType
{
  KN_INCOHERENT_ADJOINT_MODEL = 0,
  WH_INCOHERENT_ADJOINT_MODEL,
  IMPULSE_INCOHERENT_ADJOINT_MODEL,
  DB_IMPULSE_INCOHERENT_ADJOINT_MODEL
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::IncoherentAdjointModelType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::IncoherentAdjointModelType>
{
  //! Convert a MonteCarlo:: to a string
  static std::string toString( const MonteCarlo::IncoherentAdjointModelType type );

  //! Place the MonteCarlo:: in a stream
  static void toStream( std::ostream& os, const MonteCarlo::IncoherentAdjointModelType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing IncoherentAdjointModelType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::IncoherentAdjointModelType incoherent_adjoint_model )
{
  os << Utility::toString( incoherent_adjoint_model );
  return os;
}
  
} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::IncoherentAdjointModelType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::IncoherentAdjointModelType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw incoherent "
                         "adjoint model type to its corresponding enum "
                         "value!" );
      }
    }
  }
}
  
} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_MODEL_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointModelType.hpp
//---------------------------------------------------------------------------//
