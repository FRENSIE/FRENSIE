//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCModelProperties.cpp
//! \author Alex Robinson
//! \brief  DagMC model properties class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "Geometry_DagMCModelProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the default properties are correct
FRENSIE_UNIT_TEST( DagMCModelProperties, default_properties )
{
  const Geometry::DagMCModelProperties default_properties( "dummy.h5m" );

  FRENSIE_CHECK( !default_properties.isFastIdLookupUsed() );
  FRENSIE_CHECK_EQUAL( default_properties.getTerminationCellPropertyName(),
                       "termination.cell" );
  FRENSIE_CHECK_EQUAL( default_properties.getReflectingSurfacePropertyName(),
                       "reflecting.surface" );
  FRENSIE_CHECK_EQUAL( default_properties.getMaterialPropertyName(),
                       "material" );
  FRENSIE_CHECK_EQUAL( default_properties.getDensityPropertyName(),
                       "density" );
  FRENSIE_CHECK_EQUAL( default_properties.getEstimatorPropertyName(),
                       "estimator" );
  FRENSIE_CHECK_EQUAL( default_properties.getSurfaceCurrentName(),
                       "surface.current" );
  FRENSIE_CHECK_EQUAL( default_properties.getSurfaceFluxName(),
                       "surface.flux" );
  FRENSIE_CHECK_EQUAL( default_properties.getCellPulseHeightName(),
                       "cell.pulse.height" );
  FRENSIE_CHECK_EQUAL( default_properties.getCellTrackLengthFluxName(),
                       "cell.tl.flux" );
  FRENSIE_CHECK_EQUAL( default_properties.getCellCollisionFluxName(),
                       "cell.c.flux" );
  FRENSIE_CHECK_EQUAL( default_properties.getPhotonName(), "p" );
  FRENSIE_CHECK_EQUAL( default_properties.getNeutronName(), "n" );
  FRENSIE_CHECK_EQUAL( default_properties.getElectronName(), "e" );
  FRENSIE_CHECK_EQUAL( default_properties.getAdjointPhotonName(), "p*" );
  FRENSIE_CHECK_EQUAL( default_properties.getAdjointNeutronName(), "n*" );
  FRENSIE_CHECK_EQUAL( default_properties.getAdjointElectronName(), "e*" );

  FRENSIE_CHECK_EQUAL( Geometry::DagMCModelProperties::getDefaultFilePath(), "" );
}

//---------------------------------------------------------------------------//
// Check that the file name can be returned
FRENSIE_UNIT_TEST( DagMCModelProperties, constructor )
{
  std::unique_ptr<const Geometry::DagMCModelProperties>
    properties( new Geometry::DagMCModelProperties( "test.h5m" ) );

  FRENSIE_CHECK_EQUAL( properties->getModelFileName(), "test.h5m" );
  FRENSIE_CHECK_EQUAL( properties->getModelFilePath(), "" );
  FRENSIE_CHECK_EQUAL( properties->getModelFileNameWithPath(), "test.h5m" );

  properties.reset( new Geometry::DagMCModelProperties( "test_dir/test.h5m" ) );

  FRENSIE_CHECK_EQUAL( properties->getModelFileName(), "test.h5m" );
  FRENSIE_CHECK_EQUAL( properties->getModelFilePath(), "test_dir" );
  FRENSIE_CHECK_EQUAL( properties->getModelFileNameWithPath(), "test_dir/test.h5m" );

  properties.reset( new Geometry::DagMCModelProperties( "/home/test_dir/test.h5m" ) );

  FRENSIE_CHECK_EQUAL( properties->getModelFileName(), "test.h5m" );
  FRENSIE_CHECK_EQUAL( properties->getModelFilePath(), "/home/test_dir" );
  FRENSIE_CHECK_EQUAL( properties->getModelFileNameWithPath(), "/home/test_dir/test.h5m" );
}

//---------------------------------------------------------------------------//
// Check that the id lookup type can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setIdLookup )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.useFastIdLookup();

  FRENSIE_CHECK( properties.isFastIdLookupUsed() );

  properties.useStandardIdLookup();

  FRENSIE_CHECK( !properties.isFastIdLookupUsed() );
}

//---------------------------------------------------------------------------//
// Check that the termination cell property name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setTerminationCellPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setTerminationCellPropertyName( "graveyard" );

  FRENSIE_CHECK_EQUAL( properties.getTerminationCellPropertyName(),
                       "graveyard" );
}

//---------------------------------------------------------------------------//
// Check that the reflecting surface property name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setReflectingSurfacePropertyName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setReflectingSurfacePropertyName( "spec.reflect" );

  FRENSIE_CHECK_EQUAL( properties.getReflectingSurfacePropertyName(),
                       "spec.reflect" );
}

//---------------------------------------------------------------------------//
// Check that the material property name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setMaterialPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setMaterialPropertyName( "mat" );

  FRENSIE_CHECK_EQUAL( properties.getMaterialPropertyName(), "mat" );
}

//---------------------------------------------------------------------------//
// Check that the density property name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setDensityPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setDensityPropertyName( "rho" );

  FRENSIE_CHECK_EQUAL( properties.getDensityPropertyName(), "rho" );
}

//---------------------------------------------------------------------------//
// Check that the estimator property name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setEstimatorPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setEstimatorPropertyName( "tally" );

  FRENSIE_CHECK_EQUAL( properties.getEstimatorPropertyName(), "tally" );
}

//---------------------------------------------------------------------------//
// Check that all of the property names can be returned
FRENSIE_UNIT_TEST( DagMCModelProperties, getPropertyNames )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );

  std::vector<std::string> property_names;

  properties.getPropertyNames( property_names );

  FRENSIE_CHECK_EQUAL( property_names.size(), 5 );
  FRENSIE_CHECK( std::find( property_names.begin(),
                          property_names.end(),
                          "termination.cell" ) != property_names.end() );
  FRENSIE_CHECK( std::find( property_names.begin(),
                          property_names.end(),
                          "reflecting.surface" ) != property_names.end() );
  FRENSIE_CHECK( std::find( property_names.begin(),
                          property_names.end(),
                          "material" ) != property_names.end() );
  FRENSIE_CHECK( std::find( property_names.begin(),
                          property_names.end(),
                          "density" ) != property_names.end() );
  FRENSIE_CHECK( std::find( property_names.begin(),
                          property_names.end(),
                          "estimator" ) != property_names.end() );
}

//---------------------------------------------------------------------------//
// Check that the surface current name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setSurfaceCurrentName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setSurfaceCurrentName( "surf.cur" );

  FRENSIE_CHECK_EQUAL( properties.getSurfaceCurrentName(), "surf.cur" );
}

//---------------------------------------------------------------------------//
// Check that the surface flux name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setSurfaceFluxName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setSurfaceFluxName( "surf.flux" );

  FRENSIE_CHECK_EQUAL( properties.getSurfaceFluxName(), "surf.flux" );
}

//---------------------------------------------------------------------------//
// Check that the cell pulse height name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setCellPulseHeightName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setCellPulseHeightName( "cell.ph" );

  FRENSIE_CHECK_EQUAL( properties.getCellPulseHeightName(), "cell.ph" );
}

//---------------------------------------------------------------------------//
// Check that the cell track-length flux name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setCellTrackLengthFluxName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setCellTrackLengthFluxName( "cell.tl" );

  FRENSIE_CHECK_EQUAL( properties.getCellTrackLengthFluxName(), "cell.tl" );
}

//---------------------------------------------------------------------------//
// Check that the cell collision flux name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setCellCollisionFluxName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setCellCollisionFluxName( "cell.c" );

  FRENSIE_CHECK_EQUAL( properties.getCellCollisionFluxName(), "cell.c" );
}

//---------------------------------------------------------------------------//
// Check if a cell estimator name is valid
FRENSIE_UNIT_TEST( DagMCModelProperties, isCellEstimatorNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.h5m" );

  FRENSIE_CHECK( properties.isCellEstimatorNameValid(
                                       properties.getCellPulseHeightName() ) );
  FRENSIE_CHECK( properties.isCellEstimatorNameValid(
                                   properties.getCellTrackLengthFluxName() ) );
  FRENSIE_CHECK( properties.isCellEstimatorNameValid(
                                     properties.getCellCollisionFluxName() ) );
  FRENSIE_CHECK( !properties.isCellEstimatorNameValid(
                                        properties.getSurfaceCurrentName() ) );
  FRENSIE_CHECK( !properties.isCellEstimatorNameValid(
                                           properties.getSurfaceFluxName() ) );
}

//---------------------------------------------------------------------------//
// Check if a surface estimator name is valid
FRENSIE_UNIT_TEST( DagMCModelProperties, isSurfaceEstimatorNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.h5m" );

  FRENSIE_CHECK( properties.isSurfaceEstimatorNameValid(
                                        properties.getSurfaceCurrentName() ) );
  FRENSIE_CHECK( properties.isSurfaceEstimatorNameValid(
                                           properties.getSurfaceFluxName() ) );
  FRENSIE_CHECK( !properties.isSurfaceEstimatorNameValid(
                                       properties.getCellPulseHeightName() ) );
  FRENSIE_CHECK( !properties.isSurfaceEstimatorNameValid(
                                   properties.getCellTrackLengthFluxName() ) );
  FRENSIE_CHECK( !properties.isSurfaceEstimatorNameValid(
                                     properties.getCellCollisionFluxName() ) );
}

//---------------------------------------------------------------------------//
// Check if an estimator name is valid
FRENSIE_UNIT_TEST( DagMCModelProperties, isEstimatorNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.h5m" );

  FRENSIE_CHECK( properties.isEstimatorNameValid(
                                        properties.getSurfaceCurrentName() ) );
  FRENSIE_CHECK( properties.isEstimatorNameValid(
                                           properties.getSurfaceFluxName() ) );
  FRENSIE_CHECK( properties.isEstimatorNameValid(
                                       properties.getCellPulseHeightName() ) );
  FRENSIE_CHECK( properties.isEstimatorNameValid(
                                   properties.getCellTrackLengthFluxName() ) );
  FRENSIE_CHECK( properties.isEstimatorNameValid(
                                     properties.getCellCollisionFluxName() ) );
  FRENSIE_CHECK( !properties.isEstimatorNameValid( "dummy" ) );
}

//---------------------------------------------------------------------------//
// Check if the estimator type can be returned
FRENSIE_UNIT_TEST( DagMCModelProperties, getEstimatorType )
{
  const Geometry::DagMCModelProperties properties( "test.h5m" );

  Geometry::EstimatorType estimator_type =
    properties.getEstimatorType( properties.getSurfaceCurrentName() );

  FRENSIE_CHECK_EQUAL( estimator_type,
                       Geometry::SURFACE_CURRENT_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getSurfaceFluxName() );

  FRENSIE_CHECK_EQUAL( estimator_type,
                       Geometry::SURFACE_FLUX_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getCellPulseHeightName() );

  FRENSIE_CHECK_EQUAL( estimator_type,
                       Geometry::CELL_PULSE_HEIGHT_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getCellTrackLengthFluxName() );

  FRENSIE_CHECK_EQUAL( estimator_type,
                       Geometry::CELL_TRACK_LENGTH_FLUX_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getCellCollisionFluxName() );

  FRENSIE_CHECK_EQUAL( estimator_type,
                       Geometry::CELL_COLLISION_FLUX_ESTIMATOR );
}

//---------------------------------------------------------------------------//
// Check that the photon name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setPhotonName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setPhotonName( "photon" );

  FRENSIE_CHECK_EQUAL( properties.getPhotonName(), "photon" );
}

//---------------------------------------------------------------------------//
// Check that the neutron name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setNeutronName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setNeutronName( "neutron" );

  FRENSIE_CHECK_EQUAL( properties.getNeutronName(), "neutron" );
}

//---------------------------------------------------------------------------//
// Check that the electron name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setElectronName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setElectronName( "electron" );

  FRENSIE_CHECK_EQUAL( properties.getElectronName(), "electron" );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photon name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setAdjointPhotonName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setAdjointPhotonName( "adjoint-photon" );

  FRENSIE_CHECK_EQUAL( properties.getAdjointPhotonName(), "adjoint-photon" );
}

//---------------------------------------------------------------------------//
// Check that the adjoint neutron name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setAdjointNeutronName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setAdjointNeutronName( "adjoint-neutron" );

  FRENSIE_CHECK_EQUAL( properties.getAdjointNeutronName(), "adjoint-neutron" );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electron name can be set
FRENSIE_UNIT_TEST( DagMCModelProperties, setAdjointElectronName )
{
  Geometry::DagMCModelProperties properties( "test.h5m" );
  properties.setAdjointElectronName( "adjoint-electron" );

  FRENSIE_CHECK_EQUAL( properties.getAdjointElectronName(),
                       "adjoint-electron" );
}

//---------------------------------------------------------------------------//
// Check if a particle name is valid
FRENSIE_UNIT_TEST( DagMCModelProperties, isParticleNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.h5m" );

  FRENSIE_CHECK( properties.isParticleNameValid( properties.getPhotonName() ) );
  FRENSIE_CHECK( properties.isParticleNameValid( properties.getNeutronName() ) );
  FRENSIE_CHECK( properties.isParticleNameValid( properties.getElectronName() ) );
  FRENSIE_CHECK( properties.isParticleNameValid( properties.getAdjointPhotonName() ) );
  FRENSIE_CHECK( properties.isParticleNameValid( properties.getAdjointNeutronName() ) );
  FRENSIE_CHECK( properties.isParticleNameValid( properties.getAdjointElectronName() ) );
  FRENSIE_CHECK( !properties.isParticleNameValid( "dummy" ) );
}

//---------------------------------------------------------------------------//
// Check that a particle type can be returned
FRENSIE_UNIT_TEST( DagMCModelProperties, getParticleType )
{
  const Geometry::DagMCModelProperties properties( "test.h5m" );

  Geometry::ParticleType particle_type =
    properties.getParticleType( properties.getPhotonName() );

  FRENSIE_CHECK_EQUAL( particle_type, Geometry::PHOTON );

  particle_type = properties.getParticleType( properties.getNeutronName() );

  FRENSIE_CHECK_EQUAL( particle_type, Geometry::NEUTRON );

  particle_type = properties.getParticleType( properties.getElectronName() );

  FRENSIE_CHECK_EQUAL( particle_type, Geometry::ELECTRON );

  particle_type =
    properties.getParticleType( properties.getAdjointPhotonName() );

  FRENSIE_CHECK_EQUAL( particle_type, Geometry::ADJOINT_PHOTON );

  particle_type =
    properties.getParticleType( properties.getAdjointNeutronName() );

  FRENSIE_CHECK_EQUAL( particle_type, Geometry::ADJOINT_NEUTRON );

  particle_type =
    properties.getParticleType( properties.getAdjointElectronName() );

  FRENSIE_CHECK_EQUAL( particle_type, Geometry::ADJOINT_ELECTRON );
}

//---------------------------------------------------------------------------//
// Check that the properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( DagMCModelProperties,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_dagmc_model_properties" );
  std::ostringstream archive_ostream;

  // Create and archive some properties
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Geometry::DagMCModelProperties properties( "dummy.h5m" );
    properties.setTerminationCellPropertyName( "graveyard" );
    properties.setReflectingSurfacePropertyName( "ref.surf" );
    properties.setMaterialPropertyName( "mat" );
    properties.setDensityPropertyName( "rho" );
    properties.setEstimatorPropertyName( "tally" );
    properties.setSurfaceCurrentName( "s.cur" );
    properties.setSurfaceFluxName( "s.flux" );
    properties.setCellPulseHeightName( "c.pulse.h" );
    properties.setCellTrackLengthFluxName( "c.tl.flux" );
    properties.setCellCollisionFluxName( "c.c.flux" );
    properties.setPhotonName( "gamma" );
    properties.setNeutronName( "neutral" );
    properties.setElectronName( "negatron" );
    properties.setAdjointPhotonName( "agamma" );
    properties.setAdjointNeutronName("aneutral" );
    properties.setAdjointElectronName( "anegatron" );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( properties ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Geometry::DagMCModelProperties properties( "?.h5m" );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( properties ) );

  FRENSIE_CHECK_EQUAL( properties.getModelFileName(), "dummy.h5m" );
  FRENSIE_CHECK( !properties.isFastIdLookupUsed() );
  FRENSIE_CHECK_EQUAL( properties.getTerminationCellPropertyName(),
                       "graveyard" );
  FRENSIE_CHECK_EQUAL( properties.getReflectingSurfacePropertyName(),
                       "ref.surf" );
  FRENSIE_CHECK_EQUAL( properties.getMaterialPropertyName(),
                       "mat" );
  FRENSIE_CHECK_EQUAL( properties.getDensityPropertyName(),
                       "rho" );
  FRENSIE_CHECK_EQUAL( properties.getEstimatorPropertyName(),
                       "tally" );
  FRENSIE_CHECK_EQUAL( properties.getSurfaceCurrentName(),
                       "s.cur" );
  FRENSIE_CHECK_EQUAL( properties.getSurfaceFluxName(),
                       "s.flux" );
  FRENSIE_CHECK_EQUAL( properties.getCellPulseHeightName(),
                       "c.pulse.h" );
  FRENSIE_CHECK_EQUAL( properties.getCellTrackLengthFluxName(),
                       "c.tl.flux" );
  FRENSIE_CHECK_EQUAL( properties.getCellCollisionFluxName(),
                       "c.c.flux" );
  FRENSIE_CHECK_EQUAL( properties.getPhotonName(), "gamma" );
  FRENSIE_CHECK_EQUAL( properties.getNeutronName(), "neutral" );
  FRENSIE_CHECK_EQUAL( properties.getElectronName(), "negatron" );
  FRENSIE_CHECK_EQUAL( properties.getAdjointPhotonName(), "agamma" );
  FRENSIE_CHECK_EQUAL( properties.getAdjointNeutronName(), "aneutral" );
  FRENSIE_CHECK_EQUAL( properties.getAdjointElectronName(), "anegatron" );
}

//---------------------------------------------------------------------------//
// end tstDagMCModelProperties.cpp
//---------------------------------------------------------------------------//
