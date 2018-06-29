//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticCrossSectionGenerator.cpp
//! \author Eli Moll
//! \brief  Free gas elastic cross section generator
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_FreeGasElasticCrossSectionGenerator.hpp"

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
  d_cross_section.reset( new Utility::UniformDistribution( 0.0, 20.0, 1.0 ) );

  // std::vector<double> energy_vector = { 1E-11,1.31241E-11,1.70876E-11,2.2426E-11,2.91987E-11,3.83206E-11,5E-11,6.56205E-11,8.54381E-11,1.1213E-10,1.45993E-10,1.91603E-10,2.49468E-10,3.27404E-10,4.26281E-10,5.59456E-10,7.28412E-10,9.55976E-10,1.24468E-09,1.63354E-09,2.12687E-09,2.79132E-09,3.63431E-09,4.7697E-09,6.21016E-09,8.15029E-09,1.06117E-08,1.51672E-08,2.16784E-08,2.34892E-08,2.53E-08,3.61611E-08,5.67377E-08,8.83169E-08,1.65666E-07,4.0461E-07,1.68858E-06,0.0341752,0.0717318,0.109776,0.15,0.2,0.3,0.4,0.5,0.65,0.85,1.09776,1.4,1.9,2.5,3.3,4.4,5.75,7.25,9.25,11.5,14,17,20 };
  // std::vector<double> xs_vector = { 1170.27,1021.57,895.334,781.591,685.033,598.036,523.629,457.168,400.756,349.939,306.814,267.974,235.021,205.354,180.195,157.558,138.377,121.136,106.546,93.4548,82.4018,72.5133,64.1959,56.791,50.6013,45.1343,40.6103,35.562,31.5806,30.8158,30.1468,27.4089,24.9188,23.2719,21.8472,20.848,20.2988,16.8198,14.186,12.3866,10.9238,9.64353,7.95225,6.8766,6.12557,5.34944,4.63652,4.0527,3.54178,2.99292,2.55106,2.14946,1.77518,1.46586,1.22453,1.00022,0.824917,0.687115,0.568971,0.482757 };
  // std::vector<double> xs_vector = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1};
  // std::vector<double> energy_vector = {1e-20, 1e-11, 1e-6, 20};
  // std::vector<double> xs_vector     = { 1200 ,1200, 25, 1};

  // const Teuchos::Array<double> energy_array( energy_vector );
  // const Teuchos::Array<double> xs_array( xs_vector );

  // d_cross_section.reset( new Utility::TabularDistribution<Utility::LogLog>( energy_array, xs_array ) );
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
        double alpha, 
        double beta,
        double E,
        double sab )
{
  double pi3 = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi;

  if( sab < std::numeric_limits<double>::infinity() )
    return ((d_A+1)*(d_A+1)*(d_A+1)*(d_A+1)*d_kT/(16*sqrt(pi3)*d_A*E))*sab;
  else
    return std::numeric_limits<double>::infinity();
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

      double value = crossSectionValue(
                                  alpha,
                                  beta,
                                  E,
                                  sab );
      
      double analytic_value = analyticCrossSectionValue(
                                  alpha,
                                  beta,
                                  E );

      std::pair<double,double> beta_alpha( beta, alpha );
      double_differential_sigma[beta_alpha] = analytic_value;    
    }
  }
}

// Integrate over energy and angle for a total cross section value at a given energy
double FreeGasElasticCrossSectionGenerator::totalCrossSectionValue( 
           double E,
           DoubleDifferentialCrossSection& double_differential_sigma )
{
  double beta_min = Utility::calculateBetaMin( E, d_kT );
  double beta_max = d_beta_max_multiplier*beta_min;
  double beta_spacing = (beta_max - beta_min)/(d_beta_num - 1.0);
  double pi = Utility::PhysicalConstants::pi;

  std::vector<double> beta_contour;

  // Loop over beta
  for (int i = 0; i < d_beta_num; ++i)
  {
    double beta = beta_min + i*beta_spacing;

    double alpha_min = Utility::calculateAlphaMin( E, beta, d_A, d_kT );
    double alpha_max = Utility::calculateAlphaMax( E, beta, d_A, d_kT);
    double alpha_spacing = (alpha_max - alpha_min)/(d_alpha_num - 1.0);

    std::vector<double> alpha_contour;
    double alpha_cum_sum = 0;

    // Loop over alpha
    for (int j = 0; j < d_alpha_num; ++j)
    {
      double alpha = alpha_min + j*alpha_spacing;
      std::pair<double, double> beta_alpha( beta, alpha );
      alpha_contour.push_back( double_differential_sigma[beta_alpha] );
    }

    // Loop over alpha
    if (beta == 0.0)
    {
      alpha_cum_sum = (d_A + 1)*(d_A + 1)/(8*d_A*pi);
    }
    else
    {
      for (int j = 0; j < d_alpha_num - 1; ++j)
      {
        alpha_cum_sum += alpha_spacing*(0.5)*( alpha_contour[j] + alpha_contour[j+1] );
      }
    }

    beta_contour.push_back(alpha_cum_sum);
  }

  double beta_cum_sum = 0;

  // Loop over beta
  for (int i = 0; i < d_beta_num - 1; ++i)
  {
    beta_cum_sum += beta_spacing*(0.5)*( beta_contour[i] + beta_contour[i+1] );
  }

  return beta_cum_sum;
}

void FreeGasElasticCrossSectionGenerator::energyCrossSectionValue(
           double E, 
           DoubleDifferentialCrossSection& double_differential_sigma,
           std::vector<double>& beta_contour )
{
  double beta_min = Utility::calculateBetaMin( E, d_kT );
  double beta_max = d_beta_max_multiplier*beta_min;
  double beta_spacing = (beta_max - beta_min)/(d_beta_num - 1.0);

  std::cout << " " << std::endl;
  std::cout << "Beta    E_f/E_i    Sigma(E'|E)" << std::endl; 

  // Loop over beta
  for (int i = 0; i < d_beta_num; ++i)
  {
    double beta = beta_min + i*beta_spacing;

    double alpha_min = Utility::calculateAlphaMin( E, beta, d_A, d_kT );
    double alpha_max = Utility::calculateAlphaMax( E, beta, d_A, d_kT);
    double alpha_spacing = (alpha_max - alpha_min)/(d_alpha_num - 1.0);

    std::vector<double> alpha_contour;
    double alpha_cum_sum = 0;

    // Loop over alpha
    for (int j = 0; j < d_alpha_num; ++j)
    {
      double alpha = alpha_min + j*alpha_spacing;
      std::pair<double, double> beta_alpha( beta, alpha );

      // std::cout << alpha << " " << double_differential_sigma[beta_alpha] << std::endl;
      alpha_contour.push_back( double_differential_sigma[beta_alpha] );
    }
    // Loop over alpha
    for (int j = 0; j < d_alpha_num - 1; ++j)
    {
      alpha_cum_sum += alpha_spacing*(0.5)*( alpha_contour[j] + alpha_contour[j+1] );
    }

    double E_f = (beta*d_kT) + E;
    double E_r = E_f/E;

    beta_contour.push_back(alpha_cum_sum);
    std::cout << E_r << " " << alpha_cum_sum << std::endl;
  }
}

// Get total cross section
void FreeGasElasticCrossSectionGenerator::getTotalCrossSection( 
    boost::unordered_map< double, double >& total_cross_section )
{
  total_cross_section = d_total_cross_section;
}

// Calculate cross sections for all energies
void FreeGasElasticCrossSectionGenerator::calculateEnergyCrossSectionValue()
{
  // Loop over all energies
  for ( int i = 0; i < d_E.size(); ++i) 
  {
    double E = d_E[i];

    DoubleDifferentialCrossSection doubleDifferentialXS;

    doubleDifferentialCrossSectionValue( E, doubleDifferentialXS );

    d_double_differential_cross_section_map[E] = doubleDifferentialXS;

    energyCrossSectionValue( E, d_double_differential_cross_section_map[E], d_energy_cross_section );
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//
