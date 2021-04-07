//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledElasticAdjointElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The decoupled scattering elastic electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::DecoupledElasticAdjointElectroatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& total_cross_section,
      const std::shared_ptr<const std::vector<double> >& sampling_ratios,
      const size_t threshold_energy_index,
      const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
            tabular_distribution,
      const std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
            analytical_distribution )
  : BaseType( incoming_energy_grid,
              total_cross_section,
              threshold_energy_index ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_threshold_energy_index( threshold_energy_index ),
    d_sampling_ratios( sampling_ratios ),
    d_tabular_distribution( tabular_distribution ),
    d_analytical_distribution( analytical_distribution )
{
  // Make sure the sampling ratio is valid
  testPrecondition( sampling_ratios->size() > 0 );
  // Make sure scattering distributions are valid
  testPrecondition( tabular_distribution.use_count() > 0 );
  testPrecondition( analytical_distribution.use_count() > 0 );

  // Construct the grid searcher
  d_grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<std::vector<double>,processed_cross_section>(
                                         incoming_energy_grid,
                                         incoming_energy_grid->front(),
                                         incoming_energy_grid->back(),
                                         incoming_energy_grid->size()/10+1 ) );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::DecoupledElasticAdjointElectroatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& total_cross_section,
      const std::shared_ptr<const std::vector<double> >& sampling_ratios,
      const size_t threshold_energy_index,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
            tabular_distribution,
      const std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
            analytical_distribution )
  : BaseType( incoming_energy_grid,
              total_cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_grid_searcher( grid_searcher ),
    d_threshold_energy_index( threshold_energy_index ),
    d_sampling_ratios( sampling_ratios ),
    d_tabular_distribution( tabular_distribution ),
    d_analytical_distribution( analytical_distribution )
{
  // Make sure the sampling ratio is valid
  testPrecondition( sampling_ratios->size() > 0 );
  // Make sure scattering distributions are valid
  testPrecondition( tabular_distribution.use_count() > 0 );
  testPrecondition( analytical_distribution.use_count() > 0 );
}

// Return the number of adjoint photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of adjoint electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointElectrons( const double energy ) const
{
  return 1u;
}

// Return the number of adjoint positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedAdjointPositrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
AdjointElectroatomicReactionType DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
}


// Return the sampling ratio at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getSamplingRatio( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );

  double sampling_ratio;

  if( energy >= this->getThresholdEnergy() )
  {
    unsigned energy_index = d_grid_searcher->findLowerBinIndex( energy );

    sampling_ratio = this->getCrossSectionImpl( *d_sampling_ratios,
                                                energy,
                                                energy_index );
  }
  else
    sampling_ratio = 0.0;

  // Make sure the sampling ratio is valid
  testPostcondition( sampling_ratio >= 0.0 );
  testPostcondition( sampling_ratio <= 1.0 );

  return sampling_ratio;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
double DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
            const double incoming_energy,
            const double scattering_angle_cosine ) const
{
  // Make sure the energy is valid
  testPostcondition( incoming_energy >= 0.0 );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );

  if( incoming_energy >= this->getThresholdEnergy() )
  {
    // Get the PDF
    double pdf;
    if( scattering_angle_cosine <= MonteCarlo::ElasticElectronTraits::mu_peak )
    {
      pdf = d_tabular_distribution->evaluatePDF( incoming_energy,
                                                 scattering_angle_cosine );
    }
    else
    {
      pdf = d_analytical_distribution->evaluatePDF( incoming_energy,
                                                    scattering_angle_cosine );
    }

    // Get the cross section
    double cross_section = this->getCrossSection( incoming_energy );

    return pdf*cross_section;
  }
  else
    return 0.0;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void DecoupledElasticAdjointElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
                     AdjointElectronState& electron,
                     ParticleBank& bank,
                     Data::SubshellType& shell_of_interaction ) const
{
  // Get a random number
  double random_number =
            Utility::RandomNumberGenerator::getRandomNumber<double>();

  if( random_number < this->getSamplingRatio( electron.getEnergy() ) )
  {
    // Sample the tabular cutoff distribution
    d_tabular_distribution->scatterAdjointElectron( electron,
                                                    bank,
                                                    shell_of_interaction);
  }
  else
  {
    // Sample the analytical screened Rutherford Distribution
    d_analytical_distribution->scatterAdjointElectron( electron,
                                                       bank,
                                                       shell_of_interaction);
  }

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledElasticAdjointElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
