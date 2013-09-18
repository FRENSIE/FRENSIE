//---------------------------------------------------------------------------//
//!
//! \file   SurfaceHelpers.hpp
//! \author Alex Robinson
//! \brief  Helper functions for Surface operations in
//!
//---------------------------------------------------------------------------//

#ifndef SURFACE_HELPERS_HPP
#define SURFACE_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FACEMC Includes
#include "Surface.hpp"

namespace FACEMC{

//! Create a second order surface from another second order surface and a translation vector
template<typename OrdinalType, typename ScalarType>
Surface<OrdinalType,ScalarType>
createSurfaceFromTranslation( const Surface<OrdinalType,ScalarType> 
			      &original_surface,
			      const Teuchos::SerialDenseVector<char,ScalarType>
			      &translation_vector );

//! Create a second order surface from another second order surface and a rotation matrix.
template<typename OrdinalType, typename ScalarType>
Surface<OrdinalType,ScalarType>
createSurfaceFromRotation( const Surface<OrdinalType,ScalarType> 
			   &original_surface,
			   const Teuchos::SerialDenseMatrix<char,ScalarType>
			   &rotation_matrix );

//! Create a second order surface from another second order surface and a general transforation.
template<typename OrdinalType, typename ScalarType>
Surface<OrdinalType,ScalarType>
createSurfaceFromGeneralTransform( const Surface<OrdinalType,ScalarType> 
				   &original_surface,
				   const Teuchos::SerialDenseMatrix<char,ScalarType>
				   &rotation_matrix,
				   const Teuchos::SerialDenseVector<char,ScalarType>
				   &translation_vector );

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "SurfaceHelpers_def.hpp"

#endif // end SURFACE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end SurfaceHelpers.hpp
//---------------------------------------------------------------------------//


