//---------------------------------------------------------------------------//
//!
//! \file   Utility_FromStringTraits.cpp
//! \author Alex Robinson
//! \brief  From string traits class specialization definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_FromStringTraits.hpp"
#include "Utility_LoggingStaticConstants.hpp"

namespace Utility{

namespace Details{

// 9 = tab (\t), 10 = new line (\n), 32 = white space
const std::string white_space_delims( "\t\n " );

} // end Details namespace

// Extract a string
std::string FromStringTraits<std::string>::extractString(
                                                    std::istream& is,
                                                    const std::string& delims )
{
  std::string obj;

  if( delims.size() > 0 )
  {
    bool done = false;

    while( !done )
    {
      char string_element;
      is.get( string_element );

      if( (delims.size() == 0 || delims == Details::white_space_delims ) && is.eof() )
      {
        done = true;
      }
      else if( is.eof() )
      {
        THROW_EXCEPTION( Utility::StringConversionException,
                         "Unable to get the string element (EOF reached "
                         "unexpectedly)!" );
      }
      else if( !is )
      {
        THROW_EXCEPTION( Utility::StringConversionException,
                         "Unable to get the string element (one or more "
                         "error flags have been set)!" );
      }

      if( delims.find( string_element ) < delims.size() )
      {
        done = true;

        // Put the deliminator back in the stream so that it can be
        // parsed correctly later
        if( delims != Details::white_space_delims )
          is.putback( string_element );
      }

      if( !done )
        obj.push_back( string_element );
    }

    // Trim the extracted string (unless the string is only whitespace)
    if( obj.find_first_not_of( " " ) < obj.size() )
      boost::algorithm::trim( obj );
  }
  // No deliminators have been specified - use the default extraction method
  else
    std::getline( is, obj );

  return obj;
}

// Extract a string element
std::string FromStringTraits<std::string>::extractElementString(
                                                    std::istream& is,
                                                    const std::string& delims )
{
  // Check if a sub-container is present
  bool sub_container_present = false;

  std::string sub_container_string;

  while( true )
  {
    char string_element;
    is.get( string_element );
    sub_container_string.push_back( string_element );

    TEST_FOR_EXCEPTION( is.eof(),
                        Utility::StringConversionException,
                        "Unable to get the string element (EOF reached "
                        "unexpectedly)!" );

    TEST_FOR_EXCEPTION( !is,
                        Utility::StringConversionException,
                        "Unable to get the string element (one or more "
                        "error flags have been set)!" );

    if( string_element == container_start_char )
    {
      sub_container_present = true;
      break;
    }
    else
    {
      bool white_space_element = false;

      for( size_t i = 0; i < Details::white_space_delims.size(); ++i )
      {
        if( string_element == Details::white_space_delims[i] )
        {
          white_space_element = true;
          break;
        }
      }

      if( !white_space_element )
        break;
    }
  }

  // Restore the stream
  if( !sub_container_present )
  {
    while( sub_container_string.size() > 0 )
    {
      is.putback( sub_container_string.back() );
      sub_container_string.pop_back();
    }

    // Extract a string from the stream
    return FromStringTraits<std::string>::extractString( is, delims );
  }

  // Continue reading until the numer of start deliminators equals the
  // number of end deliminators
  else
  {
    // Count the number of '{' and '}' characters that occur
    size_t num_start_delim_chars = 1;
    size_t num_end_delim_chars = 0;

    while( num_start_delim_chars != num_end_delim_chars )
    {
      char string_element;
      is.get( string_element );

      TEST_FOR_EXCEPTION( is.eof(),
                          Utility::StringConversionException,
                          "Unable to get the string element (EOF reached "
                          "unexpectedly)!" );

      TEST_FOR_EXCEPTION( !is,
                          Utility::StringConversionException,
                          "Unable to get the string element (one or more "
                          "error flags have been set)!" );

      if( string_element == container_start_char )
        ++num_start_delim_chars;
      if( string_element == container_end_char )
        ++num_end_delim_chars;

      sub_container_string.push_back( string_element );
    }

    return sub_container_string;
  }
}

// Initialize the input stream that will be used to deserialize an object
void initializeInputStream( std::istream& is, const char start_delim )
{
  // Read the start deliminator
  std::string start_bracket;
  std::getline( is, start_bracket, start_delim );
  boost::algorithm::trim( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
                      std::runtime_error,
                      "Unable to initialize the input stream because there "
                      "are characters preceding the start deliminator ("
                      << start_delim << ")! Here are the extra characters: "
                      << start_bracket );
}

// Move the input stream to the start of the next element
bool moveInputStreamToNextElement( std::istream& is,
                                   const char elem_delim,
                                   const char end_delim )
{
  // Search for the specified element deliminator
  char delim;

  while( true )
  {
    is.get( delim );

    // Another element must be de-serialized
    if( delim == elem_delim )
      return false;

    // All elements have been de-serialized
    else if( delim == end_delim )
      return true;

    // An invalid deliminator has been encountered
    else if( delim != ' ' )
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Unable to move the input stream to the next element "
                       "(bad deliminator encountered: \"" << delim << "\")!" );
      return true;
    }

    TEST_FOR_EXCEPTION( is.eof(),
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(EOF reached unexpectedly)!" );

    TEST_FOR_EXCEPTION( !is,
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(one or more error flags have been set)!" );
  }
}

// Check if the input stream contains any more elements to read.
bool doesInputStreamContainAnotherElement( std::istream& is,
                                           const char end_delim,
                                           const bool ignore_whitespace )
{
  std::string stream_cache;
  char element;

  bool another_element_present;

  while( true )
  {
    is.get( element );

    TEST_FOR_EXCEPTION( is.eof(),
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(EOF reached unexpectedly)!" );

    TEST_FOR_EXCEPTION( !is,
                        std::runtime_error,
                        "Unable to move the input stream to the next element "
                        "(one or more error flags have been set)!" );

    stream_cache.push_back( element );

    // The end deliminator was encountered - there are no more elements
    if( element == end_delim )
    {
      another_element_present = false;
      break;
    }
    else if( element == ' ' )
    {
      if( !ignore_whitespace )
      {
        another_element_present = true;
        break;
      }
    }
    else
    {
      another_element_present = true;
      break;
    }
  }

  // Restore the stream
  if( another_element_present )
  {
    while( stream_cache.size() > 0 )
    {
      is.putback( stream_cache.back() );

      stream_cache.pop_back();
    }
  }

  return another_element_present;
}

namespace Details{

// Expand pi keyword in a substring
inline void expandPiKeywordInSubstring( const std::string::size_type start,
                                        const std::string::size_type true_end,
                                        std::string& substring )
{
  // Convert to lower case
  boost::algorithm::to_lower( substring );

  std::string::size_type pi_pos = substring.find( "pi", start );

  TEST_FOR_EXCEPTION( substring.find( "pi", pi_pos+2 ) < true_end,
		      std::runtime_error,
		      "The 'pi' keyword cannot occur multiple times in the "
                      "same element!" );

  if( pi_pos >= start && pi_pos < true_end )
  {
    double front_value = 1.0, end_value = 1.0;

    std::string front_string = substring.substr( start, pi_pos-start );

    if( front_string.find_first_of( "0123456789" ) < front_string.size() )
    {
      std::istringstream iss( front_string );

      iss >> front_value;
    }
    else if( front_string.find( "-" ) < front_string.size() )
      front_value = -1.0;

    std::string::size_type div_pos = substring.find_first_of( "/", start );

    if( div_pos < true_end && div_pos > pi_pos )
    {
      std::string end_string =
	substring.substr( div_pos+1, true_end - div_pos );

      if( end_string.find_first_of( "0123456789" ) <
	  end_string.size() )
      {
	std::istringstream iss( end_string );

	iss >> end_value;
      }
    }
    else if( div_pos < pi_pos )
    {
      THROW_EXCEPTION( std::runtime_error,
		       "invalid array element value ("
		       << substring.substr( start, true_end )
		       << ")! " );
    }

    std::ostringstream oss;
    oss.precision( 18 );

    oss << front_value*Utility::PhysicalConstants::pi/end_value;

    substring.replace( start, true_end - start + 1, oss.str() );
  }
}

} // end Details namespace

// Expand pi keyword in string
void expandPiKeywords( std::string& obj_rep )
{
  std::string::size_type orig_string_size = 0;
  std::string::size_type elem_start_pos, elem_end_pos;

  do{
    // This is either the first loop or the string has changed because
    // an occurrence of the pi keyword has been replaced.
    if( orig_string_size != obj_rep.size() )
    {
      // Find the start of an element
      elem_start_pos = obj_rep.find( container_start_char );

      if( elem_start_pos < obj_rep.size() )
        ++elem_start_pos;
      else
        elem_start_pos = 0;

      orig_string_size = obj_rep.size();
    }
    else
    {
      // Move the the next element
      elem_start_pos = elem_end_pos+1;
    }

    // Find the end of an element
    elem_end_pos = obj_rep.find_first_of( container_element_delims, elem_start_pos );

    if( elem_end_pos > obj_rep.size() )
      elem_end_pos = obj_rep.size();


    Details::expandPiKeywordInSubstring( elem_start_pos,
                                         elem_end_pos - 1,
                                         obj_rep );
  }while( elem_end_pos < obj_rep.size() );
}

// Convert the string to a Utility::LogRecordType
auto FromStringTraits<LogRecordType>::fromString(
                                     const std::string& obj_rep ) -> ReturnType
{
  std::string trimmed_obj_rep = boost::algorithm::trim_copy( obj_rep );

  if( trimmed_obj_rep == FRENSIE_LOG_ERROR_MSG_BASIC )
    return ERROR_RECORD;
  else if( trimmed_obj_rep == FRENSIE_LOG_WARNING_MSG_BASIC )
    return WARNING_RECORD;
  else if( trimmed_obj_rep == FRENSIE_LOG_NOTIFICATION_MSG_BASIC )
    return NOTIFICATION_RECORD;
  else if( trimmed_obj_rep == FRENSIE_LOG_DETAILS_MSG_BASIC )
    return DETAILS_RECORD;
  else if( trimmed_obj_rep == FRENSIE_LOG_PEDANTIC_DETAILS_MSG_BASIC )
    return PEDANTIC_DETAILS_RECORD;
  else
  {
    THROW_EXCEPTION( Utility::StringConversionException,
                     "unknown log record type name ("
                     << obj_rep << ")!" );
  }
}

// Extract the object from a stream
void FromStringTraits<LogRecordType>::fromStream( std::istream& is,
                                                  LogRecordType& obj,
                                                  const std::string& delim )
{
  std::string delim_copy = delim;

  std::string obj_rep =
    BaseType::extractEnumValueNameFromStream( is, delim_copy );

  // Handle the pedantic details special case
  if( std::string( FRENSIE_LOG_PEDANTIC_DETAILS_MSG_BASIC ).find( obj_rep ) == 0 )
  {
    std::string obj_rep_end;

    while( obj_rep_end.size() == 0 )
      Utility::fromStream( is, obj_rep_end, delim_copy );

    obj_rep += " ";
    obj_rep += obj_rep_end;
  }

  obj = FromStringTraits<LogRecordType>::fromString( obj_rep );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_FromStringTraits.cpp
//---------------------------------------------------------------------------//
