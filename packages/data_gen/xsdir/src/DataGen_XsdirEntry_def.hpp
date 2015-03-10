//---------------------------------------------------------------------------//
//!
//! \file   DataGen_XsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The xsdir entry base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_XSDIR_ENTRY_DEF_HPP
#define DATA_GEN_XSDIR_ENTRY_DEF_HPP

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace DataGen{

// Extract the xsdir entry tokens from the xsdir line
template<typename STLCompliantContainer>
unsigned XsdirEntry::extractTableTokensFromXsdirLine(
                                          const std::string& xsdir_line,
					  STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );

  entry_tokens.clear();

    std::string xsdir_line_copy = xsdir_line;
 
    boost::trim( xsdir_line_copy );

    boost::split( entry_tokens, 
		  xsdir_line_copy, 
		  boost::is_any_of( " " ), 
		  boost::algorithm::token_compress_on );
}

// Check if the line is a table entry
template<typename STLCompliantContainer>
bool XsdirEntry::isLineTableEntry( 
				 const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  
  return entry_tokens.size() > 0 && 
    entry_tokens.front().find( "." ) <
    entry_tokens.front().size();
}

// Check if the table type is supported
template<typename STLCompliantContainer>
bool XsdirEntry::isTableTypeSupported(
				 const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( XsdirEntry::isLineTableEntry( entry_tokens ) );

  TableType type = extractTableTypeFromEntryTokens( entry_tokens );

  return type != UNSUPPORTED_TABLE;
}

// Extract the table version from the entry tokens
template<typename STLCompliantContainer>
unsigned XsdirEntry::extractTableVersionFromEntryTokens( 
			        const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( XsdirEntry::isLineTableEntry( entry_tokens ) );

  unsigned start_pos = entry_tokens.front().find( "." );
  
  std::istringstream iss( entry_tokens.front().substr( start_pos+1, 2 ) );

  unsigned version;

  iss >> version;

  return version;
}
  
// Extract the table type from the entry tokens 
template<typename STLCompliantContainer>
XsdirEntry::TableType XsdirEntry::extractTableTypeFromEntryTokens(
				const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( isLineTableEntry( entry_tokens ) );

  if( entry_tokens[4] == "1" )
  {
    if( entry_tokens.front().find_last_of( "c" ) == 
	entry_tokens.front().size()-1 )
      return CONTINUOUS_ENERGY_NEUTRON_TABLE;
    if( entry_tokens.front().find_last_of( "t" ) == 
	entry_tokens.front().size()-1 )
      return S_ALPHA_BETA_TABLE;
    else if( entry_tokens.front().find( "12p" ) < entry_tokens.front().size() )
      return ELECTRON_PHOTON_RELAXATION_TABLE;
    else if( entry_tokens.front().find_last_of( "u" ) == 
	     entry_tokens.front().size()-1 )
      return PHOTONUCLEAR_TABLE;
    else
      return UNSUPPORTED_TABLE;
  }
  else
    return UNSUPPORTED_TABLE;
}

// Extract the file path from the entry tokens
template<typename STLCompliantContainer>
std::string XsdirEntry::extractFilePathFromEntryTokens(
			        const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( isLineTableEntry( entry_tokens ) );

  std::string file_path;

  if( entry_tokens[3] != "0" )
  {
    file_path = entry_tokens[3];
    file_path += "/";
  }

  file_path += entry_tokens[2];

  return file_path;
}

// Extract the file start line from the entry tokens
template<typename STLCompliantContainer>
unsigned XsdirEntry::extractFileStartLineFromEntryTokens(
				const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( isLineTableEntry( entry_tokens ) );

  std::istringstream iss( entry_tokens[5] );

  unsigned start;

  iss >> start;

  return start;
}

// Extract the table length from the entry tokens
template<typename STLCompliantContainer>
unsigned XsdirEntry::extractTableLengthFromEntryTokens(
				const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( isLineTableEntry( entry_tokens ) );

  std::istringstream iss( entry_tokens[6] );

  unsigned length;

  iss >> length;

  return length;
}

// Extract the table atomic weight ratio from the entry tokens
template<typename STLCompliantContainer>
double XsdirEntry::extractTableAtomicWeightRatioFromEntryTokens(
				 const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( isLineTableEntry( entry_tokens ) );

  std::istringstream iss( entry_tokens[1] );
  
  double atomic_weight_ratio;

  iss >> atomic_weight_ratio;

  return atomic_weight_ratio;
}

// Extract the table temperature (MeV) from the entry tokens
template<typename STLCompliantContainer>
double XsdirEntry::extractTableTemperatureFromEntryTokens(
				 const STLCompliantContainer& entry_tokens )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( isLineTableEntry( entry_tokens ) );

  if( entry_tokens.size() > 7 )
  {
    std::istringstream iss( entry_tokens[9] );
    
    double temperature;
    
    iss >> temperature;
    
    return temperature;
  }
  else
    return 0.0;
}

// Constructor
template<typename STLCompliantContainer>
XsdirEntry::XsdirEntry( const STLCompliantContainer& entry_tokens )
  : d_table_name( entry_tokens[0] )
{
  // Make sure the value type is a string
  testStaticPrecondition( (boost::is_same<typename STLCompliantContainer::value_type,std::string>::value) );
  // Make sure the line is a table entry
  testPrecondition( isLineTableEntry( entry_tokens ) );
  // Make sure the table type is supported
  testPrecondition( isTableTypeSupported( entry_tokens ) );

  d_table_type = extractTableTypeFromEntryTokens( entry_tokens );
  d_table_version = extractTableVersionFromEntryTokens( entry_tokens );
  d_table_file_path = extractFilePathFromEntryTokens( entry_tokens );
  d_table_file_start_line = extractFileStartLineFromEntryTokens( entry_tokens);
  d_table_length = extractTableLengthFromEntryTokens( entry_tokens );
  d_table_atomic_weight_ratio = extractTableAtomicWeightRatioFromEntryTokens(
								entry_tokens );
  d_table_temperature = extractTableTemperatureFromEntryTokens( entry_tokens );
}

} // end DataGen namespace

#endif // end DATA_GEN_XSDIR_ENTRY_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_XsdirEntry_def.hpp
//---------------------------------------------------------------------------//
