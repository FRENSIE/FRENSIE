// Define the tty shell formats (if supported)
#ifndef TTY_FORMAT_CONFIG_HPP
#define TTY_FORMAT_CONFIG_HPP

#define TTY_FORMATTING_SUPPORTED

#ifdef TTY_FORMATTING_SUPPORTED
#include <unistd.h>

// Begine the format specification
#define BEGIN_FORMAT_SPEC "\E["

// End the format specification
#define END_FORMAT_SPEC "m"

// Reset the format specification
#define RESET_FORMAT_SPEC "\E[0m"

// Format key deliminator
#define FORMAT_KEY_DELIMINATOR ";" 

// Text format keys
#define DEFAULT_FORMAT_KEY "0"
#define BOLD_FORMAT_KEY "1"
#define FADED_FORMAT_KEY "2"
#define ITALICIZED_FORMAT_KEY "3"
#define UNDERLINED_FORMAT_KEY "4"

// Text color keys
#define DEFAULT_COLOR_TEXT_FORMAT_KEY "29"
#define BLACK_TEXT_FORMAT_KEY "30"
#define RED_TEXT_FORMAT_KEY "31"
#define GREEN_TEXT_FORMAT_KEY "32"
#define YELLOW_TEXT_FORMAT_KEY "33"
#define BLUE_TEXT_FORMAT_KEY "34"
#define MAGENTA_TEXT_FORMAT_KEY "35"
#define CYAN_TEXT_FORMAT_KEY "36"
#define WHITE_TEXT_FORMAT_KEY "37"

// Text background color keys
#define DEFAULT_BKGD_COLOR_FORMAT_KEY "49"
#define BLACK_BKGD_FORMAT_KEY "40"
#define RED_BKGD_FORMAT_KEY "41"
#define GREEN_BKGD_FORMAT_KEY "42"
#define YELLOW_BKGD_FORMAT_KEY "43"
#define BLUE_BKGD_FORMAT_KEY "44"
#define MAGENTA_BKGD_FORMAT_KEY "45"
#define CYAN_BKGD_FORMAT_KEY "46"
#define WHITE_BKGD_FORMAT_KEY "47"

#else // TTY_FORMATTING_SUPPORTED

#define BEGIN_FORMAT_SPEC ""
#define END_FORMAT_SPEC ""
#define RESET_FORMAT_SPEC ""
#define FORMAT_KEY_DELIMINATOR ""
#define DEFAULT_FORMAT_KEY ""
#define BOLD_FORMAT_KEY ""
#define FADED_FORMAT_KEY ""
#define ITALICIZED_FORMAT_KEY ""
#define UNDERLINED_FORMAT_KEY ""
#define DEFAULT_COLOR_TEXT_FORMAT_KEY ""
#define BLACK_TEXT_FORMAT_KEY ""
#define RED_TEXT_FORMAT_KEY ""
#define GREEN_TEXT_FORMAT_KEY ""
#define YELLOW_TEXT_FORMAT_KEY ""
#define BLUE_TEXT_FORMAT_KEY ""
#define MAGENTA_TEXT_FORMAT_KEY ""
#define CYAN_TEXT_FORMAT_KEY ""
#define WHITE_TEXT_FORMAT_KEY ""
#define DEFAULT_BKGD_COLOR_FORMAT_KEY ""
#define BLACK_BKGD_FORMAT_KEY ""
#define RED_BKGD_FORMAT_KEY ""
#define GREEN_BKGD_FORMAT_KEY ""
#define YELLOW_BKGD_FORMAT_KEY ""
#define BLUE_BKGD_FORMAT_KEY ""
#define MAGENTA_BKGD_FORMAT_KEY ""
#define CYAN_BKGD_FORMAT_KEY ""
#define WHITE_BKGD_FORMAT_KEY ""

#endif // end TTY_FORMATTING_SUPPORTED

#endif // end TTY_FORMAT_CONFIG_HPP
