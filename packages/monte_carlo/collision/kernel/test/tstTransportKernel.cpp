//---------------------------------------------------------------------------//
//!
//! \file   tstTransportKernel.cpp
//! \author Alex Robinson
//! \brief  Transport kernel class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_TransportKernel.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::si::kelvin;
using boost::units::cgs::cubic_centimeter;
using Utility::Units::MeV;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_scattering_center_database_name;

std::shared_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase>
scattering_center_definition_database;

std::shared_ptr<MonteCarlo::MaterialDefinitionDatabase>
material_definition_database;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the optical path to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel, sampleOpticalPathLengthToNextCollisionSite )
{
  Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

  FRENSIE_CHECK_FLOATING_EQUALITY( MonteCarlo::TransportKernel::sampleOpticalPathLengthToNextCollisionSite(),
                                   0.6931471805599453,
                                   1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( MonteCarlo::TransportKernel::sampleOpticalPathLengthToNextCollisionSite(),
                                   0.2876820724517809,
                                   1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the simple distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleSimpleDistanceToNextCollisionSite_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                                     1.2454032586308799,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                                     0.5168890540558835,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleDistanceToNextCollisionSite_neutron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::NEUTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                                     1.2454032586308799,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                                     0.5168890540558835,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the simple distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleSimpleDistanceToNextCollisionSite_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                                     9.81307852954266,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                                     4.072795573128299,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleDistanceToNextCollisionSite_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::PHOTON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                                     9.81307852954266,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                                     4.072795573128299,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the simple distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleSimpleDistanceToNextCollisionSite_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ELECTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                                     1.7048714719550108e-05,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                                     7.075855923120492e-06,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( positron ),
                                     1.7048714719550335e-05,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( positron ),
                                     7.075855923120585e-06,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleDistanceToNextCollisionSite_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 1, -1.0/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ELECTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                                     1.7048714719550108e-05,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                                     7.075855923120492e-06,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( positron ),
                                     1.7048714719550335e-05,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( positron ),
                                     7.075855923120585e-06,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the simple distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleSimpleDistanceToNextCollisionSite_adjoint_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                                     3.2815500615235527,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                                     1.3619663312930712,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleDistanceToNextCollisionSite_adjoint_photon_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_PHOTON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                                     3.2815500615235527,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                                     1.3619663312930712,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the simple distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleSimpleDistanceToNextCollisionSite_adjoint_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_electron ),
                                     3.532383933300203197e-06,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleSimpleDistanceToNextCollisionSite( adjoint_electron ),
                                     1.466071794169682505e-06,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Check that the distance to the next collision site can be sampled
FRENSIE_UNIT_TEST( TransportKernel,
                   sampleDistanceToNextCollisionSite_adjoint_electron_mode )
{
  std::shared_ptr<const Geometry::Model> unfilled_model(
            new Geometry::InfiniteMediumModel( 1, 2, 1e24/cubic_centimeter ) );

  std::shared_ptr<MonteCarlo::SimulationProperties> properties( new MonteCarlo::SimulationProperties );
  properties->setParticleMode( MonteCarlo::ADJOINT_ELECTRON_MODE );

  std::shared_ptr<const MonteCarlo::FilledGeometryModel> filled_model;

  FRENSIE_CHECK_NO_THROW( filled_model.reset(
                                   new MonteCarlo::FilledGeometryModel(
                                        test_scattering_center_database_name,
                                        scattering_center_definition_database,
                                        material_definition_database,
                                        properties,
                                        unfilled_model,
                                        true ) ) );

  MonteCarlo::TransportKernel transport_kernel( filled_model );

  FRENSIE_REQUIRE( transport_kernel.isDefinedOnModel( *filled_model ) );

  {
    MonteCarlo::NeutronState neutron( 1ull );
    neutron.embedInModel( *filled_model );
    neutron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( neutron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PhotonState photon( 1ull );
    photon.embedInModel( *filled_model );
    photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::ElectronState electron( 1ull );
    electron.embedInModel( *filled_model );
    electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( electron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::PositronState positron( 1ull );
    positron.embedInModel( *filled_model );
    positron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( positron ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointPhotonState adjoint_photon( 1ull );
    adjoint_photon.embedInModel( *filled_model );
    adjoint_photon.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5} );

    FRENSIE_CHECK_EQUAL( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_photon ),
                         Utility::QuantityTraits<double>::inf() );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }

  {
    MonteCarlo::AdjointElectronState adjoint_electron( 1ull );
    adjoint_electron.embedInModel( *filled_model );
    adjoint_electron.setEnergy( 1.0 );

    Utility::RandomNumberGenerator::setFakeStream( {0.5, 0.25} );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_electron ),
                                     3.532383933300203197e-06,
                                     1e-15 );

    FRENSIE_CHECK_FLOATING_EQUALITY( transport_kernel.sampleDistanceToNextCollisionSite( adjoint_electron ),
                                     1.466071794169682505e-06,
                                     1e-15 );

    Utility::RandomNumberGenerator::unsetFakeStream();
  }
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Determine the database directory
    boost::filesystem::path database_path =
      test_scattering_center_database_name;

    // Load the database
    const Data::ScatteringCenterPropertiesDatabase database( database_path );

    const Data::AtomProperties& h_properties =
      database.getAtomProperties( 1001 );

    const Data::NuclideProperties& h1_properties =
      database.getNuclideProperties( 1001 );

    const Data::AtomProperties& o_properties =
      database.getAtomProperties( 8016 );

    const Data::NuclideProperties& o16_properties =
      database.getNuclideProperties( 8016 );

    // Set the sattering center definitions
    scattering_center_definition_database.reset(
                          new MonteCarlo::ScatteringCenterDefinitionDatabase );

    MonteCarlo::ScatteringCenterDefinition& h_definition =
      scattering_center_definition_database->createDefinition( "H1 @ 293.6K", 1001 );

    h_definition.setPhotoatomicDataProperties(
          h_properties.getSharedPhotoatomicDataProperties(
                       Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 ) );

    h_definition.setAdjointPhotoatomicDataProperties(
          h_properties.getSharedAdjointPhotoatomicDataProperties(
                Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 ) );

    h_definition.setElectroatomicDataProperties(
          h_properties.getSharedElectroatomicDataProperties(
                     Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

    h_definition.setAdjointElectroatomicDataProperties(
          h_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

    h_definition.setNuclearDataProperties(
          h1_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.53010E-08*MeV,
                                         true ) );

    MonteCarlo::ScatteringCenterDefinition& o_definition =
      scattering_center_definition_database->createDefinition( "O16 @ 293.6K", 8016 );

    o_definition.setPhotoatomicDataProperties(
          o_properties.getSharedPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE, 12 ) );

    o_definition.setElectroatomicDataProperties(
          o_properties.getSharedElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::ACE_EPR_FILE, 12 ) );

    o_definition.setNuclearDataProperties(
          o16_properties.getSharedNuclearDataProperties(
                                         Data::NuclearDataProperties::ACE_FILE,
                                         7,
                                         2.53010E-08*MeV,
                                         true ) );

    material_definition_database.reset(
                                  new MonteCarlo::MaterialDefinitionDatabase );

    // Set the material definitions
    material_definition_database->addDefinition(
                                               "Water @ 293.6K", 1,
                                               {"H1 @ 293.6K", "O16 @ 293.6K"},
                                               {2.0,           1.0});

    material_definition_database->addDefinition( "H1 @ 293.6K", 2,
                                                 {"H1 @ 293.6K"}, {1.0} );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTransportKernel.cpp
//---------------------------------------------------------------------------//
