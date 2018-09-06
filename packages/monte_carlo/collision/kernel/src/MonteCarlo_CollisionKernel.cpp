//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionKernel.cpp
//! \author Alex Robinson
//! \brief  Collision kernel class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CollisionKernel.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
CollisionKernel::CollisionKernel(
              const std::shared_ptr<const FilledGeometryModel>& geometry_model,
              const SimulationProperties& properties )
  : NeutronCollisionKernel( geometry_model, properties.isImplicitCaptureModeOn() ? false : true ),
    PhotonCollisionKernel( geometry_model, properties.isImplicitCaptureModeOn() ? false : true ),
    AdjointPhotonCollisionKernel( geometry_model, properties.isImplicitCaptureModeOn() ? false : true ),
    ElectronCollisionKernel( geometry_model, properties.isImplicitCaptureModeOn() ? false : true ),
    AdjointElectronCollisionKernel( geometry_model, properties.isImplicitCaptureModeOn() ? false : true ),
    PositronCollisionKernel( geometry_model, properties.isImplicitCaptureModeOn() ? false : true ),
    d_model( geometry_model )
{ /* ... */ }

// Check if the transport kernel is defined on the model of interest
bool CollisionKernel::isDefinedOnModel( const FilledGeometryModel& model ) const
{
  return d_model.get() == &model;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionKernel.cpp
//---------------------------------------------------------------------------//
