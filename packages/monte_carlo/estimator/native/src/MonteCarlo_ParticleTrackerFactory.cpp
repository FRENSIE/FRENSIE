//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTrackerFactory.cpp
//! \author Eli Moll
//! \brief  The particle tracker factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleTrackerFactory.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleTrackerFactory::ParticleTrackerFactory(
  const std::shared_ptr<EventHandler>& event_handler,
  std::ostream* os_warn )
  : d_number_histories( 100u ),
  d_event_handler( event_handler )
{
  // Make sure the warning output stream is valid
  testPrecondition( os_warn );
}

// Check if the parameter list describes a particle tracker
bool ParticleTrackerFactory::isParticleTrackerRep(
                              const Teuchos::ParameterList& object_rep ) const
{
  bool is_ptrac_rep = false;
  
  if( object_rep.isParameter( "Type" ) )
  {
    std::string object_type = object_rep.get<std::string>( "Type" );
    
    if( object_type == "Particle Tracker" )
    {
      is_ptrac_rep = true;
    }
  }   
  
  return is_ptrac_rep;
}

// Create and register a particle tracker 
/*! \details This method is non-const because of the potential for info
 * caching in the derived classes.
 */
void ParticleTrackerFactory::createAndRegisterParticleTracker(
                                    const Teuchos::ParameterList& ptrac_rep )
{
  // Make sure the parameter list is a particle tracker rep 
  testPrecondition( this->isParticleTrackerRep( ptrac_rep ) );
  
  // Get the number of histories
  this->getNumberOfHistories( ptrac_rep );
  
  // Get the particle tracker ID
  unsigned ptrac_id;
  
  try{
    ptrac_id = this->getParticleTrackerID( ptrac_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidParticleTrackerRepresentation,
                              "Error: could not get the particle tracker id "
                              "for estimator " << ptrac_rep.name() << "!" );
  
  // Construct the new particle tracker
  std::shared_ptr<ParticleTracker> particle_tracker;
  particle_tracker.reset( new ParticleTracker( ptrac_id,
                                               d_number_histories ) );
  
  std::shared_ptr<ParticleTracker>
    derived_particle_tracker = std::dynamic_pointer_cast<ParticleTracker>( particle_tracker );
  
  d_event_handler->addGlobalEventObserver( derived_particle_tracker );
}

// Get the number of histories from the parameter list (if present)
void ParticleTrackerFactory::getNumberOfHistories(
                                    const Teuchos::ParameterList& ptrac_rep )
{
  if( ptrac_rep.isParameter( "Histories" ) )
  {
    d_number_histories = ptrac_rep.get<unsigned>( "Histories" );
  }
}

// Get the particle tracker ID
unsigned ParticleTrackerFactory::getParticleTrackerID(
                               const Teuchos::ParameterList& ptrac_rep ) const
{
  TEST_FOR_EXCEPTION( !ptrac_rep.isParameter( "Id" ),
                      InvalidParticleTrackerRepresentation,
                      "Error: the particle tracker id was not specified "
                      "in particle tracker " << ptrac_rep.name() << "!" );
                      
   return ptrac_rep.get<unsigned>( "Id" );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTrackerFactory.cpp
//---------------------------------------------------------------------------//