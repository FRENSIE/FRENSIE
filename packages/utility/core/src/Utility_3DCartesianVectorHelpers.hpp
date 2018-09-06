//---------------------------------------------------------------------------//
//!
//! \file   Utility_3DCartesianVectorHelpers.hpp
//! \author Alex Robinson
//! \brief  3D Cartesian vector helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_3D_CARTESIAN_VECTOR_HELPERS_HPP
#define UTILITY_3D_CARTESIAN_VECTOR_HELPERS_HPP

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

//! Calculate the magnitude of a vector
double vectorMagnitude( const double x_component,
			const double y_component,
			const double z_component );

//! Calculate the magnitude of a vector
double vectorMagnitude( const double vector[3] );

//! Test if the vector is normalized (unit vector)
bool isUnitVector( const double vector[3] );

//! Test if the vector is normalized (unit vector)
bool isUnitVector( const double x_component,
                   const double y_component,
                   const double z_component );

//! Normalize the vector (create a unit vector)
void normalizeVector( double vector[3] );

//! Normalize the vector (create a unit vector)
void normalizeVector( double& x_component,
                      double& y_component,
                      double& z_component );

//! Normalize the vector and return the magnitude
double normalizeVectorAndReturnMagnitude( double vector[3] );

//! Normalize the vector and return the magnitude
double normalizeVectorAndReturnMagnitude( double& x_component,
                                          double& y_component,
                                          double& z_component );

//! Clear the vector of rounding errors
void clearVectorOfRoundingErrors( double vector[3],
                                  const double tol = 1e-15 );
  
//! Clear the vector of rounding errors
void clearVectorOfRoundingErrors( double& x_component,
                                  double& y_component,
                                  double& z_component,
                                  const double tol = 1e-15 );

//! Clear the unit vector of rounding errors
void clearUnitVectorOfRoundingErrors( double unit_vector[3],
                                      const double tol = 1e-15 );
  
//! Clear the unit vector of rounding errors
void clearUnitVectorOfRoundingErrors( double& x_component,
                                      double& y_component,
                                      double& z_component,
                                      double tol = 1e-15 );

//! Calculate the cosine of the angle between two vectors
double calculateCosineOfAngleBetweenVectors( const double vector_a[3],
					     const double vector_b[3] );

//! Calculate the cosine of the angle between two unit vectors
double calculateCosineOfAngleBetweenUnitVectors(
                                               const double unit_vector_a[3],
                                               const double unit_vector_b[3] );

//! Reflect a vector about the given unit normal
void reflectVector( const double vector[3],
                    const double unit_normal[3],
                    double reflected_vector[3] );

//! Reflect a unit vector about the given unit normal
void reflectUnitVector( const double unit_vector[3],
                        const double unit_normal[3],
                        double reflected_unit_vector[3] );

//! Convert the local vector to a global vector (coordinate transform)
void convertLocalVectorToGlobalVector(
              const double local_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double global_vector[3] );

//! Convert the local vector to a global vector (coordinate transform)
void convertLocalVectorToGlobalVector(
              const double local_x_coordinate,
              const double local_y_coordinate,
              const double local_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double& global_x_coordinate,
              double& global_y_coordinate,
              double& global_z_coordinate );

//! Convert the local vector to a global vector (coordinate transform)
void convertLocalVectorToGlobalVector(
              const double local_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double global_vector[3] );

//! Convert the local vector to a global vector (coordinate transform)
void convertLocalVectorToGlobalVector(
              const double local_x_coordinate,
              const double local_y_coordinate,
              const double local_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double& global_x_coordinate,
              double& global_y_coordinate,
              double& global_z_coordinate );

//! Convert the global vector to a local vector (coordinate transform)
void convertGlobalVectorToLocalVector(
              const double global_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double local_vector[3] );

//! Convert the global vector to a local vector (coordinate transform)
void convertGlobalVectorToLocalVector(
              const double global_x_coordinate,
              const double global_y_coordinate,
              const double global_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double& local_x_coordinate,
              double& local_y_coordinate,
              double& local_z_coordinate );

//! Convert the global vector to a local vector (coordinate transform)
void convertGlobalVectorToLocalVector(
              const double global_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double local_vector[3] );

//! Convert the global vector to a local vector (coordinate transform)
void convertGlobalVectorToLocalVector(
              const double global_x_coordinate,
              const double global_y_coordinate,
              const double global_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double& local_x_coordinate,
              double& local_y_coordinate,
              double& local_z_coordinate );

//! Rotate a vector through a polar and azimuthal angle
void rotateVectorThroughPolarAndAzimuthalAngle(
                                               const double polar_angle_cosine,
					       const double azimuthal_angle,
					       const double vector[3],
					       double rotated_vector[3] );

//! Rotate a unit vector through a polar and azimuthal angle
void rotateUnitVectorThroughPolarAndAzimuthalAngle(
                                               const double polar_angle_cosine,
					       const double azimuthal_angle,
					       const double unit_vector[3],
					       double rotated_unit_vector[3] );

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Calculate the magnitude of a vector
inline double vectorMagnitude( const double x_component,
			       const double y_component,
			       const double z_component )
{
  return sqrt( x_component*x_component + y_component*y_component +
	       z_component*z_component );
}

// Calculate the magnitude of a vector
inline double vectorMagnitude( const double vector[3] )
{
  return vectorMagnitude( vector[0], vector[1], vector[2] );
}

// Test if the vector is normalized (unit vector)
inline bool isUnitVector( const double vector[3] )
{
  return isUnitVector( vector[0], vector[1], vector[2] );
}

// Normalize the vector (create a unit vector)
inline void normalizeVector( double vector[3] )
{
  const double magnitude = normalizeVectorAndReturnMagnitude( vector );
}

// Normalize the vector (create a unit vector)
inline void normalizeVector( double& x_component,
                             double& y_component,
                             double& z_component )
{
  const double magnitude = normalizeVectorAndReturnMagnitude( x_component,
                                                              y_component,
                                                              z_component );
}

// Normalize the vector and return the magnitude
inline double normalizeVectorAndReturnMagnitude( double vector[3] )
{
  return normalizeVectorAndReturnMagnitude( vector[0], vector[1], vector[2] );
}

// Clear the vector of rounding errors
/*! \details This method will check if any components are within 
 * +/- tol*magnitude of 0.0. If so, they will be set to zero. These types
 * of rounding errors typically occur after rotations.
 */
inline void clearVectorOfRoundingErrors( double vector[3], const double tol )
{
  clearVectorOfRoundingErrors( vector[0], vector[1], vector[2], tol );
}

// Clear the unit vector of rounding errors
/*! \details This method will check if any components are within 
 * +/- tol of 0.0. If so, they will be set to zero. These types
 * of rounding errors typically occur after rotations.
 */
inline void clearUnitVectorOfRoundingErrors( double unit_vector[3],
                                             const double tol )
{
  clearUnitVectorOfRoundingErrors( unit_vector[0],
                                   unit_vector[1],
                                   unit_vector[2],
                                   tol );
}

// Calculate the cosine of the angle between two vectors
/*! \details This method will check if any components are within 
 * +/- tol of 0.0. If so, they will be set to zero. These types
 * of rounding errors typically occur after rotations.
 */
inline double calculateCosineOfAngleBetweenVectors( const double vector_a[3],
                                                    const double vector_b[3] )
{
  // Create unit vectors
  double unit_vector_a[3] = {vector_a[0], vector_a[1], vector_a[2]};

  normalizeVector( unit_vector_a );

  double unit_vector_b[3] = {vector_b[0], vector_b[1], vector_b[2]};

  normalizeVector( unit_vector_b );

  return calculateCosineOfAngleBetweenUnitVectors( unit_vector_a,
                                                   unit_vector_b );
}

// Reflect a vector about the given unit normal
inline void reflectVector( const double vector[3],
                           const double unit_normal[3],
                           double reflected_vector[3] )
{
  // Normalize the vector of interest
  double unit_vector[3] = {vector[0], vector[1], vector[2]};
  
  double magnitude = normalizeVectorAndReturnMagnitude( unit_vector );

  // Reflect the unit vector of interest
  reflectUnitVector( unit_vector, unit_normal, reflected_vector );

  // Scale the reflected vector
  reflected_vector[0] *= magnitude;
  reflected_vector[1] *= magnitude;
  reflected_vector[2] *= magnitude;
}

// Convert the local vector to a global vector (coordinate transform)
inline void convertLocalVectorToGlobalVector(
              const double local_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double global_vector[3] )
{
  convertLocalVectorToGlobalVector(
                              local_vector[0],
                              local_vector[1],
                              local_vector[2],
                              local_z_axis_unit_vector_wrt_global_coord_system,
                              local_origin_wrt_global_coord_system,
                              global_vector[0],
                              global_vector[1],
                              global_vector[2] );
}

// Convert the local vector to a global vector (coordinate transform)
inline void convertLocalVectorToGlobalVector(
              const double local_x_coordinate,
              const double local_y_coordinate,
              const double local_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double& global_x_coordinate,
              double& global_y_coordinate,
              double& global_z_coordinate )
{
  convertLocalVectorToGlobalVector(
                              local_x_coordinate,
                              local_y_coordinate,
                              local_z_coordinate,
                              local_z_axis_unit_vector_wrt_global_coord_system,
                              global_x_coordinate,
                              global_y_coordinate,
                              global_z_coordinate );

  // Shift the origin
  global_x_coordinate += local_origin_wrt_global_coord_system[0];
  global_y_coordinate += local_origin_wrt_global_coord_system[1];
  global_z_coordinate += local_origin_wrt_global_coord_system[2];
}

// Convert the local vector to a global vector (coordinate transform)
inline void convertLocalVectorToGlobalVector(
              const double local_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double global_vector[3] )
{
  convertLocalVectorToGlobalVector(
                              local_vector[0],
                              local_vector[1],
                              local_vector[2],
                              local_z_axis_unit_vector_wrt_global_coord_system,
                              global_vector[0],
                              global_vector[1],
                              global_vector[2] );
}

// Convert the global vector to a local vector (coordinate transform)
inline void convertGlobalVectorToLocalVector(
              const double global_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double local_vector[3] )
{
  convertGlobalVectorToLocalVector(
                              global_vector[0],
                              global_vector[1],
                              global_vector[2],
                              local_z_axis_unit_vector_wrt_global_coord_system,
                              local_origin_wrt_global_coord_system,
                              local_vector[0],
                              local_vector[1],
                              local_vector[2] );
}

// Convert the global vector to a local vector (coordinate transform)
inline void convertGlobalVectorToLocalVector(
              const double global_x_coordinate,
              const double global_y_coordinate,
              const double global_z_coordinate,
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              const double local_origin_wrt_global_coord_system[3],
              double& local_x_coordinate,
              double& local_y_coordinate,
              double& local_z_coordinate )
{
  // Shift the origin first
  convertGlobalVectorToLocalVector(
                 global_x_coordinate - local_origin_wrt_global_coord_system[0],
                 global_y_coordinate - local_origin_wrt_global_coord_system[1],
                 global_z_coordinate - local_origin_wrt_global_coord_system[2],
                 local_z_axis_unit_vector_wrt_global_coord_system,
                 local_x_coordinate,
                 local_y_coordinate,
                 local_z_coordinate );
}

// Convert the global vector to a local vector (coordinate transform)
inline void convertGlobalVectorToLocalVector(
              const double global_vector[3],
              const double local_z_axis_unit_vector_wrt_global_coord_system[3],
              double local_vector[3] )
{
  convertGlobalVectorToLocalVector(
                              global_vector[0],
                              global_vector[1],
                              global_vector[2],
                              local_z_axis_unit_vector_wrt_global_coord_system,
                              local_vector[0],
                              local_vector[1],
                              local_vector[2] );
}

// Rotate a vector through a polar and azimuthal angle
/*! \details The polar and azimuthal angles are with respect to the input
 * vector. The cosine of the polar angle should be passed as the first
 * argument instead of the polar angle. This is because the cosine of the
 * polar angle is commonly sampled and used much more often than the
 * polar angle. The azimuthal angle should be passed as the second argument
 * and not the cosine of the azimuthal angle. This is because the
 * azimuthal angle is often directly sampled.
 */
inline void rotateVectorThroughPolarAndAzimuthalAngle(
                                               const double polar_angle_cosine,
					       const double azimuthal_angle,
					       const double vector[3],
					       double rotated_vector[3] )
{
  // Make sure the polar angle is valid
  testPrecondition( polar_angle_cosine >= -1.0 );
  testPrecondition( polar_angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPrecondition( azimuthal_angle >= 0.0 );
  testPrecondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );

  // Calculate a unit vector from the input vector
  double unit_vector[3] = {vector[0], vector[1], vector[2]};

  double magnitude = normalizeVectorAndReturnMagnitude( unit_vector );

  // Rotate the unit vector
  rotateUnitVectorThroughPolarAndAzimuthalAngle( polar_angle_cosine,
                                                 azimuthal_angle,
                                                 unit_vector,
                                                 rotated_vector );

  // Scale the rotated unit vector
  rotated_vector[0] *= magnitude;
  rotated_vector[1] *= magnitude;
  rotated_vector[2] *= magnitude;
}

// Rotate a unit vector through a polar and azimuthal angle
/*! \details The polar and azimuthal angles are with respect to the input
 * unit vector. The cosine of the polar angle should be passed as the first
 * argument instead of the polar angle. This is because the cosine of the
 * polar angle is commonly sampled and used much more often than the
 * polar angle. The azimuthal angle should be passed as the second argument
 * and not the cosine of the azimuthal angle. This is because the
 * azimuthal angle is often directly sampled. 
 * Note: This method will be more efficient that the 
 * rotateVectorThroughPolarAndAzimuthalAngle method when dealing with a unit
 * vector (the vector magnitude will not be calculated since it is assumed
 * to be 1.0). Only a unit vector can be used with this method.
 */
inline void rotateUnitVectorThroughPolarAndAzimuthalAngle(
                                               const double polar_angle_cosine,
					       const double azimuthal_angle,
					       const double unit_vector[3],
					       double rotated_unit_vector[3] )
{
  // Make sure the polar angle is valid
  testPrecondition( polar_angle_cosine >= -1.0 );
  testPrecondition( polar_angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPrecondition( azimuthal_angle >= 0.0 );
  testPrecondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );
  // Make sure the unit vector is valid
  testPrecondition( isUnitVector( unit_vector ) );
  
  // Calculate the local rotated unit vector
  // Note: This is the rotated unit vector using the input unit vector as the
  // z-axis of a local coordinate system
  double polar_angle_sine =
    sqrt( std::max(0.0, 1.0 - polar_angle_cosine*polar_angle_cosine) );
  
  const double local_rotated_unit_vector[3] =
    {polar_angle_sine*cos(azimuthal_angle),
     polar_angle_sine*sin(azimuthal_angle),
     polar_angle_cosine};

  // Transform the local rotated unit vector to the global coordinate system
  convertLocalVectorToGlobalVector( local_rotated_unit_vector,
                                    unit_vector,
                                    rotated_unit_vector );

  // Clean roundoff errors
  normalizeVector( rotated_unit_vector );

  // Make sure that the rotated unit vector is valid
  testPostcondition( isUnitVector( rotated_unit_vector ) );
}
  
} // end Utility namespace

#endif // end UTILITY_3D_CARTESIAN_VECTOR_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_3DCartesianVectorHelpers.hpp
//---------------------------------------------------------------------------//
