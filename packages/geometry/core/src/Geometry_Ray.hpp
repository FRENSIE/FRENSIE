//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Ray.hpp
//! \author Alex Robinson
//! \brief  Ray class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_RAY_HPP
#define GEOMETRY_RAY_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_PrintableObject.hpp"

namespace Geometry{

//! The ray class
class Ray : public Utility::PrintableObject
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

  //! Constructor
  Ray( double position[3],
       double direction[3],
       const bool deep_copy = true );

  //! Destructor
  ~Ray();
  
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

  //! Change the direction of the ray
  void changeDirection( const double direction[3] );

  //! Change the direction of the ray
  void changeDirection( const double x_direction,
                        const double y_direction,
                        const double z_direction );

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
  double* d_position;

  // The direction
  double* d_direction;

  // Records if ray was constructed with a deep copy
  bool d_deep_copy_initialization;
};

} // end Geometry namespace

#endif // end GEOMETRY_RAY_HPP

//---------------------------------------------------------------------------//
// end Geometry_Ray.hpp
//---------------------------------------------------------------------------//
