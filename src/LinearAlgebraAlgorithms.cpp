//---------------------------------------------------------------------------//
// \file   LinearAlgebraAlgorithms.cpp
// \author Alex Robinson
// \brief  Function definitions for linear algebra algorithms
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>

// Trilinos Includes
#include <Teuchos_Tuple.hpp>

// FACEMC Includes
#include "LinearAlgebraAlgorithms.hpp"
#include "ContractException.hpp"

namespace FACEMC{
  
namespace LinearAlgebra{

//! Compute the magnitude of a vector
double vectorMagnitude( const Teuchos::Tuple<double,3> &vector )
{
  return sqrt( vector*vector );
}

//! Normalize a vector
void normalizeVector( Teuchos::Tuple<double,3> &vector )
{
  // the vector must be valid
  testPrecondition( vectorMagnitude( vector ) > 0 );
  
  double vector_magnitude = vectorMagnitude( vector );
  
  vector[0] /= vector_magnitude;
  vector[1] /= vector_magnitude;
  vector[2] /= vector_magnitude;
}

//! Compute the determinant of a 3x3 matrix
double matrixDeterminant( const Teuchos::Tuple<double,9> &matrix )
{
  /*     | a b c |
   * A = | d e f |
   *     | g h j |
   * det(A) = aej+bfg+cdh-ceg-bdj-afh
   */
  return matrix[0]*matrix[4]*matrix[8] +
    matrix[1]*matrix[5]*matrix[6] +
    matrix[2]*matrix[3]*matrix[7] -
    matrix[2]*matrix[4]*matrix[6] -
    matrix[1]*matrix[3]*matrix[8] -
    matrix[0]*matrix[5]*matrix[7];
}

//! Compute the transpose of a matrix
Teuchos::Tuple<double,9>
matrixTranspose( const Teuchos::Tuple<double,9> &matrix )
{
  return Teuchos::tuple( matrix[0], matrix[3], matrix[6],
			 matrix[1], matrix[4], matrix[7],
			 matrix[2], matrix[5], matrix[8] );
}

//! Compute the inverse of a 3x3 matrix
Teuchos::Tuple<double,9>
matrixInverse( const Teuchos::Tuple<double,9> &matrix )
{
  // The matrix must be valid
  testPrecondition( matrixDeterminant( matrix ) != 0.0 );

  double norm = fabs( 1/matrixDeterminant( matrix ) );

  double a_value = matrix[4]*matrix[8] - matrix[5]*matrix[7];
  double b_value = matrix[2]*matrix[7] - matrix[1]*matrix[8];
  double c_value = matrix[1]*matrix[5] - matrix[2]*matrix[4];
  double d_value = matrix[5]*matrix[6] - matrix[3]*matrix[8];
  double e_value = matrix[0]*matrix[8] - matrix[2]*matrix[6];
  double f_value = matrix[2]*matrix[3] - matrix[0]*matrix[5];
  double g_value = matrix[3]*matrix[7] - matrix[4]*matrix[6];
  double h_value = matrix[1]*matrix[6] - matrix[0]*matrix[7];
  double j_value = matrix[0]*matrix[4] - matrix[1]*matrix[3];

  return norm*Teuchos::tuple( a_value, b_value, c_value,
			      d_value, e_value, f_value,
			      g_value, h_value, j_value );
}

//! Generate a rotation matrix for rotation about the x-axis
Teuchos::Tuple<double,9>
generateXAxisRotationMatrix( const double rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( double pi = acos(-1.0) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );
  
  double cos_angle = cos( rotation_angle );
  double sin_angle = sin( rotation_angle );
  
  return Teuchos::tuple( 1.0, 0.0,       0.0,
			 0.0, cos_angle, -sin_angle,
			 0.0, sin_angle, cos_angle );
}

//! Generate a rotation matrix for rotation about the y-axis
Teuchos::Tuple<double,9>
generateYAxisRotationMatrix( const double rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( double pi = acos(-1.0) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );
  
  double cos_angle = cos( rotation_angle );
  double sin_angle = sin( rotation_angle );

  return Teuchos::tuple( cos_angle,  0.0, sin_angle,
			 0.0,        1.0, 0.0,
			 -sin_angle, 0.0, cos_angle );
}

//! Generate a rotation matrix for rotation about the z-axis
Teuchos::Tuple<double,9>
generateZAxisRotationMatrix( const double rotation_angle )
{
  // The rotation angle must be between -pi and pi
  remember( double pi = acos(-1.0) );
  testPrecondition( rotation_angle > -pi && rotation_angle <= pi );
  
  double cos_angle = cos( rotation_angle );
  double sin_angle = sin( rotation_angle );

  return Teuchos::tuple( cos_angle, -sin_angle, 0.0,
			 sin_angle, cos_angle,  0.0,
			 0.0,       0.0,        1.0 );
}

//! Generate a rotation matrix that will rotate a unit vector with a given
// direction to a unit vector with a desired direction
Teuchos::Tuple<double,9>
generateRotationMatrixFromUnitVectors( 
			      const Teuchos::Tuple<double,3> &initial_direction,
			      const Teuchos::Tuple<double,3> &final_direction )
{
  // The initial direction must be a unit vector
  testPrecondition( fabs(vectorMagnitude( initial_direction ) - 1.0) < 1e-12 );
  // The final direction must be a unit vector
  testPrecondition( fabs(vectorMagnitude( final_direction ) - 1.0) < 1e-12 );

  double u_i = initial_direction[0];
  double v_i = initial_direction[1];
  double w_i = initial_direction[2];
  double arg_i = sqrt( 1 - w_i*w_i );
  Teuchos::Tuple<double,9> initial_to_zaxis_matrix;

  double u_f = final_direction[0];
  double v_f = final_direction[1];
  double w_f = final_direction[2];
  double arg_f = sqrt( 1 - w_f*w_f );
  Teuchos::Tuple<double,9> zaxis_to_final_matrix;

  // Rotation matrix for rotating the initial direction to the z-axis
  if( fabs(fabs(w_i) - 1.0) > 1e-12 )
  {
    initial_to_zaxis_matrix =
      Teuchos::tuple( u_i*w_i/arg_i, v_i*w_i/arg_i, -arg_i,
		      -v_i/arg_i,    u_i/arg_i,     0.0,
		      u_i,           v_i,           w_i );
  }
  else if( w_i > 0.0 )
  {
    initial_to_zaxis_matrix = 
      Teuchos::tuple( 1.0, 0.0, 0.0,
		      0.0, 1.0, 0.0,
		      0.0, 0.0, 1.0 );
  }
  else
  {
    initial_to_zaxis_matrix =
      Teuchos::tuple( -1.0, 0.0,  0.0,
		       0.0, 1.0,  0.0,
		       0.0, 0.0, -1.0 );
  }

  // Rotation matrix for rotating the z-axis to the final direction
  if( fabs(fabs(w_f) - 1.0) > 1e-12 )
  {
    zaxis_to_final_matrix =
      Teuchos::tuple( u_f*w_f/arg_f, -v_f/arg_f, u_f,
		      v_f*w_f/arg_f, u_f/arg_f,  v_f,
		      -arg_f,        0.0,        w_f );
  }
  else if( w_f > 0.0 )
  {
    zaxis_to_final_matrix = 
      Teuchos::tuple( 1.0, 0.0, 0.0,
		      0.0, 1.0, 0.0,
		      0.0, 0.0, 1.0 );
  }
  else
  {
    zaxis_to_final_matrix =
      Teuchos::tuple( -1.0, 0.0,  0.0,
		       0.0, 1.0,  0.0,
		       0.0, 0.0, -1.0 );
  }
  
  return zaxis_to_final_matrix*initial_to_zaxis_matrix;
}

//! Solve a 3x3 linear system
Teuchos::Tuple<double,3>
solveSystem( const Teuchos::Tuple<double,9> &matrix,
	     const Teuchos::Tuple<double,3> &solution )
{
  // The matrix must be valid
  testPrecondition( matrixDeterminant( matrix ) != 0.0 );

  return matrixInverse( matrix )*solution;
}

//! Compute the eigenvalues of a 3x3 matrix
//Teuchos::Tuple<double,3>
//eigenvectors( const Teuchos::Tuple<double,9> &matrix )
//{
  // The matrix must be symmetric (positive eigenvalues only)
  //testPrecondition( matrix[1] == matrix[3] &&
  //		    matrix[2] == matrix[6] &&
  //		    matrix[5] == matrix[7] );
  
  //double alpha = -matrix[0] - matrix[4] - matrix[8];
  //double beta = matrix[0]*matrix[8] + matrix[4]*matrix[8] + 
  //matrix[0]*matrix[4] - matrix[2]*matrix[6] - matrix[1]*matrix[3] -
  //matrix[5]*matrix[7];
  //double gamma = -matrixDeterminant( matrix );

  //double discriminant = 18*alpha*beta*gamma - 4*alpha*alpha*alpha*gamma +
  //alpha*alpha*beta*beta - 4*beta*beta*beta - 27*gamma*gamma;

  //double eigenvalue_1 =

} // end LinearAlgebra namespace

} // end FACEMC namespace

//! Define the addition of two vectors
Teuchos::Tuple<double,3> operator+( const Teuchos::Tuple<double,3> &left_vector,
				    const Teuchos::Tuple<double,3> &right_vector )
{
  double x_value = left_vector[0] + right_vector[0];
  double y_value = left_vector[1] + right_vector[1];
  double z_value = left_vector[2] + right_vector[2];

  return Teuchos::tuple( x_value, y_value, z_value );
}

// Define the addition of two vectors (in place) 
void operator+=( Teuchos::Tuple<double,3> &left_vector,
		 const Teuchos::Tuple<double,3> &right_vector )
{
  left_vector[0] += right_vector[0];
  left_vector[1] += right_vector[1];
  left_vector[2] += right_vector[2];
}


//! Define the product of a scalar and a vector (premultiply)
Teuchos::Tuple<double,3> operator*( const double multiplier,
				    const Teuchos::Tuple<double,3> &vector )
{
  double x_value = multiplier*vector[0];
  double y_value = multiplier*vector[1];
  double z_value = multiplier*vector[2];

  return Teuchos::tuple( x_value, y_value, z_value );
}

//! Define the product of a scalar and a vector (postmultiply)
Teuchos::Tuple<double,3> operator*( const Teuchos::Tuple<double,3> &vector,
				    const double multiplier )
{
  double x_value = multiplier*vector[0];
  double y_value = multiplier*vector[1];
  double z_value = multiplier*vector[2];

  return Teuchos::tuple( x_value, y_value, z_value );
}

//! Define the product of a scalara and a vector (in place )
void operator*=( Teuchos::Tuple<double,3> &vector,
		 const double multiplier )
{
  vector[0] *= multiplier;
  vector[1] *= multiplier;
  vector[2] *= multiplier;
}

//! Define the product of a scalar and a matrix (premultiply)
Teuchos::Tuple<double,9> operator*( const double multiplier,
				    const Teuchos::Tuple<double,9> &matrix )
{
  double a_value = multiplier*matrix[0];
  double b_value = multiplier*matrix[1];
  double c_value = multiplier*matrix[2];
  double d_value = multiplier*matrix[3];
  double e_value = multiplier*matrix[4];
  double f_value = multiplier*matrix[5];
  double g_value = multiplier*matrix[6];
  double h_value = multiplier*matrix[7];
  double j_value = multiplier*matrix[8];

  return Teuchos::tuple( a_value, b_value, c_value,
			 d_value, e_value, f_value,
			 g_value, h_value, j_value );
}

//! Define the product of a scalar and a matrix (postmultiply)
Teuchos::Tuple<double,9> operator*( const Teuchos::Tuple<double,9> &matrix,
				    const double multiplier )
{
  double a_value = multiplier*matrix[0];
  double b_value = multiplier*matrix[1];
  double c_value = multiplier*matrix[2];
  double d_value = multiplier*matrix[3];
  double e_value = multiplier*matrix[4];
  double f_value = multiplier*matrix[5];
  double g_value = multiplier*matrix[6];
  double h_value = multiplier*matrix[7];
  double j_value = multiplier*matrix[8];

  return Teuchos::tuple( a_value, b_value, c_value,
			 d_value, e_value, f_value,
			 g_value, h_value, j_value );
}

//! Define the product of a scalar and a matrix (in place)
void operator*=( Teuchos::Tuple<double,9> &matrix,
		 const double multiplier )
{
  matrix[0] *= multiplier;
  matrix[1] *= multiplier;
  matrix[2] *= multiplier;
  matrix[3] *= multiplier;
  matrix[4] *= multiplier;
  matrix[5] *= multiplier;
  matrix[6] *= multiplier;
  matrix[7] *= multiplier;
  matrix[8] *= multiplier;
}


//! Define the dot product of a 1x3 row vector and a 3x1 column vector
double operator*( const Teuchos::Tuple<double,3> &left_vector,
		  const Teuchos::Tuple<double,3> &right_vector )
{
  return left_vector[0]*right_vector[0] +
    left_vector[1]*right_vector[1] +
    left_vector[2]*right_vector[2];
}

//! Define the product of a 1x3 row vector and a 3x3 matrix
Teuchos::Tuple<double,3> operator*( const Teuchos::Tuple<double,3> &vector,
				    const Teuchos::Tuple<double,9> &matrix )
{
  double x_value = vector[0]*matrix[0] + vector[1]*matrix[3] + 
    vector[2]*matrix[6];
  
  double y_value = vector[0]*matrix[1] + vector[1]*matrix[4] +
    vector[2]*matrix[7];

  double z_value = vector[0]*matrix[2] + vector[1]*matrix[5] +
    vector[2]*matrix[8];

  return Teuchos::tuple( x_value, y_value, z_value );
}

//! Define the product of a 3x3 matrix and a 3x1 column vector
Teuchos::Tuple<double,3> operator*( const Teuchos::Tuple<double,9> &matrix,
				    const Teuchos::Tuple<double,3> &vector )
{
  double x_value = matrix[0]*vector[0] + matrix[1]*vector[1] + 
    matrix[2]*vector[2];
  
  double y_value = matrix[3]*vector[0] + matrix[4]*vector[1] +
    matrix[5]*vector[2];

  double z_value = matrix[6]*vector[0] + matrix[7]*vector[1] +
    matrix[8]*vector[2];

  return Teuchos::tuple( x_value, y_value, z_value );
}

//! Define the product of two 3x3 matrices
Teuchos::Tuple<double,9> operator*( const Teuchos::Tuple<double,9> &left_matrix,
				    const Teuchos::Tuple<double,9> &right_matrix )
{
  double a_value = left_matrix[0]*right_matrix[0] + 
    left_matrix[1]*right_matrix[3] +
    left_matrix[2]*right_matrix[6];

  double b_value = left_matrix[0]*right_matrix[1] +
    left_matrix[1]*right_matrix[4] +
    left_matrix[2]*right_matrix[7];

  double c_value = left_matrix[0]*right_matrix[2] +
    left_matrix[1]*right_matrix[5] +
    left_matrix[2]*right_matrix[8];

  double d_value = left_matrix[3]*right_matrix[0] +
    left_matrix[4]*right_matrix[3] +
    left_matrix[5]*right_matrix[6];

  double e_value = left_matrix[3]*right_matrix[1] +
    left_matrix[4]*right_matrix[4] +
    left_matrix[5]*right_matrix[7];
  
  double f_value = left_matrix[3]*right_matrix[2] +
    left_matrix[4]*right_matrix[5] +
    left_matrix[5]*right_matrix[8];

  double g_value = left_matrix[6]*right_matrix[0] +
    left_matrix[7]*right_matrix[3] +
    left_matrix[8]*right_matrix[6];

  double h_value = left_matrix[6]*right_matrix[1] +
    left_matrix[7]*right_matrix[4] +
    left_matrix[8]*right_matrix[7];

  double j_value = left_matrix[6]*right_matrix[2] +
    left_matrix[7]*right_matrix[5] +
    left_matrix[8]*right_matrix[8];

  return Teuchos::tuple( a_value, b_value, c_value,
			 d_value, e_value, f_value,
			 g_value, h_value, j_value );
}

//---------------------------------------------------------------------------//
// end LinearAlgebraAlgorithms.cpp
//---------------------------------------------------------------------------//
