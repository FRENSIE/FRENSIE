//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Distributed source class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <numeric>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default Constructor
StandardParticleSource::StandardParticleSource()
  : ParticleSource()
{ /* ... */ }
  
// Constructor
StandardParticleSource::StandardParticleSource(
                  const std::vector<std::shared_ptr<ParticleSourceComponent> >&
                  source_components )
  : ParticleSource(),
    d_components( source_components ),
    d_component_sampling_dist()
{ 
  // Make sure that there is at least one source component
  testPrecondition( !source_components.empty() );

  double norm_const = 0.0;

  // Initialize the source component sampling dist
  std::vector<double> independent_values( source_components.size() ),
    dependent_values( source_components.size() );
  
  for( size_t i = 0; i < source_components.size(); ++i )
  {
    independent_values[i] = i;
    dependent_values[i] = source_components[i]->getSelectionWeight();
  }

  d_component_sampling_dist.reset( new Utility::DiscreteDistribution(
                                                          independent_values,
                                                          dependent_values ) );
}
  
// Enable thread support
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::enableThreadSupport( const size_t threads )
{
  for( size_t i = 0; i < d_components.size(); ++i )
    d_components[i]->enableThreadSupport( threads );
}

// Reset the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::resetData()
{
  for( size_t i = 0; i < d_components.size(); ++i )
    d_components[i]->resetData();
}

// Reduce the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::reduceData( const Utility::Communicator& comm,
                                         const int root_process )
{
  for( size_t i = 0; i < d_components.size(); ++i )
    d_components[i]->reduceData( comm, root_process );
}

// Print a summary of the source data
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::printSummary( std::ostream& os ) const
{
  for( size_t i = 0; i < d_components.size(); ++i )
  {
    d_components[i]->printSummary( os );
    os << "\n";
  }

  os << std::flush;
}

// Log a summary of the sampling statistics
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::logSummary() const
{
  for( size_t i = 0; i < d_components.size(); ++i )
    d_components[i]->logSummary();
}

// Sample a particle state from the source
/*! \details If MonteCarlo::ParticleSourceComponent::enableThreadSupport has 
 * been called, this method is thread-safe.
 */
void StandardParticleSource::sampleParticleState( ParticleBank& bank,
                                                  const unsigned long long history )
{
  // Sample the component that will be used to sample the particle state
  size_t component_index;

  d_component_sampling_dist->sampleAndRecordBinIndex( component_index );

  d_components[component_index]->sampleParticleState( bank, history );
}

// Get the number of components
/*! \details Only the master thread should call this method.
 */
size_t StandardParticleSource::getNumberOfComponents() const
{
  return d_components.size();
}

// Return the number of sampling trials
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfTrials() const -> Counter
{
  Counter trials = 0;

  for( size_t i = 0; i < d_components.size(); ++i )
    trials += d_components[i]->getNumberOfTrials();

  return trials;
}

// Return the number of samples that have been generate
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfSamples() const -> Counter
{
  Counter samples = 0;

  for( size_t i = 0; i < d_components.size(); ++i )
    samples += d_components[i]->getNumberOfSamples();

  return samples;
}

// Return the sampling efficiency from the source
/*! \details Only the master thread should call this method.
 */
double StandardParticleSource::getSamplingEfficiency() const
{
  Counter trials = this->getNumberOfTrials();
  Counter samples = this->getNumberOfSamples();

  if( trials > 0 )
    return static_cast<double>( samples )/trials;
  else
    return 1.0;
}

// Return the number of sampling trials in the phase space dimension
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionTrials(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  Counter trials = 0;

  for( size_t i = 0; i < d_components.size(); ++i )
    trials += d_components[i]->getNumberOfDimensionTrials( dimension );

  return trials;
}

// Return the number of samples in the phase space dimension
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionSamples(
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  Counter samples = 0;

  for( size_t i = 0; i < d_components.size(); ++i )
    samples += d_components[i]->getNumberOfDimensionSamples( dimension );

  return samples;
}

// Return the sampling efficiency in the phase space dimension
/*! \details Only the master thread should call this method.
 */
double StandardParticleSource::getDimensionSamplingEfficiency(
                                    const PhaseSpaceDimension dimension ) const
{
  Counter trials = this->getNumberOfDimensionTrials( dimension );
  Counter samples = this->getNumberOfDimensionSamples( dimension );

  if( trials > 0 )
    return static_cast<double>( samples )/trials;
  else
    return 1.0;
}

// Return the number of sampling trials
auto StandardParticleSource::getNumberOfTrials( const size_t component ) const -> Counter
{
  // Make sure that the component index is valid
  testPrecondition( component < d_components.size() );

  return d_components[component]->getNumberOfTrials();
}

// Return the number of samples that have been generated
auto StandardParticleSource::getNumberOfSamples( const size_t component ) const -> Counter
{
  // Make sure that the component index is valid
  testPrecondition( component < d_components.size() );

  return d_components[component]->getNumberOfSamples();
}

// Return the sampling efficiency from the source
double StandardParticleSource::getSamplingEfficiency( const size_t component ) const
{
  // Make sure that the component index is valid
  testPrecondition( component < d_components.size() );

  return d_components[component]->getSamplingEfficiency();
}

// Return the number of sampling trials in the phase space dimension for a component
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionTrials(
                         const size_t component,
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  // Make sure that the component index is valid
  testPrecondition( component < d_components.size() );

  return d_components[component]->getNumberOfDimensionTrials( dimension );
}

// Return the number of samples in the phase space dimension for a component
/*! \details Only the master thread should call this method.
 */
auto StandardParticleSource::getNumberOfDimensionSamples(
                         const size_t component,
                         const PhaseSpaceDimension dimension ) const -> Counter
{
  // Make sure that the component index is valid
  testPrecondition( component < d_components.size() );

  return d_components[component]->getNumberOfDimensionSamples( dimension );
}

// Return the sampling efficiency in the phase space dimension for a component
/*! \details Only the master thread should call this method.
 */
double StandardParticleSource::getDimensionSamplingEfficiency(
                                    const size_t component,
                                    const PhaseSpaceDimension dimension ) const
{
  // Make sure that the component index is valid
  testPrecondition( component < d_components.size() );

  return d_components[component]->getDimensionSamplingEfficiency( dimension );
}

// Return the starting cells that have been cached
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::getStartingCells( CellIdSet& starting_cells ) const
{
  for( size_t i = 0; i < d_components.size(); ++i )
    d_components[i]->getStartingCells( starting_cells );
}

// Return the starting cells that have been cached
/*! \details Only the master thread should call this method.
 */
void StandardParticleSource::getStartingCells( const size_t component,
                                               CellIdSet& starting_cells ) const
{
  // Make sure that the component index is valid
  testPrecondition( component < d_components.size() );
  
  d_components[component]->getStartingCells( starting_cells );
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardParticleSource );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::StandardParticleSource );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSource.cpp
//---------------------------------------------------------------------------//
