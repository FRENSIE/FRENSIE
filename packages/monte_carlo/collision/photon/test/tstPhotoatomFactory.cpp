//---------------------------------------------------------------------------//
//!
//! \file   tstPhotoatomFactory.cpp
//! \author Alex Robinson
//! \brief  Photoatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <fstream>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<const boost::filesystem::path> data_directory;
std::unique_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase> photoatom_definitions;
std::shared_ptr<MonteCarlo::AtomicRelaxationModelFactory>
atomic_relaxation_model_factory;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (only basic data)
FRENSIE_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_ace_basic )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::WH_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                     new MonteCarlo::PhotoatomFactory(
                                               *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb" ) );
  FRENSIE_CHECK( photoatom_map["Pb"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom = photoatom_map["Pb"];

  // Test the photoatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.12p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section =
    atom->getTotalCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.006275141600000259, 1e-12 );

  cross_section =
    atom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 41.18471143984235, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    atom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    atom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-11 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( -1.364234411496E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				   exp( -1.364234411496E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Test that the total photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			exp( -1.214969212306E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			exp( -1.214720768866E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );

  // Test that there is no triplet production cross section
  cross_section = atom->getReactionCrossSection(
			 exp( -1.381551055796E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			 exp( 1.151292546497E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the Doppler data is not present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setWeight( 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.1; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Reset the photoatom factory
  photoatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (only basic data)
FRENSIE_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_native_basic )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::WH_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                       new MonteCarlo::PhotoatomFactory(
					       *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( photoatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom =
    photoatom_map["Pb-Native"];

  // Test the photoatom properties
  FRENSIE_CHECK( atom->getAtomName().find( "test_epr_82_native.xml" ) <
	       atom->getAtomName().size() );

  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999999999999886, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.79084232526918314e+06, 1e-12 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.13373119562157392e+01, 1e-12 );

  // Test that the absorption cross section can be reaturned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
			   0.001,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );

  cross_section = atom->getReactionCrossSection(
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection(
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection(
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       2*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 18.5899999999999999, 1e-15 );

  // Test that the triplet production cross section can be returned
  cross_section = atom->getReactionCrossSection(
                         0.001,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       4*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                         20.0,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the Doppler data is not present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.1; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Reset the photoatom factory
  photoatom_factory.reset();
}


//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (Doppler data)
FRENSIE_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_ace_doppler )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                        new MonteCarlo::PhotoatomFactory(
                                               *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb" ) );
  FRENSIE_CHECK( photoatom_map["Pb"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom = photoatom_map["Pb"];

  // Test the photoatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.12p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section =
    atom->getTotalCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.006275141600000259, 1e-12 );

  cross_section =
    atom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 41.18471143984235, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    atom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    atom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-11 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( -1.364234411496E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				   exp( -1.364234411496E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Test that the total photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			exp( -1.214969212306E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			exp( -1.214720768866E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.718780625507E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );

  // Test that there is no triplet production cross section
  cross_section = atom->getReactionCrossSection(
			 exp( -1.381551055796E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			 exp( 1.151292546497E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setWeight( 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.1; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop
  fake_stream[4] = 0.005; // select first shell for collision - old
  fake_stream[5] = 0.005; // select first shell for collision - endf
  fake_stream[6] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[7] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (Doppler data)
FRENSIE_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_native_doppler )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                               new MonteCarlo::PhotoatomFactory(
                                               *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( photoatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom =
    photoatom_map["Pb-Native"];

  // Test the photoatom properties
  FRENSIE_CHECK( atom->getAtomName().find( "test_epr_82_native.xml" ) <
                 atom->getAtomName().size() );

  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999999999999886, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.79084232526918314e+06, 1e-15 );

  cross_section = atom->getTotalCrossSection( 20.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 21.3373119562183398, 1e-15 );

  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
			   0.001,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );

  cross_section = atom->getReactionCrossSection(
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection(
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection(
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       2*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 18.5899999999999999, 1e-15 );

  // Test that the triplet production cross section can be returned
  cross_section = atom->getReactionCrossSection(
                         0.001,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       4*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                         20.0,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-12 );

  // Test that there are no subshell cross sections
  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the Doppler data is present
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.1; // select the incoherent reaction
  fake_stream[1] = 0.001; // sample from first term of koblinger's method
  fake_stream[2] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[3] = 0.5; // accept x in scattering function rejection loop
  fake_stream[4] = 0.005; // select first shell for collision
  fake_stream[5] = 0.5; // select pz = 0.0
  fake_stream[6] = 0.0; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  atom->collideAnalogue( photon, bank );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (impulse approx data)
FRENSIE_UNIT_TEST( PhotoatomFactory,
		   createPhotoatomMap_native_impulse_approx_basic )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::IMPULSE_INCOHERENT_MODEL ),
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                   new MonteCarlo::PhotoatomFactory(
					       *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( photoatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom =
    photoatom_map["Pb-Native"];

  // Test the photoatom properties
  FRENSIE_CHECK( atom->getAtomName().find( "test_epr_82_native.xml" ) <
                 atom->getAtomName().size() );

  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999999999999886, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.79084209057610761E+06, 1e-12 );

  cross_section = atom->getTotalCrossSection( 20.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 21.3391619464462181, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that there is no total incoherent cross section
  cross_section = atom->getReactionCrossSection(
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test the subshell incoherent cross sections can be returned
  cross_section = atom->getReactionCrossSection(
		      8.82900086220703151e-02,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.25526576584511952e-09, 1e-6 );

  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.03100615156834802e-02, 1e-6 );

  cross_section = atom->getReactionCrossSection(
		     1e-3,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.198065568410027426, 1e-6 );

  cross_section = atom->getReactionCrossSection(
		     20.0,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0402322921484711687, 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection(
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection(
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       2*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 18.5899999999999999, 1e-15 );

  // Test that the triplet production cross section can be returned
  cross_section = atom->getReactionCrossSection(
                         0.001,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       4*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                         20.0,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-12 );

  // Test that there are no subshell photoelectric cross sections
  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
  
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

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (impulse approx, Doppler data)
FRENSIE_UNIT_TEST( PhotoatomFactory,
		   createPhotoatomMap_native_impulse_approx_doppler )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::FULL_PROFILE_DB_IMPULSE_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOff( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                     new MonteCarlo::PhotoatomFactory(
					       *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap
    photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( photoatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom =
    photoatom_map["Pb-Native"];

  // Test the photoatom properties
  FRENSIE_CHECK( atom->getAtomName().find( "test_epr_82_native.xml" ) <
                 atom->getAtomName().size() );

  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999999999999886, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.79084209057610761E+06, 1e-12 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 21.3391619464462181, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that there is no total incoherent cross section
  cross_section = atom->getReactionCrossSection(
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test the subshell incoherent cross sections can be returned
  cross_section = atom->getReactionCrossSection(
		      8.82900086220703151e-02,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.25526576584511952e-09, 1e-6 );

  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0603100048795882984, 1e-9 );

  cross_section = atom->getReactionCrossSection(
		     1e-3,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.198065568410027426, 1e-6 );

  cross_section = atom->getReactionCrossSection(
		     20.0,
		     MonteCarlo::P3_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0402322921484711687, 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection(
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getReactionCrossSection(
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       2*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 18.5899999999999999, 1e-15 );

  // Test that the triplet production cross section can be returned
  cross_section = atom->getReactionCrossSection(
                         0.001,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       4*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                         20.0,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-12 );

  // Test that there are no subshell photoelectric cross sections
  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

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

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (detailed pair production data)
// FRENSIE_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_detailed_pp )
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

//   MonteCarlo::PhotoatomFactory::PhotoatomNameMap
//     photoatom_map;

//   photoatom_factory->createPhotoatomMap( photoatom_map );

//   FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
//   FRENSIE_CHECK( photoatom_map.count( "Pb" ) );
//   FRENSIE_CHECK( photoatom_map["Pb"].get() );
// }

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (subshell pe data)
FRENSIE_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_ace_pe_subshells )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::WH_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                     new MonteCarlo::PhotoatomFactory(
					       *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb" ) );
  FRENSIE_CHECK( photoatom_map["Pb"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom = photoatom_map["Pb"];

  // Test the photoatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomName(), "82000.12p" );
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section =
    atom->getTotalCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.006275141600000259, 1e-12 );

  cross_section =
    atom->getTotalCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 41.18471143984235, 1e-12 );

  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( exp( -1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section =
    atom->getAbsorptionCrossSection( exp( -1.214969212306E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section =
    atom->getAbsorptionCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.115947249407E+01 ), 1e-11 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
			   exp( -1.381551055796E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.338724079720E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( -1.364234411496E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.304090138782E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			   exp( 1.151292546497E+01 ),
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -6.573285045032E+00 ), 1e-12 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   exp(-1.381551055796E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				   exp( -1.364234411496E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
				   exp( 1.151292546497E+01 ),
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );

  // Test that there is no total photoelectric
  cross_section = atom->getReactionCrossSection(
			exp( -1.381551055796E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			exp( 1.151292546497E+01 ),
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    exp( -1.381551055796E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			    exp( 2.480967890857E-02 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.431923975437E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
			    exp( 1.151292546497E+01 ),
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.718032834377E+00 ), 1e-12 );

  // Test that there is no triplet production cross section
  cross_section = atom->getReactionCrossSection(
			 exp( -1.381551055796E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			 exp( 1.151292546497E+01 ),
			 MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  // Test that the K subshell photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
		   exp( -1.381551055796E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   exp( -2.427128314806E+00 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 7.578565567350E+00 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   exp( 1.151292546497E+01 ),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.135387253512E+01 ), 1e-12 );

  // Test that the P3 subshell photoelectric cross section can be returned
  cross_section = atom->getReactionCrossSection(
		  exp( -1.381551055796E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  exp( -1.214969212306E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.719257539043E+01 ), 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  exp( 1.151292546497E+01 ),
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -2.364731020721E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a photoatom map can be created (subshell pe data)
FRENSIE_UNIT_TEST( PhotoatomFactory, createPhotoatomMap_native_pe_subshells )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "Pb-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::WH_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                     new MonteCarlo::PhotoatomFactory(
					       *data_directory,
                                               photoatom_aliases,
					       *photoatom_definitions,
					       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 1 );
  FRENSIE_CHECK( photoatom_map.count( "Pb-Native" ) );
  FRENSIE_CHECK( photoatom_map["Pb-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::Photoatom>& atom =
    photoatom_map["Pb-Native"];

  // Test the photoatom properties
  FRENSIE_CHECK( atom->getAtomName().find( "test_epr_82_native.xml" ) <
                 atom->getAtomName().size() );

  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 82 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999999999999886, 1e-12 );

  // Test that the total cross section can be returned
  double cross_section = atom->getTotalCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.79084232526918314e+06, 1e-15 );

  cross_section = atom->getTotalCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 21.3373119562183398, 1e-15 );

  // Test that the absorption cross section can be reaturned
  cross_section = atom->getAbsorptionCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.78857306272290740e+06, 1e-15 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.03368055321776603e-02, 1e-15 );

  // Test that the incoherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
			   0.001,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.23509999999967790e+00, 1e-15 );

  cross_section = atom->getReactionCrossSection(
			   20.0,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.47834228852720528e+00, 1e-15 );

  // Test that the coherent cross section can be returned
  cross_section = atom->getReactionCrossSection(
				   0.001,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.26802744627581296e+03, 1e-3 );

  cross_section = atom->getReactionCrossSection(
				   20.0,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.33286215895818971e-03, 1e-3 );

  // Test that the total photoelectric cross section is not present
  cross_section = atom->getReactionCrossSection(
			0.001,
			MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
			20.0,
		        MonteCarlo::TOTAL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  // Test that the subshell photoelectric cross sections can be returned
  cross_section = atom->getReactionCrossSection(
		   8.82900099999595622e-02,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95582145812230942e+03, 1e-15 );

  cross_section = atom->getReactionCrossSection(
		   20.0,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.61425467896072372e-02, 1e-15 );

  cross_section = atom->getReactionCrossSection(
		  1e-3,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 7.38175550850533909e+02, 1e-24 );

  cross_section = atom->getReactionCrossSection(
		  20.0,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.03007633456089762e-07, 1e-15 );

  // Test that the pair production cross section can be returned
  cross_section = atom->getReactionCrossSection(
			    0.001,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       2*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
			    20.0,
			    MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 18.5899999999999999, 1e-15 );

  // Test that the triplet production cross section can be returned
  cross_section = atom->getReactionCrossSection(
                         0.001,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                       4*Utility::PhysicalConstants::electron_rest_mass_energy,
                       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection(
                         20.0,
                         MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-12 );

  // Test that there are no subshell incoherent cross sections
  cross_section = atom->getReactionCrossSection(
		      20.0,
		      MonteCarlo::K_SUBSHELL_INCOHERENT_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
FRENSIE_UNIT_TEST( PhotoatomFactory, no_duplicate_tables )
{
  // Create the set of photoatom aliases
  MonteCarlo::PhotoatomFactory::ScatteringCenterNameSet photoatom_aliases;
  photoatom_aliases.insert( "H-1_293.6K" );
  photoatom_aliases.insert( "H-1_300K" );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 100 );
  properties.setIncoherentModelType( MonteCarlo::WH_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();

  std::unique_ptr<MonteCarlo::PhotoatomFactory> photoatom_factory(
                                          new MonteCarlo::PhotoatomFactory(
        				       *data_directory,
                                               photoatom_aliases,
        				       *photoatom_definitions,
        				       atomic_relaxation_model_factory,
                                               properties,
                                               true ) );

  MonteCarlo::PhotoatomFactory::PhotoatomNameMap photoatom_map;

  photoatom_factory->createPhotoatomMap( photoatom_map );

  FRENSIE_CHECK_EQUAL( photoatom_map.size(), 2 );

  FRENSIE_CHECK( photoatom_map.count( "H-1_293.6K" ) );
  FRENSIE_CHECK( photoatom_map["H-1_293.6K"].get() != NULL );

  FRENSIE_CHECK( photoatom_map.count( "H-1_300K" ) );
  FRENSIE_CHECK( photoatom_map["H-1_300K"].get() != NULL );

  FRENSIE_CHECK( photoatom_map["H-1_293.6K"] == photoatom_map["H-1_300K"] );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_scattering_center_database_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Determine the database directory
  boost::filesystem::path database_path =
    test_scattering_center_database_name;
  
  data_directory.reset(
                  new boost::filesystem::path( database_path.parent_path() ) );
  // Load the database
  const Data::ScatteringCenterPropertiesDatabase database( database_path );

  const Data::AtomProperties& h_properties =
    database.getAtomProperties( 1001 );
  
  const Data::AtomProperties& pb_properties =
    database.getAtomProperties( Data::Pb_ATOM );
  
  // Initialize the photoatom definitions
  photoatom_definitions.reset( new MonteCarlo::ScatteringCenterDefinitionDatabase );

  MonteCarlo::ScatteringCenterDefinition& h1_293K_definition =
    photoatom_definitions->createDefinition( "H-1_293.6K", 1001 );

  h1_293K_definition.setPhotoatomicDataProperties(
           h_properties.getSharedPhotoatomicDataProperties(
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 12 ) );

  photoatom_definitions->createDefinitionAlias( "H-1_293.6K", "H-1_300K" );
  
  MonteCarlo::ScatteringCenterDefinition& pb_definition =
    photoatom_definitions->createDefinition( "Pb", Data::Pb_ATOM );

  pb_definition.setPhotoatomicDataProperties(
           pb_properties.getSharedPhotoatomicDataProperties(
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 12 ) );

  MonteCarlo::ScatteringCenterDefinition& pb_native_definition =
    photoatom_definitions->createDefinition( "Pb-Native", Data::Pb_ATOM );

  pb_native_definition.setPhotoatomicDataProperties(
           pb_properties.getSharedPhotoatomicDataProperties(
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

  // Create the atomic relaxation model factory
  atomic_relaxation_model_factory.reset(
				new MonteCarlo::AtomicRelaxationModelFactory );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotoatomFactory.cpp
//---------------------------------------------------------------------------//
