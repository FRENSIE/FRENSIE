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

namespace MonteCarlo{

//! The bremsstrahlung photon angular distribution type enum.
enum ElasticElectronDistributionType{
  COUPLED_DISTRIBUTION = 1,
  DECOUPLED_DISTRIBUTION = 2,
  HYBRID_DISTRIBUTION = 3,
  CUTOFF_DISTRIBUTION = 4,
  SCREENED_RUTHERFORD_DISTRIBUTION = 5,
};

//! Convert a ElasticElectronDistributionType to a string
std::string convertElasticElectronDistributionTypeToString(
                      const ElasticElectronDistributionType reaction );

//! Stream operator for printing ElasticElectronDistributionType enums
inline std::ostream& operator<<( std::ostream& os,
                const ElasticElectronDistributionType reaction )
{
  os << convertElasticElectronDistributionTypeToString( reaction );
  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronDistributionType.hpp
//---------------------------------------------------------------------------//

