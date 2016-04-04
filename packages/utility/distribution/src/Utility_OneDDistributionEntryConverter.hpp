//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionEntryConverter.hpp
//! \author Alex Robinson
//! \brief  1D distribution parameter entry converter base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_HPP
#define UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace Utility{

//! The 1D distribution parameter entry converter base class
class OneDDistributionEntryConverter
{

public:

  //! Return the OneDDistribution type name associated with this object
  virtual const std::string getTypeName() const = 0;

  //! Return the OneDDistribution represented in the parameter entry
  virtual Teuchos::RCP<OneDDistribution> getDistributionRCP( 
	  const Teuchos::RCP<const Teuchos::ParameterEntry>& entry ) const = 0;

  //! Return the OneDDistribution represented in the parameter entry
  virtual std::shared_ptr<OneDDistribution> getDistributionSharedPtr( 
	  const Teuchos::RCP<const Teuchos::ParameterEntry>& entry ) const = 0;

  //! Return the parameter entry corresponding to the OneDDistribution object
  virtual Teuchos::RCP<Teuchos::ParameterEntry> getParameterEntry(
		const Teuchos::RCP<OneDDistribution>& distribution ) const = 0;
};

} // end Utility namespace

#endif // end UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionEntryConverter.hpp
//---------------------------------------------------------------------------//
