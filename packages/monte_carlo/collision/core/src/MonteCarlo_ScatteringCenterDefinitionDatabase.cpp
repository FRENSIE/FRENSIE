//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScatteringCenterDefinitionDatabase.cpp
//! \author Alex Robinson
//! \brief  The scattering center definition database definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
ScatteringCenterDefinitionDatabase::ScatteringCenterDefinitionDatabase()
{ /* ... */ }

// Check if a scattering center definition exists
bool ScatteringCenterDefinitionDatabase::doesDefinitionExist(
                                                const std::string& name ) const
{
  return d_scattering_center_definitions.find( name ) !=
    d_scattering_center_definitions.end();
}

// Create a new scattering center definition
ScatteringCenterDefinition& ScatteringCenterDefinitionDatabase::createDefinition(
                                                       const Data::ZAID& zaid )
{
  this->createDefinition( zaid.toName(), zaid );
}

// Create a new scattering center definition
ScatteringCenterDefinition& ScatteringCenterDefinitionDatabase::createDefinition(
                                                       const std::string& name,
                                                       const Data::ZAID& zaid )
{
  TEST_FOR_EXCEPTION( this->doesDefinitionExist( name ),
                      std::runtime_error,
                      "A scattering center with name " << name << " already "
                      "exists!" );

  std::shared_ptr<ScatteringCenterDefinition>& scattering_center_definition =
    d_scattering_center_definitions[name];

  scattering_center_definition.reset(
                                new ScatteringCenterDefinition( name, zaid ) );

  return *scattering_center_definition;
}

// Check if the scattering center name is an alias
bool ScatteringCenterDefinitionDatabase::isDefinitionNameAnAlias(
                                                const std::string& name ) const
{
  auto name_it = d_scattering_center_definitions.find( name );

  if( name_it != d_scattering_center_definitions.end() )
  {
    if( name_it->first != name_it->second->getName() )
      return true;
    else
      return false;
  }
  else
    return false;
}

// Create a scattering center definition alias
void ScatteringCenterDefinitionDatabase::createDefinitionAlias(
                                                     const std::string& name,
                                                     const std::string& alias )
{
  auto name_it = d_scattering_center_definitions.find( name );

  TEST_FOR_EXCEPTION( name_it == d_scattering_center_definitions.end(),
                      std::runtime_error,
                      "An alias cannot be created because a scattering center "
                      "definition with name " << name << " does not exist!" );

  d_scattering_center_definitions[alias] = name_it->second;
}

// Resolve the scattering center alias
std::string ScatteringCenterDefinitionDatabase::resolveDefinitionAlias(
                                               const std::string& alias ) const
{
  auto name_it = d_scattering_center_definitions.find( alias );

  TEST_FOR_EXCEPTION( name_it == d_scattering_center_definitions.end(),
                      std::runtime_error,
                      "There is no alias with name " << alias << "!" );

  return name_it->second->getName();
}

// Get a scattering center definition
ScatteringCenterDefinition& ScatteringCenterDefinitionDatabase::getDefinition(
                                                     const std::string& name )
{
  auto name_it = d_scattering_center_definitions.find( name );

  TEST_FOR_EXCEPTION( name_it == d_scattering_center_definitions.end(),
                      std::runtime_error,
                      "There are no scattering center definitions with name "
                      << name << "!" );

  return *name_it->second;
}

// Get a scattering center definition
const ScatteringCenterDefinition& ScatteringCenterDefinitionDatabase::getDefinition(
                                               const std::string& name ) const
{
  auto name_it = d_scattering_center_definitions.find( name );

  TEST_FOR_EXCEPTION( name_it == d_scattering_center_definitions.end(),
                      std::runtime_error,
                      "There are no scattering center definitions with name "
                      << name << "!" );

  return *name_it->second;
}

// Remove a scattering center definition
void ScatteringCenterDefinitionDatabase::removeDefinition(
                                                      const std::string& name )
{
  auto name_it = d_scattering_center_definitions.find( name );

  if( name_it != d_scattering_center_definitions.end() )
    d_scattering_center_definitions.erase( name_it );
}

// Place the object in an output stream
void ScatteringCenterDefinitionDatabase::toStream( std::ostream& os ) const
{
  auto name_it = d_scattering_center_definitions.cbegin();

  while( name_it != d_scattering_center_definitions.cend() )
  {
    if( name_it->first == name_it->second->getName() )
      name_it->second->toStream( os );
    else
      os << name_it->first << " -> " << name_it->second->getName() << "\n";
    
    ++name_it;
  }
}

EXPLICIT_CLASS_SAVE_LOAD_INST( ScatteringCenterDefinitionDatabase );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScatteringCenterDefinitionDatabase.cpp
//---------------------------------------------------------------------------//
