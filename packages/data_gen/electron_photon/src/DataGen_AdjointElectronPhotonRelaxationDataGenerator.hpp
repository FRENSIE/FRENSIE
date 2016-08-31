//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting, Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Utility_GridGenerator.hpp"

namespace DataGen{

//! The adjoint electron-photon-relaxation data generator base class
class AdjointElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  AdjointElectronPhotonRelaxationDataGenerator(
                                            const unsigned atomic_number,
                                            const double min_photon_energy,
                                            const double max_photon_energy,
                                            const double min_electron_energy,
                                            const double max_electron_energy );

  //! Destructor
  virtual ~AdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Get the atomic number
  unsigned getAtomicNumber() const;

  //! Return the min photon energy
  double getMinPhotonEnergy() const;

  //! Return the max photon energy
  double getMaxPhotonEnergy() const;

  //! Return the min electron energy
  double getMinElectronEnergy() const;

  //! Return the max electron energy
  double getMaxElectronEnergy() const;

  //! Set the default grid convergence tolerance
  void setDefaultGridConvergenceTolerance( const double convergence_tol );

  //! Get the default grid convergence tolerance
  double getDefaultGridConvergenceTolerance() const;

  //! Set the default grid absolute difference tolerance
  void setDefaultGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the default grid absolute difference tolerance
  double getDefaultGridAbsoluteDifferenceTolerance() const;

  //! Set the default grid distance tolerance
  void setDefaultGridDistanceTolerance( const double distance_tol );

  //! Get the default grid distance tolerance
  double getDefaultGridDistanceTolerance() const;

  //! Populate the electron-photon-relaxation data container
  virtual void populateEPRDataContainer(
                    Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
                    data_container ) const = 0;

protected:

  //! Set the min photon energy
  void setMinPhotonEnergy( const double min_photon_energy );

  //! Set the max photon energy
  void setMaxPhotonEnergy( const double max_photon_energy );

  //! Set the min electron energy
  void setMinElectronEnergy( const double min_electron_energy );

  //! Set the max electron energy
  void setMaxElectronEnergy( const double max_electron_energy );

  //! Set the basic data
  void setBasicData(Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
                    data_container ) const;

  //! Set the default convergence parameters
  void setDefaultConvergenceParameters(
                    Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
                    data_container ) const;

  //! Get a default grid generator (Lin-Lin grid)
  const Utility::GridGenerator<Utility::LinLin>&
  getDefaultGridGenerator() const;

private:

  // The atomic number for which relaxation data can be generated
  unsigned d_atomic_number;

  // The min photon energy
  double d_min_photon_energy;

  // The max photon energy
  double d_max_photon_energy;

  // The min electron energy
  double d_min_electron_energy;

  // The max electron energy
  double d_max_electron_energy;

  // The default grid generator
  std::unique_ptr<Utility::GridGenerator<Utility::LinLin> >
  d_default_grid_generator;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
