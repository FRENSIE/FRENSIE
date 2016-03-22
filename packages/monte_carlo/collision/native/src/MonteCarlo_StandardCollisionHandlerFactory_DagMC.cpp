//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionHandlerFactory_DagMC.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Standard collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "FRENSIE_dagmc_config.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Validate the material ids
/*! \details If DagMC has not been enabled this function will be empty. 
 */
void StandardCollisionHandlerFactory<moab::DagMC>::validateMaterialIds(
			    const Teuchos::ParameterList& material_reps ) const
{
  #ifdef HAVE_FRENSIE_DAGMC
  // Construct the set of material ids
  boost::unordered_set<ModuleTraits::InternalMaterialHandle> material_ids;

  Teuchos::ParameterList::ConstIterator it = material_reps.begin();

  while( it != material_reps.end() )
  {
    const Teuchos::ParameterList& material_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    material_ids.insert( material_rep.get<unsigned int>( "Id" ) );
    
    ++it;
  }

  // Get the material ids requested by DagMC
  std::vector<std::string> requested_material_ids;
  
  Geometry::getPropertyValues( 
			  Geometry::DagMCProperties::getMaterialPropertyName(),
			  requested_material_ids );

  // Check that the material ids requested by DagMC are valid
  for( unsigned i = 0; i < requested_material_ids.size(); ++i )
  {
    std::istringstream iss( requested_material_ids[i] );
    
    ModuleTraits::InternalMaterialHandle material_id;
    
    iss >> material_id;
    
    TEST_FOR_EXCEPTION( material_ids.find( material_id ) ==
			material_ids.end(),
			InvalidMaterialRepresentation,
			"Error: DagMC has requested material number "
			<< requested_material_ids[i] << " which is lacking "
			"a definition!" );
  } 
  #endif // end HAVE_FRENSIE_DAGMC
}

// Create the cell id data maps using DagMC
/*! \details If DagMC has not been enabled this function will be empty
 */
void StandardCollisionHandlerFactory<moab::DagMC>::createCellIdDataMaps(
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                               std::vector<std::string> >& cell_id_mat_id_map,
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_density_map ) const
{
  #ifdef HAVE_FRENSIE_DAGMC
  // Get the cell material property values
  Geometry::getCellPropertyValues( 
			  Geometry::DagMCProperties::getMaterialPropertyName(),
			  cell_id_mat_id_map );

  // Get the cell density property values
  Geometry::getCellPropertyValues(
			   Geometry::DagMCProperties::getDensityPropertyName(),
			   cell_id_density_map );

  // Make sure that the maps have the same size
  TEST_FOR_EXCEPTION( cell_id_mat_id_map.size() != cell_id_density_map.size(),
		      InvalidMaterialRepresentation,
		      "Error: DagMC must specify densities with material "
		      "ids." );
  #endif // end HAVE_FRENSIE_DAGMC
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionHandlerFactory_DagMC.cpp
//---------------------------------------------------------------------------//
