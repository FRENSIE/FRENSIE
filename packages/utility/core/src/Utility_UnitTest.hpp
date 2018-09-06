//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTest.hpp
//! \author Alex Robinson
//! \brief  The unit test base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_HPP
#define UTILITY_UNIT_TEST_HPP

// Std Lib Includes
#include <iostream>
#include <string>

namespace Utility{

/*! The unit test base class
 * \ingroup unit_test_framework
 */
class UnitTest
{

public:

  //! Constructor
  UnitTest( const std::string& group_name,
            const std::string& test_name,
            const std::string& data_name = "" );

  //! Destructor
  virtual ~UnitTest()
  { /* ... */ }

  //! Run the unit test and place report in output stream
  bool run( std::ostream& os,
            size_t& number_of_checks,
            size_t& number_of_passed_checks,
            size_t& number_of_unexpected_exceptions ) const;

  //! Return the group name
  const std::string& getGroupName() const;

  //! Return the test name
  const std::string& getTestName() const;

  //! Return the combined group and test name
  std::string getCombinedGroupTestName() const;

  //! Return the data name
  const std::string& getDataName() const;

  //! Return the full name
  std::string getFullName() const;

  //! Get the creation order index
  size_t getCreationOrderIndex() const;

  //! Return the file where the unit test object is located
  virtual std::string getFile() const = 0;

  //! Return the line number where the unit test object run impl. was defined
  virtual size_t getLineNumber() const = 0;

protected:

  //! Unit test definition
  virtual void runImpl( std::ostream& os,
                        bool& success,
                        size_t& number_of_checks,
                        size_t& number_of_passed_checks,
                        size_t& last_checkpoint_line_number ) const = 0;

private:

  // The less than operator is a friend
  friend bool operator<( const UnitTest&, const UnitTest& );

  // The group name
  std::string d_group_name;

  // The test name
  std::string d_test_name;

  // The data name
  std::string d_data_name;

  // The creation order index
  size_t d_creation_order_index;
};

/*! Less than comparison operator
 *
 * The group name will be compared first, then the creation order index.
 */
inline bool operator<( const UnitTest& lhs, const UnitTest& rhs )
{
  if( lhs.d_group_name < rhs.d_group_name )
    return true;
  else if( lhs.d_group_name > rhs.d_group_name )
    return false;
  
  // Group names are equal - compare creation order index
  else
    return lhs.d_creation_order_index < rhs.d_creation_order_index;
}

//! Comparison helper function for UnitTest*
inline bool compareUnitTestPointers( const UnitTest* lhs, const UnitTest* rhs )
{
  return *lhs < *rhs;
}
  
} // end Utility namespace

#endif // end UTILITY_UNIT_TEST_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTest.hpp
//---------------------------------------------------------------------------//
