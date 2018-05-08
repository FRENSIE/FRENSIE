//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionKernel.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Collision kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_KERNEL_HPP
#define MONTE_CARLO_COLLISION_KERNEL_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NeutronCollisionKernel.hpp"
#include "MonteCarlo_PhotonCollisionKernel.hpp"
#include "MonteCarlo_AdjointPhotonCollisionKernel.hpp"
#include "MonteCarlo_ElectronCollisionKernel.hpp"
#include "MonteCarlo_AdjointElectronCollisionKernel.hpp"
#include "MonteCarlo_PositronCollisionKernel.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The collision kernel class
 * \details The collision kernel class has been designed as a mix-in class
 * so that it is easier to add support for new particle types. In addition, the
 * individual, particle specific collision kernels are better abstracted and 
 * easier to maintain than a single, monolithic collision kernel.
 */
class CollisionKernel : public NeutronCollisionKernel,
                        public PhotonCollisionKernel,
                        public AdjointPhotonCollisionKernel,
                        public ElectronCollisionKernel,
                        public AdjointElectronCollisionKernel,
                        public PositronCollisionKernel
{

public:

  //! Constructor
  CollisionKernel(
              const std::shared_ptr<const FilledGeometryModel>& geometry_model,
              const SimulationProperties& properties );

  //! Destructor
  ~CollisionKernel()
  { /* ... */ }

  //! Have a neutron collide with the material in a cell
  using NeutronCollisionKernel::collideWithCellMaterial;

  //! Have a photon collide with the material in a cell
  using PhotonCollisionKernel::collideWithCellMaterial;

  //! Have an adjoint photon collide with the material in a cell
  using AdjointPhotonCollisionKernel::collideWithCellMaterial;

  //! Have an electron collide with the material in a cell
  using ElectronCollisionKernel::collideWithCellMaterial;

  //! Have an adjoint electron collide with the material in a cell
  using AdjointElectronCollisionKernel::collideWithCellMaterial;

  //! Have an positron collide with the material in a cell
  using PositronCollisionKernel::collideWithCellMaterial;

  //! Check if the transport kernel is defined on the model of interest
  bool isDefinedOnModel( const FilledGeometryModel& model ) const;

private:

  // The geometry model
  std::shared_ptr<const FilledGeometryModel> d_model;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_KERNEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionKernel.hpp
//---------------------------------------------------------------------------//
