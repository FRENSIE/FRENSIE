//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationAdjointPhotonProperties.hpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP
#define MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointModelType.hpp"

namespace MonteCarlo{

//! The simulation adjoint photon properties class
class SimulationAdjointPhotonProperties
{

public:

  //! Constructor
  SimulationAdjointPhotonProperties();

  //! Destructor
  virtual ~SimulationAdjointPhotonProperties()
  { /* ... */ }

  //! Set the minimum adjoint photon energy (MeV)
  void setMinAdjointPhotonEnergy( const double energy );

  //! Return the minimum adjoint photon energy (MeV)
  double getMinAdjointPhotonEnergy() const;

  //! Return the absolute minimum adjoint photon energy (MeV)
  static double getAbsoluteMinAdjointPhotonEnergy();

  //! Set the maximum adjoint photon energy (MeV)
  void setMaxAdjointPhotonEnergy( const double energy );

  //! Return the maximum adjoint photon energy (MeV)
  double getMaxAdjointPhotonEnergy() const;

  //! Return the absolute maximum adjoint photon energy (MeV)
  static double getAbsoluteMaxAdjointPhotonEnergy();

  //! Set the number of adjoint photon hash grid bins
  void setNumberOfAdjointPhotonHashGridBins( const unsigned bins );

  //! Get the number of adjoint photon hash grid bins
  unsigned getNumberOfAdjointPhotonHashGridBins() const;

  //! Set the incoherent adjoint model type
  void setIncoherentAdjointModelType(
                                      const IncoherentAdjointModelType model );

  //! Return the incoherent adjoint model type
  IncoherentAdjointModelType getIncoherentAdjointModelType() const;

  //! Set the critical line energies
  void setCriticalAdjointPhotonLineEnergies(
                        const Teuchos::Array<double>& critical_line_energies );

  //! Get the critical line energies
  const Teuchos::Array<double>& getCriticalAdjointPhotonLineEnergies() const;

private:

  // The absolute mimimum adjoint photon energy (MeV)
  static const double s_absolute_min_adjoint_photon_energy;

  // The absolume maximum adjoint photon energy (MeV)
  static const double s_absolute_max_adjoint_photon_energy;

  // The minimum adjoint photon energy (MeV)
  double d_min_adjoint_photon_energy;

  // The maximum adjoint photon energy (MeV)
  double d_max_adjoint_photon_energy;

  // The number of adjoint photon hash grid bins
  unsigned d_num_adjoint_photon_hash_grid_bins;

  // The incoherent adjoint model
  IncoherentAdjointModelType d_incoherent_adjoint_model_type;

  // The critical line energies
  Teuchos::Array<double> d_critical_line_energies;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SIMULATION_ADJOINT_PHOTON_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationAdjointPhotonProperties.hpp
//---------------------------------------------------------------------------//
