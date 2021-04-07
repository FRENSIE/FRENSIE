//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointKleinNishinaSamplingType.hpp
//! \author Alex Robinson
//! \brief  Adjoint Klein-Nishina sampling type helper function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_AdjointKleinNishinaSamplingType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a sampling type can be converted to a string
FRENSIE_UNIT_TEST( AdjointKleinNishinaSamplingType, toString )
{
  std::string sampling_name =
    Utility::toString( MonteCarlo::TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING );

  FRENSIE_CHECK_EQUAL( sampling_name, "Two Branch Rejection Adjoint Klein-Nishina Sampling" );

  sampling_name = Utility::toString( MonteCarlo::THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING );

  FRENSIE_CHECK_EQUAL( sampling_name, "Three Branch Lin Mixed Adjoint Klein-Nishina Sampling" );

  sampling_name = Utility::toString( MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING );

  FRENSIE_CHECK_EQUAL( sampling_name, "Three Branch Log Mixed Adjoint Klein-Nishina Sampling" );
}

//---------------------------------------------------------------------------//
// Check that a sampling type can be placed in a stream
FRENSIE_UNIT_TEST( AdjointKleinNishinaSamplingType, ostream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING;

  FRENSIE_CHECK_EQUAL( oss.str(), "Two Branch Rejection Adjoint Klein-Nishina Sampling" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING;

  FRENSIE_CHECK_EQUAL( oss.str(), "Three Branch Lin Mixed Adjoint Klein-Nishina Sampling" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING;

  FRENSIE_CHECK_EQUAL( oss.str(), "Three Branch Log Mixed Adjoint Klein-Nishina Sampling" );
}

//---------------------------------------------------------------------------//
// Check that a sampling type can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( AdjointKleinNishinaSamplingType,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_adjoint_kn_sampling_type" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    MonteCarlo::AdjointKleinNishinaSamplingType type_1 =
      MonteCarlo::TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING;

    MonteCarlo::AdjointKleinNishinaSamplingType type_2 =
      MonteCarlo::THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING;

    MonteCarlo::AdjointKleinNishinaSamplingType type_3 =
      MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( type_3 ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  MonteCarlo::AdjointKleinNishinaSamplingType type_1, type_2, type_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_2 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( type_3 ) );

  iarchive.reset();

  FRENSIE_CHECK_EQUAL( type_1, MonteCarlo::TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_2, MonteCarlo::THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING );
  FRENSIE_CHECK_EQUAL( type_3, MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING );
}

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointKleinNishinaSamplingType.hpp
//---------------------------------------------------------------------------//
