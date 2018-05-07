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
template<typename Material>
StandardParticleCollisionHandler<Material>::StandardParticleCollisionHandler(
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
template<typename Material>
void StandardParticleCollisionHandler<Material>::addMaterial(
                       const std::shared_ptr<const MaterialType>& material,
                       const std::vector<Geometry::Model::InternalCellHandle>&
                       cells_containing_material )
{
  // Make sure the material pointer is valid
  testPrecondition( material.get() );
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
template<typename Material>
bool StandardParticleCollisionHandler<Material>::isCellVoid(
                         const Geometry::Model::InternalCellHandle cell ) const
{
  return d_cell_id_material_map.find( cell ) == d_cell_id_material_map.end();
}

// Get the material contained in a cell
template<typename Material>
auto StandardParticleCollisionHandler<Material>::getMaterial(
                         const Geometry::Model::InternalCellHandle cell ) const
  -> const std::shared_ptr<const MaterialType>&
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  TEST_FOR_EXCEPTION( this->isCellVoid( cell ),
                      std::runtime_error,
                      "Cell " << cell << " is void!" );
  
  return d_cell_id_material_map.find( cell )->second;
}

// Get the total macroscopic cross section of a material
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicTotalCrossSection(
                                           const ParticleType& particle ) const
{
  return this->getMacroscopicTotalCrossSection( particle.getCell(),
                                                particle.getEnergy() );
}

// Get the total macroscopic cross section of a material
template<typename Material>
inline double StandardParticleCollisionHandler<Material>::getMacroscopicTotalCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
    return this->getMaterial(cell)->getMacroscopicTotalCrossSection( energy );
}

// Get the total macroscopic cross section of a material
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicTotalCrossSectionQuick(
                                           const ParticleType& particle ) const
{
  return this->getMacroscopicTotalCrossSectionQuick( particle.getCell(),
                                                     particle.getEnergy() );
}

// Get the total macroscopic cross section of a material
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
inline double StandardParticleCollisionHandler<Material>::getMacroscopicTotalCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  return this->getMaterial( cell )->getMacroscopicTotalCrossSection( energy );
}

// Get the total forward macroscopic cross section of a material
/*! \details When a distance must be converted to an optical path length only
 * use the macroscopic cross section returned from this method.
 */
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicTotalForwardCrossSection(
                                           const ParticleType& particle ) const
{
  return this->getMacroscopicTotalForwardCrossSection( particle.getCell(),
                                                       particle.getEnergy() );
}

// Get the total forward macroscopic cross section of a material
template<typename Material>
inline double StandardParticleCollisionHandler<Material>::getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
    return this->getMaterial(cell)->getMacroscopicTotalCrossSection( energy );
}

// Get the total forward macroscopic cross section of a material
/*! \details When a distance must be converted to an optical path length only
 * use the macroscopic cross section returned from this method. Before calling 
 * this method you must first check if the cell is void. Calling this method 
 * with a void cell is not allowed.
 */
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicTotalForwardCrossSectionQuick(
                                           const ParticleType& particle ) const
{
  return this->getMacroscopicTotalForwardCrossSectionQuick( particle.getCell(),
                                                            particle.getEnergy() );
}

// Get the total forward macroscopic cross section of a material
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
inline double StandardParticleCollisionHandler<Material>::getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );
  
  return this->getMaterial( cell )->getMacroscopicTotalCrossSection( energy );
}

// Get the macroscopic reaction cross section for a specific reaction
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicReactionCrossSection(
                                        const ParticleStateType& particle,
                                        const ReactionEnumType reaction ) const
{
  return this->getMacroscopicReactionCrossSection( particle.getCell(),
                                                   particle.getEnergy(),
                                                   reaction );
}

// Get the macroscopic reaction cross section for a specific reaction
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicReactionCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy,
                                const ReactionEnumType reaction ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
  {
    return this->getMaterial( cell )->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
  }
}

// Get the macroscopic reaction cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicReactionCrossSectionQuick(
                                        const ParticleStateType& particle,
                                        const ReactionEnumType reaction ) const
{
  return this->getMacroscopicReactionCrossSectionQuick( particle.getCell(),
                                                        particle.getEnergy(),
                                                        reaction );
}

// Get the macroscopic reaction cross section for a specific reaction
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardParticleCollisionHandler<Material>::getMacroscopicReactionCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy,
                                const ReactionEnumType reaction ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );
  
  return this->getMaterial( cell )->getMacroscopicReactionCrossSection(
                                                            energy, reaction );
}

// Collide with the material in a cell
template<typename Material>
void StandardParticleCollisionHandler<Material>::collideWithCellMaterial(
                                                     ParticleType& particle,
                                                     ParticleBank& bank ) const
{
  d_collision_method( particle, bank );
}

// Collide with the material in a cell (analogue)
template<typename Material>
void StandardParticleCollisionHandler<Material>::collideWithCellMaterialAnalogue(
                                                     ParticleType& particle,
                                                     ParticleBank& bank ) const
{
  // Make sure the cell is not void
  testPrecondition( !this->isCellVoid( particle.getCell() ) );

  this->getMaterial(particle.getCell())->collideAnalogue( particle, bank );
}

// Collide with the material in a cell (survival bias)
template<typename Material>
void StandardParticleCollisionHandler<Material>::collideWithCellMaterialSurvivalBias(
                                                     ParticleType& particle,
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
