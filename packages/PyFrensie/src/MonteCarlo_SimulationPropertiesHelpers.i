//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationPropertiesHelpers.i
//! \author Luke Kersting
//! \brief  The MonteCarlo simulation properties helper macros
//!
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// Helper macro for setting up the general simulation properties class python interface
//---------------------------------------------------------------------------//
%define %general_simulation_properties_setup_helper( PROPERTIES )

// Set/get Particle Mode
%feature("autodoc", "setParticleMode(PROPERTIES self, const ParticleModeType particle_mode) -> void")
MonteCarlo::PROPERTIES::setParticleMode;

%feature("autodoc", "getParticleMode(PROPERTIES self) -> ParticleModeType")
MonteCarlo::PROPERTIES::getParticleMode;

// Set/get Number Of Histories
%feature("autodoc", "setNumberOfHistories(PROPERTIES self, const unsigned long long histories) -> void")
MonteCarlo::PROPERTIES::setNumberOfHistories;

%feature("autodoc", "getNumberOfHistories(PROPERTIES self) -> unsigned long long")
MonteCarlo::PROPERTIES::getNumberOfHistories;

// Set/get Surface Flux Estimator Angle Cosine Cutoff
%feature("autodoc", "setSurfaceFluxEstimatorAngleCosineCutoff(PROPERTIES self, const double cutoff) -> void")
MonteCarlo::PROPERTIES::setSurfaceFluxEstimatorAngleCosineCutoff;

%feature("autodoc", "getSurfaceFluxEstimatorAngleCosineCutoff(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getSurfaceFluxEstimatorAngleCosineCutoff;

// Set atomic relaxation on/off
%feature("autodoc", "setWarningsOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setWarningsOff;

%feature("autodoc", "setWarningsOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setWarningsOn;

%feature("autodoc", "displayWarnings(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::displayWarnings;

// Set atomic relaxation on/off
%feature("autodoc", "setImplicitCaptureModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setImplicitCaptureModeOff;

%feature("autodoc", "setImplicitCaptureModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setImplicitCaptureModeOn;

%feature("autodoc", "isImplicitCaptureModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isImplicitCaptureModeOn;

// Set/get max energy
%feature("autodoc", "setNumberOfBatchesPerProcessor(PROPERTIES self, const unsigned batches_per_processor) -> void")
MonteCarlo::PROPERTIES::setNumberOfBatchesPerProcessor;

%feature("autodoc", "getNumberOfBatchesPerProcessor(PROPERTIES self) -> unsigned")
MonteCarlo::PROPERTIES::getNumberOfBatchesPerProcessor;


%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic particle simulation properties class python interface
//---------------------------------------------------------------------------//
%define %basic_simulation_properties_setup_helper( PARTICLE )

// Set/get min energy
%feature("autodoc", "setMin ## PARTICLE ## Energy(PROPERTIES self, const double energy) -> void")
MonteCarlo::PROPERTIES::setMin ## PARTICLE ## Energy;

%feature("autodoc", "getMin ## PARTICLE ## Energy(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getMin ## PARTICLE ## Energy;

// Set/get max energy
%feature("autodoc", "setMax ## PARTICLE ## Energy(PROPERTIES self, const double energy) -> void")
MonteCarlo::PROPERTIES::setMax ## PARTICLE ## Energy;

%feature("autodoc", "getMax ## PARTICLE ## Energy(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getMax ## PARTICLE ## Energy;

// Get min/max absolute energy
%feature("autodoc", "getAbsoluteMin ## PARTICLE ## Energy(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getAbsoluteMin ## PARTICLE ## Energy;

%feature("autodoc", "getAbsoluteMax ## PARTICLE ## Energy(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getAbsoluteMax ## PARTICLE ## Energy;

// Set/get number of hash grid bins
%feature("autodoc", "setNumberOf ## PARTICLE ## HashGridBins(PROPERTIES self, const unsigned bins) -> void")
MonteCarlo::PROPERTIES::setNumberOf ## PARTICLE ## HashGridBins;

%feature("autodoc", "getNumberOf ## PARTICLE ## HashGridBins(PROPERTIES self) -> unsigned")
MonteCarlo::PROPERTIES::getNumberOf ## PARTICLE ## HashGridBins;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up an atomic simulation properties class python interface
//---------------------------------------------------------------------------//
%define %atomic_simulation_properties_setup_helper( PROPERTIES )

// Set atomic relaxation on/off
%feature("autodoc", "setAtomicRelaxationModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAtomicRelaxationModeOff;

%feature("autodoc", "setAtomicRelaxationModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAtomicRelaxationModeOn;

%feature("autodoc", "isAtomicRelaxationModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isAtomicRelaxationModeOn;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up an neutron simulation properties class python interface
//---------------------------------------------------------------------------//
%define %neutron_simulation_properties_setup_helper( PROPERTIES )

// Set/get free gas threshold
%feature("autodoc", "setFreeGasThreshold(PROPERTIES self, const double threshold) -> void")
MonteCarlo::PROPERTIES::setFreeGasThreshold;

%feature("autodoc", "getFreeGasThreshold(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getFreeGasThreshold;

// Set unresolved resonance probability table mode On/Off
%feature("autodoc", "setUnresolvedResonanceProbabilityTableModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setUnresolvedResonanceProbabilityTableModeOn;

%feature("autodoc", "setUnresolvedResonanceProbabilityTableModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setUnresolvedResonanceProbabilityTableModeOff;

%feature("autodoc", "isUnresolvedResonanceProbabilityTableModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isUnresolvedResonanceProbabilityTableModeOn;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up photon simulation properties class python interface
//---------------------------------------------------------------------------//
%define %photon_simulation_properties_setup_helper( PROPERTIES )

// Set/get incoherent model type
%feature("autodoc", "setIncoherentModelType(PROPERTIES self, const IncoherentModelType model) -> void")
MonteCarlo::PROPERTIES::setIncoherentModelType;

%feature("autodoc", "getIncoherentModelType(PROPERTIES self) -> IncoherentModelType")
MonteCarlo::PROPERTIES::getIncoherentModelType;

// Set detailed pair production mode On/Off
%feature("autodoc", "setDetailedPairProductionModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setDetailedPairProductionModeOn;

%feature("autodoc", "setDetailedPairProductionModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setDetailedPairProductionModeOff;

%feature("autodoc", "isDetailedPairProductionModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isDetailedPairProductionModeOn;

// Set photonuclear interaction mode On/Off
%feature("autodoc", "setPhotonuclearInteractionModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setPhotonuclearInteractionModeOn;

%feature("autodoc", "setPhotonuclearInteractionModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setPhotonuclearInteractionModeOff;

%feature("autodoc", "isPhotonuclearInteractionModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isPhotonuclearInteractionModeOn;

%atomic_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up adjoint photon simulation properties class python interface
//---------------------------------------------------------------------------//
%define %adjoint_photon_simulation_properties_setup_helper( PROPERTIES )

// Set/get incoherent model type
%feature("autodoc", "setIncoherentAdjointModelType(PROPERTIES self, const IncoherentAdjointModelType model) -> void")
MonteCarlo::PROPERTIES::setIncoherentAdjointModelType;

%feature("autodoc", "getIncoherentAdjointModelType(PROPERTIES self) -> IncoherentAdjointModelType")
MonteCarlo::PROPERTIES::getIncoherentAdjointModelType;

// Set/get the critical line energies
%feature("autodoc", "setCriticalAdjointPhotonLineEnergies(PROPERTIES self, const std::vector<double>& critical_line_energies) -> void")
MonteCarlo::PROPERTIES::setCriticalAdjointPhotonLineEnergies;

%feature("autodoc", "getCriticalAdjointPhotonLineEnergies(PROPERTIES self) -> const std::vector<double>&")
MonteCarlo::PROPERTIES::getCriticalAdjointPhotonLineEnergies;

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up electron simulation properties class python interface
//---------------------------------------------------------------------------//
%define %electron_simulation_properties_setup_helper( PROPERTIES )

// Set/get Electron TwoDInterpPolicy
%feature("autodoc", "setElectronTwoDInterpPolicy(PROPERTIES self, const TwoDInterpolationType interp_type) -> void")
MonteCarlo::PROPERTIES::setElectronTwoDInterpPolicy;

%feature("autodoc", "getElectronTwoDInterpPolicy(PROPERTIES self) -> TwoDInterpolationType")
MonteCarlo::PROPERTIES::getElectronTwoDInterpPolicy;

// Set/get Electron TwoDGridPolicy
%feature("autodoc", "setElectronTwoDGridPolicy(PROPERTIES self, const TwoDGridType sampling_type) -> void")
MonteCarlo::PROPERTIES::setElectronTwoDGridPolicy;

%feature("autodoc", "getElectronTwoDGridPolicy(PROPERTIES self) -> TwoDGridType")
MonteCarlo::PROPERTIES::getElectronTwoDGridPolicy;

// Set/get Evaluation Tolerance
%feature("autodoc", "setElectronEvaluationTolerance(PROPERTIES self, const double tol) -> void")
MonteCarlo::PROPERTIES::setElectronEvaluationTolerance;

%feature("autodoc", "getElectronEvaluationTolerance(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getElectronEvaluationTolerance;

// Set Elastic Mode On/Off
%feature("autodoc", "setElasticModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setElasticModeOn;

%feature("autodoc", "setElasticModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setElasticModeOff;

%feature("autodoc", "isElasticModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isElasticModeOn;

// Set/get Elastic Electron Distribution Mode
%feature("autodoc", "setElasticElectronDistributionMode(PROPERTIES self, const ElasticElectronDistributionType distribution_mode) -> void")
MonteCarlo::PROPERTIES::setElasticElectronDistributionMode;

%feature("autodoc", "getElasticElectronDistributionMode(PROPERTIES self) -> ElasticElectronDistributionType")
MonteCarlo::PROPERTIES::getElasticElectronDistributionMode;

// Set/get Coupled Elastic Sampling Mode
%feature("autodoc", "setCoupledElasticSamplingMode(PROPERTIES self, const CoupledElasticSamplingMethod sampling_method) -> void")
MonteCarlo::PROPERTIES::setCoupledElasticSamplingMode;

%feature("autodoc", "getCoupledElasticSamplingMode(PROPERTIES self) -> CoupledElasticSamplingMethod")
MonteCarlo::PROPERTIES::getCoupledElasticSamplingMode;

// Set/get Elastic Cutoff Angle Cosine
%feature("autodoc", "setElasticCutoffAngleCosine(PROPERTIES self, const double cutoff_angle_cosine ) -> void")
MonteCarlo::PROPERTIES::setElasticCutoffAngleCosine;

%feature("autodoc", "getElasticCutoffAngleCosine(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getElasticCutoffAngleCosine;

// Set Electroionization mode On/Off
%feature("autodoc", "setElectroionizationModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setElectroionizationModeOn;

%feature("autodoc", "setElectroionizationModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setElectroionizationModeOff;

%feature("autodoc", "isElectroionizationModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isElectroionizationModeOn;

// Set Bremsstrahlung mode On/Off
%feature("autodoc", "setBremsstrahlungModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setBremsstrahlungModeOn;

%feature("autodoc", "setBremsstrahlungModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setBremsstrahlungModeOff;

%feature("autodoc", "isBremsstrahlungModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isBremsstrahlungModeOn;

// Set/get Bremsstrahlung Angular Distribution Function
%feature("autodoc", "setBremsstrahlungAngularDistributionFunction(PROPERTIES self, const BremsstrahlungAngularDistributionType function) -> void")
MonteCarlo::PROPERTIES::setBremsstrahlungAngularDistributionFunction;

%feature("autodoc", "getBremsstrahlungAngularDistributionFunction(PROPERTIES self) -> BremsstrahlungAngularDistributionType")
MonteCarlo::PROPERTIES::getBremsstrahlungAngularDistributionFunction;

// Set Atomic Excitation mode On/Off
%feature("autodoc", "setAtomicExcitationModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAtomicExcitationModeOn;

%feature("autodoc", "setAtomicExcitationModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAtomicExcitationModeOff;

%feature("autodoc", "isAtomicExcitationModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isAtomicExcitationModeOn;

// Set/get the critical line energies
%feature("autodoc", "setCriticalAdjointElectronLineEnergies(PROPERTIES self, const std::vector<double>& critical_line_energies) -> void")
MonteCarlo::PROPERTIES::setCriticalAdjointElectronLineEnergies;

%feature("autodoc", "getCriticalAdjointElectronLineEnergies(PROPERTIES self) -> const std::vector<double>&")
MonteCarlo::PROPERTIES::getCriticalAdjointElectronLineEnergies;

%atomic_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for setting up adjoint electron simulation properties class python interface
//---------------------------------------------------------------------------//
%define %adjoint_electron_simulation_properties_setup_helper( PROPERTIES )

// Set/get Evaluation Tolerance
%feature("autodoc", "setAdjointElectronEvaluationTolerance(PROPERTIES self, const double tol) -> void")
MonteCarlo::PROPERTIES::setAdjointElectronEvaluationTolerance;

%feature("autodoc", "getAdjointElectronEvaluationTolerance(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getAdjointElectronEvaluationTolerance;

// Set Elastic Mode On/Off
%feature("autodoc", "setAdjointElasticModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointElasticModeOn;

%feature("autodoc", "setAdjointElasticModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointElasticModeOff;

%feature("autodoc", "isAdjointElasticModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isAdjointElasticModeOn;

// Set/get Elastic Electron Distribution Mode
%feature("autodoc", "setAdjointElasticElectronDistributionMode(PROPERTIES self, const ElasticElectronDistributionType distribution_mode) -> void")
MonteCarlo::PROPERTIES::setAdjointElasticElectronDistributionMode;

%feature("autodoc", "getAdjointElasticElectronDistributionMode(PROPERTIES self) -> ElasticElectronDistributionType")
MonteCarlo::PROPERTIES::getAdjointElasticElectronDistributionMode;

// Set/get Coupled Elastic Sampling Mode
%feature("autodoc", "setAdjointCoupledElasticSamplingMode(PROPERTIES self, const CoupledElasticSamplingMethod sampling_method) -> void")
MonteCarlo::PROPERTIES::setAdjointCoupledElasticSamplingMode;

%feature("autodoc", "getAdjointCoupledElasticSamplingMode(PROPERTIES self) -> CoupledElasticSamplingMethod")
MonteCarlo::PROPERTIES::getAdjointCoupledElasticSamplingMode;

// Set/get Elastic Cutoff Angle Cosine
%feature("autodoc", "setAdjointElasticCutoffAngleCosine(PROPERTIES self, const double cutoff_angle_cosine ) -> void")
MonteCarlo::PROPERTIES::setAdjointElasticCutoffAngleCosine;

%feature("autodoc", "getAdjointElasticCutoffAngleCosine(PROPERTIES self) -> double")
MonteCarlo::PROPERTIES::getAdjointElasticCutoffAngleCosine;

// Set Electroionization mode On/Off
%feature("autodoc", "setAdjointElectroionizationModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointElectroionizationModeOn;

%feature("autodoc", "setAdjointElectroionizationModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointElectroionizationModeOff;

%feature("autodoc", "isAdjointElectroionizationModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isAdjointElectroionizationModeOn;

// Set Bremsstrahlung mode On/Off
%feature("autodoc", "setAdjointBremsstrahlungModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointBremsstrahlungModeOn;

%feature("autodoc", "setAdjointBremsstrahlungModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointBremsstrahlungModeOff;

%feature("autodoc", "isAdjointBremsstrahlungModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isAdjointBremsstrahlungModeOn;

// Set/get Bremsstrahlung Angular Distribution Function
%feature("autodoc", "setAdjointBremsstrahlungAngularDistributionFunction(PROPERTIES self, const BremsstrahlungAngularDistributionType function) -> void")
MonteCarlo::PROPERTIES::setAdjointBremsstrahlungAngularDistributionFunction;

%feature("autodoc", "getAdjointBremsstrahlungAngularDistributionFunction(PROPERTIES self) -> BremsstrahlungAngularDistributionType")
MonteCarlo::PROPERTIES::getAdjointBremsstrahlungAngularDistributionFunction;

// Set Atomic Excitation mode On/Off
%feature("autodoc", "setAdjointAtomicExcitationModeOn(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointAtomicExcitationModeOn;

%feature("autodoc", "setAdjointAtomicExcitationModeOff(PROPERTIES self) -> void")
MonteCarlo::PROPERTIES::setAdjointAtomicExcitationModeOff;

%feature("autodoc", "isAdjointAtomicExcitationModeOn(PROPERTIES self) -> bool")
MonteCarlo::PROPERTIES::isAdjointAtomicExcitationModeOn;

%atomic_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up the general simulation properties class python interface
//---------------------------------------------------------------------------//
%define %general_properties_setup( PROPERTIES )

%general_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up the neutron simulation properties class python interface
//---------------------------------------------------------------------------//
%define %neutron_properties_setup( PROPERTIES )

%basic_simulation_properties_setup_helper( Neutron )

%neutron_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up the photon simulation properties class python interface
//---------------------------------------------------------------------------//
%define %photon_properties_setup( PROPERTIES )

%basic_simulation_properties_setup_helper( Photon )

%photon_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up the electron simulation properties class python interface
//---------------------------------------------------------------------------//
%define %electron_properties_setup( PROPERTIES )

%basic_simulation_properties_setup_helper( Electron )

%electron_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up the adjoint photon simulation properties class python interface
//---------------------------------------------------------------------------//
%define %adjoint_photon_properties_setup( PROPERTIES )

%basic_simulation_properties_setup_helper( AdjointPhoton )

%adjoint_photon_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up the adjoint electron simulation properties class python interface
//---------------------------------------------------------------------------//
%define %adjoint_electron_properties_setup( PROPERTIES )

%basic_simulation_properties_setup_helper( AdjointElectron )

%adjoint_electron_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// Macro for setting up the simulation properties class python interface
//---------------------------------------------------------------------------//
%define %simulation_properties_setup( PROPERTIES )

%feature("docstring") Geometry::MODEL
"The MODEL class stores a geometric model. It can be used for querying
properties of the geometry and for creating navigators,
which can be used to traverse the geometry."

%basic_simulation_properties_setup_helper( Neutron )
%basic_simulation_properties_setup_helper( Photon )
%basic_simulation_properties_setup_helper( Electron )
%basic_simulation_properties_setup_helper( AdjointPhoton )
%basic_simulation_properties_setup_helper( AdjointElectron )

%general_simulation_properties_setup_helper( PROPERTIES )
%neutron_simulation_properties_setup_helper( PROPERTIES )
%photon_simulation_properties_setup_helper( PROPERTIES )
%electron_simulation_properties_setup_helper( PROPERTIES )
%adjoint_photon_simulation_properties_setup_helper( PROPERTIES )
%adjoint_electron_simulation_properties_setup_helper( PROPERTIES )

%enddef

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationPropertiesHelpers.i
//---------------------------------------------------------------------------//