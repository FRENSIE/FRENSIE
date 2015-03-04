//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The neutron scattering distribution base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringDistribution.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NeutronScatteringDistribution::NeutronScatteringDistribution( 
					     const double atomic_weight_ratio )
  : d_atomic_weight_ratio( atomic_weight_ratio )
{
  // Make sure the atomic weight ratio is valid
  testPrecondition( atomic_weight_ratio > 0.0 );
  testPrecondition( atomic_weight_ratio < 
		    std::numeric_limits<double>::infinity() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
