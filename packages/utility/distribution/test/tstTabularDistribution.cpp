//---------------------------------------------------------------------------//
//!
//! \file   tstTabularDistribution.cpp
//! \author Alex Robinson
//! \brief  Tabular distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

typedef std::tuple<Utility::LinLin,
                   Utility::LogLin,
                   Utility::LinLog,
                   Utility::LogLog
                  > TestInterpPolicies;

typedef std::tuple<
  std::tuple<si::energy,si::amount,cgs::energy,si::amount>,
  std::tuple<cgs::energy,si::amount,si::energy,si::amount>,
  std::tuple<si::energy,si::length,cgs::energy,cgs::length>,
  std::tuple<cgs::energy,cgs::length,si::energy,si::length>,
  std::tuple<si::energy,si::mass,cgs::energy,cgs::mass>,
  std::tuple<cgs::energy,cgs::mass,si::energy,si::mass>,
  std::tuple<si::energy,si::dimensionless,cgs::energy,cgs::dimensionless>,
  std::tuple<cgs::energy,cgs::dimensionless,si::energy,si::dimensionless>,
  std::tuple<si::energy,void*,cgs::energy,void*>,
  std::tuple<cgs::energy,void*,si::energy,void*>,
  std::tuple<ElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<ElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<void*,MegaElectronVolt,void*,KiloElectronVolt>
 > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<Utility::PropertyTree> test_dists_ptree;

std::shared_ptr<Utility::OneDDistribution> distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_distribution;

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;
std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
unit_aware_tab_distribution;

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the LinLin property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable_LinLin )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::TabularDistribution<Utility::LinLin> dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_full_ucase_name" ) << "Distribution A" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLin>( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 1.0, 2.0} );
  NEW_ROW( "inline_full_lcase_name" ) << "Distribution B" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {0.0, pi/4, pi/2, 3*pi/4, pi} );
  NEW_ROW( "inline_short_ucase_name" ) << "Distribution C" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLin>( {0.0, 1.0}, {1.0, 1.0} );
  NEW_ROW( "inline_short_lcase_name" ) << "Distribution D" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLin>( {-1.0, 1.0}, {2.0, 2.0} );
  NEW_ROW( "inline_bad_type" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_0_args" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_1_arg" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_indep_vals" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_unsorted_indep_vals" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_start_indep_val" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_end_indep_val" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_dep_vals" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_dep_val" ) << "Distribution M" << false << no_unused_children << dummy_dist;

  NEW_ROW( "full_ucase_name" ) << "Distribution N" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLin>( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 1.0, 2.0} );
  NEW_ROW( "full_lcase_name" ) << "Distribution O" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {0.0, pi/4, pi/2, 3*pi/4, pi} );
  NEW_ROW( "short_ucase_name" ) << "Distribution P" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {0.0, pi/4, pi/2, 3*pi/4, pi} );
  NEW_ROW( "short_lcase_name" ) << "Distribution Q" << true << std::vector<std::string>( {"dummy"} ) << Utility::TabularDistribution<Utility::LinLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {0.0, pi/4, pi/2, 3*pi/4, pi} );
  NEW_ROW( "repeated_keys" ) << "Distribution R" << true << std::vector<std::string>( {"independent values", "dependent values"} ) << Utility::TabularDistribution<Utility::LinLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {0.0, pi/4, pi/2, 3*pi/4, pi} );
  NEW_ROW( "bad_type" ) << "Distribution S" << false << no_unused_children << dummy_dist;
  NEW_ROW( "0_args" ) << "Distribution T" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inep_vals_only" ) << "Distribution U" << false << no_unused_children << dummy_dist;
  NEW_ROW( "dep_vals_only" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_indep_vals" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "unsorted_indep_vals" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_start_indep_val" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_end_indep_val" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_dep_vals" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_dep_val" ) << "Distribution AB" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_dep_val" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
}

// This table describes the data in the LogLin property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable_LogLin )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::TabularDistribution<Utility::LogLin> dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_full_ucase_name" ) << "Distribution A" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLin>( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 1.0, 2.0} );
  NEW_ROW( "inline_full_lcase_name" ) << "Distribution B" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {pi/4, pi/2, 3*pi/4, pi, 5*pi/4} );
  NEW_ROW( "inline_short_ucase_name" ) << "Distribution C" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLin>( {0.0, 1.0}, {1.0, 1.0} );
  NEW_ROW( "inline_short_lcase_name" ) << "Distribution D" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLin>( {-1.0, 1.0}, {1.0, 1.0} );
  NEW_ROW( "inline_bad_type" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_0_args" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_1_arg" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_indep_vals" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_unsorted_indep_vals" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_start_indep_val" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_end_indep_val" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_dep_vals" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_dep_val" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_dep_val" ) << "Distribution N" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_dep_val" ) << "Distribution O" << false << no_unused_children << dummy_dist;

  NEW_ROW( "full_ucase_name" ) << "Distribution P" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLin>( {-2.0, -1.0, 1.0, 2.0}, {2.0, 1.0, 1.0, 2.0} );
  NEW_ROW( "full_lcase_name" ) << "Distribution Q" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {pi/4, pi/2, 3*pi/4, pi, 5*pi/4} );
  NEW_ROW( "short_ucase_name" ) << "Distribution R" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {pi/4, pi/2, 3*pi/4, pi, 5*pi/4} );
  NEW_ROW( "short_lcase_name" ) << "Distribution S" << true << std::vector<std::string>( {"dummy"} ) << Utility::TabularDistribution<Utility::LogLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {pi, 5*pi/4, 3*pi/2, 7*pi/4, 2*pi} );
  NEW_ROW( "repeated_keys" ) << "Distribution T" << true << std::vector<std::string>( {"independent values", "dependent values"} ) << Utility::TabularDistribution<Utility::LogLin>( {-1.0, -0.5, 0.0, 0.5, 1.0}, {pi/4, pi/2, 3*pi/4, pi, 5*pi/4} );
  NEW_ROW( "bad_type" ) << "Distribution U" << false << no_unused_children << dummy_dist;
  NEW_ROW( "0_args" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inep_vals_only" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "dep_vals_only" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_indep_vals" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "unsorted_indep_vals" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_start_indep_val" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_end_indep_val" ) << "Distribution AB" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_dep_vals" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_dep_val" ) << "Distribution AD" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_dep_val" ) << "Distribution AE" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_dep_val" ) << "Distribution AF" << false << no_unused_children << dummy_dist;
}

// This table describes the data in the LinLog property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable_LinLog )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::TabularDistribution<Utility::LinLog> dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_full_ucase_name" ) << "Distribution A" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLog>( {1e-4, 1.0}, {2.0, 1.0} );
  NEW_ROW( "inline_full_lcase_name" ) << "Distribution B" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLog>( {1e-4, 1.0}, {1.0, 2.0} );
  NEW_ROW( "inline_short_ucase_name" ) << "Distribution C" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLog>( {1.0, 10.0}, {1.0, 1.0} );
  NEW_ROW( "inline_short_lcase_name" ) << "Distribution D" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLog>( {0.1, 1.0}, {2.0, 2.0} );
  NEW_ROW( "inline_bad_type" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_0_args" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_1_arg" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_indep_vals" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_unsorted_indep_vals" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_start_indep_val" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_start_indep_val" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_start_indep_val" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_end_indep_val" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_dep_vals" ) << "Distribution N" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_dep_val" ) << "Distribution O" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_dep_val" ) << "Distribution P" << false << no_unused_children << dummy_dist;

  NEW_ROW( "full_ucase_name" ) << "Distribution Q" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLog>( {1e-4, 1.0}, {2.0, 1.0} );
  NEW_ROW( "full_lcase_name" ) << "Distribution R" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLog>( {1e-4, 1.0}, {pi/4, 5*pi/4} );
  NEW_ROW( "short_ucase_name" ) << "Distribution S" << true << no_unused_children << Utility::TabularDistribution<Utility::LinLog>( {1e-4, 1.0}, {pi/4, 5*pi/4} );
  NEW_ROW( "short_lcase_name" ) << "Distribution T" << true << std::vector<std::string>( {"dummy"} ) << Utility::TabularDistribution<Utility::LinLog>( {1e-4, 1.0}, {pi/4, 5*pi/4} );
  NEW_ROW( "repeated_keys" ) << "Distribution U" << true << std::vector<std::string>( {"independent values", "dependent values"} ) << Utility::TabularDistribution<Utility::LinLog>( {1e-4, 1.0}, {pi/4, 5*pi/4} );
  NEW_ROW( "bad_type" ) << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "0_args" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inep_vals_only" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "dep_vals_only" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_indep_vals" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "unsorted_indep_vals" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_start_indep_val" ) << "Distribution AB" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_start_indep_val" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_start_indep_val" ) << "Distribution AD" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_end_indep_val" ) << "Distribution AE" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_dep_vals" ) << "Distribution AF" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_dep_val" ) << "Distribution AG" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_dep_val" ) << "Distribution AH" << false << no_unused_children << dummy_dist;
}

// This table describes the data in the LogLog property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable_LogLog )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::TabularDistribution<Utility::LogLog> dummy_dist;

  double pi = Utility::PhysicalConstants::pi;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_full_ucase_name" ) << "Distribution A" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLog>( {1e-4, 1.0}, {1.0, 1e3} );
  NEW_ROW( "inline_full_lcase_name" ) << "Distribution B" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLog>( {1e-4, 1.0}, {pi/2, 2*pi} );
  NEW_ROW( "inline_short_ucase_name" ) << "Distribution C" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLog>( {1.0, 10.0}, {1.0, 1.0} );
  NEW_ROW( "inline_short_lcase_name" ) << "Distribution D" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLog>( {0.1, 1.0}, {2.0, 2.0} );
  NEW_ROW( "inline_bad_type" ) << "Distribution E" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_0_args" ) << "Distribution F" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_1_arg" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_indep_vals" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_unsorted_indep_vals" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_start_indep_val" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_start_indep_val" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_start_indep_val" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_end_indep_val" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_too_few_dep_vals" ) << "Distribution N" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_dep_val" ) << "Distribution O" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_dep_val" ) << "Distribution P" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_dep_val" ) << "Distribution Q" << false << no_unused_children << dummy_dist;

  NEW_ROW( "full_ucase_name" ) << "Distribution R" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLog>( {1e-4, 1.0}, {1.0, 1e3} );
  NEW_ROW( "full_lcase_name" ) << "Distribution S" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLog>( {1e-4, 1.0}, {pi/2, 2*pi} );
  NEW_ROW( "short_ucase_name" ) << "Distribution T" << true << no_unused_children << Utility::TabularDistribution<Utility::LogLog>( {1e-4, 1.0}, {1e-4, 10.0} );
  NEW_ROW( "short_lcase_name" ) << "Distribution U" << true << std::vector<std::string>( {"dummy"} ) << Utility::TabularDistribution<Utility::LogLog>( {1e-4, 1.0}, {1e-3, 10.0} );
  NEW_ROW( "repeated_keys" ) << "Distribution V" << true << std::vector<std::string>( {"independent values", "dependent values"} ) << Utility::TabularDistribution<Utility::LogLog>( {1e-4, 1.0}, {1e-3, 10.0} );
  NEW_ROW( "bad_type" ) << "Distribution W" << false << no_unused_children << dummy_dist;
  NEW_ROW( "0_args" ) << "Distribution X" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inep_vals_only" ) << "Distribution Y" << false << no_unused_children << dummy_dist;
  NEW_ROW( "dep_vals_only" ) << "Distribution Z" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_indep_vals" ) << "Distribution AA" << false << no_unused_children << dummy_dist;
  NEW_ROW( "unsorted_indep_vals" ) << "Distribution AB" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_start_indep_val" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_start_indep_val" ) << "Distribution AD" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_start_indep_val" ) << "Distribution AE" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_end_indep_val" ) << "Distribution AF" << false << no_unused_children << dummy_dist;
  NEW_ROW( "too_few_dep_vals" ) << "Distribution AG" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_dep_val" ) << "Distribution AH" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_dep_val" ) << "Distribution AI" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_dep_val" ) << "Distribution AJ" << false << no_unused_children << dummy_dist;
}

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initialize( std::shared_ptr<BaseDistribution>& dist )
{
  // Use the basic constructor
  std::vector<typename BaseDistribution::IndepQuantity>
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], 1e-3 );
  Utility::setQuantity( independent_values[1], 1e-2 );
  Utility::setQuantity( independent_values[2], 1e-1 );
  Utility::setQuantity( independent_values[3], 1.0 );

  std::vector<typename BaseDistribution::DepQuantity> dependent_values( 4 );
  Utility::setQuantity( dependent_values[0], 1e2 );
  Utility::setQuantity( dependent_values[1], 1e1 );
  Utility::setQuantity( dependent_values[2], 1.0 );
  Utility::setQuantity( dependent_values[3], 1e-1 );

  dist.reset(new Utility::UnitAwareTabularDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
							  independent_values,
							  dependent_values ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            evaluate,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-3 ), 1e2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-2 ), 1e1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1e-1 ), 1.0 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 1e-1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            evaluate,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1e-3*MeV ),
		       1e2*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1e-2*MeV ),
		       1e1*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1e-1*MeV ),
		       1.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       1e-1*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 2.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            evaluatePDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-3 ),
			  67.340006734,
			  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-2 ),
			  6.7340006734,
			  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-1 ),
			  0.67340006734,
			  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 1.0 ),
			  0.067340006734,
			  1e-6 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            evaluatePDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			     unit_aware_distribution->evaluatePDF( 1e-3*MeV ),
			     67.340006734/MeV,
			     1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			     unit_aware_distribution->evaluatePDF( 1e-2*MeV ),
			     6.7340006734/MeV,
			     1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			     unit_aware_distribution->evaluatePDF( 1e-1*MeV ),
			     0.67340006734/MeV,
			     1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			      unit_aware_distribution->evaluatePDF( 1.0*MeV ),
			      0.067340006734/MeV,
			      1e-6 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 2.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            evaluateCDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 0.0 ), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-3 ),
			  0.0000000000,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-2 ),
			  0.33333333333,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-1 ),
			  0.66666666667,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ),
			  1.0000000000,
			  1e-10 );
  FRENSIE_CHECK_EQUAL( tab_distribution->evaluateCDF( 2.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            evaluateCDF,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 0.0*MeV ),
		       0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-3*MeV ),
			  0.0000000000,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-2*MeV ),
			  0.33333333333,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-1*MeV ),
			  0.66666666667,
			  1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1.0*MeV ),
			  1.0000000000,
			  1e-10 );
  FRENSIE_CHECK_EQUAL( unit_aware_tab_distribution->evaluateCDF( 2.0*MeV ),
		       1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sample,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sample,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleAndRecordTrials,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleAndRecordTrials,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*MeV );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleAndRecordBinIndex,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleAndRecordBinIndex,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_EQUAL( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
  FRENSIE_CHECK_EQUAL( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleWithRandomNumber,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleWithRandomNumber,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 1e-1  );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = tab_distribution->sampleInSubrange( 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 1e-1 );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3 );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1e-1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV  );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1*MeV, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV );
  FRENSIE_CHECK_GREATER_OR_EQUAL( sample, 1e-3*MeV );
  FRENSIE_CHECK_LESS_OR_EQUAL( sample, 1e-1*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            sampleWithRandomNumberInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( tab_distribution );

  double sample =
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1e-1  );
  FRENSIE_CHECK_EQUAL( sample, 1e-3 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            sampleWithRandomNumberInSubrange,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<MegaElectronVolt> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							       0.0, 1e-1*MeV );
  FRENSIE_CHECK_EQUAL( sample, 1e-3*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange(
							       1.0, 1e-1*MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 1e-1*MeV, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            getUpperBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            getUpperBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            getLowerBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            getLowerBoundOfIndepVar,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       1e-3*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            getDistributionType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            getDistributionType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            getDistributionTypeName,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  FRENSIE_CHECK_EQUAL( Utility::TabularDistribution<InterpolationPolicy>::typeName( true, false, " " ),
                       std::string("Tabular ")+InterpolationPolicy::name()+" Distribution" );

  FRENSIE_CHECK_EQUAL( Utility::TabularDistribution<InterpolationPolicy>::typeName( false, false, " " ),
                       std::string("Tabular ")+InterpolationPolicy::name() );
  
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::TabularDistribution<InterpolationPolicy> >(),
                       std::string("Tabular")+InterpolationPolicy::name()+"Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            getDistributionTypeName,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>::typeName( true, false, " " )),
                       std::string("Tabular ")+InterpolationPolicy::name()+" Distribution" );

  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>::typeName( false, false, " " )),
                       std::string("Tabular ")+InterpolationPolicy::name() );
  
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> >()),
                       (std::string("UnitAwareTabular")+InterpolationPolicy::name()+"Distribution<"+Utility::typeName<MegaElectronVolt,si::amount>()+">" ));
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            isTabular,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            isTabular,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            isContinuous,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            isContinuous,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            isCompatibleWithInterpType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( distribution );

  if( boost::is_same<InterpolationPolicy,Utility::LinLin>::value )
  {
    FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  }
  else
  {  
    FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LinLog>::value )
  {
    FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }
  else
  {
    FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LogLin>::value )
  {
    FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  }
  else
  {
    FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LogLog>::value )
  {
    FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
  else
  {
    FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            isCompatibleWithInterpType,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );
  
  initialize<InterpolationPolicy>( unit_aware_distribution );

  if( boost::is_same<InterpolationPolicy,Utility::LinLin>::value )
  {
    FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  }
  else
  {  
    FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LinLog>::value )
  {
    FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }
  else
  {
    FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LogLin>::value )
  {
    FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  }
  else
  {
    FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LogLog>::value )
  {
    FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
  else
  {
    FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            toString,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";
  
  std::string dist_string = Utility::toString( Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  std::unique_ptr<Utility::OneDDistribution> local_dist( new Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  dist_string = Utility::toString( *local_dist );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            toString,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  std::string dist_string = Utility::toString( Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ) );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  std::unique_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > local_dist( new Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ) );

  dist_string = Utility::toString( *local_dist );

  FRENSIE_CHECK_EQUAL( dist_string, std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            toStream,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  std::ostringstream oss;
  Utility::toStream( oss, Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  std::unique_ptr<Utility::OneDDistribution> local_dist( new Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  Utility::toStream( oss, *local_dist );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            toStream,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";
  
  std::ostringstream oss;
  Utility::toStream( oss, Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ) );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  std::unique_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > local_dist( new Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ) );

  Utility::toStream( oss, *local_dist );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            ostream_operator,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";
  
  std::ostringstream oss;
  oss << Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  std::unique_ptr<Utility::OneDDistribution> local_dist( new Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  oss << *local_dist;

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            ostream_operator,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";
  
  std::ostringstream oss;
  oss << Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} );

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );

  oss.str( "" );
  oss.clear();

  std::unique_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > local_dist( new Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ) );

  oss << *local_dist;

  FRENSIE_CHECK_EQUAL( oss.str(), std::string("{")+dist_name+", {1.000000000000000000e+00, 2.000000000000000000e+00, 3.000000000000000000e+00}, {3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}}" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a string
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            fromString,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";
  
  Utility::TabularDistribution<InterpolationPolicy> test_dist =
    Utility::fromString<Utility::TabularDistribution<InterpolationPolicy> >( std::string("{") + dist_name + ", {1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            fromString,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";
  
  Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> test_dist =
    Utility::fromString<Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> >( std::string("{") + dist_name + ", {1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} )) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            fromStream,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  std::istringstream iss( std::string("{") + dist_name + ", {1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}}" );
  Utility::TabularDistribution<InterpolationPolicy> test_dist;
  
  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            fromStream,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  std::istringstream iss( std::string("{") + dist_name + ", {1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}}" );
  Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> test_dist;
  
  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} )) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            istream_operator,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  std::istringstream iss( std::string("{") + dist_name + ", {1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}}" );
  Utility::TabularDistribution<InterpolationPolicy> test_dist;
  
  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            istream_operator,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  std::istringstream iss( std::string("{") + dist_name + ", {1.0, 2.0, 3.0}, {3.0, 2.0, 1.0}}" );
  Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} )) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
FRENSIE_UNIT_TEST_TEMPLATE( TabularDistribution,
                            toPropertyTree,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  Utility::TabularDistribution<InterpolationPolicy> copy_dist =
    ptree.get<Utility::TabularDistribution<InterpolationPolicy> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::TabularDistribution<InterpolationPolicy> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  ptree = Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), dist_name );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "independent values" ),
                       std::vector<double>( {1, 2, 3} ) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "dependent values" ),
                       std::vector<double>( {3, 2, 1} ) );

  // Use the propery tree helper methods
  ptree = Utility::toPropertyTree( Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ), true );

  copy_dist = ptree.get_value<Utility::TabularDistribution<InterpolationPolicy> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ) );

  ptree = Utility::toPropertyTree( Utility::TabularDistribution<InterpolationPolicy>( {1, 2, 3}, {3, 2, 1} ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), dist_name );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "independent values" ),
                       std::vector<double>( {1, 2, 3} ) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "dependent values" ),
                       std::vector<double>( {3, 2, 1} ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST_TEMPLATE( UnitAwareTabularDistribution,
                            toPropertyTree,
                            TestInterpPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, InterpolationPolicy );

  std::string dist_name( "Tabular " );
  dist_name += InterpolationPolicy::name();
  dist_name += " Distribution";

  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} )) );

  Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> copy_dist =
    ptree.get<Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> >( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} )) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} )) );

  ptree = Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), dist_name );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "independent values" ),
                       std::vector<double>( {1, 2, 3} ) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "dependent values" ),
                       std::vector<double>( {3, 2, 1} ) );

  // Use the propery tree helper methods
  ptree = Utility::toPropertyTree( Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> >();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( {1, 2, 3}, {3, 2, 1} ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 3 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), dist_name );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "independent values" ),
                       std::vector<double>( {1, 2, 3} ) );
  FRENSIE_CHECK_EQUAL( ptree.get<std::vector<double> >( "dependent values" ),
                       std::vector<double>( {3, 2, 1} ) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( TabularDistribution,
                        fromPropertyTree_LinLin,
                        TestPropertyTreeTable_LinLin )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree linlin_ptree = test_dists_ptree->get_child( "LinLin" );
  Utility::TabularDistribution<Utility::LinLin> dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LinLin>, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( linlin_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW(
                  dist.fromPropertyTree( linlin_ptree.get_child( dist_name ) ),
                  Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LinLin>, expected_dist );

    FRENSIE_CHECK_NO_THROW(
      dist = Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LinLin> >(
                                      linlin_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
     Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LinLin> >(
                                    linlin_ptree.get_child( dist_name ) ),
     Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareTabularDistribution,
                        fromPropertyTree_LinLin,
                        TestPropertyTreeTable_LinLin )
{
  typedef Utility::UnitAwareTabularDistribution<Utility::LinLin,MegaElectronVolt,si::amount> DistributionType;
  
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree linlin_ptree = test_dists_ptree->get_child( "LinLin" );
  DistributionType dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( linlin_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( linlin_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<DistributionType>(
                                      linlin_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<DistributionType>(
                                    linlin_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( TabularDistribution,
                        fromPropertyTree_LogLin,
                        TestPropertyTreeTable_LogLin )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree loglin_ptree = test_dists_ptree->get_child( "LogLin" );
  Utility::TabularDistribution<Utility::LogLin> dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LogLin>, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( loglin_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW(
                  dist.fromPropertyTree( loglin_ptree.get_child( dist_name ) ),
                  Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LogLin>, expected_dist );

    FRENSIE_CHECK_NO_THROW(
      dist = Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LogLin> >(
                                      loglin_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
     Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LogLin> >(
                                    loglin_ptree.get_child( dist_name ) ),
     Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareTabularDistribution,
                        fromPropertyTree_LogLin,
                        TestPropertyTreeTable_LogLin )
{
  typedef Utility::UnitAwareTabularDistribution<Utility::LogLin,MegaElectronVolt,si::amount> DistributionType;
  
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree loglin_ptree = test_dists_ptree->get_child( "LogLin" );
  DistributionType dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( loglin_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( loglin_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<DistributionType>(
                                      loglin_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<DistributionType>(
                                    loglin_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( TabularDistribution,
                        fromPropertyTree_LinLog,
                        TestPropertyTreeTable_LinLog )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree linlog_ptree = test_dists_ptree->get_child( "LinLog" );
  Utility::TabularDistribution<Utility::LinLog> dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LinLog>, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( linlog_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW(
                  dist.fromPropertyTree( linlog_ptree.get_child( dist_name ) ),
                  Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LinLog>, expected_dist );

    FRENSIE_CHECK_NO_THROW(
      dist = Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LinLog> >(
                                      linlog_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
     Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LinLog> >(
                                    linlog_ptree.get_child( dist_name ) ),
     Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareTabularDistribution,
                        fromPropertyTree_LinLog,
                        TestPropertyTreeTable_LinLog )
{
  typedef Utility::UnitAwareTabularDistribution<Utility::LinLog,MegaElectronVolt,si::amount> DistributionType;
  
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree linlog_ptree = test_dists_ptree->get_child( "LinLog" );
  DistributionType dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( linlog_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( linlog_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<DistributionType>(
                                      linlog_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<DistributionType>(
                                    linlog_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( TabularDistribution,
                        fromPropertyTree_LogLog,
                        TestPropertyTreeTable_LogLog )
{
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree linlog_ptree = test_dists_ptree->get_child( "LogLog" );
  Utility::TabularDistribution<Utility::LogLog> dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LogLog>, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( linlog_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW(
                  dist.fromPropertyTree( linlog_ptree.get_child( dist_name ) ),
                  Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( Utility::TabularDistribution<Utility::LogLog>, expected_dist );

    FRENSIE_CHECK_NO_THROW(
      dist = Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LogLog> >(
                                      linlog_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW(
     Utility::fromPropertyTree<Utility::TabularDistribution<Utility::LogLog> >(
                                    linlog_ptree.get_child( dist_name ) ),
     Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareTabularDistribution,
                        fromPropertyTree_LogLog,
                        TestPropertyTreeTable_LogLog )
{
  typedef Utility::UnitAwareTabularDistribution<Utility::LogLog,MegaElectronVolt,si::amount> DistributionType;
  
  FETCH_FROM_TABLE( std::string, dist_name );
  FETCH_FROM_TABLE( bool, valid_dist_rep );
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children );

  Utility::PropertyTree linlog_ptree = test_dists_ptree->get_child( "LogLog" );
  DistributionType dist;
  std::vector<std::string> unused_children;

  // Use the PropertyTreeCompatibleObject interface
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( linlog_ptree.get_child( dist_name ), unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );

    unused_children.clear();
  }
  else
  {
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( linlog_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }

  // Use the property tree helper methods
  if( valid_dist_rep )
  {
    FETCH_FROM_TABLE( DistributionType, expected_dist );

    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<DistributionType>(
                                      linlog_ptree.get_child( dist_name ),
                                      unused_children ) );
    FRENSIE_CHECK_EQUAL( dist, expected_dist );
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );
  }
  else
  {
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<DistributionType>(
                                    linlog_ptree.get_child( dist_name ) ),
                         Utility::PropertyTreeConversionException );
  }
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareTabularDistribution,
				   explicit_conversion,
				   TestUnitTypeQuads )
{
  FETCH_TEMPLATE_PARAM( 0, RawIndepUnitA );
  FETCH_TEMPLATE_PARAM( 1, RawDepUnitA );
  FETCH_TEMPLATE_PARAM( 2, RawIndepUnitB );
  FETCH_TEMPLATE_PARAM( 3, RawDepUnitB );

  typedef typename std::remove_pointer<RawIndepUnitA>::type IndepUnitA;
  typedef typename std::remove_pointer<RawDepUnitA>::type DepUnitA;
  typedef typename std::remove_pointer<RawIndepUnitB>::type IndepUnitB;
  typedef typename std::remove_pointer<RawDepUnitB>::type DepUnitB;
  
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  initialize<Utility::LinLin>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::TabularDistribution<Utility::LinLin>*>( distribution.get() ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 0.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 0.1 );
  Utility::setQuantity( inv_indep_quantity_a, 0.67340006734 );
  Utility::setQuantity( dep_quantity_a, 1.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-6 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_json_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_OPTION( "test_dists_json_file",
              boost::program_options::value<std::string>(&test_dists_json_file_name)->default_value(""),
              "Test distributions json file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );

  test_dists_json_file >> *test_dists_ptree;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTabularDistribution.cpp
//---------------------------------------------------------------------------//
