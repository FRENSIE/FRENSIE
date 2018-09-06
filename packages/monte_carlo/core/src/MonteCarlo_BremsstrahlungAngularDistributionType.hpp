//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAngularDistributionType.hpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung angular distribution type enumeration and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ANGULAR_DISTRIBUTION_TYPE_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ANGULAR_DISTRIBUTION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The bremsstrahlung photon angular distribution type enum.
 *
 * When adding a new type the ToStringTraits methods and the serialization 
 * method must be updated.
 */
enum BremsstrahlungAngularDistributionType{
  DIPOLE_DISTRIBUTION = 1,
  TABULAR_DISTRIBUTION = 2,
  TWOBS_DISTRIBUTION = 3
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for 
 * MonteCarlo::BremsstrahlungAngularDistributionType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::BremsstrahlungAngularDistributionType>
{
  //! Convert a MonteCarlo::BremsstrahlungAngularDistributionType to a string
  static std::string toString( const MonteCarlo::BremsstrahlungAngularDistributionType type );

  //! Place the MonteCarlo::BremsstrahlungAngularDistributionType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::BremsstrahlungAngularDistributionType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing BremsstrahlungAngularDistributionType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::BremsstrahlungAngularDistributionType reaction )
{
  os << Utility::toString( reaction );
  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::BremsstrahlungAngularDistributionType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::BremsstrahlungAngularDistributionType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::DIPOLE_DISTRIBUTION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::TABULAR_DISTRIBUTION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::TWOBS_DISTRIBUTION, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw "
                         "bremsstrahlung angular distribution type to its "
                         "corresponding enum value!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost serialization

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ANGULAR_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAngularDistributionType.hpp
//---------------------------------------------------------------------------//

