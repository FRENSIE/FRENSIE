//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator.hpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP
#define DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentCrossSectionEvaluator.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"

namespace DataGen{

//! The adjoint incoherent cross section grid generator
class AdjointIncoherentGridGenerator
{

public:

  //! Set the min table energy (default is 0.0001 MeV)
  static void setMinTableEnergy( const double min_energy );

  //! Get the min table energy
  static double getMinTableEnergy();

  //! Set the max table energy (default is 20.0 MeV)
  static void setMaxTableEnergy( const double max_energy );

  //! Get the max table energy
  static double getMaxTableEnergy();

  //! Set the energy to max energy nudge factor
  static void setEnergyToMaxEnergyNudgeFactor( const double factor );

  //! Get the energy to max energy nudge factor
  static double getEnergyToMaxEnergyNudgeFactor();

  //! Set verbose mode to on
  static void setVerboseOn();

  //! Set verbose mode to off
  static void setVerboseOff();
  
  //! Constructor
  AdjointIncoherentGridGenerator( 
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );

  //! Destructor
  ~AdjointIncoherentGridGenerator()
  { /* ... */ }

  //! Generate the bilinear grid
  template<typename TwoDInerpPolicy>
  void generate( Teuchos::Array<double>& energy_grid,
		 Teuchos::Array<Teuchos::Array<double> >& max_energy_grids,
		 Teuchos::Array<Teuchos::Array<double> >& cross_section,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 ) const;

  //! Generate a max energy grid at the desired energy
  template<typename TwoDInterpPolicy>
  void generate( Teuchos::Array<double>& processed_max_energy_grid,
		 Teuchos::Array<double>& processed_cross_section,
		 const double processed_energy,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 ) const;

  //! Evaluate the processed adjoint incoherent cross section
  template<typename TwoDInterpPolicy>
  double evaluateProcessedCrossSection( 
				     const double processed_energy,
				     const double processed_max_energy ) const;

  //! Check for 2D grid convergence
  template<typename TwoDInterpPolicy>
  bool hasGridConverged( 
		   const double processed_energy_0,
		   const double processed_energy_1,
		   const Teuchos::Array<double>& processed_max_energy_grid_0,
		   const Teuchos::Array<double>& processed_max_energy_grid_1,
		   const Teuchos::Array<double>& processed_cross_section_0,
		   const Teuchos::Array<double>& processed_cross_section_1,
		   const double convergence_tol = 0.001,
		   const double absolute_diff_tol = 1e-12,
		   const double distance_tol = 1e-14 ) const;
			     
private:

  // The min table energy
  static double s_min_table_energy;

  // The max table energy (highest energy grid point)
  static double s_max_table_energy;

  // The max table energy increase factor
  static double s_max_table_energy_nudge_factor;

  // The max table energy (highest max energy grid point)
  static double s_nudged_max_table_energy;

  // The energy to max energy nudge factor
  static double s_energy_to_max_energy_nudge_factor;

  // The verbose mode
  static bool s_verbose;
  
  // The adjoint incoherent cross section evaluator
  AdjointIncoherentCrossSectionEvaluator d_adjoint_incoherent_cross_section;  
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_AdjointIncoherentGridGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.hpp
//---------------------------------------------------------------------------//
