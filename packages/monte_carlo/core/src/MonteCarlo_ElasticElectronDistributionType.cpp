//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronDistributionType.cpp
//! \author Luke Kersting
//! \brief  Elastic electron distribution type helper function definitions.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Convert a ElasticElectronDistributionType enum to a string
std::string convertElasticElectronDistributionTypeToString(
                      const ElasticElectronDistributionType reaction )
{
  switch( reaction )
  {
  case COUPLED_DISTRIBUTION:
    return "Coupled Distribution";
  case DECOUPLED_DISTRIBUTION:
    return "Decoupled Distribution";
  case HYBRID_DISTRIBUTION:
    return "Hybrid Distribution";
  case CUTOFF_DISTRIBUTION:
    return "Cutoff Distribution";
  case SCREENED_RUTHERFORD_DISTRIBUTION:
    return "Screened Rutherford Distribution";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Error: cannot convert the Elastic electron "
                     "distribution type to a string!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronDistributionType.cpp
//---------------------------------------------------------------------------//

