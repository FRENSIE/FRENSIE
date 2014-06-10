//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CellPulseHeightEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_CELL_PULSE_HEIGHT_ESTIMATOR_HPP
#define FACEMC_CELL_PULSE_HEIGHT_ESTIMATOR_HPP

// FRENSIE Includes
#include "Facemc_EntityEstimator.hpp"
#include "Facemc_EstimatorContributionMultiplierPolicy.hpp"
#include "Facemc_ParticleGenerationEventObserver.hpp"
#include "Facemc_ParticleEnteringCellEventObserver.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The pulse height entity estimator class
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellPulseHeightEstimator : public EntityEstimator<Geometry::ModuleTraits::InternalCellHandle>, 
				 public ParticleGenerationEventObserver,
				 public ParticleEnteringCellEventObserver
{

public:

  //! Typedef for the cell id type
  typedef Geometry::ModuleTraits::InternalCellHandle cellIdType;

  //! Constructor
  CellPulseHeightEstimator( const Estimator::idType id,
			    const double multiplier,
			    const Teuchos::Array<cellIdType>& entity_ids,
			    const bool auto_register_with_dispatchers = true );
  
  //! Destructor
  ~CellPulseHeightEstimator()
  { /* ... */ }

  //! Set the response functions
  void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Add current history estimator contribution
  void updateFromParticleGenerationEvent( const ParticleState& particle );

  //! Add current history estimator contribution
  void updateFromParticleEnteringCellEvent( const ParticleState& particle,
					    const cellIdType cell_entering );
  
  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const ParticleState& particle,
				      const cellIdType& cell_leaving,
				      const cellIdType& cell_entering );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Print the estimator data
  void print( std::ostream& os ) const;

private:

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const ParticleState& particle );

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
  boost::unordered_map<cellIdType,double> d_cell_energy_deposition_map;

  // The generic particle state map (avoids having to make a new map for cont.)
  Estimator::DimensionValueMap d_dimension_values;
};

} // end Facemc namespace 

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Facemc_CellPulseHeightEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_CELL_PULSE_HEIGHT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end Facemc_CellPulseHeightEstimator.hpp
//---------------------------------------------------------------------------//
