//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting, Alex Robinson
//! \brief  The adjoint electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDGridType.hpp"
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
                                          const double atomic_weight,
                                          const double min_photon_energy,
                                          const double max_photon_energy,
                                          const double min_electron_energy,
                                          const double max_electron_energy );

  //! Constructor (existing data container)
  AdjointElectronPhotonRelaxationDataGenerator(
                          const boost::filesystem::path& file_name_with_path );

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

  //! Set the default photon grid convergence tolerance
  void setPhotonGridConvergenceTolerance( const double convergence_tol );

  //! Get the default photon grid convergence tolerance
  double getPhotonGridConvergenceTolerance() const;

  //! Set the default photon grid absolute difference tolerance
  void setPhotonGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the default photon grid absolute difference tolerance
  double getPhotonGridAbsoluteDifferenceTolerance() const;

  //! Set the default photon grid distance tolerance
  void setPhotonGridDistanceTolerance( const double distance_tol );

  //! Get the default photon grid distance tolerance
  double getPhotonGridDistanceTolerance() const;

  //! Set the default electron grid convergence tolerance
  void setElectronGridConvergenceTolerance( const double convergence_tol );

  //! Get the default electron grid convergence tolerance
  double getElectronGridConvergenceTolerance() const;

  //! Set the default electron grid absolute difference tolerance
  void setElectronGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the default electron grid absolute difference tolerance
  double getElectronGridAbsoluteDifferenceTolerance() const;

  //! Set the default electron grid distance tolerance
  void setElectronGridDistanceTolerance( const double distance_tol );

  //! Get the default electron grid distance tolerance
  double getElectronGridDistanceTolerance() const;

  //! Populate the electron-photon-relaxation data container
  virtual void populateEPRDataContainer(
    const bool populate_photons,
    const bool populate_electrons ) = 0;

  //! Get the data container
  const Data::AdjointElectronPhotonRelaxationDataContainer& getDataContainer() const;

protected:

  //! Set the min photon energy
  void setMinPhotonEnergy( const double min_photon_energy );

  //! Set the max photon energy
  void setMaxPhotonEnergy( const double max_photon_energy );

  //! Set the min electron energy
  void setMinElectronEnergy( const double min_electron_energy );

  //! Set the max electron energy
  void setMaxElectronEnergy( const double max_electron_energy );

  //! Get the volatile data container
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer& getVolatileDataContainer();

  //! Get a default photon grid generator (Lin-Lin grid)
  const Utility::GridGenerator<Utility::LinLin>&
  getDefaultPhotonGridGenerator() const;

  //! Get a default electron grid generator (Log-Log grid)
  const Utility::GridGenerator<Utility::LogLog>&
  getDefaultElectronGridGenerator() const;

private:

  // The adjoint electron-photon-relaxation volatile data container
  Data::AdjointElectronPhotonRelaxationVolatileDataContainer d_data_container;

  // The default photon grid generator
  std::unique_ptr<Utility::GridGenerator<Utility::LinLin> >
  d_default_photon_grid_generator;

  // The default electron grid generator
  std::unique_ptr<Utility::GridGenerator<Utility::LogLog> >
  d_default_electron_grid_generator;

  // The electron TwoDInterpPolicy (LogLogLog - default)
  MonteCarlo::TwoDInterpolationType d_two_d_interp;

  // The electron TwoDGridPolicy (Unit-base Correlated - default)
  MonteCarlo::TwoDGridType d_two_d_grid;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
