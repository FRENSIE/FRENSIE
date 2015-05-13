//---------------------------------------------------------------------------//
//!
//! \file   sample_csd.cpp
//! \author Alex Robinson
//! \brief  sample coherent scattering distribution tool
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <fstream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentPhotonScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_CoherentPhotonScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

// Generate the samples from the distribution
void generateSamples(
  const double energy,
  const unsigned samples,
  const Teuchos::RCP<const MonteCarlo::IncoherentPhotonScatteringDistribution>&
  scattering_dist,
  Teuchos::RCP<std::ofstream> sample_ofile,
  Teuchos::RCP<std::ofstream> dist_ofile )
{
  
}

//---------------------------------------------------------------------------//
// end sample_csd.cpp
//---------------------------------------------------------------------------//
