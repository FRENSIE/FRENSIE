//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native eadl container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_DATA_CONTAINER_HPP
#define DATA_ENDL_DATA_CONTAINER_HPP

// Std Lib Includes
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_StandardArchivableObject.hpp"
#include "Utility_StandardSerializableObject.hpp"

namespace Data{

//! The eadl container
class ENDLDataContainer : public Utility::StandardArchivableObject<ENDLDataContainer,false>, public Utility::StandardSerializableObject<ENDLDataContainer,false>
{

public:

  //! Constructor (from saved archive)
  ENDLDataContainer( 
    const std::string& archive_name,
    const Utility::ArchivableObject::ArchiveType archive_type =
        Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~ENDLDataContainer()
  { /* ... */ }

  //! Return the atomic number
  unsigned getAtomicNumber() const;

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

  //! Return the atomic subshells 
  const std::set<unsigned>& getSubshells() const;

  //! Return the number of electrons for a subshell
  const unsigned getSubshellNumberOfElectrons( const unsigned subshell ) const;

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

  //! Return the average number of particles per initial vacancy
  const unsigned getAverageParticlesPerInitialVacancy( 
    const unsigned subshell ) const;

  //! Return the average energy of particles per initial vacancy
  const double getAverageParitcleEnergyPerInitialVacancy( 
    const unsigned subshell ) const;

  //! Return the radiative transition probability
  const std::vector<double>& getRadiativeTransitionProbability( 
    const unsigned subshell,
    const unsigned secondary_subsell ) const;

  //! Return the radiative transition energy
  const std::vector<double>& getRadiativeTransitionEnergy( 
    const unsigned subshell,
    const unsigned secondary_subshell ) const;

  //! Return the non radiative transition probability
  const std::vector<double>& getNonRadiativeTransitionProbability( 
    const unsigned subshell,
    const unsigned secondary_subshell,
    const unsigned tertiary_subshell ) const;

  //! Return the non radiative transition energy
  const std::vector<double>& getNonRadiativeTransitionEnergy( 
    const unsigned subshell,
    const unsigned secondary_subshell,
    const unsigned tertiary_subshell ) const;

//---------------------------------------------------------------------------//
// GET ELASTIC DATA 
//---------------------------------------------------------------------------//

  //! Return the elastic energy grid
  const std::vector<double>& getElasticEnergyGrid() const;

  //! Return the elastic transport cross section
  const std::vector<double>& getElasticTransportCrossSection() const;

  //! Return the elastic transport cross section
  const std::vector<double>& getCutoffElasticCrossSection() const;

  //! Return the cutoff elastic average energy to the residual atom incoming energy grid
  const std::vector<double>& getCutoffElasticResidualIncomingEnergy() const;

  //! Return the cutoff elastic average energy to the residual atom
  const std::vector<double>& getCutoffElasticResidualEnergy() const;

  //! Return the cutoff elastic average energy to the scattered electron incoming energy grid
  const std::vector<double>& getCutoffElasticScatteredElectronIncomingEnergy() const;

  //! Return the cutoff elastic average energy to the scattered electron
  const std::vector<double>& getCutoffElasticScatteredElectronEnergy() const;

  //! Return the cutoff elastic angular energy grid
  const std::vector<double>& getCutoffElasticAngularEnergyGrid() const;

  //! Return the cutoff elastic scattering angles for an incoming energy
  const std::vector<double>& getCutoffElasticAngles(
					       const double incoming_energy ) const;

  //! Return the cutoff elastic scatering pdf for an incoming energy
  const std::vector<double>& getCutoffElasticPDF(
					       const double incoming_energy ) const;

  //! Return the total elastic electron cross section
  const std::vector<double>& getTotalElasticCrossSection() const;


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

  //! Return the electroionization incoming energy grid for the average scattered electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageScatteredElectronIncomingEnergy( 
                           const unsigned subshell ) const;

  //! Return the electroionization average scattered electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageScatteredElectronEnergy( 
                           const unsigned subshell ) const;

  //! Return the electroionization incoming energy grid for the average recoil electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageRecoilElectronIncomingEnergy( 
                           const unsigned subshell ) const;

  //! Return the electroionization average recoil electron energy for a subshell
  const std::vector<double>& getElectroionizationAverageRecoilElectronEnergy( 
                           const unsigned subshell ) const;

  //! Return the electroionization incoming energy grid for the recoil electron spectrum for a subshell
  const std::vector<double>& getElectroionizationRecoilEnergyGrid( 
                           const unsigned subshell ) const;

  //! Return the electroionization recoil energy for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilEnergy( 
                           const unsigned subshell,
					       const double incoming_energy ) const;

  //! Return the electroionization recoil energy pdf for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilPDF( 
                           const unsigned subshell,
					       const double incoming_energy ) const;

//---------------------------------------------------------------------------//
// GET BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//

  //! Return the bremsstrahlung electron cross section Energy Grid
  const std::vector<double>& getBremsstrahlungCrossSectionEnergyGrid() const;

  //! Return the bremsstrahlung electron cross section
  const std::vector<double>& getBremsstrahlungCrossSection() const;

  //! Return the bremsstrahlung incoming electron energy grid for the average energy of the secondary photon
  const std::vector<double>& getBremsstrahlungAveragePhotonIncomingEnergy() const;

  //! Return the bremsstrahlung average energy of the secondary photon
  const std::vector<double>& getBremsstrahlungAveragePhotonEnergy() const;

  //! Return the bremsstrahlung incoming electron energy grid for the secondary photon spectrum
  const std::vector<double>& getBremsstrahlungPhotonEnergyGrid() const;

  //! Return the bremsstrahlung photon energy for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonEnergy(
					       const double incoming_energy ) const;

  //! Return the bremsstrahlung photon energy pdf for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonPDF(
					       const double incoming_energy ) const;

  //! Return the bremsstrahlung incoming electron energy grid for the average energy of the secondary electron
  const std::vector<double>& getBremsstrahlungAverageElectronIncomingEnergy() const;

  //! Return the bremsstrahlung average energy of the secondary electron
  const std::vector<double>& getBremsstrahlungAverageElectronEnergy() const;

//---------------------------------------------------------------------------//
// GET ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//

  //! Return the atomic excitation electron energy grid
  const std::vector<double>& getAtomicExcitationEnergyGrid() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& getAtomicExcitationCrossSection() const;

  //! Return the atomic excitation average energy loss
  const std::vector<double>& getAtomicExcitationEnergyLoss() const;

protected:

  //! Default constructor
  ENDLDataContainer()
  { /* ... */ }

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//
 
  //! Set the atomic subshells
  void setSubshells( const std::set<unsigned>& subshells );

  //! Set the number of electrons in subshells
  void setSubshellNumberOfElectrons( 
    const std::map<unsigned,unsigned>& number_of_electrons );

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

  //! Set the average number of particles per initial vacancy
  void setAverageParticlesPerInitialVacancy(
    const std::map<unsigned,unsigned>& average_particle_numbers );

  //! Set the average energy of particles per initial vacancy
  void setAverageParitcleEnergyPerInitialVacancy(
    const std::map<unsigned,double>& average_particle_energies );

  //! Set the radiative transition probability
  void setRadiativeTransitionProbability( 
    const unsigned subshell,
    const std::map<unsigned,std::vector<double> >& 
        radiative_transition_probability );

  //! Set the radiative transition energy
  void setRadiativeTransitionEnergy( 
    const unsigned subshell,
    const std::map<unsigned,std::vector<double> >& 
        radiative_transition_energy );

  //! Set the non radiative transition probability
  void setNonRadiativeTransitionProbability( 
    const unsigned subshell,
    std::map<unsigned,std::map<unsigned,std::vector<double> > >&
        non_radiative_transition_probability );

  //! Set the non radiative transition energy
  void setNonRadiativeTransitionEnergy( 
    const unsigned subshell,
    std::map<unsigned,std::map<unsigned,std::vector<double> > >&
        non_radiative_transition_energy );

//---------------------------------------------------------------------------//
// SET ELASTIC DATA 
//---------------------------------------------------------------------------//

  //! Set the elastic electron energy grid
  void setElasticEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the electron elastic transport cross section
  void setElasticTransportCrossSection( 
    const std::vector<double>& elastic_transport_cross_section);

  //! Set the electron elastic cross section below mu = 0.999999
  void setCutoffElasticCrossSection( 
    const std::vector<double>& cutoff_elastic_cross_section );

  //! Set the cutoff elastic average energy to the residual atom incoming energy grid
  void setCutoffElasticResidualIncomingEnergy( 
    const std::vector<double>& residual_incoming_energy );

  //! Set the cutoff elastic average energy to the residual atom
  void setCutoffElasticResidualEnergy( 
    const std::vector<double>& residual_energy );

  //! Set the cutoff elastic average energy of the scattered electron incoming energy grid
  void setCutoffElasticScatteredElectronIncomingEnergy( 
    const std::vector<double>& scattered_electron_incoming_energy );

  //! Set the cutoff elastic average energy of the scattered electron
  void setCutoffElasticScatteredElectronEnergy(
    const std::vector<double>& scattered_electron_average_energy );

  //! Set the cutoff elastic angular energy grid
  void setCutoffElasticAngularEnergyGrid(
    const std::vector<double>& cutoff_elastic_angular_energy_grid );

  //! Set the cutoff elastic scattering angles for an incoming energy
  void setCutoffElasticAnglesAtEnergy( 
    const double incoming_energy,
    const std::vector<double>& elastic_angles );

  //! Set the cutoff elastic scattering pdf for an incoming energy
  void setCutoffElasticPDFAtEnergy( 
    const double incoming_energy,
    const std::vector<double>& elastic_pdf );

  //! Set the elastic scattering angles
  void setCutoffElasticAngles(
    const std::map<double,std::vector<double> >& elastic_angles );

  //! Set the elastic scattering pdf
  void setCutoffElasticPDF(
    const std::map<double,std::vector<double> >& elastic_pdf );

  //! Set the total elastic electron cross section
  void setTotalElasticCrossSection( 
    const std::vector<double>& total_elastic_cross_section );

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

  //! Set the electroionization incoming energy grid for the average scattered electron energy for a subshell
  void setElectroionizationAverageScatteredElectronIncomingEnergy(
    const unsigned subshell,
    const std::vector<double>& average_scattered_electron_incoming_energy );

  //! Set the electroionization average scattered electron energy for a subshell
  void setElectroionizationAverageScatteredElectronEnergy(
    const unsigned subshell,
    const std::vector<double>& average_scattered_electron_energy );

  //! Set the electroionization incoming energy grid for the average recoil electron energy for a subshell
  void setElectroionizationAverageRecoilElectronIncomingEnergy(
    const unsigned subshell,
    const std::vector<double>& average_recoil_electron_incoming_energy );

  //! Set the electroionization average recoil electron energy for a subshell
  void setElectroionizationAverageRecoilElectronEnergy(
    const unsigned subshell,
    const std::vector<double>& average_recoil_electron_energy );

  //! Set the electroionization energy grid for the recoil electron spectrum
  void setElectroionizationRecoilEnergyGrid(
    const unsigned subshell, 
    const std::vector<double>& electroionization_recoil_energy_grid );

  //! Set the electroionization recoil energy for an incoming energy and subshell
  void setElectroionizationRecoilEnergyAtIncomingEnergy( 
    const unsigned subshell, 
    const double incoming_energy,
    const std::vector<double>& electroionization_recoil_energy );

  //! Set the electroionization recoil energy pdf for an incoming energy and subshell
  void setElectroionizationRecoilPDFAtIncomingEnergy(
    const unsigned subshell,
    const double incoming_energy,
    const std::vector<double>& electroionization_recoil_pdf );

  //! Set electroionization recoil energy for all incoming energies in a subshell
  void setElectroionizationRecoilEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_energy );

  //! Set electroionization recoil energy pdf for all incoming energies in a subshell
  void setElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_pdf );

//---------------------------------------------------------------------------//
// SET BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//

  //! Set the bremsstrahlung electron cross section energy grid 
  void setBremsstrahlungCrossSectionEnergyGrid(
    const std::vector<double>& bremsstrahlung_cross_section_energy_grid );

  //! Set the bremsstrahlung electron cross section 
  void setBremsstrahlungCrossSection(
    const std::vector<double>& bremsstrahlung_cross_section );

  //! Set the bremsstrahlung incoming electron energy grid for the average energy of the secondary photon
  void setBremsstrahlungAveragePhotonIncomingEnergy(
    const std::vector<double>& bremsstrahlung_average_photon_incoming_energy );

  //! Set the bremsstrahlung average energy of the secondary photon
  void setBremsstrahlungAveragePhotonEnergy(
    const std::vector<double>& bremsstrahlung_average_photon_energy );

  //! Set the bremsstrahlung energy grid for the secondary photon spectrum
  void setBremsstrahlungPhotonEnergyGrid( 
    const std::vector<double>& bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung photon energy for an incoming energy
  void setBremsstrahlungPhotonEnergyAtIncomingEnergy(
    const double incoming_energy,
    const std::vector<double>& bremsstrahlung_photon_energy );

  //! Set the bremsstrahlung photon energy pdf for an incoming energy
  void setBremsstrahlungPhotonPDFAtIncomingEnergy(
    const double incoming_energy,
    const std::vector<double>& bremsstrahlung_photon_pdf );

  //! Set all the bremsstrahlung photon energy data
  void setBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_energy );

  //! Set all the bremsstrahlung photon energy pdf data
  void setBremsstrahlungPhotonPDF(
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_pdf );

  //! Set the bremsstrahlung incoming electron energy grid for the average energy of the secondary electron
  void setBremsstrahlungAverageElectronIncomingEnergy(
    const std::vector<double>& bremsstrahlung_average_electron_incoming_energy );

  //! Set the bremsstrahlung average energy of the secondary electron
  void setBremsstrahlungAverageElectronEnergy(
    const std::vector<double>& bremsstrahlung_average_electron_energy );

//---------------------------------------------------------------------------//
// SET ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//

  //! Set the atomic excitation electron energy grid
  void setAtomicExcitationEnergyGrid(
    const std::vector<double>& atomic_excitation_energy_grid );

  //! Set the atomic excitation electron cross section 
  void setAtomicExcitationCrossSection(
    const std::vector<double>& atomic_excitation_cross_section );

  //! Set the atomic excitation average energy loss
  void setAtomicExcitationEnergyLoss( 
            const std::vector<double>& atomic_excitation_energy_loss );

  
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

  // The atomic number
  unsigned d_atomic_number;

//---------------------------------------------------------------------------//
// RELAXATION DATA
//---------------------------------------------------------------------------//
  // The atomic subshells (ENDF designators)
  std::set<unsigned> d_subshells;

  // The number of electrons in subshells
  std::map<unsigned,unsigned> d_subshell_number_of_electrons;

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

  // The average number of particles per initial vacancy
  std::map<unsigned,unsigned> d_subshell_average_particle_numbers;

  // The average energy of particles per initial vacancy
  std::map<unsigned,double> d_subshell_average_particle_energies;

  // The radiative transition probability
  std::map<unsigned,std::map<unsigned,std::vector<double> > > 
    d_radiative_transition_probabilities;

  // The radiative transition energy
  std::map<unsigned,std::map<unsigned,std::vector<double> > >
    d_radiative_transition_energies;

  // The non radiative transition probability
  std::map<unsigned,std::map<unsigned,std::map<unsigned,std::vector<double> > > >
    d_non_radiative_transition_probabilities;

  // The non radiative transition energy
  std::map<unsigned,std::map<unsigned,std::map<unsigned,std::vector<double> > > >
    d_non_radiative_transition_energies;

//---------------------------------------------------------------------------//
// ELASTIC DATA 
//---------------------------------------------------------------------------//

  // The elastic energy grid (MeV)
  std::vector<double> d_elastic_energy_grid;

  // The elastic transport cross section (b)
  std::vector<double> d_elastic_transport_cross_section;

  // The cutoff elastic electron cross section (b)
  std::vector<double> d_cutoff_elastic_cross_section;

  // The cutoff elastic average energy to the residual atom incoming energy grid
  std::vector<double> d_cutoff_elastic_residual_incoming_energy;

  // The cutoff elastic average energy to the residual atom
  std::vector<double> d_cutoff_elastic_residual_energy;

  // The cutoff elastic average energy to the scattered electron incoming energy grid
  std::vector<double> d_cutoff_elastic_scattered_electron_incoming_energy;

  // The cutoff elastic average energy to the scattered electron
  std::vector<double> d_cutoff_elastic_scattered_electron_energy;

  // The cutoff elastic angular energy grid
  std::vector<double> d_cutoff_elastic_angular_energy_grid;

  // The cutoff elastic scattering angles
  std::map<double,std::vector<double> > d_cutoff_elastic_angles;

  // The cutoff elastic scattering pdf
  std::map<double,std::vector<double> > d_cutoff_elastic_pdf;

  // The total elastic electron cross section (b)
  std::vector<double> d_total_elastic_cross_section;

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

  // The electroionization incoming energy grid for the average scattered electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_scattered_electron_incoming_energy;

  // The electroionization average scattered electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_scattered_electron_energy;

  // The electroionization incoming energy grid for the average recoil electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_recoil_electron_incoming_energy;

  // The electroionization average recoil electron energy for a subshell
  std::map<unsigned,std::vector<double> >
    d_electroionization_average_recoil_electron_energy;

  // The electroionization recoil energy grid (MeV) for a subshell
  std::map<unsigned,std::vector<double> > d_electroionization_recoil_energy_grid;

  // The electroionization recoil energy for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > > 
    d_electroionization_recoil_energy;

  // The electroionization recoil pdf for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > > 
    d_electroionization_recoil_pdf;

//---------------------------------------------------------------------------//
// BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//

  // The bremsstrahlung electron cross section energy grid (MeV)
  std::vector<double> d_bremsstrahlung_cross_section_energy_grid;

  // The bremsstrahlung electron cross section (b)
  std::vector<double> d_bremsstrahlung_cross_section;

  // The bremsstrahlung incoming electron energy grid for the average energy of the secondary photon
  std::vector<double> d_bremsstrahlung_average_photon_incoming_energy;

  // The bremsstrahlung average energy of the secondary photon
  std::vector<double> d_bremsstrahlung_average_photon_energy;

  // The bremsstrahlung photon spectrum incoming energy grid (MeV)
  std::vector<double> d_bremsstrahlung_photon_energy_grid;

  // The bremsstrahlung photon spectrum energy
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_energy;

  // The bremsstrahlung photon spectrum pdf
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_pdf;

  // The bremsstrahlung incoming electron energy grid for the average energy of the secondary electron
  std::vector<double> d_bremsstrahlung_average_electron_incoming_energy;

  // The bremsstrahlung average energy of the secondary electron
  std::vector<double> d_bremsstrahlung_average_electron_energy;

//---------------------------------------------------------------------------//
// ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//

  // The atomic excitation electron energy grid (MeV)
  std::vector<double> d_atomic_excitation_energy_grid;

  // The atomic excitation electron cross section (b)
  std::vector<double> d_atomic_excitation_cross_section;

  // The atomic excitation energy loss
  std::vector<double> d_atomic_excitation_energy_loss;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ENDLDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ENDL_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLDataContainer.hpp
//---------------------------------------------------------------------------//
