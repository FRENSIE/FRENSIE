//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTreeConverter.hpp
//! \author Alex Robinson
//! \brief  The property tree converter class
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_CONVERTER_HPP
#define UTILITY_PROPERTY_TREE_CONVERBER_HPP

// Std Lib Includes
#include <string>
#include <memory>

// FRENSIE Includes
#include "Utility_PropertyTree.hpp"

namespace Utility{

//! The base property tree converter class
template<typename T>
class PropertyTreeConverter
{

public:

  //! Default constructor
  PropertyTreeConverter()
  { /* ... */ }

  //! Destructor
  virtual ~PropertyTreeConverter()
  { /* ... */ }

  //! Return the property tree type name associated with this converter
  virtual std::string getConcreteTypeName() const = 0;

  //! Convert the property tree to the desired type
  void convert( const Utility::PropertyTree& ptree,
                std::vector<std::string>& unused_children,
                std::shared_ptr<const T>& object ) const;

  //! Convert the property tree to the desired type
  void convert( const Utility::PropertyTree& ptree,
                std::vector<std::string>& unused_children,
                std::unique_ptr<const T>& object ) const;

protected:

  /*! Convert the property tree to the desired type
   *
   * The returned pointer must be heap-allocated (using new operator).
   */
  T* convertImpl( const Utility::PropertyTree& ptree,
                  std::vector<std::string>& unused_children ) const = 0;
};

// Convert the property tree to the desired type
template<typename T>
inline void PropertyTreeConverter<T>::convert(
                                 const Utility::PropertyTree& ptree,
                                 std::vector<std::string>& unused_children,
                                 std::shared_ptr<const T>& object ) const
{
  return std::shared_ptr<T>( this->convertImpl( ptree, unused_children ) );
}

// Convert the property tree to the desired type
template<typename T>
inline void PropertyTreeConverter<T>::convert(
                                 const Utility::PropertyTree& ptree,
                                 std::vector<std::string>& unused_children,
                                 std::unique_ptr<const T>& object ) const
{
  return std::unique_ptr<T>( this->convertImpl( ptree, unused_children ) );
}

} // end Utility namespace

#endif // end UTILITY_PROPERTY_TREE_CONVERBER_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTreeConverter.hpp
//---------------------------------------------------------------------------//
