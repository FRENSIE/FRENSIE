//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardOneDDistributionEntryConverter.hpp
//! \author Alex Robinson
//! \brief  standard 1D distribution parameter entry converter class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_HPP
#define UTILITY_STANDARD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_HPP

// FRENSIE Includes
#include "Utility_OneDDistributionEntryConverter.hpp"

namespace Utility{

//! The standard 1D distribution parameter entry converter
template<typename Distribution>
class StandardOneDDistributionEntryConverter : public OneDDistributionEntryConverter
{

public:

  //! Default constructor
  StandardOneDDistributionEntryConverter();
  
  //! Return the OneDDistribution type name associated with this object
  virtual const std::string getTypeName() const;

  //! Return the OneDDistribution represented in the parameter entry
  virtual Teuchos::RCP<OneDDistribution> getDistributionRCP( 
	  const Teuchos::RCP<const Teuchos::ParameterEntry>& entry ) const;

  //! Return the OneDDistribution represented in the parameter entry
  virtual std::shared_ptr<OneDDistribution> getDistributionSharedPtr( 
	  const Teuchos::RCP<const Teuchos::ParameterEntry>& entry ) const;

  //! Return the parameter entry corresponding to the OneDDistribution object
  virtual Teuchos::RCP<Teuchos::ParameterEntry> getParameterEntry(
		const Teuchos::RCP<OneDDistribution>& distribution ) const;

};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_StandardOneDDistributionEntryConverter_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_STANDARD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardOneDDistributionEntryConverter.hpp
//---------------------------------------------------------------------------//
