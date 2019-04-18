//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// Std Lib Include
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDGridType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Utility_GridGenerator.hpp"

namespace DataGen{

//! The electron-photon-relaxation data generator base class
class ElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  ElectronPhotonRelaxationDataGenerator( const unsigned atomic_number,
                                         const double atomic_weight,
                                         const double min_photon_energy,
                                         const double max_photon_energy,
                                         const double min_electron_energy,
                                         const double max_electron_energy );

  //! Constructor (existing data container)
  ElectronPhotonRelaxationDataGenerator(
                          const boost::filesystem::path& file_name_with_path );

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

  //! Set the occupation number evaluation tolerance
  void setOccupationNumberEvaluationTolerance(
                                           const double evaluation_tolerance );

  //! Get the occupation number evaluation tolerance
  double getOccupationNumberEvaluationTolerance() const;

  //! Set the subshell incoherent evaluation tolerance
  void setSubshellIncoherentEvaluationTolerance(
                                           const double evaluation_tolerance );

  //! Get the subshell incoherent evaluation tolerance
  double getSubshellIncoherentEvaluationTolerance() const;

  //! Set the photon threshold energy nudge factor
  void setPhotonThresholdEnergyNudgeFactor( const double nudge_factor );

  //! Get the photon threshold energy nudge factor
  double getPhotonThresholdEnergyNudgeFactor() const;

  //! Set the cutoff angle cosine
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Get the cutoff angle cosine
  double getCutoffAngleCosine() const;

  //! Set the number of moment preserving angles
  void setNumberOfMomentPreservingAngles( const unsigned number_of_angles );

  //! Get the number of moment preserving angles
  double getNumberOfMomentPreservingAngles() const;

  //! Set the FullyTabularTwoDDistribution evaluation tolerance
  void setTabularEvaluationTolerance( const double evaluation_tolerance );

  //! Get the FullyTabularTwoDDistribution evaluation tolerance
  double getTabularEvaluationTolerance() const;

  //! Set the electron TwoDInterpPolicy (LogLogLog by default)
  void setElectronTwoDInterpPolicy( MonteCarlo::TwoDInterpolationType interp );

  //! Return the electron TwoDInterpPolicy
  MonteCarlo::TwoDInterpolationType getElectronTwoDInterpPolicy() const;

  //! Set the electron TwoDGridPolicy (LogLogLog by default)
  void setElectronTwoDGridPolicy( MonteCarlo::TwoDGridType sampling );

  //! Return the electron TwoDGridPolicy
  MonteCarlo::TwoDGridType getElectronTwoDGridPolicy() const;

  //! Set refine secondary electron grids mode on (Default off)
  void setRefineSecondaryElectronGridsModeOn();

  //! Set refine secondary electron grids mode off (Default off)
  void setRefineSecondaryElectronGridsModeOff();

  //! Return if the refine secondary electron grids mode is on (default off)
  bool isRefineSecondaryElectronGridsModeOn();

  //! Set the electron elastic sampling method (TWO_D_UNION by default)
  void setElectronElasticSamplingMethod( MonteCarlo::CoupledElasticSamplingMethod sampling );

  //! Return the electron elastic sampling method
  MonteCarlo::CoupledElasticSamplingMethod getElectronElasticSamplingMethod() const;

  //! Set the bremsstrahlung cross section evaluation tolerance
  void setBremsstrahlungEvaluationTolerance( const double evaluation_tol );

  //! Return the bremsstrahlung cross section evaluation tolerance
  double getBremsstrahlungEvaluationTolerance() const;

  //! Set the bremsstrahlung grid convergence tolerance
  void setBremsstrahlungGridConvergenceTolerance( const double convergence_tol );

  //! Return the bremsstrahlung grid convergence tolerance
  double getBremsstrahlungGridConvergenceTolerance() const;

  //! Set the bremsstrahlung absolute difference tolerance
  void setBremsstrahlungAbsoluteDifferenceTolerance( const double absolute_diff_tol );

  //! Return the bremsstrahlung absolute difference tolerance
  double getBremsstrahlungAbsoluteDifferenceTolerance() const;

  //! Set the bremsstrahlung distance tolerance
  void setBremsstrahlungDistanceTolerance( const double distance_tol );

  //! Return the bremsstrahlung distance tolerance
  double getBremsstrahlungDistanceTolerance() const;

  //! Set the electroionization cross section evaluation tolerance
  void setElectroionizationEvaluationTolerance( const double evaluation_tol );

  //! Return the electroionization cross section evaluation tolerance
  double getElectroionizationEvaluationTolerance() const;

  //! Set the electroionization grid convergence tolerance
  void setElectroionizationGridConvergenceTolerance( const double convergence_tol );

  //! Return the electroionization grid convergence tolerance
  double getElectroionizationGridConvergenceTolerance() const;

  //! Set the electroionization absolute difference tolerance
  void setElectroionizationAbsoluteDifferenceTolerance( const double absolute_diff_tol );

  //! Return the electroionization absolute difference tolerance
  double getElectroionizationAbsoluteDifferenceTolerance() const;

  //! Set the electroionization distance tolerance
  void setElectroionizationDistanceTolerance( const double distance_tol );

  //! Return the electroionization distance tolerance
  double getElectroionizationDistanceTolerance() const;

  //! Set the generation notes
  void setNotes( const std::string& notes );

  //! Get the generation notes
  const std::string& getNotes() const;

  //! Populate the electron-photon-relaxation data container
  virtual void populateEPRDataContainer() = 0;

  //! Get the data container
  const Data::ElectronPhotonRelaxationDataContainer& getDataContainer() const;

  //! Get the shared data container
  std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer> getSharedDataContainer() const;

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
  Data::ElectronPhotonRelaxationVolatileDataContainer& getVolatileDataContainer();

  //! Get a default photon grid generator (Lin-Lin grid)
  const Utility::GridGenerator<Utility::LinLin>&
  getDefaultPhotonGridGenerator() const;

  //! Get a default electron grid generator (Log-Log grid)
  const Utility::GridGenerator<Utility::LogLog>&
  getDefaultElectronGridGenerator() const;

private:

  // The electron-photon-relaxation volatile data container
  std::shared_ptr<Data::ElectronPhotonRelaxationVolatileDataContainer> d_data_container;

  // The default photon grid generator
  std::unique_ptr<Utility::GridGenerator<Utility::LinLin> >
  d_default_photon_grid_generator;

  // The default electron grid generator
  std::unique_ptr<Utility::GridGenerator<Utility::LogLog> >
  d_default_electron_grid_generator;

  // The refine secondary electron grid mode bollean
  bool d_refine_secondary_electron_grid_mode;

  // The electron elastic sampling method
  MonteCarlo::CoupledElasticSamplingMethod d_elastic_sampling_method;

  // The electron TwoDInterpPolicy (LogLogLog - default)
  MonteCarlo::TwoDInterpolationType d_two_d_interp;

  // The electron TwoDGridPolicy (Unit-base Correlated - default)
  MonteCarlo::TwoDGridType d_two_d_grid;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
