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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> b_xss_data_extractor;
Teuchos::RCP<Data::XSSEPRDataExtractor> pb_xss_data_extractor;
Teuchos::RCP<Data::XSSEPRDataExtractor> pb_erp14_xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can extract the atomic number
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractAtomicNumber )
{
  TEST_EQUALITY_CONST( b_xss_data_extractor->extractAtomicNumber(), 5 );
  TEST_EQUALITY_CONST( pb_xss_data_extractor->extractAtomicNumber(), 82 );
  TEST_EQUALITY_CONST( pb_erp14_xss_data_extractor->extractAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if old fluorescence data
// is present
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, hasOldFluorescenceData )
{
  TEST_ASSERT( !b_xss_data_extractor->hasOldFluorescenceData() );
  TEST_ASSERT( pb_xss_data_extractor->hasOldFluorescenceData() );
  TEST_ASSERT( pb_erp14_xss_data_extractor->hasOldFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if fluorescence data is
// present
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, hasFluorescenceData )
{
  TEST_ASSERT( !b_xss_data_extractor->hasFluorescenceData() );
  TEST_ASSERT( pb_xss_data_extractor->hasFluorescenceData() );
  TEST_ASSERT( pb_erp14_xss_data_extractor->hasFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if additional elastic cross
// section data is present
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, hasAdditionalElasticCrossSectionData )
{
  TEST_ASSERT( !b_xss_data_extractor->hasAdditionalElasticCrossSectionData() );
  TEST_ASSERT( !pb_xss_data_extractor->hasAdditionalElasticCrossSectionData() );
  TEST_ASSERT( pb_erp14_xss_data_extractor->hasAdditionalElasticCrossSectionData() );
}

//---------------------------------------------------------------------------//
// Check that the ESZG block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractESZGBlock )
{
  Teuchos::ArrayView<const double> eszg_block =
    b_xss_data_extractor->extractESZGBlock();

  TEST_EQUALITY_CONST( eszg_block.size(), 5880 );
  TEST_EQUALITY_CONST( eszg_block.front(), -1.381551055796E+01 );
  TEST_EQUALITY_CONST( eszg_block.back(), -1.342622032664E+00 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractPhotonEnergyGrid )
{
  Teuchos::ArrayView<const double> photon_energy_grid =
    b_xss_data_extractor->extractPhotonEnergyGrid();

  TEST_EQUALITY_CONST( photon_energy_grid.size(), 1176 );
  TEST_EQUALITY_CONST( photon_energy_grid.front(), -1.381551055796E+01 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.151292546497E+01 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractIncoherentCrossSection )
{
  Teuchos::ArrayView<const double> incoherent_cs =
    b_xss_data_extractor->extractIncoherentCrossSection();

  TEST_EQUALITY_CONST( incoherent_cs.size(), 1176 );
  TEST_EQUALITY_CONST( incoherent_cs.front(), -1.489417317132E+01 );
  TEST_EQUALITY_CONST( incoherent_cs.back(), -9.370438704073E+00 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractCoherentCrossSection )
{
  Teuchos::ArrayView<const double> coherent_cs =
    b_xss_data_extractor->extractCoherentCrossSection();

  TEST_EQUALITY_CONST( coherent_cs.size(), 1176 );
  TEST_EQUALITY_CONST( coherent_cs.front(), -7.167603012571E+00 );
  TEST_EQUALITY_CONST( coherent_cs.back(), -3.066204487218E+01 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractPhotoelectricCrossSection )
{
  Teuchos::ArrayView<const double> photoelectric_cs =
    b_xss_data_extractor->extractPhotoelectricCrossSection();

  TEST_EQUALITY_CONST( photoelectric_cs.size(), 1176 );
  TEST_EQUALITY_CONST( photoelectric_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( photoelectric_cs.back(), -2.403097442973E+01 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractPairProductionCrossSection )
{
  Teuchos::ArrayView<const double> pair_production_cs =
    b_xss_data_extractor->extractPairProductionCrossSection();

  TEST_EQUALITY_CONST( pair_production_cs.size(), 1176 );
  TEST_EQUALITY_CONST( pair_production_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( pair_production_cs.back(), -1.342622032664E+00 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractJINCEBlock )
{
  Teuchos::ArrayView<const double> jince_block =
    b_xss_data_extractor->extractJINCEBlock();

  TEST_EQUALITY_CONST( jince_block.size(), 270 );
  TEST_EQUALITY_CONST( jince_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jince_block.back(), 5.000000000000E+00 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractJCOHEBlock )
{
  Teuchos::ArrayView<const double> jcohe_block =
    b_xss_data_extractor->extractJCOHEBlock();

  TEST_EQUALITY_CONST( jcohe_block.size(), 393 );
  TEST_EQUALITY_CONST( jcohe_block.front(), 0.0 );
  TEST_EQUALITY_CONST( jcohe_block.back(), 6.525100000000E-30 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractJFLOBlock )
{
  Teuchos::ArrayView<const double> jflo_block =
    b_xss_data_extractor->extractJFLOBlock();

  TEST_EQUALITY_CONST( jflo_block.size(), 0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractLHNMBlock )
{
  Teuchos::ArrayView<const double> lhnm_block =
    b_xss_data_extractor->extractLHNMBlock();

  TEST_EQUALITY_CONST( lhnm_block.size(), 1176 );
  TEST_EQUALITY_CONST( lhnm_block.front(), 9.635990815996E-07 );
  TEST_EQUALITY_CONST( lhnm_block.back(), 9.999575195820E+04 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractLNEPSBlock )
{
  Teuchos::ArrayView<const double> lneps_block =
    b_xss_data_extractor->extractLNEPSBlock();

  TEST_EQUALITY_CONST( lneps_block.size(), 3 );
  TEST_EQUALITY_CONST( lneps_block.front(), 2.0 );
  TEST_EQUALITY_CONST( lneps_block.back(), 1.0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractLBEPSBlock )
{
  Teuchos::ArrayView<const double> lbeps_block =
    b_xss_data_extractor->extractLBEPSBlock();

  TEST_EQUALITY_CONST( lbeps_block.size(), 3 );
  TEST_EQUALITY_CONST( lbeps_block.front(), 1.910000000000E-04 );
  TEST_EQUALITY_CONST( lbeps_block.back(), 0.0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractLPIPSBlock )
{
  Teuchos::ArrayView<const double> lpips_block =
    b_xss_data_extractor->extractLPIPSBlock();

  TEST_EQUALITY_CONST( lpips_block.size(), 3 );
  TEST_EQUALITY_CONST( lpips_block.front(), 4.000000000000E-01 );
  TEST_EQUALITY_CONST( lpips_block.back(), 2.000000000000E-01 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractLSWDBlock )
{
  Teuchos::ArrayView<const double> lswd_block =
    b_xss_data_extractor->extractLSWDBlock();

  TEST_EQUALITY_CONST( lswd_block.size(), 3 );
  TEST_EQUALITY_CONST( lswd_block.front(), 1.0 );
  TEST_EQUALITY_CONST( lswd_block.back(), 191.0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSWDBlock )
{
  Teuchos::ArrayView<const double> swd_block =
    b_xss_data_extractor->extractSWDBlock();

  TEST_EQUALITY_CONST( swd_block.size(), 285 );
  TEST_EQUALITY_CONST( swd_block.front(), 2.000000000000E+00 );
  TEST_EQUALITY_CONST( swd_block.back(), 1.000000000000E+00 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSUBSHBlock )
{
  Teuchos::ArrayView<const double> subsh_block =
    b_xss_data_extractor->extractSUBSHBlock();

  TEST_EQUALITY_CONST( subsh_block.size(), 20 );
  TEST_EQUALITY_CONST( subsh_block.front(), 1.0 );
  TEST_EQUALITY_CONST( subsh_block.back(), 0.0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSubshellENDFDesignators )
{
  Teuchos::ArrayView<const double> subshell_endf_designators =
    b_xss_data_extractor->extractSubshellENDFDesignators();

  TEST_EQUALITY_CONST( subshell_endf_designators.size(), 4 );
  TEST_EQUALITY_CONST( subshell_endf_designators.front(), 1.0 );
  TEST_EQUALITY_CONST( subshell_endf_designators.back(), 4.0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSubshellOccupancies )
{
  Teuchos::ArrayView<const double> subshell_occupancies =
    b_xss_data_extractor->extractSubshellOccupancies();

  TEST_EQUALITY_CONST( subshell_occupancies.size(), 4 );
  TEST_EQUALITY_CONST( subshell_occupancies.front(), 2.0 );
  TEST_EQUALITY_CONST( subshell_occupancies.back(), 0.67 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSubshellBindingEnergies )
{
  Teuchos::ArrayView<const double> subshell_be =
    b_xss_data_extractor->extractSubshellBindingEnergies();

  TEST_EQUALITY_CONST( subshell_be.size(), 4 );
  TEST_EQUALITY_CONST( subshell_be.front(), 1.956100000000E-04 );
  TEST_EQUALITY_CONST( subshell_be.back(), 6.660000000000E-06 );

  subshell_be = pb_xss_data_extractor->extractSubshellBindingEnergies();

  TEST_EQUALITY_CONST( subshell_be.size(), 24 );
  TEST_EQUALITY_CONST( subshell_be.front(), 8.829000000000E-02 );
  TEST_EQUALITY_CONST( subshell_be.back(), 5.290000000000E-06 );

  subshell_be = pb_erp14_xss_data_extractor->extractSubshellBindingEnergies();

  TEST_EQUALITY_CONST( subshell_be.size(), 24 );
  TEST_EQUALITY_CONST( subshell_be.front(), 8.829000000000E-02 );
  TEST_EQUALITY_CONST( subshell_be.back(), 5.290000000000E-06 );
}

//---------------------------------------------------------------------------//
// Check that the subshell compton interaction cdf can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSubshellComptonInteractionCDF )
{
  Teuchos::ArrayView<const double> subshell_compton_cdf =
    b_xss_data_extractor->extractSubshellComptonInteractionCDF();

  TEST_EQUALITY_CONST( subshell_compton_cdf.size(), 4 );
  TEST_EQUALITY_CONST( subshell_compton_cdf.front(), 4.000000000000E-01 );
  TEST_EQUALITY_CONST( subshell_compton_cdf.back(), 1.0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSubshellVacancyTransitionPaths )
{
  Teuchos::ArrayView<const double> subshell_transitions =
    b_xss_data_extractor->extractSubshellVacancyTransitionPaths();

  TEST_EQUALITY_CONST( subshell_transitions.size(), 4 );
  TEST_EQUALITY_CONST( subshell_transitions.front(), 0.0 );
  TEST_EQUALITY_CONST( subshell_transitions.back(), 0.0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractSPHELBlock )
{
  Teuchos::ArrayView<const double> sphel_block =
    b_xss_data_extractor->extractSPHELBlock();

  TEST_EQUALITY_CONST( sphel_block.size(), 4704 );
  TEST_EQUALITY_CONST( sphel_block.front(), 0.0 );
  TEST_EQUALITY_CONST( sphel_block.back(), -3.682568500852E+01 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractRELOBlock )
{
  Teuchos::ArrayView<const double> relo_block =
    b_xss_data_extractor->extractRELOBlock();

  TEST_EQUALITY_CONST( relo_block.size(), 0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractXPROBBlock )
{
  Teuchos::ArrayView<const double> xprob_block =
    b_xss_data_extractor->extractXPROBBlock();

  TEST_EQUALITY_CONST( xprob_block.size(), 0 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractESZEBlock )
{
  Teuchos::ArrayView<const double> esze_block =
    b_xss_data_extractor->extractESZEBlock();

  TEST_EQUALITY_CONST( esze_block.size(), 3490 );
  TEST_EQUALITY_CONST( esze_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( esze_block.back(), 1.155380000000E+05 );

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
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractElectronEnergyGrid )
{
  Teuchos::ArrayView<const double> electron_energy_grid =
    b_xss_data_extractor->extractElectronEnergyGrid();

  TEST_EQUALITY_CONST( electron_energy_grid.size(), 349 );
  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.000000000000E+05 );

  electron_energy_grid = pb_xss_data_extractor->extractElectronEnergyGrid();

  TEST_EQUALITY_CONST( electron_energy_grid.size(), 477 );
  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.000000000000E+05 );

  electron_energy_grid = pb_erp14_xss_data_extractor->extractElectronEnergyGrid();

  TEST_EQUALITY_CONST( electron_energy_grid.size(), 477 );
  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.000000000000E+05 );
}

//---------------------------------------------------------------------------//
// Check that the electron total cross section can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractElectronTotalCrossSection )
{
  Teuchos::ArrayView<const double> electron_total_cs =
    b_xss_data_extractor->extractElectronTotalCrossSection();

  TEST_EQUALITY_CONST( electron_total_cs.size(), 349 );
  TEST_EQUALITY_CONST( electron_total_cs.front(), 3.605412858153E+09 );
  TEST_EQUALITY_CONST( electron_total_cs.back(), 5.246259578280E+05 );

  electron_total_cs =
    pb_xss_data_extractor->extractElectronTotalCrossSection();

  TEST_EQUALITY_CONST( electron_total_cs.size(), 477 );
  TEST_EQUALITY_CONST( electron_total_cs.front(), 2.629060119800E+09 );
  TEST_EQUALITY_CONST( electron_total_cs.back(), 2.845403136205E+06 );

  electron_total_cs =
    pb_erp14_xss_data_extractor->extractElectronTotalCrossSection();

  TEST_EQUALITY_CONST( electron_total_cs.size(), 477 );
  TEST_EQUALITY_CONST( electron_total_cs.front(), 2.629060119800E+09 );
  TEST_EQUALITY_CONST( electron_total_cs.back(), 2.845403136205E+06 );
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

  TEST_EQUALITY_CONST( elastic_cs.size(), 349 );
  TEST_EQUALITY_CONST( elastic_cs.front(), 3.504710000000E+09 );
  TEST_EQUALITY_CONST( elastic_cs.back(), 3.279820000000E-04 );

  elastic_cs = pb_xss_data_extractor->extractElasticCutoffCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 477 );
  TEST_EQUALITY_CONST( elastic_cs.front(), 2.489240000000E+09 );
  TEST_EQUALITY_CONST( elastic_cs.back(), 8.830510000000E-02 );

  elastic_cs = pb_erp14_xss_data_extractor->extractElasticCutoffCrossSection();

  TEST_EQUALITY_CONST( elastic_cs.size(), 477 );
  TEST_EQUALITY_CONST( elastic_cs.front(), 2.489240000000E+09 );
  TEST_EQUALITY_CONST( elastic_cs.back(), 8.830510000000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the electron bremsstrahlung cross section can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractBremsstrahlungCrossSection )
{
  Teuchos::ArrayView<const double> bremss_cs =
    b_xss_data_extractor->extractBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( bremss_cs.size(), 349 );
  TEST_EQUALITY_CONST( bremss_cs.front(), 4.581530000000E+02 );
  TEST_EQUALITY_CONST( bremss_cs.back(), 1.235750000000E+01 );

  bremss_cs = pb_xss_data_extractor->extractBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( bremss_cs.size(), 477 );
  TEST_EQUALITY_CONST( bremss_cs.front(), 4.869800000000E+03 );
  TEST_EQUALITY_CONST( bremss_cs.back(), 1.954170000000E+03 );

  bremss_cs = pb_erp14_xss_data_extractor->extractBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( bremss_cs.size(), 477 );
  TEST_EQUALITY_CONST( bremss_cs.front(), 4.869800000000E+03 );
  TEST_EQUALITY_CONST( bremss_cs.back(), 1.954170000000E+03 );
}

//---------------------------------------------------------------------------//
// Check that the electron excitation cross section can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractExcitationCrossSection )
{
  Teuchos::ArrayView<const double> excitation_cs =
    b_xss_data_extractor->extractExcitationCrossSection();

  TEST_EQUALITY_CONST( excitation_cs.size(), 349 );
  TEST_EQUALITY_CONST( excitation_cs.front(), 1.445240000000E+07 );
  TEST_EQUALITY_CONST( excitation_cs.back(), 2.339010000000E+05 );

  excitation_cs = pb_xss_data_extractor->extractExcitationCrossSection();

  TEST_EQUALITY_CONST( excitation_cs.size(), 477 );
  TEST_EQUALITY_CONST( excitation_cs.front(), 8.757550000000E+06 );
  TEST_EQUALITY_CONST( excitation_cs.back(), 1.578610000000E+06 );

  excitation_cs = pb_erp14_xss_data_extractor->extractExcitationCrossSection();

  TEST_EQUALITY_CONST( excitation_cs.size(), 477 );
  TEST_EQUALITY_CONST( excitation_cs.front(), 8.757550000000E+06 );
  TEST_EQUALITY_CONST( excitation_cs.back(), 1.578610000000E+06 );
}

//---------------------------------------------------------------------------//
// Check that the total electroionization cross section can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractElectroionizationCrossSection )
{
  Teuchos::ArrayView<const double> electroionization_cs =
    b_xss_data_extractor->extractElectroionizationCrossSection();

  TEST_EQUALITY_CONST( electroionization_cs.size(), 349 );
  TEST_EQUALITY_CONST( electroionization_cs.front(), 8.625000000000E+07 );
  TEST_EQUALITY_CONST( electroionization_cs.back(), 2.907126000000E+05 );

  electroionization_cs =
    pb_xss_data_extractor->extractElectroionizationCrossSection();

  TEST_EQUALITY_CONST( electroionization_cs.size(), 477 );
  TEST_EQUALITY_CONST( electroionization_cs.front(), 1.310577000000E+08 );
  TEST_EQUALITY_CONST( electroionization_cs.back(), 1.264838877900E+06 );

  electroionization_cs =
    pb_erp14_xss_data_extractor->extractElectroionizationCrossSection();

  TEST_EQUALITY_CONST( electroionization_cs.size(), 477 );
  TEST_EQUALITY_CONST( electroionization_cs.front(), 1.310577000000E+08 );
  TEST_EQUALITY_CONST( electroionization_cs.back(), 1.264838877900E+06 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell cross sections can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor,
		   extractElectroionizationSubshellCrossSections )
{
  Teuchos::ArrayView<const double> electroionization_subshell_cs =
    b_xss_data_extractor->extractElectroionizationSubshellCrossSections();

  TEST_EQUALITY_CONST( electroionization_subshell_cs.size(), 1396 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.back(),
		       1.155380000000E+05 );

  electroionization_subshell_cs =
    pb_xss_data_extractor->extractElectroionizationSubshellCrossSections();

  TEST_EQUALITY_CONST( electroionization_subshell_cs.size(), 11448 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.back(),
		       1.822340000000E+05 );

  electroionization_subshell_cs =
    pb_erp14_xss_data_extractor->extractElectroionizationSubshellCrossSections();

  TEST_EQUALITY_CONST( electroionization_subshell_cs.size(), 11448 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.front(), 0.0 );
  TEST_EQUALITY_CONST( electroionization_subshell_cs.back(),
		       1.822340000000E+05 );
}

//---------------------------------------------------------------------------//
// Check that the EXCIT block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractEXCITBlock )
{
  Teuchos::ArrayView<const double> excit_block =
    b_xss_data_extractor->extractEXCITBlock();

  TEST_EQUALITY_CONST( excit_block.size(), 368 );
  TEST_EQUALITY_CONST( excit_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( excit_block.back(), 1.401060000000E-05 );

  excit_block = pb_xss_data_extractor->extractEXCITBlock();

  TEST_EQUALITY_CONST( excit_block.size(), 572 );
  TEST_EQUALITY_CONST( excit_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( excit_block.back(), 1.095330000000E-05 );

  excit_block = pb_erp14_xss_data_extractor->extractEXCITBlock();

  TEST_EQUALITY_CONST( excit_block.size(), 572 );
  TEST_EQUALITY_CONST( excit_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( excit_block.back(), 1.095330000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the ELASI block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractELASIBlock )
{
  Teuchos::ArrayView<const double> elasi_block =
    b_xss_data_extractor->extractELASIBlock();

  TEST_EQUALITY_CONST( elasi_block.size(), 48 );
  TEST_EQUALITY_CONST( elasi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( elasi_block.back(), 1.772000000000E+03 );

  elasi_block = pb_xss_data_extractor->extractELASIBlock();

  TEST_EQUALITY_CONST( elasi_block.size(), 42 );
  TEST_EQUALITY_CONST( elasi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( elasi_block.back(), 1.392000000000E+03 );

  elasi_block = pb_erp14_xss_data_extractor->extractELASIBlock();

  TEST_EQUALITY_CONST( elasi_block.size(), 42 );
  TEST_EQUALITY_CONST( elasi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( elasi_block.back(), 1.384e+03 );
}

//---------------------------------------------------------------------------//
// Check that the ELAS block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractELASBlock )
{
  Teuchos::ArrayView<const double> elas_block =
    b_xss_data_extractor->extractELASBlock();

  TEST_EQUALITY_CONST( elas_block.size(), 1954 );
  TEST_EQUALITY_CONST( elas_block.front(), -1.000000000000E+00 );
  TEST_EQUALITY_CONST( elas_block.back(), 1.000000000000E+00 );

  elas_block = pb_xss_data_extractor->extractELASBlock();

  TEST_EQUALITY_CONST( elas_block.size(), 1562 );
  TEST_EQUALITY_CONST( elas_block.front(), -1.000000000000E+00 );
  TEST_EQUALITY_CONST( elas_block.back(), 1.000000000000E+00 );

  elas_block = pb_erp14_xss_data_extractor->extractELASBlock();

  TEST_EQUALITY_CONST( elas_block.size(), 1564 );
  TEST_EQUALITY_CONST( elas_block.front(), -1.000000000000E+00 );
  TEST_EQUALITY_CONST( elas_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the EION block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractEIONBlock )
{
  Teuchos::ArrayView<const double> eion_block =
    b_xss_data_extractor->extractEIONBlock();

  TEST_EQUALITY_CONST( eion_block.size(), 3233 );
  TEST_EQUALITY_CONST( eion_block.front(), 7.000000000000E+00 );
  TEST_EQUALITY_CONST( eion_block.back(), 1.000000000000E+00 );

  eion_block = pb_xss_data_extractor->extractEIONBlock();

  TEST_EQUALITY_CONST( eion_block.size(), 14169 );
  TEST_EQUALITY_CONST( eion_block.front(), 5.000000000000E+00 );
  TEST_EQUALITY_CONST( eion_block.back(), 1.000000000000E+00 );

  eion_block = pb_erp14_xss_data_extractor->extractEIONBlock();

  TEST_EQUALITY_CONST( eion_block.size(), 14169 );
  TEST_EQUALITY_CONST( eion_block.front(), 5.000000000000E+00 );
  TEST_EQUALITY_CONST( eion_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the BREMI block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractBREMIBlock )
{
  Teuchos::ArrayView<const double> bremi_block =
    b_xss_data_extractor->extractBREMIBlock();

  TEST_EQUALITY_CONST( bremi_block.size(), 30 );
  TEST_EQUALITY_CONST( bremi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( bremi_block.back(), 8.520000000000E+02 );

  bremi_block = pb_xss_data_extractor->extractBREMIBlock();

  TEST_EQUALITY_CONST( bremi_block.size(), 27 );
  TEST_EQUALITY_CONST( bremi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( bremi_block.back(), 6.500000000000E+02 );

  bremi_block = pb_xss_data_extractor->extractBREMIBlock();

  TEST_EQUALITY_CONST( bremi_block.size(), 27 );
  TEST_EQUALITY_CONST( bremi_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( bremi_block.back(), 6.500000000000E+02 );
}

//---------------------------------------------------------------------------//
// Check that the BREME block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractBREMEBlock )
{
  Teuchos::ArrayView<const double> breme_block =
    b_xss_data_extractor->extractBREMEBlock();

  TEST_EQUALITY_CONST( breme_block.size(), 1064 );
  TEST_EQUALITY_CONST( breme_block.front(), 1.000000000000E-07 );
  TEST_EQUALITY_CONST( breme_block.back(), 1.000000000000E+00 );

  breme_block = pb_xss_data_extractor->extractBREMEBlock();

  TEST_EQUALITY_CONST( breme_block.size(), 852 );
  TEST_EQUALITY_CONST( breme_block.front(), 1.000000000000E-07 );
  TEST_EQUALITY_CONST( breme_block.back(), 1.000000000000E+00 );

  breme_block = pb_erp14_xss_data_extractor->extractBREMEBlock();

  TEST_EQUALITY_CONST( breme_block.size(), 852 );
  TEST_EQUALITY_CONST( breme_block.front(), 1.000000000000E-07 );
  TEST_EQUALITY_CONST( breme_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the BREML block can be extracted
TEUCHOS_UNIT_TEST( XSSEPRDataExtractor, extractBREMLBlock )
{
  Teuchos::ArrayView<const double> breml_block =
    b_xss_data_extractor->extractBREMLBlock();

  TEST_EQUALITY_CONST( breml_block.size(), 152 );
  TEST_EQUALITY_CONST( breml_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( breml_block.back(), 9.729130000000E+04 );

  breml_block = pb_xss_data_extractor->extractBREMLBlock();

  TEST_EQUALITY_CONST( breml_block.size(), 150 );
  TEST_EQUALITY_CONST( breml_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( breml_block.back(), 9.726750000000E+04 );

  breml_block = pb_erp14_xss_data_extractor->extractBREMLBlock();

  TEST_EQUALITY_CONST( breml_block.size(), 150 );
  TEST_EQUALITY_CONST( breml_block.front(), 1.000000000000E-05 );
  TEST_EQUALITY_CONST( breml_block.back(), 2.7325e+03 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string pb_ace_file_name, pb_ace_table_name;
  std::string b_ace_file_name, b_ace_table_name;
  std::string pb_ace14_file_name, pb_ace14_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "pb_ace_file",
		 &pb_ace_file_name,
		 "Test Pb ACE EPR12 file name" );
  clp.setOption( "pb_ace_table",
		 &pb_ace_table_name,
		 "Test Pb ACE table name in ACE EPR12 file" );

  clp.setOption( "b_ace_file",
                 &b_ace_file_name,
		 "Test B ACE EPR12 file name" );
  clp.setOption( "b_ace_table",
		 &b_ace_table_name,
		 "Test B ACE table name in ACE EPR12 file" );

  clp.setOption( "pb_ace14_file",
		 &pb_ace14_file_name,
		 "Test Pb ACE EPR14 file name" );
  clp.setOption( "pb_ace14_table",
		 &pb_ace14_table_name,
		 "Test Pb ACE table name in ACE EPR14 file" );

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
// end tstXSSEPRDataExtractor.cpp
//---------------------------------------------------------------------------//
