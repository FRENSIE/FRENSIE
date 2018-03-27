//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationAdjointPhotonProperties.cpp
//! \author Alex Robinson
//! \brief  Simulation adjoint photon properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>,
  std::tuple<boost::archive::polymorphic_oarchive*,boost::archive::polymorphic_iarchive*>
  > TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
FRENSIE_UNIT_TEST( SimulationAdjointPhotonProperties, defaults )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( properties.getMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getAbsoluteMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( properties.getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  FRENSIE_CHECK_EQUAL( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
  FRENSIE_CHECK_EQUAL( properties.getCriticalAdjointPhotonLineEnergies().size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the min adjoint photon energy can be set
FRENSIE_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setMinAdjointPhotonEnergy )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setMinAdjointPhotonEnergy( 1e-2 );

  FRENSIE_CHECK_EQUAL( properties.getMinAdjointPhotonEnergy(), 1e-2 );
}

//---------------------------------------------------------------------------//
// Check that the max adjoint photon energy can be set
FRENSIE_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setMaxAdjointPhotonEnergy )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setMaxAdjointPhotonEnergy( 15.0 );

  FRENSIE_CHECK_EQUAL( properties.getMaxAdjointPhotonEnergy(), 15.0 );
}

//---------------------------------------------------------------------------//
// Check that the number of adjoint photon hash grid bins can be set
FRENSIE_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setNumberOfAdjointPhotonHashGridBins )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setNumberOfAdjointPhotonHashGridBins( 750 );

  FRENSIE_CHECK_EQUAL( properties.getNumberOfAdjointPhotonHashGridBins(),
                       750 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent adjoint model type can be set
FRENSIE_UNIT_TEST( SimulationAdjointPhotonProperties,
                   setIncoherentAdjointModelType )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;
  
  properties.setIncoherentAdjointModelType(
                                     MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );

  FRENSIE_CHECK_EQUAL( properties.getIncoherentAdjointModelType(),
                       MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be set
FRENSIE_UNIT_TEST( SimulationAdjointPhotonProperties,
                   getCriticalAdjointPhotonLineEnergies )
{
  MonteCarlo::SimulationAdjointPhotonProperties properties;

  std::vector<double> critical_line_energies( 2 );
  critical_line_energies[0] = 1.0;
  critical_line_energies[1] = 10.0;
  
  properties.setCriticalAdjointPhotonLineEnergies( critical_line_energies );

  FRENSIE_CHECK_EQUAL( properties.getCriticalAdjointPhotonLineEnergies(),
                       critical_line_energies );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SimulationAdjointPhotonProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_simulation_adjoint_photon_props" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::SimulationAdjointPhotonProperties default_properties;

    MonteCarlo::SimulationAdjointPhotonProperties custom_properties;
    custom_properties.setMinAdjointPhotonEnergy( 1e-2 );
    custom_properties.setMaxAdjointPhotonEnergy( 15.0 );
    custom_properties.setNumberOfAdjointPhotonHashGridBins( 750 );
    custom_properties.setIncoherentAdjointModelType(
                                     MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );
    custom_properties.setCriticalAdjointPhotonLineEnergies( std::vector<double>({1.0, 10.0}) );
        
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( default_properties ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( custom_properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::SimulationAdjointPhotonProperties default_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( default_properties ) );

  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( default_properties.getMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( default_properties.getMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getAbsoluteMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( default_properties.getNumberOfAdjointPhotonHashGridBins(),
                       500 );
  FRENSIE_CHECK_EQUAL( default_properties.getIncoherentAdjointModelType(),
                       MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
  FRENSIE_CHECK_EQUAL( default_properties.getCriticalAdjointPhotonLineEnergies().size(), 0 );

  MonteCarlo::SimulationAdjointPhotonProperties custom_properties;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( custom_properties ) );

  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMinAdjointPhotonEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMinAdjointPhotonEnergy(), 1e-2 );
  FRENSIE_CHECK_EQUAL( custom_properties.getMaxAdjointPhotonEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getAbsoluteMaxAdjointPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( custom_properties.getNumberOfAdjointPhotonHashGridBins(),
                       750 );
  FRENSIE_CHECK_EQUAL( custom_properties.getIncoherentAdjointModelType(),
                       MonteCarlo::KN_INCOHERENT_ADJOINT_MODEL );
  FRENSIE_CHECK_EQUAL( custom_properties.getCriticalAdjointPhotonLineEnergies(),
                       std::vector<double>({1.0, 10.0}) );
}

//---------------------------------------------------------------------------//
// end tstSimulationAdjointPhotonProperties.cpp
//---------------------------------------------------------------------------//
