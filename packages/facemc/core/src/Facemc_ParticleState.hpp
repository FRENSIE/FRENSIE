//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleState.hpp
//! \author Alex Robinson
//! \brief  Particle state base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_STATE_HPP
#define FACEMC_PARTICLE_STATE_HPP

// Boost Includes
#include <boost/shared_ptr.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Facemc_ParticleType.hpp"
#include "Facemc_ParticleStateCore.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_PrintableObject.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

//! The particle state class
class ParticleState : public Utility::PrintableObject
{

public:

  //! Typedef for pointer
  typedef Teuchos::RCP<ParticleState> pointerType;

  //! Typedef for history number type
  typedef ParticleStateCore::historyNumberType historyNumberType;

  //! Typedef for energy type
  typedef ParticleStateCore::energyType energyType;

  //! Typedef for time type
  typedef ParticleStateCore::timeType timeType;

  //! Typedef for collision number type;
  typedef ParticleStateCore::collisionNumberType collisionNumberType;

  //! Typedef for generation number type
  typedef ParticleStateCore::generationNumberType generationNumberType;

private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  //! Constructor
  ParticleState( const historyNumberType history_number,
		 const ParticleType type );

  //! Copy constructor (with possible creation of new generation)
  ParticleState( const ParticleState& existing_base_state,
		 const ParticleType new_type,
		 const bool increment_generation_number,
		 const bool reset_collision_number );

  //! Core constructor
  ParticleState( const ParticleStateCore& core );

  //! Destructor
  virtual ~ParticleState()
  { /* ... */ }

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

  //! Return the generation number of the particle
  generationNumberType getGenerationNumber() const;
  
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

  //! Export the core (creating a copy of it)
  ParticleStateCore exportCore() const;

protected:

  //! Calculate the time to traverse a distance
  virtual timeType calculateTraversalTime( const double distance ) const = 0;

  //! Calculate the speed of a massive particle (cm/s)
  double calculateRelativisticSpeed( const double rest_mass_energy,
			             const double kinetic_energy ) const;

  //! Calculate the kinetic energy of a massive particle (MeV)
  double calculateRelativisticKineticEnergy( const double rest_mass_energy,
			                     const double speed ) const;

  //! Calculate the classical speed (cm/s)
  double calculateSpeed( const double rest_mass_energy,
                         const double kinetic_energy ) const;
 
  //! Calculate the classical kinetic energy of a massive particle (MeV)
  double calculateKineticEnergy( const double rest_mass_energy,
                                 const double speed ) const;

  //! Print method implementation 
  void printImplementation( std::ostream& os ) const;

private:

  // Copy constructor
  ParticleState( const ParticleState& state );

  // The particle state core
  ParticleStateCore d_core;

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
  return d_core.energy;
}

// Spawn a ray that can be used for ray tracing
inline const Geometry::Ray& ParticleState::ray() const
{
  return d_ray;
}

// Calculate the speed of a massive particle 
inline double ParticleState::calculateRelativisticSpeed(const double rest_mass_energy,
		     			                const double kinetic_energy ) const
{
  // Make sure the rest mass energy is valid
  testPrecondition( !ST::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the kinetic energy is valid
  testPrecondition( !ST::isnaninf( kinetic_energy ) );
  testPrecondition( kinetic_energy > 0.0 );
  
  double energy = kinetic_energy + rest_mass_energy;
  
  return Utility::PhysicalConstants::speed_of_light*
    sqrt( 1.0 - rest_mass_energy*rest_mass_energy/(energy*energy) );
}

// Calculate the kinetic enery of a massive particle (MeV)
inline double ParticleState::calculateRelativisticKineticEnergy( 
						 const double rest_mass_energy,
						 const double speed ) const
{
  // Make sure the rest mass energy is valid
  testPrecondition( !ST::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the speed is valid
  testPrecondition( !ST::isnaninf( speed ) );
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );
  testPrecondition( speed > 0.0 );

  return rest_mass_energy*(Utility::PhysicalConstants::speed_of_light/
			   sqrt( Utility::PhysicalConstants::speed_of_light*
				 Utility::PhysicalConstants::speed_of_light -
				 speed*speed ) - 1.0);
}

// Calculate the speed of a massive particle 
inline double ParticleState::calculateSpeed(const double rest_mass_energy,
		     		            const double kinetic_energy ) const
{
  // Make sure the rest mass energy is valid
  testPrecondition( !ST::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the kinetic energy is valid
  testPrecondition( !ST::isnaninf( kinetic_energy ) );
  testPrecondition( kinetic_energy > 0.0 );

  return Utility::PhysicalConstants::speed_of_light * sqrt( 2 * kinetic_energy /
                  rest_mass_energy);  
}

// Calculate the kinetic enery of a massive particle (MeV)
inline double ParticleState::calculateKineticEnergy( 
					 const double rest_mass_energy,
					 const double speed ) const
{
  // Make sure the rest mass energy is valid
  testPrecondition( !ST::isnaninf( rest_mass_energy ) );
  testPrecondition( rest_mass_energy > 0.0 );
  // Make sure the speed is valid
  testPrecondition( !ST::isnaninf( speed ) );
  testPrecondition( speed < Utility::PhysicalConstants::speed_of_light );
  testPrecondition( speed > 0.0 );

  return 0.5 * rest_mass_energy * speed * speed / 
        ( Utility::PhysicalConstants::speed_of_light * 
          Utility::PhysicalConstants::speed_of_light );
}

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleState.hpp
//---------------------------------------------------------------------------//
