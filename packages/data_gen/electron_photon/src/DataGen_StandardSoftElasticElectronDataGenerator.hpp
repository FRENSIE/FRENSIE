//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardSoftElasticElectronDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard soft elastic electron data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_SOFT_ELASTIC_ELECTRON_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_SOFT_ELASTIC_ELECTRON_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_SoftElasticElectronDataGenerator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

//! The standard electron-electron-relaxation data generator class
class StandardSoftElasticElectronDataGenerator : public SoftElasticElectronDataGenerator
{

public:

  //! Constructor
  StandardSoftElasticElectronDataGenerator( 
	   const unsigned atomic_number,
	   const Teuchos::RCP<const Data::ElectronPhotonRelaxationDataContainer>& native_eedl_data,
	   const double min_electron_energy,
	   const double max_electron_energy,
       const double cutoff_angle,
       const unsigned number_of_discrete_angles );

  //! Destructor
  ~StandardSoftElasticElectronDataGenerator()
  { /* ... */ }

  //! Populate the soft elastic data container
  void populateSoftElasticDataContainer(
			   Data::SoftElasticElectronVolatileDataContainer&
			   data_container ) const;

protected:

  // Set the soft elastic electron data
  void setSoftElasticElectronData( 
        Data::SoftElasticElectronVolatileDataContainer& data_container ) const;

private:

  // The EEDL data
  Teuchos::RCP<const Data::ElectronPhotonRelaxationDataContainer> d_native_eedl_data;

  // The min electron energy
  double d_min_electron_energy;

  // The max electron energy
  double d_max_electron_energy;

  // The cutoff angle between soft and hard elastic collisions
  double d_cutoff_angle;

  // The number of discrete angles that soft collisions can scatter into
  double d_number_of_discrete_angles;
};


} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_SOFT_ELASTIC_ELECTRON_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardSoftElasticElectronDataGenerator.hpp
//---------------------------------------------------------------------------//
