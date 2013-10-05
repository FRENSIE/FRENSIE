//---------------------------------------------------------------------------//
//! 
//! \file   ThreeSpaceTraitsAndPolicyDecl.hpp
//! \author Alex Robinson
//! \brief  Three space traits and policy declaration.
//!
//---------------------------------------------------------------------------//

#ifndef THREE_SPACE_TRAITS_AND_POLICY_DECL_HPP
#define THREE_SPACE_TRAITS_AND_POLICY_DECL_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_OrdinalTraits.hpp>
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

/*! \defgroup three_space_traits_policies Three Space Type Traits and Policies
 * \ingroup traits
 * \ingroup policy
 *
 * Add description
 */

namespace FACEMC{
  
  //! Direction of the axis vector that will be created
  enum AxisVectorDirection{
    POSITIVE_DIRECTION,
    NEGATIVE_DIRECTION
  };

/*! \brief This struct provides some convenient typedefs and functions
 * for use in three space.
 * \ingroup three_space_traits_policies
 * 
 * Specializations aren't required for this struct since the SerialDense
 * classes already give compile time errors if the scalar type does not have 
 * a specialization.
 */
template<typename ScalarType>
struct ThreeSpaceTraitsAndPolicy
{
  
public:
  
  //! Typedef for ordinal type
  typedef char ordinalType;

private:
  
  //! Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  //! Typedef for OrdinalTraits
  typedef Teuchos::OrdinalTraits<ordinalType> OT;
  
public:
  
  //! The vector type that is used to represent points in three space
  typedef Teuchos::SerialDenseVector<ordinalType,ScalarType> Vector;
  
  //! The matrix type that is used in three space
  typedef Teuchos::SerialDenseMatrix<ordinalType,ScalarType> Matrix;

  //! The x-axis
  static inline Vector xaxisVector( 
			  AxisVectorDirection direction = POSITIVE_DIRECTION );

  //! The y-axis
  static inline Vector yaxisVector( 
			  AxisVectorDirection direction = POSITIVE_DIRECTION );

  //! The z-axis
  static inline Vector zaxisVector( 
			  AxisVectorDirection direction = POSITIVE_DIRECTION );

  //! The zero matrix
  static inline Matrix zeroMatrix();

  //! The identity matrix
  static inline Matrix identityMatrix();

  //! Create a vector in \f$ R^3 \f$.
  static inline Vector createVector( const ScalarType x,
				     const ScalarType y,
				     const ScalarType z );

  //! Create a 3x3 matrix (for use in \f$ R^3 \f$).
  static inline Matrix createSquareMatrix( 
	    const ScalarType a00, const ScalarType a01, const ScalarType a02,
	    const ScalarType a10, const ScalarType a11, const ScalarType a12,
	    const ScalarType a20, const ScalarType a21, const ScalarType a22 );

  //! Create a 3x3 matrix (for use in \f$ R^3 \f$).
  static Matrix createSquareMatrixFromColumns( const Vector column_1,
					       const Vector column_2,
					       const Vector column_3 );

  //! Create a 3x3 matrix (for use in \f$ R^3 \f$).
  static Matrix createSquareMatrixFromRows( const Vector row_1,
					    const Vector row_2,
					    const Vector row_3 );

  //! Create a symmetric 3x3 matrix (for use in \f$ r^3 \f$).
  static inline Matrix createSymmetricMatrix( 
	    const ScalarType a00, const ScalarType a01, const ScalarType a02,
	                          const ScalarType a11, const ScalarType a12, 
	                                                const ScalarType a22 );
};

} // end FACEMC namespace

#endif // end THREE_SPACE_TRAITS_AND_POLICY_DECL_HPP

//---------------------------------------------------------------------------//
// end ThreeSpaceTraitsAndPolicyDecl.hpp
//---------------------------------------------------------------------------//


