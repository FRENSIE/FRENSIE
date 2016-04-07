//---------------------------------------------------------------------------//
//!
//! \file   samplePhotonDopplerDistributionCore.hpp
//! \author Alex Robinson
//! \brief  function decl. for generating samples from a Doppler broadened
//!         photon energy distribution
//!
//---------------------------------------------------------------------------//

#ifndef SAMPLE_PHOTON_DOPPLER_DISTRIBUTION_CORE_HPP
#define SAMPLE_PHOTON_DOPPLER_DISTRIBUTION_CORE_HPP

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

//! Initialize the Doppler broadened photon energy distribution
void initializeACEDistribution( 
                             const Data::XSSEPRDataExtractor& data_extractor,
                             const int model_type,
                             const int raw_subshell,
                             std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>& doppler_dist );

//! Initialize the Doppler broadened photon energy distribution
void initializeNativeDistribution( 
             const Data::ElectronPhotonRelaxationDataContainer& data_container,
             const int model_type,
             const int raw_subshell,
             std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>& doppler_dist );

//! Generate the samples from the desired distribution
int samplePhotonDopplerDistributionCore(
         const std::shared_ptr<const MonteCarlo::DopplerBroadenedPhotonEnergyDistribution>&
         doppler_dist,
         const double incoming_energy,
         const double scattering_angle_cosine,
         const int raw_subshell,
         const int model_type,
         const int num_samples,
         Teuchos::Array<double>& pdf_evaluation_cosines,
         std::shared_ptr<std::ofstream>& sample_ofile,
         std::shared_ptr<std::ofstream>& dist_ofile );

#endif // end SAMPLE_PHOTON_DOPPLER_DISTRIBUTION_CORE_HPP

//---------------------------------------------------------------------------//
// end samplePhotonDopplerDistributionCore.hpp
//---------------------------------------------------------------------------//
