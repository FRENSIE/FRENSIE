//---------------------------------------------------------------------------//
//!
//! \file   Utility_FancyTextOStreamBackend.cpp
//! \author Alex Robinson
//! \brief  Fancy text ostream backend for boost logging sinks
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <vector>
#include <algorithm>

// FRENSIE Includes
#include "Utility_FancyTextOStreamBackend.hpp"

namespace Utility{

//! Sink implementation
template<typename CharT>
struct BasicFancyTextOStreamBackend<CharT>::Implementation
{
  //! Type of the container that holds all aggregated streams
  typedef std::vector<boost::shared_ptr<stream_type> > OStreamSequence;

  //! Type of the container that holds all dynamic formatting functions
  typedef std::vector<DynamicFormattingFunction> DynamicFormattingFunctionSequence;

  // The output stream list
  OStreamSequence streams;

  // The dynamic formatting function list
  DynamicFormattingFunctionSequence dynamic_format_ops;

  // Auto-flush flag
  bool auto_flush;
};

// Constructor
template<typename CharT>
BasicFancyTextOStreamBackend<CharT>::BasicFancyTextOStreamBackend()
  : d_impl( new Implementation )
{ /* ... */ }

// Destructor
template<typename CharT>
BasicFancyTextOStreamBackend<CharT>::~BasicFancyTextOStreamBackend()
{
  delete d_impl;
}

// The method adds a new stream to the sink
template<typename CharT>
void BasicFancyTextOStreamBackend<CharT>::add_stream(
                                     const boost::shared_ptr<stream_type>& os )
{
  typename Implementation::OStreamSequence::iterator it =
    std::find( d_impl->streams.begin(), d_impl->streams.end(), os );

  if( it == d_impl->streams.end() )
    d_impl->streams.push_back( os );
}

// The method removes a stream from the sink
/*! \details If the stream is not attached to the sink this method has no
 * effect.
 */
template<typename CharT>
void BasicFancyTextOStreamBackend<CharT>::remove_stream(
                                     const boost::shared_ptr<stream_type>& os )
{
  typename Implementation::OStreamSequence::iterator it =
    std::find( d_impl->streams.begin(), d_impl->streams.end(), os );

  if( it != d_impl->streams.end() )
    d_impl->streams.erase( it );
}

// Set the flag to automatically flush buffers of all attached streams after each log record
template<typename CharT>
void BasicFancyTextOStreamBackend<CharT>::auto_flush( const bool auto_flush_buffers )
{
  d_impl->auto_flush = auto_flush_buffers;
}

// The method writes the message to the sink
template<typename CharT>
void BasicFancyTextOStreamBackend<CharT>::consume(
                                         const boost::log::record_view&,
                                         const string_type& formatted_message )
{
  // Create a dynamic output formatter
  Utility::DynamicOutputFormatter
    backend_formatted_message( formatted_message );

  // Apply all of the formatting operations
  typename Implementation::DynamicFormattingFunctionSequence::const_iterator
    format_ops_it = d_impl->dynamic_format_ops.begin();

  typename Implementation::DynamicFormattingFunctionSequence::const_iterator
    format_ops_end = d_impl->dynamic_format_ops.end();

  while( format_ops_it != format_ops_end )
  {
    (*format_ops_it)( backend_formatted_message );

    ++format_ops_it;
  }

  // Added the formatted output to the streams
  typename Implementation::OStreamSequence::const_iterator
    os_it = d_impl->streams.begin();

  typename Implementation::OStreamSequence::const_iterator
    os_end = d_impl->streams.end();

  while( os_it != os_end )
  {
    stream_type* const os_ptr = os_it->get();

    if( os_ptr->good() )
    {
      *os_ptr << backend_formatted_message;

      if( d_impl->auto_flush )
        os_ptr->flush();
    }

    ++os_it;
  }
}

// The method flushes the associated streams
template<typename CharT>
void BasicFancyTextOStreamBackend<CharT>::flush()
{
  typename Implementation::OStreamSequence::const_iterator it =
    d_impl->streams.begin();
  typename Implementation::OStreamSequence::const_iterator end =
    d_impl->streams.end();

  while( it != end )
  {
    stream_type* const os_ptr = it->get();

    if( os_ptr->good() )
      os_ptr->flush();

    ++it;
  }
}

// Add a dynamic formatting function
template<typename CharT>
void BasicFancyTextOStreamBackend<CharT>::addDynamicFormattingFunction(
                                        const DynamicFormattingFunction& func )
{
  d_impl->dynamic_format_ops.push_back( func );
}

// Explicitly instantiate this sink backend implementation
#ifdef BOOST_LOG_USE_CHAR
template class BasicFancyTextOStreamBackend<char>;
#endif
#ifdef BOOST_LOG_USE_WHCAR_T
template class BasicFancyTextOStreamBackend<wchar_t>;
#endif

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_FancyTextOStreamBackend.cpp
//---------------------------------------------------------------------------//
