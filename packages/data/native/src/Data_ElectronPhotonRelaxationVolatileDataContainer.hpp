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
  using ElectronPhotonRelaxationDataContainer::setAtomicNumber;
  using ElectronPhotonRelaxationDataContainer::setSubshells;
  using ElectronPhotonRelaxationDataContainer::setSubshellOccupancy;
  using ElectronPhotonRelaxationDataContainer::setSubshellBindingEnergy;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationTransitions;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationVacancies;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationParticleEnergies;
  using ElectronPhotonRelaxationDataContainer::setSubshellRelaxationProbabilities;
  using ElectronPhotonRelaxationDataContainer::setComptonProfileMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setComptonProfile;
  using ElectronPhotonRelaxationDataContainer::setOccupancyNumberMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setOccupancyNumber;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunctionMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunction;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactorMomentumGrid;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactor;
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
  using ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSection;
  using ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSection;
  using ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSectionThresholdEnergyIndex;
  using ElectronPhotonRelaxationDataContainer::setWallerHartreeTotalCrossSection;
  using ElectronPhotonRelaxationDataContainer::setImpulseApproxTotalCrossSection;

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

