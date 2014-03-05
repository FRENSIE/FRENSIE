//---------------------------------------------------------------------------//
//!
//! \file   SurfaceEstimator_def.hpp
//! \author Alex Robinson
//! \brief  Surface estimator base class definitions.
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_ESTIMATOR_DEF_HPP
#define SURFACE_ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"

// Constructor
template<typename SurfaceId>
SurfaceEstimator<SurfaceId>::SurfaceEstimator( const unsigned long long id,
					       const SurfaceId& surface_id,
					       const double norm_constant,
					       const double multiplier )
  : StandardEstimator<SurfaceId>( id, surface_id, norm_constant, multiplier )
{ /* ... */ }

// Print the estimator data
template<typename SurfaceId>
void SurfaceEstimator<SurfaceId>::print( std::ostream& os ) const
{
  os << "Tally " << getId() << ": Surface " << getEntityId() << std::endl;

  os << Estimator::printImplementation( os );
}

#endif // end SURFACE_ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end SurfaceEstimator_def.hpp
//---------------------------------------------------------------------------//
