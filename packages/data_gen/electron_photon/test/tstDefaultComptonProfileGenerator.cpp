//---------------------------------------------------------------------------//
//!
//! \file   tstDefaultComptonProfileGenerator.cpp
//! \author Alex Robinson
//! \brief  Default occupation number profile generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "DataGen_ComptonProfileGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_1 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 1 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 1 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.6000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_2 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 2 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 1 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 5.3500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.9000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_3 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 3 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 2 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.2900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.8000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.9400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 4.4000E-12 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_4 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 4 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 2 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.3400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.5000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_5 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 5 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 3 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.8600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.0000E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 9.4000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 6.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.7000E-14 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_6 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 6 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 3 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 5.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 8.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.8800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 8.0000E-14 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_7 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 7 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 3 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 6.7200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 6.2000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.0000E-13 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_8 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 8 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 3 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.7900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 8.5000E-13 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_9 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 9 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 3 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.0000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.1000E-12 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_10 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 10 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 3 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 9.0000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 4.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.7400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.8000E-12 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_11 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 11 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.9000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 7.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.2500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.1000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.0700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.7000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_12 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 12 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 4 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.4500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.9200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.4000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.5900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.5000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_13 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 13 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 5 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 6.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.6800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.8000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.2400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 9.1900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.6000E-12 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_14 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 14 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 5 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 6.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.7500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 8.9000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.0400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.1000E-12 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_15 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 15 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 5 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 5.9200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 5.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 4.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.3400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.5000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 8.9700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.3100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 8.7000E-12 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_16 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 16 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 5 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 5.5300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 6.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 7.9400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.7000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_17 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 17 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 5 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 5.2000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 8.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.2000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 7.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 7.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 4.9000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.0000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_18 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 18 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 5 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 4.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.9800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 6.5000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 6.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 4.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.1000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_19 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 19 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 6 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 4.6400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 9.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 9.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 5.7000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 3.7600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.0000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 2.4600E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.3000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_20 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 20 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 6 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 4.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.7400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 9.0200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 5.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 3.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.9500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.4000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_21 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 21 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 4.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 8.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 4.7100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 3.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.1000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.5000E-13 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.8400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.8000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_22 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 22 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.9900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.5500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 7.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 4.4100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.8200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.5000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 2.7500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.5000E-14 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.7600E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.4000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_23 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 23 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.4700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 4.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 7.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 4.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 2.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.2000E-13 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.6900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.9000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_24 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 24 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 5.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.4000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 5.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 7.1600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 5.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.9800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 7.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 2.6100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.1000E-13 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.8500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.6000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_25 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 25 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 6.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 6.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 6.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 8.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.7300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 8.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.3500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 2.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 8.2000E-13 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.5900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.3000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_26 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 26 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 7.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 6.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.5500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 2.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.3000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.5500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 5.1000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_27 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 27 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 9.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 9.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 6.2100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.9000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.7000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.5100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 6.0000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_28 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 28 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 5.9500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.2500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.7900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.4000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.4700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 7.1000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_29 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 29 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 3.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 5.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.9600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.5000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.6400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 5.9000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_30 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 30 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 7 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 5.4900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.9900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.8600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.6200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.2000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.4100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 9.4000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_31 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 31 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 8 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 5.2800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.7600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.4600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.0000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.1800E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 9.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.5000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_32 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 32 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 8 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.7200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 1.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 5.0900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.7100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.6700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.5000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.0300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 7.6900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.8000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_33 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 33 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 8 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 9.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.9100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 6.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.1000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 9.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 6.7400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 4.6000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_34 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 34 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 8 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 9.3900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 7.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.4700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.9000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 8.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 6.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 7.0000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_35 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 35 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 8 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 9.0900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 9.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.3600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.8000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 7.7200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 6.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 5.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.0000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_36 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 36 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 8.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 6.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.3300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 4.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.3400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 4.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 1.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 1.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 9.3000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 7.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 4.9600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 5.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.9000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_37 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 37 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 13 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 5.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 8.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 7.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 4.2900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.2900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.3100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 9.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.8000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 9.5700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 6.3100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 4.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 5.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 4.4300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.5600E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 6.2000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_38 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 38 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 13 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.2100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 6.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 8.0900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 8.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 4.0600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 4.1600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 2.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 7.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.2500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 9.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.5000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 9.0700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 5.7300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 3.8900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 7.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 3.9700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 4.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.0600E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.2000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_39 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 39 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 14 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 7.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 9.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.9400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 5.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 4.0400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.9600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.1800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 9.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 8.5600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 8.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.2000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 5.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 3.6100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 3.6600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 5.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 4.5400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.5000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.9000E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.6000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_40 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 40 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 14 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.0900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 7.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 6.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.9200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.8900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 6.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 8.1600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 4.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 8.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 5.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 3.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 3.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 7.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 3.9300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.6000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.8000E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.0000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_41 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 41 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 14 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 2.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 8.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 7.4100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 7.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.8200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 7.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 7.7900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 5.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 7.8700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 3.8000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 4.8000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 3.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 3.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 3.2600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 9.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 3.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.5000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.8800E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.9000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_42 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 42 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 15 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 9.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 7.2000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.6000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 8.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.7600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 8.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 7.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 7.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 7.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 4.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 4.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 3.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 3.0600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 3.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 3.4700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 5.2000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 3.5700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.4000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.8200E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.3000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_43 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 43 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 15 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.9300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 7.0000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.6100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.7000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 1.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 7.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 9.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 7.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 6.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 4.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 4.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.8700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.9100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.9900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 8.3000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 3.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 5.5000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.6200E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.2000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_44 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 44 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 15 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.8800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 6.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.4100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 6.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 9.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 1.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 6.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 6.9700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 8.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 4.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 5.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.7600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.8100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.9600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 3.0300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 6.9000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.7400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.9000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_45 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 45 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 15 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 6.6400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.3200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 7.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.5900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 9.4900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 9.7300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 6.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 6.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 3.9900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 6.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.6300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 4.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.7000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.7700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 2.8300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 9.4000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.7000E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.3000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_46 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 46 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 14 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.7900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 6.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 8.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.5400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 9.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 9.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 6.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 6.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 3.8600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 6.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.5400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 5.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.6100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.7800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.8000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 2.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.2000E-10 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_47 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 47 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 15 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 6.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 9.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 8.9100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 4.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 9.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 6.2000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 6.2500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 3.6900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 8.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 6.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 3.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.4700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 2.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.6400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.0000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_48 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 48 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 15 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 6.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 3.0700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.4500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 8.6400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 5.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 8.8800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 6.0000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 6.0500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 3.5200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 9.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 8.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 4.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 2.2800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.4500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 5.7000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_49 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 49 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 16 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 6.0000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.9900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.4100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 8.3800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 8.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 5.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 5.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 3.3600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.1900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.2600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 5.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 2.0600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 4.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 2.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.2000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.2400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 8.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 9.6200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 4.2000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_50 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 50 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 16 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.9200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 3.0400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 6.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 8.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 7.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 8.3900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 5.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 4.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 5.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 3.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 3.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 6.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.9200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 6.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.9300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 4.2000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.1000E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 8.3600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.7000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_51 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 51 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 17 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.7200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 7.9100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 8.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 8.1600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 5.4600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 5.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 5.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 3.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 3.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 2.0000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 2.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 7.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.7900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 8.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.8100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 5.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.0000E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 7.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 7.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 4.7000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_52 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 52 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 17 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.5600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.7800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.9100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 7.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 9.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 7.9400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 5.3000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 7.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 5.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 4.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.9600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.9100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.9800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 8.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.6800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.7000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 7.2000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 9.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.6500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 6.9300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.6000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_53 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 53 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 17 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.5300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 4.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.7200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.2600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 8.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 7.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 7.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 5.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 5.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 8.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 5.2100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 5.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.8400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.9000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.5900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.6100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 9.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 8.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 6.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 8.9000E-09 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_54 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 54 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 17 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.4900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 4.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 5.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.7900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 7.2900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 7.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 6.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 5.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 5.0700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 6.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.7400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.7600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.8200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 7.9700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.6200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 2.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.9200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.2000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_55 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 55 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 18 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.4600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 2.9000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 4.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 6.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.7300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 7.1000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 7.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 7.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.8800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.9400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 7.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.7000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.7600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.4500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 7.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.9800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 3.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.7400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.7000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_56 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 56 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 18 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.1200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 5.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 7.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.6800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 6.9200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 7.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 8.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 9.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.5500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.6300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.6900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 6.5700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.5200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 4.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.7300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 2.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.2300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.1000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_57 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 57 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 19 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 5.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 5.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 8.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 6.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 7.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 9.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.4600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 4.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.6300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.3100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 6.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.4000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 2.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 5.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.0700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 3.9000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_58 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 58 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.3700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 6.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 9.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.5700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.1100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 6.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 6.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 3.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 5.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.5900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 4.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.2900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.5000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 5.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 4.3100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 4.9800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.0500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 4.2000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_59 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 59 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 19 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.8000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 6.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.3800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 6.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 6.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.4100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.3400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 3.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 5.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.2500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 5.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.2600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.8000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 5.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 7.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 4.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.1500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 3.8000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_60 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 60 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 19 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.3200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 3.9000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.7000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 7.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.3300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.0600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 6.2800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 6.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.2800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 3.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.4600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 6.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.5200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 3.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.2100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 6.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.4100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.8000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.9700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 5.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 8.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 4.3400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.1300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 4.0000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_61 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 61 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 19 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.2900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.6100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 7.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.2800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 6.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 6.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.2100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 4.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 7.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.4800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 3.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.1800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 7.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.1900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 4.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.3400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 6.1000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.8600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.9900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 9.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 4.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 4.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.1100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 4.2000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_62 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 62 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 19 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 8.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.3900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 6.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 1.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 1.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.9900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 6.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.1200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 4.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 4.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 8.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.4500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 3.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 9.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 5.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.2900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 7.8000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.7500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.9100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 4.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 4.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.0900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 4.5000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_63 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 63 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 9.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 7.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 9.9200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 4.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 6.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 4.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 4.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 4.0800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 4.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.3500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 9.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 4.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 6.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 9.9000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.6000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 7.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.8400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 4.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 5.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.0700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 4.8000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_64 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 64 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 21 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.2200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 4.9000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 9.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.3000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 8.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 9.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.7300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 4.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 6.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.9400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 5.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.9900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 3.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 5.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.3200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.3800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 4.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.1000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 7.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.4000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 9.1000E-12 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.3800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 8.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.6600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.9100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 6.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 4.6800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 6.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.9300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 5.9000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_65 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 65 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.2000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 5.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.1000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 8.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 9.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.6100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 5.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.8900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 6.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.9100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 4.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 2.0300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 5.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.2900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.3600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 5.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 9.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.6000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.2100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.0000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 8.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.7000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 4.0000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 6.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.0300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 5.3000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_66 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 66 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 5.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.0600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.2200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 9.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 9.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.4900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.7700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.7800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 7.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 4.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.9900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 6.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.2600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 6.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.0600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.0000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.3000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.3500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 9.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.9400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 7.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.0100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 5.6000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_67 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 67 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 5.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.1000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 2.0200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 9.1200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.3700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 7.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.6600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.7000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 9.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.7600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 5.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.9400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 6.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 6.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 1.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.1000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.5000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.7000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.2600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 9.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.8800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 7.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.9900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 5.9000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_68 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 68 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 6.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 4.0200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 8.9300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 2.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 7.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.5600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 6.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.9000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 7.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.2100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.2800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 7.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 9.9600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 1.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.2000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.1000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 2.1000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.8300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 8.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.9700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 6.2000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_69 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 69 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 6.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.9500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.9400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 8.7600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.1600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 8.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.4500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 7.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.8600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 7.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.1800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.2500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 8.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 9.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 9.9400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.0000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 2.6000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.4700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.7800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 9.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.9500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 6.5000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_70 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 70 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 20 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.0900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 6.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.8800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.0800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 8.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 5.0500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 9.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 8.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.8300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 8.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 9.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 9.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 9.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 1.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.9000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 1.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 3.2000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 5.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.7300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.9400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 6.8000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_71 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 71 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 21 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.0700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 6.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.8700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.0500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 8.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.9500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.4900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 9.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.7900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 8.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 9.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 9.5100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 9.5300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 6.4000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 9.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 4.2000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.8000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.5400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 4.8900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.7700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 8.7000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_72 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 72 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 21 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.0500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.8300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 2.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 8.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 3.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 5.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.7500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 9.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.1000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.1800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 9.0800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 4.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 9.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 8.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 8.2000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 9.0700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 5.4000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.6100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.3800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 4.2300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 2.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.6800E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.0000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_73 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 73 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 21 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.8000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 4.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 8.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.7600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 5.0800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 5.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.3000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.3700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.7100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 9.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 8.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 5.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 9.0500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 8.5300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.0000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 8.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.9000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.4300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 3.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 4.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 3.8200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 2.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.6100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.2000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_74 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 74 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 21 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 1.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 7.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.6100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.7700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 5.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.9500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.9600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.9900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 6.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.6700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 8.6300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 6.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 8.8300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 8.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 8.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 8.7000E-11 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.9100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 4.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.1100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 3.5200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 3.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.5500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.3000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_75 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 75 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 22 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 9.9700E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 8.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.7300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 5.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.9200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.9100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 6.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.2500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.6300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.0300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 4.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.1000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 8.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 6.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 8.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 7.7700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 7.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 4.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 1.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.7900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 5.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 3.0000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 3.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 4.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 3.4600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 2.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.4900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.5000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_76 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 76 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 22 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 9.8000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 8.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 1.9000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.7000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 6.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.8900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 7.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.1200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.2000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.6000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 1.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 4.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 8.2200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 8.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 8.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 4.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 7.4400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 7.5100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.9700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 2.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.6800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 6.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.9000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 3.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 6.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 3.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 3.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.4400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.7000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_77 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 77 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 22 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 9.6200E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 8.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 6.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.8700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.5300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 4.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 7.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.0700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 9.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 4.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.0600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 8.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 9.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 8.2200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 5.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 7.1600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 7.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.8400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 2.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 7.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.8100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 3.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.9100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 7.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 3.0600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 4.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.4000E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.8000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_78 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 78 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 22 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 9.4600E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 8.9000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.6400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 7.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 2.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 8.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 3.0200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.0900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 9.6400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 5.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 7.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 8.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 6.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 6.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 2.0000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.7500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 2.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 8.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.7400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 3.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.8700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 8.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 3.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 4.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.4500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.8000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_79 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 79 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 22 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 9.2900E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 9.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.6100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 8.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.8100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 9.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.9700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 4.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.0400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 9.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 6.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 1.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 7.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 7.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 6.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 6.6600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.8000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 2.5000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.6300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 2.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 9.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.6600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 3.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.7300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 2.8800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 5.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.4100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.9000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_80 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 80 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 22 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 9.1300E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 9.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.2500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 9.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.7900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.9200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 5.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 3.0000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.4700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 9.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 6.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 9.9500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 7.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 7.6800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 7.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 6.4500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.5300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 3.0000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 2.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 4.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.5200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 2.6500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 7.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.2900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 2.4000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_81 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 81 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 23 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.9800E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 9.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.2000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 9.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.7600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 7.0200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 5.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 2.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.4500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.8700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 5.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.9500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 3.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 9.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 7.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 9.7600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 2.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 7.3300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 7.5100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 8.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 6.2500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 5.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.3300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 3.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 3.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.4600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 4.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.3500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 2.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 9.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.1500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 3.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 9.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 6.8000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_82 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 82 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 23 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.8200E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.0000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.5300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 3.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.8900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 6.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 4.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.3800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.8300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 6.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 3.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.4100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 8.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 8.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 9.5700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 3.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 7.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 7.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 6.0600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 6.8000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 6.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 4.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.2500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 3.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 5.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.2100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 2.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 2.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.0400E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 3.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 8.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 9.8000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_83 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 83 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.6700E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.0000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.0900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.7800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 6.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.9600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.3200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.7800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 7.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.8600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 4.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.3800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 8.6600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 8.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 9.3900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 3.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 7.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 7.2000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 5.8900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 8.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.9700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 5.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 3.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.2800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 6.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 2.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 2.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 2.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.4000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 9.5500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 4.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 7.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 8.3200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 4.3000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_84 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 84 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.5200E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.1000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 3.0400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.6600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 6.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 3.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.2500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 8.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 4.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.3500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 8.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 9.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 9.2100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 3.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.8800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 7.0600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 5.7300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 9.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.8000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 3.0300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 3.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 2.0000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 1.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 7.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.9700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 3.2000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 2.0300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.7000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 8.8700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 5.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 6.4500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 7.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 5.8000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_85 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 85 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.3800E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.1000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.9900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.4500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 4.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 6.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.8300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 4.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.7000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 8.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.7800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 4.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.3200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 8.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 9.0400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 4.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.9100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 5.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 7.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.9300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 4.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.9300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.1200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 8.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.8800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 3.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.9400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 2.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 8.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 5.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 5.9300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 2.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 6.9200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 7.4000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_86 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 86 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 24 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.2300E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.1000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.9400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.4400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.7600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 4.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.6600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 9.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 5.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 1.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 8.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 8.8700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 4.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.6100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.7800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 5.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 8.8000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.8400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 4.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.8700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 2.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 9.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.7900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 4.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 2.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 7.8200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 6.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 5.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 2.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 6.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 9.1000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_87 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 87 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 25 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 8.0900E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.2000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.8900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 2.9000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.7000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 4.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.0700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.7000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 6.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 7.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 8.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 4.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 1.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 5.3000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.3700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.7500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 4.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.8100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 2.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.9900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.7200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 5.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.7700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 3.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 7.1400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 7.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 4.9600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 3.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 5.7100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 2.6500E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 4.6000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_88 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 88 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 25 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.9600E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.2000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.3700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.6000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 5.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.6400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 5.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 4.0100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 1.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.6600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 6.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.2500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 7.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 8.5600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 5.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 3.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 5.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.6600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 4.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.7500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.9200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.6500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 6.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.7000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 3.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 6.5700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 8.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 4.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 4.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 5.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 2.1900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 7.3000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_89 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 89 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 26 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.8200E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.2000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.8000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 1.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 6.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 7.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 5.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.9500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 7.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 7.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 8.4100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 5.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 4.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 5.0500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.1200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 5.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.6900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.8700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 7.6000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.6300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 4.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 6.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 9.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 4.2900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 5.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 4.8400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 6.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 4.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 1.9900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 9.3000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_90 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 90 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 26 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.6900E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.3000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.3300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.5600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 6.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 6.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 8.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 5.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.9000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 8.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.2000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 7.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 8.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 6.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 4.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.2800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.9300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 2.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 5.0000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 5.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.6400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 3.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.8100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.5200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 8.9000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.5700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 4.8000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 5.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 4.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 6.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 4.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 2.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 5.3500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 6.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 1.8600E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 1.1000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_91 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 91 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.5600E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.3000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.7100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.3000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 7.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.9300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 8.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.4600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 9.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.1800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 7.3800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 8.1200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 6.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 6.0000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 5.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 2.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.8200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.8900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 1.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.4500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 5.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.6100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 4.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.7700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 5.5000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 2.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 2.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 5.8000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 4.0100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 6.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 4.5900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 2.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 5.5800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 7.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.9300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 9.9000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_92 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 92 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.4300E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.3000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.6700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.2800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.3000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 7.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 8.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 6.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.7900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 1.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 7.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 1.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 7.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.8900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 6.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 6.0600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.7200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 3.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.7900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 2.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.3800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 5.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.5700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 4.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.7300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.4500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 6.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.9300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 3.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 5.6500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 3.9000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 7.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 4.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 2.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 5.4300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 8.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.9100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 1.0000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_93 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 93 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.3000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.3000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 8.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.7500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 8.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 7.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.7400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 7.1000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 7.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.7900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 6.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.9600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 3.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.6200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 2.6000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 4.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.6900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 1.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.4500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 7.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.8200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 4.3000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 5.5200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 3.8000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 8.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 4.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 2.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 5.3200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 9.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.8900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 1.0000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_94 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 94 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 26 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.1800E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.4000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.5800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.5000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.4900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 8.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.6500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 8.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.2900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 7.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 2.9000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.3700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.4500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.1100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 6.9700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.7200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 8.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.6900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 7.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.8500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 4.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.5200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 4.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.6000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 3.0000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.2800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 5.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.6600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 8.0000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.8300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 5.0000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 5.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 3.7600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 9.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 4.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 2.8000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 1.9900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 8.8000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_95 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 95 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 7.0500E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.4000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.5400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.2100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 2.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.4700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 9.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.5700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 8.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.6400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.3300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.0900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 6.8400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.6000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 9.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 8.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.7600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 4.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 5.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 3.4000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.2200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.4600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 5.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.6200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.3600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 9.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.7400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 6.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 1.8700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 3.6000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 5.3800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 3.6700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 4.4100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 3.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.9700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 8.9000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_96 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 96 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 28 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 6.9300E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.4000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.4500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 9.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 9.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.5900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.3000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 2.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.3900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.0700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 6.7200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 9.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.4900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 9.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.6600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 4.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.3500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 6.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 3.9000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.1700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.4200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 6.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.5900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.3200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 1.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.3600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.5900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 7.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 1.6600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 4.9000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 5.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 3.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 4.2100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 3.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 5.1600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 1.3000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[27].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[27].rbegin(),
                                                   subshell_half_profiles[27].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[27].front(), 1.8300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[27].back(), 1.1000E-07 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_97 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 97 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 6.8100E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.5000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.4600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.7000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.1700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.4300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.3900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 9.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.5500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 6.6000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 2.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.5700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 5.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 7.2000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 4.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.1300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.3900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 6.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 2.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.6000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 9.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 1.6900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 5.4000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 5.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 3.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 4.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 3.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.9300E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 9.1000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_98 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 98 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 6.7000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.5000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.4200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.4000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.4100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.5000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.0800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.0000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.5000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 3.8000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.2400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.3300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 6.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.2500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.1000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.3100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.4800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 6.0000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.1900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 8.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.2600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 5.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.0800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 6.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.3600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 7.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.5300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 2.8000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.2700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 2.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.3100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.5400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.1000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 1.6200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 6.5000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 5.0500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 3.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 1.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 4.2100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 3.9000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.9100E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 9.1000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_99 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 99 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 6.5800E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.5000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.3800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.1300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.6000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.6000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 3.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.1000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.4600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.0000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.2100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 3.6000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.3000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 1.9000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 1.0200E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 6.3600E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.1400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.2000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.2300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.4000E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 6.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 9.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 5.8000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 2.0400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 7.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.3300E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 8.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.5000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 3.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.2400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 2.7000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.2800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.4000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.4900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.3000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 1.5600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 7.7000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 4.9500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 3.3700E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 4.1500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 4.2000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.8900E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 9.1000E-08 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be generated
FRENSIE_UNIT_TEST( DefaultComptonProfileGenerator,
                   generateHalfProfiles_100 ){
  std::vector<std::vector<double> > subshell_half_profiles;
  std::vector<double> union_half_momentum_grid;

  std::shared_ptr<DataGen::ComptonProfileGenerator> generator = 
    DataGen::ComptonProfileGenerator::getDefaultGenerator( 100 );

  generator->generateHalfProfiles( subshell_half_profiles,
                                   union_half_momentum_grid );

  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( union_half_momentum_grid.begin(),
                                                   union_half_momentum_grid.end() ) );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( union_half_momentum_grid.back(), 100.0 );

  FRENSIE_REQUIRE_EQUAL( subshell_half_profiles.size(), 27 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[0].rbegin(),
                                                   subshell_half_profiles[0].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].front(), 6.4600E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[0].back(), 1.5000E-03 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[1].rbegin(),
                                                   subshell_half_profiles[1].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].front(), 2.3400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[1].back(), 3.9000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[2].rbegin(),
                                                   subshell_half_profiles[2].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].front(), 1.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[2].back(), 3.8000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[3].rbegin(),
                                                   subshell_half_profiles[3].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].front(), 1.3800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[3].back(), 1.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[4].rbegin(),
                                                   subshell_half_profiles[4].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].front(), 5.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[4].back(), 9.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[5].rbegin(),
                                                   subshell_half_profiles[5].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].front(), 2.9800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[5].back(), 1.2000E-04 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[6].rbegin(),
                                                   subshell_half_profiles[6].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].front(), 3.4100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[6].back(), 4.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[7].rbegin(),
                                                   subshell_half_profiles[7].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].front(), 2.1800E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[7].back(), 4.0000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[8].rbegin(),
                                                   subshell_half_profiles[8].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].front(), 2.2700E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[8].back(), 2.1000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[9].rbegin(),
                                                   subshell_half_profiles[9].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].front(), 9.9900E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[9].back(), 2.7000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[10].rbegin(),
                                                   subshell_half_profiles[10].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].front(), 6.2500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[10].back(), 3.4000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[11].rbegin(),
                                                   subshell_half_profiles[11].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].front(), 7.0300E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[11].back(), 1.3000E-05 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[12].rbegin(),
                                                   subshell_half_profiles[12].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].front(), 5.1500E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[12].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[13].rbegin(),
                                                   subshell_half_profiles[13].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].front(), 5.3200E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[13].back(), 7.3000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[14].rbegin(),
                                                   subshell_half_profiles[14].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].front(), 4.0400E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[14].back(), 1.1000E-08 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[15].rbegin(),
                                                   subshell_half_profiles[15].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].front(), 4.1100E-02 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[15].back(), 6.7000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[16].rbegin(),
                                                   subshell_half_profiles[16].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].front(), 1.9900E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[16].back(), 7.2000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[17].rbegin(),
                                                   subshell_half_profiles[17].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].front(), 1.3000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[17].back(), 8.7000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[18].rbegin(),
                                                   subshell_half_profiles[18].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].front(), 1.4800E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[18].back(), 3.3000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[19].rbegin(),
                                                   subshell_half_profiles[19].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].front(), 1.2100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[19].back(), 3.1000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[20].rbegin(),
                                                   subshell_half_profiles[20].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].front(), 1.2600E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[20].back(), 1.6000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[21].rbegin(),
                                                   subshell_half_profiles[21].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].front(), 1.4400E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[21].back(), 1.5000E-09 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[22].rbegin(),
                                                   subshell_half_profiles[22].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].front(), 1.5100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[22].back(), 9.1000E-10 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[23].rbegin(),
                                                   subshell_half_profiles[23].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].front(), 4.8500E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[23].back(), 1.4000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[24].rbegin(),
                                                   subshell_half_profiles[24].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].front(), 3.3100E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[24].back(), 1.5000E-06 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[25].rbegin(),
                                                   subshell_half_profiles[25].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].front(), 4.1000E-01 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[25].back(), 4.5000E-07 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].size(), 31 );
  FRENSIE_CHECK( Utility::Sort::isSortedAscending( subshell_half_profiles[26].rbegin(),
                                                   subshell_half_profiles[26].rend() ) );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].front(), 1.8700E+00 );
  FRENSIE_CHECK_EQUAL( subshell_half_profiles[26].back(), 9.1000E-08 );
}

//---------------------------------------------------------------------------//
// end tstDefaultComptonProfileGenerator.cpp
//---------------------------------------------------------------------------//
