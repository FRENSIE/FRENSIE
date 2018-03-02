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
#include <string>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ArchivableObject.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

/*! The electron-photon-relaxation data container
 * \details Linear-linear interpolation should be used for all data.
 */
class AdjointElectronPhotonRelaxationDataContainer : public Utility::ArchivableObject<AdjointElectronPhotonRelaxationDataContainer>
{

public:

  //! Constructor (from saved archive)
  AdjointElectronPhotonRelaxationDataContainer(
                          const boost::filesystem::path& file_name_with_path );

  //! Destructor
  virtual ~AdjointElectronPhotonRelaxationDataContainer()
  { /* ... */ }

  //! The database name used in an archive
  const char* getArchiveName() const override;

//---------------------------------------------------------------------------//
// GET NOTES
//---------------------------------------------------------------------------//

  //! Return the table notes
  const std::string& getNotes() const;

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

  //! Return the adjoint pair production energy dist norm constant evaluation tol
  double getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance() const;

  //! Return the adjoint pair production energy dist norm constant nudge value
  double getAdjointPairProductionEnergyDistNormConstantNudgeValue() const;

  //! Return the adjoint triplet production energy dist norm const evaluation tol
  double getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance() const;

  //! Return the adjoint triplet production energy dist norm const nudge value
  double getAdjointTripletProductionEnergyDistNormConstantNudgeValue() const;

  //! Return the adjoint incoherent max energy nudge value
  double getAdjointIncoherentMaxEnergyNudgeValue() const;

  //! Return the adjoint incoherent energy to max energy nudge value
  double getAdjointIncoherentEnergyToMaxEnergyNudgeValue() const;

  //! Return the adjoint incoherent cross section evaluation tolerance
  double getAdjointIncoherentEvaluationTolerance() const;

  //! Return the adjoint incoherent grid convergence tolerance
  double getAdjointIncoherentGridConvergenceTolerance() const;

  //! Return the adjoint incoherent grid absolute difference tolerance
  double getAdjointIncoherentGridAbsoluteDifferenceTolerance() const;

  //! Return the adjoint incoherent grid distance tolerance
  double getAdjointIncoherentGridDistanceTolerance() const;

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

  //! Return the Waller-Hartree squared atomic form factor squared mom. grid
  const std::vector<double>&
  getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid() const;

  //! Return the Waller-Hartree squared atomic form factor
  const std::vector<double>& getWallerHartreeSquaredAtomicFormFactor() const;

  //! Return the adjoint photon energy grid
  const std::vector<double>& getAdjointPhotonEnergyGrid() const;

  //! Return the adjoint Waller-Hartree (WH) incoherent photon max energy grid
  const std::vector<std::vector<double> >&
  getAdjointWallerHartreeIncoherentMaxEnergyGrid() const;

  //! Return the adjoint Waller-Hartree (WH) incoherent photon cross section
  const std::vector<std::vector<double> >&
  getAdjointWallerHartreeIncoherentCrossSection() const;

  //! Return the adjoint impulse approx. (IA) incoherent photon max energy grid
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxIncoherentMaxEnergyGrid() const;

  //! Return the adjoint impulse approx. (IA) incoherent photon cross section
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxIncoherentCrossSection() const;

  //! Return the subshell adjoint impulse approx. (IA) incoh. max energy grid
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                                               const unsigned subshell ) const;

  //! Return the subshell adjoint impulse approx. (IA) incoherent photon cs
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxSubshellIncoherentCrossSection(
                                               const unsigned subshell ) const;

  //! Return the adjoint Waller-Hartree coherent cross section
  const std::vector<double>&
  getAdjointWallerHartreeCoherentCrossSection() const;

  //! Return the adjoint Waller-Hartree total max energy grid
  const std::vector<std::vector<double> >&
  getAdjointWallerHartreeTotalMaxEnergyGrid() const;

  //! Return the adjoint Waller-Hartree total cross section
  const std::vector<std::vector<double> >&
  getAdjointWallerHartreeTotalCrossSection() const;

  //! Return the adjoint impulse approx. (IA) total max energy grid
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxTotalMaxEnergyGrid() const;

  //! Return the adjoint impulse approx. (IA) total cross section
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxTotalCrossSection() const;

  //! Return the (forward) Waller-Hartree total cross section
  const std::vector<double>& getWallerHartreeTotalCrossSection() const;

  //! Return the (forward) impulse approx. total cross section
  const std::vector<double>& getImpulseApproxTotalCrossSection() const;

  //! Return the adjoint pair production energy distribution grid
  const std::vector<double>&
  getAdjointPairProductionEnergyDistributionGrid() const;

  //! Return the adjoint pair production energy distribution
  const std::vector<double>&
  getAdjointPairProductionEnergyDistribution() const;

  //! Return the adjoint pair production energy dist. norm grid
  const std::vector<double>&
  getAdjointPairProductionEnergyDistributionNormConstantGrid() const;

  //! Return the adjoint pair production energy dist. normalization constant
  const std::vector<double>&
  getAdjointPairProductionEnergyDistributionNormConstant() const;

  //! Return the adjoint triplet production energy distribution grid
  const std::vector<double>&
  getAdjointTripletProductionEnergyDistributionGrid() const;

  //! Return the adjoint triplet production energy distribution
  const std::vector<double>&
  getAdjointTripletProductionEnergyDistribution() const;

  //! Return the adjoint triplet production energy dist. norm grid
  const std::vector<double>&
  getAdjointTripletProductionEnergyDistributionNormConstantGrid() const;

  //! Return the adjoint triplet production energy dist. normalization constant
  const std::vector<double>&
  getAdjointTripletProductionEnergyDistributionNormConstant() const;

  //! Return the bremsstrahlung incoming photon energy grid for the scattering spectrum
  const std::vector<double>& getAdjointPhotonBremsstrahlungEnergyGrid() const;

  //! Return the bremsstrahlung electron energy for an incoming photon energy
  const std::vector<double>& getAdjointPhotonBremsstrahlungEnergy(
					       const double incoming_adjoint_energy ) const;

  //! Return the bremsstrahlung pdf for an incoming photon energy
  const std::vector<double>& getAdjointPhotonBremsstrahlungPDF(
					       const double incoming_adjoint_energy ) const;

  //! Return the bremsstrahlung photon cross section
  const std::vector<double>& getAdjointBremsstrahlungPhotonCrossSection() const;

  //! Return the bremsstrahlung photon cross section threshold energy bin index
  unsigned getAdjointBremsstrahlungPhotonCrossSectionThresholdEnergyIndex() const;

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

  //! Return if there is a seperate electroionization incoming electron energy grid for the scattering spectrum
  bool seperateAdjointElectroionizationEnergyGrid() const;

  //! Return the electroionization recoil energy for a subshell and incoming energy
  const std::vector<double>& getAdjointElectroionizationRecoilEnergy(
                           const unsigned subshell,
					       const double incoming_adjoint_energy ) const;

  //! Return the electroionization recoil energy pdf for a subshell and incoming energy
  const std::vector<double>& getAdjointElectroionizationRecoilPDF(
                           const unsigned subshell,
					       const double incoming_adjoint_energy ) const;

  //! Return the bremsstrahlung incoming electron energy grid for the scattering spectrum
  const std::vector<double>& getAdjointElectronBremsstrahlungEnergyGrid() const;

  //! Return if there is a seperate bremsstrahlung incoming electron energy grid for the scattering spectrum
  bool seperateAdjointBremsstrahlungEnergyGrid() const;

  //! Return the bremsstrahlung electron energy for an incoming electron energy
  const std::vector<double>& getAdjointElectronBremsstrahlungEnergy(
					       const double incoming_adjoint_energy ) const;

  //! Return the bremsstrahlung pdf for an incoming electron energy
  const std::vector<double>& getAdjointElectronBremsstrahlungPDF(
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
  const std::vector<double>& getAdjointBremsstrahlungElectronCrossSection() const;

  //! Return the bremsstrahlung electron cross section threshold energy bin index
  unsigned getAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& getAdjointAtomicExcitationCrossSection() const;

  //! Return the atomic excitation cross section threshold energy bin index
  unsigned getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex() const;

protected:

  //! Default constructor
  AdjointElectronPhotonRelaxationDataContainer()
  { /* ... */ }

//---------------------------------------------------------------------------//
// SET NOTES
//---------------------------------------------------------------------------//

  //! Set the table notes
  void setNotes( const std::string& notes );

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

  //! Set the adjoint pair production energy dist norm constant evaluation tol
  void setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Set the adjoint pair production energy dist norm constant nudge value
  void setAdjointPairProductionEnergyDistNormConstantNudgeValue(
                                                    const double nudge_value );

  //! Set the adjoint triplet production energy dist norm const evaluation tol
  void setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Set the adjoint triplet production energy dist norm const nudge value
  void setAdjointTripletProductionEnergyDistNormConstantNudgeValue(
                                                    const double nudge_value );

  //! Set the adjoint incoherent max energy nudge value
  void setAdjointIncoherentMaxEnergyNudgeValue( const double nudge_value );

  //! Set the adjoint incoherent energy to max energy nudge value
  void setAdjointIncoherentEnergyToMaxEnergyNudgeValue(
                                                    const double nudge_value );

  //! Set the adjoint incoherent cross section evaluation tolerance
  void setAdjointIncoherentEvaluationTolerance( const double evaluation_tol );

  //! Set the adjoint incoherent grid convergence tolerance
  void setAdjointIncoherentGridConvergenceTolerance(
                                                const double convergence_tol );

  //! Set the adjoint incoherent grid absolute difference tolerance
  void setAdjointIncoherentGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Set the adjoint incoherent grid distance tolerance
  void setAdjointIncoherentGridDistanceTolerance( const double distance_tol );

  //! Set the upper cutoff scattering angle below which moment preserving elastic scattering is used
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Set the number of discrete moment preserving angles
  void setNumberOfAdjointMomentPreservingAngles(
    const unsigned number_of_adjoint_moment_preserving_angles );

  //! Set the adjoint bremsstrahlung evaluation tolerance
  void setAdjointBremsstrahlungEvaluationTolerance(
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

  //! Set the Compton profile momentum grid for a subshell
  void setComptonProfileMomentumGrid(
                    const unsigned subshell,
                    const std::vector<double>& compton_profile_momentum_grid );

  //! Set the Compton profile  for a subshell
  void setComptonProfile( const unsigned subshell,
                          const std::vector<double>& compton_profile );

  //! Set the occupation number momentum grid for a subshell
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

  //! Return the Waller-Hartree squared atomic form factor squared mom. grid
  void setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
                            const std::vector<double>& squared_momentum_grid );

  //! Return the Waller-Hartree squared atomic form factor
  void setWallerHartreeSquaredAtomicFormFactor(
                       const std::vector<double>& squared_atomic_form_factor );

  //! Set the adjoint photon energy grid
  void setAdjointPhotonEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the adjoint WH incoherent photon max energy grid
  void setAdjointWallerHartreeIncoherentMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid );

  //! Set the adjoint WH incoherent photon cross section
  void setAdjointWallerHartreeIncoherentCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section );

  //! Set the adjoint impulse approx. (IA) incoherent photon max energy grid
  void setAdjointImpulseApproxIncoherentMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid );

  //! Set the adjoint impulse approx. (IA) incoherent photon cross section
  void setAdjointImpulseApproxIncoherentCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section );

  //! Set the subshell adjoint IA incoherent photon max energy grid
  void setAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                                       const unsigned subshell,
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid );

  //! Set the subshell adjoint IA incoherent photon cross section
  void setAdjointImpulseApproxSubshellIncoherentCrossSection(
                                       const unsigned subshell,
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section );

  //! Set the adjoint Waller-Hartree coherent cross section
  void setAdjointWallerHartreeCoherentCrossSection(
                           const std::vector<double>& coherent_cross_section );

  //! Set the adjoint Waller-Hartree total max energy grid
  void setAdjointWallerHartreeTotalMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_max_energy_grid );

  //! Set the adjoint Waller-Hartree total cross section
  void setAdjointWallerHartreeTotalCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_cross_section );

  //! Set the adjoint impulse approx. (IA) total max energy grid
  void setAdjointImpulseApproxTotalMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_max_energy_grid );

  //! Set the adjoint impulse approx. (IA) total cross section
  void setAdjointImpulseApproxTotalCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_cross_section );

  //! Set the (forward) Waller-Hartree total cross section
  void setWallerHartreeTotalCrossSection(
                              const std::vector<double>& total_cross_section );

  //! Set the (forward) impulse apprx. total cross section
  void setImpulseApproxTotalCrossSection(
                              const std::vector<double>& total_cross_section );

  //! Set the adjoint pair production energy distribution grid
  void setAdjointPairProductionEnergyDistributionGrid(
          const std::vector<double>& ajoint_pair_production_energy_dist_grid );

  //! Set the adjoint pair production energy distribution
  void setAdjointPairProductionEnergyDistribution(
              const std::vector<double>& adjoint_pair_production_energy_dist );

  //! Set the adjoint pair production energy dist. norm constant grid
  void setAdjointPairProductionEnergyDistributionNormConstantGrid(
                         const std::vector<double>&
                         adjoint_pair_production_energy_dist_norm_const_grid );

  //! Set the adjoint pair production energy dist. norm constant
  void setAdjointPairProductionEnergyDistributionNormConstant(
                         const std::vector<double>&
                         adjoint_pair_production_energy_dist_norm_const );

  //! Set the adjoint triplet production energy distribution grid
  void setAdjointTripletProductionEnergyDistributionGrid(
          const std::vector<double>& ajoint_triplet_production_energy_dist_grid );

  //! Set the adjoint triplet production energy distribution
  void setAdjointTripletProductionEnergyDistribution(
              const std::vector<double>& adjoint_triplet_production_energy_dist );

  //! Set the adjoint triplet production energy dist. norm constant grid
  void setAdjointTripletProductionEnergyDistributionNormConstantGrid(
                         const std::vector<double>&
                         adjoint_triplet_production_energy_dist_norm_const_grid );

  //! Set the adjoint triplet production energy dist. norm constant
  void setAdjointTripletProductionEnergyDistributionNormConstant(
                         const std::vector<double>&
                         adjoint_triplet_production_energy_dist_norm_const );

  //! Set the bremsstrahlung incoming photon energy grid for the scattering spectrum
  void setAdjointPhotonBremsstrahlungEnergyGrid(
    const std::vector<double>& adjoint_bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung electron energy for an incoming photon energy
  void setAdjointPhotonBremsstrahlungEnergyAtIncomingEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_photon_bremsstrahlung_energy );

  //! Set the bremsstrahlung pdf for an incoming photon energy
  void setAdjointPhotonBremsstrahlungPDFAtIncomingEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>&  adjoint_photon_bremsstrahlung_pdf );

  //! Set the bremsstrahlung electron energy for photons
  void setAdjointPhotonBremsstrahlungEnergy(
    const std::map<double,std::vector<double> >&
    adjoint_photon_bremsstrahlung_energy );

  //! Set the bremsstrahlung pdf for photons
  void setAdjointPhotonBremsstrahlungPDF(
    const std::map<double,std::vector<double> >&
    adjoint_photon_bremsstrahlung_pdf );

  //! Set the bremsstrahlung photon cross section
  void setAdjointBremsstrahlungPhotonCrossSection(
			 const std::vector<double>& adjoint_bremsstrahlung_cross_section );

  //! Set the bremsstrahlung photon cross section threshold energy bin index
  void setAdjointBremsstrahlungPhotonCrossSectionThresholdEnergyIndex(
                                const unsigned index );

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
  void setAdjointMomentPreservingElasticDiscreteAnglesAtEnergy(
	const double incoming_adjoint_energy,
	const std::vector<double>& adjoint_moment_preserving_elastic_discrete_angles );

  //! Set the moment preserving elastic weights for an incoming energy
  void setAdjointMomentPreservingElasticWeightsAtEnergy(
	const double incoming_adjoint_energy,
	const std::vector<double>& adjoint_moment_preserving_elastic_weights );

  //! Set the moment preserving elastic discrete angles
  void setAdjointMomentPreservingElasticDiscreteAngles(
    const std::map<double,std::vector<double> >& adjoint_moment_preserving_elastic_discrete_angles );

  //! Set the moment preserving elastic weights
  void setAdjointMomentPreservingElasticWeights(
    const std::map<double,std::vector<double> >& adjoint_moment_preserving_elastic_weights );

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

  //! Set the bremsstrahlung incoming electron energy grid for the scattering spectrum
  void setAdjointElectronBremsstrahlungEnergyGrid(
    const std::vector<double>& adjoint_bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung electron energy for an incoming electron energy
  void setAdjointElectronBremsstrahlungEnergyAtIncomingEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>& adjoint_electron_bremsstrahlung_energy );

  //! Set the bremsstrahlung pdf for an incoming electron energy
  void setAdjointElectronBremsstrahlungPDFAtIncomingEnergy(
    const double incoming_adjoint_energy,
    const std::vector<double>&  adjoint_electron_bremsstrahlung_pdf );

  //! Set the bremsstrahlung electron energy for electrons
  void setAdjointElectronBremsstrahlungEnergy(
    const std::map<double,std::vector<double> >&
    adjoint_electron_bremsstrahlung_energy );

  //! Set the bremsstrahlung pdf for electrons
  void setAdjointElectronBremsstrahlungPDF(
    const std::map<double,std::vector<double> >&
    adjoint_electron_bremsstrahlung_pdf );

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
  void setAdjointBremsstrahlungElectronCrossSection(
			 const std::vector<double>& adjoint_bremsstrahlung_cross_section );

  //! Set the bremsstrahlung electron cross section threshold energy bin index
  void setAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex(
                                const unsigned index );

  //! Set the atomic excitation electron cross section
  void setAdjointAtomicExcitationCrossSection(
			 const std::vector<double>& adjoint_atomic_excitation_cross_section );

  //! Set the atomic excitation cross section threshold energy bin index
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

  // The name used in archive name-value pairs
  static const std::string s_archive_name;

//---------------------------------------------------------------------------//
// NOTES
//---------------------------------------------------------------------------//

  // The table notes
  std::string d_notes;

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

  // The adjoint pair production energy dist norm constant evaluation tol
  double d_adjoint_pair_production_energy_dist_norm_constant_evaluation_tol;

  // The adjoint pair production energy dist norm constant nudge value
  double d_adjoint_pair_production_energy_dist_norm_constant_nudge_value;

  // The adjoint triplet production energy dist norm constant evaluation tol
  double d_adjoint_triplet_production_energy_dist_norm_constant_evaluation_tol;

  // The adjoint triplet production energy dist norm constant nudge value
  double d_adjoint_triplet_production_energy_dist_norm_constant_nudge_value;

  // The adjoint incoherent max energy nudge value
  double d_adjoint_incoherent_max_energy_nudge_value;

  // The adjoint incoherent energy to max energy nudge value
  double d_adjoint_incoherent_energy_to_max_energy_nudge_value;

  // The adjoint incoherent cross section evaluation tol
  double d_adjoint_incoherent_evaluation_tol;

  // The adjoint incoherent grid convergence tol
  double d_adjoint_incoherent_grid_convergence_tol;

  // The adjoint incoherent grid absolute difference tol
  double d_adjoint_incoherent_grid_absolute_diff_tol;

  // The adjoint incoherent grid distance tol
  double d_adjoint_incoherent_grid_distance_tol;  

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

  // The Compton profile momentum grids (me*c units)
  std::map<unsigned,std::vector<double> > d_compton_profile_momentum_grids;

  // The Compton profiles ((me*c)^-1 units)
  std::map<unsigned,std::vector<double> > d_compton_profiles;

  // The occupation number momentum grids (me*c units)
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

  // The Waller-Hartree squared atomic form factor squared mom. grid (1/cm^2)
  std::vector<double>
  d_waller_hartree_squared_atomic_form_factor_squared_momentum_grid;

  // The Waller-Hartree squared atomic form factor
  std::vector<double> d_waller_hartree_squared_atomic_form_factor;

  // The adjoint photon energy grid (MeV)
  std::vector<double> d_adjoint_photon_energy_grid;

  // The Waller-Hartree incoherent adjoint photon max energy grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_waller_hartree_incoherent_max_energy_grid;

  // The Waller-Hartree incoherent adjoint photon cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_waller_hartree_incoherent_cross_section;

  // The impulse approx. incoherent adjoint photon max energy grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_impulse_approx_incoherent_max_energy_grid;

  // The impulse approx. incoherent adjoint photon cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_impulse_approx_incoherent_cross_section;

  // The impulse approx. subshell incoh. adjoint photon max energy grid (MeV)
  std::map<unsigned,std::vector<std::vector<double> > >
  d_adjoint_impulse_approx_subshell_incoherent_max_energy_grids;

  // The impulse approx. subshell incoherent adjoint photon cross section (b)
  std::map<unsigned,std::vector<std::vector<double> > >
  d_adjoint_impulse_approx_subshell_incoherent_cross_sections;

  // The Waller-Hartree coherent cross section (b)
  std::vector<double> d_waller_hartree_coherent_cross_section;

  // The adjoint Waller-Hartree total max energy grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_waller_hatree_total_max_energy_grid;

  // The adjoint Waller-Hartree total cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_waller_hatree_total_cross_section;

  // The adjoint impulse approx. total max energ grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_impulse_approx_total_max_energy_grid;

  // The adjoint impulse approx. total cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_impulse_approx_total_cross_section;

  // The forward Waller-Hartree total cross section (b)
  std::vector<double> d_waller_hartree_total_cross_section;

  // The forward impulse approx. total cross section (b)
  std::vector<double> d_impulse_approx_total_cross_section;

  // The adjoint pair production energy distribution grid (MeV)
  std::vector<double> d_adjoint_pair_production_energy_distribution_grid;

  // The adjoint pair production energy distribution (b)
  std::vector<double> d_adjoint_pair_production_energy_distribution;

  // The adjoint pair production energy distribution norm constant grid (MeV)
  std::vector<double> d_adjoint_pair_production_norm_constant_grid;

  // The adjoint pair production energy distribution norm constant (b)
  std::vector<double> d_adjoint_pair_production_norm_constant;

  // The adjoint triplet production energy distribution grid (MeV)
  std::vector<double> d_adjoint_triplet_production_energy_distribution_grid;

  // The adjoint triplet production energy distribution (b)
  std::vector<double> d_adjoint_triplet_production_energy_distribution;

  // The adjoint triplet production energy distribution norm constant grid (MeV)
  std::vector<double> d_adjoint_triplet_production_norm_constant_grid;

  // The adjoint triplet production energy distribution norm constant (b)
  std::vector<double> d_adjoint_triplet_production_norm_constant;

  // The photon bremsstrahlung energy grid (MeV)
  std::vector<double> d_adjoint_photon_bremsstrahlung_energy_grid;

  // The photon bremsstrahlung energy
  std::map<double,std::vector<double> > d_adjoint_photon_bremsstrahlung_energy;

  // The photon bremsstrahlung pdf
  std::map<double,std::vector<double> > d_adjoint_photon_bremsstrahlung_pdf;

  // The bremsstrahlung photon cross section (b)
  std::vector<double> d_adjoint_bremsstrahlung_photon_cross_section;

  // The bremsstrahlung photon cross section threshold energy index
  unsigned d_adjoint_bremsstrahlung_photon_cross_section_threshold_index;

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

  // The electron bremsstrahlung energy grid (MeV)
  std::vector<double> d_adjoint_electron_bremsstrahlung_energy_grid;

  // The electron bremsstrahlung energy
  std::map<double,std::vector<double> > d_adjoint_electron_bremsstrahlung_energy;

  // The electron bremsstrahlung pdf
  std::map<double,std::vector<double> > d_adjoint_electron_bremsstrahlung_pdf;

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
  std::vector<double> d_adjoint_bremsstrahlung_electron_cross_section;

  // The bremsstrahlung electron cross section threshold energy index
  unsigned d_adjoint_bremsstrahlung_electron_cross_section_threshold_index;

  // The atomic excitation electron cross section (b)
  std::vector<double> d_adjoint_atomic_excitation_cross_section;

  // The atomic excitation electron cross section threshold energy index
  unsigned d_adjoint_atomic_excitation_cross_section_threshold_index;
};

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( AdjointElectronPhotonRelaxationDataContainer, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointElectronPhotonRelaxationDataContainer, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( AdjointElectronPhotonRelaxationDataContainer );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationDataContainer.hpp
//---------------------------------------------------------------------------//

