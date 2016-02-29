//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellPulseHeightEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP
#define MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename ContributionMultiplierPolicy>
CellPulseHeightEstimator<
                       ContributionMultiplierPolicy>::CellPulseHeightEstimator(
       const Estimator::idType id,
       const double multiplier,
       const Teuchos::Array<CellPulseHeightEstimator::cellIdType>& entity_ids )
  : EntityEstimator<cellIdType>( id, multiplier, entity_ids ),
    ParticleEnteringCellEventObserver(),
    ParticleLeavingCellEventObserver(),
    d_update_tracker( 1 ),
    d_dimension_values( 1 )
{ /* ... */ }

// Set the response functions
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<
                           ContributionMultiplierPolicy>::setResponseFunctions(
                      const Teuchos::Array<std::shared_ptr<ResponseFunction> >&
                      response_functions )
{
  std::cerr << "Warning: Response functions cannot be set for pulse height "
	    << "estimators. The response functions requested for pulse height "
	    << "estimator " << this->getId() << " will be ignored."
	    << std::endl;
}

// Set the particle types that can contribute to the estimator
/*! \details Only photons and electrons can contribute to this estimator
 */
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::setParticleTypes( 
			   const Teuchos::Array<ParticleType>& particle_types )
{
  Teuchos::Array<ParticleType> valid_particle_types;
  
  bool warning_issued = false;
  
  for( unsigned i = 0; i < particle_types.size(); ++i )
  {
    if( particle_types[i] != PHOTON )
    {
      if( !warning_issued )
      {
	std::cerr << "Warning: Only photons and charged particles can "
		  << "contribute to pulse height estimators. The other "
		  << "particle types requested for pulse height estimator "
		  << this->getId() << " will be ignored."
		  << std::endl;
      
	warning_issued = true;
      }
    }
    else
      valid_particle_types.push_back( particle_types[i] );
  }
  
  Estimator::setParticleTypes( valid_particle_types );

  testPostcondition( !this->isParticleTypeAssigned( NEUTRON ) );
  testPostcondition( !this->isParticleTypeAssigned( ADJOINT_NEUTRON ) );
  testPostcondition( !this->isParticleTypeAssigned( ADJOINT_PHOTON ) );
}

// Add current history estimator contribution
/*! \details It is unsafe to call this function directly! This function will
 * be called by the appropriate dispatcher when an event of interest occurs.
 * If calling this function directly, make sure that the cell of interest is
 * actually assigned to this estimator (otherwise segfaults are likely!).
 */
template<typename ContributionMultiplierPolicy>
inline void CellPulseHeightEstimator<
            ContributionMultiplierPolicy>::updateFromParticleEnteringCellEvent(
					       const ParticleState& particle,
					       const cellIdType cell_entering )
{
  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {    
    unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
    
    double contribution = particle.getWeight()*particle.getEnergy();
    
    addInfoToUpdateTracker( thread_id, cell_entering, contribution );
    
    // Indicate that there is an uncommitted history contribution
  this->setHasUncommittedHistoryContribution( thread_id );
  }
}

// Add current history estimator contribution
/*! \details It is unsafe to call this functio directly! This function will
 * be called by the appropriate dispatcher when an event of interest occurs.
 * If calling this function directly, make sure that the cell of interest is
 * actually assigned to this estimator (otherwise segfaults are likely! ).
 */
template<typename ContributionMultiplierPolicy>
inline void CellPulseHeightEstimator<
            ContributionMultiplierPolicy>::updateFromParticleLeavingCellEvent(
					        const ParticleState& particle,
					        const cellIdType cell_leaving )
{
  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {    
    unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
    
    double contribution = -particle.getWeight()*particle.getEnergy();

    addInfoToUpdateTracker( thread_id, cell_leaving, contribution );

    // Indicate that there is an uncommitted history contribution
    this->setHasUncommittedHistoryContribution( thread_id );
  }
}

// Add estimator contribution from a portion of the current history
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<
		     ContributionMultiplierPolicy>::commitHistoryContribution()
{
  unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
  
  typename SerialUpdateTracker::const_iterator 
    cell_data, end_cell_data;

  getCellIteratorFromUpdateTracker( thread_id, cell_data, end_cell_data );
  
  double energy_deposition_in_all_cells = 0.0;
  
  unsigned bin_index;
  double bin_contribution;

  Estimator::DimensionValueMap& thread_dimension_values = 
      d_dimension_values[thread_id];

  while( cell_data != end_cell_data )
  {        
    thread_dimension_values[ENERGY_DIMENSION] = 
      Teuchos::any( cell_data->second );
    
    if( this->isPointInEstimatorPhaseSpace( thread_dimension_values ) )
    {
      bin_index = this->calculateBinIndex( thread_dimension_values, 0u );
      
      bin_contribution = calculateHistoryContribution( 
					      cell_data->second,
					      ContributionMultiplierPolicy() );
      
      this->commitHistoryContributionToBinOfEntity( cell_data->first,
						    bin_index,
						    bin_contribution );
      
      // Add the energy deposition in this cell to the total energy deposition
      energy_deposition_in_all_cells += cell_data->second;
    }

    ++cell_data;
  }

  // Store the total energy deposition in the dimension values map
  thread_dimension_values[ENERGY_DIMENSION] = 
    Teuchos::any( energy_deposition_in_all_cells );
  
  // Determine the pulse bin for the combination of all cells
  if( this->isPointInEstimatorPhaseSpace( thread_dimension_values ) )
  {
    bin_index = this->calculateBinIndex( thread_dimension_values, 0u );

    bin_contribution = calculateHistoryContribution( 
					      energy_deposition_in_all_cells,
					      ContributionMultiplierPolicy() );

    this->commitHistoryContributionToBinOfTotal( bin_index,
						 bin_contribution );
  }

  // Reset the update tracker
  resetUpdateTracker( thread_id );

  // Reset the has uncommitted history contribution boolean
  this->unsetHasUncommittedHistoryContribution( thread_id );
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::printSummary( 
						       std::ostream& os ) const
{
  os << "Cell Pulse Height Estimator: " << this->getId() << std::endl;

  this->printImplementation( os, "Cell" );
}

// Enable support for multiple threads
template<typename ContributionMultiplierPolicy>
void 
CellPulseHeightEstimator<ContributionMultiplierPolicy>::enableThreadSupport(
						   const unsigned num_threads )
{
  EntityEstimator<Geometry::ModuleTraits::InternalCellHandle>::enableThreadSupport( num_threads );
  
  // Add thread support to update tracker
  d_update_tracker.resize( num_threads );

  // Add thread support to the dimension values
  d_dimension_values.resize( num_threads );
}

// Reset the estimator data
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::resetData()
{
  // Make sure only the root thread calls this
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  EntityEstimator<CellPulseHeightEstimator::cellIdType>::resetData();

  // Reset the update tracker
  for( unsigned i = 0; i < d_update_tracker.size(); ++i )
  {
    d_update_tracker[i].clear();
    
    this->unsetHasUncommittedHistoryContribution( i );
  }
}

// Export the estimator data
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const
{
  // Export the lower level data
  EntityEstimator<Geometry::ModuleTraits::InternalCellHandle>::exportData(
								hdf5_file,
								process_data );

  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );

  // Set the estimator as a cell estimator
  estimator_hdf5_file.setCellEstimator( this->getId() );
}

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<
			    ContributionMultiplierPolicy>::assignBinBoundaries(
      const std::shared_ptr<EstimatorDimensionDiscretization>& bin_boundaries )
{
  if( bin_boundaries->getDimension() == ENERGY_DIMENSION )
  {
    EntityEstimator<cellIdType>::assignBinBoundaries( bin_boundaries );
  }
  else
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
	      << " bins cannot be set for pulse height estimators. The bins "
	      << "requested for pulse height estimator " << this->getId()
	      << " will be ignored." 
	      << std::endl;
  }
}	       

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function simply returns 1.0.
 */
template<typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<
		   ContributionMultiplierPolicy>::calculateHistoryContribution(
					        const double energy_deposition,
						WeightMultiplier )
{
  return 1.0;
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function returns the energy that has been
 * deposited in the cell(s) of interest for the entire history.
 */
template<typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<
		   ContributionMultiplierPolicy>::calculateHistoryContribution(
					        const double energy_deposition,
						WeightAndEnergyMultiplier )
{
  return energy_deposition;
}

// Add info to update tracker
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::addInfoToUpdateTracker( 
						   const unsigned thread_id,
						   const cellIdType cell_id,
						   const double contribution )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );
  
  SerialUpdateTracker& thread_update_tracker = d_update_tracker[thread_id];

  if( thread_update_tracker.find( cell_id ) != thread_update_tracker.end() )
    thread_update_tracker[cell_id] += contribution;
  else
    thread_update_tracker[cell_id] = contribution;
}

// Get the entity iterators from the update tracker
template<typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<ContributionMultiplierPolicy>::getCellIteratorFromUpdateTracker(
	         const unsigned thread_id,
		 typename SerialUpdateTracker::const_iterator& start_cell,
	         typename SerialUpdateTracker::const_iterator& end_cell ) const
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );
  
  start_cell = d_update_tracker[thread_id].begin();
  end_cell = d_update_tracker[thread_id].end();
}

// Reset the update tracker
template<typename ContributionMultiplierPolicy>
void 
CellPulseHeightEstimator<ContributionMultiplierPolicy>::resetUpdateTracker( 
						     const unsigned thread_id )
{
  // Make sure the thread id is valid
  testPrecondition( thread_id < d_update_tracker.size() );
  
  d_update_tracker[thread_id].clear();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator_def.hpp
//---------------------------------------------------------------------------//
