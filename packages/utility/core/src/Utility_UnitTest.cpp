//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTest.cpp
//! \author Alex Robinson
//! \brief  The unit test base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_UnitTest.hpp"
#include "Utility_UnitTestManager.hpp"
#include "Utility_DynamicOutputFormatter.hpp"

namespace Utility{

namespace {
size_t creation_counter = 0u;
}

// Constructor
UnitTest::UnitTest( const std::string& group_name,
                    const std::string& test_name,
                    const std::string& data_name )
  : d_group_name( group_name ),
    d_test_name( test_name ),
    d_data_name( data_name ),
    d_creation_order_index( creation_counter++ )
{
  // Register the test with the manager
  UnitTestManager::getInstance().addUnitTest( *this );
}

// Return the group name
const std::string& UnitTest::getGroupName() const
{
  return d_group_name;
}

// Return the test name
const std::string& UnitTest::getTestName() const
{
  return d_test_name;
}

// Return the combined group and test name
std::string UnitTest::getCombinedGroupTestName() const
{
  return d_group_name + "/" + d_test_name;
}

// Return the data name
const std::string& UnitTest::getDataName() const
{
  return d_data_name;
}

// Return the full name
std::string UnitTest::getFullName() const
{
  if( d_data_name.size() == 0 )
    return this->getCombinedGroupTestName();
  else
    return this->getCombinedGroupTestName() + ":" + this->getDataName();
}

// Get the creation order index
size_t UnitTest::getCreationOrderIndex() const
{
  return d_creation_order_index;
}

// Run the unit test and place report in output stream
bool UnitTest::run( std::ostream& os,
                    size_t& number_of_checks,
                    size_t& number_of_passed_checks,
                    size_t& number_of_unexpected_exceptions ) const
{
  bool success = true;

  size_t checkpoint = this->getLineNumber();

  try{
    this->runImpl( os,
                   success,
                   number_of_checks,
                   number_of_passed_checks,
                   checkpoint );
  }
  __FRENSIE_TEST_CATCH_STATEMENTS__( os, true, success, checkpoint, number_of_unexpected_exceptions, UnitTestManager::getTestDetailsStartingRightShift() );

  return success;
}
    
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UnitTest.cpp
//---------------------------------------------------------------------------//
