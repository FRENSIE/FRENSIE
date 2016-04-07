//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionHandlerFactory.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Standard collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardCollisionHandlerFactory_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

#ifdef HAVE_FRENSIE_ROOT

namespace MonteCarlo{

// Validate the material ids
void StandardCollisionHandlerFactory<Geometry::Root>::validateMaterialIds(
                                           const MatIdSet& material_ids ) const
{
  // Get the material ids requested by Root
  MatIdSet root_material_ids;

  try{
    Geometry::Root::getMaterialIds( root_material_ids );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidRootGeometry,
                              InvalidMaterialRepresentation,
                              "Error: Unable to parse the material ids in "
                              "Root!" );

  MatIdSet::const_iterator root_mat_id_it = root_material_ids.begin();

  // Check that the material ids requested by Root are valid
  while( root_mat_id_it != root_material_ids.end() )
  {
    TEST_FOR_EXCEPTION( material_ids.find( *root_mat_id_it ) ==
			material_ids.end(),
			InvalidMaterialRepresentation,
			"Error: Root has requested material number "
			<< *root_mat_id_it << " which is lacking "
			"a definition!" );
    
    ++root_mat_id_it;
  }

  MatIdSet::const_iterator mat_id_it = material_ids.begin();

  // Check that every material id has a definition in Root
  while( mat_id_it != material_ids.end() )
  {
    if( root_material_ids.find( *mat_id_it ) == root_material_ids.end() )
    {
      this->getOsWarn() << "Warning: Root does not request material number "
                        << *mat_id_it << ". It will be ignored."
                        << std::endl;
    }
    
    ++mat_id_it;
  }
}

// Create the cell id data maps
void StandardCollisionHandlerFactory<Geometry::Root>::createCellIdDataMaps(
                                  CellIdMatIdMap& cell_id_mat_id_map,
                                  CellIdDensityMap& cell_id_density_map ) const
{
  try{
    Geometry::Root::getCellMaterialIds( cell_id_mat_id_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidRootGeometry,
                              InvalidMaterialRepresentation,
                              "Error: could not parse the material ids "
                              "associated with cells in Root!" );  

  try{
    Geometry::Root::getCellDensities( cell_id_density_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidRootGeometry,
                              InvalidMaterialRepresentation,
                              "Error: could not parse the cell densities in"
                              "Root!" );  

  CellIdMatIdMap::const_iterator cell_id_mat_id_it = 
    cell_id_mat_id_map.begin();
    
  // Make sure that the maps have the same size
  while( cell_id_mat_id_it != cell_id_mat_id_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_id_density_map.find( cell_id_mat_id_it->first ) ==
                        cell_id_density_map.end(),
                        InvalidMaterialRepresentation,
                        "Error: Cell " << cell_id_mat_id_it->first << 
                        " has a material id assigned in Root but not a "
                        "density!" );

    ++cell_id_mat_id_it;
  }
  
  CellIdDensityMap::const_iterator cell_id_density_it = 
    cell_id_density_map.begin();

  while( cell_id_density_it != cell_id_density_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_id_mat_id_map.find( cell_id_density_it->first ) ==
                        cell_id_mat_id_map.end(),
                        InvalidMaterialRepresentation,
                        "Error: Cell " << cell_id_density_it->first <<
                        " has a density assigned in Root but not a "
                        "material!" );

    ++cell_id_density_it;
  }
}

} // end MonteCarlo namespace

#endif // end HAVE_FRENSIE_ROOT

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
