//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatom.cpp
//! \author Luke Kersting
//! \brief  Positronatom unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

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
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::Positronatom> ace_positronatom, native_positronatom,
                                         epr14_positronatom;

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
// Check that the scattering reaction types can be returned
TEUCHOS_UNIT_TEST( Positronatom, getScatteringReactionTypes )
{
  const boost::unordered_set<MonteCarlo::PositronatomicReactionType>&
    scattering_types = MonteCarlo::Positronatom::getScatteringReactionTypes();

  TEST_ASSERT( scattering_types.count(
               MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::L1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::L2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::L3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::M5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::N7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::O9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P4_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P5_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P6_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P7_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P8_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P9_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P10_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::P11_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::Q1_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::Q2_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
        MonteCarlo::Q3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION ) );

  TEST_ASSERT( scattering_types.count(
               MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION ) );
  TEST_ASSERT( scattering_types.count(
               MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atom name can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomName_ace )
{
  TEST_EQUALITY_CONST( ace_positronatom->getAtomName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atom name can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomName_native )
{
  TEST_EQUALITY_CONST( native_positronatom->getAtomName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the positronatom nuclide name can be returned
TEUCHOS_UNIT_TEST( Positronatom, getNuclideName_ace )
{
  TEST_EQUALITY_CONST( ace_positronatom->getNuclideName(), "82000.12p" );
}

//---------------------------------------------------------------------------//
// Check that the positronatom nuclide name can be returned
TEUCHOS_UNIT_TEST( Positronatom, getNuclideName_native )
{
  TEST_EQUALITY_CONST( native_positronatom->getNuclideName(), "Pb" );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic number can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomicNumber_ace )
{
  TEST_EQUALITY_CONST( ace_positronatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic number can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomicNumber_native )
{
  TEST_EQUALITY_CONST( native_positronatom->getAtomicNumber(), 82 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic mass number can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomicMassNumber_ace )
{
  TEST_EQUALITY_CONST( ace_positronatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic mass number can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomicMassNumber_native )
{
  TEST_EQUALITY_CONST( native_positronatom->getAtomicMassNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom isomer number can be returned
TEUCHOS_UNIT_TEST( Positronatom, getIsomerNumber_ace )
{
  TEST_EQUALITY_CONST( ace_positronatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom isomer number can be returned
TEUCHOS_UNIT_TEST( Positronatom, getIsomerNumber_native )
{
  TEST_EQUALITY_CONST( native_positronatom->getIsomerNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic weight can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomicWeight_ace )
{
  TEST_FLOATING_EQUALITY( ace_positronatom->getAtomicWeight(),
                          207.1999470456033,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom atomic weight can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAtomicWeight_native )
{
  TEST_FLOATING_EQUALITY( native_positronatom->getAtomicWeight(),
                          207.1999470456033,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom temperature can be returned
TEUCHOS_UNIT_TEST( Positronatom, getTemperature_ace )
{
  TEST_EQUALITY_CONST( ace_positronatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the positronatom temperature can be returned
TEUCHOS_UNIT_TEST( Positronatom, getTemperature_native )
{
  TEST_EQUALITY_CONST( native_positronatom->getTemperature(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( Positronatom, getTotalCrossSection_ace )
{
  double cross_section =
    ace_positronatom->getTotalCrossSection( 2e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.96517E+08,
                          1e-12 );
  cross_section =
    ace_positronatom->getTotalCrossSection( 4e-4 );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.22682E+08,
                          1e-12 );
  cross_section =
    ace_positronatom->getTotalCrossSection( 9E-05 );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.16042E+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( Positronatom, getTotalCrossSection_native )
{
  double cross_section =
    native_positronatom->getTotalCrossSection( 2e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );
  cross_section =
    native_positronatom->getTotalCrossSection( 4e-4 );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );
  cross_section =
    native_positronatom->getTotalCrossSection( 9e-5 );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
TEUCHOS_UNIT_TEST( Positronatom, getTotalCrossSection_epr14 )
{
  double cross_section =
    epr14_positronatom->getTotalCrossSection( 5.2371421547030929e-02 );

  TEST_FLOATING_EQUALITY( cross_section,
                          4.4981474879191741e+07,
                          1e-12 );

  cross_section =
    epr14_positronatom->getTotalCrossSection( 2e-03 );

  TEST_FLOATING_EQUALITY( cross_section,
                          3.9416460301500607e+08,
                          1e-12 );
  cross_section =
    epr14_positronatom->getTotalCrossSection( 4e-04 );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.1706481556832719e+08,
                          1e-12 );
  cross_section =
    epr14_positronatom->getTotalCrossSection( 9e-05 );

  TEST_FLOATING_EQUALITY( cross_section,
                          1.5083218251907730e+09,
                          1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAbsorptionCrossSection_ace )
{
  double cross_section =
    ace_positronatom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    ace_positronatom->getAbsorptionCrossSection( 2e-3 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    ace_positronatom->getAbsorptionCrossSection( 4e-4 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    ace_positronatom->getAbsorptionCrossSection( 9e-5 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
TEUCHOS_UNIT_TEST( Positronatom, getAbsorptionCrossSection_native )
{
  double cross_section =
    native_positronatom->getAbsorptionCrossSection( 1.000000000E-02 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    native_positronatom->getAbsorptionCrossSection( 2e-3 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    native_positronatom->getAbsorptionCrossSection( 4e-4 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =
    native_positronatom->getAbsorptionCrossSection( 9e-5 );

   TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( Positronatom, getSurvivalProbability_ace )
{
  double survival_prob =
    ace_positronatom->getSurvivalProbability( 2e-3 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob =
    ace_positronatom->getSurvivalProbability( 4e-4 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob =
    ace_positronatom->getSurvivalProbability( 9e-5 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( Positronatom, getSurvivalProbability_native )
{
  double survival_prob =
    native_positronatom->getSurvivalProbability( 2e-3 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob =
    native_positronatom->getSurvivalProbability( 4e-4 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob =
    native_positronatom->getSurvivalProbability( 9e-5 );

   TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
TEUCHOS_UNIT_TEST( Positronatom, getReactionCrossSection_ace )
{
  // Total Electroionization
  double cross_section = ace_positronatom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                   2e-3,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                   4e-4,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                   9e-5,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = ace_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.96517E+08, 1e-12 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.22682E+08, 1e-12 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.16042E+09, 1e-12 );

  // Bremsstrahlung
  cross_section = ace_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.258661418255E+03, 1e-12 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    4e-4,
                 MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.914234996439E+03, 1e-12 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.249970966838E+03, 1e-12 );

  // Coupled Elastic
  cross_section = ace_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Cutoff Elastic
  cross_section = ace_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Total
  cross_section = ace_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.96517E+08,
                          1e-12 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.22682E+08,
                          1e-12 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.16042E+09,
                          1e-12 );

  // Absorption
  cross_section = ace_positronatom->getReactionCrossSection(
                    1.000000000000E-02,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =ace_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = ace_positronatom->getReactionCrossSection(
                    9e-5,
               MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction cross section can be returned
TEUCHOS_UNIT_TEST( Positronatom, getReactionCrossSection_native )
{
  // Total Electroionization
  double cross_section = native_positronatom->getReactionCrossSection(
                   1.000000000000E-02,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                   2e-3,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                   4e-4,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                   9e-5,
                   MonteCarlo::TOTAL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );

   TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Atomic Excitation
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.96517E+08, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 6.22682E+08, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.16042E+09, 1e-12 );

  // Bremsstrahlung
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.2586614182549074e+03, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                 MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 8.9142349964387486e+03, 1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.2499709668376108e+03, 1e-12 );

  // Cutoff Elastic
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  // Total
  cross_section = native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.2586614182549074e+03 + 1.96517E+08,
                          1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.9142349964387486e+03 + 6.22682E+08,
                          1e-12 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
                    MonteCarlo::TOTAL_POSITRONATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.2499709668376108e+03 + 1.16042E+09,
                          1e-12 );

  // Absorption
  cross_section = native_positronatom->getReactionCrossSection(
                    1.000000000000E-02,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section =native_positronatom->getReactionCrossSection(
                    2e-3,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    4e-4,
                    MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = native_positronatom->getReactionCrossSection(
                    9e-5,
               MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that an analogue collision with the atom can be modeled
TEUCHOS_UNIT_TEST( Positronatom, collideAnalogue )
{
  Teuchos::RCP<MonteCarlo::PositronState> positron(
                        new MonteCarlo::PositronState( 0 ) );
  positron->setEnergy( 20 );
  positron->setDirection( 0.0, 0.0, 1.0 );
  positron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // choose scattering rxn

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_positronatom->collideAnalogue( *positron, bank );

  TEST_ASSERT( !positron->isGone() );
  TEST_EQUALITY_CONST( positron->getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a survival biased collision with the atom can be modeled
TEUCHOS_UNIT_TEST( Positronatom, collideSurvivalBias )
{
  Teuchos::RCP<MonteCarlo::PositronState> positron(
                        new MonteCarlo::PositronState( 0 ) );
  positron->setEnergy( 1 );
  positron->setDirection( 0.0, 0.0, 1.0 );
  positron->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  ace_positronatom->collideSurvivalBias( *positron, bank );

  TEST_ASSERT( !positron->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  // reset the particle
  positron.reset( new MonteCarlo::PositronState( 0 ) );
  positron->setEnergy( 1 );
  positron->setDirection( 0.0, 0.0, 1.0 );
  positron->setWeight( 1.0 );

  ace_positronatom->collideSurvivalBias( *positron, bank );

  TEST_ASSERT( !positron->isGone() );
  TEST_FLOATING_EQUALITY( positron->getWeight(), 1.0, 1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atom can be relaxed
TEUCHOS_UNIT_TEST( Positronatom, relaxAtom )
{
  Teuchos::RCP<MonteCarlo::PositronState> positron(
                                          new MonteCarlo::PositronState( 0 ) );
  positron->setEnergy( exp( -1.214969212306E+01 ) );
  positron->setDirection( 0.0, 0.0, 1.0 );
  positron->setWeight( 1.0 );

  Data::SubshellType vacancy = Data::K_SUBSHELL;
  MonteCarlo::ParticleBank bank;

  ace_positronatom->relaxAtom( vacancy, *positron, bank );
  TEST_EQUALITY_CONST( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a positronatom can be constructed from a core
TEUCHOS_UNIT_TEST( Positronatom, core_constructor )
{
  MonteCarlo::Positronatom positronatom_copy( ace_positronatom->getAtomName(),
                      ace_positronatom->getAtomicNumber(),
                      ace_positronatom->getAtomicWeight(),
                      ace_positronatom->getCore() );

  TEST_EQUALITY( positronatom_copy.getAtomName(),
         ace_positronatom->getAtomName() );
  TEST_EQUALITY( positronatom_copy.getNuclideName(),
         ace_positronatom->getNuclideName() );
  TEST_EQUALITY( positronatom_copy.getAtomicNumber(),
         ace_positronatom->getAtomicNumber() );
  TEST_EQUALITY( positronatom_copy.getAtomicMassNumber(),
         ace_positronatom->getAtomicMassNumber() );
  TEST_EQUALITY( positronatom_copy.getIsomerNumber(),
         ace_positronatom->getIsomerNumber() );
  TEST_EQUALITY( positronatom_copy.getAtomicWeight(),
         ace_positronatom->getAtomicWeight() );
  TEST_EQUALITY( positronatom_copy.getTemperature(),
         ace_positronatom->getTemperature() );

  TEST_EQUALITY( positronatom_copy.getTotalCrossSection( 1e-3 ),
         ace_positronatom->getTotalCrossSection( 1e-3 ) );
  TEST_EQUALITY( positronatom_copy.getTotalCrossSection( 20.0 ),
         ace_positronatom->getTotalCrossSection( 20.0 ) );
  TEST_EQUALITY( positronatom_copy.getAbsorptionCrossSection( 1e-3 ),
         ace_positronatom->getAbsorptionCrossSection( 1e-3 ) );
  TEST_EQUALITY( positronatom_copy.getAbsorptionCrossSection( 20.0 ),
         ace_positronatom->getAbsorptionCrossSection( 20.0 ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name,
            test_epr14_file_name, test_epr14_table_name;

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
  clp().setOption( "test_epr14_file",
                   &test_epr14_file_name,
                   "Test EPR14 file name" );
  clp().setOption( "test_epr14_table",
                   &test_epr14_table_name,
                   "Test EPR14 table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
                 new Data::ACEFileHandler( test_ace_file_name,
                                           test_ace_table_name,
                                           1u ) );
    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                      ace_file_handler->getTableNXSArray(),
                      ace_file_handler->getTableJXSArray(),
                      ace_file_handler->getTableXSSArray() ) );

    // Create the atomic excitation, bremsstrahlung cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

    // Create the hash-based grid searcher
    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                         energy_grid,
                         energy_grid[0],
                         energy_grid[energy_grid.size()-1],
                         100 ) );

    Teuchos::ArrayView<const double> raw_ae_cross_section =
      xss_data_extractor->extractExcitationCrossSection();

    Teuchos::ArrayView<const double>::iterator start =
      std::find_if( raw_ae_cross_section.begin(),
            raw_ae_cross_section.end(),
            notEqualZero );

    Teuchos::ArrayRCP<double> ae_cross_section;
    ae_cross_section.assign( start, raw_ae_cross_section.end() );

    unsigned ae_threshold_index =
      energy_grid.size() - ae_cross_section.size();

    // Extract the atomic excitation information data block (EXCIT)
    Teuchos::ArrayView<const double> excit_block(
                      xss_data_extractor->extractEXCITBlock() );

    // Extract the number of tabulated energies
    int size = excit_block.size()/2;

    // Extract the energy grid for atomic excitation energy loss
    Teuchos::Array<double> ae_energy_grid(excit_block(0,size));

    // Extract the energy loss for atomic excitation
    Teuchos::Array<double> energy_loss(excit_block(size,size));

    // Create the energy loss distributions
    MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
     ae_energy_loss_function;

    ae_energy_loss_function.reset(
      new Utility::TabularDistribution<Utility::LinLin>( ae_energy_grid,
                                                         energy_loss ) );

    std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
                      ae_energy_loss_distribution;

    ae_energy_loss_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

    std::shared_ptr<MonteCarlo::PositronatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationPositronatomicReaction<Utility::LinLin>(
                energy_grid,
                ae_cross_section,
                ae_threshold_index,
                ae_energy_loss_distribution ) );

    Teuchos::ArrayView<const double> raw_b_cross_section =
      xss_data_extractor->extractBremsstrahlungCrossSection();

    start = std::find_if( raw_b_cross_section.begin(),
            raw_b_cross_section.end(),
            notEqualZero );

    Teuchos::ArrayRCP<double> b_cross_section;
    b_cross_section.assign( start, raw_b_cross_section.end() );

    unsigned b_threshold_index =
      energy_grid.size() - b_cross_section.size();

    std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        b_scattering_distribution;

    MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
        xss_data_extractor->extractAtomicNumber(),
        *xss_data_extractor,
        b_scattering_distribution );

    // Create the scattering distributions
    std::shared_ptr<MonteCarlo::PositronatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungPositronatomicReaction<Utility::LinLin>(
                energy_grid,
                b_cross_section,
                b_threshold_index,
                b_scattering_distribution ) );

    // Create the reaction maps
    MonteCarlo::PositronatomCore::ReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Extract the atomic weight
    double atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;

    // Create a test positronatom
    ace_positronatom.reset(
           new MonteCarlo::Positronatom(
                    ace_file_handler->getTableName(),
                    xss_data_extractor->extractAtomicNumber(),
                    atomic_weight,
                    energy_grid,
                    grid_searcher,
                    scattering_reactions,
                    absorption_reactions,
                    relaxation_model,
                    false,
                    Utility::LinLin() ) );
  }

  // Create the Native positronatom core
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer data_container(
        test_native_file_name );

    // Create the atomic excitation, bremsstrahlung cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( data_container.getElectronEnergyGrid() );

    // Create the hash-based grid searcher
    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                         energy_grid,
                         energy_grid[0],
                         energy_grid[energy_grid.size()-1],
                         100 ) );

    // Atomic Excitation cross section
    Teuchos::ArrayRCP<double> ae_cross_section;
    ae_cross_section.assign(
      data_container.getAtomicExcitationCrossSection().begin(),
      data_container.getAtomicExcitationCrossSection().end() );

    unsigned ae_threshold_index =
        data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex();

    // Create the energy loss distributions
    MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
        ae_energy_loss_function(
            new Utility::TabularDistribution<Utility::LogLog>(
                data_container.getAtomicExcitationEnergyGrid(),
                data_container.getAtomicExcitationEnergyLoss() ) );

    std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
        ae_energy_loss_distribution(
            new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

    std::shared_ptr<MonteCarlo::PositronatomicReaction> ae_reaction(
        new MonteCarlo::AtomicExcitationPositronatomicReaction<Utility::LogLog>(
            energy_grid,
            ae_cross_section,
            ae_threshold_index,
            grid_searcher,
            ae_energy_loss_distribution ) );


    // Bremsstrahlung cross section
    Teuchos::ArrayRCP<double> b_cross_section;
    b_cross_section.assign(
      data_container.getBremsstrahlungCrossSection().begin(),
      data_container.getBremsstrahlungCrossSection().end() );

    unsigned b_threshold_index =
        data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex();


    // Get the energy grid for bremsstrahlung energy distributions
    std::vector<double> b_energy_grid =
        data_container.getBremsstrahlungEnergyGrid();

    Utility::FullyTabularTwoDDistribution::DistributionType
      function_data( b_energy_grid.size() );

    for( unsigned n = 0; n < b_energy_grid.size(); ++n )
    {
      function_data[n].first = b_energy_grid[n];

      // Get the energy of the bremsstrahlung photon at the incoming energy
      Teuchos::Array<double> photon_energy(
        data_container.getBremsstrahlungPhotonEnergy( b_energy_grid[n] ) );

      // Get the bremsstrahlung photon pdf at the incoming energy
      Teuchos::Array<double> pdf(
        data_container.getBremsstrahlungPhotonPDF( b_energy_grid[n] ) );

      function_data[n].second.reset(
        new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                                 pdf ) );
    }

    // Create the scattering function
    std::shared_ptr<Utility::FullyTabularTwoDDistribution> b_energy_loss_function(
      new Utility::InterpolatedFullyTabularTwoDDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
            function_data ) );

    std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        b_scattering_distribution(
            new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
                data_container.getAtomicNumber(),
                b_energy_loss_function ) );


    // Create the bremsstrahlung scattering reaction
    std::shared_ptr<MonteCarlo::PositronatomicReaction> b_reaction(
        new MonteCarlo::BremsstrahlungPositronatomicReaction<Utility::LogLog>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

    // Create the reaction maps
    MonteCarlo::PositronatomCore::ReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test positronatom
    native_positronatom.reset(
           new MonteCarlo::Positronatom(
                    "Pb",
                    data_container.getAtomicNumber(),
                    207.1999470456033,
                    energy_grid,
                    grid_searcher,
                    scattering_reactions,
                    absorption_reactions,
                    relaxation_model,
                    false,
                    Utility::LogLog() ) );
  }

  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
                 new Data::ACEFileHandler( test_epr14_file_name,
                                           test_epr14_table_name,
                                           1u ) );
    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
                      ace_file_handler->getTableNXSArray(),
                      ace_file_handler->getTableJXSArray(),
                      ace_file_handler->getTableXSSArray() ) );

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
                   new MonteCarlo::VoidAtomicRelaxationModel );

    // Extract the atomic weight
    double atomic_weight = ace_file_handler->getTableAtomicWeightRatio()*
      Utility::PhysicalConstants::neutron_rest_mass_amu;

    // Create the simulation properties
    MonteCarlo::SimulationElectronProperties properties;

    Teuchos::RCP<MonteCarlo::PositronatomCore> core;

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
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatom.cpp
//---------------------------------------------------------------------------//

