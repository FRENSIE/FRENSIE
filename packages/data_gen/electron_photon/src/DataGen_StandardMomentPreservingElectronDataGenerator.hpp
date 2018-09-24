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

// FRENSIE Includes
#include "DataGen_MomentPreservingElectronDataGenerator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"

namespace DataGen{

//! The standard electron-electron-relaxation data generator class
class StandardMomentPreservingElectronDataGenerator : public MomentPreservingElectronDataGenerator
{

public:

  //! Constructor
  StandardMomentPreservingElectronDataGenerator(
    const unsigned atomic_number,
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& native_eedl_data,
    const MonteCarlo::TwoDInterpolationType two_d_interp,
    const MonteCarlo::TwoDGridType two_d_grid,
    const double min_electron_energy,
    const double max_electron_energy,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol );

  //! Destructor
  ~StandardMomentPreservingElectronDataGenerator()
  { /* ... */ }

  //! Populate the moment preserving data container
  void populateMomentPreservingDataContainer(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const;

//protected:

  // Set the moment preserving electron data
  void setMomentPreservingElectronData(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const;

  // Generate elastic discrete angle cosines and weights
  void evaluateDiscreteAnglesAndWeights(
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

  // The cutoff angle cosine between moment preserving and coupled elastic collisions
  double d_cutoff_angle_cosine;

  // The FullyTabularTwoDDistribution evaluation tolerance
  double d_tabular_evaluation_tol;

  // The 2D interplation type
  MonteCarlo::TwoDInterpolationType d_two_d_interp;

  // The 2D grid type
  MonteCarlo::TwoDGridType d_two_d_grid;

  // The moment evaluator of the elastic scattering distribution
  std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator> d_moments_evaluator;
};


} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_MOMENT_PRESERVING_ELECTRON_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardMomentPreservingElectronDataGenerator.hpp
//---------------------------------------------------------------------------//
