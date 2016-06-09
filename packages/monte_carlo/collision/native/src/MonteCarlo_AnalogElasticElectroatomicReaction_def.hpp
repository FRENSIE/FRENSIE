//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The analog scattering elastic electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ANALOG_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ANALOG_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::AnalogElasticElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
         scattering_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                    incoming_energy_grid,
                                                    cross_section,
                                                    threshold_energy_index ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() ==
		    incoming_energy_grid.size() - threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure scattering distribution is valid
  testPrecondition( !scattering_distribution.is_null() );

  // Construct the grid searcher
  d_grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
			   incoming_energy_grid,
			   incoming_energy_grid[0],
			   incoming_energy_grid[incoming_energy_grid.size()-1],
			   incoming_energy_grid.size()/10+1 ) );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::AnalogElasticElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
         scattering_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                    incoming_energy_grid,
                                                    cross_section,
                                                    threshold_energy_index,
                                                    grid_searcher ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index ),
    d_grid_searcher( grid_searcher ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() ==
		    incoming_energy_grid.size() - threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure scattering distribution is valid
  testPrecondition( !scattering_distribution.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return CUTOFF_ELASTIC_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
				     ElectronState& electron,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterElectron( electron,
                                              bank,
                                              shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}


// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );

  // Get the cross section ratio for the cutoff angle
  double cross_section_ratio =
    d_scattering_distribution->evaluateCutoffCrossSectionRatio( energy );

  double cross_section;

  if( energy >= this->getThresholdEnergy() )
  {
    unsigned energy_index = d_grid_searcher->findLowerBinIndex( energy );

    unsigned cs_index = energy_index - d_threshold_energy_index;

    cross_section =
      InterpPolicy::interpolate( d_incoming_energy_grid[energy_index],
				 d_incoming_energy_grid[energy_index+1],
				 energy,
				 d_cross_section[cs_index],
				 d_cross_section[cs_index+1] );
  }
  else if( energy < this->getThresholdEnergy() )
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  // Make sure the cross section ratio is valid
  testPostcondition( cross_section_ratio >= 0.0 );
  testPostcondition( cross_section_ratio <= 1.0 );

  return cross_section*cross_section_ratio;
}

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
				const double energy,
                const unsigned bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( d_incoming_energy_grid[bin_index] <=
		    InterpPolicy::processIndepVar( energy ) );
  testPrecondition( d_incoming_energy_grid[bin_index+1] >=
		    InterpPolicy::processIndepVar( energy ) );

  // Get the cross section ratio for the cutoff angle
  double cross_section_ratio =
    d_scattering_distribution->evaluateCutoffCrossSectionRatio( energy );

  double cross_section;

  if( bin_index >= d_threshold_energy_index )
  {
    unsigned cs_index = bin_index - d_threshold_energy_index;

    double processed_slope =
      (d_cross_section[cs_index+1]-d_cross_section[cs_index])/
      (d_incoming_energy_grid[bin_index+1]-
       d_incoming_energy_grid[bin_index]);

    double processed_energy = InterpPolicy::processIndepVar( energy );

    cross_section =
        InterpPolicy::interpolate( d_incoming_energy_grid[bin_index],
				      processed_energy,
				      d_cross_section[cs_index],
				      processed_slope );
  }
  else
    cross_section = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );

  // Make sure the cross section ratio is valid
  testPostcondition( cross_section_ratio >= 0.0 );
  testPostcondition( cross_section_ratio <= 1.0 );

  return cross_section*cross_section_ratio;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ANALOG_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
