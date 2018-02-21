//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesDatabase.cpp
//! \author Alex Robinson
//! \brief  The scattering center properties database definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <fstream>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_PolymorphicHDF5OArchive.hpp"
#include "Utility_PolymorphicHDF5IArchive.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Initialize static member data
const std::string ScatteringCenterPropertiesDatabase::s_archive_name( "database" );

// Default constructor
ScatteringCenterPropertiesDatabase::ScatteringCenterPropertiesDatabase()
{ /* ... */ }

// Load existing database constructor
ScatteringCenterPropertiesDatabase::ScatteringCenterPropertiesDatabase(
                       const boost::filesystem::path& database_name_with_path )
{
  this->loadFromFile( database_name_with_path );
}

// The database name used in an archive
const char* ScatteringCenterPropertiesDatabase::getArchiveName() const
{
  return s_archive_name.c_str();
}

// Check if properties with the name of interest exist
bool ScatteringCenterPropertiesDatabase::doPropertiesExist( const AtomType atom )
{
  return this->doPropertiesExist( Data::ZAID(atom) );
}

// Check if properties with zaid exist
bool ScatteringCenterPropertiesDatabase::doPropertiesExist(
                                                        const Data::ZAID zaid )
{
  if( d_properties.find( zaid ) != d_properties.end() )
    return true;
  else
    return false;
}

// Add scattering center properties to the database
void ScatteringCenterPropertiesDatabase::addProperties(
                                             const AtomProperties& properties )
{
  if( d_properties.find( properties.zaid() ) != d_properties.end() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterPropertiesDatabase",
                                "Properties with zaid "
                                << properties.zaid() << " already exist! "
                                "The existing properties will be "
                                "overwritten." );
  }

  d_properties[properties.zaid()].reset( properties.clone() );
}

// Return the desired properties
/*! \details If the atom properties do not exist an exception will be
 * thrown.
 */
const AtomProperties& ScatteringCenterPropertiesDatabase::getAtomProperties(
                                                    const AtomType atom ) const
{
  return this->getAtomProperties( Data::ZAID(atom) );
}

// Return the desired properties
/*! If the atom properties do not exist an exception will be
 * thrown.
 */
AtomProperties& ScatteringCenterPropertiesDatabase::getAtomProperties(
                                                          const AtomType atom )
{
  return this->getAtomProperties( Data::ZAID(atom) );
}

// Return the desired properties
/*! If the atom properties do not exist an exception will be
 * thrown.
 */
const AtomProperties& ScatteringCenterPropertiesDatabase::getAtomProperties(
                                                  const Data::ZAID zaid ) const
{
  ScatteringCenterZaidPropertiesMap::const_iterator properties_it = 
    d_properties.find( zaid );
  
  if( properties_it != d_properties.end() )
    return *properties_it->second;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There are no atom properties associated "
                     "with zaid " << zaid << " in the database!" );
  }
}

// Return the desired properties
/*! If the atom properties do not exist an exception will be
 * thrown.
 */
AtomProperties& ScatteringCenterPropertiesDatabase::getAtomProperties(
                                                        const Data::ZAID zaid )
{
  ScatteringCenterZaidPropertiesMap::iterator properties_it = 
    d_properties.find( zaid );

  if( properties_it != d_properties.end() )
    return *properties_it->second;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There are no atom properties associated "
                     "with zaid " << zaid << " in the database!" );
  }
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabase::initializeAtomProperties(
                                             const AtomType atom,
                                             const double atomic_weight_ratio )
{
  return this->initializeAtomProperties( Data::ZAID(atom),
                                         atomic_weight_ratio );
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabase::initializeAtomProperties(
                             const AtomType atom,
                             const AtomProperties::AtomicWeight atomic_weight )
{
  return this->initializeAtomProperties( Data::ZAID(atom),
                                         atomic_weight );
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabase::initializeAtomProperties(
                                             const Data::ZAID zaid,
                                             const double atomic_weight_ratio )
{
  return this->initializeAtomPropertiesImpl( zaid, atomic_weight_ratio );
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabase::initializeAtomProperties(
                             const Data::ZAID zaid,
                             const AtomProperties::AtomicWeight atomic_weight )
{
  return this->initializeAtomPropertiesImpl( zaid, atomic_weight );
}

// Return the desired properties
/*! If the nuclide properties do not exist or the zaid corresponds to 
 * atom properties and not nuclide properties an exception will be
 * thrown.
 */
const NuclideProperties& ScatteringCenterPropertiesDatabase::getNuclideProperties(
                                                  const Data::ZAID zaid ) const
{
  const AtomProperties& properties = this->getAtomProperties( zaid );

  if( properties.isNuclide() )
    return dynamic_cast<const NuclideProperties&>( properties );
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There properties associated with zaid " << zaid <<
                     " are not nuclide properties!" );
  }
}

// Return the desired properties
/*! If the nuclide properties do not exist or the zaid corresponds to 
 * atom properties and not nuclide properties an exception will be
 * thrown.
 */
NuclideProperties& ScatteringCenterPropertiesDatabase::getNuclideProperties(
                                                        const Data::ZAID zaid )
{
  AtomProperties& properties = this->getAtomProperties( zaid );

  if( properties.isNuclide() )
    return dynamic_cast<NuclideProperties&>( properties );
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There properties associated with zaid " << zaid <<
                     " are not nuclide properties!" );
  }
}

// Initialize the nuclide properties
/*! \details If the nuclide properties already exist, the existing properties
 * will be returned. When initializing new nuclide properties atom properties
 * associated with the nuclide will be copied. To take advantage of this 
 * feature, atom properties should be set before setting any nuclide
 * properties.
 */
NuclideProperties& ScatteringCenterPropertiesDatabase::initializeNuclideProperties(
                                             const Data::ZAID zaid,
                                             const double atomic_weight_ratio )
{
  if( d_properties.find( zaid ) != d_properties.end() )
  {
    FRENSIE_LOG_TAGGED_WARNING( "ScatteringCenterPropertiesDatabase",
                                "Properties with zaid "
                                << zaid << " already exist! "
                                "The existing properties will be "
                                "returned." );

    return this->getNuclideProperties( zaid );
  }
  else
  {
    std::unique_ptr<AtomProperties>& properties = d_properties[zaid];

    // Check if the atom properties have been set
    ScatteringCenterZaidPropertiesMap::iterator properties_it =
      d_properties.find( Data::ZAID(zaid.atom()) );
    
    if( properties_it != d_properties.end() )
    {
      properties.reset( new NuclideProperties( *properties_it->second,
                                               zaid,
                                               atomic_weight_ratio ) );
    }
    else
    {
      properties.reset( new NuclideProperties( zaid, atomic_weight_ratio ) );
    }
  }
}

// Remove scattering center properties from the database
void ScatteringCenterPropertiesDatabase::removeProperties(
                                                        const Data::ZAID zaid )
{
  if( d_properties.find( zaid ) != d_properties.end() )
    d_properties.erase( zaid );
}

// Return the number of stored properties
size_t ScatteringCenterPropertiesDatabase::getNumberOfProperties() const
{
  return d_properties.size();
}

// List the properties names
void ScatteringCenterPropertiesDatabase::listPropertiesZaids(
                                                       std::ostream& os ) const
{
  os << "Scattering Centers:\n";
  
  ScatteringCenterZaidPropertiesMap::const_iterator properties_it =
    d_properties.begin();

  while( properties_it != d_properties.end() )
  {
    os << "  " << properties_it->first << "\n";

    ++properties_it;
  }

  os.flush();
}

// Log the properties zaids
void ScatteringCenterPropertiesDatabase::logPropertiesZaids() const
{
  std::ostringstream oss;
  oss << "\n";

  this->listPropertiesZaids( oss );

  FRENSIE_LOG_TAGGED_NOTIFICATION( "ScatteringCenterPropertiesDatabase",
                                   oss.str() );
}

// List the properties zaids associated with the atom type
void ScatteringCenterPropertiesDatabase::listPropertiesZaids(
                                                       const AtomType atom,
                                                       std::ostream& os ) const
{
  ScatteringCenterZaidPropertiesMap::const_iterator properties_it =
    d_properties.begin();

  os << atom << " Scattering Centers:\n";

  while( properties_it != d_properties.end() )
  {
    if( properties_it->first.atom() == atom )
      os << "  " << properties_it->first << "\n"; 
    
    ++properties_it;
  }

  os.flush();
}

// Log the properties zaids associated with the atom type
void ScatteringCenterPropertiesDatabase::logPropertiesZaids(
                                                    const AtomType atom ) const
{
  std::ostringstream oss;
  oss << "\n";

  this->listPropertiesZaids( atom, oss );

  FRENSIE_LOG_TAGGED_NOTIFICATION( "ScatteringCenterPropertiesDatabase",
                                   oss.str() );
}

// Save the model to an archive
template<typename Archive>
void ScatteringCenterPropertiesDatabase::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_properties );
}

// Load the model from an archive
template<typename Archive>
void ScatteringCenterPropertiesDatabase::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_properties );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesDatabase );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ScatteringCenterPropertiesDatabase, Data );

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesDatabase.cpp
//---------------------------------------------------------------------------//
