//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager.i
//! \author Luke Kersting
//! \brief  The ParticleSimulationManager classes interface file
//!
//---------------------------------------------------------------------------//

%{
// Std Lib Includes
#include <csignal>
#include <functional>
#include <thread>
#include <set>
  
// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_StandardParticleSimulationManager.hpp"
#include "MonteCarlo_BatchedDistributedStandardParticleSimulationManager.hpp"
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_ParticleSource.hpp"
#include "Utility_Communicator.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_OpenMPProperties.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>
%include <std_shared_ptr.i>

// Include typemaps support
%include <typemaps.i>

// Standard exception handling
%include "exception.i"

// General exception handling
%exception
{
  try{
    $action;
    if( PyErr_Occurred() )
      SWIG_fail;
  }
  catch( Utility::ContractException& e )
  {
    SWIG_exception( SWIG_ValueError, e.what() );
  }
  catch( std::runtime_error& e )
  {
    SWIG_exception( SWIG_RuntimeError, e.what() );
  }
  catch( ... )
  {
    SWIG_exception( SWIG_UnknownError, "Unknown C++ exception" );
  }
}

// Add a few general typedefs
typedef unsigned long int uint64_t;

// Import the classes needed to construct the ParticleSimulationManagerFactory
%import "MonteCarlo_SimulationGeneralProperties.hpp"
%import "MonteCarlo_SimulationProperties.hpp"
%import "MonteCarlo_FilledGeometryModel.hpp"
%import "MonteCarlo_EventHandler.hpp"
%import "MonteCarlo_ParticleSource.hpp"
%import "MonteCarlo_CollisionForcer.hpp"

%shared_ptr(MonteCarlo::FilledGeometryModel);
%shared_ptr(MonteCarlo::ParticleSource);
%shared_ptr(MonteCarlo::EventHandler);
%shared_ptr(MonteCarlo::SimulationGeneralProperties);
%shared_ptr(MonteCarlo::SimulationProperties);
%shared_ptr(MonteCarlo::CollisionForcer);

// ---------------------------------------------------------------------------//
// Add ParticleSimulationManager support
// ---------------------------------------------------------------------------//

%{
  void delayedInterrupt( const double duration_in_sec )
  {
    std::shared_ptr<Utility::Timer> timer =
      Utility::OpenMPProperties::createTimer();

    timer->start();
    
    while( timer->elapsed().count() < duration_in_sec );
    
    timer->stop();
    timer.reset();
    
    // Terminate the simulation (it is set up to run indefinitely unless it
    // receives an interput signal)
    std::raise( SIGINT );
  }
%}

%extend MonteCarlo::ParticleSimulationManager
{
  /*! \brief Run a simulation that can be interrupted by the user (used for
   *  testing purposes to check SIGINT signal handling)
   */
  void runInterruptibleSimulationForDuration( const double duration_in_sec )
  {
    
    std::thread t1( std::bind<void>( &MonteCarlo::ParticleSimulationManager::runInterruptibleSimulation, std::ref(*$self) ) );
    std::thread t2( ::delayedInterrupt, duration_in_sec );
    
    t1.join();
    t2.join();
  }
}

%shared_ptr(MonteCarlo::ParticleSimulationManager);

%include "MonteCarlo_ParticleSimulationManager.hpp"

// Add functions for testing the particle simulation manager
%inline %{
  uint64_t broadcast( uint64_t broadcast )
  {
    std::shared_ptr<const Utility::Communicator> comm =
      Utility::Communicator::getDefault();

    Utility::broadcast( *comm, broadcast, 0 );

    return broadcast;
  }
%}


// ---------------------------------------------------------------------------//
// Add ParticleSimulationManagerFactory support
// ---------------------------------------------------------------------------//

// Add typemaps for converting file_path to and from Python string
%typemap(in) const boost::filesystem::path& ( boost::filesystem::path temp ){
  temp = PyString_AsString( $input );
  $1 = &temp;
}

%typemap(typecheck, precedence=1140) (const boost::filesystem::path&) {
  $1 = (PyString_Check($input)) ? 1 : 0;
}

%include "MonteCarlo_ParticleSimulationManagerFactory.hpp"

// Add functions for testing the particle simulation manager type
%define %standard_simulation_manager_test( DISTRIBUTION_BASE, PARTICLE_MODE, MODE_NAME )

  %inline %{
    // Return if the manager is a DISTRIBUTION_BASE ParticleSimulationManager PARTICLE_MODE
    bool is ## DISTRIBUTION_BASE ## MODE_NAME ## SimulationManager(
        std::shared_ptr<MonteCarlo::ParticleSimulationManager> manager )
    {
      std::shared_ptr<MonteCarlo::DISTRIBUTION_BASE ## ParticleSimulationManager<MonteCarlo::PARTICLE_MODE> > true_manager = std::dynamic_pointer_cast<MonteCarlo::DISTRIBUTION_BASE ## ParticleSimulationManager<MonteCarlo::PARTICLE_MODE> >( manager );

      return true_manager.get() != NULL;
    }
  %}

%enddef

%standard_simulation_manager_test( Standard, NEUTRON_MODE, Neutron )
%standard_simulation_manager_test( Standard, PHOTON_MODE, Photon )
%standard_simulation_manager_test( Standard, ELECTRON_MODE, Electron )
%standard_simulation_manager_test( Standard, NEUTRON_PHOTON_MODE, NeutronPhoton )
%standard_simulation_manager_test( Standard, PHOTON_ELECTRON_MODE, PhotonElectron )
%standard_simulation_manager_test( Standard, NEUTRON_PHOTON_ELECTRON_MODE, NeutronPhotonElectron )
%standard_simulation_manager_test( Standard, ADJOINT_NEUTRON_MODE, AdjointNeutron )
%standard_simulation_manager_test( Standard, ADJOINT_PHOTON_MODE, AdjointPhoton )
%standard_simulation_manager_test( Standard, ADJOINT_ELECTRON_MODE, AdjointElectron )

%standard_simulation_manager_test( BatchedDistributedStandard, NEUTRON_MODE, Neutron )
%standard_simulation_manager_test( BatchedDistributedStandard, PHOTON_MODE, Photon )
%standard_simulation_manager_test( BatchedDistributedStandard, ELECTRON_MODE, Electron )
%standard_simulation_manager_test( BatchedDistributedStandard, NEUTRON_PHOTON_MODE, NeutronPhoton )
%standard_simulation_manager_test( BatchedDistributedStandard, PHOTON_ELECTRON_MODE, PhotonElectron )
%standard_simulation_manager_test( BatchedDistributedStandard, NEUTRON_PHOTON_ELECTRON_MODE, NeutronPhotonElectron )
%standard_simulation_manager_test( BatchedDistributedStandard, ADJOINT_NEUTRON_MODE, AdjointNeutron )
%standard_simulation_manager_test( BatchedDistributedStandard, ADJOINT_PHOTON_MODE, AdjointPhoton )
%standard_simulation_manager_test( BatchedDistributedStandard, ADJOINT_ELECTRON_MODE, AdjointElectron )

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.i
//---------------------------------------------------------------------------//
