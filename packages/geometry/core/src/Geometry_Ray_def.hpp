//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Ray_def.hpp
//! \author Alex Robinson
//! \brief  Ray class definition
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_RAY_DEF_HPP
#define GEOMETRY_RAY_DEF_HPP

// Boost Includes
#include <boost/units/systems/cgs.hpp>

// FRENSIE Includes
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Constructor
template<typename LengthUnit>
UnitAwareRay<LengthUnit>::UnitAwareRay( const Length x_position,
                                        const Length y_position,
                                        const Length z_position,
                                        const double x_direction,
                                        const double y_direction,
                                        const double z_direction )
  : d_position( new Length[3] ),
    d_direction( new double[3] ),
    d_deep_copy_initialization( true )
{
  // Make sure the position is valid
  testPrecondition( !LQT::isnaninf( x_position ) );
  testPrecondition( !LQT::isnaninf( y_position ) );
  testPrecondition( !LQT::isnaninf( z_position ) );
  // Make sure the direction is a unit vector
  testPrecondition( Utility::isUnitVector( x_direction,
                                           y_direction,
                                           z_direction ) );

  d_position[0] = x_position;
  d_position[1] = y_position;
  d_position[2] = z_position;

  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Constructor
template<typename LengthUnit>
UnitAwareRay<LengthUnit>::UnitAwareRay( const Length position[3],
                                        const double direction[3] )
  : d_position( new Length[3] ),
    d_direction( new double[3] ),
    d_deep_copy_initialization( true )
{
  // Make sure the position and direction are valid
  testPrecondition( !LQT::isnaninf( d_position[0] ) );
  testPrecondition( !LQT::isnaninf( d_position[1] ) );
  testPrecondition( !LQT::isnaninf( d_position[2] ) );
  // Make sure the direction is a unit vector
  testPrecondition( Utility::isUnitVector( direction[0],
                                           direction[1],
                                           direction[2] ) );

  d_position[0] = position[0];
  d_position[1] = position[1];
  d_position[2] = position[2];

  d_direction[0] = direction[0];
  d_direction[1] = direction[1];
  d_direction[2] = direction[2];
}

// Constructor
/*! \details Warning: creating a shallow copy of the input pointers can be
 * dangerous (i.e. persistence of the data arrays must be guaranteed to avoid
 * undefined behavior and/or seg. faults). Only do this if you know what you're
 * doing!
 */
template<typename LengthUnit>
UnitAwareRay<LengthUnit>::UnitAwareRay( Length position[3],
                                        double direction[3],
                                        const bool deep_copy )
  : d_position( position ),
    d_direction( direction ),
    d_deep_copy_initialization( deep_copy )
{
  if( deep_copy )
  {
    // Make sure the position and direction are valid
    testPrecondition( !LQT::isnaninf( d_position[0] ) );
    testPrecondition( !LQT::isnaninf( d_position[1] ) );
    testPrecondition( !LQT::isnaninf( d_position[2] ) );
    // Make sure the direction is a unit vector
    testPrecondition( Utility::isUnitVector( direction[0],
                                             direction[1],
                                             direction[2] ) );
    d_position = new Length[3];
    d_position[0] = position[0];
    d_position[1] = position[1];
    d_position[2] = position[2];

    d_direction = new double[3];
    d_direction[0] = direction[0];
    d_direction[1] = direction[1];
    d_direction[2] = direction[2];
  }
}

// Destructor
template<typename LengthUnit>
UnitAwareRay<LengthUnit>::~UnitAwareRay()
{
  if( d_deep_copy_initialization )
  {
    delete[] d_position;
    delete[] d_direction;
  }
}

// Return the x position of the ray
template<typename LengthUnit>
auto UnitAwareRay<LengthUnit>::getXPosition() const -> Length
{
  return d_position[0];
}

// Return the y position of the ray
template<typename LengthUnit>
auto UnitAwareRay<LengthUnit>::getYPosition() const -> Length
{
  return d_position[1];
}

// Return the z position of the ray
template<typename LengthUnit>
auto UnitAwareRay<LengthUnit>::getZPosition() const -> Length
{
  return d_position[2];
}

// Return the position of the ray
template<typename LengthUnit>
auto UnitAwareRay<LengthUnit>::getPosition() const -> const Length*
{
  return d_position;
}

// Return the x direction of the ray
template<typename LengthUnit>
double UnitAwareRay<LengthUnit>::getXDirection() const
{
  return d_direction[0];
}

// Return the y direction of the ray
template<typename LengthUnit>
double UnitAwareRay<LengthUnit>::getYDirection() const
{
  return d_direction[1];
}

// Return the z direction of the ray
template<typename LengthUnit>
double UnitAwareRay<LengthUnit>::getZDirection() const
{
  return d_direction[2];
}

// Return the direction of the ray
template<typename LengthUnit>
const double* UnitAwareRay<LengthUnit>::getDirection() const
{
  return d_direction;
}

// Change the direction of the ray
template<typename LengthUnit>
void UnitAwareRay<LengthUnit>::changeDirection( const double direction[3] )
{
  // Make sure the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  // Deep copy the direction
  d_direction[0] = direction[0];
  d_direction[1] = direction[1];
  d_direction[2] = direction[2];
}

// Change the direction of the ray
template<typename LengthUnit>
void UnitAwareRay<LengthUnit>::changeDirection( const double x_direction,
                                                const double y_direction,
                                                const double z_direction )
{
  // Make sure the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction,
                                           y_direction,
                                           z_direction ) );

  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Advance the head along its direction by the requested distance
template<typename LengthUnit>
void UnitAwareRay<LengthUnit>::advanceHead( const Length distance )
{
  // Make sure the distance is valid
  testPrecondition( !LQT::isnaninf( distance ) );

  d_position[0] += d_direction[0]*distance;
  d_position[1] += d_direction[1]*distance;
  d_position[2] += d_direction[2]*distance;
}

// Print method implementation
template<typename LengthUnit>
void UnitAwareRay<LengthUnit>::toStream( std::ostream& os ) const
{
  os << "{{Position, {"
     << Utility::toString(d_position[0]) << ","
     << Utility::toString(d_position[1]) << ","
     << Utility::toString(d_position[2])
     << "}}, "
     << "{Direction, {"
     << Utility::toString(d_direction[0]) << ","
     << Utility::toString(d_direction[1]) << ","
     << Utility::toString(d_direction[2])
     << "}}}";
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareRay<void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareRay<boost::units::cgs::length> );

} // end Geometry namespace

#endif // end GEOMETRY_RAY_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_Ray_def.hpp
//---------------------------------------------------------------------------//
