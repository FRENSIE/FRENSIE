//---------------------------------------------------------------------------//
//!
//! \file   Ray.hpp
//! \author Alex Robinson
//! \brief  Ray class declaration
//!
//---------------------------------------------------------------------------//

#ifndef RAY_HPP
#define RAY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "PrintableObject.hpp"


namespace FACEMC{

//! The ray class
class Ray : public PrintableObject
{

private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  Ray( const double x_position,
       const double y_position,
       const double z_position,
       const double x_direction,
       const double y_direction,
       const double z_direction );

  //! Constructor
  Ray( const double position[3],
       const double direction[3] );

  //! Return the x position of the ray
  double getXPosition() const;

  //! Return the y position of the ray
  double getYPosition() const;

  //! Return the z position of the ray
  double getZPosition() const;

  //! Return the position of the ray
  const double* getPosition() const;

  //! Return the x direction of the ray
  double getXDirection() const;

  //! Return the y direction of the ray
  double getYDirection() const;

  //! Return the z direction of the ray
  double getZDirection() const;

  //! Return the direction of the ray
  const double* getDirection() const;

  //! Advance the head along its direction by the requested distance
  void advanceHead( const double distance );

  //! Print method implementation
  void print( std::ostream& os ) const;

private:

  // Default constructor
  Ray();
  
  // Copy constructor
  Ray( const Ray& );

  // The position
  double d_position[3];

  // The direction
  double d_direction[3];
};

} // end FACEMC namespace

#endif // end RAY_HPP

//---------------------------------------------------------------------------//
// end Ray.hpp
//---------------------------------------------------------------------------//
