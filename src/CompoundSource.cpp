//---------------------------------------------------------------------------//
//!
//! \file   CompoundSource.cpp
//! \author Alex Robinson
//! \brief  Compound source class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "CompoundSource.hpp"
#include "ContractException.hpp"
#include "SearchAlgorithms.hpp"
#include "RandomNumberGenerator.hpp"

namespace FACEMC{

// Constructor
CompoundSource::CompoundSource( 
		  const Teuchos::Array<Teuchos::RCP<ParticleSource> >& sources,
		  const Teuchos::Array<double>& source_sampling_weights )
  : d_sources( sources.size() )
{
  // Make sure that every source has a sampling weight
  testPrecondition( sources.size() == source_sampling_weights.size() );

  // Create the array of sources
  double total_weight = 0.0;
  
  for( unsigned i = 0; i < sources.size(); ++i )
  {
    total_weight += source_sampling_weights[i];
    
    d_sources[i].first = sources[i];
    d_sources[i].second = total_weight;
    d_sources[i].third = 0;
  }

  // Normalize the CDF
  for( unsigned i = 0; i < sources.size(); ++i )
    d_sources[i].second /= total_weight;

  // Make sure that the CDF has been normalized correctly
  testPostcondition( d_sources.back().second == 1.0 );
}

// Sample a particle state from the source
void CompoundSource::sampleParticleState( ParticleBank& bank )
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  // Sample the source that will be sampled from
  Teuchos::Array<Trip<Teuchos::RCP<ParticleSource>,double,unsigned> >::iterator
    selected_source = Search::binaryUpperBound<SECOND>( d_sources.begin(),
							d_sources.end(),
							random_number );
  // Sample from the source
  selected_source->first->sampleParticleState( bank );
  
  // Increment the number of samples from the source
  ++(selected_source->third);  
}

// Return the sampling efficiency from the source
double CompoundSource::getSamplingEfficiency() const
{
  // Get the number of trials performed by each source
  unsigned trials = 0;
  unsigned samples = 0;

  for( unsigned i = 0; i < d_sources.size(); ++i )
  {
    trials += (unsigned)( d_sources[i].third/
			  d_sources[i].first->getSamplingEfficiency() );
    
    samples += d_sources[i].third;
  }

  return static_cast<double>( samples )/trials;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end CompoundSource.cpp
//---------------------------------------------------------------------------//
