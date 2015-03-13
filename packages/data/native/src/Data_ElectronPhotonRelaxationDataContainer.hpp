//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationDataContainer.hpp
//! \author Alex Robinson
//! \brief  The native electron-photon-relaxation data container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

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

/*! The electron-photon-relaxation data container
 * \details Linear-linear interpolation should be used for all data.
 */
class ElectronPhotonRelaxationDataContainer : public Utility::StandardArchivableObject<ElectronPhotonRelaxationDataContainer,false>, public Utility::StandardSerializableObject<ElectronPhotonRelaxationDataContainer,false>
{

public:

  //! Constructor (from saved archive)
  ElectronPhotonRelaxationDataContainer( 
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type =
		  Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~ElectronPhotonRelaxationDataContainer()
  { /* ... */ }

  //! Return the atomic number
  unsigned getAtomicNumber() const;

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

  //! Return the Compton profile momentum grid 
  const std::vector<double>& getComptonProfileMomentumGrid(
					       const unsigned subshell ) const;

  //! Return the Compton profile for a subshell
  const std::vector<double>& getComptonProfile(const unsigned subshell ) const;

  //! Return the occupation number momentum grid 
  const std::vector<double>& getOccupationNumberMomentumGrid(
					       const unsigned subshell ) const;
  
  //! Return the occupation number for a subshell
  const std::vector<double>& getOccupationNumber(
					       const unsigned subshell ) const;

  //! Return the Waller-Hartree scattering function momentum grid
  const std::vector<double>& 
  getWallerHartreeScatteringFunctionMomentumGrid() const;

  //! Return the Waller-Hartree scattering function
  const std::vector<double>& getWallerHartreeScatteringFunction() const;
  
  //! Return the Waller-Hartree atomic form factor momentum grid
  const std::vector<double>&
  getWallerHartreeAtomicFormFactorMomentumGrid() const;

  //! Return the Waller-Hartree atomic form factor
  const std::vector<double>& getWallerHartreeAtomicFormFactor() const;

  //! Return the photon energy grid
  const std::vector<double>& getPhotonEnergyGrid() const;

  //! Return the average heating numbers
  const std::vector<double>& getAveragePhotonHeatingNumbers() const;

  //! Return the Waller-Hartree (WH) incoherent photon cross section 
  const std::vector<double>& 
  getWallerHartreeIncoherentCrossSection() const;

  //! Return the WH incoherent photon cross section threshold energy bin index
  unsigned
  getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the impluse approx. (IA) incoherent photon cross section
  const std::vector<double>&
  getImpulseApproxIncoherentCrossSection() const;

  //! Return the IA incoherent photon cross section threshold energy bin index
  unsigned
  getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the subshell Impulse approx. incoherent photon cross section
  const std::vector<double>&
  getImpulseApproxSubshellIncoherentCrossSection( 
					       const unsigned subshell ) const;

  //! Return the subshell IA incoherent photon cs threshold energy bin index
  unsigned
  getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 
					       const unsigned subshell ) const;

  //! Return the Waller-Hartree coherent cross section
  const std::vector<double>&
  getWallerHartreeCoherentCrossSection() const;

  //! Return the Waller-Hartree coherent cs threshold energy bin index
  unsigned
  getWallerHartreeCoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the pair production cross section
  const std::vector<double>&
  getPairProductionCrossSection() const;

  //! Return the pair production cross section threshold energy bin index
  unsigned getPairProductionCrossSectionThresholdEnergyIndex() const;

  //! Return the Photoelectric effect cross section
  const std::vector<double>& getPhotoelectricCrossSection() const;

  //! Return the Photoelectric effect cross section theshold energy bin index
  unsigned getPhotoelectricCrossSectionThresholdEnergyIndex() const;

  //! Return the Photoelectric effect cross section for a subshell
  const std::vector<double>&
  getSubshellPhotoelectricCrossSection( const unsigned subshell ) const;

  //! Return the subshell Photoelectric effect cross section threshold index
  unsigned
  getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 
					       const unsigned subshell ) const;

  //! Return the Waller-Hartree total cross section
  const std::vector<double>& getWallerHartreeTotalCrossSection() const;

  //! Return the impulse approx. total cross section
  const std::vector<double>& getImpulseApproxTotalCrossSection() const;

protected:

  //! Default constructor
  ElectronPhotonRelaxationDataContainer()
  { /* ... */ }

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );
  
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
  
  //! Set the Compton profile momentum grid 
  void setComptonProfileMomentumGrid(
		    const unsigned subshell,
		    const std::vector<double>& compton_profile_momentum_grid );
  
  //! Set the Compton profile for a subshell
  void setComptonProfile( const unsigned subshell,
			  const std::vector<double>& compton_profile );
  
  //! Set the occupation number momentum grid 
  void setOccupationNumberMomentumGrid( 
		   const unsigned subshell,
		   const std::vector<double>& occupation_number_momentum_grid );
  
  //! Set the occupation number for a subshell
  void setOccupationNumber( const unsigned subshell,
			   const std::vector<double>& occupation_number );

  //! Set the Waller-Hartree scattering function momentum grid
  void setWallerHartreeScatteringFunctionMomentumGrid(
				    const std::vector<double>& momentum_grid );
  
  //! Set the Waller-Hartree scattering function 
  void setWallerHartreeScatteringFunction(
			      const std::vector<double>& scattering_function );

  //! Set the Waller-Hartree atomic form factor momentum grid
  void setWallerHartreeAtomicFormFactorMomentumGrid(
				    const std::vector<double>& momentum_grid );
  
  //! Set the Waller-Hartree atomic form factor 
  void setWallerHartreeAtomicFormFactor(
			       const std::vector<double>& atomic_form_factor );
  
  //! Set the photon energy grid
  void setPhotonEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the average photon heating numbers
  void setAveragePhotonHeatingNumbers( 
				  const std::vector<double>& heating_numbers );
  
  //! Set the incoherent photon cross section using Waller-Hartree (WH) theory
  void setWallerHartreeIncoherentCrossSection(
			 const std::vector<double>& incoherent_cross_section );

  //! Set the WH incoherent cross section threshold energy bin index
  void setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(
						        const unsigned index );
  
  //! Set the incoherent photon cross section using the impulse approx. (IA)
  void setImpulseApproxIncoherentCrossSection(
			 const std::vector<double>& incoherent_cross_section );

  //! Set the IA incoherent photon cross section threshold energy bin index
  void setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
							const unsigned index );

  //! Set the IA subshell incoherent photon cross section
  void setImpulseApproxSubshellIncoherentCrossSection(
			 const unsigned subshell,
			 const std::vector<double>& incoherent_cross_section );

  //! Set the IA subshell incoherent photon cs threshold energy bin index
  void setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
						       const unsigned subshell,
						       const unsigned index );
  
  //! Set the WH coherent cross section 
  void setWallerHartreeCoherentCrossSection(
			   const std::vector<double>& coherent_cross_section );

  //! Set the WH coherent cross section threshold energy bin index
  void setWallerHartreeCoherentCrossSectionThresholdEnergyIndex(
							const unsigned index );
  
  //! Set the pair production cross section
  void setPairProductionCrossSection(
		    const std::vector<double>& pair_production_cross_section );

  //! Set the pair production cross section threshold energy bin index
  void setPairProductionCrossSectionThresholdEnergyIndex( 
							const unsigned index );

  //! Set the Photoelectric effect cross section
  void setPhotoelectricCrossSection(
		      const std::vector<double>& photoelectric_cross_section );

  //! Set the Photoelectric effect cross section threshold energy bin index
  void setPhotoelectricCrossSectionThresholdEnergyIndex(const unsigned index );
  
  //! Set the Photoelectric effect cross section for a subshell
  void setSubshellPhotoelectricCrossSection( 
		      const unsigned subshell,
		      const std::vector<double>& photoelectric_cross_section );
  
  //! Set the subshell Photoelectric effect cross section threshold index
  void setSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
						       const unsigned subshell,
						       const unsigned index );

  //! Set the Waller-Hartree total cross section
  void setWallerHartreeTotalCrossSection( 
			      const std::vector<double>& total_cross_section );

  //! Set the impulse approx. total cross section
  void setImpulseApproxTotalCrossSection(
			      const std::vector<double>& total_cross_section );
  
private:

  // Test if a value is less than or equal to zero
  static bool isValueLessThanOrEqualToZero( const double value );

  // Test if a value is less than zero
  static bool isValueLessThanZero( const double value );

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

  // The Compton profile momentum grids (me*c units)
  std::map<unsigned,std::vector<double> > d_compton_profile_momentum_grids;

  // The subshell Compton profiles ((me*c)^-1 units)
  std::map<unsigned,std::vector<double> > d_compton_profiles;

  // The occupation number momentum grids
  std::map<unsigned,std::vector<double> > d_occupation_number_momentum_grids;

  // The subshell occupation numbers
  std::map<unsigned,std::vector<double> > d_occupation_numbers;

  // The Waller-Hartree scattering function momentum grid (1/cm)
  std::vector<double> d_waller_hartree_scattering_function_momentum_grid;

  // The Waller-Hartree scattering function
  std::vector<double> d_waller_hartree_scattering_function;

  // The Waller-Hartree atomic form factor momentum grid (1/cm)
  std::vector<double> d_waller_hartree_atomic_form_factor_momentum_grid;

  // The Waller-Hartree atomic form factor
  std::vector<double> d_waller_hartree_atomic_form_factor;

  // The photon energy grid (MeV)
  std::vector<double> d_photon_energy_grid;
  
  // The average heating numbers
  std::vector<double> d_average_photon_heating_numbers;

  // The Waller-Hartree incoherent photon cross section (b)
  std::vector<double> d_waller_hartree_incoherent_cross_section;

  // The Waller-Hartree incoherent photon cross section threshold energy index
  unsigned d_waller_hartree_incoherent_cross_section_threshold_index;

  // The impulse approx. incoherent photon cross section (b)
  std::vector<double> d_impulse_approx_incoherent_cross_section;

  // The impulse approx. incoherent photon cross section threshold energy index
  unsigned d_impulse_approx_incoherent_cross_section_threshold_index;

  // The impulse approx. subshell incoherent photon cross sections (b)
  std::map<unsigned,std::vector<double> > 
  d_impulse_approx_subshell_incoherent_cross_sections;

  // The impulse approx. subshell incoherent photon cross section thes. indices
  std::map<unsigned,unsigned> 
  d_impulse_approx_subshell_incoherent_cross_section_theshold_indices;

  // The Waller-Hartree coherent cross section (b)
  std::vector<double> d_waller_hartree_coherent_cross_section;

  // The Waller-Hartree coherent cross section threshold energy index
  unsigned d_waller_hartree_coherent_cross_section_threshold_index;

  // The pair production cross section (b)
  std::vector<double> d_pair_production_cross_section;
  
  // The pair production cross section threshold energy index
  unsigned d_pair_production_cross_section_threshold_index;

  // The photoelectric effect cross section (b)
  std::vector<double> d_photoelectric_cross_section;

  // The photoelectric effect cross section energy index
  unsigned d_photoelectric_cross_section_threshold_index;

  // The subshell photoelectric effect cross sections (b)
  std::map<unsigned,std::vector<double> > 
  d_subshell_photoelectric_cross_sections;

  // The subshell photoelectric effect cross section threshold indices
  std::map<unsigned,unsigned> 
  d_subshell_photoelectric_cross_section_threshold_indices;

  // The Waller-Hartree total cross section (b)
  std::vector<double> d_waller_hartree_total_cross_section;

  // The impulse approx. total cross section (b)
  std::vector<double> d_impulse_approx_total_cross_section;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ElectronPhotonRelaxationDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationDataContainer.hpp
//---------------------------------------------------------------------------//

