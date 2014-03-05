//---------------------------------------------------------------------------//
//!
//! \file   StandardEstimator.hpp
//! \author Alex Robinson
//! \brief  Standard estimator class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef STANDARD_ESTIMATOR_HPP
#define STANDARD_ESTIMATOR_HPP

// FACEMC Includes
#include "Estimator.hpp"

namespace FACEMC{

// The standard estimator class
template<typename EntityId>
class StandardEstimator : Estimator
{

public:

  //! Default constructor
  StandardEstimator();

  //! Constructor
  StandardEstimator( const unsigned long long id,
		     const EntityId& entity_id,
		     const double norm_constant,
		     const double multiplier = 1.0 );

  //! Destructor
  virtual ~StandarEstimator()
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

  //! Add estimator contribution from a portion of the current history
  void addPartialHistoryContribution( const BasicParticleState& particle,
				      const double contribution,
				      const double angle_cosine );

  //! Commit the contribution from the current history to the estimator
  void commitHistoryContribution();

  //! Return the entity handle that this estimator is assigned to
  const EntityId& getEntityId() const;

private:

  // The entity that this estimator is assigned to
  EntityId d_entity_id;

  // The estimator first moment for each bin of the current history
  Teuchos::Array<double> d_current_history_first_moments;
}; 
	 
} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "StandardEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end STANDARD_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end StandardEstimator.hpp
//---------------------------------------------------------------------------//
