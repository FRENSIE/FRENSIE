//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectronPhotonRelaxationDataContainer.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The native electron-photon-relaxation data container class decl.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <fstream>
#include <sstream>
#include <typeinfo>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_DataContainerHelpers.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor (from saved archive)
AdjointElectronPhotonRelaxationDataContainer::AdjointElectronPhotonRelaxationDataContainer(
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
{
  // Import the data in the archive - no way to use initializer list :(
  this->importData( archive_name, archive_type );
}

//---------------------------------------------------------------------------//
// Get Notes
//---------------------------------------------------------------------------//

// Data table notes
const std::string& AdjointElectronPhotonRelaxationDataContainer::getNotes() const
{
  return d_notes;
}
  
//---------------------------------------------------------------------------//
// GET TABLE DATA
//---------------------------------------------------------------------------//

// Return the atomic number
unsigned AdjointElectronPhotonRelaxationDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the minimum photon energy
double AdjointElectronPhotonRelaxationDataContainer::getMinPhotonEnergy() const
{
  return d_min_photon_energy;
}

// Return the maximum photon energy
double AdjointElectronPhotonRelaxationDataContainer::getMaxPhotonEnergy() const
{
  return d_max_photon_energy;
}

// Return the minimum electron energy
double AdjointElectronPhotonRelaxationDataContainer::getMinElectronEnergy() const
{
  return d_min_electron_energy;
}

// Return the maximum electron energy
double AdjointElectronPhotonRelaxationDataContainer::getMaxElectronEnergy() const
{
  return d_max_electron_energy;
}

// Return the adjoint pair production energy dist norm constant evaluation tol
double AdjointElectronPhotonRelaxationDataContainer::getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance() const
{
  return d_adjoint_pair_production_energy_dist_norm_constant_evaluation_tol;
}

// Return the adjoint triplet production energy dist norm const evaluation tol
double AdjointElectronPhotonRelaxationDataContainer::getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance() const
{
  return d_adjoint_triplet_production_energy_dist_norm_constant_evaluation_tol;
}

// Return the adjoint incoherent max energy nudge value
double AdjointElectronPhotonRelaxationDataContainer::getAdjointIncoherentMaxEnergyNudgeValue() const
{
  return d_adjoint_incoherent_max_energy_nudge_value;
}

// Return the adjoint incoherent energy to max energy nudge value
double AdjointElectronPhotonRelaxationDataContainer::getAdjointIncoherentEnergyToMaxEnergyNudgeValue() const
{
  return d_adjoint_incoherent_energy_to_max_energy_nudge_value;
}

// Return the adjoint incoherent cross section evaluation tolerance
double AdjointElectronPhotonRelaxationDataContainer::getAdjointIncoherentEvaluationTolerance() const
{
  return d_adjoint_incoherent_evaluation_tol;
}

// Return the adjoint incoherent grid convergence tolerance
double AdjointElectronPhotonRelaxationDataContainer::getAdjointIncoherentGridConvergenceTolerance() const
{
  return d_adjoint_incoherent_grid_convergence_tol;
}

// Return the adjoint incoherent grid absolute difference tolerance
double AdjointElectronPhotonRelaxationDataContainer::getAdjointIncoherentGridAbsoluteDifferenceTolerance() const
{
  return d_adjoint_incoherent_grid_absolute_diff_tol;
}

// Return the adjoint incoherent grid distance tolerance
double AdjointElectronPhotonRelaxationDataContainer::getAdjointIncoherentGridDistanceTolerance() const
{
  return d_adjoint_incoherent_grid_distance_tol;
}

// Return the elastic cutoff angle
double AdjointElectronPhotonRelaxationDataContainer::getCutoffAngleCosine() const
{
  return d_cutoff_angle_cosine;
}

// Return the number of discrete moment preserving angles
unsigned AdjointElectronPhotonRelaxationDataContainer::getNumberOfAdjointMomentPreservingAngles() const
{
  return d_number_of_adjoint_moment_preserving_angles;
}

// Return the union energy grid convergence tolerance
double
AdjointElectronPhotonRelaxationDataContainer::getGridConvergenceTolerance() const
{
  return d_grid_convergence_tol;
}

// Return the union energy grid absolute difference tolerance
double
AdjointElectronPhotonRelaxationDataContainer::getGridAbsoluteDifferenceTolerance() const
{
  return d_grid_absolute_diff_tol;
}

// Return the union energy grid distance tolerance
double AdjointElectronPhotonRelaxationDataContainer::getGridDistanceTolerance() const
{
  return d_grid_distance_tol;
}

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

// Return the atomic subshells
const std::set<unsigned>&
AdjointElectronPhotonRelaxationDataContainer::getSubshells() const
{
  return d_subshells;
}

// Return the subshell occupancies
double AdjointElectronPhotonRelaxationDataContainer::getSubshellOccupancy(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_occupancies.find( subshell )->second;
}

// Return the subshell binding energies
double AdjointElectronPhotonRelaxationDataContainer::getSubshellBindingEnergy(
						const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
		    d_subshells.end() );

  return d_subshell_binding_energies.find( subshell )->second;
}

// Return if there is relaxation data
bool AdjointElectronPhotonRelaxationDataContainer::hasAdjointRelaxationData() const
{
  return false;
}

//---------------------------------------------------------------------------//
// GET PHOTON DATA
//---------------------------------------------------------------------------//

// Return the Compton profile momentum grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getComptonProfileMomentumGrid(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_compton_profile_momentum_grids.find( subshell )->second;
}

// Return the Compton profile for a subshell
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getComptonProfile(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                   d_subshells.end() );

  return d_compton_profiles.find( subshell )->second;
}

// Return the occupation number momentum grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getOccupationNumberMomentumGrid(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_occupation_number_momentum_grids.find( subshell )->second;
}

// Return the occupation number for a subshell
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getOccupationNumber(
					        const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_occupation_numbers.find( subshell )->second;
}

// Return the Waller-Hartree scattering function momentum grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getWallerHartreeScatteringFunctionMomentumGrid() const
{
  return d_waller_hartree_scattering_function_momentum_grid;
}

// Return the Waller-Hartree scattering function
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getWallerHartreeScatteringFunction() const
{
  return d_waller_hartree_scattering_function;
}

// Return the Waller-Hartree atomic form factor momentum grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getWallerHartreeAtomicFormFactorMomentumGrid() const
{
  return d_waller_hartree_atomic_form_factor_momentum_grid;
}

// Return the Waller-Hartree atomic form factor
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getWallerHartreeAtomicFormFactor() const
{
  return d_waller_hartree_atomic_form_factor;
}

// Return the adjoint photon energy grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointPhotonEnergyGrid() const
{
  return d_adjoint_photon_energy_grid;
}

// Return the adjoint Waller-Hartree (WH) incoherent photon max energy grid
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointWallerHartreeIncoherentMaxEnergyGrid() const
{
  return d_adjoint_waller_hartree_incoherent_max_energy_grid;
}

// Return the adjoint Waller-Hartree (WH) incoherent photon cross section
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointWallerHartreeIncoherentCrossSection() const
{
  return d_adjoint_waller_hartree_incoherent_cross_section;
}

// the adjoint impulse approx. (IA) incoherent photon max energy grid
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointImpulseApproxIncoherentMaxEnergyGrid() const
{
  return d_adjoint_impulse_approx_incoherent_max_energy_grid;
}

// Return the adjoint impulse approx. (IA) incoherent photon cross section
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointImpulseApproxIncoherentCrossSection() const
{
  return d_adjoint_impulse_approx_incoherent_cross_section;
}

// Return the subshell adjoint impulse approx. (IA) incoh. max energy grid
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_adjoint_impulse_approx_subshell_incoherent_max_energy_grids.find( subshell )->second;
}

// Return the subshell adjoint impulse approx. (IA) incoherent photon cs
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointImpulseApproxSubshellIncoherentCrossSection(
                                                const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) !=
                    d_subshells.end() );

  return d_adjoint_impulse_approx_subshell_incoherent_cross_sections.find( subshell )->second;
}

// Return the adjoint Waller-Hartree coherent cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointWallerHartreeCoherentCrossSection() const
{
  return d_waller_hartree_coherent_cross_section;
}

// Return the adjoint Waller-Hartree total max energy grid
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointWallerHartreeTotalMaxEnergyGrid() const
{
  return d_adjoint_waller_hatree_total_max_energy_grid;
}

// Return the adjoint Waller-Hartree total cross section
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointWallerHartreeTotalCrossSection() const
{
  return d_adjoint_waller_hatree_total_cross_section;
}

// Return the adjoint impulse approx. (IA) total max energy grid
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointImpulseApproxTotalMaxEnergyGrid() const
{
  return d_adjoint_impulse_approx_total_max_energy_grid;
}

// Return the adjoint impulse approx. (IA) total cross section
const std::vector<std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointImpulseApproxTotalCrossSection() const
{
  return d_adjoint_impulse_approx_total_cross_section;
}

// Return the (forward) Waller-Hartree total cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getWallerHartreeTotalCrossSection() const
{
  return d_waller_hartree_total_cross_section;
}

// Return the (forward) impulse approx. total cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getImpulseApproxTotalCrossSection() const
{
  return d_impulse_approx_total_cross_section;
}

// Return the adjoint pair production energy distribution grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointPairProductionEnergyDistributionGrid() const
{
  return d_adjoint_pair_production_energy_distribution_grid;
}

// Return the adjoint pair production energy distribution
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointPairProductionEnergyDistribution() const
{
  return d_adjoint_pair_production_energy_distribution;
}

// Return the adjoint pair production energy dist. norm grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointPairProductionEnergyDistributionNormConstantGrid() const
{
  return d_adjoint_pair_production_norm_constant_grid;
}

// Return the adjoint pair production energy dist. normalization constant
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointPairProductionEnergyDistributionNormConstant() const
{
  return d_adjoint_pair_production_norm_constant;
}

// Return the adjoint triplet production energy distribution grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointTripletProductionEnergyDistributionGrid() const
{
  return d_adjoint_triplet_production_energy_distribution_grid;
}

// Return the adjoint triplet production energy distribution
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointTripletProductionEnergyDistribution() const
{
  return d_adjoint_triplet_production_energy_distribution;
}

// Return the adjoint triplet production energy dist. norm grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointTripletProductionEnergyDistributionNormConstantGrid() const
{
  return d_adjoint_triplet_production_norm_constant_grid;
}

// Return the adjoint triplet production energy dist. normalization constant
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointTripletProductionEnergyDistributionNormConstant() const
{
  return d_adjoint_triplet_production_norm_constant;
}

//---------------------------------------------------------------------------//
// GET ELECTRON DATA
//---------------------------------------------------------------------------//

// Return the elastic angular energy grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointElasticAngularEnergyGrid() const
{
  return d_adjoint_angular_energy_grid;
}

// Return the elastic angles map
const std::map<double,std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointCutoffElasticAngles() const
{
  return d_adjoint_cutoff_elastic_angles;
}

// Return the elastic pdf map
const std::map<double,std::vector<double> >&
AdjointElectronPhotonRelaxationDataContainer::getAdjointCutoffElasticPDF() const
{
  return d_adjoint_cutoff_elastic_pdf;
}

// Return the elastic angles for an incoming energy
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointCutoffElasticAngles(
					        const double incoming_adjoint_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );

  return d_adjoint_cutoff_elastic_angles.find( incoming_adjoint_energy )->second;
}

// Return the elastic pdf for an incoming energy
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointCutoffElasticPDF(
					        const double incoming_adjoint_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );

  return d_adjoint_cutoff_elastic_pdf.find( incoming_adjoint_energy )->second;
}

// Return if there is moment preserving data
bool AdjointElectronPhotonRelaxationDataContainer::hasAdjointMomentPreservingData() const
{
  return d_adjoint_moment_preserving_elastic_discrete_angles.size() > 0;
}

// Return the moment preserving elastic discrete angles
const std::map<double,std::vector<double> >
AdjointElectronPhotonRelaxationDataContainer::getAdjointMomentPreservingElasticDiscreteAngles() const
{
  return d_adjoint_moment_preserving_elastic_discrete_angles;
}

// Return the moment preserving elastic weights
const std::map<double,std::vector<double> >
AdjointElectronPhotonRelaxationDataContainer::getAdjointMomentPreservingElasticWeights() const
{
  return d_adjoint_moment_preserving_elastic_weights;
}

// Return the moment preserving elastic discrete angles for an incoming energy
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointMomentPreservingElasticDiscreteAngles(
					        const double incoming_adjoint_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );

  return d_adjoint_moment_preserving_elastic_discrete_angles.find( incoming_adjoint_energy )->second;
}

// Return the moment preserving elastic weights for an incoming energy
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointMomentPreservingElasticWeights(
					        const double incoming_adjoint_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );

  return d_adjoint_moment_preserving_elastic_weights.find( incoming_adjoint_energy )->second;
}

// Return the electroionization energy grid for a subshell
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointElectroionizationEnergyGrid(
                            const unsigned subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  return d_adjoint_electroionization_energy_grid.find( subshell )->second;
}

// Return the electroionization recoil energy for a subshell and energy bin
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointElectroionizationRecoilEnergy(
                           const unsigned subshell,
					       const double incoming_adjoint_energy ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_adjoint_energy >=
            d_adjoint_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_adjoint_energy <=
            d_adjoint_electroionization_energy_grid.find( subshell )->second.back() );

  return d_adjoint_electroionization_recoil_energy.find( subshell )->second.find( incoming_adjoint_energy )->second;
}

// Return the electroionization recoil energy pdf for a subshell and energy bin
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointElectroionizationRecoilPDF(
                           const unsigned subshell,
					       const double incoming_adjoint_energy ) const
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition(
            incoming_adjoint_energy >=
            d_adjoint_electroionization_energy_grid.find( subshell )->second.front() );
  testPrecondition(
            incoming_adjoint_energy <=
            d_adjoint_electroionization_energy_grid.find( subshell )->second.back() );

  return d_adjoint_electroionization_recoil_pdf.find( subshell )->second.find( incoming_adjoint_energy )->second;
}

// Return the bremsstrahlung energy grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointBremsstrahlungEnergyGrid() const
{
  return d_adjoint_bremsstrahlung_energy_grid;
}

// Return the bremsstrahlung for an incoming energy
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointBremsstrahlungPhotonEnergy(
					        const double incoming_adjoint_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_bremsstrahlung_energy_grid.back() );

  return d_adjoint_bremsstrahlung_photon_energy.find( incoming_adjoint_energy )->second;
}

// Return the bremsstrahlung photon pdf for an incoming energy
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointBremsstrahlungPhotonPDF(
					        const double incoming_adjoint_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_bremsstrahlung_energy_grid.back() );

  return d_adjoint_bremsstrahlung_photon_pdf.find( incoming_adjoint_energy )->second;
}

// Return the atomic excitation energy grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointAtomicExcitationEnergyGrid() const
{
  return d_adjoint_atomic_excitation_energy_grid;
}

// Return the atomic excitation energy gain
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointAtomicExcitationEnergyGain() const
{
  return d_adjoint_atomic_excitation_energy_gain;
}

// Return the electron energy grid
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointElectronEnergyGrid() const
{
  return d_adjoint_electron_energy_grid;
}
// Return the cutoff elastic electron cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointCutoffElasticCrossSection() const
{
  return d_adjoint_cutoff_elastic_cross_section;
}

// Return the cutoff elastic cross section threshold energy bin index
unsigned
AdjointElectronPhotonRelaxationDataContainer::getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() const
{
  return d_adjoint_cutoff_elastic_cross_section_threshold_index;
}
// Return the screened Rutherford elastic electron cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointScreenedRutherfordElasticCrossSection() const
{
  return d_adjoint_screened_rutherford_elastic_cross_section;
}

// Return the screened Rutherford elastic cross section threshold energy bin index
unsigned
AdjointElectronPhotonRelaxationDataContainer::getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() const
{
  return d_adjoint_screened_rutherford_elastic_cross_section_threshold_index;
}
// Return the total elastic electron cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointTotalElasticCrossSection() const
{
  return d_adjoint_total_elastic_cross_section;
}

// Return the total elastic cross section threshold energy bin index
unsigned
AdjointElectronPhotonRelaxationDataContainer::getAdjointTotalElasticCrossSectionThresholdEnergyIndex() const
{
  return d_adjoint_total_elastic_cross_section_threshold_index;
}

// Return the Moment Preserving (MP) elastic electron cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointMomentPreservingCrossSection() const
{
  return d_adjoint_moment_preserving_elastic_cross_section;
}

// Return the MP elastic cross section threshold energy bin index
unsigned
AdjointElectronPhotonRelaxationDataContainer::getAdjointMomentPreservingCrossSectionThresholdEnergyIndex() const
{
  return d_adjoint_moment_preserving_elastic_cross_section_threshold_index;
}

// Return the electroionization electron cross section for a subshell
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointElectroionizationCrossSection(
    const unsigned subshell ) const
{
  return d_adjoint_electroionization_subshell_cross_section.find( subshell )->second;
}

// Return the electroionization cross section threshold energy bin index for a subshell
unsigned
AdjointElectronPhotonRelaxationDataContainer::getAdjointElectroionizationCrossSectionThresholdEnergyIndex(
    const unsigned subshell ) const
{
  return d_adjoint_electroionization_subshell_cross_section_threshold_index.find( subshell )->second;
}

// Return the bremsstrahlung electron cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointBremsstrahlungCrossSection() const
{
  return d_adjoint_bremsstrahlung_cross_section;
}

// Return the bremsstrahlung cross section threshold energy bin index
unsigned
AdjointElectronPhotonRelaxationDataContainer::getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex() const
{
  return d_adjoint_bremsstrahlung_cross_section_threshold_index;
}

// Return the atomic excitation electron cross section
const std::vector<double>&
AdjointElectronPhotonRelaxationDataContainer::getAdjointAtomicExcitationCrossSection() const
{
  return d_adjoint_atomic_excitation_cross_section;
}

// Return the atomic excitation cross section threshold energy bin index
unsigned
AdjointElectronPhotonRelaxationDataContainer::getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex() const
{
  return d_adjoint_atomic_excitation_cross_section_threshold_index;
}

//---------------------------------------------------------------------------//
// SET NOTES
//---------------------------------------------------------------------------//

// Set the table notes
void AdjointElectronPhotonRelaxationDataContainer::setNotes(
                                                     const std::string& notes )
{
  d_notes = notes;
}

//---------------------------------------------------------------------------//
// SET TABLE DATA
//---------------------------------------------------------------------------//

// Set the atomic number
void AdjointElectronPhotonRelaxationDataContainer::setAtomicNumber(
						 const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}

// Set the minimum photon energy
void AdjointElectronPhotonRelaxationDataContainer::setMinPhotonEnergy(
    const double min_photon_energy )
{
  // Make sure the energy is valid
  testPrecondition( min_photon_energy >= 0.0 );

  d_min_photon_energy = min_photon_energy;
}

// Set the maximum photon energy
void AdjointElectronPhotonRelaxationDataContainer::setMaxPhotonEnergy(
    const double max_photon_energy )
{
  // Make sure the energy is valid
  testPrecondition( max_photon_energy >= 0.0 );

  d_max_photon_energy = max_photon_energy;
}

// Set the minimum electron energy
void AdjointElectronPhotonRelaxationDataContainer::setMinElectronEnergy(
    const double min_electron_energy )
{
  // Make sure the energy is valid
  testPrecondition( min_electron_energy >= 0.0 );

  d_min_electron_energy = min_electron_energy;
}

// Set the adjoint pair production energy dist norm constant evaluation tol
void AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol >= 0.0 );

  d_adjoint_pair_production_energy_dist_norm_constant_evaluation_tol =
    evaluation_tol;
}

// Set the adjoint triplet production energy dist norm const evaluation tol
void AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol >= 0.0 );

  d_adjoint_triplet_production_energy_dist_norm_constant_evaluation_tol =
    evaluation_tol;
}

// Set the adjoint incoherent max energy nudge value
void AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentMaxEnergyNudgeValue(
                                                     const double nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( nudge_value > 0.0 );

  d_adjoint_incoherent_max_energy_nudge_value = nudge_value;
}

// Set the adjoint incoherent energy to max energy nudge value
void AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentEnergyToMaxEnergyNudgeValue(
                                                     const double nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( nudge_value >= 0.0 );

  d_adjoint_incoherent_energy_to_max_energy_nudge_value = nudge_value;
}

// Set the adjoint incoherent cross section evaluation tolerance
void AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol >= 0.0 );

  d_adjoint_incoherent_evaluation_tol = evaluation_tol;
}

// Set the adjoint incoherent grid convergence tolerance
void AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( convergence_tol >= 0.0 );

  d_adjoint_incoherent_grid_convergence_tol = convergence_tol;
}

// Set the adjoint incoherent grid absolute difference tolerance
void AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentGridAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_adjoint_incoherent_grid_absolute_diff_tol = absolute_diff_tol;
}

// Set the adjoint incoherent grid distance tolerance
void AdjointElectronPhotonRelaxationDataContainer::setAdjointIncoherentGridDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( distance_tol >= 0.0 );

  d_adjoint_incoherent_grid_distance_tol = distance_tol;
}

// Set the maximum electron energy
void AdjointElectronPhotonRelaxationDataContainer::setMaxElectronEnergy(
    const double max_electron_energy )
{
  // Make sure the energy is valid
  testPrecondition( max_electron_energy >= 0.0 );

  d_max_electron_energy = max_electron_energy;
}

// Set the elastic cutoff angle
void AdjointElectronPhotonRelaxationDataContainer::setCutoffAngleCosine(
                         const double cutoff_angle_cosine )
{
  // Make sure the elastic cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );

  d_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Set the number of discrete moment preserving angles
void AdjointElectronPhotonRelaxationDataContainer::setNumberOfAdjointMomentPreservingAngles(
    const unsigned number_of_adjoint_moment_preserving_angles )
{
  // Make sure the number of angles is valid
  testPrecondition( number_of_adjoint_moment_preserving_angles >= 0 );

  d_number_of_adjoint_moment_preserving_angles = number_of_adjoint_moment_preserving_angles;
}

// Set the union energy grid convergence tolerance
void AdjointElectronPhotonRelaxationDataContainer::setGridConvergenceTolerance(
    const double grid_convergence_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_convergence_tol >= 0.0 );

  d_grid_convergence_tol = grid_convergence_tol;
}

// Set the union energy grid absolute difference tolerance
void AdjointElectronPhotonRelaxationDataContainer::setGridAbsoluteDifferenceTolerance(
    const double grid_absolute_diff_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_absolute_diff_tol >= 0.0 );

  d_grid_absolute_diff_tol = grid_absolute_diff_tol;
}

// Set the union energy grid distance tolerance
void AdjointElectronPhotonRelaxationDataContainer::setGridDistanceTolerance(
    const double grid_distance_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( grid_distance_tol >= 0.0 );

  d_grid_distance_tol = grid_distance_tol;
}

//---------------------------------------------------------------------------//
// SET RELAXATION DATA
//---------------------------------------------------------------------------//


// Set the atomic subshells
void AdjointElectronPhotonRelaxationDataContainer::setSubshells(
				       const std::set<unsigned>& subshells )
{
  // Make sure the subshells are valid
  testPrecondition( subshells.size() > 0 );
  testPreconditionValuesGreaterThanOrEqualToZero( subshells );

  d_subshells = subshells;
}

// Set the subshell occupancy
void AdjointElectronPhotonRelaxationDataContainer::setSubshellOccupancy(
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
void AdjointElectronPhotonRelaxationDataContainer::setSubshellBindingEnergy(
						  const unsigned subshell,
						  const double binding_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the subshell binding energy is valid
  testPrecondition( binding_energy > 0.0 );

  d_subshell_binding_energies[subshell] = binding_energy;
}

//---------------------------------------------------------------------------//
// SET PHOTON DATA
//---------------------------------------------------------------------------//

// Set the Compton profile momentum grid for a subshell
void AdjointElectronPhotonRelaxationDataContainer::setComptonProfileMomentumGrid(
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
void AdjointElectronPhotonRelaxationDataContainer::setComptonProfile(
                                   const unsigned subshell,
                                   const std::vector<double>& compton_profile )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the compton_profile is valid
  testPrecondition( compton_profile.size() ==
		    d_compton_profile_momentum_grids.find( subshell )->second.size() );
  testPreconditionValuesGreaterThanZero( compton_profile );

  d_compton_profiles[subshell] = compton_profile;
}

// Set the occupation number momentum grid for a subshell
void AdjointElectronPhotonRelaxationDataContainer::setOccupationNumberMomentumGrid(
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
void AdjointElectronPhotonRelaxationDataContainer::setOccupationNumber(
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
void AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunctionMomentumGrid(
                                     const std::vector<double>& momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( momentum_grid.begin(),
						      momentum_grid.end() ) );
  testPreconditionValuesGreaterThanOrEqualToZero( momentum_grid );

  d_waller_hartree_scattering_function_momentum_grid = momentum_grid;
}

// Set the Waller-Hartree scattering function
void AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeScatteringFunction(
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
void AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactorMomentumGrid(
                                     const std::vector<double>& momentum_grid )
{
  // Make sure the momentum grid is valid
  testPrecondition( momentum_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( momentum_grid.begin(),
						      momentum_grid.end() ) );
  testPreconditionValuesGreaterThanOrEqualToZero( momentum_grid );

  d_waller_hartree_atomic_form_factor_momentum_grid = momentum_grid;
}

// Set the Waller-Hartree atomic form factor
void AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeAtomicFormFactor(
                                const std::vector<double>& atomic_form_factor )
{
  // Make sure the atomic form factor is valid
  testPrecondition( atomic_form_factor.size() ==
		    d_waller_hartree_atomic_form_factor_momentum_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending(
						 atomic_form_factor.rbegin(),
						 atomic_form_factor.rend() ) );
  testPrecondition( atomic_form_factor.front() == d_atomic_number );
  testPrecondition( atomic_form_factor.back() >= 0.0 );

  d_waller_hartree_atomic_form_factor = atomic_form_factor;
}

// Set the adjoint photon energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointPhotonEnergyGrid(
                                       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( energy_grid );

  d_adjoint_photon_energy_grid = energy_grid;
}

// Set the adjoint WH incoherent photon max energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeIncoherentMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid )
{
  // Make sure the max energy grid is valid
  testPrecondition( adjoint_incoherent_max_energy_grid.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_waller_hartree_incoherent_max_energy_grid =
    adjoint_incoherent_max_energy_grid;
}

// Set the adjoint WH incoherent photon cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeIncoherentCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( adjoint_incoherent_cross_section.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_waller_hartree_incoherent_cross_section =
    adjoint_incoherent_cross_section;
}

// Set the adjoint impulse approx. (IA) incoherent photon max energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxIncoherentMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid )
{
  // Make sure the max energy grid is valid
  testPrecondition( adjoint_incoherent_max_energy_grid.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_impulse_approx_incoherent_max_energy_grid =
    adjoint_incoherent_max_energy_grid;
}

// Set the adjoint impulse approx. (IA) incoherent photon cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxIncoherentCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( adjoint_incoherent_cross_section.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_impulse_approx_incoherent_cross_section =
    adjoint_incoherent_cross_section;
}

// Set the subshell adjoint IA incoherent photon max energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                                       const unsigned subshell,
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the max energy grid is valid
  testPrecondition( adjoint_incoherent_max_energy_grid.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_impulse_approx_subshell_incoherent_max_energy_grids[subshell] =
    adjoint_incoherent_max_energy_grid;
}

// Set the subshell adjoint IA incoherent photon cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxSubshellIncoherentCrossSection(
                                       const unsigned subshell,
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the cross section is valid
  testPrecondition( adjoint_incoherent_cross_section.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_impulse_approx_subshell_incoherent_cross_sections[subshell] =
    adjoint_incoherent_cross_section;
}

// Set the adjoint Waller-Hartree coherent cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeCoherentCrossSection(
                            const std::vector<double>& coherent_cross_section )
{
  // Make sure the coherent cross section is valid
  testPrecondition( coherent_cross_section.size() ==
		    d_adjoint_photon_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( coherent_cross_section );

  d_waller_hartree_coherent_cross_section = coherent_cross_section;
}

// Set the adjoint Waller-Hartree total max energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeTotalMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_max_energy_grid )
{
  // Make sure the max energy grid is valid
  testPrecondition( adjoint_total_max_energy_grid.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_waller_hatree_total_max_energy_grid =
    adjoint_total_max_energy_grid;
}

// Set the adjoint Waller-Hartree total cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointWallerHartreeTotalCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( adjoint_total_cross_section.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_waller_hatree_total_cross_section =
    adjoint_total_cross_section;
}

// Set the adjoint impulse approx. (IA) total max energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxTotalMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_max_energy_grid )
{
  // Make sure the max energy grid is valid
  testPrecondition( adjoint_total_max_energy_grid.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_impulse_approx_total_max_energy_grid =
    adjoint_total_max_energy_grid;
}

// Set the adjoint impulse approx. (IA) total cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointImpulseApproxTotalCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_cross_section )
{
  // Make sure the cross section is valid
  testPrecondition( adjoint_total_cross_section.size() ==
                    d_adjoint_photon_energy_grid.size() );

  d_adjoint_impulse_approx_total_cross_section =
    adjoint_total_cross_section;
}

// Set the (forward) Waller-Hartree total cross section
void AdjointElectronPhotonRelaxationDataContainer::setWallerHartreeTotalCrossSection(
                               const std::vector<double>& total_cross_section )
{
  // Make sure the total cross section is valid
  testPrecondition( total_cross_section.size() ==
                    d_adjoint_photon_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( total_cross_section );

  d_waller_hartree_total_cross_section = total_cross_section;
}

// Set the (forward) impulse apprx. total cross section
void AdjointElectronPhotonRelaxationDataContainer::setImpulseApproxTotalCrossSection(
                               const std::vector<double>& total_cross_section )
{
  // Make sure the total cross section is valid
  testPrecondition( total_cross_section.size() ==
                    d_adjoint_photon_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( total_cross_section );

  d_impulse_approx_total_cross_section = total_cross_section;
}

// Set the adjoint pair production energy distribution grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistributionGrid(
          const std::vector<double>& adjoint_pair_production_energy_dist_grid )
{
  // Make sure the energy distribution grid is valid
  testPreconditionEnergyGrid( adjoint_pair_production_energy_dist_grid );

  d_adjoint_pair_production_energy_distribution_grid =
    adjoint_pair_production_energy_dist_grid;
}

// Set the adjoint pair production energy distribution
void AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistribution(
               const std::vector<double>& adjoint_pair_production_energy_dist )
{
  // Make sure the energy distribution grid is valid
  testPrecondition( adjoint_pair_production_energy_dist.size() ==
                    d_adjoint_pair_production_energy_distribution_grid.size());

  d_adjoint_pair_production_energy_distribution =
    adjoint_pair_production_energy_dist;
}

// Set the adjoint pair production energy dist. norm constant grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistributionNormConstantGrid(
                          const std::vector<double>&
                          adjoint_pair_production_energy_dist_norm_const_grid )
{
  // Make sure the energy distribution grid is valid
  testPreconditionEnergyGrid(
                         adjoint_pair_production_energy_dist_norm_const_grid );
  
  d_adjoint_pair_production_norm_constant_grid =
    adjoint_pair_production_energy_dist_norm_const_grid;
}

// Set the adjoint pair production energy dist. norm constant
void AdjointElectronPhotonRelaxationDataContainer::setAdjointPairProductionEnergyDistributionNormConstant(
                               const std::vector<double>&
                               adjoint_pair_production_energy_dist_norm_const )
{
  // Make sure the energy dist. norm constant is valid
  testPrecondition( adjoint_pair_production_energy_dist_norm_const.size() ==
                    d_adjoint_pair_production_norm_constant_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending(
                    adjoint_pair_production_energy_dist_norm_const.begin(),
                    adjoint_pair_production_energy_dist_norm_const.end() ) );

  d_adjoint_pair_production_norm_constant =
    adjoint_pair_production_energy_dist_norm_const;
}

// Set the adjoint triplet production energy distribution grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistributionGrid(
       const std::vector<double>& adjoint_triplet_production_energy_dist_grid )
{
  // Make sure the energy distribution grid is valid
  testPreconditionEnergyGrid( adjoint_triplet_production_energy_dist_grid );

  d_adjoint_triplet_production_energy_distribution_grid =
    adjoint_triplet_production_energy_dist_grid;
}

// Set the adjoint triplet production energy distribution
void AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistribution(
            const std::vector<double>& adjoint_triplet_production_energy_dist )
{
  // Make sure the energy distribution grid is valid
  testPrecondition(
                 adjoint_triplet_production_energy_dist.size() ==
                 d_adjoint_triplet_production_energy_distribution_grid.size());

  d_adjoint_triplet_production_energy_distribution =
    adjoint_triplet_production_energy_dist;
}

// Set the adjoint triplet production energy dist. norm constant grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistributionNormConstantGrid(
                       const std::vector<double>&
                       adjoint_triplet_production_energy_dist_norm_const_grid )
{
  // Make sure the energy distribution grid is valid
  testPreconditionEnergyGrid(
                      adjoint_triplet_production_energy_dist_norm_const_grid );
  
  d_adjoint_triplet_production_norm_constant_grid =
    adjoint_triplet_production_energy_dist_norm_const_grid;
}

// Set the adjoint triplet production energy dist. norm constant
void AdjointElectronPhotonRelaxationDataContainer::setAdjointTripletProductionEnergyDistributionNormConstant(
                            const std::vector<double>&
                            adjoint_triplet_production_energy_dist_norm_const )
{
  // Make sure the energy dist. norm constant is valid
  testPrecondition( adjoint_triplet_production_energy_dist_norm_const.size() ==
                    d_adjoint_triplet_production_norm_constant_grid.size() );
  testPrecondition( Utility::Sort::isSortedAscending(
                     adjoint_triplet_production_energy_dist_norm_const.begin(),
                     adjoint_triplet_production_energy_dist_norm_const.end() ) );

  d_adjoint_triplet_production_norm_constant =
    adjoint_triplet_production_energy_dist_norm_const;
}
  
//---------------------------------------------------------------------------//
// SET ELECTRON DATA
//---------------------------------------------------------------------------//

// Set the elastic angular energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElasticAngularEnergyGrid(
				       const std::vector<double>& adjoint_angular_energy_grid )
{
  // Make sure the angular energy grid is valid
  testPrecondition( adjoint_angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( adjoint_angular_energy_grid.begin(),
			                              adjoint_angular_energy_grid.end() ) );

  testPreconditionValuesGreaterThanZero( adjoint_angular_energy_grid );

  d_adjoint_angular_energy_grid = adjoint_angular_energy_grid;
}

// Set the total elastic angles for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticAnglesAtEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_cutoff_elastic_angles )
{
  // Make sure the incoming_adjoint_energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );
  // Make sure the elastic angles are valid
  testPrecondition( std::find_if( adjoint_cutoff_elastic_angles.begin(),
                                  adjoint_cutoff_elastic_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    adjoint_cutoff_elastic_angles.end() );
  testPrecondition( std::find_if( adjoint_cutoff_elastic_angles.begin(),
                                  adjoint_cutoff_elastic_angles.end(),
                                  isValueGreaterThanOne ) ==
                    adjoint_cutoff_elastic_angles.end() );

  d_adjoint_cutoff_elastic_angles[incoming_adjoint_energy] = adjoint_cutoff_elastic_angles;
}

// Set the total elastic pdf for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticPDFAtEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_cutoff_elastic_pdf )
{
  // Make sure the incoming_adjoint_energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );
  // Make sure the weight is valid
  testPreconditionValuesGreaterThanZero( adjoint_cutoff_elastic_pdf );

  d_adjoint_cutoff_elastic_pdf[incoming_adjoint_energy] = adjoint_cutoff_elastic_pdf;
}
// Set the total elastic angles
void AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticAngles(
    const std::map<double,std::vector<double> >& adjoint_cutoff_elastic_angles )
{
  d_adjoint_cutoff_elastic_angles = adjoint_cutoff_elastic_angles;
}

// Set the total elastic pdf
void AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticPDF(
    const std::map<double,std::vector<double> >& adjoint_cutoff_elastic_pdf )
{
  d_adjoint_cutoff_elastic_pdf = adjoint_cutoff_elastic_pdf;
}

// Set the moment preserving elastic discrete angles for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticDiscreteAnglesAtEnergy(
		     const double incoming_adjoint_energy,
		     const std::vector<double>& adjoint_moment_preserving_elastic_discrete_angles )
{
  // Make sure the incoming_adjoint_energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );
  // Make sure the moment preserving elastic discrete angles are valid
 /* testPrecondition( adjoint_moment_preserving_elastic_discrete_angles.size() ==
               d_adjoint_number_of_discrete_angles.find( incoming_adjoint_energy )->second );*/
  testPrecondition( std::find_if( adjoint_moment_preserving_elastic_discrete_angles.begin(),
                                  adjoint_moment_preserving_elastic_discrete_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    adjoint_moment_preserving_elastic_discrete_angles.end() );
  testPrecondition( std::find_if( adjoint_moment_preserving_elastic_discrete_angles.begin(),
                                  adjoint_moment_preserving_elastic_discrete_angles.end(),
                                  isValueGreaterThanOne ) ==
                    adjoint_moment_preserving_elastic_discrete_angles.end() );

  d_adjoint_moment_preserving_elastic_discrete_angles[incoming_adjoint_energy] =
        adjoint_moment_preserving_elastic_discrete_angles;
}

// Set the moment preserving elastic weights for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticWeightsAtEnergy(
			 const double incoming_adjoint_energy,
			 const std::vector<double>& adjoint_moment_preserving_elastic_weights )
{
  // Make sure the incoming_adjoint_energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_angular_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_angular_energy_grid.back() );
  // Make sure the weight is valid
  /*testPrecondition( adjoint_moment_preserving_elastic_weights.size() ==
               d_adjoint_number_of_discrete_angles.find( incoming_adjoint_energy )->second );*/
  testPreconditionValuesGreaterThanZero( adjoint_moment_preserving_elastic_weights );
  testPrecondition( std::find_if( adjoint_moment_preserving_elastic_weights.begin(),
                                  adjoint_moment_preserving_elastic_weights.end(),
                                  isValueGreaterThanOne ) ==
                    adjoint_moment_preserving_elastic_weights.end() );

  d_adjoint_moment_preserving_elastic_weights[incoming_adjoint_energy] = adjoint_moment_preserving_elastic_weights;
}

// Set the moment preserving elastic discrete angles for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticDiscreteAngles(
    const std::map<double,std::vector<double> >& adjoint_moment_preserving_elastic_discrete_angles )
{
  d_adjoint_moment_preserving_elastic_discrete_angles =
        adjoint_moment_preserving_elastic_discrete_angles;
}

// Set the moment preserving elastic weights
void AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingElasticWeights(
    const std::map<double,std::vector<double> >& adjoint_moment_preserving_elastic_weights )
{
  d_adjoint_moment_preserving_elastic_weights =
    adjoint_moment_preserving_elastic_weights;
}

// Set the electroionization energy grid for a subshell
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationEnergyGrid(
            const unsigned subshell,
            const std::vector<double>& adjoint_electroionization_energy_grid )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  testPreconditionEnergyGrid( adjoint_electroionization_energy_grid );

  d_adjoint_electroionization_energy_grid[subshell] =
    adjoint_electroionization_energy_grid;
}

// Set the electroionization recoil energy for a subshell and energy bin
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilEnergyAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_adjoint_energy,
            const std::vector<double>& adjoint_electroionization_recoil_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >=
    d_adjoint_electroionization_energy_grid[subshell].front() );
  testPrecondition( incoming_adjoint_energy <=
    d_adjoint_electroionization_energy_grid[subshell].back() );
  // Make sure the electroionization recoil energy is valid
  testPreconditionValuesGreaterThanZero( adjoint_electroionization_recoil_energy );

  d_adjoint_electroionization_recoil_energy[subshell][ incoming_adjoint_energy] =
    adjoint_electroionization_recoil_energy;
}

// Set the electroionization recoil energy pdf for a subshell and energy bin
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilPDFAtIncomingEnergy(
            const unsigned subshell,
            const double incoming_adjoint_energy,
            const std::vector<double>& adjoint_electroionization_recoil_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the incoming energy is valid
  testPrecondition( incoming_adjoint_energy >=
    d_adjoint_electroionization_energy_grid[subshell].front() );
  testPrecondition( incoming_adjoint_energy <=
    d_adjoint_electroionization_energy_grid[subshell].back() );
  // Make sure the electroionization recoil pdf is valid
  testPreconditionValuesGreaterThanZero( adjoint_electroionization_recoil_pdf );

  d_adjoint_electroionization_recoil_pdf[subshell][ incoming_adjoint_energy] =
    adjoint_electroionization_recoil_pdf;
}

// Set electroionization recoil energy for all incoming energies in a subshell
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& adjoint_electroionization_recoil_energy )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_adjoint_electroionization_recoil_energy[subshell] =
    adjoint_electroionization_recoil_energy;
}

// Set electroionization recoil energy pdf for all incoming energies in a subshell
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationRecoilPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& adjoint_electroionization_recoil_pdf )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );

  d_adjoint_electroionization_recoil_pdf[subshell] =
    adjoint_electroionization_recoil_pdf;
}

// Set the bremsstrahlung energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungEnergyGrid(
				       const std::vector<double>& adjoint_bremsstrahlung_energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( adjoint_bremsstrahlung_energy_grid );

  d_adjoint_bremsstrahlung_energy_grid = adjoint_bremsstrahlung_energy_grid;
}

// Set the bremsstrahlung photon energy for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy(
		     const double incoming_adjoint_energy,
		     const std::vector<double>&  adjoint_bremsstrahlung_photon_energy )
{
  // Make sure the incoming_adjoint_energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_bremsstrahlung_energy_grid.back() );
  // Make sure the bremsstrahlung photon energies are valid
  testPreconditionValuesGreaterThanZero( adjoint_bremsstrahlung_photon_energy );

  d_adjoint_bremsstrahlung_photon_energy[incoming_adjoint_energy] =
    adjoint_bremsstrahlung_photon_energy;
}

// Set the bremsstrahlung photon pdf for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungPhotonPDFAtIncomingEnergy(
	 const double incoming_adjoint_energy,
	 const std::vector<double>& adjoint_bremsstrahlung_photon_pdf )
{
  // Make sure the incoming_adjoint_energy is valid
  testPrecondition( incoming_adjoint_energy >= d_adjoint_bremsstrahlung_energy_grid.front() );
  testPrecondition( incoming_adjoint_energy <= d_adjoint_bremsstrahlung_energy_grid.back() );
  // Make sure the pdf is valid
  testPreconditionValuesGreaterThanZero( adjoint_bremsstrahlung_photon_pdf );

  d_adjoint_bremsstrahlung_photon_pdf[incoming_adjoint_energy] =
    adjoint_bremsstrahlung_photon_pdf;
}

// Set all the bremsstrahlung photon energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungPhotonEnergy(
    const std::map<double,std::vector<double> >&  adjoint_bremsstrahlung_photon_energy )
{
  d_adjoint_bremsstrahlung_photon_energy = adjoint_bremsstrahlung_photon_energy;
}

// Set all the bremsstrahlung photon pdf
void AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungPhotonPDF(
    const std::map<double,std::vector<double> >& adjoint_bremsstrahlung_photon_pdf )
{
  d_adjoint_bremsstrahlung_photon_pdf = adjoint_bremsstrahlung_photon_pdf;
}

// Set the atomic excitation energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationEnergyGrid(
    const std::vector<double>& adjoint_atomic_excitation_energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( adjoint_atomic_excitation_energy_grid );

  d_adjoint_atomic_excitation_energy_grid = adjoint_atomic_excitation_energy_grid;
}

// Set the atomic excitation energy gain for an incoming energy
void AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationEnergyGain(
    const std::vector<double>&  adjoint_atomic_excitation_energy_gain )
{
  // Make sure the atomic excitation energy gain are valid
  testPreconditionValuesGreaterThanZero( adjoint_atomic_excitation_energy_gain );

  d_adjoint_atomic_excitation_energy_gain =
    adjoint_atomic_excitation_energy_gain;
}

// Set the electron energy grid
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectronEnergyGrid(
    const std::vector<double>& adjoint_energy_grid )
{
  // Make sure the energy grid is valid
  testPreconditionEnergyGrid( adjoint_energy_grid );

  d_adjoint_electron_energy_grid = adjoint_energy_grid;
}

// Set the cutoff elastic electron cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticCrossSection(
			 const std::vector<double>& adjoint_cutoff_elastic_cross_section )
{
  // Make sure the cutoff elastic cross section is valid
  testPrecondition( adjoint_cutoff_elastic_cross_section.size() <=
                    d_adjoint_electron_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( adjoint_cutoff_elastic_cross_section );

  d_adjoint_cutoff_elastic_cross_section = adjoint_cutoff_elastic_cross_section;
}

// Set the cutoff elastic cross section threshold energy bin index
void AdjointElectronPhotonRelaxationDataContainer::setAdjointCutoffElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_adjoint_cutoff_elastic_cross_section.size() + index ==
        d_adjoint_electron_energy_grid.size() );

 d_adjoint_cutoff_elastic_cross_section_threshold_index = index;
}

// Set the screened rutherford elastic electron cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointScreenedRutherfordElasticCrossSection(
			 const std::vector<double>& adjoint_screened_rutherford_elastic_cross_section )
{
  // Make sure the screened rutherford elastic cross section is valid
  testPrecondition( adjoint_screened_rutherford_elastic_cross_section.size() <=
                    d_adjoint_electron_energy_grid.size() );
  testPrecondition( std::find_if( adjoint_screened_rutherford_elastic_cross_section.begin(),
                                  adjoint_screened_rutherford_elastic_cross_section.end(),
                                  isValueLessThanZero ) ==
                    adjoint_screened_rutherford_elastic_cross_section.end() );

  d_adjoint_screened_rutherford_elastic_cross_section =
    adjoint_screened_rutherford_elastic_cross_section;
}

// Set the screened rutherford elastic cross section threshold energy bin index
void AdjointElectronPhotonRelaxationDataContainer::setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_adjoint_screened_rutherford_elastic_cross_section.size() + index ==
        d_adjoint_electron_energy_grid.size() );

 d_adjoint_screened_rutherford_elastic_cross_section_threshold_index = index;
}

// Set the total elastic electron cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointTotalElasticCrossSection(
			 const std::vector<double>& adjoint_total_elastic_cross_section )
{
  // Make sure the total elastic cross section is valid
  testPrecondition( adjoint_total_elastic_cross_section.size() <=
                    d_adjoint_electron_energy_grid.size() );
  testPreconditionValuesGreaterThanZero( adjoint_total_elastic_cross_section );

  d_adjoint_total_elastic_cross_section = adjoint_total_elastic_cross_section;
}

// Set the total elastic cross section threshold energy bin index
void AdjointElectronPhotonRelaxationDataContainer::setAdjointTotalElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_adjoint_total_elastic_cross_section.size() + index ==
        d_adjoint_electron_energy_grid.size() );

 d_adjoint_total_elastic_cross_section_threshold_index = index;
}

// Set the elastic electron cross section using Moment Preserving (MP) theory
void AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingCrossSection(
			 const std::vector<double>& adjoint_moment_preserving_elastic_cross_section )
{
  // Make sure the moment preserving elastic cross section is valid
  testPrecondition( adjoint_moment_preserving_elastic_cross_section.size() <=
                    d_adjoint_electron_energy_grid.size() );
  testPreconditionValuesGreaterThanZero(
    adjoint_moment_preserving_elastic_cross_section );

  d_adjoint_moment_preserving_elastic_cross_section =
        adjoint_moment_preserving_elastic_cross_section;
}

// Set the MP elastic cross section threshold energy bin index
void AdjointElectronPhotonRelaxationDataContainer::setAdjointMomentPreservingCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_adjoint_moment_preserving_elastic_cross_section.size() + index ==
        d_adjoint_electron_energy_grid.size() );

 d_adjoint_moment_preserving_elastic_cross_section_threshold_index= index;
}

// Set the electroionization electron cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationCrossSection(
            const unsigned subshell,
            const std::vector<double>& adjoint_electroionization_cross_section )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the electroionization cross section is valid
  testPrecondition( adjoint_electroionization_cross_section.size() <=
                    d_adjoint_electron_energy_grid.size() );
  testPreconditionValuesGreaterThanOrEqualToZero(
    adjoint_electroionization_cross_section );

  d_adjoint_electroionization_subshell_cross_section[subshell] =
    adjoint_electroionization_cross_section;
}

// Set the electroionization cross section threshold energy bin index
void AdjointElectronPhotonRelaxationDataContainer::setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
            const unsigned subshell,
	        const unsigned index )
{
  // Make sure the subshell is valid
  testPrecondition( d_subshells.find( subshell ) != d_subshells.end() );
  // Make sure the threshold index is valid
  testPrecondition(
        d_adjoint_electroionization_subshell_cross_section[subshell].size() + index ==
        d_adjoint_electron_energy_grid.size() );

  d_adjoint_electroionization_subshell_cross_section_threshold_index[subshell] =
    index;
}

// Set the bremsstrahlung electron cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungCrossSection(
			 const std::vector<double>& adjoint_bremsstrahlung_cross_section )
{
  // Make sure the bremsstrahlung cross section is valid
  testPrecondition( adjoint_bremsstrahlung_cross_section.size() <=
                    d_adjoint_electron_energy_grid.size() );
  testPreconditionValuesGreaterThanOrEqualToZero( adjoint_bremsstrahlung_cross_section );

  d_adjoint_bremsstrahlung_cross_section = adjoint_bremsstrahlung_cross_section;
}

// Set the bremsstrahlung cross section threshold energy bin index
void AdjointElectronPhotonRelaxationDataContainer::setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_adjoint_bremsstrahlung_cross_section.size() + index ==
        d_adjoint_electron_energy_grid.size() );

 d_adjoint_bremsstrahlung_cross_section_threshold_index = index;
}

// Set the atomic excitation electron cross section
void AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationCrossSection(
			 const std::vector<double>& adjoint_atomic_excitation_cross_section )
{
  // Make sure the atomic excitation cross section is valid
  testPrecondition( adjoint_atomic_excitation_cross_section.size() <=
                    d_adjoint_electron_energy_grid.size() );
  testPreconditionValuesGreaterThanOrEqualToZero( adjoint_atomic_excitation_cross_section );

  d_adjoint_atomic_excitation_cross_section =
    adjoint_atomic_excitation_cross_section;
}

// Set the atomic excitation cross section threshold energy bin index
void AdjointElectronPhotonRelaxationDataContainer::setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition(
        d_adjoint_atomic_excitation_cross_section.size() + index ==
        d_adjoint_electron_energy_grid.size() );

 d_adjoint_atomic_excitation_cross_section_threshold_index = index;
}


} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationDataContainer.cpp
//---------------------------------------------------------------------------//
