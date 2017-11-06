//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Utility_GridGenerator.hpp"

namespace DataGen{

//! The electron-photon-relaxation data generator base class
class ElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  ElectronPhotonRelaxationDataGenerator( const unsigned atomic_number,
                                         const double min_photon_energy,
                                         const double max_photon_energy,
                                         const double min_electron_energy,
                                         const double max_electron_energy );

  //! Destructor
  virtual ~ElectronPhotonRelaxationDataGenerator()
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

  //! Set the default photon grid convergence tolerance
  void setDefaultPhotonGridConvergenceTolerance( const double convergence_tol );

  //! Get the default photon grid convergence tolerance
  double getDefaultPhotonGridConvergenceTolerance() const;

  //! Set the default photon grid absolute difference tolerance
  void setDefaultPhotonGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the default photon grid absolute difference tolerance
  double getDefaultPhotonGridAbsoluteDifferenceTolerance() const;

  //! Set the default photon grid distance tolerance
  void setDefaultPhotonGridDistanceTolerance( const double distance_tol );

  //! Get the default photon grid distance tolerance
  double getDefaultPhotonGridDistanceTolerance() const;

  //! Set the default electron grid convergence tolerance
  void setDefaultElectronGridConvergenceTolerance( const double convergence_tol );

  //! Get the default electron grid convergence tolerance
  double getDefaultElectronGridConvergenceTolerance() const;

  //! Set the default electron grid absolute difference tolerance
  void setDefaultElectronGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the default electron grid absolute difference tolerance
  double getDefaultElectronGridAbsoluteDifferenceTolerance() const;

  //! Set the default electron grid distance tolerance
  void setDefaultElectronGridDistanceTolerance( const double distance_tol );

  //! Get the default electron grid distance tolerance
  double getDefaultElectronGridDistanceTolerance() const;

  //! Populate the electron-photon-relaxation data container
  virtual void populateEPRDataContainer(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
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
  void setBasicData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;
  
  //! Set the default convergence parameters
  void setDefaultConvergenceParameters(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Get a default photon grid generator (Lin-Lin grid)
  const Utility::GridGenerator<Utility::LinLin>&
  getDefaultPhotonGridGenerator() const;

  //! Get a default electron grid generator (Log-Log grid)
  const Utility::GridGenerator<Utility::LogLog>&
  getDefaultElectronGridGenerator() const;

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

  // The default photon grid generator
  std::unique_ptr<Utility::GridGenerator<Utility::LinLin> >
  d_default_photon_grid_generator;

  // The default electron grid generator
  std::unique_ptr<Utility::GridGenerator<Utility::LogLog> >
  d_default_electron_grid_generator;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
