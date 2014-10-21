//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardInelasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron modified Wentzel scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HARD_INELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_HARD_INELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class HardInelasticElectronScatteringDistribution : public ElectronScatteringDistribution
{

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HARD_INELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardInelasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
