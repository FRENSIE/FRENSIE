//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointIncoherentGridGenerator.hpp
//! \author Alex Robinson
//! \brief  Standard adjoint incoherent grid generator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP
#define DATA_GEN_STANDARD_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentCrossSectionHelpers.hpp"
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_GridGenerator.hpp"

namespace DataGen{

//! The adjoint incoherent cross section grid generator
template<typename TwoDInterpPolicy>
class StandardAdjointIncoherentGridGenerator : public AdjointIncoherentGridGenerator
{

public:
  
  //! Constructor
  StandardAdjointIncoherentGridGenerator( 
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const double convergence_tol = 0.001,
      const double absolute_diff_tol = 1e-12,
      const double distance_tol = 1e-14 );

  //! Destructor
  ~StandardAdjointIncoherentGridGenerator()
  { /* ... */ }

  //! Set verbose mode to on
  void setVerboseModeOn();

  //! Set verbose mode to off
  void setVerboseModeOff();

  //! Set the convergence tolerance
  void setConvergenceTolerance( const double convergence_tol );
  
  //! Set the absolute difference tolerance
  void setAbsoluteDifferenceTolerance( const double absolute_diff_tol );
  
  //! Set the distance tolerance
  void setDistanceTolerance( const double distance_tol );

  //! Generate the bilinear grid
  void generate( Teuchos::Array<double>& energy_grid,
		 Teuchos::Array<Teuchos::Array<double> >& max_energy_grids,
		 Teuchos::Array<Teuchos::Array<double> >& cross_section) const;

  //! Generate a max energy grid at the desired energy
  void generate( Teuchos::Array<double>& max_energy_grid,
		 Teuchos::Array<double>& cross_section,
		 const double energy ) const;

  //! Check for 2D grid convergence
  bool hasGridConverged( const double energy_0,
			 const double energy_1,
			 const Teuchos::Array<double>& max_energy_grid_0,
			 const Teuchos::Array<double>& max_energy_grid_1,
			 const Teuchos::Array<double>& cross_section_0,
			 const Teuchos::Array<double>& cross_section_1 ) const;
			     
private:

  // Calculate the energy midpoint
  double calculateEnergyMidpoint( const double energy_0,
				  const double energy_1 ) const;

  // Calculate the max enery midpoint
  double calculateMaxEnergyMidpoint( const double max_energy_0,
				     const double max_energy_1 ) const;

  // The verbosity
  bool d_verbose;

  // The cross section evaluation precision
  double d_precision;

  // The convergence tolerance
  double d_convergence_tol;

  // The absolute difference tolerance
  double d_absolute_diff_tol;
  
  // The distance tolerance
  double d_distance_tol;

  // The grid generator
  Utility::GridGenerator<typename TwoDInterpPolicy::ZYInterpPolicy> 
  d_max_energy_grid_generator;
  
  // The adjoint incoherent cross section evaluator
  MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution 
  d_adjoint_incoherent_cross_section;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_StandardAdjointIncoherentGridGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_STANDARD_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointIncoherentGridGenerator.hpp
//---------------------------------------------------------------------------//
