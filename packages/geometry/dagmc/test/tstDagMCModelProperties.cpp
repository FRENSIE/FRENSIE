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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_DagMCModelProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the default properties are correct
TEUCHOS_UNIT_TEST( DagMCModelProperties, default_properties )
{
  const Geometry::DagMCModelProperties default_properties( "dummy.sat" );

  TEST_EQUALITY_CONST( default_properties.getFacetTolerance(), 1e-3 );
  TEST_ASSERT( !default_properties.isFastIdLookupUsed() );
  TEST_EQUALITY_CONST( default_properties.getTerminationCellPropertyName(),
                       "termination.cell" );
  TEST_EQUALITY_CONST( default_properties.getReflectingSurfacePropertyName(),
                       "reflecting.surface" );
  TEST_EQUALITY_CONST( default_properties.getMaterialPropertyName(),
                       "material" );
  TEST_EQUALITY_CONST( default_properties.getDensityPropertyName(),
                       "density" );
  TEST_EQUALITY_CONST( default_properties.getEstimatorPropertyName(),
                       "estimator" );
  TEST_EQUALITY_CONST( default_properties.getSurfaceCurrentName(),
                       "surface.current" );
  TEST_EQUALITY_CONST( default_properties.getSurfaceFluxName(),
                       "surface.flux" );
  TEST_EQUALITY_CONST( default_properties.getCellPulseHeightName(),
                       "cell.pulse.height" );
  TEST_EQUALITY_CONST( default_properties.getCellTrackLengthFluxName(),
                       "cell.tl.flux" );
  TEST_EQUALITY_CONST( default_properties.getCellCollisionFluxName(),
                       "cell.c.flux" );
}

//---------------------------------------------------------------------------//
// Check that the file name can be returned
TEUCHOS_UNIT_TEST( DagMCModelProperties, getModelFileName )
{
  const Geometry::DagMCModelProperties properties( "test.sat" );

  TEST_EQUALITY_CONST( properties.getModelFileName(), "test.sat" );
}

//---------------------------------------------------------------------------//
// Check that the facet tolerance can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setFacetTolerance )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setFacetTolerance( 5e-4 );

  TEST_EQUALITY_CONST( properties.getFacetTolerance(), 5e-4 );
}

//---------------------------------------------------------------------------//
// Check that the id lookup type can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setIdLookup )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.useFastIdLookup();

  TEST_ASSERT( properties.isFastIdLookupUsed() );

  properties.useStandardIdLookup();

  TEST_ASSERT( !properties.isFastIdLookupUsed() );
}

//---------------------------------------------------------------------------//
// Check that the termination cell property name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setTerminationCellPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setTerminationCellPropertyName( "graveyard" );

  TEST_EQUALITY_CONST( properties.getTerminationCellPropertyName(),
                       "graveyard" );
}

//---------------------------------------------------------------------------//
// Check that the reflecting surface property name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setReflectingSurfacePropertyName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setReflectingSurfacePropertyName( "spec.reflect" );

  TEST_EQUALITY_CONST( properties.getReflectingSurfacePropertyName(),
                       "spec.reflect" );
}

//---------------------------------------------------------------------------//
// Check that the material property name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setMaterialPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setMaterialPropertyName( "mat" );

  TEST_EQUALITY_CONST( properties.getMaterialPropertyName(), "mat" );
}

//---------------------------------------------------------------------------//
// Check that the density property name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setDensityPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setDensityPropertyName( "rho" );

  TEST_EQUALITY_CONST( properties.getDensityPropertyName(), "rho" );
}

//---------------------------------------------------------------------------//
// Check that the estimator property name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setEstimatorPropertyName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setEstimatorPropertyName( "tally" );

  TEST_EQUALITY_CONST( properties.getEstimatorPropertyName(), "tally" );
}

//---------------------------------------------------------------------------//
// Check that all of the property names can be returned
TEUCHOS_UNIT_TEST( DagMCModelProperties, getPropertyNames )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  
  std::vector<std::string> property_names;

  properties.getPropertyNames( property_names );

  TEST_EQUALITY_CONST( property_names.size(), 5 );
  TEST_ASSERT( std::find( property_names.begin(),
                          property_names.end(),
                          "termination.cell" ) != property_names.end() );
  TEST_ASSERT( std::find( property_names.begin(),
                          property_names.end(),
                          "reflecting.surface" ) != property_names.end() );
  TEST_ASSERT( std::find( property_names.begin(),
                          property_names.end(),
                          "material" ) != property_names.end() );
  TEST_ASSERT( std::find( property_names.begin(),
                          property_names.end(),
                          "density" ) != property_names.end() );
  TEST_ASSERT( std::find( property_names.begin(),
                          property_names.end(),
                          "estimator" ) != property_names.end() );
}

//---------------------------------------------------------------------------//
// Check that the surface current name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setSurfaceCurrentName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setSurfaceCurrentName( "surf.cur" );

  TEST_EQUALITY_CONST( properties.getSurfaceCurrentName(), "surf.cur" );
}

//---------------------------------------------------------------------------//
// Check that the surface flux name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setSurfaceFluxName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setSurfaceFluxName( "surf.flux" );

  TEST_EQUALITY_CONST( properties.getSurfaceFluxName(), "surf.flux" );
}

//---------------------------------------------------------------------------//
// Check that the cell pusle height name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setCellPulseHeightName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setCellPulseHeightName( "cell.ph" );

  TEST_EQUALITY_CONST( properties.getCellPulseHeightName(), "cell.ph" );
}

//---------------------------------------------------------------------------//
// Check that the cell track-length flux name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setCellTrackLengthFluxName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setCellTrackLengthFluxName( "cell.tl" );

  TEST_EQUALITY_CONST( properties.getCellTrackLengthFluxName(), "cell.tl" );
}

//---------------------------------------------------------------------------//
// Check that the cell collision flux name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setCellCollisionFluxName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setCellCollisionFluxName( "cell.c" );

  TEST_EQUALITY_CONST( properties.getCellCollisionFluxName(), "cell.c" );
}

//---------------------------------------------------------------------------//
// Check if a cell estimator name is valid
TEUCHOS_UNIT_TEST( DagMCModelProperties, isCellEstimatorNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.sat" );

  TEST_ASSERT( properties.isCellEstimatorNameValid(
                                       properties.getCellPulseHeightName() ) );
  TEST_ASSERT( properties.isCellEstimatorNameValid(
                                   properties.getCellTrackLengthFluxName() ) );
  TEST_ASSERT( properties.isCellEstimatorNameValid(
                                     properties.getCellCollisionFluxName() ) );
  TEST_ASSERT( !properties.isCellEstimatorNameValid(
                                        properties.getSurfaceCurrentName() ) );
  TEST_ASSERT( !properties.isCellEstimatorNameValid(
                                           properties.getSurfaceFluxName() ) );
}

//---------------------------------------------------------------------------//
// Check if a surface estimator name is valid
TEUCHOS_UNIT_TEST( DagMCModelProperties, isSurfaceEstimatorNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.sat" );

  TEST_ASSERT( properties.isSurfaceEstimatorNameValid(
                                        properties.getSurfaceCurrentName() ) );
  TEST_ASSERT( properties.isSurfaceEstimatorNameValid(
                                           properties.getSurfaceFluxName() ) );
  TEST_ASSERT( !properties.isSurfaceEstimatorNameValid(
                                       properties.getCellPulseHeightName() ) );
  TEST_ASSERT( !properties.isSurfaceEstimatorNameValid(
                                   properties.getCellTrackLengthFluxName() ) );
  TEST_ASSERT( !properties.isSurfaceEstimatorNameValid(
                                     properties.getCellCollisionFluxName() ) );
}

//---------------------------------------------------------------------------//
// Check if an estimator name is valid
TEUCHOS_UNIT_TEST( DagMCModelProperties, isEstimatorNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.sat" );

  TEST_ASSERT( properties.isEstimatorNameValid(
                                        properties.getSurfaceCurrentName() ) );
  TEST_ASSERT( properties.isEstimatorNameValid(
                                           properties.getSurfaceFluxName() ) );
  TEST_ASSERT( properties.isEstimatorNameValid(
                                       properties.getCellPulseHeightName() ) );
  TEST_ASSERT( properties.isEstimatorNameValid(
                                   properties.getCellTrackLengthFluxName() ) );
  TEST_ASSERT( properties.isEstimatorNameValid(
                                     properties.getCellCollisionFluxName() ) );
  TEST_ASSERT( !properties.isEstimatorNameValid( "dummy" ) );
}

//---------------------------------------------------------------------------//
// Check if the estimator type can be returned
TEUCHOS_UNIT_TEST( DagMCModelProperties, getEstimatorType )
{
  const Geometry::DagMCModelProperties properties( "test.sat" );

  Geometry::DagMCEstimatorType estimator_type =
    properties.getEstimatorType( properties.getSurfaceCurrentName() );

  TEST_EQUALITY_CONST( estimator_type,
                       Geometry::DAGMC_SURFACE_CURRENT_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getSurfaceFluxName() );

  TEST_EQUALITY_CONST( estimator_type,
                       Geometry::DAGMC_SURFACE_FLUX_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getCellPulseHeightName() );

  TEST_EQUALITY_CONST( estimator_type,
                       Geometry::DAGMC_CELL_PULSE_HEIGHT_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getCellTrackLengthFluxName() );

  TEST_EQUALITY_CONST( estimator_type,
                       Geometry::DAGMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR );

  estimator_type =
    properties.getEstimatorType( properties.getCellCollisionFluxName() );

  TEST_EQUALITY_CONST( estimator_type,
                       Geometry::DAGMC_CELL_COLLISION_FLUX_ESTIMATOR );
}

//---------------------------------------------------------------------------//
// Check that the photon name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setPhotonName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setPhotonName( "photon" );

  TEST_EQUALITY_CONST( properties.getPhotonName(), "photon" );
}

//---------------------------------------------------------------------------//
// Check that the neutron name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setNeutronName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setNeutronName( "neutron" );

  TEST_EQUALITY_CONST( properties.getNeutronName(), "neutron" );
}

//---------------------------------------------------------------------------//
// Check that the electron name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setElectronName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setElectronName( "electron" );

  TEST_EQUALITY_CONST( properties.getElectronName(), "electron" );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photon name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setAdjointPhotonName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setAdjointPhotonName( "adjoint-photon" );

  TEST_EQUALITY_CONST( properties.getAdjointPhotonName(), "adjoint-photon" );
}

//---------------------------------------------------------------------------//
// Check that the adjoint neutron name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setAdjointNeutronName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setAdjointNeutronName( "adjoint-neutron" );

  TEST_EQUALITY_CONST( properties.getAdjointNeutronName(), "adjoint-neutron" );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electron name can be set
TEUCHOS_UNIT_TEST( DagMCModelProperties, setAdjointElectronName )
{
  Geometry::DagMCModelProperties properties( "test.sat" );
  properties.setAdjointElectronName( "adjoint-electron" );

  TEST_EQUALITY_CONST( properties.getAdjointElectronName(),
                       "adjoint-electron" );
}

//---------------------------------------------------------------------------//
// Check if a particle name is valid
TEUCHOS_UNIT_TEST( DagMCModelProperties, isParticleNameValid )
{
  const Geometry::DagMCModelProperties properties( "test.sat" );

  TEST_ASSERT( properties.isParticleNameValid( properties.getPhotonName() ) );
  TEST_ASSERT( properties.isParticleNameValid( properties.getNeutronName() ) );
  TEST_ASSERT( properties.isParticleNameValid( properties.getElectronName() ) );
  TEST_ASSERT( properties.isParticleNameValid( properties.getAdjointPhotonName() ) );
  TEST_ASSERT( properties.isParticleNameValid( properties.getAdjointNeutronName() ) );
  TEST_ASSERT( properties.isParticleNameValid( properties.getAdjointElectronName() ) );
  TEST_ASSERT( !properties.isParticleNameValid( "dummy" ) );
}

//---------------------------------------------------------------------------//
// Check that a particle type can be returned
TEUCHOS_UNIT_TEST( DagMCModelProperties, getParticleType )
{
  const Geometry::DagMCModelProperties properties( "test.sat" );

  Geometry::DagMCParticleType particle_type =
    properties.getParticleType( properties.getPhotonName() );

  TEST_EQUALITY_CONST( particle_type, Geometry::DAGMC_PHOTON );

  particle_type = properties.getParticleType( properties.getNeutronName() );

  TEST_EQUALITY_CONST( particle_type, Geometry::DAGMC_NEUTRON );

  particle_type = properties.getParticleType( properties.getElectronName() );

  TEST_EQUALITY_CONST( particle_type, Geometry::DAGMC_ELECTRON );

  particle_type =
    properties.getParticleType( properties.getAdjointPhotonName() );

  TEST_EQUALITY_CONST( particle_type, Geometry::DAGMC_ADJOINT_PHOTON );

  particle_type =
    properties.getParticleType( properties.getAdjointNeutronName() );

  TEST_EQUALITY_CONST( particle_type, Geometry::DAGMC_ADJOINT_NEUTRON );

  particle_type =
    properties.getParticleType( properties.getAdjointElectronName() );

  TEST_EQUALITY_CONST( particle_type, Geometry::DAGMC_ADJOINT_ELECTRON );
}

//---------------------------------------------------------------------------//
// end tstDagMCModelProperties.cpp
//---------------------------------------------------------------------------//
