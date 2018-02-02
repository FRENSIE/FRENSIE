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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_DynamicOutputFormatter.hpp"
#include "FRENSIE_tty_format_config.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the raw output can be returned
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, getRawOutput )
{
  Utility::DynamicOutputFormatter formatter( "Testing" );

  TEST_EQUALITY_CONST( formatter.getRawOutput(), "Testing" );
}

//---------------------------------------------------------------------------//
// Check that the formatted output can be returned
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, getFormattedOutput )
{
  Utility::DynamicOutputFormatter formatter( "Testing" );

  TEST_EQUALITY_CONST( formatter.getFormattedOutput(), "Testing" );
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatKeyword )
{
  // Check all defaults
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check bold text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[1;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check faded text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[2;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check italicized text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[3;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check underlined text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[4;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the black text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;30;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the red text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;31;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the green text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;32;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check yellow text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;33;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the blue text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;34;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the magenta text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;35;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the cyan text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;36;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the white text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;37;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the black text background color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;40mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the red text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;41mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the green text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;42mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the yellow text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;43mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the blue text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;44mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the magenta text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;45mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the cyan text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;46mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check the white text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;29;47mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }

  // Check combinations
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::GreenTextColor,Utility::MagentaTextBackgroundColor>( "test" );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[4;32;45mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
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
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;31;49mThis\E[0m is a \E[4;32;45mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
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
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;31;49mThis\E[0m \E[1;31;49mis\E[0m a \E[4;32;45mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test." );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, boldKeyword )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "\E[1;29;49mThis\E[0m \E[1;29;49mis\E[0m a \E[1;29;49mtest\E[0m." );
#else
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be italicized
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, italicizedKeyword )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.italicizedKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "\E[3;29;49mThis\E[0m \E[3;29;49mis\E[0m a \E[3;29;49mtest\E[0m." );
#else
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be underlined
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, underlinedKeyword )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.underlinedKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "\E[4;29;49mThis\E[0m \E[4;29;49mis\E[0m a \E[4;29;49mtest\E[0m." );
#else
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-red
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, boldRedKeyword )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldRedKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "\E[1;31;49mThis\E[0m \E[1;31;49mis\E[0m a \E[1;31;49mtest\E[0m." );
#else
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-cyan
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, boldCyanKeyword )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldCyanKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "\E[1;36;49mThis\E[0m \E[1;36;49mis\E[0m a \E[1;36;49mtest\E[0m." );
#else
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-magenta
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, boldMagentaKeyword )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldMagentaKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "\E[1;35;49mThis\E[0m \E[1;35;49mis\E[0m a \E[1;35;49mtest\E[0m." );
#else
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that a keyword can be formatted in bold-white
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, boldWhiteKeyword )
{
  Utility::DynamicOutputFormatter formatter( "This is a test." );

  formatter.boldWhiteKeyword( "\\w*s\\w*" );

#ifdef TTY_FORMATTING_SUPPORTED
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "\E[1;37;49mThis\E[0m \E[1;37;49mis\E[0m a \E[1;37;49mtest\E[0m." );
#else
  TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                       "This is a test." );
#endif
}

//---------------------------------------------------------------------------//
// Check that the standard error message keywords can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatStandardErrorKeywords )
{
  // Check that the "Error:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: this is a test!" );

    formatter.formatStandardErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;31;49mError:\E[0m this is a test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Error: this is a test!" );
#endif
  }

  // Check that the "error:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " error: this is a test!" );

    formatter.formatStandardErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;31;49m error:\E[0m this is a test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         " error: this is a test!" );
#endif
  }

  // Check that the "Error" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is an Error test!" );

    formatter.formatStandardErrorKeywords();

    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is an Error test!" );
  }

  // Check that the "error" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is an error test!" );

    formatter.formatStandardErrorKeywords();

    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is an error test!" );
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: this is an error test!" );

    formatter.formatStandardErrorKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;31;49mError:\E[0m this is an error test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Error: this is an error test!" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard warning message keywords can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatStandardWarningKeywords )
{
  // Check that the "Warning:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Warning: this is a test!" );

    formatter.formatStandardWarningKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;35;49mWarning:\E[0m this is a test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Warning: this is a test!" );
#endif
  }

  // Check that the "warning:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " warning: this is a test!" );

    formatter.formatStandardWarningKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;35;49m warning:\E[0m this is a test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "warning: this is a test!" );
#endif
  }

  // Check that the "Warning" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a Warning test!" );

    formatter.formatStandardWarningKeywords();

    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a Warning test!" );
  }

  // Check that the "warning" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a warning test!" );

    formatter.formatStandardWarningKeywords();

    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a warning test!" );
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Warning: This is a warning test!" );

    formatter.formatStandardWarningKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;35;49mWarning:\E[0m This is a warning test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Warning: This is a warning test!" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard note keywords can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatStandardNoteKeywords )
{
  // Check that the "Note:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Note: this is a test!" );

    formatter.formatStandardNoteKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;36;49mNote:\E[0m this is a test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Note: this is a test!" );
#endif
  }

  // Check that the "note:" keyword can be formatted
  {
    Utility::DynamicOutputFormatter formatter( " note: this is a test!" );

    formatter.formatStandardNoteKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;36;49m note:\E[0m this is a test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "note: this is a test!" );
#endif
  }

  // Check that the "Note" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a Note test!" );

    formatter.formatStandardNoteKeywords();

    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a Note test!" );
  }

  // Check that the "note" keyword will not be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a note test!" );

    formatter.formatStandardNoteKeywords();

    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a note test!" );
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "Note: This is a note test!" );

    formatter.formatStandardNoteKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;36;49mNote:\E[0m This is a note test!" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Note: This is a note test!" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard filename keywords can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatStandardFilenameKeywords )
{
  // Check that a filename ending in ".hpp" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: test.hpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file:\E[1;29;49m test.hpp\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file: test.hpp" );
#endif
  }

  // Check that a filename ending in ".hpp" with a path can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: /home/test_dir/test.hpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file:\E[1;29;49m /home/test_dir/test.hpp\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file: /home/test_dir/test.hpp" );
#endif
  }

  // Check that a filename ending in ".hpp" with a path and line number
  // can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: /home/test_dir/test.hpp:201" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file:\E[1;29;49m /home/test_dir/test.hpp:201\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file: /home/test_dir/test.hpp:201" );
#endif
  }

  // Check that a filename ending in ".cpp" can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: test.cpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file:\E[1;29;49m test.cpp\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file: test.cpp" );
#endif
  }

  // Check that a filename ending in ".cpp" with a path can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: local_dir/test.cpp" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file:\E[1;29;49m local_dir/test.cpp\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file: local_dir/test.cpp" );
#endif
  }

  // Check that a filename ending in ".cpp" with a path and line number can
  // be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test file: local_dir/test.cpp:16:" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file:\E[1;29;49m local_dir/test.cpp:16:\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test file: local_dir/test.cpp:16:" );
#endif
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "These are test files: include/test.hpp, /home/src/test.cpp:1111" );

    formatter.formatStandardFilenameKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "These are test files:\E[1;29;49m include/test.hpp\E[0m,\E[1;29;49m /home/src/test.cpp:1111\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "These are test files: include/test.hpp, home/src/test.cpp:1111" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard pass keywords can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatStandardPassKeywords )
{
  // Check that Pass can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Pass]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;32;49mPass\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [Pass]" );
#endif
  }

  // Check that pass can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [pass]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;32;49mpass\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [pass]" );
#endif
  }

  // Check that Passed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Passed]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;32;49mPassed\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [Passed]" );
#endif
  }

  // Check that passed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [passed]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;32;49mpassed\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [passed]" );
#endif
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a passed test: [Pass]" );

    formatter.formatStandardPassKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;32;49mpassed\E[0m test: [\E[0;32;49mPass\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a passed test: [Pass]" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the standard fail keywords can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatStandardFailKeywords )
{
  // Check that Fail can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Fail]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;31;49mFail\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [Fail]" );
#endif
  }

  // Check that fail can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [fail]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;31;49mfail\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [fail]" );
#endif
  }

  // Check that Failed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [Failed]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;31;49mFailed\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [Failed]" );
#endif
  }

  // Check that failed can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a test: [failed]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [\E[0;31;49mfailed\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a test: [failed]" );
#endif
  }

  // Check that multiple occurrences can be formatted
  {
    Utility::DynamicOutputFormatter formatter( "This is a failed test: [Fail]" );

    formatter.formatStandardFailKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a \E[0;31;49mfailed\E[0m test: [\E[0;31;49mFail\E[0m]" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "This is a failed test: [Fail]" );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the Teuchos unit test keywords can be formatted
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, formatTeuchosUnitTestKeywords )
{
  // Check that Passed is formatted
  {
    Utility::DynamicOutputFormatter formatter( "ExampleTest_UnitTest ... [Passed] (0.001 sec)" );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "ExampleTest_UnitTest ... [\E[0;32;49mPassed\E[0m] (0.001 sec)" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "ExampleTest_UnitTest ... [Passed] (0.001 sec)" );
#endif
  }

  // Check that TEST PASSED is formatted
  {
    Utility::DynamicOutputFormatter formatter( "End Result: TEST PASSED" );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "End Result: \E[0;32;49mTEST PASSED\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "End Result: TEST PASSED" );
#endif
  }

  // Check that FAILED is formatted
  {
    Utility::DynamicOutputFormatter formatter( "ExampleTest_UnitTest ... [FAILED] (0.001 sec)" );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "ExampleTest_UnitTest ... [\E[0;31;49mFAILED\E[0m] (0.001 sec)" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "ExampleTest_UnitTest ... [FAILED] (0.001 sec)" );
#endif
  }

  // Check that TEST FAILED is formatted
  {
    Utility::DynamicOutputFormatter formatter( "End Result: TEST FAILED" );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "End Result: \E[0;31;49mTEST FAILED\E[0m" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "End Result: TEST FAILED" );
#endif
  }

  // Check that passed and failed are formatted
  {
    Utility::DynamicOutputFormatter formatter( "Summary: total = N, run = N, passed = X, failed = N-X" );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Summary: total = N, run = N, \E[0;32;49mpassed\E[0m = X, \E[0;31;49mfailed\E[0m = N-X" );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Summary: total = N, run = N, passed = X, failed = N-X" );
#endif
  }

  // Check that Error: is formatted
  {
    Utility::DynamicOutputFormatter formatter( "Error: details..." );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;31;49mError:\E[0m details..." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Error: details..." );
#endif
  }

  // Check that Note: is formatted
  {
    Utility::DynamicOutputFormatter formatter( "Note: details..." );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;36;49mNote:\E[0m details..." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Note: details..." );
#endif
  }

  // Check that Warning: is formatted
  {
    Utility::DynamicOutputFormatter formatter( "Warning: details..." );

    formatter.formatTeuchosUnitTestKeywords();

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "\E[1;35;49mWarning:\E[0m details..." );
#else
    TEST_EQUALITY_CONST( formatter.getFormattedOutput(),
                         "Warning: details..." );
#endif
  }
}

//---------------------------------------------------------------------------//
// Check that the desired output can be printed
TEUCHOS_UNIT_TEST( DynamicOutputFormatter, print )
{
  std::cout << std::endl;
  std::ostringstream oss_raw, oss;

  // Check all defaults
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the bold text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::BoldTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[1;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the faded text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::FadedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[2;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the italicized text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::ItalicizedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[3;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the underlined text format only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::UnderlinedTextFormat,Utility::DefaultTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[4;29;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the black text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlackTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;30;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the red text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::RedTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;31;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the green text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::GreenTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;32;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the yellow text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::YellowTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;33;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the blue text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::BlueTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;34;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the magenta text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::MagentaTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;35;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the cyan text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::CyanTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;36;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the white text color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::WhiteTextColor,Utility::DefaultTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;37;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the black text background color only
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlackTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;40mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the red text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::RedTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;41mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the green text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::GreenTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;42mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the yellow text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::YellowTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;43mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the blue text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::BlueTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;44mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the magenta text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::MagentaTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;45mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the cyan text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::CyanTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;46mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }

  // Check the white text background color
  {
    Utility::DynamicOutputFormatter formatter( "This is a test." );

    formatter.formatKeyword<Utility::DefaultTextFormat,Utility::DefaultTextColor,Utility::WhiteTextBackgroundColor>( "test" );
    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "This is a \E[0;29;47mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
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

    formatter.print( oss_raw, false );
    formatter.print( oss, true );

    TEST_EQUALITY_CONST( oss_raw.str(), "This is a test." );

#ifdef TTY_FORMATTING_SUPPORTED
    TEST_EQUALITY_CONST( oss.str(), "\E[1;29;49mThis\E[0m \E[1;31;49mis\E[0m \E[1;36;49ma\E[0m \E[1;35;49mtest\E[0m." );
#else
    TEST_EQUALITY_CONST( oss.str(), "This is a test." );
#endif

    std::cout << formatter << std::endl;
    oss.str( "" ); oss_raw.str( "" );
    oss.clear(); oss_raw.clear();
  }
}

//---------------------------------------------------------------------------//
// end tstDynamicOutputFormatter.cpp
//---------------------------------------------------------------------------//
