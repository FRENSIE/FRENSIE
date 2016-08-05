//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the min table energy can be set
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, setMinTableEnergy )
{
  double min_table_energy =
    DataGen::AdjointIncoherentGridGenerator::getMinTableEnergy();

  TEST_EQUALITY_CONST( min_table_energy, 0.0001 );

  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.00001 );

  min_table_energy =
    DataGen::AdjointIncoherentGridGenerator::getMinTableEnergy();

  TEST_EQUALITY_CONST( min_table_energy, 0.00001 );
}

//---------------------------------------------------------------------------//
// Check that the max table energy can be set
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator, setMaxTableEnergy )
{
  double max_table_energy =
    DataGen::AdjointIncoherentGridGenerator::getMaxTableEnergy();

  TEST_EQUALITY_CONST( max_table_energy, 20.0 );

  double nudged_max_table_energy =
    DataGen::AdjointIncoherentGridGenerator::getNudgedMaxTableEnergy();

  TEST_FLOATING_EQUALITY( nudged_max_table_energy, 20.2, 1e-15 );

  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 30.0 );

  max_table_energy =
    DataGen::AdjointIncoherentGridGenerator::getMaxTableEnergy();

  TEST_EQUALITY_CONST( max_table_energy, 30.0 );

  nudged_max_table_energy =
    DataGen::AdjointIncoherentGridGenerator::getNudgedMaxTableEnergy();

  TEST_FLOATING_EQUALITY( nudged_max_table_energy, 30.3, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the energy to max energy nudge factor can be set
TEUCHOS_UNIT_TEST( AdjointIncoherentGridGenerator,
		   setEnergyToMaxEnergyNudgeFactor )
{
  double nudge_factor =
    DataGen::AdjointIncoherentGridGenerator::getEnergyToMaxEnergyNudgeFactor();

  TEST_EQUALITY_CONST( nudge_factor, 1e-6 );

  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor(
									1e-5 );

  nudge_factor =
    DataGen::AdjointIncoherentGridGenerator::getEnergyToMaxEnergyNudgeFactor();

  TEST_EQUALITY_CONST( nudge_factor, 1e-5 );
}

//---------------------------------------------------------------------------//
// end tstAdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
