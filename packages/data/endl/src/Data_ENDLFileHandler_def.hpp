//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDLFileHandler_def.hpp
//! \author Luke Kersting
//! \brief  Evaluate Nuclear Data Library file handler class template def.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDL_FILE_HANDLER_DEF_HPP
#define DATA_ENDL_FILE_HANDLER_DEF_HPP

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Data_ENDLFileHandler.hpp"
#include "Data_ENDLHelperWrappers.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{
// Map two column subshell data table in EADL file
template< typename T >
void ENDLFileHandler::mapTwoColumnSubshellData(
    std::vector<unsigned>& subshells,
    std::map<unsigned,T>& subshell_data )
{
  std::vector<double> column_one, column_two;
  processTwoColumnTable( column_one, column_two );

  // convert eadl subshell typ to endf subshell type
  subshells.resize( column_one.size() );
  for ( int i = 0; i < column_one.size(); ++i )
  {
    unsigned shell = convertEADLDesignatorToENDFDesignator( column_one[i] );
    subshells[i] = shell;

    T shell_data = column_two[i];
    subshell_data.emplace( shell, shell_data );
  }

  testPostcondition( !subshells.empty() );
  testPostcondition( !subshell_data.empty() );
}

// Process two column table in ENDL file
template< typename T, typename P >
void ENDLFileHandler::mapTwoColumnTable(
    std::vector<T>& bin,
    std::map<T,P>& bin_data,
    bool convert_subshell )
{
  int io_flag, table_size;

  std::vector<double> column_one, column_two;
  processTwoColumnTable( column_one, column_two );

  // Resize and clear arrays to table size
  bin.resize( column_one.size() );
  bin_data.clear();

  T data_bin;

  // Loop through the data points
  for ( int i = 0; i < column_one.size(); ++i )
  {
    // start the new distribution
    if ( convert_subshell )
    {
      data_bin =
        Data::convertEADLDesignatorToENDFDesignator( column_one[i] );
    }
    else
    {
      data_bin = column_one[i];
    }

    bin[i] = data_bin;
    bin_data.emplace( data_bin, column_two[i] );
  }

  testPostcondition( !bin_data.empty() );
  testPostcondition( !bin.empty() );
}

// Map three column table in ENDL file
template< typename T, typename P >
void ENDLFileHandler::mapThreeColumnTable(
    std::vector<T>& bin,
    std::map<T,P>& indep_variable,
    std::map<T,P>& dep_variable,
    bool convert_subshell )
{

  int io_flag, table_size;

  std::vector<double> column_one, column_two, column_three;

  processThreeColumnTable( column_one, column_two, column_three );

  // Resize and clear arrays to table size
  bin.resize( column_one.size() );
  indep_variable.clear();
  dep_variable.clear();

  // Process the table data
  T bin_data_point;

  // Loop through the data points
  for ( int i = 0; i < column_one.size(); ++i )
  {
    if ( convert_subshell )
    {
      bin_data_point =
        Data::convertEADLDesignatorToENDFDesignator( column_one[i] );
    }
    else
    {
      bin_data_point = column_one[i];
    }

    // bin vectors
    bin[i] = bin_data_point;

    // map<bin,data>
    indep_variable.emplace( bin_data_point, column_two[i] );
    dep_variable.emplace( bin_data_point, column_three[i] );
  }

  testPostcondition( !indep_variable.empty() );
  testPostcondition( !dep_variable.empty() );
  testPostcondition( !bin.empty() );
}

// Map three column table in ENDL file
template< typename T, typename P >
void ENDLFileHandler::mapThreeColumnTable(
    std::vector<T>& bins,
    std::map<T,std::vector<P> >& indep_variable,
    std::map<T,std::vector<P> >& dep_variable,
    bool convert_subshell )
{
  int io_flag, table_size;

  std::vector<double> column_one, column_two, column_three;

  processThreeColumnTable( column_one, column_two, column_three );

  // Clear arrays
  bins.clear();
  indep_variable.clear();
  dep_variable.clear();

  // Process the table data
  std::pair<T,std::vector<P> > indep, dep;

  // Assign energy of first data point
  T data_bin;
  if ( convert_subshell )
  {
    data_bin =
        Data::convertEADLDesignatorToENDFDesignator( column_one.front() );
  }
  else
  {
    data_bin = column_one.front();
  }
  bins.push_back( data_bin );
  indep.first = data_bin;
  dep.first = data_bin;

  // insert first indep and dep data points at that bin
  indep.second.push_back( column_two.front() );
  dep.second.push_back( column_three.front() );

  // Loop through the rest of the data points
  for ( int i = 1; i < column_one.size(); ++i )
  {
    if ( convert_subshell )
    {
      data_bin =
        Data::convertEADLDesignatorToENDFDesignator( column_one[i] );
    }
    else
    {
      data_bin = column_one[i];
    }

    // start a new distribution at next bin
    if ( data_bin != bins.back() )
    {
      // insert old distribution
      indep_variable.insert( indep );
      dep_variable.insert( dep );

      // clear indep and dep distributions
      indep.second.clear();
      dep.second.clear();

      // start the new distribution
      bins.push_back( data_bin );
      indep.first = data_bin;
      dep.first = data_bin;
      indep.second.push_back( column_two[i] );
      dep.second.push_back( column_three[i] );
    }
    // Continue inserting indep and dep variables for this energy bin
    else
    {
      indep.second.push_back( column_two[i] );
      dep.second.push_back( column_three[i] );
    }
  }

  // insert last distribution
  indep_variable.insert( indep );
  dep_variable.insert( dep );

  testPostcondition( !indep_variable.empty() );
  testPostcondition( !dep_variable.empty() );
  testPostcondition( !bins.empty() );
}

// Map four column table in ENDL file
template< typename T, typename P, typename Q >
void ENDLFileHandler::mapFourColumnTable(
    std::vector<T>& bin,
    std::map<T,std::vector<P> >& secondary_bin,
    std::map<T,std::map<P,Q> >& indep_variable,
    std::map<T,std::map<P,Q> >& dep_variable,
    bool convert_subshell )
{
  int io_flag, table_size;

  std::vector<double> column_one, column_two, column_three, column_four;

  processFourColumnTable( column_one, column_two, column_three, column_four );

  // Clear arrays to table size
  bin.clear();
  secondary_bin.clear();
  indep_variable.clear();
  dep_variable.clear();

  // Process the table data
  std::vector<P> sec_bin;
  std::map<P,Q> indep_map, dep_map;
  T bin_data_point;
  P secondary_bin_data_point;

  // Process first data point
  if ( convert_subshell )
  {
    bin_data_point =
        Data::convertEADLDesignatorToENDFDesignator( column_one.front() );

    secondary_bin_data_point =
        Data::convertEADLDesignatorToENDFDesignator( column_two.front() );
  }
  else
  {
    bin_data_point = column_one.front();
    secondary_bin_data_point = column_two.front();
  }
  // bin and secondary bin
  bin.push_back( bin_data_point );
  sec_bin.push_back( secondary_bin_data_point );

  // map<secondary_bin,data>
  indep_map.emplace( secondary_bin_data_point, column_three.front() );
  dep_map.emplace( secondary_bin_data_point, column_four.front() );

  // Loop through the data points
  for ( int i = 1; i < column_one.size(); ++i )
  {
    if ( convert_subshell )
    {
      bin_data_point =
        Data::convertEADLDesignatorToENDFDesignator( column_one[i] );

      secondary_bin_data_point =
        Data::convertEADLDesignatorToENDFDesignator( column_two[i] );
    }
    else
    {
      bin_data_point = column_one[i];
      secondary_bin_data_point = column_two[i];
    }

    // Add bin data to map and start a new map at next bin
    if ( bin_data_point != bin.back() )
    {
      // Add map<secondary_bin,data> to map<bin,map<secondary_bin,data> >
      indep_variable.emplace( bin.back(), indep_map );
      dep_variable.emplace( bin.back(), dep_map );

      // Add pair<bin,secondary_bins> to map<bin,secondary_bins>
      secondary_bin.emplace( bin.back(), sec_bin );

      indep_map.clear();
      dep_map.clear();
      sec_bin.clear();

      // map<secondary_bin,data>
      indep_map.emplace( secondary_bin_data_point, column_three[i] );
      dep_map.emplace( secondary_bin_data_point, column_four[i] );

      // bin and secondary bin
      bin.push_back( bin_data_point );
      sec_bin.push_back( secondary_bin_data_point );
    }
    // Continue to add to the map<secondary_bin,data>
    else
    {
      // map<secondary_bin,data>
      indep_map.emplace( secondary_bin_data_point, column_three[i] );
      dep_map.emplace( secondary_bin_data_point, column_four[i] );
      sec_bin.push_back( secondary_bin_data_point );
    }
  }

  // insert last distribution
  secondary_bin.emplace( bin_data_point, sec_bin );
  indep_variable.emplace( bin_data_point, indep_map );
  dep_variable.emplace( bin_data_point, dep_map );

  testPostcondition( !indep_variable.empty() );
  testPostcondition( !dep_variable.empty() );
  testPostcondition( !bin.empty() );
  testPostcondition( !secondary_bin.empty() );
}

} // end Data namespace

#endif // DATA_ENDL_FILE_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_ENDLFileHandler_def.hpp
//---------------------------------------------------------------------------//
