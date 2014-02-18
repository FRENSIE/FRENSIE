//---------------------------------------------------------------------------//
//!
//! \file   tstCylindricalSpatialDistribution.cpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "OneDDistribution.hpp"
#include "PowerDistribution.hpp"
#include "UniformDistribution.hpp"
#include "SpatialDistribution.hpp"
#include "CylindricalSpatialDistribution.hpp"
#include "PhysicalConstants.hpp"
#include "RandomNumberGenerator.hpp"

Teuchos::RCP<FACEMC::SpatialDistribution> spatial_distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution( 
		       Teuchos::RCP<FACEMC::SpatialDistribution>& distribution,
		       const FACEMC::Axis axis )
{
  // Power distribution in r dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    r_distribution( new FACEMC::PowerDistribution<1u>( 2.0, 0.0, 1.0 ) );

  // Uniform distribution in theta dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0, 
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );

  // Uniform distribution in axis dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    axis_distribution( new FACEMC::UniformDistribution( -1.0, 1.0, 1.0 ) );

  spatial_distribution.reset( new FACEMC::CylindricalSpatialDistribution( 
							   r_distribution,
							   theta_distribution,
							   axis_distribution,
							   1.0,
							   1.0,
							   1.0,
							   axis ) );
}

//---------------------------------------------------------------------------//
// end tstCylindricalSpatialDistribution.cpp
//---------------------------------------------------------------------------//

