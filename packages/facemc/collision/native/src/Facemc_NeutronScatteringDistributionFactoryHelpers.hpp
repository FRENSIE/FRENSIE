//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringDistributionFactoryHelpers.hpp
//! \author Alex Robinson
//! \brief  Neutron scattering distribution factory helper function decls.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_DISTRIBUTION_FACTORY_HELPERS_HPP
#define FACEMC_NEUTRON_SCATTERING_DISTRIBUTION_FACTORY_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Array.hpp>

namespace Facemc{

//! Calculate the AND/DLW block distribution array sizes
void calculateDistArraySizes( 
                    const Teuchos::ArrayView<const double>& location_block,
		    const Teuchos::ArrayView<const double>& data_block,
                    Teuchos::Array<unsigned>& dist_array_sizes );

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_DISTRIBUTION_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringDistributionFactoryHelpers.hpp
//---------------------------------------------------------------------------//
