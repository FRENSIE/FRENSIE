//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <deque>

// Boost Includes
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "Utility_LinearGridGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Initialize the static member data
double AdjointIncoherentGridGenerator::min_table_energy = 0.0001;
double AdjointIncoherentGridGenerator::max_table_energy = 20.0;

//! Set the min table energy (default is 0.0001 MeV)
void AdjointIncoherentGridGenerator::setMinTableEnergy( 
						      const double min_energy )
{
  // Make sure the min energy is valid
  testPrecondition( min_energy > 0.0 );
  testPrecondition( min_energy < 
		    AdjointIncoherentGridGenerator::max_table_energy );

  AdjointIncoherentGridGenerator::min_table_energy = min_energy;
}

// Get the min table energy
double AdjointIncoherentGridGenerator::getMinTableEnergy()
{
  return AdjointIncoherentGridGenerator::min_table_energy;
}

// Set the max table energy (default is 20.0 MeV)
void AdjointIncoherentGridGenerator::setMaxTableEnergy( 
						      const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  testPrecondition( max_energy > 
		    AdjointIncoherentGridGenerator::min_table_energy );

  AdjointIncoherentGridGenerator::max_table_energy = max_energy;
}

// Get the max table energy
double AdjointIncoherentGridGenerator::getMaxTableEnergy()
{
  return AdjointIncoherentGridGenerator::max_table_energy;
}

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
		     Teuchos::Array<Teuchos::Array<double> >& log_energy_grids,
		     const Teuchos::Array<double>& initial_log_max_energy_grid,
		     const double convergence_tol,
		     const double absolute_diff_tol,
		     const double distance_tol ) const
{
  // Make sure the initial grid is valid
  testPrecondition( initial_log_max_energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( 
					 initial_log_max_energy_grid.begin(),
				         initial_log_max_energy_grid.end() ) );
  // Make sure the tolerances are valid
  testPrecondition( convergence_tol > 0.0 );
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( absolute_diff_tol > 0.0 );
  testPrecondition( distance_tol > 0.0 );

  log_max_energy_grid.clear();
  log_energy_grids.clear();
  
  // boost::function<double (double x, double y)> adjoint_cross_section = 
  //   boost::bind( &AdjointIncoherentGridGenerator::evaluateLogAdjointIncoherentCrossSection,
  // 		 boost::ref( *this ),
  // 		 _1,
  // 		 _2 );
  
  // boost::function<double (double x)> lower_energy_limit_function = 
  //   AdjointIncoherentGridGenerator::getLowerLogEnergyLimit;
  
  // boost::function<double (double x)> upper_energy_limit_function = 
  //   AdjointIncoherentGridGenerator::getUpperLogEnergyLimit;
  
  // Utility::BilinearGridGenerator grid_generator( adjoint_cross_section,
  // 						 lower_energy_limit_function,
  // 						 upper_energy_limit_function );

  // // Use a queue data structure to calculate the max energy grid points
  // std::deque<double> log_max_energy_grid_queue(
  // 					   initial_log_max_energy_grid.begin(),
  // 					   initial_log_max_energy_grid.end() );

  // // Calculate the max energy grid points
  // while( log_max_energy_grid_queue.size() > 1 )
  // {
  //   // Generate the log energy grid at the first max energy
  //   double log_max_energy_0 = log_max_energy_grid_queue.front();

  //   log_max_energy_grid_queue.pop_front();

  //   boost::function<double (double y)> log_max_energy_0_cross_secion = 
  //     boost::bind( &AdjointIncoherentGridGenerator::evaluateLogAdjointIncoherentCrossSection,
  // 		   boost::ref( *this ),
  // 		   log_max_energy_0,
  // 		   _1 );

  //   Teuchos::Array<double> log_max_energy_0_initial_log_energy_grid( 3 );
  //   log_max_energy_0_log_energy_grid[0] = 
  //     AdjointIncoherentGridGenerator::getLowerLogEnergyLimit(log_max_energy_0);
  //   log_max_energy_0_log_energy_grid[1] = 
  //     AdjointIncoherentGridGenerator::getLogEnergyOfCrossSectionPeak(
  // 							    log_max_energy_0 );
  //   log_max_energy_0_log_energy_grid[2] = 
  //     AdjointIncoherentGridGenerator::getUpperLogEnergyLimit(log_max_energy_0);

  //   Teuchos::Array<double> log_max_energy_0_log_energy_grid;

  //   Utility::LinearGridGenerator log_max_energy_0_log_energy_grid_generator(
  // 					       log_max_energy_0_cross_secion );

  //   log_max_energy_0_log_energy_grid_generator.generate( 
  // 				      log_max_energy_0_log_energy_grid,
  // 				      log_max_energy_0_initial_log_energy_grid,
  // 				      convergence_tol,
  // 				      absolute_diff_tol,
  // 				      distance_tol );

  //   // Generate the log energy grid at the second max energy
  //   double log_max_energy_1 = log_max_energy_grid_queue.front();

  //   boost::function<double (double y)> log_max_energy_1_cross_secion = 
  //     boost::bind( &AdjointIncoherentGridGenerator::evaluateLogAdjointIncoherentCrossSection,
  // 		   boost::ref( *this ),
  // 		   log_max_energy_1,
  // 		   _1 );
    
  //   Teuchos::Array<double> log_max_energy_1_initial_log_energy_grid( 3 );
  //   log_max_energy_1_log_energy_grid[0] = 
  //     AdjointIncoherentGridGenerator::getLowerLogEnergyLimit(log_max_energy_0);
  //   log_max_energy_1_log_energy_grid[1] = 
  //     AdjointIncoherentGridGenerator::getLogEnergyOfCrossSectionPeak(
  // 							    log_max_energy_0 );
  //   log_max_energy_1_log_energy_grid[2] = 
  //     AdjointIncoherentGridGenerator::getUpperLogEnergyLimit(log_max_energy_0);

  //   Teuchos::Array<double> log_max_energy_1_log_energy_grid;

  //   Utility::LinearGridGenerator log_max_energy_1_log_energy_grid_generator(
  // 					       log_max_energy_1_cross_secion );

  //   log_max_energy_1_log_energy_grid_generator.generate( 
  // 				      log_max_energy_1_log_energy_grid,
  // 				      log_max_energy_1_initial_log_energy_grid,
  // 				      convergence_tol,
  // 				      absolute_diff_tol,
  // 				      distance_tol );
    
  //   // Test if the distance tolerance has been satisfied
  //   double relative_distance = 
  //     Utility::Policy::relError( log_max_energy_0, log_max_energy_1 );
    
  //   if( relative_distance > distance_tol )
  //   {
  //     // Check if the local 2D grid has converged
  //     double log_max_energy_grid_mid = 
  // 	0.5*(log_max_energy_0 + log_max_energy_1 );

  //     boost::function<double (double y)> log_max_energy_mid_cross_secion = 
  //     boost::bind( &AdjointIncoherentGridGenerator::evaluateLogAdjointIncoherentCrossSection,
  // 		   boost::ref( *this ),
  // 		   log_max_energy_mid,
  // 		   _1 );

  //     double L0 = log_max_energy_0_log_energy_grid.back() - 
  // 	log_max_energy_0_log_energy_grid.front();
  //     double L1 = log_max_energy_1_log_energy_grid.back() -
  // 	log_max_energy_1_log_energy_grid.front();
  //     double Lx = 
  // 	AdjointIncoherentGridGenerator::getUpperLogEnergyLimit( 
  // 							 log_max_energy_mid ) -
  // 	AdjointIncoherentGridGenerator::getLowerLogEnergyLimit( 
  // 							  log_max_energy_mid );
  //   }
  // }
  
}

// Evaluate the log adjoint incoherent cross section on the specified grid
void AdjointIncoherentGridGenerator::evaluateLogCrossSectionOnGrid(
			     const Teuchos::Array<double>& log_max_energy_grid,
			     const Teuchos::Array<Teuchos::Array<double> >&
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
						  const double log_max_energy )
{
  
  return log( AdjointIncoherentGridGenerator::min_table_energy );
}

// Get the upper log energy limit for a given log max energy
double AdjointIncoherentGridGenerator::getUpperLogEnergyLimit( 
						  const double log_max_energy )
{
  return log_max_energy;
}

// Evaluate the log of the incoherent cross section
double
AdjointIncoherentGridGenerator::evaluateLogAdjointIncoherentCrossSection(
						const double log_max_energy, 
					        const double log_energy ) const
{
  
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.cpp
//---------------------------------------------------------------------------//
