//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  The standard particle collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_HPP

// Std Lib Includes
#include <unordered_map>
#include <functional>
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The standard particle collision handler class
template<typename DerivedHandlerTypeTraits>
class StandardParticleCollisionHandler
{

private:

  // Typedef for this type
  typedef StandardParticleCollisionHandler<DerivedHandlerTypeTraits> ThisType;

public:

  //! Constructor
  StandardParticleCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~StandardParticleCollisionHandler()
  { /* ... */ }

  //! Add a material to the collision handler
  void addMaterial(
           const Teuchos::RCP<const typename DerivedHandlerTypeTraits::MaterialType>&
           material,
           const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
           cells_containing_material );

  //! Check if a cell is void
  bool isCellVoid(
                 const Geometry::ModuleTraits::InternalCellHandle cell ) const;

  //! Get the material contained in a cell
  const Teuchos::RCP<const typename DerivedHandlerTypeTraits::MaterialType>&
  getMaterial( const Geometry::ModuleTraits::InternalCellHandle cell ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSection(
       const typename DerivedHandlerTypeTraits::ParticleType& particle ) const;

  //! Get the total forward macroscopic cross section of a material
  virtual double getMacroscopicTotalForwardCrossSection(
       const typename DerivedHandlerTypeTraits::ParticleType& particle ) const;

  //! Collide with the material in a cell
  virtual void collideWithCellMaterial(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const;

private:

  //! Collide with the material in a cell (analogue)
  void collideWithCellMaterialAnalogue(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const;

  //! Collide with the material in a cell (survival bias)
  void collideWithCellMaterialSurvivalBias(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const;

  // The collision method function pointer
  std::function<void(typename DerivedHandlerTypeTraits::ParticleType&,ParticleBank&)>
  d_collision_method;

  // Typedef for cell id neutron material map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			       Teuchos::RCP<const typename DerivedHandlerTypeTraits::MaterialType> >
  CellIdMaterialMap;

  // The cell id neutron material map
  CellIdMaterialMap d_cell_id_material_map;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardParticleCollisionHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleCollisionHandler.hpp
//---------------------------------------------------------------------------//
