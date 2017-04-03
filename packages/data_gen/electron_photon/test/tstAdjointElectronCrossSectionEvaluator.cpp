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

double max_ionization_adjoint_energy, max_brem_adjoint_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointCrossSection )
{
  double precision = 1e-5;

  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.361E-05, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.24070944606782875e15,
                                  1e-5 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.88E-05, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.20814984485908125e15,
                                  1e-5 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.123900E-02, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.1037229360055688477e12,
                                  1e-5 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 8.75350E-01, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.7717016620250481367e8,
                                  1e-5 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_adjoint_energy - 6.0e-8,
        precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.2498959635742576211e4,
                                  1e-5 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_adjoint_energy,
        precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.2415414649009922869e4,
                                  1e-5 );


  // Native Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e-5, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.4064216868408593086e1,
                                  1e-5 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 5.0e-4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  3.1844399889852791574e1,
                                  1e-5 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 6.0e4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.435228075256366651e2,
                                  1e-5 );

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

  boost::numeric::odeint::bulirsch_stoer< state_type > integrator( 1e-6, 1e-6 );

  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.361E-05,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.24070943822096700000e+15,
                                  1e-5 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        1.88E-05,
//        integrator );

//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.20814989033250925000e+15,
//                                  1e-6 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        1.123900E-02,
//        integrator );

//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.10372261069091381836e+12,
//                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        8.75350E-01,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.77166062940861403942e+08,
                                  1e-6 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        max_ionization_adjoint_energy - 6.0e-8,
//        integrator );

//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  6.24995750261499561020e+04,
//                                  1e-4 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_adjoint_energy,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.24160868308713252191e+04,
                                  1e-5 );


  // Native Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.40642043030664893877e+01,
                                  1e-4 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  3.18443915788826075186e+01,
                                  1e-4 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.43522797349649721355e+02,
                                  1e-4 );

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
    integrator = boost::numeric::odeint::make_controlled( 1e-20, 0.0, boost::numeric::odeint::runge_kutta_fehlberg78< state_type >() );

  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.361E-05,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.23579293160572525000e+15,
                                  1e-6 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        1.88E-05,
//        integrator );
//
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.20814240684407500000e+15,
//                                  1e-6 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        1.123900E-02,
//        integrator );
//
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.10443306202688964844e+12,
//                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        8.75350E-01,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.76814572461703449488e+08,
                                  1e-6 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        max_ionization_adjoint_energy - 6.0e-8,
//        integrator );
//
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  6.24553306981942005223e+04,
//                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_adjoint_energy,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.21549562750184122706e+04,
                                  1e-6 );
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  6.23727176077972617350e+04,
//                                  1e-6 );


  // Native Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.41257417444869162182e+01,
                                  1e-6 );

//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  6.40588100246348091105e+01,
//                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.98888101438753643890e+01,
                                  1e-6 );
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.98564811027263132814e+01,
//                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.45440228409134562071e+02,
                                  1e-6 );
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.43540180845688951194e+02,
//                                  1e-6 );

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

//  unsigned number_of_steps = 10000;
  unsigned number_of_steps = 500;

  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        1.361E-05,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.24070944489935125000e+15,
                                  1e-5 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        1.88E-05,
//        integrator,
//        number_of_steps );
//
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.20814983800845875000e+15,
//                                  1e-6 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        1.123900E-02,
//        integrator,
//        number_of_steps );
//
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.10372293404933154297e+12,
//                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        8.75350E-01,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.76729600550244659185e+08,
                                  1e-6 );
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  1.77012239739321440458e+08,
//                                  1e-6 );

//  cross_section =
//    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
//        max_ionization_adjoint_energy - 6.0e-8,
//        integrator,
//        number_of_steps );
//
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  6.24981090890891791787e+04,
//                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_adjoint_energy,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.23978697591429445310e+04,
                                  1e-6 );
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  6.24146940556790723349e+04,
//                                  1e-6 );

  // Native Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        1.0e-5,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.40642162585073720038e+01,
                                  1e-5 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        5.0e-4,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.51070455345109451173e+01,
                                  1e-6 );
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  3.11165234069050526955e+01,
//                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection(
        6.0e4,
        integrator,
        number_of_steps );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.43785200767495459877e+06,
                                  1e-6 );
//  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
//                                  7.20023484833667171188e+04,
//                                  1e-6 );

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
                                                      1e-4,
                                                      1e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  5.31863324213552096306e-04,
                                  1e-5 );

  diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 1.1239e-2,
                                                      3.16228,
                                                      1e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.99114216905034926044e-09,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 8.75350E-01,
                                                      max_ionization_adjoint_energy,
                                                      1e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.89708690449891991391e-09,
                                  1e-5 );

  // Native Bremsstralung
  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 5.0e-4,
                                                5.0e-3,
                                                1.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.03626700429070384146,
                                  1e-5 );

  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 6.0e4,
                                                1.0e5,
                                                1.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  4.40196553421104620864e-09,
                                  1e-5 );

  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 1.0e5-5.0e-8,
                                                1.0e5,
                                                1.0e-4 );

  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

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
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = true;
  double evaluation_tol = 1e-7;
  double min_energy = 1e-5;
  double max_energy_nudge_value = 2e-7;
  max_brem_adjoint_energy = 1e5 - max_energy_nudge_value;
  double energy_to_outgoing_energy_nudge_value = 1e-7;

  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> brem_energy_grid =
        data_container->getBremsstrahlungEnergyGrid();

  // Create the reaction
  std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
    bremsstrahlung_reaction;
  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<BremsstrahlungReaction,Utility::LinLinLog>(
    *data_container,
    energy_grid,
    grid_searcher,
    bremsstrahlung_reaction,
    MonteCarlo::TWOBS_DISTRIBUTION,
    correlated_sampling_mode_on,
    unit_based_interpolation_mode_on,
    evaluation_tol );

  // Initialize the hydrogen adjoint cross section evaluator
  native_adjoint_brem_cs.reset( new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
                    bremsstrahlung_reaction,
                    brem_energy_grid,
                    min_energy,
                    max_brem_adjoint_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value ) );
  }

  // Create the Native adjoint electroionization cross section evaluators
  {
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = true;
  double evaluation_tol = 1e-7;
  double min_energy = 1e-5;

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
    electroionization_subshell_reaction,
    correlated_sampling_mode_on,
    unit_based_interpolation_mode_on,
    evaluation_tol );

  binding_energy = data_container->getSubshellBindingEnergy( *shell );

  double max_energy_nudge_value = 2.0*binding_energy;
  double energy_to_outgoing_energy_nudge_value = binding_energy + 1.0e-7;
  max_ionization_adjoint_energy = 1e5 - max_energy_nudge_value;

  native_adjoint_ionization_cs.reset(
    new DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction>(
      electroionization_subshell_reaction,
      ionization_energy_grid,
      min_energy,
      max_ionization_adjoint_energy,
      max_energy_nudge_value,
      energy_to_outgoing_energy_nudge_value ) );
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
