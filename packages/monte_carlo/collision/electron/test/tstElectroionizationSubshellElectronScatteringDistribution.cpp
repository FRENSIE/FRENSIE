//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Electroionization electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestElectroionizationSubshellElectronScatteringDistribution : public MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution
{
public:
  TestElectroionizationSubshellElectronScatteringDistribution(
    const std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution>&
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

std::shared_ptr<MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
  ace_ionization_dist, unit_base_ionization_dist,
  unit_correlated_ionization_dist, correlated_ionization_dist;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   getBindingEnergy )
{
  // Get binding energy
  double binding_energy =
    ace_ionization_dist->getBindingEnergy();

  // Test original electron
  FRENSIE_CHECK_EQUAL( binding_energy, 8.8290E-02 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_ace )
{
  double pdf = ace_ionization_dist->evaluate( 8.829e-2, 5e-8 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 683.2234482287432229, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.0671460400747981e+02, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.4576996990397919074, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.045394577710E+00, 1e-12 );

  pdf = ace_ionization_dist->evaluate( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 4.399431656723E-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_unit_base_correlated )
{
  double pdf = unit_correlated_ionization_dist->evaluate( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.686609585545175651e+05, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.679251358474245848e+01, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.960842280963701056e-02, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.181572340246931117e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.463650607155497925e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluate( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.4497193189141950e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluate_unit_base )
{
  double pdf = unit_base_ionization_dist->evaluate( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.705943332386640250e+05, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.214511053554863906e+01, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.723956931559732925e-02, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.041372775354081575e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.978620753317426450e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluate( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.449719318914194985e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_ace )
{
  double pdf = ace_ionization_dist->evaluatePDF( 8.829e-2, 5e-8 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 683.2234482287432229, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.0671460400747981e+02, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.4576996990397919074, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.045394577710E+00, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 4.399431656723E-07, 1e-12 );

  pdf = ace_ionization_dist->evaluatePDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.337458903100E-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_unit_base_correlated )
{
  double pdf = unit_correlated_ionization_dist->evaluatePDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.686609474301526207e+05, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.679251185801403778e+01, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.960841830018341184e-02, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.181571917482869945e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.463649747804036948e-04, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.4497177573288197e-11, 1e-12 );

  pdf = unit_correlated_ionization_dist->evaluatePDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.2480895846405665e-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluatePDF_unit_base )
{
  double pdf = unit_base_ionization_dist->evaluatePDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.705943142532409111e+05, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.214510913056970054e+01, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.723956710989508340e-02, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.041372433304052866e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.978620103418276112e-04, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.449717757328819723e-11, 1e-12 );

  pdf = unit_base_ionization_dist->evaluatePDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.248089584640566462e-15, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_ace )
{
  double cdf = ace_ionization_dist->evaluateCDF( 8.829e-2, 5e-8 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 2.92009701772965E-01, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 0.67056930428109073894, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.99240642349262E-01, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 7.299181455072E-01, 1e-12 );

  cdf = ace_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.999123864280E-01, 1e-10 );

  cdf = ace_ionization_dist->evaluateCDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_unit_base_correlated )
{
  double cdf = unit_correlated_ionization_dist->evaluateCDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.936486081837607731e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.998427516770949097e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.999882572442484463e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.999815090034120946e-01, 1e-12 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.999999850122608391e-01, 1e-10 );

  cdf = unit_correlated_ionization_dist->evaluateCDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   evaluateCDF_unit_base )
{
  double cdf = unit_base_ionization_dist->evaluateCDF( 8.829e-2, 1e-7 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  cdf = unit_base_ionization_dist->evaluateCDF( 9.12175e-2, 4.275e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9030213872906114e-01, 1e-4 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e-1, 1e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9964169418960402e-01, 1e-7 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1.0, 1.33136131511529e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9997873853576236e-01, 1e-10 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1.0, 9.7163E-02 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9996847362592778e-01, 1e-9 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e5, 1.752970e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9999998501226084e-01, 1e-10 );

  cdf = unit_base_ionization_dist->evaluateCDF( 1e5, 5e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-10 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );


  incoming_energy = 1.1;
  // sample the electron
  ace_ionization_dist->sample( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 4.34461320777921E-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 1e-7, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
/* Note: This tests a bug that caused electroionization to return non-realistic
 * knock-on energies. A unit based sampling routine was used to fix the problem.
 */
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on_native )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.0;         // Sample Bin
  fake_stream[1] = 0.0;         // Sample Electron
  fake_stream[2] = 0.0;         // Sample Bin
  fake_stream[3] = 1.0-1e-15;   // Sample Electron
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 6.041e-05;
  double knock_on_energy, knock_on_angle_cosine;

  // sample the electron at the min random number
  unit_base_ionization_dist->sample( incoming_energy,
                                     knock_on_energy,
                                     knock_on_angle_cosine );

  // Test knock-on electron at the min random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 4.0687255489257182e-02, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 1.0E-07, 1e-12 );

  // sample the electron at the max random number
  unit_base_ionization_dist->sample( incoming_energy,
                                     knock_on_energy,
                                     knock_on_angle_cosine );

  // Test knock-on electron at the max random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 6.680945582865727150e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 2.696314156988142391e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
/* Note: This tests a bug that caused electroionization to return non-realistic
 * knock-on energies with a correlated sampling routine.
 * The non-realistic sampled values can be rejected.
 */
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sample_knock_on_native_correlated )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
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
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 4.128782338482339664e-02, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 1.029739057966893379e-07, 1e-12 );

  // sample the electron at the max random number
  correlated_ionization_dist->sample( incoming_energy,
                                      knock_on_energy,
                                      knock_on_angle_cosine );

  // Test knock-on electron at the max random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 6.779557631590895639e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 2.7765e-05, 1e-12 );

  // Sample at the max energy
  incoming_energy = 1e5;

  // sample the electron at the min random number
  correlated_ionization_dist->sample( incoming_energy,
                                      knock_on_energy,
                                      knock_on_angle_cosine );

  // Test knock-on electron at the min random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 3.128075402437809332e-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 9.999999999512e-08, 1e-12 );

  // sample the electron at the max random number
  correlated_ionization_dist->sample( incoming_energy,
                                      knock_on_energy,
                                      knock_on_angle_cosine );

  // Test knock-on electron at the max random number
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 9.999948900092839876e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.999954497675684979e+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.964446703542646, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 8.706573789423E-01, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
                   sampleAndRecordTrials_ace )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 0.0;

  double incoming_energy = 1.0;

  double knock_on_energy, scattering_angle_cosine, knock_on_angle_cosine;

  // sample the electron
  ace_ionization_dist->sampleAndRecordTrials( incoming_energy,
                                              knock_on_energy,
                                              knock_on_angle_cosine,
                                              trials );

  // Test trials
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_angle_cosine, 0.279436961765390, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( knock_on_energy, 4.105262105768E-02, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 0.964446703542646, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 8.706573789423E-01, 1e-12 );

  // Test knock-on electron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 0.279436961765390, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 4.105262105768E-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 7.8974722856283108e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), 4.5585500000302387e-01, 1e-12 );

  // Test knock-on positron
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 07.8974722855920831e-01, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 4.5585499999697615e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name,
            test_native_ratio_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_table",
                                        test_ace_table_name, "",
                                        "Test ACE table name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_ratio_file",
                                        test_native_ratio_file_name, "",
                                        "Test Native ratio file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create ACE distribution
  {
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
     new Data::ACEFileHandler( test_ace_file_name,
                               test_ace_table_name,
                               1u ) );
  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  // Extract the cross sections energy grid
  Utility::ArrayView<const double> energy_grid =
    xss_data_extractor->extractElectronEnergyGrid() ;

  // Extract the subshell information
  Utility::ArrayView<const double> subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  // Extract the subshell binding energies
  Utility::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the electroionization data block (EION)
  Utility::ArrayView<const double> eion_block(
    xss_data_extractor->extractEIONBlock() );

  // Extract the location of info about first knock-on table relative to the EION block
  unsigned eion_loc = xss_data_extractor->returnEIONLoc();

  // Extract the number of subshells (N_s)
  int num_shells = subshell_endf_designators.size();

  // Extract the number of knock-on tables by subshell (N_i)
  std::vector<double> num_tables(eion_block(0,num_shells));

  // Extract the location of info about knock-on tables by subshell
  std::vector<double> table_info(eion_block(num_shells,num_shells));

  // Extract the location of knock-on tables by subshell
  std::vector<double> table_loc(eion_block(2*num_shells,num_shells));

  // Subshell
  unsigned subshell = 0;

  // Subshell table info realtive to the EION Block
  unsigned subshell_info = table_info[subshell]- eion_loc - 1;

  // Subshell table loc realtive to the EION Block
  unsigned subshell_loc = table_loc[subshell]- eion_loc - 1;

  // Extract the energies for which knock-on sampling tables are given
  std::vector<double> table_energy_grid(eion_block( subshell_info,
                                                       num_tables[subshell] ) );

  // Extract the length of the knock-on sampling tables
  std::vector<double> table_length(eion_block(
                               subshell_info + num_tables[subshell],
                               num_tables[subshell] ) );

  // Extract the offset of the knock-on sampling tables
  std::vector<double> table_offset(eion_block(
                             subshell_info + 2*num_tables[subshell],
                             num_tables[subshell] ) );

  // Create the scattering function
  std::vector<double> primary_grid( num_tables[subshell] );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( num_tables[subshell] );

  for( unsigned n = 0; n < num_tables[subshell]; ++n )
  {
    primary_grid[n] = table_energy_grid[n];

    secondary_dists[n].reset(
     new Utility::HistogramDistribution(
      eion_block( subshell_loc + table_offset[n], table_length[n] ),
      eion_block( subshell_loc + table_offset[n] + table_length[n] + 1,
                  table_length[n] - 1),
      true ) );
  }

  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                                               primary_grid,
                                                               secondary_dists,
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
  std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer( test_native_file_name ) );

  std::set<unsigned> subshells = data_container->getSubshells();

  unsigned subshell = *subshells.find(6);
  double binding_energy =
    data_container->getSubshellBindingEnergy( subshell );

  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
    data_container->getElectroionizationEnergyGrid( subshell );

  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    std::vector<double> recoil_energy(
        data_container->getElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    std::vector<double> pdf(
        data_container->getElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LogLog>( recoil_energy,
                                                               pdf ) );
  }

  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogLog> >(
                                                              primary_grid,
                                                              secondary_dists,
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
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
    new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                              primary_grid,
                                                              secondary_dists,
                                                              1e-6,
                                                              1e-12 ) );

  // Create the distributions
  unit_correlated_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energy ) );
  }
  }

  // Create Native distribution
  {
  // Create the native data file container
  std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer( test_native_ratio_file_name ) );

  std::set<unsigned> subshells = data_container->getSubshells();

  unsigned subshell = *subshells.find(6);
  double binding_energy =
    data_container->getSubshellBindingEnergy( subshell );

  // Get the energies for which knock-on sampling tables are given
  std::vector<double> energy_grid =
    data_container->getElectroionizationEnergyGrid( subshell );

  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    std::vector<double> recoil_energy(
        data_container->getElectroionizationRecoilEnergy(
            subshell,
            energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    std::vector<double> pdf(
        data_container->getElectroionizationRecoilPDF(
            subshell,
            energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LogLog>( recoil_energy,
                                                               pdf ) );
  }

  {
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LogLogLog> >(
                                                             primary_grid,
                                                             secondary_dists,
                                                             1e-6,
                                                             1e-12 ) );

  // Create the distributions
  correlated_ionization_dist.reset(
        new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
                            subshell_distribution,
                            binding_energy,
                            true ) );
  }
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
