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
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

/*! \defgroup three_space_traits_policies Three Space Type Traits and Policies
 * \ingroup traits
 * \ingroup policy
 *
 * Add description
 */

namespace FACEMC{

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
  //! Typedef for ordinal type
  typedef char ordinalType;
  
  //! The vector type that is used to represent points in three space
  typedef Teuchos::SerialDenseVector<ordinalType,ScalarType> Vector;
  
  //! The matrix type that is used in three space
  typedef Teuchos::SerialDenseMatrix<ordinalType,ScalarType> Matrix;

  //! Create a vector in \f$ R^3 \f$.
  static inline Vector createVector( const ScalarType x,
				     const ScalarType y,
				     const ScalarType z );

  //! Create a 3x3 matrix (for use in \f$ R^3 \f$).
  static inline Matrix createSquareMatrix( 
	    const ScalarType a00, const ScalarType a01, const ScalarType a02,
	    const ScalarType a10, const ScalarType a11, const ScalarType a12,
	    const ScalarType a20, const ScalarType a21, const ScalarType a22 );

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


