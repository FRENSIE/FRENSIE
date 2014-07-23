//---------------------------------------------------------------------------//
//!
//! \file   tstLabSystemConversionPolicy.cpp
//! \author Alex Bennett
//! \brief  Lab System Conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Facemc_UnitTestHarnessExtensions.hpp"
#include "Facemc_LabSystemConversionPolicy.hpp"


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( LabSystemConversionPolicy, convertToLabEnergy )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;

  double outgoing_lab_energy = Facemc::CMSystemConversionPolicy::convertToLabEnergy(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  TEST_FLOATING_EQUALITY(outgoing_lab_energy, 2.20711, 1e-5);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( LabSystemConversionPolicy, convertToLabAngleCosine )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;
  double outgoing_lab_energy = 2;

  double lab_scattering_angle_cosine = Facemc::CMSystemConversionPolicy::convertToLabAngleCosine(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             outgoing_lab_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  TEST_FLOATING_EQUALITY(lab_scattering_angle_cosine, 0.853553, 1e-6);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( LabSystemConversionPolicy, convertToSysEnergy )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;

  double outgoing_lab_energy = Facemc::LabSystemConversionPolicy::convertToLabEnergy(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  TEST_FLOATING_EQUALITY(outgoing_lab_energy, 1.0, 1e-15);
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( LabSystemConversionPolicy, convertToSysAngleCosine )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;
  double outgoing_lab_energy = 2;

  double lab_scattering_angle_cosine = Facemc::LabSystemConversionPolicy::convertToLabAngleCosine(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             outgoing_lab_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  TEST_FLOATING_EQUALITY(lab_scattering_angle_cosine, 0.5, 1e-15);
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}


//---------------------------------------------------------------------------//
// tstLabSystemConversionPolicy.cpp
//---------------------------------------------------------------------------//
