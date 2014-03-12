//---------------------------------------------------------------------------//
//!
//! \file   CellPulseHeightEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CELL_PULSE_HEIGHT_ESTIMATOR_HPP
#define CELL_PULSE_HEIGHT_ESTIMATOR_HPP

// FACEMC Includes
#include "EntityEstimator.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"

namespace FACEMC{

//! The pulse height entity estimator class
template<typename CellId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class CellPulseHeightEstimator : EntityEstimator<CellId>
{

public:

  //! Constructor
  CellPulseHeightEstimator( 
			   const unsigned long long id,
			   const Teuchos::Array<CellId>& entity_ids,
		           const Teuchos::Array<double>& entity_norm_constants,
			   const double multiplier );

  //! Destructor
  ~CellPulseHeightEstimator()
  { /* ... */ }

  //! Set the energy bin boundaries
  void setEnergyBinBoundaries(
			 const Teuchos::Array<double>& energy_bin_boundaries );

  //! Set the cosine bin boundaries
  void setCosineBinBoundaries(
			 const Teuchos::Array<double>& cosine_bin_boundaries );

  //! Set the time bin boundaries
  void setTimeBinBoundaries(
			   const Teuchos::Array<double>& time_bin_boundaries );

  //! Set the collision number bins
  void setCollisionNumberBins( 
		       const Teuchos::Array<unsigned>& collision_number_bins );

  //! Set the response functions
  void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );
  
  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const EntityId& cell_leaving,
				      const EntityId& cell_entering );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Print the estimator data
  void print( std::ostream& os ) const;

private:

  //! Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( const double energy_deposition,
				       WeightMultiplier );

  //! Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( const double energy_deposition,
				       EnergyAndWeightMultiplier );

  // The total estimator moments for all entities
  EstimatorMomentsArray d_total_energy_deposition_moments;

  // The energy deposited in each cell of interest by the current history
  boost::unordered_map<CellId,double> d_cell_energy_deposition_map;
};

} // end FACEMC namespace 

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "CellPulseHeightEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end CELL_PULSE_HEIGHT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end CellPulseHeightEstimator.hpp
//---------------------------------------------------------------------------//
