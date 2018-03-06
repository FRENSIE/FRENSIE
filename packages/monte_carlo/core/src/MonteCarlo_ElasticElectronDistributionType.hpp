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

//! The elastic electron distribution type enum.
enum ElasticElectronDistributionType{
  COUPLED_DISTRIBUTION = 1,
  DECOUPLED_DISTRIBUTION = 2,
  HYBRID_DISTRIBUTION = 3,
  CUTOFF_DISTRIBUTION = 4,
  SCREENED_RUTHERFORD_DISTRIBUTION = 5
};

//! The coupled elastic electron sampling method enum.
enum CoupledElasticSamplingMethod{
  ONE_D_UNION = 1,
  TWO_D_UNION = 2,
  SIMPLIFIED_UNION = 3
};

//! Convert a ElasticElectronDistributionType to a string
std::string convertElasticElectronDistributionTypeToString(
                      const ElasticElectronDistributionType reaction );

//! Convert a CoupledElasticSamplingMethod to a string
std::string convertCoupledElasticSamplingMethodToString(
                      const CoupledElasticSamplingMethod method );

//! Convert a string to a CoupledElasticSamplingMethod
CoupledElasticSamplingMethod convertStringToCoupledElasticSamplingMethod(
                      const std::string raw_method );

//! Stream operator for printing ElasticElectronDistributionType enums
inline std::ostream& operator<<( std::ostream& os,
                const ElasticElectronDistributionType reaction )
{
  os << convertElasticElectronDistributionTypeToString( reaction );
  return os;
}

//! Stream operator for printing CoupledElasticSamplingMethod enums
inline std::ostream& operator<<( std::ostream& os,
                const CoupledElasticSamplingMethod method )
{
  os << convertCoupledElasticSamplingMethodToString( method );
  return os;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_DISTRIBUTION_TYPE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronDistributionType.hpp
//---------------------------------------------------------------------------//

