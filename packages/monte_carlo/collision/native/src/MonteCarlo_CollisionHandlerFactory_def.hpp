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
void CollisionHandlerFactory::createMaterialNameDataMapsUsingDagMC(
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                            Teuchos::Array<double> >& material_id_fraction_map,
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
		      Teuchos::Array<std::string> >& material_id_component_map,
   const boost::unordered_map<std::string,Teuchos::RCP<ScatteringCenterType> >&
   scattering_center_map,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_mat_id_map,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_density_map,
   boost::unordered_map<std::string,Teuchos::RCP<MaterialType> >&
   material_name_pointer_map,
   boost::unordered_map<std::string,
                  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
   material_name_cell_ids_map )
{
  // Make sure the cell data maps have the same size
  testPrecondition( cell_id_mat_id_map.size() == cell_id_density_map.size() );
  
  // Load the nuclide name data maps
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                       std::vector<std::string> >::const_iterator 
    cell_id_mat_id_it = cell_id_mat_id_map.begin();

  while( cell_id_mat_id_it != cell_id_mat_id_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_id_mat_id_it->second.size() > 1,
			InvalidMaterialRepresentation,
			"Error: " << cell_id_mat_id_it->second.size() << 
			" materials set to cell "
			<< cell_id_mat_id_it->first << "!" );
    TEST_FOR_EXCEPTION( cell_id_density_map.find( cell_id_mat_id_it->first )->second.size() > 1,
			InvalidMaterialRepresentation,
			"Error: " << cell_id_mat_id_it->second.size() << 
			" densities set to cell "
			<< cell_id_mat_id_it->first << "!" );
    
    Teuchos::RCP<std::istringstream> 
      iss( new std::istringstream( cell_id_mat_id_it->second[0] ) );

    ModuleTraits::InternalMaterialHandle material_id;

    *iss >> material_id;

    Geometry::ModuleTraits::InternalCellHandle cell_id = 
      cell_id_mat_id_it->first;

    std::string density_string = 
      cell_id_density_map.find( cell_id_mat_id_it->first )->second[0];

    iss.reset( new std::istringstream( density_string ) );

    double density;

    *iss >> density;

    std::string material_name( cell_id_mat_id_it->second[0] );
    material_name += "_";
    material_name += density_string;

    if( material_name_pointer_map.find( material_name ) == 
	material_name_pointer_map.end() )
    {
      Teuchos::RCP<NeutronMaterial>& new_material= 
	material_name_pointer_map[material_name];

      new_material.reset( new MaterialType( 
		     material_id,
		     density,
		     scattering_center_map,
		     material_id_fraction_map.find( material_id)->second,
		     material_id_component_map.find( material_id )->second ) );
    }

    material_name_cell_ids_map[material_name].push_back( cell_id );

    ++cell_id_mat_id_it;
  }
}

// Register materials with cells
template<typename MaterialType>
void CollisionHandlerFactory::registerMaterials(
   const boost::unordered_map<std::string,Teuchos::RCP<MaterialType> >&
   material_name_pointer_map,
   const boost::unordered_map<std::string,
                  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
   material_name_cell_ids_map )
{
  boost::unordered_map<std::string,Teuchos::RCP<MaterialType> >::const_iterator
    material_name_pointer_it = material_name_pointer_map.begin();
  
  while( material_name_pointer_it != material_name_pointer_map.end() )
  {
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
      cells_containing_material = material_name_cell_ids_map.find( 
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
