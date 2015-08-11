//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandlerFactory.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "FRENSIE_root_config.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_CollisionHandlerFactory_Root.hpp"
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

// Initialize the collision handler using Root
/*! \details Make sure the simulation properties have been set 
 * (in MonteCarlo::SimulationProperties) before running this factory
 * method. The properties will influence how this factory method behaves.
 */
void CollisionHandlerFactory<Geometry::Root>::initializeHandler( 
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

    CollisionHandlerFactory<Geometry::Root>::validateMaterialRep( material_rep,
						  material_ids );

    ++it;
  }
  
  material_ids.clear();

  // Validate the material ids
  CollisionHandlerFactory<Geometry::Root>::validateMaterialIds( material_reps );
  
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

  CollisionHandlerFactory<Geometry::Root>::createAliasSet( material_reps, 
                                           alias_map_list,
                                           aliases );

  // Create the material id data maps
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<double> > material_id_fraction_map;
  boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                       Teuchos::Array<std::string> > material_id_component_map;
  
  CollisionHandlerFactory<Geometry::Root>::createMaterialIdDataMaps( material_reps,
                                                     material_id_fraction_map,
                                                     material_id_component_map );

  // Create the cell id data maps
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
		       std::vector<std::string> > cell_id_mat_id_map;
  
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
		       std::vector<std::string> > cell_id_density_map;

  CollisionHandlerFactory<Geometry::Root>::createCellIdDataMaps( 
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
    CollisionHandlerFactory<Geometry::Root>::createNeutronMaterials(
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
    CollisionHandlerFactory<Geometry::Root>::createPhotonMaterials(
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
    
    CollisionHandlerFactory<Geometry::Root>::createNeutronMaterials(
						  cross_sections_table_info,
						  cross_sections_xml_directory,
						  material_id_fraction_map,
						  material_id_component_map,
						  aliases,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  false,
						  true );

    CollisionHandlerFactory<Geometry::Root>::createPhotonMaterials(
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
    CollisionHandlerFactory<Geometry::Root>::createElectronMaterials(
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
void CollisionHandlerFactory<Geometry::Root>::validateMaterialRep( 
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

// Validate the material ids
// If ROOT has not been enabled this function will be empty. 
void CollisionHandlerFactory<Geometry::Root>::validateMaterialIds(
				  const Teuchos::ParameterList& material_reps )
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
			<< requested_material_ids[i] << " which is lacking "
			"a definition!" );
				
		material_counter += 1;
		mat = Geometry::Root::getManager()->GetMaterial( material_counter );
  } 
  #endif // end HAVE_FRENSIE_ROOT
}

// Create the set of all nuclides/atoms needed to construct materials
void CollisionHandlerFactory<Geometry::Root>::createAliasSet( 
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
void CollisionHandlerFactory<Geometry::Root>::createMaterialIdDataMaps(
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
    
    const Utility::ArrayString& array_string = 
      material_rep.get<Utility::ArrayString>( "Fractions" );

    Teuchos::Array<double> material_fractions;

    try{
      material_fractions = array_string.getConcreteArray<double>();
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				InvalidMaterialRepresentation,
				"Error: The fractions requested for "
				"material " << material_rep.name() << 
				" are not valid!" );      

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

// Create the cell id data maps
// If ROOT has not been enabled this function will be empty
void CollisionHandlerFactory<Geometry::Root>::createCellIdDataMaps(
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                             unsigned >& cell_id_mat_id_map,
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                             double >& cell_id_density_map )
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
    
    // TODO Chop off the prior part of the number
    // Check for the void properties and then IF statement to do nothing
    
    double density =  mat->GetDensity();
    
    // Update the unordered maps
    cell_id_mat_id_map[ i + 1 ] = material;
    cell_id_density_map[ i + 1 ] = density;
  }

  // Make sure that the maps have the same size
  TEST_FOR_EXCEPTION( cell_id_mat_id_map.size() != cell_id_density_map.size(),
		      InvalidMaterialRepresentation,
		      "Error: ROOT must specify densities with material "
		      "ids." );
  #endif // end HAVE_FRENSIE_ROOT
}

// Create the neutron materials
void CollisionHandlerFactory<Geometry::Root>::createNeutronMaterials( 
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

  CollisionHandlerFactory<Geometry::Root>::createMaterialNameDataMaps( 
						  material_id_fraction_map,
						  material_id_component_map,
						  nuclide_map,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  material_name_pointer_map,
						  material_name_cell_ids_map );

  // Register materials with the collision handler
  CollisionHandlerFactory<Geometry::Root>::registerMaterials( material_name_pointer_map,
					      material_name_cell_ids_map );
}

// Create the photon materials
void CollisionHandlerFactory<Geometry::Root>::createPhotonMaterials(
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
   const unsigned hash_grid_bins,
   const IncoherentModelType incoherent_model,
   const double kahn_sampling_cutoff_energy,
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
					hash_grid_bins,
					incoherent_model,
					kahn_sampling_cutoff_energy,
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

  CollisionHandlerFactory<Geometry::Root>::createMaterialNameDataMaps( 
						  material_id_fraction_map,
						  material_id_component_map,
						  photoatom_map,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  material_name_pointer_map,
						  material_name_cell_ids_map );

  // Register materials with the collision handler
  CollisionHandlerFactory<Geometry::Root>::registerMaterials( material_name_pointer_map,
					      material_name_cell_ids_map );
}

// Create the electron materials
void CollisionHandlerFactory<Geometry::Root>::createElectronMaterials(
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

  CollisionHandlerFactory<Geometry::Root>::createMaterialNameDataMaps( 
						  material_id_fraction_map,
						  material_id_component_map,
						  electroatom_map,
						  cell_id_mat_id_map,
						  cell_id_density_map,
						  material_name_pointer_map,
						  material_name_cell_ids_map );

  // Register materials with the collision handler
  CollisionHandlerFactory<Geometry::Root>::registerMaterials( material_name_pointer_map,
                                              material_name_cell_ids_map );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
