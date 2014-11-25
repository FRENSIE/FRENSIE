//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Collision handler class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_CollisionHandler.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the static member data
CollisionHandler::CellIdNeutronMaterialMap 
CollisionHandler::master_neutron_map;

CollisionHandler::CellIdPhotonMaterialMap
CollisionHandler::master_photon_map;

// Add a material to the collision handler
void CollisionHandler::addMaterial(
	      const Teuchos::RCP<NeutronMaterial>& material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material )
{
  // Make sure the material pointer is valid
  testPrecondition( !material.is_null() );
  // Make sure the cells are valid
  testPrecondition( cells_containing_material.size() > 0 );
  
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

// Add a material to the collision handler
void CollisionHandler::addMaterial(
	      const Teuchos::RCP<PhotonMaterial>& material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material )
{
  // Make sure the material pointer is valid
  testPrecondition( !material.is_null() );
  // Make sure the cells are valid
  testPrecondition( cells_containing_material.size() > 0 );
  
  for( unsigned i = 0u; i < cells_containing_material.size(); ++i )
  {
    TEST_FOR_EXCEPTION(
      CollisionHandler::master_photon_map.find(cells_containing_material[i]) !=
      CollisionHandler::master_photon_map.end(),
      std::logic_error,
      "Error:: cell " << cells_containing_material[i] << " already has a "
      "material assigned!" );
    
    CollisionHandler::master_photon_map[cells_containing_material[i]] = 
      material;
  }
}

// Add a material to the collision handler
void CollisionHandler::addMaterial(
	      const Teuchos::RCP<NeutronMaterial>& neutron_material,
	      const Teuchos::RCP<PhotonMaterial>& photon_material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material )
{
  // Make sure the material pointers are valid
  testPrecondition( !neutron_material.is_null() );
  testPrecondition( !photon_material.is_null() );
  // Make sure the cells are valid
  testPrecondition( cells_containing_material.size() > 0 );
  
  CollisionHandler::addMaterial( neutron_material, cells_containing_material );
  
  CollisionHandler::addMaterial( photon_material, cells_containing_material );
}

// Check if a cell is void
bool CollisionHandler::isCellVoid(
			 const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type )
{
  switch( particle_type )
  {
  case NEUTRON:
    if( CollisionHandler::master_neutron_map.find( cell ) == 
      CollisionHandler::master_neutron_map.end() )
      return true;
    else
      return false;
  case PHOTON:
    if( CollisionHandler::master_photon_map.find( cell ) ==
	CollisionHandler::master_photon_map.end() )
      return true;
    else
      return false;
  default:
    return true;
  }
}

// Get the neutron material contained in a cell
const Teuchos::RCP<NeutronMaterial>&
CollisionHandler::getCellNeutronMaterial( 
			const Geometry::ModuleTraits::InternalCellHandle cell )
{
  // Make sure the cell is not void
  testPrecondition( !CollisionHandler::isCellVoid( cell, NEUTRON ) );

  return CollisionHandler::master_neutron_map.find( cell )->second;
}

// Get the photon material contained in a cell
const Teuchos::RCP<PhotonMaterial>&
CollisionHandler::getCellPhotonMaterial(
			const Geometry::ModuleTraits::InternalCellHandle cell )
{
  // Make sure the cell is not void
  testPrecondition( !CollisionHandler::isCellVoid( cell, PHOTON ) );

  return CollisionHandler::master_photon_map.find( cell )->second;
}

// Get the total macroscopic cross section of a material
double CollisionHandler::getMacroscopicTotalCrossSection(
						const ParticleState& particle )
{
  // Make sure the cell is not void
  testPrecondition( !CollisionHandler::isCellVoid(particle.getCell(),
						  particle.getParticleType()));
  
  switch( particle.getParticleType() )
  {
  case NEUTRON:
  {
    Teuchos::RCP<NeutronMaterial>& material = 
      CollisionHandler::master_neutron_map.find( particle.getCell() )->second;
    
    return material->getMacroscopicTotalCrossSection( particle.getEnergy() );
  }  
  case PHOTON:
  {
    Teuchos::RCP<PhotonMaterial>& material = 
      CollisionHandler::master_photon_map.find( particle.getCell() )->second;
    
    return material->getMacroscopicTotalCrossSection( particle.getEnergy() );
  }  
  default:
    return 0.0;
  }
}

// Get the macroscopic cross section for a specific reaction
double CollisionHandler::getMacroscopicReactionCrossSection(
					   const ParticleState& particle,
					   const NuclearReactionType reaction )
{
  // Make sure the particle is a neutron
  testPrecondition( particle.getParticleType() == NEUTRON );

  CellIdNeutronMaterialMap::const_iterator it =
    CollisionHandler::master_neutron_map.find( particle.getCell() );
  
  if( it != CollisionHandler::master_neutron_map.end() )
  {
    return it->second->getMacroscopicReactionCrossSection(particle.getEnergy(),
							  reaction );
  }
  else
    return 0.0;
}

// Get the macroscopic cross section for a specific reaction
double CollisionHandler::getMacroscopicReactionCrossSection(
				      const ParticleState& particle,
				      const PhotoatomicReactionType reaction )
{
  // Make sure the particle is a photon
  testPrecondition( particle.getParticleType() == PHOTON );

  CellIdPhotonMaterialMap::const_iterator it = 
    CollisionHandler::master_photon_map.find( particle.getCell() );

  if( it != CollisionHandler::master_photon_map.end() )
  {
    return it->second->getMacroscopicReactionCrossSection(particle.getEnergy(),
							  reaction );
  }
  else
    return 0.0;
}

// Get the macroscopic cross section for a specific reaction
double CollisionHandler::getMacroscopicReactionCrossSection(
				      const ParticleState& particle,
				      const PhotonuclearReactionType reaction )
{
  // Make sure the particle is a photon
  testPrecondition( particle.getParticleType() == PHOTON );

  CellIdPhotonMaterialMap::const_iterator it = 
    CollisionHandler::master_photon_map.find( particle.getCell() );

  if( it != CollisionHandler::master_photon_map.end() )
  {
    return it->second->getMacroscopicReactionCrossSection(particle.getEnergy(),
							  reaction );
  }
  else
    return 0.0;
}

// Collide with the material in a cell
void CollisionHandler::collideWithCellMaterial( ParticleState& particle,
						ParticleBank& bank,
						const bool analogue )
{
  // Make sure the cell is not void
  testPrecondition( !CollisionHandler::isCellVoid(particle.getCell(),
						  particle.getParticleType()));
  
  switch( particle.getParticleType() )
  {
  case NEUTRON:
  {
    const Teuchos::RCP<NeutronMaterial>& material = 
      CollisionHandler::master_neutron_map.find( particle.getCell() )->second;

    if( analogue )
      material->collideAnalogue( dynamic_cast<NeutronState&>(particle), bank );
    else
    {
      material->collideSurvivalBias( dynamic_cast<NeutronState&>( particle ),
				     bank );
    }

    break; 
  }
  
  case PHOTON:
  {
    const Teuchos::RCP<PhotonMaterial>& material = 
      CollisionHandler::master_photon_map.find( particle.getCell() )->second;

    if( analogue )
      material->collideAnalogue( dynamic_cast<PhotonState&>(particle), bank );
    else
    {
      material->collideSurvivalBias( dynamic_cast<PhotonState&>(particle),
				     bank );
    }

    break;
  }
  
  default:
    THROW_EXCEPTION( std::logic_error, 
		     "Error: particle type " << particle.getParticleType() <<
		     "is not currently supported!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandler.cpp
//---------------------------------------------------------------------------//
