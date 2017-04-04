//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationVolatileDataContainer.hpp
//! \author Alex Robinson
//! \brief  The native electron-photon-relaxation volatile data container class
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_VOLATILE_DATA_CONTAINER_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_VOLATILE_DATA_CONTAINER_HPP

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace Data{

//! The electron-photon-relaxation volatile data container
class ElectronPhotonRelaxationVolatileDataContainer : public ElectronPhotonRelaxationDataContainer
{

public:

  //! Default constructor
  ElectronPhotonRelaxationVolatileDataContainer();

  //! Constructor (from saved archive)
  ElectronPhotonRelaxationVolatileDataContainer(
                   const std::string& archive_name,
                   const Utility::ArchivableObject::ArchiveType archive_type );

  // Add the setter member functions to the public interface
  using ElectronPhotonRelaxationDataContainer::setNotes;
  using ElectronPhotonRelaxationDataContainer::setAtomicNumber;
  using ElectronPhotonRelaxationDataContainer::setMinPhotonEnergy;
  using ElectronPhotonRelaxationDataContainer::setMaxPhotonEnergy;
  using ElectronPhotonRelaxationDataContainer::setMinElectronEnergy;
  using ElectronPhotonRelaxationDataContainer::setMaxElectronEnergy;
  using ElectronPhotonRelaxationDataContainer::setOccupationNumberEvaluationTolerance;
  using ElectronPhotonRelaxationDataContainer::setSubshellIncoherentEvaluationTolerance;
  using ElectronPhotonRelaxationDataContainer::setPhotonThresholdEnergyNudgeFactor;
  using ElectronPhotonRelaxationDataContainer::setCutoffAngleCosine;
  using ElectronPhotonRelaxationDataContainer::setNumberOfMomentPreservingAngles;
  using ElectronPhotonRelaxationDataContainer::setElectronTabularEvaluationTolerance;
  using ElectronPhotonRelaxationDataContainer::setElectronLinLinLogInterpolationModeOnOff;
  using ElectronPhotonRelaxationDataContainer::setElectronCorrelatedSamplingModeOnOff;
  using ElectronPhotonRelaxationDataContainer::setElectronUnitBasedInterpolationModeOnOff;
  using ElectronPhotonRelaxationDataContainer::setGridConvergenceTolerance;
  using ElectronPhotonRelaxationDataContainer::setGridAbsoluteDifferenceTolerance;
  using ElectronPhotonRelaxationDataContainer::setGridDistanceTolerance;

  // Relaxation functions
  using ElectronPhotonRelaxationDataContainer::setSubshells;
  using ElectronPhotonRelaxationDataContainer::setSubshellOccupancy;
  using ElectronPhotonRelaxationDataContainer::setSubshellBindingEnergy;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationTransitions;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationVacancies;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationParticleEnergies;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationProbabilities;
  using ElectronPhotonRelaxationDataContainer::setComptonProfileMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setComptonProfile;
  using ElectronPhotonRelaxationDataContainer::setOccupationNumberMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setOccupationNumber;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunctionMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunction;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactorMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactor;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeSquaredAtomicFormFactor;
  using ElectronPhotonRelaxationDataContainer::setPhotonEnergyGrid;
  using ElectronPhotonRelaxationDataContainer::setAveragePhotonHeatingNumbers;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeIncoherentCrossSection;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setImpulseApproxIncoherentCrossSection;
  using ElectronPhotonRelaxationDataContainer::setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setImpulseApproxSubshellIncoherentCrossSection;
  using ElectronPhotonRelaxationDataContainer::setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeCoherentCrossSection;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeCoherentCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setPairProductionCrossSection;
  using ElectronPhotonRelaxationDataContainer::setPairProductionCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setTripletProductionCrossSection;
  using ElectronPhotonRelaxationDataContainer::setTripletProductionCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSection;
  using ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSection;
  using ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeTotalCrossSection;
  using ElectronPhotonRelaxationDataContainer::setImpulseApproxTotalCrossSection;

  // Electron functions
  using ElectronPhotonRelaxationDataContainer::setElasticAngularEnergyGrid;
  using ElectronPhotonRelaxationDataContainer::setCutoffElasticAnglesAtEnergy;
  using ElectronPhotonRelaxationDataContainer::setCutoffElasticPDFAtEnergy;
  using ElectronPhotonRelaxationDataContainer::setCutoffElasticAngles;
  using ElectronPhotonRelaxationDataContainer::setCutoffElasticPDF;
  using ElectronPhotonRelaxationDataContainer::setScreenedRutherfordNormalizationConstant;
  using ElectronPhotonRelaxationDataContainer::setMoliereScreeningConstant;
  using ElectronPhotonRelaxationDataContainer::clearMomentPreservingData;
  using ElectronPhotonRelaxationDataContainer::setMomentPreservingElasticDiscreteAngles;
  using ElectronPhotonRelaxationDataContainer::setMomentPreservingElasticWeights;
  using ElectronPhotonRelaxationDataContainer::setReducedCutoffCrossSectionRatios;
  using ElectronPhotonRelaxationDataContainer::setElectroionizationEnergyGrid;
  using ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy;
  using ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy;
  using ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilEnergy;
  using ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilPDF;
  using ElectronPhotonRelaxationDataContainer::setBremsstrahlungEnergyGrid;
  using ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy;
  using ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy;
  using ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonEnergy;
  using ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonPDF;
  using ElectronPhotonRelaxationDataContainer::setAtomicExcitationEnergyGrid;
  using ElectronPhotonRelaxationDataContainer::setAtomicExcitationEnergyLoss;
  using ElectronPhotonRelaxationDataContainer::setElectronEnergyGrid;
  using ElectronPhotonRelaxationDataContainer::setCutoffElasticCrossSection;
  using ElectronPhotonRelaxationDataContainer::setCutoffElasticCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setScreenedRutherfordElasticCrossSection;
  using ElectronPhotonRelaxationDataContainer::setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setTotalElasticCrossSection;
  using ElectronPhotonRelaxationDataContainer::setTotalElasticCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setMomentPreservingCrossSection;
  using ElectronPhotonRelaxationDataContainer::setMomentPreservingCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setElectroionizationCrossSection;
  using ElectronPhotonRelaxationDataContainer::setElectroionizationCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setBremsstrahlungCrossSection;
  using ElectronPhotonRelaxationDataContainer::setBremsstrahlungCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setAtomicExcitationCrossSection;
  using ElectronPhotonRelaxationDataContainer::setAtomicExcitationCrossSectionThresholdEnergyIndex;

  // Add the export member function to the public interface
  using ElectronPhotonRelaxationDataContainer::exportData;

  // Add the packDataInString member function to the public interface
  using ElectronPhotonRelaxationDataContainer::packDataInString;
};

} // end Data namespace

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

