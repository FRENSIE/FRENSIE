//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectronPhotonRelaxationDataContainer.hpp
//! \author Luke Kersting
//! \brief  The native adjoint electron-photon-relaxation data container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP
#define DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

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
class AdjointElectronPhotonRelaxationDataContainer : public Utility::StandardArchivableObject<AdjointElectronPhotonRelaxationDataContainer,false>, public Utility::StandardSerializableObject<AdjointElectronPhotonRelaxationDataContainer,false>
{

public:

  //! Constructor (from saved archive)
  AdjointElectronPhotonRelaxationDataContainer(
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type =
		  Utility::ArchivableObject::XML_ARCHIVE );

  //! Destructor
  virtual ~AdjointElectronPhotonRelaxationDataContainer()
  { /* ... */ }

//---------------------------------------------------------------------------//
// GET TABLE DATA
//---------------------------------------------------------------------------//

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the minimum photon energy
  double getMinPhotonEnergy() const;

  //! Return the maximum photon energy
  double getMaxPhotonEnergy() const;

  //! Return the minimum electron energy
  double getMinElectronEnergy() const;

  //! Return the maximum electron energy
  double getMaxElectronEnergy() const;

  //! Return the upper cutoff scattering angle cosine above which moment preserving elastic scattering is used
  double getCutoffAngleCosine() const;

  //! Return the number of discrete moment preserving angles
  unsigned getNumberOfAdjointMomentPreservingAngles() const;

  //! Return the adjoint bremsstrahlung evaluation tolerance
  double getAdjointBremsstrahlungEvaluationTolerance() const;

  //! Return the union energy grid convergence tolerance
  double getGridConvergenceTolerance() const;

  //! Return the union energy grid absolute difference tolerance
  double getGridAbsoluteDifferenceTolerance() const;

  //! Return the union energy grid distance tolerance
  double getGridDistanceTolerance() const;

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

  //! Return the atomic subshells
  const std::set<unsigned>& getSubshells() const;

  //! Return the occupancy for a subshell
  double getSubshellOccupancy( const unsigned subshell ) const;

  //! Return the binding energy for a subshell
  double getSubshellBindingEnergy( const unsigned subshell ) const;

  //! Return if there is adjoint relaxation data
  bool hasAdjointRelaxationData() const;

//---------------------------------------------------------------------------//
// GET PHOTON DATA
//---------------------------------------------------------------------------//

  //! Return if there is adjoint photon data
  bool hasAdjointPhotonData() const;

//---------------------------------------------------------------------------//
// GET ELECTRON DATA
//---------------------------------------------------------------------------//

  //! Return the elastic angular energy grid
  const std::vector<double>& getAdjointElasticAngularEnergyGrid() const;

  //! Return the map of the cutoff elastic scattering angles
  const std::map<double,std::vector<double> >& getAdjointCutoffElasticAngles() const;

  //! Return the map of the cutoff elastic scatering pdf
  const std::map<double,std::vector<double> >& getAdjointCutoffElasticPDF() const;

  //! Return the cutoff elastic scattering angles for an incoming energy
  const std::vector<double>& getAdjointCutoffElasticAngles(
					       const double incoming_adjoint_energy ) const;

  //! Return the cutoff elastic scatering pdf for an incoming energy
  const std::vector<double>& getAdjointCutoffElasticPDF(
					       const double incoming_adjoint_energy ) const;

  //! Return if there is moment preserving data
  bool hasAdjointMomentPreservingData() const;

  //! Return the moment preserving elastic discrete angles
  const std::map<double,std::vector<double> >
    getAdjointMomentPreservingElasticDiscreteAngles() const;

  //! Return the moment preserving elastic weights
  const std::map<double,std::vector<double> >
    getAdjointMomentPreservingElasticWeights() const;

  //! Return the moment preserving elastic discrete angles for an incoming energy
  const std::vector<double>& getAdjointMomentPreservingElasticDiscreteAngles(
					       const double incoming_adjoint_energy ) const;

  //! Return the moment preserving elastic weights for an incoming energy
  const std::vector<double>& getAdjointMomentPreservingElasticWeights(
					       const double incoming_adjoint_energy ) const;

  //! Return the electroionization energy grid for the recoil electron spectrum for a subshell
  const std::vector<double>& getAdjointElectroionizationEnergyGrid(
                           const unsigned subshell ) const;

  //! Return the electroionization recoil energy for a subshell and incoming energy
  const std::vector<double>& getAdjointElectroionizationRecoilEnergy(
                           const unsigned subshell,
					       const double incoming_adjoint_energy ) const;

  //! Return the electroionization recoil energy pdf for a subshell and incoming energy
  const std::vector<double>& getAdjointElectroionizationRecoilPDF(
                           const unsigned subshell,
					       const double incoming_adjoint_energy ) const;

  //! Return the bremsstrahlung energy grid for the secondary photon spectrum
  const std::vector<double>& getAdjointBremsstrahlungEnergyGrid() const;

  //! Return the bremsstrahlung photon energy for an incoming energy
  const std::vector<double>& getAdjointBremsstrahlungPhotonEnergy(
					       const double incoming_adjoint_energy ) const;

  //! Return the bremsstrahlung photon energy pdf for an incoming energy
  const std::vector<double>& getAdjointBremsstrahlungPhotonPDF(
					       const double incoming_adjoint_energy ) const;

  //! Return the atomic excitation average energy gain energy grid
  const std::vector<double>& getAdjointAtomicExcitationEnergyGrid() const;

  //! Return the atomic excitation average energy gain
  const std::vector<double>& getAdjointAtomicExcitationEnergyGain() const;

  //! Return the electron energy grid
  const std::vector<double>& getAdjointElectronEnergyGrid() const;

  //! Return the elastic electron cross section below mu = 0.999999
  const std::vector<double>& getAdjointCutoffElasticCrossSection() const;

  //! Return the cutoff elastic cross section threshold energy bin index
  unsigned getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the screened Rutherford elastic electron cross section
  const std::vector<double>& getAdjointScreenedRutherfordElasticCrossSection() const;

  //! Return the screened Rutherford elastic cross section threshold energy bin index
  unsigned getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the total elastic electron cross section
  const std::vector<double>& getAdjointTotalElasticCrossSection() const;

  //! Return the total elastic cross section threshold energy bin index
  unsigned getAdjointTotalElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the Moment Preserving (MP) elastic electron cross section
  const std::vector<double>& getAdjointMomentPreservingCrossSection() const;

  //! Return the MP elastic cross section threshold energy bin index
  unsigned getAdjointMomentPreservingCrossSectionThresholdEnergyIndex() const;

  //! Return the electroionization electron cross section for a subshell
  const std::vector<double>&
    getAdjointElectroionizationCrossSection( const unsigned subshell ) const;

  //! Return the electroionization cross section threshold energy bin index for a subshell
  unsigned getAdjointElectroionizationCrossSectionThresholdEnergyIndex(
    const unsigned subshell ) const;

  //! Return the bremsstrahlung electron cross section
  const std::vector<double>& getAdjointBremsstrahlungCrossSection() const;

  //! Return the bremsstrahlung cross section threshold energy bin index
  unsigned getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& getAdjointAtomicExcitationCrossSection() const;

  //! Return the atomic excitation cross section threshold energy bin index
  unsigned getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex() const;

protected:

  //! Default constructor
  AdjointElectronPhotonRelaxationDataContainer()
  { /* ... */ }

//---------------------------------------------------------------------------//
// SET TABLE DATA
//---------------------------------------------------------------------------//

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

  //! Set the minimum photon energy
  void setMinPhotonEnergy( const double min_photon_energy );

  //! Set the maximum photon energy
  void setMaxPhotonEnergy( const double max_photon_energy );

  //! Set the minimum electron energy
  void setMinElectronEnergy( const double min_electron_energy );

  //! Set the maximum electron energy
  void setMaxElectronEnergy( const double max_electron_energy );

  //! Set the upper cutoff scattering angle below which moment preserving elastic scattering is used
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Set the number of discrete moment preserving angles
  void setNumberOfAdjointMomentPreservingAngles(
    const unsigned number_of_adjoint_moment_preserving_angles );

  //! Set the adjoint bremsstrahlung evaluation tolerance
  void getAdjointBremsstrahlungEvaluationTolerance(
    const double adjoint_bremsstrahlung_evaluation_tolerance );

  //! Set the union energy grid convergence tolerance
  void setGridConvergenceTolerance( const double grid_convergence_tol );

  //! Set the union energy grid absolute difference tolerance
  void setGridAbsoluteDifferenceTolerance( const double grid_absolute_diff_tol );

  //! Set the union energy grid distance tolerance
  void setGridDistanceTolerance( const double grid_distance_tol );

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

//---------------------------------------------------------------------------//
// SET PHOTON DATA
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// SET ELECTRON DATA
//---------------------------------------------------------------------------//

  //! Set the elastic angular energy grid
  void setAdjointElasticAngularEnergyGrid(
    const std::vector<double>& adjoint_angular_energy_grid );

  //! Set the elastic scattering angles for an incoming energy
  void setAdjointCutoffElasticAnglesAtEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_cutoff_elastic_angles );

  //! Set the elastic scattering pdf for an incoming energy
  void setAdjointCutoffElasticPDFAtEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_cutoff_elastic_pdf );

  //! Set the elastic scattering angles
  void setAdjointCutoffElasticAngles(
    const std::map<double,std::vector<double> >& adjoint_cutoff_elastic_angles );

  //! Set the elastic scattering pdf
  void setAdjointCutoffElasticPDF(
    const std::map<double,std::vector<double> >& adjoint_cutoff_elastic_pdf );

  //! Set the moment preserving elastic discrete angles for an incoming energy
  void setAdjointMomentPreservingElasticDiscreteAngles(
	const double incoming_adjoint_energy,
	const std::vector<double>& adjoint_moment_preserving_elastic_discrete_angles );

  //! Set the moment preserving elastic weights for an incoming energy
  void setAdjointMomentPreservingElasticWeights(
	const double incoming_adjoint_energy,
	const std::vector<double>& adjoint_moment_preserving_elastic_weights );

  //! Set the electroionization energy grid for the recoil electron spectrum
  void setAdjointElectroionizationEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& adjoint_electroionization_energy_grid );

  //! Set the electroionization recoil energy for an incoming energy and subshell
  void setAdjointElectroionizationRecoilEnergyAtIncomingEnergy(
    const unsigned subshell,
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_electroionization_recoil_energy );

  //! Set the electroionization recoil energy pdf for an incoming energy and subshell
  void setAdjointElectroionizationRecoilPDFAtIncomingEnergy(
    const unsigned subshell,
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_electroionization_recoil_pdf );

  //! Set electroionization recoil energy for all incoming energies in a subshell
  void setAdjointElectroionizationRecoilEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >&
    adjoint_electroionization_recoil_energy );

  //! Set electroionization recoil energy pdf for all incoming energies in a subshell
  void setAdjointElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >&
    adjoint_electroionization_recoil_pdf );

  //! Set the bremsstrahlung energy grid for the secondary photon spectrum
  void setAdjointBremsstrahlungEnergyGrid(
    const std::vector<double>& adjoint_bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung photon energy for an incoming energy
  void setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_bremsstrahlung_photon_energy );

  //! Set the bremsstrahlung photon energy pdf for an incoming energy
  void setAdjointBremsstrahlungPhotonPDFAtIncomingEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>&  adjoint_bremsstrahlung_photon_pdf );

  //! Set all the bremsstrahlung photon energy data
  void setAdjointBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >&
    adjoint_bremsstrahlung_photon_energy );

  //! Set all the bremsstrahlung photon energy pdf data
  void setAdjointBremsstrahlungPhotonPDF(
    const std::map<double,std::vector<double> >&
    adjoint_bremsstrahlung_photon_pdf );

  //! Set the atomic excitation average energy gain energy grid
  void setAdjointAtomicExcitationEnergyGrid(
    const std::vector<double>& adjoint_atomic_excitation_energy_grid );

  //! Set the atomic excitation average energy gain
  void setAdjointAtomicExcitationEnergyGain(
    const std::vector<double>& adjoint_atomic_excitation_energy_gain );

  //! Set the electron energy grid
  void setAdjointElectronEnergyGrid(
    const std::vector<double>& adjoint_energy_grid );

  //! Set the elastic electron cross section below mu = 0.999999
  void setAdjointCutoffElasticCrossSection(
    const std::vector<double>& adjoint_cutoff_elastic_cross_section );

  //! Set the elastic cutoff cross section threshold energy bin index
  void setAdjointCutoffElasticCrossSectionThresholdEnergyIndex(
    const unsigned index );

  //! Set the screened Rutherford elastic electron cross section
  void setAdjointScreenedRutherfordElasticCrossSection(
    const std::vector<double>& adjoint_screened_rutherford_elastic_cross_section );

  //! Set the screened Rutherford elastic cross section threshold energy bin index
  void setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
    const unsigned index );

  //! Set the total elastic electron cross section
  void setAdjointTotalElasticCrossSection(
    const std::vector<double>& adjoint_total_elastic_cross_section );

  //! Set the total elastic cross section threshold energy bin index
  void setAdjointTotalElasticCrossSectionThresholdEnergyIndex(
    const unsigned index );

  //! Set the moment preserving elastic electron cross section using Moment Preserving (MP) theory
  void setAdjointMomentPreservingCrossSection(
    const std::vector<double>& adjoint_moment_preserving_elastic_cross_section );

  //! Set the MP moment preserving elastic cross section threshold energy bin index
  void setAdjointMomentPreservingCrossSectionThresholdEnergyIndex(
						        const unsigned index );

  //! Set the electroionization electron cross section for a subshell
  void setAdjointElectroionizationCrossSection( const unsigned subshell,
			 const std::vector<double>& adjoint_electroionization_cross_section );

  //! Set the electroionization cross section threshold energy bin index
  void setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
             const unsigned subshell,
             const unsigned index );

  //! Set the bremsstrahlung electron cross section
  void setAdjointBremsstrahlungCrossSection(
			 const std::vector<double>& adjoint_bremsstrahlung_cross_section );

  //! Set the bremsstrahlung cross section threshold energy bin index
  void setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(
                                const unsigned index );

  //! Set the atomic excitation electron cross section
  void setAdjointAtomicExcitationCrossSection(
			 const std::vector<double>& adjoint_atomic_excitation_cross_section );

  //! Set the bremsstrahlung cross section threshold energy bin index
  void setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(
                                const unsigned index );

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

//---------------------------------------------------------------------------//
// SET TABLE DATA
//---------------------------------------------------------------------------//

  // The atomic number
  unsigned d_atomic_number;

  // The minimum photon energy
  double d_min_photon_energy;

  // The maximum photon energy
  double d_max_photon_energy;

  // The minimum electron energy
  double d_min_electron_energy;

  // The maximum electron energy
  double d_max_electron_energy;

  // The elastic cutoff angle
  double d_cutoff_angle_cosine;

  // The number of discrete moment preserving angles
  double d_number_of_adjoint_moment_preserving_angles;

  // The union energy grid convergence tolerance
  double d_grid_convergence_tol;

  // The union energy grid absolute difference tolerance
  double d_grid_absolute_diff_tol;

  // The union energy grid distance tolerance
  double d_grid_distance_tol;

//---------------------------------------------------------------------------//
// RELAXATION DATA
//---------------------------------------------------------------------------//

  // The atomic subshells (ENDF designators)
  std::set<unsigned> d_subshells;

  // The subshell occupancies
  std::map<unsigned,double> d_subshell_occupancies;

  // The subshell binding energies
  std::map<unsigned,double> d_subshell_binding_energies;

//---------------------------------------------------------------------------//
// PHOTON DATA
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
// ELECTRON DATA
//---------------------------------------------------------------------------//

  // The elastic angular energy grid (MeV)
  std::vector<double> d_adjoint_angular_energy_grid;

  // The cutoff elastic scattering angles
  std::map<double,std::vector<double> > d_adjoint_cutoff_elastic_angles;

  // The cutoff elastic scattering pdf
  std::map<double,std::vector<double> > d_adjoint_cutoff_elastic_pdf;

  // The moment preserving elastic discrete angles
  std::map<double,std::vector<double> > d_adjoint_moment_preserving_elastic_discrete_angles;

  // The moment preserving elastic weights
  std::map<double,std::vector<double> > d_adjoint_moment_preserving_elastic_weights;

  // The electroionization energy grid (MeV) for a subshell
  std::map<unsigned,std::vector<double> > d_adjoint_electroionization_energy_grid;

  // The electroionization recoil energy for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_adjoint_electroionization_recoil_energy;

  // The electroionization recoil pdf for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_adjoint_electroionization_recoil_pdf;

  // The bremsstrahlung energy grid (MeV)
  std::vector<double> d_adjoint_bremsstrahlung_energy_grid;

  // The bremsstrahlung photon energy
  std::map<double,std::vector<double> > d_adjoint_bremsstrahlung_photon_energy;

  // The bremsstrahlung photon pdf
  std::map<double,std::vector<double> > d_adjoint_bremsstrahlung_photon_pdf;

  // The atomic excitation energy grid (MeV)
  std::vector<double> d_adjoint_atomic_excitation_energy_grid;

  // The atomic excitation energy gain
  std::vector<double> d_adjoint_atomic_excitation_energy_gain;

  // The electron energy grid (MeV)
  std::vector<double> d_adjoint_electron_energy_grid;

  // The cutoff elastic electron cross section (b)
  std::vector<double> d_adjoint_cutoff_elastic_cross_section;

  // The cutoff elastic electron cross section threshold energy index
  unsigned d_adjoint_cutoff_elastic_cross_section_threshold_index;

  // The screened rutherford elastic electron cross section (b)
  std::vector<double> d_adjoint_screened_rutherford_elastic_cross_section;

  // The screened rutherford elastic electron cross section threshold energy index
  unsigned d_adjoint_screened_rutherford_elastic_cross_section_threshold_index;

  // The total elastic electron cross section (b)
  std::vector<double> d_adjoint_total_elastic_cross_section;

  // The total elastic electron cross section threshold energy index
  unsigned d_adjoint_total_elastic_cross_section_threshold_index;

  // The Moment Preserving elastic electron cross section (b)
  std::vector<double> d_adjoint_moment_preserving_elastic_cross_section;

  // The Moment Preserving elastic electron cross section threshold energy index
  unsigned d_adjoint_moment_preserving_elastic_cross_section_threshold_index;

  // The electroionization subshell electron cross section (b)
  std::map<unsigned,std::vector<double> >
    d_adjoint_electroionization_subshell_cross_section;

  // The hard elastic electron cross section threshold energy index
  std::map<unsigned,unsigned>
    d_adjoint_electroionization_subshell_cross_section_threshold_index;

  // The bremsstrahlung electron cross section (b)
  std::vector<double> d_adjoint_bremsstrahlung_cross_section;

  // The bremsstrahlung electron cross section threshold energy index
  unsigned d_adjoint_bremsstrahlung_cross_section_threshold_index;

  // The atomic excitation electron cross section (b)
  std::vector<double> d_adjoint_atomic_excitation_cross_section;

  // The atomic excitation electron cross section threshold energy index
  unsigned d_adjoint_atomic_excitation_cross_section_threshold_index;
};

} // end Data namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationDataContainer.hpp
//---------------------------------------------------------------------------//

