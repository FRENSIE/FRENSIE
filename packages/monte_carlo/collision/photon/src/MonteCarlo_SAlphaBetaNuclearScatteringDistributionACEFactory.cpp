//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory_def.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  S(alpha,beta) nuclear scattering distribution factor base class template defs.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP
#define MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP

// Std Lib Includes
#include <sstream>
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp"
#include "MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ElasticNeutronNuclearScatteringDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Basic Constructor
SAlphaBetaNuclearScatteringDistributionACEFactory::
    SAlphaBetaNuclearScatteringDistributionACEFactory(
        const std::string& table_name, const double atomic_weight_ratio,
        const Data::XSSNeutronDataExtractor& raw_nuclide_data,
        const Data::XSSSabDataExtractor& sab_nuclide_data)
    : NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,
                                              MonteCarlo::NeutronState>(
          table_name, atomic_weight_ratio, raw_nuclide_data.extractMTRBlock(),
          raw_nuclide_data.extractTYRBlock(),
          raw_nuclide_data.extractLANDBlock(),
          raw_nuclide_data.extractANDBlock(),
          raw_nuclide_data.extractLDLWBlock(),
          raw_nuclide_data.extractDLWBlock()),
      d_table_name(table_name),
      d_atomic_weight_ratio(atomic_weight_ratio),
      d_sab_nuclide_data(sab_nuclide_data) {
  initialize(
      raw_nuclide_data.extractMTRBlock(), raw_nuclide_data.extractTYRBlock(),
      raw_nuclide_data.extractLANDBlock(), raw_nuclide_data.extractANDBlock(),
      raw_nuclide_data.extractLDLWBlock(), raw_nuclide_data.extractDLWBlock(),
      sab_nuclide_data.extractITIEBlock(), sab_nuclide_data.extractITXEBlock(),
      sab_nuclide_data.extractITCEBlock(), sab_nuclide_data.extractITCABlock());
}

// Constructor
/*! \details The ArrayView objects are based by value so that data extractor
 * class extract member functions can be used directly in the constructor. 
 * Passing by reference would not allow this to be done.
 */
SAlphaBetaNuclearScatteringDistributionACEFactory::
    SAlphaBetaNuclearScatteringDistributionACEFactory(
        const std::string& table_name, const double atomic_weight_ratio,
        const Utility::ArrayView<const double> mtr_block,
        const Utility::ArrayView<const double> tyr_block,
        const Utility::ArrayView<const double> land_block,
        const Utility::ArrayView<const double> and_block,
        const Utility::ArrayView<const double> ldlw_block,
        const Utility::ArrayView<const double> dlw_block,
        const Data::XSSSabDataExtractor& sab_nuclide_data)
    : NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,
                                              MonteCarlo::NeutronState>(
          table_name, atomic_weight_ratio, mtr_block, tyr_block, land_block,
          and_block, ldlw_block, dlw_block),
      d_table_name(table_name),
      d_atomic_weight_ratio(atomic_weight_ratio),
      d_sab_nuclide_data(sab_nuclide_data) {
  initialize(
      mtr_block, tyr_block, land_block, and_block, ldlw_block, dlw_block,
      sab_nuclide_data.extractITIEBlock(), sab_nuclide_data.extractITXEBlock(),
      sab_nuclide_data.extractITCEBlock(), sab_nuclide_data.extractITCABlock());
}

// Constructor (no TYR block)
/*! \details The ArrayView objects are based by value so that data extractor
 * class extract member functions can be used directly in the constructor.
 * Passing by reference would not allow this to be done. If the tyr block is
 * not given, all reactions are assumed to take place in the lab system and
 * the multiplicities are assumed to be one.
 */
SAlphaBetaNuclearScatteringDistributionACEFactory::
    SAlphaBetaNuclearScatteringDistributionACEFactory(
        const std::string& table_name, const double atomic_weight_ratio,
        const Utility::ArrayView<const double> mtr_block,
        const Utility::ArrayView<const double> land_block,
        const Utility::ArrayView<const double> and_block,
        const Utility::ArrayView<const double> ldlw_block,
        const Utility::ArrayView<const double> dlw_block,
        const Data::XSSSabDataExtractor& sab_nuclide_data)
    : NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,
                                              MonteCarlo::NeutronState>(
          table_name, atomic_weight_ratio, mtr_block, land_block, and_block,
          ldlw_block, dlw_block),
      d_table_name(table_name),
      d_atomic_weight_ratio(atomic_weight_ratio),
      d_sab_nuclide_data(sab_nuclide_data) {
  initialize(
      mtr_block, land_block, and_block, ldlw_block, dlw_block,
      sab_nuclide_data.extractITIEBlock(), sab_nuclide_data.extractITXEBlock(),
      sab_nuclide_data.extractITCEBlock(), sab_nuclide_data.extractITCABlock());
}

// Initialize the factory
void SAlphaBetaNuclearScatteringDistributionACEFactory::initialize(
    const Utility::ArrayView<const double> mtr_block,
    const Utility::ArrayView<const double> tyr_block,
    const Utility::ArrayView<const double> land_block,
    const Utility::ArrayView<const double> and_block,
    const Utility::ArrayView<const double> ldlw_block,
    const Utility::ArrayView<const double> dlw_block,
    const Utility::ArrayView<const double> itie_block,
    const Utility::ArrayView<const double> itxe_block,
    const Utility::ArrayView<const double> itce_block,
    const Utility::ArrayView<const double> itca_block) {
  // Initialize the parent distribution ACE factory
  NuclearScatteringDistributionACEFactory::initialize(
      mtr_block, tyr_block, land_block, and_block, ldlw_block, dlw_block);

  // Initialize the S(alpha,beta) distribution information
  initializeSAlphaBetaData(itie_block, itxe_block, itce_block, itca_block);
}

// Initialize the factory (no TYR block)
void SAlphaBetaNuclearScatteringDistributionACEFactory::initialize(
    const Utility::ArrayView<const double> mtr_block,
    const Utility::ArrayView<const double> land_block,
    const Utility::ArrayView<const double> and_block,
    const Utility::ArrayView<const double> ldlw_block,
    const Utility::ArrayView<const double> dlw_block,
    const Utility::ArrayView<const double> itie_block,
    const Utility::ArrayView<const double> itxe_block,
    const Utility::ArrayView<const double> itce_block,
    const Utility::ArrayView<const double> itca_block) {
  // Initialize the parent distribution ACE factory
  NuclearScatteringDistributionACEFactory::initialize(
      mtr_block, land_block, and_block, ldlw_block, dlw_block);

  // Initialize the S(alpha,beta) distribution information
  initializeSAlphaBetaData(itie_block, itxe_block, itce_block, itca_block);
}

// Initialize the S(alpha,beta) data
void SAlphaBetaNuclearScatteringDistributionACEFactory::
    initializeSAlphaBetaData(
        const Utility::ArrayView<const double> itie_block,
        const Utility::ArrayView<const double> itxe_block,
        const Utility::ArrayView<const double> itce_block,
        const Utility::ArrayView<const double> itca_block) {
  d_is_continuous_energy = d_sab_nuclide_data.isDataContinuousEnergy();

  // Initialize the inelastic data
  if (!itie_block.size() > 0 && !itxe_block.size() > 0) {
    // Assign the itxe_block to the member data

    d_itie_block = itie_block;
    d_itxe_block = itxe_block;

    // Set the inelastic data
    setInelasticSAlphaBetaEnergies();
    setInelasticSAlphaBetaDistributionLocators();
    setInelasticSAlphaBetaOutgoingEnergies();
  } else {
    THROW_EXCEPTION(
        std::runtime_error,
        "Error: the S(alpha,beta) nuclear "
        "scattering distribution factory was unable to find appropriate data. "
        "Please check that S(alpha,beta) treatment is desired and a valid file "
        "has been provided.");
  }

  // Initialize the elastic data
  if (!itce_block.size() > 0) {
    // Assign the itce_block to the member data
    d_itce_block = itce_block;

    setElasticSAlphaBetaEnergies();

    // Check if the elastic angular distributions are explicit
    if (!itca_block.size() > 0) {
      // Assign the itce_block to the member data
      d_itca_block = itca_block;

      setElasticSAlphaBetaCosines(true);
    } else {
      setElasticSAlphaBetaCosines(false);
    }
  }
}

// Set the inelastic S(alpha,beta) energies
void SAlphaBetaNuclearScatteringDistributionACEFactory::
    setInelasticSAlphaBetaEnergies() {
  d_inelastic_energies = d_sab_nuclide_data.extractInelasticEnergyGrid();
}

// Set the inelastic S(alpha,beta) distribution locators
void SAlphaBetaNuclearScatteringDistributionACEFactory::
    setInelasticSAlphaBetaDistributionLocators() {
  d_inelastic_distribution_locators =
      d_sab_nuclide_data.extractInelasticDistributionLocations();
}

// Set the inelastic S(alpha,beta) outgoing energies
void SAlphaBetaNuclearScatteringDistributionACEFactory::
    setInelasticSAlphaBetaOutgoingEnergies() {
  d_inelastic_outgoing_energies =
      d_sab_nuclide_data.extractNumberOfOutgoingEnergies();
}

// Set the inelastic S(alpha,beta) energies
void SAlphaBetaNuclearScatteringDistributionACEFactory::
    setElasticSAlphaBetaEnergies() {
  d_elastic_energies = d_sab_nuclide_data.extractElasticEnergyGrid();
}

void SAlphaBetaNuclearScatteringDistributionACEFactory::
    setElasticSAlphaBetaCosines(bool is_implicit_elastic) {
  d_is_implicit_elastic = is_implicit_elastic;
}

// Create S(alpha,beta) distributions
void SAlphaBetaNuclearScatteringDistributionACEFactory::
    createSAlphaBetaScatteringDistributions(
        const unsigned reaction_type,
        std::shared_ptr<DistributionType>& distribution) const {
  // Create the inelastic scattering distribution
  if (reaction_type == MonteCarlo::SALPHABETA_N__N_INELASTIC_REACTION) {
    NuclearScatteringEnergyDistributionACEFactory::createSAlphaBetaInelasticDistribution(
        d_atomic_weight_ratio, d_inelastic_energies,
        d_inelastic_distribution_locators, d_inelastic_outgoing_energies,
        d_itxe_block, d_is_continuous_energy, d_table_name, reaction_type,
        false, distribution);
  } else if (reaction_type == MonteCarlo::SALPHABETA_N__N_ELASTIC_REACTION) {
    std::shared_ptr<NuclearScatteringAngularDistribution> angular_distribution;

    if (d_is_implicit_elastic) {
      NuclearScatteringAngularDistributionACEFactory::
          createSAlphaBetaDistribution(d_elastic_energies, d_itca_block,
                                       angular_distribution);
    } else {
      NuclearScatteringAngularDistributionACEFactory::
          createSAlphaBetaIsotropicDistribution(d_elastic_energies,
                                                angular_distribution);
    }

    distribution.reset(new ElasticNeutronNuclearScatteringDistribution(
        d_atomic_weight_ratio, 0., angular_distribution));
  } else {
    THROW_EXCEPTION(
        std::runtime_error,
        "Error: The S(alpha,beta) scattering "
        "distribution ACE factory has found reaction type "
            << reaction_type
            << " which does not correspond to an S(alpha,beta) reaction.");
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory_def.hpp
//---------------------------------------------------------------------------//
