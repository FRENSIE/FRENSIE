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
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Convert a MonteCarlo::ElasticElectronDistributionType to a string
std::string ToStringTraits<MonteCarlo::ElasticElectronDistributionType>::toString(
                   const MonteCarlo::ElasticElectronDistributionType reaction )
{
  switch( reaction )
  {
  case MonteCarlo::COUPLED_DISTRIBUTION:
    return "Coupled Distribution";
  case MonteCarlo::DECOUPLED_DISTRIBUTION:
    return "Decoupled Distribution";
  case MonteCarlo::HYBRID_DISTRIBUTION:
    return "Hybrid Distribution";
  case MonteCarlo::CUTOFF_DISTRIBUTION:
    return "Cutoff Distribution";
  case MonteCarlo::SCREENED_RUTHERFORD_DISTRIBUTION:
    return "Screened Rutherford Distribution";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Cannot convert the Elastic electron "
                     "distribution type to a string!" );
  }
}

// Place the MonteCarlo::ElasticElectronDistributionType in a stream
void ToStringTraits<MonteCarlo::ElasticElectronDistributionType>::toStream( std::ostream& os, const MonteCarlo::ElasticElectronDistributionType type )
{
  os << ToStringTraits<MonteCarlo::ElasticElectronDistributionType>::toString( type );
}

// Convert a MonteCarlo::CoupledElasticSamplingMethod to a string
std::string ToStringTraits<MonteCarlo::CoupledElasticSamplingMethod>::toString(
                        const MonteCarlo::CoupledElasticSamplingMethod method )
{
  switch( method )
  {
  case MonteCarlo::ONE_D_UNION:
    return "One D Union";
  case MonteCarlo::TWO_D_UNION:
    return "Two D Union";
  case MonteCarlo::MODIFIED_TWO_D_UNION:
    return "Modified Two D Union";
  default:
    THROW_EXCEPTION( std::logic_error,
                     "Cannot convert the coupled elastic "
                     "electron sampling method to a string!" );
  }
}

// Place the MonteCarlo::CoupledElasticSamplingMethod in a stream
void ToStringTraits<MonteCarlo::CoupledElasticSamplingMethod>::toStream( std::ostream& os, const MonteCarlo::CoupledElasticSamplingMethod type )
{
  os << ToStringTraits<MonteCarlo::CoupledElasticSamplingMethod>::toString( type );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronDistributionType.cpp
//---------------------------------------------------------------------------//

