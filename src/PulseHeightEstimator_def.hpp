//---------------------------------------------------------------------------//
//!
//! \file   PulseHeightEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Pulse height estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef PULSE_HEIGHT_ESTIMATOR_DEF_HPP
#define PULSE_HEIGHT_ESTIMATOR_DEF_HPP

// Std Lib Includes
#include <iostream>

// FACEMC Includes
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename CellId,typename ContributionMultiplierPolicy>
PulseHeightEstimator<CellId,
		     ContributionMultiplierPolicy>::PulseHeightEstimator(
						   const unsigned long long id,
						   const CellId& cell_id,
						   const double norm_constant,
						   const double multiplier )
  : Estimator( id, norm_constant, multiplier ),
    d_cell_id( cell_id ),
    d_current_history_first_moment( 0.0 )
{ /* ... */ }

// Set the cosine bin boundaries
template<typename CellId,typename ContributionMultiplierPolicy>
void PulseHeightEstimator<CellId,
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
void PulseHeightEstimator<CellId,
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
void PulseHeightEstimator<CellId,
			 ContributionMultiplierPolicy>::setCollisionNumberBins(
			  const Teuchos::Array<double>& collision_number_bins )
{
  std::cerr << "Warning: Collision number bins cannot be set for pulse height "
	    << "estimators. The collision number bins requested for pulse "
	    << "height estimator " << getId() << " will be ignored."
	    << std::endl;
}

// Set the response functions
template<typename CellId,typename ContributionMultiplierPolicy>
void PulseHeightEstimator<CellId,
			  ContributionMultiplierPolicy>::setResponseFunctions(
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  std::cerr << "Warning: Response functions cannot be set for pulse height "
	    << "estimators. The response functions requested for pulse height "
	    << "estimator " << getId() << " will be ignored."
	    << std::endl;
}

// Calculate and add estimator contribution from a portion of the cur. history
template<typename CellId,typename ContributionMultiplierPolicy>
void PulseHeightEstimator<CellId,
      ContributionMultiplierPolicy>::calculateAndAddPartialHistoryContribution(
			                    const BasicParticleState& particle,
					    const bool entering_cell )
{
  double contribution = particle.getWeight()*particle.getEnergy();

  // Particles exiting the cell contribute a negative value
  if( !entering_cell )
    contribution *= -1;  

  d_current_history_first_moment += contribution;
}
	      
// Commit the contribution from the current history to the estimator
/*! \details The energy deposited in the detector from this entire history
 * determines the bin of the contribution. The contribution to the bin is
 * then either 1.0 or the energy (depending on the specified multiplier 
 * policy).
 */ 
template<typename CellId,typename ContributionMultiplierPolicy>
void PulseHeightEstimator<CellId,
		     ContributionMultiplierPolicy>::commitHistoryContribution()
{
  unsigned bin_index = calculateBinIndex( d_current_history_first_moment,
					  0.0,
					  0.0,
					  0,
					  1 );

  double contribution = calculateHistoryContribution( 
						ContributionMultiplierPolicy );
  
  commitHistoryContributionToBin( bin_index, 1.0 );
}

// Print the estimator data
template<typename CellId,typename ContributionMultiplierPolicy>
void PulseHeightEstimator<CellId,ContributionMultiplierPolicy>::print(
							     std::ostream& os )
{
  os << "Estimator "<< getId() << ": Cell " << getEntityId() << std::endl;
}

// Return the cell handle that this estimator is assigned to
template<typename CellId,typename ContributionMultiplierPolicy>
const CellId& PulseHeightEstimator<CellId,
			     ContributionMultiplierPolicy>::getEntityId() const
{
  return d_cell_id;
}

// Calculate the estimator contribution from the entire history
/*! \details The multiplier policy cannot be used directly since it only
 * operates on a particle state. The policy classes will instead be used as
 * tags for tag dispatching. This function simply returns 1.0.
 */
template<typename CellId,typename ContributionMultiplierPolicy>
inline double PulseHeightEstimator<CellId,
	           ContributionMultiplierPolicy>::calculateHistoryContribution(
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

template<typename CellId,typename ContributionMultiplierPolicy>
inline double PulseHeightEstimator<CellId,
		   ContributionMultiplierPolicy>::calculateHistoryContribution(
						    EnergyAndWeightMultiplier )
{
  return d_current_history_first_moment;
}


} // end FACEMC namespace

#define // end PULSE_HEIGHT_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end PulseHeightEstimator_def.hpp
//---------------------------------------------------------------------------//
