//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointIncoherentGridGenerator_def.hpp
//! \author Alex Robinson
//! \brief  Standard adjoint incoherent grid generator template definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ADJOINT_INCOHERENT_GRID_GENERATOR_DEF_HPP
#define DATA_GEN_STANDARD_ADJOINT_INCOHERENT_GRID_GENERATOR_DEF_HPP

// Std Lib
#include <deque>
#include <algorithm>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
template<typename TwoDInterpPolicy>
StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::StandardAdjointIncoherentGridGenerator(
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const double convergence_tol,
      const double absolute_diff_tol,
      const double distance_tol )
  : d_verbose( false ),
    d_precision( 1e-3 ),
    d_convergence_tol( convergence_tol ),
    d_absolute_diff_tol( absolute_diff_tol ),
    d_distance_tol( distance_tol ),
    d_max_energy_grid_generator( convergence_tol, 
				 absolute_diff_tol,
				 distance_tol ),
    d_adjoint_incoherent_cross_section( 20.0, scattering_function )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  // Make sure the tolerances are valid
  testPrecondition( convergence_tol > 0.0 );
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( absolute_diff_tol > 0.0 );
  testPrecondition( distance_tol > 0.0 );
}

// Set verbose mode to on
template<typename TwoDInterpPolicy>
void StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::setVerboseModeOn()
{
  d_verbose = true;
}

// Set verbose mode to off
template<typename TwoDInterpPolicy>
void StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::setVerboseModeOff()
{
  d_verbose = false;
}

// Set the convergence tolerance
template<typename TwoDInterpPolicy>
void StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::setConvergenceTolerance( const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol > 0.0 );
  testPrecondition( convergence_tol <= 1.0 );
  
  d_convergence_tol = convergence_tol;

  d_max_energy_grid_generator.setConvergenceTolerance( convergence_tol );
}
  
// Set the absolute difference tolerance
template<typename TwoDInterpPolicy>
void StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::setAbsoluteDifferenceTolerance( const double absolute_diff_tol )
{
  // Make sure the absolute diff tolerance is valid
  testPrecondition( absolute_diff_tol > 0.0 );

  d_absolute_diff_tol = absolute_diff_tol;

  d_max_energy_grid_generator.setAbsoluteDifferenceTolerance( 
							   absolute_diff_tol );
}

// Set the distance tolerance
template<typename TwoDInterpPolicy>
void StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::setDistanceTolerance( const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol > 0.0 );

  d_distance_tol = distance_tol;

  d_max_energy_grid_generator.setAbsoluteDifferenceTolerance( distance_tol );
}

// Generate the bilinear grid
template<typename TwoDInterpPolicy>
void StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::generate( 
		 Teuchos::Array<double>& energy_grid,
		 Teuchos::Array<Teuchos::Array<double> >& max_energy_grids,
		 Teuchos::Array<Teuchos::Array<double> >& cross_section ) const
{
  // Make sure the same inerpolation is used for the energy and max energy
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  // Reset the energy grid
  energy_grid.clear();
      
  // Reset the max energy grids and cross section
  max_energy_grids.clear();
  cross_section.clear();

  // Initialize the energy grid queue
  std::deque<double> energy_grid_queue;
  
  energy_grid_queue.push_back( getMinTableEnergy() );

  double energy_of_max_cs = getEnergyOfMaxCrossSection( 
						   getNudgedMaxTableEnergy() );
  if( energy_of_max_cs > getMinTableEnergy() )
  {
    energy_grid_queue.push_back( energy_of_max_cs );
  }
  
  energy_grid_queue.push_back( getMaxTableEnergy() );

  double energy_0, energy_1;
  Teuchos::Array<double> max_energy_grid_0, max_energy_grid_1;
  Teuchos::Array<double> cross_section_grid_0, cross_section_grid_1;

  // Generate the first max energy grid
  energy_0 = energy_grid_queue.front();
  energy_grid_queue.pop_front();
  
  this->generate( max_energy_grid_0, cross_section_grid_0, energy_0 );
  
  // Optimize the 2D grid
  while( !energy_grid_queue.empty() )
  {
    // Generate the max energy grid at the second energy grid point
    energy_1 = energy_grid_queue.front();
    
    this->generate( max_energy_grid_1, cross_section_grid_1, energy_1 );
    
    bool converged = this->hasGridConverged( energy_0, 
					     energy_1, 
					     max_energy_grid_0, 
					     max_energy_grid_1,
					     cross_section_grid_0,
					     cross_section_grid_1 );
    
    // Keep the grid points
    if( converged )
    {
      energy_grid.push_back( energy_0 );
      max_energy_grids.push_back( max_energy_grid_0 );
      cross_section.push_back( cross_section_grid_0 );
      
      if( d_verbose )
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
      energy_grid_queue.push_front( 
			 this->calculateEnergyMidpoint( energy_0, energy_1 ) );
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
void StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::generate( 
			               Teuchos::Array<double>& max_energy_grid,
				       Teuchos::Array<double>& cross_section,
				       const double energy ) const
{
  // Make sure the same inerpolation is used for the energy and max energy
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  // Make sure the energy is valid
  testPrecondition( energy <= getNudgedMaxTableEnergy() );
  
  // Load the initial max energy grid
  
  if( doesEnergyCorrespondToAMaxCrossSectionValue( energy ) )
  {
    double max_energy_of_max_cs = 
      getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( energy );
    
    if( max_energy_of_max_cs < getNudgedMaxTableEnergy() )
    {
      max_energy_grid.resize( 3 );
      
      max_energy_grid[0] = energy*(1.0 + getEnergyToMaxEnergyNudgeFactor() );
      max_energy_grid[1] = max_energy_of_max_cs;
      max_energy_grid[2] = getNudgedMaxTableEnergy();
    }
    else
    {
      max_energy_grid.resize( 2 );
    
      max_energy_grid[0] = energy*(1.0 + getEnergyToMaxEnergyNudgeFactor() );
    
      max_energy_grid[1] = getNudgedMaxTableEnergy();
    }
  }
  else
  {
    max_energy_grid.resize( 2 );
    
    max_energy_grid[0] = energy*(1.0 + getEnergyToMaxEnergyNudgeFactor() );
    
    max_energy_grid[1] = getNudgedMaxTableEnergy();
  }

  // Create the boost function that returns the processed cross section
  boost::function<double (double max_energy)> grid_function = 
    boost::bind( &MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSection,
		 boost::cref( d_adjoint_incoherent_cross_section ),
		 energy,
		 _1,
		 d_precision );

  d_max_energy_grid_generator.generateAndEvaluateInPlace( max_energy_grid,
							  cross_section,
							  grid_function );
}

// Check for 2D grid convergence
template<typename TwoDInterpPolicy>
bool 
StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::hasGridConverged( 
		          const double energy_0,
			  const double energy_1,
			  const Teuchos::Array<double>& max_energy_grid_0,
			  const Teuchos::Array<double>& max_energy_grid_1,
			  const Teuchos::Array<double>& cross_section_0,
			  const Teuchos::Array<double>& cross_section_1 ) const
{
  // Make sure the same inerpolation is used for the energy and max energy
  testStaticPrecondition( (boost::is_same<typename TwoDInterpPolicy::FirstIndepVarProcessingTag,typename TwoDInterpPolicy::SecondIndepVarProcessingTag>::value) );
  // Make sure the process energies are valid
  testPrecondition( energy_0 < energy_1 );
  // Make sure the processed max energy grids are valid
  testPrecondition( Utility::Sort::isSortedAscending( 
					 max_energy_grid_0.begin(),
					 max_energy_grid_0.end() ) );
  testPrecondition( Utility::Sort::isSortedAscending(
					 max_energy_grid_1.begin(),
					 max_energy_grid_1.end() ) );
  // Make sure the processed cross sections are valid
  testPrecondition( cross_section_0.size() == 
		    max_energy_grid_0.size() );
  testPrecondition( cross_section_1.size() ==
		    max_energy_grid_1.size() );

  bool converged = true;

  double distance = Utility::Policy::relError( energy_0, energy_1 );

  if( distance > d_distance_tol )
  {
    // Generate an optimized grid at the intermediate energy
    const double intermediate_energy = 
      this->calculateEnergyMidpoint( energy_0, energy_1 );
        
    Teuchos::Array<double> max_energy_grid_mid, cross_section_grid_mid;
    
    this->generate( max_energy_grid_mid,
		    cross_section_grid_mid,
		    intermediate_energy );
    
    for( unsigned i = 0; i < max_energy_grid_mid.size(); ++i )
    {
      // Check for convergence at the grid point
      double interp_cross_section = TwoDInterpPolicy::interpolateUnitBase( 
					   energy_0,
					   energy_1,
					   intermediate_energy,
					   max_energy_grid_mid[i],
					   max_energy_grid_0.begin(),
					   max_energy_grid_0.end(),
					   cross_section_0.begin(),
					   cross_section_0.end(),
					   max_energy_grid_1.begin(),
					   max_energy_grid_1.end(),
					   cross_section_1.begin(),
					   cross_section_1.end() );
    
      double relative_error =
	Utility::Policy::relError( cross_section_grid_mid[i],
				   interp_cross_section );

      double abs_diff = fabs( cross_section_grid_mid[i] -
			      interp_cross_section );

      if( relative_error > d_convergence_tol &&
	  abs_diff > d_absolute_diff_tol )
      {
	converged = false;
	
	break;
      }
      else if( relative_error > d_convergence_tol &&
	       abs_diff <= d_absolute_diff_tol )
      {
	std::cerr << "Warning: absolute difference tolerance hit before "
		  << "convergence - energy_0="
		  << energy_0 << ", energy_1="
		  << energy_1 << ", max_energy="
		  << max_energy_grid_mid[i] << ", abs_diff_cs="
		  << abs_diff << std::endl;
      }

      // Check for convergence at the grid mid point
      if( i < max_energy_grid_mid.size()-1 )
      {
	double max_energy_mid_point = this->calculateMaxEnergyMidpoint( 
						    max_energy_grid_mid[i],
						    max_energy_grid_mid[i+1] );
	
	interp_cross_section = TwoDInterpPolicy::interpolateUnitBase( 
					   energy_0,
					   energy_1,
					   intermediate_energy,
					   max_energy_mid_point,
					   max_energy_grid_0.begin(),
					   max_energy_grid_0.end(),
					   cross_section_0.begin(),
					   cross_section_0.end(),
					   max_energy_grid_1.begin(),
					   max_energy_grid_1.end(),
					   cross_section_1.begin(),
					   cross_section_1.end() );
    
	double true_cross_section = 
	  d_adjoint_incoherent_cross_section.evaluateIntegratedCrossSection(
							intermediate_energy,
							max_energy_mid_point,
							d_precision );
	
	relative_error = Utility::Policy::relError( true_cross_section,
						    interp_cross_section );

	abs_diff = fabs( true_cross_section - interp_cross_section );

	if( relative_error > d_convergence_tol &&
	    abs_diff > d_absolute_diff_tol )
	{
	  converged = false;
	  
	  break;
	}
	else if( relative_error > d_convergence_tol &&
		 abs_diff <= d_absolute_diff_tol )
	{
	  std::cerr.precision( 18 );
	  std::cerr << "Warning: absolute difference tolerance hit before "
		    << "convergence - energy_0="
		    << energy_0 << ", energy_1="
		    << energy_1 << ", max_energy="
		    << max_energy_grid_mid[i] << ", abs_diff_cs="
		    << abs_diff << std::endl;
	}
      }
    }    
  }
  else
  {
    std::cerr.precision( 18 );
    std::cerr << "Warning: distance tolerance hit before convergence - "
	      << "relError(energy_0,energy_1) =\n" 
	      << "relError(" << energy_0 << "," 
	      << energy_1 << ") = " << distance << std::endl;
  }
    
  return converged;
}

// Calculate the energy midpoint
template<typename TwoDInterpPolicy>
double StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::calculateEnergyMidpoint( 
						  const double energy_0,
						  const double energy_1 ) const
{
  return TwoDInterpPolicy::recoverProcessedFirstIndepVar(
		   0.5*(TwoDInterpPolicy::processFirstIndepVar(energy_0) +
			TwoDInterpPolicy::processFirstIndepVar(energy_1) ) );
}

// Calculate the max energy 
template<typename TwoDInterpPolicy>
double StandardAdjointIncoherentGridGenerator<TwoDInterpPolicy>::calculateMaxEnergyMidpoint( 
					      const double max_energy_0,
					      const double max_energy_1 ) const
{
  return TwoDInterpPolicy::recoverProcessedSecondIndepVar(
		0.5*(TwoDInterpPolicy::processSecondIndepVar(max_energy_0) +
		     TwoDInterpPolicy::processSecondIndepVar(max_energy_1) ) );
}

} // end DataGen

#endif // end DATA_GEN_STANDARD_ADJOINT_INCOHERENT_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator_def.hpp
//---------------------------------------------------------------------------//
