//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardWeightCutoffRoulette.cpp
//! \author Luke Kersting
//! \brief  Standard weight cutoff roulette class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardWeightCutoffRoulette.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
StandardWeightCutoffRoulette::StandardWeightCutoffRoulette()
  : d_roulette_cutoff_weights()
{ /* ... */ }

// Set the roulette cutoff weights for the specified particle type
void StandardWeightCutoffRoulette::setCutoffWeights(
                                          const ParticleType particle_type,
                                          const WeightType& threshold_weight,
                                          const WeightType& survival_weight )
{
  RouletteCutoffWeightData& particle_roulette_weight_data =
    d_roulette_cutoff_weights[particle_type];

  Utility::get<0>( particle_roulette_weight_data ) = threshold_weight;
  Utility::get<1>( particle_roulette_weight_data ) = survival_weight;
}

// Return the roulette cutoff weights for the specified particle type
void StandardWeightCutoffRoulette::getCutoffWeights(
                                          const ParticleType particle_type,
                                          WeightType& threshold_weight,
                                          WeightType& survival_weight ) const
{
  ParticleTypeWeightCutoffRouletteMap::const_iterator particle_type_data_it =
    d_roulette_cutoff_weights.find( particle_type );

  threshold_weight = Utility::get<0>( particle_type_data_it->second );
  survival_weight = Utility::get<1>( particle_type_data_it->second );
}

// Return the particle types that will have weight cutoff rouletting
void StandardWeightCutoffRoulette::getParticleTypes(
                                 std::set<ParticleType>& particle_types ) const
{
  ParticleTypeWeightCutoffRouletteMap::const_iterator particle_type_data_it =
    d_roulette_cutoff_weights.begin();

  while( particle_type_data_it != d_roulette_cutoff_weights.end() )
  {
    particle_types.insert( particle_type_data_it->first );

    ++particle_type_data_it;
  }
}

// Roulette the particle weight based on the threshold and survival weights
/*! \details The survival probabilty of the particle is set to
 * 'particle weight'/'survival weight'. If the particle survives its new weight
 * is set to the 'survival weight'.
 */
void StandardWeightCutoffRoulette::rouletteParticleWeight( ParticleState& particle ) const
{
  ParticleTypeWeightCutoffRouletteMap::const_iterator particle_data_it =
    d_roulette_cutoff_weights.find( particle.getParticleType() );

  // Check if rouletting is set for the particle type
  if( particle_data_it != d_roulette_cutoff_weights.end() )
  {
    // Check if the particle's weight is below the threshold
    if( particle.getWeight() < Utility::get<0>( particle_data_it->second ) )
    {
      double survival_weight = Utility::get<1>( particle_data_it->second );
      double random_number =
        Utility::RandomNumberGenerator::getRandomNumber<double>();

      // Particle doesn't survive roulette (new weight = 0)
      if ( random_number > particle.getWeight()/survival_weight )
      {
        //particle.multiplyWeight( 0.0 ); // this is not necessary
        particle.setAsGone();
      }
      // Particle survive roulette (new weight = survival_weight)
      else
        particle.setWeight( survival_weight );
    }
  }
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( StandardWeightCutoffRoulette, MonteCarlo );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardWeightCutoffRoulette );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardWeightCutoffRoulette.cpp
//---------------------------------------------------------------------------//
