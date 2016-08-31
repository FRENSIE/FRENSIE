//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_UnitTestHarnessExtensions.hpp
//! \author Alex Robinson
//! \brief  Extensions to the Teuchos_UnitTestHarness
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_UNIT_TEST_HARNESS_EXTENSIONS_HPP
#define MONTE_CARLO_UNIT_TEST_HARNESS_EXTENSIONS_HPP

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"

/*! \brief A macro for the Teuchos Unit Test Harness for creating a
 * templated unit test on an PhaseSpaceDimension enum.
 * \ingroup unit_test_harness_extensions
 */
#define MC_UNIT_TEST_EPSD_TEMPLATE_1_DECL(TEST_GROUP, TEST_NAME, EPSD_VALUE) \
  template<MonteCarlo::PhaseSpaceDimension EPSD_VALUE>		\
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest( const std::string& value )	\
    : Teuchos::UnitTestBase(						\
		       #TEST_GROUP, value+"_"+std::string(#TEST_NAME) ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<MonteCarlo::PhaseSpaceDimension EPSD_VALUE>		\
  void TEST_GROUP##_##TEST_NAME##_UnitTest<EPSD_VALUE>::runUnitTestImpl(\
		          Teuchos::FancyOStream &out, bool &success ) const \


#endif // end MONTE_CARLO_UNIT_TEST_HARNESS_EXTENSIONS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_UnitTestHarnessExtensions.hpp
//---------------------------------------------------------------------------//
