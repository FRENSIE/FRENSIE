//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager.i
//! \author Luke Kersting
//! \brief  The ParticleSimulationManager classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "MonteCarlo_ParticleSimulationManager.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_ParticleSource.hpp"


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

%import "MonteCarlo_SimulationProperties.hpp"
%import "MonteCarlo_FilledGeometryModel.hpp"
%import "MonteCarlo_EventHandler.hpp"
%import "MonteCarlo_ParticleSource.hpp"

%shared_ptr(MonteCarlo::FilledGeometryModel);
%shared_ptr(MonteCarlo::ParticleSource);
%shared_ptr(MonteCarlo::EventHandler);
%shared_ptr(MonteCarlo::SimulationProperties);


// ---------------------------------------------------------------------------//
// Add ParticleSimulationManager support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::ParticleSimulationManager);

%include "MonteCarlo_ParticleSimulationManager.hpp"

// ---------------------------------------------------------------------------//
// Add ParticleSimulationManagerFactory support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_ParticleSimulationManagerFactory.hpp"

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.i
//---------------------------------------------------------------------------//
