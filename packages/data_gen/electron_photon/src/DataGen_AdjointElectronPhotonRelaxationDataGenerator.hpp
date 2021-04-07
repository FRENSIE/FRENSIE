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
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
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

  //! Set the table notes
  void setNotes( const std::string& notes );

  //! Return the table notes
  const std::string& getNotes() const;

  //! Get the atomic number
  unsigned getAtomicNumber() const;

  ///////////////////////
  // Photon Table Data //
  ///////////////////////

  //! Return the min photon energy
  double getMinPhotonEnergy() const;

  //! Return the max photon energy
  double getMaxPhotonEnergy() const;

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

  //! Set the photon threshold energy nudge factor
  void setPhotonThresholdEnergyNudgeFactor( const double nudge_factor );

  //! Get the photon threshold energy nudge factor
  double getPhotonThresholdEnergyNudgeFactor() const;

  //! Set the adjoint pair production energy dist. norm const. evaluation tol.
  void setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Return the adjoint pair production energy dist. norm const. evaluation tol
  double getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance() const;

  //! Set the adjoint pair production energy dist. norm const. nudge value
  void setAdjointPairProductionEnergyDistNormConstantNudgeValue(
                                                    const double nudge_value );

  //! Return the adjoint pair production energy dist. norm const. nudge value
  double getAdjointPairProductionEnergyDistNormConstantNudgeValue() const;

  //! Set the adjoint triplet production energy dist. norm const. evaluation tol.
  void setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Return the adjoint triplet production energy dist. norm const. evaluation tol
  double getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance() const;

  //! Set the adjoint triplet production energy dist. norm const. nudge value
  void setAdjointTripletProductionEnergyDistNormConstantNudgeValue(
                                                    const double nudge_value );

  //! Return the adjoint triplet production energy dist. norm const. nudge value
  double getAdjointTripletProductionEnergyDistNormConstantNudgeValue() const;

  //! Set the adjoint incoherent max energy nudge value
  void setAdjointIncoherentMaxEnergyNudgeValue( const double max_energy_nudge_value );

  //! Return the adjoint incoherent max energy nudge value
  double getAdjointIncoherentMaxEnergyNudgeValue() const;

  //! Set the adjoint incoherent energy to max energy nudge value
  void setAdjointIncoherentEnergyToMaxEnergyNudgeValue(
                               const double energy_to_max_energy_nudge_value );

  //! Return the adjoint incoherent energy to max energy nudge value
  double getAdjointIncoherentEnergyToMaxEnergyNudgeValue() const;

  //! Set the adjoint incoherent cross section evaluation tolerance
  void setAdjointIncoherentEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Return the adjoint incoherent cross section evaluation tolerance
  double getAdjointIncoherentEvaluationTolerance() const;

  //! Set the adjoint incoherent grid convergence tolerance
  void setAdjointIncoherentGridConvergenceTolerance(
                                                const double convergence_tol );

  //! Return the adjoint incoherent grid convergence tolerance
  double getAdjointIncoherentGridConvergenceTolerance() const;

  //! Set the adjoint incoherent grid absolute difference tolerance
  void setAdjointIncoherentGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Return the adjoint incoherent grid absolute difference tolerance
  double getAdjointIncoherentGridAbsoluteDifferenceTolerance() const;

  //! Set the adjoint incoherent grid distance tolerance
  void setAdjointIncoherentGridDistanceTolerance( const double distance_tol );

  //! Return the adjoint incoherent grid distance tolerance
  double getAdjointIncoherentGridDistanceTolerance() const;

  /////////////////////////
  // Electron Table Data //
  /////////////////////////

  //! Return the min electron energy
  double getMinElectronEnergy() const;

  //! Return the max electron energy
  double getMaxElectronEnergy() const;

  //! Set the electron scatter above max energy mode is on (on by default)
  void setElectronScatterAboveMaxModeOn();

  //! Set the electron scatter above max energy mode is off (on by default)
  void setElectronScatterAboveMaxModeOff();

  //! Return if the electron scatter above max energy mode is on
  bool isElectronScatterAboveMaxModeOn() const;

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

  //! Set the cutoff angle cosine above which screened rutherford is used
  void setCutoffAngleCosine( const double angle_cutoff );

  //! Return the cutoff angle cosine above which screened rutherford is used
  double getCutoffAngleCosine() const;

  //! Set the number of moment preserving angles
  void setNumberOfMomentPreservingAngles( const unsigned number_of_angles );

  //! Return the number of moment preserving angles
  unsigned getNumberOfMomentPreservingAngles() const;

  //! Set the electron FullyTabularTwoDDistribution evaluation tolerance
  void setElectronTabularEvaluationTolerance( const double tabular_evaluation_tol );

  //! Return the electron FullyTabularTwoDDistribution evaluation tolerance
  double getElectronTabularEvaluationTolerance() const;

  //! Set the electron TwoDInterpPolicy (LogLogLog by default)
  void setElectronTwoDInterpPolicy( const MonteCarlo::TwoDInterpolationType two_d_interp );

  //! Return the electron TwoDInterpPolicy (LogLogLog by default)
  MonteCarlo::TwoDInterpolationType getElectronTwoDInterpPolicy() const;

  //! Set the electron TwoDGridPolicy (Unit-base Correlated by default)
  void setElectronTwoDGridPolicy( const MonteCarlo::TwoDGridType two_d_grid );

  //! Return the electron TwoDGridPolicy (Unit-base Correlated by default)
  MonteCarlo::TwoDGridType getElectronTwoDGridPolicy() const;

  //! Set the adjoint electron elastic sampling method (TWO_D_UNION by default)
  void setAdjointElectronElasticSamplingMethod( MonteCarlo::CoupledElasticSamplingMethod sampling );

  //! Return the adjoint electron elastic sampling method
  MonteCarlo::CoupledElasticSamplingMethod getAdjointElectronElasticSamplingMethod() const;

  //! Set the adjoint bremsstrahlung min energy nudge value
  void setAdjointBremsstrahlungMinEnergyNudgeValue( const double min_energy_nudge_value );

  //! Return the adjoint bremsstrahlung min energy nudge value
  double getAdjointBremsstrahlungMinEnergyNudgeValue() const;

  //! Set the adjoint bremsstrahlung max energy nudge value
  void setAdjointBremsstrahlungMaxEnergyNudgeValue( const double max_energy_nudge_value );

  //! Return the adjoint bremsstrahlung max energy nudge value
  double getAdjointBremsstrahlungMaxEnergyNudgeValue() const;

  //! Set the adjoint bremsstrahlung cross section evaluation tolerance
  void setAdjointBremsstrahlungEvaluationTolerance( const double evaluation_tol );

  //! Return the adjoint bremsstrahlung cross section evaluation tolerance
  double getAdjointBremsstrahlungEvaluationTolerance() const;

  //! Set the adjoint bremsstrahlung grid convergence tolerance
  void setAdjointBremsstrahlungGridConvergenceTolerance( const double convergence_tol );

  //! Return the adjoint bremsstrahlung grid convergence tolerance
  double getAdjointBremsstrahlungGridConvergenceTolerance() const;

  //! Set the adjoint bremsstrahlung absolute difference tolerance
  void setAdjointBremsstrahlungAbsoluteDifferenceTolerance( const double absolute_diff_tol );

  //! Return the adjoint bremsstrahlung absolute difference tolerance
  double getAdjointBremsstrahlungAbsoluteDifferenceTolerance() const;

  //! Set the adjoint bremsstrahlung distance tolerance
  void setAdjointBremsstrahlungDistanceTolerance( const double distance_tol );

  //! Return the adjoint bremsstrahlung distance tolerance
  double getAdjointBremsstrahlungDistanceTolerance() const;

  //! Set the forward electroionization sampling mode
  void setForwardElectroionizationSamplingMode(
      const MonteCarlo::ElectroionizationSamplingType sampling_mode );

  //! Return the forward electroionization sampling mode
  MonteCarlo::ElectroionizationSamplingType getForwardElectroionizationSamplingMode() const;

  //! Set the adjoint electroionization min energy nudge value
  void setAdjointElectroionizationMinEnergyNudgeValue( const double min_energy_nudge_value );

  //! Return the adjoint electroionization min energy nudge value
  double getAdjointElectroionizationMinEnergyNudgeValue() const;

  //! Set the adjoint electroionization max energy nudge value
  void setAdjointElectroionizationMaxEnergyNudgeValue( const double max_energy_nudge_value );

  //! Return the adjoint electroionization max energy nudge value
  double getAdjointElectroionizationMaxEnergyNudgeValue() const;

  //! Set the adjoint electroionization cross section evaluation tolerance
  void setAdjointElectroionizationEvaluationTolerance( const double evaluation_tol );

  //! Return the adjoint electroionization cross section evaluation tolerance
  double getAdjointElectroionizationEvaluationTolerance() const;

  //! Set the adjoint electroionization grid convergence tolerance
  void setAdjointElectroionizationGridConvergenceTolerance( const double convergence_tol );

  //! Return the adjoint electroionization grid convergence tolerance
  double getAdjointElectroionizationGridConvergenceTolerance() const;

  //! Set the adjoint electroionization absolute difference tolerance
  void setAdjointElectroionizationAbsoluteDifferenceTolerance( const double absolute_diff_tol );

  //! Return the adjoint electroionization absolute difference tolerance
  double getAdjointElectroionizationAbsoluteDifferenceTolerance() const;

  //! Set the adjoint electroionization distance tolerance
  void setAdjointElectroionizationDistanceTolerance( const double distance_tol );

  //! Return the adjoint electroionization distance tolerance
  double getAdjointElectroionizationDistanceTolerance() const;


  //! Populate the electron-photon-relaxation data container
  virtual void populateEPRDataContainer(
    const bool populate_photons,
    const bool populate_electrons ) = 0;

  //! Get the data container
  const Data::AdjointElectronPhotonRelaxationDataContainer& getDataContainer() const;

  //! Get the shared data container
  std::shared_ptr<const Data::AdjointElectronPhotonRelaxationDataContainer> getSharedDataContainer() const;

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

  // Convert string to TwoDInterpolationType
  const MonteCarlo::TwoDInterpolationType
  convertStringToTwoDInterpType( const std::string& raw_policy ) const;

  // Convert string to TwoDGridType
  const MonteCarlo::TwoDGridType convertStringToTwoDGridType( const std::string& raw_policy ) const;

  // Convert string to ElectroionizationSamplingType
  const MonteCarlo::ElectroionizationSamplingType convertStringToElectroionizationSamplingType(
      const std::string& raw_policy ) const;

  // The adjoint electron-photon-relaxation volatile data container
  std::shared_ptr<Data::AdjointElectronPhotonRelaxationVolatileDataContainer> d_data_container;

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

  // The electron elastic sampling method
  MonteCarlo::CoupledElasticSamplingMethod d_elastic_sampling_method;

  // The forward ElectroionizationSamplingType (Knock-on - default)
  MonteCarlo::ElectroionizationSamplingType d_forward_electroionization_sampling_mode;

  bool d_scatter_above_max;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
