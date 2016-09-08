//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Surface.hpp
//! \author Alex Robinson
//! \brief  Surface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_SURFACE_HPP
#define GEOMETRY_SURFACE_HPP

// Trilinos Includes
#include <Teuchos_SerialDenseMatrix.hpp>
#include <Teuchos_SerialDenseVector.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_OrdinalTraits.hpp>
#include <Teuchos_Tuple.hpp>

// FRENIE Includes
#include "Geometry_ThreeSpaceObject.hpp"
#include "Geometry_Vector.hpp"
#include "Geometry_Matrix.hpp"
#include "Utility_PrintableObject.hpp"

namespace Geometry{

//! Surface sense enumeration
enum SurfaceSense{
  POS_SURFACE_SENSE,
  NEG_SURFACE_SENSE,
  ON_SURFACE
};

template<typename OrdinalType, typename ScalarType>
class Surface : public Utility::PrintableObject, public ThreeSpaceObject
{

public:

  //@{
  //! Typedefs
  //! Typedef for ordinal type (only used for surface ids)
  typedef OrdinalType ordinalType;
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //@}

private:

  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  //! Typedef for ordinal traits
  typedef Teuchos::OrdinalTraits<OrdinalType> OT;
  //! Typedef for Teuchos::Tuple index
  typedef typename Teuchos::Tuple<ScalarType,10>::Ordinal tupleIndex;
  //! Typedef for Teuchos::Tuple ordinal traits
  typedef Teuchos::OrdinalTraits<tupleIndex> Tuple_OT;

public:

  //! General Surface Constructor.
  // \details ax^2+by^2+cz^2+dxy+eyz+fxz+gx+hy+jz+k = 0
  Surface( OrdinalType id,
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
	   ScalarType tolerance_ratio = ST::prec() );

  //! Symmetric 2nd order surface constructor.
  Surface( OrdinalType id,
	   ScalarType a,
	   ScalarType b,
	   ScalarType c,
	   ScalarType g,
	   ScalarType h,
	   ScalarType j,
	   ScalarType k,
	   ScalarType tolerance_ratio = ST::prec() );

  //! Planar surface constructor.
  Surface( OrdinalType id,
	   ScalarType g,
	   ScalarType h,
	   ScalarType j,
	   ScalarType k,
	   ScalarType tolerance_ratio = ST::prec() );

  //! Construct surface by translating another surface
  Surface( OrdinalType id,
	   const Surface<OrdinalType,ScalarType> &original_surface,
	   const Vector<ScalarType> &translation_vector );

  //! Construct surface by rotating another surface
  Surface( OrdinalType id,
	   const Surface<OrdinalType,ScalarType> &original_surface,
	   const Matrix<ScalarType> &rotation_matrix );

  //! Construct surface by conducting a general transform on another surface
  Surface( OrdinalType id,
	   const Surface<OrdinalType,ScalarType> &original_surface,
	   const Matrix<ScalarType> &rotation_matrix,
	   const Vector<ScalarType> &translation_vector );

  //! Destructor.
  virtual ~Surface()
  { /* ... */ }

  //! Return if the point is on the surface.
  bool isOn( const ScalarType x,
	     const ScalarType y,
	     const ScalarType z ) const;

  //! Return if the point is on the surface.
  bool isOn( const Vector<ScalarType> &point ) const;

  //! Return if the surface is planar.
  bool isPlanar() const;

  //! Return if the surface is symmetric
  bool isSymmetric() const;

  //! Return the surface id.
  OrdinalType getId() const;

  //! Return the sense of a point with respect to the surface.
  SurfaceSense getSenseOfPoint( const ScalarType x,
				const ScalarType y,
				const ScalarType z ) const;

  //! Return the sense of a point with respect to the surface.
  SurfaceSense getSenseOfPoint( const Vector<ScalarType> &point ) const;

  //! Return the unit normal from the surface at a point on the surface, pointing in the direction of the desired sense.
  Vector<ScalarType> getUnitNormalAtPoint(
			  const ScalarType x,
			  const ScalarType y,
			  const ScalarType z,
			  const SurfaceSense sense = POS_SURFACE_SENSE ) const;

  //! Return the unit normal from the surface at a point on the surface, pointing in the direction of the desired sense.
  Vector<ScalarType> getUnitNormalAtPoint(
			  const Vector<ScalarType> &point,
			  const SurfaceSense sense = POS_SURFACE_SENSE ) const;

  //! Return the distance to the surface from the given point along the given direction
  ScalarType getDistance( const ScalarType x,
			  const ScalarType y,
			  const ScalarType z,
			  const ScalarType x_direction,
			  const ScalarType y_direction,
			  const ScalarType z_direction ) const;

  //! Return the distance to the surface from the given point along the given direction
  ScalarType getDistance( const Vector<ScalarType> &point,
			  const Vector<ScalarType> &direction ) const;

  //! Return the quadratic form matrix of the surface
  Matrix<ScalarType> getQuadraticFormMatrix() const;

  //! Return the linear term vector of the surface
  Vector<ScalarType> getLinearTermVector() const;

  //! Return the constant term of the surface
  ScalarType getConstantTerm() const;

  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;

protected:

  //! Calculate and set the tolerance based on the tolerance ratio.
  void setTolerance( ScalarType tolerance_ratio );

  //! Filter out small values that can be calculated from a transform.
  void filterDefinition( ScalarType cutoff_value = ST::prec() );

  //! Check if the surface symmetry has changed after a transform (change d_symmetric if so).
  void checkSymmetry();

  //! Evaluate the surface definition at a point.
  ScalarType evaluateSurface( const ScalarType x,
			      const ScalarType y,
			      const ScalarType z ) const;

  //! Evaluate planar surface.
  ScalarType evaluatePlanarSurface( const ScalarType x,
				    const ScalarType y,
				    const ScalarType z ) const;

  //! Evaluate symmetric 2nd order surface
  ScalarType evaluateSymmetricSecondOrderSurface( const ScalarType x,
						  const ScalarType y,
						  const ScalarType z ) const;

  //! Evaluate general 2nd order surface
  ScalarType evaluateGeneralSecondOrderSurface( const ScalarType x,
						const ScalarType y,
						const ScalarType z ) const;

  //! Calculate the alpha parameter of a given direction
  ScalarType calculateAlphaParameter( const ScalarType x_direction,
				      const ScalarType y_direction,
				      const ScalarType z_direction ) const;

  //! Calculate the beta parameter of a given direction and point
  ScalarType calculateBetaParameter( const ScalarType x,
				     const ScalarType y,
				     const ScalarType z,
				     const ScalarType x_direction,
				     const ScalarType y_direction,
				     const ScalarType z_direction ) const;

  //! Calculate the gamma parameter of a given point
  ScalarType calculateGammaParameter( const ScalarType x,
				      const ScalarType y,
				      const ScalarType z ) const;

  //! Compute the minimum real positive root of a second order polynomial
  ScalarType calculateMinimumRealPositiveRoot( const ScalarType alpha,
					       const ScalarType beta,
					       const ScalarType gamma ) const;

  //! Compute the root of a first order polynomial
  ScalarType calculateRoot( const ScalarType beta,
			    const ScalarType gamma ) const;

private:

  // Surface ID
  OrdinalType d_id;

  // Implicit surface definition: ax^2+by^2+cz^2+dxy+eyz+fxz+gx+hy+jz+k = 0
  Teuchos::Tuple<ScalarType,10> d_definition;

  // Tolerance used for performing tests
  ScalarType d_tolerance;

  // Boolean that indicates whether the surface is symmetric (no cross terms)
  bool d_symmetric;

  // Boolean that indicates whether the surface is planar or not
  bool d_planar;

};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_Surface_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_SURFACE_HPP

//---------------------------------------------------------------------------//
// end Geometry_Surface.hpp
//---------------------------------------------------------------------------//
