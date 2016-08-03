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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSElectronDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSElectronDataExtractor> b_xss_data_extractor;
Teuchos::RCP<Data::XSSElectronDataExtractor> pb_xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSElectronDataExtractor can extract the atomic number
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractAtomicNumber )
{
  TEST_EQUALITY_CONST( b_xss_data_extractor->extractAtomicNumber(), 5 );
  TEST_EQUALITY_CONST( pb_xss_data_extractor->extractAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the K edge can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractKEdge )
{
  double k_edge =
    b_xss_data_extractor->extractKEdge();

  TEST_EQUALITY_CONST( k_edge, 1.880000000000E-01 );

  k_edge = pb_xss_data_extractor->extractKEdge();

  TEST_EQUALITY_CONST( k_edge, 8.800400100000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the Auger electron emission energy can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractAugerEmissionEnergy )
{
  double auger_emission_energy =
    b_xss_data_extractor->extractAugerEmissionEnergy();

  TEST_EQUALITY_CONST( auger_emission_energy, 1.880000000000E-01 );

  auger_emission_energy = pb_xss_data_extractor->extractAugerEmissionEnergy();

  TEST_EQUALITY_CONST( auger_emission_energy, 5.860600000000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the radiation stopping power interpolation data block can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractStoppingPowersBlock )
{
  Teuchos::ArrayView<const double> stopping_powers_block =
    b_xss_data_extractor->extractStoppingPowersBlock();

  TEST_EQUALITY_CONST( stopping_powers_block.size(), 171 );
  TEST_EQUALITY_CONST( stopping_powers_block.front(), 1.000000000000E+04 );
  TEST_EQUALITY_CONST( stopping_powers_block.back(), 1.030000000000E-03 );

  stopping_powers_block = pb_xss_data_extractor->extractStoppingPowersBlock();

  TEST_EQUALITY_CONST( stopping_powers_block.size(), 171 );
  TEST_EQUALITY_CONST( stopping_powers_block.front(), 1.000000000000E+04 );
  TEST_EQUALITY_CONST( stopping_powers_block.back(), 2.250000000000E-03 );
}

//---------------------------------------------------------------------------//
// Check that the Mott scattering correction points data block can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractMottScatteringCorrectionBlock )
{
  Teuchos::ArrayView<const double> mott_scattering_block =
    b_xss_data_extractor->extractMottScatteringCorrectionBlock();

  TEST_EQUALITY_CONST( mott_scattering_block.size(), 108 );
  TEST_EQUALITY_CONST( mott_scattering_block.front(), 1.000000000000E+03 );
  TEST_EQUALITY_CONST( mott_scattering_block.back(), 1.003430000000E+00 );

  mott_scattering_block = pb_xss_data_extractor->extractMottScatteringCorrectionBlock();

  TEST_EQUALITY_CONST( mott_scattering_block.size(), 108 );
  TEST_EQUALITY_CONST( mott_scattering_block.front(), 1.000000000000E+03 );
  TEST_EQUALITY_CONST( mott_scattering_block.back(), 1.480320000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the Riley scattering cross section data block can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractRileyBlock )
{
  Teuchos::ArrayView<const double> riley_block =
    b_xss_data_extractor->extractRileyBlock();

  TEST_EQUALITY_CONST( riley_block.size(), 126 );
  TEST_EQUALITY_CONST( riley_block.front(), 2.560000000000E+02 );
  TEST_EQUALITY_CONST( riley_block.back(), 6.056827290000E-03 );

  riley_block = pb_xss_data_extractor->extractRileyBlock();

  TEST_EQUALITY_CONST( riley_block.size(), 126 );
  TEST_EQUALITY_CONST( riley_block.front(), 2.560000000000E+02 );
  TEST_EQUALITY_CONST( riley_block.back(), 1.698662370000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the Bremsstrahlung interpolation data block can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractBremsstrahlungInterpolationBlock )
{
  Teuchos::ArrayView<const double> bremsstrahlung_Interpolation =
    b_xss_data_extractor->extractBremsstrahlungInterpolationBlock();

  TEST_EQUALITY_CONST( bremsstrahlung_Interpolation.size(), 1797 );
  TEST_EQUALITY_CONST( bremsstrahlung_Interpolation.front(), 1.000000000000E-03 );
  TEST_EQUALITY_CONST( bremsstrahlung_Interpolation.back(), 2.314500000000E-04 );

  bremsstrahlung_Interpolation =
    pb_xss_data_extractor->extractBremsstrahlungInterpolationBlock();

  TEST_EQUALITY_CONST( bremsstrahlung_Interpolation.size(), 1797 );
  TEST_EQUALITY_CONST( bremsstrahlung_Interpolation.front(), 1.000000000000E-03 );
  TEST_EQUALITY_CONST( bremsstrahlung_Interpolation.back(), 1.323420000000E-03 );
}

//---------------------------------------------------------------------------//
// Check that the photon to electron energy ratios for spectrum can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractEnergySpectrumRatios )
{
  Teuchos::ArrayView<const double> rkt =
    b_xss_data_extractor->extractEnergySpectrumRatios();

  TEST_EQUALITY_CONST( rkt.size(), 89 );
  TEST_EQUALITY_CONST( rkt.front(), 1.0000000000000E-06 );
  TEST_EQUALITY_CONST( rkt.back(), 1.000000000000E+00 );

  rkt = pb_xss_data_extractor->extractEnergySpectrumRatios();

  TEST_EQUALITY_CONST( rkt.size(), 89 );
  TEST_EQUALITY_CONST( rkt.front(), 1.000000000000E-06 );
  TEST_EQUALITY_CONST( rkt.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that photon to electron energy ratios for angular can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractEnergyAngularRatios )
{
  Teuchos::ArrayView<const double> rka =
    b_xss_data_extractor->extractEnergyAngularRatios();

  TEST_EQUALITY_CONST( rka.size(), 34 );
  TEST_EQUALITY_CONST( rka.front(), 9.999000000000E-01 );
  TEST_EQUALITY_CONST( rka.back(), 1.000000000000E-06 );

  rka = pb_xss_data_extractor->extractEnergyAngularRatios();

  TEST_EQUALITY_CONST( rka.size(), 34 );
  TEST_EQUALITY_CONST( rka.front(), 9.999000000000E-01 );
  TEST_EQUALITY_CONST( rka.back(), 1.000000000000E-06 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractOccupationNumbers )
{
  Teuchos::ArrayView<const double> occupation_number =
    b_xss_data_extractor->extractOccupationNumbers();

  TEST_EQUALITY_CONST( occupation_number.size(), 2 );
  TEST_EQUALITY_CONST( occupation_number.front(), 2.000000000000E+00 );
  TEST_EQUALITY_CONST( occupation_number.back(), -3.000000000000E+00 );


  occupation_number = pb_xss_data_extractor->extractOccupationNumbers();

  TEST_EQUALITY_CONST( occupation_number.size(), 23 );
  TEST_EQUALITY_CONST( occupation_number.front(), 2.000000000000E+00 );
  TEST_EQUALITY_CONST( occupation_number.back(), -2.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the binding energy can be extracted
TEUCHOS_UNIT_TEST( XSSElectronDataExtractor, extractBindingEnergy )
{
  Teuchos::ArrayView<const double> binding_energy =
    b_xss_data_extractor->extractBindingEnergy();

  TEST_EQUALITY_CONST( binding_energy.size(), 2 );
  TEST_EQUALITY_CONST( binding_energy.front(), 1.920000000000E+02 );
  TEST_EQUALITY_CONST( binding_energy.back(), 1.138600000000E+01 );

  binding_energy = pb_xss_data_extractor->extractBindingEnergy();

  TEST_EQUALITY_CONST( binding_energy.size(), 23 );
  TEST_EQUALITY_CONST( binding_energy.front(), 8.801100000000E+04 );
  TEST_EQUALITY_CONST( binding_energy.back(), 7.420000000000E+00 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string pb_ace_file_name, pb_ace_table_name;
  std::string b_ace_file_name, b_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "pb_ace_file",
		 &pb_ace_file_name,
		 "Test Pb ACE file name" );
  clp.setOption( "pb_ace_table",
		 &pb_ace_table_name,
		 "Test Pb ACE table name in ACE file" );
  clp.setOption( "b_ace_file",
                 &b_ace_file_name,
		 "Test B ACE file name" );
  clp.setOption( "b_ace_table",
		 &b_ace_table_name,
		 "Test B ACE table name in ACE file" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize ace file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
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

  // Clear setup data
  ace_file_handler.reset();

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstXSSElectronDataExtractor.cpp
//---------------------------------------------------------------------------//
