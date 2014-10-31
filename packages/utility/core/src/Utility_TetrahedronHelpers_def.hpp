//---------------------------------------------------------------------------//
//!
//! \file   Utility_TetrahedronHelpers_def.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tetrahedron helper function template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TETRAHEDRON_HELPERS_DEF_HPP
#define UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseSolver.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Calculate tetrahedron barycentric transform matrix                        
template<typename Matrix>                                                      
void calculateBarycentricTransformMatrix( const double vertex_a[3],    
					  const double vertex_b[3],    
					  const double vertex_c[3],    
					  const double vertex_d[3],    
					  Matrix& matrix ) 
{
  // Make sure the matrix is valid
  testPrecondition( matrix.numRows() == 3 );
  testPrecondition( matrix.numCols() == 3 );
  
  matrix( 0, 0 ) = vertex_a[0] - vertex_d[0];
  matrix( 0, 1 ) = vertex_b[0] - vertex_d[0];
  matrix( 0, 2 ) = vertex_c[0] - vertex_d[0];
  matrix( 1, 0 ) = vertex_a[1] - vertex_d[1];
  matrix( 1, 1 ) = vertex_b[1] - vertex_d[1];
  matrix( 1, 2 ) = vertex_c[1] - vertex_d[1];
  matrix( 2, 0 ) = vertex_a[2] - vertex_d[2];
  matrix( 2, 1 ) = vertex_b[2] - vertex_d[2];
  matrix( 2, 2 ) = vertex_c[2] - vertex_d[2];

  Teuchos::SerialDenseSolver<typename Matrix::ordinalType,
			     typename Matrix::scalarType> solver;
  solver.setMatrix( Teuchos::rcp<Matrix>( &matrix, false ) );
  
  int return_value = solver.invert();

  // Make sure the tet is valid
  testPrecondition( return_value == 0 );
}

} // end Utility namespace

#endif // end UTILITY_TETRAHEDRON_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_TetrahedronHelpers_def.hpp
//---------------------------------------------------------------------------//
