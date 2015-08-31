//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedElectronVolatileDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native eedl volatile data container class
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EVALUATED_ELECTRON_VOLATILE_DATA_CONTAINER_HPP
#define DATA_EVALUATED_ELECTRON_VOLATILE_DATA_CONTAINER_HPP

// FRENSIE Includes
#include "Data_EvaluatedElectronDataContainer.hpp"

namespace Data{

//! The eedl volatile data container
class EvaluatedElectronVolatileDataContainer : public EvaluatedElectronDataContainer
{

public:

  //! Default constructor
  EvaluatedElectronVolatileDataContainer();

  //! Constructor (from saved archive)
  EvaluatedElectronVolatileDataContainer(
		   const std::string& archive_name,
		   const Utility::ArchivableObject::ArchiveType archive_type );

  // Add the setter member functions to the public interface
  using EvaluatedElectronDataContainer::setAtomicNumber;
  using EvaluatedElectronDataContainer::setSubshells;
  using EvaluatedElectronDataContainer::setCutoffAngle;
  using EvaluatedElectronDataContainer::setElasticAngularEnergyGrid;
//  using EvaluatedElectronDataContainer::setNumberOfDiscreteAngles;
  using EvaluatedElectronDataContainer::setAnalogElasticAnglesAtEnergy;
  using EvaluatedElectronDataContainer::setAnalogElasticPDFAtEnergy;
  using EvaluatedElectronDataContainer::setAnalogElasticAngles;
  using EvaluatedElectronDataContainer::setAnalogElasticPDF;
  using EvaluatedElectronDataContainer::setScreenedRutherfordNormalizationConstant;
  using EvaluatedElectronDataContainer::setMoliereScreeningConstant;
  using EvaluatedElectronDataContainer::setMomentPreservingElasticDiscreteAngles;
  using EvaluatedElectronDataContainer::setMomentPreservingElasticWeights;
  using EvaluatedElectronDataContainer::setElectroionizationEnergyGrid;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilPDF;
  using EvaluatedElectronDataContainer::setBremsstrahlungEnergyGrid;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonPDF;
  using EvaluatedElectronDataContainer::setAtomicExcitationEnergyGrid;
  using EvaluatedElectronDataContainer::setAtomicExcitationEnergyLoss;
  using EvaluatedElectronDataContainer::setElectronEnergyGrid;
  using EvaluatedElectronDataContainer::setCutoffElasticCrossSection;
  using EvaluatedElectronDataContainer::setCutoffElasticCrossSectionThresholdEnergyIndex;
  using EvaluatedElectronDataContainer::setScreenedRutherfordElasticCrossSection;
  using EvaluatedElectronDataContainer::setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex;
  using EvaluatedElectronDataContainer::setTotalElasticCrossSection;
  using EvaluatedElectronDataContainer::setTotalElasticCrossSectionThresholdEnergyIndex;
/*
  using EvaluatedElectronDataContainer::setHardElasticCrossSection;
  using EvaluatedElectronDataContainer::setHardElasticCrossSectionThresholdEnergyIndex;
*/
  using EvaluatedElectronDataContainer::setMomentPreservingCrossSection;
  using EvaluatedElectronDataContainer::setMomentPreservingCrossSectionThresholdEnergyIndex;
  using EvaluatedElectronDataContainer::setElectroionizationCrossSection;
  using EvaluatedElectronDataContainer::setElectroionizationCrossSectionThresholdEnergyIndex;
  using EvaluatedElectronDataContainer::setBremsstrahlungCrossSection;
  using EvaluatedElectronDataContainer::setBremsstrahlungCrossSectionThresholdEnergyIndex;
  using EvaluatedElectronDataContainer::setAtomicExcitationCrossSection;
  using EvaluatedElectronDataContainer::setAtomicExcitationCrossSectionThresholdEnergyIndex;

  // Add the export member function to the public interface
  using EvaluatedElectronDataContainer::exportData;

  // Add the packDataInString member function to the public interface
  using EvaluatedElectronDataContainer::packDataInString;
};

} // end Data namespace

#endif // end DATA_EVALUATED_ELECTRON_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_EvaluatedElectronVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

