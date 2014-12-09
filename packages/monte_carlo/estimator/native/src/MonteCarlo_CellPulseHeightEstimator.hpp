//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CellPulseHeightEstimator.hpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_CELL_PULSE_HEIGHT_ESTIMATOR_HPP
#define FACEMC_CELL_PULSE_HEIGHT_ESTIMATOR_HPP

// Boost Includes
#include <boost/mpl/vector.hpp>

// FRENSIE Includes
#include "MonteCarlo_EntityEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleEnteringCellEventObserver.hpp"
#include "MonteCarlo_ParticleLeavingCellEventObserver.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The pulse height entity estimator class
template<typename ContributionMultiplierPolicy = WeightMultiplier>
class CellPulseHeightEstimator : public EntityEstimator<Geometry::ModuleTraits::InternalCellHandle>, 
				 public ParticleEnteringCellEventObserver,
				 public ParticleLeavingCellEventObserver
{

public:

  //! Typedef for the cell id type
  typedef Geometry::ModuleTraits::InternalCellHandle cellIdType;

  //! Typedef for event tags used for quick dispatcher registering
  typedef boost::mpl::vector<ParticleEnteringCellEventObserver::EventTag,
			     ParticleLeavingCellEventObserver::EventTag>
  EventTags;

  //! Constructor
  CellPulseHeightEstimator( const Estimator::idType id,
			    const double multiplier,
			    const Teuchos::Array<cellIdType>& entity_ids );
  
  //! Destructor
  ~CellPulseHeightEstimator()
  { /* ... */ }

  //! Set the response functions
  void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Set the particle types that can contribute to the estimator
  void setParticleTypes( const Teuchos::Array<ParticleType>& particle_types );

  //! Add current history estimator contribution
  void updateFromParticleEnteringCellEvent( const ParticleState& particle,
					    const cellIdType cell_entering );

  //! Add current history estimator contribution
  void updateFromParticleLeavingCellEvent( const ParticleState& particle,
					   const cellIdType cell_leaving );
  
  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Print the estimator data
  void print( std::ostream& os ) const;

  //! Export the estimator data
  void exportData( EstimatorHDF5FileHandler& hdf5_file,
		   const bool process_data ) const;

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
  Estimator::TwoEstimatorMomentsArray d_total_energy_deposition_moments;

  // The energy deposited in each cell of interest by the current history
  boost::unordered_map<cellIdType,double> d_cell_energy_deposition_map;

  // The generic particle state map (avoids having to make a new map for cont.)
  Estimator::DimensionValueMap d_dimension_values;
};

} // end MonteCarlo namespace 

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CellPulseHeightEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_CELL_PULSE_HEIGHT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CellPulseHeightEstimator.hpp
//---------------------------------------------------------------------------//
