//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionHandlerFactory_DagMC.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "FRENSIE_dagmc_config.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"
#endif

#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the collision handler using DagMC
/*! \details Make sure the simulation properties have been set 
 * (in MonteCarlo::SimulationProperties) before running this factory
 * method. The properties will influence how this factory method behaves.
 */
void StandardCollisionHandlerFactory<moab::DagMC>::initializeHandler( 
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

    StandardCollisionHandlerFactory<moab::DagMC>::validateMaterialRep( 
                          material_rep,
						  material_ids );

    ++it;
  }
  
  material_ids.clear();

  // Validate the material ids
  StandardCollisionHandlerFactory<moab::DagMC>::validateMaterialIds( 
                                                               material_reps );
  
  // Extract the cross section table alias map
  Teuchos::ParameterList alias_map_list;
  
  try{
    alias_map_list = cross_sections_table_info.sublist( "alias map" );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception, 
			    "Error: The cross_sections.xml file in " 
			    << cross_sections_xml_directory << 
			    " is invalid - the 'alias_map' ParameterList "
			    "is not defined!" );
  
  // Create the set of all nuclides/atoms needed to construct materials
  boost::unordered_set<std::string> aliases;

  StandardCollisionHandlerFactory<moab::DagMC>::createAliasSet( 
                                           material_reps, 
                                           alias_map_list,
                                           aliases );

  // Create the material id data maps
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<double> > material_id_fraction_map;
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<std::string> > material_id_component_map;
  
  StandardCollisionHandlerFactory<moab::DagMC>::createMaterialIdDataMaps( 
                                                     material_reps,
                                                     material_id_fraction_map,
                                                     material_id_component_map );

  // Create the cell id data maps
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
		       std::vector<std::string> > cell_id_mat_id_map;
  
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
		       std::vector<std::string> > cell_id_density_map;

  StandardCollisionHandlerFactory<moab::DagMC>::createCellIdDataMaps( 
							 cell_id_mat_id_map, 
							 cell_id_density_map );

  // Initialize an atomic relaxation model factory
  Teuchos::RCP<AtomicRelaxationModelFactory> atomic_relaxation_model_factory(
					    new AtomicRelaxationModelFactory );

  // Load the cross section data
  switch( SimulationProperties::getParticleMode() )
  {
  case NEUTRON_MODE:
  {
    StandardCollisionHandlerFactory<moab::DagMC>::createNeutronMaterials(
						  cross_sections_table_info,
						  cross_sections_xml_directory,
						  material_id_fraction_map,
						  material_id_component_map,
						  aliases,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  false,
						  false );
    break;
  }
  case PHOTON_MODE:
  {
    StandardCollisionHandlerFactory<moab::DagMC>::createPhotonMaterials(
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationProperties::getNumberOfPhotonHashGridBins(),
		     SimulationProperties::getIncoherentModelType(),
		     SimulationProperties::getKahnSamplingCutoffEnergy(),
		     SimulationProperties::isDetailedPairProductionModeOn(),
		     SimulationProperties::isAtomicRelaxationModeOn(),
		     SimulationProperties::isPhotonuclearInteractionModeOn() );
    break;
  }
  case NEUTRON_PHOTON_MODE:
  {
    std::cerr << "Warning: Neutron-Photon mode is not fully supported!" 
	      << std::endl;
    
    StandardCollisionHandlerFactory<moab::DagMC>::createNeutronMaterials(
						  cross_sections_table_info,
						  cross_sections_xml_directory,
						  material_id_fraction_map,
						  material_id_component_map,
						  aliases,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  false,
						  true );

    StandardCollisionHandlerFactory<moab::DagMC>::createPhotonMaterials(
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationProperties::getNumberOfPhotonHashGridBins(),
		     SimulationProperties::getIncoherentModelType(),
		     SimulationProperties::getKahnSamplingCutoffEnergy(),
		     SimulationProperties::isDetailedPairProductionModeOn(),
		     SimulationProperties::isAtomicRelaxationModeOn(),
		     SimulationProperties::isPhotonuclearInteractionModeOn() );
    break;
  }
  case ELECTRON_MODE:
  {
    StandardCollisionHandlerFactory<moab::DagMC>::createElectronMaterials(
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationProperties::getBremsstrahlungAngularDistributionFunction(),
		     SimulationProperties::isAtomicRelaxationModeOn() );
    break;
  }
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: " << SimulationProperties::getParticleMode() <<
		     " is not currently supported!" );
  }	    
}

// Validate a material representation
void StandardCollisionHandlerFactory<moab::DagMC>::validateMaterialRep( 
	      const Teuchos::ParameterList& material_rep,
	      boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>&
	      material_ids )
{
  CollisionHandlerFactory::validateMaterialRep( material_rep, material_ids );
}

// Validate the material ids
// If DagMC has not been enabled this function will be empty. 
void StandardCollisionHandlerFactory<moab::DagMC>::validateMaterialIds(
				  const Teuchos::ParameterList& material_reps )
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

// Create the set of all nuclides/atoms needed to construct materials
void StandardCollisionHandlerFactory<moab::DagMC>::createAliasSet( 
		       const Teuchos::ParameterList& material_reps,
		       const Teuchos::ParameterList& cross_sections_alias_map,
		       boost::unordered_set<std::string>& nuclides )
{
  CollisionHandlerFactory::createAliasSet( material_reps,
                                           cross_sections_alias_map,
                                           nuclides );
}

// Create the material id data maps
void StandardCollisionHandlerFactory<moab::DagMC>::createMaterialIdDataMaps(
     const Teuchos::ParameterList& material_reps,
     boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                          Teuchos::Array<double> >& material_id_fraction_map,
     boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<std::string> >& material_id_component_map )
{
  CollisionHandlerFactory::createMaterialIdDataMaps( material_reps,
                                                     material_id_fraction_map,
                                                     material_id_component_map );
}

// Create the cell id data maps using DagMC
// If DagMC has not been enabled this function will be empty
void StandardCollisionHandlerFactory<moab::DagMC>::createCellIdDataMaps(
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                               std::vector<std::string> >& cell_id_mat_id_map,
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_density_map )
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
