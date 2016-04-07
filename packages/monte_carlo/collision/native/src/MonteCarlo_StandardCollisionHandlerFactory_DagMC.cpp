//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionHandlerFactory_DagMC.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Standard collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

#ifdef HAVE_FRENSIE_DAGMC

namespace MonteCarlo{

// Validate the material ids
void StandardCollisionHandlerFactory<Geometry::DagMC>::validateMaterialIds(
                                           const MatIdSet& material_ids ) const
{
  // Get the material ids requested by DagMC
  MatIdSet dagmc_material_ids;
  
  try{
    Geometry::DagMC::getMaterialIds( dagmc_material_ids );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidDagMCGeometry,
                              InvalidMaterialRepresentation,
                              "Error: Unable to parse the material ids in "
                              "DagMC!" );

  MatIdSet::const_iterator dagmc_mat_id_it = dagmc_material_ids.begin();

  // Check that the material ids requested by DagMC are valid
  while( dagmc_mat_id_it != dagmc_material_ids.end() )
  {
    TEST_FOR_EXCEPTION( material_ids.find( *dagmc_mat_id_it ) ==
			material_ids.end(),
			InvalidMaterialRepresentation,
			"Error: DagMC has requested material number "
			<< *dagmc_mat_id_it << " which is lacking "
			"a definition!" );

    ++dagmc_mat_id_it;
  } 

  MatIdSet::const_iterator mat_id_it = material_ids.begin();

  // Check that every material id has a definition in DagMC
  while( mat_id_it != material_ids.end() )
  {
    if( dagmc_material_ids.find( *mat_id_it ) == dagmc_material_ids.end() )
    {
      this->getOsWarn() << "Warning: DagMC does not request material number "
                        << *mat_id_it << ". It will be ignored."
                        << std::endl;
    }
    
    ++mat_id_it;
  }
}

// Create the cell id data maps using DagMC
void StandardCollisionHandlerFactory<Geometry::DagMC>::createCellIdDataMaps(
                                  CellIdMatIdMap& cell_id_mat_id_map,
                                  CellIdDensityMap& cell_id_density_map ) const
{
  try{
    Geometry::DagMC::getCellMaterialIds( cell_id_mat_id_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidDagMCGeometry,
                              InvalidMaterialRepresentation,
                              "Error: Unable to parse the material ids "
                              " associated with cells in DagMC!" );
  
  try{
    Geometry::DagMC::getCellDensities( cell_id_density_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidDagMCGeometry,
                              InvalidMaterialRepresentation,
                              "Error: Unable to parse the cell densities in "
                              "DagMC!" );

  CellIdMatIdMap::const_iterator cell_id_mat_id_it = 
    cell_id_mat_id_map.begin();

  // Make sure that the maps have the same size
  while( cell_id_mat_id_it != cell_id_mat_id_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_id_density_map.find( cell_id_mat_id_it->first ) ==
                        cell_id_density_map.end(),
                        InvalidMaterialRepresentation,
                        "Error: Cell " << cell_id_mat_id_it->first << 
                        " has a material id assigned in DagMC but not a "
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
                        " has a density assigned in DagMC but not a "
                        "material!" );

    ++cell_id_density_it;
  }
}

} // end MonteCarlo namespace

#endif // end HAVE_FRENSIE_DAGMC

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionHandlerFactory_DagMC.cpp
//---------------------------------------------------------------------------//
