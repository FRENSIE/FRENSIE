//---------------------------------------------------------------------------//
//!
//! \file   Data_NuclideProperties_def.hpp
//! \author Alex Robinson
//! \brief  The nuclide properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_NUCLIDE_PROPERTIES_DEF_HPP
#define DATA_NUCLIDE_PROPERTIES_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Check if there is data available with the desired format, table version, and evaluation temp
template<typename PropertiesMap>
inline bool NuclideProperties::dataAvailable(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Energy evaluation_temp )
{
  return NuclideProperties::dataAvailableImpl( properties,
                                               file_type,
                                               table_version,
                                               [&evaluation_temp]( const typename PropertiesMap::mapped_type::mapped_type::value_type& element ) -> bool
                                               { return Utility::get<0>(element) == evaluation_temp; }
}

// Check if there is data available with the desired format, table version, and evaluation temp
template<typename PropertiesMap>
inline bool NuclideProperties::dataAvailable(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Temperature evaluation_temp )
{
  return NuclideProperties::dataAvailable( properties,
                                           file_type,
                                           table_version,
                                           evaluation_temp*Utility::PhysicalConstants::boltzmann_constant_q );
}

// Check if there is data available with the desired format, table version, and evaluation temp comparison function
template<typename PropertiesMap, typename EvaluationTempCompFunc>
inline bool NuclideProperties::dataAvailableImpl(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const EvaluationTempCompFunc temp_comp_func )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( file_type );

  if( properties_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      properties_it->find( table_version );
    
    if( version_it != properties_it->end() )
    {
      const typename PropertiesMap::mapped_type::mapped_type& temp_grid =
        version_it->second;

      typename PropertiesMap::mapped_type::mapped_type::const_iterator
        temp_grid_it = std::find_if( temp_grid.begin(),
                                     temp_grid.end(),
                                     temp_comp_func );

      return temp_grid_it != temp_grid.end();
    }
  }

  return false;
}

// Check if there is data available with the desired format
template<typename PropertiesMap>
bool NuclideProperties::dataAvailable( const PropertiesMap& properties,
                                       const std::string& name )
{
  return properties.find( name ) != properties.end();
}

// Check if there is data available with the desired name and format
template<typename PropertiesMap>
bool NuclideProperties::dataAvailable(
                const PropertiesMap& properties,
                const std::string& name,
                const typename PropertiesMap::mapped_type::key_type file_type )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
    return AtomProperties::dataAvailable( properties_it->second, file_type );
  else
    return false;
}

// Check if there is data available with the desired name, format and table version
template<typename PropertiesMap>
bool NuclideProperties::dataAvailable(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
  {
    return AtomProperties::dataAvailable( properties_it->second,
                                          file_type,
                                          table_version );
  }
  else
    return false;
}

// Check if there is data available with the desired name, format and table version, and evaluation temp
template<typename PropertiesMap>
bool NuclideProperties::dataAvailable(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Energy evaluation_temp )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
  {
    return NuclideProperties::dataAvailable( properties_it->second,
                                             file_type,
                                             table_version,
                                             evaluation_temp );
  }
  else
    return false;
}

// Check if there is data available with the desired name, format and table version, and evaluation temp key
template<typename PropertiesMap>
bool NuclideProperties::dataAvailable(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Temperature evaluation_temp )
{
  return NuclideProperties::dataAvailable( properties,
                                           name,
                                           file_type,
                                           table_version,
                                           evaluation_temp*Utility::PhysicalConstants::boltzmann_constant_q );
}

// Get the max data file version
template<typename PropertiesMap>
unsigned NuclideProperties::getMaxDataFileVersion(
                              const PropertiesMap& properties,
                              const std::string& name,
                              const typename PropertiesMap::key_type file_type,
                              const std::string& type_name )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
  {
    return NuclideProperties::getMaxDataFileVersion( properties_it->second,
                                                     file_type,
                                                     name + " " + type_name );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     type_name << " data properties for " << name <<
                     " with file type " << file_type << " do not have a "
                     "recommended version!" );
  }
}

// Get the data file types
template<typename PropertiesMap>
std::set<typename PropertiesMap::mapped_type::key_type>
NuclideProperties::getDataFileTypes( const PropertiesMap& properties,
                                     const std::string& name )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
    return AtomProperties::getDataFileTypes( properties_it->second );
  else
    return std::set<typename PropertiesMap::mapped_type::key_type>();
}

// Get the data file versions
template<typename PropertiesMap>
std::set<unsigned> NuclideProperties::getDataFileVersions(
                const PropertiesMap& properties,
                const std::string& name,
                const typename PropertiesMap::mapped_type::key_type file_type )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
  {
    return AtomProperties::getDataFileTypes( properties_it->second, file_type );
  }
  else
    return std::set<unsigned>();
}

// Get the data file names
template<typename PropertiesMap>
std::set<std::string> NuclideProperties::getThermalNuclearDataNames(
                                              const PropertiesMap& properties )
{
  std::set<std::string> data_names;
  
  typename PropertiesMap::const_iterator properties_it = properties.begin();

  while( properties_it != properties.end() )
  {
    data_names.insert( properties_it->first );
    
    ++properties_it;
  }

  return data_names;
}

// Get the data evaluation temps
template<typename PropertiesMap>
std::vector<Energy> NuclideProperties::getDataEvaluationTempsInMeV(
                                       const PropertiesMap& properties,
                                       const PropertiesMap::key_type file_type,
                                       const unsigned table_version )
{
  std::vector<Energy> evaluation_temps;

  typename PropertiesMap::const_iterator file_type_it =
    properties.find( file_type );

  if( file_type_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      file_type_it->find( table_version );

    if( version_it != file_type_it->end() )
    {
      const typename PropertiesMap::mapped_type::mapped_type& temp_grid =
        version_it->second;

      evaluation_temps.resize( temp_grid.size() );
      
      for( size_t i = 0; i < temp_grid.size(); ++i )
        evaluation_temps[i] = Utility::get<0>( temp_grid[i] );
    }
  }

  return evaluation_temps;
}

// Get the data evaluation temps
template<typename PropertiesMap>
std::vector<Energy> NuclideProperties::getDataEvaluationTempsInMeV(
                          const PropertiesMap& properties,
                          const std::string& name,
                          const PropertiesMap::mapped_type::key_type file_type,
                          const unsigned table_version )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
  {
    return NuclideProperties::getDataEvaluationTempsInMeV( properties_it->second,
                                                           file_type,
                                                           table_version );
  }
  else
    return std::vector<Energy>();
}

// Get the data evaluation temps
template<typename PropertiesMap>
std::vector<Temperature> NuclideProperties::getDataEvaluationTemps(
                                       const PropertiesMap& properties,
                                       const PropertiesMap::key_type file_type,
                                       const unsigned table_version )
{
  std::vector<Energy> evaluation_temps_in_mev =
    NuclideProperties::getDataEvaluationTempsInMeV( properties,
                                                    file_type,
                                                    table_version );

  std::vector<Temperature> evaluation_temps( evaluation_temps_in_mev );

  for( size_t i = 0; i < evaluation_temps_in_mev.size(); ++i )
  {
    evaluation_temps[i] =
      evaluation_temps[i]/Utility::PhysicalConstants::boltzmann_constant_q;
  }

  return evaluation_temps;
}

// Get the data evaluation temps
template<typename PropertiesMap>
std::vector<Temperature> NuclideProperties::getDataEvaluationTemps(
                          const PropertiesMap& properties,
                          const std::string& name,
                          const PropertiesMap::mapped_type::key_type file_type,
                          const unsigned table_version )
{
  typename PropertiesMap::const_iterator properties_it =
    properties.find( name );

  if( properties_it != properties.end() )
  {
    return NuclideProperties::getDataEvaluationTemps( properties_it->second,
                                                      file_type,
                                                      table_version );
  }
  else
    return std::vector<Temperature>();
}

// Get the data properties
template<typename Properties, typename PropertiesMap>
const Properties& NuclideProperties::getProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Energy evaluation_temp,
                              const bool find_exact,
                              const std::string& type_name )
{
  typename PropertiesMap::const_iterator file_type_it =
    properties.find( file_type );

  if( file_type_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      file_type_it->find( table_version );

    if( version_it != file_type_it->end() )
    {
      const typename PropertiesMap::mapped_type::mapped_type& temp_grid =
        version_it->second;

      typename PropertiesMap::mapped_type::mapped_type::const_iterator
        temp_grid_it;

      if( evaluation_temp < Utility::get<0>(temp_grid.front()) )
        temp_grid_it = temp_grid.begin();
      else if( evaluation_temp >= Utility::get<0>(temp_grid.back()) )
      {
        temp_grid_it = temp_grid.end();
        --temp_grid_it;
      }
      else
      {
        temp_grid_it =
          Utility::Search::binaryLowerBound<0>( temp_grid.begin(),
                                                temp_grid.end(),
                                                evaluation_temp );
      }

      // Check if there are suitable properties available
      if( Utility::get<0>(*properties_it) != evaluation_temp )
      {
        if( find_exact )
        {
          THROW_EXCEPTION( std::runtime_error,
                           type_name << " data properties with file type "
                           << file_type << ", version " << table_version <<
                           " and evaluation temp " << evaluation_temp <<
                           " do not exist!" );
        }
        else
        {
          // Check if we have the closest evaluation temp
          if( std::distance( properties_it, temp_grid.end() ) > 1 )
          {
            decltype(properties_it) next_properties_it = properties_it;
            ++next_properties_it;

            Energy mid_temp =
              (Utility::get<0>(*properties_it) + Utility::get<0>(*next_properties_it))/2.0;

            if( evaluation_temp >= mid_temp )
              ++properties_it;
          }

          FRENSIE_LOG_TAGGED_WARNING( "NuclideProperties",
                                      type_name << " data properties with "
                                      "file type " << file_type <<
                                      ", version " << table_version <<
                                      " and evaluation temp "
                                      << evaluation_temp << " do not exist! "
                                      "Data for the closes evaluation temp ("
                                      << Utility::get<0>(*properties_it) <<
                                      ") will be returned!" );
        }
      }

      return *Utility::get<2>(*properties_it);
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       type_name << " data properties with file type "
                       << file_type << " and version " << table_version <<
                       " do not exist!" );
    }
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     type_name << " data properties with file type "
                     << file_type << " do not exist!" );
  }
}

// Get the data properties
template<typename Properties, typename PropertiesMap>
const Properties& NuclideProperties::getProperties(
                              const PropertiesMap& properties,
                              const typename PropertiesMap::key_type file_type,
                              const unsigned table_version,
                              const Temperature evaluation_temp,
                              const bool find_exact,
                              const std::string& type_name )
{
  return NuclideProperties::getProperties( properties,
                                           file_type,
                                           table_version,
                                           evaluation_temp*Utility::PhysicalConstants::boltzmann_constant_q,
                                           find_exact,
                                           type_name );
}

// Get the data properties
template<typename Properties, typename PropertiesMap>
inline const Properties& NuclideProperties::getProperties(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Energy evaluation_temp,
                 const bool find_exact,
                 const std::string& type_name )
{
  typename PropertiesMap::const_iterator name_it =
    properties.find( name );

  if( name_it != properties.end() )
  {
    return NuclideProperties::getProperties( name_it->second,
                                             file_type,
                                             table_version,
                                             evaluation_temp,
                                             find_exact,
                                             name + " " + type_name );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     type_name << " data properties with name " << name << 
                     " do not exist!" );
  }
}

// Get the data properties
template<typename Properties, typename PropertiesMap>
inline const Properties& NuclideProperties::getProperties(
                 const PropertiesMap& properties,
                 const std::string& name,
                 const typename PropertiesMap::mapped_type::key_type file_type,
                 const unsigned table_version,
                 const Temperature evaluation_temp,
                 const bool find_exact,
                 const std::string& type_name )
{
  return NuclideProperties::getProperties( properties,
                                           name,
                                           file_type,
                                           table_version,
                                           evaluation_temp*Utility::PhysicalConstants::boltzmann_constant_q,
                                           find_exact,
                                           type_name );
}

// Set the nuclear properties
template<typename Properties, typename PropertiesMap>
void NuclideProperties::setNuclearProperties(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const std::string& type_name )
{
  if( new_properties.get() )
  {
    Energy evaluation_temp = new_properties->evaluationTemperatureInMeV();
    
    PropertiesMap::mapped_type::mapped_type& temp_grid = 
      properties[new_properties->fileType()][new_properties->fileVersion()];

    if( temp_grid.empty() )
      temp_grid.push_back( std::make_pair( evaluation_temp, new_properties ) );
    else
    {
      PropertiesMap::mapped_type::mapped_type::iterator temp_grid_it;
    
      if( evaluation_temp > Utility::get<0>(temp_grid.back()) )
        temp_grid_it = temp_grid.end();
      else
      {
        temp_grid_it =
          Utility::Search::binaryUpperBound<0>( temp_grid.begin(),
                                                temp_grid.end(),
                                                evaluation_temp );
      }
      
      if( temp_grid_it != temp_grid.end() )
      {
        if( Utility::get<0>( *temp_grid_it ) == evaluation_temp )
        {
          FRENSIE_LOG_TAGGED_WARNING( "NuclideProperties",
                                      type_name << " data properties with "
                                      "file type "
                                      << new_properties->fileType() <<
                                      ", version "
                                      << new_properties->fileVersion() <<
                                      " and evaluation temperature "
                                      << evaluation_temp << 
                                      " are already present! The old "
                                      "properties will be overwritten." );

          Utility::get<1>( *temp_grid_it ) = new_properties;
        }
        else
        {
          temp_grid.insert( temp_grid_it,
                            std::make_pair(evaluation_temp, new_properties) );
        }
      }
      else
      {
        temp_grid.insert( temp_grid_it,
                          std::make_pair(evaluation_temp, new_properties) );
      }
    }
  }
}

// Set the thermal nuclear properties
template<typename Properties, typename PropertiesMap>
void NuclideProperties::setThermalNuclearProperties(
                       PropertiesMap& properties,
                       const std::shared_ptr<const Properties>& new_properties,
                       const std::string& type_name )
{
  if( new_properties.get() )
  {
    NuclideProperties::setNuclearProperties(
                                      properties[new_properties->name()],
                                      new_properties,
                                      new_properties->name() + " " type_name );
  }
}

// Clone the nuclear properties map
template<typename PropertiesMap>
void NuclideProperties::cloneNuclearProperties(
                                      const PropertiesMap& original_properties,
                                      PropertiesMap& new_properties )
{
  new_properties.clear();

  typename PropertiesMap::const_iterator properties_it =
    original_properties.begin();

  while( properties_it != original_properties.end() )
  {
    typename PropertiesMap::mapped_type& new_properties_map =
      new_properties[properties_it->first];

    typename PropertiesMap::mapped_type::const_iterator version_it =
      properties_it->begin();

    while( version_it != properties_it->end() )
    {
      typename PropertiesMap::mapped_type::mapped_type& new_temp_grid =
        new_properties_map[version_it->first];

      new_temp_grid.resize( version_it->second.size() );

      for( size_t i = 0; i < new_temp_grid.size(); ++i )
      {
        Utility::get<0>( new_temp_grid[i] ) =
          Utility::get<0>( version_it->second[i] );

        Utility::get<0>( new_temp_grid[i] ) =
          Utility::get<0>( version_it->second[i] );

        Utility::get<1>( new_temp_grid[i] ).reset(
                            Utility::get<1>( version_it->second[i] ).clone() );
      }

      ++version_it;
    }

    ++properties_it;
  }
}

// Clone the thermal nuclear properties map
template<typename PropertiesMap>
void NuclideProperties::cloneThermalNuclearProperties(
                                      const PropertiesMap& original_properties,
                                      PropertiesMap& new_properties )
{
  new_properties.clear();

  typename PropertiesMap::const_iterator name_it =
    original_properties.begin();

  while( name_it != original_properties.end() )
  {
    NuclideProperties::cloneNuclearProperties( name_it->second,
                                               new_properties[name_it->first] );
    ++name_it;
  }
}

// Print nuclear properties
template<typename PropertiesMap>
void NuclideProperties::printNuclearProperties(
                                               const PropertiesMap& properties,
                                               const std::string& type_name,
                                               const bool extra_indent,
                                               std::ostream& os )
{
  std::string indent( "  " );

  if( extra_indent )
    indent += "  ";

  os << indent << type_name << ":\n";

  indent += "  ";

  typename PropertiesMap::const_iterator file_type_it = properties.begin();

  while( file_type_it != properties.end() )
  {
    typename PropertiesMap::mapped_type::const_iterator version_it =
      file_type_it->second.begin();
    
    while( version_it != file_type_it->second.end() )
    {
      typename PropertiesMap::mapped_type::mapped_type::const_iterator
        temp_grid_it = version_it->second.begin();

      while( temp_grid_it != version_it->second.end() )
      {
        os << indent << file_type_it->first << " version " << version_it->first
           << " @ " << Utility::get<0>( *temp_grid_it )
           << " (" << Utility::get<1>( *temp_grid_it )->tableName() << "): "
           << Utility::get<1>( *temp_grid_it )->filePath().string() << "\n";
        
        ++temp_grid_it;
      }
      
      ++version_it;
    }
    
    ++file_type_it;
  }
}

// Print thermal nuclear properties
template<typename PropertiesMap>
void NuclideProperties::printThermalNuclearProperties(
                                               const PropertiesMap& properties,
                                               const std::string& type_name,
                                               std::ostream& os )
{
  os << "  " << type_name << ":\n";

  typename PropertiesMap::const_iterator name_it = properties.begin();

  while( name_it != properties.end() )
  {
    NuclideProperties::printNuclearProperties( name_it->second,
                                               name_it->first,
                                               true,
                                               os );
    
    ++name_it;
  }
}

} // end Data namespace

#endif // end DATA_NUCLIDE_PROPERTIES_DEF_HPP 

//---------------------------------------------------------------------------//
// end Data_NuclideProperties_def.hpp
//---------------------------------------------------------------------------//
