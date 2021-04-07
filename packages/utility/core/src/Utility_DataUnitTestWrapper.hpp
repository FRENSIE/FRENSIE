//---------------------------------------------------------------------------//
//!
//! \file   Utility_DataUnitTestWrapper.hpp
//! \author Alex Robinson
//! \brief  The data unit test wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DATA_UNIT_TEST_WRAPPER_HPP
#define UTILITY_DATA_UNIT_TEST_WRAPPER_HPP

// Std Lib Includes
#include <memory>
#include <vector>

// FRENSIE Includes
#include "Utility_UnitTestDataTable.hpp"
#include "Utility_UnitTest.hpp"

namespace Utility{

/*! The data unit test wrapper class
 * \ingroup unit_test_framework
 */
template<typename UnitTestType>
class DataUnitTestWrapper
{

public:

  //! Constructor
  template<typename DataTableCreator>
  DataUnitTestWrapper( const std::string& table_name,
                       const DataTableCreator& data_table_creator );

  //! Destructor
  ~DataUnitTestWrapper()
  { /* ... */ }

  //! Return the number of instantiated tests
  size_t getNumberOfTests() const;

private:

  // The data table
  std::shared_ptr<UnitTestDataTable> d_data_table;

  // The instantiated tests
  std::vector<std::shared_ptr<Utility::UnitTest> > d_instantiated_tests;
};

// Constructor
template<typename UnitTestType>
template<typename DataTableCreator>
DataUnitTestWrapper<UnitTestType>::DataUnitTestWrapper(
                                   const std::string& table_name,
                                   const DataTableCreator& data_table_creator )
  : d_data_table( new UnitTestDataTable( table_name ) ),
    d_instantiated_tests()
{
  // Create the data table
  data_table_creator( *d_data_table );

  // Get the table row names (these will be the unit test data names)
  const std::vector<std::string>& row_names = d_data_table->getRowNames();

  // Create a unit test for each row
  d_instantiated_tests.resize( row_names.size() );

  for( size_t i = 0; i < row_names.size(); ++i )
  {
    d_instantiated_tests[i].reset(
                              new UnitTestType( row_names[i], d_data_table ) );
  }
}

// Return the number of instantiated tests
template<typename UnitTestType>
inline size_t DataUnitTestWrapper<UnitTestType>::getNumberOfTests() const
{
  return d_instantiated_tests.size();
}

} // end Utility namespace

#endif // end UTILITY_DATA_UNIT_TEST_WRAPPER_HPP

//---------------------------------------------------------------------------//
// end Utility_DataUnitTestWrapper.hpp
//---------------------------------------------------------------------------//
