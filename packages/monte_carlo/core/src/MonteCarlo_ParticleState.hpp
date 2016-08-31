//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleState.hpp
//! \author Alex Robinson
//! \brief  Particle state base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_STATE_HPP
#define MONTE_CARLO_PARTICLE_STATE_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_PrintableObject.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The particle state class
class ParticleState : public Utility::PrintableObject
{

public:

  //! Typedef for history number type
  typedef unsigned long long historyNumberType;

  //! Typedef for position type
  typedef double positionType;

  //! Typedef for direction type
  typedef double directionType;

  //! Typedef for energy type
  typedef double energyType;

  //! Typedef for time type
  typedef double timeType;

  //! Typedef for collision number type;
  typedef unsigned collisionNumberType;

  //! Typedef for generation number type
  typedef unsigned generationNumberType;

  //! Typedef for weight type
  typedef double weightType;

private:

  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  ParticleState();

  //! Constructor
  ParticleState( const historyNumberType history_number,
		 const ParticleType type );

  //! Copy constructor (with possible creation of new generation)
  ParticleState( const ParticleState& existing_base_state,
		 const ParticleType new_type,
		 const bool increment_generation_number,
		 const bool reset_collision_number );

  //! Destructor
  virtual ~ParticleState()
  { /* ... */ }

  /*! Clone the particle state (do not use to generate new particles!)
   * \details This method returns a heap-allocated pointer. It is only safe
   * to call this method inside of a smart pointer constructor or reset
   * method.
   */
  virtual ParticleState* clone() const = 0;

  //! Clone the particle state but change the history number
  ParticleState* clone( const historyNumberType new_history_number ) const;

  //! Return the history number
  historyNumberType getHistoryNumber() const;

  //! Return the particle type
  ParticleType getParticleType() const;

  //! Return the cell handle for the cell containing the particle
  Geometry::ModuleTraits::InternalCellHandle getCell() const;

  //! Set the cell containing the particle
  void setCell( const Geometry::ModuleTraits::InternalCellHandle cell );

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

  //! Rotate the direction of the particle using polar a. cos and azimuthal a.
  void rotateDirection( const double polar_angle_cosine,
			const double azimuthal_angle );

  //! Advance the particle along its direction by the requested distance
  void advance( const double distance );

  //! Return the energy of the particle (MeV)
  energyType getEnergy() const;

  //! Set the energy of the particle (MeV)
  virtual void setEnergy( const energyType energy );

  //! Return the speed of the particle (cm/s)
  virtual double getSpeed() const = 0;

  //! Return the time state of the particle (s)
  timeType getTime() const;

  //! Set the time state of the particle (s)
  void setTime( const timeType time );

  //! Return the collision number of the particle
  collisionNumberType getCollisionNumber() const;

  //! Increment the collision number of the particle
  void incrementCollisionNumber();

  //! Reset the collision number of the particle
  void resetCollisionNumber();

  //! Return the generation number of the particle
  generationNumberType getGenerationNumber() const;

  //! Increment the generation number of the particle
  void incrementGenerationNumber();

  //! Return the weight of the particle
  double getWeight() const;

  //! Set the weight of the particle
  void setWeight( const double weight );

  //! Multiply the weight of the particle by a factor
  void multiplyWeight( const double weight_factor );

  //! Return if the particle is lost
  bool isLost() const;

  //! Set the particle as lost
  void setAsLost();

  //! Return if the particle is gone
  bool isGone() const;

  //! Set the particle as gone
  void setAsGone();

  //! Spawn a ray that can be used for ray tracing
  const Geometry::Ray& ray() const;

protected:

  //! Calculate the time to traverse a distance
  virtual timeType calculateTraversalTime( const double distance ) const = 0;

  //! Print method implementation
  template<typename DerivedType>
  void printImplementation( std::ostream& os ) const;

private:

  //! Copy constructor
  ParticleState( const ParticleState& state );

  //! Assignment operator
  ParticleState& operator=( const ParticleState& state );

  // Save the state to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The history number
  historyNumberType d_history_number;

  // The particle type
  ParticleType d_particle_type;

  // Position of the particle
  positionType d_position[3];

  // Direction of the particle
  directionType d_direction[3];

  // Energy of the particle (MeV)
  energyType d_energy;

  // Time of the particle (s)
  timeType d_time;

  // Collision number of the particle
  collisionNumberType d_collision_number;

  // The generation number of the particle
  generationNumberType d_generation_number;

  // The weight of the particle
  weightType d_weight;

  // The current cell handle
  Geometry::ModuleTraits::InternalCellHandle d_cell;

  // Lost particle boolean
  bool d_lost;

  // Finished history boolean
  bool d_gone;

  // Ray for ray tracing
  Geometry::Ray d_ray;
};

// Set the position of the particle
inline void ParticleState::setPosition( const double position[3] )
{
  setPosition( position[0], position[1], position[2] );
}

// Set the direction of the particle
inline void ParticleState::setDirection( const double direction[3] )
{
  setDirection( direction[0], direction[1], direction[2] );
}

// Return the energy of the particle
inline ParticleState::energyType ParticleState::getEnergy() const
{
  return d_energy;
}

// Spawn a ray that can be used for ray tracing
inline const Geometry::Ray& ParticleState::ray() const
{
  return d_ray;
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::ParticleState );
BOOST_CLASS_VERSION( MonteCarlo::ParticleState, 0 );

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleState_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleState.hpp
//---------------------------------------------------------------------------//
