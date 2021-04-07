//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The bremsstrahlung scattering distribution factory class that uses ACE data
class BremsstrahlungElectronScatteringDistributionACEFactory
{

public:

  //! Create a simple dipole bremsstrahlung distribution
  static void createBremsstrahlungDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol = 1e-7 );

  //! Create a detailed 2BS bremsstrahlung distribution
  static void createBremsstrahlungDistribution(
    const int atomic_number,
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
        scattering_distribution,
    const double evaluation_tol = 1e-7 );

protected:

  //! Create the energy loss function
  static void createScatteringFunction(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
        scattering_function,
    const double evaluation_tol );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG__ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

