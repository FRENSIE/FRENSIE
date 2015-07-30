//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The single scattering elastic electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HARD_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_HARD_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
HardElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::HardElasticElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const HardElasticElectronScatteringDistribution>&
         scattering_distribution,
       const double cutoff_angle_cosine )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                    incoming_energy_grid,
                                                    cross_section,
                                                    threshold_energy_index ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index ),
    d_scattering_distribution( scattering_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
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
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );
}

// Return the cross section at the given energy
/*! The total elastic cross section is a combination of the distribution cross
 *! section and the normalized screened rutherford cross section.
 */
template<typename InterpPolicy, bool processed_cross_section>
double HardElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection( 
						    const double energy ) const
{
  double cross_section;
  
  double processed_energy = InterpPolicy::processIndepVar( energy );

  // cutoff between tabular distribution and screened Rutherford
  double rutherford_cutoff = 0.999999;

  // Get the ratio of the screened rutherford cross section to the distribution cross section
  double screened_rutherford_ratio;
  if ( rutherford_cutoff < d_cutoff_angle_cosine )
  {
std::cout << " d_cutoff_angle_cosine = " << d_cutoff_angle_cosine << std::endl;
std::cout << " rutherford_cutoff = " << rutherford_cutoff << std::endl;
    screened_rutherford_ratio =
      d_scattering_distribution->evaluateScreenedRutherfordCrossSectionRatio( 
                                        energy );
  }
  else
  {
    screened_rutherford_ratio = 0.0;
  }
  
  if( energy >= this->getThresholdEnergy() &&
      processed_energy < d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {
    unsigned energy_index = 
      Utility::Search::binaryLowerBoundIndex( d_incoming_energy_grid.begin(),
					      d_incoming_energy_grid.end(),
					      processed_energy );

    unsigned cs_index = energy_index - d_threshold_energy_index;

    double processed_slope = 
      (d_cross_section[cs_index+1]-d_cross_section[cs_index])/
      (d_incoming_energy_grid[energy_index+1]-
       d_incoming_energy_grid[energy_index]);

    cross_section = 
      InterpPolicy::interpolate( d_incoming_energy_grid[energy_index],
				 processed_energy,
				 d_cross_section[cs_index],
				 processed_slope );
  }
  else if( energy < this->getThresholdEnergy() )
    cross_section = 0.0;
  else if( processed_energy == d_incoming_energy_grid[d_incoming_energy_grid.size()-1] )
  {

    cross_section = InterpPolicy::recoverProcessedDepVar( 
        				   d_cross_section[d_cross_section.size()-1] );
  }
  else // energy > max_energy_grid_pt
    cross_section = 0.0;

  // The hard elastic cross section must be normalized for scattering below the cutoff angle cosine
  double cutoff_cdf = 
        d_scattering_distribution->evaluateCDF( energy, d_cutoff_angle_cosine);
    

  // Make sure the cross section is valid
  testPostcondition( cross_section >= 0.0 );
  testPostcondition( screened_rutherford_ratio >= 0.0 );
  testPostcondition( cutoff_cdf >= 0.0 );

  // Normalize the cross section to the screened rutherford and the cutoff angle cosine
  return cross_section*( 1.0 + screened_rutherford_ratio )*cutoff_cdf;
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned HardElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned HardElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType HardElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return HARD_ELASTIC_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void HardElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     ElectronState& electron, 
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterElectron( electron, 
                                              bank, 
                                              shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction = UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HARD_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
