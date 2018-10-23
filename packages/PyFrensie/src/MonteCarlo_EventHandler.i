//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandler.i
//! \author Luke Kersting
//! \brief  The EventHandler class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"


using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Simulation properties handling
%import(module="PyFrensie.MonteCarlo") MonteCarlo_SimulationProperties.i

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

// ---------------------------------------------------------------------------//
// Add EventHandler support
// ---------------------------------------------------------------------------//

%shared_ptr(MonteCarlo::EventHandler)

// Define the updateObserversFromParticle from the base classes
// %extend MonteCarlo::EventHandler
// {
//   // Update the observers from a surface intersection event
//   void updateObserversFromParticleCrossingSurfaceEvent(
//                               const ParticleState& particle,
//                               const Geometry::Model::EntityId surface_crossing,
//                               const double surface_normal[3] )
//   {
//     $self->updateObserversFromParticleCrossingSurfaceEvent(
//       particle, surface_crossing, surface_normal );
//   };

//   // Update the observers from a particle entering cell event
//   void updateObserversFromParticleEnteringCellEvent(
//                                const ParticleState& particle,
//                                const Geometry::Model::EntityId cell_entering )
//   {
//     $self->updateObserversFromParticleEnteringCellEvent(
//       particle, cell_entering );
//   };

//   // Update the observers from a particle leaving cell event
//   void updateObserversFromParticleLeavingCellEvent(
//                                 const ParticleState& particle,
//                                 const Geometry::Model::EntityId cell_leaving )
//   {
//     $self->updateObserversFromParticleLeavingCellEvent(
//       particle, cell_leaving );
//   };

//   // Update the observers from a particle colliding in cell event
//   void updateObserversFromParticleCollidingInCellEvent(
//                                     const ParticleState& particle,
//                                     const double inverse_total_cross_section )
//   {
//     $self->updateObserversFromParticleCollidingInCellEvent(
//       particle, inverse_total_cross_section );
//   }

//   // Update the observers from a particle subtrack ending in cell event
//   void updateObserversFromParticleSubtrackEndingInCellEvent(
//                               const ParticleState& particle,
//                               const Geometry::Model::EntityId cell_of_subtrack,
//                               const double particle_subtrack_length )
//   {
//     $self->updateObserversFromParticleSubtrackEndingInCellEvent(
//       particle, cell_of_subtrack, particle_subtrack_length );
//   }

//   // Update the global estimators from a subtrack ending event
//   void updateObserversFromParticleSubtrackEndingGlobalEvent(
//       const ParticleState& particle,
//       const double start_point[3],
//       const double end_point[3] )
//   {
//     $self->updateObserversFromParticleSubtrackEndingGlobalEvent(
//       particle, start_point, end_point );
//   }

//   // Update the global estimators from a subtrack ending event
//   void updateObserversFromParticleGoneGlobalEvent( const ParticleState& particle )
//   {
//     $self->updateObserversFromParticleGoneGlobalEvent(
//       particle );
//   }
// };

%ignore MonteCarlo::EventHandler::enableThreadSupport;
%ignore MonteCarlo::EventHandler::updateObserversFromParticleSimulationStartedEvent;
%ignore MonteCarlo::EventHandler::updateObserversFromParticleSimulationStoppedEvent;
%ignore MonteCarlo::EventHandler::commitObserverHistoryContributions;
%ignore MonteCarlo::EventHandler::resetObserverData;
%ignore MonteCarlo::EventHandler::reduceObserverData;
%ignore MonteCarlo::EventHandler::registerObserver;

%include "MonteCarlo_EventHandler.hpp"

// Add addEstimator function templates
%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >;

%template(addEstimator) MonteCarlo::EventHandler::addEstimator<MonteCarlo::CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier> >;

//---------------------------------------------------------------------------//
// Turn off the exception handling
//---------------------------------------------------------------------------//
%exception;

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandler.i
//---------------------------------------------------------------------------//
