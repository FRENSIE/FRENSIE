//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
AdjointIncoherentGridGenerator::AdjointIncoherentGridGenerator(
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function )
  : d_scattering_function( scattering_function ),
    d_quadrature_kernel( 1e-6 )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
}

// Generate the bilinear grid
void AdjointIncoherentGridGenerator::generate( 
		     Teuchos::Array<double>& log_max_energy_grid,
		     Teucho::Array<Teuchos::Array<double> >& log_energy_grids,
		     const Teuchos::Array<double>& initial_log_max_energy_grid,
		     const double convergence_tol = 0.001,
		     const double absolute_diff_tol = 1e-12,
		     const double distance_tol = 1e-14 ) const
{
  boost::function<double (double x, double y)> adjoint_cross_section = 
    AdjointIncoherentGridGenerator::evaluateLogAdjointIncoherentCrossSection;
  
  boost::function<double (double x)> lower_energy_limit_function = 
    AdjointIncoherentGridGenerator::getLowerLogEnergyLimit;
  
  boost::function<double (double x)> upper_energy_limite_function = 
    AdjointIncoherentGridGenerator::getUpperLogEnergyLimit;
  
  Utility::BilinearGridGenerator grid_generator( adjoint_cross_section,
						 lower_energy_limit_function,
						 upper_energy_limit_function );

  grid_generator.generate( log_max_energy_grid,
			   log_energy_grids,
			   initial_log_max_energy_grid,
			   convergence_tol,
			   absolute_diff_tol,
			   distance_tol );
}

// Evaluate the log adjoint incoherent cross section on the specified grid
void AdjointIncoherentGridGenerator::evaluateLogCrossSectionOnGrid(
			     const Teuchos::Array<double>& log_max_energy_grid,
			     const Teucho::Array<Teuchos::Array<double> >&
			     log_energy_grids,
			     Teuchos::Array<Teuchos::Array<double> >&
			     log_adjoint_incoherent_cross_section ) const
{
  // Make sure the grid is valid
  testPrecondition( log_max_energy_grid.size() > 1 );
  testPrecondition( log_max_energy_grid.size() == log_energy_grids.size() );

  log_adjoint_incoherent_cross_section.resize( log_energy_grids.size() );

  for( unsigned i = 0; i < log_max_energy_grid.size(); ++i )
  {
    log_adjoint_incoherent_cross_section[i].resize(log_energy_grids[i].size());
    
    for( unsigned j = 0; j < log_energy_grids[i].size(); ++ j )
    {
      log_adjoint_incoherent_cross_section[i][j] = 
	evaluateLogAdjointIncoherentCrossSection( log_max_energy_grid[i],
						  log_energy_grids[i][j] );
    }
  }
}

// Get the lower log energy limit for a given log max energy
double AdjointIncoherentGridGenerator::getLowerLogEnergyLimit( 
					    const double log_max_energy ) const
{
  
  return log( MonteCarlo::SimulationProperties::getMinPhotonEnergy() );
}

// Get the upper log energy limit for a given log max energy
double AdjointIncoherentGridGenerator::getUpperLogEnergyLimit( 
					    const double log_max_energy ) const
{
  return log_max_energy;
}

// Evaluate the differential adjoint incoherent cross section (dc/dx)
double AdjointIncoherentGridGenerator::evaluateDifferentialAdjointIncoherentCrossSection(
	  const double inverse_energy_gain_ratio, 
	  const Utility::AdjointKleinNishinaDistribution& distribution ) const
{
  double inverse_wavelength = distribution.getEnergy()/
    (Utility::PhysicalConstants::planck_constant*
     Utility::PhysicalConstants::speed_of_light);
  
  double scat_func_arg = 
    sqrt( (1.0 - inverse_energy_gain_ratio)/distribution.getAlpha() )*
    inverse_wavelength;
  
  return distribution.evaluate( inverse_energy_gain_ratio )*
    d_scattering_function->evaluate( scat_func_arg );
    
}

// Evaluate the log of the incoherent cross section
double
AdjointIncoherentGridGenerator::evaluateLogAdjointIncoherentCrossSection(
						const double log_max_energy, 
					        const double log_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( log_max_energy >= log_energy );
  
  if( log_energy < log_max_energy )
  {
    Utility::AdjointKleinNishinaDistribution distribution(exp(log_energy),
							  exp(log_max_energy));

    boost::function<double (double energy)> adjoint_kn_dist_wrapper = 
      boost::bind<double>( &AdjointIncoherentGridGenerator::evaluateDifferentialAdjointIncoherentCrossSection,
			   boost::ref( *this ),
			   _1,
			   distribution );

    double cross_section;
    double abs_error;
        
    d_quadrature_kernel.integrateAdaptively<21>( 
					adjoint_kn_dist_wrapper,
					distribution.getLowerBoundOfIndepVar(),
					distribution.getUpperBoundOfIndepVar(),
					cross_section,
					abs_error );
					
    return log( cross_section );
  }
  else
    return log( std::numeric_limits<double>::min() );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
