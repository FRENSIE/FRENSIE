//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Directional distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_DirectionalDistributionFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Create the directional distribution represented by the parameter list
Teuchos::RCP<DirectionalDistribution>
DirectionalDistributionFactory::createDistribution( 
			       const Teuchos::ParameterList& distribution_rep )
{

}

// Validate a distribution representation
void DirectionalDistributionFactory::validateDistributionRep( 
			       const Teuchos::ParameterList& distribution_rep )
{

}

// Validate the axis name
void DirectionalDistributionFactory::validateAxisName( 
						 const std::string& axis_name )
{

}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_DirectionalDistributionFactory.cpp
//---------------------------------------------------------------------------//
