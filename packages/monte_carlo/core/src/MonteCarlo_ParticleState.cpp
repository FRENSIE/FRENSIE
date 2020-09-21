//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleState.cpp
//! \author Alex Robinson
//! \brief  Basic particle state class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Default constructor
/*! \details The default constructor should only be called before loading the
 * particle state from an archive.
 */
ParticleState::ParticleState()
  : d_history_number( 0 ),
    d_particle_type(),
    d_source_id( 0 ),
    d_source_energy( 0.0 ),
    d_energy( 0.0 ),
    d_charge( 0 ),
    d_source_time( 0.0 ),
    d_time( 0.0 ),
    d_collision_number( 0 ),
    d_generation_number( 0 ),
    d_source_weight( 1.0 ),
    d_weight( 1.0 ),
    d_ray_safety_distance( 0.0 ),
    d_source_cell( 0 ),
    d_lost( false ),
    d_gone( false ),
    d_model( new Geometry::InfiniteMediumModel( d_source_cell ) ),
    d_navigator( d_model->createNavigatorAdvanced( this->createAdvanceCompleteCallback() ) ),
    d_importance_pair( std::make_pair(1.0, 1.0))
{ /* ... */ }

// Constructor
ParticleState::ParticleState(
                         const ParticleState::historyNumberType history_number,
                         const ParticleType type,
                         const chargeType charge )
  : d_history_number( history_number ),
    d_particle_type( type ),
    d_source_id( 0 ),
    d_source_energy( 0.0 ),
    d_energy( 0.0 ),
    d_charge( charge ),
    d_source_time( 0.0 ),
    d_time( 0.0 ),
    d_collision_number( 0 ),
    d_generation_number( 0 ),
    d_source_weight( 1.0 ),
    d_weight( 1.0 ),
    d_ray_safety_distance( 0.0 ),
    d_source_cell( 0 ),
    d_lost( false ),
    d_gone( false ),
    d_model( new Geometry::InfiniteMediumModel( d_source_cell ) ),
    d_navigator( d_model->createNavigatorAdvanced( this->createAdvanceCompleteCallback() ) ),
    d_importance_pair( std::make_pair(1.0, 1.0))
{ /* ... */ }

// Copy constructor
/*! \details When copied, the new particle is assumed to not be lost and
 * not be gone (i.e. the lost and gone states will never be copied). The
 * newly created particle will also be embedded in the same model as the
 * copied particle.
 */
ParticleState::ParticleState( const ParticleState& existing_base_state,
                              const ParticleType new_type,
                              const chargeType new_charge,
                              const bool increment_generation_number,
                              const bool reset_collision_number,
                              const raySafetyDistanceType ray_safety_distance )
  : d_history_number( existing_base_state.d_history_number ),
    d_particle_type( new_type ),
    d_source_id( existing_base_state.d_source_id ),
    d_source_energy( existing_base_state.d_source_energy ),
    d_energy( existing_base_state.d_energy ),
    d_charge( new_charge ),
    d_source_time( existing_base_state.d_source_time ),
    d_time( existing_base_state.d_time ),
    d_collision_number( existing_base_state.d_collision_number ),
    d_generation_number( existing_base_state.d_generation_number ),
    d_source_weight( existing_base_state.d_source_weight ),
    d_weight( existing_base_state.d_weight ),
    d_ray_safety_distance( ray_safety_distance ),
    d_source_cell( existing_base_state.d_source_cell ),
    d_lost( false ),
    d_gone( false ),
    d_model( existing_base_state.d_model ),
    d_navigator( existing_base_state.d_navigator->clone( this->createAdvanceCompleteCallback() ) ),
    d_importance_pair( existing_base_state.d_importance_pair )
{
  // Increment the generation number if requested
  if( increment_generation_number )
    ++d_generation_number;

  // Reset the collision number if requested
  if( reset_collision_number )
    d_collision_number = 0u;
}

// Clone the particle state but change the history number
/*! \details This method returns a heap-allocated pointer. It is only safe
 * to call this method inside of a smart pointer constructor or reset method.
 * The clone will only need a new history number in very rare circumstances
 * (e.g. state source).
 */
ParticleState* ParticleState::clone(
              const ParticleState::historyNumberType new_history_number ) const
{
  ParticleState* clone_state = this->clone();

  clone_state->d_history_number = new_history_number;

  return clone_state;
}

// Return the history number
ParticleState::historyNumberType ParticleState::getHistoryNumber() const
{
  return d_history_number;
}

// Return the particle type
ParticleType ParticleState::getParticleType() const
{
  return d_particle_type;
}

// Set the initial value of the importance pair (when emerging from source only)
void ParticleState::setInitialImportance( const double initial_importance )
{
  if(this->getCollisionNumber() == 0)
  {
    d_importance_pair.first = initial_importance;
  }
  else
  {
    THROW_EXCEPTION(std::runtime_error, "setInitialImportance method used with non-zero collision number");
  }
  
}

// Set the new importance value of the importance pair (immediately after it's traveled from its first source emission)
void ParticleState::setNewImportance( const double new_importance )
{
  if(this->getCollisionNumber() == 1)
  {
    d_importance_pair.second = new_importance;
  }
  else
  {
    THROW_EXCEPTION(std::runtime_error, "setNewImportance method used with collision number != 1");
  }
}

// Update importance pair based on new phase space transition (only used after both have been set)
void ParticleState::updateImportance( const double new_importance )
{
  if (this->getCollisionNumber() > 1)
  {
    d_importance_pair.first = d_importance_pair.second;
    d_importance_pair.second = new_importance;
  }
  else
  {
    THROW_EXCEPTION(std::runtime_error, "updateImportance method used with collision number < 1");
  }
}

const std::pair<double, double>& ParticleState::getImportancePair() const
{
  return d_importance_pair;
}

// Return the source id that created the particle (history)
ParticleState::sourceIdType ParticleState::getSourceId() const
{
  return d_source_id;
}

// Set the source id of the source that created the particle (history)
void ParticleState::setSourceId( const sourceIdType id )
{
  d_source_id = id;
}

// Return the cell handle for the cell where the particle (history) started
Geometry::Model::EntityId ParticleState::getSourceCell() const
{
  return d_source_cell;
}

// Set the cell where the particle (history) started
/*! \details This method should only be called when the particle history
 * is first started (particle with generation number 0).
 */
void ParticleState::setSourceCell(
                        const Geometry::Model::EntityId cell )
{
  d_source_cell = cell;
}

// Return the cell handle for the cell containing the particle
Geometry::Model::EntityId ParticleState::getCell() const
{
  return d_navigator->getCurrentCell();
}

// Return the x position of the particle
double ParticleState::getXPosition() const
{
  return d_navigator->getPosition()[0].value();
}

// Return the y position of the particle
double ParticleState::getYPosition() const
{
  return d_navigator->getPosition()[1].value();
}

// Return the z position of the particle
double ParticleState::getZPosition() const
{
  return d_navigator->getPosition()[2].value();
}

// Return the position of the particle
const double* ParticleState::getPosition() const
{
  return Utility::reinterpretAsRaw( d_navigator->getPosition() );
}

// Set the position of the particle
void ParticleState::setPosition( const double x_position,
                                 const double y_position,
                                 const double z_position )
{
  // Make sure the coordinates are valid
  testPrecondition( !QT::isnaninf( x_position ) );
  testPrecondition( !QT::isnaninf( y_position ) );
  testPrecondition( !QT::isnaninf( z_position ) );

  const double* current_direction = d_navigator->getDirection();

  d_navigator->setState( Geometry::Navigator::Length::from_value(x_position),
                         Geometry::Navigator::Length::from_value(y_position),
                         Geometry::Navigator::Length::from_value(z_position),
                         current_direction[0],
                         current_direction[1],
                         current_direction[2] );
}

// Return the x direction of the particle
double ParticleState::getXDirection() const
{
  return d_navigator->getDirection()[0];
}

// Return the y direction of the particle
double ParticleState::getYDirection() const
{
  return d_navigator->getDirection()[1];
}

// Return the z direction of the particle
double ParticleState::getZDirection() const
{
  return d_navigator->getDirection()[2];
}

// Return the direction of the particle
const double* ParticleState::getDirection() const
{
  return d_navigator->getDirection();
}

// Set the direction of the particle
void ParticleState::setDirection( const double x_direction,
                                  const double y_direction,
                                  const double z_direction )
{
  // Make sure the direction coordinates are valid
  testPrecondition( !QT::isnaninf( x_direction ) );
  testPrecondition( !QT::isnaninf( y_direction ) );
  testPrecondition( !QT::isnaninf( z_direction ) );
  // Make sure the direction is a unit vector
  testPrecondition( Utility::isUnitVector( x_direction,
                                           y_direction,
                                           z_direction ) );

  d_navigator->changeDirection( x_direction, y_direction, z_direction );
}

// Rotate the direction of the particle using polar a. cosine and azimuthal a.
/*! \details The polar angle cosine and azimuthal angle are w.r.t. the
 * current particle direction and not the global coordinate system. These
 * are the variables the commonly occur when sampling a new direction
 * for the particle from a scattering distribution. This function is therefore
 * meant to avoid duplicate code that would otherwise arise when determining
 * the new particle direction
 */
void ParticleState::rotateDirection( const double polar_angle_cosine,
                                     const double azimuthal_angle )
{
  // Make sure the current particle direction is valid (initialized)
  testPrecondition( Utility::isUnitVector( this->getDirection() ) );
  // Make sure the polar angle cosine is valid
  testPrecondition( polar_angle_cosine >= -1.0 );
  testPrecondition( polar_angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPrecondition( azimuthal_angle >= 0.0 );
  testPrecondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );

  double outgoing_direction[3];

  Utility::rotateUnitVectorThroughPolarAndAzimuthalAngle( polar_angle_cosine,
                                                          azimuthal_angle,
                                                          this->getDirection(),
                                                          outgoing_direction );

  this->setDirection( outgoing_direction );
}

// Advance the particle along its direction by the requested distance
/*! \details If the particle has been embedded in geometry model the
 * particle's navigator will be used to move through the model as the
 * requested distance is traversed. All boundary crossing info will be lost.
 * If an exception occurs due to a navigator tracking error the particle
 * state will be set to lost. If the model boundary is reached, movement
 * of the particle will be stopped and the state will be set to gone. Be sure
 * to check that the particle state is still valid after calling this method.
 */
void ParticleState::advance( double raw_distance )
{
  // Make sure the distance is valid
  testPrecondition( !QT::isnaninf( raw_distance ) );
  testPrecondition( !this->isLost() );
  testPrecondition( !this->isGone() );

  Geometry::Navigator::Length distance =
    Geometry::Navigator::Length::from_value( raw_distance );

  Geometry::Navigator::Length distance_to_surface = d_navigator->fireRay();

  while( distance > distance_to_surface )
  {
    // Try to advance the particle to the next cell boundary. If the
    // advance fails, the particle is lost.
    try{
      d_navigator->advanceToCellBoundary();
    }
    catch( const std::exception& exception )
    {
      FRENSIE_LOG_TAGGED_WARNING( "ParticleState",
                                  "Particle " << d_history_number << " of "
                                  "type " << d_particle_type << " was lost "
                                  "at cell " << this->getCell() <<
                                  " boundary! The particle has been reported "
                                  "as lost.\n" << exception.what() );

      d_lost = true;

      return;
    }

    // Update the distance left to travel
    distance -= distance_to_surface;

    // Determine the distance to the next surface
    if( !d_model->isTerminationCell( this->getCell() ) )
      distance_to_surface = d_navigator->fireRay();

    // The particle has exited the model
    else
    {
      d_gone = true;
      return;
    }
  }

  // Travel any remaining distance
  if( distance > 0.0*boost::units::cgs::centimeter )
  {
    d_navigator->advanceBySubstep( distance );
  }
}

// Increase the particle time due to a traversal
void ParticleState::increaseParticleTime( const Geometry::Navigator::Length distance_traversed )
{
  d_time += this->calculateTraversalTime( distance_traversed.value() );
}

// Set the source (starting) energy of the particle (history) (MeV)
/*! \details This method should only be called when the particle history
 * is first started (particle with generation number 0).
 */
void ParticleState::setSourceEnergy( const energyType energy )
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  d_source_energy = energy;
}

// Set the energy of the particle (MeV)
/*! The default implementation is only valid for massless particles (It is
 * assumed that the speed of the particle does not change with the energy).
 */
void ParticleState::setEnergy( const ParticleState::energyType energy )
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  d_energy = energy;
}

// Return the charge of the particle
ParticleState::chargeType ParticleState::getCharge() const
{
  return d_charge;
}

// Return the source (starting) time of the particle (history) (s)
ParticleState::timeType ParticleState::getSourceTime() const
{
  return d_source_time;
}

// Set the source (starting) time of the particle (history) (s)
/*! \details This method should only be called when the particle history
 * is first started (particle with generation number 0).
 */
void ParticleState::setSourceTime( const timeType time )
{
  d_source_time = time;
}

// Return the time state of the particle
ParticleState::timeType ParticleState::getTime() const
{
  return d_time;
}

// Set the time state of the particle
/*! \details This is not the recommended way to update the particle time.
 * As the particle position is advanced, either through the advance method
 * or through the particle navigator advance methods, the time will be
 * automatically updated using the traversal distance and the particle speed.
 */
void ParticleState::setTime( const ParticleState::timeType time )
{
  d_time = time;
}

// Return the collision number of the particle
ParticleState::collisionNumberType ParticleState::getCollisionNumber() const
{
  return d_collision_number;
}

// Increment the collision number
void ParticleState::incrementCollisionNumber()
{
  ++d_collision_number;
}

// Reset the collision number
/*! \details This should rarely be used - try to rely on the contructor to
 * reset the collision number.
 */
void ParticleState::resetCollisionNumber()
{
  d_collision_number = 0u;
}

// Return the generation number of the particle
ParticleState::generationNumberType ParticleState::getGenerationNumber() const
{
  return d_generation_number;
}

// Increment the generation number
void ParticleState::incrementGenerationNumber()
{
  ++d_generation_number;
}

// Return the source (starting) weight of the particle (history)
double ParticleState::getSourceWeight() const
{
  return d_source_weight;
}

// Set the source (starting) weight of the particle (history)
/*! \details This method should only be called when the particle history
 * is first started (particle with generation number 0).
 */
void ParticleState::setSourceWeight( const double weight )
{
  // Make sure the weight is valid
  testPrecondition( weight > 0.0 );

  d_source_weight = weight;
}

// Return the weight of the particle
double ParticleState::getWeight() const
{
  return d_weight;
}

// Set the weight of the particle
void ParticleState::setWeight( const double weight )
{
  // Make sure that the current weight is valid
  testPrecondition( weight > 0.0 );

  d_weight = weight;
}

// Multiply the weight of the particle by a factor
void ParticleState::multiplyWeight( const double weight_factor )
{
  // Make sure that the current weight is valid
  testPrecondition( d_weight > 0.0 );
  testPrecondition( weight_factor > 0.0 );

  d_weight *= weight_factor;
}

// Return the ray safety distance (i.e. distance to the closest boundary)
auto ParticleState::getRaySafetyDistance() const -> raySafetyDistanceType
{
  return d_ray_safety_distance;
}

// Set the ray safety distance (i.e. distance to the closest boundary)
void ParticleState::setRaySafetyDistance( const raySafetyDistanceType ray_safety_distance )
{
  // Make sure that the current safety distance is valid
  testPrecondition( ray_safety_distance >= 0.0 );

  d_ray_safety_distance = ray_safety_distance;
}

// Return if the particle is lost
bool ParticleState::isLost() const
{
  return d_lost;
}

// Set the particle as lost
void ParticleState::setAsLost()
{
  d_lost = true;
}

// Return if the particle is gone
bool ParticleState::isGone() const
{
  return d_gone;
}

// Set the particle as gone
void ParticleState::setAsGone()
{
  d_gone = true;
}

// Check if the particle state is still valid
/*! \details This will return false if the particle is lost or gone.
 */
ParticleState::operator bool() const
{
  return !(this->isLost() || this->isGone());
}

// Embed the particle in the desired model
void ParticleState::embedInModel(
                          const std::shared_ptr<const Geometry::Model>& model )
{
  // Make sure that the model is valid
  testPrecondition( model.get() );

  // Cache the current particle position and direction
  const double position[3] = {d_navigator->getPosition()[0].value(),
                              d_navigator->getPosition()[1].value(),
                              d_navigator->getPosition()[2].value()};

  const double direction[3] = {d_navigator->getDirection()[0],
                               d_navigator->getDirection()[1],
                               d_navigator->getDirection()[2]};

  this->embedInModel( model, position, direction );
}

// Embed the particle in the desired model
/*! \details The current particle position must be inside of the cell. If
 * it is not, the particle will become lost.
 */
void ParticleState::embedInModel(
                        const std::shared_ptr<const Geometry::Model>& model,
                        const Geometry::Model::EntityId cell )
{
  // Make sure that the model is valid
  testPrecondition( model.get() );

  // Cache the current particle position and direction
  const double position[3] = {d_navigator->getPosition()[0].value(),
                              d_navigator->getPosition()[1].value(),
                              d_navigator->getPosition()[2].value()};

  const double direction[3] = {d_navigator->getDirection()[0],
                               d_navigator->getDirection()[1],
                               d_navigator->getDirection()[2]};

  this->embedInModel( model, position, direction, cell );
}

// Embed the particle in the desired model at the desired position
void ParticleState::embedInModel(
                           const std::shared_ptr<const Geometry::Model>& model,
                           const double position[3],
                           const double direction[3] )
{
  // Make sure that the model is valid
  testPrecondition( model.get() );

  // Create the new navigator
  d_navigator.reset( model->createNavigatorAdvanced( this->createAdvanceCompleteCallback() ) );

  // Cache the new model
  d_model = model;

  // Try to initialize the new navigator. If it fails to initialize, the
  // particle is lost.
  try{
    d_navigator->setState( Utility::reinterpretAsQuantity<Geometry::Navigator::Length>(position), direction );
  }
  catch( const std::exception& exception )
  {
    FRENSIE_LOG_WARNING( "Attempt to embed particle in geometry model "
                         << model->getName() << " failed! \n"
                         << exception.what() );
    d_lost = true;
  }
}

// Embed the particle in the desired model at the desired position
/*! \details The position must be inside of the cell. If it is not, the
 * particle will become lost.
 */
void ParticleState::embedInModel(
                        const std::shared_ptr<const Geometry::Model>& model,
                        const double position[3],
                        const double direction[3],
                        const Geometry::Model::EntityId cell )
{
  // Make sure that the model is valid
  testPrecondition( model.get() );

  // Create the new navigator
  d_navigator.reset( model->createNavigatorAdvanced( this->createAdvanceCompleteCallback() ) );

  // Cache the new model
  d_model = model;

  // Try to initialize the new navigator. If it fails to initialize, the
  // particle is lost.
  try{
    d_navigator->setState( Utility::reinterpretAsQuantity<Geometry::Navigator::Length>(position), direction, cell );
  }
  catch( const std::exception& exception )
  {
    FRENSIE_LOG_WARNING( "Attempt to embed particle in geometry model "
                         << model->getName() << " failed! \n"
                         << exception.what() );

    d_lost = true;
  }
}

// Extract the particle from the model
void ParticleState::extractFromModel()
{
  // Cache the current particle position and direction
  const Geometry::Navigator::Length position[3] =
    {d_navigator->getPosition()[0],
     d_navigator->getPosition()[1],
     d_navigator->getPosition()[2]};

  const double direction[3] = {d_navigator->getDirection()[0],
                               d_navigator->getDirection()[1],
                               d_navigator->getDirection()[2]};

  // Create a dummy model
  d_source_cell = 0;

  d_navigator.reset();

  d_model.reset( new Geometry::InfiniteMediumModel( d_source_cell ) );

  // Create the dummy navigator
  d_navigator.reset( d_model->createNavigatorAdvanced( this->createAdvanceCompleteCallback() ) );

  // Initialize the new navigator
  d_navigator->setState( position, direction );
}

// Check if a particle is embedded in the model of interest
/*! \details This check is currently done using a simple memory comparison
 * between the cached model and the model of interest.
 */
bool ParticleState::isEmbeddedInModel( const Geometry::Model& model ) const
{
  return d_model.get() == &model;
}

// Create the navigator AdvanceComplete callback method
// Note: We must "bind" the navigator to the particle state so that if we
//       change the navigator state, the particle state also gets changed.
//       Specifically, changes to the navigator's position must result in
//       a change to the particle's time based on the distance traveled and
//       the particle speed. Any navigator that the particle creates must use
//       the callback returned from this method to "bind" the navigator to the
//       particle state.
Geometry::Navigator::AdvanceCompleteCallback
ParticleState::createAdvanceCompleteCallback()
{
  return std::bind<void>( &ParticleState::increaseParticleTime,
                          std::ref(*this),
                          std::placeholders::_1 );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ParticleState );

} // end MonteCarlo

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleState.cpp
//---------------------------------------------------------------------------//
