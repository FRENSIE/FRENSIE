//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Ray.hpp
//! \author Alex Robinson
//! \brief  Ray class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_RAY_HPP
#define GEOMETRY_RAY_HPP

// FRENSIE Includes
#include "Utility_OStreamableObject.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Geometry{

//! The ray class
template<typename LengthUnit>
class UnitAwareRay : public Utility::OStreamableObject
{
  // Typedef for length quantity
  typedef typename Utility::UnitTraits<LengthUnit>::template GetQuantityType<double>::type LengthQuantity;
    
  // Typedef for length QuantityTraits
  typedef Utility::QuantityTraits<LengthQuantity> LQT;

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The length quantity
  typedef LengthQuantity Length;

  //! Constructor
  UnitAwareRay( const Length x_position,
                const Length y_position,
                const Length z_position,
                const double x_direction,
                const double y_direction,
                const double z_direction );

  //! Constructor
  UnitAwareRay( const Length position[3],
                const double direction[3] );
  
  //! Constructor
  UnitAwareRay( Length position[3],
                double direction[3],
                const bool deep_copy = true );
  
  //! Destructor
  ~UnitAwareRay();

  //! Return the x position of the ray
  Length getXPosition() const;

  //! Return the y position of the ray
  Length getYPosition() const;

  //! Return the z position of the ray
  Length getZPosition() const;

  //! Return the position of the ray
  const Length* getPosition() const;

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
  void advanceHead( const Length distance );

  //! Print method implementation
  void toStream( std::ostream& os ) const override;

private:

  // Default constructor
  UnitAwareRay();

  // Copy constructor
  UnitAwareRay( const UnitAwareRay& );

  // The position
  Length* d_position;

  // The direction
  double* d_direction;

  // Records if ray was constructed with a deep copy
  bool d_deep_copy_initialization;
};

//! The ray type (unit-agnostic)
typedef UnitAwareRay<void> Ray;

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Geometry_Ray_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_RAY_HPP

//---------------------------------------------------------------------------//
// end Geometry_Ray.hpp
//---------------------------------------------------------------------------//
