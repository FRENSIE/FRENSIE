//---------------------------------------------------------------------------//
// \file   Surface.cpp
// \author Alex Robinson
// \brief  Surface class definition
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <cmath>

// Trilinos Includes
#include <Teuchos_Tuple.hpp>

// FACEMC Includes
#include "Surface.hpp"
#include "ContractException.hpp"
#include "LinearAlgebraAlgorithms.hpp"

namespace FACEMC{

//! Constructor
Surface::Surface( unsigned int id,
		  double a,
		  double b,
		  double c,
		  double d,
		  double e,
		  double f,
		  double g,
		  double h,
		  double j,
		  double k )
  : d_id( id ),
    d_quadratic_form_matrix( Teuchos::tuple( a,   d/2, f/2, 
					     d/2, b,   e/2, 
					     f/2, e/2, c   ) ),
    d_linear_term_vector( Teuchos::tuple( g, h, j ) ),
    d_constant_term( k )
{ 
  double max = 0.0;
  for( unsigned int i = 0; i < 9; ++i )
  {
    if( fabs(d_quadratic_form_matrix[i]) > max )
      max = fabs(d_quadratic_form_matrix[i]);
  }
  for( unsigned int i = 0; i < 3; ++i )
  {
    if( fabs(d_linear_term_vector[i]) > max )
      max = fabs(d_linear_term_vector[i]);
  }
  if( fabs(d_constant_term) > max )
    max = fabs(d_constant_term);
  
  d_tolerance = 1e-12*max;
}

//! Return if the point is on the surface
bool Surface::isOn( const Vector &point ) const
{
  return fabs( point*d_quadratic_form_matrix*point + 
	       d_linear_term_vector*point +
	       d_constant_term ) < d_tolerance;
}

//! Return the sense of a point with respect to the surface
short Surface::getSense( const Vector &point ) const
{
  double value = point*d_quadratic_form_matrix*point + 
    d_linear_term_vector*point +
    d_constant_term;
  
  if( value > d_tolerance )
    return 1;
  else if( value < -d_tolerance )
    return -1;
  else 
    return 0;
}

//! Return the unit normal from the surface at a point on the surface,
// pointing in the direction of the desired sense
Surface::Vector Surface::getUnitNormal( const Vector &point,
					const short sense ) const
{
  // The point must be on the surface
  testPrecondition( isOn( point ) );
  
  Vector gradient = getGradient( point );
  LinearAlgebra::normalizeVector( gradient );
  return gradient;
}

//! Return the quadratic form matrix of the surface
Surface::Matrix Surface::getQuadraticFormMatrix() const
{
  return d_quadratic_form_matrix;
}

//! Return the linear term vector of the surface
Surface::Vector Surface::getLinearTermVector() const
{
  return d_linear_term_vector;
}

//! Return the constant term of the surface
double Surface::getConstantTerm() const
{
  return d_constant_term;
}

//! Rotate the surface using the provided rotation matrix
void Surface::transformSurface( const Matrix &rotation_matrix,
				const Vector &translation_vector )
{
  // The rotation matrix must be valid (orthonormal)
  remember( Vector column_1 = Teuchos::tuple( rotation_matrix[0],
					      rotation_matrix[3],
					      rotation_matrix[6] ) );
  remember( double column_1_magnitude = 
	    LinearAlgebra::vectorMagnitude( column_1 ) );
  remember( Vector column_2 = Teuchos::tuple( rotation_matrix[1],
					      rotation_matrix[4],
					      rotation_matrix[7] ) );
  remember( double column_2_magnitude = 
	    LinearAlgebra::vectorMagnitude( column_2 ) );
  remember( Vector column_3 = Teuchos::tuple( rotation_matrix[2],
					      rotation_matrix[5],
					      rotation_matrix[8] ) );
  remember( double column_3_magnitude = 
	    LinearAlgebra::vectorMagnitude( column_3 ) );
  testPrecondition( fabs(column_1_magnitude - 1.0) < 1e-12 );
  testPrecondition( fabs(column_2_magnitude - 1.0) < 1e-12 );
  testPrecondition( fabs(column_3_magnitude - 1.0) < 1e-12 );
  testPrecondition( fabs(column_1*column_2) < 1e-12 );
  testPrecondition( fabs(column_1*column_3) < 1e-12 );
  testPrecondition( fabs(column_2*column_3) < 1e-12 );

  d_constant_term = 
    translation_vector*d_quadratic_form_matrix*translation_vector +
    d_linear_term_vector*translation_vector +
    d_constant_term;

  Matrix rotation_matrix_transpose = 
    LinearAlgebra::matrixTranspose( rotation_matrix );

  d_linear_term_vector = 
    2*(rotation_matrix_transpose*(d_quadratic_form_matrix*translation_vector)) +
    d_linear_term_vector*rotation_matrix;

  d_quadratic_form_matrix = 
    rotation_matrix_transpose*d_quadratic_form_matrix*rotation_matrix;
}  

//! Return the gradient of the surface at a given point
Surface::Vector Surface::getGradient( const Vector &point ) const
{
  // The point must be on the surface
  testPrecondition( isOn( point ) );
  
  // 2ax+dy+fz+g
  double x_gradient = 2*(d_quadratic_form_matrix[0]*point[0] +
			 d_quadratic_form_matrix[1]*point[1] +
			 d_quadratic_form_matrix[2]*point[2]) + 
    d_linear_term_vector[0];
  
  // 2by+dx+ez+h
  double y_gradient = 2*(d_quadratic_form_matrix[4]*point[1] +
			 d_quadratic_form_matrix[1]*point[0] +
			 d_quadratic_form_matrix[5]*point[2]) +
    d_linear_term_vector[1];
  
  // 2cz+ey+fx+j
  double z_gradient = 2*(d_quadratic_form_matrix[8]*point[2] +
			 d_quadratic_form_matrix[5]*point[1] +
			 d_quadratic_form_matrix[2]*point[0]) +
    d_linear_term_vector[2];
  
  Vector gradient = Teuchos::tuple( x_gradient, y_gradient, z_gradient );

  return gradient;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end Surface.cpp
//---------------------------------------------------------------------------//

