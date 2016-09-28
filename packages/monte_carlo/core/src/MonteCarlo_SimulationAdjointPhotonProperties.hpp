//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointModelType.hpp"

namespace MonteCarlo{

//! The simulation adjoint photon properties class
class SimulationAdjointPhotonProperties
{

public:

  //! Set the minimum adjoint photon energy (MeV)
  static void setMinAdjointPhotonEnergy( const double energy );

  //! Return the minimum adjoint photon energy (MeV)
  static double getMinAdjointPhotonEnergy();

  //! Return the absolute minimum adjoint photon energy (MeV)
  static double getAbsoluteMinAdjointPhotonEnergy();

  //! Set the maximum adjoint photon energy (MeV)
  static void setMaxAdjointPhotonEnergy( const double energy );

  //! Return the maximum adjoint photon energy (MeV)
  static double getMaxAdjointPhotonEnergy();

  //! Return the absolute maximum adjoint photon energy (MeV)
  static double getAbsoluteMaxAdjointPhotonEnergy();

  //! Set the number of adjoint photon hash grid bins
  static void setNumberOfAdjointPhotonHashGridBins( const unsigned bins );

  //! Get the number of adjoint photon hash grid bins
  static unsigned getNumberOfAdjointPhotonHashGridBins();

  //! Set the incoherent adjoint model type
  static void setIncoherentAdjointModelType(
                                      const IncoherentAdjointModelType model );

  //! Return the incoherent adjoint model type
  static IncoherentAdjointModelType getIncoherentAdjointModelType();

private:

  // The absolute mimimum adjoint photon energy (MeV)
  static const double s_absolute_min_adjoint_photon_energy;

  // The minimum adjoint photon energy (MeV)
  static double s_min_adjoint_photon_energy;

  // The maximum adjoint photon energy (MeV)
  static double s_max_adjoint_photon_energy;

  // The absolume maximum adjoint photon energy (MeV)
  static const double s_absolute_max_adjoint_photon_energy;

  // The number of adjoint photon hash grid bins
  static unsigned s_num_adjoint_photon_hash_grid_bins;

  // The incoherent adjoint model
  static IncoherentAdjointModelType s_incoherent_adjoint_model_type;
};

// Return the minimum adjoint photon energy (MeV)
inline double SimulationAdjointPhotonProperties::getMinAdjointPhotonEnergy()
{
  return s_min_adjoint_photon_energy;
}

// Return the absolute minimum adjoint photon energy (MeV)
inline double SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy()
{
  return s_absolute_min_adjoint_photon_energy;
}

// Return the maximum adjoint photon energy (MeV)
inline double SimulationAdjointPhotonProperties::getMaxAdjointPhotonEnergy()
{
  return s_max_adjoint_photon_energy;
}

// Return the absolute maximum adjoint photon energy (MeV)
inline double SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy()
{
  return s_absolute_max_adjoint_photon_energy;
}

// Get the number of adjoint photon hash grid bins
inline unsigned SimulationAdjointPhotonProperties::getNumberOfAdjointPhotonHashGridBins()
{
  return s_num_adjoint_photon_hash_grid_bins;
}

// Return the incoherent adjoint model type
inline IncoherentAdjointModelType SimulationAdjointPhotonProperties::getIncoherentAdjointModelType()
{
  return s_incoherent_adjoint_model_type;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonProperties.hpp
//---------------------------------------------------------------------------//
