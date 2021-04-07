//---------------------------------------------------------------------------//
//!
//! \file   Utility_FancyTextOStreamBackend.hpp
//! \author Alex Robinson
//! \brief  Fancy text ostream backend for boost logging sinks
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_FANCY_TEXT_OSTREAM_BACKEND_HPP
#define UTILITY_FANCY_TEXT_OSTREAM_BACKEND_HPP

// Std Lib Includes
#include <ostream>
#include <functional>
#include <string>

// Boost Includes
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>

// FRENSIE Includes
#include "Utility_DynamicOutputFormatter.hpp"

namespace Utility{

/*! \brief An implementation of a text output stream logging sink backend
 *
 * The sink backend puts formatted log records to one or more text streams.
 * Unlike the boost::log::sinks::text_ostream_backend, this class allows
 * one to add tty formatting to the output stream.
 */
template<typename CharT>
class BasicFancyTextOStreamBackend : public boost::log::sinks::basic_formatted_sink_backend<CharT,boost::log::sinks::combine_requirements<boost::log::sinks::synchronized_feeding,boost::log::sinks::flushing>::type>
{

private:

  // The base type
  typedef boost::log::sinks::basic_formatted_sink_backend<CharT,boost::log::sinks::combine_requirements<boost::log::sinks::synchronized_feeding,boost::log::sinks::flushing>::type> base_type;

public:

  //! Character type
  typedef typename base_type::char_type char_type;

  //! String type to be used as a message text holder
  typedef typename base_type::string_type string_type;

  //! Output stream type
  typedef std::basic_ostream<char_type> stream_type;

  //! Constructor
  BasicFancyTextOStreamBackend();

  //! Destructor
  ~BasicFancyTextOStreamBackend();

  //! The method adds a basic backend formattering operation
  template<typename FunctionPtr>
  void addBasicDynamicFormattingOp( FunctionPtr op );

  //! The method adds a backend formatting operation
  template<typename FunctionPtr>
  void addDynamicFormattingOp( FunctionPtr op, const std::string& keyword );

  //! The method adds a new stream to the sink
  void add_stream( const boost::shared_ptr<stream_type>& os );

  //! The method removes a stream from the sink
  void remove_stream( const boost::shared_ptr<stream_type>& os );

  //! Set the flag to automatically flush buffers of all attached streams after each log record
  void auto_flush( const bool auto_flush_buffers = true );

  //! The method writes the message to the sink
  void consume( const boost::log::record_view& record,
                const string_type& formatted_message );

  //! The method flushes the associated streams
  void flush();

private:

  // Type of function pointer that will handle dynamic formatting
  typedef std::function<void(Utility::DynamicOutputFormatter&)> DynamicFormattingFunction;

  // Add a dynamic formatting function
  void addDynamicFormattingFunction( const DynamicFormattingFunction& func );

  struct Implementation;
  Implementation* d_impl;
};

// The method adds a basic backend formattering operation
template<typename CharT>
template<typename FunctionPtr>
inline void BasicFancyTextOStreamBackend<CharT>::addBasicDynamicFormattingOp(
                                                               FunctionPtr op )
{
  DynamicFormattingFunction new_formatting_op =
    std::bind<void>( op, std::placeholders::_1 );

  this->addDynamicFormattingFunction( new_formatting_op );
}

// The method adds a dynamic formatting operation
template<typename CharT>
template<typename FunctionPtr>
inline void BasicFancyTextOStreamBackend<CharT>::addDynamicFormattingOp(
                                   FunctionPtr op, const std::string& keyword )
{
  DynamicFormattingFunction new_formatting_op = 
    std::bind<void>( op, std::placeholders::_1, keyword );

  this->addDynamicFormattingFunction( new_formatting_op );
}

#ifdef BOOST_LOG_USE_CHAR
typedef BasicFancyTextOStreamBackend<char> FancyTextOStreamBackend;
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef BasicFancyTextOStreamBackend<wchar_t> WFancyTextOStreamBackend;
#endif
  
} // end Utility namespace

#endif // end UTILITY_FANCY_TEXT_OSTREAM_BACKEND_HPP

//---------------------------------------------------------------------------//
// end Utility_FancyTextOStreamBackend.hpp
//---------------------------------------------------------------------------//
