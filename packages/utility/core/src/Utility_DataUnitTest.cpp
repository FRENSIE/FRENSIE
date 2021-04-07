//---------------------------------------------------------------------------//
//!
//! \file   Utility_DataUnitTest.hpp
//! \author Alex Robinson
//! \brief  The data unit test class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DataUnitTest.hpp"

namespace Utility{

// Constructor
DataUnitTest::DataUnitTest(
                   const std::string& group_name,
                   const std::string& test_name,
                   const std::string& data_table_row_name,
                   const std::shared_ptr<const UnitTestDataTable>& data_table )
  : UnitTest( group_name, test_name, data_table_row_name ),
    d_data_table( data_table )
{ /* ... */ }

// Get the data table element for the desired column
const Utility::Variant& DataUnitTest::getDataTableElement(
                                         const std::string& column_name ) const
{
  return d_data_table->getElement( this->getDataName(), column_name );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DataUnitTest.hpp
//---------------------------------------------------------------------------//
