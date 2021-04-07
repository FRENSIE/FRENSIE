//---------------------------------------------------------------------------//
//!
//! \file   tstXSSEPRDataExtractorPbv12.cpp
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
std::shared_ptr<Data::XSSEPRDataExtractor> pb_xss_data_extractor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can extract the atomic number
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractAtomicNumber )
{
  FRENSIE_CHECK_EQUAL( pb_xss_data_extractor->extractAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if old fluorescence data
// is present
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, hasOldFluorescenceData )
{
  FRENSIE_CHECK( pb_xss_data_extractor->hasOldFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if fluorescence data is
// present
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, hasFluorescenceData )
{
  FRENSIE_CHECK( pb_xss_data_extractor->hasFluorescenceData() );
}

//---------------------------------------------------------------------------//
// Check that the XSSEPRDataExtractor can check if the file is version eprdata14
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, isEPRVersion14 )
{
  FRENSIE_CHECK( !pb_xss_data_extractor->isEPRVersion14() );
}

//---------------------------------------------------------------------------//
// Check that the ESZG block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractESZGBlock )
{
  Utility::ArrayView<const double> eszg_block =
    pb_xss_data_extractor->extractESZGBlock();

  FRENSIE_CHECK_EQUAL( eszg_block.size(), 15880 );
  FRENSIE_CHECK_EQUAL( eszg_block.front(), -1.381551055796E+01 );
  FRENSIE_CHECK_EQUAL( eszg_block.back(), 3.718032834377E+00 );
}

//---------------------------------------------------------------------------//
// Check that the photon energy grid can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractPhotonEnergyGrid )
{
  Utility::ArrayView<const double> photon_energy_grid =
    pb_xss_data_extractor->extractPhotonEnergyGrid();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 3176 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), -1.381551055796E+01 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.151292546497E+01 );
}

//---------------------------------------------------------------------------//
// Check that the incoherent cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractIncoherentCrossSection )
{
  Utility::ArrayView<const double> incoherent_cs =
    pb_xss_data_extractor->extractIncoherentCrossSection();

  FRENSIE_CHECK_EQUAL( incoherent_cs.size(), 3176 );
  FRENSIE_CHECK_EQUAL( incoherent_cs.front(), -1.338724079720E+01 );
  FRENSIE_CHECK_EQUAL( incoherent_cs.back(), -6.573285045032E+00 );
}

//---------------------------------------------------------------------------//
// Check that the coherent cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractCoherentCrossSection )
{
  Utility::ArrayView<const double> coherent_cs =
    pb_xss_data_extractor->extractCoherentCrossSection();

  FRENSIE_CHECK_EQUAL( coherent_cs.size(), 3176 );
  FRENSIE_CHECK_EQUAL( coherent_cs.front(), -5.071403810640E+00 );
  FRENSIE_CHECK_EQUAL( coherent_cs.back(), -2.309498238246E+01 );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractPhotoelectricCrossSection )
{
  Utility::ArrayView<const double> photoelectric_cs =
    pb_xss_data_extractor->extractPhotoelectricCrossSection();

  FRENSIE_CHECK_EQUAL( photoelectric_cs.size(), 3176 );
  FRENSIE_CHECK_EQUAL( photoelectric_cs.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( photoelectric_cs.back(), -1.115947249407E+01 );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractPairProductionCrossSection )
{
  Utility::ArrayView<const double> pair_production_cs =
    pb_xss_data_extractor->extractPairProductionCrossSection();

  FRENSIE_CHECK_EQUAL( pair_production_cs.size(), 3176 );
  FRENSIE_CHECK_EQUAL( pair_production_cs.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( pair_production_cs.back(), 3.718032834377E+00 );
}

//---------------------------------------------------------------------------//
// Check that the JINCE block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractJINCEBlock )
{
  Utility::ArrayView<const double> jince_block =
    pb_xss_data_extractor->extractJINCEBlock();

  FRENSIE_CHECK_EQUAL( jince_block.size(), 282 );
  FRENSIE_CHECK_EQUAL( jince_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( jince_block.back(), 8.200000000000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the JCOHE block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractJCOHEBlock )
{
  Utility::ArrayView<const double> jcohe_block =
    pb_xss_data_extractor->extractJCOHEBlock();

  FRENSIE_CHECK_EQUAL( jcohe_block.size(), 411 );
  FRENSIE_CHECK_EQUAL( jcohe_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( jcohe_block.back(), 1.158600000000E-20 );
}

//---------------------------------------------------------------------------//
// Check that the JFLO block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractJFLOBlock )
{
  Utility::ArrayView<const double> jflo_block =
    pb_xss_data_extractor->extractJFLOBlock();

  FRENSIE_CHECK_EQUAL( jflo_block.size(), 24 );
  FRENSIE_CHECK_EQUAL( jflo_block.front(), 1.471266666670E-02 );
  FRENSIE_CHECK_EQUAL( jflo_block.back(), 8.762024531250E-02 );
}

//---------------------------------------------------------------------------//
// Check that the LHNM block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLHNMBlock )
{
  Utility::ArrayView<const double> lhnm_block =
    pb_xss_data_extractor->extractLHNMBlock();

  FRENSIE_CHECK_EQUAL( lhnm_block.size(), 3176 );
  FRENSIE_CHECK_EQUAL( lhnm_block.front(), 9.916958825662E-07 );
  FRENSIE_CHECK_EQUAL( lhnm_block.back(), 9.999864243970E+04 );
}

//---------------------------------------------------------------------------//
// Check that the LNEPS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLNEPSBlock )
{
  Utility::ArrayView<const double> lneps_block =
    pb_xss_data_extractor->extractLNEPSBlock();

  FRENSIE_CHECK_EQUAL( lneps_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lneps_block.front(), 2.0 );
  FRENSIE_CHECK_EQUAL( lneps_block.back(), 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the LBEPS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLBEPSBlock )
{
  Utility::ArrayView<const double> lbeps_block =
    pb_xss_data_extractor->extractLBEPSBlock();

  FRENSIE_CHECK_EQUAL( lbeps_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lbeps_block.front(), 8.800500000000E-02);
  FRENSIE_CHECK_EQUAL( lbeps_block.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the LPIPS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLPIPSBlock )
{
  Utility::ArrayView<const double> lpips_block =
    pb_xss_data_extractor->extractLPIPSBlock();

  FRENSIE_CHECK_EQUAL( lpips_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lpips_block.front(), 2.439024390244E-02 );
  FRENSIE_CHECK_EQUAL( lpips_block.back(), 2.439024390244E-02 );
}

//---------------------------------------------------------------------------//
// Check that the LSWD block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractLSWDBlock )
{
  Utility::ArrayView<const double> lswd_block =
    pb_xss_data_extractor->extractLSWDBlock();

  FRENSIE_CHECK_EQUAL( lswd_block.size(), 23 );
  FRENSIE_CHECK_EQUAL( lswd_block.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( lswd_block.back(), 2091.0 );
}

//---------------------------------------------------------------------------//
// Check that the SWD block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSWDBlock )
{
  Utility::ArrayView<const double> swd_block =
    pb_xss_data_extractor->extractSWDBlock();

  FRENSIE_CHECK_EQUAL( swd_block.size(), 2185 );
  FRENSIE_CHECK_EQUAL( swd_block.front(), 2.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( swd_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the SUBSH block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSUBSHBlock )
{
  Utility::ArrayView<const double> subsh_block =
    pb_xss_data_extractor->extractSUBSHBlock();

  FRENSIE_CHECK_EQUAL( subsh_block.size(), 120 );
  FRENSIE_CHECK_EQUAL( subsh_block.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( subsh_block.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell ENDF designators can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellENDFDesignators )
{
  Utility::ArrayView<const double> subshell_endf_designators =
    pb_xss_data_extractor->extractSubshellENDFDesignators();

  FRENSIE_CHECK_EQUAL( subshell_endf_designators.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_endf_designators.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( subshell_endf_designators.back(), 28.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancies can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellOccupancies )
{
  Utility::ArrayView<const double> subshell_occupancies =
    pb_xss_data_extractor->extractSubshellOccupancies();

  FRENSIE_CHECK_EQUAL( subshell_occupancies.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_occupancies.front(), 2.0 );
  FRENSIE_CHECK_EQUAL( subshell_occupancies.back(), 1.33 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energies can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellBindingEnergies )
{
  auto subshell_be = pb_xss_data_extractor->extractSubshellBindingEnergies();

  FRENSIE_CHECK_EQUAL( subshell_be.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_be.front(), 8.829000000000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_be.back(), 5.290000000000E-06 );
  
  auto subshell_be_in_mev =
    pb_xss_data_extractor->extractSubshellBindingEnergiesInMeV();

  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.front(), 8.829000000000E-02*MeV );
  FRENSIE_CHECK_EQUAL( subshell_be_in_mev.back(), 5.290000000000E-06*MeV );
}

//---------------------------------------------------------------------------//
// Check that the subshell compton interaction cdf can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellComptonInteractionCDF )
{
  Utility::ArrayView<const double> subshell_compton_cdf =
    pb_xss_data_extractor->extractSubshellComptonInteractionCDF();

  FRENSIE_CHECK_EQUAL( subshell_compton_cdf.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_compton_cdf.front(), 2.439024390244E-02 );
  FRENSIE_CHECK_EQUAL( subshell_compton_cdf.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell vacancy transition paths can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSubshellVacancyTransitionPaths )
{
  Utility::ArrayView<const double> subshell_transitions =
    pb_xss_data_extractor->extractSubshellVacancyTransitionPaths();

  FRENSIE_CHECK_EQUAL( subshell_transitions.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_transitions.front(), 1.890000000000E+02 );
  FRENSIE_CHECK_EQUAL( subshell_transitions.back(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the SPHEL block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractSPHELBlock )
{
  Utility::ArrayView<const double> sphel_block =
    pb_xss_data_extractor->extractSPHELBlock();

  FRENSIE_CHECK_EQUAL( sphel_block.size(), 76224 );
  FRENSIE_CHECK_EQUAL( sphel_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( sphel_block.back(), -2.364731020721E+01 );
}

//---------------------------------------------------------------------------//
// Check that the RELO block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractRELOBlock )
{
  Utility::ArrayView<const double> relo_block =
    pb_xss_data_extractor->extractRELOBlock();

  FRENSIE_CHECK_EQUAL( relo_block.size(), 24 );
  FRENSIE_CHECK_EQUAL( relo_block.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( relo_block.back(), 7.764000000000E+03 );
}

//---------------------------------------------------------------------------//
// Check that the XPROB block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractXPROBBlock )
{
  Utility::ArrayView<const double> xprob_block =
    pb_xss_data_extractor->extractXPROBBlock();

  FRENSIE_CHECK_EQUAL( xprob_block.size(), 7764 );
  FRENSIE_CHECK_EQUAL( xprob_block.front(), 3.0 );
  FRENSIE_CHECK_EQUAL( xprob_block.back(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the ESZE block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractESZEBlock )
{
  Utility::ArrayView<const double> esze_block =
    pb_xss_data_extractor->extractESZEBlock();

  FRENSIE_CHECK_EQUAL( esze_block.size(), 14310 );
  FRENSIE_CHECK_EQUAL( esze_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( esze_block.back(), 1.822340000000E+05 );
}

//---------------------------------------------------------------------------//
// Check that the ESZE2 block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractESZE2Block )
{
  Utility::ArrayView<const double> esze2_block =
    pb_xss_data_extractor->extractESZE2Block();

  FRENSIE_CHECK_EQUAL( esze2_block.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electron energy grid can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElectronEnergyGrid )
{
  auto electron_energy_grid =
    pb_xss_data_extractor->extractElectronEnergyGrid();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.000000000000E+05 );

  auto electron_energy_grid_in_mev =
    pb_xss_data_extractor->extractElectronEnergyGridInMeV();

  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.front(), 1.000000000000E-05*MeV );
  FRENSIE_CHECK_EQUAL( electron_energy_grid_in_mev.back(), 1.000000000000E+05*MeV );
}

//---------------------------------------------------------------------------//
// Check that the electron total cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElectronTotalCrossSection )
{
  auto electron_total_cs =
    pb_xss_data_extractor->extractElectronTotalCrossSection();

  FRENSIE_CHECK_EQUAL( electron_total_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_total_cs.front(), 2.629060119800E+09 );
  FRENSIE_CHECK_EQUAL( electron_total_cs.back(), 2.845403136205E+06 );

  auto electron_total_cs_in_barns =
    pb_xss_data_extractor->extractElectronTotalCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.front(), 2.629060119800E+09*barns );
  FRENSIE_CHECK_EQUAL( electron_total_cs_in_barns.back(), 2.845403136205E+06*barns );
}

//---------------------------------------------------------------------------//
// Check that the electron elastic transport cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElasticTransportCrossSection )
{
  Utility::ArrayView<const double> elastic_cs =
    pb_xss_data_extractor->extractElasticTransportCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cs.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electron elastic total cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElasticTotalCrossSection )
{
  Utility::ArrayView<const double> elastic_cs =
    pb_xss_data_extractor->extractElasticTotalCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cs.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the electron elastic cutoff cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElasticCutoffCrossSection )
{
  Utility::ArrayView<const double> elastic_cs =
    pb_xss_data_extractor->extractElasticCutoffCrossSection();

  FRENSIE_CHECK_EQUAL( elastic_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( elastic_cs.front(), 2.489240000000E+09 );
  FRENSIE_CHECK_EQUAL( elastic_cs.back(), 8.830510000000E-02 );

  auto elastic_cs_in_barns =
    pb_xss_data_extractor->extractElasticCutoffCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.front(), 2.489240000000E+09*barns );
  FRENSIE_CHECK_EQUAL( elastic_cs_in_barns.back(), 8.830510000000E-02*barns );
}

//---------------------------------------------------------------------------//
// Check that the electron bremsstrahlung cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBremsstrahlungCrossSection )
{
  auto bremss_cs = pb_xss_data_extractor->extractBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( bremss_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( bremss_cs.front(), 4.869800000000E+03 );
  FRENSIE_CHECK_EQUAL( bremss_cs.back(), 1.954170000000E+03 );

  auto bremss_cs_in_barns =
    pb_xss_data_extractor->extractBremsstrahlungCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.front(), 4.869800000000E+03*barns );
  FRENSIE_CHECK_EQUAL( bremss_cs_in_barns.back(), 1.954170000000E+03*barns );
}

//---------------------------------------------------------------------------//
// Check that the electron excitation cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractExcitationCrossSection )
{
  auto excitation_cs = pb_xss_data_extractor->extractExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( excitation_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( excitation_cs.front(), 8.757550000000E+06 );
  FRENSIE_CHECK_EQUAL( excitation_cs.back(), 1.578610000000E+06 );

  auto excitation_cs_in_barns =
    pb_xss_data_extractor->extractExcitationCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.front(), 8.757550000000E+06*barns );
  FRENSIE_CHECK_EQUAL( excitation_cs_in_barns.back(), 1.578610000000E+06*barns );
}

//---------------------------------------------------------------------------//
// Check that the total electroionization cross section can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractElectroionizationCrossSection )
{
  auto electroionization_cs =
    pb_xss_data_extractor->extractElectroionizationCrossSection();

  FRENSIE_CHECK_EQUAL( electroionization_cs.size(), 477 );
  FRENSIE_CHECK_EQUAL( electroionization_cs.front(), 1.310577000000E+08 );
  FRENSIE_CHECK_EQUAL( electroionization_cs.back(), 1.264838877900E+06 );

  auto electroionization_cs_in_barns =
    pb_xss_data_extractor->extractElectroionizationCrossSectionInBarns();

  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.size(), 477 );
  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.front(), 1.310577000000E+08*barns );
  FRENSIE_CHECK_EQUAL( electroionization_cs_in_barns.back(), 1.264838877900E+06*barns );
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell cross sections can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor,
		   extractElectroionizationSubshellCrossSections )
{
  auto electroionization_subshell_cs =
    pb_xss_data_extractor->extractElectroionizationSubshellCrossSections();

  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.size(), 11448 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs.back(),
		       1.822340000000E+05 );

  auto electroionization_subshell_cs_in_barns =
    pb_xss_data_extractor->extractElectroionizationSubshellCrossSectionsInBarns();

  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.size(), 11448 );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.front(), 0.0*barns );
  FRENSIE_CHECK_EQUAL( electroionization_subshell_cs_in_barns.back(),
		       1.822340000000E+05*barns );
}

//---------------------------------------------------------------------------//
// Check that the EXCIT block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractEXCITBlock )
{
  Utility::ArrayView<const double> excit_block =
    pb_xss_data_extractor->extractEXCITBlock();

  FRENSIE_CHECK_EQUAL( excit_block.size(), 572 );
  FRENSIE_CHECK_EQUAL( excit_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( excit_block.back(), 1.095330000000E-05 );
}

//---------------------------------------------------------------------------//
// Check that the ELASI block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractELASIBlock )
{
  Utility::ArrayView<const double> elasi_block =
    pb_xss_data_extractor->extractELASIBlock();

  FRENSIE_CHECK_EQUAL( elasi_block.size(), 42 );
  FRENSIE_CHECK_EQUAL( elasi_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( elasi_block.back(), 1.392000000000E+03 );
}

//---------------------------------------------------------------------------//
// Check that the ELAS block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractELASBlock )
{
  Utility::ArrayView<const double> elas_block =
    pb_xss_data_extractor->extractELASBlock();

  FRENSIE_CHECK_EQUAL( elas_block.size(), 1562 );
  FRENSIE_CHECK_EQUAL( elas_block.front(), -1.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( elas_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the EION block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractEIONBlock )
{
  Utility::ArrayView<const double> eion_block =
    pb_xss_data_extractor->extractEIONBlock();

  FRENSIE_CHECK_EQUAL( eion_block.size(), 14169 );
  FRENSIE_CHECK_EQUAL( eion_block.front(), 5.000000000000E+00 );
  FRENSIE_CHECK_EQUAL( eion_block.back(), 1.000000000000E+00 );

}

//---------------------------------------------------------------------------//
// Check that the BREMI block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBREMIBlock )
{
  Utility::ArrayView<const double> bremi_block =
    pb_xss_data_extractor->extractBREMIBlock();

  FRENSIE_CHECK_EQUAL( bremi_block.size(), 27 );
  FRENSIE_CHECK_EQUAL( bremi_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( bremi_block.back(), 6.500000000000E+02 );
}

//---------------------------------------------------------------------------//
// Check that the BREME block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBREMEBlock )
{
  Utility::ArrayView<const double> breme_block =
    pb_xss_data_extractor->extractBREMEBlock();

  FRENSIE_CHECK_EQUAL( breme_block.size(), 852 );
  FRENSIE_CHECK_EQUAL( breme_block.front(), 1.000000000000E-07 );
  FRENSIE_CHECK_EQUAL( breme_block.back(), 1.000000000000E+00 );
}

//---------------------------------------------------------------------------//
// Check that the BREML block can be extracted
FRENSIE_UNIT_TEST( XSSEPRDataExtractor, extractBREMLBlock )
{
  Utility::ArrayView<const double> breml_block =
    pb_xss_data_extractor->extractBREMLBlock();

  FRENSIE_CHECK_EQUAL( breml_block.size(), 150 );
  FRENSIE_CHECK_EQUAL( breml_block.front(), 1.000000000000E-05 );
  FRENSIE_CHECK_EQUAL( breml_block.back(), 9.726750000000E+04 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string pb_ace_file_name, pb_ace_table_name;
unsigned pb_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "pb_ace_table",
                                        pb_ace_table_name, "",
                                        "Test Pb ACE table name in ACE file" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "pb_ace_file",
                                        pb_ace_file_name, "",
                                        "Test Pb ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "pb_ace_file_start_line",
                                        pb_ace_file_start_line, 1,
                                        "Test Pb ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize ace file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                          new Data::ACEFileHandler( pb_ace_file_name,
                                                    pb_ace_table_name,
						    pb_ace_file_start_line ) );

  pb_xss_data_extractor.reset(
      new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
				     ace_file_handler->getTableJXSArray(),
				     ace_file_handler->getTableXSSArray() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstXSSEPRDataExtractorPbv12.cpp
//---------------------------------------------------------------------------//
