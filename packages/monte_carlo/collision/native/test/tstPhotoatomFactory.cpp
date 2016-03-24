//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomFactory.cpp
//! \author Alex Robinson
//! \brief  Photoatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string cross_sections_xml_directory;
Teuchos::ParameterList cross_section_table_info;
std::unordered_set<std::string> photoatom_aliases;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory> 
atomic_relaxation_model_factory;
Teuchos::RCP<MonteCarlo::PhotoatomFactory> photoatom_factory;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (only basic data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_ace_basic )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       100,
					       MonteCarlo::WH_INCOHERENT_MODEL,
					       3.0,
					       false,
					       false ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb" ) );
  TEST_ASSERT( !photoatom_map["Pb"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb"];

  // Test the photoatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = 
    atom->getTotalCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.006275141600000259, 1e-12 );

  cross_section = 
    atom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 41.18471143984235, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section = 
    atom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = 
    atom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    atom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-11 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			   exp( -1.364234411496E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );
  
  cross_section = atom->getReactionCrossSection( 
				   exp( -1.364234411496E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Test that the total photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section = atom->getReactionCrossSection( 
			exp( -1.214969212306E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			exp( -1.214720768866E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );
  
  // Test that there is no triplet production cross section
  cross_section = atom->getReactionCrossSection( 
			 exp( -1.381551055796E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			 exp( 1.151292546497E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the Doppler data is not present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setWeight( 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.9; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Reset the photoatom factory
  photoatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (only basic data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_native_basic )
{
  
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb-Native" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       100,
					       MonteCarlo::WH_INCOHERENT_MODEL,
					       3.0,
					       false,
					       false ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !photoatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb-Native"];

  std::string cross_sections_xml_name = cross_sections_xml_directory;
  cross_sections_xml_name += "/test_epr_82_native.xml";

  // Test the photoatom properties
  TEST_ASSERT( atom->getAtomName().find( "test_epr_82_native.xml" ) <
	       atom->getAtomName().size() );

  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.79084232526918314e+06, 1e-15 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.13373119562157392e+01, 1e-15 );
  
  // Test that the absorption cross section can be reaturned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			   0.001,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );
  
  cross_section = atom->getReactionCrossSection( 
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection( 
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );
  
  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 
			    1.02673329640432032e+00,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.09098184021483652e-06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.87762999999973985e+01, 1e-15 );
  
  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
					
  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  // Test that there is no triple production cross section
  cross_section = atom->getReactionCrossSection(
			 20.0,
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
						
  // Test that the Doppler data is not present
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.9; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop
    
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Reset the photoatom factory
  photoatom_factory.reset();
}


//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (Doppler data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_ace_doppler )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
		 cross_sections_xml_directory,
		 cross_section_table_info,
		 photoatom_aliases,
		 atomic_relaxation_model_factory,
		 100,
		 MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		 3.0,
		 false,
		 false ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb" ) );
  TEST_ASSERT( !photoatom_map["Pb"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb"];

  // Test the photoatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = 
    atom->getTotalCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.006275141600000259, 1e-12 );

  cross_section = 
    atom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 41.18471143984235, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section = 
    atom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = 
    atom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    atom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-11 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			   exp( -1.364234411496E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );
  
  cross_section = atom->getReactionCrossSection( 
				   exp( -1.364234411496E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Test that the total photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
    
  cross_section = atom->getReactionCrossSection( 
			exp( -1.214969212306E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			exp( -1.214720768866E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );
  
  // Test that there is no triplet production cross section
  cross_section = atom->getReactionCrossSection( 
			 exp( -1.381551055796E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			 exp( 1.151292546497E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setWeight( 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.9; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop
  fake_stream[4] = 0.005; // select first shell for collision - old
  fake_stream[5] = 0.005; // select first shell for collision - endf
  fake_stream[6] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[7] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );
  
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (Doppler data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_native_doppler )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb-Native" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
		   cross_sections_xml_directory,
		   cross_section_table_info,
		   photoatom_aliases,
		   atomic_relaxation_model_factory,
		   100,
		   MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL,
		   3.0,
		   false,
		   false ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !photoatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb-Native"];

  std::string cross_sections_xml_name = cross_sections_xml_directory;
  cross_sections_xml_name += "/test_epr_82_native.xml";

  // Test the photoatom properties
  TEST_ASSERT( atom->getAtomName().find( "test_epr_82_native.xml" ) <
	       atom->getAtomName().size() );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.79084232526918314e+06, 1e-15 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.13373119562157392e+01, 1e-15 );
  
  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			   0.001,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );
  
  cross_section = atom->getReactionCrossSection( 
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection( 
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );
  
  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 
			    1.02673329640432032e+00,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.09098184021483652e-06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.87762999999973985e+01, 1e-15 );
  
  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
					
  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no triple production cross section
  cross_section = atom->getReactionCrossSection(
			 20.0,
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
						
  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.9; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop
  fake_stream[4] = 0.005; // select first shell for collision
  fake_stream[5] = 0.5; // select pz = 0.0
  fake_stream[6] = 0.0; // azimuthal_angle = pi
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (impulse approx data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, 
		   createPhotoatomMap_native_impulse_approx_basic )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb-Native" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					  cross_sections_xml_directory,
					  cross_section_table_info,
					  photoatom_aliases,
					  atomic_relaxation_model_factory,
					  100,
					  MonteCarlo::IMPULSE_INCOHERENT_MODEL,
					  3.0,
					  false,
					  false ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !photoatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb-Native"];

  std::string cross_sections_xml_name = cross_sections_xml_directory;
  cross_sections_xml_name += "/test_epr_82_native.xml";

  // Test the photoatom properties
  TEST_ASSERT( atom->getAtomName().find( "test_epr_82_native.xml" ) <
	       atom->getAtomName().size() );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.79084209030231880e+06, 1e-15 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.13391613162646543e+01, 1e-15 );
  
  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that there is no total incoherent cross section
  cross_section = atom->getReactionCrossSection(
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test the subshell incoherent cross sections can be returned
  cross_section = atom->getReactionCrossSection( 
		      8.82900086220703151e-02,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 5.25553220583787745e-09, 1e-15 );
  
  cross_section = atom->getReactionCrossSection( 
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-15 );
						
  cross_section = atom->getReactionCrossSection( 
		     1e-3,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.98041761897415292e-01, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
		     20.0,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.02322890775264064e-02, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection( 
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 
			    1.02673329640432032e+00,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.09098184021483652e-06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.87762999999973985e+01, 1e-15 );

  // Test that there are no subshell photoelectric cross sections
  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no triple production cross section
  cross_section = atom->getReactionCrossSection(
			 20.0,
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the Doppler data is not present
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.005; // select the K shell incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[4] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (impulse approx, Doppler data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, 
		   createPhotoatomMap_native_impulse_approx_doppler )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb-Native" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       100,
					       MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL,
					       3.0,
					       false,
					       false ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !photoatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb-Native"];

  std::string cross_sections_xml_name = cross_sections_xml_directory;
  cross_sections_xml_name += "/test_epr_82_native.xml";

  // Test the photoatom properties
  TEST_ASSERT( atom->getAtomName().find( "test_epr_82_native.xml" ) <
	       atom->getAtomName().size() );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.79084209030231880e+06, 1e-15 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.13391613162646543e+01, 1e-15 );
  
  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that there is no total incoherent cross section
  cross_section = atom->getReactionCrossSection(
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test the subshell incoherent cross sections can be returned
  cross_section = atom->getReactionCrossSection( 
		      8.82900086220703151e-02,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 5.25553220583787745e-09, 1e-15 );
  
  cross_section = atom->getReactionCrossSection( 
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-15 );
						
  cross_section = atom->getReactionCrossSection( 
		     1e-3,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.98041761897415292e-01, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
		     20.0,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.02322890775264064e-02, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection( 
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 
			    1.02673329640432032e+00,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.09098184021483652e-06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.87762999999973985e+01, 1e-15 );

  // Test that there are no subshell photoelectric cross sections
  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no triple production cross section
  cross_section = atom->getReactionCrossSection(
			 20.0,
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.005; // select the K shell incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[4] = 0.5; // select pz = 0.0
  fake_stream[5] = 0.0; // azimuthal_angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (detailed pair production data)
// TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_detailed_pp )
// {
//   // Create the set of photoatom aliases
//   photoatom_aliases.insert( "Pb" );
//  
//   photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
// 					       cross_sections_xml_directory,
// 					       cross_section_table_info,
// 					       photoatom_aliases,
// 					       atomic_relaxation_model_factory,
// 					       true,
// 					       false,
// 					       false ) );

//   std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
//     photoatom_map;

//   photoatom_factory->createPhotoatomMap( photoatom_map );

//   TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
//   TEST_ASSERT( photoatom_map.count( "Pb" ) );
//   TEST_ASSERT( !photoatom_map["Pb"].is_null() );
// }

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (subshell pe data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_ace_pe_subshells )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       100,
					       MonteCarlo::WH_INCOHERENT_MODEL,
					       3.0,
					       false,
					       true ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb" ) );
  TEST_ASSERT( !photoatom_map["Pb"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb"];

  // Test the photoatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "82000.12p" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = 
    atom->getTotalCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.006275141600000259, 1e-12 );

  cross_section = 
    atom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 41.18471143984235, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section = 
    atom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = 
    atom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = 
    atom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-11 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			   exp( -1.364234411496E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );
  
  cross_section = atom->getReactionCrossSection( 
				   exp( -1.364234411496E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Test that there is no total photoelectric
  cross_section = atom->getReactionCrossSection( 
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );
  
  // Test that there is no triplet production cross section
  cross_section = atom->getReactionCrossSection( 
			 exp( -1.381551055796E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			 exp( 1.151292546497E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  // Test that the K subshell photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   exp( -2.427128314806E+00 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 7.578565567350E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.135387253512E+01 ), 1e-12 );

  // Test that the P3 subshell photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
		  exp( -1.381551055796E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  exp( -1.214969212306E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  exp( 1.151292546497E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -2.364731020721E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (subshell pe data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_native_pe_subshells )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "Pb-Native" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       100,
					       MonteCarlo::WH_INCOHERENT_MODEL,
					       3.0,
					       false,
					       true ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
  TEST_ASSERT( photoatom_map.count( "Pb-Native" ) );
  TEST_ASSERT( !photoatom_map["Pb-Native"].is_null() );

  Teuchos::RCP<MonteCarlo::Photoatom>& atom = photoatom_map["Pb-Native"];

  std::string cross_sections_xml_name = cross_sections_xml_directory;
  cross_sections_xml_name += "/test_epr_82_native.xml";

  // Test the photoatom properties
  TEST_ASSERT( atom->getAtomName().find( "test_epr_82_native.xml" ) <
	       atom->getAtomName().size() );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 1.79084232526918314e+06, 1e-15 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 2.13373119562157392e+01, 1e-15 );
  
  // Test that the absorption cross section can be reaturned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			   0.001,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );
  
  cross_section = atom->getReactionCrossSection( 
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection( 
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection( 
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the total photoelectric cross section is not present
  cross_section = atom->getReactionCrossSection( 
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the subshell photoelectric cross sections can be returned
  cross_section = atom->getReactionCrossSection(
		   8.82900099999595622e-02,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.95582145812230942e+03, 1e-15 );
		      
  cross_section = atom->getReactionCrossSection( 
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.61425467896072372e-02, 1e-15 );
  
  cross_section = atom->getReactionCrossSection( 
		  1e-3,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.38175550850533909e+02, 1e-24 );
  
  cross_section = atom->getReactionCrossSection( 
		  20.0,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.03007633456089762e-07, 1e-15 );
  
  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection( 
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 
			    1.02673329640432032e+00,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.09098184021483652e-06, 1e-15 );

  cross_section = atom->getReactionCrossSection( 
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.87762999999973985e+01, 1e-15 );
  
  // Test that there are no subshell incoherent cross sections
  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that there is no triple production cross section
  cross_section = atom->getReactionCrossSection(
			 20.0,
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
TEUCHOS_UNIT_TEST( PhotoatomFactory, no_duplicate_tables )
{
  // Create the set of photoatom aliases
  photoatom_aliases.clear();
  photoatom_aliases.insert( "H-1_293.6K" );
  photoatom_aliases.insert( "H-1_300K" );
  
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       100,
					       MonteCarlo::WH_INCOHERENT_MODEL,
					       3.0,
					       false,
					       true ) );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  TEST_EQUALITY_CONST( photoatom_map.size(), 2 );
  
  TEST_ASSERT( photoatom_map.count( "H-1_293.6K" ) );
  TEST_ASSERT( !photoatom_map["H-1_293.6K"].is_null() );

  TEST_ASSERT( photoatom_map.count( "H-1_300K" ) );
  TEST_ASSERT( !photoatom_map["H-1_300K"].is_null() );
  
  TEST_EQUALITY( photoatom_map["H-1_293.6K"], photoatom_map["H-1_300K"] );
} 

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
		 &cross_sections_xml_directory,
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
    std::string cross_sections_xml_file = cross_sections_xml_directory;
    cross_sections_xml_file += "/cross_sections.xml";
    
    // Read in the xml file storing the cross section table info
    Teuchos::updateParametersFromXmlFile(
			       cross_sections_xml_file,
			       Teuchos::inoutArg( cross_section_table_info ) );

    // Create the atomic relaxation model factory
    atomic_relaxation_model_factory.reset(
				new MonteCarlo::AtomicRelaxationModelFactory );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}


//---------------------------------------------------------------------------//
// end tstPhotoatomFactory.cpp
//---------------------------------------------------------------------------//
