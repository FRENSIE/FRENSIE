//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTreeConversionFactory.hpp
//! \author Alex Robinson
//! \brief  Property tree conversion factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_CONVERSION_FACTORY_HPP
#define UTILITY_PROPERTY_TREE_CONVERSION_FACTORY_HPPw

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "Utility_PropertyTreeConverter.hpp"
#include "Utility_PropertyTree.hpp"
#include "Utility_Map.hpp"

namespace Utility{

//! The property tree conversion factory
template<typename T>
class PropertyTreeConversionFactory
{

public:

  //! The converter pointer type
  typedef std::shared_ptr<const Utility::PropertyTreeConverter<T> > ConverterPtr;

  //! The type extractor type
  typedef std::function<std::string(const Utility::PropertyTree&)> InlineTypeExtractor;

  //! Constructor
  PropertyTreeConversionFactory();

  //! Destructor
  virtual ~PropertyTreeConversionFactory()
  { /* ... */ }

  //! Register a converter with the factory
  static bool registerConverter( const ConverterPtr& converter );

  //! Register an inline property tree type extraction method
  static bool registerInlineTypeExtractionMethod(
                             const InlineTypeExtractor inline_type_extractor );

  //! Get the type key
  virtual std::string getTypeKey() const;

  //! Convert the object represented by the property tree
  void convert( const Utility::PropertyTree& ptree,
                std::vector<std::string>& unused_children,
                std::shared_ptr<const T>& object );

  //! Convert the object represented by the property tree
  void convert( const Utility::PropertyTree& ptree,
                std::vector<std::string>& unused_children,
                std::unique_ptr<const T>& object );

private:

  //! Default inline type extraction method
  static std::string extractInlineType( const Utility::PropertyTree& ptree );

  //! Extract the type
  std::string extractType( const Utility::PropertyTree& ptree );

  //! Create the object represented by the property tree
  template<template<typename,typename...> class SmartPointer>
  void convertImpl( const Utility::PropertyTree& ptree,
                    std::vector<std::string>& unused_children,
                    SmartPointer<const T>& object );

  // The property tree converters
  typedef std::map<std::string,ConverterPtr> ConverterMap;
  static ConverterMap s_converters;

  // The inline type extraction method
  static InlineTypeExtractor s_inline_type_extractor;

  // The property tree converter aliases
  typedef std::map<std::string,std::string> ConverterAliasMap;
  ConverterAliasMap d_converter_aliases;
};

} // end Utility namespace

#endif // end UTILITY_PROPERTY_TREE_CONVERSION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTreeConversionFactory.hpp
//---------------------------------------------------------------------------//
