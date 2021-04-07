//---------------------------------------------------------------------------//
//!
//! \file   Utility_ParameterListHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Parameter list helper function definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PARAMETER_LIST_HELPERS_DEF_HPP
#define UTILITY_PARAMETER_LIST_HELPERS_DEF_HPP

// Std Lib Includes
#include <sstream>

// Boost Includes
#include <boost/algorithm/string.hpp>

namespace Utility{

// Get the unused parameter warning messages (if any)
/*! \details Ideally, the warning message that have been extracted will be
 * logged with the FRENSIE_LOG_WARNING macro (or another similar macro).
 */
template<template<typename,typename...> class Array>
void getUnusedParameterWarningMessages(
                                  const Teuchos::ParameterList& parameter_list,
                                  Array<std::string>& warning_messages )
{
  std::ostringstream oss;

  parameter_list.unused( oss );
  
  if( oss.str().size() > 0 )
  {
    std::vector<std::string> raw_warning_messages;
    std::string raw_warning_string = oss.str();
    
    boost::algorithm::split( raw_warning_messages,
                             raw_warning_string,
                             boost::algorithm::is_any_of( "\n" ),
                             boost::algorithm::token_compress_on );

    for( size_t i = 0; i < raw_warning_messages.size(); ++i )
    {
      if( raw_warning_messages[i].size() > 0 )
      {
        const size_t warning_start = raw_warning_messages[i].find( ":" ) + 2;

        warning_messages.push_back(
                             raw_warning_messages[i].substr( warning_start ) );
      }
    }
  }
}

} // end Utility namespace

#endif // end UTILITY_PARAMETER_LIST_HELPERS_DEF_HPP
