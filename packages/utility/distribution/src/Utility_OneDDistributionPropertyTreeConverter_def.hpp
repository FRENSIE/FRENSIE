//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionPropertyTreeConverter_def.hpp
//! \author Alex Robinson
//! \brief  The OneDDistribution property tree converter class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_PROPERTY_TREE_CONVERTER_DEF_HPP
#define UTILITY_ONE_D_DISTRIBUTION_PROPERTY_TREE_CONVERTER_DEF_HPP

namespace Utility{

// Initialize static member data
template<typename DistributionType, typename BaseDistributionType>
bool OneDDistributionPropertyTreeConverter<DistributionType,BaseDistributionType>::s_registered = OneDDistributionPropertyTreeConverter<DistributionType,BaseDistributionType>::registerWithFactory();

// Return the property tree type name associated with this converter
template<typename DistributionType, typename BaseDistributionType>
std::string OneDDistributionPropertyTreeConverter<DistributionType,BaseDistributionType>::getTypeName() const override
{
  return DistributionType::typeName( false, false, " " );
}

// Convert the property tree to the desired type
template<typename DistributionType, typename BaseDistributionType>
BaseDistributionType* OneDDistributionPropertyTreeConverter<DistributionType,BaseDistributionType>::convertImpl(
                              const Utility::PropertyTree& ptree,
                              std::vector<std::string>& unused_children ) const
{
  BaseDistributionType* distribution = new DistributionType;

  distribution->fromPropertyTree( ptree, unused_children );
  
  return distribution;
}

// Register this converter with the factory
template<typename DistributionType, typename BaseDistributionType>
bool OneDDistributionPropertyTreeConverter<DistributionType,BaseDistributionType>::registerWithFactory()
{
  typedef PropertyTreeConversionFactory<BaseDistributionType> FactoryType;
  
  // Create the converter
  typename FactoryType::ConverterPtr converter( new ThisType );

  return FactoryType::registerConverter( converter ) &&
    FactoryType::registerInlineTypeExtractionMethod( &ThisType::extractTypeNameFromInlinedPropertyTree );      
}
  
} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_PROPERTY_TREE_CONVERTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionPropertyTreeConverter_def.hpp
//---------------------------------------------------------------------------//
