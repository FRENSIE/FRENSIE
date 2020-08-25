//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleState.hpp
//! \author Alex Robinson
//! \brief  Particle state base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_STATE_HPP
#define MONTE_CARLO_PARTICLE_STATE_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleType.hpp"
#include "Geometry_Navigator.hpp"
#include "Geometry_Model.hpp"
#include "Utility_OStreamableObject.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The particle state class
class ParticleState : public Utility::OStreamableObject
{

public:

  //! Typedef for history number type
  typedef uint64_t historyNumberType;

  //! Typedef for energy type
  typedef double energyType;

  //! Typedef for charge type
  typedef int chargeType;

  //! Typedef for time type
  typedef double timeType;

  //! Typedef for collision number type;
  typedef unsigned collisionNumberType;

  //! Typedef for generation number type
  typedef unsigned generationNumberType;

  //! Typedef for the source id type
  typedef uint32_t sourceIdType;

  //! Typedef for weight type
  typedef double weightType;

  //! Typedef for ray safety distance type
  typedef double raySafetyDistanceType;

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! Default constructor
  ParticleState();

  //! Constructor
  ParticleState( const historyNumberType history_number,
                 const ParticleType type,
                 const chargeType charge );

  //! Copy constructor (with possible creation of new generation)
  ParticleState( const ParticleState& existing_base_state,
                 const ParticleType new_type,
                 const chargeType new_charge,
                 const bool increment_generation_number,
                 const bool reset_collision_number,
                 const raySafetyDistanceType ray_safety_distance );

  //! Destructor
  virtual ~ParticleState()
  { /* ... */ }

  /*! Clone the particle state (do not use to generate new particles through reactions, VR is fine!)
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

  //! Set the initial value of the importance pair (when emerging from source only)
  void setInitialImportance( const double initial_importance );

  //! Set the new importance value of the importance pair (immediately after it's traveled from its first source emission)
  void setNewImportance( const double new_importance );

  //! Update importance pair based on new phase space transition (only used after both have been set)
  void updateImportance( const double new_importance );

  const std::pair<double, double>& getImportancePair() const;

  //! Return the id of the source that created the particle (history)
  sourceIdType getSourceId() const;

  //! Set the id of the source that created the particle (history)
  void setSourceId( const sourceIdType id );

  //! Return the cell handle for the cell where the particle (history) started
  Geometry::Model::EntityId getSourceCell() const;

  //! Set the cell where the particle (history) started
  void setSourceCell( const Geometry::Model::EntityId cell );

  //! Return the cell handle for the cell containing the particle
  Geometry::Model::EntityId getCell() const;

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
  void advance( double distance );

  //! Return the source (starting) energy of the particle (history) (MeV)
  energyType getSourceEnergy() const;

  //! Set the source (starting) energy of the particle (history) (MeV)
  void setSourceEnergy( const energyType energy );

  //! Return the energy of the particle (MeV)
  energyType getEnergy() const;

  //! Set the energy of the particle (MeV)
  virtual void setEnergy( const energyType energy );

  //! Return the speed of the particle (cm/s)
  virtual double getSpeed() const = 0;

  //! Return the charge of the particle (e)
  chargeType getCharge() const;

  //! Return the source (starting) time of the particle (history) (s)
  timeType getSourceTime() const;

  //! Set the source (starting) time of the particle (history) (s)
  void setSourceTime( const timeType time );

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

  //! Return the source (starting) weight of the particle (history)
  double getSourceWeight() const;

  //! Set the source (starting) weight of the particle (history)
  void setSourceWeight( const double weight );

  //! Return the weight of the particle
  weightType getWeight() const;

  //! Set the weight of the particle
  void setWeight( const weightType weight );

  //! Multiply the weight of the particle by a factor
  void multiplyWeight( const double weight_factor );

  //! Set the ray safety distance ( i.e. distance to the closest boundary )
  void setRaySafetyDistance( const raySafetyDistanceType ray_safety_distance );

  //! Return the ray safety distance (i.e. distance to the closest boundary)
  raySafetyDistanceType getRaySafetyDistance() const;

  //! Return if the particle is lost
  bool isLost() const;

  //! Set the particle as lost
  void setAsLost();

  //! Return if the particle is gone
  bool isGone() const;

  //! Set the particle as gone
  void setAsGone();

  //! Check if the particle state is still valid
  operator bool() const;

  //! Embed the particle in the desired model
  void embedInModel( const std::shared_ptr<const Geometry::Model>& model );

  //! Embed the particle in the desired model
  void embedInModel( const std::shared_ptr<const Geometry::Model>& model,
                     const Geometry::Model::EntityId cell );

  //! Embed the particle in the desired model at the desired position
  void embedInModel( const std::shared_ptr<const Geometry::Model>& model,
                     const double position[3],
                     const double direction[3] );

  //! Embed the particle in the desired model at the desired position
  void embedInModel( const std::shared_ptr<const Geometry::Model>& model,
                     const double position[3],
                     const double direction[3],
                     const Geometry::Model::EntityId cell );

  //! Extract the particle from the model
  void extractFromModel();

  //! Check if a particle is embedded in the model of interest
  bool isEmbeddedInModel( const Geometry::Model& model ) const;

  //! Get the navigator used by the particle
  Geometry::Navigator& navigator();

  //! Get the navigator used by the particle
  const Geometry::Navigator& navigator() const;

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

  // Increase the particle time due to a traversal
  void increaseParticleTime( const Geometry::Navigator::Length distance_traversed );

  // Create the navigator AdvanceComplete callback method
  Geometry::Navigator::AdvanceCompleteCallback createAdvanceCompleteCallback();

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

  // The source id
  sourceIdType d_source_id;

  // Source (starting) energy of the particle (history) (MeV)
  energyType d_source_energy;

  // Energy of the particle (MeV)
  energyType d_energy;

  // Charge of the particle (e)
  chargeType d_charge;

  // Source (starting) time of the particle (history) (s)
  timeType d_source_time;

  // Time of the particle (s)
  timeType d_time;

  // Collision number of the particle
  collisionNumberType d_collision_number;

  // The generation number of the particle
  generationNumberType d_generation_number;

  // The source (starting) weight of the particle (history)
  weightType d_source_weight;

  // The weight of the particle
  weightType d_weight;

  // The importance pair of the phase space transitions of a particle <old_importance, new_importance>
  std::pair<double, double> d_importance_pair;

  // The ray safety distance (i.e. distance to the closest boundary)
  raySafetyDistanceType d_ray_safety_distance;

  // The source (starting) cell of the particle (history)
  Geometry::Model::EntityId d_source_cell;

  // Lost particle boolean
  bool d_lost;

  // Finished history boolean
  bool d_gone;

  // The model that the particle is embedded in
  // Note: This must be stored to avoid persistence issues that could arrise
  //       from the model being deleted while the particle is still embedded
  //       in it.
  std::shared_ptr<const Geometry::Model> d_model;

  // The navigator used by the particle
  std::unique_ptr<Geometry::Navigator> d_navigator;
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

// Return the source (starting) energy of the particle (history) (MeV)
inline ParticleState::energyType ParticleState::getSourceEnergy() const
{
  return d_source_energy;
}

// Return the energy of the particle
inline ParticleState::energyType ParticleState::getEnergy() const
{
  return d_energy;
}

// Get the navigator used by the particle
/*! \details Do not call setOnAdvanceCompleteMethod or
 * clearOnAdvanceCompleteMethod on the returned navigator. A callback is set
 * by the particle state to ensure that the particle time is updated after an
 * advance method is called.
 */
inline Geometry::Navigator& ParticleState::navigator()
{
  return *d_navigator;
}

// Get the navigator used by the particle
inline const Geometry::Navigator& ParticleState::navigator() const
{
  return *d_navigator;
}

} // end MonteCarlo namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ParticleState, MonteCarlo );
BOOST_SERIALIZATION_CLASS_VERSION( ParticleState, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ParticleState );

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleState_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_STATE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleState.hpp
//---------------------------------------------------------------------------//
