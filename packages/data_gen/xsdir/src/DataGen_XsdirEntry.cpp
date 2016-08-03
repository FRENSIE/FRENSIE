//---------------------------------------------------------------------------//
//!
//! \file   DataGen_XsdirEntry.cpp
//! \author Alex Robinson
//! \brief  The xsdir entry base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// Boost Includes
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

// FRENSIE Includes
#include "DataGen_XsdirEntry.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Extract zaid from table name
unsigned XsdirEntry::extractZaidFromTableName( const std::string& table_name )
{
  // Make sure the table name is valid
  testPrecondition( table_name.size() > 0 );

  unsigned pos = table_name.find( "." );

  if( table_name.find_first_not_of( "0123456789" ) >= pos )
  {
    std::istringstream iss( table_name.substr( 0, pos ) );

    unsigned zaid;

    iss >> zaid;

    return zaid;
  }
  else
    return 0u;
}

// Extract atomic number from zaid
unsigned XsdirEntry::extractAtomicNumberFromZaid( const unsigned zaid )
{
  return zaid/1000u;
}

// Extract atomic mass number from zaid
unsigned XsdirEntry::extractAtomicMassNumberFromZaid( const unsigned zaid )
{
  return zaid%1000u;
}

// Return the table name
const std::string& XsdirEntry::getTableName() const
{
  return d_table_name;
}

// Return the table type
XsdirEntry::TableType XsdirEntry::getTableType() const
{
  return d_table_type;
}

// Return the table version
unsigned XsdirEntry::getTableVersion() const
{
  return d_table_version;
}

// Return the table file path
const std::string& XsdirEntry::getTableFilePath() const
{
  return d_table_file_path;
}

// Return the table file start line
unsigned XsdirEntry::getTableFileStartLine() const
{
  return d_table_file_start_line;
}

// Return the table length
unsigned XsdirEntry::getTableLength() const
{
  return d_table_length;
}

// Return the table atomic weight ratio
double XsdirEntry::getTableAtomicWeightRatio() const
{
  return d_table_atomic_weight_ratio;
}

// Return the table temperature (MeV)
double XsdirEntry::getTableTemperatureMeV() const
{
  return d_table_temperature;
}

// Return the table temperature (Kelvin)
double XsdirEntry::getTableTemperatureKelvin() const
{
  return d_table_temperature/Utility::PhysicalConstants::boltzmann_constant;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_XsdirEntry.cpp
//---------------------------------------------------------------------------//
