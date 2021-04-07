//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialDefinitionDatabase.cpp
//! \author Alex Robinson
//! \brief  The material definition database definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
MaterialDefinitionDatabase::MaterialDefinitionDatabase()
{ /* ... */ }

// Check if a material exists
bool MaterialDefinitionDatabase::doesDefinitionExist( const std::string& name ) const
{
  return d_material_id_name_map.right.find( name ) !=
    d_material_id_name_map.right.end();
}

// Check if a material exists
bool MaterialDefinitionDatabase::doesDefinitionExist( const size_t material_id ) const
{
  return d_material_id_name_map.left.find( material_id ) !=
    d_material_id_name_map.left.end();
}

// Add a material definition
/*! \details Both the material name and material id must be unique. There must
 * also be at least one component provided. Negative fractions will be
 * interpreted as weight fractions.
 */
void MaterialDefinitionDatabase::addDefinition(
                          const std::string& material_name,
                          const size_t material_id,
                          const MaterialDefinitionArray& material_components )
{
  TEST_FOR_EXCEPTION( d_material_id_name_map.right.find( material_name ) !=
                      d_material_id_name_map.right.end(),
                      std::runtime_error,
                      "A material with name " << material_name << " already "
                      "exists" );
  
  TEST_FOR_EXCEPTION( d_material_id_name_map.left.find( material_id ) !=
                      d_material_id_name_map.left.end(),
                      std::runtime_error,
                      "A material with id " << material_id << " already "
                      "exists!" );

  TEST_FOR_EXCEPTION( material_components.empty(),
                      std::runtime_error,
                      "A material definition must contain at least one "
                      "component!" );

  d_material_id_name_map.insert( MaterialIdNameBimap::value_type( material_id, material_name ) );
  d_material_id_definition_map[material_id] = material_components;
}

// Add a material definition
/*! \details The material name will simply be set to the id.
 */
void MaterialDefinitionDatabase::addDefinition(
                           const size_t material_id,
                           const MaterialDefinitionArray& material_components )
{
  this->addDefinition( Utility::toString( material_id ),
                       material_id,
                       material_components );
}

// Add a material definition
/*! \details There must be at least one component provided (one name and
 * one fraction). Negative fractions will be interpreted as weight fractions.
 */
void MaterialDefinitionDatabase::addDefinition(
                     const std::string& material_name,
                     const size_t material_id,
                     const std::vector<std::string>& material_component_names,
                     const std::vector<double>& material_component_fractions )
{
  TEST_FOR_EXCEPTION( material_component_names.size() !=
                      material_component_fractions.size(),
                      std::runtime_error,
                      "Every material component name must have a corresponding"
                      " fraction." );

  MaterialDefinitionArray definition_array( material_component_names.size() );
  
  for( size_t i = 0; i < material_component_names.size(); ++i )
  {
    Utility::get<0>(definition_array[i]) = material_component_names[i];
    Utility::get<1>(definition_array[i]) = material_component_fractions[i];
  }

  this->addDefinition( material_name,
                       material_id,
                       definition_array );
}

// Add a material definition
/*! \details The material name will simply be set to the id.
 */
void MaterialDefinitionDatabase::addDefinition(
                      const size_t material_id,
                      const std::vector<std::string>& material_component_names,
                      const std::vector<double>& material_component_fractions )
{
  this->addDefinition( Utility::toString( material_id ),
                       material_id,
                       material_component_names,
                       material_component_fractions );
}

// Get a material definition
auto MaterialDefinitionDatabase::getDefinition(
     const std::string& material_name ) const -> const MaterialDefinitionArray&
{
  auto name_it = d_material_id_name_map.right.find( material_name );
  
  TEST_FOR_EXCEPTION( name_it == d_material_id_name_map.right.end(),
                      std::runtime_error,
                      "There is no material definition corresponding to name "
                      << material_name << "!" );

  return this->getDefinition( name_it->second );
}

// Get a material definition
auto MaterialDefinitionDatabase::getDefinition(
             const size_t material_id ) const -> const MaterialDefinitionArray&
{
  auto material_id_it = d_material_id_definition_map.find( material_id );

  TEST_FOR_EXCEPTION( material_id_it == d_material_id_definition_map.end(),
                      std::runtime_error,
                      "There is no material definition corresponding to id "
                      << material_id << "!" );

  return material_id_it->second;
}

// Get the material id
size_t MaterialDefinitionDatabase::getMaterialId(
                                       const std::string& material_name ) const
{
  auto name_it = d_material_id_name_map.right.find( material_name );
  
  TEST_FOR_EXCEPTION( name_it == d_material_id_name_map.right.end(),
                      std::runtime_error,
                      "There is no material definition with name "
                      << material_name << "!" );

  return name_it->second;
}

// Get the material name
const std::string& MaterialDefinitionDatabase::getMaterialName(
                                               const size_t material_id ) const
{
  auto id_it = d_material_id_name_map.left.find( material_id );

  TEST_FOR_EXCEPTION( id_it == d_material_id_name_map.left.end(),
                      std::runtime_error,
                      "There is no material definition with id "
                      << material_id << "!" );

  return id_it->second;
}

// Remove material definition
void MaterialDefinitionDatabase::removeDefinition( const std::string& material_name )
{
  auto name_it = d_material_id_name_map.right.find( material_name );
  
  if( name_it != d_material_id_name_map.right.end() )
  {
    d_material_id_definition_map.erase( name_it->second );
    d_material_id_name_map.right.erase( name_it );
  }
}

// Remove material definition
void MaterialDefinitionDatabase::removeDefinition( const size_t material_id )
{
  auto id_it = d_material_id_name_map.left.find( material_id );

  if( id_it != d_material_id_name_map.left.end() )
  {
    d_material_id_definition_map.erase( material_id );
    d_material_id_name_map.left.erase( id_it );
  }
}

// Get the material ids
void MaterialDefinitionDatabase::getMaterialIds(
                                            MaterialIdSet& material_ids ) const
{
  auto material_definition_it = d_material_id_definition_map.cbegin();

  while( material_definition_it != d_material_id_definition_map.cend() )
  {
    material_ids.insert( material_definition_it->first );
    
    ++material_definition_it;
  }
}

// Get the material ids
auto MaterialDefinitionDatabase::getMaterialIds() const -> MaterialIdSet
{
  MaterialIdSet material_ids;

  this->getMaterialIds( material_ids );

  return material_ids;
}

// Get the unique scattering center names
void MaterialDefinitionDatabase::getUniqueScatteringCenterNames(
                      ScatteringCenterNameSet& scattering_center_names ) const
{
  MaterialIdSet material_ids;

  this->getMaterialIds( material_ids );

  this->getUniqueScatteringCenterNames( material_ids,
                                        scattering_center_names );
}

// Get the unique scattering center names
auto MaterialDefinitionDatabase::getUniqueScatteringCenterNames() const -> ScatteringCenterNameSet
{
  ScatteringCenterNameSet scattering_center_names;

  this->getUniqueScatteringCenterNames( scattering_center_names );

  return scattering_center_names;
}

// Get an iterator to the first material definition
auto MaterialDefinitionDatabase::begin() const -> MaterialDefinitionIterator
{
  return d_material_id_definition_map.cbegin();
}

// Get an iterator to the one-past-the-last material definition
auto MaterialDefinitionDatabase::end() const -> MaterialDefinitionIterator
{
  return d_material_id_definition_map.cend();
}

// Place the material properties in a stream
void MaterialDefinitionDatabase::toStream( std::ostream& os ) const
{
  auto material_definition_it = d_material_id_definition_map.cbegin();

  while( material_definition_it != d_material_id_definition_map.cend() )
  {
    const std::string& material_name =
      d_material_id_name_map.left.find(material_definition_it->first)->second;
    
    os << "\"" << material_name << "\" "
       << "(" << material_definition_it->first << "): ";

    for( size_t i = 0; i < material_definition_it->second.size(); ++i )
    {
      os << Utility::get<0>( material_definition_it->second[i] ) << "("
         << Utility::toString(Utility::get<1>( material_definition_it->second[i] ))
         << ") ";
    }

    os << "\n";
    
    ++material_definition_it;
  }
}

EXPLICIT_CLASS_SAVE_LOAD_INST( MaterialDefinitionDatabase );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialDefinitionDatabase.cpp
//---------------------------------------------------------------------------//
