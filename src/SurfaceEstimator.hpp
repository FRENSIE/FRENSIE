//---------------------------------------------------------------------------//
//!
//! \file   SurfaceEstimator.hpp
//! \author Alex Robinson
//! \brief  Surface estimator base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_ESTIMATOR_HPP
#define SURFACE_ESTIMATOR_HPP

// FACEMC Includes
#include "SurfaceEstimator.hpp"

//! The surface estimator base class
template<typename SurfaceId>
class SurfaceEstimator : public StandardEstimator<SurfaceId>
{

public:

  //! Constructor
  SurfaceEstimator( const unsigned long long id,
		    const SurfaceId& surface_id,
		    const double norm_constant,
		    const double multiplier = 1.0 );

  //! Destructor
  virtual ~SurfaceEstimator()
  { /* ... */ }

  //! Calculate and add estimator contribution from a portion of the cur. hist.
  void calculateAndAddPartialHistoryContribution( 
				     const BasicParticleState& particle,
				     const double reference_direction[3] ) = 0;

  //! Print the estimator data
  virtual print( std::ostream& os ) const;
};

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "SurfaceEstimator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SURFACE_ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end SurfaceEstimator.hpp
//---------------------------------------------------------------------------//
