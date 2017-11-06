//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistribution_def.hpp
//! \author Alex Robinson
//! \brief  One-dimension distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_DEF_HPP
#define UTILITY_ONE_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ComparisonPolicy.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace Utility{ 

// Check if the type name matches the distribution type name
/*! \details The type name provided will be checked against the distribution 
 * type name returned from getDistributionTypeName( false, true ).
 */
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::doesTypeNameMatch( const std::string type_name ) const
{
  std::string lower_type_name = boost::algorithm::to_lower_copy( type_name );

  return lower_type_name.find(this->getDistributionTypeName( false, true )) < lower_type_name.size();
}

// Test if the distribution is tabular
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isTabular() const
{
  return false;
}

// Test if the distribution is compatible with the interpolation type
/*! \details Some higher-level classes use the output of the OneDDistribution
 * methods to do interpolations. This method can be used to check that the
 * requested interpolation policy can be safetly used with the distribution's
 * output.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InterpPolicy>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isCompatibleWithInterpType() const
{
  // Check if interpolation can be used
  if( this->canInterpolationBeUsed() )
  {
    return
      this->isIndepVarCompatibleWithProcessingType(
                               typename InterpPolicy::IndepVarProcessingTag() )
         &&
      this->isDepVarCompatibleWithProcessingType(
                               typename InterpPolicy::DepVarProcessingTag() );
  }
  else
    return false;
}

// Test if interpolation can ever be used
/*! \details This can be used as an override if intepolation should never
 * be used with a particular distribution (e.g. Utility::DeltaDistribution).
 * In general, only continuous distributions should be used with an
 * interpolation scheme.
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::canInterpolationBeUsed() const
{
  if( this->isContinuous() )
    return true;
  else
    return false;
}

// Test if the independent variable is compatible with Lin processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return true;
}
  
// Test if the independent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return LogLog::isIndepVarInValidRange( this->getLowerBoundOfIndepVar() ) &&
    LogLog::isIndepVarInValidRange( this->getUpperBoundOfIndepVar() );
}

// Test if the dependent variable is compatible with Lin processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return true;
}

// Test if the dependent variable is compatible with Log processing
/*! \details It may be necessary to override this default behavior
 * (e.g. Utility::TabularDistribution).
 */
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return !this->canDepVarBeZeroInIndepBounds();
}

namespace Details{

//! Helper class for placing data in an output stream
template<size_t I, typename TupleType, typename Enabled = void>
struct DataOStreamHelper
{
  static inline void placeElementInOStream( std::ostream& os,
                                            const TupleType& data )
  {
    os << Utility::get<I>( data )
       << Utility::next_container_element_char << " ";

    DataOStreamHelper<I+1,TupleType>::placeElementInOStream( os, data );
  }
};

//! Specialization of DataOStreamHelper for parameter packs of I = TupleSize-1
template<size_t I, typename TupleType>
struct DataOStreamHelper<I,TupleType,typename std::enable_if<I==Utility::TupleSize<TupleType>::value-1>::type>
{
  static inline void placeElementInOStream( std::ostream& os,
                                            const TupleType& data )
  { os << Utility::get<I>( data ); }
};

//! Specialization of DataOStreamHelper for parameter packs of I = TupleSize
template<size_t I, typename TupleType>
struct DataOStreamHelper<I,TupleType,typename std::enable_if<I==Utility::TupleSize<TupleType>::value>::type>
{
  static inline void placeElementInOStream( std::ostream&, const TupleType& )
  { /* ... */ }
};
  
} // end Details namespace

// Add data to the stream
template<typename IndependentUnit, typename DependentUnit>
template<typename... Types>
inline void UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::toStreamImpl( std::ostream& os, const Types&... data ) const
{
  os << Utility::container_start_char
     << this->getDistributionTypeName( true, false )
     << Utility::next_container_element_char << " ";

  Details::DataOStreamHelper<0,decltype(std::tie(data...))>::placeElementInOStream( os, std::tie(data...) );

  os << Utility::container_end_char;
}

// Extract data from the stream
/*! \details The distribution data will be extracted from the stream and
 * stored in a Utility::VariantList. If the distribution type cannot be 
 * verified an exception will be thrown.
 */
template<typename IndependentUnit, typename DependentUnit>
inline void UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::fromStreamImpl( std::istream& is, VariantList& distribution_data )
{
  try{
    Utility::fromStream( is, distribution_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "Could not extract the distribution data from "
                           "the stream!" );

  if( distribution_data.size() > 1 )
  {
    this->verifyDistributionType( distribution_data.front() );

    distribution_data.pop_front();
  }
  else
  {
    THROW_EXCEPTION( Utility::StringConversionException,
                     "The "
                     << this->getDistributionTypeName(true, true) <<
                     "could not be constructed because the type could not be "
                     "verified!" );
  }
}

// Check for unused stream data
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::checkForUnusedStreamData( const VariantList& distribution_data ) const
{
  // Check if there is any superfluous data
  if( !distribution_data.empty() )
  {
    FRENSIE_LOG_TAGGED_WARNING( this->getDistributionTypeName( true, false ),
                                "Superfluous data was encountered during "
                                "initialization from stream ("
                                << distribution_data << ")!" );
  }
}

// Add the data to an inlined property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::toInlinedPropertyTreeImpl() const
{
  Utility::PropertyTree ptree;

  ptree.put_value( *this );

  return ptree;
}

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
template<typename IndependentUnit, typename DependentUnit>
template<typename... Types>
Utility::PropertyTree UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::toPropertyTreeImpl(
                   const std::tuple<std::string&,Types&>&... data ) const
{
  Utility::PropertyTree ptree;

  // Add the distribution type name to the property tree
  ptree.put( "type", this->getDistributionTypeName( true, false ) );

  // Add the distribution data
  Details::ToPropertyTreeHelper<0,decltype(std::tie(data...))>::placeElementInPropertyTree( ptree, std::tie(data...) );

  return ptree;
}

// Extract froman inlined property tree
/*! \details The distribution data in the property tree node must be
 * inlined (i.e. node.size() == 0).
 */
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::fromInlinedPropertyTreeImpl( const Utility::PropertyTree& node )
{
  std::istringstream iss( node.data().toString() );

  try{
    this->fromStream( iss );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              Utility::PropertyTreeConversionException,
                              "Could not create the "
                              << this->getDistributionTypeName(true, true) <<
                              "!" );
}

// Extract from a property tree
/*! \details The distribution data in the property tree node cannot be inlined
 * (i.e. node.size() != 0 ). Once distribution data is encountered and 
 * extracted its extract will be removed from the extractors list. If an 
 * extractor is left in the list after this method finishes it is an indication
 * that the data was not encountered in the property tree.
 */
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::fromPropertyTreeImpl(
                                     const Utility::PropertyTree& node,
                                     std::vector<std::string>& unused_children,
                                     DataExtractorList& data_extractors )
{
  bool type_verified = false;

  for( Utility::PropertyTree::const_iterator node_it = node.begin();
       node_it != node.end();
       ++node_it )
  {
    std::string child_node_key =
      boost::algorithm::to_lower_copy( node_it->first );

    // Verify the type
    if( child_node_key.find( "type" ) < child_node_key.size() )
    {
      if( !type_verified )
      {
        try{
          this->verifyDistributionType( node_it->second.data() );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the "
                                    << this->getDistributionTypeName(true, true) <<
                                    "!" );
        type_verified = true;
        continue;
      }
    }
    // Extract data required by calling distribution
    else
    {
      DataExtractorList::iterator data_extractor_it = data_extractors.begin();
      DataExtractorList::iterator data_extractor_end = data_extractors.end();

      bool data_extracted = false;

      while( data_extractor_it != data_extractor_end )
      {
        if( child_node_key.find( data_extractor_it->first ) <
            child_node_key.size() )
        {
          // Extract the data from the child node
          data_extractor_it->second( node_it->second );
          data_extracted = true;

          // Remove the data extractor
          data_extractors.erase( data_extractor_it );

          break;
        }
          
        ++data_extractor_it;
      }

      // Data has been extracted - go to the next child node
      if( data_extracted )
        continue;
    }

    // If we get to this point the node is unused
    if( child_node_key.find( PTREE_COMMENT_NODE_KEY ) >=
        child_node_key.size() )
    {
      unused_children.push_back( node_it->first );
    }
  }

  // Make sure that the distribution type was verified
  TEST_FOR_EXCEPTION( !type_verified,
                      Utility::PropertyTreeConversionException,
                      "The "
                      << this->getDistributionTypeName(true, true) <<
                      "could not be constructed because the type could not be "
                      "verified!" );
}

// Verify that the distribution type is correct
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::verifyDistributionType( const Utility::Variant& type_data ) const
{
  TEST_FOR_EXCEPTION( !this->doesTypeNameMatch( type_data.toString() ),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName(true, true) <<
                      "cannot be constructed because the distribution type ("
                      << type_data.toString() << ") does not match!" );
}

// Test if the distribution has the same bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::hasSameBounds(
	const UnitAwareOneDDistribution<IndependentUnit,DependentUnit>& distribution ) const
{
  return
    (RelativeErrorComparisonPolicy::compare( this->getUpperBoundOfIndepVar(),
                                             distribution.getUpperBoundOfIndepVar(),
                                             1e-9 ) ||
     CloseComparisonPolicy::compare( this->getUpperBoundOfIndepVar(),
                                     distribution.getUpperBoundOfIndepVar(),
                                     1e-9 )) &&
    (RelativeErrorComparisonPolicy::compare( this->getLowerBoundOfIndepVar(),
                                             distribution.getLowerBoundOfIndepVar(),
                                             1e-9 ) ||
     CloseComparisonPolicy::compare( this->getLowerBoundOfIndepVar(),
                                     distribution.getLowerBoundOfIndepVar(),
                                     1e-9 ));
}

// Check if data is inlined by default when converting to a property tree
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::isDataInlinedByDefault() const
{
  return false;
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareOneDDistribution<void,void> );
  
} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistribution_def.hpp
//---------------------------------------------------------------------------//
