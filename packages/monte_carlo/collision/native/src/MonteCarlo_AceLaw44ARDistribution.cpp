//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw44ARDistribution.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The law 44 AR distribution base class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AceLaw44ARDistribution.hpp"

namespace MonteCarlo{

// Constructor
AceLaw44ARDistribution::AceLaw44ARDistribution(
		  const Teuchos::ArrayView<const double>& outgoing_energy_grid,
		  const Teuchos::ArrayView<const double>& A_array,
		  const Teuchos::ArrayView<const double>& R_array )
  : d_outgoing_energy_grid( outgoing_energy_grid ),
    d_A( A_array ),
    d_R( R_array )
{
  // Make sure the arrays have the same size
  testPrecondition( outgoing_energy_grid.size() > 0 );
  testPrecondition( outgoing_energy_grid.size() == A_array.size() );
  testPrecondition( outgoing_energy_grid.size() == R_array.size() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw44ARDistribution.cpp
//---------------------------------------------------------------------------//
