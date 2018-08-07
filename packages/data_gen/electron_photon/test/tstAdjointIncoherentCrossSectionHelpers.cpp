//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointIncoherentCrossSectionHelpers.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent cross section helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentCrossSectionHelpers.cpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
FRENSIE_UNIT_TEST( AdjointIncoherentCrossSectionHelpers,
		   getEnergyOfMaxCrossSection )
{
  double energy = DataGen::getEnergyOfMaxCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.0009961013562397372, 1e-15 );

  energy = DataGen::getEnergyOfMaxCrossSection( 0.01 );

  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.0096233513926591, 1e-15 );

  energy = DataGen::getEnergyOfMaxCrossSection( 0.1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.0718705616632476, 1e-15 );

  energy = DataGen::getEnergyOfMaxCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.20350423413905203, 1e-15 );

  energy = DataGen::getEnergyOfMaxCrossSection( 10.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.24913409257587504, 1e-15 );

  energy = DataGen::getEnergyOfMaxCrossSection( 100.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.25484831899871596, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the energy can be tested for the presence of a max cross section
// value
FRENSIE_UNIT_TEST( AdjointIncoherentCrossSectionHelpers,
		   doesEnergyCorrespondToAMaxCrossSectionValue )
{
  FRENSIE_CHECK( DataGen::doesEnergyCorrespondToAMaxCrossSectionValue( 0.001 ) );

  FRENSIE_CHECK( DataGen::doesEnergyCorrespondToAMaxCrossSectionValue( 0.255 ) );

  FRENSIE_CHECK( !DataGen::doesEnergyCorrespondToAMaxCrossSectionValue( 0.255499455065 ) );

  FRENSIE_CHECK( !DataGen::doesEnergyCorrespondToAMaxCrossSectionValue( 10.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the max energy resulting in a max cross section value at an
// energy can be returned
FRENSIE_UNIT_TEST( AdjointIncoherentCrossSectionHelpers,
		   getMaxEnergyResultingInMaxCrossSectionValueAtEnergy )
{
  double max_energy = DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
								       0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy, 0.0010039292814978508, 1e-15 );

  max_energy = DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
									0.01 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy, 0.010407332879714635, 1e-15 );

  max_energy = DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
									 0.1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy, 0.16430890703649043, 1e-15 );

  max_energy = DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
							 0.25227662801581613 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy, 20.0, 1e-14 );

  max_energy = DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
								       0.255 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy, 130.44689223759954, 1e-15 );
}

//---------------------------------------------------------------------------//
// end tstAdjointIncoherentCrossSectionHelpers.cpp
//---------------------------------------------------------------------------//
