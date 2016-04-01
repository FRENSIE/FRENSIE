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
/*
//---------------------------------------------------------------------------//
// SET RELAXATION DATA 
//---------------------------------------------------------------------------//
  using EvaluatedElectronDataContainer::setSubshells;
  using EvaluatedElectronDataContainer::setSubshellOccupancy;
  using EvaluatedElectronDataContainer::setSubshellBindingEnergy;
  using EvaluatedElectronDataContainer::setSubshellRelaxationTransitions;
  using EvaluatedElectronDataContainer::setSubshellRelaxationVacancies;
  using EvaluatedElectronDataContainer::setSubshellRelaxationParticleEnergies;
  using EvaluatedElectronDataContainer::setSubshellRelaxationProbabilities;
*/
//---------------------------------------------------------------------------//
// SET ELASTIC DATA 
//---------------------------------------------------------------------------//
  using EvaluatedElectronDataContainer::setElasticEnergyGrid;
  using EvaluatedElectronDataContainer::setElasticTransportCrossSection;
  using EvaluatedElectronDataContainer::setCutoffElasticCrossSection;
  using EvaluatedElectronDataContainer::setCutoffElasticResidualIncomingEnergy;
  using EvaluatedElectronDataContainer::setCutoffElasticResidualEnergy;
  using EvaluatedElectronDataContainer::setCutoffElasticScatteredElectronIncomingEnergy;
  using EvaluatedElectronDataContainer::setCutoffElasticScatteredElectronEnergy;
  using EvaluatedElectronDataContainer::setCutoffElasticAngularEnergyGrid;
  using EvaluatedElectronDataContainer::setCutoffElasticAnglesAtEnergy;
  using EvaluatedElectronDataContainer::setCutoffElasticPDFAtEnergy;
  using EvaluatedElectronDataContainer::setCutoffElasticAngles;
  using EvaluatedElectronDataContainer::setCutoffElasticPDF;
  using EvaluatedElectronDataContainer::setTotalElasticCrossSection;
/*
  using EvaluatedElectronDataContainer::setScreenedRutherfordElasticCrossSection;
  using EvaluatedElectronDataContainer::setScreenedRutherfordNormalizationConstant;
  using EvaluatedElectronDataContainer::setMoliereScreeningConstant;
*/
//---------------------------------------------------------------------------//
// SET ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  using EvaluatedElectronDataContainer::setElectroionizationCrossSectionEnergyGrid;
  using EvaluatedElectronDataContainer::setElectroionizationCrossSection;
  using EvaluatedElectronDataContainer::setElectroionizationAverageScatteredElectronIncomingEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationAverageScatteredElectronEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationAverageRecoilElectronIncomingEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationAverageRecoilElectronEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilEnergyGrid;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilEnergy;
  using EvaluatedElectronDataContainer::setElectroionizationRecoilPDF;
//---------------------------------------------------------------------------//
// SET BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  using EvaluatedElectronDataContainer::setBremsstrahlungCrossSectionEnergyGrid;
  using EvaluatedElectronDataContainer::setBremsstrahlungCrossSection;
  using EvaluatedElectronDataContainer::setBremsstrahlungAveragePhotonIncomingEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungAveragePhotonEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergyGrid;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungPhotonPDF;
  using EvaluatedElectronDataContainer::setBremsstrahlungAverageElectronIncomingEnergy;
  using EvaluatedElectronDataContainer::setBremsstrahlungAverageElectronEnergy;
//---------------------------------------------------------------------------//
// SET ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
  using EvaluatedElectronDataContainer::setAtomicExcitationCrossSectionEnergyGrid;
  using EvaluatedElectronDataContainer::setAtomicExcitationCrossSection;
  using EvaluatedElectronDataContainer::setAtomicExcitationEnergyLossIncomingEnergy;
  using EvaluatedElectronDataContainer::setAtomicExcitationEnergyLoss;

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

