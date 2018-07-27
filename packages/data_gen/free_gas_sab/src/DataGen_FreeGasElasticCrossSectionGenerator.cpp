//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticCrossSectionGenerator.cpp
//! \author Eli Moll
//! \brief  Free gas elastic cross section generator
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_FreeGasElasticCrossSectionGenerator.hpp"

#include <cmath>

namespace DataGen{

//  Constructor
FreeGasElasticCrossSectionGenerator::FreeGasElasticCrossSectionGenerator(
	   double kT,
	   std::vector<double> E,
     double A,
     int beta_num,
     int alpha_num,
     double beta_max_multiplier,
     double zero_tolerance )
  : d_kT( kT ),
    d_E( E ),
    d_A( A ),
    d_beta_num( beta_num ),
    d_alpha_num( alpha_num ),
    d_beta_max_multiplier( beta_max_multiplier ),
    d_zero_tolerance( zero_tolerance )
{
  // Make sure the values are valid
  testPrecondition( A > 0.0 );
  testPrecondition( kT > 0.0 );

  setBaseCrossSection();
  setBaseAngularDistribution();
  d_sab_function.reset( new FreeGasElasticSAlphaBetaFunction(
						                    d_cross_section, 
						                    d_angular_distribution,
						                    d_A,
						                    d_kT ) );
}

// Set base cross section
void FreeGasElasticCrossSectionGenerator::setBaseCrossSection()
{
  //d_cross_section.reset( new Utility::UniformDistribution( 0.0, 20.0, 1.0 ) );
  
  
  std::vector<double> energy_vector = {1e-12, 1e-11, 1e-6, 20};
  std::vector<double> xs_vector     = {1170, 1170, 20, 20};
  //std::vector<double> xs_vector     = {1, 1, 1, 1};
  const Teuchos::Array<double> energy_array( energy_vector );
  const Teuchos::Array<double> xs_array( xs_vector );
  d_cross_section.reset( new Utility::TabularDistribution<Utility::LogLog>( energy_array, xs_array ) );
  
}

// Set base angular distribution
void FreeGasElasticCrossSectionGenerator::setBaseAngularDistribution()
{
  // Initialize the scattering probability distribution
  Teuchos::RCP<Utility::TabularOneDDistribution> isotropic_distribution(
			  new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  // Initialize the scattering distribution
  MonteCarlo::NuclearScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;
  
  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  d_angular_distribution.reset( 
			 new MonteCarlo::NuclearScatteringAngularDistribution(
							      distribution ) );
}

// Calculate Analytical Cross Section for Isotropic Scattering and Unity Sigma
double FreeGasElasticCrossSectionGenerator::analyticCrossSectionValue( 
        double alpha, 
        double beta,
        double E )
{
  double pi3 = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi;

  if( alpha > 0.0 || beta > 0.0 )
  {
    return (d_kT*(d_A+1)*(d_A+1)/(16*sqrt(pi3)*d_A*E*sqrt(alpha)))*
      exp( -(alpha + beta)*(alpha + beta)/(4*alpha) );
  }
  else
    return std::numeric_limits<double>::infinity();
}

// Calculate cross section
double FreeGasElasticCrossSectionGenerator::crossSectionValue( 
        double beta_int,
        double E )
{
  double pi3 = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi;

  return (d_A+1)*(d_A+1)*(d_A+1)*(d_A+1)*(d_kT/E)/(4*d_A*sqrt(pi3))*beta_int;
}

//  Constructruct full double differential cross section at a given energy
void FreeGasElasticCrossSectionGenerator::doubleDifferentialCrossSectionValue( 
        double E,
        DoubleDifferentialCrossSection& double_differential_sigma )
{
  double beta_min = Utility::calculateBetaMin( E, d_kT );
  double beta_max = d_beta_max_multiplier*beta_min;
  double beta_spread = (beta_max - beta_min)/(d_beta_num - 1.0);

  // Loop over all beta for given energy
  for ( int j = 0; j < d_beta_num; ++j )
  {
    double beta = beta_min + j*beta_spread;

    // Correct for zero value beta
    if (beta > -1.0*d_zero_tolerance && beta < 0.0 )
    {
      beta = -1*d_zero_tolerance;
    }
    else if (beta < 1.0*d_zero_tolerance && beta > 0.0 )
    {
      beta = d_zero_tolerance;
    }
    else if (beta <= beta_min)
    {
      beta = beta_min - beta_min*1e-3;
    }

    double alpha_min = Utility::calculateAlphaMin( E, 
                                                   beta, 
                                                   d_A, 
                                                   d_kT);

    double alpha_max = Utility::calculateAlphaMax( E, 
                                                   beta, 
                                                   d_A, 
                                                   d_kT);

    double alpha_spread = (alpha_max - alpha_min)/(d_alpha_num - 1.0);

    for (int k = 0; k < d_alpha_num; ++k )
    {
      double alpha = alpha_min + k*alpha_spread;

      double sab = (*d_sab_function)( alpha, beta, E );

      double value = crossSectionValue( sab, E );

      std::pair<double,double> beta_alpha( beta, alpha );
      double_differential_sigma[beta_alpha] = value;    
    }
  }
}

// Integrate over energy and angle for a total cross section value at a given energy
void FreeGasElasticCrossSectionGenerator::totalCrossSectionValue( 
           double E )
{
  d_beta_function.reset( new DataGen::FreeGasElasticMarginalBetaFunction(
						    d_cross_section, 
						    d_angular_distribution,
						    d_A,
						    d_kT,
						    E ) );

  d_total_cross_section[E] = this->crossSectionValue( d_beta_function->getNormalizationConstant(), E );
}

void FreeGasElasticCrossSectionGenerator::energyCrossSectionValue(
           double E )
{
  d_beta_function.reset( new DataGen::FreeGasElasticMarginalBetaFunction(
						    d_cross_section, 
						    d_angular_distribution,
						    d_A,
						    d_kT,
						    E ) );

  double beta_min = Utility::calculateBetaMin( E, d_kT );
  double beta_max = d_beta_max_multiplier*beta_min;
  double beta_spacing = (beta_max - beta_min)/(d_beta_num - 1.0);

  DifferentialEnergyCrossSection beta_pdf;

  // Loop over beta
  for (int i = 0; i < d_beta_num; ++i)
  {
    if (true)
    {
      double beta = beta_min + i*beta_spacing;
      double pdf  = d_beta_function->operator()( beta );
      beta_pdf.push_back( std::make_pair(beta, pdf) ); 
    }
    else
    {
      double beta = beta_min + i*beta_spacing;

      d_alpha_function.reset( new DataGen::FreeGasElasticMarginalAlphaFunction(
						    d_cross_section, 
						    d_angular_distribution,
						    d_A,
						    d_kT,
						    beta,
                E ) );

      double pdf = d_alpha_function->getNormalizationConstant();

      beta_pdf.push_back( std::make_pair(beta, pdf) );
    }
  }

  d_beta_pdf_map[E] = beta_pdf;
}

// Get total cross section
void FreeGasElasticCrossSectionGenerator::getTotalCrossSection( 
    boost::unordered_map< double, double >& total_cross_section )
{
  for (int i = 0; i < d_E.size(); ++i)
  {
    this->totalCrossSectionValue( d_E[i] );
  }

  total_cross_section = d_total_cross_section;
}

// Calculate cross sections for all energies
void FreeGasElasticCrossSectionGenerator::getDifferentialEnergyCrossSectionMap(
  DifferentialEnergyCrossSectionMap& energy_cross_section_map )
{
  // Loop over all energies
  for ( int i = 0; i < d_E.size(); ++i) 
  {
    energyCrossSectionValue( d_E[i] );
  }

  energy_cross_section_map = d_beta_pdf_map;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//
