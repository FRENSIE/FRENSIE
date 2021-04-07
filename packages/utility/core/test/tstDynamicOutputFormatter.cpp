//---------------------------------------------------------------------------//
//!
//! \file   tstDynamicOutputFormatter.cpp
//! \author Alex Robinson
//! \brief  The dynamic output formatter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// FRENSIE Includes
#include "Utility_DynamicOutputFormatter.hpp"
#include "FRENSIE_tty_format_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the raw output can be returned
BOOST_AUTO_TEST_CASE( getRawOutput )
{
  Utility::DynamicOutputFormatter formatter( "Testing" );

  BOOST_CHECK_EQUAL( formatter.getRawOutput(), "Testing" );
}

//---------------------------------------------------------------------------//
// Check that the formatted output can be returned
BOOST_AUTO_TEST_CASE( getFormattedOutput,
                      * boost::unit_test::depends_on( "getRawOutput" ) )
{
  Utility::DynamicOutputFormatter formatter( "Testing" );

  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Testing" );
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted
BOOST_AUTO_TEST_CASE( formatKeyword,
                      * boost::unit_test::depends_on( "getFormattedOutput" ) )
{
  // Check all defaults
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check bold text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[1;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check faded text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[2;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check italicized text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[3;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check underlined text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[4;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the black text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;30;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the red text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;31;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the green text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;32;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check yellow text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;33;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the blue text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;34;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the magenta text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;35;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the cyan text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;36;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the white text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;37;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the black text background color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;40mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the red text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;41mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the green text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;42mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the yellow text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;43mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the blue text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;44mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the magenta text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;45mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the cyan text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;46mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check the white text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;29;47mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check combinations
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[4;32;45mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check multiple formats
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "test" );

    formatter.formatKeyword<Utility::BoldTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "This" );

    // Make sure repeats are ignored
    formatter.formatKeyword<Utility::BoldTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>( "This" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mThis\E[0m is a \E[4;32;45mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
  }

  // Check regex
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "test" );

    formatter.formatKeyword<Utility::BoldTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "\\w*is\\b" );

    // Make sure repeats are ignored
    formatter.formatKeyword<Utility::BoldTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>( "This" );

    formatter.formatKeyword<Utility::BoldTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "\\w*is\\b" );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                         "\E[1;31;49mThis\E[0m \E[1;31;49mis\E[0m a \E[4;32;45mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold
BOOST_AUTO_TEST_CASE( boldKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[1;29;49mThis\E[0m \E[1;29;49mis\E[0m a \E[1;29;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be italicized
BOOST_AUTO_TEST_CASE( italicizedKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.italicizedKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[3;29;49mThis\E[0m \E[3;29;49mis\E[0m a \E[3;29;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be underlined
BOOST_AUTO_TEST_CASE( underlinedKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.underlinedKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[4;29;49mThis\E[0m \E[4;29;49mis\E[0m a \E[4;29;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in red
BOOST_AUTO_TEST_CASE( redKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.redKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;31;49mThis\E[0m \E[0;31;49mis\E[0m a \E[0;31;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-red
BOOST_AUTO_TEST_CASE( boldRedKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldRedKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mThis\E[0m \E[1;31;49mis\E[0m a \E[1;31;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in green
BOOST_AUTO_TEST_CASE( greenKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.greenKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;32;49mThis\E[0m \E[0;32;49mis\E[0m a \E[0;32;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-green
BOOST_AUTO_TEST_CASE( boldGreenKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldGreenKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;32;49mThis\E[0m \E[1;32;49mis\E[0m a \E[1;32;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in yellow
BOOST_AUTO_TEST_CASE( yellowKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.yellowKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[0;33;49mThis\E[0m \E[0;33;49mis\E[0m a \E[0;33;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-yellow
BOOST_AUTO_TEST_CASE( boldYellowKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldYellowKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;33;49mThis\E[0m \E[1;33;49mis\E[0m a \E[1;33;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in cyan
BOOST_AUTO_TEST_CASE( cyanKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.cyanKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[0;36;49mThis\E[0m \E[0;36;49mis\E[0m a \E[0;36;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-cyan
BOOST_AUTO_TEST_CASE( boldCyanKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldCyanKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[1;36;49mThis\E[0m \E[1;36;49mis\E[0m a \E[1;36;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in magenta
BOOST_AUTO_TEST_CASE( magentaKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.magentaKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[0;35;49mThis\E[0m \E[0;35;49mis\E[0m a \E[0;35;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-magenta
BOOST_AUTO_TEST_CASE( boldMagentaKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldMagentaKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[1;35;49mThis\E[0m \E[1;35;49mis\E[0m a \E[1;35;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-white
BOOST_AUTO_TEST_CASE( boldWhiteKeyword,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldWhiteKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "\E[1;37;49mThis\E[0m \E[1;37;49mis\E[0m a \E[1;37;49mtest\E[0m." );
#else
  BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                     "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that the standard error message keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardErrorKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that the "Error:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: this is a test!" );

    formatter.formatStandardErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mError: \E[0mthis is a test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Error: this is a test!" );
#endif
  }

  // Check that the "My Error:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "My Error: this is a test!" );

    formatter.formatStandardErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mMy Error: \E[0mthis is a test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "My Error: this is a test!" );
#endif
  }

  // Check that the "error:" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( " error: this is a test!" );

    formatter.formatStandardErrorKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " error: this is a test!" );
  }

  // Check that the "Error" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is an Error test!" );

    formatter.formatStandardErrorKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is an Error test!" );
  }

  // Check that the "error" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is an error test!" );

    formatter.formatStandardErrorKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is an error test!" );
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: this is an error test!" );

    formatter.formatStandardErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mError: \E[0mthis is an error test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Error: this is an error test!" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that extra error keywords can be formatted
BOOST_AUTO_TEST_CASE( formatExtraErrorKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that the "Error:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: this is a test!" );

    formatter.formatExtraErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mError:\E[0m this is a test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Error: this is a test!" );
#endif
  }

  // Check that the "error:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " error: this is a test!" );

    formatter.formatExtraErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49m error:\E[0m this is a test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " error: this is a test!" );
#endif
  }

  // Check that the "Error" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is an Error test!" );

    formatter.formatExtraErrorKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is an Error test!" );
  }

  // Check that the "error" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is an error test!" );

    formatter.formatExtraErrorKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is an error test!" );
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: this is an error test!" );

    formatter.formatExtraErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mError:\E[0m this is an error test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Error: this is an error test!" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard warning message keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardWarningKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that the "Warning:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Warning: this is a test!" );

    formatter.formatStandardWarningKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;35;49mWarning: \E[0mthis is a test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Warning: this is a test!" );
#endif
  }

  // Check that the "Warning" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a Warning test!" );

    formatter.formatStandardWarningKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a Warning test!" );
  }

  // Check that the "warning" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a warning test!" );

    formatter.formatStandardWarningKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a warning test!" );
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Warning: This is a warning test!" );

    formatter.formatStandardWarningKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;35;49mWarning: \E[0mThis is a warning test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Warning: This is a warning test!" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard note keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardNoteKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that the "Note:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Note: this is a test!" );

    formatter.formatStandardNoteKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49mNote:\E[0m this is a test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Note: this is a test!" );
#endif
  }

  // Check that the "note:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " note: this is a test!" );

    formatter.formatStandardNoteKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m note:\E[0m this is a test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " note: this is a test!" );
#endif
  }

  // Check that the "Note" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a Note test!" );

    formatter.formatStandardNoteKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a Note test!" );
  }

  // Check that the "note" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a note test!" );

    formatter.formatStandardNoteKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a note test!" );
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Note: This is a note test!" );

    formatter.formatStandardNoteKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49mNote:\E[0m This is a note test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Note: This is a note test!" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the extra message keywords can be formatted
BOOST_AUTO_TEST_CASE( formatExtraMessageKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that the "Msg:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\nMsg: this is a message test!" );

    formatter.formatExtraMessageKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m\nMsg:\E[0m this is a message test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\nMsg: this is a message test!" );
#endif
  }

  // Check that the "My Msg:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\nMy Msg: this is a message test!" );

    formatter.formatExtraMessageKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m\nMy Msg:\E[0m this is a message test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\nMy Msg: this is a message test!" );
#endif
  }

  // Check that the "msg:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( " msg: this is a message test!" );

    formatter.formatExtraMessageKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " msg: this is a message test!" );
  }

  // Check that "Msg" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Msg test!" );

    formatter.formatExtraMessageKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "Msg test!" );
  }

  // Check that "msg" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "msg test!" );

    formatter.formatExtraMessageKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "msg test!" );
  }
}

//---------------------------------------------------------------------------//
// Check that the standard location keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardLocationKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that " Location:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " Location: my location message!" );

    formatter.formatStandardLocationKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m Location:\E[0m my location message!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " Location: my location message!" );
#endif
  }

  // Check that "  Location:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "  Location: my location message!" );

    formatter.formatStandardLocationKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m  Location:\E[0m my location message!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "  Location: my location message!" );
#endif
  }

  // Check that "Location:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Location: my location message!" );

    formatter.formatStandardLocationKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Location: my location message!" );
  }

  // Check that "location:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "location: my location message!" );

    formatter.formatStandardLocationKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "location: my location message!" );
  }

  // Check that " location:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( " location: my location message!" );

    formatter.formatStandardLocationKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " location: my location message!" );
  }
}

//---------------------------------------------------------------------------//
// Check that the standard stack keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardStackKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that "Stack:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\nStack: my stack message!" );

    formatter.formatStandardStackKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m\nStack:\E[0m my stack message!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\nStack: my stack message!" );
#endif
  }

  // Check that " Stack:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\n Stack: my stack message!" );

    formatter.formatStandardStackKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m\n Stack:\E[0m my stack message!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\n Stack: my stack message!" );
#endif
  }

  // Check that "My Stack:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\nMy Stack: my stack message!" );

    formatter.formatStandardStackKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m\nMy Stack:\E[0m my stack message!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\nMy Stack: my stack message!" );
#endif
  }

  // Check that " My Stack:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\n My Stack: my stack message!" );

    formatter.formatStandardStackKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m\n My Stack:\E[0m my stack message!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\n My Stack: my stack message!" );
#endif
  }

  // Check that "stack:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\nstack: my stack message!" );

    formatter.formatStandardStackKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\nstack: my stack message!" );
  }

  // Check that starting "Stack:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Stack: my stack message!" );

    formatter.formatStandardStackKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Stack: my stack message!" );
  }
}

//---------------------------------------------------------------------------//
// Check that the standard arrow keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardArrowKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that "  ->  " can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "this  ->  that" );

    formatter.formatStandardArrowKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "this\E[1;36;49m  ->  \E[0mthat" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "this  ->  that" );
#endif
  }

  // Check that " -> " will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "this -> that" );

    formatter.formatStandardArrowKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "this -> that" );
  }

  // Check that "->" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "this->that" );

    formatter.formatStandardArrowKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(), "this->that" );
  }
}

//---------------------------------------------------------------------------//
// Check that the standard exception type keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardExceptionTypeKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that " Exception Type:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " Exception Type: my exception type!" );

    formatter.formatStandardExceptionTypeKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m Exception Type:\E[0m my exception type!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " Exception Type: my exception type!" );
#endif
  }

  // Check that "  Exception Type:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "  Exception Type: my exception type!" );

    formatter.formatStandardExceptionTypeKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m  Exception Type:\E[0m my exception type!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "  Exception Type: my exception type!" );
#endif
  }

  // Check that "Exception Type:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Exception Type: my exception type!" );

    formatter.formatStandardExceptionTypeKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Exception Type: my exception type!" );
  }

  // Check that "exception type:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "exception type: my exception type!" );

    formatter.formatStandardExceptionTypeKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "exception type: my exception type!" );
  }

  // Check that " exception type:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( " exception type: my exception type!" );

    formatter.formatStandardExceptionTypeKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " exception type: my exception type!" );
  }
}

//---------------------------------------------------------------------------//
// Check that the standard throw test evaluated true keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardThrowTestEvaluatedTrueKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that " Throw test that evaluated to true:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " Throw test that evaluated to true: my test!" );

    formatter.formatStandardThrowTestEvaluatedTrueKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m Throw test that evaluated to true:\E[0m my test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " Throw test that evaluated to true: my test!" );
#endif
  }

  // Check that "  Throw test that evaluated to true:" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "  Throw test that evaluated to true: my test!" );

    formatter.formatStandardThrowTestEvaluatedTrueKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49m  Throw test that evaluated to true:\E[0m my test!" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "  Throw test that evaluated to true: my test!" );
#endif
  }

  // Check that "Throw test that evaluated to true:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Throw test that evaluated to true: my test!" );

    formatter.formatStandardThrowTestEvaluatedTrueKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Throw test that evaluated to true: my test!" );
  }

  // Check that "throw test that evaluated to true:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "throw test that evaluated to true: my test!" );

    formatter.formatStandardThrowTestEvaluatedTrueKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "throw test that evaluated to true: my test!" );
  }

  // Check that " throw test that evaluated to true:" will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( " throw test that evaluated to true: my test!" );

    formatter.formatStandardThrowTestEvaluatedTrueKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " throw test that evaluated to true: my test!" );
  }
}

//---------------------------------------------------------------------------//
// Check that the standard beginning nested errors keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardBeginningNestedErrorsKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that "Beginning nested errors..." can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Beginning nested errors..." );

    formatter.formatStandardBeginningNestedErrorsKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[4;29;49mBeginning nested errors...\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Beginning nested errors..." );
#endif
  }

  // Check that "\nBeginning nested errors..." can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\nBeginning nested errors..." );

    formatter.formatStandardBeginningNestedErrorsKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[4;29;49m\nBeginning nested errors...\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\nBeginning nested errors..." );
#endif
  }

  // Check that " Beginning nested errors..." will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( " Beginning nested errors..." );

    formatter.formatStandardBeginningNestedErrorsKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       " Beginning nested errors..." );
  }

  // Check that "\n Beginning nested errors..." will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\n Beginning nested errors..." );

    formatter.formatStandardBeginningNestedErrorsKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\n Beginning nested errors..." );
  }

  // Check that "beginning nested errors..." will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "beginning nested errors..." );

    formatter.formatStandardBeginningNestedErrorsKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "beginning nested errors..." );
  }

  // Check that "\nbeginning nested errors..." will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "\nbeginning nested errors..." );

    formatter.formatStandardBeginningNestedErrorsKeywords();

    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\nbeginning nested errors..." );
  }
}

//---------------------------------------------------------------------------//
// Check that the standard filename keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardFilenameKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that a filename ending in ".hpp" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: test.hpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file:\E[1;29;49m test.hpp\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file: test.hpp" );
#endif
  }

  // Check that a filename ending in ".hpp" with a path can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: /home/test_dir/test.hpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file:\E[1;29;49m /home/test_dir/test.hpp\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file: /home/test_dir/test.hpp" );
#endif
  }

  // Check that a filename ending in ".hpp" with a path and line number
  // can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: /home/test_dir/test.hpp:201" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file:\E[1;29;49m /home/test_dir/test.hpp:201\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file: /home/test_dir/test.hpp:201" );
#endif
  }

  // Check that a filename ending in ".cpp" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: test.cpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file:\E[1;29;49m test.cpp\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file: test.cpp" );
#endif
  }

  // Check that a filename ending in ".cpp" with a path can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: local_dir/test.cpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file:\E[1;29;49m local_dir/test.cpp\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file: local_dir/test.cpp" );
#endif
  }

  // Check that a filename ending in ".cpp" with a path and line number can
  // be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: local_dir/test.cpp:16:" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file:\E[1;29;49m local_dir/test.cpp:16:\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test file: local_dir/test.cpp:16:" );
#endif
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "These are test files: include/test.hpp, /home/src/test.cpp:1111" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "These are test files:\E[1;29;49m include/test.hpp\E[0m,\E[1;29;49m /home/src/test.cpp:1111\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "These are test files: include/test.hpp, /home/src/test.cpp:1111" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard pass keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardPassKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that Pass can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Pass]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;32;49mPass\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [Pass]" );
#endif
  }

  // Check that pass can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [pass]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;32;49mpass\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [pass]" );
#endif
  }

  // Check that Passed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Passed]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;32;49mPassed\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [Passed]" );
#endif
  }

  // Check that passed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [passed]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;32;49mpassed\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [passed]" );
#endif
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a passed test: [Pass]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;32;49mpassed\E[0m test: [\E[0;32;49mPass\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a passed test: [Pass]" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard fail keywords can be formatted
BOOST_AUTO_TEST_CASE( formatStandardFailKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that Fail can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Fail]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;31;49mFail\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [Fail]" );
#endif
  }

  // Check that fail can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [fail]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;31;49mfail\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [fail]" );
#endif
  }

  // Check that Failed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Failed]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;31;49mFailed\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [Failed]" );
#endif
  }

  // Check that failed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [failed]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [\E[0;31;49mfailed\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a test: [failed]" );
#endif
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a failed test: [Fail]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a \E[0;31;49mfailed\E[0m test: [\E[0;31;49mFail\E[0m]" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "This is a failed test: [Fail]" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the unit test keywords can be formatted
BOOST_AUTO_TEST_CASE( formatUnitTestKeywords,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  // Check that Passed is formatted
  {
    Utility::DynamicOutputFormatter formatter( "ExampleTest_UnitTest ... [Passed] (0.001 sec)" );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "ExampleTest_UnitTest ... [\E[0;32;49mPassed\E[0m] (0.001 sec)" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "ExampleTest_UnitTest ... [Passed] (0.001 sec)" );
#endif
  }

  // Check that TEST PASSED is formatted
  {
    Utility::DynamicOutputFormatter formatter( "End Result: TEST PASSED" );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "End Result: \E[0;32;49mTEST PASSED\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "End Result: TEST PASSED" );
#endif
  }

  // Check that FAILED is formatted
  {
    Utility::DynamicOutputFormatter formatter( "ExampleTest_UnitTest ... [FAILED] (0.001 sec)" );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "ExampleTest_UnitTest ... [\E[0;31;49mFAILED\E[0m] (0.001 sec)" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "ExampleTest_UnitTest ... [FAILED] (0.001 sec)" );
#endif
  }

  // Check that TEST FAILED is formatted
  {
    Utility::DynamicOutputFormatter formatter( "End Result: TEST FAILED" );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "End Result: \E[0;31;49mTEST FAILED\E[0m" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "End Result: TEST FAILED" );
#endif
  }

  // Check that passed and failed are formatted
  {
    Utility::DynamicOutputFormatter formatter( "Summary: total = N, run = N, passed = X, failed = N-X" );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Summary: total = N, run = N, \E[0;32;49mpassed\E[0m = X, \E[0;31;49mfailed\E[0m = N-X" );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Summary: total = N, run = N, passed = X, failed = N-X" );
#endif
  }

  // Check that Error: is formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: details..." );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;31;49mError: \E[0mdetails..." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Error: details..." );
#endif
  }

  // Check that Note: is formatted
  {
    Utility::DynamicOutputFormatter formatter( "Note: details..." );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;36;49mNote:\E[0m details..." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Note: details..." );
#endif
  }

  // Check that Warning: is formatted
  {
    Utility::DynamicOutputFormatter formatter( "Warning: details..." );

    formatter.formatUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "\E[1;35;49mWarning: \E[0mdetails..." );
#else
    BOOST_CHECK_EQUAL( formatter.getFormattedOutput(),
                       "Warning: details..." );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the desired output can be printed
BOOST_AUTO_TEST_CASE( toStream,
                      * boost::unit_test::depends_on( "formatKeyword" ) )
{
  std::cout << std::endl;
  std::ostringstream oss_raw, oss;

  // Check all defaults
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the bold text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[1;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the faded text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[2;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the italicized text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[3;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the underlined text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[4;29;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the black text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;30;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the red text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;31;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the green text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;32;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the yellow text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;33;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the blue text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;34;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the magenta text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;35;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the cyan text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;36;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the white text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;37;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the black text background color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;40mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the red text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;41mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the green text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;42mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the yellow text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;43mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the blue text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;44mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the magenta text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;45mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the cyan text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;46mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the white text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor>( "test" );
    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "This is a \E[0;29;47mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check multiple formats
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.boldKeyword( "This" );
    formatter.boldRedKeyword( "is" );
    formatter.boldCyanKeyword( "a" );
    formatter.boldMagentaKeyword( "test" );

    formatter.toStream( oss_raw, false );
    formatter.toStream( oss, true );

    BOOST_CHECK_EQUAL( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    BOOST_CHECK_EQUAL( oss.str(), "\E[1;29;49mThis\E[0m \E[1;31;49mis\E[0m \E[1;36;49ma\E[0m \E[1;35;49mtest\E[0m." );
#else
    BOOST_CHECK_EQUAL( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }
}

//---------------------------------------------------------------------------//
// end tstDynamicOutputFormatter.cpp
//---------------------------------------------------------------------------//
