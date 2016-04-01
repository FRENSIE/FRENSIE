//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTrackerFactory.hpp
//! \author Eli Moll
//! \brief  The particle tracker factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_TRACKER_FACTORY_HPP
#define MONTE_CARLO_PARTICLE_TRACKER_FACTORY_HPP

// Std Lib Includes
#include <iostream>
#include <stdexcept>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_ResponseFunction.hpp"

namespace MonteCarlo{

//! The particle tracker factory class
class ParticleTrackerFactory
{
  
public:

  //! Constructor
  ParticleTrackerFactory(
    const std::shared_ptr<EventHandler>& event_handler,
    std::ostream* os_warn = &std::cerr );
  
  //! Destructor
  ~ParticleTrackerFactory()
  { /*...*/ }  
  
  //! Check if the parameter list describes a particle tracker
  bool isParticleTrackerRep( const Teuchos::ParameterList& ptrac_rep ) const;
  
  //! Create and register a particle tracker
  void createAndRegisterParticleTracker(
                                   const Teuchos::ParameterList& ptrac_rep );

  //! Get the particle tracker ID
  unsigned getParticleTrackerID(
                              const Teuchos::ParameterList& ptrac_rep ) const;

  // Get the number of histories requested - optional
  void getNumberOfHistories( const Teuchos::ParameterList& ptrac_rep );

private:

  // Number of histories requested 
  unsigned d_number_histories;

  // The event handler
  std::shared_ptr<EventHandler> d_event_handler;

};

//! Helper function for creating an estimatory factory instance
inline std::shared_ptr<ParticleTrackerFactory> 
getParticleTrackerFactoryInstance( 
       const std::shared_ptr<EventHandler>& event_handler,
       std::ostream* os_warn = &std::cerr )
{
  return std::shared_ptr<ParticleTrackerFactory>(
    new ParticleTrackerFactory( event_handler,
                                os_warn ) );
}
 
//! The invalid estimator representation error
class InvalidParticleTrackerRepresentation : public std::runtime_error
{
  
public:

  InvalidParticleTrackerRepresentation( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};
 
} // end MonteCarlo namespace

#endif // MONTE_CARLO_PARTICLE_TRACKER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTrackerFactory.hpp
//---------------------------------------------------------------------------//
