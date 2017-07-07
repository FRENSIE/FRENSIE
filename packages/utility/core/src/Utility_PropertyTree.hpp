//---------------------------------------------------------------------------//
//!
//! \file   Utility_PropertyTree.hpp
//! \author Alex Robinson
//! \brief  Boost property tree helper functions and extensions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PROPERTY_TREE_HPP
#define UTILITY_PROPERTY_TREE_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/info_parser.hpp>

// FRENSIE Includes
#include "Utility_Variant.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

/*! \defgroup ptree Property Tree
 */

namespace Utility{

/*! The property tree
 *
 * \ingroup ptree
 */
typedef boost::property_tree::basic_ptree<std::string,Utility::Variant> PropertyTree;

/*! The comment node key
 * \ingroup ptree
 */
#define PTREE_COMMENT_NODE_KEY "comment"

/*! Check if the property tree node stores a JSON array
 * \ingroup ptree
 */
bool doesPTreeNodeStoreJSONArray( const Utility::PropertyTree& ptree );

/*! Convert property tree node to a VariantVector
 * \ingroup ptree
 */
VariantVector convertPTreeNodeToVariantVector( const Utility::PropertyTree& ptree );

/*! Convert property tree node to a VariantDeque
 * \ingroup ptree
 */
VariantDeque convertPTreeNodeToVariantDeque( const Utility::PropertyTree& ptree );
  
/*! Convert property tree node to a VariantList
 * \ingroup ptree
 */
VariantList convertPTreeNodeToVariantList( const Utility::PropertyTree& ptree );
  
/*! Convert property tree node to a VariantForwardList
 * \ingroup ptree
 */
VariantForwardList convertPTreeNodeToVariantForwardList( const Utility::PropertyTree& ptree );
  
/*! Convert property tree node to a VariantMap
 * \ingroup ptree
 */
VariantMap convertPTreeNodeToVariantMap( const Utility::PropertyTree& ptree );

/*! Specialization of Utility::ToStringTraits for Utility::PropertyTree
 * \ingroup ptree
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<PropertyTree>
{
  //! Convert a PropertyTree to a string
  static inline std::string toString( const PropertyTree& obj )
  {
    std::ostringstream oss;

    ToStringTraits<PropertyTree>::toStream( oss, obj );

    return boost::algorithm::trim_copy(oss.str());
  }

  //! Place the PropertyTree in a stream
  static inline void toStream( std::ostream& os, const PropertyTree& obj )
  { boost::property_tree::write_json( os, obj, false ); }
};

/*! Specialization of Utility::FromStringTraits for Utility::PropertyTree
 * \ingroup ptree
 * \ingroup from_string_traits
 */
template<>
struct FromStringTraits<PropertyTree>
{
  //! The type that a string will be converted to
  typedef PropertyTree ReturnType;

  //! Convert the string to a PropertyTree object
  static inline ReturnType fromString( const std::string& obj_rep )
  {
    std::istringstream iss( obj_rep );

    ReturnType ptree;

    FromStringTraits<PropertyTree>::fromStream( iss, ptree );

    return ptree;
  }

  //! Extract a ProperyTree from a stream
  static inline void fromStream( std::istream& is,
                                 PropertyTree& obj,
                                 const std::string& delims = std::string() )
  {
    try{
      boost::property_tree::read_json( is, obj );
    }
    EXCEPTION_CATCH_RETHROW_AS( boost::property_tree::json_parser_error,
                                Utility::StringConversionException,
                                "Could not extract a property tree from the "
                                "stream!" );
  }
};
  
} // end Utility namespace

namespace boost {

namespace property_tree {

/*! \brief Specialize boost::property_tree::translator_between so that we can
 * use a custom translator between Utility::Variant and other types.
 * \ingroup ptree
 */
template<typename T>
struct translator_between<Utility::Variant,T>;
  
} // end property_tree namespace
  
} // end boost namespace

namespace std{

/*! Place a Utility::PropertyTree in a stream
 * \ingroup ptree
 */
inline std::ostream& operator<<( std::ostream& os,
                                 const Utility::PropertyTree& ptree )
{
  Utility::toStream( os, ptree );

  return os;
}

/*! Extract a Utility::PropertyTree from a stream
 * \ingroup ptree
 */
inline std::istream& operator>>( istream& is,
                                 Utility::PropertyTree& ptree )
{
  Utility::fromStream( is, ptree );

  return is;
}
  
} // end std namespace

//---------------------------------------------------------------------------//
// Template Inludes
//---------------------------------------------------------------------------//

#include "Utility_PropertyTree_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_PROPERTY_TREE_HPP

//---------------------------------------------------------------------------//
// end Utility_PropertyTree.hpp
//---------------------------------------------------------------------------//
