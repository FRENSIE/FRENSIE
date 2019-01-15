//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSamplingType.hpp
//! \author Luke Kersting
//! \brief  Electroionization sampling type enum and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SAMPLING_TYPE_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SAMPLING_TYPE_HPP

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The Electroionization sampling type enum
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated
 */
enum ElectroionizationSamplingType
{
  KNOCK_ON_SAMPLING,
  OUTGOING_ENERGY_SAMPLING,
  OUTGOING_ENERGY_RATIO_SAMPLING,
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::ElectroionizationSamplingType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::ElectroionizationSamplingType>
{
  //! Convert a MonteCarlo:: to a string
  static std::string toString( const MonteCarlo::ElectroionizationSamplingType type );

  //! Place the MonteCarlo:: in a stream
  static void toStream( std::ostream& os, const MonteCarlo::ElectroionizationSamplingType type );
};

} // end Utility namespace

namespace std{

//! Stream operator for printing ElectroionizationSamplingType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::ElectroionizationSamplingType incoherent_adjoint_model )
{
  os << Utility::toString( incoherent_adjoint_model );
  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::ElectroionizationSamplingType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::ElectroionizationSamplingType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::KNOCK_ON_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OUTGOING_ENERGY_SAMPLING, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING, int, type );

      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw adjoint "
                         "Klein-Nishina sampling type to its corresponding "
                         "enum value!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SAMPLING_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSamplingType.hpp
//---------------------------------------------------------------------------//
