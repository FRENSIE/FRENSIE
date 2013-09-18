//---------------------------------------------------------------------------//
//!
//! \file   ThreeSpaceHelpers.hpp
//! \author Alex Robinson
//! \brief  Helper function declarations for operations in \f$ R^3 \f$.
//!
//---------------------------------------------------------------------------//

#ifndef THREE_SPACE_HELPERS_HPP
#define THREE_SPACE_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

namespace FACEMC{

//! Create a vector in \f$ R^3 \f$.
template<typename ScalarType>
Teuchos::SerialDenseVector<char,ScalarType> 
createThreeSpaceVector( ScalarType x,
			ScalarType y,
			ScalarType z );

//! Create a 3x3 matrix (for use in \f$ R^3 \f$).
template<typename ScalarType>
Teuchos::SerialDenseMatrix<char,ScalarType> 
createThreeByThreeMatrix( ScalarType a00, ScalarType a01, ScalarType a02,
			  ScalarType a10, ScalarType a11, ScalarType a12,
			  ScalarType a20, ScalarType a21, ScalarType a22 );

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "ThreeSpaceHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end THREE_SPACE_HELPERS_HPP

//---------------------------------------------------------------------------//
// end ThreeSpaceHelpers.hpp
//---------------------------------------------------------------------------//

