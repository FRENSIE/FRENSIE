//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardMomentPreservingElectronDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard moment preserving electron data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_MOMENT_PRESERVING_ELECTRON_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_MOMENT_PRESERVING_ELECTRON_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_MomentPreservingElectronDataGenerator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

//! The standard electron-electron-relaxation data generator class
class StandardMomentPreservingElectronDataGenerator : public MomentPreservingElectronDataGenerator
{

public:

  //! Constructor
  StandardMomentPreservingElectronDataGenerator(
    const unsigned atomic_number,
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& native_eedl_data,
    const double min_electron_energy,
    const double max_electron_energy,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol,
    const bool linlinlog_interpolation_mode_on );

  //! Destructor
  ~StandardMomentPreservingElectronDataGenerator()
  { /* ... */ }

  //! Populate the moment preserving data container
  void populateMomentPreservingDataContainer(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const;

protected:

  // Set the moment preserving electron data
  void setMomentPreservingElectronData(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const;

  // Generate elastic discrete angle cosines and weights
  void evaluateDisceteAnglesAndWeights(
    const std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    const int& number_of_discrete_angles,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights ) const;

private:

  // The EEDL data
  std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer> d_native_eedl_data;

  // The min electron energy
  double d_min_electron_energy;

  // The max electron energy
  double d_max_electron_energy;

  // The cutoff angle cosine between moment preserving and analog elastic collisions
  double d_cutoff_angle_cosine;

  // The FullyTabularTwoDDistribution evaluation tolerance
  double d_tabular_evaluation_tol;

  // The LinLinLog interplation mode
  bool d_linlinlog_interpolation_mode_on;
};


} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_MOMENT_PRESERVING_ELECTRON_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardMomentPreservingElectronDataGenerator.hpp
//---------------------------------------------------------------------------//
