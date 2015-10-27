//---------------------------------------------------------------------------//
//!
//! \file   samplePhotonDistributionCore.hpp
//! \author Alex Robinson
//! \brief  function decl. for generating samples from a photon distribution
//!
//---------------------------------------------------------------------------//

#ifndef SAMPLE_PHOTON_DISTRIBUTION_CORE_HPP
#define SAMPLE_PHOTON_DISTRIBUTION_CORE_HPP

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"

int samplePhotonDistributionCore(
            const Teuchos::RCP<const MonteCarlo::PhotonScatteringDistribution>&
	    scattering_dist,
	    const Teuchos::Array<double>& energies,
	    const int samples,
	    const Teuchos::Array<double>& pdf_evaluation_cosines,
	    Teuchos::RCP<std::ofstream>& sample_ofile,
	    Teuchos::RCP<std::ofstream>& dist_ofile );

#endif // end SAMPLE_PHOTON_DISTRIBUTION_CORE_HPP

//---------------------------------------------------------------------------//
// end samplePhotonDistributionCore.hpp
//---------------------------------------------------------------------------//
