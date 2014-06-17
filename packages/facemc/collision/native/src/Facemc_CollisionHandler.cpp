//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Collision handler class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Facemc_CollisionHandler.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Add a material to the collision handler
void CollisionHandler::addMaterial(
	      const Teuchos::RCP<NeutronMaterial>& material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material )
{
  for( unsigned i = 0u; i < cells_containing_material.size(); ++i )
  {
    TEST_FOR_EXCEPTION( 
      CollisionHandler::master_neutron_map.find(cells_containing_material[i])!=
				    CollisionHandler::master_neutron_map.end(),
      std::logic_error,
      "Error: cell " << cells_containing_material[i] << " already has a "
      "material assigned!" );
    
    CollisionHandler::master_neutron_map[cells_containing_material[i]] =
      material;
  }
}

// Check if a cell is void
bool CollisionHandler::isCellVoid(
			const Geometry::ModuleTraits::InternalCellHandle cell )
{
  if( CollisionHandler::master_neutron_map.find( cell ) == 
      CollisionHandler::master_neutron_map.end() )
    return true;
  else
    return false;
}

// Get the material contained in a cell
const Teuchos::RCP<NeutronMaterial>&
CollisionHandler::getCellMaterial( 
			const Geometry::ModuleTraits::InternalCellHandle cell )
{
  // Make sure the cell is not void
  testPrecondition( !CollisionHandler::isCellVoid( cell ) );

  return CollisionHandler::master_neutron_map.find( cell )->second;
}

// Get the total macroscopic cross section of a material
double CollisionHandler::getMacroscopicTotalCrossSection(
						const ParticleState& particle )
{
  // Make sure the cell is not void
  testPrecondition( !CollisionHandler::isCellVoid( particle.getCell() ) );
  // Make sure the particle is a neutron
  testPrecondition( particle.getParticleType() == NEUTRON );

  Teuchos::RCP<NeutronMaterial>& material = 
    CollisionHandler::master_neutron_map.find( particle.getCell() )->second;

  return material->getMacroscopicTotalCrossSection( particle.getEnergy() );
}

// Collide with the material in a cell
void CollisionHandler::collideWithCellMaterial( ParticleState& particle,
						ParticleBank& bank,
						const bool analogue )
{
  // Make sure the cell is not void
  testPrecondition( !CollisionHandler::isCellVoid( particle.getCell() ) );
  // Make sure the particle is a neutron
  testPrecondition( particle.getParticleType() == NEUTRON );
  
  const Teuchos::RCP<NeutronMaterial>& material = 
    CollisionHandler::master_neutron_map.find( particle.getCell() )->second;

  if( analogue )
    material->collideAnalogue( dynamic_cast<NeutronState&>( particle ), bank );
  else
  {
    material->collideSurvivalBias( dynamic_cast<NeutronState&>( particle ),
				   bank );
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_CollisionHandler.cpp
//---------------------------------------------------------------------------//
