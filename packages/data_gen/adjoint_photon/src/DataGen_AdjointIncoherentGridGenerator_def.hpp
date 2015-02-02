//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator_def.hpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator template definition
//!
//---------------------------------------------------------------------------//

// Std Lib
#include <deque>
#include <algorithm>

// FRENSIE Includes
#include "Utility_LinearGridGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Generate the bilinear grid
template<typename TwoDInterpPolicy>
void AdjointIncoherentGridGenerator::generate( 
		     Teuchos::Array<double>& energy_grid,
		     Teuchos::Array<Teuchos::Array<double> >& max_energy_grids,
		     Teuchos::Array<Teuchos::Array<double> >& cross_section,
		     const double convergence_tol,
		     const double absolute_diff_tol,
		     const double distance_tol ) const
{
  // Make sure the same inerpolation is used for the energy and max energy
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  // Make sure the tolerances are valid
  testPrecondition( convergence_tol > 0.0 );
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( absolute_diff_tol > 0.0 );
  testPrecondition( distance_tol > 0.0 );

  // Reset the energy grid
  energy_grid.clear();
      
  // Reset the max energy grids and cross section
  max_energy_grids.clear();
  cross_section.clear();

  // Initialize the energy grid queue
  std::deque<double> energy_grid_queue;
  energy_grid_queue.push_back( 
		TwoDInterpPolicy::processFirstIndepVar( s_min_table_energy ) );

  double energy_of_max_cs = 
    AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
						   s_nudged_max_table_energy );
  if( energy_of_max_cs > s_min_table_energy )
  {
    energy_grid_queue.push_back( TwoDInterpPolicy::processFirstIndepVar(
							  energy_of_max_cs ) );
  }
  
  energy_grid_queue.push_back( 
		TwoDInterpPolicy::processFirstIndepVar( s_max_table_energy ) );

  double energy_0, energy_1;
  Teuchos::Array<double> max_energy_grid_0, max_energy_grid_1;
  Teuchos::Array<double> cross_section_grid_0, cross_section_grid_1;

  // Generate the first max energy grid
  energy_0 = energy_grid_queue.front();
  energy_grid_queue.pop_front();
  
  this->generate<TwoDInterpPolicy>( max_energy_grid_0,
				    cross_section_grid_0,
				    energy_0,
				    convergence_tol,
				    absolute_diff_tol,
				    distance_tol );
  
  // Optimize the 2D grid
  while( !energy_grid_queue.empty() )
  {
    // Generate the max energy grid at the second energy grid point
    energy_1 = energy_grid_queue.front();
    
    this->generate<TwoDInterpPolicy>( max_energy_grid_1,
				      cross_section_grid_1,
				      energy_1,
				      convergence_tol,
				      absolute_diff_tol,
				      distance_tol );
    
    bool converged = this->hasGridConverged<TwoDInterpPolicy>( 
							  energy_0, 
							  energy_1, 
							  max_energy_grid_0, 
							  max_energy_grid_1,
							  cross_section_grid_0,
							  cross_section_grid_1,
							  convergence_tol,
							  absolute_diff_tol,
							  distance_tol );
    
    // Keep the grid points
    if( converged )
    {
      energy_grid.push_back( energy_0 );
      max_energy_grids.push_back( max_energy_grid_0 );
      cross_section.push_back( cross_section_grid_0 );
      
      if( s_verbose )
      {
	std::cout.precision( 18 );
	std::cout << "Added " << energy_0 << " (" 
		  << energy_grid.size()-1 << ")"
		  << std::endl;
      }
      
      energy_0 = energy_1;
      energy_grid_queue.pop_front();

      max_energy_grid_0 = max_energy_grid_1;
      cross_section_grid_0 = cross_section_grid_1;
    }
    // Refine the grid
    else
    {
      energy_grid_queue.push_front( 0.5*(energy_0+energy_1) );      
    }
  }

  energy_grid.push_back( energy_0 );
  max_energy_grids.push_back( max_energy_grid_0 );
  cross_section.push_back( cross_section_grid_0 );

  // Make sure there is a max energy grid for every energy grid point
  testPostcondition( energy_grid.size() == max_energy_grids.size() );
  testPostcondition( max_energy_grids.size() == cross_section.size() );
  // Make sure the optimized grid has at least 2 grid points
  testPostcondition( energy_grid.size() >= 2 );
}

// Generate a max energy grid at the desired energy
template<typename TwoDInterpPolicy>
void AdjointIncoherentGridGenerator::generate( 
			     Teuchos::Array<double>& processed_max_energy_grid,
			     Teuchos::Array<double>& processed_cross_section,
			     const double processed_energy,
			     const double convergence_tol,
			     const double absolute_diff_tol,
			     const double distance_tol ) const
{
  // Make sure the same inerpolation is used for the energy and max energy
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  // Make sure the energy is valid
  testPrecondition(
	    processed_energy <= 
	    TwoDInterpPolicy::processFirstIndepVar(s_nudged_max_table_energy));
  // Make sure the tolerances are valid
  testPrecondition( convergence_tol > 0.0 );
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( absolute_diff_tol > 0.0 );
  testPrecondition( distance_tol > 0.0 );
  
  // Load the initial max energy grid
  Teuchos::Array<double> initial_processed_max_energy_grid;

  double raw_energy = 
      TwoDInterpPolicy::recoverProcessedFirstIndepVar( processed_energy );
  
  if( AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( raw_energy ) )
  {
    double max_energy_of_max_cs = AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( raw_energy );
    
    if( max_energy_of_max_cs < s_nudged_max_table_energy )
    {
      initial_processed_max_energy_grid.resize( 3 );
      
      initial_processed_max_energy_grid[0] = 
	TwoDInterpPolicy::processSecondIndepVar( 
		      raw_energy*(1.0 + s_energy_to_max_energy_nudge_factor) );
      initial_processed_max_energy_grid[1] = 
	TwoDInterpPolicy::processSecondIndepVar( max_energy_of_max_cs );
      initial_processed_max_energy_grid[2] = 
	TwoDInterpPolicy::processSecondIndepVar( s_nudged_max_table_energy );
    }
    else
    {
      initial_processed_max_energy_grid.resize( 2 );
    
      initial_processed_max_energy_grid[0] = 
	TwoDInterpPolicy::processSecondIndepVar( 
		      raw_energy*(1.0 + s_energy_to_max_energy_nudge_factor) );
    
      initial_processed_max_energy_grid[1] = 
	TwoDInterpPolicy::processSecondIndepVar( s_nudged_max_table_energy );
    }
  }
  else
  {
    initial_processed_max_energy_grid.resize( 2 );
    
    initial_processed_max_energy_grid[0] = 
      TwoDInterpPolicy::processSecondIndepVar( 
		       raw_energy*(1.0+ s_energy_to_max_energy_nudge_factor) );
    
    initial_processed_max_energy_grid[1] = 
      TwoDInterpPolicy::processSecondIndepVar( s_nudged_max_table_energy );
  }

  // Create the boost function that returns the processed cross section
  boost::function<double (double max_energy)> grid_function = 
    boost::bind( &AdjointIncoherentGridGenerator::evaluateProcessedCrossSection<TwoDInterpPolicy>,
		 boost::ref( *this ),
		 processed_energy,
		 _1 );

  Utility::LinearGridGenerator max_grid_generator( grid_function );
  
  max_grid_generator.generate( processed_max_energy_grid,
			       processed_cross_section,
  			       initial_processed_max_energy_grid,
  			       convergence_tol,
  			       absolute_diff_tol,
  			       distance_tol );
}

// Evaluate the processed adjoint incoherent cross section
template<typename TwoDInterpPolicy>
double AdjointIncoherentGridGenerator::evaluateProcessedCrossSection( 
				      const double processed_energy,
				      const double processed_max_energy ) const
{
  // Make sure the same inerpolation is used for the energy and max energy
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  
  double cross_section = 
    d_adjoint_incoherent_cross_section.evaluateCrossSection( 
      TwoDInterpPolicy::recoverProcessedFirstIndepVar( processed_energy ),
      TwoDInterpPolicy::recoverProcessedSecondIndepVar( processed_max_energy ),
      1e-3 );

  if( cross_section > 0.0 )
    return TwoDInterpPolicy::processDepVar( cross_section );
  else
  {
    return TwoDInterpPolicy::processDepVar(std::numeric_limits<double>::min());
  }
}

// Check for 2D grid convergence
template<typename TwoDInterpPolicy>
bool AdjointIncoherentGridGenerator::hasGridConverged( 
		    const double processed_energy_0,
		    const double processed_energy_1,
		    const Teuchos::Array<double>& processed_max_energy_grid_0,
		    const Teuchos::Array<double>& processed_max_energy_grid_1,
		    const Teuchos::Array<double>& processed_cross_section_0,
		    const Teuchos::Array<double>& processed_cross_section_1,
		    const double convergence_tol,
		    const double absolute_diff_tol,
		    const double distance_tol ) const
{
  // Make sure the same inerpolation is used for the energy and max energy
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  // Make sure the process energies are valid
  testPrecondition( processed_energy_0 < processed_energy_1 );
  // Make sure the processed max energy grids are valid
  testPrecondition( Utility::Sort::isSortedAscending( 
					 processed_max_energy_grid_0.begin(),
					 processed_max_energy_grid_0.end() ) );
  testPrecondition( Utility::Sort::isSortedAscending(
					 processed_max_energy_grid_1.begin(),
					 processed_max_energy_grid_1.end() ) );
  // Make sure the processed cross sections are valid
  testPrecondition( processed_cross_section_0.size() == 
		    processed_max_energy_grid_0.size() );
  testPrecondition( processed_cross_section_1.size() ==
		    processed_max_energy_grid_1.size() );

  bool converged = true;

  double distance = 
    Utility::Policy::relError( processed_energy_0, processed_energy_1 );

  if( distance > distance_tol )
  {
    // Generate an optimized grid at the intermediate energy
    const double intermediate_processed_energy = 
      0.5*(processed_energy_0+processed_energy_1);
    
    Teuchos::Array<double> max_energy_grid_mid, cross_section_grid_mid;
    
    this->generate<TwoDInterpPolicy>( max_energy_grid_mid,
				      cross_section_grid_mid,
				      intermediate_processed_energy,
				      convergence_tol,
				      absolute_diff_tol,
				      distance_tol );
    
    for( unsigned i = 0; i < max_energy_grid_mid.size(); ++i )
    {
      // Check for convergence at the grid point
      double interp_processed_cross_section = TwoDInterpPolicy::processDepVar(
	TwoDInterpPolicy::interpolateProcessedUnitBase( 
					   processed_energy_0,
					   processed_energy_1,
					   intermediate_processed_energy,
					   max_energy_grid_mid[i],
					   processed_max_energy_grid_0.begin(),
					   processed_max_energy_grid_0.end(),
					   processed_cross_section_0.begin(),
					   processed_cross_section_0.end(),
					   processed_max_energy_grid_1.begin(),
					   processed_max_energy_grid_1.end(),
					   processed_cross_section_1.begin(),
					   processed_cross_section_1.end() ) );
    
      double relative_error =
	Utility::Policy::relError( cross_section_grid_mid[i],
				   interp_processed_cross_section );

      double abs_diff = fabs( cross_section_grid_mid[i] -
			      interp_processed_cross_section );

      if( relative_error > convergence_tol &&
	abs_diff > absolute_diff_tol )
      {
	converged = false;
	
	break;
      }
      else if( relative_error > convergence_tol &&
	       abs_diff <= absolute_diff_tol )
      {
	std::cerr << "Warning: absolute difference tolerance hit before "
		  << "convergence - processed_energy_0="
		  << processed_energy_0 << ", processed_energy_1="
		  << processed_energy_1 << ", processed_max_energy="
		  << max_energy_grid_mid[i] << ", abs_diff_cs="
		  << abs_diff << std::endl;
      }

      // Check for convergence at the grid mid point
      if( i < max_energy_grid_mid.size()-1 )
      {
	double max_energy_mid_point = 0.5*(max_energy_grid_mid[i]+
					   max_energy_grid_mid[i+1]);
	
	interp_processed_cross_section = TwoDInterpPolicy::processDepVar(
	  TwoDInterpPolicy::interpolateProcessedUnitBase( 
					   processed_energy_0,
					   processed_energy_1,
					   intermediate_processed_energy,
					   max_energy_mid_point,
					   processed_max_energy_grid_0.begin(),
					   processed_max_energy_grid_0.end(),
					   processed_cross_section_0.begin(),
					   processed_cross_section_0.end(),
					   processed_max_energy_grid_1.begin(),
					   processed_max_energy_grid_1.end(),
					   processed_cross_section_1.begin(),
					   processed_cross_section_1.end() ) );
    
	double true_processed_cross_section = 
	  this->evaluateProcessedCrossSection<TwoDInterpPolicy>( 
						 intermediate_processed_energy,
						 max_energy_mid_point );
	
	relative_error =
	  Utility::Policy::relError( true_processed_cross_section,
				     interp_processed_cross_section );

	abs_diff = fabs( true_processed_cross_section -
			 interp_processed_cross_section );

	if( relative_error > convergence_tol &&
	    abs_diff > absolute_diff_tol )
	{
	  converged = false;
	  
	  break;
	}
	else if( relative_error > convergence_tol &&
	       abs_diff <= absolute_diff_tol )
	{
	  std::cerr << "Warning: absolute difference tolerance hit before "
		    << "convergence - processed_energy_0="
		    << processed_energy_0 << ", processed_energy_1="
		    << processed_energy_1 << ", processed_max_energy="
		    << max_energy_grid_mid[i] << ", abs_diff_cs="
		    << abs_diff << std::endl;
	}
      }
    }    
  }
  else
  {
    std::cerr << "Warning: distance tolerance hit before convergence - "
	      << "relError(processed_energy_0,processed_energy_1) =\n" 
	      << "relError(" << processed_energy_0 << "," 
	      << processed_energy_1 << ") = " << distance << std::endl;
  }
    
  return converged;
}

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator_def.hpp
//---------------------------------------------------------------------------//
