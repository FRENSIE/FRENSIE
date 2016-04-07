//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLVolatileDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native endl volatile data container class
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_VOLATILE_DATA_CONTAINER_HPP
#define DATA_ENDL_VOLATILE_DATA_CONTAINER_HPP

// FRENSIE Includes
#include "Data_ENDLDataContainer.hpp"

namespace Data{

//! The endl volatile data container
class ENDLVolatileDataContainer : public ENDLDataContainer
{

public:

  //! Default constructor
  ENDLVolatileDataContainer();

  //! Constructor (from saved archive)
  ENDLVolatileDataContainer(
		   const std::string& archive_name,
		   const Utility::ArchivableObject::ArchiveType archive_type );

  // Add the setter member functions to the public interface
  using ENDLDataContainer::setAtomicNumber;

//---------------------------------------------------------------------------//
// SET RELAXATION DATA 
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setSubshells;
  using ENDLDataContainer::setSubshellNumberOfElectrons;
  using ENDLDataContainer::setSubshellBindingEnergy;
  using ENDLDataContainer::setSubshellKineticEnergy;
  using ENDLDataContainer::setSubshellAverageRadius;
  using ENDLDataContainer::setSubshellRadiativeLevel;
  using ENDLDataContainer::setSubshellNonRadiativeLevel;
  using ENDLDataContainer::setLocalDepositionPerInitialVacancy;
  using ENDLDataContainer::setAverageParticlesPerInitialVacancy;
  using ENDLDataContainer::setAverageParitcleEnergyPerInitialVacancy;
  using ENDLDataContainer::setRadiativeTransitionProbability;
  using ENDLDataContainer::setRadiativeTransitionEnergy;
  using ENDLDataContainer::setNonRadiativeTransitionProbability;
  using ENDLDataContainer::setNonRadiativeTransitionEnergy;

//---------------------------------------------------------------------------//
// SET ELASTIC DATA 
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setElasticEnergyGrid;
  using ENDLDataContainer::setElasticTransportCrossSection;
  using ENDLDataContainer::setCutoffElasticCrossSection;
  using ENDLDataContainer::setCutoffElasticResidualIncomingEnergy;
  using ENDLDataContainer::setCutoffElasticResidualEnergy;
  using ENDLDataContainer::setCutoffElasticScatteredElectronIncomingEnergy;
  using ENDLDataContainer::setCutoffElasticScatteredElectronEnergy;
  using ENDLDataContainer::setCutoffElasticAngularEnergyGrid;
  using ENDLDataContainer::setCutoffElasticAnglesAtEnergy;
  using ENDLDataContainer::setCutoffElasticPDFAtEnergy;
  using ENDLDataContainer::setCutoffElasticAngles;
  using ENDLDataContainer::setCutoffElasticPDF;
  using ENDLDataContainer::setTotalElasticCrossSection;
/*
  using ENDLDataContainer::setScreenedRutherfordElasticCrossSection;
  using ENDLDataContainer::setScreenedRutherfordNormalizationConstant;
  using ENDLDataContainer::setMoliereScreeningConstant;
*/
//---------------------------------------------------------------------------//
// SET ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setElectroionizationCrossSectionEnergyGrid;
  using ENDLDataContainer::setElectroionizationCrossSection;
  using ENDLDataContainer::setElectroionizationAverageScatteredElectronIncomingEnergy;
  using ENDLDataContainer::setElectroionizationAverageScatteredElectronEnergy;
  using ENDLDataContainer::setElectroionizationAverageRecoilElectronIncomingEnergy;
  using ENDLDataContainer::setElectroionizationAverageRecoilElectronEnergy;
  using ENDLDataContainer::setElectroionizationRecoilEnergyGrid;
  using ENDLDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy;
  using ENDLDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy;
  using ENDLDataContainer::setElectroionizationRecoilEnergy;
  using ENDLDataContainer::setElectroionizationRecoilPDF;
//---------------------------------------------------------------------------//
// SET BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setBremsstrahlungCrossSectionEnergyGrid;
  using ENDLDataContainer::setBremsstrahlungCrossSection;
  using ENDLDataContainer::setBremsstrahlungAveragePhotonIncomingEnergy;
  using ENDLDataContainer::setBremsstrahlungAveragePhotonEnergy;
  using ENDLDataContainer::setBremsstrahlungPhotonEnergyGrid;
  using ENDLDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy;
  using ENDLDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy;
  using ENDLDataContainer::setBremsstrahlungPhotonEnergy;
  using ENDLDataContainer::setBremsstrahlungPhotonPDF;
  using ENDLDataContainer::setBremsstrahlungAverageElectronIncomingEnergy;
  using ENDLDataContainer::setBremsstrahlungAverageElectronEnergy;
//---------------------------------------------------------------------------//
// SET ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setAtomicExcitationEnergyGrid;
  using ENDLDataContainer::setAtomicExcitationCrossSection;
  using ENDLDataContainer::setAtomicExcitationEnergyLoss;

  // Add the export member function to the public interface
  using ENDLDataContainer::exportData;

  // Add the packDataInString member function to the public interface
  using ENDLDataContainer::packDataInString;
};

} // end Data namespace

#endif // end DATA_ENDL_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

