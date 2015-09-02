//---------------------------------------------------------------------------//
//!
//! \file   tstXsdirEntryFactory.cpp
//! \author Alex Robinson
//! \brief  Xsdir entry factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_XsdirEntryFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//
const std::string line_a( " 1001.70c 0.999167 endf70a 0 1 1 8177 0 0 2.5301E-08" );
const std::string line_b( " smeth.60t  0.999170 sab2002 0 1 823113 53047 0 0 1.89580E-09" );

const std::string line_c( "  1000.12p      0.999242  mcplib12 0 1        1     1898 0 0 0.00000E+00" );

const std::string line_d( "  1002.24u     1.996300 data/la150u 0 1 216233   3686  0 0 0.000E+00" );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the xsdir entry can be created
TEUCHOS_UNIT_TEST( XsdirEntryFactory, createEntry )
{
  Teuchos::Array<std::string> entry_tokens;

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_a, entry_tokens );

  Teuchos::RCP<DataGen::XsdirEntry> entry;

  DataGen::XsdirEntryFactory::createEntry( entry_tokens, entry );

  TEST_EQUALITY_CONST( entry->getTableType(),
		       DataGen::XsdirEntry::CONTINUOUS_ENERGY_NEUTRON_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_b, entry_tokens );

  DataGen::XsdirEntryFactory::createEntry( entry_tokens, entry );

  TEST_EQUALITY_CONST( entry->getTableType(),
		       DataGen::XsdirEntry::S_ALPHA_BETA_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_c, entry_tokens );

  DataGen::XsdirEntryFactory::createEntry( entry_tokens, entry );

  TEST_EQUALITY_CONST( entry->getTableType(),
		       DataGen::XsdirEntry::ELECTRON_PHOTON_RELAXATION_TABLE );

  DataGen::XsdirEntry::extractTableTokensFromXsdirLine( line_d, entry_tokens );

  DataGen::XsdirEntryFactory::createEntry( entry_tokens, entry );

  TEST_EQUALITY_CONST( entry->getTableType(),
		       DataGen::XsdirEntry::PHOTONUCLEAR_TABLE );

}

//---------------------------------------------------------------------------//
// end tstXsdirEntryFactory.cpp
//---------------------------------------------------------------------------//
