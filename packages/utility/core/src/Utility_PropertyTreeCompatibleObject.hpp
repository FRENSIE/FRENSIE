//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTreeCompatibleObject.hpp
//! \author Alex Robinson
//! \brief  Property tree compatible object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP
#define UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP

// FRENSIE Includes
#include "Utility_PropertyTree.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The base class for Utility::PropertyTree compatible objects
 * \ingroup ptree
 */
class PropertyTreeCompatibleObject 
{

public:

  //! Check if data can be inlined
  virtual bool canDataBeInlined() const;

  //! Return the type key
  virtual std::string getTypeKey() const;

  //! Return the type name
  std::string getTypeName( const bool verbose_name = true,
                           const bool lowercase = true ) const;

  //! Method for converting the type to a property tree
  virtual Utility::PropertyTree toPropertyTree() const = 0;
  
  //! Method for initializing the object from a property tree
  virtual void fromPropertyTree( const Utility::PropertyTree& node,
                                 std::vector<std::string>& unused_children ) = 0;
  
  //! Method for initializing the object from a property tree
  void fromPropertyTree( const Utility::PropertyTree& node,
                         const bool log_unused_children = true );

protected:

  //! Return the type name
  virtual std::string getTypeNameImpl( const bool verbose_name ) const = 0;

  //! Add the data to a property tree
  template<typename... Types>
  Utility::PropertyTree toPropertyTreeImpl(
                  const std::tuple<const std::string&,Types&>&... data ) const;

  //! Extract an array from a node
  template<template<typename,typename...> class Container>
  static void extractArrayFromNode( const Utility::PropertyTree& array_data,
                                    Container<double>& array,
                                    const std::string& type_name );
  
  //! Extract a value from a node
  template<typename QuantityType>
  static void extractValueFromNode( const Utility::PropertyTree& value_data,
                                    QuantityType& value,
                                    const std::string& type_name );

  //! Extract an array
  template<template<typename,typename...> class Container>
  static void extractArray( const Utility::Variant& array_data,
                            Container<double>& array,
                            const std::string& type_name );
  
  //! Extract a value
  template<typename QuantityType>
  static void extractValue( const Utility::Variant& value_data,
                            QuantityType& value,
                            const std::string& type_name );

  //! The data importance enum
  enum ExtractedDataType{ REQUIRED_DATA = true, OPTIONAL_DATA = false };

  /*! The data extractor type
   * \details The PropertyTreeCompatibleObject::extractArrayFromNode and 
   * PropertyTree::extractValueFromNode methods can be used as basic
   * data extractors (use std::bind to create the required function
   * signature).
   */
  typedef std::function<void(const Utility::PropertyTree&)> DataExtractor;

  /*! The data extractor map type
   * \details Key = property tree node key
   * Value0 = minimal match string used to identify node keys
   * Value1 = data importance (required/optional)
   * Value2 = data extractor
   */
  typedef std::map<std::string,std::tuple<const std::string,const ExtractedDataType,DataExtractor> > DataExtractorMap;

  //! Extract from a property tree
  void fromPropertyTreeImpl( const Utility::PropertyTree& node,
                             std::vector<std::string>& unused_children,
                             DataExtractorMap& data_extractors );

  // Verify that the type is correct
  void verifyType( const Utility::Variant& type_data ) const;

private:

  // Check if the type name matches the required type name
  bool doesTypeNameMatch( const std::string type_name ) const;

  // Determine which data must be extracted from a property tree
  static void getRequiredDataKeys(
                        const DataExtractorMap& data_extractors,
                        std::map<std::string,bool>& required_data_keys ) const;

  // Extract the data from the property tree
  bool extractDataFromPropertyTree(
                                   const Utility::PropertyTree& node,
                                   std::vector<std::string>& unused_children,
                                   DataExtractorMap& data_extractors,
                                   std::map<std::string,bool>& required_data );

  // Determine the data extractor key that best matches the node key
  static DataExtractorMap::iterator determineBestKeyMatch(
                                      const std::string& node_key,
                                      const DataExtractorMap& data_extractors )
                
};

/*! \brief Specialization of Utility::ToPropertyTreeTraits for 
 * Utility::PropertyTreeCompatibleObject
 * \ingroup ptree_traits
 */
template<>
struct ToPropertyTreeTraits<PropertyTreeCompatibleObject>
{
  //! Convert an object of DerivedType to a Utility::PropertyTree
  static inline PropertyTree toPropertyTree(
                                       const PropertyTreeCompatibleObject& obj,
                                       const bool )
  { return obj.toPropertyTree(); }
};

/*! \brief Partial specialization of Utility::ToPropertyTreeTraits for 
 * types that inherit from Utility::PropertyTreeCompatibleObject
 * \ingroup ptree_traits
 */
template<typename DerivedType>
struct ToPropertyTreeTraits<DerivedType,typename std::enable_if<std::is_base_of<PropertyTreeCompatibleObject,DerivedType>::value>::type> : public ToPropertyTreeTraits<PropertyTreeCompatibleObject>
{ /* ... */ };

/*! \brief Overload of Utility::toPropertyTree for
 * Utility::PropertyTreeCompatibleObject
 *
 * The data inlining default value will be retrieved from the 
 * Utility::PropertyTreeCompatibleObject that is passed in.
 * \ingroup ptree
 */
template<typename DerivedType>
inline typename std::enable_if<std::is_base_of<PropertyTreeCompatibleObject,DerivedType>::value,Utility::PropertyTree>::type
toPropertyTree( const DerivedType& obj )
{
  return Utility::ToPropertyTreeTraits<PropertyTreeCompatibleObject>::toPropertyTree( obj, false );
}

/*! \brief Specialization of Utility::FromPropertyTreeTraits for types that
 * inherit from Utility::PropertyTreeCompatibleObject
 * \ingroup ptree_traits
 */
template<typename DerivedType>
struct FromPropertyTreeTraits<DerivedType,typename std::enable_if<std::is_base_of<PropertyTreeCompatibleObject,DerivedType>::value && !std::is_abstract<DerivedType>::value>::type>
{
  //! The type that a property tree will be converted to
  typedef DerivedType ReturnType;
  
  //! Convert the property tree to an object of ReturnType
  template<template<typename,typename...> class STLCompliantSequenceContainer>
  static inline ReturnType fromPropertyTree(
                  const PropertyTree& ptree,
                  STLCompliantSequenceContainer<std::string>& unused_children )
  { 
    ReturnType obj;

    std::vector<std::string> unused_children_copy;

    obj.fromPropertyTree( ptree, unused_children );

    if( unused_children_copy.size() > 0 )
    {
      unused_children.insert( unused_children.end(),
                              unused_children_copy.begin(),
                              unused_children_copy.end() );
    }
    
    return obj;
  }

  //! Convert the property tree to an object of type T
  static inline ReturnType fromPropertyTree(
                                    const PropertyTree& ptree,
                                    std::vector<std::string>& unused_children )
  { 
    ReturnType obj;

    obj.fromPropertyTree( ptree, unused_children );

    return obj;
  }
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_PropertyTreeCompatibleObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTreeCompatibleObject.hpp
//---------------------------------------------------------------------------//
