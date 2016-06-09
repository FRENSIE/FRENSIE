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
#include "Utility_ContractException.hpp"
#include "Utility_HistogramDistribution.hpp"

namespace DataGen{

// Constructor
StandardMomentPreservingElectronDataGenerator::StandardMomentPreservingElectronDataGenerator(
    const unsigned atomic_number,
    const Teuchos::RCP<const Data::ElectronPhotonRelaxationDataContainer>& native_eedl_data,
    const double min_electron_energy,
    const double max_electron_energy,
    const double cutoff_angle_cosine )
  : MomentPreservingElectronDataGenerator( atomic_number ),
    d_native_eedl_data( native_eedl_data ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  testPrecondition( atomic_number == native_eedl_data->getAtomicNumber() );
  // Make sure the endl data is valid
  testPrecondition( !native_eedl_data.is_null() );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );
}

// Populate the moment preserving electron data container
void StandardMomentPreservingElectronDataGenerator::populateMomentPreservingDataContainer(
    Data::MomentPreservingElectronVolatileDataContainer& data_container,
    const int& number_of_discrete_angles ) const
{
  // Set the atomic number
  this->setAtomicNumber( data_container );

  // Set the moment preserving electron data
  std::cout << "Setting the moment preserving electron data: " << std::endl;
  this->setMomentPreservingElectronData( data_container, number_of_discrete_angles );
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

  // Create the moment evaluator of the elastic scattering distribution
  Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator> moments_evaluator;
  moments_evaluator.reset(
    new DataGen::ElasticElectronMomentsEvaluator( *d_native_eedl_data,
                                                  d_cutoff_angle_cosine ) );

  std::vector<double> discrete_angles, weights;

  // iterate through all angular energy bins
  for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  {
    evaluateDisceteAnglesAndWeights(
        moments_evaluator,
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
void StandardMomentPreservingElectronDataGenerator::evaluateDisceteAnglesAndWeights(
    const Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    const int& number_of_discrete_angles,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights ) const
{
  std::vector<Utility::long_float> legendre_moments;
  double precision = 1e-13;
  int n = ( number_of_discrete_angles+1 )*2 -2;
  //int n = ( number_of_discrete_angles+1 )*2 + 2+10;

  // Get the discrete angles and weights
  moments_evaluator->evaluateElasticMoment( legendre_moments,
                                            energy,
                                            n,
                                            precision );

  // Use radau quadrature to find the discrete angles and weights from the moments
  Teuchos::RCP<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( legendre_moments ) );

  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             number_of_discrete_angles+1 );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardMomentPreservingElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
