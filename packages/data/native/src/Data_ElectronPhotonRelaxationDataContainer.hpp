//---------------------------------------------------------------------------//
//!
//! \file   Data_ElectronPhotonRelaxationDataContainer.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The native electron-photon-relaxation data container class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP
#define DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

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
class ElectronPhotonRelaxationDataContainer : public Utility::ArchivableObject<ElectronPhotonRelaxationDataContainer>
{
  // The base type
  typedef Utility::ArchivableObject<ElectronPhotonRelaxationDataContainer> BaseType;

public:

  //! Constructor (from saved archive)
  ElectronPhotonRelaxationDataContainer(
                          const boost::filesystem::path& file_name_with_path );

  //! Destructor
  virtual ~ElectronPhotonRelaxationDataContainer()
  { /* ... */ }

  //! The database name used in an archive
  const char* getArchiveName() const override;

//---------------------------------------------------------------------------//
// GET NOTES
//---------------------------------------------------------------------------//

  //! Data table notes
  const std::string& getNotes() const;

//---------------------------------------------------------------------------//
// GET TABLE DATA
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

  //! Return the occupation number evaluation tolerance
  double getOccupationNumberEvaluationTolerance() const;

  //! Return the subshell incoherent evaluation tolerance
  double getSubshellIncoherentEvaluationTolerance() const;

  //! Return the photon threshold energy nudge factor
  double getPhotonThresholdEnergyNudgeFactor() const;

  //! Return the upper cutoff scattering angle cosine above which moment preserving elastic scattering is used
  double getCutoffAngleCosine() const;

  //! Return the number of discrete moment preserving angles
  unsigned getNumberOfMomentPreservingAngles() const;

  //! Return the electron FullyTabularTwoDDistribution evaluation tolerance
  double getElectronTabularEvaluationTolerance() const;

  //! Return the photon union energy grid convergence tolerance
  double getPhotonGridConvergenceTolerance() const;

  //! Return the photon union energy grid absolute difference tolerance
  double getPhotonGridAbsoluteDifferenceTolerance() const;

  //! Return the photon union energy grid distance tolerance
  double getPhotonGridDistanceTolerance() const;

  //! Return the electron union energy grid convergence tolerance
  double getElectronGridConvergenceTolerance() const;

  //! Return the electron union energy grid absolute difference tolerance
  double getElectronGridAbsoluteDifferenceTolerance() const;

  //! Return the electron union energy grid distance tolerance
  double getElectronGridDistanceTolerance() const;

  //! Return the bremsstrahlung cross section evaluation tolerance
  double getBremsstrahlungEvaluationTolerance() const;

  //! Return the bremsstrahlung grid convergence tolerance
  double getBremsstrahlungGridConvergenceTolerance() const;

  //! Return the bremsstrahlung absolute difference tolerance
  double getBremsstrahlungAbsoluteDifferenceTolerance() const;

  //! Return the bremsstrahlung distance tolerance
  double getBremsstrahlungDistanceTolerance() const;

  //! Return the electroionization cross section evaluation tolerance
  double getElectroionizationEvaluationTolerance() const;

  //! Return the electroionization grid convergence tolerance
  double getElectroionizationGridConvergenceTolerance() const;

  //! Return the electroionization absolute difference tolerance
  double getElectroionizationAbsoluteDifferenceTolerance() const;

  //! Return the electroionization distance tolerance
  double getElectroionizationDistanceTolerance() const;

//---------------------------------------------------------------------------//
// GET RELAXATION DATA
//---------------------------------------------------------------------------//

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

  //! Return the photon energy grid
  const std::vector<double>& getPhotonEnergyGrid() const;

  //! Check if there are average heating numbers
  bool hasAveragePhotonHeatingNumbers() const;

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

  //! Return the triplet production cross section
  const std::vector<double>&
  getTripletProductionCrossSection() const;

  //! Return the triple production cross section threshold energy bin index
  unsigned getTripletProductionCrossSectionThresholdEnergyIndex() const;

  //! Return the Photoelectric effect cross section
  const std::vector<double>& getPhotoelectricCrossSection() const;

  //! Return the Photoelectric effect cross section threshold energy bin index
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


//---------------------------------------------------------------------------//
// GET ELECTRON DATA
//---------------------------------------------------------------------------//

  //! Return the electron TwoDInterpPolicy
  const std::string& getElectronTwoDInterpPolicy() const;

  //! Return the electron TwoDGridPolicy
  const std::string& getElectronTwoDGridPolicy() const;

  //! Return the elastic angular energy grid
  const std::vector<double>& getElasticAngularEnergyGrid() const;

  //! Return the cutoff elastic scattering interpolation policy
  const std::string& getCutoffElasticInterpPolicy() const;

  //! Return the map of the cutoff elastic scattering angles
  const std::map<double,std::vector<double> >& getCutoffElasticAngles() const;

  //! Return the map of the cutoff elastic scattering pdf
  const std::map<double,std::vector<double> >& getCutoffElasticPDF() const;

  //! Return the cutoff elastic scattering angles for an incoming energy
  const std::vector<double>& getCutoffElasticAngles(
                    const double incoming_energy ) const;

  //! Return the cutoff elastic scattering pdf for an incoming energy
  const std::vector<double>& getCutoffElasticPDF(
                    const double incoming_energy ) const;

  //! Return if there is moment preserving data
  bool hasMomentPreservingData() const;

  //! Return the moment preserving cross section reductions
  const std::vector<double>& getMomentPreservingCrossSectionReduction() const;

  //! Return the moment preserving elastic discrete angles
  const std::map<double,std::vector<double> >&
    getMomentPreservingElasticDiscreteAngles() const;

  //! Return the moment preserving elastic weights
  const std::map<double,std::vector<double> >&
    getMomentPreservingElasticWeights() const;

  //! Return the moment preserving elastic discrete angles for an incoming energy
  const std::vector<double>& getMomentPreservingElasticDiscreteAngles(
                                const double incoming_energy ) const;

  //! Return the moment preserving elastic weights for an incoming energy
  const std::vector<double>& getMomentPreservingElasticWeights(
                                const double incoming_energy ) const;

  //! Return the electroionization energy grid for the recoil electron spectrum for a subshell
  const std::vector<double>& getElectroionizationEnergyGrid(
                                const unsigned subshell ) const;

  //! Return the electroionization recoil interpolation policy
  const std::string& getElectroionizationInterpPolicy() const;

  //! Return the electroionization recoil energy for a subshell
  const std::map<double,std::vector<double> >& getElectroionizationRecoilEnergy(
                                const unsigned subshell ) const;

  //! Return the electroionization recoil energy for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilEnergy(
                                const unsigned subshell,
                                const double incoming_energy ) const;

  //! Return the electroionization recoil energy pdf for a subshell
  const std::map<double,std::vector<double> >& getElectroionizationRecoilPDF(
                                const unsigned subshell ) const;

  //! Return the electroionization recoil energy pdf for a subshell and incoming energy
  const std::vector<double>& getElectroionizationRecoilPDF(
                                const unsigned subshell,
                                const double incoming_energy ) const;

  //! Return if there is electroionization outgoing energy data
  bool hasElectroionizationOutgoingEnergyData() const;

  //! Return the electroionization outgoing energy for a subshell
  const std::map<double,std::vector<double> >& getElectroionizationOutgoingEnergy(
                                const unsigned subshell ) const;

  //! Return the electroionization outgoing energy for a subshell and incoming energy
  const std::vector<double>& getElectroionizationOutgoingEnergy(
                                const unsigned subshell,
                                const double incoming_energy ) const;

  //! Return the electroionization outgoing energy pdf for a subshell
  const std::map<double,std::vector<double> >& getElectroionizationOutgoingPDF(
                                const unsigned subshell ) const;

  //! Return the electroionization outgoing energy pdf for a subshell and incoming energy
  const std::vector<double>& getElectroionizationOutgoingPDF(
                                const unsigned subshell,
                                const double incoming_energy ) const;

  //! Return the bremsstrahlung energy grid for the secondary photon spectrum
  const std::vector<double>& getBremsstrahlungEnergyGrid() const;

  //! Return the bremsstrahlung photon interpolation policy
  const std::string& getBremsstrahlungPhotonInterpPolicy() const;

  //! Return the bremsstrahlung photon energy
  const std::map<double,std::vector<double> >& getBremsstrahlungPhotonEnergy() const;

  //! Return the bremsstrahlung photon energy for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonEnergy(
                                const double incoming_energy ) const;

  //! Return the bremsstrahlung photon energy pdf
  const std::map<double,std::vector<double> >& getBremsstrahlungPhotonPDF() const;

  //! Return the bremsstrahlung photon energy pdf for an incoming energy
  const std::vector<double>& getBremsstrahlungPhotonPDF(
                                const double incoming_energy ) const;

  //! Return the atomic excitation average energy loss energy grid
  const std::vector<double>& getAtomicExcitationEnergyGrid() const;

  //! Return the atomic excitation average energy loss interpolation policy
  const std::string& getAtomicExcitationEnergyLossInterpPolicy() const;

  //! Return the atomic excitation average energy loss
  const std::vector<double>& getAtomicExcitationEnergyLoss() const;

  //! Return the electron energy grid
  const std::vector<double>& getElectronEnergyGrid() const;

  //! Return the electron cross section interpolation policy
  const std::string& getElectronCrossSectionInterpPolicy() const;

  //! Return the total electron cross section
  const std::vector<double>& getTotalElectronCrossSection() const;

  //! Return the elastic electron cross section below mu = 0.999999
  const std::vector<double>& getCutoffElasticCrossSection() const;

  //! Return the cutoff elastic cross section threshold energy bin index
  unsigned getCutoffElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the screened Rutherford elastic electron cross section
  const std::vector<double>& getScreenedRutherfordElasticCrossSection() const;

  //! Return the screened Rutherford elastic cross section threshold energy bin index
  unsigned getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the total elastic electron cross section
  const std::vector<double>& getTotalElasticCrossSection() const;

  //! Return the total elastic cross section threshold energy bin index
  unsigned getTotalElasticCrossSectionThresholdEnergyIndex() const;

  //! Return the electroionization electron cross section for a subshell
  const std::vector<double>&
    getElectroionizationCrossSection( const unsigned subshell ) const;

  //! Return the electroionization cross section threshold energy bin index for a subshell
  unsigned getElectroionizationCrossSectionThresholdEnergyIndex(
    const unsigned subshell ) const;

  //! Return the bremsstrahlung electron cross section
  const std::vector<double>& getBremsstrahlungCrossSection() const;

  //! Return the bremsstrahlung cross section threshold energy bin index
  unsigned getBremsstrahlungCrossSectionThresholdEnergyIndex() const;

  //! Return the atomic excitation electron cross section
  const std::vector<double>& getAtomicExcitationCrossSection() const;

  //! Return the atomic excitation cross section threshold energy bin index
  unsigned getAtomicExcitationCrossSectionThresholdEnergyIndex() const;

protected:

  //! Default constructor
  ElectronPhotonRelaxationDataContainer()
  { /* ... */ }

  //! Load the archived object (implementation)
  void loadFromFileImpl( const boost::filesystem::path& archive_name_with_path ) final override;

  //! Archive the object (implementation)
  void saveToFileImpl( const boost::filesystem::path& archive_name_with_path,
                       const bool overwrite ) const final override;

//---------------------------------------------------------------------------//
// SET NOTES
//---------------------------------------------------------------------------//

  //! Data table notes
  void setNotes( const std::string& notes );

//---------------------------------------------------------------------------//
// SET TABLE DATA
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

  //! Set the occupation number evaluation tolerance
  void setOccupationNumberEvaluationTolerance(
    const double occupation_number_evaluation_tolerance );

  //! Set the subshell incoherent evaluation tolerance
  void setSubshellIncoherentEvaluationTolerance(
    const double subshell_incoherent_evaluation_tolerance );

  //! Set the photon threshold energy nudge factor
  void setPhotonThresholdEnergyNudgeFactor( const double nudge_factor );

  //! Set the upper cutoff scattering angle below which moment preserving elastic scattering is used
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Set the number of discrete moment preserving angles
  void setNumberOfMomentPreservingAngles(
    const unsigned number_of_moment_preserving_angles);

  //! Set the electron FullyTabularTwoDDistribution evaluation tolerance
  void setElectronTabularEvaluationTolerance(
    const double electron_tabular_evaluation_tol );

  //! Set the photon union energy grid convergence tolerance
  void setPhotonGridConvergenceTolerance( const double grid_convergence_tol );

  //! Set the photon union energy grid absolute difference tolerance
  void setPhotonGridAbsoluteDifferenceTolerance( const double grid_absolute_diff_tol );

  //! Set the photon union energy grid distance tolerance
  void setPhotonGridDistanceTolerance( const double grid_distance_tol );

  //! Set the electron union energy grid convergence tolerance
  void setElectronGridConvergenceTolerance( const double grid_convergence_tol );

  //! Set the electron union energy grid absolute difference tolerance
  void setElectronGridAbsoluteDifferenceTolerance( const double grid_absolute_diff_tol );

  //! Set the electron union energy grid distance tolerance
  void setElectronGridDistanceTolerance( const double grid_distance_tol );

  //! Set the bremsstrahlung cross section evaluation tolerance
  void setBremsstrahlungEvaluationTolerance(
    const double evaluation_tolerance );

  //! Set the bremsstrahlung grid convergence tolerance
  void setBremsstrahlungGridConvergenceTolerance(
    const double convergence_tolerance );

  //! Set the bremsstrahlung absolute difference tolerance
  void setBremsstrahlungAbsoluteDifferenceTolerance(
    const double absolute_diff_tol );

  //! Set the bremsstrahlung distance tolerance
  void setBremsstrahlungDistanceTolerance( const double distance_tol );

  //! Set the electroionization cross section evaluation tolerance
  void setElectroionizationEvaluationTolerance(
    const double evaluation_tol );

  //! Set the electroionization grid convergence tolerance
  void setElectroionizationGridConvergenceTolerance(
    const double convergence_tol );

  //! Set the electroionization absolute difference tolerance
  void setElectroionizationAbsoluteDifferenceTolerance(
    const double absolute_diff_tol );

  //! Set the electroionization distance tolerance
  void setElectroionizationDistanceTolerance( const double distance_tol );

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

//---------------------------------------------------------------------------//
// SET PHOTON DATA
//---------------------------------------------------------------------------//

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

  //! Return the Waller-Hartree squared atomic form factor squared mom. grid
  void setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
                            const std::vector<double>& squared_momentum_grid );

  //! Return the Waller-Hartree squared atomic form factor
  void setWallerHartreeSquaredAtomicFormFactor(
                       const std::vector<double>& squared_atomic_form_factor );

  //! Set the photon energy grid
  void setPhotonEnergyGrid( const std::vector<double>& energy_grid );

  //! Set that the container has average photon heating numbers
  void setHasAveragePhotonHeatingNumbers( const bool has_heating_numbers );

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

  //! Set the triplet production cross section
  void setTripletProductionCrossSection(
                 const std::vector<double>& triplet_production_cross_section );

  //! Set the triplet production cross section threshold energy bin index
  void setTripletProductionCrossSectionThresholdEnergyIndex(
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

//---------------------------------------------------------------------------//
// SET ELECTRON DATA
//---------------------------------------------------------------------------//

  //! Set the electronTwoDInterpPolicy
  void setElectronTwoDInterpPolicy( const std::string& electron_two_d_interp );

  //! Set the electronTwoDGridPolicy
  void setElectronTwoDGridPolicy( const std::string& electron_two_d_grid );

  //! Set the elastic angular energy grid
  void setElasticAngularEnergyGrid(
    const std::vector<double>& angular_energy_grid );

  //! Set the cutoff elastic InterpPolicy
  void setCutoffElasticInterpPolicy( const std::string& cutoff_elastic_interp );

  //! Set the elastic scattering angles for an incoming energy
  void setCutoffElasticAnglesAtEnergy(
    const double incoming_energy,
    const std::vector<double>& elastic_angles );

  //! Set the elastic scattering pdf for an incoming energy
  void setCutoffElasticPDFAtEnergy(
    const double incoming_energy,
    const std::vector<double>& elastic_pdf );

  //! Set the elastic scattering angles
  void setCutoffElasticAngles(
    const std::map<double,std::vector<double> >& elastic_angles );

  //! Set the elastic scattering pdf
  void setCutoffElasticPDF(
    const std::map<double,std::vector<double> >& elastic_pdf );

//  //! Set the screened Rutherford elastic normalization constant
//  void setScreenedRutherfordNormalizationConstant(
//    const std::vector<double>& screened_rutherford_normalization_constant );

//  //! Set Moliere's screening constant
//  void setMoliereScreeningConstant(
//    const std::vector<double>& moliere_screening_constant );

  //! Clear all the moment preserving data
  void clearMomentPreservingData();

  //! Set the moment preserving cross section reduction
  void setMomentPreservingCrossSectionReduction(
    const std::vector<double>& cross_section_reduction );

  //! Set the moment preserving elastic discrete angles
  void setMomentPreservingElasticDiscreteAngles(
    const std::map<double,std::vector<double> >& moment_preserving_elastic_discrete_angles);

  //! Set the moment preserving elastic weights
  void setMomentPreservingElasticWeights(
    const std::map<double,std::vector<double> >& moment_preserving_elastic_weights );

  //! Set the moment preserving elastic discrete angles for an incoming energy
  void setMomentPreservingElasticDiscreteAngles(
    const double incoming_energy,
    const std::vector<double>& moment_preserving_elastic_discrete_angles );

  //! Set the moment preserving elastic weights for an incoming energy
  void setMomentPreservingElasticWeights(
    const double incoming_energy,
    const std::vector<double>& moment_preserving_elastic_weights );

  //! Set the electroionization energy grid for the recoil electron spectrum
  void setElectroionizationEnergyGrid(
    const unsigned subshell,
    const std::vector<double>& electroionization_energy_grid );

  //! Set the electroionization InterpPolicy
  void setElectroionizationInterpPolicy(
    const std::string& electroionization_interp );

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

  //! Set the electroionization outgoing energy for an incoming energy and subshell
  void setElectroionizationOutgoingEnergyAtIncomingEnergy(
    const unsigned subshell,
    const double incoming_energy,
    const std::vector<double>& electroionization_outgoing_energy );

  //! Set the electroionization outgoing energy pdf for an incoming energy and subshell
  void setElectroionizationOutgoingPDFAtIncomingEnergy(
    const unsigned subshell,
    const double incoming_energy,
    const std::vector<double>& electroionization_outgoing_pdf );

  //! Set electroionization outgoing energy for all incoming energies in a subshell
  void setElectroionizationOutgoingEnergy(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_outgoing_energy );

  //! Set electroionization outgoing energy pdf for all incoming energies in a subshell
  void setElectroionizationOutgoingPDF(
    const unsigned subshell,
    const std::map<double,std::vector<double> >& electroionization_outgoing_pdf );

  //! Set the bremsstrahlung energy grid for the secondary photon spectrum
  void setBremsstrahlungEnergyGrid(
    const std::vector<double>& bremsstrahlung_energy_grid );

  //! Set the bremsstrahlung photon InterpPolicy
  void setBremsstrahlungPhotonInterpPolicy(
    const std::string& bremsstrahlung_photon_interp );

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

  //! Set the atomic excitation average energy loss InterpPolicy
  void setAtomicExcitationEnergyLossInterpPolicy(
    const std::string& atomic_excitation_energy_loss_interp );

  //! Set the atomic excitation average energy loss
  void setAtomicExcitationEnergyLoss(
            const std::vector<double>& atomic_excitation_energy_loss );

  //! Set the electron energy grid
  void setElectronEnergyGrid( const std::vector<double>& energy_grid );

  //! Set the electron cross section interpolation policy
  void setElectronCrossSectionInterpPolicy(
    const std::string& electron_cross_section_interp );

  //! Set the total electron electron cross section
  void setTotalElectronCrossSection(
    const std::vector<double>& total_electron_cross_section );

  //! Set the elastic electron cross section below mu = 0.999999
  void setCutoffElasticCrossSection(
    const std::vector<double>& cutoff_elastic_cross_section );

  //! Set the elastic cutoff cross section threshold energy bin index
  void setCutoffElasticCrossSectionThresholdEnergyIndex( const unsigned index );

  //! Set the screened Rutherford elastic electron cross section
  void setScreenedRutherfordElasticCrossSection(
    const std::vector<double>& total_elastic_cross_section );

  //! Set the screened Rutherford elastic cross section threshold energy bin index
  void setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex( const unsigned index );

  //! Set the total elastic electron cross section
  void setTotalElasticCrossSection(
    const std::vector<double>& total_elastic_cross_section );

  //! Set the total elastic cross section threshold energy bin index
  void setTotalElasticCrossSectionThresholdEnergyIndex( const unsigned index );

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

  // The occupation number evaluation tolerance
  double d_occupation_number_evaluation_tolerance;

  // The subshell incoherent evaluation tolerance
  double d_subshell_incoherent_evaluation_tolerance;

  // The photon threshold energy nudge factor
  double d_photon_threshold_energy_nudge_factor;

  // The elastic cutoff angle
  double d_cutoff_angle_cosine;

  // The number of discrete moment preserving angles
  double d_number_of_moment_preserving_angles;

  // The electron FullyTabularTwoDDistribution evaluation tolerance
  double d_electron_tabular_evaluation_tol;

  // The photon union energy grid convergence tolerance
  double d_photon_grid_convergence_tol;

  // The photon union energy grid absolute difference tolerance
  double d_photon_grid_absolute_diff_tol;

  // The photon union energy grid distance tolerance
  double d_photon_grid_distance_tol;

  // The electron union energy grid convergence tolerance
  double d_electron_grid_convergence_tol;

  // The electron union energy grid absolute difference tolerance
  double d_electron_grid_absolute_diff_tol;

  // The electron union energy grid distance tolerance
  double d_electron_grid_distance_tol;

  // The bremsstrahlung cross section evaluation tolerance
  double d_bremsstrahlung_evaluation_tolerance;

  // The bremsstrahlung grid convergence tolerance
  double d_bremsstrahlung_convergence_tolerance;

  // The bremsstrahlung absolute difference tolerance
  double d_bremsstrahlung_absolute_diff_tol;

  // The bremsstrahlung distance tolerance
  double d_bremsstrahlung_distance_tol;

  // The electroionization cross section evaluation tolerance
  double d_electroionization_evaluation_tol;

  // The electroionization grid convergence tolerance
  double d_electroionization_convergence_tol;

  // The electroionization absolute difference tolerance
  double d_electroionization_absolute_diff_tol;

  // The electroionization distance tolerance
  double d_electroionization_distance_tol;

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

//---------------------------------------------------------------------------//
// PHOTON DATA
//---------------------------------------------------------------------------//

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

  // The Waller-Hartree squared atomic form factor squared mom. grid (1/cm^2)
  std::vector<double>
  d_waller_hartree_squared_atomic_form_factor_squared_momentum_grid;

  // The Waller-Hartree squared atomic form factor
  std::vector<double> d_waller_hartree_squared_atomic_form_factor;

  // The photon energy grid (MeV)
  std::vector<double> d_photon_energy_grid;

  // There are average heating numbers
  bool d_has_average_photon_heating_numbers;

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

  // The impulse approx. subshell incoherent photon cross section thresh. indices
  std::map<unsigned,unsigned>
  d_impulse_approx_subshell_incoherent_cross_section_threshold_indices;

  // The Waller-Hartree coherent cross section (b)
  std::vector<double> d_waller_hartree_coherent_cross_section;

  // The Waller-Hartree coherent cross section threshold energy index
  unsigned d_waller_hartree_coherent_cross_section_threshold_index;

  // The pair production cross section (b)
  std::vector<double> d_pair_production_cross_section;

  // The pair production cross section threshold energy index
  unsigned d_pair_production_cross_section_threshold_index;

  // The triplet production cross section (b)
  std::vector<double> d_triplet_production_cross_section;

  // The triplet production cross section threshold energy index
  unsigned d_triplet_production_cross_section_threshold_index;

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


//---------------------------------------------------------------------------//
// ELECTRON DATA
//---------------------------------------------------------------------------//

  // The electron TwoDInterpPolicy
  std::string d_electron_two_d_interp;

  // The electron TwoDGridPolicy
  std::string d_electron_two_d_grid;

  // The elastic angular energy grid (MeV)
  std::vector<double> d_angular_energy_grid;

  // The cutoff elastic scattering InterpPolicy
  std::string d_cutoff_elastic_interp;

  // The cutoff elastic scattering angles
  std::map<double,std::vector<double> > d_cutoff_elastic_angles;

  // The cutoff elastic scattering pdf
  std::map<double,std::vector<double> > d_cutoff_elastic_pdf;

  // The moment preserving elastic discrete angles
  std::map<double,std::vector<double> > d_moment_preserving_elastic_discrete_angles;

  // The moment preserving elastic weights
  std::map<double,std::vector<double> > d_moment_preserving_elastic_weights;

  // The moment preserving cross section reductions
  std::vector<double> d_moment_preserving_cross_section_reductions;

  // The electroionization energy grid (MeV) for a subshell
  std::map<unsigned,std::vector<double> > d_electroionization_energy_grid;

  // The electroionization InterpPolicy
  std::string d_electroionization_interp;

  // The electroionization recoil energy for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_recoil_energy;

  // The electroionization recoil pdf for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_recoil_pdf;

  // The electroionization outgoing energy for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_outgoing_energy;

  // The electroionization outgoing energy pdf for subshell and incoming energy
  std::map<unsigned,std::map<double,std::vector<double> > >
    d_electroionization_outgoing_pdf;

  // The bremsstrahlung energy grid (MeV)
  std::vector<double> d_bremsstrahlung_energy_grid;

  // The bremsstrahlung photon InterpPolicy
  std::string d_bremsstrahlung_photon_interp;

  // The bremsstrahlung photon energy
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_energy;

  // The bremsstrahlung photon pdf
  std::map<double,std::vector<double> > d_bremsstrahlung_photon_pdf;

  // The atomic excitation energy grid (MeV)
  std::vector<double> d_atomic_excitation_energy_grid;

  // The atomic excitation energy loss InterpPolicy
  std::string d_atomic_excitation_energy_loss_interp;

  // The atomic excitation energy loss
  std::vector<double> d_atomic_excitation_energy_loss;

  // The electron energy grid (MeV)
  std::vector<double> d_electron_energy_grid;

  // The electron cross section InterpPolicy
  std::string d_electron_cross_section_interp;

  // The total electron electron cross section (b)
  std::vector<double> d_total_electron_cross_section;

  // The cutoff elastic electron cross section (b)
  std::vector<double> d_cutoff_elastic_cross_section;

  // The cutoff elastic electron cross section threshold energy index
  unsigned d_cutoff_elastic_cross_section_threshold_index;

  // The screened rutherford elastic electron cross section (b)
  std::vector<double> d_screened_rutherford_elastic_cross_section;

  // The screened rutherford elastic electron cross section threshold energy index
  unsigned d_screened_rutherford_elastic_cross_section_threshold_index;

  // The total elastic electron cross section (b)
  std::vector<double> d_total_elastic_cross_section;

  // The total elastic electron cross section threshold energy index
  unsigned d_total_elastic_cross_section_threshold_index;

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

BOOST_SERIALIZATION_CLASS_VERSION( ElectronPhotonRelaxationDataContainer, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ElectronPhotonRelaxationDataContainer, Data );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, ElectronPhotonRelaxationDataContainer );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Data_ElectronPhotonRelaxationDataContainer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_ELECTRON_PHOTON_RELAXATION_DATA_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_ElectronPhotonRelaxationDataContainer.hpp
//---------------------------------------------------------------------------//

