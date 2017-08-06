//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestDataTable.hpp
//! \author Alex Robinson
//! \brief  The unit test data table class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_DATA_TABLE_HPP
#define UTILITY_UNIT_TEST_DATA_TABLE_HPP

// FRENSIE Includes
#include "Utility_Variant.hpp"

namespace Utility{

//! The unit test data table
class UnitTestDataTable
{
  
public:

  //! The data table row
  class Row;

  //! The column initializer
  class ColumnInitializer;
  
  //! Constructor
  UnitTestDataTable( const std::string& name );

  //! Destructor
  virtual ~UnitTestDataTable()
  { /* ... */ }

  //! Get the data table name
  const std::string& getName() const;

  //! Add a column
  void addColumn( const std::string& column_name );

  //! Create the columns
  ColumnInitializer columns();  
  //! Create a new row
  Row& addRow( const std::string& row_name );

  //! Check if a row exists
  bool doesRowExist( const std::string& row_name ) const;

  //! Get the number of rows
  size_t getNumberOfRows() const;

  //! Get the row names (in the order they were created)
  const std::vector<std::string>& getRowNames() const;

  //! Get the row
  Row& getRow( const std::string& row_name );

  //! Get the row
  const Row& getRow( const std::string& row_name ) const;

  //! Get a table element
  Utility::Variant& getElement( const std::string& row_name,
                                const std::string& column_name );

  //! Get a table element
  const Utility::Variant& getElement( const std::string& row_name,
                                      const std::string& column_name ) const;

  //! Get a concrete table element
  template<typename T>
  T getConcreteElement( const std::string& row_name,
                        const std::string& column_name ) const;

private:

  // The data table name
  std::string d_name;

  // The column name index map
  typedef std::map<std::string,size_t> ColumnNameIndexMap;
  ColumnNameIndexMap d_column_name_index_map;

  // The row order
  std::vector<std::string> d_row_order;

  // The row name map
  typedef std::map<std::string,std::shared_ptr<Row> > RowNameMap;
  RowNameMap d_row_name_map;
};

// Get a concrete table element
template<typename T>
inline T UnitTestDataTable::getConcreteElement(
                                         const std::string& row_name,
                                         const std::string& column_name ) const
{
  return Utility::variant_cast<T>( this->getElement( row_name, column_name ) );
}

//! The ostream operator for Utility::UnitTestDataTable::Row
UnitTestDataTable::Row& operator<<( UnitTestDataTable::Row& row, 
                                    const Utility::Variant& opaque_value );
  
//! The ostream operator for the Utility::UnitTestDataTable::Row class
template<typename T>
inline UnitTestDataTable::Row& operator<<( UnitTestDataTable::Row& row,
                                           const T& value )
{ return row << Utility::Variant( value ); }

//! The ostream operator for Utility::UnitTestDataTable::ColumnInitializer
UnitTestDataTable::ColumnInitializer& operator<<(
                      UnitTestDataTable::ColumnInitializer& column_initializer,
                      const std::string& column_name );
  
} // end Utility namespace

#endif // end UTILITY_UNIT_TEST_DATA_TABLE_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestDataTable.hpp
//---------------------------------------------------------------------------//
