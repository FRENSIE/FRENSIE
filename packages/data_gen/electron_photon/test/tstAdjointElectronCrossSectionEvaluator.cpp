//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronCrossSectionEvaluator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/numeric/odeint.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectronCrossSectionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Typedefs
//---------------------------------------------------------------------------//
  typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
    ElectroionizationReaction;

  typedef MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> 
    BremsstrahlungReaction;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> >
  native_adjoint_ionization_cs;

std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >
  ace_adjoint_brem_cs, native_adjoint_brem_cs;

double binding_energy;

double max_ionization_subshell_adjoint_energy, max_brem_adjoint_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointCrossSection )
{
  double precision = 1e-16;

  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.361E-05, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  139697665948165.39062,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.88E-05, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  79238679438795.984375,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.123900E-02, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  206857228.81656169891,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 8.75350E-01, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  125955.16402119601844,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy - 6.0e-8,
        precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  62498.955793047840416,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy,
        precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  62415.410824211663567,
                                  1e-6 );

  // ACE Bremsstrahlung
  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e-5, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  43.721988052516138623,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 5.0e-4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  27.299866535868648754,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 6.0e4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  0.95396344926418752408,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e5, precision );

  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // ACE Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e-5, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  43.499364453430203525,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 5.0e-4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  27.374363809080310972,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 6.0e4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  0.95353481301793019398,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e5, precision );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointCrossSection_bulirsch_stoer )
{
  typedef std::vector<long double> state_type;

  boost::numeric::odeint::bulirsch_stoer< state_type > integrator( 1e-4, 1e-4 );


  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.361E-05,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.39697667397453E+14,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.88E-05,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  7.92386682832987E+13,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.123900E-02,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.07025626751333E+08,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        8.75350E-01,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.25942268435020E+05,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy - 6.0e-8,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.25024074584368E+04,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.23966194750117E+04,
                                  1e-6 );


  // ACE Bremsstrahlung
  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.36682445857224E+01,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.72839592308506E+01,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  3.20507974678438E+00,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e5,
        integrator );

  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // ACE Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.35677519110254E+01,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.73538849445199E+01,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.03971446875982E+00,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e5,
        integrator );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointCrossSection_runge_kutta_fehlberg78 )
{
  typedef std::vector<long double> state_type;

  boost::numeric::odeint::controlled_runge_kutta< boost::numeric::odeint::runge_kutta_fehlberg78< state_type > >
    integrator = boost::numeric::odeint::make_controlled( 1e-30, 0.0, boost::numeric::odeint::runge_kutta_fehlberg78< state_type >() );

  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.361E-05,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.39697663987778E+14,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.88E-05,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  7.92386668832148E+13,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.123900E-02,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.06856200238313E+08,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        8.75350E-01,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  3.38847968548376E+04,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy - 6.0e-8,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.24061742400031E+04,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.23572420814518E+04,
                                  1e-6 );


  // ACE Bremsstrahlung
  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.35919675141220E+01,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.51864794749388E+01,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  9.52796360800739E-01,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e5,
        integrator );

  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // ACE Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.33754648058720E+01,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.58384144376514E+01,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  9.53570206185442E-01,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e5,
        integrator );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointCrossSection_runge_kutta_fehlberg78_steps )
{
  typedef std::vector<long double> state_type;

  boost::numeric::odeint::runge_kutta_fehlberg78< state_type > integrator;

  unsigned number_of_steps = 10000;

  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.361E-05,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.39697665914982E+14,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.88E-05,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  7.92386683377038E+13,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.123900E-02,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.06855086964100E+08,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        8.75350E-01,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  5.12187501953332E+04,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy - 6.0e-8,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.24981052463153E+04,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.24146902309549E+04,
                                  1e-6 );


  // ACE Bremsstrahlung
  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.37272700164298E+01,
                                  2e-5 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.23310895865381E+01,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  3.03690935369109E-01,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e5,
        integrator,
        number_of_steps );

  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // ACE Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.35055262457013E+01,
                                  2e-5 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.23202012265406E+01,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  3.03154232437691E-01,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e5,
        integrator,
        number_of_steps );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointPDF )
{
  // Native Electroionization
  double diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 1.88E-05,
                                                      1.0E-04,
                                                      1.0e-16 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  4.99027E+07*12876.48039/79238679438792.5625,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 1.123900E-02,
                                                      3.16228,
                                                      1.0e-16 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  2.19766977908530E+03/206857228.81668719649,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 8.75350E-01,
                                                      max_ionization_subshell_adjoint_energy,
                                                      1.0e-16 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  3.36107129975999E-01/125955.16376563441008,
                                  1.0e-6 );

  // ACE Bremsstrahlung
  diff_cross_section =
    ace_adjoint_brem_cs->evaluateAdjointPDF( 5.0e-4,
                                             5.0e-3,
                                             1.0e-16 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  2.763762632859210E+01/27.299866535868648754,
                                  1e-6 );

  diff_cross_section =
    ace_adjoint_brem_cs->evaluateAdjointPDF( 6.0e4,
                                             1.0e5,
                                             1.0e-16 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  5.641165944163830E-07/0.95396356210989363689,
                                  1e-6 );

  diff_cross_section =
    ace_adjoint_brem_cs->evaluateAdjointPDF( 1.0e5-5.0e-8,
                                             1.0e5,
                                             1.0e-16 );

  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );


  // Native Bremsstralung
  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 5.0e-4,
                                                5.0e-3,
                                                1.0e-16 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.2054819285461100264,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 6.0e4,
                                                1.0e5,
                                                1.0e-16 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  6.6256883700079266363e-07,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 1.0e5-5.0e-8,
                                                1.0e5,
                                                1.0e-16 );

  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create ACE adjoint brem cross section evaluator
  {
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );

  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  // Bremsstrahlung cross section with zeros removed
  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;

  MonteCarlo::ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
			energy_grid,
			xss_data_extractor->extractBremsstrahlungCrossSection(),
			bremsstrahlung_cross_section,
			threshold_energy_index );

  // Extract the bremsstrahlung scattering information data block (BREMI)
  Teuchos::ArrayView<const double> bremi_block =
    xss_data_extractor->extractBREMIBlock();

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;

  // Extract the electron energy grid for bremsstrahlung energy distributions
  Teuchos::Array<double> electron_energy_grid(bremi_block(0,N));

  // Extract the table lengths for bremsstrahlung energy distributions
  Teuchos::Array<double> table_length(bremi_block(N,N));

  // Extract the offsets for bremsstrahlung energy distributions
  Teuchos::Array<double> offset(bremi_block(2*N,N));

  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Teuchos::ArrayView<const double> breme_block =
    xss_data_extractor->extractBREMEBlock();

  // Create the bremsstrahlung scattering functions
  MonteCarlo::TwoDDistribution energy_loss_distribution( N );

  for( unsigned n = 0; n < N; ++n )
  {
    energy_loss_distribution[n].first = electron_energy_grid[n];

    energy_loss_distribution[n].second.reset(
	  new Utility::HistogramDistribution(
		 breme_block( offset[n], table_length[n] ),
		 breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }

  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    bremsstrahlung_distribution(
        new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
            energy_loss_distribution ) );

  // Create the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
        energy_grid,
        energy_grid[0],
        energy_grid[energy_grid.size()-1],
        energy_grid.size()/10+1 ) );

  std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
    bremsstrahlung_reaction(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            bremsstrahlung_cross_section,
            threshold_energy_index,
            grid_searcher,
            bremsstrahlung_distribution ) );

  std::vector<double> brem_energy_grid(
    electron_energy_grid.begin(),
    electron_energy_grid.end() );

  // Initialize the hydrogen adjoint cross section evaluator
  ace_adjoint_brem_cs.reset( new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
                    bremsstrahlung_reaction,
                    brem_energy_grid,
                    1e-5,
                    1e5,
                    0.0,
                    0.0 ) );
  }

  // Create the native data file container
  std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer(
        test_native_file_name ) );

  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container->getElectronEnergyGrid().begin(),
                      data_container->getElectronEnergyGrid().end() );

  // Create the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
        energy_grid,
        energy_grid[0],
        energy_grid[energy_grid.size()-1],
        energy_grid.size()/10+1 ) );

  // Create Native adjoint brem cross section evaluator
  {
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> brem_energy_grid =
        data_container->getBremsstrahlungEnergyGrid();

  // Create the reaction
  std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
    bremsstrahlung_reaction;
  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<BremsstrahlungReaction>(
    *data_container,
    energy_grid,
    grid_searcher,
    bremsstrahlung_reaction,
    MonteCarlo::TWOBS_DISTRIBUTION );

  // Initialize the hydrogen adjoint cross section evaluator
  native_adjoint_brem_cs.reset( new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
                    bremsstrahlung_reaction,
                    brem_energy_grid,
                    1e-5,
                    1e5,
                    0.0,
                    0.0 ) );
  }

  // Create the Native adjoint electroionization cross section evaluators
  {
  // Extract the subshell information
  std::set<unsigned> subshells = data_container->getSubshells();

  Data::SubshellType subshell_type;

  std::set<unsigned>::iterator shell = subshells.begin();

  // Get the energies for which knock-on sampling tables are given
  std::vector<double> ionization_energy_grid =
    data_container->getElectroionizationEnergyGrid( *shell );

  // Create the subshell electroelectric reaction
  std::shared_ptr<ElectroionizationReaction> electroionization_subshell_reaction;
  MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<ElectroionizationReaction>(
    *data_container,
    energy_grid,
    grid_searcher,
    *shell,
    electroionization_subshell_reaction );

  binding_energy = data_container->getSubshellBindingEnergy( *shell );

  max_ionization_subshell_adjoint_energy = 1e5 - 2.0*binding_energy;

  native_adjoint_ionization_cs.reset(
    new DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction>(
      electroionization_subshell_reaction,
      ionization_energy_grid,
      1e-5,
      max_ionization_subshell_adjoint_energy,
      2.0*binding_energy,
      binding_energy + 1.0e-7 ) );
  }

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
// end tstAdjointElectronCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
