//---------------------------------------------------------------------------//
//!
//! \file   DataGen_EPRDataGeneratorHelpers.hpp
//! \author Luke Kersting
//! \brief  The EPR data generator helpers declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_EPR_DATA_GENERATOR_HELPERS_HPP
#define DATA_GEN_EPR_DATA_GENERATOR_HELPERS_HPP

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "DataGen_StandardMomentPreservingElectronDataGenerator.hpp"

namespace DataGen{

//----------------------------------------------------------------------------//
//      ****Moment Preserving****
//----------------------------------------------------------------------------//

//! Create the moment preserving data generator
std::shared_ptr<DataGen::StandardMomentPreservingElectronDataGenerator> createMomentPreservingDataGenerator(
    const unsigned atomic_number,
    const Data::ElectronPhotonRelaxationDataContainer& native_eedl_data,
    const MonteCarlo::TwoDInterpolationType two_d_interp,
    const MonteCarlo::TwoDGridType two_d_grid,
    const double min_electron_energy,
    const double max_electron_energy,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol );

} // end DataGen namespace

#endif // end DATA_GEN_EPR_DATA_GENERATOR_HELPERS_HPP

//---------------------------------------------------------------------------//
// end DataGen_EPRDataGeneratorHelpers.hpp
//---------------------------------------------------------------------------//
