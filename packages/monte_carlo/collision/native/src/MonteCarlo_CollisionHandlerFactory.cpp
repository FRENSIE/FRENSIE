//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandlerFactory.cpp
//! \author Alex Robinson
//! \brief  Collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "FRENSIE_dagmc_config.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationProperties.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"
#endif

#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the collision handler using DagMC
/*! \details Make sure the simulation properties have been set 
 * (in MonteCarlo::SimulationProperties) before running this factory
 * method. The properties will influence how this factory method behaves.
 */
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

  CollisionHandlerFactory::createAliasSet( material_reps, 
                                           alias_map_list,
                                           aliases );

  // Create the material id data maps
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<double> > material_id_fraction_map;
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<std::string> > material_id_component_map;
  
  CollisionHandlerFactory::createMaterialIdDataMaps( material_reps,
                                                     material_id_fraction_map,
                                                     material_id_component_map );

  // Create the cell id data maps using DagMC
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
		       std::vector<std::string> > cell_id_mat_id_map;
  
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
		       std::vector<std::string> > cell_id_density_map;

  CollisionHandlerFactory::createCellIdDataMapsUsingDagMC( 
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
    CollisionHandlerFactory::createNeutronMaterials(
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
    CollisionHandlerFactory::createPhotonMaterials(
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationProperties::getNumberOfPhotonHashGridBins(),
		     SimulationProperties::getMinPhotonEnergy(),
		     SimulationProperties::getMaxPhotonEnergy(),
		     SimulationProperties::isImpulseApproximationModeOn(),
		     SimulationProperties::isPhotonDopplerBroadeningModeOn(),
		     SimulationProperties::isDetailedPairProductionModeOn(),
		     SimulationProperties::isAtomicRelaxationModeOn(),
		     SimulationProperties::isPhotonuclearInteractionModeOn() );
    break;
  }
  case NEUTRON_PHOTON_MODE:
  {
    std::cerr << "Warning: Neutron-Photon mode is not fully supported!" 
	      << std::endl;
    
    CollisionHandlerFactory::createNeutronMaterials(
						  cross_sections_table_info,
						  cross_sections_xml_directory,
						  material_id_fraction_map,
						  material_id_component_map,
						  aliases,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  false,
						  true );

    CollisionHandlerFactory::createPhotonMaterials(
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationProperties::getNumberOfPhotonHashGridBins(),
		     SimulationProperties::getMinPhotonEnergy(),
		     SimulationProperties::getMaxPhotonEnergy(),
		     SimulationProperties::isImpulseApproximationModeOn(),
		     SimulationProperties::isPhotonDopplerBroadeningModeOn(),
		     SimulationProperties::isDetailedPairProductionModeOn(),
		     SimulationProperties::isAtomicRelaxationModeOn(),
		     SimulationProperties::isPhotonuclearInteractionModeOn() );
    break;
  }
  case ELECTRON_MODE:
  {
    CollisionHandlerFactory::createElectronMaterials(
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
// If DagMC has not been enabled this function will be empty. 
void CollisionHandlerFactory::validateMaterialIdsUsingDagMC(
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
void CollisionHandlerFactory::createAliasSet( 
		       const Teuchos::ParameterList& material_reps,
		       const Teuchos::ParameterList& cross_sections_alias_map,
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
    {
      // The name is a key - store the mapped name
      if( cross_sections_alias_map.isParameter( material_isotopes[i] ) )
      {
	std::string mapped_alias;
	try{ 
	  mapped_alias = 
	    cross_sections_alias_map.get<std::string>( material_isotopes[i] );
        }
	EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
				  "Error: cross section alias map entry "
				  << material_isotopes[i] <<
				  "is invalid! Please fix this entry." );

	nuclides.insert( mapped_alias );	   
      }
      // The name is not a key - store the name
      else
	nuclides.insert( material_isotopes[i] );
    }
    
    ++it;
  }
}

// Create the material id data maps
void CollisionHandlerFactory::createMaterialIdDataMaps(
     const Teuchos::ParameterList& material_reps,
     boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                          Teuchos::Array<double> >& material_id_fraction_map,
     boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<std::string> >& material_id_component_map )
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

    material_id_component_map[material_rep.get<unsigned>( "Id" )] = 
      material_isotopes;
    
    ++it;
  }
}

// Create the cell id data maps using DagMC
// If DagMC has not been enabled this function will be empty
void CollisionHandlerFactory::createCellIdDataMapsUsingDagMC(
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

// Create the neutron materials
void CollisionHandlerFactory::createNeutronMaterials( 
   const Teuchos::ParameterList& cross_sections_table_info,
   const std::string& cross_sections_xml_directory,
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                            Teuchos::Array<double> >& material_id_fraction_map,
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                      Teuchos::Array<std::string> >& material_id_component_map,
   const boost::unordered_set<std::string>& nuclide_aliases,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_mat_id_map,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                               std::vector<std::string> >& cell_id_density_map,
   const bool use_unresolved_resonance_data,
   const bool use_photon_production_data )
{
  // Load the nuclides of interest
  NuclideFactory nuclide_factory( cross_sections_xml_directory,
				  cross_sections_table_info,
				  nuclide_aliases,
				  use_unresolved_resonance_data,
				  use_photon_production_data );

  boost::unordered_map<std::string,Teuchos::RCP<Nuclide> > nuclide_map;

  nuclide_factory.createNuclideMap( nuclide_map );

  // Create the material name data maps
  boost::unordered_map<std::string,Teuchos::RCP<NeutronMaterial> >
    material_name_pointer_map;
  
  boost::unordered_map<std::string,
                   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >
    material_name_cell_ids_map;

  CollisionHandlerFactory::createMaterialNameDataMaps( 
						  material_id_fraction_map,
						  material_id_component_map,
						  nuclide_map,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  material_name_pointer_map,
						  material_name_cell_ids_map );

  // Register materials with the collision handler
  CollisionHandlerFactory::registerMaterials( material_name_pointer_map,
					      material_name_cell_ids_map );
}

// Create the photon materials
void CollisionHandlerFactory::createPhotonMaterials(
   const Teuchos::ParameterList& cross_sections_table_info,
   const std::string& cross_sections_xml_directory,
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                            Teuchos::Array<double> >& material_id_fraction_map,
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                      Teuchos::Array<std::string> >& material_id_component_map,
   const boost::unordered_set<std::string>& photoatom_aliases,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_mat_id_map,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                               std::vector<std::string> >& cell_id_density_map,
   const Teuchos::RCP<AtomicRelaxationModelFactory>& 
   atomic_relaxation_model_factory,
   const bool use_impulse_approximation_data,
   const bool use_doppler_broadening_data,
   const bool use_detailed_pair_production_data,
   const bool use_atomic_relaxation_data,
   const bool use_photonuclear_data )
{
  boost::unordered_map<std::string,Teuchos::RCP<Photoatom> > photoatom_map;

  // Load the photonuclides of interest
  if( use_photonuclear_data )
  {
    THROW_EXCEPTION( std::logic_error,
		     "Error: Photonuclear data is not currently supported!" );
  }
  // Load the photoatoms of interest
  else
  {
    PhotoatomFactory photoatom_factory( cross_sections_xml_directory,
					cross_sections_table_info,
					photoatom_aliases,
					atomic_relaxation_model_factory,
					use_impulse_approximation_data,
					use_doppler_broadening_data,
					use_detailed_pair_production_data,
					use_atomic_relaxation_data );
    
    photoatom_factory.createPhotoatomMap( photoatom_map );
  }

  // Create the material name data maps
  boost::unordered_map<std::string,Teuchos::RCP<PhotonMaterial> >
    material_name_pointer_map;
  
  boost::unordered_map<std::string,
                   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >
    material_name_cell_ids_map;

  CollisionHandlerFactory::createMaterialNameDataMaps( 
						  material_id_fraction_map,
						  material_id_component_map,
						  photoatom_map,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  material_name_pointer_map,
						  material_name_cell_ids_map );

  // Register materials with the collision handler
  CollisionHandlerFactory::registerMaterials( material_name_pointer_map,
					      material_name_cell_ids_map );
}

// Create the electron materials
void CollisionHandlerFactory::createElectronMaterials(
   const Teuchos::ParameterList& cross_sections_table_info,
   const std::string& cross_sections_xml_directory,
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                            Teuchos::Array<double> >& material_id_fraction_map,
   const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                      Teuchos::Array<std::string> >& material_id_component_map,
   const boost::unordered_set<std::string>& electroatom_aliases,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_mat_id_map,
   const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                               std::vector<std::string> >& cell_id_density_map,
   const Teuchos::RCP<AtomicRelaxationModelFactory>& 
   atomic_relaxation_model_factory,
   const BremsstrahlungAngularDistributionType photon_distribution_function,
   const bool use_atomic_relaxation_data )
{
  boost::unordered_map<std::string,Teuchos::RCP<Electroatom> > electroatom_map;

  ElectroatomFactory electroatom_factory( cross_sections_xml_directory,
                                          cross_sections_table_info,
					  electroatom_aliases,
                                          atomic_relaxation_model_factory,
                                          photon_distribution_function,
                                          use_atomic_relaxation_data );
    
  electroatom_factory.createElectroatomMap( electroatom_map );

  // Create the material name data maps
  boost::unordered_map<std::string,Teuchos::RCP<ElectronMaterial> >
    material_name_pointer_map;
  
  boost::unordered_map<std::string,
                   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >
    material_name_cell_ids_map;

  CollisionHandlerFactory::createMaterialNameDataMaps( 
						  material_id_fraction_map,
						  material_id_component_map,
						  electroatom_map,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  material_name_pointer_map,
						  material_name_cell_ids_map );

  // Register materials with the collision handler
  CollisionHandlerFactory::registerMaterials( material_name_pointer_map,
                                              material_name_cell_ids_map );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
