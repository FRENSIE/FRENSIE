//---------------------------------------------------------------------------//
//!
//! \file   CellPulseHeightEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class definition
//!
//---------------------------------------------------------------------------//

#ifndef CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP
#define CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename CellId,typename ContributionMultiplierPolicy>
CellPulseHeightEstimator<CellId,
		       ContributionMultiplierPolicy>::CellPulseHeightEstimator(
			  const unsigned long long id,
			  const double multiplier,
			  const Teuchos::Array<CellId>& entity_ids )
			   
  : EntityEstimator<CellId>( id,
			     multiplier,
			     entity_ids ),
    d_total_energy_deposition_moments( 1 )
{
  // Set up the entity map
  for( unsigned i = 0; i < entity_ids.size(); ++i )
  {
    // Ignore duplicate entity ids
    if( d_cell_energy_deposition_map.count( entity_ids[i] ) == 0 )
      d_cell_energy_deposition_map[ entity_ids[i] ] = 0.0;
  }
}

// Set the energy bin boundaries
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
			 ContributionMultiplierPolicy>::setEnergyBinBoundaries(
			  const Tuechos::Array<double>& energy_bin_boundaries )
{
  EntityEstimator<CellId>::setEnergyBinBoundaries( energy_bin_boundaries );

  // Resize the total energy deposition moments array
  d_total_energy_deposition_moments.resize( getNumberOfBins() );
}

// Set the cosine bin boundaries
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
			 ContributionMultiplierPolicy>::setCosineBinBoundaries(
			  const Teuchos::Array<double>& cosine_bin_boundaries )
{
  std::cerr << "Warning: Cosine bins cannot be set for pulse height "
	    << "estimators. The cosine bins requested for pulse height "
	    << "estimator " << getId() << " will be ignored."
	    << std::endl;
}

// Set the time bin boundaries
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
			   ContributionMultiplierPolicy>::setTimeBinBoundaries(
			    const Teuchos::Array<double>& time_bin_boundaries )
{
  std::cerr << "Warning: Time bins cannot be set for pulse height "
	    << "estimators. The time bins requested for pulse height "
	    << "estimator " << getId() << " will be ignored."
	    << std::endl;
}

// Set the collision number bins
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
			 ContributionMultiplierPolicy>::setCollisionNumberBins(
			const Teuchos::Array<unsigned>& collision_number_bins )
{
  std::cerr << "Warning: Collision number bins cannot be set for pulse height "
	    << "estimators. The collision number bins requested for pulse "
	    << "height estimator " << getId() << " will be ignored."
	    << std::endl;
}

// Set the response functions
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
			   ContributionMultiplierPolicy>::setResponseFunctions(
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  std::cerr << "Warning: Response functions cannot be set for pulse height "
	    << "estimators. The response functions requested for pulse height "
	    << "estimator " << getId() << " will be ignored."
	    << std::endl;
}

// Set the particle types that can contribute to the estimator
/*! \details Only photons and electrons can contribute to this estimator
 */
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
			      ContributionMultiplierPolicy>::setParticleTypes( 
			   const Teuchos::Array<ParticleType>& particle_types )
{
  Estimator::setParticleTypes( particle_types );

  testPostcondition( !isParticleTypeAssigned( NEUTRON ) );
  testPostcondition( !isParticleTypeAssigned( ADJOINT_NEUTRON ) );
  testPostcondition( !isParticleTypeAssigned( ADJOINT_PHOTON ) );
}

// Add estimator contribution from a portion of the current history
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
		  ContributionMultiplierPolicy>::addPartialHistoryContribution(
					    const BasicParticleState& particle,
					    const EntityId& cell_leaving,
					    const EntityId& cell_entering )
{
  if( isParticleTypeAssigned( particle.getType() )
  {
    double contribution = particle.getWeight()*particle.getEnergy();
    
    // Subtract the contribution from the cell being exited
    if( d_cell_energy-deposition_map.count( cell_leaving ) != 0 )
      d_cell_energy_deposition_map[cell_leaving] -= contribution;
    
    // Add the contribution to the cell being entered
    if( d_cell_energy_deposition_map.count( cell_entering ) != 0 )
      d_cell_energy_deposition_map[cell_entering] += contribution;
  }
}

// Add estimator contribution from a portion of the current history
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,
		     ContributionMultiplierPolicy>::commitHistoryContribution()
{
  boost::unordered_map<CellId,double>::iterator entity, end_entity;

  entity = d_cell_energy_deposition_map.begin();
  end_entity = d_cell_energy_deposition_map.end();

  double energy_deposition_in_all_cells = 0.0;
  
  unsigned bin_index;
  double bin_contribution;

  while( entity != end_entity )
  {
    if( isEnergyInEstimatorEnergySpace( entity->second ) )
    {
      bin_index = calculateEnergyBinIndex( entity->second );
      
      bin_contribution = calculateHistoryContribution( 
						entity->second,
						ContributionMultiplierPolicy );
      
      commitHistoryContributionToBinOfEntity( entity->first,
					      bin_index,
					      bin_contribution );
      
      // Add the energy deposition in this cell to the total energy deposition
      energy_deposition_in_all_cells += entity->second;

      // Reset the energy deposition in this cell
      entity->second = 0.0;
    }
  }

  // Determine the pulse bin for the combination of all cells
  if( isEnergyInEstimatorEnergySpace( energy_deposition_in_all_cells ) )
  {
    bin_index = calculateEnergyBinIndex( energy_deposition_in_all_cells );

    bin_contribution = calculateHistoryContribution( 
					        energy_deposition_in_all_cells,
					        ContributionMultiplierPolicy );

    // Compute the moment contributions
    d_total_energy_deposition[bin_index].first += bin_contribution;
    
    bin_contribution *= bin_contribution;
    d_total_energy_deposition[bin_index].second += bin_contribution;

    bin_contribution *= bin_contribution;
    d_total_energy_deposition[bin_index].third += bin_contribution;

    bin_contribution *= bin_contribution;
    d_total_energy_deposition[bin_index].fourth += bin_contribution;
  }
}

// Print the estimator data
template<typename CellId,typename ContributionMultiplierPolicy>
void CellPulseHeightEstimator<CellId,ContributionMultiplierPolicy>::print( 
						       std::ostream& os ) const
{
  os << "Cell Pulse Height Estimator: " << getId() << std::endl;

  printImplementation( os, "Cell" );

  os << "Total Bin Data (all cells): " << std::endl;

  printEstimatorBinData( os,
			 d_total_energy_deposition_moments,
			 getTotalNormConstant() );
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function simply returns 1.0.
 */
template<typename CellId,typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<CellId,
		   ContributionMultiplierPolicy>::calculateHistoryContribution(
					        const double energy_deposition,
						WeightMultiplier )
{
  return 1.0
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function returns the energy that has been
 * deposited in the cell(s) of interest for the entire history.
 */
template<typename CellId,typename ContributionMultiplierPolicy>
inline double CellPulseHeightEstimator<CellId,
		   ContributionMultiplierPolicy>::calculateHistoryContribution(
					        const double energy_deposition,
						EnergyAndWeightMultiplier )
{
  return energy_deposition;
}

} // end FACEMC namespace

#endif // end CELL_PULSE_HEIGHT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end CellPulseHeightEstimator_def.hpp
//---------------------------------------------------------------------------//
