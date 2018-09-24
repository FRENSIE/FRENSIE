//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronDistributionType.hpp
//! \author Luke Kersting
//! \brief  Elastic electron distribution type enumeration and helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_ELECTRON_DISTRIBUTION_TYPE_HPP
#define MONTE_CARLO_ELASTIC_ELECTRON_DISTRIBUTION_TYPE_HPP

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

/*! The elastic electron distribution type enum.
 *
 * When adding a new type the ToStringTraits methods and the serialization
 * method must be updated.
 */
enum ElasticElectronDistributionType{
  ElasticElectronDistributionType_START = 0,
  COUPLED_DISTRIBUTION = ElasticElectronDistributionType_START,
  DECOUPLED_DISTRIBUTION,
  HYBRID_DISTRIBUTION,
  CUTOFF_DISTRIBUTION,
  SCREENED_RUTHERFORD_DISTRIBUTION,
  ElasticElectronDistributionType_END
};

/*! The coupled elastic electron sampling method enum.
 *
 * When adding a new type the ToStringTraits methods, FromStringTraits methods,
 * and the serialization method must be updated.
 */
enum CoupledElasticSamplingMethod{
  CoupledElasticSamplingMethod_START = 0,
  ONE_D_UNION = CoupledElasticSamplingMethod_START,
  TWO_D_UNION,
  MODIFIED_TWO_D_UNION,
  CoupledElasticSamplingMethod_END
};

} // end MonteCarlo namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::ElasticElectronDistributionType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::ElasticElectronDistributionType>
{
  //! Convert a MonteCarlo::ElasticElectronDistributionType to a string
  static std::string toString( const MonteCarlo::ElasticElectronDistributionType type );

  //! Place the MonteCarlo::ElasticElectronDistributionType in a stream
  static void toStream( std::ostream& os, const MonteCarlo::ElasticElectronDistributionType type );
};

/*! \brief Specialization of Utility::ToStringTraits for
 * MonteCarlo::CoupledElasticSamplingMethod
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<MonteCarlo::CoupledElasticSamplingMethod>
{
  //! Convert a MonteCarlo::CoupledElasticSamplingMethod to a string
  static std::string toString( const MonteCarlo::CoupledElasticSamplingMethod type );

  //! Place the MonteCarlo::CoupledElasticSamplingMethod in a stream
  static void toStream( std::ostream& os, const MonteCarlo::CoupledElasticSamplingMethod type );
};

} // end Utility namespace

namespace std{

//! Stream operator for printing ElasticElectronDistributionType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::ElasticElectronDistributionType reaction )
{
  os << Utility::toString( reaction );
  return os;
}

//! Stream operator for printing CoupledElasticSamplingMethod enums
inline std::ostream& operator<<( std::ostream& os,
                                 const MonteCarlo::CoupledElasticSamplingMethod method )
{
  os << Utility::toString( method );
  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the MonteCarlo::ElasticElectronDistributionType enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::ElasticElectronDistributionType& type,
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
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::COUPLED_DISTRIBUTION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::DECOUPLED_DISTRIBUTION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::HYBRID_DISTRIBUTION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::CUTOFF_DISTRIBUTION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw elastic "
                         "electron distribution type to its "
                         "corresponding enum value!" );
      }
    }
  }
}

//! Serialize the MonteCarlo::CoupledElasticSamplingMethod enum
template<typename Archive>
void serialize( Archive& archive,
                MonteCarlo::CoupledElasticSamplingMethod& type,
                const unsigned version )
{
  if( Archive::is_saving::value )
  {
    archive & (int)type;
  }
  else
  {
    int raw_type;

    archive & raw_type;

    switch( raw_type )
    {
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::ONE_D_UNION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::TWO_D_UNION, int, type );
      BOOST_SERIALIZATION_ENUM_CASE( MonteCarlo::MODIFIED_TWO_D_UNION, int, type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Cannot convert the deserialized raw coupled "
                         "elastic sampling method to its corresponding "
                         "enum value!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronDistributionType.hpp
//---------------------------------------------------------------------------//

