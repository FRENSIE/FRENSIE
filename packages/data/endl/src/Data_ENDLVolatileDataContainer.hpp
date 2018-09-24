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
  ENDLVolatileDataContainer( const boost::filesystem::path& file_name_with_path );

  // Add the setter member functions to the public interface
  using ENDLDataContainer::setAtomicNumber;
  using ENDLDataContainer::setAtomicWeight;

//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setSubshells;
  using ENDLDataContainer::setSubshellOccupancy;
  using ENDLDataContainer::setSubshellBindingEnergy;
  using ENDLDataContainer::setSubshellKineticEnergy;
  using ENDLDataContainer::setSubshellAverageRadius;
  using ENDLDataContainer::setSubshellRadiativeLevel;
  using ENDLDataContainer::setSubshellNonRadiativeLevel;
  using ENDLDataContainer::setLocalDepositionPerInitialVacancy;
  using ENDLDataContainer::setAveragePhotonsPerInitialVacancy;
  using ENDLDataContainer::setAveragePhotonEnergyPerInitialVacancy;
  using ENDLDataContainer::setAverageElectronsPerInitialVacancy;
  using ENDLDataContainer::setAverageElectronEnergyPerInitialVacancy;
  using ENDLDataContainer::setRadiativeTransitionProbability;
  using ENDLDataContainer::setRadiativeTransitionEnergy;
  using ENDLDataContainer::setNonRadiativeTransitionProbability;
  using ENDLDataContainer::setNonRadiativeTransitionEnergy;

//---------------------------------------------------------------------------//
// SET COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  using ENDLDataContainer::setCoherentCrossSectionEnergyGrid;
  using ENDLDataContainer::setCoherentCrossSection;
  using ENDLDataContainer::setCoherentCrossSectionInterpType;
  using ENDLDataContainer::setCoherentFormFactorArgument;
  using ENDLDataContainer::setCoherentFormFactor;
  using ENDLDataContainer::setCoherentFormFactorInterpType;
  using ENDLDataContainer::setCoherentImaginaryAnomalousFactorIncidentEnergy;
  using ENDLDataContainer::setCoherentImaginaryAnomalousFactor;
  using ENDLDataContainer::setCoherentImaginaryAnomalousFactorInterpType;
  using ENDLDataContainer::setCoherentRealAnomalousFactorIncidentEnergy;
  using ENDLDataContainer::setCoherentRealAnomalousFactor;
  using ENDLDataContainer::setCoherentRealAnomalousFactorInterpType;
  using ENDLDataContainer::setCoherentAveragePhotonIncidentEnergy;
  using ENDLDataContainer::setCoherentAveragePhotonEnergy;
  using ENDLDataContainer::setCoherentAveragePhotonEnergyInterpType;

//---------------------------------------------------------------------------//
// SET INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  using ENDLDataContainer::setIncoherentCrossSectionEnergyGrid;
  using ENDLDataContainer::setIncoherentCrossSection;
  using ENDLDataContainer::setIncoherentCrossSectionInterpType;
  using ENDLDataContainer::setIncoherentScatteringFunctionArgument;
  using ENDLDataContainer::setIncoherentScatteringFunction;
  using ENDLDataContainer::setIncoherentScatteringFunctionInterpType;
  using ENDLDataContainer::setIncoherentAveragePhotonIncidentEnergy;
  using ENDLDataContainer::setIncoherentAveragePhotonEnergy;
  using ENDLDataContainer::setIncoherentAveragePhotonEnergyInterpType;
  using ENDLDataContainer::setIncoherentAverageElectronIncidentEnergy;
  using ENDLDataContainer::setIncoherentAverageElectronEnergy;
  using ENDLDataContainer::setIncoherentAverageElectronEnergyInterpType;

//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  using ENDLDataContainer::setPhotoelectricCrossSectionEnergyGrid;
  using ENDLDataContainer::setPhotoelectricCrossSection;
  using ENDLDataContainer::setPhotoelectricCrossSectionInterpType;
  using ENDLDataContainer::setPhotoelectricAverageResidualIncidentEnergy;
  using ENDLDataContainer::setPhotoelectricAverageResidualEnergy;
  using ENDLDataContainer::setPhotoelectricAverageResidualEnergyInterpType;
  using ENDLDataContainer::setPhotoelectricAveragePhotonsIncidentEnergy;
  using ENDLDataContainer::setPhotoelectricAveragePhotonsEnergy;
  using ENDLDataContainer::setPhotoelectricAveragePhotonsEnergyInterpType;
  using ENDLDataContainer::setPhotoelectricAverageElectronsIncidentEnergy;
  using ENDLDataContainer::setPhotoelectricAverageElectronsEnergy;
  using ENDLDataContainer::setPhotoelectricAverageElectronsEnergyInterpType;

//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  using ENDLDataContainer::setPhotoelectricCrossSectionEnergyGrid;
  using ENDLDataContainer::setPhotoelectricCrossSection;
  using ENDLDataContainer::setPhotoelectricCrossSectionInterpType;
  using ENDLDataContainer::setPhotoelectricAverageResidualIncidentEnergy;
  using ENDLDataContainer::setPhotoelectricAverageResidualEnergy;
  using ENDLDataContainer::setPhotoelectricAverageResidualEnergyInterpType;
  using ENDLDataContainer::setPhotoelectricAveragePhotonsIncidentEnergy;
  using ENDLDataContainer::setPhotoelectricAveragePhotonsEnergy;
  using ENDLDataContainer::setPhotoelectricAveragePhotonsEnergyInterpType;
  using ENDLDataContainer::setPhotoelectricAverageElectronsIncidentEnergy;
  using ENDLDataContainer::setPhotoelectricAverageElectronsEnergy;
  using ENDLDataContainer::setPhotoelectricAverageElectronsEnergyInterpType;

//---------------------------------------------------------------------------//
// SET PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  using ENDLDataContainer::setPairProductionCrossSectionEnergyGrid;
  using ENDLDataContainer::setPairProductionCrossSection;
  using ENDLDataContainer::setPairProductionCrossSectionInterpType;
  using ENDLDataContainer::setPairProductionAveragePositronIncidentEnergy;
  using ENDLDataContainer::setPairProductionAveragePositronEnergy;
  using ENDLDataContainer::setPairProductionAveragePositronEnergyInterpType;
  using ENDLDataContainer::setPairProductionAverageElectronIncidentEnergy;
  using ENDLDataContainer::setPairProductionAverageElectronEnergy;
  using ENDLDataContainer::setPairProductionAverageElectronEnergyInterpType;

//---------------------------------------------------------------------------//
// SET TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  using ENDLDataContainer::setTripletProductionCrossSectionEnergyGrid;
  using ENDLDataContainer::setTripletProductionCrossSection;
  using ENDLDataContainer::setTripletProductionCrossSectionInterpType;
  using ENDLDataContainer::setTripletProductionAveragePositronIncidentEnergy;
  using ENDLDataContainer::setTripletProductionAveragePositronEnergy;
  using ENDLDataContainer::setTripletProductionAveragePositronEnergyInterpType;
  using ENDLDataContainer::setTripletProductionAverageElectronIncidentEnergy;
  using ENDLDataContainer::setTripletProductionAverageElectronEnergy;
  using ENDLDataContainer::setTripletProductionAverageElectronEnergyInterpType;

//---------------------------------------------------------------------------//
// SET ELASTIC DATA
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setElasticEnergyGrid;
  using ENDLDataContainer::setElasticTransportCrossSection;
  using ENDLDataContainer::setElasticTransportCrossSectionInterpType;
  using ENDLDataContainer::setCutoffElasticCrossSection;
  using ENDLDataContainer::setCutoffElasticCrossSectionInterpType;
  using ENDLDataContainer::setCutoffElasticResidualIncidentEnergy;
  using ENDLDataContainer::setCutoffElasticResidualEnergy;
  using ENDLDataContainer::setCutoffElasticResidualEnergyInterpType;
  using ENDLDataContainer::setCutoffElasticScatteredElectronIncidentEnergy;
  using ENDLDataContainer::setCutoffElasticScatteredElectronEnergy;
  using ENDLDataContainer::setCutoffElasticScatteredElectronEnergyInterpType;
  using ENDLDataContainer::setCutoffElasticAngularEnergyGrid;
  using ENDLDataContainer::setCutoffElasticAnglesAtEnergy;
  using ENDLDataContainer::setCutoffElasticPDFAtEnergy;
  using ENDLDataContainer::setCutoffElasticAngles;
  using ENDLDataContainer::setCutoffElasticPDF;
  using ENDLDataContainer::setCutoffElasticPDFInterpType;
  using ENDLDataContainer::setTotalElasticCrossSection;
  using ENDLDataContainer::setTotalElasticCrossSectionInterpType;
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
  using ENDLDataContainer::setElectroionizationCrossSectionInterpType;
  using ENDLDataContainer::setElectroionizationAverageScatteredElectronIncidentEnergy;
  using ENDLDataContainer::setElectroionizationAverageScatteredElectronEnergy;
  using ENDLDataContainer::setElectroionizationAverageScatteredElectronEnergyInterpType;
  using ENDLDataContainer::setElectroionizationAverageRecoilElectronIncidentEnergy;
  using ENDLDataContainer::setElectroionizationAverageRecoilElectronEnergy;
  using ENDLDataContainer::setElectroionizationAverageRecoilElectronEnergyInterpType;
  using ENDLDataContainer::setElectroionizationRecoilEnergyGrid;
  using ENDLDataContainer::setElectroionizationRecoilEnergyAtIncidentEnergy;
  using ENDLDataContainer::setElectroionizationRecoilPDFAtIncidentEnergy;
  using ENDLDataContainer::setElectroionizationRecoilEnergy;
  using ENDLDataContainer::setElectroionizationRecoilPDF;
  using ENDLDataContainer::setElectroionizationRecoilPDFInterpType;
  
//---------------------------------------------------------------------------//
// SET BREMSSTRAHLUNG DATA
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setBremsstrahlungCrossSectionEnergyGrid;
  using ENDLDataContainer::setBremsstrahlungCrossSection;
  using ENDLDataContainer::setBremsstrahlungCrossSectionInterpType;
  using ENDLDataContainer::setBremsstrahlungAveragePhotonIncidentEnergy;
  using ENDLDataContainer::setBremsstrahlungAveragePhotonEnergy;
  using ENDLDataContainer::setBremsstrahlungAveragePhotonEnergyInterpType;
  using ENDLDataContainer::setBremsstrahlungPhotonEnergyGrid;
  using ENDLDataContainer::setBremsstrahlungPhotonEnergyAtIncidentEnergy;
  using ENDLDataContainer::setBremsstrahlungPhotonPDFAtIncidentEnergy;
  using ENDLDataContainer::setBremsstrahlungPhotonEnergy;
  using ENDLDataContainer::setBremsstrahlungPhotonPDF;
  using ENDLDataContainer::setBremsstrahlungPhotonPDFInterpType;
  using ENDLDataContainer::setBremsstrahlungAverageElectronIncidentEnergy;
  using ENDLDataContainer::setBremsstrahlungAverageElectronEnergy;
  using ENDLDataContainer::setBremsstrahlungAverageElectronEnergyInterpType;
  
//---------------------------------------------------------------------------//
// SET ATOMIC EXCITATION DATA
//---------------------------------------------------------------------------//
  using ENDLDataContainer::setAtomicExcitationEnergyGrid;
  using ENDLDataContainer::setAtomicExcitationCrossSection;
  using ENDLDataContainer::setAtomicExcitationCrossSectionInterpType;
  using ENDLDataContainer::setAtomicExcitationEnergyLoss;
  using ENDLDataContainer::setAtomicExcitationEnergyLossInterpType;
};

} // end Data namespace

#endif // end DATA_ENDL_VOLATILE_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

