//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator_def.hpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator template definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_LinearGridGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Generate the bilinear grid
template<typename InterpPolicy>
void AdjointIncoherentGridGenerator::generate( 
		     Teuchos::Array<double>& energy_grid,
		     Teuchos::Array<Teuchos::Array<double> >& max_energy_grids,
		     const Teuchos::Array<double>& initial_energy_grid,
		     const double convergence_tol,
		     const double absolute_diff_tol,
		     const double distance_tol ) const
{
  // // Make sure the initial grid is valid
  // testPrecondition( initial_energy_grid.size() > 1 );
  // testPrecondition( Utility::Sort::isSortedAscending( 
  // 					         initial_energy_grid.begin(),
  // 				                 initial_energy_grid.end() ) );
  // // Make sure the tolerances are valid
  // testPrecondition( convergence_tol > 0.0 );
  // testPrecondition( convergence_tol <= 1.0 );
  // testPrecondition( absolute_diff_tol > 0.0 );
  // testPrecondition( distance_tol > 0.0 );

  // energy_grid.clear();
  // energy_grid.resize( 3 );
  
  // energy_grid[0] = AdjointIncoherentGridGenerator::min_table_energy;
  // energy_grid[1] = 
  //   AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
  // 			    AdjointIncoherentGridGenerator::max_table_energy );
  // energy_grid[2] = AdjointIncoherentGridGenerator::max_table_energy;
  
  // max_energy_grids.clear();

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

// Generate a max energy grid at the desired energy
template<typename InterpPolicy>
void AdjointIncoherentGridGenerator::generate( 
				       Teuchos::Array<double>& max_energy_grid,
				       const double raw_energy,
				       const double convergence_tol,
				       const double absolute_diff_tol,
				       const double distance_tol )
{
  // // Make sure the energy is valid
  // testPrecondition( raw_energy > 0.0 );
  // testPrecondition( raw_energy <= 
  // 		    AdjointIncoherentCrossSectionEvaluator::max_table_energy );
  // // Make sure the tolerances are valid
  // testPrecondition( convergence_tol > 0.0 );
  // testPrecondition( convergence_tol <= 1.0 );
  // testPrecondition( absolute_diff_tol > 0.0 );
  // testPrecondition( distance_tol > 0.0 );
  
  // // Load the initial max energy grid
  // Teuchos::Array<double> initial_max_energy_grid;
  
  // if( AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondeToAMaxCrossSectionValue( raw_energy ) )
  // {
  //   initial_max_energy_grid.resize( 3 );

  //   initial_max_energy_grid[0] = InterpPolicy::processIndepVar( raw_energy );
  //   initial_max_energy_grid[1] = InterpPolicy::processIndepVar( AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( raw_energy ) );
  //   initial_max_energy_grid[2] = InterpPolicy::processIndepVar( AdjointIncoherentGridGenerator::getMaxTableEnergy() );
  // }
  // else
  // {
  //   initial_max_energy_grid.resize( 2 );
    
  //   initial_max_energy_grid[0] = InterpPolicy::processIndepVar( raw_energy );
  //   initial_max_energy_grid[1] = InterpPolicy::processIndepVar( AdjointIncoherentGridGenerator::getMaxTableEnergy() );
  // }

  // // Create the boost function that returns the processed cross section
  // boost::function<double (double max_energy)> grid_function = boost::bind( 
  //   &InterpPolicy::processDepVar,
  //   boost::bind( &AdjointIncoherentCrossSectionEvaluator::evaluateCrossSection,
  // 		 boost::ref( d_adjoint_incoherent_cross_section ),
  // 		 raw_energy,
  // 		 boost::bind( &InterpPolicy::recoverProcessedIndepVar, _1 )) );

  // Utility::LinearGridGenerator max_grid_generator( grid_function );

  // max_grid_generator.generate( max_energy_grid,
  // 			       initial_max_energy_grid,
  // 			       convergence_tol,
  // 			       absolute_diff_tol,
  // 			       distance_tol );
}

// Evaluate the log adjoint incoherent cross section on the specified grid
template<typename InterpPolicy>
void AdjointIncoherentGridGenerator::evaluateCrossSectionOnGrid(
			     const Teuchos::Array<double>& energy_grid,
			     const Teuchos::Array<Teuchos::Array<double> >&
			     max_energy_grids,
			     Teuchos::Array<Teuchos::Array<double> >&
			     adjoint_incoherent_cross_section )
{
  // // Make sure the grid is valid
  // testPrecondition( energy_grid.size() > 1 );
  // testPrecondition( energy_grid.size() == max_energy_grids.size() );

  // adjoint_incoherent_cross_section.resize( max_energy_grids.size() );

  // for( unsigned i = 0; i < energy_grid.size(); ++i )
  // {
  //   adjoint_incoherent_cross_section[i].resize( max_energy_grids[i].size() );

  //   double energy = InterpPolicy::recoverProcessedIndepVar( energy_grid[i] );
    
  //   for( unsigned j = 0; j < max_energy_grids[i].size(); ++j )
  //   {
  //     double max_energy = 
  // 	InterpPolicy::recoverProcessedIndepVar( max_energy_grids[i][j] );
    
  //     double raw_cross_section =
  // 	d_adjoint_incoherent_cross_section.evaluateCrossSection( energy,
  // 								 max_energy );
 
  //     adjoint_incoherent_cross_section[i][j] = 
  // 	InterpPolicy::processDepVar( raw_cross_section );
  //   }
  // }
}

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator_def.hpp
//---------------------------------------------------------------------------//
