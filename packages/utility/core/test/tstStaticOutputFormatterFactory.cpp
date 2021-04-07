//---------------------------------------------------------------------------//
//!
//! \file   tstStaticOutputFormatterFactory.cpp
//! \author Alex Robinson
//! \brief  The static output formatter factory unit tests
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
#include "Utility_StaticOutputFormatterFactory.hpp"

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
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check bold text format only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check faded text format only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check italicized text format only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check underlined text format only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(), test_format.getFormattedOutput() );
  }

  // Check the black text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the red text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the green text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the yellow text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the blue text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the magenta text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the cyan text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the white text color only
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the black text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the red text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the green text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the yellow text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the blue text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the magenta text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );
    
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the cyan text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check the white text background color
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }

  // Check combinations
  {
    factory.reset( new Utility::StaticOutputFormatterFactory<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor> );

    format = factory->createOutputFormatter( "Testing" );

    Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor> test_format( "Testing" );
    
    BOOST_CHECK_EQUAL( format->getFormattedOutput(),
                       test_format.getFormattedOutput() );
  }
}

//---------------------------------------------------------------------------//
// end tstStaticOutputFormatterFactory.cpp
//---------------------------------------------------------------------------//
