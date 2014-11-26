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
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string cross_sections_xml_directory;
Teuchos::ParameterList cross_section_table_info;
boost::unordered_set<std::string> photoatom_aliases;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory> 
atomic_relaxation_model_factory;
Teuchos::RCP<MonteCarlo::PhotoatomFactory> photoatom_factory;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (only basic data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_basic )
{
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       false,
					       false,
					       false ) );

  boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
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
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
				 exp( -1.364234411496E+01 ),
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				 exp( 1.151292546497E+01 ),
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );

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
  fake_stream[0] = 0.1; // select the incoherent reaction
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
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_doppler )
{
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       true,
					       false,
					       false ) );

  boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
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
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
				 exp( -1.364234411496E+01 ),
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				 exp( 1.151292546497E+01 ),
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );

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
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.1; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop
  fake_stream[4] = 0.005; // select first shell for collision
  fake_stream[5] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[6] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.3528040136905526, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (detailed pair production data)
// TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_detailed_pp )
// {
//   photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
// 					       cross_sections_xml_directory,
// 					       cross_section_table_info,
// 					       photoatom_aliases,
// 					       atomic_relaxation_model_factory,
// 					       true,
// 					       false,
// 					       false ) );

//   boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
//     photoatom_map;

//   photoatom_factory->createPhotoatomMap( photoatom_map );

//   TEST_EQUALITY_CONST( photoatom_map.size(), 1 );
//   TEST_ASSERT( photoatom_map.count( "Pb" ) );
//   TEST_ASSERT( !photoatom_map["Pb"].is_null() );
// }

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (subshell pe data)
TEUCHOS_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_pe_subshells )
{
  photoatom_factory.reset( new MonteCarlo::PhotoatomFactory(
					       cross_sections_xml_directory,
					       cross_section_table_info,
					       photoatom_aliases,
					       atomic_relaxation_model_factory,
					       false,
					       false,
					       true ) );

  boost::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> > 
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
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection( 
				 exp( -1.364234411496E+01 ),
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				 exp( 1.151292546497E+01 ),
				 MonteCarlo::INCOHERENT_PHOTOATOMIC_REACTION );

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

    // Create the set of photoatom aliases
    photoatom_aliases.insert( "Pb" );  
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
