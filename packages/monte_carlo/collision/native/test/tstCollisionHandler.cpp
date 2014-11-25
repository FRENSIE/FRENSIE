//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Collision handler class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_CollisionHandler.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::NeutronMaterial> cold_hydrogen;
Teuchos::RCP<MonteCarlo::NeutronMaterial> hot_hydrogen;

Teuchos::RCP<MonteCarlo::PhotonMaterial> lead;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that material can be added to the collision handler
TEUCHOS_UNIT_TEST( CollisionHandler, addMaterial )
{
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;
  
  MonteCarlo::CollisionHandler::addMaterial( cold_hydrogen,
					     cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 2, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 3, MonteCarlo::NEUTRON ) );

  cells_containing_material[0] = 4;
  cells_containing_material[1] = 5;
  cells_containing_material[2] = 6;

  MonteCarlo::CollisionHandler::addMaterial( hot_hydrogen,
					     cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 4, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 6, MonteCarlo::NEUTRON ) );

  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 0, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::NEUTRON ) );

  MonteCarlo::CollisionHandler::addMaterial( lead, cells_containing_material );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 4, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 6, MonteCarlo::PHOTON ) );

  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 0, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::PHOTON ) );
}

//---------------------------------------------------------------------------//
// Check that the material contained in a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getCellNeutronMaterial )
{
  Teuchos::RCP<MonteCarlo::NeutronMaterial> cell_material = 
    MonteCarlo::CollisionHandler::getCellNeutronMaterial( 1 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 2 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 3 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 4 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );

  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 5 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );
  
  cell_material = MonteCarlo::CollisionHandler::getCellNeutronMaterial( 6 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the material contained within a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getCellPhotonMaterial )
{
  Teuchos::RCP<MonteCarlo::PhotonMaterial> cell_material = 
    MonteCarlo::CollisionHandler::getCellPhotonMaterial( 4 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellPhotonMaterial( 5 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );

  cell_material = MonteCarlo::CollisionHandler::getCellPhotonMaterial( 6 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getMacroscopicTotalCrossSection )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );
  
  double cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );
  
  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 2 );
  
  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );
  
  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 3 );
  
  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );
  
  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic reaction cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( CollisionHandler, getMacroscopicReactionCrossSection )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
						   neutron,
						   MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
						   neutron,
						   MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  
  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 693.47099764974, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28845947418338, 1e-13 );
  
  neutron.setEnergy( 1.0e-11 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__GAMMA_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  neutron.setEnergy( 2.0e1 );
  
  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__GAMMA_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__DPA );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  neutron.setEnergy( 2.0e1 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__DPA );

  TEST_FLOATING_EQUALITY( cross_section, 1.833066682067e-4, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section = 
    MonteCarlo::CollisionHandler::getMacroscopicReactionCrossSection( 
					       neutron,
					       MonteCarlo::N__FISSION_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );
} 

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( CollisionHandler, collideWithCellMaterial )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  MonteCarlo::CollisionHandler::collideWithCellMaterial( neutron, bank, true );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  neutron.setCell( 4 );
  neutron.setEnergy( 1.0 );
  
  MonteCarlo::CollisionHandler::collideWithCellMaterial( neutron, bank, true );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );  

  neutron.setCell( 1 );
  neutron.setEnergy( 1.03125e-11 );

  MonteCarlo::CollisionHandler::collideWithCellMaterial( neutron, bank, false );

  TEST_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_cross_sections_xml_directory;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
		 &test_cross_sections_xml_directory,
		 "Test cross_sections.xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Assign the name of the cross_sections.xml file with path
    std::string cross_section_xml_file = test_cross_sections_xml_directory;
    cross_section_xml_file += "/cross_sections.xml";

    // Read in the xml file storing the cross section table information 
    Teuchos::ParameterList cross_section_table_info;
    Teuchos::updateParametersFromXmlFile( 
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );

    boost::unordered_set<std::string> nuclide_aliases;
    nuclide_aliases.insert( "H-1_293.6K" );
    nuclide_aliases.insert( "H-1_900K" );

    MonteCarlo::NuclideFactory nuclide_factory( 
					     test_cross_sections_xml_directory,
					     cross_section_table_info,
					     nuclide_aliases );

    boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Nuclide> > 
      nuclide_map;

    nuclide_factory.createNuclideMap( nuclide_map );

    // Create cold hydrogen
    Teuchos::Array<double> nuclide_fractions( 1 );
    Teuchos::Array<std::string> nuclide_names( 1 );
    
    nuclide_fractions[0] = -1.0;
    nuclide_names[0] = "H-1_293.6K";
    
    cold_hydrogen.reset( new MonteCarlo::NeutronMaterial( 0,
							  -1.0,
							  nuclide_map,
							  nuclide_fractions,
							  nuclide_names ) );

    // Create hot hydrogen
    nuclide_names[0] = "H-1_900K";
    
    hot_hydrogen.reset( new MonteCarlo::NeutronMaterial( 1,
							 -1.0,
							 nuclide_map,
							 nuclide_fractions,
							 nuclide_names ) );

    boost::unordered_set<std::string> atom_aliases;
    atom_aliases.insert( "Pb" );

    // Create the factories
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory> 
      atomic_relaxation_model_factory(
				new MonteCarlo::AtomicRelaxationModelFactory );
    
    MonteCarlo::PhotoatomFactory factory( test_cross_sections_xml_directory,
					  cross_section_table_info,
					  atom_aliases,
					  atomic_relaxation_model_factory );

    boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> >
      atom_map;

    factory.createPhotoatomMap( atom_map );

    // Assign the atom fractions and names
    Teuchos::Array<double> atom_fractions( 1 );
    Teuchos::Array<std::string> atom_names( 1 );

    atom_fractions[0] = -1.0; // weight fraction
    atom_names[0] = "Pb";

    // Create the lead
    lead.reset( new MonteCarlo::PhotonMaterial( 0,
						-1.0,
						atom_map,
						atom_fractions,
						atom_names ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstCollisionHandler.cpp
//---------------------------------------------------------------------------//
