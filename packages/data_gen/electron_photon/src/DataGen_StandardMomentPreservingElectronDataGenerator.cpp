//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardMomentPreservingElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The standard moment preserving electron data generator class def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_StandardMomentPreservingElectronDataGenerator.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_HistogramDistribution.hpp"

namespace DataGen{

// Constructor
StandardMomentPreservingElectronDataGenerator::StandardMomentPreservingElectronDataGenerator(
    const unsigned atomic_number,
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& native_eedl_data,
    const MonteCarlo::TwoDInterpolationType two_d_interp,
    const MonteCarlo::TwoDGridType two_d_grid,
    const double min_electron_energy,
    const double max_electron_energy,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol )
  : MomentPreservingElectronDataGenerator( atomic_number ),
    d_native_eedl_data( native_eedl_data ),
    d_two_d_interp( two_d_interp ),
    d_two_d_grid( two_d_grid ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_tabular_evaluation_tol( tabular_evaluation_tol )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  testPrecondition( atomic_number == native_eedl_data->getAtomicNumber() );
  // Make sure the endl data is valid
  testPrecondition( native_eedl_data.use_count() > 0 );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );
  // Make sure the cutoff angle is valid
  testPrecondition( cutoff_angle_cosine >= -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( tabular_evaluation_tol >= -1.0 );
  testPrecondition( tabular_evaluation_tol <= 1.0 );

  // Create the moment evaluator of the elastic scattering distribution
  d_moments_evaluator.reset(
    new DataGen::ElasticElectronMomentsEvaluator(
                                            *d_native_eedl_data,
                                            d_two_d_interp,
                                            d_two_d_grid,
                                            d_cutoff_angle_cosine,
                                            d_tabular_evaluation_tol ) );

}

// Populate the moment preserving electron data container
void StandardMomentPreservingElectronDataGenerator::populateMomentPreservingDataContainer(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const
{
  // Set the atomic number
  this->setAtomicNumber( data_container );

  // Set the moment preserving electron data
  std::cout << "Setting the moment preserving electron data...";
  std::cout.flush();
  this->setMomentPreservingElectronData( data_container, number_of_discrete_angles );
  std::cout << "done." << std::endl;
}

// Set the moment preserving electron data
void StandardMomentPreservingElectronDataGenerator::setMomentPreservingElectronData(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const
{
  // Set cutoff angle cosine
  data_container.setCutoffAngleCosine( d_cutoff_angle_cosine );

  std::vector<double> angular_energy_grid =
    d_native_eedl_data->getElasticAngularEnergyGrid();

  // Set the elastic angular energy grid
  data_container.setElasticAngularEnergyGrid( angular_energy_grid );

  // iterate through all angular energy bins
  std::vector<double> discrete_angles, weights;
  for ( unsigned i = 0; i < angular_energy_grid.size(); ++i )
  {
    evaluateDiscreteAnglesAndWeights(
        angular_energy_grid[i],
        number_of_discrete_angles,
        discrete_angles,
        weights );

    data_container.setNumberOfDiscreteAngles( i, discrete_angles.size() );
    data_container.setMomentPreservingDiscreteAngles( i, discrete_angles );
    data_container.setMomentPreservingWeights( i, weights );
  }
}

// Generate elastic discrete angle cosines and weights
void StandardMomentPreservingElectronDataGenerator::evaluateDiscreteAnglesAndWeights(
    const double& energy,
    const int& number_of_discrete_angles,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights ) const
{
  std::vector<Utility::long_float> legendre_moments;
  double precision = 1e-13;
  int n = ( number_of_discrete_angles+1 )*2 -2;

  // Get the discrete angles and weights
  d_moments_evaluator->evaluateElasticMoment( legendre_moments,
                                              energy,
                                              n,
                                              precision );

  // Use radau quadrature to find the discrete angles and weights from the moments
  std::shared_ptr<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( legendre_moments ) );

  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             number_of_discrete_angles+1 );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardMomentPreservingElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
