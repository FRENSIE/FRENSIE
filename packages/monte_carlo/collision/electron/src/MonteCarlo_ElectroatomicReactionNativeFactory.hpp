//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction Native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The electroatomic reaction factory class that uses Native data
class ElectroatomicReactionNativeFactory
{

public:

  // Typedef for the Elastic Distribution Factory
  using ElasticFactory = ElasticElectronScatteringDistributionNativeFactory;

  // Typedef for the Bremsstrahlung Distribution Factory
  using BremsstrahlungFactory =
    BremsstrahlungElectronScatteringDistributionNativeFactory;

  // Typedef for the Electroionization Subshell Distribution Factory
  using ElectroionizationFactory =
    ElectroionizationSubshellElectronScatteringDistributionNativeFactory;

  // Typedef for the Atomic Excitation Distribution Factory
  using ExcitationFactory =
    AtomicExcitationElectronScatteringDistributionNativeFactory;

  // Typedef for this type
  using ThisType = ElectroatomicReactionNativeFactory;

  //! Create an coupled elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = ElectroatomicReaction>
  static void createCoupledElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol );

  //! Create a hybrid elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = ElectroatomicReaction>
  static void createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a decoupled elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = ElectroatomicReaction>
  static void createDecoupledElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double evaluation_tol );

  //! Create an cutoff elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = ElectroatomicReaction>
  static void createCutoffElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a screened Rutherford elastic scattering electroatomic reaction
  static void createScreenedRutherfordElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ElectroatomicReaction>& elastic_reaction );

  //! Create the moment preserving elastic scattering electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = ElectroatomicReaction>
  static void createMomentPreservingElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create an atomic excitation scattering electroatomic reaction
  static void createAtomicExcitationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ElectroatomicReaction>& atomic_excitation_reaction );

  //! Create the subshell electroionization electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated,
            typename ReactionType = ElectroatomicReaction>
  static void createSubshellElectroionizationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const unsigned subshell,
    std::shared_ptr<const ReactionType>& electroionization_subshell_reaction,
    const ElectroionizationSamplingType sampling_type,
    const double evaluation_tol );

  //! Create the subshell electroionization electroatomic reactions
  template< typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated,
            typename ReactionType = ElectroatomicReaction>
  static void createSubshellElectroionizationReactions(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::vector<std::shared_ptr<const ReactionType> >&
        electroionization_subshell_reactions,
    const ElectroionizationSamplingType sampling_type,
    const double evaluation_tol );

  //! Create the bremsstrahlung electroatomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated,
            typename ReactionType = ElectroatomicReaction>
  static void createBremsstrahlungReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& bremsstrahlung_reaction,
    BremsstrahlungAngularDistributionType photon_distribution_function,
    const double evaluation_tol );

  //! Create a void absorption electroatomic reaction
  static void createVoidAbsorptionReaction(
    std::shared_ptr<const ElectroatomicReaction>& void_absorption_reaction );

private:

  // Constructor
  ElectroatomicReactionNativeFactory();
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroatomicReactionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
