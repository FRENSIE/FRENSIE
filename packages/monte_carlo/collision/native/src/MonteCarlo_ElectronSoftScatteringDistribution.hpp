//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronSoftScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron soft scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_SOFT_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTRON_SOFT_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class ElectronSoftScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Constructor
  ElectronSoftScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~ElectronSoftScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the electron
  virtual void scatterElectron( ElectronState& electron,
			                    ParticleBank& bank) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_Soft_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronSoftScatteringDistribution.hpp
//---------------------------------------------------------------------------//
