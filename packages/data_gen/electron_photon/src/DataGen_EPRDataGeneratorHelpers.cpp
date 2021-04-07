//---------------------------------------------------------------------------//
//!
//! \file   DataGen_EPRDataGeneratorHelpers.cpp
//! \author Luke Kersting
//! \brief  The EPR data generator helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_EPRDataGeneratorHelpers.hpp"

namespace DataGen{

//----------------------------------------------------------------------------//
//      ****Moment Preserving****
//----------------------------------------------------------------------------//

//! Create the moment preserving data generator
std::shared_ptr<DataGen::StandardMomentPreservingElectronDataGenerator> createMomentPreservingDataGenerator(
    const unsigned atomic_number,
    const Data::ElectronPhotonRelaxationDataContainer& native_data,
    const MonteCarlo::TwoDInterpolationType two_d_interp,
    const MonteCarlo::TwoDGridType two_d_grid,
    const double min_electron_energy,
    const double max_electron_energy,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol )
{
  auto ptr =
    std::make_shared<const Data::ElectronPhotonRelaxationDataContainer>( native_data );

  std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
    data_ptr = ptr;

  std::shared_ptr< DataGen::StandardMomentPreservingElectronDataGenerator>
    data_generator( new StandardMomentPreservingElectronDataGenerator(
                            atomic_number,
                            data_ptr,
                            two_d_interp,
                            two_d_grid,
                            min_electron_energy,
                            max_electron_energy,
                            cutoff_angle_cosine,
                            tabular_evaluation_tol ) );

  return data_generator;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_EPRDataGeneratorHelpers.cpp
//---------------------------------------------------------------------------//
