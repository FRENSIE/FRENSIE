//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialDefinitionDatabase.hpp
//! \author Alex Robinson
//! \brief  The material definition database declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_DEFINITION_DATABASE_HPP
#define MONTE_CARLO_MATERIAL_DEFINITION_DATABASE_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/bimap.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"
#include "Utility_OStreamableObject.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The material properties class
class MaterialDefinitionDatabase : public Utility::OStreamableObject
{
  // The material definition array
  typedef std::vector<std::pair<std::string,double> > MaterialDefinitionArrayPrivate;

  // The material id definition map type
  typedef std::map<size_t,MaterialDefinitionArrayPrivate> MaterialIdDefinitionMap;

  // The material id name map type
  typedef boost::bimap<size_t,std::string> MaterialIdNameBimap;

public:

  //! The material definition array
  typedef MaterialDefinitionArrayPrivate MaterialDefinitionArray;

  //! The material id set
  typedef std::set<size_t> MaterialIdSet;

  //! The scattering center name set
  typedef std::set<std::string> ScatteringCenterNameSet;

  //! The material definition iterator
  typedef MaterialIdDefinitionMap::const_iterator MaterialDefinitionIterator;

  //! Constructor
  MaterialDefinitionDatabase();

  //! Destructor
  ~MaterialDefinitionDatabase()
  { /* ... */ }

  //! Check if a material exists
  bool doesDefinitionExist( const std::string& name ) const;

  //! Check if a material exists
  bool doesDefinitionExist( const size_t material_id ) const;

  //! Add a material definition
  void addDefinition( const std::string& material_name,
                      const size_t material_id,
                      const MaterialDefinitionArray& material_components );

  //! Add a material definition
  void addDefinition( const size_t material_id,
                      const MaterialDefinitionArray& material_components );

  //! Add a material definition
  void addDefinition(
                     const std::string& material_name,
                     const size_t material_id,
                     const std::vector<std::string>& material_component_names,
                     const std::vector<double>& material_component_fractions );

  //! Add a material definition
  void addDefinition(
                     const size_t material_id,
                     const std::vector<std::string>& material_component_names,
                     const std::vector<double>& material_component_fractions );

  //! Get a material definition
  const MaterialDefinitionArray& getDefinition(
                                      const std::string& material_name ) const;

  //! Get a material definition
  const MaterialDefinitionArray& getDefinition(
                                              const size_t material_id ) const;

  //! Get the material id
  size_t getMaterialId( const std::string& material_name ) const;

  //! Get the material name
  const std::string& getMaterialName( const size_t material_id ) const;

  //! Remove material definition
  void removeDefinition( const std::string& material_name );

  //! Remove material definition
  void removeDefinition( const size_t material_id );

  //! Get an iterator to the first material definition
  MaterialDefinitionIterator begin() const;

  //! Get an iterator to the one-past-the-last material definition
  MaterialDefinitionIterator end() const;

  //! Get the material ids
  void getMaterialIds( MaterialIdSet& material_ids ) const;

  //! Get the material ids
  MaterialIdSet getMaterialIds() const;

  //! Get the unique scattering center names
  void getUniqueScatteringCenterNames(
                      ScatteringCenterNameSet& scattering_center_names ) const;

  //! Get the unique scattering center names
  ScatteringCenterNameSet getUniqueScatteringCenterNames() const;

  // SWIG has trouble parsing complex templates and throws a syntax error.
  #if !defined SWIG
  //! Get the unique scattering center names from the materials of interest
  template<template<typename,typename...> class Set, typename MaterialIdType>
  void getUniqueScatteringCenterNames(
                      const Set<MaterialIdType>& material_ids,
                      ScatteringCenterNameSet& scattering_center_names ) const;


  //! Get the unique scattering center names
  template<template<typename,typename...> class Set, typename MaterialIdType>
  ScatteringCenterNameSet getUniqueScatteringCenterNames(
                               const Set<MaterialIdType>& material_ids ) const;

  #endif // end !defined SWIG

  //! Place the material properties in a stream
  void toStream( std::ostream& os ) const final override;

private:

  // Save the object to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the object from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The material definitions
  MaterialIdDefinitionMap d_material_id_definition_map;

  // The material id name map
  MaterialIdNameBimap d_material_id_name_map;
};

// Save the object to an archive
template<typename Archive>
void MaterialDefinitionDatabase::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_material_id_definition_map );
  ar & BOOST_SERIALIZATION_NVP( d_material_id_name_map );
}

// Load the object from an archive
template<typename Archive>
void MaterialDefinitionDatabase::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_material_id_definition_map );
  ar & BOOST_SERIALIZATION_NVP( d_material_id_name_map );
}

// SWIG has trouble parsing complex templates and throws a syntax error.
#if !defined SWIG

// Get the unique scattering center names from the materials of interest
template<template<typename,typename...> class Set, typename MaterialIdType>
void MaterialDefinitionDatabase::getUniqueScatteringCenterNames(
                       const Set<MaterialIdType>& material_ids,
                       ScatteringCenterNameSet& scattering_center_names ) const
{
  typename Set<MaterialIdType>::const_iterator material_id_it =
    material_ids.begin();

  while( material_id_it != material_ids.end() )
  {
    auto material_definition_it =
      d_material_id_definition_map.find( *material_id_it );

    if( material_definition_it != d_material_id_definition_map.end() )
    {
      for( size_t i = 0; i < material_definition_it->second.size(); ++i )
      {
        scattering_center_names.insert(
                        Utility::get<0>( material_definition_it->second[i] ) );
      }
    }

    ++material_id_it;
  }
}

//  Get the unique scattering center names
template<template<typename,typename...> class Set, typename MaterialIdType>
auto MaterialDefinitionDatabase::getUniqueScatteringCenterNames(
     const Set<MaterialIdType>& material_ids ) const -> ScatteringCenterNameSet
{
  ScatteringCenterNameSet scattering_center_names;

  this->getUniqueScatteringCenterNames( material_ids,
                                        scattering_center_names );

  return scattering_center_names;
}

#endif // end !defined SWIG

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( MaterialDefinitionDatabase, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, MaterialDefinitionDatabase );

#endif // end MONTE_CARLO_MATERIAL_DEFINITION_DATABASE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialDefinitionDatabase.hpp
//---------------------------------------------------------------------------//
