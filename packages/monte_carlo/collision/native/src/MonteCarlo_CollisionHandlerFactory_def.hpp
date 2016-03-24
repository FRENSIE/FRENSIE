//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandlerFactory_def.hpp
//! \author Alex Robinson
//! \brief  Collision handler factory class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_HANDLER_FACTORY_DEF_HPP
#define MONTE_CARLO_COLLISION_HANDLER_FACTORY_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the material name data maps
template<typename ScatteringCenterType, typename MaterialType>
void CollisionHandlerFactory::createMaterialNameDataMaps(
   const MatIdFractionMap& material_id_fraction_map,
   const MatIdComponentMap& material_id_component_map,
   const std::unordered_map<std::string,Teuchos::RCP<ScatteringCenterType> >&
   scattering_center_map,
   const CellIdMatIdMap& cell_id_mat_id_map,
   const CellIdDensityMap& cell_id_density_map,
   std::unordered_map<std::string,Teuchos::RCP<MaterialType> >& 
   material_name_pointer_map,
   MatNameCellIdsMap& material_name_cell_ids_map )
{
  // Make sure the cell data maps have the same size
  testPrecondition( cell_id_mat_id_map.size() == cell_id_density_map.size() );
  
  // Load the nuclide name data maps
  CellIdMatIdMap::const_iterator 
    cell_id_mat_id_it = cell_id_mat_id_map.begin();

  while( cell_id_mat_id_it != cell_id_mat_id_map.end() )
  {
    Geometry::ModuleTraits::InternalCellHandle cell_id = 
      cell_id_mat_id_it->first;
    
    ModuleTraits::InternalMaterialHandle material_id = 
      cell_id_mat_id_it->second;

    double density = cell_id_density_map.find( cell_id )->second;
    
    std::ostringstream oss;
    oss << "mat_" << material_id << "_";
    oss << cell_id_density_map.find( cell_id )->second;
    
    std::string material_name( oss.str() );

    if( material_name_pointer_map.find( material_name ) == 
	material_name_pointer_map.end() )
    {
      Teuchos::RCP<MaterialType>& new_material= 
	material_name_pointer_map[material_name];

      new_material.reset( new MaterialType( 
		     material_id,
		     density,
		     scattering_center_map,
		     material_id_fraction_map.find( material_id )->second,
		     material_id_component_map.find( material_id )->second ) );
    }

    material_name_cell_ids_map[material_name].push_back( cell_id );

    ++cell_id_mat_id_it;
  }
}

// Register materials with cells
template<typename MaterialType>
void CollisionHandlerFactory::registerMaterials(
   const std::unordered_map<std::string,Teuchos::RCP<MaterialType> >&
   material_name_pointer_map,
   const MatNameCellIdsMap& material_name_cell_ids_map )
{
  typename std::unordered_map<std::string,
                              Teuchos::RCP<MaterialType> >::const_iterator
    material_name_pointer_it = material_name_pointer_map.begin();
  
  while( material_name_pointer_it != material_name_pointer_map.end() )
  {
    const MatNameCellIdsMap::mapped_type& cells_containing_material = 
      material_name_cell_ids_map.find( 
                                     material_name_pointer_it->first )->second;
    
    CollisionHandler::addMaterial( material_name_pointer_it->second,
                                   cells_containing_material );

    ++material_name_pointer_it;
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_HANDLER_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory_def.hpp
//---------------------------------------------------------------------------//
