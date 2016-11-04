//---------------------------------------------------------------------------//
//!
//! \file   Geometry_VectorHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Vector helper function definitions.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_VECTOR_HELPERS_DEF_HPP
#define GEOMETRY_VECTOR_HELPERS_DEF_HPP

namespace Geometry{

// Create a vector
template<typename ScalarType>
Vector<ScalarType> createVector( const ScalarType x,
				 const ScalarType y,
				 const ScalarType z )
{
  return Vector<ScalarType>( x, y, z );
}

// Create a vector from a tuple struct
template<typename ScalarType>
Vector<ScalarType> createVector(
		 const Utility::Trip<ScalarType,ScalarType,ScalarType> &tuple )
{
  return Vector<ScalarType>( tuple );
}

// Create a x-axis vector
template<typename ScalarType>
Vector<ScalarType> createXAxisVector(
				 const Utility::AxisVectorDirection direction )
{
  if( direction == Utility::POSITIVE_DIRECTION )
    return Vector<ScalarType>( 1, 0, 0 );
  else
    return Vector<ScalarType>( -1, 0, 0 );
}

// Create a y-axis vector
template<typename ScalarType>
Vector<ScalarType> createYAxisVector(
				 const Utility::AxisVectorDirection direction )
{
  if( direction == Utility::POSITIVE_DIRECTION )
    return Vector<ScalarType>( 0, 1, 0 );
  else
    return Vector<ScalarType>( 0, -1, 0 );
}

// Create a z-axis vector
template<typename ScalarType>
Vector<ScalarType> createZAxisVector(
				 const Utility::AxisVectorDirection direction )
{
  if( direction == Utility::POSITIVE_DIRECTION )
    return Vector<ScalarType>( 0, 0, 1 );
  else
    return Vector<ScalarType>( 0, 0, -1 );
}

// Create a vector that satisfies the relationship n*x0+const = 0 (ret. x0)
template<typename ScalarType>
Vector<ScalarType> createZeroingVector( const Vector<ScalarType> &vector,
					const ScalarType constant_term )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  // The vector must be valid
  testPrecondition( !vector.isZeroVector() );

  ScalarType zeroing_term;

  if( ST::magnitude( vector[0] ) > ST::prec() )
  {
    zeroing_term = -constant_term/vector[0];

    return Vector<ScalarType>( zeroing_term, ST::zero(), ST::zero() );
  }
  else if( ST::magnitude( vector[1] ) > ST::prec() )
  {
    zeroing_term = -constant_term/vector[1];

    return Vector<ScalarType>( ST::zero(), zeroing_term, ST::zero() );
  }
  else
  {
    zeroing_term = -constant_term/vector[2];

    return Vector<ScalarType>( ST::zero(), ST::zero(), zeroing_term );
  }
}

} // end Geometry namespace

#endif // end GEOMETRY_VECTOR_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_VectorHelpers_def.hpp
//---------------------------------------------------------------------------//
