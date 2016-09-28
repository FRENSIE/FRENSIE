//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// The absolute mimimum adjoint photon energy (MeV)
const double SimulationAdjointPhotonProperties::s_absolute_min_adjoint_photon_energy = 1e-3;

// The minimum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::s_min_adjoint_photon_energy =
  SimulationAdjointPhotonProperties::s_absolute_min_adjoint_photon_energy;

// The absolume maximum adjoint photon energy (MeV)
const double SimulationAdjointPhotonProperties::s_absolute_max_adjoint_photon_energy = 20.0;

// The maximum adjoint photon energy (MeV)
double SimulationAdjointPhotonProperties::s_max_adjoint_photon_energy =
  SimulationAdjointPhotonProperties::s_absolute_max_adjoint_photon_energy;

// The number of adjoint photon hash grid bins
unsigned SimulationAdjointPhotonProperties::s_num_adjoint_photon_hash_grid_bins = 500;

// The incoherent adjoint model
IncoherentAdjointModelType SimulationAdjointPhotonProperties::s_incoherent_adjoint_model_type = FULL_PROFILE_DB_IMPULSE_INCOHERENT_ADJOINT_MODEL;

// Set the minimum adjoint photon energy (MeV)
void SimulationAdjointPhotonProperties::setMinAdjointPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy >= s_absolute_min_adjoint_photon_energy );
  testPrecondition( energy < s_max_adjoint_photon_energy );

  s_min_adjoint_photon_energy = energy;
}

// Set the maximum adjoint photon energy (MeV)
void SimulationAdjointPhotonProperties::setMaxAdjointPhotonEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > s_min_adjoint_photon_energy );
  testPrecondition( energy <= s_absolute_max_adjoint_photon_energy );

  s_max_adjoint_photon_energy = energy;
}

// Set the number of adjoint photon hash grid bins
void SimulationAdjointPhotonProperties::setNumberOfAdjointPhotonHashGridBins( const unsigned bins )
{
  // Make sure the number of bins is valid
  testPrecondition( bins >= 1 );

  s_num_adjoint_photon_hash_grid_bins = bins;
}

// Set the incoherent adjoint model type
void SimulationAdjointPhotonProperties::setIncoherentAdjointModelType(
                                       const IncoherentAdjointModelType model )
{
  s_incoherent_adjoint_model_type = model;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonProperties.cpp
//---------------------------------------------------------------------------//
