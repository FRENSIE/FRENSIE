//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native endl container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_DATA_CONTAINER_HPP
#define DATA_ENDL_DATA_CONTAINER_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ArchivableObject.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The eadl container
class ENDLDataContainer : public Utility::ArchivableObject<ENDLDataContainer>
{
  // The base type
  typedef Utility::ArchivableObject<ENDLDataContainer> BaseType;

public:

  //! Constructor (from saved archive)
  ENDLDataContainer( const boost::filesystem::path& file_name_with_path );

  //! Destructor
  virtual ~ENDLDataContainer()
  { /* ... */ }

  //! The database name used in an archive
  const char* getArchiveName() const override;

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the atomic weight
  double getAtomicWeight() const;

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

  //! Return the atomic subshells
  const std::set<unsigned>& getSubshells() const;

  //! Return the number of electrons for a subshell
  const double getSubshellOccupancy( const unsigned subshell ) const;

  //! Return the binding energy for a subshell
  const double getSubshellBindingEnergy( const unsigned subshell ) const;

  //! Return the kinetic energy for a subshell
  const double getSubshellKineticEnergy( const unsigned subshell ) const;

  //! Return the average radius for a subshell
  const double getSubshellAverageRadius( const unsigned subshell ) const;

  //! Return the radiative level width for a subshell
  const double getSubshellRadiativeLevel( const unsigned subshell ) const;

  //! Return the non radiative level for a subshell
  const double getSubshellNonRadiativeLevel( const unsigned subshell ) const;

  //! Return the average energy to the residual atom per initial vacancy
  const double getLocalDepositionPerInitialVacancy(
    const unsigned subshell ) const;

  //! Return the average number of photons per initial vacancy
  const double getAveragePhotonsPerInitialVacancy(
    const unsigned subshell ) const;

  //! Return the average energy of photons per initial vacancy
  const double getAveragePhotonEnergyPerInitialVacancy(
    const unsigned subshell ) const;

  //! Return the average number of electrons per initial vacancy
  const double getAverageElectronsPerInitialVacancy(
    const unsigned subshell ) const;

  //! Return the average energy of electrons per initial vacancy
  const double getAverageElectronEnergyPerInitialVacancy(
    const unsigned subshell ) const;

  //! Check if a subshell has radiative transitions
  bool hasRadiativeTransitions( const unsigned subshell ) const;

  //! Return the radiative transition probability
  const std::map<unsigned,double>& getRadiativeTransitionProbability(
    const unsigned subshell ) const;

  //! Return the radiative transition energy
  const std::map<unsigned,double>& getRadiativeTransitionEnergy(
    const unsigned subshell ) const;

  //! Check if a subshell has non radiative transitions
  bool hasNonRadiativeTransitions( const unsigned subshell ) const;

  //! Return the non radiative transition probability
  const std::map<unsigned,std::map<unsigned,double> >&
  getNonRadiativeTransitionProbability( const unsigned subshell ) const;

  //! Return the non radiative transition energy
  const std::map<unsigned,std::map<unsigned,double> >&
  getNonRadiativeTransitionEnergy( const unsigned subshell ) const;

//---------------------------------------------------------------------------//
// GET COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  //! Return the coherent cross section energy grid
  const std::vector<double>& getCoherentCrossSectionEnergyGrid() const;

  //! Return the coherent photon cross section
  const std::vector<double>& getCoherentCrossSection() const;

  //! Return the coherent cross section interpolation type
  const std::string& getCoherentCrossSectionInterpType() const;

  //! Return the argument for the coherent form factor (1/cm)
  const std::vector<double>& getCoherentFormFactorArgument() const;

  //! Return the coherent form factor
  const std::vector<double>& getCoherentFormFactor() const;

  //! Return the coherent form factor interpolation type
  const std::string& getCoherentFormFactorInterpType() const;

  //! Return the incident energy grid for the coherent imaginary anomalous scattering factor
  const std::vector<double>&
  getCoherentImaginaryAnomalousFactorIncidentEnergy() const;

  //! Return the coherent imaginary anomalous scattering factor
  const std::vector<double>& getCoherentImaginaryAnomalousFactor() const;

  //! Return the coherent imaginary anomalous scattering factor interpolation type
  const std::string& getCoherentImaginaryAnomalousFactorInterpType() const;

  //! Return the incident energy grid for the coherent real anomalous scattering factor
  const std::vector<double>&
  getCoherentRealAnomalousFactorIncidentEnergy() const;

  //! Return the coherent real anomalous scattering factor
  const std::vector<double>& getCoherentRealAnomalousFactor() const;

  //! Return the coherent real anomalous scattering factor interpolation type
  const std::string& getCoherentRealAnomalousFactorInterpType() const;

  //! Return the incident energy grid for the coherent average energy of the scattered photon
  const std::vector<double>& getCoherentAveragePhotonIncidentEnergy() const;

  //! Return the coherent average energy of the scattered photon
  const std::vector<double>& getCoherentAveragePhotonEnergy() const;

  //! Return the coherent average energy of the scattered photon interpolation type
  const std::string& getCoherentAveragePhotonEnergyInterpType() const;

//---------------------------------------------------------------------------//
// GET INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  //! Return the incoherent cross section energy grid
  const std::vector<double>& getIncoherentCrossSectionEnergyGrid() const;

  //! Return the incoherent photon cross section
  const std::vector<double>& getIncoherentCrossSection() const;

  //! Return the incoherent photon cross section interpolation type
  const std::string& getIncoherentCrossSectionInterpType() const;

  //! Return the argument for the incoherent scattering function (1/cm)
  const std::vector<double>& getIncoherentScatteringFunctionArgument() const;

  //! Return the incoherent scattering function
  const std::vector<double>& getIncoherentScatteringFunction() const;

  //! Return the incoherent scattering function interpolation type
  const std::string& getIncoherentScatteringFunctionInterpType() const;

  //! Return the incident energy grid for the incoherent average energy of the scattered photon
  const std::vector<double>& getIncoherentAveragePhotonIncidentEnergy() const;

  //! Return the incoherent average energy of the scattered photon
  const std::vector<double>& getIncoherentAveragePhotonEnergy() const;

  //! Return the incoherent average energy of the scattered photon interpolation type
  const std::string& getIncoherentAveragePhotonEnergyInterpType() const;

  //! Return the incident energy grid for the incoherent average energy of the recoil electron
  const std::vector<double>& getIncoherentAverageElectronIncidentEnergy() const;

  //! Return the incoherent average energy of the recoil electron
  const std::vector<double>& getIncoherentAverageElectronEnergy() const;

  //! Return the incoherent average energy of the recoil electron interpolation type
  const std::string& getIncoherentAverageElectronEnergyInterpType() const;

//---------------------------------------------------------------------------//
// GET PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  //! Return the photoelectric cross section energy grid
  const std::vector<double>& getPhotoelectricCrossSectionEnergyGrid() const;

  //! Return the photoelectric photon cross section
  const std::vector<double>& getPhotoelectricCrossSection() const;

  //! Return the photoelectric photon cross section interpolation type
  const std::string& getPhotoelectricCrossSectionInterpType() const;

  //! Return the incident energy grid for the photoelectric average energy of the residual atom
  const std::vector<double>& getPhotoelectricAverageResidualIncidentEnergy() const;

  //! Return the photoelectric average energy of the residual atom
  const std::vector<double>& getPhotoelectricAverageResidualEnergy() const;

  //! Return the photoelectric average energy of the residual atom interpolation type
  const std::string& getPhotoelectricAverageResidualEnergyInterpType() const;

  //! Return the incident energy grid for the photoelectric average energy of the secondary photons
  const std::vector<double>& getPhotoelectricAveragePhotonsIncidentEnergy() const;

  //! Return the photoelectric average energy of the secondary photons
  const std::vector<double>& getPhotoelectricAveragePhotonsEnergy() const;

  //! Return the photoelectric average energy of the secondary photons interpolation type
  const std::string& getPhotoelectricAveragePhotonsEnergyInterpType() const;

  //! Return the incident energy grid for the photoelectric average energy of the secondary electrons
  const std::vector<double>& getPhotoelectricAverageElectronsIncidentEnergy() const;

  //! Return the photoelectric average energy of the secondary electrons
  const std::vector<double>& getPhotoelectricAverageElectronsEnergy() const;

  //! Return the photoelectric average energy of the secondary electrons interpolation type
  const std::string& getPhotoelectricAverageElectronsEnergyInterpType() const;

//---------------------------------------------------------------------------//
// GET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  //! Return the photoelectric cross section energy grid for a subshell
  const std::vector<double>&
  getPhotoelectricCrossSectionEnergyGrid( const unsigned subshell ) const;

  //! Return the photoelectric photon cross section for a subshell
  const std::vector<double>&
  getPhotoelectricCrossSection( const unsigned subshell ) const;

  //! Return the photoelectric photon cross section interpolation type for a subshell
  const std::string& getPhotoelectricCrossSectionInterpType( const unsigned subshell ) const;

  //! Return the incident energy grid for the photoelectric average energy of the residual atom for a subshell
  const std::vector<double>&
  getPhotoelectricAverageResidualIncidentEnergy( const unsigned subshell ) const;

  //! Return the photoelectric average energy of the residual atom for a subshell
  const std::vector<double>&
  getPhotoelectricAverageResidualEnergy( const unsigned subshell ) const;

  //! Return the photoelectric average energy of the residual atom interpolation type for a subshell
  const std::string& getPhotoelectricAverageResidualEnergyInterpType( const unsigned subshell ) const;

  //! Return the incident energy grid for the photoelectric average energy of the secondary photons for a subshell
  const std::vector<double>&
  getPhotoelectricAveragePhotonsIncidentEnergy( const unsigned subshell ) const;

  //! Return the photoelectric average energy of the secondary photons for a subshell
  const std::vector<double>&
  getPhotoelectricAveragePhotonsEnergy( const unsigned subshell ) const;

  //! Return the photoelectric average energy of the secondary photons interpolation type for a subshell
  const std::string& getPhotoelectricAveragePhotonsEnergyInterpType( const unsigned subshell ) const;

  //! Return the incident energy grid for the photoelectric average energy of the secondary electrons for a subshell
  const std::vector<double>&
  getPhotoelectricAverageElectronsIncidentEnergy( const unsigned subshell ) const;

  //! Return the photoelectric average energy of the secondary electrons for a subshell
  const std::vector<double>&
  getPhotoelectricAverageElectronsEnergy( const unsigned subshell ) const;

  //! Return the photoelectric average energy of the secondary electrons interpolation type for a subshell
  const std::string& getPhotoelectricAverageElectronsEnergyInterpType( const unsigned subshell ) const;

//---------------------------------------------------------------------------//
// GET PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  //! Return the pair production cross section energy grid
  const std::vector<double>& getPairProductionCrossSectionEnergyGrid() const;

  //! Return the pair production photon cross section
  const std::vector<double>& getPairProductionCrossSection() const;

  //! Return the pair production photon cross section interpolation type
  const std::string& getPairProductionCrossSectionInterpType() const;

  //! Return the incident energy grid for the pair production average energy of the secondary positron
  const std::vector<double>& getPairProductionAveragePositronIncidentEnergy() const;

  //! Return the pair production average energy of the secondary positron
  const std::vector<double>& getPairProductionAveragePositronEnergy() const;

  //! Return the pair production average energy of the secondary positron interpolation type
  const std::string& getPairProductionAveragePositronEnergyInterpType() const;

  //! Return the incident energy grid for the pair production average energy of the secondary electron
  const std::vector<double>& getPairProductionAverageElectronIncidentEnergy() const;

  //! Return the pair production average energy of the secondary electron
  const std::vector<double>& getPairProductionAverageElectronEnergy() const;

  //! Return the pair production average energy of the secondary electron interpolation type
  const std::string& getPairProductionAverageElectronEnergyInterpType() const;

//---------------------------------------------------------------------------//
// GET TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  //! Return the triplet production cross section energy grid
  const std::vector<double>& getTripletProductionCrossSectionEnergyGrid() const;

  //! Return the triplet production photon cross section
  const std::vector<double>& getTripletProductionCrossSection() const;

  //! Return the triplet production photon cross section interpolation type
  const std::string& getTripletProductionCrossSectionInterpType() const;

  //! Return the incident energy grid for the triplet production average energy of the secondary positron
  const std::vector<double>& getTripletProductionAveragePositronIncidentEnergy() const;

  //! Return the triplet production average energy of the secondary positron
  const std::vector<double>& getTripletProductionAveragePositronEnergy() const;

  //! Return the triplet production average energy of the secondary positron interpolation type
  const std::string& getTripletProductionAveragePositronEnergyInterpType() const;

  //! Return the incident energy grid for the triplet production average energy of the secondary electron
  const std::vector<double>& getTripletProductionAverageElectronIncidentEnergy() const;

  //! Return the triplet production average energy of the secondary electron
  const std::vector<double>& getTripletProductionAverageElectronEnergy() const;

  //! Return the triplet production average energy of the secondary electron interpolation type
  const std::string& getTripletProductionAverageElectronEnergyInterpType() const;

//---------------------------------------------------------------------------//
// GET ELASTIC ELECTRON DATA
//---------------------------------------------------------------------------//

  //! Return the elastic energy grid
  const std::vector<double>& getElasticEnergyGrid() const;

  //! Return the elastic transport cross section
  const std::vector<double>& getElasticTransportCrossSection() const;

  //! Return the elastic transport cross section interpolation type
  const std::string& getElasticTransportCrossSectionInterpType() const;

  //! Return the elastic transport cross section
  const std::vector<double>& getCutoffElasticCrossSection() const;

  //! Return the elastic transport cross section interpolation type
  const std::string& getCutoffElasticCrossSectionInterpType() const;

  //! Return the incident energy grid for the cutoff elastic average energy to the residual atom
  const std::vector<double>& getCutoffElasticResidualIncidentEnergy() const;

  //! Return the cutoff elastic average energy to the residual atom
  const std::vector<double>& getCutoffElasticResidualEnergy() const;

  //! Return the cutoff elastic average energy to the residual atom interpolation type
  const std::string& getCutoffElasticResidualEnergyInterpType() const;

  //! Return the incident energy grid for the cutoff elastic average energy to the scattered electron
  const std::vector<double>& getCutoffElasticScatteredElectronIncidentEnergy() const;

  //! Return the cutoff elastic average energy to the scattered electron
  const std::vector<double>& getCutoffElasticScatteredElectronEnergy() const;

  //! Return the cutoff elastic average energy to the scattered electron interpolation type
  const std::string& getCutoffElasticScatteredElectronEnergyInterpType() const;

  //! Return the cutoff elastic angular energy grid
  const std::vector<double>& getCutoffElasticAngularEnergyGrid() const;

  //! Return the cutoff elastic scattering angles for an incident energy
  const std::vector<double>& getCutoffElasticAnglesAtEnergy(
                                        const double incident_energy ) const;

  //! Return the cutoff elastic scattering pdf for an incident energy
  const std::vector<double>& getCutoffElasticPDFAtEnergy(
                                        const double incident_energy ) const;

  //! Return the cutoff elastic scattering angles for all incident energy
  const std::map<double,std::vector<double> >& getCutoffElasticAngles() const;

  //! Return the cutoff elastic scattering pdf for all incident energy
  const std::map<double,std::vector<double> >& getCutoffElasticPDF() const;

  //! Return the cutoff elastic scattering pdf interpolation type
  const std::string& getCutoffElasticPDFInterpType() const;

  //! Return the total elastic electron cross section
  const std::vector<double>& getTotalElasticCrossSection() const;

  //! Return the total elastic electron cross section interpolation type
  const std::string& getTotalElasticCrossSectionInterpType() const;

/*
  //! Return the screened Rutherford elastic electron cross section
  const std::vector<double>& getScreenedRutherfordElasticCrossSection() const;

  //! Return the screened Rutherford elastic normalization constants
  const std::vector<double>& getScreenedRutherfordNormalizationConstant() const;

  //! Return Moliere's screening constant
  const std::vector<double>& getMoliereScreeningConstant() const;
*/

//---------------------------------------------------------------------------//
// GET ELECTROIONIZATION DATA
//---------------------------------------------------------------------------//

  //! Return the electroionization energy grid for the cross section for a subshell
  const std::vector<double>&
    getElectroionizationCrossSectionEnergyGrid( const unsigned subshell ) const;

  //! Return the electroionization cross section for a subshell
  const std::vector<double>&
    getElectroionizationCrossSection( const unsigned subshell ) const;

  //! Return the electroionization cross section interpolation type for a subshell
  const std::string& getElectroionizationCrossSectionInterpType( const unsigned subshell ) const;

  //! Return the electroionization incident energy grid for the average scattered electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageScatteredElectronIncidentEnergy(
                           const unsigned subshell ) const;

  //! Return the electroionization average scattered electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageScatteredElectronEnergy(
                           const unsigned subshell ) const;

  //! Return the electroionization average scattered electron energy interpolation type for a subshell
  const std::string& getElectroionizationAverageScatteredElectronEnergyInterpType(
                           const unsigned subshell ) const;

  //! Return the electroionization incident energy grid for the average recoil electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageRecoilElectronIncidentEnergy(
                           const unsigned subshell ) const;

  //! Return the electroionization average recoil electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageRecoilElectronEnergy(
                           const unsigned subshell ) const;

  //! Return the electroionization average recoil electron energy interpolation type for a subshell
  const std::string& getElectroionizationAverageRecoilElectronEnergyInterpType(
                           const unsigned subshell ) const;

  //! Return the electroionization incident energy grid for the recoil electron spectrum for all subshells
  const std::map<unsigned,std::vector<double> >& getElectroionizationRecoilEnergyGrid() const;

  //! Return the electroionization incident energy grid for the recoil electron spectrum for a subshell
  const std::vector<double>& getElectroionizationRecoilEnergyGrid(
                           const unsigned subshell ) const;

  //! Return the electroionization recoil energy for a subshell and incident energy
  const std::vector<double>& getElectroionizationRecoilEnergyAtEnergy(
                           const unsigned subshell,
                           const double incident_energy ) const;

  //! Return the electroionization recoil energy for a subshell and all incident energies
  const std::map<double,std::vector<double> >&
    getElectroionizationRecoilEnergy( const unsigned subshell ) const;

  //! Return the electroionization recoil energy pdf for a subshell and incident energy
  const std::vector<double>& getElectroionizationRecoilPDFAtEnergy(
                           const unsigned subshell,
                           const double incident_energy ) const;

  //! Return the electroionization recoil energy pdf for a subshell and all incident energies
  const std::map<double,std::vector<double> >&
    getElectroionizationRecoilPDF( const unsigned subshell ) const;

  //! Return the electroionization recoil energy pdf interpolation type for a subshell and all incident energies
  const std::string&
    getElectroionizationRecoilPDFInterpType( const unsigned subshell ) const;

//---------------------------------------------------------------------------//
// GET BREMSSTRAHLUNG DATA
//---------------------------------------------------------------------------//

  //! Return the bremsstrahlung electron cross section Energy Grid
  const std::vector<double>& getBremsstrahlungCrossSectionEnergyGrid() const;

  //! Return the bremsstrahlung electron cross section
  const std::vector<double>& getBremsstrahlungCrossSection() const;

  //! Return the bremsstrahlung electron cross section interpolation type
  const std::string& getBremsstrahlungCrossSectionInterpType() const;

  //! Return the bremsstrahlung incident electron energy grid for the average energy of the secondary photon
  const std::vector<double>& getBremsstrahlungAveragePhotonIncidentEnergy() const;

  //! Return the bremsstrahlung average energy of the secondary photon
  const std::vector<double>& getBremsstrahlungAveragePhotonEnergy() const;

  //! Return the bremsstrahlung average energy of the secondary photon interpolation type
  const std::string& getBremsstrahlungAveragePhotonEnergyInterpType() const;

  //! Return the bremsstrahlung incident electron energy grid for the secondary photon spectrum
  const std::vector<double>& getBremsstrahlungPhotonEnergyGrid() const;

  //! Return the bremsstrahlung photon energy for an incident energy
  const std::vector<double>& getBremsstrahlungPhotonEnergyAtEnergy(
					       const double incident_energy ) const;

  //! Return the bremsstrahlung photon energy for all incident energies
  const std::map<double,std::vector<double> >&
    getBremsstrahlungPhotonEnergy() const;

  //! Return the bremsstrahlung photon energy pdf for an incident energy
  const std::vector<double>& getBremsstrahlungPhotonPDFAtEnergy(
					       const double incident_energy ) const;

  //! Return the bremsstrahlung photon energy pdf for all incident energies
  const std::map<double,std::vector<double> >&
    getBremsstrahlungPhotonPDF() const;

  //! Return the bremsstrahlung photon energy pdf interpolation type for all incident energies
  const std::string& getBremsstrahlungPhotonPDFInterpType() const;

  //! Return the bremsstrahlung incident electron energy grid for the average energy of the secondary electron
  const std::vector<double>& getBremsstrahlungAverageElectronIncidentEnergy() const;

  //! Return the bremsstrahlung average energy of the secondary electron
  const std::vector<double>& getBremsstrahlungAverageElectronEnergy() const;

  //! Return the bremsstrahlung average energy of the secondary electron interpolation type
  const std::string& getBremsstrahlungAverageElectronEnergyInterpType() const;

//---------------------------------------------------------------------------//
// GET ATOMIC EXCITATION DATA
//---------------------------------------------------------------------------//

  //! Return the atomic excitation electron energy grid
  const std::vector<double>& getAtomicExcitationEnergyGrid() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& getAtomicExcitationCrossSection() const;

  //! Return the atomic excitation electron cross section interpolation type
  const std::string& getAtomicExcitationCrossSectionInterpType() const;

  //! Return the atomic excitation average energy loss
  const std::vector<double>& getAtomicExcitationEnergyLoss() const;

  //! Return the atomic excitation average energy loss interpolation type
  const std::string& getAtomicExcitationEnergyLossInterpType() const;

protected:

  //! Default constructor
  ENDLDataContainer()
  { /* ... */ }

  //! Load the archived object (implementation)
  void loadFromFileImpl( const boost::filesystem::path& archive_name_with_path ) final override;

  //! Archive the object (implementation)
  void saveToFileImpl( const boost::filesystem::path& archive_name_with_path,
                       const bool overwrite ) const final override;

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

  //! Set the atomic weight
  void setAtomicWeight( const double atomic_weight );

//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//

  //! Set the atomic subshells
  void setSubshells( const std::set<unsigned>& subshells );

  //! Set the number of electrons in subshells
  void setSubshellOccupancy(
    const std::map<unsigned,double>& number_of_electrons );

  //! Set the binding energy in subshells
  void setSubshellBindingEnergy(
    const std::map<unsigned,double>& binding_energies );

  //! Set the kinetic energy in subshells
  void setSubshellKineticEnergy(
    const std::map<unsigned,double>& kinetic_energies );

  //! Set the average radius in subshells
  void setSubshellAverageRadius(
    const std::map<unsigned,double>& average_radii );

  //! Set the radiative level width in subshells
  void setSubshellRadiativeLevel(
    const std::map<unsigned,double>& radiative_levels );

  //! Set the non radiative level in subshells
  void setSubshellNonRadiativeLevel(
    const std::map<unsigned,double>& non_radiative_levels );

  //! Set the average energy to the residual atom per initial vacancy
  void setLocalDepositionPerInitialVacancy(
    const std::map<unsigned,double>& local_depositions );

  //! Set the average number of photons per initial vacancy
  void setAveragePhotonsPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_numbers );

  //! Set the average energy of photons per initial vacancy
  void setAveragePhotonEnergyPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_energies );

  //! Set the average number of electrons per initial vacancy
  void setAverageElectronsPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_numbers );

  //! Set the average energy of electrons per initial vacancy
  void setAverageElectronEnergyPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_energies );

  //! Set the radiative transition probability
  void setRadiativeTransitionProbability(
    const unsigned subshell,
    const std::map<unsigned,double>&
        radiative_transition_probability );

  //! Set the radiative transition energy
  void setRadiativeTransitionEnergy(
    const unsigned subshell,
    const std::map<unsigned,double>&
        radiative_transition_energy );

  //! Set the non radiative transition probability
  void setNonRadiativeTransitionProbability(
    const unsigned subshell,
    std::map<unsigned,std::map<unsigned,double> >&
        non_radiative_transition_probability );

  //! Set the non radiative transition energy
  void setNonRadiativeTransitionEnergy(
    const unsigned subshell,
    std::map<unsigned,std::map<unsigned,double> >&
        non_radiative_transition_energy );

//---------------------------------------------------------------------------//
// SET COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  //! Set the coherent cross section energy grid
  void setCoherentCrossSectionEnergyGrid(
    const std::vector<double>& energy_grid );

  //! Set the coherent photon cross section
  void setCoherentCrossSection( const std::vector<double>& cross_section );

  //! Set the coherent photon cross section interpolation type
  template<typename InterpType>
  void setCoherentCrossSectionInterpType();

  //! Set the argument for the coherent form factor
  void setCoherentFormFactorArgument(
    const std::vector<double>& form_factor_argument );

  //! Set the coherent form factor
  void setCoherentFormFactor( const std::vector<double>& form_factor );

  //! Set the coherent form factor interpolation type
  template<typename InterpType>
  void setCoherentFormFactorInterpType();

  //! Set the incident energy grid for the coherent imaginary anomalous scattering factor
  void setCoherentImaginaryAnomalousFactorIncidentEnergy(
    const std::vector<double>& anomalous_incident_energy );

  //! Set the coherent imaginary anomalous scattering factor
  void setCoherentImaginaryAnomalousFactor(
    const std::vector<double>& anomalous_factor );

  //! Set the coherent imaginary anomalous scattering factor interpolation type
  template<typename InterpType>
  void setCoherentImaginaryAnomalousFactorInterpType();

  //! Set the incident energy grid for the coherent real anomalous scattering factor
  void setCoherentRealAnomalousFactorIncidentEnergy(
    const std::vector<double>& anomalous_incident_energy );

  //! Set the coherent real anomalous scattering factor
  void setCoherentRealAnomalousFactor(
    const std::vector<double>& anomalous_factor );

  //! Set the coherent real anomalous scattering factor interpolation type
  template<typename InterpType>
  void setCoherentRealAnomalousFactorInterpType();

  //! Set the incident energy grid for the coherent average energy of the scattered photon
  void setCoherentAveragePhotonIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the coherent average energy of the scattered photon
  void setCoherentAveragePhotonEnergy(
    const std::vector<double>& average_energy );

  //! Set the coherent average energy of the scattered photon interpolation type
  template<typename InterpType>
  void setCoherentAveragePhotonEnergyInterpType();

//---------------------------------------------------------------------------//
// SET INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  //! Set the incoherent cross section energy grid
  void setIncoherentCrossSectionEnergyGrid(
    const std::vector<double>& energy_grid );

  //! Set the incoherent photon cross section
  void setIncoherentCrossSection( const std::vector<double>& cross_section );

  //! Set the incoherent photon cross section interpolation type
  template<typename InterpType>
  void setIncoherentCrossSectionInterpType();

  //! Set the argument for the incoherent scattering function
  void setIncoherentScatteringFunctionArgument(
    const std::vector<double>& scattering_function_argument );

  //! Set the incoherent scattering function
  void setIncoherentScatteringFunction(
    const std::vector<double>& scattering_function );

  //! Set the incoherent scattering function interpolation type
  template<typename InterpType>
  void setIncoherentScatteringFunctionInterpType();

  //! Set the incident energy grid for the incoherent average energy of the scattered photon
  void setIncoherentAveragePhotonIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the incoherent average energy of the scattered photon
  void setIncoherentAveragePhotonEnergy(
    const std::vector<double>& average_energy );

  //! Set the incoherent average energy of the scattered photon
  template<typename InterpType>
  void setIncoherentAveragePhotonEnergyInterpType();

  //! Set the incident energy grid for the incoherent average energy of the recoil electron
  void setIncoherentAverageElectronIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the incoherent average energy of the recoil electron
  void setIncoherentAverageElectronEnergy(
    const std::vector<double>& average_energy );

  //! Set the incoherent average energy of the recoil electron interpolation type
  template<typename InterpType>
  void setIncoherentAverageElectronEnergyInterpType();

//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  //! Set the photoelectric cross section energy grid
  void setPhotoelectricCrossSectionEnergyGrid(
    const std::vector<double>& energy_grid );

  //! Set the photoelectric photon cross section
  void setPhotoelectricCrossSection( const std::vector<double>& cross_section );

  //! Set the photoelectric photon cross section interpolation type
  template<typename InterpType>
  void setPhotoelectricCrossSectionInterpType();

  //! Set the incident energy grid for the photoelectric average energy of the residual atom
  void setPhotoelectricAverageResidualIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the photoelectric average energy of the residual atom
  void setPhotoelectricAverageResidualEnergy(
    const std::vector<double>& average_energy );

  //! Set the photoelectric average energy of the residual atom interpolation type
  template<typename InterpType>
  void setPhotoelectricAverageResidualEnergyInterpType();

  //! Set the incident energy grid for the photoelectric average energy of the secondary photons
  void setPhotoelectricAveragePhotonsIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the photoelectric average energy of the secondary photons
  void setPhotoelectricAveragePhotonsEnergy(
    const std::vector<double>& average_energy );

  //! Set the photoelectric average energy of the secondary photons interpolation type
  template<typename InterpType>
  void setPhotoelectricAveragePhotonsEnergyInterpType();

  //! Set the incident energy grid for the photoelectric average energy of the secondary electrons
  void setPhotoelectricAverageElectronsIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the photoelectric average energy of the secondary electrons
  void setPhotoelectricAverageElectronsEnergy(
    const std::vector<double>& average_energy );

  //! Set the photoelectric average energy of the secondary electrons interpolation type
  template<typename InterpType>
  void setPhotoelectricAverageElectronsEnergyInterpType();

//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  //! Set the photoelectric cross section energy grid for a subshell
  void setPhotoelectricCrossSectionEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& energy_grid );

  //! Set the photoelectric photon cross section for a subshell
  void setPhotoelectricCrossSection(
    const unsigned subshell,
    const std::vector<double>& cross_section );

  //! Set the photoelectric photon cross section interpolation type for a subshell
  template<typename InterpType>
  void setPhotoelectricCrossSectionInterpType( const unsigned subshell );

  //! Set the incident energy grid for the photoelectric average energy of the residual atom for a subshell
  void setPhotoelectricAverageResidualIncidentEnergy(
    const unsigned subshell,
    const std::vector<double>& incident_energy );

  //! Set the photoelectric average energy of the residual atom for a subshell
  void setPhotoelectricAverageResidualEnergy(
    const unsigned subshell,
    const std::vector<double>& average_energy  );

  //! Set the photoelectric average energy of the residual atom interpolation type for a subshell
  template<typename InterpType>
  void setPhotoelectricAverageResidualEnergyInterpType( const unsigned subshell );

  //! Set the incident energy grid for the photoelectric average energy of the secondary photons for a subshell
  void setPhotoelectricAveragePhotonsIncidentEnergy(
    const unsigned subshell,
    const std::vector<double>& incident_energy );

  //! Set the photoelectric average energy of the secondary photons for a subshell
  void setPhotoelectricAveragePhotonsEnergy(
    const unsigned subshell,
    const std::vector<double>& average_energy  );

  //! Set the photoelectric average energy of the secondary photons interpolation type for a subshell
  template<typename InterpType>
  void setPhotoelectricAveragePhotonsEnergyInterpType( const unsigned subshell );

  //! Set the incident energy grid for the photoelectric average energy of the secondary electrons for a subshell
  void setPhotoelectricAverageElectronsIncidentEnergy(
    const unsigned subshell,
    const std::vector<double>& incident_energy );

  //! Set the photoelectric average energy of the secondary electrons for a subshell
  void setPhotoelectricAverageElectronsEnergy(
    const unsigned subshell,
    const std::vector<double>& average_energy );

  //! Set the photoelectric average energy of the secondary electrons interpolation type for a subshell
  template<typename InterpType>
  void setPhotoelectricAverageElectronsEnergyInterpType( const unsigned subshell );

//---------------------------------------------------------------------------//
// SET PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  //! Set the pair production cross section energy grid
  void setPairProductionCrossSectionEnergyGrid(
    const std::vector<double>& energy_grid );

  //! Set the pair production photon cross section
  void setPairProductionCrossSection( const std::vector<double>& cross_section );

  //! Set the pair production photon cross section interpolation type
  template<typename InterpType>
  void setPairProductionCrossSectionInterpType();

  //! Set the incident energy grid for the pair production average energy of the secondary positron
  void setPairProductionAveragePositronIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the pair production average energy of the secondary positron
  void setPairProductionAveragePositronEnergy(
    const std::vector<double>& average_energy );

  //! Set the pair production average energy of the secondary positron interpolation type
  template<typename InterpType>
  void setPairProductionAveragePositronEnergyInterpType();

  //! Set the incident energy grid for the pair production average energy of the secondary electron
  void setPairProductionAverageElectronIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the pair production average energy of the secondary electron
  void setPairProductionAverageElectronEnergy(
    const std::vector<double>& average_energy );

  //! Set the pair production average energy of the secondary electron interpolation type
  template<typename InterpType>
  void setPairProductionAverageElectronEnergyInterpType();

//---------------------------------------------------------------------------//
// SET TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  //! Set the triplet production cross section energy grid
  void setTripletProductionCrossSectionEnergyGrid(
    const std::vector<double>& energy_grid );

  //! Set the triplet production photon cross section
  void setTripletProductionCrossSection(
    const std::vector<double>& cross_section );

  //! Set the triplet production photon cross section interpolation type
  template<typename InterpType>
  void setTripletProductionCrossSectionInterpType();

  //! Set the incident energy grid for the triplet production average energy of the secondary positron
  void setTripletProductionAveragePositronIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the triplet production average energy of the secondary positron
  void setTripletProductionAveragePositronEnergy(
    const std::vector<double>& average_energy );

  //! Set the triplet production average energy of the secondary positron interpolation type
  template<typename InterpType>
  void setTripletProductionAveragePositronEnergyInterpType();

  //! Set the incident energy grid for the triplet production average energy of the secondary electron
  void setTripletProductionAverageElectronIncidentEnergy(
    const std::vector<double>& incident_energy );

  //! Set the triplet production average energy of the secondary electron
  void setTripletProductionAverageElectronEnergy(
    const std::vector<double>& average_energy );

  //! Set the triplet production average energy of the secondary electron interpolation type
  template<typename InterpType>
  void setTripletProductionAverageElectronEnergyInterpType();

//---------------------------------------------------------------------------//
// SET ELASTIC DATA
//---------------------------------------------------------------------------//

  //! Set the elastic electron energy grid
  void setElasticEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the electron elastic transport cross section
  void setElasticTransportCrossSection(
    const std::vector<double>& elastic_transport_cross_section);

  //! Set the electron elastic transport cross section interpolation type
  template<typename InterpType>
  void setElasticTransportCrossSectionInterpType();

  //! Set the electron elastic cross section below mu = 0.999999
  void setCutoffElasticCrossSection(
    const std::vector<double>& cutoff_elastic_cross_section );

  //! Set the electron elastic cross section below mu = 0.999999 interpolation type
  template<typename InterpType>
  void setCutoffElasticCrossSectionInterpType();

  //! Set the incident energy grid for the cutoff elastic average energy to the residual atom
  void setCutoffElasticResidualIncidentEnergy(
    const std::vector<double>& residual_incident_energy );

  //! Set the cutoff elastic average energy to the residual atom
  void setCutoffElasticResidualEnergy(
    const std::vector<double>& residual_energy );

  //! Set the cutoff elastic average energy to the residual atom interpolation type
  template<typename InterpType>
  void setCutoffElasticResidualEnergyInterpType();

  //! Set the incident energy grid for the cutoff elastic average energy of the scattered electron
  void setCutoffElasticScatteredElectronIncidentEnergy(
    const std::vector<double>& scattered_electron_incident_energy );

  //! Set the cutoff elastic average energy of the scattered electron
  void setCutoffElasticScatteredElectronEnergy(
    const std::vector<double>& scattered_electron_average_energy );

  //! Set the cutoff elastic average energy of the scattered electron
  template<typename InterpType>
  void setCutoffElasticScatteredElectronEnergyInterpType();

  //! Set the cutoff elastic angular energy grid
  void setCutoffElasticAngularEnergyGrid(
    const std::vector<double>& cutoff_elastic_angular_energy_grid );

  //! Set the cutoff elastic scattering angles for an incident energy
  void setCutoffElasticAnglesAtEnergy(
    const double incident_energy,
    const std::vector<double>& elastic_angles );

  //! Set the cutoff elastic scattering pdf for an incident energy
  void setCutoffElasticPDFAtEnergy(
    const double incident_energy,
    const std::vector<double>& elastic_pdf );

  //! Set the elastic scattering angles
  void setCutoffElasticAngles(
    const std::map<double,std::vector<double> >& elastic_angles );

  //! Set the elastic scattering pdf
  void setCutoffElasticPDF(
    const std::map<double,std::vector<double> >& elastic_pdf );

  //! Set the elastic scattering pdf interpolation type
  template<typename InterpType>
  void setCutoffElasticPDFInterpType();

  //! Set the total elastic electron cross section
  void setTotalElasticCrossSection(
    const std::vector<double>& total_elastic_cross_section );

  //! Set the total elastic electron cross section interpolation type
  template<typename InterpType>
  void setTotalElasticCrossSectionInterpType();

/*
  //! Set the screened Rutherford elastic normalization constant
  void setScreenedRutherfordNormalizationConstant(
    const std::vector<double>& screened_rutherford_normalization_constant );

  //! Set Moliere's screening constant
  void setMoliereScreeningConstant(
    const std::vector<double>& moliere_screening_constant );

  //! Set the screened Rutherford elastic electron cross section
  void setScreenedRutherfordElasticCrossSection(
    const std::vector<double>& total_elastic_cross_section );

  //! Set the screened Rutherford elastic cross section threshold energy bin index
  void setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex( const unsigned index );
*/

//---------------------------------------------------------------------------//
// SET ELECTROIONIZATION DATA
//---------------------------------------------------------------------------//

  //! Set the electroionization energy grid for the cross section for a subshell
  void setElectroionizationCrossSectionEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& electroionization_energy_grid );

  //! Set the electroionization electron cross section for a subshell
  void setElectroionizationCrossSection(
    const unsigned subshell,
    const std::vector<double>& electroionization_cross_section );

  //! Set the electroionization electron cross section interpolation type for a subshell
  template<typename InterpType>
  void setElectroionizationCrossSectionInterpType( const unsigned subshell );

  //! Set the electroionization incident energy grid for the average scattered electron energy for a subshell
  void setElectroionizationAverageScatteredElectronIncidentEnergy(
    const unsigned subshell,
    const std::vector<double>& average_scattered_electron_incident_energy );

  //! Set the electroionization average scattered electron energy for a subshell
  void setElectroionizationAverageScatteredElectronEnergy(
    const unsigned subshell,
    const std::vector<double>& average_scattered_electron_energy );

  //! Set the electroionization average scattered electron energy interpolation type for a subshell
  template<typename InterpType>
  void setElectroionizationAverageScatteredElectronEnergyInterpType( const unsigned subshell );

  //! Set the electroionization incident energy grid for the average recoil electron energy for a subshell
  void setElectroionizationAverageRecoilElectronIncidentEnergy(
    const unsigned subshell,
    const std::vector<double>& average_recoil_electron_incident_energy );

  //! Set the electroionization average recoil electron energy for a subshell
  void setElectroionizationAverageRecoilElectronEnergy(
    const unsigned subshell,
    const std::vector<double>& average_recoil_electron_energy );

  //! Set the electroionization average recoil electron energy interp type for a subshell
  template<typename InterpType>
  void setElectroionizationAverageRecoilElectronEnergyInterpType( const unsigned subshell );

  //! Set the electroionization energy grid for the recoil electron spectrum
  void setElectroionizationRecoilEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& electroionization_recoil_energy_grid );

  //! Set the electroionization recoil energy for an incident energy and subshell
  void setElectroionizationRecoilEnergyAtIncidentEnergy(
    const unsigned subshell,
    const double incident_energy,
    const std::vector<double>& electroionization_recoil_energy );

  //! Set the electroionization recoil energy pdf for an incident energy and subshell
  void setElectroionizationRecoilPDFAtIncidentEnergy(
    const unsigned subshell,
    const double incident_energy,
    const std::vector<double>& electroionization_recoil_pdf );

  //! Set electroionization recoil energy for all incident energies in a subshell
  void setElectroionizationRecoilEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_energy );

  //! Set electroionization recoil energy pdf for all incident energies in a subshell
  void setElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_pdf );

  //! Set electroionization recoil energy pdf interpolation type for all incident energies in a subshell
  template<typename InterpType>
  void setElectroionizationRecoilPDFInterpType( const unsigned subshell );

//---------------------------------------------------------------------------//
// SET BREMSSTRAHLUNG DATA
//---------------------------------------------------------------------------//

  //! Set the bremsstrahlung electron cross section energy grid
  void setBremsstrahlungCrossSectionEnergyGrid(
    const std::vector<double>& bremsstrahlung_cross_section_energy_grid );

  //! Set the bremsstrahlung electron cross section
  void setBremsstrahlungCrossSection(
    const std::vector<double>& bremsstrahlung_cross_section );

  //! Set the bremsstrahlung electron cross section interpolation type
  template<typename InterpType>
  void setBremsstrahlungCrossSectionInterpType();

  //! Set the bremsstrahlung incident electron energy grid for the average energy of the secondary photon
  void setBremsstrahlungAveragePhotonIncidentEnergy(
    const std::vector<double>& bremsstrahlung_average_photon_incident_energy );

  //! Set the bremsstrahlung average energy of the secondary photon
  void setBremsstrahlungAveragePhotonEnergy(
    const std::vector<double>& bremsstrahlung_average_photon_energy );

  //! Set the bremsstrahlung average energy of the secondary photon interpolation type
  template<typename InterpType>
  void setBremsstrahlungAveragePhotonEnergyInterpType();

  //! Set the bremsstrahlung energy grid for the secondary photon spectrum
  void setBremsstrahlungPhotonEnergyGrid(
    const std::vector<double>& bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung photon energy for an incident energy
  void setBremsstrahlungPhotonEnergyAtIncidentEnergy(
    const double incident_energy,
    const std::vector<double>& bremsstrahlung_photon_energy );

  //! Set the bremsstrahlung photon energy pdf for an incident energy
  void setBremsstrahlungPhotonPDFAtIncidentEnergy(
    const double incident_energy,
    const std::vector<double>& bremsstrahlung_photon_pdf );

  //! Set all the bremsstrahlung photon energy data
  void setBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_energy );

  //! Set all the bremsstrahlung photon energy pdf data
  void setBremsstrahlungPhotonPDF(
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_pdf );

  //! Set all the bremsstrahlung photon energy pdf data interpolation type
  template<typename InterpType>
  void setBremsstrahlungPhotonPDFInterpType();

  //! Set the bremsstrahlung incident electron energy grid for the average energy of the secondary electron
  void setBremsstrahlungAverageElectronIncidentEnergy(
    const std::vector<double>& bremsstrahlung_average_electron_incident_energy );

  //! Set the bremsstrahlung average energy of the secondary electron
  void setBremsstrahlungAverageElectronEnergy(
    const std::vector<double>& bremsstrahlung_average_electron_energy );

  //! Set the bremsstrahlung average energy of the secondary electron interpolation type
  template<typename InterpType>
  void setBremsstrahlungAverageElectronEnergyInterpType();

//---------------------------------------------------------------------------//
// SET ATOMIC EXCITATION DATA
//---------------------------------------------------------------------------//

  //! Set the atomic excitation electron energy grid
  void setAtomicExcitationEnergyGrid(
    const std::vector<double>& atomic_excitation_energy_grid );

  //! Set the atomic excitation electron cross section
  void setAtomicExcitationCrossSection(
    const std::vector<double>& atomic_excitation_cross_section );

  //! Set the atomic excitation electron cross section interpolation type
  template<typename InterpType>
  void setAtomicExcitationCrossSectionInterpType();

  //! Set the atomic excitation average energy loss
  void setAtomicExcitationEnergyLoss(
            const std::vector<double>& atomic_excitation_energy_loss );

  //! Set the atomic excitation average energy loss interpolation type
  template<typename InterpType>
  void setAtomicExcitationEnergyLossInterpType();

private:

  // Save the data to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The name used in archive name-value pairs
  static const std::string s_archive_name;

  // The atomic number
  unsigned d_atomic_number;

  // The atomic weight
  double d_atomic_weight;

//---------------------------------------------------------------------------//
// RELAXATION DATA
//---------------------------------------------------------------------------//
  // The atomic subshells (ENDF designators)
  std::set<unsigned> d_subshells;

  // The number of electrons in subshells
  std::map<unsigned,double> d_subshell_occupancies;

  // The binding energy in subshells
  std::map<unsigned,double> d_subshell_binding_energies;

  // The kinetic energy in subshells
  std::map<unsigned,double> d_subshell_kinetic_energies;

  // The average radius in subshells
  std::map<unsigned,double> d_subshell_average_radii;

  // The radiative level width in subshells
  std::map<unsigned,double> d_subshell_radiative_levels;

  // The non radiative level in subshells
  std::map<unsigned,double> d_subshell_non_radiative_levels;

  // The average energy to the residual atom per initial vacancy
  std::map<unsigned,double> d_subshell_local_depositions;

  // The average number of photons per initial vacancy
  std::map<unsigned,double> d_subshell_average_photon_numbers;

  // The average energy of photons per initial vacancy
  std::map<unsigned,double> d_subshell_average_photon_energies;

  // The average number of electrons per initial vacancy
  std::map<unsigned,double> d_subshell_average_electron_numbers;

  // The average energy of particles per initial vacancy
  std::map<unsigned,double> d_subshell_average_electron_energies;

  // The radiative transition probability
  std::map<unsigned,std::map<unsigned,double> >
    d_radiative_transition_probabilities;

  // The radiative transition energy
  std::map<unsigned,std::map<unsigned,double> >
    d_radiative_transition_energies;

  // The non radiative transition probability
  std::map<unsigned,std::map<unsigned,std::map<unsigned,double> > >
    d_non_radiative_transition_probabilities;

  // The non radiative transition energy
  std::map<unsigned,std::map<unsigned,std::map<unsigned,double> > >
    d_non_radiative_transition_energies;

//---------------------------------------------------------------------------//
// THE COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  // The coherent cross section energy grid
  std::vector<double> d_coherent_cross_section_energy_grid;

  // The coherent photon cross section
  std::vector<double> d_coherent_cross_section;

  // The coherent photon cross section interpolation type
  std::string d_coherent_cross_section_interp_type;

  // The argument for the coherent form factor (1/cm)
  std::vector<double> d_coherent_form_factor_argument;

  // The coherent form factor
  std::vector<double> d_coherent_form_factor;

  // The coherent form factor interpolation type
  std::string d_coherent_form_factor_interp_type;

  // The incident energy grid for the coherent imaginary anomalous scattering factor
  std::vector<double>
    d_coherent_imaginary_anomalous_scattering_factor_incident_energy;

  // The coherent imaginary anomalous scattering factor
  std::vector<double> d_coherent_imaginary_anomalous_scattering_factor;

  // The coherent imaginary anomalous scattering factor interpolation type
  std::string d_coherent_imaginary_anomalous_scattering_factor_interp_type;

  // The incident energy grid for the coherent real anomalous scattering factor
  std::vector<double> d_coherent_real_anomalous_scattering_factor_incident_energy;

  // The coherent real anomalous scattering factor
  std::vector<double> d_coherent_real_anomalous_scattering_factor;

  // The coherent real anomalous scattering factor
  std::string d_coherent_real_anomalous_scattering_factor_interp_type;

  // The incident energy grid for the coherent average energy of the scattered photon
  std::vector<double> d_coherent_average_photon_incident_energy;

  // The coherent average energy of the scattered photon
  std::vector<double> d_coherent_average_photon_energy;

  // The coherent average energy of the scattered photon interpolation type
  std::string d_coherent_average_photon_energy_interp_type;

//---------------------------------------------------------------------------//
// THE INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  // The incoherent cross section energy grid
  std::vector<double> d_incoherent_cross_section_energy_grid;

  // The incoherent photon cross section
  std::vector<double> d_incoherent_cross_section;

  // The incoherent photon cross section interpolation type
  std::string d_incoherent_cross_section_interp_type;

  // The argument for the incoherent scattering function (1/cm)
  std::vector<double> d_incoherent_scattering_function_argument;

  // The incoherent scattering function
  std::vector<double> d_incoherent_scattering_function;

  // The incoherent scattering function interpolation type
  std::string d_incoherent_scattering_function_interp_type;

  // The incident energy grid for the incoherent average energy of the scattered photon
  std::vector<double> d_incoherent_average_photon_incident_energy;

  // The incoherent average energy of the scattered photon
  std::vector<double> d_incoherent_average_photon_energy;

  // The incoherent average energy of the scattered photon interpolation type
  std::string d_incoherent_average_photon_energy_interp_type;

  // The incident energy grid for the incoherent average energy of the recoil electron
  std::vector<double> d_incoherent_average_electron_incident_energy;

  // The incoherent average energy of the recoil electron
  std::vector<double> d_incoherent_average_electron_energy;

  // The incoherent average energy of the recoil electron interpolation type
  std::string d_incoherent_average_electron_energy_interp_type;

//---------------------------------------------------------------------------//
// THE PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  // The photoelectric cross section energy grid
  std::vector<double> d_photoelectric_cross_section_energy_grid;

  // The photoelectric photon cross section
  std::vector<double> d_photoelectric_cross_section;

  // The photoelectric photon cross section interpolation type
  std::string d_photoelectric_cross_section_interp_type;

  // The incident energy grid for the photoelectric average energy of the residual atom
  std::vector<double> d_photoelectric_average_residual_incident_energy;

  // The photoelectric average energy of the residual atom
  std::vector<double> d_photoelectric_average_residual_energy;

  // The photoelectric average energy of the residual atom interpolation type
  std::string d_photoelectric_average_residual_energy_interp_type;

  // The incident energy grid for the photoelectric average energy of the secondary photons
  std::vector<double> d_photoelectric_secondary_photons_incident_energy;

  // The photoelectric average energy of the secondary photons
  std::vector<double> d_photoelectric_secondary_photons_energy;

  // The photoelectric average energy of the secondary photons interpolation type
  std::string d_photoelectric_secondary_photons_energy_interp_type;

  // The incident energy grid for the photoelectric average energy of the secondary electrons
  std::vector<double> d_photoelectric_secondary_electrons_incident_energy;

  // The photoelectric average energy of the secondary electrons
  std::vector<double> d_photoelectric_secondary_electrons_energy;

  // The photoelectric average energy of the secondary electrons interpolation type
  std::string d_photoelectric_secondary_electrons_energy_interp_type;

//---------------------------------------------------------------------------//
// THE PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  // The photoelectric cross section energy grid for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_cross_section_energy_grid;

  // The photoelectric photon cross section for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_cross_section;

  // The photoelectric photon cross section for a subshell
  std::map<unsigned,std::string>
    d_photoelectric_subshell_cross_section_interp_type;

  // The incident energy grid for the photoelectric average energy of the residual atom for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_average_residual_incident_energy;

  // The photoelectric average energy of the residual atom for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_average_residual_energy;

  // The photoelectric average energy of the residual atom interpolation type for a subshell
  std::map<unsigned,std::string>
    d_photoelectric_subshell_average_residual_energy_interp_type;

  // The incident energy grid for the photoelectric average energy of the secondary photons for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_secondary_photons_incident_energy;

  // The photoelectric average energy of the secondary photons for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_secondary_photons_energy;

  // The photoelectric average energy of the secondary photons interpolation type for a subshell
  std::map<unsigned,std::string>
    d_photoelectric_subshell_secondary_photons_energy_interp_type;

  // The incident energy grid for the photoelectric average energy of the secondary electrons for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_secondary_electrons_incident_energy;

  // The photoelectric average energy of the secondary electrons for a subshell
  std::map<unsigned,std::vector<double> >
    d_photoelectric_subshell_secondary_electrons_energy;

  // The photoelectric average energy of the secondary electrons interpolation type for a subshell
  std::map<unsigned,std::string>
    d_photoelectric_subshell_secondary_electrons_energy_interp_type;

//---------------------------------------------------------------------------//
// THE PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  // The pair production cross section energy grid
  std::vector<double> d_pair_production_cross_section_energy_grid;

  // The pair production photon cross section
  std::vector<double> d_pair_production_cross_section;

  // The pair production photon cross section interpolation type
  std::string d_pair_production_cross_section_interp_type;

  // The incident energy grid for the pair production average energy of the secondary positron
  std::vector<double> d_pair_production_average_positron_incident_energy;

  // The pair production average energy of the secondary positron
  std::vector<double> d_pair_production_average_positron_energy;

  // The pair production average energy of the secondary positron interpolation type
  std::string d_pair_production_average_positron_energy_interp_type;

  // The incident energy grid for the pair production average energy of the secondary electron
  std::vector<double> d_pair_production_average_electron_incident_energy;

  // The pair production average energy of the secondary electron
  std::vector<double> d_pair_production_average_electron_energy;

  // The pair production average energy of the secondary electron interpolation type
  std::string d_pair_production_average_electron_energy_interp_type;

//---------------------------------------------------------------------------//
// THE TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  // The triplet production cross section energy grid
  std::vector<double> d_triplet_production_cross_section_energy_grid;

  // The triplet production photon cross section
  std::vector<double> d_triplet_production_cross_section;

  // The triplet production photon cross section interpolation type
  std::string d_triplet_production_cross_section_interp_type;

  // The incident energy grid for the triplet production average energy of the secondary positron
  std::vector<double> d_triplet_production_average_positron_incident_energy;

  // The triplet production average energy of the secondary positron
  std::vector<double> d_triplet_production_average_positron_energy;

  // The triplet production average energy of the secondary positron interpolation type
  std::string d_triplet_production_average_positron_energy_interp_type;

  // The incident energy grid for the triplet production average energy of the secondary electron
  std::vector<double> d_triplet_production_average_electron_incident_energy;

  // The triplet production average energy of the secondary electron
  std::vector<double> d_triplet_production_average_electron_energy;

  // The triplet production average energy of the secondary electron interpolation type
  std::string d_triplet_production_average_electron_energy_interp_type;

//---------------------------------------------------------------------------//
// ELASTIC ELECTRON DATA
//---------------------------------------------------------------------------//

  // The elastic energy grid (MeV)
  std::vector<double> d_elastic_energy_grid;

  // The elastic transport cross section (b)
  std::vector<double> d_elastic_transport_cross_section;

  // The elastic transport cross section interpolation type
  std::string d_elastic_transport_cross_section_interp_type;

  // The cutoff elastic electron cross section (b)
  std::vector<double> d_cutoff_elastic_cross_section;

  // The cutoff elastic electron cross section interpolation type
  std::string d_cutoff_elastic_cross_section_interp_type;

  // The incident energy grid for the cutoff elastic average energy to the residual atom
  std::vector<double> d_cutoff_elastic_residual_incident_energy;

  // The cutoff elastic average energy to the residual atom
  std::vector<double> d_cutoff_elastic_residual_energy;

  // The cutoff elastic average energy to the residual atom interpolation type
  std::string d_cutoff_elastic_residual_energy_interp_type;

  // The incident energy grid for the cutoff elastic average energy to the scattered electron
  std::vector<double> d_cutoff_elastic_scattered_electron_incident_energy;

  // The cutoff elastic average energy to the scattered electron
  std::vector<double> d_cutoff_elastic_scattered_electron_energy;

  // The cutoff elastic average energy to the scattered electron interpolation type
  std::string d_cutoff_elastic_scattered_electron_energy_interp_type;

  // The cutoff elastic angular energy grid
  std::vector<double> d_cutoff_elastic_angular_energy_grid;

  // The cutoff elastic scattering angles
  std::map<double,std::vector<double> > d_cutoff_elastic_angles;

  // The cutoff elastic scattering pdf
  std::map<double,std::vector<double> > d_cutoff_elastic_pdf;

  // The cutoff elastic scattering pdf interpolation type
  std::string d_cutoff_elastic_pdf_interp_type;

  // The total elastic electron cross section (b)
  std::vector<double> d_total_elastic_cross_section;

  // The total elastic electron cross section interpolation type
  std::string d_total_elastic_cross_section_interp_type;

/*
  // The screened rutherford normalization constant for elastic scattering
  std::vector<double> d_screened_rutherford_normalization_constant;

  // Moliere's screening constant
  std::vector<double> d_moliere_screening_constant;

  // The screened rutherford elastic electron cross section (b)
  std::vector<double> d_screened_rutherford_elastic_cross_section;
*/

//---------------------------------------------------------------------------//
// ELECTROIONIZATION DATA
//---------------------------------------------------------------------------//

  // The electroionization subshell electron cross section energy grid
  std::map<unsigned,std::vector<double> >
    d_electroionization_subshell_cross_section_energy_grid;

  // The electroionization subshell electron cross section (b)
  std::map<unsigned,std::vector<double> >
    d_electroionization_subshell_cross_section;

  // The electroionization subshell electron cross section interpolation type
  std::map<unsigned,std::string>
    d_electroionization_subshell_cross_section_interp_type;

  // The electroionization incident energy grid for the average scattered electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_scattered_electron_incident_energy;

  // The electroionization average scattered electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_scattered_electron_energy;

  // The electroionization average scattered electron energy interpolation type for a subshell
  std::map<unsigned,std::string>
    d_electroionization_average_scattered_electron_energy_interp_type;

  // The electroionization incident energy grid for the average recoil electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_recoil_electron_incident_energy;

  // The electroionization average recoil electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_recoil_electron_energy;

  // The electroionization average recoil electron energy interpolation type for a subshell
  std::map<unsigned,std::string>
    d_electroionization_average_recoil_electron_energy_interp_type;

  // The electroionization recoil energy grid (MeV) for a subshell
  std::map<unsigned,std::vector<double> > d_electroionization_recoil_energy_grid;

  // The electroionization recoil energy for subshell and incident energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_recoil_energy;

  // The electroionization recoil pdf for subshell and incident energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_recoil_pdf;

  // The electroionization recoil pdf interpolation type for subshell and incident energy
  std::map<unsigned,std::string> d_electroionization_recoil_pdf_interp_type;

//---------------------------------------------------------------------------//
// BREMSSTRAHLUNG DATA
//---------------------------------------------------------------------------//

  // The bremsstrahlung electron cross section energy grid (MeV)
  std::vector<double> d_bremsstrahlung_cross_section_energy_grid;

  // The bremsstrahlung electron cross section (b)
  std::vector<double> d_bremsstrahlung_cross_section;

  // The bremsstrahlung electron cross section interpolation type
  std::string d_bremsstrahlung_cross_section_interp_type;

  // The bremsstrahlung incident electron energy grid for the average energy of the secondary photon
  std::vector<double> d_bremsstrahlung_average_photon_incident_energy;

  // The bremsstrahlung average energy of the secondary photon
  std::vector<double> d_bremsstrahlung_average_photon_energy;

  // The bremsstrahlung average energy of the secondary photon interpolation type
  std::string d_bremsstrahlung_average_photon_energy_interp_type;

  // The bremsstrahlung photon spectrum incident energy grid (MeV)
  std::vector<double> d_bremsstrahlung_photon_energy_grid;

  // The bremsstrahlung photon spectrum energy
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_energy;

  // The bremsstrahlung photon spectrum pdf
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_pdf;

  // The bremsstrahlung photon spectrum pdf interpolation type
  std::string d_bremsstrahlung_photon_pdf_interp_type;

  // The bremsstrahlung incident electron energy grid for the average energy of the secondary electron
  std::vector<double> d_bremsstrahlung_average_electron_incident_energy;

  // The bremsstrahlung average energy of the secondary electron
  std::vector<double> d_bremsstrahlung_average_electron_energy;

  // The bremsstrahlung average energy of the secondary electron interpolation type
  std::string d_bremsstrahlung_average_electron_energy_interp_type;

//---------------------------------------------------------------------------//
// ATOMIC EXCITATION DATA
//---------------------------------------------------------------------------//

  // The atomic excitation electron energy grid (MeV)
  std::vector<double> d_atomic_excitation_energy_grid;

  // The atomic excitation electron cross section (b)
  std::vector<double> d_atomic_excitation_cross_section;

  // The atomic excitation electron cross section interpolation type
  std::string d_atomic_excitation_cross_section_interp_type;

  // The atomic excitation energy loss
  std::vector<double> d_atomic_excitation_energy_loss;

  // The atomic excitation energy loss interpolation type
  std::string d_atomic_excitation_energy_loss_interp_type;
};

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( ENDLDataContainer, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ENDLDataContainer, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, ENDLDataContainer );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ENDLDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ENDL_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer.hpp
//---------------------------------------------------------------------------//
