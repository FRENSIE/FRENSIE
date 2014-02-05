//---------------------------------------------------------------------------//
//!
//! \file   ParticleState.hpp
//! \author Alex Robinson
//! \brief  Particle state class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_STATE_HPP
#define PARTICLE_STATE_HPP

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/array.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "PrintableObject.hpp"
#include "ParticleType.hpp"

namespace FACEMC{

//! The particle state class
template<typename CellHandle>
class ParticleState : public PrintableObject
{

private:
  
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;
  
public:
  
  //! Typedef for the cell handle
  typedef CellHandle cellHandle;
  //! Typedef for particle state pointer
  typedef Teuchos::RCP<ParticleState<CellHandle> > ParticleStatePtr;

  //! Default constructor
  ParticleState();

  //! Constructor for a particular history
  ParticleState( const unsigned long long history_number,
		 const ParticleType particle_type );

  //! Copy constructor
  ParticleState( const ParticleState<CellHandle>& existing_particle_state );

  //! Assignment operator
  ParticleState<CellHandle>& operator=( 
		    const ParticleState<CellHandle>& existing_particle_state );

  //! Destructor
  ~ParticleState()
  { /* ... */ }

  //! Return the particle type
  ParticleType getParticleType() const;

  //! Set the particle type
  ParticleType setParticleType( const ParticleType particle_type );

  //! Return the history number
  unsigned long long getHistoryNumber() const;

  //! Return the energy of the particle
  double getEnergy() const;

  //! Set the energy of the particle
  void setEnergy( const double energy );

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

  //! Return the time state of the particle
  void getTime() const;

  //! Set the time state of the particle
  void setTime();

  //! Return the weight of the particle
  void getWeight() const;

  //! Set the weight of the particle
  void setWeight();

  //! multiply the weight of the particle by a factor
  void multiplyWeight( const double weight_factor );

  //! Set the source strength multiplier
  void setSourceStrengthMultiplier();
    
  //! Get the source strength multiplier
  void getSourceStrengthMultiplier();

  //! Return the cell handle for the cell containing the particle
  CellHandle getCell() const;

  //! Set the cell handle for the cell containing the particle
  void setCell( const CellHandle& cell );

  //! Return if the history is the root
  bool isRootHistory() const;

  //! Return if the particle is lost
  bool isLost() const;

  //! Set the particle as lost
  void setAsLost();

  //! Return if the particle is gone
  bool isGone() const;

  //! Set the particle as gone
  void setAsGone();

  //! Advance the particle along its direction by the requested distance
  void advance( const double distance );

  //! Spawn a child state (the history number will not change)
  ParticleStatePtr spawnChildState( 
			        const ParticleType child_particle_type ) const;

  //! Spawn a child state that is the same type as the parent
  ParticleStatePtr spawnChildState() const;

  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream& os ) const;

private:

  //! Set the history as a child
  void setAsChildHistory();

  //! Test if the direction is valid
  bool validDirection( const double x_direction,
		       const double y_direction,
		       const double z_direction );

  // Energy of the particle
  double d_energy;

  // Position of the particle
  boost::array<double,3> d_position;
  
  // Direction of the particle
  boost::array<double,3> d_direction;

  // Time of the particle
  double d_time;

  // Weight of the particle
  double d_weight;

  // Type of particle
  ParticleType d_type;

  // History number
  unsigned long long d_history_number;

  // Current cell handle
  CellHandle d_cell;

  // Root history boolean
  bool d_root_history;  

  // Lost particle boolean
  bool d_lost;

  // Finished history boolean
  bool d_gone;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "ParticleState_def.hpp"

//---------------------------------------------------------------------------//

#endif // end PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end ParticleState.hpp
//---------------------------------------------------------------------------//
