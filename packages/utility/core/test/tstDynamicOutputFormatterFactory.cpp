//---------------------------------------------------------------------------//
//!
//! \file   tstDynamicOutputFormatterFactory.cpp
//! \author Alex Robinson
//! \brief  The dynamic output formatter factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_DynamicOutputFormatterFactory.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can create output formatters
BOOST_AUTO_TEST_CASE( createOutputFormatter )
{
  std::unique_ptr<Utility::OutputFormatterFactory> factory;
  std::shared_ptr<const Utility::OutputFormatter> format;

  // Check all defaults
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );

    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );

    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check bold text format only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check faded text format only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check italicized text format only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check underlined text format only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the black text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the red text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the green text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check yellow text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the blue text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the magenta text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the cyan text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the white text color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the black text background color only
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the red text background color
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the green text background color
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the yellow text background color
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the blue text background color
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the magenta text background color
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the cyan text background color
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the white text background color
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check combinations
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "test" );

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check multiple formats
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::BoldTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "This" ) );
    // This should be ignored
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::BoldTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "This" ) );
    
    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "test" );

    test_format.formatKeyword<Utility::BoldTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "This" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check regex
  {
    Utility::DynamicOutputFormatterFactory::FormattingFunctionArray format_functions;
    
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "test" ) );
    format_functions.push_back( std::bind<void>( &Utility::DynamicOutputFormatter::formatKeyword<Utility::BoldTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>,
                                                 std::placeholders::_1,
                                                 "\\w*is\\b" ) );

    factory.reset( new Utility::DynamicOutputFormatterFactory( format_functions ) );
    format = factory->createOutputFormatter( "This is a test." );
    
    Utility::DynamicOutputFormatter test_format( "This is a test." );

    test_format.formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "test" );

    test_format.formatKeyword<Utility::BoldTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "\\w*is\\b" ); 

    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }
}

//---------------------------------------------------------------------------//
// end tstDynamicOutputFormatterFactory.cpp
//---------------------------------------------------------------------------//
