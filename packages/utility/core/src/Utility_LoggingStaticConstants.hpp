//---------------------------------------------------------------------------//
//!
//! \file   Utility_LoggingStaticConstants.hpp
//! \author Alex Robinson
//! \brief  Logging static constants
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_LOGGING_STATIC_CONSTANTS_HPP
#define UTILITY_LOGGING_STATIC_CONSTANTS_HPP

//---------------------------------------------------------------------------//
// Attribute Keywords
//---------------------------------------------------------------------------//

//! The severity attribute keyword
#define FRENSIE_LOG_RECORD_TYPE_ATTR_KEYWORD "Severity"

//! The tag attribute keyword
#define FRENSIE_LOG_TAG_ATTR_KEYWORD "Tag"

//! The line id attribute keyword
#define FRENSIE_LOG_LINE_ID_ATTR_KEYWORD "LineID"

//! The scope attribute keyword
#define FRENSIE_LOG_SCOPE_ATTR_KEYWORD "Scope"

//! The thread id attribute keyword
#define FRENSIE_LOG_THREAD_ID_ATTR_KEYWORD "ThreadID"

//! The process id attribute keyword
#define FRENSIE_LOG_PROCESS_ID_ATTR_KEYWORD "ProcessID"

//! The time stamp attribute keyword
#define FRENSIE_LOG_TIME_STAMP_ATTR_KEYWORD "TimeStamp"

//! The chrono attribute keyword
#define FRENSIE_LOG_CHRONO_ATTR_KEYWORD "Chrono"

//---------------------------------------------------------------------------//
// Special tag attribute values
//---------------------------------------------------------------------------//

//! The tag value used in FRENSIE Error logs to report nested error data
#define FRENSIE_LOG_NESTED_ERROR_TAG "__NESTED__"

//! The tag value used in FRENSIE Notification logs to report a partial entry
#define FRENSIE_LOG_PARTIAL_NOTIFICATION_TAG "__PARTIAL__"

//---------------------------------------------------------------------------//
// Error log message strings
//---------------------------------------------------------------------------//

//! The white-space free error log message basic starting string
#define FRENSIE_LOG_ERROR_MSG_BASIC "Error"

//! The error log message starting string
#define FRENSIE_LOG_ERROR_MSG FRENSIE_LOG_ERROR_MSG_BASIC ": "

//! The regex string used for finding error log message starting strings
#define FRENSIE_LOG_ERROR_MSG_REGEX "^[\\w ]*" FRENSIE_LOG_ERROR_MSG "|\\n[\\w ]*" FRENSIE_LOG_ERROR_MSG

/*! \brief The message used to report that nested errors will be reported (no 
 * beginning or trailing white-space)
 */
#define FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG_BASIC "Beginning nested errors..."

//! The message used to report that nested errors will be reported
#define FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG_BASIC "\n\n" 

/*! \brief The regex string used for finding messages used to report that 
 * nested errors will be reported
 */
#define FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG_REGEX "^" FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG_BASIC "|\\n" FRENSIE_LOG_BEGINNING_NESTED_ERRORS_MSG_BASIC

//---------------------------------------------------------------------------//
// Warning log message strings
//---------------------------------------------------------------------------//

//! The white-space free warning log message basic starting string
#define FRENSIE_LOG_WARNING_MSG_BASIC "Warning"

//! The warning log message starting string
#define FRENSIE_LOG_WARNING_MSG FRENSIE_LOG_WARNING_MSG_BASIC ": "

//! The regex string used for finding warning log message starting strings
#define FRENSIE_LOG_WARNING_MSG_REGEX "^[\\w ]*" FRENSIE_LOG_WARNING_MSG "|\\n[\\w ]*" FRENSIE_LOG_WARNING_MSG

//---------------------------------------------------------------------------//
// Notification log message strings
//---------------------------------------------------------------------------//

//! The white-space free notification log message basic starting string
#define FRENSIE_LOG_NOTIFICATION_MSG_BASIC "Notification"

//! The white-space free details log message basic starting string
#define FRENSIE_LOG_DETAILS_MSG_BASIC "Details"

//! The white-space free pedantic details log message basic starting string
#define FRENSIE_LOG_PEDANTIC_DETAILS_MSG_BASIC "Pedantic Details"

//---------------------------------------------------------------------------//
// Log data message strings
//---------------------------------------------------------------------------//

//! The string to be used at the start of a data line in a log
#define FRENSIE_LOG_DATA_LINE_START "  "

/*! \brief The message used to report the throw test that evaluated to TRUE 
 * (no beginning or trailing white-space)
 */
#define FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG_BASIC "Throw test that evaluated to true:"

//! The message used to report the throw test that evaluated to TRUE
#define FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG FRENSIE_LOG_DATA_LINE_START FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG_BASIC " "

/*! \brief The regex string that can be used to find the message used to report
 * that a throw test evaluated to true
 */
#define FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG_REGEX "[ ]+" FRENSIE_LOG_THROW_TEST_THAT_EVALUATED_TO_TRUE_MSG_BASIC

/*! \brief The exception type message starting string (no beginning or 
 * trailing white-space)
 */
#define FRENSIE_LOG_EXCEPTION_TYPE_MSG_BASIC "Exception Type:"

//! The exception type message starting string
#define FRENSIE_LOG_EXCEPTION_TYPE_MSG FRENSIE_LOG_DATA_LINE_START FRENSIE_LOG_EXCEPTION_TYPE_MSG_BASIC " "

/*! \brief The regex string that can be used to find exception type message 
 * starting strings
 */
#define FRENSIE_LOG_EXCEPTION_TYPE_MSG_REGEX "[ ]+" FRENSIE_LOG_EXCEPTION_TYPE_MSG_BASIC

//! The location message starting string (no beginning or trailing white-space)
#define FRENSIE_LOG_LOCATION_MSG_BASIC "Location:"

//! The location message starting string
#define FRENSIE_LOG_LOCATION_MSG FRENSIE_LOG_DATA_LINE_START FRENSIE_LOG_LOCATION_MSG_BASIC " "

//! The regex string that can be used to find location message starting strings
#define FRENSIE_LOG_LOCATION_MSG_REGEX "[ ]+" FRENSIE_LOG_LOCATION_MSG_BASIC

//! The stack message starting string (no beginning or trailing white-space)
#define FRENSIE_LOG_STACK_MSG_BASIC "Stack:"

//! The stack message starting string
#define FRENSIE_LOG_STACK_MSG FRENSIE_LOG_DATA_LINE_START FRENSIE_LOG_STACK_MSG_BASIC " "

//! The regex string that can be used to find stack message starting strings
#define FRENSIE_LOG_STACK_MSG_REGEX "\\n[\\w ]*" FRENSIE_LOG_STACK_MSG_BASIC

//! The white-space free partial stack deliminator
#define FRENSIE_LOG_STACK_DELIMINATOR_BASIC_PARTIAL "*"

//! The white-space free complete stack deliminator
#define FRENSIE_LOG_STACK_DELIMINATOR_BASIC FRENSIE_LOG_STACK_DELIMINATOR_BASIC_PARTIAL FRENSIE_LOG_STACK_DELIMINATOR_BASIC_PARTIAL

//! The stack deliminator
#define FRENSIE_LOG_STACK_DELIMINATOR "\n    " FRENSIE_LOG_STACK_DELIMINATOR_BASIC "  "

/*! \brief The regex string that can be used can be used to search for stack 
 * deliminators
 */
#define FRENSIE_LOG_STACK_DELIMINATOR_REGEX "  \\" FRENSIE_LOG_STACK_DELIMINATOR_BASIC_PARTIAL "\\" FRENSIE_LOG_STACK_DELIMINATOR_BASIC_PARTIAL "  "

//! The separator used when reporting file name and line number data
#define FRENSIE_LOG_FILE_LINE_SEP ":"

//! The white-space free separator used to report that something has changed
#define FRENSIE_LOG_ARROW_SEP_BASIC "->"

//! The separator used to report that something has changed
#define FRENSIE_LOG_ARROW_SEP "  " FRENSIE_LOG_ARROW_SEP_BASIC "  "

//! The regex string that can be used to find the arrow separator
#define FRENSIE_LOG_ARROW_SEP_REGEX FRENSIE_LOG_ARROW_SEP


#endif // end UTILITY_LOGGING_STATIC_CONSTANTS_HPP

//---------------------------------------------------------------------------//
// end Utility_LoggingStaticConstants.hpp
//---------------------------------------------------------------------------//
