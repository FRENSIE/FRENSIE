//---------------------------------------------------------------------------//
//!
//! \file   tstXSSEPRDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS photoatomic data extractor class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::MeV;
using Utility::Units::barn;
using Utility::Units::barns;

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::shared_ptr<Data::XSSEPRDataExtractor> b_xss_data_extractor;
std::shared_ptr<Data::XSSEPRDataExtractor> pb_xss_data_extractor;
std::shared_ptr<Data::XSSEPRDataExtractor> pb_erp14_xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can extract the atomic number
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractAtomicNumber )
{
  TEST_EQUALITY_CONST( b_xss_data_extractor->extractAtomicNumber(), 5 );
  TEST_EQUALITY_CONST( pb_xss_data_extractor->extractAtomicNumber(), 82 );
  TEST_EQUALITY_CONST( pb_erp14_xss_data_extractor->extractAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if old fluorescence data
// is present
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, hasOldFluorescenceData )
{
  TEST_ASSERT( !b_xss_data_extractor->hasOldFluorescenceData() );
  TEST_ASSERT( pb_xss_data_extractor->hasOldFluorescenceData() );
  TEST_ASSERT( pb_erp14_xss_data_extractor->hasOldFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if fluorescence data is
// present
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, hasFluorescenceData )
{
  TEST_ASSERT( !b_xss_data_extractor->hasFluorescenceData() );
  TEST_ASSERT( pb_xss_data_extractor->hasFluorescenceData() );
  TEST_ASSERT( pb_erp14_xss_data_extractor->hasFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if the file is version eprdata14
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, isEPRVersion14 )
{
  TEST_ASSERT( !b_xss_data_extractor->isEPRVersion14() );
  TEST_ASSERT( !pb_xss_data_extractor->isEPRVersion14() );
  TEST_ASSERT( pb_erp14_xss_data_extractor->isEPRVersion14() );
}

//---------------------------------------------------------------------------//
// Check that the ESZG block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractESZGBlock )
{
  Utility::ArrayView<const double> eszg_block =
    b_xss_data_extractor->extractESZGBlock();

  FRENSIE_CHECK_EQUAL( eszg_block.size(), 5880 );
  FRENSIE_CHECK_EQUAL( eszg_block.front(), -1.381551055796E+01 );
  FRENSIE_CHECK_EQUAL( eszg_block.back(), -1.342622032664E+00 );

  eszg_block = pb_xss_data_extractor->extractESZGBlock();

  TEST_EQUALITY_CONST( eszg_block.size(), 15880 );
  TEST_EQUALITY_CONST( eszg_block.front(), -1.381551055796E+01 );
  TEST_EQUALITY_CONST( eszg_block.back(), 3.718032834377E+00 );

  eszg_block = pb_erp14_xss_data_extractor->extractESZGBlock();

  TEST_EQUALITY_CONST( eszg_block.size(), 15880 );
  TEST_EQUALITY_CONST( eszg_block.front(), -1.381551055796E+01 );
  TEST_EQUALITY_CONST( eszg_block.back(), 3.718032834377E+00 );
}

//---------------------------------------------------------------------------//
// Check that the photon energy grid can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractPhotonEnergyGrid )
{
  Utility::ArrayView<const double> photon_energy_grid =
    b_xss_data_extractor->extractPhotonEnergyGrid();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 1176 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), -1.381551055796E+01 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.151292546497E+01 );

  photon_energy_grid = pb_xss_data_extractor->extractPhotonEnergyGrid();

  TEST_EQUALITY_CONST( photon_energy_grid.size(), 3176 );
  TEST_EQUALITY_CONST( photon_energy_grid.front(), -1.381551055796E+01 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.151292546497E+01 );

  photon_energy_grid = pb_erp14_xss_data_extractor->extractPhotonEnergyGrid();

  TEST_EQUALITY_CONST( photon_energy_grid.size(), 3176 );
  TEST_EQUALITY_CONST( photon_energy_grid.front(), -1.381551055796E+01 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.151292546497E+01 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractIncoherentCrossSection )
{
  Utility::ArrayView<const double> incoherent_cs =
    b_xss_data_extractor->extractIncoherentCrossSection();

  FRENSIE_CHECK_EQUAL( incoherent_cs.size(), 1176 );
  FRENSIE_CHECK_EQUAL( incoherent_cs.front(), -1.489417317132E+01 );
  FRENSIE_CHECK_EQUAL( incoherent_cs.back(), -9.370438704073E+00 );

  incoherent_cs = pb_xss_data_extractor->extractIncoherentCrossSection();

  TEST_EQUALITY_CONST( incoherent_cs.size(), 3176 );
  TEST_EQUALITY_CONST( incoherent_cs.front(), -1.338724079720E+01 );
  TEST_EQUALITY_CONST( incoherent_cs.back(), -6.573285045032E+00 );

  incoherent_cs = pb_erp14_xss_data_extractor->extractIncoherentCrossSection();

  TEST_EQUALITY_CONST( incoherent_cs.size(), 3176 );
  TEST_EQUALITY_CONST( incoherent_cs.front(), -1.338724079720E+01 );
  TEST_EQUALITY_CONST( incoherent_cs.back(), -6.573285045032E+00 );
}

//---------------------------------------------------------------------------//
// Check that the coherent cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractCoherentCrossSection )
{
  Utility::ArrayView<const double> coherent_cs =
    b_xss_data_extractor->extractCoherentCrossSection();

  FRENSIE_CHECK_EQUAL( coherent_cs.size(), 1176 );
  FRENSIE_CHECK_EQUAL( coherent_cs.front(), -7.167603012571E+00 );
  FRENSIE_CHECK_EQUAL( coherent_cs.back(), -3.066204487218E+01 );

  coherent_cs = pb_xss_data_extractor->extractCoherentCrossSection();

  TEST_EQUALITY_CONST( coherent_cs.size(), 3176 );
  TEST_EQUALITY_CONST( coherent_cs.front(), -5.071403810640E+00 );
  TEST_EQUALITY_CONST( coherent_cs.back(), -2.309498238246E+01 );

  coherent_cs = pb_erp14_xss_data_extractor->extractCoherentCrossSection();

  TEST_EQUALITY_CONST( coherent_cs.size(), 3176 );
  TEST_EQUALITY_CONST( coherent_cs.front(), -5.071403810640E+00 );
  TEST_EQUALITY_CONST( coherent_cs.back(), -2.309498238246E+01 );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractPhotoelectricCrossSection )
{
  Utility::ArrayView<const double> photoelectric_cs =
    b_xss_data_extractor->extractPhotoelectricCrossSection();

  FRENSIE_CHECK_EQUAL( photoelectric_cs.size(), 1176 );
  FRENSIE_CHECK_EQUAL( photoelectric_cs.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( photoelectric_cs.back(), -2.403097442973E+01 );

  photoelectric_cs = pb_xss_data_extractor->extractPhotoelectricCrossSection();

  TEST_EQUALITY_CONST( photoelectric_cs.size(), 3176 );
  TEST_EQUALITY_CONST( photoelectric_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( photoelectric_cs.back(), -1.115947249407E+01 );

  photoelectric_cs = pb_erp14_xss_data_extractor->extractPhotoelectricCrossSection();

  TEST_EQUALITY_CONST( photoelectric_cs.size(), 3176 );
  TEST_EQUALITY_CONST( photoelectric_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( photoelectric_cs.back(), -1.115947249407E+01 );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractPairProductionCrossSection )
{
  Utility::ArrayView<const double> pair_production_cs =
    b_xss_data_extractor->extractPairProductionCrossSection();

  FRENSIE_CHECK_EQUAL( pair_production_cs.size(), 1176 );
  FRENSIE_CHECK_EQUAL( pair_production_cs.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( pair_production_cs.back(), -1.342622032664E+00 );

  pair_production_cs =
    pb_xss_data_extractor->extractPairProductionCrossSection();

  TEST_EQUALITY_CONST( pair_production_cs.size(), 3176 );
  TEST_EQUALITY_CONST( pair_production_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( pair_production_cs.back(), 3.718032834377E+00 );

  pair_production_cs =
    pb_erp14_xss_data_extractor->extractPairProductionCrossSection();

  TEST_EQUALITY_CONST( pair_production_cs.size(), 3176 );
  TEST_EQUALITY_CONST( pair_production_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( pair_production_cs.back(), 3.718032834377E+00 );
}

//---------------------------------------------------------------------------//
// Check that the JINCE block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractJINCEBlock )
{
  Utility::ArrayView<const double> jince_block =
    b_xss_data_extractor->extractJINCEBlock();

  FRENSIE_CHECK_EQUAL( jince_block.size(), 270 );
  FRENSIE_CHECK_EQUAL( jince_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( jince_block.back(), 5.000000000000E+00 );

  jince_block = pb_xss_data_extractor->extractJINCEBlock();

  TEST_EQUALITY_CONST( jince_block.size(), 282 );
  TEST_EQUALITY_CONST( jince_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jince_block.back(), 8.200000000000E+01 );

  jince_block = pb_erp14_xss_data_extractor->extractJINCEBlock();

  TEST_EQUALITY_CONST( jince_block.size(), 282 );
  TEST_EQUALITY_CONST( jince_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jince_block.back(), 8.200000000000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the JCOHE block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractJCOHEBlock )
{
  Utility::ArrayView<const double> jcohe_block =
    b_xss_data_extractor->extractJCOHEBlock();

  FRENSIE_CHECK_EQUAL( jcohe_block.size(), 393 );
  FRENSIE_CHECK_EQUAL( jcohe_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( jcohe_block.back(), 6.525100000000E-30 );

  jcohe_block = pb_xss_data_extractor->extractJCOHEBlock();

  TEST_EQUALITY_CONST( jcohe_block.size(), 411 );
  TEST_EQUALITY_CONST( jcohe_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jcohe_block.back(), 1.158600000000E-20 );

  jcohe_block = pb_erp14_xss_data_extractor->extractJCOHEBlock();

  TEST_EQUALITY_CONST( jcohe_block.size(), 411 );
  TEST_EQUALITY_CONST( jcohe_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jcohe_block.back(), 1.158600000000E-20 );
}

//---------------------------------------------------------------------------//
// Check that the JFLO block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractJFLOBlock )
{
  Utility::ArrayView<const double> jflo_block =
    b_xss_data_extractor->extractJFLOBlock();

  FRENSIE_CHECK_EQUAL( jflo_block.size(), 0 );

  jflo_block = pb_xss_data_extractor->extractJFLOBlock();

  TEST_EQUALITY_CONST( jflo_block.size(), 24 );
  TEST_EQUALITY_CONST( jflo_block.front(), 1.471266666670E-02 );
  TEST_EQUALITY_CONST( jflo_block.back(), 8.762024531250E-02 );

  jflo_block = pb_erp14_xss_data_extractor->extractJFLOBlock();

  TEST_EQUALITY_CONST( jflo_block.size(), 24 );
  TEST_EQUALITY_CONST( jflo_block.front(), 1.471266666670E-02 );
  TEST_EQUALITY_CONST( jflo_block.back(), 8.762024531250E-02 );
}

//---------------------------------------------------------------------------//
// Check that the LHNM block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLHNMBlock )
{
  Utility::ArrayView<const double> lhnm_block =
    b_xss_data_extractor->extractLHNMBlock();

  FRENSIE_CHECK_EQUAL( lhnm_block.size(), 1176 );
  FRENSIE_CHECK_EQUAL( lhnm_block.front(), 9.635990815996E-07 );
  FRENSIE_CHECK_EQUAL( lhnm_block.back(), 9.999575195820E+04 );

  lhnm_block = pb_xss_data_extractor->extractLHNMBlock();

  TEST_EQUALITY_CONST( lhnm_block.size(), 3176 );
  TEST_EQUALITY_CONST( lhnm_block.front(), 9.916958825662E-07 );
  TEST_EQUALITY_CONST( lhnm_block.back(), 9.999864243970E+04 );

  lhnm_block = pb_erp14_xss_data_extractor->extractLHNMBlock();

  TEST_EQUALITY_CONST( lhnm_block.size(), 3176 );
  TEST_EQUALITY_CONST( lhnm_block.front(), 9.916958825662E-07 );
  TEST_EQUALITY_CONST( lhnm_block.back(), 9.999864243970E+04 );
}

//---------------------------------------------------------------------------//
// Check that the LNEPS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLNEPSBlock )
{
  Utility::ArrayView<const double> lneps_block =
    b_xss_data_extractor->extractLNEPSBlock();

  FRENSIE_CHECK_EQUAL( lneps_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( lneps_block.front(), 2.0 );
  FRENSIE_CHECK_EQUAL( lneps_block.back(), 1.0 );

  lneps_block = pb_xss_data_extractor->extractLNEPSBlock();

  TEST_EQUALITY_CONST( lneps_block.size(), 23 );
  TEST_EQUALITY_CONST( lneps_block.front(), 2.0 );
  TEST_EQUALITY_CONST( lneps_block.back(), 2.0 );

  lneps_block = pb_erp14_xss_data_extractor->extractLNEPSBlock();

  TEST_EQUALITY_CONST( lneps_block.size(), 23 );
  TEST_EQUALITY_CONST( lneps_block.front(), 2.0 );
  TEST_EQUALITY_CONST( lneps_block.back(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the LBEPS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLBEPSBlock )
{
  Utility::ArrayView<const double> lbeps_block =
    b_xss_data_extractor->extractLBEPSBlock();

  FRENSIE_CHECK_EQUAL( lbeps_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( lbeps_block.front(), 1.910000000000E-04 );
  FRENSIE_CHECK_EQUAL( lbeps_block.back(), 0.0 );

  lbeps_block = pb_xss_data_extractor->extractLBEPSBlock();

  TEST_EQUALITY_CONST( lbeps_block.size(), 23 );
  TEST_EQUALITY_CONST( lbeps_block.front(), 8.800500000000E-02);
  TEST_EQUALITY_CONST( lbeps_block.back(), 0.0 );

  lbeps_block = pb_erp14_xss_data_extractor->extractLBEPSBlock();

  TEST_EQUALITY_CONST( lbeps_block.size(), 23 );
  TEST_EQUALITY_CONST( lbeps_block.front(), 8.800500000000E-02);
  TEST_EQUALITY_CONST( lbeps_block.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the LPIPS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLPIPSBlock )
{
  Utility::ArrayView<const double> lpips_block =
    b_xss_data_extractor->extractLPIPSBlock();

  FRENSIE_CHECK_EQUAL( lpips_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( lpips_block.front(), 4.000000000000E-01 );
  FRENSIE_CHECK_EQUAL( lpips_block.back(), 2.000000000000E-01 );

  lpips_block = pb_xss_data_extractor->extractLPIPSBlock();

  TEST_EQUALITY_CONST( lpips_block.size(), 23 );
  TEST_EQUALITY_CONST( lpips_block.front(), 2.439024390244E-02 );
  TEST_EQUALITY_CONST( lpips_block.back(), 2.439024390244E-02 );

  lpips_block = pb_erp14_xss_data_extractor->extractLPIPSBlock();

  TEST_EQUALITY_CONST( lpips_block.size(), 23 );
  TEST_EQUALITY_CONST( lpips_block.front(), 2.439024390244E-02 );
  TEST_EQUALITY_CONST( lpips_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the LSWD block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLSWDBlock )
{
  Utility::ArrayView<const double> lswd_block =
    b_xss_data_extractor->extractLSWDBlock();

  FRENSIE_CHECK_EQUAL( lswd_block.size(), 3 );
  FRENSIE_CHECK_EQUAL( lswd_block.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( lswd_block.back(), 191.0 );

  lswd_block = pb_xss_data_extractor->extractLSWDBlock();

  TEST_EQUALITY_CONST( lswd_block.size(), 23 );
  TEST_EQUALITY_CONST( lswd_block.front(), 1.0 );
  TEST_EQUALITY_CONST( lswd_block.back(), 2091.0 );

  lswd_block = pb_erp14_xss_data_extractor->extractLSWDBlock();

  TEST_EQUALITY_CONST( lswd_block.size(), 23 );
  TEST_EQUALITY_CONST( lswd_block.front(), 1.0 );
  TEST_EQUALITY_CONST( lswd_block.back(), 2091.0 );
}

//---------------------------------------------------------------------------//
// Check that the SWD block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSWDBlock )
{
  Utility::ArrayView<const double> swd_block =
    b_xss_data_extractor->extractSWDBlock();

  FRENSIE_CHECK_EQUAL( swd_block.size(), 285 );
  FRENSIE_CHECK_EQUAL( swd_block.front(), 2.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( swd_block.back(), 1.000000000000E+00 );

  swd_block = pb_xss_data_extractor->extractSWDBlock();

  TEST_EQUALITY_CONST( swd_block.size(), 2185 );
  TEST_EQUALITY_CONST( swd_block.front(), 2.000000000000E+00 );
  TEST_EQUALITY_CONST( swd_block.back(), 1.000000000000E+00 );

  swd_block = pb_erp14_xss_data_extractor->extractSWDBlock();

  TEST_EQUALITY_CONST( swd_block.size(), 2185 );
  TEST_EQUALITY_CONST( swd_block.front(), 2.000000000000E+00 );
  TEST_EQUALITY_CONST( swd_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the SUBSH block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSUBSHBlock )
{
  Utility::ArrayView<const double> subsh_block =
    b_xss_data_extractor->extractSUBSHBlock();

  FRENSIE_CHECK_EQUAL( subsh_block.size(), 20 );
  FRENSIE_CHECK_EQUAL( subsh_block.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( subsh_block.back(), 0.0 );

  subsh_block = pb_xss_data_extractor->extractSUBSHBlock();

  TEST_EQUALITY_CONST( subsh_block.size(), 120 );
  TEST_EQUALITY_CONST( subsh_block.front(), 1.0 );
  TEST_EQUALITY_CONST( subsh_block.back(), 0.0 );

  subsh_block = pb_erp14_xss_data_extractor->extractSUBSHBlock();

  TEST_EQUALITY_CONST( subsh_block.size(), 120 );
  TEST_EQUALITY_CONST( subsh_block.front(), 1.0 );
  TEST_EQUALITY_CONST( subsh_block.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell ENDF designators can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellENDFDesignators )
{
  Utility::ArrayView<const double> subshell_endf_designators =
    b_xss_data_extractor->extractSubshellENDFDesignators();

  FRENSIE_CHECK_EQUAL( subshell_endf_designators.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_endf_designators.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( subshell_endf_designators.back(), 4.0 );

  subshell_endf_designators =
    pb_xss_data_extractor->extractSubshellENDFDesignators();

  TEST_EQUALITY_CONST( subshell_endf_designators.size(), 24 );
  TEST_EQUALITY_CONST( subshell_endf_designators.front(), 1.0 );
  TEST_EQUALITY_CONST( subshell_endf_designators.back(), 28.0 );

  subshell_endf_designators =
    pb_erp14_xss_data_extractor->extractSubshellENDFDesignators();

  TEST_EQUALITY_CONST( subshell_endf_designators.size(), 24 );
  TEST_EQUALITY_CONST( subshell_endf_designators.front(), 1.0 );
  TEST_EQUALITY_CONST( subshell_endf_designators.back(), 28.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancies can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellOccupancies )
{
  Utility::ArrayView<const double> subshell_occupancies =
    b_xss_data_extractor->extractSubshellOccupancies();

  FRENSIE_CHECK_EQUAL( subshell_occupancies.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_occupancies.front(), 2.0 );
  FRENSIE_CHECK_EQUAL( subshell_occupancies.back(), 0.67 );

  subshell_occupancies =
    pb_xss_data_extractor->extractSubshellOccupancies();

  TEST_EQUALITY_CONST( subshell_occupancies.size(), 24 );
  TEST_EQUALITY_CONST( subshell_occupancies.front(), 2.0 );
  TEST_EQUALITY_CONST( subshell_occupancies.back(), 1.33 );

  subshell_occupancies =
    pb_erp14_xss_data_extractor->extractSubshellOccupancies();

  TEST_EQUALITY_CONST( subshell_occupancies.size(), 24 );
  TEST_EQUALITY_CONST( subshell_occupancies.front(), 2.0 );
  TEST_EQUALITY_CONST( subshell_occupancies.back(), 1.33 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energies can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellBindingEnergies )
{
  auto subshell_be = b_xss_data_extractor->extractSubshellBindingEnergies();

  FRENSIE_CHECK_EQUAL( subshell_be.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_be.front(), 1.956100000000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_be.back(), 6.660000000000E-06 );

  subshell_be = pb_xss_data_extractor->extractSubshellBindingEnergies();

  FRENSIE_CHECK_EQUAL( subshell_be.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_be.front(), 8.829000000000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_be.back(), 5.290000000000E-06 );

  auto subshell_be_in_mev =
    b_xss_data_extractor->extractSubshellBindingEnergiesInMeV();

  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.front(), 1.956100000000E-04*MeV );
  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.back(), 6.660000000000E-06*MeV );

  subshell_be_in_mev =
    pb_xss_data_extractor->extractSubshellBindingEnergiesInMeV();

  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.front(), 8.829000000000E-02*MeV );
  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.back(), 5.290000000000E-06*MeV );

  subshell_be = pb_erp14_xss_data_extractor->extractSubshellBindingEnergies();

  TEST_EQUALITY_CONST( subshell_be.size(), 24 );
  TEST_EQUALITY_CONST( subshell_be.front(), 8.829000000000E-02 );
  TEST_EQUALITY_CONST( subshell_be.back(), 5.290000000000E-06 );

  subshell_be =
    pb_erp14_xss_data_extractor->extractSubshellBindingEnergiesInMeV();

  TEST_EQUALITY_CONST( subshell_be.size(), 24 );
  TEST_EQUALITY_CONST( subshell_be.front(), 8.829000000000E-02*MeV );
  TEST_EQUALITY_CONST( subshell_be.back(), 5.290000000000E-06*MeV );
}

//---------------------------------------------------------------------------//
// Check that the subshell compton interaction cdf can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellComptonInteractionCDF )
{
  Utility::ArrayView<const double> subshell_compton_cdf =
    b_xss_data_extractor->extractSubshellComptonInteractionCDF();

  FRENSIE_CHECK_EQUAL( subshell_compton_cdf.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_compton_cdf.front(), 4.000000000000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_compton_cdf.back(), 1.0 );

  subshell_compton_cdf =
    pb_xss_data_extractor->extractSubshellComptonInteractionCDF();

  TEST_EQUALITY_CONST( subshell_compton_cdf.size(), 24 );
  TEST_EQUALITY_CONST( subshell_compton_cdf.front(), 2.439024390244E-02 );
  TEST_EQUALITY_CONST( subshell_compton_cdf.back(), 1.0 );

  subshell_compton_cdf =
    pb_erp14_xss_data_extractor->extractSubshellComptonInteractionCDF();

  TEST_EQUALITY_CONST( subshell_compton_cdf.size(), 24 );
  TEST_EQUALITY_CONST( subshell_compton_cdf.front(), 2.439024390244E-02 );
  TEST_EQUALITY_CONST( subshell_compton_cdf.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell vacancy transition paths can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellVacancyTransitionPaths )
{
  Utility::ArrayView<const double> subshell_transitions =
    b_xss_data_extractor->extractSubshellVacancyTransitionPaths();

  FRENSIE_CHECK_EQUAL( subshell_transitions.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_transitions.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( subshell_transitions.back(), 0.0 );

  subshell_transitions =
    pb_xss_data_extractor->extractSubshellVacancyTransitionPaths();

  TEST_EQUALITY_CONST( subshell_transitions.size(), 24 );
  TEST_EQUALITY_CONST( subshell_transitions.front(), 1.890000000000E+02 );
  TEST_EQUALITY_CONST( subshell_transitions.back(), 0.0 );

  subshell_transitions =
    pb_erp14_xss_data_extractor->extractSubshellVacancyTransitionPaths();

  TEST_EQUALITY_CONST( subshell_transitions.size(), 24 );
  TEST_EQUALITY_CONST( subshell_transitions.front(), 1.890000000000E+02 );
  TEST_EQUALITY_CONST( subshell_transitions.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the SPHEL block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSPHELBlock )
{
  Utility::ArrayView<const double> sphel_block =
    b_xss_data_extractor->extractSPHELBlock();

  FRENSIE_CHECK_EQUAL( sphel_block.size(), 4704 );
  FRENSIE_CHECK_EQUAL( sphel_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( sphel_block.back(), -3.682568500852E+01 );

  sphel_block = pb_xss_data_extractor->extractSPHELBlock();

  TEST_EQUALITY_CONST( sphel_block.size(), 76224 );
  TEST_EQUALITY_CONST( sphel_block.front(), 0.0 );
  TEST_EQUALITY_CONST( sphel_block.back(), -2.364731020721E+01 );

  sphel_block = pb_erp14_xss_data_extractor->extractSPHELBlock();

  TEST_EQUALITY_CONST( sphel_block.size(), 76224 );
  TEST_EQUALITY_CONST( sphel_block.front(), 0.0 );
  TEST_EQUALITY_CONST( sphel_block.back(), -2.364731020721E+01 );
}

//---------------------------------------------------------------------------//
// Check that the RELO block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractRELOBlock )
{
  Utility::ArrayView<const double> relo_block =
    b_xss_data_extractor->extractRELOBlock();

  FRENSIE_CHECK_EQUAL( relo_block.size(), 0 );

  relo_block = pb_xss_data_extractor->extractRELOBlock();

  TEST_EQUALITY_CONST( relo_block.size(), 24 );
  TEST_EQUALITY_CONST( relo_block.front(), 0.0 );
  TEST_EQUALITY_CONST( relo_block.back(), 7.764000000000E+03 );

  relo_block = pb_erp14_xss_data_extractor->extractRELOBlock();

  TEST_EQUALITY_CONST( relo_block.size(), 24 );
  TEST_EQUALITY_CONST( relo_block.front(), 0.0 );
  TEST_EQUALITY_CONST( relo_block.back(), 7.764000000000E+03 );
}

//---------------------------------------------------------------------------//
// Check that the XPROB block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractXPROBBlock )
{
  Utility::ArrayView<const double> xprob_block =
    b_xss_data_extractor->extractXPROBBlock();

  FRENSIE_CHECK_EQUAL( xprob_block.size(), 0 );

  xprob_block = pb_xss_data_extractor->extractXPROBBlock();

  TEST_EQUALITY_CONST( xprob_block.size(), 7764 );
  TEST_EQUALITY_CONST( xprob_block.front(), 3.0 );
  TEST_EQUALITY_CONST( xprob_block.back(), 1.0 );

  xprob_block = pb_erp14_xss_data_extractor->extractXPROBBlock();

  TEST_EQUALITY_CONST( xprob_block.size(), 7764 );
  TEST_EQUALITY_CONST( xprob_block.front(), 3.0 );
  TEST_EQUALITY_CONST( xprob_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the ESZE block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractESZEBlock )
{
  Utility::ArrayView<const double> esze_block =
    b_xss_data_extractor->extractESZEBlock();

  FRENSIE_CHECK_EQUAL( esze_block.size(), 3490 );
  FRENSIE_CHECK_EQUAL( esze_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( esze_block.back(), 1.155380000000E+05 );

  esze_block = pb_xss_data_extractor->extractESZEBlock();

  TEST_EQUALITY_CONST( esze_block.size(), 14310 );
  TEST_EQUALITY_CONST( esze_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( esze_block.back(), 1.822340000000E+05 );

  esze_block = pb_erp14_xss_data_extractor->extractESZEBlock();

  TEST_EQUALITY_CONST( esze_block.size(), 14310 );
  TEST_EQUALITY_CONST( esze_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( esze_block.back(), 1.822340000000E+05 );
}

//---------------------------------------------------------------------------//
// Check that the ESZE2 block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractESZE2Block )
{
  Teuchos::ArrayView<const double> esze2_block =
    b_xss_data_extractor->extractESZE2Block();

  TEST_EQUALITY_CONST( esze2_block.size(), 0 );

  esze2_block = pb_xss_data_extractor->extractESZE2Block();

  TEST_EQUALITY_CONST( esze2_block.size(), 0 );

  esze2_block = pb_erp14_xss_data_extractor->extractESZE2Block();

  TEST_EQUALITY_CONST( esze2_block.size(), 954 );
  TEST_EQUALITY_CONST( esze2_block.front(), 2.48924e+09 );
  TEST_EQUALITY_CONST( esze2_block.back(), 2.11161e+06 );
}

//---------------------------------------------------------------------------//
// Check that the electron energy grid can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElectronEnergyGrid )
{
  auto electron_energy_grid =
    b_xss_data_extractor->extractElectronEnergyGrid();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 349 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.000000000000E+05 );

  electron_energy_grid = pb_xss_data_extractor->extractElectronEnergyGrid();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.000000000000E+05 );

  auto electron_energy_grid_in_mev =
    b_xss_data_extractor->extractElectronEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.size(), 349 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.front(), 1.000000000000E-05*MeV );
  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.back(), 1.000000000000E+05*MeV );

  electron_energy_grid_in_mev =
    pb_xss_data_extractor->extractElectronEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.front(), 1.000000000000E-05*MeV );
  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.back(), 1.000000000000E+05*MeV );

  electron_energy_grid = pb_erp14_xss_data_extractor->extractElectronEnergyGrid();

  TEST_EQUALITY_CONST( electron_energy_grid.size(), 477 );
  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.000000000000E+05 );

  electron_energy_grid_in_mev =
    pb_erp14_xss_data_extractor->extractElectronEnergyGrid();

  TEST_EQUALITY_CONST( electron_energy_grid.size(), 477 );
  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.000000000000E-05*MeV );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.000000000000E+05*MeV );
}

//---------------------------------------------------------------------------//
// Check that the electron total cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElectronTotalCrossSection )
{
  auto electron_total_cs =
    b_xss_data_extractor->extractElectronTotalCrossSection();

  FRENSIE_CHECK_EQUAL( electron_total_cs.size(), 349 );
  FRENSIE_CHECK_EQUAL( electron_total_cs.front(), 3.605412858153E+09 );
  FRENSIE_CHECK_EQUAL( electron_total_cs.back(), 5.246259578280E+05 );

  electron_total_cs =
    pb_xss_data_extractor->extractElectronTotalCrossSection();

  FRENSIE_CHECK_EQUAL( electron_total_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_total_cs.front(), 2.629060119800E+09 );
  FRENSIE_CHECK_EQUAL( electron_total_cs.back(), 2.845403136205E+06 );

  auto electron_total_cs_in_barns =
    b_xss_data_extractor->extractElectronTotalCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.size(), 349 );
  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.front(), 3.605412858153E+09*barns );
  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.back(), 5.246259578280E+05*barns );

  electron_total_cs_in_barns =
    pb_xss_data_extractor->extractElectronTotalCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.front(), 2.629060119800E+09*barns );
  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.back(), 2.845403136205E+06*barns );
}

//---------------------------------------------------------------------------//
// Check that the electron elastic transport cross section can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractElasticTransportCrossSection )
{
  Teuchos::ArrayView<const double> elastic_cs =
    b_xss_data_extractor->extractElasticTransportCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 0 );

  elastic_cs = pb_xss_data_extractor->extractElasticTransportCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 0 );

  elastic_cs = pb_erp14_xss_data_extractor->extractElasticTransportCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 477 );
  TEST_EQUALITY_CONST( elastic_cs.front(), 2.489240000000E+09 );
  TEST_EQUALITY_CONST( elastic_cs.back(), 2.87092e-06 );
}

//---------------------------------------------------------------------------//
// Check that the electron elastic total cross section can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractElasticTotalCrossSection )
{
  Teuchos::ArrayView<const double> elastic_cs =
    b_xss_data_extractor->extractElasticTotalCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 0 );

  elastic_cs = pb_xss_data_extractor->extractElasticTotalCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 0 );

  elastic_cs = pb_erp14_xss_data_extractor->extractElasticTotalCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 477 );
  TEST_EQUALITY_CONST( elastic_cs.front(), 2.489240000000E+09 );
  TEST_EQUALITY_CONST( elastic_cs.back(), 2.11161e+06 );
}

//---------------------------------------------------------------------------//
// Check that the electron elastic cutoff cross section can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractElasticCutoffCrossSection )
{
  Teuchos::ArrayView<const double> elastic_cs =
    b_xss_data_extractor->extractElasticCutoffCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cs.size(), 349 );
  FRENSIE_CHECK_EQUAL( elastic_cs.front(), 3.504710000000E+09 );
  FRENSIE_CHECK_EQUAL( elastic_cs.back(), 3.279820000000E-04 );

  elastic_cs = pb_xss_data_extractor->extractElasticCutoffCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 477 );
  TEST_EQUALITY_CONST( elastic_cs.front(), 2.489240000000E+09 );
  TEST_EQUALITY_CONST( elastic_cs.back(), 8.830510000000E-02 );

  elastic_cs = pb_erp14_xss_data_extractor->extractElasticCutoffCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( elastic_cs.front(), 2.489240000000E+09 );
  FRENSIE_CHECK_EQUAL( elastic_cs.back(), 8.830510000000E-02 );

  auto elastic_cs_in_barns =
    b_xss_data_extractor->extractElasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.size(), 349 );
  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.front(), 3.504710000000E+09*barns );
  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.back(), 3.279820000000E-04*barns );

  elastic_cs_in_barns =
    pb_xss_data_extractor->extractElasticCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.front(), 2.489240000000E+09*barns );
  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.back(), 8.830510000000E-02*barns );
}

//---------------------------------------------------------------------------//
// Check that the electron bremsstrahlung cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBremsstrahlungCrossSection )
{
  auto bremss_cs = b_xss_data_extractor->extractBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( bremss_cs.size(), 349 );
  FRENSIE_CHECK_EQUAL( bremss_cs.front(), 4.581530000000E+02 );
  FRENSIE_CHECK_EQUAL( bremss_cs.back(), 1.235750000000E+01 );

  bremss_cs = pb_xss_data_extractor->extractBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( bremss_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( bremss_cs.front(), 4.869800000000E+03 );
  FRENSIE_CHECK_EQUAL( bremss_cs.back(), 1.954170000000E+03 );

  auto bremss_cs_in_barns =
    b_xss_data_extractor->extractBremsstrahlungCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.size(), 349 );
  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.front(), 4.581530000000E+02*barns );
  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.back(), 1.235750000000E+01*barns );

  bremss_cs_in_barns =
    pb_xss_data_extractor->extractBremsstrahlungCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.front(), 4.869800000000E+03*barns );
  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.back(), 1.954170000000E+03*barns );

  bremss_cs = pb_erp14_xss_data_extractor->extractBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( bremss_cs.size(), 477 );
  TEST_EQUALITY_CONST( bremss_cs.front(), 4.869800000000E+03 );
  TEST_EQUALITY_CONST( bremss_cs.back(), 1.954170000000E+03 );

  bremss_cs_in_barns =
    pb_erp14_xss_data_extractor->extractBremsstrahlungCrossSectionInBarns();

  TEST_EQUALITY_CONST( bremss_cs.size(), 477 );
  TEST_EQUALITY_CONST( bremss_cs.front(), 4.869800000000E+03*barns );
  TEST_EQUALITY_CONST( bremss_cs.back(), 1.954170000000E+03*barns );
}

//---------------------------------------------------------------------------//
// Check that the electron excitation cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractExcitationCrossSection )
{
  auto excitation_cs = b_xss_data_extractor->extractExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( excitation_cs.size(), 349 );
  FRENSIE_CHECK_EQUAL( excitation_cs.front(), 1.445240000000E+07 );
  FRENSIE_CHECK_EQUAL( excitation_cs.back(), 2.339010000000E+05 );

  excitation_cs = pb_xss_data_extractor->extractExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( excitation_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( excitation_cs.front(), 8.757550000000E+06 );
  FRENSIE_CHECK_EQUAL( excitation_cs.back(), 1.578610000000E+06 );

  auto excitation_cs_in_barns =
    b_xss_data_extractor->extractExcitationCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.size(), 349 );
  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.front(), 1.445240000000E+07*barns );
  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.back(), 2.339010000000E+05*barns );

  excitation_cs_in_barns =
    pb_xss_data_extractor->extractExcitationCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.front(), 8.757550000000E+06*barns );
  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.back(), 1.578610000000E+06*barns );
  excitation_cs = pb_erp14_xss_data_extractor->extractExcitationCrossSection();

  TEST_EQUALITY_CONST( excitation_cs.size(), 477 );
  TEST_EQUALITY_CONST( excitation_cs.front(), 8.757550000000E+06 );
  TEST_EQUALITY_CONST( excitation_cs.back(), 1.578610000000E+06 );

  excitation_cs_in_barns =
    pb_erp14_xss_data_extractor->extractExcitationCrossSectionInBarns();

  TEST_EQUALITY_CONST( excitation_cs.size(), 477 );
  TEST_EQUALITY_CONST( excitation_cs.front(), 8.757550000000E+06*barns );
  TEST_EQUALITY_CONST( excitation_cs.back(), 1.578610000000E+06*barns );
}

//---------------------------------------------------------------------------//
// Check that the total electroionization cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElectroionizationCrossSection )
{
  auto electroionization_cs =
    b_xss_data_extractor->extractElectroionizationCrossSection();

  FRENSIE_CHECK_EQUAL( electroionization_cs.size(), 349 );
  FRENSIE_CHECK_EQUAL( electroionization_cs.front(), 8.625000000000E+07 );
  FRENSIE_CHECK_EQUAL( electroionization_cs.back(), 2.907126000000E+05 );

  electroionization_cs =
    pb_xss_data_extractor->extractElectroionizationCrossSection();

  FRENSIE_CHECK_EQUAL( electroionization_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( electroionization_cs.front(), 1.310577000000E+08 );
  FRENSIE_CHECK_EQUAL( electroionization_cs.back(), 1.264838877900E+06 );

  auto electroionization_cs_in_barns =
    b_xss_data_extractor->extractElectroionizationCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.size(), 349 );
  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.front(), 8.625000000000E+07*barns );
  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.back(), 2.907126000000E+05*barns );

  electroionization_cs_in_barns =
    pb_xss_data_extractor->extractElectroionizationCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.front(), 1.310577000000E+08*barns );
  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.back(), 1.264838877900E+06*barns );

  electroionization_cs =
    pb_erp14_xss_data_extractor->extractElectroionizationCrossSection();

  TEST_EQUALITY_CONST( electroionization_cs.size(), 477 );
  TEST_EQUALITY_CONST( electroionization_cs.front(), 1.310577000000E+08 );
  TEST_EQUALITY_CONST( electroionization_cs.back(), 1.264838877900E+06 );

  electroionization_cs_in_barns =
    pb_erp14_xss_data_extractor->extractElectroionizationCrossSectionInBarns();

  TEST_EQUALITY_CONST( electroionization_cs.size(), 477 );
  TEST_EQUALITY_CONST( electroionization_cs.front(), 1.310577000000E+08*barns );
  TEST_EQUALITY_CONST( electroionization_cs.back(), 1.264838877900E+06*barns );
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell cross sections can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor,
		   extractElectroionizationSubshellCrossSections )
{
  auto electroionization_subshell_cs =
    b_xss_data_extractor->extractElectroionizationSubshellCrossSections();

  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.size(), 1396 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.back(),
		       1.155380000000E+05 );

  electroionization_subshell_cs =
    pb_xss_data_extractor->extractElectroionizationSubshellCrossSections();

  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.size(), 11448 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.back(),
		       1.822340000000E+05 );

  auto electroionization_subshell_cs_in_barns =
    b_xss_data_extractor->extractElectroionizationSubshellCrossSectionsInBarns();

  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.size(), 1396 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.front(), 0.0*barns );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.back(),
		       1.155380000000E+05*barns );

  electroionization_subshell_cs_in_barns =
    pb_xss_data_extractor->extractElectroionizationSubshellCrossSectionsInBarns();

  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.size(), 11448 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.front(), 0.0*barns );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.back(),
		       1.822340000000E+05*barns );

  electroionization_subshell_cs =
    pb_erp14_xss_data_extractor->extractElectroionizationSubshellCrossSections();

  TEST_EQUALITY_CONST( electroionization_subshell_cs.size(), 11448 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.back(),
		       1.822340000000E+05 );

  electroionization_subshell_cs_in_barns =
    pb_erp14_xss_data_extractor->extractElectroionizationSubshellCrossSectionsInBarns();

  TEST_EQUALITY_CONST( electroionization_subshell_cs_in_barns.size(), 11448 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs_in_barns.front(),
                       0.0*barns );
  TEST_EQUALITY_CONST( electroionization_subshell_cs_in_barns.back(),
		       1.822340000000E+05*barns );
}

//---------------------------------------------------------------------------//
// Check that the EXCIT block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractEXCITBlock )
{
  Utility::ArrayView<const double> excit_block =
    b_xss_data_extractor->extractEXCITBlock();

  FRENSIE_CHECK_EQUAL( excit_block.size(), 368 );
  FRENSIE_CHECK_EQUAL( excit_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( excit_block.back(), 1.401060000000E-05 );

  excit_block = pb_xss_data_extractor->extractEXCITBlock();

  FRENSIE_CHECK_EQUAL( excit_block.size(), 572 );
  FRENSIE_CHECK_EQUAL( excit_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( excit_block.back(), 1.095330000000E-05 );

  excit_block = pb_erp14_xss_data_extractor->extractEXCITBlock();

  TEST_EQUALITY_CONST( excit_block.size(), 572 );
  TEST_EQUALITY_CONST( excit_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( excit_block.back(), 1.095330000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the ELASI block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractELASIBlock )
{
  Utility::ArrayView<const double> elasi_block =
    b_xss_data_extractor->extractELASIBlock();

  FRENSIE_CHECK_EQUAL( elasi_block.size(), 48 );
  FRENSIE_CHECK_EQUAL( elasi_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( elasi_block.back(), 1.772000000000E+03 );

  elasi_block = pb_xss_data_extractor->extractELASIBlock();

  FRENSIE_CHECK_EQUAL( elasi_block.size(), 42 );
  FRENSIE_CHECK_EQUAL( elasi_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( elasi_block.back(), 1.392000000000E+03 );

  elasi_block = pb_erp14_xss_data_extractor->extractELASIBlock();

  TEST_EQUALITY_CONST( elasi_block.size(), 42 );
  TEST_EQUALITY_CONST( elasi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( elasi_block.back(), 1.384e+03 );
}

//---------------------------------------------------------------------------//
// Check that the ELAS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractELASBlock )
{
  Utility::ArrayView<const double> elas_block =
    b_xss_data_extractor->extractELASBlock();

  FRENSIE_CHECK_EQUAL( elas_block.size(), 1954 );
  FRENSIE_CHECK_EQUAL( elas_block.front(), -1.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( elas_block.back(), 1.000000000000E+00 );

  elas_block = pb_xss_data_extractor->extractELASBlock();

  FRENSIE_CHECK_EQUAL( elas_block.size(), 1562 );
  FRENSIE_CHECK_EQUAL( elas_block.front(), -1.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( elas_block.back(), 1.000000000000E+00 );

  elas_block = pb_erp14_xss_data_extractor->extractELASBlock();

  TEST_EQUALITY_CONST( elas_block.size(), 1564 );
  TEST_EQUALITY_CONST( elas_block.front(), -1.000000000000E+00 );
  TEST_EQUALITY_CONST( elas_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the EION block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractEIONBlock )
{
  Utility::ArrayView<const double> eion_block =
    b_xss_data_extractor->extractEIONBlock();

  FRENSIE_CHECK_EQUAL( eion_block.size(), 3233 );
  FRENSIE_CHECK_EQUAL( eion_block.front(), 7.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( eion_block.back(), 1.000000000000E+00 );

  eion_block = pb_xss_data_extractor->extractEIONBlock();

  FRENSIE_CHECK_EQUAL( eion_block.size(), 14169 );
  FRENSIE_CHECK_EQUAL( eion_block.front(), 5.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( eion_block.back(), 1.000000000000E+00 );

  eion_block = pb_erp14_xss_data_extractor->extractEIONBlock();

  TEST_EQUALITY_CONST( eion_block.size(), 14169 );
  TEST_EQUALITY_CONST( eion_block.front(), 5.000000000000E+00 );
  TEST_EQUALITY_CONST( eion_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the BREMI block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBREMIBlock )
{
  Utility::ArrayView<const double> bremi_block =
    b_xss_data_extractor->extractBREMIBlock();

  FRENSIE_CHECK_EQUAL( bremi_block.size(), 30 );
  FRENSIE_CHECK_EQUAL( bremi_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( bremi_block.back(), 8.520000000000E+02 );

  bremi_block = pb_xss_data_extractor->extractBREMIBlock();

  FRENSIE_CHECK_EQUAL( bremi_block.size(), 27 );
  FRENSIE_CHECK_EQUAL( bremi_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( bremi_block.back(), 6.500000000000E+02 );

  bremi_block = pb_xss_data_extractor->extractBREMIBlock();

  TEST_EQUALITY_CONST( bremi_block.size(), 27 );
  TEST_EQUALITY_CONST( bremi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( bremi_block.back(), 6.500000000000E+02 );
}

//---------------------------------------------------------------------------//
// Check that the BREME block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBREMEBlock )
{
  Utility::ArrayView<const double> breme_block =
    b_xss_data_extractor->extractBREMEBlock();

  FRENSIE_CHECK_EQUAL( breme_block.size(), 1064 );
  FRENSIE_CHECK_EQUAL( breme_block.front(), 1.000000000000E-07 );
  FRENSIE_CHECK_EQUAL( breme_block.back(), 1.000000000000E+00 );

  breme_block = pb_xss_data_extractor->extractBREMEBlock();

  FRENSIE_CHECK_EQUAL( breme_block.size(), 852 );
  FRENSIE_CHECK_EQUAL( breme_block.front(), 1.000000000000E-07 );
  FRENSIE_CHECK_EQUAL( breme_block.back(), 1.000000000000E+00 );

  breme_block = pb_erp14_xss_data_extractor->extractBREMEBlock();

  TEST_EQUALITY_CONST( breme_block.size(), 852 );
  TEST_EQUALITY_CONST( breme_block.front(), 1.000000000000E-07 );
  TEST_EQUALITY_CONST( breme_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the BREML block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBREMLBlock )
{
  Utility::ArrayView<const double> breml_block =
    b_xss_data_extractor->extractBREMLBlock();

  FRENSIE_CHECK_EQUAL( breml_block.size(), 152 );
  FRENSIE_CHECK_EQUAL( breml_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( breml_block.back(), 9.729130000000E+04 );

  breml_block = pb_xss_data_extractor->extractBREMLBlock();

  FRENSIE_CHECK_EQUAL( breml_block.size(), 150 );
  FRENSIE_CHECK_EQUAL( breml_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( breml_block.back(), 9.726750000000E+04 );

  breml_block = pb_erp14_xss_data_extractor->extractBREMLBlock();

  TEST_EQUALITY_CONST( breml_block.size(), 150 );
  TEST_EQUALITY_CONST( breml_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( breml_block.back(), 2.7325e+03 );
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
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "pb_ace14_file",
                                        pb_ace14_file_name, "",
                                        "Test Pb ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "pb_ace14_table",
                                        pb_ace14_table_name, "",
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
      new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
				     ace_file_handler->getTableJXSArray(),
				     ace_file_handler->getTableXSSArray() ) );

  ace_file_handler.reset( new Data::ACEFileHandler( b_ace_file_name,
                                                    b_ace_table_name,
						    1u ) );

  b_xss_data_extractor.reset(
      new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
				     ace_file_handler->getTableJXSArray(),
				     ace_file_handler->getTableXSSArray() ) );

  ace_file_handler.reset( new Data::ACEFileHandler( pb_ace14_file_name,
                                                    pb_ace14_table_name,
						    1u ) );

  pb_erp14_xss_data_extractor.reset(
      new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
				     ace_file_handler->getTableJXSArray(),
				     ace_file_handler->getTableXSSArray() ) );

  // Clear setup data
  ace_file_handler.reset();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSEPRDataExtractor.cpp
//---------------------------------------------------------------------------//
