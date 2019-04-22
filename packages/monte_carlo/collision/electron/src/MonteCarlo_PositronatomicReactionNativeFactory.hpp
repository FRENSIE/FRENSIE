//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomicReactionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The positron-atomic reaction Native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_POSITRONATOMIC_REACTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
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

//! The positron-atomic reaction factory class that uses Native data
class PositronatomicReactionNativeFactory
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
  using ThisType = PositronatomicReactionNativeFactory;

  //! Create an coupled elastic scattering positron-atomic reaction
  template< typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = PositronatomicReaction>
  static void createCoupledElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol );

  //! Create a hybrid elastic scattering positron-atomic reaction
  template< typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = PositronatomicReaction>
  static void createHybridElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a decoupled elastic scattering positron-atomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = PositronatomicReaction>
  static void createDecoupledElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double evaluation_tol );

  //! Create an cutoff elastic scattering positron-atomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = PositronatomicReaction>
  static void createCutoffElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a screened Rutherford elastic scattering positron-atomic reaction
  static void createScreenedRutherfordElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const PositronatomicReaction>& elastic_reaction );

  //! Create the moment preserving elastic scattering positron-atomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogCosLog,
            template<typename> class TwoDGridPolicy = Utility::Correlated,
            typename ReactionType = PositronatomicReaction>
  static void createMomentPreservingElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create an atomic excitation scattering positron-atomic reaction
  static void createAtomicExcitationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const PositronatomicReaction>& atomic_excitation_reaction );

  //! Create the subshell electroionization positron-atomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated,
            typename ReactionType = PositronatomicReaction>
  static void createSubshellPositronionizationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const unsigned subshell,
    std::shared_ptr<const ReactionType>& electroionization_subshell_reaction,
    const ElectroionizationSamplingType sampling_type,
    const double evaluation_tol );

  //! Create the subshell electroionization positron-atomic reactions
  template< typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated,
            typename ReactionType = PositronatomicReaction>
  static void createSubshellPositronionizationReactions(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::vector<std::shared_ptr<const ReactionType> >&
        electroionization_subshell_reactions,
    const ElectroionizationSamplingType sampling_type,
    const double evaluation_tol );

  //! Create the bremsstrahlung positron-atomic reaction
  template< typename TwoDInterpPolicy = Utility::LogLogLog,
            template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated,
            typename ReactionType = PositronatomicReaction>
  static void createBremsstrahlungReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_positronatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const ReactionType>& bremsstrahlung_reaction,
    BremsstrahlungAngularDistributionType photon_distribution_function,
    const double evaluation_tol );

  //! Create a void absorption positron-atomic reaction
  static void createVoidAbsorptionReaction(
    std::shared_ptr<const PositronatomicReaction>& void_absorption_reaction );

private:

  // Constructor
  PositronatomicReactionNativeFactory();
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PositronatomicReactionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_POSITRONATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
