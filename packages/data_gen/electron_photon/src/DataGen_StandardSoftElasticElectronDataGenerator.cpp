//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardSoftElasticElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The standard soft elastic electron data generator class def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_StandardSoftElasticElectronDataGenerator.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_HistogramDistribution.hpp"

namespace DataGen{

// Constructor
StandardSoftElasticElectronDataGenerator::StandardSoftElasticElectronDataGenerator( 
	   const unsigned atomic_number,
	   const Teuchos::RCP<const Data::ElectronPhotonRelaxationDataContainer>& native_eedl_data,
	   const double min_electron_energy,
	   const double max_electron_energy,
       const double cutoff_angle,
       const unsigned number_of_discrete_angles )
  : SoftElasticElectronDataGenerator( atomic_number ),
    d_native_eedl_data( native_eedl_data ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle( cutoff_angle ),
    d_number_of_discrete_angles( number_of_discrete_angles )
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

// Populate the soft elastic electron data container
void StandardSoftElasticElectronDataGenerator::populateSoftElasticDataContainer(
			   Data::SoftElasticElectronVolatileDataContainer&
			   data_container ) const
{
  // Set the atomic number
  this->setAtomicNumber( data_container );

  // Set the soft elastic electron data
  std::cout << "Setting the soft elastic electron data: " << std::endl;
  this->setSoftElasticElectronData( data_container );
}

// Set the soft elastic electron data
void StandardSoftElasticElectronDataGenerator::setSoftElasticElectronData( 
    Data::SoftElasticElectronVolatileDataContainer& data_container ) const
{
  // Set cutoff angle cosine
  data_container.setCutoffAngleCosine( d_cutoff_angle );

  // Set the elastic angular energy grid
  data_container.setElasticAngularEnergyGrid( 
    d_native_eedl_data->getElasticAngularEnergyGrid() );

  // Get the moment of the elastic scattering distribution
  Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator> moments_evaluator;
  moments_evaluator.reset( 
    new DataGen::ElasticElectronMomentsEvaluator( *d_native_eedl_data, 
                                                  d_cutoff_angle ) );

  

  Teuchos::Array<double> discrete_angles, weights;
  Teuchos::Array<Utility::long_float> legendre_moments;
  Teuchos::RCP<Utility::SloanRadauQuadrature> radau_quadrature;
  double precision = 1e-13;
  int n = ( d_number_of_discrete_angles+1 )*2 + 2+10;
  int size = d_native_eedl_data->getElasticAngularEnergyGrid().size();

  // iterate through all angular energy bins
  for ( unsigned i = 0; i < size; i++ )
  {
    // Get the discrete angles and weights
    moments_evaluator->evaluateElasticMoment( legendre_moments, 
                                              i, 
                                              n, 
                                              precision );

    std::cout << std::setprecision(20) << "legendre_moments[0] = \t" << legendre_moments[0] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[1] = \t" << legendre_moments[1] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[2] = \t" << legendre_moments[2] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[3] = \t" << legendre_moments[3] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[4] = \t" << legendre_moments[4] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[5] = \t" << legendre_moments[5] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[6] = \t" << legendre_moments[6] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[7] = \t" << legendre_moments[7] << std::endl;
    std::cout << std::setprecision(20) << "legendre_moments[8] = \t" << legendre_moments[8] << std::endl;

    // Use radau quadrature to find the discrete angles and weights from the moments
    radau_quadrature.reset(
      new Utility::SloanRadauQuadrature( legendre_moments ) );

    radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                               weights,
                                               d_number_of_discrete_angles+1 );

    data_container.setNumberOfDiscreteAngles( i, discrete_angles.size() );
    data_container.setSoftElasticDiscreteAngles( i, 
                                                 discrete_angles.toVector() );
    data_container.setSoftElasticWeights( i, weights.toVector() );
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardSoftElasticElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
