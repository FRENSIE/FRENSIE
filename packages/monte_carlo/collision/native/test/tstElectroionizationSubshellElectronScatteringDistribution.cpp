//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Electroionization electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestElectroionizationSubshellElectronScatteringDistribution : public MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution
{
public:
  TestElectroionizationSubshellElectronScatteringDistribution(
    const std::shared_ptr<Utility::FullyTabularTwoDDistribution>&
      electroionization_subshell_scattering_distribution,
    const double binding_energy )
    : MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
        electroionization_subshell_scattering_distribution,
        binding_energy )
  { /* ... */ }

  ~TestElectroionizationSubshellElectronScatteringDistribution()
  { /* ... */ }

  // Allow public access to the ElectroionizationSubshellElectronScatteringDistribution protected member functions
  using MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution::outgoingAngle;

};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  ace_ionization_dist, unit_base_ionization_dist,
  unit_correlated_ionization_dist, correlated_ionization_dist;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   getBindingEnergy )
{
  // Get binding energy
  double binding_energy =
    ace_ionization_dist->getBindingEnergy();

  // Test original electron
  TEST_EQUALITY_CONST( binding_energy, 8.8290E-02 );
}

//---------------------------------------------------------------------------//
// Check that the max secondary (knock-on) electron energy can be returned
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   getMaxSecondaryEnergyAtIncomingEnergy )
{
  // Get max energy
  double max_energy =
    ace_ionization_dist->getMaxSecondaryEnergyAtIncomingEnergy( 8.829E-02 );

  // Test original electron
  TEST_EQUALITY_CONST( max_energy, 0.0 );

  // Get max energy
  max_energy =
    ace_ionization_dist->getMaxSecondaryEnergyAtIncomingEnergy( 1e5 );

  // Test original electron
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 4.9999955855E+04, 1e-12 );

  // Get max energy
  max_energy =
    ace_ionization_dist->getMaxSecondaryEnergyAtIncomingEnergy( 2.0 );

  // Test original electron
  UTILITY_TEST_FLOATING_EQUALITY( max_energy, 9.55855E-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_ace )
{
  double pdf = ace_ionization_dist->evaluate( 8.829e-2, 5e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 683.2234482287432229, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.0671460400747981e+02, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.4576996990397919074, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.045394577710E+00, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.399431656723E-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_unit_base_correlated )
{
  double pdf = unit_correlated_ionization_dist->evaluate( 8.829e-2, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.6866000434174901e+05, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.6794064728877693e+01, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.9611321793168750e-02, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.1815828429294956e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.4636700787675897e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 8.4497193189141950e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_unit_base )
{
  double pdf = unit_base_ionization_dist->evaluate( 8.829e-2, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.7059433323866402e+05, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.2145110535548639e+01, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.7239569315597329e-02, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.0413727753540816e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.9786207533174264e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 8.4497193189141911e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_ace )
{
  double pdf = ace_ionization_dist->evaluatePDF( 8.829e-2, 5e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 683.2234482287432229, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.0671460400747981e+02, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.4576996990397919074, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.045394577710E+00, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 4.399431656723E-07, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.337458903100E-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_unit_base_correlated )
{
  double pdf = unit_correlated_ionization_dist->evaluatePDF( 8.829e-2, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.6865999321744699e+05, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.6794063002002872e+01, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.9611317283132534e-02, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.1815824201618231e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.4636692194095449e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 8.4497177573288197e-11, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.2480895846405665e-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_unit_base )
{
  double pdf = unit_base_ionization_dist->evaluatePDF( 8.829e-2, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.7059431425324091e+05, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.2145109130569701e+01, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.7239567109895083e-02, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.0413724333040529e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 1.9786201034182761e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 8.4497177573288068e-11, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf, 2.2480895846405767e-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_ace )
{
  double cdf = ace_ionization_dist->evaluateCDF( 8.829e-2, 5e-8 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 0.0, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 2.92009701772965E-01, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 0.67056930428109073894, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 7.99240642349262E-01, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 7.299181455072E-01, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.999123864280E-01, 1e-10 );

  cdf = ace_ionization_dist->evaluateCDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_unit_base_correlated )
{
  double cdf = unit_correlated_ionization_dist->evaluateCDF( 8.829e-2, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 0.0, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9364828663505689e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9984273751835129e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9998825717709872e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9998150891124138e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9999998501226084e-01, 1e-10 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_unit_base )
{
  double cdf = unit_base_ionization_dist->evaluateCDF( 8.829e-2, 1e-7 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 0.0, 1e-12 );

  cdf = unit_base_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9030213872906114e-01, 1e-12 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9964169418960402e-01, 1e-12 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9997873853576236e-01, 1e-12 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9996847362592778e-01, 1e-12 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 9.9999998501226084e-01, 1e-10 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e5, 5e4 );
  UTILITY_TEST_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron
  ace_ionization_dist->sample( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );


  incoming_energy = 1.1;
  // sample the electron
  ace_ionization_dist->sample( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 4.34461320777921E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 1e-7, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
/* Note: This tests a bug that caused electroionization to return non-realistic
 * knock-on energies. A unit based sampling routine was used to fix the problem.
 */
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 1.0-1e-15;
  fake_stream[3] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 6.041e-05;
  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron at the min random number
  unit_base_ionization_dist->sample( incoming_energy,
                                     knock_on_energy,
                                     knock_on_angle_cosine );

  // Test knock-on electron at the min random number
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 4.0687255489257182e-02, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 1.0E-07, 1e-12 );

  // sample the electron at the max random number
  unit_base_ionization_dist->sample( incoming_energy,
                                     knock_on_energy,
                                     knock_on_angle_cosine );

  // Test knock-on electron at the max random number
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 6.7795576315906780e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 2.7765e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
/* Note: This tests a bug that caused electroionization to return non-realistic
 * knock-on energies with a correlated sampling routine.
 * The non-realistic sampled values can be rejected.
 */
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on_native_correlated )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0-1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 6.041e-05;
  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron at the min random number
  correlated_ionization_dist->sample( incoming_energy,
                                                knock_on_energy,
                                                knock_on_angle_cosine );

  // Test knock-on electron at the min random number
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.0406872554892572, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 1.0E-07, 1e-12 );

  // sample the electron at the max random number
  correlated_ionization_dist->sample( incoming_energy,
                                                knock_on_energy,
                                                knock_on_angle_cosine );

  // Test knock-on electron at the max random number
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 6.680945582865936982e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 2.696314156988312136e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   samplePrimaryAndSecondary_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;

  double outgoing_energy, knock_on_energy,
         scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  ace_ionization_dist->samplePrimaryAndSecondary(
        incoming_energy,
        outgoing_energy,
        knock_on_energy,
        scattering_angle_cosine,
        knock_on_angle_cosine );

  // Test original electron
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.964446703542646, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 8.706573789423E-01, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sampleAndRecordTrials_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;

  double incoming_energy = 1.0;

  double knock_on_energy, scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  ace_ionization_dist->sampleAndRecordTrials( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine,
                                              trials );

  // Test trials
  TEST_EQUALITY_CONST( trials, 1.0 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   scatterElectron_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  ace_ionization_dist->scatterElectron( electron,
                                        bank,
                                        shell_of_interaction );

  // Test original electron
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 0.964446703542646, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.706573789423E-01, 1e-12 );

  // Test knock-on electron
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.279436961765390, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.105262105768E-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
TEUCHOS_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   scatterPositron_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1.0 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter positron
  ace_ionization_dist->scatterPositron( positron,
                                        bank,
                                        shell_of_interaction );

  // Test original positron
  TEST_FLOATING_EQUALITY( positron.getZDirection(), 7.8974722856283108e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( positron.getEnergy(), 4.5585500000302387e-01, 1e-12 );
  std::cout << std::setprecision(16) << std::scientific << "positron.getZDirection() = \t" << positron.getZDirection() << std::endl;
  std::cout << std::setprecision(16) << std::scientific << "positron.getEnergy() = \t" << positron.getEnergy() << std::endl;

  // Test knock-on positron
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 07.8974722855920831e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 4.5585499999697615e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create ACE distribution
  {
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
     new Data::ACEFileHandler( test_ace_file_name,
                               test_ace_table_name,
                               1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  // Extract the cross sections energy grid
  Teuchos::ArrayView<const double> energy_grid =
    xss_data_extractor->extractElectronEnergyGrid() ;

  // Extract the subshell information
  Teuchos::ArrayView<const double> subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the electroionization data block (EION)
  Teuchos::ArrayView<const double> eion_block(
    xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of subshells (N_s)
  int num_shells = subshell_endf_designators.size();

  // Extract the number of knock-on tables by subshell (N_i)
  Teuchos::Array<double> num_tables(eion_block(0,num_shells));

  // Extract the location of info about knock-on tables by subshell
  Teuchos::Array<double> table_info(eion_block(num_shells,num_shells));

  // Extract the location of knock-on tables by subshell
  Teuchos::Array<double> table_loc(eion_block(2*num_shells,num_shells));

  // Subshell
  unsigned subshell = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  Teuchos::Array<double> table_energy_grid(eion_block( subshell_info,
                                                       num_tables[subshell] ) );

  // Extract the length of the knock-on sampling tables
  Teuchos::Array<double> table_length(eion_block(
                               subshell_info + num_tables[subshell],
                               num_tables[subshell] ) );

  // Extract the offset of the knock-on sampling tables
  Teuchos::Array<double> table_offset(eion_block(
                             subshell_info + 2*num_tables[subshell],
                             num_tables[subshell] ) );

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType
     function_data( num_tables[subshell] );

  for( unsigned n = 0; n < num_tables[subshell]; ++n )
  {
    function_data[n].first = table_energy_grid[n];

    function_data[n].second.reset(
     new Utility::HistogramDistribution(
      eion_block( subshell_loc + table_offset[n], table_length[n] ),
      eion_block( subshell_loc + table_offset[n] + table_length[n] + 1,
                  table_length[n] - 1),
      true ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LinLinLin,Utility::Correlated>(
            function_data,
            1e-6,
            1e-12 ) );

  // Create the distributions
  ace_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energies[subshell] ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();
  }

  // Create Native distribution
  {
  // Create the native data file container
  Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer( test_native_file_name ) );

  std::set<unsigned> subshells = data_container->getSubshells();

  unsigned subshell = *subshells.find(6);
  double binding_energy =
    data_container->getSubshellBindingEnergy( subshell );

  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
    data_container->getElectroionizationEnergyGrid( subshell );

  // Create the scattering function
  Utility::FullyTabularTwoDDistribution::DistributionType
     function_data( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    function_data[n].first = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    Teuchos::Array<double> recoil_energy(
        data_container->getElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    Teuchos::Array<double> pdf(
        data_container->getElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    function_data[n].second.reset(
      new const Utility::TabularDistribution<Utility::LogLog>( recoil_energy,
                                                               pdf ) );
  }

  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog,Utility::UnitBase>(
            function_data,
            1e-6,
            1e-12 ) );

  // Create the distributions
  unit_base_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energy ) );
  }
  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
            function_data,
            1e-6,
            1e-12 ) );

  // Create the distributions
  unit_correlated_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energy ) );
  }
  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularTwoDDistribution> subshell_distribution(
    new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::LogLogLog,Utility::Correlated>(
            function_data,
            1e-6,
            1e-12 ) );

  // Create the distributions
  correlated_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energy ) );
  }
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
