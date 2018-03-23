//---------------------------------------------------------------------------//
//!
//! \file   Utility_3DCartesianVectorHelpers.cpp
//! \author Alex Robinson
//! \brief  3D Cartesian vector helper function definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

// Test if the vector is normalized (unit vector)
bool isUnitVector( const double x_component,
                   const double y_component,
                   const double z_component )
{
  // Make sure that the coordinates are valid
  remember( typedef QuantityTraits<double> QT );
  testPrecondition( !QT::isnaninf( x_component ) );
  testPrecondition( !QT::isnaninf( y_component ) );
  testPrecondition( !QT::isnaninf( z_component ) );

  double argument =
    vectorMagnitude( x_component, y_component, z_component ) - 1.0;
  argument = fabs( argument );

  return argument < 1e-15;
}

// Normalize the vector and return the magnitude
double normalizeVectorAndReturnMagnitude( double& x_component,
                                          double& y_component,
                                          double& z_component )
{
  // Make sure that the coordinates are valid
  remember( typedef QuantityTraits<double> QT );
  testPrecondition( !QT::isnaninf( x_component ) );
  testPrecondition( !QT::isnaninf( y_component ) );
  testPrecondition( !QT::isnaninf( z_component ) );

  double magnitude = vectorMagnitude( x_component, y_component, z_component );

  x_component /= magnitude;
  y_component /= magnitude;
  z_component /= magnitude;

  return magnitude;
}

// Clear the vector of rounding errors
/*! \details This method will check if any components are within
 * +/- tol*magnitude of 0.0. If so, they will be set to zero. These types
 * of rounding errors typically occur after rotations.
 */
void clearVectorOfRoundingErrors( double& x_component,
                                  double& y_component,
                                  double& z_component,
                                  const double tol )
{
  // Calculate the vector magnitude
  const double magnitude =
    vectorMagnitude( x_component, y_component, z_component );

  // Check the x-component
  if( fabs( x_component ) < tol*magnitude )
    x_component = 0.0;

  // Check the y-component
  if( fabs( y_component ) < tol*magnitude )
    y_component = 0.0;

  // Check the z-component
  if( fabs( z_component ) < tol*magnitude )
    z_component = 0.0;
}

// Clear the unit vector of rounding errors
/*! \details This method will check if any components are within
 * +/- tol of 0.0. If so, they will be set to zero. These types
 * of rounding errors typically occur after rotations.
 */
void clearUnitVectorOfRoundingErrors( double& x_component,
                                      double& y_component,
                                      double& z_component,
                                      const double tol )
{
  // Make sure that the unit vectors is valid
  testPrecondition( isUnitVector( x_component, y_component, z_component ) );

  // Check the x-component
  if( fabs( x_component ) < tol )
    x_component = 0.0;

  // Check the y-component
  if( fabs( y_component ) < tol )
    y_component = 0.0;

  // Check the z-component
  if( fabs( z_component ) < tol )
    z_component = 0.0;

  // Re-normalize the unit vector
  normalizeVector( x_component, y_component, z_component );
}

// Calculate the cosine of the angle between two unit vectors
/*! \details This method will be more efficient than the
 * calculateCosineOfAngleBetweenUnitVectors method when dealing with
 * unit vectors (vector magnitudes will not be calculated since it is assumed
 * that they are 1.0). Only unit vectors can be used with this method.
 */
double calculateCosineOfAngleBetweenUnitVectors(
                                                const double unit_vector_a[3],
                                                const double unit_vector_b[3] )
{
  // Make sure that the unit vectors are valid
  testPrecondition( isUnitVector( unit_vector_a ) );
  testPrecondition( isUnitVector( unit_vector_b ) );

  double angle_cosine = unit_vector_a[0]*unit_vector_b[0] +
    unit_vector_a[1]*unit_vector_b[1] + unit_vector_a[2]*unit_vector_b[2];

  // Check for round-off error
  if( fabs( angle_cosine ) > 1.0 )
    angle_cosine = copysign( 1.0, angle_cosine );

  // Make sure the angle cosine is valid
  testPostcondition( angle_cosine >= -1.0 );
  testPostcondition( angle_cosine <= 1.0 );

  return angle_cosine;
}

// Reflect a unit vector about the given unit normal
/*! \details This method will be more efficient than the reflectVector method
 * when dealing with a unit vector (the vector magnitude will not be
 * calculated since it is assumed to be 1.0). Only a unit vector can be used
 * with this method.
 */
void reflectUnitVector( const double unit_vector[3],
                        const double unit_normal[3],
                        double reflected_unit_vector[3] )
{
  // Make sure that the unit vectors are valid
  testPrecondition( isUnitVector( unit_vector ) );
  testPrecondition( isUnitVector( unit_normal ) );

  // Calculate the angle cosine between the unit vector and unit normal
  double angle_cosine =
    calculateCosineOfAngleBetweenUnitVectors( unit_vector, unit_normal );

  reflected_unit_vector[0] = unit_vector[0] - 2.0*angle_cosine*unit_normal[0];
  reflected_unit_vector[1] = unit_vector[1] - 2.0*angle_cosine*unit_normal[1];
  reflected_unit_vector[2] = unit_vector[2] - 2.0*angle_cosine*unit_normal[2];

  // Make sure that the reflect unit vector is valid
  testPostcondition( isUnitVector( reflected_unit_vector ) );
}

// Convert the local vector to a global vector (coordinate transform)
/*! \details The transformation can be represented with the following equation:
 * V_g = R_lg*V_l + LO_g, where R_lg is the rotation matrix representing a
 * rotation of the local coordinate system to the global coordinate system and
 * LO_g is the local origin w.r.t. the global coordinate system. Note that
 * the local z-axis unit vector w.r.t. the global coordinate system is (u,v,w).
 * R_lg = [u*w/sqrt(1-w*w), -v/sqrt(1-w*w), u;
 *         v*w/sqrt(1-w*w), u/sqrt(1-w*w) , v;
 *         -sqrt(1-w*w)   , 0             , w]
 * LO_g = [x_O, y_O, z_O]
 * If w ~ 1 then sqrt(1-w*w) ~ 0 and we must assume that the spherical
 * coordinates of the local z-axis w.r.t. the global coordinate system are
 * measure w.r.t. the y-axis. For this special case R_lg has the following
 * form:
 * R_lg_special = [w/sqrt(1-v*v) , -u*v/sqrt(1-v*v), u;
 *                 0             , sqrt(1-v*v)     , v;
 *                 -u/sqrt(1-v*v), -v*w/sqrt(1-v*v) , w]
 * If the origin of the local coordinate system is different than the origin
 * of the global coordinate system, the local origin's coordinates must be
 * added to the global coordinates returned from this method
 * (e.g. x = global_x_coordinate + x_O);
 */
void convertLocalVectorToGlobalVector(
              const double local_x_coordinate,
              const double local_y_coordinate,
              const double local_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double& global_x_coordinate,
              double& global_y_coordinate,
              double& global_z_coordinate )
{
  // Make sure that the unit vector is valid
  testPrecondition( isUnitVector( local_z_axis_unit_vector_wrt_global_coord_system ) );

  // Create shorthand for local z-axis components
  double u = local_z_axis_unit_vector_wrt_global_coord_system[0];
  double v = local_z_axis_unit_vector_wrt_global_coord_system[1];
  double w = local_z_axis_unit_vector_wrt_global_coord_system[2];

  // Calculate the polar angle sine
  double polar_angle_sine = sqrt( std::max(0.0, 1.0 - w*w) );

  if( polar_angle_sine > 1e-10 )
  {
    global_x_coordinate = u*local_z_coordinate +
      (u*w*local_x_coordinate - v*local_y_coordinate)/polar_angle_sine;

    global_y_coordinate = v*local_z_coordinate +
      (v*w*local_x_coordinate + u*local_y_coordinate)/polar_angle_sine;

    global_z_coordinate = w*local_z_coordinate -
      polar_angle_sine*local_x_coordinate;
  }
  // Special case: polar_angle_sine ~ 0.0 (z ~ 1.0)
  //               Assume spherical coordinates are w.r.t. y-axis instead of
  //               z-axis
  else
  {
    // Recompute the polar angle sine
    polar_angle_sine = sqrt( std::max(0.0, 1.0 - v*v) );

    global_x_coordinate = u*local_z_coordinate +
      (w*local_x_coordinate - u*v*local_y_coordinate)/polar_angle_sine;

    global_y_coordinate = v*local_z_coordinate +
      polar_angle_sine*local_y_coordinate;

    global_z_coordinate = w*local_z_coordinate -
      (u*local_x_coordinate + w*v*local_y_coordinate)/polar_angle_sine;
  }
}

// Convert the global vector to a local vector (coordinate transform)
/*! \details The transformation can be represented with the following equation:
 * V_l = R_gl*(V_g - LO_g), where R_gl is the rotation matrix representing
 * a rotation of the global coordinate system to the local coordinate system
 * and LO_g is the local origin w.r.t. the global coordinate system. Note that
 * the local z-axis unit vector w.r.t. the global coordinate system is (u,v,w).
 * R_gl = [u*w/sqrt(1-w*w), v*w/sqrt(1-w*w), -sqrt(1-w*w);
 *         -v/sqrt(1-w*w) , u/sqrt(1-w*w)  , 0;
 *         u              , v              , w]
 * LO_g = [x_O, y_O, z_O]
 * If w ~ 1 then sqrt(1-w*w) ~ 0 and we must assume that the spherical
 * coordinates of the local z-axis w.r.t. the global coordinate system are
 * measured w.r.t. the y-axis. For this special case R_gl has the following
 * form:
 * R_gl_special = [w/sqrt(1-v*v)   , 0           , -u/sqrt(1-v*v);
 *                 -u*v/sqrt(1-v*v), sqrt(1-v*v) , -v*w/sqrt(1-v*v);
 *                 u               , v           , w]
 * If the origin of the local coordinate system is different than the origin
 * of the global coordinate system, the shifted coordinates must be passed
 * into this method (e.g. global_x_coordinate = x - x_O).
 */
void convertGlobalVectorToLocalVector(
              const double global_x_coordinate,
              const double global_y_coordinate,
              const double global_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double& local_x_coordinate,
              double& local_y_coordinate,
              double& local_z_coordinate )
{
  // Make sure that the unit vector is valid
  testPrecondition( isUnitVector( local_z_axis_unit_vector_wrt_global_coord_system ) );

  // Create shorthand for local z-axis components
  double u = local_z_axis_unit_vector_wrt_global_coord_system[0];
  double v = local_z_axis_unit_vector_wrt_global_coord_system[1];
  double w = local_z_axis_unit_vector_wrt_global_coord_system[2];

  // Calculate the polar angle sine
  double polar_angle_sine = sqrt( std::max(0.0, 1.0 - w*w) );

  if( polar_angle_sine > 1e-10 )
  {
    local_x_coordinate = -polar_angle_sine*global_z_coordinate +
      (u*w*global_x_coordinate + v*w*global_y_coordinate)/polar_angle_sine;

    local_y_coordinate =
      (-v*global_x_coordinate + u*global_y_coordinate)/polar_angle_sine;

    local_z_coordinate =
      u*global_x_coordinate + v*global_y_coordinate + w*global_z_coordinate;
  }
  // Special case: polar_angle_sine ~ 0.0 (z ~ 1.0)
  //               Assume spherical coordinates are w.r.t. y-axis instead of
  //               z-axis
  else
  {
    // Recompute the polar angle sine
    polar_angle_sine = sqrt( std::max(0.0, 1.0 - v*v) );

    local_x_coordinate =
      (w*global_x_coordinate - u*global_z_coordinate)/polar_angle_sine;

    local_y_coordinate = polar_angle_sine*global_y_coordinate -
      (u*v*global_x_coordinate + w*v*global_z_coordinate)/polar_angle_sine;

    local_z_coordinate = u*global_x_coordinate + v*global_y_coordinate +
      w*global_z_coordinate;
  }
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_3DCartesianVectorHelpers.cpp
//---------------------------------------------------------------------------//
