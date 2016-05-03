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
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model;
std::string electroatom_name;
double atomic_weight;
double cutoff_angle;
Teuchos::RCP<MonteCarlo::Electroatom> atom;
MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
unsigned hash_grid_bins = 100;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution 
 * data can be created
 *//*
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
        cutoff_angle );


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

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.995260E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.103010E+08, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          6.130900E+08, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          2.489240E+09, 
                          1e-12 );

  // Test that the screened Rutherford elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.1116099116949E+06, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          1.088440E+06, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
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
        cutoff_angle );

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

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.995260E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.103010E+08, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          6.130900E+08, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          2.489240E+09, 
                          1e-12 );

  // Test that the screened Rutherford elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
            1.000E+05,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.1116099116949E+06, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
            1.995260E+01,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          1.088440E+06, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
            6.309570E+00,
            MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  
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
*/
//---------------------------------------------------------------------------//
// Check that a electroatom with a higher cutoff angle can be created
TEUCHOS_UNIT_TEST( ElectroatomNativeFactory, createElectroatom_cutoff )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  double new_cutoff_angle = 0.1;
  double cross_section_ratio;

  MonteCarlo::ElectroatomNativeFactory::createElectroatom( 
        *data_container,
        electroatom_name,
        atomic_weight,
        hash_grid_bins,
        relaxation_model,
        atom,
        photon_distribution_function,
        true,
        new_cutoff_angle );

Teuchos::RCP<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
        cutoff_elastic_distribution,
        *data_container,
        new_cutoff_angle );

  // Test the electroatom properties
  TEST_EQUALITY_CONST( atom->getAtomName(), "Pb-Native" );
  TEST_EQUALITY_CONST( atom->getAtomicNumber(), 82 );
  TEST_FLOATING_EQUALITY( atom->getAtomicWeight(), 207.1999470456033, 1e-12 );

  // Test that the total cross section can be returned
  double energy = 1.000000000000E-05;
  double elastic_cross_section =
    atom->getReactionCrossSection(
                    energy,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  double cross_section = 
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 
                          1.398201198000000E+08 + elastic_cross_section,
                          1e-12 );

  energy = 2.000000000000E-01;
  elastic_cross_section = 
    atom->getReactionCrossSection(
                    energy,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  cross_section = 
    atom->getTotalCrossSection( energy );
 
  TEST_FLOATING_EQUALITY( cross_section, 
                          6.411260911064270E+06 + elastic_cross_section,
                          1e-12 );


  energy = 1.000000000000E+05;
  elastic_cross_section =
    atom->getReactionCrossSection(
                    energy,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  cross_section = 
    atom->getTotalCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.845403047900000E+06 + elastic_cross_section,
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

  // Test that the cutoff elastic cross section can be returned
  cross_section = atom->getReactionCrossSection(
                    1.00E-03,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio = 
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( 1.00E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 
                          2.902810E+08*cross_section_ratio, 
                          1e-12 );

  cross_section = atom->getReactionCrossSection(
                    1.995260E-04,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio = 
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( 1.99526E-04 );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          6.130900E+08*cross_section_ratio, 
                          1e-12 );
  
  cross_section = atom->getReactionCrossSection(
                    1.000000000000E-05,
                    MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );

  cross_section_ratio = 
    cutoff_elastic_distribution->evaluateCutoffCrossSectionRatio( 1.00E-05 );
  
  TEST_FLOATING_EQUALITY( cross_section,  
                          2.489240E+09*cross_section_ratio, 
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
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name, test_epr_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test native file name" );
  clp.setOption( "test_epr_file",
		 &test_epr_file_name,
		 "Test epr file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  electroatom_name = "Pb-Native";
  atomic_weight = 207.1999470456033;
  cutoff_angle = 1.0e-6;
  
  {
    // Create the native data file container
    data_container.reset( new Data::ElectronPhotonRelaxationDataContainer( 
						     test_native_file_name ) );


    MonteCarlo::AtomicRelaxationModelFactory::createAtomicRelaxationModel(
							   *data_container,
							   relaxation_model,
							   true );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
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
// end tstElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
