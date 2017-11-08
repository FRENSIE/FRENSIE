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
  ~Row();

  //! Get the row name
  const std::string& getName() const;
  
  //! Add an element to the end of the row
  void addElement( const Utility::Variant& value );

  //! Get the row size
  size_t getSize() const;

  //! Set the default output format for the row
  void setDefaultOutputFormat( const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Set the output format for a specific element
  void setOutputFormat( const size_t index,
                        const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Set the row name output format
  void setNameOutputFormat( const std::shared_ptr<const OutputFormatterFactory>& format );

  //! Set the row name output padding
  void setNameOutputPadding( const int padding );

  //! Get the row name output padding
  int getNameOutputPadding() const;

  //! Get a row element (stl-like interface)
  Utility::Variant& operator[]( const size_t index );

  //! Get a row element (stl-like interface)
  const Utility::Variant& operator[]( const size_t index ) const;

  //! Print the row
  void print( std::ostream& os,
              const int row_name_column_width,
              const std::vector<int>& column_widths ) const;

private:

  // The row name
  std::string d_row_name;

  // The row data
  std::vector<Utility::Variant> d_row_elements;

  // The default row output format
  std::shared_ptr<const OutputFormatterFactory> d_default_output_format;

  // The element output formats
  std::vector<std::shared_ptr<const OutputFormatterFactory> > d_row_element_output_formats;

  // The row name output format
  std::shared_ptr<const OutputFormatterFactory> d_row_name_output_format;

  // The row name output padding
  int d_row_name_output_padding;
};

// Constructor
UnitTestDataTable::Row::Row( const std::string& name )
  : d_row_name( name ),
    d_row_elements(),
    d_default_output_format(),
    d_row_element_output_formats(),
    d_row_name_output_format(),
    d_row_name_output_padding( 0 )
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

  d_row_element_output_formats.push_back( std::shared_ptr<const OutputFormatterFactory>() );
}

// Get the row size
size_t UnitTestDataTable::Row::getSize() const
{
  return d_row_elements.size();
}

// Set the default output format for the row
void UnitTestDataTable::Row::setDefaultOutputFormat( const std::shared_ptr<const OutputFormatterFactory>& format )
{
  d_default_output_format = format;
}

// Set the output format for a specific element
void UnitTestDataTable::Row::setOutputFormat( const size_t index,
                                              const std::shared_ptr<const OutputFormatterFactory>& format )
{
  TEST_FOR_EXCEPTION( index >= this->getSize(),
                      Utility::BadUnitTestDataTable,
                      "Data table row " << this->getName() << " does not have "
                      "an element at index " << index << "!" );
  
  d_row_element_output_formats[index] = format;
}

// Set the row name output format
void UnitTestDataTable::Row::setNameOutputFormat( const std::shared_ptr<const OutputFormatterFactory>& format )
{
  d_row_name_output_format = format;
}

// Set the row name output padding
void UnitTestDataTable::Row::setNameOutputPadding( const int padding )
{
  if( padding >= 0 )
    d_row_name_output_padding = padding;
}

// Get the row name output padding
int UnitTestDataTable::Row::getNameOutputPadding() const
{
  return d_row_name_output_padding;
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

namespace Details{

// Calculate the cell back padding
inline int calculateCellBackPadding( const int padding,
                                     const std::string& cell_data,
                                     const int column_width )
{
  int back_padding = column_width - padding - cell_data.size();

  if( back_padding <= 0 )
    return 1;
  else
    return back_padding;
}

} // end Details namespace

// Print the row
void UnitTestDataTable::Row::print( std::ostream& os,
                                    const int row_name_column_width,
                                    const std::vector<int>& column_widths ) const
{
  // Print the row name
  os << std::string( d_row_name_output_padding, ' ' );

  if( d_row_name_output_format )
    os << *(d_row_name_output_format->createOutputFormatter(d_row_name));
  else if( d_default_output_format )
    os << *(d_default_output_format->createOutputFormatter(d_row_name));
  else
    os << d_row_name;

  // Print the row name column back padding
  int back_padding_size =
    Details::calculateCellBackPadding( d_row_name_output_padding,
                                       d_row_name,
                                       row_name_column_width );
  
  os << std::string( back_padding_size, ' ' );
  
  // Print the row elements
  for( size_t i = 0; i < d_row_elements.size(); ++i )
  {
    const std::string element_string = this->operator[](i).toString();
    
    if( d_row_element_output_formats[i] )
      os << *(d_row_element_output_formats[i]->createOutputFormatter(element_string));
    else if( d_default_output_format )
      os << *(d_default_output_format->createOutputFormatter(element_string));
    else
      os << element_string;

    back_padding_size = Details::calculateCellBackPadding( 0,
                                                           element_string,
                                                           column_widths[i] );

    os << std::string( back_padding_size, ' ' );
  }

  os << "\n";
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

  // The ostream operator is a friend
  friend ColumnInitializer& operator<<( ColumnInitializer&, const std::string& );

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
    d_name_format(),
    d_column_initializer( new ColumnInitializer( this ) ),
    d_column_name_index_map(),
    d_default_column_name_format(),
    d_column_name_format_map(),
    d_row_order(),
    d_row_name_map()
{ /* ... */ }

// Destructor
UnitTestDataTable::~UnitTestDataTable()
{ /* ... */ }

// Get the data table name
const std::string& UnitTestDataTable::getName() const
{
  return d_name;
}

// Set the table name output format
void UnitTestDataTable::setTableNameOutputFormat(
                  const std::shared_ptr<const OutputFormatterFactory>& format )
{
  d_name_format = format;
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
UnitTestDataTable::ColumnInitializer& UnitTestDataTable::columns()
{
  return *d_column_initializer;
}

// Check if a column exists
bool UnitTestDataTable::doesColumnExist( const std::string& name ) const
{
  return d_column_name_index_map.find( name ) != d_column_name_index_map.end();
}

// Get the column index corresponding to the name
size_t UnitTestDataTable::getColumnIndex( const std::string& name ) const
{
  TEST_FOR_EXCEPTION( !this->doesColumnExist( name ),
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

// Set the default column name output format
void UnitTestDataTable::setDefaultColumnNameOutputFormat(
                  const std::shared_ptr<const OutputFormatterFactory>& format )
{
  d_default_column_name_format = format;
}

// Set the column name output format
void UnitTestDataTable::setColumnNameOutputFormat(
                  const std::string& column_name,
                  const std::shared_ptr<const OutputFormatterFactory>& format )
{
  if( this->doesColumnExist( column_name ) )
    d_column_name_format_map[column_name] = format;
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
const std::vector<std::string>& UnitTestDataTable::getRowNames() const
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

  return *(d_row_name_map.find(row_name)->second);
}

// Set the row output format
void UnitTestDataTable::setRowOutputFormat(
                  const std::string& row_name,
                  const std::shared_ptr<const OutputFormatterFactory>& format )
{
  this->getRow( row_name ).setDefaultOutputFormat( format );
}

// Set the row name output format
void UnitTestDataTable::setRowNameOutputFormat(
                  const std::string& row_name,
                  const std::shared_ptr<const OutputFormatterFactory>& format )
{
  this->getRow( row_name ).setNameOutputFormat( format );
}

// Set the table output row padding
void UnitTestDataTable::setRowOutputPadding( const std::string& row_name,
                                             const int padding_size )
{
  this->getRow( row_name ).setNameOutputPadding( padding_size );
}

// Get a table element
const Utility::Variant& UnitTestDataTable::getElement(
                                         const std::string& row_name,
                                         const std::string& column_name ) const
{
  return this->getRow( row_name )[this->getColumnIndex( column_name )];
}

// Set an element output format
void UnitTestDataTable::setElementOutputFormat(
                  const std::string& row_name,
                  const std::string& column_name,
                  const std::shared_ptr<const OutputFormatterFactory>& format )
{
  this->getRow( row_name ).setOutputFormat(
                                   this->getColumnIndex(column_name), format );
}

// Place the table in an output stream
void UnitTestDataTable::toStream( std::ostream& os ) const
{
  // Print the table name
  if( d_name_format )
    os << *(d_name_format->createOutputFormatter( d_name ));
  else
    os << d_name;

  os << "\n";
  
  // Calculate the column output widths
  int row_name_column_width;
  std::map<std::string,int> column_name_widths_map;

  this->calculateColumnOutputWidths( row_name_column_width,
                                     column_name_widths_map );

  // Organize the column names and widths
  std::vector<std::string> column_names( d_column_name_index_map.size() );
  std::vector<int> column_widths( d_column_name_index_map.size() );

  {
    ColumnNameIndexMap::const_iterator column_name_it, column_name_end;
    column_name_it = d_column_name_index_map.begin();
    column_name_end = d_column_name_index_map.end();
    
    while( column_name_it != column_name_end )
    {
      column_names[column_name_it->second] = column_name_it->first;
      column_widths[column_name_it->second] =
        column_name_widths_map[column_name_it->first];
      
      ++column_name_it;
    }
  }

  // Leave the row name column blank
  os << std::string( row_name_column_width, ' ' );

  // Print the column names
  for( size_t i = 0; i < column_names.size(); ++i )
  {
    if( d_column_name_format_map.find( column_names[i] ) !=
        d_column_name_format_map.end() )
    {
      const std::shared_ptr<const OutputFormatterFactory>& format =
        d_column_name_format_map.find( column_names[i] )->second;
    
    if( format )
        os << *(format->createOutputFormatter( column_names[i] ));
      else if( d_default_column_name_format )
        os << *(d_default_column_name_format->createOutputFormatter( column_names[i] ));
      else
        os << column_names[i];
    }
    else if( d_default_column_name_format )
      os << *(d_default_column_name_format->createOutputFormatter( column_names[i] ));
    else
      os << column_names[i];

    // Add the cell back padding
    int back_padding = Details::calculateCellBackPadding(
                                        0, column_names[i], column_widths[i] );
    
    os << std::string( back_padding, ' ' );
  }

  os << "\n";

  // Print each row
  for( size_t i = 0; i < d_row_order.size(); ++i )
  {
    d_row_name_map.find(d_row_order[i])->second->print( os, row_name_column_width, column_widths );
  }
}

// Calculate the column output widths
void UnitTestDataTable::calculateColumnOutputWidths(
                               int& row_name_column_width,
                               std::map<std::string,int>& column_widths ) const
{
  // Determine the width of the row name column
  row_name_column_width = 0;
  
  RowNameMap::const_iterator row_it, row_end;
  row_it = d_row_name_map.begin();
  row_end = d_row_name_map.end();

  while( row_it != row_end )
  {
    int row_name_length = row_it->first.size() +
      row_it->second->getNameOutputPadding() + 2;
    
    if( row_name_length > row_name_column_width )
      row_name_column_width = row_name_length;

    ++row_it;
  }

  // Determine the width of each column
  column_widths.clear();

  ColumnNameIndexMap::const_iterator column_it, column_end;
  column_it = d_column_name_index_map.begin();
  column_end = d_column_name_index_map.end();

  while( column_it != column_end )
  {
    int& column_width = column_widths[column_it->first];
    column_width = column_it->first.size();

    row_it = d_row_name_map.begin();
    row_end = d_row_name_map.end();

    while( row_it != row_end )
    {
      int element_width =
        (*row_it->second)[column_it->second].toString().size() + 1;

      if( element_width > column_width )
        column_width = element_width;

      ++row_it;
    }

    ++column_it;
  }
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UnitTestDataTable.cpp
//---------------------------------------------------------------------------//
