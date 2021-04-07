//---------------------------------------------------------------------------//
//!
//! \file   Geometry_MatrixHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Matrix helper function definitions.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MATRIX_HELPERS_DEF_HPP
#define GEOMETRY_MATRIX_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Create a 3x3 matrix
template<typename ScalarType>
Matrix<ScalarType> createMatrix(
	    const ScalarType a00, const ScalarType a01, const ScalarType a02,
	    const ScalarType a10, const ScalarType a11, const ScalarType a12,
	    const ScalarType a20, const ScalarType a21, const ScalarType a22 )
{
  return Matrix<ScalarType>( a00, a01, a02,
			     a10, a11, a12,
			     a20, a21, a22 );
}

// Create a 3x3 symmetric matrix
template<typename ScalarType>
Matrix<ScalarType> createMatrix(
	    const ScalarType a00,
	    const ScalarType a10, const ScalarType a11,
	    const ScalarType a20, const ScalarType a21, const ScalarType a22 )
{
  return Matrix<ScalarType>( a00,
			     a10, a11,
			     a20, a21, a22 );
}

// Create a 3x3 matrix from row vectors
template<typename ScalarType>
Matrix<ScalarType> createMatrixFromRows( const Vector<ScalarType> row_1,
					 const Vector<ScalarType> row_2,
					 const Vector<ScalarType> row_3 )
{
  Matrix<ScalarType> new_matrix;

  new_matrix( 0, 0 ) = row_1[0];
  new_matrix( 0, 1 ) = row_1[1];
  new_matrix( 0, 2 ) = row_1[2];
  new_matrix( 1, 0 ) = row_2[0];
  new_matrix( 1, 1 ) = row_2[1];
  new_matrix( 1, 2 ) = row_2[2];
  new_matrix( 2, 0 ) = row_3[0];
  new_matrix( 2, 1 ) = row_3[1];
  new_matrix( 2, 2 ) = row_3[2];

  return new_matrix;
}

// Create a 3x3 matrix from columns
template<typename ScalarType>
Matrix<ScalarType> createMatrixFromColumns( const Vector<ScalarType> column_1,
					    const Vector<ScalarType> column_2,
					    const Vector<ScalarType> column_3 )
{
  Matrix<ScalarType> new_matrix;

  new_matrix( 0, 0 ) = column_1[0];
  new_matrix( 1, 0 ) = column_1[1];
  new_matrix( 2, 0 ) = column_1[2];
  new_matrix( 0, 1 ) = column_2[0];
  new_matrix( 1, 1 ) = column_2[1];
  new_matrix( 2, 1 ) = column_2[2];
  new_matrix( 0, 2 ) = column_3[0];
  new_matrix( 1, 2 ) = column_3[1];
  new_matrix( 2, 2 ) = column_3[2];

  return new_matrix;
}

// Generate a rotation matrix for rotation about the x-axis
template<typename ScalarType>
Matrix<ScalarType> createXAxisRotationMatrix( const ScalarType rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( ScalarType pi = acos( -1.0 ) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );

  ScalarType cos_angle = cos( rotation_angle );
  ScalarType sin_angle = sin( rotation_angle );

  Matrix<ScalarType> rotation_matrix( 1.0, 0.0,       0.0,
				      0.0, cos_angle, -sin_angle,
				      0.0, sin_angle, cos_angle );

  // The rotation matrix must be orthonormal
  testPostcondition( rotation_matrix.isOrthonormal() );

  return rotation_matrix;
}

// Generate a rotation matrix for rotation about the y-axis
template<typename ScalarType>
Matrix<ScalarType> createYAxisRotationMatrix( const ScalarType rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( ScalarType pi = acos( -1.0 ) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );

  ScalarType cos_angle = cos( rotation_angle );
  ScalarType sin_angle = sin( rotation_angle );

  Matrix<ScalarType> rotation_matrix( cos_angle,  0.0, sin_angle,
				      0.0,        1.0, 0.0,
				      -sin_angle, 0.0, cos_angle );

  // The rotation matrix must be orthonormal
  testPostcondition( rotation_matrix.isOrthonormal() );

  return rotation_matrix;
}

// Generate a rotation matrix for rotation about the z-axis
template<typename ScalarType>
Matrix<ScalarType> createZAxisRotationMatrix( const ScalarType rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( ScalarType pi = acos( -1.0 ) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );

  ScalarType cos_angle = cos( rotation_angle );
  ScalarType sin_angle = sin( rotation_angle );

  Matrix<ScalarType> rotation_matrix( cos_angle, -sin_angle, 0.0,
				      sin_angle, cos_angle,  0.0,
				      0.0,       0.0,        1.0 );

  // The rotation matrix must be orthonormal
  testPostcondition( rotation_matrix.isOrthonormal() );

  return rotation_matrix;
}

// Generate a rotation matrix that will rotate one unit vector to another.
template<typename ScalarType>
Matrix<ScalarType> createRotationMatrixFromUnitVectors(
				   const Vector<ScalarType> &initial_direction,
				   const Vector<ScalarType> &final_direction )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  // The initial direction must be a unit vector
  testPrecondition( ST::magnitude( initial_direction.normTwo() -
				   ST::one() ) < ST::prec() );
  // The final direction must be a unit vector
  testPrecondition( ST::magnitude( final_direction.normTwo() -
				   ST::one() ) < ST::prec() );
  // Both directions must be three space vectors
  testPrecondition( initial_direction.length() == 3 );
  testPrecondition( initial_direction.length() == 3 );

  ScalarType u_i = initial_direction[0];
  ScalarType v_i = initial_direction[1];
  ScalarType w_i = initial_direction[2];
  ScalarType arg_i = ST::squareroot( ST::one() - w_i*w_i );

  ScalarType u_f = final_direction[0];
  ScalarType v_f = final_direction[1];
  ScalarType w_f = final_direction[2];
  ScalarType arg_f = ST::squareroot( ST::one() - w_f*w_f );

  Matrix<ScalarType> initial_dir_to_zaxis_matrix;
  Matrix<ScalarType> zaxis_to_final_dir_matrix;

  // Create a rotation matrix for rotating the initial direction to the z-axis
  if( ST::magnitude( ST::magnitude( w_i ) - ST::one() ) > ST::prec() )
  {
    initial_dir_to_zaxis_matrix = createMatrix(
					  u_i*w_i/arg_i, v_i*w_i/arg_i, -arg_i,
					  -v_i/arg_i,    u_i/arg_i, ST::zero(),
					  u_i,           v_i,           w_i );
  }
  // The initial direction is parallel to the z-axis
  else if( w_i > ST::zero() )
  {
    initial_dir_to_zaxis_matrix.identity();
  }
  // The initial direction is anti-parallel to the z-axis
  else
  {
    initial_dir_to_zaxis_matrix = createMatrix(
					  ST::one(), ST::zero(), ST::zero(),
					  ST::zero(), ST::one(), ST::zero(),
					  ST::zero(), ST::zero(), -ST::one() );
  }

  // Create a rotation matrix for rotating the z-axis to the final direction
  if( ST::magnitude( ST::magnitude( w_f ) - ST::one() ) > ST::prec() )
  {
    zaxis_to_final_dir_matrix = createMatrix(
					      u_f*w_f/arg_f, -v_f/arg_f, u_f,
					      v_f*w_f/arg_f, u_f/arg_f,  v_f,
					      -arg_f,        ST::zero(), w_f );
  }
  // The final direction is parallel to the z-axis
  else if( w_f > ST::zero() )
    zaxis_to_final_dir_matrix.identity();
  // The final direction is anti-parallel to the z-axis
  else
  {
    zaxis_to_final_dir_matrix = createMatrix(
					  ST::one(), ST::zero(), ST::zero(),
					  ST::zero(), ST::one(), ST::zero(),
					  ST::zero(), ST::zero(), -ST::one() );
  }

  Matrix<ScalarType> rotation_matrix;

  rotation_matrix.multiply( ST::one(),
			    zaxis_to_final_dir_matrix,
			    false,
			    initial_dir_to_zaxis_matrix,
			    false,
			    ST::zero() );

  // The rotation matrix must be orthonormal
  testPostcondition( initial_dir_to_zaxis_matrix.isOrthonormal() );
  testPostcondition( zaxis_to_final_dir_matrix.isOrthonormal() );
  testPostcondition( rotation_matrix.isOrthonormal() );

  return rotation_matrix;
}

} // end Geometry namespace

#endif // GEOMETRY_MATRIX_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_MatrixHelpers_def.hpp
//---------------------------------------------------------------------------//
