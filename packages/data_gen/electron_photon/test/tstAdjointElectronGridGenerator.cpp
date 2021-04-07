//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronGridGenerator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron grid generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "DataGen_AdjointElectronGridGenerator.hpp"
#include "MonteCarlo_VoidElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::function<double(const double&)> brem_cs_evaluator, ionization_cs_evaluator, brem_cs_evaluator2;
std::function<double(const double&, const double&)> brem_pdf_evaluator, ionization_pdf_evaluator, brem_pdf_evaluator2, ionization_pdf_evaluator2;

std::vector<double> brem_energy_grid, ionization_energy_grid;

std::function<double(const double&)> brem_min_function, ionization_min_function, brem_min_function2, ionization_min_function2;

double binding_energy;

double min_energy = 1e-5;
double max_energy = 20.0;
double min_energy_nudge_value = 1e-9;
double max_energy_nudge_value = 2e-7;
double convergence_tol = 0.001;
double absolute_diff_tol = 1e-10;
double distance_tol = 1e-8;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the min energy can be returned
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, getMinIncomingEnergy )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( brem_cs_evaluator,
                    brem_pdf_evaluator,
                    brem_min_function,
                    brem_energy_grid );

    FRENSIE_CHECK_EQUAL( grid_generator.getMinIncomingEnergy(), 1e-5 );
  }

  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( ionization_cs_evaluator,
                    ionization_pdf_evaluator,
                    ionization_min_function,
                    ionization_energy_grid,
                    min_energy,
                    max_energy,
                    min_energy_nudge_value,
                    max_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol,
                    false );

    FRENSIE_CHECK_EQUAL( grid_generator.getMinIncomingEnergy(), 1e-5 );
  }
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, getMaxIncomingEnergy )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( brem_cs_evaluator,
                    brem_pdf_evaluator,
                    brem_min_function,
                    brem_energy_grid );

    FRENSIE_CHECK_EQUAL( grid_generator.getMaxIncomingEnergy(), 20.0 );
  }

  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( ionization_cs_evaluator,
                    ionization_pdf_evaluator,
                    ionization_min_function,
                    ionization_energy_grid,
                    min_energy,
                    max_energy,
                    min_energy_nudge_value,
                    max_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol,
                    false );

    double max_energy = 20.0 - ionization_min_function(20.0) - max_energy_nudge_value;
    FRENSIE_CHECK_EQUAL( grid_generator.getMaxIncomingEnergy(), max_energy );
  }
}

//---------------------------------------------------------------------------//
// Check that the min energy can be returned
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, getMinOutgoingEnergy )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( brem_cs_evaluator,
                    brem_pdf_evaluator,
                    brem_min_function,
                    brem_energy_grid );

    double min_energy = 1e-5 + brem_min_function(1e-5) + 1e-9;

    FRENSIE_CHECK_EQUAL( grid_generator.getMinOutgoingEnergy(), min_energy );
  }

  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( ionization_cs_evaluator,
                    ionization_pdf_evaluator,
                    ionization_min_function,
                    ionization_energy_grid,
                    min_energy,
                    max_energy,
                    min_energy_nudge_value,
                    max_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol,
                    false );

    double min_energy = 1e-5 + ionization_min_function(1e-5) + min_energy_nudge_value;

    FRENSIE_CHECK_EQUAL( grid_generator.getMinOutgoingEnergy(), min_energy );
  }
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, getMaxOutgoingEnergy )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( brem_cs_evaluator,
                    brem_pdf_evaluator,
                    brem_min_function,
                    brem_energy_grid );

    double max_energy = 20.0 + brem_min_function(20.0) + 1e-2;
    FRENSIE_CHECK_EQUAL( grid_generator.getMaxOutgoingEnergy(), max_energy );
  }

  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( ionization_cs_evaluator,
                    ionization_pdf_evaluator,
                    ionization_min_function,
                    ionization_energy_grid,
                    min_energy,
                    max_energy,
                    min_energy_nudge_value,
                    max_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol,
                    false );

    FRENSIE_CHECK_EQUAL( grid_generator.getMaxOutgoingEnergy(), 20.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the nudged min energy can be returned
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, getNudgedMinEnergy )
{
  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( brem_cs_evaluator,
                    brem_pdf_evaluator,
                    brem_min_function,
                    brem_energy_grid );

    FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMinEnergy(1e-5),
                         1.010128918305179141e-05 );

    FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMinEnergy(1.0),
                         1.000000113241543920 );
  }

  {
    DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    grid_generator( ionization_cs_evaluator,
                    ionization_pdf_evaluator,
                    ionization_min_function,
                    ionization_energy_grid,
                    min_energy,
                    max_energy,
                    min_energy_nudge_value,
                    max_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol,
                    false );

    FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMinEnergy(1e-5),
                         2.881704197261944681e-05 );

    FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMinEnergy(1.0),
                         1.000006621027896614 );
  }
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
                   evaluateAdjointDifferentialCrossSection )
{
  double precision = 1e-5;
  double diff_cs;

  // Native Electroionization
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator,
                  ionization_min_function,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( 1.361E-05, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 8.830479002878427505e+08, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( max_energy - ionization_min_function(max_energy), max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 1.677745972568486404e+10, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( max_energy - ionization_min_function(max_energy) - max_energy_nudge_value, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 6.551681151980347633e+09, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( 1.2686300708196014e-04, 2.6912428420799615e-04 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 5.877865343492855072e+09, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( 1.2686300708196014e-04, 2.5692514588713508e-04 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 6.754196245496340752e+09, 1e-5 );
  }

  // Native Electroionization
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator2,
                  ionization_min_function2,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( 1.361E-05, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 1.766095800583091497e+09, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( max_energy - ionization_min_function2(max_energy) - 1e-7, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 3.203327310399196243e+10, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( max_energy - ionization_min_function2(max_energy) - max_energy_nudge_value, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 3.116084093189196777e+10, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( 1.2686300708196014e-04, 2.6912428420799615e-04 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 9.867613378496900558e+09, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( 1.2686300708196014e-04, 2.5692514588713508e-04 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 1.120499392700973892e+10, 1e-5 );

  diff_cs = grid_generator.evaluateAdjointDifferentialCrossSection( 1e-2, 0.020001807385767029 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cs, 3.476975539039256546e+04, 1e-5 );
  }
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
                   evaluateAdjointCrossSection )
{
  double precision = 1e-5;
  double cross_section;

  // Native Electroionization using primary electron energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator,
                  ionization_min_function,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol,
                  false );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.361E-05, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   1.755054813563216400e+10,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.88E-05, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   1.051665027492438698e+10,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.123900E-02, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   8.240145836951123783e+05,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 8.75350E-01, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   9.200993640772635990e+04,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( grid_generator.getMaxIncomingEnergy(), precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   1.564045178753465279e+03,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( max_energy, precision );
  FRENSIE_CHECK_SMALL( cross_section, 1e-10 );
  }

  // Native Electroionization using knock-on electron energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator2,
                  ionization_min_function2,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.361E-05, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   3.487370980899057770e+10,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.88E-05, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   2.087237619683746338e+10,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1e-2, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   3.156589491447718814e+06,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 8.75350E-01, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   1.980256015241121058e+05,
                                   1e-5 );

  cross_section = grid_generator.evaluateAdjointCrossSection( grid_generator.getMaxIncomingEnergy(), precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   6.394264444875007939e+03,
                                   1e-5 );
  }

  // Native Bremsstrahlung using outgoing electron energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( brem_cs_evaluator,
                  brem_pdf_evaluator2,
                  brem_min_function2,
                  brem_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  1e-7,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.0e-5, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.351638054689366442e+01, 1e-2 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 5.0e-4, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.524064806248562931e+01, 1e-2 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.0, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.272042083081573960e-01, 1e-2 );

  cross_section = grid_generator.evaluateAdjointCrossSection( grid_generator.getMaxIncomingEnergy(), precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.839957621975410157e-02, 1e-2 );
  }

  // Native Bremsstrahlung using brem photon energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( brem_cs_evaluator,
                  brem_pdf_evaluator2,
                  brem_min_function2,
                  brem_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  1e-7,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol,
                  false );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.0e-5, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   4.351638054689366442e+01,
                                   1e-2 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 5.0e-4, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   2.524064806248562931e+01,
                                   1e-2 );

  cross_section = grid_generator.evaluateAdjointCrossSection( 1.0, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   5.272042083072600027e-01,
                                   1e-2 );

  cross_section = grid_generator.evaluateAdjointCrossSection( grid_generator.getMaxIncomingEnergy(), precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                   3.839957620874796806e-02,
                                   1e-2 );

  cross_section = grid_generator.evaluateAdjointCrossSection( max_energy, precision );
  FRENSIE_CHECK_SMALL( cross_section, 1e-10 );
  }
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
                   evaluateAdjointPDF )
{
  double diff_cross_section;

  // Native Electroionization using primary electron energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator,
                  ionization_min_function,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1e-2, 0.019992531061237977, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   2.107703779356190008e-02,
                                   1e-5 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1e-2, 0.020001807385767029, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   2.105672252086151011e-02,
                                   1e-6 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1e-2, 0.020011088014413269, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   2.103643167266970246e-02,
                                   1.0e-5 );
  }

  // Native Electroionization using knock-on electron energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator2,
                  ionization_min_function2,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol,
                  false );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1e-2, 0.019992531061237977, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   1.103296055519369274e-02,
                                   1e-5 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1e-2, 0.020001807385767029, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   1.101498123523672948e-02,
                                   1e-6 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1e-2, 0.020011088014413269, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   1.100152468338382039e-02,
                                   1.0e-5 );
  }

  // Native Bremsstrahlung using outgoing electron energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( brem_cs_evaluator,
                  brem_pdf_evaluator,
                  brem_min_function,
                  brem_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol,
                  false );

  diff_cross_section = grid_generator.evaluateAdjointPDF( 5.0e-4, 5.0e-3, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   1.274033943527141943,
                                   1e-3 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( max_energy, max_energy + brem_min_function(max_energy), 1.0e-4 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( grid_generator.getMaxIncomingEnergy(), max_energy, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   3.650288135897016618e+06,
                                   1e-5 );
  }

   // Native Bremsstrahlung using brem photon energy
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( brem_cs_evaluator,
                  brem_pdf_evaluator2,
                  brem_min_function2,
                  brem_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 5.0e-4, 5.0e-3, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   1.304982053060023350,
                                   1e-2 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( max_energy,
                                       max_energy + brem_min_function(max_energy),
                                       1.0e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   4.967620234690813348e+06,
                                   1e-2 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF(
        max_energy, max_energy + brem_min_function(max_energy) + 1e-7, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   3.171379277815473732e+06,
                                   1e-2 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( max_energy,
                                       grid_generator.getMaxOutgoingEnergy(),
                                       1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                   3.004094868198797107e+06,
                                   1e-2 );
  }
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung outgoing energy grid can be generated for H
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
                   generateAndEvaluateDistribution_brem_h )
{
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( brem_cs_evaluator,
                  brem_pdf_evaluator,
                  brem_min_function,
                  brem_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  // Set the primary energy grid
  std::vector<double> primary_energy_grid(3);
  primary_energy_grid[0] = 0.01;
  primary_energy_grid[1] = 1.0;
  primary_energy_grid[2] = 20.0;

  // cross section values
  std::vector<double> cross_sections(3);
  cross_sections[0] = 1.0;
  cross_sections[1] = 1.0;
  cross_sections[2] = 1.0;


  std::map<double,std::vector<double> > outgoing_energy_grid, pdf;

  // Generate an outgoing energy grid at E=0.01 MeV
  grid_generator.generateAndEvaluateDistributionOnPrimaryEnergyGrid(
          outgoing_energy_grid,
          pdf,
          1e-6,
          primary_energy_grid,
          cross_sections,
          0 );

  // Check the generated outgoing energy grid
  size_t length = outgoing_energy_grid[0.01].size();
  FRENSIE_CHECK_EQUAL( length, 406 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                   1.000016099117129707e-02,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 2.000000038495000609e+01, 1e-15 );

  // Check the evaluated pdf
  FRENSIE_CHECK_EQUAL( pdf[0.01].size(), 406 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].front(),
                                   2.990881441231125966e+06,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].back(),
                                   1.490279324963618507e-08,
                                   1e-6 );

  // Check the generated max energy grid
  length = outgoing_energy_grid[1.0].size();
  FRENSIE_CHECK_EQUAL( length, 416 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                   1.000000113241543920,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 2.000000038495000609e+01, 1e-15 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[1.0].size(), 416 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].front(),
                                   3.873460800275939982e+05,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].back(),
                                   3.775785017031689289e-06,
                                   1e-6 );

  // Check the generated max energy grid
  length = outgoing_energy_grid[20.0].size();
  FRENSIE_CHECK_EQUAL( length, 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[20.0].front(),
                                   2.000000018595000739e+01,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[20.0].back(), 2.000000038495000609e+01, 1e-15 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[20.0].size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[20.0].front(),
                                   4.060883440778022632e+05,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[20.0].back(),
                                   2.294577930913071032e+05,
                                   1e-6 );
  }

  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( brem_cs_evaluator,
                  brem_pdf_evaluator2,
                  brem_min_function2,
                  brem_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol,
                  false );

  // Set the primary energy grid
  std::vector<double> primary_energy_grid(2);
  primary_energy_grid[0] = 0.01;
  primary_energy_grid[1] = 1.0;

  // cross section values
  std::vector<double> cross_sections(2);
  cross_sections[0] = 1.0;
  cross_sections[1] = 1.0;

  std::map<double,std::vector<double> > outgoing_energy_grid, pdf;

  // Generate an outgoing energy grid at E=0.01 MeV
  grid_generator.generateAndEvaluateDistributionOnPrimaryEnergyGrid(
          outgoing_energy_grid,
          pdf,
          1e-6,
          primary_energy_grid,
          cross_sections,
          0 );

  // Check the generated outgoing energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[0.01].size(), 434 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                   1.0000101e-02,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.0, 1e-12 );

  // Check the evaluated pdf
  FRENSIE_CHECK_EQUAL( pdf[0.01].size(), 434 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].front(),
                                   2.964746405015475117e+06,
                                   1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].back(),
                                   1.306649507190665842e-08,
                                   1e-5 );

  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[1.0].size(), 378 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                   1.000000101,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.0, 1e-12 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[1.0].size(), 378 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].front(),
                                   3.904767041709205369e+05,
                                   1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].back(),
                                   4.491926441876438354e-06,
                                   1e-2 );
  }
}

//---------------------------------------------------------------------------//
// Check that the ionization outgoing energy grid can be generated for Si
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
                   generateAndEvaluateDistribution_ionization_si )
{
  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator,
                  ionization_min_function,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol,
                  false );

  // Set the primary energy grid
  std::vector<double> primary_energy_grid(8);
  primary_energy_grid[0] = 1e-5;
  primary_energy_grid[1] = 1e-4;
  primary_energy_grid[2] = 1e-3;
  primary_energy_grid[3] = 1e-2;
  primary_energy_grid[4] = 1e-1;
  primary_energy_grid[5] = 1.0;
  primary_energy_grid[6] = 10.0;
  primary_energy_grid[7] = grid_generator.getMaxIncomingEnergy();

  // cross section values
  std::vector<double> cross_sections(8);
  cross_sections[0] = 1.0;
  cross_sections[1] = 1.0;
  cross_sections[2] = 1.0;
  cross_sections[3] = 1.0;
  cross_sections[4] = 1.0;
  cross_sections[5] = 1.0;
  cross_sections[6] = 1.0;
  cross_sections[7] = 1.0;


  std::map<double,std::vector<double> > outgoing_energy_grid, pdf;

  // Generate an outgoing energy grid at E=0.01 MeV
  grid_generator.generateAndEvaluateDistributionOnPrimaryEnergyGrid(
          outgoing_energy_grid,
          pdf,
          1e-6,
          primary_energy_grid,
          cross_sections,
          0 );

  // Check the generated outgoing energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[0.01].size(), 261 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                   1.001888424818502855e-02,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.0, 1e-12 );

  // Check the evaluated pdf
  FRENSIE_CHECK_EQUAL( pdf[0.01].size(), 261 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].front(),
                                   3.466011435732554932e+11,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].back(),
                                   1.424141510374246764e+03,
                                   1e-6 );

  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[1.0].size(), 337 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                   1.000006621027896614,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.0, 1e-12 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[1.0].size(), 337 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].front(),
                                   1.812063055919265366e+10,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].back(),
                                   1.280301380379990639e-01,
                                   1e-6 );

  // Check the generated max energy grid
  double energy = grid_generator.getMaxIncomingEnergy();
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[energy].size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[energy].front(),
                                   1.999999980099552133e+01,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[energy].back(), 20.0, 1e-12 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[energy].size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[energy].front(),
                                   1.467361177588845634e+10,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[energy].back(),
                                   6.551681151980347633e+09,
                                   1e-6 );
  }

  {
  DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
  grid_generator( ionization_cs_evaluator,
                  ionization_pdf_evaluator2,
                  ionization_min_function2,
                  ionization_energy_grid,
                  min_energy,
                  max_energy,
                  min_energy_nudge_value,
                  max_energy_nudge_value,
                  convergence_tol,
                  absolute_diff_tol,
                  distance_tol );

  // Set the primary energy grid
  std::vector<double> primary_energy_grid(3);
  primary_energy_grid[0] = 0.01;
  primary_energy_grid[1] = 1.0;
  primary_energy_grid[2] = 20.0;

  // cross section values
  std::vector<double> cross_sections(3);
  cross_sections[0] = 1.0;
  cross_sections[1] = 1.0;
  cross_sections[2] = 1.0;

  std::map<double,std::vector<double> > outgoing_energy_grid, pdf;

  // Generate an outgoing energy grid at E=0.01 MeV
  grid_generator.generateAndEvaluateDistributionOnPrimaryEnergyGrid(
          outgoing_energy_grid,
          pdf,
          1e-6,
          primary_energy_grid,
          cross_sections,
          0 );

  // Check the generated outgoing energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[0.01].size(), 274 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                   1.000662100000000027e-02,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 2.000000681999999941e+01, 1e-6 );

  // Check the evaluated pdf
  FRENSIE_CHECK_EQUAL( pdf[0.01].size(), 274 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].front(),
                                   6.928568723063168945e+11,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].back(),
                                   2.795075426553683883e+03,
                                   1e-6 );

  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[1.0].size(), 343 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                   1.000006621000000040e+00,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 2.000000681999999941e+01, 1e-6 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[1.0].size(), 343 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].front(),
                                   3.622907066742088318e+10,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].back(),
                                   2.492927196616450125e-01,
                                   1e-6 );

  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[20.0].size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[20.0].front(),
                                   2.000000662100000071e+01,
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[20.0].back(), 2.000000681999999941e+01, 1e-6 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[20.0].size(), 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[20.0].front(),
                                   3.355889318427837372e+10,
                                   1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[20.0].back(),
                                   3.116084087798591232e+10,
                                   1e-6 );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_h_file_name;
std::string test_native_si_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_h_file",
                                        test_native_h_file_name, "",
                                        "Test Native H file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_si_file",
                                        test_native_si_file_name, "",
                                        "Test Native Si file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  double evaluation_tol = 1e-10;

  // Create the brem data with H
  {
    // Create the native H data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_h_file_name );

    // Extract the common electron energy grid
    std::shared_ptr<std::vector<double> > union_energy_grid(
        new std::vector<double>( data_container.getElectronEnergyGrid() ) );

    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                  union_energy_grid,
                  union_energy_grid->front(),
                  union_energy_grid->back(),
                  union_energy_grid->size()/10 + 1 ) );

    // Create bremsstrahlung data
    {
      // Create the bremsstrahlung reaction
      std::shared_ptr<const MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>> h_brem_reaction(
        new MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>(
          union_energy_grid,
          std::make_shared<std::vector<double> >( data_container.getBremsstrahlungCrossSection() ),
          data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
          grid_searcher ) );

      // Create the forward cross section evaluator
      brem_cs_evaluator = [h_brem_reaction](const double& incoming_energy){return h_brem_reaction->getCrossSection( incoming_energy );};

      // Create the bremsstrahlung secondary distribution
      brem_energy_grid = data_container.getBremsstrahlungEnergyGrid();
      std::vector<double> brem_max_energy_grid( brem_energy_grid.size() );
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
        secondary_dists( brem_energy_grid.size() );

      for( size_t n = 0; n < brem_energy_grid.size(); ++n )
      {
        double energy = brem_energy_grid[n];

        // Get the energy of the bremsstrahlung photon at the incoming energy
        std::vector<double> energy_bins(
            data_container.getBremsstrahlungPhotonEnergy( energy ) );

        // Get the bremsstrahlung photon pdf at the incoming energy
        std::vector<double> pdf(
            data_container.getBremsstrahlungPhotonPDF( energy ) );

        // Reverse the order of the energy bins and pdfs
        std::reverse(energy_bins.begin(), energy_bins.end() );
        std::reverse(pdf.begin(), pdf.end() );

        // Convert the photon energy to the outgoing electron energy
        std::for_each(energy_bins.begin(), energy_bins.end(), [ &energy ](double& energy_bin) { energy_bin = energy - energy_bin;});

        // Make sure the first energy_bin is > 0
        energy_bins[0] = 1e-15;

        // Set the max outgoing energy for the incoming energy
        brem_max_energy_grid[n] = energy_bins.back();

        // Set the secondary energy distribution
        secondary_dists[n].reset(
          new const Utility::TabularDistribution<Utility::LogLog>( energy_bins,
                                                                  pdf ) );
      }

      std::shared_ptr<const Utility::TabularUnivariateDistribution> max_energy_distribution(
          new const Utility::TabularDistribution<Utility::LogLog>( brem_max_energy_grid,
                                                                   brem_energy_grid ) );

      // Create the min adjoint energy gain function for brem
      brem_min_function = [max_energy_distribution](const double& energy){return max_energy_distribution->evaluate(energy) - energy;};

      // Create the scattering function
      std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> brem_distribution(
        new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                brem_energy_grid,
                secondary_dists,
                1e-6,
                evaluation_tol ) );

      // Create the forward pdf evaluator
      brem_pdf_evaluator = [brem_distribution](const double& incoming_energy, const double& outgoing_energy){return brem_distribution->evaluateSecondaryConditionalPDF( incoming_energy, outgoing_energy );};



      // Create the min adjoint energy function for bremsstrahlung
      brem_min_function2 = [](const double& energy){return 1e-7;};

      std::shared_ptr<const MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LogLog> > full_brem_reaction;

      MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
          data_container,
          union_energy_grid,
          grid_searcher,
          full_brem_reaction,
          MonteCarlo::DIPOLE_DISTRIBUTION,
          evaluation_tol );

      // Create the forward cross section evaluator
      brem_cs_evaluator2 = [full_brem_reaction](const double& incoming_energy){return full_brem_reaction->getCrossSection( incoming_energy );};


      for( size_t n = 0; n < brem_energy_grid.size(); ++n )
      {
        double energy = brem_energy_grid[n];

        // Get the energy of the bremsstrahlung photon at the incoming energy
        std::vector<double> energy_bins(
            data_container.getBremsstrahlungPhotonEnergy( energy ) );

        // Get the bremsstrahlung photon pdf at the incoming energy
        std::vector<double> pdf(
            data_container.getBremsstrahlungPhotonPDF( energy ) );

        secondary_dists[n].reset(
          new const Utility::TabularDistribution<Utility::LogLog>( energy_bins,
                                                                  pdf ) );
      }

      // Create the scattering function
      std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> brem_distribution2(
        new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                brem_energy_grid,
                secondary_dists,
                1e-6,
                evaluation_tol ) );


      // Create the forward pdf evaluator
      brem_pdf_evaluator2 = [brem_distribution2](const double& incoming_energy, const double& outgoing_energy){return brem_distribution2->evaluateSecondaryConditionalPDF( incoming_energy, incoming_energy - outgoing_energy); };

    }
  }


  // Create electroionization data with Si
  {
    // Create the native H data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_si_file_name );

    // Extract the common electron energy grid
    std::shared_ptr<std::vector<double> > union_energy_grid(
        new std::vector<double>( data_container.getElectronEnergyGrid() ) );

    std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                  union_energy_grid,
                  union_energy_grid->front(),
                  union_energy_grid->back(),
                  union_energy_grid->size()/10 + 1 ) );

    // Create electroionization subshell 6 data
    {
      // Extract the shell data
      unsigned shell = *(data_container.getSubshells().end()--);
      std::cout << std::setprecision(16) << std::scientific << "shell = \t" << shell << std::endl;


      binding_energy = data_container.getSubshellBindingEnergy( shell );

      // Create the electroionization reaction
      std::shared_ptr<const MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>> h_ionization_reaction(
        new MonteCarlo::VoidElectroatomicReaction<Utility::LogLog, false>(
          union_energy_grid,
          std::make_shared<std::vector<double> >( data_container.getElectroionizationCrossSection(shell) ),
          data_container.getElectroionizationCrossSectionThresholdEnergyIndex(shell),
          grid_searcher ) );

      // Create the forward cross section evaluator
      ionization_cs_evaluator = [h_ionization_reaction](const double& incoming_energy){return h_ionization_reaction->getCrossSection( incoming_energy );};

      // Create the electroionization secondary distribution
      ionization_energy_grid = data_container.getElectroionizationEnergyGrid(shell);
      std::vector<double> ionization_max_energy_grid( ionization_energy_grid.size() );
      std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
        secondary_dists( ionization_energy_grid.size() );


      for( size_t n = 0; n < ionization_energy_grid.size(); ++n )
      {
        double energy = ionization_energy_grid[n];

        // Get the energy of the knock-on electron energy at the incoming energy
        std::vector<double> knock_on_energy(
            data_container.getElectroionizationRecoilEnergy( shell, energy ) );

        // Get the knock-on electron pdf at the incoming energy
        std::vector<double> knock_on_pdf(
            data_container.getElectroionizationRecoilPDF( shell, energy ) );

        double energy_2k;
        // If the grid point is not greater than the binding energy then fix it
        if( energy <= binding_energy )
        {
          energy_2k = 2.0*knock_on_energy.back();
        }
        // Make sure the max knock-on energy matches the incoming energy
        else
        {
          double old_max = knock_on_energy.back();
          energy_2k = energy - binding_energy;
          knock_on_energy.back() = energy_2k/2.0;
        }

        // Evaluate the energy of the primary electron energy at the incoming energy
        std::vector<double>::iterator end = --knock_on_energy.end();

        std::vector<double> primary_energy( knock_on_energy.begin(), end );
        std::reverse(primary_energy.begin(), primary_energy.end() );

        std::for_each(primary_energy.begin(), primary_energy.end(), [ &energy_2k ](double& energy_bin) { energy_bin = energy_2k - energy_bin;});


        // Get the primary electron pdf at the incoming energy
        end = --knock_on_pdf.end();
        std::vector<double> primary_pdf( knock_on_pdf.begin(), end );
        std::reverse(primary_pdf.begin(), primary_pdf.end() );

        std::vector<double> energy_bins;
        energy_bins.reserve( knock_on_energy.size() + primary_energy.size() ); // preallocate memory
        energy_bins.insert( energy_bins.end(), knock_on_energy.begin(), knock_on_energy.end() );
        energy_bins.insert( energy_bins.end(), primary_energy.begin(), primary_energy.end() );
        std::vector<double> pdf;
        pdf.reserve( knock_on_pdf.size() + primary_pdf.size() ); // preallocate memory
        pdf.insert( pdf.end(), knock_on_pdf.begin(), knock_on_pdf.end() );
        pdf.insert( pdf.end(), primary_pdf.begin(), primary_pdf.end() );

        // Set the max outgoing energy for the incoming energy
        ionization_max_energy_grid[n] = energy_bins.back();

        // Set the secondary energy distribution
        secondary_dists[n].reset(
          new const Utility::TabularDistribution<Utility::LogLog>( energy_bins,
                                                                  pdf ) );
      }

      std::shared_ptr<const Utility::TabularUnivariateDistribution> max_energy_distribution(
          new const Utility::TabularDistribution<Utility::LogLog>( ionization_max_energy_grid,
                                                                   ionization_energy_grid ) );

      // Create the min adjoint energy function for electroionization
      ionization_min_function = [max_energy_distribution](const double& energy){return max_energy_distribution->evaluate(energy) - energy;};

      // Create the scattering function
      std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> ionization_distribution(
        new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogLog> >(
                ionization_energy_grid,
                secondary_dists,
                1e-6,
                evaluation_tol ) );

      // Create the forward pdf evaluator
      ionization_pdf_evaluator = [ionization_distribution](const double& incoming_energy, const double& outgoing_energy){return ionization_distribution->evaluateSecondaryConditionalPDF( incoming_energy, outgoing_energy );};


      std::vector<double> ionization_min_energy_grid( ionization_energy_grid.size() );
      for( size_t n = 0; n < ionization_energy_grid.size(); ++n )
      {
        double energy = ionization_energy_grid[n];

        // Get the energy of the knock-on electron energy at the incoming energy
        std::vector<double> knock_on_energy(
            data_container.getElectroionizationRecoilEnergy( shell, energy ) );

        // Get the knock-on electron pdf at the incoming energy
        std::vector<double> knock_on_pdf(
            data_container.getElectroionizationRecoilPDF( shell, energy ) );

        ionization_min_energy_grid[n] = knock_on_energy.front();

        // Make sure the max knock-on energy matches the incoming energy
        if( ionization_energy_grid[n] > binding_energy )
        {
          double old_max = knock_on_energy.back();
          knock_on_energy.back() = (energy - binding_energy)/2.0;
        }
        secondary_dists[n].reset(
          new const Utility::TabularDistribution<Utility::LogLog>( knock_on_energy,
                                                                   knock_on_pdf ) );
      }

      std::shared_ptr<const Utility::TabularUnivariateDistribution> min_energy_distribution(
          new const Utility::TabularDistribution<Utility::LogLog>( ionization_max_energy_grid,
                                                                   ionization_min_energy_grid ) );

      // Create the min adjoint energy function for electroionization
      ionization_min_function2 = [min_energy_distribution](const double& energy){return min_energy_distribution->evaluate(energy) + binding_energy;};

      // Create the scattering function
      std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> ionization_distribution2(
        new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBase<Utility::LogLogLog> >(
                ionization_energy_grid,
                secondary_dists,
                1e-6,
                evaluation_tol ) );

      // Create the forward pdf evaluator
      ionization_pdf_evaluator2 = [ionization_distribution2](const double& incoming_energy, const double& outgoing_energy){
        double energy = outgoing_energy;
        double max_knock_on_energy = (incoming_energy - binding_energy)/2.0;
        if ( outgoing_energy > max_knock_on_energy)
        {
          energy = incoming_energy - binding_energy - outgoing_energy;
        }

        auto f_min = [&ionization_distribution2](double x){return ionization_distribution2->getLowerBoundOfSecondaryConditionalIndepVar(x); };
        auto f_max = [](double x){return (x - binding_energy)/2.0; };
        return ionization_distribution2->evaluateSecondaryConditionalPDF( incoming_energy, energy, f_min, f_max );
      };
    }
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectronGridGenerator.cpp
//---------------------------------------------------------------------------//
