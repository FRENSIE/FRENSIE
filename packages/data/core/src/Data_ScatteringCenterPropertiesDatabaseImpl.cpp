//---------------------------------------------------------------------------//
//!
//! \file   Data_ScatteringCenterPropertiesDatabaseDecl.cpp
//! \author Alex Robinson
//! \brief  The scattering center properties database definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <fstream>

// Boost Includes
#include <boost/serialization/map.hpp>
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Data_ScatteringCenterPropertiesDatabaseImpl.hpp"
#include "Utility_PolymorphicHDF5OArchive.hpp"
#include "Utility_PolymorphicHDF5IArchive.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

// Default constructor
ScatteringCenterPropertiesDatabaseImpl::ScatteringCenterPropertiesDatabaseImpl()
{ /* ... */ }

// Check if atom properties with the name of interest exist
bool ScatteringCenterPropertiesDatabaseImpl::doAtomPropertiesExist( const AtomType atom )
{
  return d_atom_properties.find( atom ) != d_atom_properties.end();
}

// Check if the atom properties exist
bool ScatteringCenterPropertiesDatabaseImpl::doAtomPropertiesExist(
                                                        const Data::ZAID zaid )
{
  return this->doAtomPropertiesExist( zaid.atom() );
}

// Check if nuclide properties with zaid exist
bool ScatteringCenterPropertiesDatabaseImpl::doNuclidePropertiesExist(
                                                        const Data::ZAID zaid )
{
  return d_nuclide_properties.find( zaid ) != d_nuclide_properties.end();
}

// Remove atom properties from the database
void ScatteringCenterPropertiesDatabaseImpl::removeAtomProperties(
                                                          const AtomType atom )
{
  if( d_atom_properties.find( atom ) != d_atom_properties.end() )
    d_atom_properties.erase( atom );
}

// Remove atom properties from the database
void ScatteringCenterPropertiesDatabaseImpl::removeAtomProperties(
                                                        const Data::ZAID zaid )
{
  this->removeAtomProperties( zaid.atom() );
}

// Remove nuclide properties from the database
void ScatteringCenterPropertiesDatabaseImpl::removeNuclideProperties(
                                                        const Data::ZAID zaid )
{
  if( d_nuclide_properties.find( zaid ) != d_nuclide_properties.end() )
    d_nuclide_properties.erase( zaid );
}

// Remove empty properties from the database
void ScatteringCenterPropertiesDatabaseImpl::removeEmptyProperties(
                                           const bool include_atom_properties )
{
  // Remove empty atom properties
  if( include_atom_properties )
  {
    AtomPropertiesMap::iterator properties_it =
      d_atom_properties.begin();

    while( properties_it != d_atom_properties.end() )
    {
      if( properties_it->second->empty() )
        properties_it = d_atom_properties.erase( properties_it );
      else
        ++properties_it;
    }
  }

  // Remove empty nuclide properties
  NuclidePropertiesMap::iterator properties_it = d_nuclide_properties.begin();

  while( properties_it != d_nuclide_properties.end() )
  {
    if( properties_it->second->empty() )
      properties_it = d_nuclide_properties.erase( properties_it );
    else
      ++properties_it;
  }
}

// Return the desired properties
/*! \details If the atom properties do not exist an exception will be
 * thrown.
 */
const AtomProperties& ScatteringCenterPropertiesDatabaseImpl::getAtomProperties(
                                                    const AtomType atom ) const
{
  AtomPropertiesMap::const_iterator properties_it = 
    d_atom_properties.find( atom );
  
  if( properties_it != d_atom_properties.end() )
    return *properties_it->second;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There are no atom properties associated "
                     "with " << atom << " in the database!" );
  }
}

// Return the desired properties
/*! If the atom properties do not exist an exception will be
 * thrown.
 */
AtomProperties& ScatteringCenterPropertiesDatabaseImpl::getAtomProperties(
                                                          const AtomType atom )
{
  AtomPropertiesMap::iterator properties_it = d_atom_properties.find( atom );

  if( properties_it != d_atom_properties.end() )
    return *properties_it->second;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There are no atom properties associated "
                     "with " << atom << " in the database!" );
  }
}

// Return the desired properties
/*! If the atom properties do not exist an exception will be
 * thrown.
 */
const AtomProperties& ScatteringCenterPropertiesDatabaseImpl::getAtomProperties(
                                                  const Data::ZAID zaid ) const
{
  return this->getAtomProperties( zaid.atom() );
}

// Return the desired properties
/*! If the atom properties do not exist an exception will be
 * thrown.
 */
AtomProperties& ScatteringCenterPropertiesDatabaseImpl::getAtomProperties(
                                                        const Data::ZAID zaid )
{
  return this->getAtomProperties( zaid.atom() );
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabaseImpl::initializeAtomProperties(
                                             const AtomType atom,
                                             const double atomic_weight_ratio )
{
  return this->initializeAtomPropertiesImpl( atom, atomic_weight_ratio );
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabaseImpl::initializeAtomProperties(
                             const AtomType atom,
                             const AtomProperties::AtomicWeight atomic_weight )
{
  return this->initializeAtomPropertiesImpl( atom, atomic_weight );
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabaseImpl::initializeAtomProperties(
                                             const Data::ZAID zaid,
                                             const double atomic_weight_ratio )
{
  return this->initializeAtomProperties( zaid.atom(), atomic_weight_ratio );
}

// Initialize the atom properties
/*! \details If the atom properties already exist, the existing properties
 * will be returned.
 */
AtomProperties& ScatteringCenterPropertiesDatabaseImpl::initializeAtomProperties(
                             const Data::ZAID zaid,
                             const AtomProperties::AtomicWeight atomic_weight )
{
  return this->initializeAtomProperties( zaid.atom(), atomic_weight );
}

// Return the desired properties
/*! If the nuclide properties do not exist an exception will be thrown.
 */
const NuclideProperties& ScatteringCenterPropertiesDatabaseImpl::getNuclideProperties(
                                                  const Data::ZAID zaid ) const
{
  NuclidePropertiesMap::const_iterator properties_it = 
    d_nuclide_properties.find( zaid );
  
  if( properties_it != d_nuclide_properties.end() )
    return *properties_it->second;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There are no nuclide properties associated "
                     "with zaid " << zaid << " in the database!" );
  }
}

// Return the desired properties
/*! If the nuclide properties do not exist an exception will be thrown.
 */
NuclideProperties& ScatteringCenterPropertiesDatabaseImpl::getNuclideProperties(
                                                        const Data::ZAID zaid )
{
  NuclidePropertiesMap::const_iterator properties_it = 
    d_nuclide_properties.find( zaid );
  
  if( properties_it != d_nuclide_properties.end() )
    return *properties_it->second;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "There are no nuclide properties associated "
                     "with zaid " << zaid << " in the database!" );
  }
}

// Initialize the nuclide properties
/*! \details If the nuclide properties already exist, the existing properties
 * will be returned.
 */
NuclideProperties& ScatteringCenterPropertiesDatabaseImpl::initializeNuclideProperties(
                                             const Data::ZAID zaid,
                                             const double atomic_weight_ratio )
{
  return this->initializeNuclidePropertiesImpl( zaid, atomic_weight_ratio );
}

// Initialize the nuclide properties
/*! \details If the nuclide properties already exist, the existing properties
 * will be returned.
 */
NuclideProperties& ScatteringCenterPropertiesDatabaseImpl::initializeNuclideProperties(
                          const Data::ZAID zaid,
                          const NuclideProperties::AtomicWeight atomic_weight )
{
  return this->initializeNuclidePropertiesImpl( zaid, atomic_weight );
}

// Return the number of stored atom properties
size_t ScatteringCenterPropertiesDatabaseImpl::getNumberOfAtomProperties() const
{
  return d_atom_properties.size();
}

// Return the number of stored nuclide properties
size_t ScatteringCenterPropertiesDatabaseImpl::getNumberOfNuclideProperties() const
{
  return d_nuclide_properties.size();
}

// List the atoms
void ScatteringCenterPropertiesDatabaseImpl::listAtoms( std::ostream& os ) const
{
  os << "Atoms:\n";

  AtomPropertiesMap::const_iterator properties_it = d_atom_properties.begin();

  while( properties_it != d_atom_properties.end() )
  {
    os << "  " << properties_it->first << "\n";

    ++properties_it;
  }

  os.flush();
}

// Log the atoms
void ScatteringCenterPropertiesDatabaseImpl::logAtoms() const
{
  std::ostringstream oss;
  oss << "\n";

  this->listAtoms();

  FRENSIE_LOG_TAGGED_NOTIFICATION( "ScatteringCenterPropertiesDatabase",
                                   oss.str() );
}

// List the zaids
void ScatteringCenterPropertiesDatabaseImpl::listZaids(
                                                       std::ostream& os ) const
{
  os << "Nuclides:\n";

  NuclidePropertiesMap::const_iterator properties_it =
    d_nuclide_properties.begin();
  
  while( properties_it != d_nuclide_properties.end() )
  {
    os << "  " << properties_it->first << "\n";

    ++properties_it;
  }

  os.flush();
}

// List the zaids associated with the atom type
void ScatteringCenterPropertiesDatabaseImpl::listZaids(
                                                       const AtomType atom,
                                                       std::ostream& os ) const
{
  NuclidePropertiesMap::const_iterator properties_it =
    d_nuclide_properties.begin();

  os << atom << " Nuclides:\n";

  while( properties_it != d_nuclide_properties.end() )
  {
    if( properties_it->first.atom() == atom )
      os << "  " << properties_it->first << "\n"; 
    
    ++properties_it;
  }

  os.flush();
}

// Log the zaids
void ScatteringCenterPropertiesDatabaseImpl::logZaids() const
{
  std::ostringstream oss;
  oss << "\n";

  this->listZaids( oss );

  FRENSIE_LOG_TAGGED_NOTIFICATION( "ScatteringCenterPropertiesDatabase",
                                   oss.str() );
}

// Log the properties zaids associated with the atom type
void ScatteringCenterPropertiesDatabaseImpl::logZaids(
                                                    const AtomType atom ) const
{
  std::ostringstream oss;
  oss << "\n";

  this->listZaids( atom, oss );

  FRENSIE_LOG_TAGGED_NOTIFICATION( "ScatteringCenterPropertiesDatabase",
                                   oss.str() );
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ScatteringCenterPropertiesDatabaseImpl );
  
} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ScatteringCenterPropertiesDatabaseImpl, Data );

//---------------------------------------------------------------------------//
// end Data_ScatteringCenterPropertiesDatabaseDecl.cpp
//---------------------------------------------------------------------------//
