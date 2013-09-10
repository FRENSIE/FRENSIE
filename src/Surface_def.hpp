//---------------------------------------------------------------------------//
//!
//! \file   Surface_def.hpp
//! \author Alex Robinson
//! \brief  Surface class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <cmath>

// Trilinos Includes
#include <Teuchos_BLAS.hpp>

// FACEMC Includes
#include "Surface.hpp"
#include "ContractException.hpp"
#include "LinearAlgebraAlgorithms.hpp"

namespace FACEMC{

//! General Surface Constructor
template<typename OrdinalType, typename ScalarType>
Surface<OrdinalType,ScalarType>::Surface( OrdinalType id,
					  ScalarType a,
					  ScalarType b,
					  ScalarType c,
					  ScalarType d,
					  ScalarType e,
					  ScalarType f,
					  ScalarType g,
					  ScalarType h,
					  ScalarType j,
					  ScalarType k,
					  ScalarType tolerance_ratio )
  : d_id( id ),
    d_quadratic_form_matrix( 3, 3 ),
    d_linear_term_vector( 3 ),
    d_constant_term( k ),
    d_tolerance( ST::zero() ),
    d_symmetric( false ),
    d_planar( false )
{ 
  // Make sure the correct constructor has been used
  testPrecondition( (a != ST::zero() || b != ST::zero() || c != ST::zero()) && 
		    (d != ST::zero() || e != ST::zero() || f != ST::zero()) );
  
  // Load quadratic form matrix
  d_quadratic_form_matrix( 0, 0 ) = a;
  d_quadratic_form_matrix( 0, 1 ) = d/2.0;
  d_quadratic_form_matrix( 0, 2 ) = f/2.0;
  d_quadratic_form_matrix( 1, 0 ) = d/2.0;
  d_quadratic_form_matrix( 1, 1 ) = b;
  d_quadratic_form_matrix( 1, 2 ) = e/2.0;
  d_quadratic_form_matrix( 2, 0 ) = f/2.0;
  d_quadratic_form_matrix( 2, 1 ) = e/2.0;
  d_quadratic_form_matrix( 2, 2 ) = c;

  // Load linear term vector
  d_linear_term_vector[0] = g;
  d_linear_term_vector[1] = h;
  d_linear_term_vector[2] = j;

  // Determine floating point tolerance
  typename ST::magnitudeType max = ST::magnitude( a );
  
  if( max < ST::magnitude( b ) )
    max = ST::magnitude( b );
  if( max < ST::magnitude( c ) )
    max = ST::magnitude( c );
  if( max < ST::magnitude( d ) )
    max = ST::magnitude( d );
  if( max < ST::magnitude( e ) )
    max = ST::magnitude( e );
  if( max < ST::magnitude( f ) )
    max = ST::magnitude( f );
  if( max < ST::magnitude( g ) )
    max = ST::magnitude( g );
  if( max < ST::magnitude( h ) )
    max = ST::magnitude( h );
  if( max < ST::magnitude( j ) )
    max = ST::magnitude( j );
  if( max < ST::magnitude( k ) )
    max = ST::magnitude( k );
  
  d_tolerance = tolerance_ratio*max;

  d_tolerance = tolerance_ratio*
}

// Symmetric 2nd order surface constructor
template<typename OrdinalType, typename ScalarType>
Surface<OrdinalType,ScalarType>::Surface( OrdinalType id,
					  ScalarType a,
					  ScalarType b,
					  ScalarType c,
					  ScalarType g,
					  ScalarType h,
					  ScalarType j,
					  ScalarType k,
					  ScalarType tolerance_ratio )
  : d_id( id ),
    d_quadratic_form_matrix( 3, 3 ),
    d_linear_term_vector( 3 ),
    d_constant_term( k ),
    d_tolerance( ST::zero() ),
    d_symmetric( true ),
    d_planar( false )
{
  // Make sure the correct constructor has been used
  testPrecondition( a != ST::zero() || b != ST::zero() || c != ST::zero() );

  // Load quadratic form matrix
  d_quadratic_form_matrix( 0, 0 ) = a;
  d_quadratic_form_matrix( 1, 1 ) = b;
  d_quadratic_form_matrix( 2, 2 ) = c;

  // Load linear term vector
  d_linear_term_vector[0] = g;
  d_linear_term_vector[1] = h;
  d_linear_term_vector[2] = j;

  // Determine floating point tolerance
  typename ST::magnitudeType max = ST::magnitude( a );
  
  if( max < ST::magnitude( b ) )
    max = ST::magnitude( b );
  if( max < ST::magnitude( c ) )
    max = ST::magnitude( c );
  if( max < ST::magnitude( g ) )
    max = ST::magnitude( g );
  if( max < ST::magnitude( h ) )
    max = ST::magnitude( h );
  if( max < ST::magnitude( j ) )
    max = ST::magnitude( j );
  if( max < ST::magnitude( k ) )
    max = ST::magnitude( k );
  
  d_tolerance = tolerance_ratio*max;
}

// Planar Surface constructor
template<typename OrdinalType, typename ScalarType>
Surface<OrdinalType,ScalarType>::Surface( OrdinalType id,
					  ScalarType g,
					  ScalarType h,
					  ScalarType j,
					  ScalarType k )
  : d_id( id ),
    d_quadratic_form_matrix( 3, 3 ),
    d_linear_term_vector( 3 ),
    d_constant_term( k ),
    d_tolerance( ST::zero() ),
    d_symmetric( true ),
    d_planar( true )
{
  // Make sure that the surface is valid
  testPrecondition( g != ST::zero() || h != ST::zero() || j != ST::zero() );

  // Load linear term vector
  d_linear_term_vector[0] = g;
  d_linear_term_vector[1] = h;
  d_linear_term_vector[2] = j;

  typename ST::magnitudeType max = ST::magnitude( g );
  
  if( max < ST::magnitude( h ) )
    max = ST::magnitude( h );
  if( max < ST::magnitude( j ) )
    max = ST::magnitude( j );
  if( max < ST::magnitude( k ) )
    max = ST::magnitude( k );
  
  d_tolerance = tolerance_ratio*max;
}

//! Return if the point is on the surface
template<typename OrdinalType, typename ScalarType>
bool Surface<OrdinalType,ScalarType>::isOn( const Vector &point ) const
{
  if( d_planar )
  {
    return ST::magnitude( d_linear_term_vector.dot( point ) + 
			  d_constant_term ) < d_tolerance;
  }
  else
  {
    // x^T*A*x + b^t*x + c
    // x^T = row vector
    // x = column vector (default for serial dense vector)
    Vector Ax( 3 );
    Ax.multiply( Teuchos::NO_TRANS, 
		 Teuchos::NO_TRANS, 
		 1.0, 
		 d_quadratic_form_matrix,
		 point, 
		 0.0 );
    return ST::magnitude( point.dot( Ax ) + 
			  d_linear_term_vector.dot( point ) +
			  d_constant_term ) < d_tolerance;
  }
}

//! Return the sense of a point with respect to the surface
template<typename OrdinalType, typename ScalarType>
typename Surface<OrdinalType,ScalarType>::sense 
Surface<OrdinalType,ScalarType>::getSense( const Vector &point ) const
{
  ScalarType value;
  
  if( d_planar )
  {
    value = d_linear_term_vector.dot( point ) + d_constant_term;
  }
  else
  {
    // x^T*A*x + b^t*x + c
    // x^T = row vector
    // x = column vector (default for serial dense vector)
    Vector Ax( 3 );
    Ax.multiply( Teuchos::NO_TRANS, 
		 Teuchos::NO_TRANS, 
		 1.0, 
		 d_quadratic_form_matrix,
		 point, 
		 0.0 );
    value = point.dot( Ax ) + 
      d_linear_term_vector.dot( point ) +
      d_constant_term;
  }
  
  if( value > d_tolerance )
    return 1;
  else if( value < -d_tolerance )
    return -1;
  else 
    return 0;
}

//! Return the surface id
template<typename OrdinalType, typename ScalarType>
OrdinalType Surface<OrdinalType,ScalarType>::getId() const
{
  return d_id;
}

//! Return if the surface is planar
template<typename OrdinalType, typename ScalarType>
bool Surface<OrdinalType,ScalarType>::isPlanar() const
{
  return d_planar;
}

//! Return the unit normal from the surface at a point on the surface,
// pointing in the direction of the desired sense
template<typename OrdinalType, typename ScalarType>
typename Surface<OrdinalType,ScalarType>::Vector 
Surface<OrdinalType,ScalarType>::getUnitNormal( const Vector &point,
						const short sense ) const
{
  // The point must be on the surface
  testPrecondition( isOn( point ) );

  Vector gradient( 3 );
  
  if( d_planar )
    gradient = d_linear_term_vector;
  else
    gradient = getGradient( point );
  
  // Normalize the vector
  gradient.scale( 1.0/gradient.normFrobenius() );

  return gradient;
}

//! Return the quadratic form matrix of the surface
template<typename OrdinalType, typename ScalarType>
typename Surface<OrdinalType,ScalarType>::Matrix
Surface<OrdinalType,ScalarType>::getQuadraticFormMatrix() const
{
  return d_quadratic_form_matrix;
}

//! Return the linear term vector of the surface
template<typename OrdinalType, typename ScalarType>
typename Surface<OrdinalType,ScalarType>::Vector
Surface<OrdinalType,ScalarType>::getLinearTermVector() const
{
  return d_linear_term_vector;
}

//! Return the constant term of the surface
template<typename OrdinalType, typename ScalarType>
ScalarType Surface<OrdinalType,ScalarType>::getConstantTerm() const
{
  return d_constant_term;
}

//! Rotate the surface using the provided rotation matrix
void Surface::transformSurface( const Matrix &rotation_matrix,
				const Vector &translation_vector )
{
  // The rotation matrix must be valid (orthonormal)
  remember( Vector column_1( Teuchos::getCol( Teuchos::View, 
					      rotation_matrix, 
					      0 ) ) );
  remember( Vector column_2( Teuchos::getCol( Teuchos::View,
					      rotation_matrix,
					      1 ) ) );
  remember( Vector column_3( Teuchos::getCol( Teuchos::View,
					      rotations_matrix,
					      2 ) ) );
  remember( ScalarType column_1_magnitude = column_1.normFrobenius() );
  remember( ScalarType column_2_magnitude = column_2.normFrobenius() );
  remember( ScalarType column_3_magnitude = column_3.normFrobenius() );
  testPrecondition( ST::magnitude( column_1_magnitude - 1.0 ) < d_tolerance );
  testPrecondition( ST::magnitude( column_2_magnitude - 1.0 ) < d_tolerance );
  testPrecondition( ST::magnitude( column_3_magnitude - 1.0 ) < d_tolerance );
  testPrecondition( ST::magnitude( column_1.dot( column_2 ) ) < d_tolerance );
  testPrecondition( ST::magnitude( column_1.dot( column_3 ) ) < d_tolerance );
  testPrecondition( ST::magnitude( column_2.dot( column_3 ) ) < d_tolerance );
  
  if( d_planar )
  {
    d_constant_term += d_linear_term_vector.dot( translation_vector );

    d_linear_term_vector.multiply( Teuchos::TRANS, 
				   Teuchos::NO_TRANS,
				   1.0,
				   rotation_matrix,
				   d_linear_term_vector,
				   0.0 );
  }
  else
  {
    // Matrix rotation_matrix_transpose = 
    // LinearAlgebra::matrixTranspose( rotation_matrix );

    Vector Ax( 3 );
    Ax.multiply( Teuchos::NO_TRANS, 
		 Teuchos::NO_TRANS, 
		 1.0, 
		 d_quadratic_form_matrix,
		 translation_vector, 
		 0.0 );

    Vector Atx( 3 );
    Atx.multiply( Teuchos::TRANS,
		  Teuchos::NO_TRANS,
		  1.0,
		  d_quadratic_form_matrix,
		  translation_vector,
		  0.0 );

    Vector SA( 3, 3 );
    SA += Ax;
    SA += Atx;

    Vector AB( 3, 3 );
    AB.multiply( Teuchos::NO_TRANS,
		 Teuchos::NO_TRANS,
		 1.0,
		 d_quadratic_form_matrix,
		 rotation_matrix,
		 0.0 );

    // c' = b^t*x_0 + c
    d_constant_term +=
      translation_vector.dot( Ax ) +
      d_linear_term_vector.dot( translation_vector );

    // b' = B^t*(A+A^t)*x_0 + B^t*b
    d_linear_term_vector.multiply( Teuchos::TRANS, 
				   Teuchos::NO_TRANS,
				   1.0,
				   rotation_matrix,
				   d_linear_term_vector,
				   0.0 );
    
    d_linear_term_vector.multiply( Teuchos::TRANS,
				   Teuchos::NO_TRANS,
				   1.0,
				   rotation_matrix,
				   SA,
				   1.0 );

    d_quadratic_form_matrix.multiply( Teuchos::TRANS,
				      Teuchos::NO_TRANS,
				      1.0,
				      rotation_matrix,
				      AB,
				      0.0 );
  }  
}

//! Return the gradient of the surface at a given point
template<typename OrdinalType, typename ScalarType>
typename Surface<OrdinalType,ScalarType>::Vector 
Surface<OrdinalType,ScalarType>::getGradient( const Vector &point ) const
{
  // The point must be on the surface
  testPrecondition( isOn( point ) );
  
  // 2ax+dy+fz+g
  ScalarType x_gradient = 2*(d_quadratic_form_matrix(0,0)*point[0] +
			     d_quadratic_form_matrix(0,1)*point[1] +
			     d_quadratic_form_matrix(0,2)*point[2]) + 
    d_linear_term_vector[0];
  
  // 2by+dx+ez+h
  ScalarType y_gradient = 2*(d_quadratic_form_matrix(1,1)*point[1] +
			     d_quadratic_form_matrix(1,0)*point[0] +
			     d_quadratic_form_matrix(1,2)*point[2]) +
    d_linear_term_vector[1];
  
  // 2cz+ey+fx+j
  ScalarType z_gradient = 2*(d_quadratic_form_matrix(2,2)*point[2] +
			     d_quadratic_form_matrix(2,1)*point[1] +
			     d_quadratic_form_matrix(2,0)*point[0]) +
    d_linear_term_vector[2];
  
  Vector gradient( 3 );
  gradient[0] = x_gradient;
  gradient[1] = y_gradient;
  gradient[2] = z_gradient;
  
  return gradient;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end Surface_def.hpp
//---------------------------------------------------------------------------//

