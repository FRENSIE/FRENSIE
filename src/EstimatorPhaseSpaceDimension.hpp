//---------------------------------------------------------------------------//
//!
//! \file   EstimatorPhaseSpaceDimension.hpp
//! \author Alex Robinson
//! \brief  Estimator phase space dimension enumeration
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_PHASE_SPACE_DIMENSION_HPP
#define ESTIMATOR_PHASE_SPACE_DIMENSION_HPP

namespace FACEMC{

/*! The estimator phase space dimension enumeration
 *
 * Make sure that the DIMENSION_end value equals the last dimension name if
 * more dimension names are added. The start and end enum names are used for
 * iterating through the list of dimensions.
 */
enum EstimatorPhaseSpaceDimension{
  DIMENSON_start = 0,
  ENERGY_DIMENSION = DIMENSON_start,
  COSINE_DIMENSION,
  TIME_DIMENSION,
  COLLISION_NUMBER_DIMENSION,
  DIMENSION_end
};

} // end FACEMC namespace

#endif // end ESTIMATOR_PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end EstimatorPhaseSpaceDimension.hpp
//---------------------------------------------------------------------------//
