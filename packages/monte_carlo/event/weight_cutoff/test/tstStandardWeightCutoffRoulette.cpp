//---------------------------------------------------------------------------//
//!
//! \file   tstStandardWeightCutoffRoulette.cpp
//! \author Luke Kersting
//! \brief  Standard weight cutoff roulette unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardWeightCutoffRoulette.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

using boost::units::si::kelvin;
using boost::units::cgs::cubic_centimeter;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cutoff weights can be set
FRENSIE_UNIT_TEST( StandardWeightCutoffRoulette,
                   setCutoffWeights )
{
  auto weight_roulette = std::make_shared<MonteCarlo::StandardWeightCutoffRoulette>();

  double threshold_weight = 1e-20;
  double survival_weight = 1e-5;


  weight_roulette->setCutoffWeights( MonteCarlo::PHOTON,
                                     threshold_weight,
                                     survival_weight );

  double test_threshold_weight, test_survival_weight;

  weight_roulette->getCutoffWeights( MonteCarlo::PHOTON,
                                     test_threshold_weight,
                                     test_survival_weight );

  FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
  FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

  test_threshold_weight = 0.0;
  test_survival_weight = 1.0;

  weight_roulette->setCutoffWeights( MonteCarlo::NEUTRON,
                                     threshold_weight,
                                     survival_weight );

  weight_roulette->getCutoffWeights( MonteCarlo::NEUTRON,
                                     test_threshold_weight,
                                     test_survival_weight );

  FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
  FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

  test_threshold_weight = 0.0;
  test_survival_weight = 1.0;

  weight_roulette->setCutoffWeights( MonteCarlo::ELECTRON,
                                     threshold_weight,
                                     survival_weight );

  weight_roulette->getCutoffWeights( MonteCarlo::ELECTRON,
                                     test_threshold_weight,
                                     test_survival_weight );

  FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
  FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

  test_threshold_weight = 0.0;
  test_survival_weight = 1.0;

  weight_roulette->setCutoffWeights( MonteCarlo::POSITRON,
                                     threshold_weight,
                                     survival_weight );

  weight_roulette->getCutoffWeights( MonteCarlo::POSITRON,
                                     test_threshold_weight,
                                     test_survival_weight );

  FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
  FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

  test_threshold_weight = 0.0;
  test_survival_weight = 1.0;

  std::set<MonteCarlo::ParticleType> particle_types;

  weight_roulette->getParticleTypes( particle_types );

  FRENSIE_REQUIRE_EQUAL( particle_types.size(), 4 );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( particle_types.count( MonteCarlo::POSITRON ) );
}

//---------------------------------------------------------------------------//
// Check that a particle can be rouletted
FRENSIE_UNIT_TEST( StandardWeightCutoffRoulette,
                   rouletteParticleWeight )
{
  std::shared_ptr<MonteCarlo::StandardWeightCutoffRoulette>
    weight_roulette( new MonteCarlo::StandardWeightCutoffRoulette );

  double threshold_weight = 1e-15;
  double survival_weight = 1e-12;

  weight_roulette->setCutoffWeights( MonteCarlo::PHOTON,
                                     threshold_weight,
                                     survival_weight );

  weight_roulette->setCutoffWeights( MonteCarlo::NEUTRON,
                                     threshold_weight,
                                     survival_weight );

  weight_roulette->setCutoffWeights( MonteCarlo::ELECTRON,
                                     threshold_weight,
                                     survival_weight );

  weight_roulette->setCutoffWeights( MonteCarlo::POSITRON,
                                     threshold_weight,
                                     survival_weight );

  {
    MonteCarlo::PhotonState photon( 0 );
    photon.setEnergy( 1.0 );
    photon.setPosition( 0.0, 0.0, 0.0 );
    photon.setDirection( 0.0, 0.0, 1.0 );
    photon.setWeight( 9e-16 );

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 9e-4; // Particle survives
    fake_stream[1] = 9e-4 + 1e-10; // Particle is rouletted

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    weight_roulette->rouletteParticleWeight( photon );

    FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( photon.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( photon.getWeight(), survival_weight );

    photon.setWeight( 9e-16 );
    weight_roulette->rouletteParticleWeight( photon );

    //FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.0 );
    FRENSIE_CHECK( photon.isGone() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::NeutronState neutron( 0 );
    neutron.setEnergy( 1.0 );
    neutron.setPosition( 0.0, 0.0, 0.0 );
    neutron.setDirection( 0.0, 0.0, 1.0 );
    neutron.setWeight( 9e-16 );

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 9e-4; // Particle survives
    fake_stream[1] = 9e-4 + 1e-10; // Particle is rouletted

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    weight_roulette->rouletteParticleWeight( neutron );

    FRENSIE_CHECK_EQUAL( neutron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( neutron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( neutron.getWeight(), survival_weight );

    neutron.setWeight( 9e-16 );
    weight_roulette->rouletteParticleWeight( neutron );

    //FRENSIE_CHECK_EQUAL( neutron.getWeight(), 0.0 );
    FRENSIE_CHECK( neutron.isGone() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 1.0 );
    electron.setPosition( 0.0, 0.0, 0.0 );
    electron.setDirection( 0.0, 0.0, 1.0 );
    electron.setWeight( 9e-16 );

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 9e-4; // Particle survives
    fake_stream[1] = 9e-4 + 1e-10; // Particle is rouletted

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    weight_roulette->rouletteParticleWeight( electron );

    FRENSIE_CHECK_EQUAL( electron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( electron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( electron.getWeight(), survival_weight );

    electron.setWeight( 9e-16 );
    weight_roulette->rouletteParticleWeight( electron );

    //FRENSIE_CHECK_EQUAL( electron.getWeight(), 0.0 );
    FRENSIE_CHECK( electron.isGone() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 0 );
    positron.setEnergy( 1.0 );
    positron.setPosition( 0.0, 0.0, 0.0 );
    positron.setDirection( 0.0, 0.0, 1.0 );
    positron.setWeight( 9e-16 );

    std::vector<double> fake_stream( 2 );
    fake_stream[0] = 9e-4; // Particle survives
    fake_stream[1] = 9e-4 + 1e-10; // Particle is rouletted

    Utility::RandomNumberGenerator::setFakeStream( fake_stream );

    weight_roulette->rouletteParticleWeight( positron );

    FRENSIE_CHECK_EQUAL( positron.getXPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getYPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getZPosition(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getXDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getYDirection(), 0.0 );
    FRENSIE_CHECK_EQUAL( positron.getZDirection(), 1.0 );
    FRENSIE_CHECK_EQUAL( positron.getWeight(), survival_weight );

    positron.setWeight( 9e-16 );
    weight_roulette->rouletteParticleWeight( positron );

    //FRENSIE_CHECK_EQUAL( positron.getWeight(), 0.0 );
    FRENSIE_CHECK( positron.isGone() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that a weight cutoff roulette can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardWeightCutoffRoulette,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_standard_weight_roulette" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::StandardWeightCutoffRoulette>
      weight_roulette;

    {
      std::shared_ptr<MonteCarlo::StandardWeightCutoffRoulette>
        tmp_weight_roulette( new MonteCarlo::StandardWeightCutoffRoulette );

      double threshold_weight = 1e-15;
      double survival_weight = 1e-12;

      tmp_weight_roulette->setCutoffWeights( MonteCarlo::PHOTON,
                                             threshold_weight,
                                             survival_weight );

      tmp_weight_roulette->setCutoffWeights( MonteCarlo::NEUTRON,
                                             threshold_weight,
                                             survival_weight );

      tmp_weight_roulette->setCutoffWeights( MonteCarlo::ELECTRON,
                                             threshold_weight,
                                             survival_weight );

      tmp_weight_roulette->setCutoffWeights( MonteCarlo::POSITRON,
                                             threshold_weight,
                                             survival_weight );

      weight_roulette = tmp_weight_roulette;
    }

    std::shared_ptr<const MonteCarlo::WeightCutoffRoulette> base_weight_roulette =
      weight_roulette;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(base_weight_roulette) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(weight_roulette) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::WeightCutoffRoulette> base_weight_roulette;
  std::shared_ptr<const MonteCarlo::StandardWeightCutoffRoulette> weight_roulette;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(base_weight_roulette) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(weight_roulette) );

  iarchive.reset();

  FRENSIE_CHECK( weight_roulette.get() == base_weight_roulette.get() );

  {
    double threshold_weight = 1e-15;
    double survival_weight = 1e-12;
    double test_threshold_weight = 0.0;
    double test_survival_weight = 1.0;

    base_weight_roulette->getCutoffWeights( MonteCarlo::PHOTON,
                                            test_threshold_weight,
                                            test_survival_weight );

    FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
    FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

    test_threshold_weight = 0.0;
    test_survival_weight = 1.0;

    base_weight_roulette->getCutoffWeights( MonteCarlo::NEUTRON,
                                            test_threshold_weight,
                                            test_survival_weight );

    FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
    FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

    test_threshold_weight = 0.0;
    test_survival_weight = 1.0;

    base_weight_roulette->getCutoffWeights( MonteCarlo::ELECTRON,
                                            test_threshold_weight,
                                            test_survival_weight );

    FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
    FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

    test_threshold_weight = 0.0;
    test_survival_weight = 1.0;

    base_weight_roulette->getCutoffWeights( MonteCarlo::POSITRON,
                                            test_threshold_weight,
                                            test_survival_weight );

    FRENSIE_CHECK_EQUAL( threshold_weight, test_threshold_weight );
    FRENSIE_CHECK_EQUAL( survival_weight, test_survival_weight );

    test_threshold_weight = 0.0;
    test_survival_weight = 1.0;

    std::set<MonteCarlo::ParticleType> particle_types;
    base_weight_roulette->getParticleTypes( particle_types );

    FRENSIE_REQUIRE_EQUAL( particle_types.size(), 4 );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::PHOTON ) );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::NEUTRON ) );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::ELECTRON ) );
    FRENSIE_CHECK( particle_types.count( MonteCarlo::POSITRON ) );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();


FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardWeightCutoffRoulette.cpp
//---------------------------------------------------------------------------//
