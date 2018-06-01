//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FreeGasElasticCrossSectionGenerator.hpp
//! \author Eli Moll
//! \brief  Free gas elastic cross section generator
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FREE_GAS_CROSS_SECTION_GENERATOR_HPP
#define DATA_GEN_FREE_GAS_CROSS_SECTION_GENERATOR_HPP

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>
#include <vector>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalAlphaFunction.hpp"
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

//! The free gas elastic marginal alpha function 
class FreeGasElasticCrossSectionGenerator
{

public:

  typedef boost::unordered_map< std::pair<double, double>, double >
    DoubleDifferentialCrossSection;
    
  typedef boost::unordered_map< double, DoubleDifferentialCrossSection >
    DoubleDifferentialCrossSectionMap;

  //! Constructor
  FreeGasElasticCrossSectionGenerator(
	    double kT,
	    std::vector< double> E,
      double A,
      int beta_num,
      int alpha_num,
      double beta_max_multiplier = 1,
      double zero_tolerance = 1e-6 );

  //! Destructor
  ~FreeGasElasticCrossSectionGenerator()
  { /* ... */ }

  //! Calculate Analytical Cross Section for Isotropic Scattering and Unity Sigma
  double analyticCrossSectionValue( double alpha,
                                    double beta,
                                    double E );

  //! Calculate cross section
  double crossSectionValue( double alpha,
				                    double beta,
                            double E,
				                    double sab_value );

  //! Construct full double differential cross section
  void doubleDifferentialCrossSectionValue( 
       double E,
       DoubleDifferentialCrossSection& double_differential_sigma );

  //! Integrate over energy and angle for a total cross section 
  double totalCrossSectionValue(
       double E,
       DoubleDifferentialCrossSection& double_differential_sigma );

  //! Calculate cross sections for all energies 
  void calculateEnergyCrossSectionValue(  );

  //! Get base cross section
  void getBaseCrossSection();

  //! Get base angular distribution
  void getBaseAngularDistribution();

  //! Get total cross section
  void getTotalCrossSection( boost::unordered_map< double, double >& total_cross_section );

private: 

  //! Set base cross section
  void setBaseCrossSection();

  //! Set base angular distribution
  void setBaseAngularDistribution();

  // Temperature
  double d_kT;

  // Incident energy 
  std::vector<double> d_E;

  // Atomic Weight Ratio
  double d_A;

  // Number of beta bins 
  double d_beta_num;

  // Number of alpha bins 
  double d_alpha_num;

  // Beta max multiplier as a function of beta_min 
  double d_beta_max_multiplier;

  // Alpha/Beta tolerance at 0
  double d_zero_tolerance;

  // Bound state cross section 
  Teuchos::RCP<Utility::OneDDistribution> d_cross_section;

  // Bound state angular distribution
  Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution> d_angular_distribution;

  // S(alpha,beta) Function
  Teuchos::RCP<DataGen::FreeGasElasticSAlphaBetaFunction> d_sab_function;

  // Total cross section value 
  boost::unordered_map< double, double > d_total_cross_section;

  // Double differential cross section 
  DoubleDifferentialCrossSectionMap d_double_differential_cross_section_map;

};

} // end DataGen namespace

#endif // end DATA_GEN_FREE_GAS_ELASTIC_MARGINAL_ALPHA_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end DataGen_FreeGasElasticCrossSectionGenerator.hpp
//---------------------------------------------------------------------------//
