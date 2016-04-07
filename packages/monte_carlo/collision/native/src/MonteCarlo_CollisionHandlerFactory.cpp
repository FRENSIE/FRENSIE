//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandlerFactory.hpp
//! \author Alex Robinson
//! \brief  Collision handler factory class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
CollisionHandlerFactory::CollisionHandlerFactory( std::ostream* os_warn )
  : d_os_warn( os_warn )
{
  // Make sure the output stream is valid
  testPrecondition( os_warn != NULL );
}

// Initialize the collision handler
/*! \details Make sure the simulation properties have been set 
 * (in MonteCarlo::SimulationGeneralProperties etc) before running this factory
 * method. The properties can influence how this factory method behaves.
 */
void CollisionHandlerFactory::initializeHandler(
		     const Teuchos::ParameterList& material_reps,
		     const Teuchos::ParameterList& cross_sections_table_info,
		     const std::string& cross_sections_xml_directory )
{
  // Validate the materials
  Teuchos::ParameterList::ConstIterator it = material_reps.begin();

  MatIdSet material_ids;
  
  while( it != material_reps.end() )
  {
    const Teuchos::ParameterList& material_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    CollisionHandlerFactory::validateMaterialRep( material_rep,
						  material_ids );

    ++it;
  }
  
  // Validate the material ids
  this->validateMaterialIds( material_ids );
  
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
  AliasSet aliases;

  CollisionHandlerFactory::createAliasSet( material_reps, 
					   alias_map_list,
					   aliases );

  // Create the material id data maps
  MatIdFractionMap material_id_fraction_map;
  MatIdComponentMap material_id_component_map;
  
  CollisionHandlerFactory::createMaterialIdDataMaps( 
						   material_reps,
						   material_id_fraction_map,
						   material_id_component_map );

  // Create the cell id data maps
  CellIdMatIdMap cell_id_mat_id_map;
  CellIdDensityMap cell_id_density_map;

  this->createCellIdDataMaps( cell_id_mat_id_map, cell_id_density_map );

  // Initialize an atomic relaxation model factory
  Teuchos::RCP<AtomicRelaxationModelFactory> atomic_relaxation_model_factory(
					    new AtomicRelaxationModelFactory );

  // Load the cross section data
  switch( SimulationGeneralProperties::getParticleMode() )
  {
  case NEUTRON_MODE:
  {
    this->createNeutronMaterials( cross_sections_table_info,
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
    this->createPhotonMaterials( 
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationPhotonProperties::getNumberOfPhotonHashGridBins(),
		     SimulationPhotonProperties::getIncoherentModelType(),
		     SimulationPhotonProperties::getKahnSamplingCutoffEnergy(),
		     SimulationPhotonProperties::isDetailedPairProductionModeOn(),
		     SimulationPhotonProperties::isAtomicRelaxationModeOn(),
		     SimulationPhotonProperties::isPhotonuclearInteractionModeOn() );
    break;
  }
  case NEUTRON_PHOTON_MODE:
  {
    this->createNeutronMaterials( cross_sections_table_info,
				  cross_sections_xml_directory,
				  material_id_fraction_map,
				  material_id_component_map,
				  aliases,
				  cell_id_mat_id_map,
				  cell_id_density_map,
				  false,
				  true );

    this->createPhotonMaterials(
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationPhotonProperties::getNumberOfPhotonHashGridBins(),
		     SimulationPhotonProperties::getIncoherentModelType(),
		     SimulationPhotonProperties::getKahnSamplingCutoffEnergy(),
		     SimulationPhotonProperties::isDetailedPairProductionModeOn(),
		     SimulationPhotonProperties::isAtomicRelaxationModeOn(),
		     SimulationPhotonProperties::isPhotonuclearInteractionModeOn() );
    break;
  }
  case ELECTRON_MODE:
  {
    this->createElectronMaterials(
		     cross_sections_table_info,
		     cross_sections_xml_directory,
		     material_id_fraction_map,
		     material_id_component_map,
		     aliases,
		     cell_id_mat_id_map,
		     cell_id_density_map,
		     atomic_relaxation_model_factory,
		     SimulationElectronProperties::getBremsstrahlungAngularDistributionFunction(),
		     SimulationElectronProperties::isAtomicRelaxationModeOn() );
    break;
  }
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: " << SimulationGeneralProperties::getParticleMode() <<
		     " is not currently supported!" );
  }	    
}

// Validate a material representation
void CollisionHandlerFactory::validateMaterialRep( 
	                            const Teuchos::ParameterList& material_rep,
                                    MatIdSet& material_ids )
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

// Create the set of all nuclides/atoms needed to construct materials
void CollisionHandlerFactory::createAliasSet( 
		        const Teuchos::ParameterList& material_reps,
                        const Teuchos::ParameterList& cross_sections_alias_map,
                        AliasSet& nuclides )
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
                                 MatIdFractionMap& material_id_fraction_map,
                                 MatIdComponentMap& material_id_component_map )
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

// Create the neutron materials
void CollisionHandlerFactory::createNeutronMaterials( 
                       const Teuchos::ParameterList& cross_sections_table_info,
                       const std::string& cross_sections_xml_directory,
                       const MatIdFractionMap& material_id_fraction_map,
                       const MatIdComponentMap& material_id_component_map,
                       const AliasSet& nuclide_aliases,
                       const CellIdMatIdMap& cell_id_mat_id_map,
                       const CellIdDensityMap& cell_id_density_map,
                       const bool use_unresolved_resonance_data,
                       const bool use_photon_production_data )
{
  // Load the nuclides of interest
  NuclideFactory nuclide_factory( cross_sections_xml_directory,
				  cross_sections_table_info,
				  nuclide_aliases,
				  use_unresolved_resonance_data,
				  use_photon_production_data,
				  d_os_warn );

  std::unordered_map<std::string,Teuchos::RCP<Nuclide> > nuclide_map;

  nuclide_factory.createNuclideMap( nuclide_map );

  // Create the material name data maps
  std::unordered_map<std::string,Teuchos::RCP<NeutronMaterial> >
    material_name_pointer_map;
  
  MatNameCellIdsMap material_name_cell_ids_map;

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
                       const MatIdFractionMap& material_id_fraction_map,
                       const MatIdComponentMap& material_id_component_map,
                       const AliasSet& photoatom_aliases,
                       const CellIdMatIdMap& cell_id_mat_id_map,
                       const CellIdDensityMap& cell_id_density_map,
                       const Teuchos::RCP<AtomicRelaxationModelFactory>& 
                       atomic_relaxation_model_factory,
                       const unsigned hash_grid_bins,
                       const IncoherentModelType incoherent_model,
                       const double kahn_sampling_cutoff_energy,
                       const bool use_detailed_pair_production_data,
                       const bool use_atomic_relaxation_data,
                       const bool use_photonuclear_data )
{
  std::unordered_map<std::string,Teuchos::RCP<Photoatom> > photoatom_map;

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
					use_atomic_relaxation_data,
					d_os_warn );
    
    photoatom_factory.createPhotoatomMap( photoatom_map );
  }

  // Create the material name data maps
  std::unordered_map<std::string,Teuchos::RCP<PhotonMaterial> >
    material_name_pointer_map;
  
  MatNameCellIdsMap material_name_cell_ids_map;

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
      const MatIdFractionMap& material_id_fraction_map,
      const MatIdComponentMap& material_id_component_map,
      const AliasSet& electroatom_aliases,
      const CellIdMatIdMap& cell_id_mat_id_map,
      const CellIdDensityMap& cell_id_density_map,
      const Teuchos::RCP<AtomicRelaxationModelFactory>& 
      atomic_relaxation_model_factory,
      const BremsstrahlungAngularDistributionType photon_distribution_function,
      const bool use_atomic_relaxation_data )
{
  std::unordered_map<std::string,Teuchos::RCP<Electroatom> > electroatom_map;

  ElectroatomFactory electroatom_factory( cross_sections_xml_directory,
                                          cross_sections_table_info,
					  electroatom_aliases,
                                          atomic_relaxation_model_factory,
                                          photon_distribution_function,
                                          use_atomic_relaxation_data,
					  d_os_warn );
    
  electroatom_factory.createElectroatomMap( electroatom_map );

  // Create the material name data maps
  std::unordered_map<std::string,Teuchos::RCP<ElectronMaterial> >
    material_name_pointer_map;
  
  MatNameCellIdsMap material_name_cell_ids_map;

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

// Get the warning output stream
std::ostream& CollisionHandlerFactory::getOsWarn() const
{
  return *d_os_warn;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
