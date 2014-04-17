//---------------------------------------------------------------------------//
//!
//! \file   BasicParticleState.hpp
//! \author Alex Robinson
//! \brief  Basic particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef BASIC_PARTICLE_STATE_HPP
#define BASIC_PARTICLE_STATE_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "ParticleType.hpp"
#include "PrintableObject.hpp"
#include "PhaseSpaceDimension.hpp"

namespace FACEMC{

//! The basic particle state struct
class BasicParticleState : public PrintableObject
{

public:

  //! Typedef for energy type
  typedef double energyType;

  //! Typedef for time type
  typedef double timeType;

  //! Typedef for collision number type;
  typedef unsigned collisionNumberType;

private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  //! Default constructor
  BasicParticleState();

  //! Constructor
  BasicParticleState( const ParticleType type,
		      const double position[3],
		      const double direction[3],
		      const double energy,
		      const double time,
		      const double weight );

  //! Copy constructor
  BasicParticleState( const BasicParticleState& existing_basic_state );

  //! Assignment operator
  BasicParticleState& operator=(
			      const BasicParticleState& existing_basic_state );

  //! Destructor
  virtual ~BasicParticleState()
  { /* ... */ }

  //! Return the particle type
  ParticleType getParticleType() const;

  //! Set the particle type
  ParticleType setParticleType( const ParticleType particle_type );

  //! Return the x position of the particle
  double getXPosition() const;

  //! Return the y position of the particle
  double getYPosition() const;

  //! Return the z position of the particle
  double getZPosition() const;

  //! Return the position of the particle
  const double* getPosition() const;

  //! Set the position of the particle
  void setPosition( const double x_position, 
		    const double y_position,
		    const double z_position );

  //! Set the position of the particle
  void setPosition( const double position[3] );

  //! Return the x direction of the particle
  double getXDirection() const;

  //! Return the y direction of the particle
  double getYDirection() const;

  //! Return the z direction of the particle
  double getZDirection() const;

  //! Return the direction of the particle
  const double* getDirection() const;

  //! Set the direction of the particle
  void setDirection( const double x_direction,
		     const double y_direction,
		     const double z_direction );

  //! Set the direction of the particle
  void setDirection( const double direction[3] );

  //! Advance the particle along its direction by the requested distance
  void advance( const double distance );

  //! Return the energy of the particle (MeV)
  energyType getEnergy() const;

  //! Set the energy of the particle (MeV)
  void setEnergy( const double energy );

  //! Return the speed of the particle (cm/s)
  double getSpeed() const;

  //! Return the time state of the particle (s)
  timeType getTime() const;

  //! Set the time state of the particle (s)
  void setTime( const double time );

  //! Return the collision number of the particle
  collisionNumberType getCollisionNumber() const;
  
  //! Increment the collision number of the particle
  void incrementCollisionNumber();

  //! Return the weight of the particle
  double getWeight() const;

  //! Set the weight of the particle
  void setWeight( const double weight );

  //! Multiply the weight of the particle by a factor
  void multiplyWeight( const double weight_factor );

  //! Print method that defines the behavior of the std::stream << operator
  virtual void print( std::ostream& os ) const;

protected:

  //! Print method implementation 
  void printImplementation( std::ostream& os ) const;

private:

  // Calculate the velocity of a neutron
  void calculateNeutronSpeed();

  // Particle type
  ParticleType d_type;

  // Position of the particle
  double d_position[3];

  // Direction of the particle
  double d_direction[3];
  
  // Energy of the particle (MeV)
  energyType d_energy;

  // Speed of the particle (cm/s)
  double d_speed;

  // Time of the particle (s)
  timeType d_time;

  // Collision number of the particle
  collisionNumberType d_collision_number;

  // Weight o the particle
  double d_weight;
};

} // end FACEMC namespace

#endif // end BASIC_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end BasicParticleState.hpp
//---------------------------------------------------------------------------//
