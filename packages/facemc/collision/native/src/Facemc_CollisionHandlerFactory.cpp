//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CollisionHandlerFactory.cpp
//! \author Alex Robinson
//! \brief  Collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "Facemc_CollisionHandlerFactory.hpp"
#include "Facemc_NuclideFactory.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the collision handler using DagMC
void CollisionHandlerFactory::initializeHandlerUsingDagMC( 
		       const Teuchos::ParameterList& material_reps,
		       const Teuchos::ParameterList& cross_sections_table_info,
		       const std::string& cross_sections_xml_directory )
{
  // Validate the materials
  Teuchos::ParameterList::ConstIterator it = material_reps.begin();

  boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle> 
    material_ids;
  
  while( it != material_reps.end() )
  {
    const Teuchos::ParameterList& material_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    CollisionHandlerFactory::validateMaterialRep( material_rep,
						  material_ids );

    ++it;
  }
  
  material_ids.clear();

  // Validate the material ids
  CollisionHandlerFactory::validateMaterialIdsUsingDagMC( material_reps );
  
  // Create the set of all nuclides needed to construct materials
  boost::unordered_set<std::string> nuclide_names;

  CollisionHandlerFactory::createNuclideSet( material_reps, 
					     nuclide_names );

  // Load the nuclides of interest
  NuclideFactory nuclide_factory( cross_sections_xml_directory,
				  cross_sections_table_info,
				  nuclide_names );

  boost::unordered_map<std::string,Teuchos::RCP<Nuclide> > nuclide_map;

  nuclide_factory.createNuclideMap( nuclide_map );

  // Create the material id data maps
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<double> > material_id_fraction_map;
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<std::string> > material_id_nuclide_map;
  
  CollisionHandlerFactory::createMaterialIdDataMaps( material_reps,
						     material_id_fraction_map,
						     material_id_nuclide_map );

  // Create the material name data maps
  boost::unordered_map<std::string,Teuchos::RCP<NeutronMaterial> >
    material_name_pointer_map;
  
  boost::unordered_map<std::string,
                   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >
    material_name_cell_ids_map;

  CollisionHandlerFactory::createMaterialNameDataMapsUsingDagMC( 
						  material_id_fraction_map,
						  material_id_nuclide_map,
						  nuclide_map,
						  material_name_pointer_map,
						  material_name_cell_ids_map );

  // Initialize the Collision Handler
  boost::unordered_map<std::string,
                       Teuchos::RCP<NeutronMaterial> >::const_iterator
    material_name_pointer_it = material_name_pointer_map.begin();
  
  while( material_name_pointer_it != material_name_pointer_map.end() )
  {
    const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
      cells_containing_material = material_name_cell_ids_map.find( 
				     material_name_pointer_it->first )->second;
    
    CollisionHandler::addMaterial( material_name_pointer_it->second,
				   cells_containing_material );
  }
}

// Validate a material representation
void CollisionHandlerFactory::validateMaterialRep( 
	      const Teuchos::ParameterList& material_rep,
	      boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>&
	      material_ids )
{
  // Make sure the id is present
  TEST_FOR_EXCEPTION( !material_rep.isParameter( "Id" ),
		      InvalidMaterialRepresentation,
		      "Error: a material must have an id specified!" );

  // Make sure the id is unique
  TEST_FOR_EXCEPTION( material_ids.find( material_rep.get<unsigned>( "Id" ) )!=
		      material_ids.end(),
		      InvalidMaterialRepresentation,
		      "Error: a materials id must be unique (material id "
		      << material_rep.get<unsigned>( "Id" ) <<
		      " appears more than once)!" );

  material_ids.insert( material_rep.get<unsigned>( "Id" ) );

  // Make sure the isotopes that make up the material are specified
  TEST_FOR_EXCEPTION( !material_rep.isParameter( "Isotopes" ),
		      InvalidMaterialRepresentation,
		      "Error: a material must have isotopes specified!" );

  // Make sure the isotope fractions are specified
  TEST_FOR_EXCEPTION( !material_rep.isParameter( "Fractions" ),
		      InvalidMaterialRepresentation,
		      "Error: a material must have isotope fractions "
		      "specified!" );
}

// Validate the material ids using DagMC
void CollisionHandlerFactory::validateMaterialIdsUsingDagMC(
				  const Teuchos::ParameterList& material_reps )
{
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
}

// Create the set of all nuclides needed to construct materials
void CollisionHandlerFactory::createNuclideSet( 
			          const Teuchos::ParameterList& material_reps,
				  boost::unordered_set<std::string>& nuclides )
{
  Teuchos::ParameterList::ConstIterator it = material_reps.begin();

  while( it != material_reps.end() )
  {
    const Teuchos::ParameterList& material_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    const Teuchos::Array<std::string>& material_isotopes = 
      material_rep.get<Teuchos::Array<std::string> >( "Isotopes" );

    for( unsigned i = 0; i < material_isotopes.size(); ++i )
      nuclides.insert( material_isotopes[i] );
    
    ++it;
  }
}

// Create the material id data maps
void CollisionHandlerFactory::createMaterialIdDataMaps(
     const Teuchos::ParameterList& material_reps,
     boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                          Teuchos::Array<double> >& material_id_fraction_map,
     boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<std::string> >& material_id_nuclide_map )
{
  Teuchos::ParameterList::ConstIterator it = material_reps.begin();

  while( it != material_reps.end() )
  {
    const Teuchos::ParameterList& material_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );
    
    const Teuchos::Array<double>& material_fractions = 
      material_rep.get<Teuchos::Array<double> >( "Fractions" );

    const Teuchos::Array<std::string>& material_isotopes = 
      material_rep.get<Teuchos::Array<std::string> >( "Isotopes" );

    TEST_FOR_EXCEPTION( material_fractions.size() != material_isotopes.size(),
			InvalidMaterialRepresentation,
			"Error: The number of fractions does not "
			"equal the number of isotopes in material "
			<< material_rep.name() << "!" );

    material_id_fraction_map[material_rep.get<unsigned>( "Id" )] = 
      material_fractions;

    material_id_nuclide_map[material_rep.get<unsigned>( "Id" )] = 
      material_isotopes;
    
    ++it;
  }
}

// Create the material name data maps
void CollisionHandlerFactory::createMaterialNameDataMapsUsingDagMC(
     const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                            Teuchos::Array<double> >& material_id_fraction_map,
     const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                        Teuchos::Array<std::string> >& material_id_nuclide_map,
     const boost::unordered_map<std::string,Teuchos::RCP<Nuclide> >& 
     nuclide_map,
     boost::unordered_map<std::string,Teuchos::RCP<NeutronMaterial> >&
     material_name_pointer_map,
     boost::unordered_map<std::string,
                  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
     material_name_cell_ids_map )
{
  // Get the cell material property values
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                       std::vector<std::string> > cell_id_mat_id_map;

  Geometry::getCellPropertyValues( 
			  Geometry::DagMCProperties::getMaterialPropertyName(),
			  cell_id_mat_id_map );

  // Get the cell density property values
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                       std::vector<std::string> > cell_id_density_map;
  
  Geometry::getCellPropertyValues(
			   Geometry::DagMCProperties::getDensityPropertyName(),
			   cell_id_density_map );

  // Make sure that the maps have the same size
  TEST_FOR_EXCEPTION( cell_id_mat_id_map.size() != cell_id_density_map.size(),
		      InvalidMaterialRepresentation,
		      "Error: DagMC must specify densities with material "
		      "ids." );

  // Load the nuclide name data maps
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                       std::vector<std::string> >::const_iterator 
    cell_id_mat_id_it = cell_id_mat_id_map.begin();

  while( cell_id_mat_id_it != cell_id_mat_id_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_id_mat_id_it->second.size() > 1,
			InvalidMaterialRepresentation,
			"Error: DagMC set " 
			<< cell_id_mat_id_it->second.size() << " material "
			"ids to cell "
			<< cell_id_mat_id_it->first << "!" );
    TEST_FOR_EXCEPTION( cell_id_density_map.find( cell_id_mat_id_it->first )->second.size() > 1,
			InvalidMaterialRepresentation,
			"Error: DagMC set " 
			<< cell_id_mat_id_it->second.size() << " densities "
			"to cell "
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

      new_material.reset( new NeutronMaterial( 
		       material_id,
		       density,
		       nuclide_map,
		       material_id_fraction_map.find( material_id)->second,
		       material_id_nuclide_map.find( material_id )->second ) );
    }

    material_name_cell_ids_map[material_name].push_back( cell_id );

    ++cell_id_mat_id_it;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_CollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
