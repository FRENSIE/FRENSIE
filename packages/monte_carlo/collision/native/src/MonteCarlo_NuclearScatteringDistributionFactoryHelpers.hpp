//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp
//! \author Alex Robinson
//! \brief  Nuclear scattering distribution factory helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_FACTORY_HELPERS_HPP
#define MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_FACTORY_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Array.hpp>

namespace MonteCarlo{

//! Calculate the AND/DLW block distribution array sizes
void calculateDistArraySizes(
                    const Teuchos::ArrayView<const double>& location_block,
		    const Teuchos::ArrayView<const double>& data_block,
                    Teuchos::Array<unsigned>& dist_array_sizes );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp
//---------------------------------------------------------------------------//
