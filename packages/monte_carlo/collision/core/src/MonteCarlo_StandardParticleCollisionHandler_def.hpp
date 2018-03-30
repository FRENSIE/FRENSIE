//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleCollisionHandler_def.hpp
//! \author Alex Robinson
//! \brief  The standard particle collision handler class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_DEF_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_DEF_HPP

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename DerivedHandlerTypeTraits>
StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::StandardParticleCollisionHandler(
                                               const bool analogue_collisions )
  : d_collision_method(),
    d_cell_id_material_map()
{
  // Assign the collision method
  if( analogue_collisions )
  {
    d_collision_method = std::bind<void>(
                                    &ThisType::collideWithCellMaterialAnalogue,
                                    std::cref( *this ),
                                    std::placeholders::_1,
                                    std::placeholders::_2 );
  }
  else
  {
    d_collision_method = std::bind<void>(
                                &ThisType::collideWithCellMaterialSurvivalBias,
                                std::cref( *this ),
                                std::placeholders::_1,
                                std::placeholders::_2 );
  }
}

// Add a material to the collision handler
template<typename DerivedHandlerTypeTraits>
void StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::addMaterial(
     const std::shared_ptr<const typename DerivedHandlerTypeTraits::MaterialType>&
     material,
     const std::vector<Geometry::ModuleTraits::InternalCellHandle>&
     cells_containing_material )
{
  // Make sure the material pointer is valid
  testPrecondition( !material.is_null() );
  // Make sure the cells are valid
  testPrecondition( cells_containing_material.size() > 0 );

  for( size_t i = 0; i < cells_containing_material.size(); ++i )
  {
    TEST_FOR_EXCEPTION(
                 d_cell_id_material_map.find( cells_containing_material[i] ) !=
                 d_cell_id_material_map.end(),
                 std::logic_error,
                 "cell " << cells_containing_material[i] <<
                 " already has a material assigned!" );

    d_cell_id_material_map[cells_containing_material[i]] = material;
  }
}

// Check if a cell is void
template<typename DerivedHandlerTypeTraits>
bool StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::isCellVoid(
                  const Geometry::ModuleTraits::InternalCellHandle cell ) const
{
  return d_cell_id_material_map.find( cell ) == d_cell_id_material_map.end();
}

// Get the material contained in a cell
template<typename DerivedHandlerTypeTraits>
const std::shared_ptr<const typename DerivedHandlerTypeTraits::MaterialType>&
StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::getMaterial(
                  const Geometry::ModuleTraits::InternalCellHandle cell ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  return d_cell_id_material_map.find( cell )->second;
}

// Get the total macroscopic cross section of a material
template<typename DerivedHandlerTypeTraits>
double StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::getMacroscopicTotalCrossSection(
        const typename DerivedHandlerTypeTraits::ParticleType& particle ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  return this->getMaterial(particle.getCell())->getMacroscopicTotalCrossSection(
                                                        particle.getEnergy() );
}

// Get the total forward macroscopic cross section of a material
/*! \details When a distance must be converted to an optical path length only
 * use the macroscopic cross section returned from this method.
 */
template<typename DerivedHandlerTypeTraits>
double StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::getMacroscopicTotalForwardCrossSection(
        const typename DerivedHandlerTypeTraits::ParticleType& particle ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  return this->getMaterial(particle.getCell())->getMacroscopicTotalCrossSection(
                                                        particle.getEnergy() );
}

// Collide with the material in a cell
template<typename DerivedHandlerTypeTraits>
void StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::collideWithCellMaterial(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  d_collision_method( particle, bank );
}

// Collide with the material in a cell (analogue)
template<typename DerivedHandlerTypeTraits>
void StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::collideWithCellMaterialAnalogue(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  this->getMaterial(particle.getCell())->collideAnalogue( particle, bank );
}

// Collide with the material in a cell (survival bias)
template<typename DerivedHandlerTypeTraits>
void StandardParticleCollisionHandler<DerivedHandlerTypeTraits>::collideWithCellMaterialSurvivalBias(
                     typename DerivedHandlerTypeTraits::ParticleType& particle,
                     ParticleBank& bank ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  this->getMaterial(particle.getCell())->collideSurvivalBias( particle, bank );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_DEF_HPP


//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleCollisionHandler_def.hpp
//---------------------------------------------------------------------------//
