//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationDataContainer.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The native electron-photon-relaxation data container class decl.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <fstream>
#include <sstream>
#include <typeinfo>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_DataContainerHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Initialize static member data
const std::string ElectronPhotonRelaxationDataContainer::s_archive_name( "container" );

// Constructor (from saved archive)
ElectronPhotonRelaxationDataContainer::ElectronPhotonRelaxationDataContainer(
                           const boost::filesystem::path& file_name_with_path )
{
  // Import the data in the archive
  this->loadFromFile( file_name_with_path );
}

// Load the archived object (implementation)
void ElectronPhotonRelaxationDataContainer::loadFromFileImpl(
                        const boost::filesystem::path& archive_name_with_path )
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpis pointer must be NULL. Depending on the libraries that have been
  // loaded (e.g. utility_grid) the bpis might be initialized to a non-NULL
  // value
  const boost::archive::detail::basic_pointer_iserializer* bpis =
    this->resetBpisPointer<std::vector<double> >( extension );

  // Import the data in the archive
  BaseType::loadFromFileImpl( archive_name_with_path );

  // The bpis pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBpisPointer<std::vector<double> >( extension, bpis );
}

// Archive the object (implementation)
void ElectronPhotonRelaxationDataContainer::saveToFileImpl(
                         const boost::filesystem::path& archive_name_with_path,
                         const bool overwrite ) const
{
  std::string extension = archive_name_with_path.extension().string();

  // The bpos pointer must be NULL. Depending on the libraries that have been
  // loaded (e.g. utility_grid) the bpos might be initialized to a non-NULL
  // value
  const boost::archive::detail::basic_pointer_oserializer* bpos =
    this->resetBposPointer<std::vector<double> >( extension );

  // Import the data in the archive
  BaseType::saveToFileImpl( archive_name_with_path, overwrite );

  // The bpos pointer must be restored to its original value so that libraries
  // that expect it to be non-NULL behave correctly
  this->restoreBposPointer<std::vector<double> >( extension, bpos );
}

// The database name used in an archive
const char* ElectronPhotonRelaxationDataContainer::getArchiveName() const
{
  return s_archive_name.c_str();
}

//---------------------------------------------------------------------------//
// GET NOTES
//---------------------------------------------------------------------------//

// Data table notes
const std::string& ElectronPhotonRelaxationDataContainer::getNotes() const
{
  return d_notes;
}

//---------------------------------------------------------------------------//
// GET TABLE DATA
//---------------------------------------------------------------------------//

// Return the atomic number
unsigned ElectronPhotonRelaxationDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic weight
double ElectronPhotonRelaxationDataContainer::getAtomicWeight() const
{
  return d_atomic_weight;
}

// Return the minimum photon energy
double ElectronPhotonRelaxationDataContainer::getMinPhotonEnergy() const
{
  return d_min_photon_energy;
}

// Return the maximum photon energy
double ElectronPhotonRelaxationDataContainer::getMaxPhotonEnergy() const
{
  return d_max_photon_energy;
}

// Return the minimum electron energy
double ElectronPhotonRelaxationDataContainer::getMinElectronEnergy() const
{
  return d_min_electron_energy;
}

// Return the maximum electron energy
double ElectronPhotonRelaxationDataContainer::getMaxElectronEnergy() const
{
  return d_max_electron_energy;
}

// Return the occupation number evaluation tolerance
double
ElectronPhotonRelaxationDataContainer::getOccupationNumberEvaluationTolerance() const
{
  return d_occupation_number_evaluation_tolerance;
}

// Return the subshell incoherent evaluation tolerance
double ElectronPhotonRelaxationDataContainer::getSubshellIncoherentEvaluationTolerance() const
{
  return d_subshell_incoherent_evaluation_tolerance;
}

// Return the photon threshold energy nudge factor
double ElectronPhotonRelaxationDataContainer::getPhotonThresholdEnergyNudgeFactor() const
{
  return d_photon_threshold_energy_nudge_factor;
}

// Return the elastic cutoff angle
double ElectronPhotonRelaxationDataContainer::getCutoffAngleCosine() const
{
  return d_cutoff_angle_cosine;
}

// Return the number of discrete moment preserving angles
unsigned ElectronPhotonRelaxationDataContainer::getNumberOfMomentPreservingAngles() const
{
  return d_number_of_moment_preserving_angles;
}

// Return the electron FullyTabularTwoDDistribution evaluation tolerance
double ElectronPhotonRelaxationDataContainer::getElectronTabularEvaluationTolerance() const
{
  return d_electron_tabular_evaluation_tol;
}

// Return the photon union energy grid convergence tolerance
double ElectronPhotonRelaxationDataContainer::getPhotonGridConvergenceTolerance() const
{
  return d_photon_grid_convergence_tol;
}

// Return the photon union energy grid absolute difference tolerance
double ElectronPhotonRelaxationDataContainer::getPhotonGridAbsoluteDifferenceTolerance() const
{
  return d_photon_grid_absolute_diff_tol;
}

// Return the photon union energy grid distance tolerance
double ElectronPhotonRelaxationDataContainer::getPhotonGridDistanceTolerance() const
{
  return d_photon_grid_distance_tol;
}

// Return the electron union energy grid convergence tolerance
double ElectronPhotonRelaxationDataContainer::getElectronGridConvergenceTolerance() const
{
  return d_electron_grid_convergence_tol;
}

// Return the electron union energy grid absolute difference tolerance
double ElectronPhotonRelaxationDataContainer::getElectronGridAbsoluteDifferenceTolerance() const
{
  return d_electron_grid_absolute_diff_tol;
}

// Return the electron union energy grid distance tolerance
double ElectronPhotonRelaxationDataContainer::getElectronGridDistanceTolerance() const
{
  return d_electron_grid_distance_tol;
}

// Return the bremsstrahlung cross section evaluation tolerance
double ElectronPhotonRelaxationDataContainer::getBremsstrahlungEvaluationTolerance() const
{
  return d_bremsstrahlung_evaluation_tolerance;
}

// Return the bremsstrahlung grid convergence tolerance
double ElectronPhotonRelaxationDataContainer::getBremsstrahlungGridConvergenceTolerance() const
{
  return d_bremsstrahlung_convergence_tolerance;
}

// Return the bremsstrahlung absolute difference tolerance
double ElectronPhotonRelaxationDataContainer::getBremsstrahlungAbsoluteDifferenceTolerance() const
{
  return d_bremsstrahlung_absolute_diff_tol;
}

// Return the bremsstrahlung distance tolerance
double ElectronPhotonRelaxationDataContainer::getBremsstrahlungDistanceTolerance() const
{
  return d_bremsstrahlung_distance_tol;
}

// Return the electroionization cross section evaluation tolerance
double ElectronPhotonRelaxationDataContainer::getElectroionizationEvaluationTolerance() const
{
  return d_electroionization_evaluation_tol;
}

// Return the electroionization grid convergence tolerance
double ElectronPhotonRelaxationDataContainer::getElectroionizationGridConvergenceTolerance() const
{
  return d_electroionization_convergence_tol;
}

// Return the electroionization absolute difference tolerance
double ElectronPhotonRelaxationDataContainer::getElectroionizationAbsoluteDifferenceTolerance() const
{
  return d_electroionization_absolute_diff_tol;
}

// Return the electroionization distance tolerance
double ElectronPhotonRelaxationDataContainer::getElectroionizationDistanceTolerance() const
{
  return d_electroionization_distance_tol;
}

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

// Return the atomic subshells
const std::set<unsigned>&
ElectronPhotonRelaxationDataContainer::getSubshells() const
{
  return d_subshells;
}

// Return the subshell occupancies
double ElectronPhotonRelaxationDataContainer::getSubshellOccupancy(
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_subshell_occupancies.find( subshell )->second;
}

// Return the subshell binding energies
double ElectronPhotonRelaxationDataContainer::getSubshellBindingEnergy(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_subshell_binding_energies.find( subshell )->second;
}

// Return if there is relaxation data
bool ElectronPhotonRelaxationDataContainer::hasRelaxationData() const
{
  return d_relaxation_transitions.size() > 0;
}

// Return if the subshell has relaxation data
bool ElectronPhotonRelaxationDataContainer::hasSubshellRelaxationData(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_relaxation_transitions.find( subshell ) !=
    d_relaxation_transitions.end();
}

// Return the number of transitions that can fill a subshell vacancy
unsigned ElectronPhotonRelaxationDataContainer::getSubshellRelaxationTransitions(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_relaxation_transitions.find( subshell )->second;
}

// Return the relaxation vacancies for a subshell
const std::vector<std::pair<unsigned,unsigned> >&
ElectronPhotonRelaxationDataContainer::getSubshellRelaxationVacancies(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_relaxation_vacancies.find( subshell )->second;
}

// Return the relaxation particle energies for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getSubshellRelaxationParticleEnergies(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_relaxation_particle_energies.find( subshell )->second;
}

// Return the relaxation probabilities for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getSubshellRelaxationProbabilities(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_relaxation_probabilities.find( subshell )->second;
}

//---------------------------------------------------------------------------//
// GET PHOTON DATA
//---------------------------------------------------------------------------//

// Return the Compton profile momentum grid for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getComptonProfileMomentumGrid(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_compton_profile_momentum_grids.find( subshell )->second;
}

// Return the Compton profile for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getComptonProfile(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_compton_profiles.find( subshell )->second;
}

// Return the occupation number momentum grid for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getOccupationNumberMomentumGrid(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_occupation_number_momentum_grids.find( subshell )->second;
}

// Return the occupation number for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getOccupationNumber(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_occupation_numbers.find( subshell )->second;
}

// Return the Waller-Hartree scattering function momentum grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeScatteringFunctionMomentumGrid() const
{
  return d_waller_hartree_scattering_function_momentum_grid;
}

// Return the Waller-Hartree scattering function
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeScatteringFunction() const
{
  return d_waller_hartree_scattering_function;
}

// Return the Waller-Hartree atomic form factor momentum grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeAtomicFormFactorMomentumGrid() const
{
  return d_waller_hartree_atomic_form_factor_momentum_grid;
}

// Return the Waller-Hartree atomic form factor
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getWallerHartreeAtomicFormFactor() const
{
  return d_waller_hartree_atomic_form_factor;
}

// Return the Waller-Hartree squared atomic form factor squared mom. grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid() const
{
  return d_waller_hartree_squared_atomic_form_factor_squared_momentum_grid;
}

// Return the Waller-Hartree squared atomic form factor
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeSquaredAtomicFormFactor() const
{
  return d_waller_hartree_squared_atomic_form_factor;
}

// Return the photon energy grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getPhotonEnergyGrid() const
{
  return d_photon_energy_grid;
}

// Check if there are average heating numbers
bool ElectronPhotonRelaxationDataContainer::hasAveragePhotonHeatingNumbers() const
{
  return d_has_average_photon_heating_numbers;
}

// Return the average heating numbers
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getAveragePhotonHeatingNumbers() const
{
  return d_average_photon_heating_numbers;
}

// Return the Waller-Hartree (WH) incoherent photon cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeIncoherentCrossSection() const
{
  return d_waller_hartree_incoherent_cross_section;
}

// Return the WH incoherent photon cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex() const
{
  return d_waller_hartree_incoherent_cross_section_threshold_index;
}

// Return the impluse approx. (IA) incoherent photon cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getImpulseApproxIncoherentCrossSection() const
{
  return d_impulse_approx_incoherent_cross_section;
}

// Return the IA incoherent photon cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex() const
{
  return d_impulse_approx_incoherent_cross_section_threshold_index;
}

// Return the subshell Impulse approx. incoherent photon cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getImpulseApproxSubshellIncoherentCrossSection(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_impulse_approx_subshell_incoherent_cross_sections.find( subshell )->second;
}

// Return the subshell IA incoherent photon cs threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_impulse_approx_subshell_incoherent_cross_section_threshold_indices.find( subshell )->second;
}

// Return the Waller-Hartree coherent cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getWallerHartreeCoherentCrossSection() const
{
  return d_waller_hartree_coherent_cross_section;
}

// Return the Waller-Hartree coherent cs threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getWallerHartreeCoherentCrossSectionThresholdEnergyIndex() const
{
  return d_waller_hartree_coherent_cross_section_threshold_index;
}

// Return the pair production cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getPairProductionCrossSection() const
{
  return d_pair_production_cross_section;
}

// Return the pair production cross section threshold energy bin index
unsigned ElectronPhotonRelaxationDataContainer::getPairProductionCrossSectionThresholdEnergyIndex() const
{
  return d_pair_production_cross_section_threshold_index;
}

// Return the triplet production cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getTripletProductionCrossSection() const
{
  return d_triplet_production_cross_section;
}

// Return the triplet production cross section threshold energy bin index
unsigned ElectronPhotonRelaxationDataContainer::getTripletProductionCrossSectionThresholdEnergyIndex() const
{
  return d_triplet_production_cross_section_threshold_index;
}

// Return the Photoelectric effect cross section
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getPhotoelectricCrossSection() const
{
  return d_photoelectric_cross_section;
}

// Return the Photoelectric effect cross section threshold energy bin index
unsigned ElectronPhotonRelaxationDataContainer::getPhotoelectricCrossSectionThresholdEnergyIndex() const
{
  return d_photoelectric_cross_section_threshold_index;
}

// Return the Photoelectric effect cross section for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getSubshellPhotoelectricCrossSection(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_subshell_photoelectric_cross_sections.find( subshell )->second;
}

// Return the subshell Photoelectric effect cross section threshold index
unsigned
ElectronPhotonRelaxationDataContainer::getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_subshell_photoelectric_cross_section_threshold_indices.find( subshell )->second;
}

// Return the Waller-Hartree total cross section
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getWallerHartreeTotalCrossSection() const
{
  return d_waller_hartree_total_cross_section;
}

// Return the impulse approx. total cross section
const std::vector<double>& ElectronPhotonRelaxationDataContainer::getImpulseApproxTotalCrossSection() const
{
  return d_impulse_approx_total_cross_section;
}


//---------------------------------------------------------------------------//
// GET ELECTRON DATA
//---------------------------------------------------------------------------//

// Return the electron TwoDInterpPolicy
const std::string&
ElectronPhotonRelaxationDataContainer::getElectronTwoDInterpPolicy() const
{
  return d_electron_two_d_interp;
}

// Return the electron TwoDGridPolicy
const std::string&
ElectronPhotonRelaxationDataContainer::getElectronTwoDGridPolicy() const
{
  return d_electron_two_d_grid;
}

// Return the elastic angular energy grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElasticAngularEnergyGrid() const
{
  return d_angular_energy_grid;
}

// Return the cutoff elastic scattering interpolation policy
const std::string&
ElectronPhotonRelaxationDataContainer::getCutoffElasticInterpPolicy() const
{
  return d_cutoff_elastic_interp;
}

// Return the elastic angles map
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getCutoffElasticAngles() const
{
  return d_cutoff_elastic_angles;
}

// Return the elastic pdf map
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getCutoffElasticPDF() const
{
  return d_cutoff_elastic_pdf;
}

// Return the elastic angles for an incoming energy
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getCutoffElasticAngles(
                            const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_cutoff_elastic_angles.find( incoming_energy )->second;
}

// Return the elastic pdf for an incoming energy
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getCutoffElasticPDF(
                            const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_cutoff_elastic_pdf.find( incoming_energy )->second;
}

//// Return if there is screened Rutherford data
//bool ElectronPhotonRelaxationDataContainer::hasScreenedRutherfordData() const
//{
//  return d_screened_rutherford_normalization_constant.size() > 0;
//}

//// Return the screened Rutherford elastic normalization constant
//const std::vector<double>&
//ElectronPhotonRelaxationDataContainer::getScreenedRutherfordNormalizationConstant() const
//{
//  return d_screened_rutherford_normalization_constant;
//}

//// Return Moliere's screening constant
//const std::vector<double>&
//ElectronPhotonRelaxationDataContainer::getMoliereScreeningConstant() const
//{
//  return d_moliere_screening_constant;
//}

// Return if there is moment preserving data
bool ElectronPhotonRelaxationDataContainer::hasMomentPreservingData() const
{
  return d_moment_preserving_elastic_discrete_angles.size() > 0;
}

// Return the moment preserving elastic discrete angles
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getMomentPreservingElasticDiscreteAngles() const
{
  return d_moment_preserving_elastic_discrete_angles;
}

// Return the moment preserving elastic weights
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getMomentPreservingElasticWeights() const
{
  return d_moment_preserving_elastic_weights;
}

// Return the moment preserving elastic discrete angles for an incoming energy
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getMomentPreservingElasticDiscreteAngles(
                            const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_moment_preserving_elastic_discrete_angles.find( incoming_energy )->second;
}

// Return the moment preserving elastic weights for an incoming energy
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getMomentPreservingElasticWeights(
                            const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );

  return d_moment_preserving_elastic_weights.find( incoming_energy )->second;
}

// Return the moment preserving cross section reductions
/*! \details The cross sections reductions are on the elastic angular energy grid.
 */
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getMomentPreservingCrossSectionReduction() const
{
  return d_moment_preserving_cross_section_reductions;
}

// Return the electroionization energy grid for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElectroionizationEnergyGrid(
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_energy_grid.find( subshell )->second;
}

// Return the electroionization recoil interpolation policy
const std::string&
ElectronPhotonRelaxationDataContainer::getElectroionizationInterpPolicy() const
{
  return d_electroionization_interp;
}

// Return the electroionization recoil energy for a subshell
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getElectroionizationRecoilEnergy(
                           const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_recoil_energy.find( subshell )->second;
}

// Return the electroionization recoil energy for a subshell and energy bin
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElectroionizationRecoilEnergy(
                           const unsigned subshell,
                           const double incoming_energy ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_energy >=
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_energy <=
            d_electroionization_energy_grid.find( subshell )->second.back() );

  return d_electroionization_recoil_energy.find( subshell )->second.find( incoming_energy )->second;
}

// Return the electroionization recoil energy pdf for a subshell
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getElectroionizationRecoilPDF(
                           const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_recoil_pdf.find( subshell )->second;
}

// Return the electroionization recoil energy pdf for a subshell and energy bin
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElectroionizationRecoilPDF(
                           const unsigned subshell,
                           const double incoming_energy ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_energy >=
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_energy <=
            d_electroionization_energy_grid.find( subshell )->second.back() );

  return d_electroionization_recoil_pdf.find( subshell )->second.find( incoming_energy )->second;
}

// Return if there is electroionization outgoing energy data
bool ElectronPhotonRelaxationDataContainer::hasElectroionizationOutgoingEnergyData() const
{
  return d_electroionization_outgoing_energy.size() > 0;
}

// Return the electroionization outgoing energy for a subshell
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getElectroionizationOutgoingEnergy(
                           const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_outgoing_energy.find( subshell )->second;
}

// Return the electroionization outgoing energy for a subshell and energy bin
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElectroionizationOutgoingEnergy(
                           const unsigned subshell,
                           const double incoming_energy ) const
{
  // Make sure there is outgoing energy data
  testPrecondition( this->hasElectroionizationOutgoingEnergyData() );
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_energy >=
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_energy <=
            d_electroionization_energy_grid.find( subshell )->second.back() );

  return d_electroionization_outgoing_energy.find( subshell )->second.find( incoming_energy )->second;
}

// Return the electroionization outgoing energy pdf for a subshell
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getElectroionizationOutgoingPDF(
                           const unsigned subshell ) const
{
  // Make sure there is outgoing energy data
  testPrecondition( this->hasElectroionizationOutgoingEnergyData() );
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_electroionization_outgoing_pdf.find( subshell )->second;
}

// Return the electroionization outgoing energy pdf for a subshell and energy bin
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElectroionizationOutgoingPDF(
                           const unsigned subshell,
                           const double incoming_energy ) const
{
  // Make sure there is outgoing energy data
  testPrecondition( this->hasElectroionizationOutgoingEnergyData() );
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_energy >=
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_energy <=
            d_electroionization_energy_grid.find( subshell )->second.back() );

  return d_electroionization_outgoing_pdf.find( subshell )->second.find( incoming_energy )->second;
}

// Return the bremsstrahlung energy grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getBremsstrahlungEnergyGrid() const
{
  return d_bremsstrahlung_energy_grid;
}

// Return the bremsstrahlung photon interpolation policy
const std::string&
ElectronPhotonRelaxationDataContainer::getBremsstrahlungPhotonInterpPolicy() const
{
  return d_bremsstrahlung_photon_interp;
}

// Return the bremsstrahlung photon energy
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getBremsstrahlungPhotonEnergy() const
{
  return d_bremsstrahlung_photon_energy;
}

// Return the bremsstrahlung photon energy for an incoming energy
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getBremsstrahlungPhotonEnergy(
                            const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );

  return d_bremsstrahlung_photon_energy.find( incoming_energy )->second;
}

// Return the bremsstrahlung photon pdf
const std::map<double,std::vector<double> >&
ElectronPhotonRelaxationDataContainer::getBremsstrahlungPhotonPDF() const
{
  return d_bremsstrahlung_photon_pdf;
}

// Return the bremsstrahlung photon pdf for an incoming energy
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getBremsstrahlungPhotonPDF(
                            const double incoming_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );

  return d_bremsstrahlung_photon_pdf.find( incoming_energy )->second;
}

// Return the atomic excitation energy grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getAtomicExcitationEnergyGrid() const
{
  return d_atomic_excitation_energy_grid;
}

// Return the atomic excitation energy loss interpolation policy
const std::string&
ElectronPhotonRelaxationDataContainer::getAtomicExcitationEnergyLossInterpPolicy() const
{
  return d_atomic_excitation_energy_loss_interp;
}

// Return the atomic excitation energy loss
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getAtomicExcitationEnergyLoss() const
{
  return d_atomic_excitation_energy_loss;
}

// Return the electron energy grid
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElectronEnergyGrid() const
{
  return d_electron_energy_grid;
}

// Return the electron cross section interpolation policy
const std::string&
ElectronPhotonRelaxationDataContainer::getElectronCrossSectionInterpPolicy() const
{
  return d_electron_cross_section_interp;
}

// Return the total electron electron cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getTotalElectronCrossSection() const
{
  return d_total_electron_cross_section;
}

// Return the cutoff elastic electron cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getCutoffElasticCrossSection() const
{
  return d_cutoff_elastic_cross_section;
}

// Return the cutoff elastic cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getCutoffElasticCrossSectionThresholdEnergyIndex() const
{
  return d_cutoff_elastic_cross_section_threshold_index;
}
// Return the screened Rutherford elastic electron cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getScreenedRutherfordElasticCrossSection() const
{
  return d_screened_rutherford_elastic_cross_section;
}

// Return the screened Rutherford elastic cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() const
{
  return d_screened_rutherford_elastic_cross_section_threshold_index;
}

// Return the total elastic electron cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getTotalElasticCrossSection() const
{
  return d_total_elastic_cross_section;
}

// Return the total elastic cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getTotalElasticCrossSectionThresholdEnergyIndex() const
{
  return d_total_elastic_cross_section_threshold_index;
}

// Return the electroionization electron cross section for a subshell
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getElectroionizationCrossSection(
    const unsigned subshell ) const
{
  return d_electroionization_subshell_cross_section.find( subshell )->second;
}

// Return the electroionization cross section threshold energy bin index for a subshell
unsigned
ElectronPhotonRelaxationDataContainer::getElectroionizationCrossSectionThresholdEnergyIndex(
    const unsigned subshell ) const
{
  return d_electroionization_subshell_cross_section_threshold_index.find( subshell )->second;
}

// Return the bremsstrahlung electron cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getBremsstrahlungCrossSection() const
{
  return d_bremsstrahlung_cross_section;
}

// Return the bremsstrahlung cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getBremsstrahlungCrossSectionThresholdEnergyIndex() const
{
  return d_bremsstrahlung_cross_section_threshold_index;
}

// Return the atomic excitation electron cross section
const std::vector<double>&
ElectronPhotonRelaxationDataContainer::getAtomicExcitationCrossSection() const
{
  return d_atomic_excitation_cross_section;
}

// Return the atomic excitation cross section threshold energy bin index
unsigned
ElectronPhotonRelaxationDataContainer::getAtomicExcitationCrossSectionThresholdEnergyIndex() const
{
  return d_atomic_excitation_cross_section_threshold_index;
}

//---------------------------------------------------------------------------//
// SET NOTES
//---------------------------------------------------------------------------//

// Data table notes
void ElectronPhotonRelaxationDataContainer::setNotes( const std::string& notes )
{
  d_notes = notes;
}

//---------------------------------------------------------------------------//
// SET TABLE DATA
//---------------------------------------------------------------------------//

// Set the atomic number
void ElectronPhotonRelaxationDataContainer::setAtomicNumber(
                         const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}

// Set the atomic weight
void ElectronPhotonRelaxationDataContainer::setAtomicWeight(
                                                   const double atomic_weight )
{
  // Make sure that the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );

  d_atomic_weight = atomic_weight;
}

// Set the minimum photon energy
void ElectronPhotonRelaxationDataContainer::setMinPhotonEnergy(
    const double min_photon_energy )
{
  // Make sure the energy is valid
  testPrecondition( min_photon_energy >= 0.0 );

  d_min_photon_energy = min_photon_energy;
}

// Set the maximum photon energy
void ElectronPhotonRelaxationDataContainer::setMaxPhotonEnergy(
    const double max_photon_energy )
{
  // Make sure the energy is valid
  testPrecondition( max_photon_energy >= 0.0 );

  d_max_photon_energy = max_photon_energy;
}

// Set the minimum electron energy
void ElectronPhotonRelaxationDataContainer::setMinElectronEnergy(
    const double min_electron_energy )
{
  // Make sure the energy is valid
  testPrecondition( min_electron_energy >= 0.0 );

  d_min_electron_energy = min_electron_energy;
}

// Set the maximum electron energy
void ElectronPhotonRelaxationDataContainer::setMaxElectronEnergy(
    const double max_electron_energy )
{
  // Make sure the energy is valid
  testPrecondition( max_electron_energy >= 0.0 );

  d_max_electron_energy = max_electron_energy;
}

// Set the occupation number evaluation tolerance
void ElectronPhotonRelaxationDataContainer::setOccupationNumberEvaluationTolerance(
    const double occupation_number_evaluation_tolerance )
{
  // Make sure the tolerance is valid
  testPrecondition( occupation_number_evaluation_tolerance >= 0.0 );

  d_occupation_number_evaluation_tolerance =
    occupation_number_evaluation_tolerance;
}

// Set the subshell incoherent evaluation tolerance
void ElectronPhotonRelaxationDataContainer::setSubshellIncoherentEvaluationTolerance(
    const double subshell_incoherent_evaluation_tolerance )
{
  // Make sure the tolerance is valid
  testPrecondition( subshell_incoherent_evaluation_tolerance >= 0.0 );

  d_subshell_incoherent_evaluation_tolerance =
    subshell_incoherent_evaluation_tolerance;
}

// Set the photon threshold energy nudge factor
void ElectronPhotonRelaxationDataContainer::setPhotonThresholdEnergyNudgeFactor(
                                                    const double nudge_factor )
{
  // Make sure the nudge factor is valid
  testPrecondition( nudge_factor >= 1.0 );

  d_photon_threshold_energy_nudge_factor = nudge_factor;
}

// Set the elastic cutoff angle
void ElectronPhotonRelaxationDataContainer::setCutoffAngleCosine(
                         const double cutoff_angle_cosine )
{
  // Make sure the elastic cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine >= -1.0 );

  d_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Set the number of discrete moment preserving angles
void ElectronPhotonRelaxationDataContainer::setNumberOfMomentPreservingAngles(
    const unsigned number_of_moment_preserving_angles )
{
  // Make sure the number of angles is valid
  testPrecondition( number_of_moment_preserving_angles >= 0 );

  d_number_of_moment_preserving_angles = number_of_moment_preserving_angles;
}

// Set the electron FullyTabularTwoDDistribution evaluation tolerance
void ElectronPhotonRelaxationDataContainer::setElectronTabularEvaluationTolerance(
    const double electron_tabular_evaluation_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( electron_tabular_evaluation_tol < 1.0 );
  testPrecondition( electron_tabular_evaluation_tol > 0.0 );

  d_electron_tabular_evaluation_tol = electron_tabular_evaluation_tol;
}

// Set the photon union energy grid convergence tolerance
void ElectronPhotonRelaxationDataContainer::setPhotonGridConvergenceTolerance(
    const double grid_convergence_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_convergence_tol >= 0.0 );

  d_photon_grid_convergence_tol = grid_convergence_tol;
}

// Set the photon union energy grid absolute difference tolerance
void ElectronPhotonRelaxationDataContainer::setPhotonGridAbsoluteDifferenceTolerance(
    const double grid_absolute_diff_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_absolute_diff_tol >= 0.0 );

  d_photon_grid_absolute_diff_tol = grid_absolute_diff_tol;
}

// Set the photon union energy grid distance tolerance
void ElectronPhotonRelaxationDataContainer::setPhotonGridDistanceTolerance(
    const double grid_distance_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_distance_tol >= 0.0 );

  d_photon_grid_distance_tol = grid_distance_tol;
}

// Set the electron union energy grid convergence tolerance
void ElectronPhotonRelaxationDataContainer::setElectronGridConvergenceTolerance(
    const double grid_convergence_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_convergence_tol >= 0.0 );

  d_electron_grid_convergence_tol = grid_convergence_tol;
}

// Set the electron union energy grid absolute difference tolerance
void ElectronPhotonRelaxationDataContainer::setElectronGridAbsoluteDifferenceTolerance(
    const double grid_absolute_diff_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_absolute_diff_tol >= 0.0 );

  d_electron_grid_absolute_diff_tol = grid_absolute_diff_tol;
}

// Set the electron union energy grid distance tolerance
void ElectronPhotonRelaxationDataContainer::setElectronGridDistanceTolerance(
    const double grid_distance_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_distance_tol >= 0.0 );

  d_electron_grid_distance_tol = grid_distance_tol;
}

// Set the bremsstrahlung cross section evaluation tolerance
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungEvaluationTolerance(
    const double evaluation_tolerance )
{
  // Make sure the evaluation_tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );

  d_bremsstrahlung_evaluation_tolerance = evaluation_tolerance;
}

// Set the bremsstrahlung grid convergence tolerance
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungGridConvergenceTolerance(
    const double convergence_tolerance )
{
  // Make sure the convergence_tolerance is valid
  testPrecondition( convergence_tolerance > 0.0 );

  d_bremsstrahlung_convergence_tolerance = convergence_tolerance;
}

// Set the bremsstrahlung absolute difference tolerance
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungAbsoluteDifferenceTolerance(
    const double absolute_diff_tol )
{
  // Make sure the absolute_diff_tol is valid
  testPrecondition( absolute_diff_tol > 0.0 );

  d_bremsstrahlung_absolute_diff_tol = absolute_diff_tol;
}

// Set the bremsstrahlung distance tolerance
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungDistanceTolerance(
    const double distance_tol )
{
  // Make sure the distance_tol is valid
  testPrecondition( distance_tol > 0.0 );

  d_bremsstrahlung_distance_tol = distance_tol;
}

// Set the electroionization cross section evaluation tolerance
void ElectronPhotonRelaxationDataContainer::setElectroionizationEvaluationTolerance(
    const double evaluation_tol )
{
  // Make sure the evaluation_tol is valid
  testPrecondition( evaluation_tol > 0.0 );

  d_electroionization_evaluation_tol = evaluation_tol;
}

// Set the electroionization grid convergence tolerance
void ElectronPhotonRelaxationDataContainer::setElectroionizationGridConvergenceTolerance(
    const double convergence_tol )
{
  // Make sure the convergence_tol is valid
  testPrecondition( convergence_tol > 0.0 );

  d_electroionization_convergence_tol = convergence_tol;
}

// Set the electroionization absolute difference tolerance
void ElectronPhotonRelaxationDataContainer::setElectroionizationAbsoluteDifferenceTolerance(
    const double absolute_diff_tol )
{
  // Make sure the absolute_diff_tol is valid
  testPrecondition( absolute_diff_tol > 0.0 );

  d_electroionization_absolute_diff_tol = absolute_diff_tol;
}

// Set the electroionization distance tolerance
void ElectronPhotonRelaxationDataContainer::setElectroionizationDistanceTolerance(
    const double distance_tol )
{
  // Make sure the distance_tol is valid
  testPrecondition( distance_tol > 0.0 );

  d_electroionization_distance_tol = distance_tol;
}

//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//


// Set the atomic subshells
void ElectronPhotonRelaxationDataContainer::setSubshells(
                       const std::set<unsigned>& subshells )
{
  // Make sure the subshells are valid
  testPrecondition( subshells.size() > 0 );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( subshells ) );

  d_subshells = subshells;
}

// Set the subshell occupancy
void ElectronPhotonRelaxationDataContainer::setSubshellOccupancy(
                               const unsigned subshell,
                               const double occupancy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the subshell occupancy is valid
  testPrecondition( occupancy > 0.0 );

  d_subshell_occupancies[subshell] = occupancy;
}

// Set the subshell binding energy
void ElectronPhotonRelaxationDataContainer::setSubshellBindingEnergy(
                          const unsigned subshell,
                          const double binding_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the subshell binding energy is valid
  testPrecondition( binding_energy > 0.0 );

  d_subshell_binding_energies[subshell] = binding_energy;
}

// Set the number of transitions that can fill a subshell vacancy
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationTransitions(
                           const unsigned subshell,
                           const unsigned transitions )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_relaxation_transitions[subshell] = transitions;
}

// Set the relaxation vacancies for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationVacancies(
       const unsigned subshell,
       const std::vector<std::pair<unsigned,unsigned> >& relaxation_vacancies )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the relaxation vacancies are valid
  testPrecondition( relaxation_vacancies.size() ==
                    d_relaxation_transitions.find( subshell )->second );

  d_relaxation_vacancies[subshell] = relaxation_vacancies;
}

// Set the relaxation particle energies for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationParticleEnergies(
              const unsigned subshell,
              const std::vector<double>& relaxation_particle_energies )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the relaxation particle energies are valid
  testPrecondition( relaxation_particle_energies.size() ==
                    d_relaxation_transitions.find( subshell )->second );

  d_relaxation_particle_energies[subshell] = relaxation_particle_energies;
}

// Set the relaxation probabilities for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellRelaxationProbabilities(
                          const unsigned subshell,
                          const std::vector<double>& relaxation_probabilities )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the relaxation cdf is valid
  testPrecondition( relaxation_probabilities.size() ==
                    d_relaxation_transitions.find( subshell )->second );
  testPrecondition( Data::valuesGreaterThanZero( relaxation_probabilities ) );

  d_relaxation_probabilities[subshell] = relaxation_probabilities;
}

//---------------------------------------------------------------------------//
// SET PHOTON DATA
//---------------------------------------------------------------------------//

// Set the Compton profile momentum grid for a subshell
void ElectronPhotonRelaxationDataContainer::setComptonProfileMomentumGrid(
                     const unsigned subshell,
                     const std::vector<double>& compton_profile_momentum_grid )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the momentum grid is valid
  testPrecondition( compton_profile_momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending(
                                       compton_profile_momentum_grid.begin(),
                                       compton_profile_momentum_grid.end() ) );
  testPrecondition( compton_profile_momentum_grid.front() == -1.0 );

  d_compton_profile_momentum_grids[subshell] = compton_profile_momentum_grid;
}

// Set the Compton profile for a subshell
void ElectronPhotonRelaxationDataContainer::setComptonProfile(
                                   const unsigned subshell,
                                   const std::vector<double>& compton_profile )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the compton_profile is valid
  testPrecondition( compton_profile.size() ==
                    d_compton_profile_momentum_grids.find( subshell )->second.size() );
  testPrecondition( Data::valuesGreaterThanZero( compton_profile ) );

  d_compton_profiles[subshell] = compton_profile;
}

// Set the occupation number momentum grid for a subshell
void ElectronPhotonRelaxationDataContainer::setOccupationNumberMomentumGrid(
                    const unsigned subshell,
                    const std::vector<double>& occupation_number_momentum_grid )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the occupation number momentum grid is valid
  testPrecondition( occupation_number_momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending(
                                        occupation_number_momentum_grid.begin(),
                                        occupation_number_momentum_grid.end()));
  testPrecondition( occupation_number_momentum_grid.front() == -1.0 );

  d_occupation_number_momentum_grids[subshell] = occupation_number_momentum_grid;
}

// Set the occupation number for a subshell
void ElectronPhotonRelaxationDataContainer::setOccupationNumber(
                                  const unsigned subshell,
                                  const std::vector<double>& occupation_number )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the occupation number is valid
  testPrecondition( occupation_number.size() ==
                    d_occupation_number_momentum_grids.find( subshell )->second.size() );
  testPrecondition( occupation_number.front() == 0.0 );
  testPrecondition( occupation_number.back() <= 1.0 );

  d_occupation_numbers[subshell] = occupation_number;
}

// Set the Waller-Hartree scattering function momentum grid
void ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunctionMomentumGrid(
                                     const std::vector<double>& momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( momentum_grid.begin(),
                                                      momentum_grid.end() ) );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( momentum_grid ) );

  d_waller_hartree_scattering_function_momentum_grid = momentum_grid;
}

// Set the Waller-Hartree scattering function
void ElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunction(
                               const std::vector<double>& scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( scattering_function.size() ==
                    d_waller_hartree_scattering_function_momentum_grid.size());
  testPrecondition( scattering_function.front() >= 0.0 );
  testPrecondition( scattering_function.back() == d_atomic_number );

  d_waller_hartree_scattering_function = scattering_function;
}

// Set the Waller-Hartree atomic form factor momentum grid
void ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactorMomentumGrid(
                                     const std::vector<double>& momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( momentum_grid.begin(),
                                                      momentum_grid.end() ) );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( momentum_grid ) );

  d_waller_hartree_atomic_form_factor_momentum_grid = momentum_grid;
}

// Set the Waller-Hartree atomic form factor
void ElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactor(
                                const std::vector<double>& atomic_form_factor )
{
  // Make sure the atomic form factor is valid
  testPrecondition( atomic_form_factor.size() ==
                    d_waller_hartree_atomic_form_factor_momentum_grid.size() );
  testPrecondition( Utility::Sort::isSortedDescending(
                                                  atomic_form_factor.begin(),
                                                  atomic_form_factor.end() ) );
  testPrecondition( atomic_form_factor.front() == d_atomic_number );
  testPrecondition( atomic_form_factor.back() >= 0.0 );

  d_waller_hartree_atomic_form_factor = atomic_form_factor;
}

// Return the Waller-Hartree squared atomic form factor squared mom. grid
void ElectronPhotonRelaxationDataContainer::setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
                             const std::vector<double>& squared_momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( squared_momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending(
                                               squared_momentum_grid.begin(),
                                               squared_momentum_grid.end() ) );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( squared_momentum_grid ) );

  d_waller_hartree_squared_atomic_form_factor_squared_momentum_grid =
    squared_momentum_grid;
}

// Return the Waller-Hartree squared atomic form factor
void ElectronPhotonRelaxationDataContainer::setWallerHartreeSquaredAtomicFormFactor(
                        const std::vector<double>& squared_atomic_form_factor )
{
  // Make sure the atomic form factor is valid
  testPrecondition(
     squared_atomic_form_factor.size() ==
     d_waller_hartree_squared_atomic_form_factor_squared_momentum_grid.size() );
  testPrecondition( Utility::Sort::isSortedDescending(
                                          squared_atomic_form_factor.begin(),
                                          squared_atomic_form_factor.end() ) );
  testPrecondition( squared_atomic_form_factor.front() ==
                    d_atomic_number*d_atomic_number );
  testPrecondition( squared_atomic_form_factor.back() >= 0.0 );

  d_waller_hartree_squared_atomic_form_factor = squared_atomic_form_factor;
}

// Set the photon energy grid
void ElectronPhotonRelaxationDataContainer::setPhotonEnergyGrid(
                                       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_photon_energy_grid = energy_grid;
}

// Set that the container has average photon heating numbers
void ElectronPhotonRelaxationDataContainer::setHasAveragePhotonHeatingNumbers(
                                               const bool has_heating_numbers )
{
  d_has_average_photon_heating_numbers = has_heating_numbers;
}

// Set the average photon heating numbers
void ElectronPhotonRelaxationDataContainer::setAveragePhotonHeatingNumbers(
                                   const std::vector<double>& heating_numbers )
{
  // Make sure the heating numbers are valid
  testPrecondition( heating_numbers.size() == d_photon_energy_grid.size() );

  d_average_photon_heating_numbers = heating_numbers;
}

// Set the incoherent photon cross section using Waller-Hartree (WH) theory
void ElectronPhotonRelaxationDataContainer::setWallerHartreeIncoherentCrossSection(
                          const std::vector<double>& incoherent_cross_section )
{
  // Make sure the incoherent cross section is valid
  testPrecondition( incoherent_cross_section.size() <=
                    d_photon_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( incoherent_cross_section ) );

  d_waller_hartree_incoherent_cross_section = incoherent_cross_section;
}

// Set the WH incoherent cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(
                                                         const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_waller_hartree_incoherent_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_waller_hartree_incoherent_cross_section_threshold_index = index;
}

// Set the incoherent photon cross section using the impulse approx. (IA)
void ElectronPhotonRelaxationDataContainer::setImpulseApproxIncoherentCrossSection(
                          const std::vector<double>& incoherent_cross_section )
{
  // Make sure the incoherent cross section is valid
  testPrecondition( incoherent_cross_section.size() <=
                    d_photon_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( incoherent_cross_section ) );

  d_impulse_approx_incoherent_cross_section = incoherent_cross_section;
}

// Set the IA incoherent photon cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
                                                         const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_impulse_approx_incoherent_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_impulse_approx_incoherent_cross_section_threshold_index = index;
}

// Set the IA subshell incoherent photon cross section
void ElectronPhotonRelaxationDataContainer::setImpulseApproxSubshellIncoherentCrossSection(
                          const unsigned subshell,
                          const std::vector<double>& incoherent_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoherent cross section is valid
  testPrecondition( incoherent_cross_section.size() <=
                    d_photon_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( incoherent_cross_section ) );

  d_impulse_approx_subshell_incoherent_cross_sections[subshell] =
    incoherent_cross_section;
}

// Set the IA subshell incoherent photon cs threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
                                                       const unsigned subshell,
                                                       const unsigned index )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the threshold index is valid
  testPrecondition( d_impulse_approx_subshell_incoherent_cross_sections.find( subshell ) !=
                    d_impulse_approx_subshell_incoherent_cross_sections.end());
  remember( const std::vector<double>& incoherent_cross_section =
            d_impulse_approx_subshell_incoherent_cross_sections.find( subshell )->second );
  testPrecondition( incoherent_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_impulse_approx_subshell_incoherent_cross_section_threshold_indices[subshell] =
    index;
}

// Set the WH coherent cross section
void ElectronPhotonRelaxationDataContainer::setWallerHartreeCoherentCrossSection(
                            const std::vector<double>& coherent_cross_section )
{
  // Make sure the coherent cross section is valid
  testPrecondition( coherent_cross_section.size() <=
                    d_photon_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( coherent_cross_section ) );

  d_waller_hartree_coherent_cross_section = coherent_cross_section;
}

// Set the WH coherent cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setWallerHartreeCoherentCrossSectionThresholdEnergyIndex(
                                                         const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_waller_hartree_coherent_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_waller_hartree_coherent_cross_section_threshold_index = index;
}

// Set the pair production cross section
void ElectronPhotonRelaxationDataContainer::setPairProductionCrossSection(
                     const std::vector<double>& pair_production_cross_section )
{
  // Make sure the pair production cross section is valid
  testPrecondition( pair_production_cross_section.size() <=
                    d_photon_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( pair_production_cross_section ) );

  d_pair_production_cross_section = pair_production_cross_section;
}

// Set the pair production cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setPairProductionCrossSectionThresholdEnergyIndex(
                                                         const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_pair_production_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_pair_production_cross_section_threshold_index = index;
}

// Set the triplet production cross section
void ElectronPhotonRelaxationDataContainer::setTripletProductionCrossSection(
                  const std::vector<double>& triplet_production_cross_section )
{
  // Make sure the triplet production cross section is valid
  testPrecondition( triplet_production_cross_section.size() <=
                    d_photon_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( triplet_production_cross_section ) );

  d_triplet_production_cross_section = triplet_production_cross_section;
}

// Set the triplet production cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setTripletProductionCrossSectionThresholdEnergyIndex(
                                                         const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_triplet_production_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_triplet_production_cross_section_threshold_index = index;
}

// Set the Photoelectric effect cross section
void ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSection(
                       const std::vector<double>& photoelectric_cross_section )
{
  // Make sure the photoelectric cross section is valid
  testPrecondition( photoelectric_cross_section.size() <=
                    d_photon_energy_grid.size() );

  d_photoelectric_cross_section = photoelectric_cross_section;
}

// Set the Photoelectric effect cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setPhotoelectricCrossSectionThresholdEnergyIndex(
                                                         const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( d_photoelectric_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_photoelectric_cross_section_threshold_index = index;
}

// Set the Photoelectric effect cross section for a subshell
void ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSection(
                       const unsigned subshell,
                       const std::vector<double>& photoelectric_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the photoelectric cross section is valid
  testPrecondition( photoelectric_cross_section.size() <=
                    d_photon_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( photoelectric_cross_section ) );

  d_subshell_photoelectric_cross_sections[subshell] =
    photoelectric_cross_section;
}

// Set the subshell Photoelectric effect cross section threshold index
void ElectronPhotonRelaxationDataContainer::setSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
                                                       const unsigned subshell,
                                                       const unsigned index )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the index is valid
  testPrecondition( d_subshell_photoelectric_cross_sections.find( subshell ) !=
                    d_subshell_photoelectric_cross_sections.end() );
  remember( const std::vector<double> photoelectric_cross_section =
            d_subshell_photoelectric_cross_sections.find( subshell )->second );
  testPrecondition( photoelectric_cross_section.size() + index ==
                    d_photon_energy_grid.size() );

  d_subshell_photoelectric_cross_section_threshold_indices[subshell] = index;
}

// Set the Waller-Hartree total cross section
void ElectronPhotonRelaxationDataContainer::setWallerHartreeTotalCrossSection(
                               const std::vector<double>& total_cross_section )
{
  // Make sure the total cross section is valid
  testPrecondition( total_cross_section.size() == d_photon_energy_grid.size());
  testPrecondition( Data::valuesGreaterThanZero( total_cross_section ) );

  d_waller_hartree_total_cross_section = total_cross_section;
}

// Set the impulse approx. total cross section
void ElectronPhotonRelaxationDataContainer::setImpulseApproxTotalCrossSection(
                               const std::vector<double>& total_cross_section )
{
  // Make sure the total cross section is valid
  testPrecondition( total_cross_section.size() == d_photon_energy_grid.size());
  testPrecondition( Data::valuesGreaterThanZero( total_cross_section ) );

  d_impulse_approx_total_cross_section = total_cross_section;
}


//---------------------------------------------------------------------------//
// SET ELECTRON DATA
//---------------------------------------------------------------------------//

// Set the electron TwoDInterpPolicy
void ElectronPhotonRelaxationDataContainer::setElectronTwoDInterpPolicy(
    const std::string& electron_two_d_interp )
{
  // Make sure the string is valid
  testPrecondition( isTwoDInterpPolicyValid( electron_two_d_interp ) );

  d_electron_two_d_interp = electron_two_d_interp;
}

// Set the electron TwoDGridPolicy
void ElectronPhotonRelaxationDataContainer::setElectronTwoDGridPolicy(
    const std::string& electron_two_d_grid )
{
  // Make sure the string is valid
  testPrecondition( isTwoDGridPolicyValid( electron_two_d_grid ) );

  d_electron_two_d_grid = electron_two_d_grid;
}

// Set the elastic angular energy grid
void ElectronPhotonRelaxationDataContainer::setElasticAngularEnergyGrid(
                       const std::vector<double>& angular_energy_grid )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::valuesGreaterThanZero( angular_energy_grid ) );

  d_angular_energy_grid = angular_energy_grid;
}

// Set the cutoff elastic scattering InterpPolicy
void ElectronPhotonRelaxationDataContainer::setCutoffElasticInterpPolicy(
    const std::string& cutoff_elastic_interp )
{
  // Make sure the string is valid
  testPrecondition( isInterpPolicyValid( cutoff_elastic_interp ) );

  d_cutoff_elastic_interp = cutoff_elastic_interp;
}

// Set the total elastic angles for an incoming energy
void ElectronPhotonRelaxationDataContainer::setCutoffElasticAnglesAtEnergy(
    const double incoming_energy,
    const std::vector<double>& cutoff_elastic_angles )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the elastic angles are valid
  testPrecondition( std::find_if( cutoff_elastic_angles.begin(),
                                  cutoff_elastic_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    cutoff_elastic_angles.end() );
  testPrecondition( std::find_if( cutoff_elastic_angles.begin(),
                                  cutoff_elastic_angles.end(),
                                  isValueGreaterThanOne ) ==
                    cutoff_elastic_angles.end() );

  d_cutoff_elastic_angles[incoming_energy] = cutoff_elastic_angles;
}

// Set the total elastic pdf for an incoming energy
void ElectronPhotonRelaxationDataContainer::setCutoffElasticPDFAtEnergy(
    const double incoming_energy,
    const std::vector<double>& cutoff_elastic_pdf )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the weight is valid
  testPrecondition( Data::valuesGreaterThanZero( cutoff_elastic_pdf ) );

  d_cutoff_elastic_pdf[incoming_energy] = cutoff_elastic_pdf;
}
// Set the total elastic angles
void ElectronPhotonRelaxationDataContainer::setCutoffElasticAngles(
    const std::map<double,std::vector<double> >& cutoff_elastic_angles )
{
  d_cutoff_elastic_angles = cutoff_elastic_angles;
}

// Set the total elastic pdf
void ElectronPhotonRelaxationDataContainer::setCutoffElasticPDF(
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf )
{
  d_cutoff_elastic_pdf = cutoff_elastic_pdf;
}

// Clear all the moment preserving data
void ElectronPhotonRelaxationDataContainer::clearMomentPreservingData()
{
  d_moment_preserving_elastic_discrete_angles.clear();
  d_moment_preserving_elastic_weights.clear();
  d_moment_preserving_cross_section_reductions.clear();
}

// Set the moment preserving elastic discrete angles
void ElectronPhotonRelaxationDataContainer::setMomentPreservingElasticDiscreteAngles(
  const std::map<double,std::vector<double> >& moment_preserving_elastic_discrete_angles)
{
  // Make sure the moment preserving elastic discrete angles are valid
  testPrecondition( moment_preserving_elastic_discrete_angles.size() ==
                    this->getElasticAngularEnergyGrid().size() );

  d_moment_preserving_elastic_discrete_angles = moment_preserving_elastic_discrete_angles;
}

// Set the moment preserving elastic weights
void ElectronPhotonRelaxationDataContainer::setMomentPreservingElasticWeights(
  const std::map<double,std::vector<double> >& moment_preserving_elastic_weights )
{
  // Make sure the moment preserving elastic weights are valid
  testPrecondition( moment_preserving_elastic_weights.size() ==
                    this->getElasticAngularEnergyGrid().size() );

  d_moment_preserving_elastic_weights = moment_preserving_elastic_weights;
}

// Set the moment preserving elastic discrete angles for an incoming energy
void ElectronPhotonRelaxationDataContainer::setMomentPreservingElasticDiscreteAngles(
            const double incoming_energy,
            const std::vector<double>& moment_preserving_elastic_discrete_angles )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the moment preserving elastic discrete angles are valid
  /* testPrecondition( moment_preserving_elastic_discrete_angles.size() ==
               d_number_of_discrete_angles.find( incoming_energy )->second );*/
  testPrecondition( std::find_if( moment_preserving_elastic_discrete_angles.begin(),
                                  moment_preserving_elastic_discrete_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    moment_preserving_elastic_discrete_angles.end() );
  testPrecondition( std::find_if( moment_preserving_elastic_discrete_angles.begin(),
                                  moment_preserving_elastic_discrete_angles.end(),
                                  isValueGreaterThanOne ) ==
                    moment_preserving_elastic_discrete_angles.end() );

  d_moment_preserving_elastic_discrete_angles[incoming_energy] =
        moment_preserving_elastic_discrete_angles;
}

// Set the moment preserving elastic weights for an incoming energy
void ElectronPhotonRelaxationDataContainer::setMomentPreservingElasticWeights(
            const double incoming_energy,
            const std::vector<double>& moment_preserving_elastic_weights )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_angular_energy_grid.front() );
  testPrecondition( incoming_energy <= d_angular_energy_grid.back() );
  // Make sure the weight is valid
  /*testPrecondition( moment_preserving_elastic_weights.size() ==
               d_number_of_discrete_angles.find( incoming_energy )->second );*/
  testPrecondition( Data::valuesGreaterThanZero( moment_preserving_elastic_weights ) );
  testPrecondition( std::find_if( moment_preserving_elastic_weights.begin(),
                                  moment_preserving_elastic_weights.end(),
                                  isValueGreaterThanOne ) ==
                    moment_preserving_elastic_weights.end() );

  d_moment_preserving_elastic_weights[incoming_energy] = moment_preserving_elastic_weights;
}

// Set the moment preserving cross section reduction
/*! \details The size of the cross sections reductions equal to the size of the
 *  elastic angular energy grid.
 */
void ElectronPhotonRelaxationDataContainer::setMomentPreservingCrossSectionReduction(
    const std::vector<double>& cross_section_reduction )
{
  // Make sure the cross_section_reduction is valid
  testPrecondition( cross_section_reduction.size() ==
                    d_angular_energy_grid.size() );

  d_moment_preserving_cross_section_reductions = cross_section_reduction;
}

// Set the electroionization energy grid for a subshell
void ElectronPhotonRelaxationDataContainer::setElectroionizationEnergyGrid(
            const unsigned subshell,
            const std::vector<double>& electroionization_energy_grid )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  testPrecondition( Data::energyGridValid( electroionization_energy_grid ) );

  d_electroionization_energy_grid[subshell]=electroionization_energy_grid;
}

// Set the electroionization InterpPolicy
void ElectronPhotonRelaxationDataContainer::setElectroionizationInterpPolicy(
    const std::string& electroionization_interp )
{
  // Make sure the string is valid
  testPrecondition( isInterpPolicyValid( electroionization_interp ) );

  d_electroionization_interp = electroionization_interp;
}

// Set the electroionization recoil energy for a subshell and energy bin
void ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilEnergyAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_energy,
            const std::vector<double>& electroionization_recoil_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_electroionization_energy_grid[subshell].front() );
  testPrecondition( incoming_energy <= d_electroionization_energy_grid[subshell].back() );
  // Make sure the electroionization recoil energy is valid
  testPrecondition( Data::valuesGreaterThanZero( electroionization_recoil_energy ) );

  d_electroionization_recoil_energy[subshell][ incoming_energy] =
    electroionization_recoil_energy;
}

// Set the electroionization recoil energy pdf for a subshell and energy bin
void ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilPDFAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_energy,
            const std::vector<double>& electroionization_recoil_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_electroionization_energy_grid[subshell].front() );
  testPrecondition( incoming_energy <= d_electroionization_energy_grid[subshell].back() );
  // Make sure the electroionization recoil pdf is valid
  testPrecondition( Data::valuesGreaterThanZero( electroionization_recoil_pdf ) );

  d_electroionization_recoil_pdf[subshell][ incoming_energy] =
    electroionization_recoil_pdf;
}

// Set electroionization recoil energy for all incoming energies in a subshell
void ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_electroionization_recoil_energy[subshell] =
    electroionization_recoil_energy;
}

// Set electroionization recoil energy pdf for all incoming energies in a subshell
void ElectronPhotonRelaxationDataContainer::setElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_recoil_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_electroionization_recoil_pdf[subshell] =
    electroionization_recoil_pdf;
}

// Set the electroionization outgoing energy for a subshell and energy bin
void ElectronPhotonRelaxationDataContainer::setElectroionizationOutgoingEnergyAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_energy,
            const std::vector<double>& electroionization_outgoing_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_energy >=
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_energy <=
            d_electroionization_energy_grid.find( subshell )->second.back() );

  // Make sure the electroionization outgoing energy is valid
  testPrecondition( Data::valuesGreaterThanZero( electroionization_outgoing_energy ) );

  d_electroionization_outgoing_energy[subshell][ incoming_energy] =
    electroionization_outgoing_energy;
}

// Set the electroionization outgoing energy pdf for a subshell and energy bin
void ElectronPhotonRelaxationDataContainer::setElectroionizationOutgoingPDFAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_energy,
            const std::vector<double>& electroionization_outgoing_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_energy >=
            d_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_energy <=
            d_electroionization_energy_grid.find( subshell )->second.back() );
  // Make sure the electroionization recoil pdf is valid
  testPrecondition( Data::valuesGreaterThanZero( electroionization_outgoing_pdf ) );

  d_electroionization_outgoing_pdf[subshell][ incoming_energy] =
    electroionization_outgoing_pdf;
}

// Set electroionization outgoing energy for all incoming energies in a subshell
void ElectronPhotonRelaxationDataContainer::setElectroionizationOutgoingEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_outgoing_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_electroionization_outgoing_energy[subshell] =
    electroionization_outgoing_energy;
}

// Set electroionization outgoing energy pdf for all incoming energies in a subshell
void ElectronPhotonRelaxationDataContainer::setElectroionizationOutgoingPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_outgoing_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_electroionization_outgoing_pdf[subshell] =
    electroionization_outgoing_pdf;
}

// Set the bremsstrahlung energy grid
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungEnergyGrid(
                       const std::vector<double>& bremsstrahlung_energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( bremsstrahlung_energy_grid ) );

  d_bremsstrahlung_energy_grid = bremsstrahlung_energy_grid;
}

// Set the bremsstrahlung photon InterpPolicy
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonInterpPolicy(
    const std::string& bremsstrahlung_photon_interp )
{
  // Make sure the string is valid
  testPrecondition( isInterpPolicyValid( bremsstrahlung_photon_interp ) );

  d_bremsstrahlung_photon_interp = bremsstrahlung_photon_interp;
}

// Set the bremsstrahlung photon energy for an incoming energy
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonEnergyAtIncomingEnergy(
             const double incoming_energy,
             const std::vector<double>&  bremsstrahlung_photon_energy )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );
  // Make sure the bremsstrahlung photon energies are valid
  testPrecondition( Data::valuesGreaterThanZero( bremsstrahlung_photon_energy ) );

  d_bremsstrahlung_photon_energy[incoming_energy] =
    bremsstrahlung_photon_energy;
}

// Set the bremsstrahlung photon pdf for an incoming energy
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonPDFAtIncomingEnergy(
             const double incoming_energy,
             const std::vector<double>& bremsstrahlung_photon_pdf )
{
  // Make sure the incoming_energy is valid
  testPrecondition( incoming_energy >= d_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_energy <= d_bremsstrahlung_energy_grid.back() );
  // Make sure the pdf is valid
  testPrecondition( Data::valuesGreaterThanZero( bremsstrahlung_photon_pdf ) );

  d_bremsstrahlung_photon_pdf[incoming_energy] = bremsstrahlung_photon_pdf;
}

// Set all the bremsstrahlung photon energy
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >&  bremsstrahlung_photon_energy )
{
  d_bremsstrahlung_photon_energy = bremsstrahlung_photon_energy;
}

// Set all the bremsstrahlung photon pdf
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungPhotonPDF(
    const std::map<double,std::vector<double> >& bremsstrahlung_photon_pdf )
{
  d_bremsstrahlung_photon_pdf = bremsstrahlung_photon_pdf;
}

// Set the atomic excitation energy grid
void ElectronPhotonRelaxationDataContainer::setAtomicExcitationEnergyGrid(
                       const std::vector<double>& atomic_excitation_energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( atomic_excitation_energy_grid ) );

  d_atomic_excitation_energy_grid = atomic_excitation_energy_grid;
}

// Set the atomic excitation energy loss InterpPolicy
void ElectronPhotonRelaxationDataContainer::setAtomicExcitationEnergyLossInterpPolicy(
    const std::string& atomic_excitation_energy_loss_interp )
{
  // Make sure the string is valid
  testPrecondition( isInterpPolicyValid( atomic_excitation_energy_loss_interp ) );

  d_atomic_excitation_energy_loss_interp = atomic_excitation_energy_loss_interp;
}

// Set the atomic excitation energy loss for an incoming energy
void ElectronPhotonRelaxationDataContainer::setAtomicExcitationEnergyLoss(
             const std::vector<double>&  atomic_excitation_energy_loss )
{
  // Make sure the atomic excitation energy loss are valid
  testPrecondition( Data::valuesGreaterThanZero( atomic_excitation_energy_loss ) );

  d_atomic_excitation_energy_loss = atomic_excitation_energy_loss;
}

// Set the electron energy grid
void ElectronPhotonRelaxationDataContainer::setElectronEnergyGrid(
                       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( Data::energyGridValid( energy_grid ) );

  d_electron_energy_grid = energy_grid;
}

// Set the electron cross section interpolation policy
void ElectronPhotonRelaxationDataContainer::setElectronCrossSectionInterpPolicy(
    const std::string& electron_cross_section_interp )
{
  // Make sure the atomic excitation energy loss are valid
  testPrecondition( isInterpPolicyValid( electron_cross_section_interp ) );

  d_electron_cross_section_interp = electron_cross_section_interp;
}

// Set the total electron electron cross section
void ElectronPhotonRelaxationDataContainer::setTotalElectronCrossSection(
             const std::vector<double>& total_electron_cross_section )
{
  // Make sure the total electron cross section is valid
  testPrecondition( total_electron_cross_section.size() ==
                    d_electron_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( total_electron_cross_section ) );

  d_total_electron_cross_section = total_electron_cross_section;
}

// Set the cutoff elastic electron cross section
void ElectronPhotonRelaxationDataContainer::setCutoffElasticCrossSection(
             const std::vector<double>& cutoff_elastic_cross_section )
{
  // Make sure the cutoff elastic cross section is valid
  testPrecondition( cutoff_elastic_cross_section.size() <=
                    d_electron_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( cutoff_elastic_cross_section ) );

  d_cutoff_elastic_cross_section = cutoff_elastic_cross_section;
}

// Set the cutoff elastic cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setCutoffElasticCrossSectionThresholdEnergyIndex(
                                const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_cutoff_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );

 d_cutoff_elastic_cross_section_threshold_index = index;
}

// Set the screened rutherford elastic electron cross section
void ElectronPhotonRelaxationDataContainer::setScreenedRutherfordElasticCrossSection(
             const std::vector<double>& screened_rutherford_elastic_cross_section )
{
  // Make sure the screened rutherford elastic cross section is valid
  testPrecondition( screened_rutherford_elastic_cross_section.size() <=
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( screened_rutherford_elastic_cross_section.begin(),
                                  screened_rutherford_elastic_cross_section.end(),
                                  isValueLessThanZero ) ==
                    screened_rutherford_elastic_cross_section.end() );

  d_screened_rutherford_elastic_cross_section = screened_rutherford_elastic_cross_section;
}

// Set the screened rutherford elastic cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
                                const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_screened_rutherford_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );

 d_screened_rutherford_elastic_cross_section_threshold_index = index;
}

// Set the total elastic electron cross section
void ElectronPhotonRelaxationDataContainer::setTotalElasticCrossSection(
             const std::vector<double>& total_elastic_cross_section )
{
  // Make sure the total elastic cross section is valid
  testPrecondition( total_elastic_cross_section.size() <=
                    d_electron_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( total_elastic_cross_section ) );

  d_total_elastic_cross_section = total_elastic_cross_section;
}

// Set the total elastic cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setTotalElasticCrossSectionThresholdEnergyIndex(
                                const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_total_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );

 d_total_elastic_cross_section_threshold_index = index;
}

// Set the electroionization electron cross section
void ElectronPhotonRelaxationDataContainer::setElectroionizationCrossSection(
            const unsigned subshell,
            const std::vector<double>& electroionization_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the electroionization cross section is valid
  testPrecondition( electroionization_cross_section.size() <=
                    d_electron_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero(electroionization_cross_section) );

  d_electroionization_subshell_cross_section[subshell] =
    electroionization_cross_section;
}

// Set the electroionization cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setElectroionizationCrossSectionThresholdEnergyIndex(
            const unsigned subshell,
            const unsigned index )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the threshold index is valid
  testPrecondition(
        d_electroionization_subshell_cross_section[subshell].size() + index ==
        d_electron_energy_grid.size() );

 d_electroionization_subshell_cross_section_threshold_index[subshell] = index;
}

// Set the bremsstrahlung electron cross section
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungCrossSection(
             const std::vector<double>& bremsstrahlung_cross_section )
{
  // Make sure the bremsstrahlung cross section is valid
  testPrecondition( bremsstrahlung_cross_section.size() <=
                    d_electron_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanZero( bremsstrahlung_cross_section ) );

  d_bremsstrahlung_cross_section = bremsstrahlung_cross_section;
}

// Set the bremsstrahlung cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setBremsstrahlungCrossSectionThresholdEnergyIndex(
                                const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_bremsstrahlung_cross_section.size() + index ==
        d_electron_energy_grid.size() );

 d_bremsstrahlung_cross_section_threshold_index = index;
}

// Set the atomic excitation electron cross section
void ElectronPhotonRelaxationDataContainer::setAtomicExcitationCrossSection(
             const std::vector<double>& atomic_excitation_cross_section )
{
  // Make sure the atomic excitation cross section is valid
  testPrecondition( atomic_excitation_cross_section.size() <=
                    d_electron_energy_grid.size() );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( atomic_excitation_cross_section ) );

  d_atomic_excitation_cross_section = atomic_excitation_cross_section;
}

// Set the atomic excitation cross section threshold energy bin index
void ElectronPhotonRelaxationDataContainer::setAtomicExcitationCrossSectionThresholdEnergyIndex(
                                const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_atomic_excitation_cross_section.size() + index ==
        d_electron_energy_grid.size() );

 d_atomic_excitation_cross_section_threshold_index = index;
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ElectronPhotonRelaxationDataContainer );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ElectronPhotonRelaxationDataContainer, Data );

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationDataContainer.cpp
//---------------------------------------------------------------------------//
