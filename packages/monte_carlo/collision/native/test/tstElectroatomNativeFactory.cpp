//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatom factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model;
std::string electroatom_name;
double atomic_weight;
double cutoff_angle_cosine;
Teuchos::RCP<MonteCarlo::Electroatom> atom;
MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
unsigned hash_grid_bins = 100;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_detailed_brem )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::ElectroatomNativeFactory::createElectroatom(
        *data_container,
        electroatom_name,
        atomic_weight,
        hash_grid_bins,
        relaxation_model,
        atom,
        photon_distribution_function,
        true,
        cutoff_angle_cosine );


  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.000000000000E-05;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.629060119800000E+09,
                          1e-12 );


  energy = 2.000000000000E-01;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.252314241820250E+07,
                          1e-12 );


  energy = 1.000000000000E+05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.957013047900000E+06,
                          1e-12 );


  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    5.520610E-04,
				 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.235190E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800E+03, 1e-12 );

  // Test that the analog elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.830509999999990E-02 + 2.1116099116949E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.0571E+06 + 1.088440E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.68623E+06 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E-03,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.103010E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E-04,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.130900E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.000000000000E-05,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.489240E+09 + 0.0,
                          1e-12 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
			1.000000000000E-05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			1.000000000000E+05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		   1.000000000000E-05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   9.121750E-02,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.500920E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   1.000000000000E+05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-03,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E+05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that a electroatom with electroionization subshell data can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_ionization_subshells )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomNativeFactory::createElectroatom(
        *data_container,
        electroatom_name,
        atomic_weight,
        hash_grid_bins,
        relaxation_model,
        atom,
        photon_distribution_function,
        true,
        cutoff_angle_cosine );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.000000000000E-05;
  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.629060119800000E+09,
                          1e-12 );


  energy = 2.000000000000E-01;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.252314241820250E+07,
                          1e-12 );


  energy = 1.000000000000E+05;
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.957013047900000E+06,
                          1e-12 );


  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    5.520610E-04,
				 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.235190E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800E+03, 1e-12 );

  // Test that the analog elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.830509999999990E-02 + 2.1116099116949E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.0571E+06 + 1.088440E+06,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.68623E+06 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E-03,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.103010E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E-04,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          6.130900E+08 + 0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.000000000000E-05,
            MonteCarlo::ANALOG_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.489240E+09 + 0.0,
                          1e-12 );

  // Test that the moment preserving elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
			1.000000000000E-05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			1.000000000000E+05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		   1.000000000000E-05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   9.121750E-02,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.500920E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   1.000000000000E+05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-03,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E+05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a electroatom with a higher cutoff angle can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_cutoff )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double new_cutoff_angle_cosine = 0.9;

  MonteCarlo::ElectroatomNativeFactory::createElectroatom(
        *data_container,
        electroatom_name,
        atomic_weight,
        hash_grid_bins,
        relaxation_model,
        atom,
        photon_distribution_function,
        true,
        new_cutoff_angle_cosine );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        cutoff_elastic_distribution,
        *data_container,
        new_cutoff_angle_cosine );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.000000000000E-05;
  double cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, new_cutoff_angle_cosine );
  double inelastic = 1.398201198000000E+08;
  double elastic = 2.48924E+09*cross_section_ratio + 1.106329441558590E+08;

  double cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          inelastic + elastic,
                          1e-12 );

  energy = 2.000000000000E-01;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, new_cutoff_angle_cosine );
  inelastic = 6.41057988372776E+06;
  elastic = 1.611188150713820E+07*cross_section_ratio + 1.950992057434620E+06;
  
  cross_section =
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section,
                          inelastic + elastic,
                          1e-12 );

  energy = 1.000000000000E+05;
  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( energy, new_cutoff_angle_cosine );
  inelastic = 2.845403047900000E+06;
  elastic = 8.83051E-02*cross_section_ratio + 2.203770304996720E-03;
  
  cross_section =
    atom->getTotalCrossSection( energy );
  
  TEST_FLOATING_EQUALITY( cross_section,
                          inelastic + elastic,
                          1e-12 );


  // Test that the absorption cross section can be returned
  cross_section =
    atom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 2.000000000000E-03 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 4.000000000000E-04 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    atom->getAbsorptionCrossSection( 9.000000000000E-05 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Test that the atomic excitation cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    2.000000000000E-03,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.965170000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    4.000000000000E-04,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.226820000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    9.000000000000E-05,
                    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.160420000000E+09, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-03,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.528370E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    5.520610E-04,
				 MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.235190E+03, 1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1e-5,
                    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.869800E+03, 1e-12 );

  // Test that the hybrid elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1e5,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1e5, new_cutoff_angle_cosine );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.83051e-2*cross_section_ratio + 2.20377030499672E-03,
                          1e-11 );

  cross_section = atom->getReactionCrossSection(
                    1e-3,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1e-3, new_cutoff_angle_cosine );
  
  TEST_FLOATING_EQUALITY( cross_section,
                          2.902810E+08*cross_section_ratio + 1.2584013774057174E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E-04,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1.99526E-04, new_cutoff_angle_cosine );
  
  TEST_FLOATING_EQUALITY( cross_section,
                          6.130900E+08*cross_section_ratio + 2.5849727567112732E+08,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio =
    cutoff_elastic_distribution->evaluateCDF( 1.E-05, new_cutoff_angle_cosine );

  TEST_FLOATING_EQUALITY( cross_section,
                          2.489240E+09*cross_section_ratio + 1.106329441558590E+08,
                          1e-12 );

  // Test that there is no cutoff elastic cross section
  cross_section = atom->getReactionCrossSection(
                    1.00E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );


  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  // Test that there is no screened Rutherford reaction
  cross_section = atom->getReactionCrossSection(
			1.000000000000E-05,
			MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			1.000000000000E+05,
			MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that there is no moment preserving elastic cross section
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          0.0,
                          1e-12 );

  // Test that there is no total electroionization
  cross_section = atom->getReactionCrossSection(
			1.000000000000E-05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
			1.000000000000E+05,
			MonteCarlo::TOTAL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		   1.000000000000E-05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   9.121750E-02,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.500920E-01, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		   1.000000000000E+05,
		   MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.649190E+01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.065300000000E+08, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E-03,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.248850E+07, 1e-12 );

  cross_section = atom->getReactionCrossSection(
		  1.000000000000E+05,
		  MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.822340000000E+05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  electroatom_name = "Pb-Native";
  atomic_weight = 207.1999470456033;
  cutoff_angle_cosine = 1.0;

  {
    // Create the native data file container
    data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );


    MonteCarlo::AtomicRelaxationModelFactory::createAtomicRelaxationModel(
           *data_container,
           relaxation_model,
           true );
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
