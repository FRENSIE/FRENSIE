//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  The electron scattering distribution ACE factory helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a cutoff elastic distribution
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data )
{
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
    distribution, raw_electroatom_data );

  return distribution;
}

//! Create a screened Rutherford elastic distribution
std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution> createScreenedRutherfordElasticDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data )
{
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionACEFactory::createScreenedRutherfordElasticDistribution(
    distribution, raw_electroatom_data.extractAtomicNumber() );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a simple dipole bremsstrahlung distribution
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
    raw_electroatom_data, distribution, evaluation_tol );

  return distribution;
}

//! Create a detailed 2BS bremsstrahlung distribution
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const int atomic_number,
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
    atomic_number, raw_electroatom_data, distribution, evaluation_tol );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const unsigned subshell,
    const double evaluation_tol )
{
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    distribution;

  ElectroionizationSubshellElectronScatteringDistributionACEFactory::createElectroionizationSubshellDistribution(
    raw_electroatom_data,
    distribution,
    subshell,
    evaluation_tol );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create a atomic excitation distribution
std::shared_ptr<const AtomicExcitationElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data )
{
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    distribution;

  AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
    raw_electroatom_data, distribution );

  return distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.cpp
//---------------------------------------------------------------------------//
