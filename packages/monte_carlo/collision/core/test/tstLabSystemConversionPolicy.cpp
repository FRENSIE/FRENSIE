//---------------------------------------------------------------------------//
//!
//! \file   tstLabSystemConversionPolicy.cpp
//! \author Alex Bennett
//! \brief  Lab System Conversion policy unit tests
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( LabSystemConversionPolicy, convertToLabEnergy )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;

  double outgoing_lab_energy = MonteCarlo::CMSystemConversionPolicy::convertToLabEnergy(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  FRENSIE_CHECK_FLOATING_EQUALITY(outgoing_lab_energy, 2.20711, 1e-5);
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( LabSystemConversionPolicy, convertToLabAngleCosine )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;
  double outgoing_lab_energy = 2;

  double lab_scattering_angle_cosine = MonteCarlo::CMSystemConversionPolicy::convertToLabAngleCosine(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             outgoing_lab_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  FRENSIE_CHECK_FLOATING_EQUALITY(lab_scattering_angle_cosine, 0.853553, 1e-6);
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( LabSystemConversionPolicy, convertToSysEnergy )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;

  double outgoing_lab_energy = MonteCarlo::LabSystemConversionPolicy::convertToLabEnergy(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  FRENSIE_CHECK_FLOATING_EQUALITY(outgoing_lab_energy, 1.0, 1e-15);
}

//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( LabSystemConversionPolicy, convertToSysAngleCosine )
{
  double incident_energy = 2;
  double outgoing_sys_energy = 1;
  double sys_scattering_angle_cosine = 0.5;
  double atomic_weight_ratio = 1;
  double outgoing_lab_energy = 2;

  double lab_scattering_angle_cosine = MonteCarlo::LabSystemConversionPolicy::convertToLabAngleCosine(
                                             incident_energy,
                                             outgoing_sys_energy,
                                             outgoing_lab_energy,
                                             sys_scattering_angle_cosine,
                                             atomic_weight_ratio);

  FRENSIE_CHECK_FLOATING_EQUALITY(lab_scattering_angle_cosine, 0.5, 1e-15);
}

//---------------------------------------------------------------------------//
// tstLabSystemConversionPolicy.cpp
//---------------------------------------------------------------------------//
