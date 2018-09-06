//---------------------------------------------------------------------------//
//!
//! \file   Utility_DataUnitTest.hpp
//! \author Alex Robinson
//! \brief  The data unit test base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DATA_UNIT_TEST_HPP
#define UTILITY_DATA_UNIT_TEST_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_UnitTest.hpp"
#include "Utility_UnitTestDataTable.hpp"

namespace Utility{

/*! The data unit test base class
 * \ingroup unit_test_framework
 */
class DataUnitTest : public UnitTest
{
  
public:

  //! Constructor
  DataUnitTest( const std::string& group_name,
                const std::string& test_name,
                const std::string& data_table_row_name,
                const std::shared_ptr<const UnitTestDataTable>& data_table );

  //! Destructor
  ~DataUnitTest()
  { /* ... */ }

  //! Get the data table element for the desired column
  const Utility::Variant& getDataTableElement(
                                        const std::string& column_name ) const;
  
  //! Get the concrete data table element for the desired column
  template<typename T>
  T getConcreteDataTableElement( const std::string& column_name ) const;

private:

  // The unit test data table
  std::shared_ptr<const UnitTestDataTable> d_data_table;
};

// Get the concrete data table element for the desired column
template<typename T>
inline T DataUnitTest::getConcreteDataTableElement(
                                         const std::string& column_name ) const
{
  return Utility::variant_cast<T>(this->getDataTableElement( column_name ));
}
  
} // end Utility namespace

#endif // end UTILITY_DATA_UNIT_TEST_HPP

//---------------------------------------------------------------------------//
// end Utility_DataUnitTest.hpp
//---------------------------------------------------------------------------//
