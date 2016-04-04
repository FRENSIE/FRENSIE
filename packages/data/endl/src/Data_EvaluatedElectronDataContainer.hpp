//---------------------------------------------------------------------------//
//!
//! \file   Data_EvaluatedElectronDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native eedl container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_EVALUATED_ELECTRON_DATA_CONTAINER_HPP
#define DATA_EVALUATED_ELECTRON_DATA_CONTAINER_HPP

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

/*! The eedl container
 * \details Linear-linear interpolation should be used for all data.
 */
class EvaluatedElectronDataContainer : public Utility::StandardArchivableObject<EvaluatedElectronDataContainer,false>, public Utility::StandardSerializableObject<EvaluatedElectronDataContainer,false>
{

public:

  //! Constructor (from saved archive)
  EvaluatedElectronDataContainer( 
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type =
		  Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~EvaluatedElectronDataContainer()
  { /* ... */ }

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the atomic subshells 
  const std::set<unsigned>& getSubshells() const;

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//
/*

  //! Return the atomic subshells 
  const std::set<unsigned>& getSubshells() const;

  //! Return the occupancy for a subshell
  double getSubshellOccupancy( const unsigned subshell ) const;

  //! Return the binding energy for a subshell
  double getSubshellBindingEnergy( const unsigned subshell ) const;

  //! Return if there is relaxation data
  bool hasRelaxationData() const;

  //! Return if the subshell has relaxation data
  bool hasSubshellRelaxationData( const unsigned subshell ) const;

  //! Return the number of transitions that can fill a subshell vacancy
  unsigned getSubshellRelaxationTransitions( const unsigned subshell ) const;

  //! Return the relaxation vacancies for a subshell
  const std::vector<std::pair<unsigned,unsigned> >&
  getSubshellRelaxationVacancies( const unsigned subshell ) const;

  //! Return the relaxation particle energies for a subshell
  const std::vector<double>& getSubshellRelaxationParticleEnergies(
					       const unsigned subshell ) const;

  //! Return the relaxation probabilities for a subshell
  const std::vector<double>& getSubshellRelaxationProbabilities(
					       const unsigned subshell ) const;
*/

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

  //! Return the atomic excitation electron cross section energy grid
  const std::vector<double>& getAtomicExcitationCrossSectionEnergyGrid() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& getAtomicExcitationCrossSection() const;

  //! Return the atomic excitation average energy loss energy grid
  const std::vector<double>& getAtomicExcitationEnergyLossIncomingEnergy() const;

  //! Return the atomic excitation average energy loss
  const std::vector<double>& getAtomicExcitationEnergyLoss() const;

protected:

  //! Default constructor
  EvaluatedElectronDataContainer()
  { /* ... */ }

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

  //! Set the atomic subshells
  void setSubshells( const std::set<unsigned>& subshells );

/*
//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//
 
  //! Set the atomic subshells
  void setSubshells( const std::set<unsigned>& subshells );

  //! Set the occupancy for a subshell
  void setSubshellOccupancy( const unsigned subshell,
                             const double occupancy );
  
  //! Set the binding energy for a subshell
  void setSubshellBindingEnergy( const unsigned subshell,
                                 const double binding_energy );

  //! Set the number of transitions that can fill a subshell vacancy
  void setSubshellRelaxationTransitions( const unsigned subshell,
                                         const unsigned transitions );

  //! Set the relaxation vacancies for a subshell
  void setSubshellRelaxationVacancies( 
      const unsigned subshell,
      const std::vector<std::pair<unsigned,unsigned> >& relaxation_vacancies );

  //! Set the relaxation particle energies for a subshell
  void setSubshellRelaxationParticleEnergies(
		     const unsigned subshell,
		     const std::vector<double>& relaxation_particle_energies );

  //! Set the relaxation probabilities for a subshell
  void setSubshellRelaxationProbabilities( 
			 const unsigned subshell,
			 const std::vector<double>& relaxation_probabilities );
*/

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

  //! Set the atomic excitation electron cross section energy grid
  void setAtomicExcitationCrossSectionEnergyGrid(
    const std::vector<double>& atomic_excitation_cross_section_energy_grid );

  //! Set the atomic excitation electron cross section 
  void setAtomicExcitationCrossSection(
    const std::vector<double>& atomic_excitation_cross_section );

  //! Set the atomic excitation average energy loss incoming energy grid
  void setAtomicExcitationEnergyLossIncomingEnergy( 
    const std::vector<double>& atomic_excitation_energy_loss_incoming_energy );

  //! Set the atomic excitation average energy loss
  void setAtomicExcitationEnergyLoss( 
            const std::vector<double>& atomic_excitation_energy_loss );
  
private:

  // Test preconditions for cross sections
  void testPreconditionCrossSection( 
    const std::vector<double>& cross_section,
    const std::vector<double>& energy_grid );

  // Test preconditions for energy grids
  void testPreconditionEnergyGrid(
    const std::vector<double>& energy_grid );

  // Test preconditions for values in array greater than zero
  template<typename Array>
  void testPreconditionValuesGreaterThanZero( 
    const Array& values );

  // Test preconditions for values in array greater than or equal to zero
  template<typename Array>
  void testPreconditionValuesGreaterThanOrEqualToZero( 
    const Array& values );

  // Test if a value is less than or equal to zero
  static bool isValueLessThanOrEqualToZero( const double value );

  // Test if a value is less than zero
  static bool isValueLessThanZero( const double value );

  // Test if a value is greater than one
  static bool isValueGreaterThanOne( const double value );

  // Test if a value is less than minus one
  static bool isValueLessThanMinusOne( const double value );

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

  // The atomic subshells (ENDF designators)
  std::set<unsigned> d_subshells;

/*
//---------------------------------------------------------------------------//
// RELAXATION DATA
//---------------------------------------------------------------------------//
  // The atomic subshells (ENDF designators)
  std::set<unsigned> d_subshells;

  // The subshell occupancies
  std::map<unsigned,double> d_subshell_occupancies;

  // The subshell binding energies
  std::map<unsigned,double> d_subshell_binding_energies;

  // The subshell relaxation transitions
  std::map<unsigned,unsigned> d_relaxation_transitions;

  // The subshell relaxation vacancies
  std::map<unsigned,std::vector<std::pair<unsigned,unsigned> > >
  d_relaxation_vacancies;

  // The subshell relaxation particle energies
  std::map<unsigned,std::vector<double> > d_relaxation_particle_energies;

  // The subshell relaxation probabilities
  std::map<unsigned,std::vector<double> > d_relaxation_probabilities;
*/

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

  // The atomic excitation electron cross section energy grid (MeV)
  std::vector<double> d_atomic_excitation_cross_section_energy_grid;

  // The atomic excitation electron cross section (b)
  std::vector<double> d_atomic_excitation_cross_section;

  // The atomic excitation energy loss energy grid (MeV)
  std::vector<double> d_atomic_excitation_energy_loss_energy_grid;

  // The atomic excitation energy loss
  std::vector<double> d_atomic_excitation_energy_loss;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_EvaluatedElectronDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_EVALUATED_ELECTRON_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_EvaluatedElectronDataContainer.hpp
//---------------------------------------------------------------------------//
