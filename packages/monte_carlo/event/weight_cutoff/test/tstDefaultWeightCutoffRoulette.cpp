//---------------------------------------------------------------------------//
//!
//! \file   tstDefaultWeightCutoffRoulette.cpp
//! \author Luke Kersting
//! \brief  Default weight cutoff roulette unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_WeightCutoffRoulette.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cells can be returned
FRENSIE_UNIT_TEST( DefaultWeightCutoffRoulette, getCutoffWeights )
{
  std::shared_ptr<const MonteCarlo::WeightCutoffRoulette> weight_roulette =
    MonteCarlo::WeightCutoffRoulette::getDefault();

  double threshold_weight = 0.0;
  double survival_weight = 0.0;

  weight_roulette->getCutoffWeights( MonteCarlo::PHOTON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );

  weight_roulette->getCutoffWeights( MonteCarlo::ELECTRON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );

  weight_roulette->getCutoffWeights( MonteCarlo::POSITRON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );

  weight_roulette->getCutoffWeights( MonteCarlo::NEUTRON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the particle types can be returned
FRENSIE_UNIT_TEST( DefaultWeightCutoffRoulette, getParticleTypes )
{
  std::shared_ptr<const MonteCarlo::WeightCutoffRoulette> weight_roulette =
    MonteCarlo::WeightCutoffRoulette::getDefault();

  std::set<MonteCarlo::ParticleType> particle_types;

  weight_roulette->getParticleTypes( particle_types );

  FRENSIE_CHECK( particle_types.empty() );
}


//---------------------------------------------------------------------------//
// Check that a particle can be rouletted
FRENSIE_UNIT_TEST( DefaultWeightCutoffRoulette, rouletteParticleWeight )
{
  std::shared_ptr<const MonteCarlo::WeightCutoffRoulette> weight_roulette =
    MonteCarlo::WeightCutoffRoulette::getDefault();

  {
    MonteCarlo::PhotonState photon( 0 );
    photon.setEnergy( 1.0 );
    photon.setPosition( 0.0, 0.0, 0.0 );
    photon.setDirection( 0.0, 0.0, 1.0 );
    photon.setWeight( 1.0 );

    FRENSIE_REQUIRE_NO_THROW( weight_roulette->rouletteParticleWeight( photon ) );

    FRENSIE_CHECK_EQUAL( photon.getWeight(), 1.0 );
  }

  {
    MonteCarlo::ElectronState electron( 0 );
    electron.setEnergy( 1.0 );
    electron.setPosition( 0.0, 0.0, 0.0 );
    electron.setDirection( 0.0, 0.0, 1.0 );
    electron.setWeight( 1.0 );

    FRENSIE_REQUIRE_NO_THROW( weight_roulette->rouletteParticleWeight( electron ) );

    FRENSIE_CHECK_EQUAL( electron.getWeight(), 1.0 );
  }

  {
    MonteCarlo::PositronState positron( 0 );
    positron.setEnergy( 1.0 );
    positron.setPosition( 0.0, 0.0, 0.0 );
    positron.setDirection( 0.0, 0.0, 1.0 );
    positron.setWeight( 1.0 );

    FRENSIE_REQUIRE_NO_THROW( weight_roulette->rouletteParticleWeight( positron ) );

    FRENSIE_CHECK_EQUAL( positron.getWeight(), 1.0 );
  }

  {
    MonteCarlo::NeutronState neutron( 0 );
    neutron.setEnergy( 1.0 );
    neutron.setPosition( 0.0, 0.0, 0.0 );
    neutron.setDirection( 0.0, 0.0, 1.0 );
    neutron.setWeight( 1.0 );

    FRENSIE_REQUIRE_NO_THROW( weight_roulette->rouletteParticleWeight( neutron ) );

    FRENSIE_CHECK_EQUAL( neutron.getWeight(), 1.0 );
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

  std::string archive_base_name( "test_default_weight_roulette" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const MonteCarlo::WeightCutoffRoulette> weight_roulette =
      MonteCarlo::WeightCutoffRoulette::getDefault();

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(weight_roulette) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const MonteCarlo::WeightCutoffRoulette> weight_roulette;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(weight_roulette) );

  iarchive.reset();

  double threshold_weight = 0.0;
  double survival_weight = 0.0;

  weight_roulette->getCutoffWeights( MonteCarlo::PHOTON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );

  weight_roulette->getCutoffWeights( MonteCarlo::ELECTRON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );

  weight_roulette->getCutoffWeights( MonteCarlo::POSITRON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );

  weight_roulette->getCutoffWeights( MonteCarlo::NEUTRON,
                                     threshold_weight,
                                     survival_weight );

  FRENSIE_CHECK( threshold_weight == 0.0 );
  FRENSIE_CHECK( survival_weight == 0.0 );

  std::set<MonteCarlo::ParticleType> particle_types;

  weight_roulette->getParticleTypes( particle_types );

  FRENSIE_CHECK( particle_types.empty() );
}

//---------------------------------------------------------------------------//
// end tstDefaultWeightCutoffRoulette.cpp
//---------------------------------------------------------------------------//
