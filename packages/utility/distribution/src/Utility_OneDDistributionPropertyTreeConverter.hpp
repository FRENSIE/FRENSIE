//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionPropertyTreeConverter.hpp
//! \author Alex Robinson
//! \brief  The OneDDistribution property tree converter class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_PROPERTY_TREE_CONVERTER_HPP
#define UTILITY_ONE_D_DISTRIBUTION_PROPERTY_TREE_CONVERTER_HPP

// FRENSIE Includes
#include "Utility_PropertyTreeConverter.hpp"
#include "Utility_PropertyTreeConversionFactory.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace Utility{

//! The base Utility::OneDDistribution property tree converter class
template<typename DistributionType, typename BaseDistributionType>
class OneDDistributionPropertyTreeConverter : public PropertyTreeConverter<BaseDistributionType>
{

  // Typedef for this type
  typedef OneDDistributionPropertyTreeConverter<DistributionType,BaseDistributionType> ThisType;

public:

  //! Destructor
  virtual ~OneDDistributionPropertyTreeConverter()
  { /* ... */ }

  //! Return the property tree type name associated with this converter
  std::string getConcreteTypeName() const override;

protected:

  //! Default constructor
  OneDDistributionPropertyTreeConverter()
  { /* ... */ }

  /*! Convert the property tree to the desired type
   *
   * The returned pointer will be heap-allocated (using new operator).
   */
  BaseDistributionType* convertImpl(
                    const Utility::PropertyTree& ptree,
                    std::vector<std::string>& unused_children ) const override;
private:

  // Extract the type name from an inlined property tree
  static std::string extractTypeNameFromInlinedPropertyTree(
                                          const Utility::PropertyTree& ptree );

  // Register this converter with the factory
  static bool registerWithFactory();

  // Used for factory registration
  static const bool s_registered;
};
  
} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_PROPERTY_TREE_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionPropertyTreeConverter.hpp
//---------------------------------------------------------------------------//
