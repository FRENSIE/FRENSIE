//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatomic reaction Native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_TwoDGridPolicy.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The adjoint electroatomic reaction factory class that uses Native data
class AdjointElectroatomicReactionNativeFactory
{

private:

  // Typedef for the Elastic Distribution Factory
  using ElasticFactory = ElasticElectronScatteringDistributionNativeFactory;

  // Typedef for the Bremsstrahlung Adjoint Distribution Factory
  using BremsstrahlungFactory =
    BremsstrahlungAdjointElectronScatteringDistributionNativeFactory;

  // Typedef for the Electroionization Subshell Adjoint Distribution Factory
  using ElectroionizationFactory =
    ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory;

  // Typedef for this type
  using ThisType = AdjointElectroatomicReactionNativeFactory;

public:

  //! Create an coupled elastic scattering adjoint electroatomic reaction
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createCoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol );

  //! Create an coupled elastic scattering adjoint electroatomic reaction
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createDecoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction,
    const double evaluation_tol );

  //! Create a hybrid elastic scattering adjoint electroatomic reaction
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createHybridElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create an cutoff elastic scattering adjoint electroatomic reaction
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createCutoffElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a screened Rutherford elastic scattering adjoint electroatomic reaction
  static void createScreenedRutherfordElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction );

  //! Create the moment preserving elastic scattering adjoint electroatomic reaction
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createMomentPreservingElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& elastic_reaction,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create an atomic excitation scattering adjoint electroatomic reaction
  static void createAtomicExcitationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& atomic_excitation_reaction,
    const std::shared_ptr<const std::vector<double> >& critical_line_energies );

  //! Create the subshell electroionization adjoint electroatomic reaction
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createSubshellElectroionizationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const unsigned subshell,
    std::shared_ptr<const AdjointElectroatomicReaction>& electroionization_subshell_reaction,
    const std::shared_ptr<const std::vector<double> >& critical_line_energies,
    const double evaluation_tol );

  //! Create the subshell electroionization adjoint electroatomic reactions
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createSubshellElectroionizationReactions(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::vector<std::shared_ptr<const AdjointElectroatomicReaction> >&
        electroionization_subshell_reactions,
    const std::shared_ptr<const std::vector<double> >& critical_line_energies,
    const double evaluation_tol );

  //! Create the bremsstrahlung adjoint electroatomic reaction
  template<typename TwoDInterpPolicy = Utility::LogLogLog,
           template<typename> class TwoDGridPolicy = Utility::UnitBaseCorrelated>
  static void createBremsstrahlungReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer&
        raw_adjoint_electroatom_data,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    std::shared_ptr<const AdjointElectroatomicReaction>& bremsstrahlung_reaction,
    const std::shared_ptr<const std::vector<double> >& critical_line_energies,
    const double evaluation_tol );

  //! Create the forward total reaction (only used to get the cross section)
  static void createTotalForwardReaction(
        const std::vector<std::vector<double> >& forward_inelastic_cross_section,
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        const std::function<double (const double&)> forward_elastic_xs_evaluator,
        std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction );
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
