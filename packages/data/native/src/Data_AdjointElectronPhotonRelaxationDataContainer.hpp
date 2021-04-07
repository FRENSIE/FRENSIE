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
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ArchivableObject.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

/*! The electron-photon-relaxation data container
 * \details Linear-linear interpolation should be used for all data.
 */
class AdjointElectronPhotonRelaxationDataContainer : public Utility::ArchivableObject<AdjointElectronPhotonRelaxationDataContainer>
{
  // The base type
  typedef Utility::ArchivableObject<AdjointElectronPhotonRelaxationDataContainer> BaseType;

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
// GET BASIC TABLE DATA
//---------------------------------------------------------------------------//

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the atomic weight
  double getAtomicWeight() const;

  //! Return the minimum photon energy
  double getMinPhotonEnergy() const;

  //! Return the maximum photon energy
  double getMaxPhotonEnergy() const;

  //! Return the minimum electron energy
  double getMinElectronEnergy() const;

  //! Return the maximum electron energy
  double getMaxElectronEnergy() const;

//---------------------------------------------------------------------------//
// GET PHOTON TABLE DATA
//---------------------------------------------------------------------------//

  //! Return the adjoint photon grid convergence tolerance
  double getAdjointPhotonGridConvergenceTolerance() const;

  //! Return the adjoint photon grid absolute diff tolerance
  double getAdjointPhotonGridAbsoluteDifferenceTolerance() const;

  //! Return the adjoint photon grid distance tolerance
  double getAdjointPhotonGridDistanceTolerance() const;

  //! Return the adjoint photon threshold energy nudge factor
  double getAdjointPhotonThresholdEnergyNudgeFactor() const;

  //! Return the photon FullyTabularTwoDDistribution evaluation tolerance
  double getAdjointPhotonTabularEvaluationTolerance() const;

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

//---------------------------------------------------------------------------//
// GET ELECTRON TABLE DATA
//---------------------------------------------------------------------------//

  //! Return the upper cutoff scattering angle cosine above which moment preserving elastic scattering is used
  double getCutoffAngleCosine() const;

  //! Return the number of discrete moment preserving angles
  unsigned getNumberOfAdjointMomentPreservingAngles() const;

  //! Return the adjoint electron grid convergence tolerance
  double getAdjointElectronGridConvergenceTolerance() const;

  //! Return the adjoint electron grid absolute diff tolerance
  double getAdjointElectronGridAbsoluteDifferenceTolerance() const;

  //! Return the adjoint electron grid distance tolerance
  double getAdjointElectronGridDistanceTolerance() const;

  //! Return the electron FullyTabularTwoDDistribution evaluation tolerance
  double getElectronTabularEvaluationTolerance() const;

  //! Return the adjoint bremsstrahlung min energy nudge value
  double getAdjointBremsstrahlungMinEnergyNudgeValue() const;

  //! Return the adjoint bremsstrahlung max energy nudge value
  double getAdjointBremsstrahlungMaxEnergyNudgeValue() const;

  //! Return the adjoint bremsstrahlung cross section evaluation tolerance
  double getAdjointBremsstrahlungEvaluationTolerance() const;

  //! Return the adjoint bremsstrahlung grid convergence tolerance
  double getAdjointBremsstrahlungGridConvergenceTolerance() const;

  //! Return the adjoint bremsstrahlung absolute difference tolerance
  double getAdjointBremsstrahlungAbsoluteDifferenceTolerance() const;

  //! Return the adjoint bremsstrahlung distance tolerance
  double getAdjointBremsstrahlungDistanceTolerance() const;

  //! Return the adjoint electroionization min energy nudge value
  double getAdjointElectroionizationMinEnergyNudgeValue() const;

  //! Return the adjoint electroionization max energy nudge value
  double getAdjointElectroionizationMaxEnergyNudgeValue() const;

  //! Return the adjoint electroionization cross section evaluation tolerance
  double getAdjointElectroionizationEvaluationTolerance() const;

  //! Return the adjoint electroionization grid convergence tolerance
  double getAdjointElectroionizationGridConvergenceTolerance() const;

  //! Return the adjoint electroionization absolute difference tolerance
  double getAdjointElectroionizationAbsoluteDifferenceTolerance() const;

  //! Return the adjoint electroionization distance tolerance
  double getAdjointElectroionizationDistanceTolerance() const;

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

  //! Return the adjoint impulse approx. (IA) incoherent photon cross section threshold energy bin index
  unsigned getAdjointImpulseApproxIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the adjoint Doppler broadened impulse approx. (IA) incoherent photon max energy grid
  const std::vector<std::vector<double> >&
  getAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid() const;

  //! Return the adjoint Doppler broadened impulse approx. (IA) incoherent photon cross section
  const std::vector<std::vector<double> >&
  getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection() const;

  //! Return the adjoint Doppler broadened impulse approx. (IA) incoherent photon cross section threshold energy index
  unsigned getAdjointDopplerBroadenedImpulseApproxIncoherentCrossSectionThresholdEnergyIndex() const;

  //! Return the subshell adjoint impulse approx. (IA) incoh. max energy grid
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                                               const unsigned subshell ) const;

  //! Return the subshell adjoint impulse approx. (IA) incoherent photon cs
  const std::vector<std::vector<double> >&
  getAdjointImpulseApproxSubshellIncoherentCrossSection(
                                               const unsigned subshell ) const;

  //! Return the subshell adjoint impulse approx. (IA) incoherent cross section threshod energy bin index
  unsigned getAdjointImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( const unsigned subshell ) const;

  //! Return the subshell adjoint Doppler broadened impulse approx. (IA) incoh. max energy grid
  const std::vector<std::vector<double> >&
  getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(
                                               const unsigned subshell ) const;

  //! Return the subshell adjoint Doppler broadened impulse approx. (IA) incoherent photon cs
  const std::vector<std::vector<double> >&
  getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(
                                               const unsigned subshell ) const;

  //! Return the subshell adjoint Doppler broadened impulse approx. (IA) incoherent cross section threshod energy bin index
  unsigned getAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( const unsigned subshell ) const;

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

  //! Return the adjoint Doppler broadened impulse approx. (IA) total max energy grid
  const std::vector<std::vector<double> >&
  getAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid() const;

  //! Return the adjoint Doppler broadened impulse approx. (IA) total cross section
  const std::vector<std::vector<double> >&
  getAdjointDopplerBroadenedImpulseApproxTotalCrossSection() const;

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

  //! Return the electron TwoDInterpPolicy
  const std::string& getElectronTwoDInterpPolicy() const;

  //! Return the electron TwoDGridPolicy
  const std::string& getElectronTwoDGridPolicy() const;

  //! Return the elastic angular energy grid
  const std::vector<double>& getAdjointElasticAngularEnergyGrid() const;

  //! Return the map of the cutoff elastic scattering angles
  const std::map<double,std::vector<double> >& getAdjointCutoffElasticAngles() const;

  //! Return the map of the cutoff elastic scattering pdf
  const std::map<double,std::vector<double> >& getAdjointCutoffElasticPDF() const;

  //! Return the cutoff elastic scattering angles for an incoming energy
  const std::vector<double>& getAdjointCutoffElasticAngles(
                           const double incoming_adjoint_energy ) const;

  //! Return the cutoff elastic scattering pdf for an incoming energy
  const std::vector<double>& getAdjointCutoffElasticPDF(
                           const double incoming_adjoint_energy ) const;

  //! Return if there is moment preserving data
  bool hasAdjointMomentPreservingData() const;

  //! Return the moment preserving cross section reductions
  const std::vector<double>& getAdjointMomentPreservingCrossSectionReduction() const;

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

  //! Return the forward electroionization sampling mode
  const std::string&
  getForwardElectroionizationSamplingMode() const;

  //! Return the electroionization energy grid for the recoil electron spectrum for a subshell
  const std::vector<double>& getAdjointElectroionizationEnergyGrid(
                           const unsigned subshell ) const;

  //! Return if there is a separate electroionization incoming electron energy grid for the scattering spectrum
  bool separateAdjointElectroionizationEnergyGrid() const;

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

  //! Return if there is a separate bremsstrahlung incoming electron energy grid for the scattering spectrum
  bool separateAdjointBremsstrahlungEnergyGrid() const;

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

  //! Return the forward bremsstrahlung electron cross section
  const std::vector<double>& getForwardBremsstrahlungElectronCrossSection() const;

  //! Return the forward bremsstrahlung electron cross section threshold energy bin index
  unsigned getForwardBremsstrahlungElectronCrossSectionThresholdEnergyIndex() const;

  //! Return the forward electroionization electron cross section
  const std::vector<double>& getForwardElectroionizationElectronCrossSection() const;

  //! Return the forward electroionization electron cross section threshold energy bin index
  unsigned getForwardElectroionizationElectronCrossSectionThresholdEnergyIndex() const;

  //! Return the forward atomic excitation electron cross section
  const std::vector<double>& getForwardAtomicExcitationElectronCrossSection() const;

  //! Return the forward atomic excitation electron cross section threshold energy bin index
  unsigned getForwardAtomicExcitationElectronCrossSectionThresholdEnergyIndex() const;

protected:

  //! Default constructor
  AdjointElectronPhotonRelaxationDataContainer()
  { /* ... */ }

  //! Load the archived object (implementation)
  void loadFromFileImpl( const boost::filesystem::path& archive_name_with_path ) final override;

  //! Archive the object (implementation)
  void saveToFileImpl( const boost::filesystem::path& archive_name_with_path,
                       const bool overwrite ) const final override;

//---------------------------------------------------------------------------//
// SET NOTES
//---------------------------------------------------------------------------//

  //! Set the table notes
  void setNotes( const std::string& notes );

//---------------------------------------------------------------------------//
// SET BASIC TABLE DATA
//---------------------------------------------------------------------------//

  //! Set the atomic number
  void setAtomicNumber( const unsigned atomic_number );

  //! Set the atomic weight
  void setAtomicWeight( const double atomic_weight );

  //! Set the minimum photon energy
  void setMinPhotonEnergy( const double min_photon_energy );

  //! Set the maximum photon energy
  void setMaxPhotonEnergy( const double max_photon_energy );

  //! Set the minimum electron energy
  void setMinElectronEnergy( const double min_electron_energy );

  //! Set the maximum electron energy
  void setMaxElectronEnergy( const double max_electron_energy );

//---------------------------------------------------------------------------//
// SET PHOTON TABLE DATA
//---------------------------------------------------------------------------//

  //! Set the adjoint photon grid convergence tolerance
  void setAdjointPhotonGridConvergenceTolerance( const double grid_convergence_tol );

  //! Set the adjoint photon grid absolute difference tolerance
  void setAdjointPhotonGridAbsoluteDifferenceTolerance( const double grid_absolute_diff_tol );

  //! Set the adjoint photon grid distance tolerance
  void setAdjointPhotonGridDistanceTolerance( const double grid_distance_tol );

  //! Set the adjoint photon threshold energy nudge factor
  void setAdjointPhotonThresholdEnergyNudgeFactor( const double nudge_factor );

  //! Set the photon FullyTabularTwoDDistribution evaluation tolerance
  void setAdjointPhotonTabularEvaluationTolerance( const double evaluation_tol );

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

//---------------------------------------------------------------------------//
// SET ELECTRON TABLE DATA
//---------------------------------------------------------------------------//

  //! Set the upper cutoff scattering angle below which moment preserving elastic scattering is used
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Set the number of discrete moment preserving angles
  void setNumberOfAdjointMomentPreservingAngles(
    const unsigned number_of_moment_preserving_angles );

  //! Set the adjoint electron grid convergence tolerance
  void setAdjointElectronGridConvergenceTolerance(
    const double grid_convergence_tol );

  //! Set the adjoint electron absolute diff tolerance
  void setAdjointElectronGridAbsoluteDifferenceTolerance(
    const double absolute_diff_tol );

  //! Set the adjoint electron distance tolerance
  void setAdjointElectronGridDistanceTolerance( const double distance_tol );

  //! Set the electron FullyTabularTwoDDistribution evaluation tolerance
  void setElectronTabularEvaluationTolerance( const double evaluation_tol );

  //! Set the adjoint bremsstrahlung min energy nudge value
  void setAdjointBremsstrahlungMinEnergyNudgeValue(
    const double min_energy_nudge_value );

  //! Set the adjoint bremsstrahlung max energy nudge value
  void setAdjointBremsstrahlungMaxEnergyNudgeValue(
    const double max_energy_nudge_value );

  //! Set the adjoint bremsstrahlung cross section evaluation tolerance
  void setAdjointBremsstrahlungEvaluationTolerance(
    const double evaluation_tolerance );

  //! Set the adjoint bremsstrahlung grid convergence tolerance
  void setAdjointBremsstrahlungGridConvergenceTolerance(
    const double convergence_tolerance );

  //! Set the adjoint bremsstrahlung absolute difference tolerance
  void setAdjointBremsstrahlungAbsoluteDifferenceTolerance(
    const double absolute_diff_tol );

  //! Set the adjoint bremsstrahlung distance tolerance
  void setAdjointBremsstrahlungDistanceTolerance( const double distance_tol );

  //! Set the adjoint electroionization min energy nudge value
  void setAdjointElectroionizationMinEnergyNudgeValue(
    const double min_energy_nudge_value );

  //! Set the adjoint electroionization max energy nudge value
  void setAdjointElectroionizationMaxEnergyNudgeValue(
    const double max_energy_nudge_value );

  //! Set the adjoint electroionization cross section evaluation tolerance
  void setAdjointElectroionizationEvaluationTolerance(
    const double evaluation_tol );

  //! Set the adjoint electroionization grid convergence tolerance
  void setAdjointElectroionizationGridConvergenceTolerance(
    const double convergence_tol );

  //! Set the adjoint electroionization absolute difference tolerance
  void setAdjointElectroionizationAbsoluteDifferenceTolerance(
    const double absolute_diff_tol );

  //! Set the adjoint electroionization distance tolerance
  void setAdjointElectroionizationDistanceTolerance( const double distance_tol );

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

  //! Set the adjoint impulse approx. (IA) incoherent photon cross section threshold energy bin index
  void setAdjointImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
                                                        const unsigned index );

  //! Set the adjoint Doppler broadened impulse approx. (IA) incoherent photon max energy grid
  void setAdjointDopplerBroadenedImpulseApproxIncoherentMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid );

  //! Set the adjoint Doppler broadened impulse approx. (IA) incoherent photon cross section
  void setAdjointDopplerBroadenedImpulseApproxIncoherentCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section );

  //! Set the adjoint Doppler broadened impulse approx. (IA) incoherent photon cross section threshold energy bin index
  void setAdjointDopplerBroadenedImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
                                                        const unsigned index );

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

  //! Set the subshell adjoint IA incoherent photon cross section threshold energy bin index
  void setAdjointImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
                                                       const unsigned subshell,
                                                       const unsigned index );

  //! Set the subshell adjoint Doppler broadened IA incoherent photon max energy grid
  void setAdjointDopplerBroadenedImpulseApproxSubshellIncoherentMaxEnergyGrid(
                                       const unsigned subshell,
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_max_energy_grid );

  //! Set the subshell adjoint Doppler broadened IA incoherent photon cross section
  void setAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSection(
                                       const unsigned subshell,
                                       const std::vector<std::vector<double> >&
                                       adjoint_incoherent_cross_section );

  //! Set the subshell adjoint Doppler broadened IA incoherent photon cross section threshold energy bin index
  void setAdjointDopplerBroadenedImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
                                                       const unsigned subshell,
                                                       const unsigned index );

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

  //! Set the adjoint Doppler broadened impulse approx. (IA) total max energy grid
  void setAdjointDopplerBroadenedImpulseApproxTotalMaxEnergyGrid(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_max_energy_grid );

  //! Set the adjoint Doppler broadened impulse approx. (IA) total cross section
  void setAdjointDopplerBroadenedImpulseApproxTotalCrossSection(
                                       const std::vector<std::vector<double> >&
                                       adjoint_total_cross_section );

  //! Set the (forward) Waller-Hartree total cross section
  void setWallerHartreeTotalCrossSection(
                              const std::vector<double>& total_cross_section );

  //! Set the (forward) impulse approx. total cross section
  void setImpulseApproxTotalCrossSection(
                              const std::vector<double>& total_cross_section );

  //! Set the adjoint pair production energy distribution grid
  void setAdjointPairProductionEnergyDistributionGrid(
          const std::vector<double>& adjoint_pair_production_energy_dist_grid );

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
          const std::vector<double>& adjoint_triplet_production_energy_dist_grid );

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

  //! Set the electron TwoDInterpPolicy
  void setElectronTwoDInterpPolicy( const std::string& electron_two_d_interp );

  //! Set the electron TwoDGridPolicy
  void setElectronTwoDGridPolicy( const std::string& electron_two_d_grid );

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

  //! Set the adjoint moment preserving cross section reduction
  void setAdjointMomentPreservingCrossSectionReduction(
    const std::vector<double>& adjoint_cross_section_reduction );

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

  //! Set the forward electroionization sampling mode
  void setForwardElectroionizationSamplingMode( const std::string sampling_mode );

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

  //! Set the forward bremsstrahlung electron cross section
  void setForwardBremsstrahlungElectronCrossSection(
           const std::vector<double>& forward_inelastic_electron_cross_section );

  //! Set the forward bremsstrahlung electron cross section threshold energy bin index
  void setForwardBremsstrahlungElectronCrossSectionThresholdEnergyIndex(
                                const unsigned index );

  //! Set the forward electroionization electron cross section
  void setForwardElectroionizationElectronCrossSection(
           const std::vector<double>& forward_inelastic_electron_cross_section );

  //! Set the forward electroionization electron cross section threshold energy bin index
  void setForwardElectroionizationElectronCrossSectionThresholdEnergyIndex(
                                const unsigned index );

  //! Set the forward atomic excitation electron cross section
  void setForwardAtomicExcitationElectronCrossSection(
           const std::vector<double>& forward_inelastic_electron_cross_section );

  //! Set the forward atomic excitation electron cross section threshold energy bin index
  void setForwardAtomicExcitationElectronCrossSectionThresholdEnergyIndex(
                                const unsigned index );

private:

  // Test if the Electroionization Sampling Mode is valid
  bool isElectroionizationSamplingModeValid( const std::string value );

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
// BASIC TABLE DATA
//---------------------------------------------------------------------------//

  // The atomic number
  unsigned d_atomic_number;

  // The atomic weight
  double d_atomic_weight;

  // The minimum photon energy
  double d_min_photon_energy;

  // The maximum photon energy
  double d_max_photon_energy;

  // The minimum electron energy
  double d_min_electron_energy;

  // The maximum electron energy
  double d_max_electron_energy;

//---------------------------------------------------------------------------//
// PHOTON TABLE DATA
//---------------------------------------------------------------------------//

  // The adjoint photon grid convergence tolerance
  double d_adjoint_photon_grid_convergence_tol;

  // The adjoint photon grid absolute difference tolerance
  double d_adjoint_photon_grid_absolute_diff_tol;

  // The adjoint photon grid distance tolerance
  double d_adjoint_photon_grid_distance_tol;

  // The adjoint photon threshold energy nudge factor
  double d_adjoint_photon_threshold_energy_nudge_factor;

  // The adjoint photon FullyTabularTwoDDistribution evaluation tolerance
  double d_adjoint_photon_tabular_evaluation_tol;

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

//---------------------------------------------------------------------------//
// ELECTRON TABLE DATA
//---------------------------------------------------------------------------//

  // The elastic cutoff angle
  double d_cutoff_angle_cosine;

  // The number of discrete moment preserving angles
  double d_number_of_adjoint_moment_preserving_angles;

  // The adjoint electron grid convergence tolerance
  double d_adjoint_electron_grid_convergence_tol;

  // The adjoint electron grid absolute diff tolerance
  double d_adjoint_electron_grid_absolute_diff_tol;

  // The adjoint electron grid distance tolerance
  double d_adjoint_electron_grid_distance_tol;

  // The electron FullyTabularTwoDDistribution evaluation tolerance
  double d_electron_tabular_evaluation_tol;

  // The adjoint bremsstrahlung min energy nudge value
  double d_adjoint_bremsstrahlung_min_energy_nudge_value;

  // The adjoint bremsstrahlung max energy nudge value
  double d_adjoint_bremsstrahlung_max_energy_nudge_value;

  // The adjoint bremsstrahlung cross section evaluation tolerance
  double d_adjoint_bremsstrahlung_evaluation_tolerance;

  // The adjoint bremsstrahlung grid convergence tolerance
  double d_adjoint_bremsstrahlung_convergence_tolerance;

  // The adjoint bremsstrahlung absolute difference tolerance
  double d_adjoint_bremsstrahlung_absolute_diff_tol;

  // The adjoint bremsstrahlung distance tolerance
  double d_adjoint_bremsstrahlung_distance_tol;

  // The adjoint electroionization min energy nudge value
  double d_adjoint_electroionization_min_energy_nudge_value;

  // The adjoint electroionization max energy nudge value
  double d_adjoint_electroionization_max_energy_nudge_value;

  // The adjoint electroionization cross section evaluation tolerance
  double d_adjoint_electroionization_evaluation_tol;

  // The adjoint electroionization grid convergence tolerance
  double d_adjoint_electroionization_convergence_tol;

  // The adjoint electroionization absolute difference tolerance
  double d_adjoint_electroionization_absolute_diff_tol;

  // The adjoint electroionization distance tolerance
  double d_adjoint_electroionization_distance_tol;

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

  // The impulse approx. incoherent adjoint photon cross section threshold energy bin index
  unsigned d_adjoint_impulse_approx_incoherent_cross_section_threshold_index;

  // The Doppler broadened impulse approx. incoherent adjoint photon max energy grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_doppler_broadened_impulse_approx_incoherent_max_energy_grid;

  // The Doppler broadened impulse approx. incoherent adjoint photon cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_doppler_broadened_impulse_approx_incoherent_cross_section;

  // The Doppler broadened impulse approx. incoherent adjoint photon cross section threshold energy bin index
  unsigned d_adjoint_doppler_broadened_impulse_approx_incoherent_cross_section_threshold_index;

  // The impulse approx. subshell incoh. adjoint photon max energy grid (MeV)
  std::map<unsigned,std::vector<std::vector<double> > >
  d_adjoint_impulse_approx_subshell_incoherent_max_energy_grids;

  // The impulse approx. subshell incoherent adjoint photon cross section (b)
  std::map<unsigned,std::vector<std::vector<double> > >
  d_adjoint_impulse_approx_subshell_incoherent_cross_sections;

  // The impulse approx. subshell incoherent adjoint photon cross section threshold energy bin indices
  std::map<unsigned,unsigned> d_adjoint_impulse_approx_subshell_incoherent_cross_section_threshold_indices;

  // The Doppler broadened impulse approx. subshell incoh. adjoint photon max energy grid (MeV)
  std::map<unsigned,std::vector<std::vector<double> > >
  d_adjoint_doppler_broadened_impulse_approx_subshell_incoherent_max_energy_grids;

  // The Doppler broadened impulse approx. subshell incoherent adjoint photon cross section (b)
  std::map<unsigned,std::vector<std::vector<double> > >
  d_adjoint_doppler_broadened_impulse_approx_subshell_incoherent_cross_sections;

  // The Doppler broadened impulse approx. subshell incoherent adjoint photon cross section threshold energy bin indices
  std::map<unsigned,unsigned> d_adjoint_doppler_broadened_impulse_approx_subshell_incoherent_cross_section_threshold_indices;

  // The Waller-Hartree coherent cross section (b)
  std::vector<double> d_waller_hartree_coherent_cross_section;

  // The adjoint Waller-Hartree total max energy grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_waller_hatree_total_max_energy_grid;

  // The adjoint Waller-Hartree total cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_waller_hatree_total_cross_section;

  // The adjoint impulse approx. total max energy grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_impulse_approx_total_max_energy_grid;

  // The adjoint impulse approx. total cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_impulse_approx_total_cross_section;

  // The adjoint Doppler broadened impulse approx. total max energy grid (MeV)
  std::vector<std::vector<double> >
  d_adjoint_doppler_broadened_impulse_approx_total_max_energy_grid;

  // The adjoint impulse approx. total cross section (b)
  std::vector<std::vector<double> >
  d_adjoint_doppler_broadened_impulse_approx_total_cross_section;

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

  // The electron TwoDInterpPolicy
  std::string d_electron_two_d_interp;

  // The electron TwoDGridPolicy
  std::string d_electron_two_d_grid;

  // The elastic angular energy grid (MeV)
  std::vector<double> d_adjoint_angular_energy_grid;

  // The cutoff elastic scattering angles
  std::map<double,std::vector<double> > d_adjoint_cutoff_elastic_angles;

  // The cutoff elastic scattering pdf
  std::map<double,std::vector<double> > d_adjoint_cutoff_elastic_pdf;

  // The moment preserving cross section reductions
  std::vector<double> d_adjoint_moment_preserving_cross_section_reductions;

  // The moment preserving elastic discrete angles
  std::map<double,std::vector<double> > d_adjoint_moment_preserving_elastic_discrete_angles;

  // The moment preserving elastic weights
  std::map<double,std::vector<double> > d_adjoint_moment_preserving_elastic_weights;

  // The forward electroionization sampling mode
  std::string d_forward_electroionization_sampling_mode;

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

  // The forward bremsstrahlung electron cross section (b)
  std::vector<double> d_forward_bremsstrahlung_electron_cross_section;

  // The forward bremsstrahlung electron cross section threshold energy index
  unsigned d_forward_bremsstrahlung_electron_cross_section_threshold_index;

  // The forward electroionization electron cross section (b)
  std::vector<double> d_forward_electroionization_electron_cross_section;

  // The forward electroionization electron cross section threshold energy index
  unsigned d_forward_electroionization_electron_cross_section_threshold_index;

  // The forward atomic excitation electron cross section (b)
  std::vector<double> d_forward_atomic_excitation_electron_cross_section;

  // The forward atomic excitation electron cross section threshold energy index
  unsigned d_forward_atomic_excitation_electron_cross_section_threshold_index;

};

} // end Data namespace

BOOST_SERIALIZATION_CLASS_VERSION( AdjointElectronPhotonRelaxationDataContainer, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( AdjointElectronPhotonRelaxationDataContainer, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, AdjointElectronPhotonRelaxationDataContainer );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_AdjointElectronPhotonRelaxationDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectronPhotonRelaxationDataContainer.hpp
//---------------------------------------------------------------------------//

