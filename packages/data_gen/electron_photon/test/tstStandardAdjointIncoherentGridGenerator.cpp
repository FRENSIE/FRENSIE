//---------------------------------------------------------------------------//
//!
//! \file   tstStandardAdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Standard adjoint incoherent grid generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "DataGen_AdjointIncoherentCrossSectionHelpers.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "Utility_InverseAngstromUnit.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::AdjointIncoherentGridGenerator>
  linlinlin_grid_generator_free;
std::shared_ptr<DataGen::AdjointIncoherentGridGenerator>
  linloglog_grid_generator_free;
std::shared_ptr<DataGen::AdjointIncoherentGridGenerator>
  logloglog_grid_generator_free;
std::shared_ptr<DataGen::AdjointIncoherentGridGenerator>
  linlinlin_grid_generator_h;
std::shared_ptr<DataGen::AdjointIncoherentGridGenerator>
  linloglog_grid_generator_h;
std::shared_ptr<DataGen::AdjointIncoherentGridGenerator>
  logloglog_grid_generator_h;
std::shared_ptr<DataGen::AdjointIncoherentGridGenerator>
  logloglog_grid_generator_pb;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that an max energy grid can be generated at a single energy
FRENSIE_UNIT_TEST( StandardAdjointIncoherentGridGenerator,
                   generate_single_free )
{
  double nudge_factor = 1e-8;
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor(
                                                                nudge_factor );

  std::vector<double> max_energy_grid, cross_section;

  double max_energy_of_max_cs =
    DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 0.1 );

  // Generate a lin-lin max energy grid at E = 0.1
  linlinlin_grid_generator_free->generate( max_energy_grid,
                                           cross_section,
                                           0.1 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 43 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                  0.1*(1.0+nudge_factor),
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                  20.2,
                                  1e-6 );
  FRENSIE_CHECK_EQUAL(
                 max_energy_grid[max_energy_grid.size()-2],
                 max_energy_of_max_cs );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 43 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  2.54954928358413249e-08,
                                  1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.701697560627866257,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     cross_section[cross_section.size()-2],
                     0.701697560627866257,
                     1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-log max energy grid at E = 0.1
  linloglog_grid_generator_free->generate( max_energy_grid,
                                           cross_section,
                                           0.1 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 40 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                  0.1*(1.0+nudge_factor),
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                  20.2,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                 max_energy_grid[max_energy_grid.size()-2],
                 max_energy_of_max_cs,
                 1e-6 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 40 );


  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  2.54954928358413249e-08,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.701697560627866257,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     cross_section[cross_section.size()-2],
                     0.701697560627866257,
                     1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-lin max energy grid at E = 1.0
  linlinlin_grid_generator_free->generate( max_energy_grid,
                                           cross_section,
                                           1.0 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 64 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                         1.0*(1.0+nudge_factor),
                         1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                  20.2,
                                  1e-6 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 64 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  2.54954930897518544e-09,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.397416434130255625,
                                  1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-log max energy grid at E = 1.0
  linloglog_grid_generator_free->generate( max_energy_grid,
                                           cross_section,
                                           1.0 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 35 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                  1.0*(1.0+nudge_factor),
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                  20.2,
                                  1e-6 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 35 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  2.54954930897518544e-09,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.397416434130255625,
                                  1e-6 );

  max_energy_grid.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that an max energy grid can be generated at a single energy
FRENSIE_UNIT_TEST( StandardAdjointIncoherentGridGenerator, generate_single_h )
{
  double nudge_factor = 1e-8;
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor(
                                                                nudge_factor );

  std::vector<double> max_energy_grid, cross_section;

  double max_energy_of_max_cs =
    DataGen::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 0.1 );

  // Generate a lin-lin max energy grid at E = 0.1
  linlinlin_grid_generator_h->generate( max_energy_grid,
                                        cross_section,
                                        0.1 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 36 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                  0.1*(1.0+nudge_factor),
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                  20.2,
                                  1e-6 );
  FRENSIE_CHECK_EQUAL(
                 max_energy_grid[max_energy_grid.size()-2],
                 max_energy_of_max_cs );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 36 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  1.28144457314458103e-12,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.70123552310933901,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                     cross_section[cross_section.size()-2],
                     0.70123552310933901,
                     1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-log max energy grid at E = 0.1
  linloglog_grid_generator_h->generate( max_energy_grid,
                                        cross_section,
                                        0.1 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 255 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                    0.1*(1.0+nudge_factor),
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                    20.2,
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                   max_energy_grid[max_energy_grid.size()-2],
                 max_energy_of_max_cs,
                   1e-6 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 255 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  1.28144457314458103e-12,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.70123552310933901,
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                       cross_section[cross_section.size()-2],
                     0.70123552310933901,
                       1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a Log-Log max energy grid at E = 0.1
  logloglog_grid_generator_h->generate( max_energy_grid,
                                        cross_section,
                                        0.1 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 356 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                    0.1*(1.0+nudge_factor),
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                    20.2,
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                   max_energy_grid[max_energy_grid.size()-2],
                   max_energy_of_max_cs,
                   1e-6 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 356 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  1.28144457314458103e-12,
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.70123552310933901,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
                       cross_section[cross_section.size()-2],
                     0.70123552310933901,
                       1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-lin max energy grid at E = 1.0
  linlinlin_grid_generator_h->generate( max_energy_grid,
                                        cross_section,
                                        1.0 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 62 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                    1.0*(1.0+nudge_factor),
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                    20.2,
                                    1e-6 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), 62 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  1.28233099739908285e-12,
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.397416434130255625,
                                    1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a lin-log max energy grid at E = 1.0
  linloglog_grid_generator_h->generate( max_energy_grid,
                                        cross_section,
                                        1.0 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 33 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                    1.0*(1.0+nudge_factor),
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                    20.2,
                                    1e-6 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 33 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  1.28233099739908285e-12,
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.397416434130255625,
                                    1e-6 );

  max_energy_grid.clear();
  cross_section.clear();

  // Generate a log-log max energy grid at E = 1.0
  logloglog_grid_generator_h->generate( max_energy_grid,
                                        cross_section,
                                        1.0 );

  FRENSIE_CHECK_EQUAL( max_energy_grid.size(), 367 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.front(),
                                  1.0*(1.0+nudge_factor),
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                    20.2,
                                    1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( max_energy_grid.back(),
                                    20.2,
                                    1e-15 );

  FRENSIE_CHECK_EQUAL( cross_section.size(), 367 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.front(),
                                  1.28233099739908285e-12,
                                    1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section.back(),
                                  0.397416434130255625,
                                    1e-6 );

  max_energy_grid.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
FRENSIE_UNIT_TEST( StandardAdjointIncoherentGridGenerator, generate_free )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor(
                                                                        1e-8 );

  std::shared_ptr<DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog> > derived_pointer = std::shared_ptr_dynamic_cast<DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog> >( logloglog_grid_generator_free );

  derived_pointer->setConvergenceTolerance( 0.05 );

  std::vector<double> energy_grid;
  std::vector<std::vector<double> > max_energy_grids, cross_section;

  logloglog_grid_generator_free->generate( energy_grid,
                                           max_energy_grids,
                                           cross_section );

  FRENSIE_CHECK_EQUAL( energy_grid.size(), 93 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_grid.front(), 0.001, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_grid.back(), 20.0, 1e-6 );


  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
FRENSIE_UNIT_TEST( StandardAdjointIncoherentGridGenerator, generate_h )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor(
                                                                        1e-8 );

  std::shared_ptr<DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog> > derived_pointer = std::shared_ptr_dynamic_cast<DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog> >( logloglog_grid_generator_h );

  derived_pointer->setConvergenceTolerance( 0.05 );

  std::vector<double> energy_grid;
  std::vector<std::vector<double> > max_energy_grids, cross_section;

  logloglog_grid_generator_h->generate( energy_grid,
                                        max_energy_grids,
                                        cross_section );

  FRENSIE_CHECK_EQUAL( energy_grid.size(), 110 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_grid.front(), 0.001, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_grid.back(), 20.0, 1e-6 );

  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Check that a full 2D grid can be generated
FRENSIE_UNIT_TEST( StandardAdjointIncoherentGridGenerator, generate_pb )
{
  DataGen::AdjointIncoherentGridGenerator::setMinTableEnergy( 0.001 );
  DataGen::AdjointIncoherentGridGenerator::setMaxTableEnergy( 20.0 );
  DataGen::AdjointIncoherentGridGenerator::setEnergyToMaxEnergyNudgeFactor(
                                                                          1e-8 );

  std::shared_ptr<DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog> > derived_pointer = std::shared_ptr_dynamic_cast<DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog> >( logloglog_grid_generator_pb );

  derived_pointer->setConvergenceTolerance( 0.05 );

  std::vector<double> energy_grid;
  std::vector<std::vector<double> > max_energy_grids, cross_section;

  logloglog_grid_generator_pb->generate( energy_grid,
                                           max_energy_grids,
                                           cross_section );

  FRENSIE_CHECK_EQUAL( energy_grid.size(), 121 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_grid.front(), 0.001, 1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( energy_grid.back(), 20.0, 1e-6 );

  energy_grid.clear();
  max_energy_grids.clear();
  cross_section.clear();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_ace_file_name, test_h_ace_table_name;
std::string test_pb_ace_file_name, test_pb_ace_table_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_ace_file",
                                        test_h_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_ace_table",
                                        test_h_ace_table_name, "",
                                        "Test ACE table name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_pb_ace_file",
                                        test_pb_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_pb_ace_table",
                                        test_pb_ace_table_name, "",
                                        "Test ACE table name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create the adjoint Klein-Nishina cross section
    std::shared_ptr<MonteCarlo::KleinNishinaAdjointPhotonScatteringDistribution>
      adjoint_incoherent_dist(
        new MonteCarlo::KleinNishinaAdjointPhotonScatteringDistribution(
              DataGen::AdjointIncoherentGridGenerator::getMaxTableEnergy() ) );

    // Initialize the grid generator
    linlinlin_grid_generator_free.reset( new DataGen::StandardAdjointIncoherentGridGenerator<Utility::LinLinLin>(
                                                   adjoint_incoherent_dist ) );

    linloglog_grid_generator_free.reset( new DataGen::StandardAdjointIncoherentGridGenerator<Utility::LinLogLog>(
                                                   adjoint_incoherent_dist ) );

    logloglog_grid_generator_free.reset( new DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog>(
                                                   adjoint_incoherent_dist ) );
  }

  {
    // Create a file handler and data extractor for hydrogen
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                               new Data::ACEFileHandler( test_h_ace_file_name,
                                                         test_h_ace_table_name,
                                                         1u ) );

    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                                new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

    // Create the scattering function
    Utility::ArrayView<const double> jince_block =
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    std::vector<double> recoil_momentum( jince_block( 0, scatt_func_size ));
    std::vector<double> scattering_func_vals(
                             jince_block( scatt_func_size, scatt_func_size ) );

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseAngstrom,void> > raw_scattering_function(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>(
                           recoil_momentum,
                           scattering_func_vals ) );

    std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
      new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );

    // Create the Waller-Hartee incoherent adjoint scattering distribution
    std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
      adjoint_incoherent_dist(
           new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution(
                  DataGen::AdjointIncoherentGridGenerator::getMaxTableEnergy(),
                  scattering_function ) );

    linlinlin_grid_generator_h.reset( new DataGen::StandardAdjointIncoherentGridGenerator<Utility::LinLinLin>(
                                                       adjoint_incoherent_dist,
                                                       1e-3,
                                                       0.001,
                                                       1e-15 ) );

    linloglog_grid_generator_h.reset( new DataGen::StandardAdjointIncoherentGridGenerator<Utility::LinLogLog>(
                                                       adjoint_incoherent_dist,
                                                       1e-3,
                                                       0.001,
                                                       1e-15 ) );

    logloglog_grid_generator_h.reset( new DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog>(
                                                       adjoint_incoherent_dist,
                                                       1e-3,
                                                       0.001,
                                                       1e-15 ) );
  }

  {
    // Create a file handler and data extractor for lead
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                              new Data::ACEFileHandler( test_pb_ace_file_name,
                                                        test_pb_ace_table_name,
                                                        1u ) );

    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                                new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

    // Create the scattering function
    Utility::ArrayView<const double> jince_block =
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    std::vector<double> recoil_momentum( jince_block( 0, scatt_func_size ));

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseAngstrom,void> > raw_scattering_function(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>(
                           recoil_momentum,
                           jince_block( scatt_func_size, scatt_func_size ) ) );

    std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
      new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );

    // Create the Waller-Hartree incoherent adjoint scattering distribution
    std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
      adjoint_incoherent_dist(
           new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution(
                  DataGen::AdjointIncoherentGridGenerator::getMaxTableEnergy(),
                  scattering_function ) );

    logloglog_grid_generator_pb.reset( new DataGen::StandardAdjointIncoherentGridGenerator<Utility::LogLogLog>(
                                                   adjoint_incoherent_dist ) );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardAdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
