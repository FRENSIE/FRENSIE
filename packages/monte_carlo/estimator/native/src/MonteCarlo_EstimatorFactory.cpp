//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorFactory.cpp
//! \author Alex Robinson
//! \brief  The estimator factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EstimatorFactory.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string EstimatorFactory::s_surface_current_name = 
  "Surface Current";

const std::string EstimatorFactory::s_surface_flux_name = 
  "Surface Flux";

const std::string EstimatorFactory::s_cell_pulse_height_name = 
  "Cell Pulse Height";

const std::string EstimatorFactory::s_cell_track_length_flux_name = 
  "Cell Track-Length Flux";

const std::string EstimatorFactory::s_cell_collision_flux_name = 
  "Cell Collision Flux";

const std::string EstimatorFactory::s_tet_mesh_track_length_flux_name = 
  "Tet Mesh Track-Length Flux";

// Constructor
EstimatorFactory::EstimatorFactory(
          const std::shared_ptr<EventHandler>& event_handler,
          const boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> >&
          response_function_id_map,
          std::ostream* os_warn )
  : d_event_handler( event_handler ),
    d_response_function_id_map( response_function_id_map ),
    d_os_warn( os_warn )
{
  // Make sure the warning output stream is valid
  testPrecondition( os_warn );
}

// Check if the parameter list describes an estimator
bool EstimatorFactory::isEstimatorRep( 
                               const Teuchos::ParameterList& object_rep ) const
{
  bool is_estimator_rep = false;

  if( object_rep.isParameter( "Type" ) )
  {
    std::string object_type = object_rep.get<std::string>( "Type" );

    is_estimator_rep = this->isEstimator( object_type );
  }
}

// Create and register an estimator
/*! \details This method is non-const because of the potential for info
 * caching in the derived classes.
 */
void EstimatorFactory::createAndRegisterEstimator( 
                                  const Teuchos::ParameterList& estimator_rep )
{
  // Make sure the parameter list is an estimator rep
  testPrecondition( this->isEstimatorRep( estimator_rep ) );

  // Get the estimator id - required
  unsigned estimator_id;
  
  try{
    estimator_id = this->getEstimatorId( estimator_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidEstimatorRepresentation,
                              "Error: could not get the estimator id for "
                              "estimator " << estimator_rep.name() << "!" );

  // Make sure this id is valid
  TEST_FOR_EXCEPTION( d_event_handler->doesObserverExist( estimator_id ),
                      InvalidEstimatorRepresentation,
                      "Error: estimator id " << estimator_id << " is used by "
                      "another observer!" );

  // Get the estimator type
  std::string estimator_type;

  try{
    this->getEstimatorType( estimator_type, estimator_id, estimator_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidEstimatorRepresentation,
                              "Error: could not get the estimator type for "
                              "estimator " << estimator_id << "!" );

  // Get the estimator particle type - required
  Teuchos::Array<ParticleType> particle_types;

  try{
    this->getEstimatorParticleType( particle_types, 
                                    estimator_id, 
                                    estimator_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidEstimatorRepresentation,
                              "Error: could not get the particle type for"
                              "estimator " << estimator_id << "!" );

  // Get the estimator multiplier - optional
  double multiplier;

  try{
    multiplier = this->getEstimatorMultiplier( estimator_id, estimator_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidEstimatorRepresentation,
                              "Error: could not get the estimator multiplier "
                              "for estimator " << estimator_id << "!" );

  // Get the energy multiplication flag - optional
  bool energy_mult;

  try{
    energy_mult = this->isEnergyMultiplicationRequested( estimator_id,
                                                         estimator_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidEstimatorRepresentation,
                              "Error: could not get the estimator "
                              << estimator_id << " energy multiplication "
                              "flag!" );

  // Get the estimator bins - optional
  const Teuchos::ParameterList* estimator_bins;

  try{
    estimator_bins = this->getEstimatorBins( estimator_id, estimator_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidEstimatorRepresentation,
                              "Error: could not get the bins for estimator "
                              << estimator_id << "!" );

  // Get the response functions assigned to the estimator - optional
  Teuchos::Array<Teuchos::RCP<ResponseFunction> > response_functions;

  try{
    this->getResponseFunctions( response_functions,
                                estimator_id,
                                estimator_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidEstimatorRepresentation,
                              "Error: could not get the response functions "
                              "for estimator " << estimator_id << "!" );

  // Create and register a cell pulse height estimator
  if( this->isCellPulseHeightEstimator( estimator_type ) )
  {
    this->createAndRegisterCellPulseHeightEstimator( estimator_rep,
                                                     estimator_id,
                                                     multiplier,
                                                     particle_types,
                                                     response_functions,
                                                     energy_multiplication,
                                                     bins );
  }

  // Create and register a cell track length flux estimator
  else if( this->isCellTrackLengthFluxEstimator( estimator_type ) )
  {
    this->createAndRegisterCellTrackLengthFluxEstimator( estimator_rep,
                                                         estimator_id,
                                                         multiplier,
                                                         particle_types,
                                                         response_functions,
                                                         energy_multiplication,
                                                         bins );
  }

  // Create and register a cell collision flux estimator
  else if( this->isCellCollisionFluxEstimator( estimator_type ) )
  {
    this->createAndRegisterCellCollisionFluxEstimator( estimator_rep,
                                                       estimator_id,
                                                       multiplier,
                                                       particle_types,
                                                       response_functions,
                                                       energy_multiplication,
                                                       bins );
  }

  // Create and register a surface flux estimator
  else if( this->isSurfaceFluxEstimator( estimator_type ) )
  {
    this->createAndRegisterSurfaceFluxEstimator( estimator_rep,
                                                 estimator_id,
                                                 multiplier,
                                                 particle_types,
                                                 response_functions,
                                                 energy_multiplication,
                                                 bins );
  }

  // Create and register a surface current estimator
  else if( this->isSurfaceCurrentEstimator( estimator_type ) )
  {
    this->createAndRegisterSurfaceCurrentEstimator( estimator_rep,
                                                    estimator_id,
                                                    multiplier,
                                                    particle_types,
                                                    response_functions,
                                                    energy_multiplication,
                                                    bins );
  }

  // Create and register a tet mesh track length flux estimator
  else if( this->isTetMeshTrackLengthFluxEstimator( estimator_type ) )
  {
    this->createAndRegisterTetMeshTrackLengthFluxEstimator( estimator_rep,
                                                            estimator_id,
                                                            multiplier,
                                                            particle_types,
                                                            response_functions,
                                                            energy_multiplication,
                                                            bins );
  }

  // Invalid estimator type
  else
  {
    THROW_EXCEPTION( InvalidEstimatorRepresentation,
                     "Error: estimator type " << estimator_type << 
                     " is invalid!" );
  }

  // Update the estimator cache info
  this->updateEstimatorCacheInfo( estimator_id );

  // Print unused parameters
  estimator_rep.unused( *d_os_warn );
}

// Check if an estimator type is a cell pulse height estimator
bool EstimatorFactory::isCellPulseHeightEstimator( 
                                            const std::string& estimator_name )
{
  return estimator_name == s_cell_pulse_height_name;
}

// Check if an estimator type is a cell track length flux estimator
bool EstimatorFactory::isCellTrackLengthFluxEstimator( 
					   const std::string& estimator_name )
{
  return estimator_name == s_cell_track_length_flux_name;
}

// Check if an estimator type is a cell collision flux estimator
bool EstimatorFactory::isCellCollisionFluxEstimator(
                                            const std::string& estimator_name )
{
  return estimator_name == s_cell_collision_flux_name;
}

// Check if an estimator type is a cell estimator
bool EstimatorFactory::isCellEstimator( const std::string& estimator_name )
{
  return isCellPulseHeightEstimator( estimator_name ) ||
    isCellTrackLengthFluxEstimator( estimator_name ) ||
    isCellCollisionFluxEstimator( estimator_name );
}

// Check if an estimator type is a surface flux estimator
bool EstimatorFactory::isSurfaceFluxEstimator( 
                                            const std::string& estimator_name )
{
  return estimator_name == s_surface_flux_name;
}

// Check if an estimator type is a surface current estimator
bool EstimatorFactory::isSurfaceCurrentEstimator( 
                                            const std::string& estimator_name )
{
  return estimator_name == s_surface_current_name;
}

// Check if an estimator type is a surface estimator
bool EstimatorFactory::isSurfaceEstimator( const std::string& estimator_name )
{
  return isSurfaceFluxEstimator( estimator_name ) ||
    isSurfaceCurrentEstimator( estimator_name );
}

// Check if an estimator type is a tet mesh track length flux estimator
bool EstimatorFactory::isTetMeshTrackLengthFluxEstimator( 
                                           const std::string& estimator_name )
{
  return estimator_name == s_tet_mesh_track_length_flux_name;
}

// Check if an estimator type is a mesh estimator
bool EstimatorFactory::isMeshEstimator( const std::string& estimator_name )
{
  return isTetMeshTrackLengthFluxEstimator( estimator_name );
}

// Check if an object type is an estimator
bool EstimatorFactory::isEstimator( const std::string& object_name )
{
  return isCellEstimator( object_name ) ||
    isSurfaceEstimator( object_name ) ||
    isMeshEstimator( object_name );
}

// Get the estimator id - required
unsigned EstimatorFactory::getEstimatorId( 
                            const Teuchos::ParameterList& estimator_rep ) const
{
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Id" ),
                      InvalidEstimatorRepresentation,
                      "Error: the estimator id was not specified in estimator "
                      << estimator_rep.name() << "!" );
  
  return estimator_rep.get<unsigned>( "Id" );
}

// Get the estimator type - required
void EstimatorFactory::getEstimatorType( std::string& estimator_type,
                                         const unsigned estimator_id,
                                         const Teuchos::ParameterList& estimator_rep ) const
{
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Type" ),
                      InvalidEstimatorRepresentation,
                      "Error: estimator " << estimator_id << " does not have "
                      "a type specified!" );

  estimator_type = estimator_rep.get<std::string>( "Type" );

  // Make sure the estimator type is consistent with cached data
  this->verifyEstimatorTypeConsistency( estimator_id, estimator_type );
}

// Get the estimator particle types - required
void EstimatorFactory::getEstimatorParticleType( 
                                  Teuchos::Array<ParticleType>& particle_types,
                                  const unsigned estimator_id,
                                  const Teuchos::ParameterList& estimator_rep ) const
{
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Particle Type" ),
                      InvalidEstimatorRepresentation,
                      "Error: estimator " << estimator_id << " does not have "
                      "a particle type specified!" );

  const std::string& particle_type = 
    estimator_rep.get<std::string>( "Particle Type" );

  TEST_FOR_EXCEPTION( !isValidParticleTypeName( particle_type ),
                      InvalidEstimatorRepresentation,
                      "Error: estimator " << estimator_id << " specified "
                      "particle type " << particle_type << " which is not "
                      "valid!" );

  particle_types.resize( 1 );
  particle_type[0] = 
    convertParticleTypeNameToParticleTypeEnum( estimator_particle_type );
}

// Get the estimator multiplier - optional
double EstimatorFactory::getEstimatorMultiplier( 
                            const unsigned estimator_id,
                            const Teuchos::ParameterList& estimator_rep ) const
{
  double multiplier = 1.0;

  if( estimator_rep.isParameter( "Multiplier" ) )
    multiplier = estimator_rep.get<double>( "Multiplier" );

  TEST_FOR_EXCEPTION( multiplier <= 0.0,
                      InvalidEstimatorRepresentation,
                      "Error: estimator " << id << " has a negative "
                      "multiplier specified!" );

  return multiplier;
}

// Check if energy multiplication was requested - optional
bool EstimatorFactory::isEnergyMultiplicationRequested( 
                            const unsigned estimator_id,
                            const Teuchos::ParameterList& estimator_rep ) const
{
  bool energy_mult = false;

  if( estimator_rep.isParameter( "Energy Multiplication" ) )
    energy_mult = estimator_rep.get<bool>( "Energy Multiplication" ); 

  return energy_mult;
}

// Get the estimator bins - optional
const Teuchos::ParameterList* EstimatorFactory::getEstimatorBins( 
                            const unsigned estimator_id,
                            const Teuchos::ParameterList& estimator_rep ) const
{
  const Teuchos::ParameterList* estimator_bins = NULL;

  if( estimator_rep.isParameter( "Bins" ) )
    estimator_bins = &estimator_rep.get<Teuchos::ParameterList>( "Bins" );

  return estimator_bins;
}

// Get the response functions assigned to the estimator - optional
void EstimatorFactory::getResponseFunctions( 
           Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions,
           const unsigned estimator_id,
           const Teuchos::ParameterList& estimator_rep ) const
{
  if( estimator_rep.isParameter( "Response Functions" ) )
  {
    const Utility::ArrayString& array_string = 
      estimator_rep.get<Utility::ArrayString>( "Response Functions" );

    Teuchos::Array<unsigned> requested_response_functions;

    try{
      requested_response_functions = 
        array_string.getConcreteArray<unsigned>();
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                InvalidEstimatorRepresentation,
                                "Error: the response functions requested for"
                                " estimator " << id << " are not valid!" );

    response_functions.resize( requested_response_functions.size() );

    for( unsigned i = 0; i < requested_response_functions.size(); ++i )
    {
      TEST_FOR_EXCEPTION( d_response_function_id_map.find( requested_response_functions[i] ) ==
                          d_response_function_id_map.end(),
                          InvalidEstimatorRepresentation,
                          "Error: estimator " << id << " has requested "
                          "response function " << 
                          requested_response_functions[i] << 
                          " which does not exist!" );

      response_functions[i] = d_response_function_id_map.find( 
                                     requested_response_functions[i] )->second;
    }
  }
}

// Create and register a cell pulse height estimator
void EstimatorFactory::createAndRegisterCellPulseHeightEstimator(
      const Teuchos::ParameterList& estimator_rep,
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL ) const
{
  // Make sure the parameter list is valid
  testPrecondition( this->getEstimatorId( estimator_rep ) == id );
  testPrecondition( this->getEstimatorType( estimator_rep ) ==
                    s_cell_pulse_height_name );
  
  std::shared_ptr<Estimator> estimator;

  // Get the estimator cells
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> cells;
  
  this->getEstimatorCells( cells, id, estimator_rep );

  if( energy_multiplication )
  {
    estimator.reset( new CellPulseHeightEstimator<WeightAndEnergyMultiplier>(
								    id,
						                    multiplier,
								    cells ) );
  }
  else
  {
    estimator.reset( new CellPulseHeightEstimator<WeightMultiplier>(id,
								    multiplier,
								    cells ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs ); 

  // Assign estimator bins
  if( bins )
    this->assignBinsToEstimator( *bins, estimator );
  // Add this estimator to the handler
  if( energy_multiplication )
  {
    std::shared_ptr<CellPulseHeightEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = std::dynamic_pointer_cast<CellPulseHeightEstimator<WeightAndEnergyMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, cells );
  }
  else
  {
    std::shared_ptr<CellPulseHeightEstimator<WeightMultiplier> >
      derived_estimator = std::dynamic_pointer_cast<CellPulseHeightEstimator<WeightMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, cells );
  }
}

// Create and register a cell track length flux estimator
void EstimatorFactory::createAndRegisterCellTrackLengthFluxEstimator(
      const Teuchos::ParameterList& estimator_rep,
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL )
{
  // Make sure the parameter list is valid
  testPrecondition( this->getEstimatorId( estimator_rep ) == id );
  testPrecondition( this->getEstimatorType( estimator_rep ) ==
                    s_cell_track_length_flux_name );
  
  std::shared_ptr<Estimator> estimator;

  // Get the estimator cells
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> cells;
  
  this->getEstimatorCells( cells, id, estimator_rep );

  // Get the cell volumes
  Teuchos::Array<double> cell_volumes;

  this->getCellVolumes( cell_volumes, cells );
  
  if( energy_multiplication )
  {
    estimator.reset( 
	          new CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }
  else
  {
    estimator.reset( new CellTrackLengthFluxEstimator<WeightMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    this->assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    std::shared_ptr<CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = std::dynamic_pointer_cast<CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, cells );
  }
  else
  {
    std::shared_ptr<CellTrackLengthFluxEstimator<WeightMultiplier> >
      derived_estimator = std::dynamic_pointer_cast<CellTrackLengthFluxEstimator<WeightMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, cells );
  }
}
  
// Create and register a cell collision flux estimator
void EstimatorFactory::createAndRegisterCellCollisionFluxEstimator(
      const Teuchos::ParameterList& estimator_rep,
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication = false,
      const Teuchos::ParameterList* bins = NULL ) const  
{
  // Make sure the parameter list is valid
  testPrecondition( this->getEstimatorId( estimator_rep ) == id );
  testPrecondition( this->getEstimatorType( estimator_rep ) ==
                    s_cell_collision_flux_name );
  
  std::shared_ptr<Estimator> estimator;

  // Get the estimator cells
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> cells;
  
  this->getEstimatorCells( cells, id, estimator_rep );

  // Get the cell volumes
  Teuchos::Array<double> cell_volumes;

  this->getCellVolumes( cell_volumes, cells );
  
  if( energy_multiplication )
  {
    estimator.reset( new CellCollisionFluxEstimator<WeightAndEnergyMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }
  else
  {
    estimator.reset( new CellCollisionFluxEstimator<WeightMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    this->assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    std::shared_ptr<CellCollisionFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = std::dynamic_pointer_cast<CellCollisionFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, cells );
  }
  else
  {
    std::shared_ptr<CellCollisionFluxEstimator<WeightMultiplier> >
      derived_estimator = std::dynamic_pointer_cast<CellCollisionFluxEstimator<WeightMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, cells );
  }
}

// Create and register a surface flux estimator
void createAndRegisterSurfaceFluxEstimator(
         const Teuchos::ParameterList& estimator_rep,
         const unsigned id,
	 const double multiplier,
	 const Teuchos::Array<ParticleType> particle_types,
         const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
	 const bool energy_multiplication = false,
	 const Teuchos::ParameterList* bins = NULL )
{
  // Make sure the parameter list is valid
  testPrecondition( this->getEstimatorId( estimator_rep ) == id );
  testPrecondition( this->getEstimatorType( estimator_rep ) ==
                    s_surface_flux_name );
  
  std::shared_ptr<Estimator> estimator;

  // Get the estimator surfaces
  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> surfaces;
  
  this->getEstimatorSurfaces( surfaces, id, estimator_rep );

  // Get the surface ares
  Teuchos::Array<double> surface_areas

  this->getCellVolumes( surface_areas, surfaces );

  if( energy_multiplication )
  {
    estimator.reset( new SurfaceFluxEstimator<WeightAndEnergyMultiplier>(
							      id,
							      multiplier,
							      surfaces,
							      surface_areas ) );
  }
  else
  {
    estimator.reset( new SurfaceFluxEstimator<WeightMultiplier>(
							      id,
							      multiplier,
							      surfaces,
							      surface_areas ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    this->assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    std::shared_ptr<SurfaceFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = std::dynamic_pointer_cast<SurfaceFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, surfaces );
  }
  else
  {
    std::shared_ptr<SurfaceFluxEstimator<WeightMultiplier> >
      derived_estimator = std::dynamic_pointer_cast<SurfaceFluxEstimator<WeightMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, surfaces );
  }
}

// Create a surface current estimator
void createAndRegisterSurfaceCurrentEstimator(
         const Teuchos::ParameterList& estimator_rep,
         const unsigned id,
	 const double multiplier,
	 const Teuchos::Array<ParticleType> particle_types,
         const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
	 const bool energy_multiplication = false,
	 const Teuchos::ParameterList* bins = NULL ) const
{
  // Make sure the parameter list is valid
  testPrecondition( this->getEstimatorId( estimator_rep ) == id );
  testPrecondition( this->getEstimatorType( estimator_rep ) ==
                    s_surface_current_name );
  
  std::shared_ptr<Estimator> estimator;

  // Get the estimator surfaces
  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> surfaces;
  
  this->getEstimatorSurfaces( surfaces, id, estimator_rep );

  if( energy_multiplication )
  {
    estimator.reset( new SurfaceCurrentEstimator<WeightAndEnergyMultiplier>(
							          id,
							          multiplier,
							          surfaces ) );
  }
  else
  {
    estimator.reset( new SurfaceCurrentEstimator<WeightMultiplier>(
							          id,
							          multiplier,
							          surfaces ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    this->assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    std::shared_ptr<SurfaceCurrentEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = std::dynamic_pointer_cast<SurfaceCurrentEstimator<WeightAndEnergyMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, surfaces );
  }
  else
  {
    std::shared_ptr<SurfaceCurrentEstimator<WeightMultiplier> >
      derived_estimator = std::dynamic_pointer_cast<SurfaceCurrentEstimator<WeightMultiplier> >( estimator );

    d_event_handler->addEntityEventObserver( derived_estimator, surfaces );
  }
}

// Create and register a tet mesh track length flux estimator
void EstimatorFactory::createAndRegisterTetMeshTrackLengthFluxEstimator(
         const Teuchos::ParameterList& estimator_rep,
	 const unsigned id,
	 const double multiplier,
	 const Teuchos::Array<ParticleType> particle_types,
	 const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
         const bool energy_multiplication = false,
	 const Teuchos::ParameterList* bins = NULL ) const
{
  // Make sure the parameter list is valid
  testPrecondition( this->getEstimatorId( estimator_rep ) == id );
  testPrecondition( this->getEstimatorType( estimator_rep ) ==
                    s_tet_mesh_track_length_flux_name );
  
  std::shared_ptr<Estimator> estimator;

  // Get the mesh file name
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Mesh File Name" ),
                      InvalidEstimatorRepresentation,
                      "Error: mesh estimator " << id <<
                      " does not have a mesh file name specified!" );
  
  std::string mesh_file_name = estimator_rep.get<std::string>( 
							    "Mesh File Name" );

  // Get the output mesh file name
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Output Mesh File Name"),
                      InvalidEstimatorRepresentation,
                      "Error: mesh estimator " << id <<
                      " does not have an output file name specified! ");
  
  std::string output_mesh_file_name = estimator_rep.get<std::string>(
						     "Output Mesh File Name" );
  
  if( energy_multiplication )
  {
    estimator.reset( new TetMeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier>(
						     id,
						     multiplier,
						     mesh_file_name,
						     output_mesh_file_name ) );
  }
  else
  {
    estimator.reset( new TetMeshTrackLengthFluxEstimator<WeightMultiplier>(
						     id,
						     multiplier,
						     mesh_file_name,
						     output_mesh_file_name ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    this->assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    std::shared_ptr<TetMeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = std::dynamic_pointer_cast<TetMeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    d_event_handler->addGlobalEventObserver( derived_estimator );
  }
  else
  {
    std::shared_ptr<TetMeshTrackLengthFluxEstimator<WeightMultiplier> >
      derived_estimator = std::dynamic_pointer_cast<TetMeshTrackLengthFluxEstimator<WeightMultiplier> >( estimator );

    d_event_handler->addGlobalEventObserver( derived_estimator );
  }
}

// Return the warning output stream
std::ostream& getWarningOutputStream() const
{
  return *d_os_warn;
}

// Assign bins to an estimator
void assignBinsToEstimator( const Teuchos::ParameterList& bins,
                            std::shared_ptr<Estimator>& estimator ) const 
{
  Teuchos::ParameterList::ConstIterator it = bins.begin();

  while( it != bins.end() )
  {
    if( bins.name( it ) == "Energy Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<double> energy_bins;
      
      try{
	energy_bins = array_string.getConcreteArray<double>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the energy bins requested for "
				  "estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION(!Utility::Sort::isSortedAscending(energy_bins.begin(),
							   energy_bins.end() ),
                         InvalidEstimatorRepresentation,
                         "Error: the energy bins requested for estimator "
                         << estimator->getId() << " are not sorted from "
                         "lowest to highest!" );
    
      estimator->setBinBoundaries<ENERGY_DIMENSION>( energy_bins );
    }

    else if( bins.name( it ) == "Time Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<double> time_bins;

      try{
	time_bins = array_string.getConcreteArray<double>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the time bins requested for "
				  "estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( time_bins.begin(),
							     time_bins.end() ),
			  InvalidEstimatorRepresentation,
			  "Error: the time bins requested for estimator "
			  << estimator->getId() << " are not sorted from "
			  "lowest to highest!" );

      estimator->setBinBoundaries<TIME_DIMENSION>( time_bins );
    }

    else if( bins.name( it ) == "Collision Number Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<unsigned> col_num_bins;
      
      try{
	col_num_bins = array_string.getConcreteArray<unsigned>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the collision number bins requested "
				  "for estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending(
							  col_num_bins.begin(),
							  col_num_bins.end() ),
			  InvalidEstimatorRepresentation,
			  "Error: the collision number bins requested for "
			  "estimator " << estimator->getId() << " are not "
			  "sorted from lowest to highest!" );

      estimator->setBinBoundaries<COLLISION_NUMBER_DIMENSION>( col_num_bins );
    }

    else if( bins.name( it ) == "Cosine Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<double> cosine_bins;

      try{
	cosine_bins = array_string.getConcreteArray<double>();
      }

      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the cosine bins requested "
				  "for estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION(!Utility::Sort::isSortedAscending(cosine_bins.begin(),
							   cosine_bins.end() ),
			  InvalidEstimatorRepresentation,
			  "Error: the cosine bins requested for estimator "
			  << estimator->getId() << " are not sorted from "
			  "lowest to highest!" );

      estimator->setBinBoundaries<COSINE_DIMENSION>( cosine_bins );
    }
    
    ++it;
  }

  bins.unused( *d_os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorFactory.cpp
//---------------------------------------------------------------------------//
