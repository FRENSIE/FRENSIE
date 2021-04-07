//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTreeConversionFactory_def.hpp
//! \author Alex Robinson
//! \brief  Property tree conversion factory class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_CONVERSION_FACTORY_DEF_HPP
#define UTILITY_PROPERTY_TREE_CONVERSION_FACTORY_DEF_HPP

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

// Initialize static member data
template<typename T>
PropertyTreeConversionFactory<T>::ConverterList PropertyTreeConversionFactory<T>::s_converters

template<typename T>
PropertyTreeConversionFactory<T>::InlineTypeExtractor PropertyTreeConversionFactory<T>::s_inline_type_extractor = &PropertyTreeConversionFactory<T>::extractInlineType;

// Constructor
template<typename T>
PropertyTreeConversionFactory<T>::PropertyTreeConversionFactory()
  : d_converter_aliases()
{ /* ... */ }

// Register a converter with the factory
template<typename T>
bool PropertyTreeConversionFactory<T>::registerConverter(
                                                const ConverterPtr& converter )
{
  // Make sure that the converter is valid
  testPrecondition( converter.get() );

  const std::string type_name = converter.getConcreteTypeName();
  
  ConverterMap::const_iterator converter_it = s_converters.find( type_name );

  if( converter_it != converter.end() )
  {
    FRENSIE_LOG_WARNING( "A property tree converter for type name \""
                         << type_name << "\" has already been "
                         "registered (the previous converter registered will "
                         "be discarded)!" );
  }

  s_converters[type_name] = converter;
}

// Register an inline property tree type extraction method
template<typename T>
bool PropertyTreeConversionFactory<T>::registerInlineTypeExtractionMethod(
                              const InlineTypeExtractor inline_type_extractor )
{
  s_inline_type_extractor = inline_type_extractor;
}

// Get the type key
template<typename T>
std::string PropertyTreeConversionFactory<T>::getTypeKey() const
{
  return PTREE_TYPE_KEY;
}

// Convert the object represented by the property tree
template<typename T>
void PropertyTreeConversionFactory<T>::convert(
                                     const Utility::PropertyTree& ptree,
                                     std::vector<std::string>& unused_children,
                                     std::shared_ptr<const T>& object )
{
  this->convertImpl( ptree, unused_children, object );
}   

// Convert the object represented by the property tree
template<typename T>
void PropertyTreeConversionFactory<T>::convert(
                                     const Utility::PropertyTree& ptree,
                                     std::vector<std::string>& unused_children,
                                     std::unique_ptr<const T>& object )
{
  this->convertImpl( ptree, unused_children, object );
}

// Create the object represented by the property tree
template<typename T>
template<template<typename,typename...> class SmartPointer>
void PropertyTreeConversionFactory<T>::convertImpl(
                                     const Utility::PropertyTree& ptree,
                                     std::vector<std::string>& unused_children,
                                     SmartPointer<const T>& object )
{
  // Get the distribution type name specified in the property tree
  std::string ptree_type_name;

  if( ptree.size() == 0 )
    ptree_type_name = s_inline_type_extractor( ptree );
  else
    ptree_type_name = this->extractType( ptree );
}

// Default inline type extraction method
template<typename T>
std::string PropertyTreeConversionFactory<T>::extractInlineType(
                                           const Utility::PropertyTree& ptree )
{
  THROW_EXCEPTION( Utility::PropertyTreeConversionException,
                   "The type cannot be extracted from the inline property "
                   "tree because no inline property tree type extraction "
                   "method has been registered with the factory!" );
}

// Extract the type
template<typename T>
std::string PropertyTreeConversionFactory<T>:extractType(
                                           const Utility::PropertyTree& ptree )
{
  const std::string type_key = this->getTypeKey();
    
  bool type_found = false;

  for( Utility::PropertyTree::const_iterator node_it = ptree.begin();
       node_it != ptree.end();
       ++node_it )
  {
    std::string child_node_key =
      boost::algorithm::to_lower_copy( node_it->first );

    // Extract the type
    if( child_node_key.find( type_key ) < child_node_key.size() )
    {
      if( !type_found )
      {
        TEST_FOR_EXCEPTION( node_it->size() != 0,
                            Utility::PropertyTreeConversionException,
                            "The property tree cannot be converted to the "
                            "desired type because the type node is not "
                            "inlined!" );
        
        ptree_type_name = node_it->second.data().toString();
        
        type_found = true;
      }
      else
      {
        THROW_EXCEPTION( Utility::PropertyTreeConversionException,
                         "The property tree cannot be converted to the "
                         "desired type because multiple type nodes were "
                         "encountered!" );
      }
    }
  }

  // Find the required type converter
  ConverterMap::const_iterator converter_it =
    s_converters.find( ptree_type_name );

  bool alias_used = false;
  bool cache_alias = false;

  // The type name is not an exact match with any of the registered
  // converters - check known aliases
  if( converter_it == s_converters.end() )
  {
    ConverterAliasMap::alias_it = d_converter_aliases.find( ptree_type_name );

    if( alias_it != d_converter_aliases.end() )
      converter_it = s_converters.find( alias_it->second );
    else
      cache_alias = true;
    
    alias_used = true;
  }

  // The alias used was not a known alias - do a brute force, case-insensitive
  // search
  if( converter_it == s_converters.end() )
  {
    std::string lcase_ptree_type_name =
      boost::algorithm::to_lower_copy( ptree_type_name );
    
    converter_it = s_converters.begin();

    while( converter_it != s_converters.end() )
    {
      std::string converter_type_name =
        boost::algorithm::to_lower_copy( converter_it->first );

      if( lcase_ptree_type_name.find( converter_type_name ) <
          lcase_ptree_type_name.size() )
        break;

      ++converter_it;
    }
  }

  TEST_FOR_EXCEPTION( converter_it == s_converters.end(),
                      Utility::PropertyTreeConversionException,
                      "The property tree cannot be converted to the desired "
                      "type because no registered converters are "
                      "compatible with the type name (" << ptree_type_name <<
                      ") extracted from the property tree!" );

  converter_it->second->convert( ptree, unused_children, object );
}
  
} // end Utility namespace

#endif // end UTILITY_PROPERTY_TREE_CONVERSION_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTreeConversionFactory_def.hpp
//---------------------------------------------------------------------------//
