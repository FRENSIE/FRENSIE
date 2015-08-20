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

  //! Return the elastic cutoff angle cosine
  double getCutoffAngleCosine() const;

  //! Return the elastic angular energy grid
  const std::vector<double>& getElasticAngularEnergyGrid() const;
/*
  //! Return the number of elastic angular bins for an incoming energy
  unsigned getNumberOfAngularBins( const double incoming_energy ) const;
*/
  //! Return the elastic scattering angles for an incoming energy
  const std::vector<double>& getElasticAngles(
					       const double incoming_energy ) const;

  //! Return the elastic scatering pdf for an incoming energy
  const std::vector<double>& getElasticPDF(
					       const double incoming_energy ) const;
/*
  //! Return the number of soft discrete angles for an incoming energy
  unsigned getNumberOfDiscreteAngles( const double incoming_energy ) const;
*/
  //! Return the soft elastic discrete angles for an incoming energy
  const std::vector<double>& getSoftElasticDiscreteAngles(
					       const double incoming_energy ) const;

  //! Return the soft elastic weights for an incoming energy
  const std::vector<double>& getSoftElasticWeights(
					       const double incoming_energy ) const;

  //! Return the electroionization energy grid for the recoil electron spectrum for a subshell
  const std::vector<double>& getElectroionizationEnergyGrid( 
                           const unsigned subshell ) const;

  //! Return the electroionization recoil energy for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilEnergy( 
                           const unsigned subshell,
					       const double incoming_energy ) const;

  //! Return the electroionization recoil energy pdf for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilPDF( 
                           const unsigned subshell,
					       const double incoming_energy ) const;

  //! Return the bremsstrahlung energy grid for the secondary photon spectrum
  const std::vector<double>& getBremsstrahlungEnergyGrid() const;

  //! Return the bremsstrahlung photon energy for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonEnergy(
					       const double incoming_energy ) const;

  //! Return the bremsstrahlung photon energy pdf for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonPDF(
					       const double incoming_energy ) const;

  //! Return the atomic excitation average energy loss energy grid
  const std::vector<double>& getAtomicExcitationEnergyGrid() const;

  //! Return the atomic excitation average energy loss
  const std::vector<double>& getAtomicExcitationEnergyLoss() const;

  //! Return the electron energy grid
  const std::vector<double>& getElectronEnergyGrid() const;

  //! Return the elastic electron cross section below mu = 0.999999
  const std::vector<double>& 
  getCutoffElasticCrossSection() const;

  //! Return the cutoff elastic cross section threshold energy bin index
  unsigned 
  getCutoffElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the total elastic electron cross section
  const std::vector<double>& 
  getTotalElasticCrossSection() const;

  //! Return the total elastic cross section threshold energy bin index
  unsigned 
  getTotalElasticCrossSectionThresholdEnergyIndex() const;
/*
  //! Return the hard elastic electron cross section
  const std::vector<double>& 
  getHardElasticCrossSection() const;

  //! Return the hard cross section threshold energy bin index
  unsigned getHardElasticCrossSectionThresholdEnergyIndex() const;
*/
  //! Return the Moment Preserving (MP) soft elastic electron cross section
  const std::vector<double>& getMomentPreservingCrossSection() const;

  //! Return the MP soft elastic cross section threshold energy bin index
  unsigned getMomentPreservingCrossSectionThresholdEnergyIndex() const;

  //! Return the electroionization electron cross section for a subshell
  const std::vector<double>& 
  getElectroionizationCrossSection( const unsigned subshell ) const;

  //! Return the electroionization cross section threshold energy bin index for a subshell
  unsigned getElectroionizationCrossSectionThresholdEnergyIndex( 
    const unsigned subshell ) const;

  //! Return the bremsstrahlung electron cross section
  const std::vector<double>& 
  getBremsstrahlungCrossSection() const;

  //! Return the bremsstrahlung cross section threshold energy bin index
  unsigned 
  getBremsstrahlungCrossSectionThresholdEnergyIndex() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& 
  getAtomicExcitationCrossSection() const;

  //! Return the atomic excitation cross section threshold energy bin index
  unsigned 
  getAtomicExcitationCrossSectionThresholdEnergyIndex() const;

protected:

  //! Default constructor
  EvaluatedElectronDataContainer()
  { /* ... */ }

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

  //! set the atomic subshells 
  void setSubshells( const std::set<unsigned>& subshells );

  //! Set the elastic cutoff angle cosine
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Set the elastic angular energy grid
  void setElasticAngularEnergyGrid( 
            const std::vector<double>& angular_energy_grid );
/*
  //! Set the number of elastic angles for an incoming energy
  void setNumberOfAngles( 
            const double incoming_energy, 
            const unsigned number_of_elastic_angles );
*/
  //! Set the elastic scattering angles for an incoming energy
  void setElasticAngles(
            const double incoming_energy,
            const std::vector<double>& elastic_angles );

  //! Set the elastic scattering pdf for an incoming energy
  void setElasticPDF(
            const double incoming_energy,
            const std::vector<double>& elastic_pdf );
/*
  //! Set the number of discrete angles for an incoming energy
  void setNumberOfDiscreteAngles( 
             const double incoming_energy,
             const unsigned number_of_discrete_angles );
*/
  //! Set the soft elastic discrete angles for an incoming energy
  void setSoftElasticDiscreteAngles(
		     const double incoming_energy,
		     const std::vector<double>& soft_elastic_discrete_angles );

  //! Set the soft elastic weights for an incoming energy
  void setSoftElasticWeights( 
			 const double incoming_energy,
			 const std::vector<double>& soft_elastic_weights );

  //! Set the electroionization energy grid for the recoil electron spectrum
  void setElectroionizationEnergyGrid(
            const unsigned subshell, 
            const std::vector<double>& electroionization_energy_grid );

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

  //! Set the bremsstrahlung energy grid for the secondary photon spectrum
  void setBremsstrahlungEnergyGrid( 
            const std::vector<double>& bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung photon energy for an incoming energy
  void setBremsstrahlungPhotonEnergyAtIncomingEnergy(
            const double incoming_energy,
            const std::vector<double>& bremsstrahlung_photon_energy );

  //! Set the bremsstrahlung photon energy pdf for an incoming energy
  void setBremsstrahlungPhotonPDFAtIncomingEnergy(
            const double incoming_energy,
            const std::vector<double>&  bremsstrahlung_photon_pdf );

  //! Set all the bremsstrahlung photon energy data
  void setBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_energy );

  //! Set all the bremsstrahlung photon energy pdf data
  void setBremsstrahlungPhotonPDF(
    const std::map<double,std::vector<double> >&  bremsstrahlung_photon_pdf );

  //! Set the atomic excitation average energy loss energy grid
  void setAtomicExcitationEnergyGrid( 
            const std::vector<double>& atomic_excitation_energy_grid );

  //! Set the atomic excitation average energy loss
  void setAtomicExcitationEnergyLoss( 
            const std::vector<double>& atomic_excitation_energy_loss );
  
  //! Set the electron energy grid
  void setElectronEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the elastic electron cross section below mu = 0.999999
  void setCutoffElasticCrossSection( 
    const std::vector<double>& cutoff_elastic_cross_section );

  //! Set the elastic cutoff cross section threshold energy bin index
  void setCutoffElasticCrossSectionThresholdEnergyIndex( const unsigned index );

  //! Set the total elastic electron cross section
  void setTotalElasticCrossSection( 
    const std::vector<double>& total_elastic_cross_section );

  //! Set the total elastic cross section threshold energy bin index
  void setTotalElasticCrossSectionThresholdEnergyIndex( const unsigned index );
/*
  //! Set the hard elastic electron cross section 
  void setHardElasticCrossSection(
			 const std::vector<double>& hard_elastic_cross_section );

  //! Set the hard elastic cross section threshold energy bin index
  void setHardElasticCrossSectionThresholdEnergyIndex( const unsigned index );
*/
  //! Set the soft elastic electron cross section using Moment Preserving (MP) theory
  void setMomentPreservingCrossSection(
			 const std::vector<double>& soft_elastic_cross_section );

  //! Set the MP soft elastic cross section threshold energy bin index
  void setMomentPreservingCrossSectionThresholdEnergyIndex(
						        const unsigned index );

  //! Set the electroionization electron cross section for a subshell
  void setElectroionizationCrossSection( const unsigned subshell,
			 const std::vector<double>& electroionization_cross_section );

  //! Set the electroionization cross section threshold energy bin index
  void setElectroionizationCrossSectionThresholdEnergyIndex( 
             const unsigned subshell,
             const unsigned index );

  //! Set the bremsstrahlung electron cross section 
  void setBremsstrahlungCrossSection(
			 const std::vector<double>& bremsstrahlung_cross_section );

  //! Set the bremsstrahlung cross section threshold energy bin index
  void setBremsstrahlungCrossSectionThresholdEnergyIndex( 
                                const unsigned index );

  //! Set the atomic excitation electron cross section 
  void setAtomicExcitationCrossSection(
			 const std::vector<double>& atomic_excitation_cross_section );

  //! Set the bremsstrahlung cross section threshold energy bin index
  void setAtomicExcitationCrossSectionThresholdEnergyIndex( 
                                const unsigned index );


  
private:

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

  // The elastic cutoff angle cosine
  double d_cutoff_angle_cosine;

  // The elastic angular energy grid (MeV)
  std::vector<double> d_angular_energy_grid;

  // The elastic scattering angles
  std::map<double,std::vector<double> > d_elastic_angles;

  // The elastic scattering pdf
  std::map<double,std::vector<double> > d_elastic_pdf;
/*
  // The number of elastic angles for incoming energy
  std::map<double,unsigned> d_number_of_elastic_angles;

  // The hard elastic angles
  std::map<double,std::vector<double> > d_hard_elastic_angles;

  // The hard elastic pdf
  std::map<double,std::vector<double> > d_hard_elastic_pdf;

  // The number of discrete angles for incoming energy
  std::map<double,unsigned> d_number_of_discrete_angles;
*/
  // The soft elastic discrete angles
  std::map<double,std::vector<double> > d_soft_elastic_discrete_angles;

  // The soft elastic weights
  std::map<double,std::vector<double> > d_soft_elastic_weights;

  // The electroionization energy grid (MeV) for a subshell
  std::map<unsigned,std::vector<double> > d_electroionization_energy_grid;
/*
  // The number of elastic angles for subshell and incoming energy
  std::map<unsigned,std::map<double,unsigned> > d_number_of_elastic_angles;
*/
  // The electroionization recoil energy for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > > 
    d_electroionization_recoil_energy;

  // The electroionization recoil pdf for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > > 
    d_electroionization_recoil_pdf;

  // The bremsstrahlung energy grid (MeV)
  std::vector<double> d_bremsstrahlung_energy_grid;

  // The bremsstrahlung photon energy
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_energy;

  // The bremsstrahlung photon pdf
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_pdf;

  // The atomic excitation energy grid (MeV)
  std::vector<double> d_atomic_excitation_energy_grid;

  // The atomic excitation energy loss
  std::vector<double> d_atomic_excitation_energy_loss;

  // The electron energy grid (MeV)
  std::vector<double> d_electron_energy_grid;

  // The cutoff elastic electron cross section (b)
  std::vector<double> d_cutoff_elastic_cross_section;

  // The cutoff elastic electron cross section threshold energy index
  unsigned d_cutoff_elastic_cross_section_threshold_index;

  // The total elastic electron cross section (b)
  std::vector<double> d_total_elastic_cross_section;

  // The total elastic electron cross section threshold energy index
  unsigned d_total_elastic_cross_section_threshold_index;

/*
  // The hard elastic electron cross section (b)
  std::vector<double> d_hard_elastic_cross_section;

  // The hard elastic electron cross section threshold energy index
  unsigned d_hard_elastic_cross_section_threshold_index;
*/
  // The Moment Preserving soft elastic electron cross section (b)
  std::vector<double> d_moment_preserving_soft_elastic_cross_section;

  // The Moment Preserving soft elastic electron cross section threshold energy index
  unsigned d_moment_preserving_soft_elastic_cross_section_threshold_index;

  // The electroionization subshell electron cross section (b)
  std::map<unsigned,std::vector<double> > 
    d_electroionization_subshell_cross_section;

  // The hard elastic electron cross section threshold energy index
  std::map<unsigned,unsigned>
    d_electroionization_subshell_cross_section_threshold_index;

  // The bremsstrahlung electron cross section (b)
  std::vector<double> d_bremsstrahlung_cross_section;

  // The bremsstrahlung electron cross section threshold energy index
  unsigned d_bremsstrahlung_cross_section_threshold_index;

  // The atomic excitation electron cross section (b)
  std::vector<double> d_atomic_excitation_cross_section;

  // The atomic excitation electron cross section threshold energy index
  unsigned d_atomic_excitation_cross_section_threshold_index;

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
