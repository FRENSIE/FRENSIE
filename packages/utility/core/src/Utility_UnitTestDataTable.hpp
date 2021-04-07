//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestDataTable.hpp
//! \author Alex Robinson
//! \brief  The unit test data table class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_DATA_TABLE_HPP
#define UTILITY_UNIT_TEST_DATA_TABLE_HPP

// Std Lib Includes
#include <stdexcept>
#include <memory>

// FRENSIE Includes
#include "Utility_OStreamableObject.hpp"
#include "Utility_Variant.hpp"
#include "Utility_OutputFormatterFactory.hpp"

namespace Utility{

//! The unit test data table
class UnitTestDataTable : public OStreamableObject
{
  
public:

  //! The data table row
  class Row;

  //! The column initializer
  class ColumnInitializer;
  
  //! Constructor
  UnitTestDataTable( const std::string& name );

  //! Destructor
  ~UnitTestDataTable();

  //! Get the data table name
  const std::string& getName() const;

  //! Set the table name output format
  void setTableNameOutputFormat( const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Add a column
  void addColumn( const std::string& column_name );

  //! Create the columns
  ColumnInitializer& columns();

  //! Check if a column exists
  bool doesColumnExist( const std::string& column_name ) const;

  //! Get the column index
  size_t getColumnIndex( const std::string& column_name ) const;

  //! Get the number of columns
  size_t getNumberOfColumns() const;

  //! Set the default column name output format
  void setDefaultColumnNameOutputFormat(
                 const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Set the column name output format
  void setColumnNameOutputFormat( const std::string& column_name,
                                  const std::shared_ptr<const OutputFormatterFactory>& format );
  
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

  //! Set the row output format
  void setRowOutputFormat( const std::string& row_name,
                           const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Set the row name output format
  void setRowNameOutputFormat( const std::string& row_name,
                               const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Set the table output row padding
  void setRowOutputPadding( const std::string& row_name,
                            const int padding_size );

  //! Get a table element
  const Utility::Variant& getElement( const std::string& row_name,
                                      const std::string& column_name ) const;

  //! Get a concrete table element
  template<typename T>
  T getConcreteElement( const std::string& row_name,
                        const std::string& column_name ) const;

  //! Set an element output format
  void setElementOutputFormat( const std::string& row_name,
                               const std::string& column_name,
                               const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Place the table in an output stream
  void toStream( std::ostream& os ) const override;

private:

  // Calculate the column output widths
  void calculateColumnOutputWidths( int& row_name_column_width,
                                    std::map<std::string,int>& column_widths ) const;

  // Calculate the cell back padding
  int calculateCellBackPadding( const int padding,
                                const std::string& cell_data,
                                const int column_width );

  // The data table name
  std::string d_name;

  // The data table name format
  std::shared_ptr<const OutputFormatterFactory> d_name_format;

  // The column initializer
  std::unique_ptr<ColumnInitializer> d_column_initializer;

  // The column name index map
  typedef std::map<std::string,size_t> ColumnNameIndexMap;
  ColumnNameIndexMap d_column_name_index_map;

  // The default column name output format
  std::shared_ptr<const OutputFormatterFactory> d_default_column_name_format;

  // The column name output format map
  typedef std::map<std::string,std::shared_ptr<const OutputFormatterFactory> > ColumnNameFormatMap;
  ColumnNameFormatMap d_column_name_format_map;

  // The row order
  std::vector<std::string> d_row_order;

  // The row name map
  typedef std::map<std::string,std::shared_ptr<Row> > RowNameMap;
  RowNameMap d_row_name_map;
};

/*! \brief Exception thrown by Utility::UnitTestDataTable when the table is
 * ill-formed.
 */
class BadUnitTestDataTable : public std::logic_error
{
public:
  BadUnitTestDataTable( const std::string& msg )
    : std::logic_error( msg )
  { /* ... */ }

  ~BadUnitTestDataTable() throw()
  { /* ... */ }
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
