//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronGridGenerator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron grid generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectronGridGenerator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the min table energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator, setMinTableEnergy )
{
  double min_table_energy =
    DataGen::AdjointElectronGridGenerator::getMinTableEnergy();

  TEST_EQUALITY_CONST( min_table_energy, 0.00001 );

  DataGen::AdjointElectronGridGenerator::setMinTableEnergy( 0.0001 );

  min_table_energy =
    DataGen::AdjointElectronGridGenerator::getMinTableEnergy();

  TEST_EQUALITY_CONST( min_table_energy, 0.0001 );
}

//---------------------------------------------------------------------------//
// Check that the max table energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator, setMaxTableEnergy )
{
  double max_table_energy =
    DataGen::AdjointElectronGridGenerator::getMaxTableEnergy();

  TEST_EQUALITY_CONST( max_table_energy, 20.0 );

  DataGen::AdjointElectronGridGenerator::setMaxTableEnergy( 30.0 );

  max_table_energy =
    DataGen::AdjointElectronGridGenerator::getMaxTableEnergy();

  TEST_EQUALITY_CONST( max_table_energy, 30.0 );
}

//---------------------------------------------------------------------------//
// end tstAdjointElectronGridGenerator.cpp
//---------------------------------------------------------------------------//
