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
#include "FRENSIE_root_config.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_Root.hpp"
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Validate the material ids
/*! \details If ROOT has not been enabled this function will be empty. 
 */
void StandardCollisionHandlerFactory<Geometry::Root>::validateMaterialIds(
			    const Teuchos::ParameterList& material_reps ) const
{
  #ifdef HAVE_FRENSIE_ROOT
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
  
  int material_counter = 0;
  TGeoMaterial* mat = Geometry::Root::getManager()->GetMaterial(material_counter);
  
  while ( mat != NULL )
  {
    // TODO: Obtain the material number from ROOT and -> InternalMaterialHandle
    std::string requested_material_id_name = mat->GetName();
    
    
    // TODO: test how to efficiently extract the number from the "mat_#"
    std::istringstream iss( requested_material_id_name );
    
    ModuleTraits::InternalMaterialHandle material_id;
    
    iss >> material_id;
    
    TEST_FOR_EXCEPTION( material_ids.find( material_id ) ==
			material_ids.end(),
			InvalidMaterialRepresentation,
			"Error: ROOT has requested material number "
			<< material_id << " which is lacking "
			"a definition!" );
				
		material_counter += 1;
		mat = Geometry::Root::getManager()->GetMaterial( material_counter );
  } 
  #endif // end HAVE_FRENSIE_ROOT
}

// Create the cell id data maps
/*! If ROOT has not been enabled this function will be empty
 */
void StandardCollisionHandlerFactory<Geometry::Root>::createCellIdDataMaps(
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
	  std::vector<std::string> >& cell_id_mat_id_map,
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
	  std::vector<std::string> >& cell_id_density_map ) const
{
#ifdef HAVE_FRENSIE_ROOT
  // Get the cell property values (material and density)
  TObjArray* cells = Geometry::Root::getManager()->GetListOfVolumes();
  int number_cells = cells->GetEntries();
  
  for ( Geometry::ModuleTraits::InternalCellHandle i=0; i < number_cells; i++ )
  {
    // Obtain the material and density data from ROOT
    TGeoVolume* cell  = Geometry::Root::getManager()->GetVolume( i + 1 );
    TGeoMaterial* mat = cell->GetMaterial();
    std::string mat_id  = mat->GetName();
    
    std::vector<std::string> material_names;
    material_names.push_back( mat_id.substr(0,3) );
    material_names.push_back( mat_id.substr(4) );
    
    double density =  mat->GetDensity();
    
    std::vector<std::string> density_names;
    density_names.push_back( "rho" );
    density_names.push_back( "-" + std::to_string( density ) );
    
    // Update the unordered maps
    cell_id_mat_id_map[i + 1] = material_names;
    cell_id_density_map[i + 1] = density_names;
  }

  // Make sure that the maps have the same size
  TEST_FOR_EXCEPTION( cell_id_mat_id_map.size() != cell_id_density_map.size(),
		      InvalidMaterialRepresentation,
		      "Error: ROOT must specify densities with material "
		      "ids." );
  #endif // end HAVE_FRENSIE_ROOT
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
