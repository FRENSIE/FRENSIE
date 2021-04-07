//---------------------------------------------------------------------------//
//!
//! \file   tstStaticOutputFormatter.cpp
//! \author Alex Robinson
//! \brief  The static output formatter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_StaticOutputFormatter.hpp"
#include "FRENSIE_tty_format_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the raw output can be returned
BOOST_AUTO_TEST_CASE( getRawOutput )
{
  std::shared_ptr<Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor> > formatter(
    new Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "Testing" ) );

  BOOST_CHECK_EQUAL( formatter->getRawOutput(), "Testing" );

  formatter.reset( new Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( 0.0 ) );
  
  BOOST_CHECK_EQUAL( formatter->getRawOutput(), "0.000000000000000000e+00" );

  formatter.reset( new Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( 1000 ) );

  BOOST_CHECK_EQUAL( formatter->getRawOutput(), "1000" );
}

//---------------------------------------------------------------------------//
// Check that the formatted output can be returned
BOOST_AUTO_TEST_CASE( getFormattedOutput,
                      * boost::unit_test::depends_on( "getRawOutput" ) )
{
  // Check all defaults
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check bold text format only
  {
    Utility::StaticOutputFormatter<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check faded text format only
  {
    Utility::StaticOutputFormatter<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[2;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check italicized text format only
  {
    Utility::StaticOutputFormatter<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[3;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check underlined text format only
  {
    Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[4;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the black text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;30;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the red text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;31;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the green text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;32;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the yellow text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;33;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the blue text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;34;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the magenta text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;35;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the cyan text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;36;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the white text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;37;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the black text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;40mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the red text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;41mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the green text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;42mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the yellow text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;43mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the blue text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;44mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the magenta text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;45mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the cyan text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;46mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check the white text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;47mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }

  // Check combinations
  {
    Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor> formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[4;32;45mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the desired output can be printed
BOOST_AUTO_TEST_CASE( toStream,
                      * boost::unit_test::depends_on( "getFormattedOutput" ) )
{
  std::cout << std::endl;
  std::ostringstream oss_raw, oss;
  
  // Check all defaults
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "\E[0;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( oss.str(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
    
  }

  // Check bold text format only
  {
    Utility::StaticOutputFormatter<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check faded text format only
  {
    Utility::StaticOutputFormatter<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[2;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check italicized text format only
  {
    Utility::StaticOutputFormatter<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[3;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check underlined text format only
  {
    Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[4;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the black text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;30;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the red text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;31;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the green text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;32;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the yellow text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;33;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the blue text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;34;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the magenta text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;35;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the cyan text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;36;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the white text color only
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;37;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the black text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;40mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the red text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;41mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the green text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;42mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the yellow text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;43mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the blue text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;44mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the magenta text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;45mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the cyan text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;46mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the white text background color
  {
    Utility::StaticOutputFormatter<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;29;47mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check combinations
  {
    Utility::StaticOutputFormatter<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor> formatter( "Testing" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[4;32;45mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
    
    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }
}

//---------------------------------------------------------------------------//
// Check the bold formatter
BOOST_AUTO_TEST_CASE( bold_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;
  
  Utility::Bold formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif

    std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the italicized formatter
BOOST_AUTO_TEST_CASE( italicized_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::Italicized formatter( "Testing" );
    
#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                         "\E[3;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the underlined formatter
BOOST_AUTO_TEST_CASE( underlined_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::Underlined formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                         "\E[4;29;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the red formatter
BOOST_AUTO_TEST_CASE( red_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::Red formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[0;31;49mTesting\E[0m" );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif

  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-red formatter
BOOST_AUTO_TEST_CASE( bold_red_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::BoldRed formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the green formatter
BOOST_AUTO_TEST_CASE( green_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::Green formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;32;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-green formatter
BOOST_AUTO_TEST_CASE( bold_green_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::BoldGreen formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;32;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-yellow formatter
BOOST_AUTO_TEST_CASE( yellow_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::Yellow formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;33;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-yellow formatter
BOOST_AUTO_TEST_CASE( bold_yellow_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::BoldYellow formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;33;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-cyan formatter
BOOST_AUTO_TEST_CASE( cyan_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::Cyan formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;36;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-cyan formatter
BOOST_AUTO_TEST_CASE( bold_cyan_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::BoldCyan formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-magenta formatter
BOOST_AUTO_TEST_CASE( magenta_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::Magenta formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;35;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-magenta formatter
BOOST_AUTO_TEST_CASE( bold_magenta_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::BoldMagenta formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;35;49mTesting\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif
  
  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// Check the bold-white formatter
BOOST_AUTO_TEST_CASE( bold_white_typedef,
                      * boost::unit_test::depends_on( "toStream" ) )
{
  std::cout << std::endl;

  Utility::BoldWhite formatter( "Testing" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;37;49mTesting\E[0m" );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
#endif

  std::cout << formatter << std::endl;
}

//---------------------------------------------------------------------------//
// end tstStaticOutputFormatter.cpp
//---------------------------------------------------------------------------//
