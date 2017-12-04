//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTreeCompatibleObject_def.hpp
//! \author Alex Robinson
//! \brief  Property tree compatible object base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_DEF_HPP
#define UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_DEF_HPP

// FRENSIE Includes
#include "Utility_QuantityTraits.hpp"

namespace Utility{

namespace Details{

//! Helper class for placing data in a property tree
template<size_t I, typename TupleType, typename Enabled = void>
struct ToPropertyTreeHelper
{
  static inline void placeElementInPropertyTree( Utility::PropertyTree& ptree,
                                                 const TupleType& data )
  {
    auto& element_I = Utility::get<I>( data );
    
    ptree.put( Utility::get<0>( element_I ), Utility::get<1>( element_I ) );

    ToPropertyTreeHelper<I+1,TupleType>::placeElementInPropertyTree( ptree, data );
  }
};

//! Specialization of ToPropertyTreeHelper for parameter packs of I = TupleSize-1
template<size_t I, typename TupleType>
struct ToPropertyTreeHelper<I,TupleType,typename std::enable_if<I==Utility::TupleSize<TupleType>::value-1>::type>
{
  static inline void placeElementInPropertyTree( Utility::PropertyTree& ptree,
                                                 const TupleType& data )
  {
    auto& element_I = Utility::get<I>( data );
    
    ptree.put( Utility::get<0>( element_I ), Utility::get<1>( element_I ) );
  }
};

//! Specialization of ToPropertyTreeHelper for parameter packs of I = TupleSize
template<size_t I, typename TupleType>
struct ToPropertyTreeHelper<I,TupleType,typename std::enable_if<I==Utility::TupleSize<TupleType>::value>::type>
{
  static inline void placeElementInPropertyTree( Utility::PropertyTree&,
                                                 const TupleType& )
  { /* ... */ }
};
  
} // end Details namespace

// Add the data to a property tree
template<typename... Types>
Utility::PropertyTree PropertyTreeCompatibleObject::toPropertyTreeImpl(
                   const std::tuple<const std::string&,Types&>&... data ) const
{
  Utility::PropertyTree ptree;

  // Add the type name to the property tree
  ptree.put( this->getTypeKey(), this->getTypeName( true, false ) );

  // Add the distribution data
  Details::ToPropertyTreeHelper<0,decltype(std::tie(data...))>::placeElementInPropertyTree( ptree, std::tie(data...) );

  return ptree;
}

// Extract a value from a node
template<template<typename,typename...> class Container>
void PropertyTreeCompatibleObject::extractArrayFromNode(
                                       const Utility::PropertyTree& array_data,
                                       Container<double>& array,
                                       const std::string& type_name )
{
  // Inline array
  if( array_data.size() == 0 )
  {
    try{
      ThisType::extractArray( array_data.data(), array, type_name );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Could not create the " << type_name << 
                                " because the array values are invalid!" );
  }

  // JSON array
  else
  {
    try{
      array = Utility::fromPropertyTree<Container<double> >( array_data );
    }
    EXCEPTION_CATCH_RETHROW( Utility::PropertyTreeConversionException,
                             "Could not create the " << type_name << 
                             " because the JSON array values are invalid!" );
  }
}

// Extract a value from a node
template<typename QuantityType>
void PropertyTreeCompatibleObject::extractValueFromNode(
                                       const Utility::PropertyTree& value_data,
                                       QuantityType& value,
                                       const std::string& type_name )
{
  // The data must be inlined in the node
  TEST_FOR_EXCEPTION( value_data.size() != 0,
                      Utility::PropertyTreeConversionException,
                      "Could not extract the value!" );

  try{
    ThisType::extractValue( value_data.data(), value, type_name );
  }
  EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                              Utility::PropertyTreeConversionException,
                              "Could not create the " << type_name <<
                              " because a value is invalid!" );
}

// Extract an array
template<template<typename,typename...> class Container>
void PropertyTreeCompatibleObject::extractArray(
                                            const Utility::Variant& array_data,
                                            Container<double>& array,
                                            const std::string& type_name )
{
  try{
    array = Utility::variant_cast<Container<double> >( array_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "Could not create the " << type_name << 
                           " because the array values are invalid!" );
}

// Extract a value
template<typename QuantityType>
void PropertyTreeCompatibleObject::extractValue(
                                            const Utility::Variant& value_data,
                                            QuantityType& value,
                                            const std::string& type_name )
{
  typename Utility::QuantityTraits<QuantityType>::RawType raw_value;

  try{
    raw_value = Utility::variant_cast<typename Utility::QuantityTraits<QuantityType>::RawType>( value_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "Could not create the " << type_name <<
                           " because a value is invalid!" );

  Utility::setQuantity( value, raw_value );
}

// Extract from a property tree
/*! \details The data in the property tree node cannot be inlined
 * (i.e. node.size() != 0 ). Once object data is encountered and 
 * extracted its extractor will be removed from the extractors list. If an 
 * extractor is left in the list after this method finishes it is an indication
 * that the data was not encountered in the property tree.
 */
void PropertyTreeCompatibleObject::fromPropertyTreeImpl(
                                     const Utility::PropertyTree& node,
                                     std::vector<std::string>& unused_children,
                                     DataExtractorMap& data_extractors )
{
  // Determine which data must be extracted
  std::map<std::string,bool> required_data;

  this->getRequiredDataKeys( data_extractors, required_data );

  // Extract the data
  bool type_verified = this->extractDataFromPropertyTree( node,
                                                          unused_children,
                                                          data_extractors,
                                                          required_data );

  // Make sure that the distribution type was verified
  TEST_FOR_EXCEPTION( !type_verified,
                      Utility::PropertyTreeConversionException,
                      "The "
                      << this->getTypeName(true, true) <<
                      " could not be constructed because the type could not be"
                      " verified!" );

  // Make sure that all required data was extracted
  for( std::map<std::string,bool>::const_iterator required_data_it = required_data.begin();
       required_data_it != required_data.end();
       ++required_data_it )
  {
    TEST_FOR_EXCEPTION( !required_data_it->second,
                        Utility::PropertyTreeConversionException,
                        "The "
                        << this->getTypeName(true, true) <<
                        " could not be constructed because the "
                        << required_data_it->first << " data was not "
                        "specified!" );
  }  
}

// Determine which data must be extracted from a property tree
void PropertyTreeCompatibleObject::getRequiredDataKeys(
                         const DataExtractorMap& data_extractors,
                         std::map<std::string,bool>& required_data_keys ) const
{
  for( typename DataExtractorMap::const_iterator data_it = data_extractors.begin();
       data_it != data_extractors.end();
       ++data_it )
  {
    if( Utility::get<1>(data_it->second) == REQUIRED_DATA )
    {
      // Initialize the flag that indicates that the required data has been
      // extracted
      required_data[data_it->first] = false;
    }
  }
}

// Extract the data from the property tree
bool PropertyTreeCompatibleObject::extractDataFromPropertyTree(
                               const Utility::PropertyTree& node,
                               std::vector<std::string>& unused_children,
                               DataExtractorMap& data_extractors,
                               std::map<std::string,bool>& required_data )
{
  bool type_verified = false;
  
  // Convert the type key to lowercase
  std::string type_key = this->getTypeKey();

  boost::algorithm::to_lower( type_key );

  // Extract data from each child node of the property tree (or report the
  // child node as unused)
  for( Utility::PropertyTree::const_iterator node_it = node.begin();
       node_it != node.end();
       ++node_it )
  {
    std::string child_node_key =
      boost::algorithm::to_lower_copy( node_it->first );

    // Verify the type
    if( child_node_key.find( type_key ) < child_node_key.size() )
    {
      if( !type_verified )
      {
        TEST_FOR_EXCEPTION( node_it->size() != 0,
                            Utility::PropertyTreeConversionException,
                            "Could not create the "
                            << this->getTypeName(true, true) <<
                            " because the type node is not inlined!" );
        try{
          this->verifyType( node_it->second.data() );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the "
                                    << this->getTypeName(true, true) <<
                                    "!" );
        type_verified = true;
        continue;
      }
      else
      {
        THROW_EXCEPTION( Utility::PropertyTreeConversionException,
                         "Could not create the "
                         << this->getTypeName(true, true) <<
                         "because the type was specified multiple times!" );
      }
    }
    
    // Extract data used by calling object
    else
    {
      // Determine the best data key match
      DataExtractorMap::iterator data_extractor_it =
        this->determineBestKeyMatch( child_node_key, data_extractors );

      if( data_extractor_it != data_extractors.end() )
      {
        // Extract the data from the child node
        try{
          Utility::get<2>(data_extractor_it->second)( node_it->second );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not extract "
                                    << best_key_match.second->first << " data "
                                    "from property tree node "
                                    << node_it->first << "!" );

        // Check if this is required data
        if( required_data.find( best_key_match.second->first ) !=
            required_data.end() )
          required_data[best_key_match.second->first] = true;
          
        // Remove the data extractor
        data_extractors.erase( best_key_match.second );

        continue;
      }
    }

    // If we get to this point the node is unused
    if( child_node_key.find( PTREE_COMMENT_NODE_KEY ) >=
        child_node_key.size() )
    {
      unused_children.push_back( node_it->first );
    }
  }

  return type_verified;
}

// Determine the data extractor key that best matches the node key
auto PropertyTreeCompatibleObject::determineBestKeyMatch(
                                      const std::string& node_key,
                                      const DataExtractorMap& data_extractors )
  -> DataExtractorMap::iterator
{
  DataExtractorMap::iterator data_extractor_it = data_extractors.begin();
  DataExtractorMap::iterator data_extractor_end = data_extractors.end();

  // The data extractor key with the longest matching string is assumed to
  // be the best match
  std::pair<size_t,typename DataExtractorMap::iterator> best_key_match = 
    std::make_pair( 0, data_extractors.end() );
  
  while( data_extractor_it != data_extractor_end )
  {
    if( node_key.find( Utility::get<0>(data_extractor_it->second) ) <
        node_key.size() )
    {
      size_t match_length =
        Utility::get<0>(data_extractor_it->second).size();

      // If the match length is the same, default to the first match
      // found
      if( best_key_match.first < match_length )
      {
        best_key_match.first = match_length;
        best_key_match.second = data_extractor_it;
      }
    }

    ++data_extractor_it;
  }

  return best_key_match.second;
}
  
} // end Utility namespace

#endif // end UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTreeCompatibleObject.hpp
//---------------------------------------------------------------------------//
