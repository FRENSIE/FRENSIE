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
class CellPulseHeightEstimator : public EntityEstimator<CellId>
{

public:

  //! Constructor
  CellPulseHeightEstimator( const unsigned long long id,
			    const double multiplier,
			    const Teuchos::Array<CellId>& entity_ids );
  
  //! Destructor
  ~CellPulseHeightEstimator()
  { /* ... */ }

  //! Set the response functions
  void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );
  
  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const CellId& cell_leaving,
				      const CellId& cell_entering );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Print the estimator data
  void print( std::ostream& os ) const;

private:

  //! Assign bin boundaries to an estimator dimension
  void assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries );

  //! Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( const double energy_deposition,
				       WeightMultiplier );

  //! Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( const double energy_deposition,
				       WeightAndEnergyMultiplier );

  // The total estimator moments for all entities
  Estimator::EstimatorMomentsArray d_total_energy_deposition_moments;

  // The energy deposited in each cell of interest by the current history
  boost::unordered_map<CellId,double> d_cell_energy_deposition_map;

  // The generic particle state map (avoids having to make a new map for cont.)
  Estimator::DimensionValueMap d_dimension_values;
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
