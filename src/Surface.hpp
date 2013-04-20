//---------------------------------------------------------------------------//
// \file   Surface.hpp
// \author Alex Robinson
// \brief  Surface class declaration
//---------------------------------------------------------------------------//

#ifndef SURFACE_HPP
#define SURFACE_HPP

// Trilinos Includes
#include <Teuchos_Tuple.hpp>

namespace FACEMC{

class Surface
{

public:

  //@{
  //! Typedefs
  typedef Teuchos::Tuple<double,9> Matrix;
  typedef Teuchos::Tuple<double,3> Vector;
  typedef short Sense;
  //@}

  //! General Surface Constructor
  // \brief ax^2+by^2+cz^2+dxy+eyz+fxz+gx+hy+jz+k = 0
  Surface( unsigned id,
	   double a,
	   double b, 
	   double c,
	   double d,
	   double e,
	   double f,
	   double g,
	   double h,
	   double j,
	   double k );

  //! Symmetric 2nd order surface constructor
  Surface( unsigned id,
	   double a,
	   double b,
	   double c,
	   double g,
	   double h,
	   double j,
	   double k );

  //! Planar Surface constructor
  Surface( unsigned id,
	   double g,
	   double h,
	   double j,
	   double k );

  //! Destructor
  ~Surface()
  { /* ... */ }
  
  //! Return if the point is on the surface
  bool isOn( const Vector &point ) const;

  //! Return if the surface is planar
  bool isPlanar() const;

  //! Return the sense of a point with respect to the surface
  Sense getSense( const Vector &point ) const;

  //! Return the surface id
  unsigned getId() const;

  //! Return the unit normal from the surface at a point on the surface,
  // pointing in the direction of the desired sense
  Vector getUnitNormal( const Vector &point,
			const short sense = 1 ) const;

  //! Return the quadratic form matrix of the surface
  Matrix getQuadraticFormMatrix() const;

  //! Return the linear term vector of the surface
  Vector getLinearTermVector() const;

  //! Return the constant term of the surface
  double getConstantTerm() const;

  //! Rotate the surface using the provided rotation matrix
  void transformSurface( const Matrix &rotation_matrix,
			 const Vector &translation_vector );

protected:

  //! Return the gradient of the surface at a given point
  Vector getGradient( const Vector &point ) const;

private:

  // Surface ID
  unsigned d_id;

  // Matrix storing the quadratic form matrix of the surface
  Matrix d_quadratic_form_matrix;

  // Array storing the vector of linear terms of the surface
  Vector d_linear_term_vector;

  // Constant term of the surface
  double d_constant_term;

  // Tolerance used for performing tests
  double d_tolerance;

  // Boolean that indicates whether the surface is symmetric or not
  bool d_symmetric;

  // Boolean that indicates whether the surface is planar or not
  bool d_planar;
  
};

} // end FACEMC namespace

#endif // end SURFACE_HPP

//---------------------------------------------------------------------------//
// end Surface.hpp
//---------------------------------------------------------------------------//
