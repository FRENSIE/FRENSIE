//---------------------------------------------------------------------------//
//!
//! \file   tstXSSElectronDataExtractor.cpp
//! \author Luke Kersting
//! \brief  XSS electron condensed history data extractor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSElectronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<Data::XSSElectronDataExtractor> b_xss_data_extractor;
std::shared_ptr<Data::XSSElectronDataExtractor> pb_xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSElectronDataExtractor can extract the atomic number
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractAtomicNumber )
{
  FRENSIE_CHECK_EQUAL( b_xss_data_extractor->extractAtomicNumber(), 5 );
  FRENSIE_CHECK_EQUAL( pb_xss_data_extractor->extractAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the K edge can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractKEdge )
{
  double k_edge =
    b_xss_data_extractor->extractKEdge();

  FRENSIE_CHECK_EQUAL( k_edge, 1.880000000000E-01 );

  k_edge = pb_xss_data_extractor->extractKEdge();

  FRENSIE_CHECK_EQUAL( k_edge, 8.800400100000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the Auger electron emission energy can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractAugerEmissionEnergy )
{
  double auger_emission_energy =
    b_xss_data_extractor->extractAugerEmissionEnergy();

  FRENSIE_CHECK_EQUAL( auger_emission_energy, 1.880000000000E-01 );

  auger_emission_energy = pb_xss_data_extractor->extractAugerEmissionEnergy();

  FRENSIE_CHECK_EQUAL( auger_emission_energy, 5.860600000000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the radiation stopping power interpolation data block can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractStoppingPowersBlock )
{
  Utility::ArrayView<const double> stopping_powers_block =
    b_xss_data_extractor->extractStoppingPowersBlock();

  FRENSIE_CHECK_EQUAL( stopping_powers_block.size(), 171 );
  FRENSIE_CHECK_EQUAL( stopping_powers_block.front(), 1.000000000000E+04 );
  FRENSIE_CHECK_EQUAL( stopping_powers_block.back(), 1.030000000000E-03 );

  stopping_powers_block = pb_xss_data_extractor->extractStoppingPowersBlock();

  FRENSIE_CHECK_EQUAL( stopping_powers_block.size(), 171 );
  FRENSIE_CHECK_EQUAL( stopping_powers_block.front(), 1.000000000000E+04 );
  FRENSIE_CHECK_EQUAL( stopping_powers_block.back(), 2.250000000000E-03 );
}

//---------------------------------------------------------------------------//
// Check that the Mott scattering correction points data block can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractMottScatteringCorrectionBlock )
{
  Utility::ArrayView<const double> mott_scattering_block =
    b_xss_data_extractor->extractMottScatteringCorrectionBlock();

  FRENSIE_CHECK_EQUAL( mott_scattering_block.size(), 108 );
  FRENSIE_CHECK_EQUAL( mott_scattering_block.front(), 1.000000000000E+03 );
  FRENSIE_CHECK_EQUAL( mott_scattering_block.back(), 1.003430000000E+00 );

  mott_scattering_block = pb_xss_data_extractor->extractMottScatteringCorrectionBlock();

  FRENSIE_CHECK_EQUAL( mott_scattering_block.size(), 108 );
  FRENSIE_CHECK_EQUAL( mott_scattering_block.front(), 1.000000000000E+03 );
  FRENSIE_CHECK_EQUAL( mott_scattering_block.back(), 1.480320000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the Riley scattering cross section data block can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractRileyBlock )
{
  Utility::ArrayView<const double> riley_block =
    b_xss_data_extractor->extractRileyBlock();

  FRENSIE_CHECK_EQUAL( riley_block.size(), 126 );
  FRENSIE_CHECK_EQUAL( riley_block.front(), 2.560000000000E+02 );
  FRENSIE_CHECK_EQUAL( riley_block.back(), 6.056827290000E-03 );

  riley_block = pb_xss_data_extractor->extractRileyBlock();

  FRENSIE_CHECK_EQUAL( riley_block.size(), 126 );
  FRENSIE_CHECK_EQUAL( riley_block.front(), 2.560000000000E+02 );
  FRENSIE_CHECK_EQUAL( riley_block.back(), 1.698662370000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the Bremsstrahlung interpolation data block can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractBremsstrahlungInterpolationBlock )
{
  Utility::ArrayView<const double> bremsstrahlung_Interpolation =
    b_xss_data_extractor->extractBremsstrahlungInterpolationBlock();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_Interpolation.size(), 1797 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_Interpolation.front(), 1.000000000000E-03 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_Interpolation.back(), 2.314500000000E-04 );

  bremsstrahlung_Interpolation =
    pb_xss_data_extractor->extractBremsstrahlungInterpolationBlock();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_Interpolation.size(), 1797 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_Interpolation.front(), 1.000000000000E-03 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_Interpolation.back(), 1.323420000000E-03 );
}

//---------------------------------------------------------------------------//
// Check that the photon to electron energy ratios for spectrum can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractEnergySpectrumRatios )
{
  Utility::ArrayView<const double> rkt =
    b_xss_data_extractor->extractEnergySpectrumRatios();

  FRENSIE_CHECK_EQUAL( rkt.size(), 89 );
  FRENSIE_CHECK_EQUAL( rkt.front(), 1.0000000000000E-06 );
  FRENSIE_CHECK_EQUAL( rkt.back(), 1.000000000000E+00 );

  rkt = pb_xss_data_extractor->extractEnergySpectrumRatios();

  FRENSIE_CHECK_EQUAL( rkt.size(), 89 );
  FRENSIE_CHECK_EQUAL( rkt.front(), 1.000000000000E-06 );
  FRENSIE_CHECK_EQUAL( rkt.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that photon to electron energy ratios for angular can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractEnergyAngularRatios )
{
  Utility::ArrayView<const double> rka =
    b_xss_data_extractor->extractEnergyAngularRatios();

  FRENSIE_CHECK_EQUAL( rka.size(), 34 );
  FRENSIE_CHECK_EQUAL( rka.front(), 9.999000000000E-01 );
  FRENSIE_CHECK_EQUAL( rka.back(), 1.000000000000E-06 );

  rka = pb_xss_data_extractor->extractEnergyAngularRatios();

  FRENSIE_CHECK_EQUAL( rka.size(), 34 );
  FRENSIE_CHECK_EQUAL( rka.front(), 9.999000000000E-01 );
  FRENSIE_CHECK_EQUAL( rka.back(), 1.000000000000E-06 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractOccupationNumbers )
{
  Utility::ArrayView<const double> occupation_number =
    b_xss_data_extractor->extractOccupationNumbers();

  FRENSIE_CHECK_EQUAL( occupation_number.size(), 2 );
  FRENSIE_CHECK_EQUAL( occupation_number.front(), 2.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( occupation_number.back(), -3.000000000000E+00 );


  occupation_number = pb_xss_data_extractor->extractOccupationNumbers();

  FRENSIE_CHECK_EQUAL( occupation_number.size(), 23 );
  FRENSIE_CHECK_EQUAL( occupation_number.front(), 2.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( occupation_number.back(), -2.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the binding energy can be extracted
FRENSIE_UNIT_TEST( XSSElectronDataExtractor, extractBindingEnergy )
{
  Utility::ArrayView<const double> binding_energy =
    b_xss_data_extractor->extractBindingEnergy();

  FRENSIE_CHECK_EQUAL( binding_energy.size(), 2 );
  FRENSIE_CHECK_EQUAL( binding_energy.front(), 1.920000000000E+02 );
  FRENSIE_CHECK_EQUAL( binding_energy.back(), 1.138600000000E+01 );

  binding_energy = pb_xss_data_extractor->extractBindingEnergy();

  FRENSIE_CHECK_EQUAL( binding_energy.size(), 23 );
  FRENSIE_CHECK_EQUAL( binding_energy.front(), 8.801100000000E+04 );
  FRENSIE_CHECK_EQUAL( binding_energy.back(), 7.420000000000E+00 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string pb_ace_file_name, pb_ace_table_name;
std::string b_ace_file_name, b_ace_table_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "pb_ace_file",
                                        pb_ace_file_name, "",
                                        "Test Pb ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "pb_ace_table",
                                        pb_ace_table_name, "",
                                        "Test Pb ACE table name in ACE file" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "b_ace_file",
                                        b_ace_file_name, "",
                                        "Test B ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "b_ace_table",
                                        b_ace_table_name, "",
                                        "Test B ACE table name in ACE file" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                                 new Data::ACEFileHandler( pb_ace_file_name,
                                                           pb_ace_table_name,
                                                           1u ) );

  pb_xss_data_extractor.reset(
      new Data::XSSElectronDataExtractor( ace_file_handler->getTableNXSArray(),
                                          ace_file_handler->getTableJXSArray(),
                                          ace_file_handler->getTableXSSArray() ) );

  ace_file_handler.reset( new Data::ACEFileHandler( b_ace_file_name,
                                                    b_ace_table_name,
                                                    1u ) );

  b_xss_data_extractor.reset(
      new Data::XSSElectronDataExtractor( ace_file_handler->getTableNXSArray(),
                                          ace_file_handler->getTableJXSArray(),
                                          ace_file_handler->getTableXSSArray() ) );

}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSElectronDataExtractor.cpp
//---------------------------------------------------------------------------//
