//---------------------------------------------------------------------------//
//!
//! \file   PulseHeightEstimator.hpp
//! \author Alex Robinson
//! \brief  Pulse height estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef PULSE_HEIGHT_ESTIMATOR_HPP
#define PULSE_HEIGHT_ESTIMATOR_HPP

// FACEMC Includes
#include "PulseHeightEstimator.hpp"

namespace FACEMC{

// The pulse height estimator class
template<typename CellId,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class PulseHeightEstimator : Estimator
{

public:
  
  //! Constructor
  PulseHeightEstimator( const unsigned long long id,
			const CellId& cell_id,
			const double norm_constant,
			const double multiplier = 1.0 );

  //! Destructor
  ~PulseHeightEstimator()
  { /* ... */ }

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

  //! Calculate and add estimator contribution from a portion of the cur. hist.
  void calculateAndAddPartialHistoryContribution( 
			                    const BasicParticleState& particle,
					    const bool entering_cell )
  
  //! Return the cell handle that this esimator is assigned to
  const CellId& getEntityId() const;

  //! Print the estimator data
  void print( std::ostream& os ) const;

protected:

  //! Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( WeightMultiplier );

  //! Calculate the estimator contribution from the entire history
  double calculateHistoryContribution( EnergyAndWeightMultiplier );
  
private:

  // The cell that this estimator is assigned to
  CellId d_cell_id;

  // The estimator first moment for the current history
  double d_current_history_first_moment;
};
	 
} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "PulseHeightEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PULSE_HEIGHT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end PulseHeightEstimator.hpp
//---------------------------------------------------------------------------//
