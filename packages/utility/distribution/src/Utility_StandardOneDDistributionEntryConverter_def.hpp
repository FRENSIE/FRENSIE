//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardOneDDistributionEntryConverter_def.hpp
//! \author Alex Robinson
//! \brief  standard 1D distribution parameter entry converter class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DEF_HPP
#define UTILITY_STANDARD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DEF_HPP

// Trilinos Includes
#include <Teuchos_TypeNameTraits.hpp>
#include <Teuchos_ParameterEntryXMLConverterDB.hpp>

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
template<typename Distribution>
StandardOneDDistributionEntryConverter<Distribution>::StandardOneDDistributionEntryConverter()
{
  TEUCHOS_ADD_TYPE_CONVERTER( Distribution );
}

// Return the OneDDistribution type name associated with this object
template<typename Distribution>
const std::string 
StandardOneDDistributionEntryConverter<Distribution>::getTypeName() const
{
  return Teuchos::TypeNameTraits<Distribution>::name();
}

// Return the OneDDistribution represented in the parameter entry
template<typename Distribution>
Teuchos::RCP<OneDDistribution> 
StandardOneDDistributionEntryConverter<Distribution>::getDistributionRCP( 
	       const Teuchos::RCP<const Teuchos::ParameterEntry>& entry ) const
{
  // Make sure the entry is valid
  testPrecondition( entry->getAny().typeName() == getTypeName() );
  
  return Teuchos::RCP<OneDDistribution>( new Distribution( 
				  Teuchos::getValue<Distribution>( entry ) ) );
}

// Return the OneDDistribution represented in the parameter entry
template<typename Distribution>
std::shared_ptr<OneDDistribution> 
StandardOneDDistributionEntryConverter<Distribution>::getDistributionSharedPtr(
	       const Teuchos::RCP<const Teuchos::ParameterEntry>& entry ) const
{
  // Make sure the entry is valid
  testPrecondition( entry->getAny().typeName() == getTypeName() );
  
  return std::shared_ptr<OneDDistribution>( new Distribution( 
				  Teuchos::getValue<Distribution>( entry ) ) );
}

// Return the parameter entry corresponding to the OneDDistribution object
template<typename Distribution>
Teuchos::RCP<Teuchos::ParameterEntry> 
StandardOneDDistributionEntryConverter<Distribution>::getParameterEntry(
		     const Teuchos::RCP<OneDDistribution>& distribution ) const
{
  return Teuchos::RCP<Teuchos::ParameterEntry>( new Teuchos::ParameterEntry(
		  *Teuchos::rcp_dynamic_cast<Distribution>( distribution ) ) );
}

} // end Utility namespace

#endif // end UTILITY_STANDARD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardOneDDistributionEntryConverter_def.hpp
//---------------------------------------------------------------------------//

