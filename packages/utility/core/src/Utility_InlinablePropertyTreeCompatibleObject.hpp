//---------------------------------------------------------------------------//
//!
//! \file   Utility_InlinablePropertyTreeCompatibleObject.hpp
//! \author Alex Robinson
//! \brief  Inlinable property tree compatible object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INLINABLE_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP
#define UTILITY_INLINABLE_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP

// FRENSIE Includes
#include "Utility_PropertyTreeCompatibleObject.hpp"
#include "Utility_StreamableObject.hpp"

namespace Utility{

/*! \brief The base class for Utility::PropertyTree compatible objects and
 * streamable objects
 */
class InlinablePropertyTreeCompatibleObject : public PropertyTreeCompatibleObject,
                                              public StreamableObject
{

public:

  //! Check if data can be inlined
  bool canDataBeInlined() const override;

  //! Check if data is inlined by default when converting to a property tree
  virtual bool isDataInlinedByDefault() const = 0;

  //! Method for converting the type to a property tree
  virtual Utility::PropertyTree toPropertyTree( const bool inline_data ) const = 0;

  //! Method for converting the type to a property tree
  Utility::PropertyTree toPropertyTree() const override;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is, const std::string& delims ) override;

  //! Method for initializing the object from an input stream
  using IStreamableObject::fromStream;

protected:

  //! Add data to the stream
  template<typename... Types>
  void toStreamImpl( std::ostream& os, const Types&... data ) const;

  //! Process the data that was extracted the stream
  virtual void fromStreamImpl( VariantList& stream_data ) = 0;

  //! Extract the data from a stream
  static Utility::Variant extractStreamData( std::istream& is,
                                             VariantList& stream_data );

  //! Add the data to an inlined property tree
  Utility::PropertyTree toInlinedPropertyTreeImpl() const;

  //! Extract from an inlined property tree
  void fromInlinedPropertyTreeImpl( const Utility::PropertyTree& node );

  //! Extract the type name from an inlined property tree
  static std::string getInlinedPropertyTreeTypeName(
                                           const Utility::PropertyTree& node );

private:

  // Check for unused stream data
  void checkForUnusedStreamData( const VariantList& stream_data ) const;
};

/*! \brief Specialization of Utility::ToPropertyTreeTraits for 
 * Utility::InlinablePropertyTreeCompatibleObject
 * \ingroup ptree_traits
 */
template<>
struct ToPropertyTreeTraits<InlinablePropertyTreeCompatibleObject>
{
  //! Convert an object of DerivedType to a Utility::PropertyTree
  static inline PropertyTree toPropertyTree(
                              const InlinablePropertyTreeCompatibleObject& obj,
                              const bool inline_data )
  { return obj.toPropertyTree( inline_data ); }
};

/*! \brief Overload of Utility::toPropertyTree for
 * Utility::PropertyTreeCompatibleObject
 *
 * The data inlining default value will be retrieved from the 
 * Utility::PropertyTreeCompatibleObject that is passed in.
 * \ingroup ptree
 */
template<typename DerivedType>
inline typename std::enable_if<std::is_base_of<InlinablePropertyTreeCompatibleObject,DerivedType>::value,Utility::PropertyTree>::type
toPropertyTree( const DerivedType& obj )
{
  return Utility::ToPropertyTreeTraits<InlinablePropertyTreeCompatibleObject>::toPropertyTree( obj, obj.isDataInlinedByDefault() );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InlinablePropertyTreeCompatibleObject_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INLINABLE_PROPERTY_TREE_COMPATIBLE_OBJECT_HPP

//---------------------------------------------------------------------------//
// end Utility_InlineablePropertyTreeCompatibleObject.hpp
//---------------------------------------------------------------------------//
