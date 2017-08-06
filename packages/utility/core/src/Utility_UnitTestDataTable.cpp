//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestDataTable.cpp
//! \author Alex Robinson
//! \brief  The unit test data table class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_UnitTestDataTable.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

//! The unit test data table row
class UnitTestDataTable::Row
{
  
public:
  
  //! Constructor
  Row( const std::string& name );
  
  //! Destructor
  ~Row()
  { /* ... */ }

  //! Get the row name
  const std::string& getName() const;
  
  //! Add an element to the end of the row
  void addElement( const Utility::Variant& value );

    //! Get the row size
  size_t getSize() const;

  //! Get a row element (stl-like interface)
  Utility::Variant& operator[]( const size_t index );

  //! Get a row element (stl-like interface)
  const Utility::Variant& operator[]( const size_t index ) const;

private:

  // The row name
  std::string d_row_name;

  // The row data
  std::vector<Utility::Variant> d_row_elements;
};

// Constructor
UnitTestDataTable::Row::Row( const std::string& name )
  : d_row_name( name ),
    d_row_elements()
{ /* ... */ }
    
  
// Destructor
UnitTestDataTable::Row::~Row()
{ /* ... */ }

// Get the row name
const std::string& UnitTestDataTable::Row::getName() const
{
  return d_row_name;
}
  
// Add an element to the end of the row
void UnitTestDataTable::Row::addElement( const Utility::Variant& value )
{
  d_row_elements.push_back( value );
}

// Get the row size
size_t UnitTestDataTable::Row::getSize() const
{
  return d_row_elements.size();
}

// Get a row element (stl-like interface)
Utility::Variant& UnitTestDataTable::Row::operator[]( const size_t index )
{
  TEST_FOR_EXCEPTION( index >= this->getSize(),
                      Utility::BadUnitTestDataTable,
                      "Data table row " << this->getName() << " does not have "
                      "an element at index " << index << "!" );
  
  return d_row_elements[index];
}

// Get a row element (stl-like interface)
const Utility::Variant& UnitTestDataTable::Row::operator[]( const size_t index ) const
{
  TEST_FOR_EXCEPTION( index >= this->getSize(),
                      Utility::BadUnitTestDataTable,
                      "Data table row " << this->getName() << " does not have "
                      "an element at index " << index << "!" );
  
  return d_row_elements[index];
}

// The ostream operator for Utility::UnitTestDataTable::Row
UnitTestDataTable::Row& operator<<( UnitTestDataTable::Row& row, 
                                    const Utility::Variant& opaque_value )
{
  row.addElement( opaque_value );
  return row;
}

//! The column initializer
class UnitTestDataTable::ColumnInitializer
{
  //! Add a column
  void addColumn( const std::string& name )
  { d_data_table->addColumn( name ); }
    
protected:
    
  //! Constructor
  ColumnInitializer( UnitTestDataTable* data_table )
    : d_data_table( data_table )
  { /* ... */ }

private:

  // The UnitTestDataTable is a friend
  friend class UnitTestDataTable;

  // The data table
  UnitTestDataTable* d_data_table;
};

// The ostream operator for Utility::UnitTestDataTable::ColumnInitializer
UnitTestDataTable::ColumnInitializer& operator<<(
                      UnitTestDataTable::ColumnInitializer& column_initializer,
                      const std::string& column_name )
{
  column_initializer.addColumn( column_name );
  return column_initializer;
}

// Constructor
UnitTestDataTable::UnitTestDataTable( const std::string& name )
  : d_name( name ),
    d_column_name_index_map(),
    d_row_order(),
    d_row_name_map()
{ /* ... */ }

// Get the data table name
const std::string& UnitTestDataTable::getName() const
{
  return d_name;
}

// Add a column
void UnitTestDataTable::addColumn( const std::string& column_name )
{
  TEST_FOR_EXCEPTION( this->doesColumnExist( column_name ),
                      Utility::BadUnitTestDataTable,
                      "Cannot add column " << column_name << " to test data "
                      "table because a column with that name already "
                      "exists!" );

  const size_t column_index = d_column_name_index_map.size();
  
  d_column_name_index_map[column_name] = column_index;
}

// Create the columns
UnitTestDataTable::ColumnInitializer UnitTestDataTable::columns()
{
  return UnitTestDataTable::ColumnInitializer( this );
}

// Check if a column exists
bool UnitTestDataTable::doesColumnExist( const std::string& name ) const
{
  return d_column_name_index_map.find( name ) != d_column_name_index_map.end();
}

// Get the column index corresponding to the name
size_t UnitTestDataTable::getColumnIndex( const std::string& name ) const
{
  TEST_FOR_EXCEPTION( !this->doesColumnExist( column_name ),
                      Utility::BadUnitTestDataTable,
                      "Cannot get the index of column " << name << " because "
                      "it doesn't exist!" );
  
  return d_column_name_index_map.find( name )->second;
}

// Get the number of columns in the data table
size_t UnitTestDataTable::getNumberOfColumns() const
{
  return d_column_name_index_map.size();
}

// Create a new row
UnitTestDataTable::Row&
UnitTestDataTable::addRow( const std::string& row_name )
{
  TEST_FOR_EXCEPTION( this->doesRowExist( row_name ),
                      Utility::BadUnitTestDataTable,
                      "Cannot add row " << row_name << " to test data "
                      "table because a row with that name already "
                      "exists!" );

  d_row_order.push_back( row_name );
  
  std::shared_ptr<UnitTestDataTable::Row>& row = d_row_name_map[row_name];
  row.reset( new UnitTestDataTable::Row( row_name ) );
  
  return *row;
}

// Check if a row exists
bool UnitTestDataTable::doesRowExist( const std::string& row_name ) const
{
  return d_row_name_map.find( row_name ) != d_row_name_map.end();
}

// Get the number of rows
size_t UnitTestDataTable::getNumberOfRows() const
{
  return d_row_name_map.size();
}

// Get the row names (in the order they were created)
std::vector<std::string>& UnitTestDataTable::getRowNames() const
{
  return d_row_order;
}

// Get the row
UnitTestDataTable::Row&
UnitTestDataTable::getRow( const std::string& row_name )
{
  TEST_FOR_EXCEPTION( !this->doesRowExist( row_name ),
                      Utility::BadUnitTestDataTable,
                      "Cannot get row " << row_name << " from the test data "
                      "table because it does not exist!" );

  return *d_row_name_map[row_name];
}
  
// Get the row
const UnitTestDataTable::Row&
UnitTestDataTable::getRow( const std::string& row_name ) const
{
  TEST_FOR_EXCEPTION( !this->doesRowExist( row_name ),
                      Utility::BadUnitTestDataTable,
                      "Cannot get row " << row_name << " from the test data "
                      "table because it does not exist!" );

  return *d_row_name_map[row_name];
}

// Get a table element
Utility::Variant& UnitTestDataTable::getElement(
                                               const std::string& row_name,
                                               const std::string& column_name )
{
  return this->getRow( row_name )[this->getColumnIndex( column_name )];
}

// Get a table element
const Utility::Variant& UnitTestDataTable::getElement(
                                         const std::string& row_name,
                                         const std::string& column_name ) const
{
  return this->getRow( row_name )[this->getColumnIndex( column_name )];
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UnitTestDataTable.cpp
//---------------------------------------------------------------------------//
