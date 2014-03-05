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
template<typename CellHandle,
	 typename ContributionMultiplierPolicy = WeightMultiplier>
class PulseHeightEstimator : Estimator
{

public:
  
  //! Default constructor
  PulseHeightEstimator();

  //! Constructor
  PulseHeightEstimator( const unsigned long long id,
			const CellHandle& entity,
			const double norm_constant,
			const double multiplier = 1.0 );

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

  //! Add a response function
  void addResponseFunction(
		     const Teuchos::RCP<ResponseFunction>& response_function );

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const double raw_contribution,
				      const double angle_cosine );

  //! Return the cell handle that this esimator is assigned to
  const CellHandle& getEntityHandle() const;

  //! Print the estimator data
  void print( std::ostream& os ) const;
  
private:

  // The cell that this estimator is assigned to
  CellHandle d_cell;

  // The estimator first moment for the current history
  double d_current_history_first_moment;
};
	 
} // end FACEMC namespace

#endif // end PULSE_HEIGHT_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end PulseHeightEstimator.hpp
//---------------------------------------------------------------------------//
