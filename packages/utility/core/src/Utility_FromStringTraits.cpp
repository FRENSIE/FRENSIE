//---------------------------------------------------------------------------//
//!
//! \file   Utility_FromStringTraits.cpp
//! \author Alex Robinson
//! \brief  From string traits class specialization definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_FromStringTraits.hpp"

namespace Utility{

// Container element deliminators
const char* container_element_delims = ",}";

// Container start character
const char container_start_char = '{';

// Next container element character
const char next_container_element_char = ',';

// Container end character
const char container_end_char = '}';

namespace Details{

// 9 = tab (\t), 10 = new line (\n), 32 = white space
const char white_space_delims[3] = {(char)9, (char)10, (char)32};

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
    else if( string_element != ' ' )
      break;
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

    // Another element must be deserialized
    if( delim == elem_delim )
      return false;
    
    // All elements have been deserialized
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
    // an occurance of the pi keyword has been replaced.
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
  
namespace Details{

// Replace occurances of interval keyword within a substring
inline void expandIntervalKeywordInSubstring( const std::string& left_element,
                                              std::string& middle_element,
                                              const std::string& right_element )
{
  bool raw_left_element = left_element.find( next_container_element_char ) > left_element.size();
  bool raw_right_element = right_element.find( next_container_element_char ) > right_element.size();

  std::string::size_type op_pos;

  if( middle_element.find( "pi" ) >= middle_element.size() )
    op_pos = middle_element.find_first_of( "il" );
  else
    op_pos = middle_element.size();


  if( raw_left_element && raw_right_element &&
      op_pos < middle_element.size() )
  {
    TEST_FOR_EXCEPTION( left_element.find( "inf" ) < left_element.size(),
                        std::runtime_error,
                        "The inf keyword cannot be used with the interval "
                        "keyword!" );

    if( left_element.find( "pi" ) >= left_element.size() )
    {
      TEST_FOR_EXCEPTION( left_element.find_first_of( "il" ) <
                          left_element.size(),
                          std::runtime_error,
                          "interval keywords cannot occur in consecutive "
                          "elements!" );
    }

    TEST_FOR_EXCEPTION( right_element.find( "inf" ) < right_element.size(),
                        std::runtime_error,
                        "The inf keyword cannot be used with the interval "
                        "keyword!" );

    if( right_element.find( "pi" ) >= right_element.size() )
    {
      TEST_FOR_EXCEPTION( right_element.find_first_of( "il" ) <
                          right_element.size(),
                          std::runtime_error,
                          "interval keywords cannot occur in consecutive "
                          "elements!" );
    }

    double left_value = Utility::fromString<double>( left_element );
    double right_value = Utility::fromString<double>( right_element );

    TEST_FOR_EXCEPTION( left_value > right_value,
			std::runtime_error,
			"the array elements must be in ascending order ("
                        << left_value << " !<= " << right_value << ")!" );

    size_t intervals =
      Utility::fromString<size_t>( middle_element.substr( 0, op_pos ) );

    TEST_FOR_EXCEPTION( intervals <= 0ll,
			std::runtime_error,
			"a positive integer must be specified with the "
                        "interval keyword (e.g. 3i or 10l)!" );

    // Increment the interval value to account for the last element
    ++intervals;

    // Linear increments
    if( middle_element[op_pos] == 'i' )
    {
      double step_size = (right_value-left_value)/intervals;

      // Replace the interval keyword with the new elements
      middle_element = " ";

      for( size_t i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;
	oss.precision( 18 );

	oss << left_value + step_size*i;

	middle_element += oss.str();

	if( i < intervals-1 )
        {
	  middle_element += next_container_element_char;
          middle_element += " ";
        }
      }
    }
    // Log increments
    else 
    {
      TEST_FOR_EXCEPTION( left_value <= 0.0,
			  std::runtime_error,
			  "the starting value ( " << left_value <<
                          ") must be positive when using the log interval "
                          "keyword 'l'!" );

      double step_size = log(right_value/left_value)/intervals;

      // Replace the interval keyword with the new elements
      middle_element = " ";

      for( size_t i = 1; i < intervals; ++i )
      {
	std::ostringstream oss;
	oss.precision( 18 );

	oss << exp( log(left_value) + step_size*i );

	middle_element += oss.str();

	if( i < intervals-1 )
        {
	  middle_element += next_container_element_char;
          middle_element += " ";
        }
      }
    }
  }
}

} // end Details namespace

// Expand interval keywords in string
void expandIntervalKeywords( std::string& obj_rep )
{
  // Loop through all array elements
  boost::algorithm::trim( obj_rep );

  std::vector<std::string> array_elements;

  boost::split( array_elements,
                obj_rep,
                boost::is_any_of( "," ) );

  std::string front_copy =
    boost::algorithm::to_lower_copy( array_elements.front() );

  if( front_copy.find( "inf" ) >= front_copy.size() &&
      front_copy.find( "pi" ) >= front_copy.size() )
  {
    TEST_FOR_EXCEPTION( array_elements.front().find_first_of( "il" ) <
                        array_elements.front().size(),
                        std::runtime_error,
                        "the first element cannot have an interval keyword!" );
  }

  std::string back_copy =
    boost::algorithm::to_lower_copy( array_elements.back() );

  if( back_copy.find( "inf" ) >= back_copy.size() &&
      back_copy.find( "pi" ) >= back_copy.size() )
  {
    TEST_FOR_EXCEPTION( array_elements.back().find_first_of( "il" ) <
                        array_elements.back().size(),
                        std::runtime_error,
                        "the last element cannot have an interval keyword!" );
  }

  std::string::size_type bracket_pos =
    array_elements.front().find( container_start_char );

  if( bracket_pos < array_elements.front().size() )
    array_elements.front().erase( bracket_pos, 1 );

  bracket_pos = array_elements.back().find( container_end_char );

  if( bracket_pos < array_elements.back().size() )
    array_elements.back().erase( bracket_pos, 1 );

  for( size_t i = 1; i < array_elements.size()-1; ++i )
  {
    // We want the 'i' and 'l' keywords to be case insensitive
    boost::algorithm::to_lower( array_elements[i] );
    
    Details::expandIntervalKeywordInSubstring(
                      boost::algorithm::to_lower_copy( array_elements[i-1] ),
                      array_elements[i],
                      boost::algorithm::to_lower_copy( array_elements[i+1] ) );
  }

  // Reconstruct the array string
  obj_rep = container_start_char;
  obj_rep += array_elements.front();

  for( unsigned i = 1; i < array_elements.size(); ++i )
  {
    obj_rep += next_container_element_char;
    obj_rep += array_elements[i];
  }

  obj_rep += container_end_char;
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_FromStringTraits.cpp
//---------------------------------------------------------------------------//
