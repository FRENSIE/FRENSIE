//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomEPR14.cpp
//! \author Luke Kersting
//! \brief  Positronatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "MonteCarlo_PositronatomACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationPositronatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::Positronatom> epr14_positronatom;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Positronatom, getTotalCrossSection_epr14 )
{
  double cross_section =
    epr14_positronatom->getTotalCrossSection( 5.2371421547030929e-02 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          4.4981474879191741e+07,
                          1e-12 );

  cross_section =
    epr14_positronatom->getTotalCrossSection( 2e-03 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          3.9416460301500607e+08,
                          1e-12 );
  cross_section =
    epr14_positronatom->getTotalCrossSection( 4e-04 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          9.1706481556832719e+08,
                          1e-12 );
  cross_section =
    epr14_positronatom->getTotalCrossSection( 9e-05 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                          1.5083218251907730e+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_epr14_file_name;
unsigned test_epr14_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_epr14_file",
                                        test_epr14_file_name, "",
                                        "Test EPR14 file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_epr14_file_start_line",
                                        test_epr14_file_start_line, 1,
                                        "Test EPR14 file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                 new Data::ACEFileHandler( test_epr14_file_name,
                                           "79000.14p",
                                           test_epr14_file_start_line ) );
  
  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                      ace_file_handler->getTableNXSArray(),
                      ace_file_handler->getTableJXSArray(),
                      ace_file_handler->getTableXSSArray() ) );

  // Create a void atomic relaxation model
  std::shared_ptr<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

  // Extract the atomic weight
  double atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
    Utility::PhysicalConstants::neutron_rest_mass_amu;

  // Create the simulation properties
  MonteCarlo::SimulationElectronProperties properties;
  
  std::shared_ptr<const MonteCarlo::PositronatomCore> core;
  
  MonteCarlo::PositronatomACEFactory::createPositronatomCore(
                                                  *xss_data_extractor,
                                                  relaxation_model,
                                                  properties,
                                                  core );

  // Create the positronatom
  epr14_positronatom.reset(
    new MonteCarlo::Positronatom( ace_file_handler->getTableName(),
                                  xss_data_extractor->extractAtomicNumber(),
                                  atomic_weight,
                                  *core ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomEPR14.cpp
//---------------------------------------------------------------------------//

