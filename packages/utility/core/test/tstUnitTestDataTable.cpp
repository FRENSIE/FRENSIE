//---------------------------------------------------------------------------//
//!
//! \file   tstUnitTestDataTable.cpp
//! \author Alex Robinson
//! \brief  unit test data table tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_UnitTestDataTable.hpp"
#include "Utility_StaticOutputFormatterFactory.hpp"
#include "Utility_DynamicOutputFormatterFactory.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an empty table can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  Utility::UnitTestDataTable table( "test table" );

  BOOST_CHECK_EQUAL( table.getName(), "test table" );
  BOOST_CHECK_EQUAL( table.getNumberOfColumns(), 0 );
  BOOST_CHECK_EQUAL( table.getNumberOfRows(), 0 );
}

//---------------------------------------------------------------------------//
// Check that columns can be added to the data table individually
BOOST_AUTO_TEST_CASE( addColumn )
{
  Utility::UnitTestDataTable table( "test table" );
  table.addColumn( "Column 0" );
  
  BOOST_CHECK_EQUAL( table.getNumberOfColumns(), 1 );
  BOOST_CHECK( table.doesColumnExist( "Column 0" ) );
  BOOST_CHECK_EQUAL( table.getColumnIndex( "Column 0" ), 0 );

  table.addColumn( "Column 1" );

  BOOST_CHECK_EQUAL( table.getNumberOfColumns(), 2 );
  BOOST_CHECK( table.doesColumnExist( "Column 1" ) );
  BOOST_CHECK_EQUAL( table.getColumnIndex( "Column 1" ), 1 );

  BOOST_CHECK( !table.doesColumnExist( "Column 2" ) );
}

//---------------------------------------------------------------------------//
// Check that a series of columns can be added at the same time
BOOST_AUTO_TEST_CASE( columns )
{
  Utility::UnitTestDataTable table( "test table" );

  table.columns() << "Column 0" << "Column 1" << "Column 2";

  BOOST_CHECK_EQUAL( table.getNumberOfColumns(), 3 );
  
  BOOST_CHECK( table.doesColumnExist( "Column 0" ) );
  BOOST_CHECK( table.doesColumnExist( "Column 1" ) );
  BOOST_CHECK( table.doesColumnExist( "Column 2" ) );

  BOOST_CHECK_EQUAL( table.getColumnIndex( "Column 0" ), 0 );
  BOOST_CHECK_EQUAL( table.getColumnIndex( "Column 1" ), 1 );
  BOOST_CHECK_EQUAL( table.getColumnIndex( "Column 2" ), 2 );
}

//---------------------------------------------------------------------------//
// Check that rows can be added to the data table
BOOST_AUTO_TEST_CASE( addRow )
{
  Utility::UnitTestDataTable table( "test table" );

  table.columns() << "Input" << "Expected Output" << "Extra Data";

  table.addRow( "float" ) << 0.0f << 1.0f << 0.1f;
  table.addRow( "double" ) << 0.0 << 1.0 << 0.1;
  table.addRow( "int" ) << 0 << 1 << -1;
  table.addRow( "unsigned" ) << 0u << 1u << 10u;
  table.addRow( "string" ) << "input" << "output" << "";

  BOOST_CHECK_EQUAL( table.getNumberOfRows(), 5 );
  BOOST_CHECK( table.doesRowExist( "float" ) );
  BOOST_CHECK( table.doesRowExist( "double" ) );
  BOOST_CHECK( table.doesRowExist( "int" ) );
  BOOST_CHECK( table.doesRowExist( "unsigned" ) );
  BOOST_CHECK( table.doesRowExist( "string" ) );

  BOOST_CHECK_EQUAL( table.getRowNames().size(), 5 );
  BOOST_CHECK_EQUAL( table.getRowNames()[0], "float" );
  BOOST_CHECK_EQUAL( table.getRowNames()[1], "double" );
  BOOST_CHECK_EQUAL( table.getRowNames()[2], "int" );
  BOOST_CHECK_EQUAL( table.getRowNames()[3], "unsigned" );
  BOOST_CHECK_EQUAL( table.getRowNames()[4], "string" );

  BOOST_CHECK( &table.getRow( "float" ) != NULL );
  BOOST_CHECK( &table.getRow( "double" ) != NULL );
  BOOST_CHECK( &table.getRow( "int" ) != NULL );
  BOOST_CHECK( &table.getRow( "unsigned" ) != NULL );
  BOOST_CHECK( &table.getRow( "string" ) != NULL );
}

//---------------------------------------------------------------------------//
// Check that table elements can be accessed
BOOST_AUTO_TEST_CASE( getElement )
{
  Utility::UnitTestDataTable table( "test table" );

  table.columns() << "Input" << "Expected Output" << "Extra Data";

  table.addRow( "float" ) << 0.0f << 1.0f << 0.1f;
  table.addRow( "double" ) << 0.0 << 1.0 << 0.1;
  table.addRow( "int" ) << 0 << 1 << -1;
  table.addRow( "unsigned" ) << 0u << 1u << 10u;
  table.addRow( "string" ) << "input" << "output" << "";

  BOOST_CHECK_EQUAL( table.getElement( "float", "Input" ).toFloat(), 0.0f );
  BOOST_CHECK_EQUAL( table.getElement( "float", "Expected Output" ).toFloat(), 1.0f );
  BOOST_CHECK_EQUAL( table.getElement( "float", "Extra Data" ).toFloat(), 0.1f );

  BOOST_CHECK_EQUAL( table.getElement( "double", "Input" ).toDouble(), 0.0 );
  BOOST_CHECK_EQUAL( table.getElement( "double", "Expected Output" ).toDouble(), 1.0 );
  BOOST_CHECK_EQUAL( table.getElement( "double", "Extra Data" ).toDouble(), 0.1 );

  BOOST_CHECK_EQUAL( table.getElement( "int", "Input" ).toInt(), 0 );
  BOOST_CHECK_EQUAL( table.getElement( "int", "Expected Output" ).toInt(), 1 );
  BOOST_CHECK_EQUAL( table.getElement( "int", "Extra Data" ).toInt(), -1 );

  BOOST_CHECK_EQUAL( table.getElement( "unsigned", "Input" ).toInt(), 0u );
  BOOST_CHECK_EQUAL( table.getElement( "unsigned", "Expected Output" ).toInt(), 1u );
  BOOST_CHECK_EQUAL( table.getElement( "unsigned", "Extra Data" ).toInt(), 10u );

  BOOST_CHECK_EQUAL( table.getElement( "string", "Input" ).toString(), "input" );
  BOOST_CHECK_EQUAL( table.getElement( "string", "Expected Output" ).toString(), "output" );
  BOOST_CHECK_EQUAL( table.getElement( "string", "Extra Data" ).toString(), "" );
}

//---------------------------------------------------------------------------//
// Check that concrete table elements can be accessed
BOOST_AUTO_TEST_CASE( getConcreteElement )
{
  Utility::UnitTestDataTable table( "test table" );

  table.columns() << "Input" << "Expected Output" << "Extra Data";

  table.addRow( "float" ) << 0.0f << 1.0f << 0.1f;
  table.addRow( "double" ) << 0.0 << 1.0 << 0.1;
  table.addRow( "int" ) << 0 << 1 << -1;
  table.addRow( "unsigned" ) << 0u << 1u << 10u;
  table.addRow( "string" ) << "input" << "output" << "";

  BOOST_CHECK_EQUAL( table.getConcreteElement<float>( "float", "Input" ), 0.0f );
  BOOST_CHECK_EQUAL( table.getConcreteElement<float>( "float", "Expected Output" ), 1.0f );
  BOOST_CHECK_EQUAL( table.getConcreteElement<float>( "float", "Extra Data" ), 0.1f );

  BOOST_CHECK_EQUAL( table.getConcreteElement<double>( "double", "Input" ), 0.0 );
  BOOST_CHECK_EQUAL( table.getConcreteElement<double>( "double", "Expected Output" ), 1.0 );
  BOOST_CHECK_EQUAL( table.getConcreteElement<double>( "double", "Extra Data" ), 0.1 );

  BOOST_CHECK_EQUAL( table.getConcreteElement<int>( "int", "Input" ), 0 );
  BOOST_CHECK_EQUAL( table.getConcreteElement<int>( "int", "Expected Output" ), 1 );
  BOOST_CHECK_EQUAL( table.getConcreteElement<int>( "int", "Extra Data" ), -1 );

  BOOST_CHECK_EQUAL( table.getConcreteElement<unsigned>( "unsigned", "Input" ), 0u );
  BOOST_CHECK_EQUAL( table.getConcreteElement<unsigned>( "unsigned", "Expected Output" ), 1u );
  BOOST_CHECK_EQUAL( table.getConcreteElement<unsigned>( "unsigned", "Extra Data" ), 10u );

  BOOST_CHECK_EQUAL( table.getConcreteElement<std::string>( "string", "Input" ), "input" );
  BOOST_CHECK_EQUAL( table.getConcreteElement<std::string>( "string", "Expected Output" ), "output" );
  BOOST_CHECK_EQUAL( table.getConcreteElement<std::string>( "string", "Extra Data" ), "" );
}

//---------------------------------------------------------------------------//
// Check that a data table can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream_operator_basic )
{
  Utility::UnitTestDataTable table( "test table" );

  table.columns() << "Input" << "Expected Output" << "Extra Data";

  table.addRow( "float" ) << 0.0f << 1.0f << 0.1f;
  table.addRow( "double" ) << 0.0 << 1.0 << 0.1;
  table.addRow( "int" ) << 0 << 1 << -1;
  table.addRow( "unsigned" ) << 0u << 1u << 10u;
  table.addRow( "string" ) << "input" << "output" << "";

  std::ostringstream oss;
  
  BOOST_CHECK_NO_THROW( oss << table );
  
  std::cout << std::endl << table << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a data table can be placed in a stream
BOOST_AUTO_TEST_CASE( ostream_operator_advanced )
{
  Utility::UnitTestDataTable table( "test table" );

  table.columns() << "Input" << "Expected Output" << "Extra Data";

  table.addRow( "float" ) << 0.0f << 1.0f << 0.1f;
  table.addRow( "double" ) << 0.0 << 1.0 << 0.1;
  table.addRow( "int" ) << 0 << 1 << -1;
  table.addRow( "unsigned" ) << 0u << 1u << 10u;
  table.addRow( "string" ) << "input" << "output" << "";

  // Set the title format
  std::shared_ptr<Utility::OutputFormatterFactory> title_format(
        new Utility::StaticOutputFormatterFactory<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

  table.setTableNameOutputFormat( title_format );

  // Set the column name formats
  std::shared_ptr<Utility::OutputFormatterFactory> default_column_name_format(
                new Utility::StaticOutputFormatterFactory<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

  table.setDefaultColumnNameOutputFormat( default_column_name_format );

  std::shared_ptr<Utility::OutputFormatterFactory> extra_data_column_name_format(
                new Utility::StaticOutputFormatterFactory<Utility::UnderlinedTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor> );

  table.setColumnNameOutputFormat( "Extra Data", extra_data_column_name_format );

  // Set the row name formats
  std::shared_ptr<Utility::OutputFormatterFactory> row_name_format(
                new Utility::StaticOutputFormatterFactory<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

  table.setRowNameOutputFormat( "float", row_name_format );
  table.setRowNameOutputFormat( "double", row_name_format );
  table.setRowNameOutputFormat( "int", row_name_format );
  table.setRowNameOutputFormat( "unsigned", row_name_format );

  // Set the default row output formats
  std::shared_ptr<Utility::OutputFormatterFactory> default_even_row_format(
                new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor> );

  std::shared_ptr<Utility::OutputFormatterFactory> default_odd_row_format(
                new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor> );

  table.setRowOutputFormat( "float", default_even_row_format );
  table.setRowOutputPadding( "float", 2 );
  
  table.setRowOutputFormat( "double", default_odd_row_format );
  table.setRowOutputPadding( "double", 2 );
  
  table.setRowOutputFormat( "int", default_even_row_format );
  table.setRowOutputPadding( "int", 2 );
  
  table.setRowOutputFormat( "unsigned", default_odd_row_format );
  table.setRowOutputPadding( "unsigned", 2 );
  
  table.setRowOutputFormat( "string", default_even_row_format );
  table.setRowOutputPadding( "string", 2 );

  // Set the element specific output formats
  std::shared_ptr<Utility::OutputFormatterFactory> element_format(
                new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor> );

  table.setElementOutputFormat( "string", "Expected Output", element_format );

  std::ostringstream oss;
  
  BOOST_CHECK_NO_THROW( oss << table );

  std::cout << std::endl << table << std::endl;
}

//---------------------------------------------------------------------------//
// end tstUnitTestDataTable.cpp
//---------------------------------------------------------------------------//
