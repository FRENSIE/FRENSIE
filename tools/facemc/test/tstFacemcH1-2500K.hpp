//---------------------------------------------------------------------------//
//!
//! \file   tstFacemcH1-2500K.hpp
//! \author Alex Robinson
//! \brief  facemc executable verification test helpers for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

#ifndef TST_FACEMC_H1_2500K_HPP
#define TST_FACEMC_H1_2500K_HPP

// Std Lib Includes
#include <string>

// FRENSIE Includes
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"

//! Conduct a serial test
int conductSerialTest( int argc, 
                       char** argv,
                       const std::string& simulation_hdf5_file_name,
                       const bool surface_estimators_present );

//! Conduct a parallel test
int conductParallelTest( int argc,
                         char** argv,
                         const std::string& simulation_hdf5_file_name,
                         const bool surface_estimators_present );

//! Test the output of the H1-2500K simulation
bool testSimulationResults( const std::string& simulation_hdf5_file_name,
                            const bool surface_estimators_present );

//! Test estimator 1 data
bool testEstimator1Data( 
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler );

//! Test estimator 2 data
bool testEstimator2Data(
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler );

//! Test estimator 3 data
bool testEstimator3Data(
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler );

//! Test estimator 4 data
bool testEstimator4Data(
               const MonteCarlo::EstimatorHDF5FileHandler& hdf5_file_handler );
                 
                            

#endif // end TST_FACEMC_H1_2500K_HPP

//---------------------------------------------------------------------------//
// end tstFacemcH1-2500K.hpp
//---------------------------------------------------------------------------//
