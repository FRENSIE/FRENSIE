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

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_AdjointKleinNishinaDistribution.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"

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
  
  //! Constructor
  AdjointIncoherentGridGenerator( 
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );

  //! Destructor
  ~AdjointIncoherentGridGenerator()
  { /* ... */ }

  //! Generate the bilinear grid
  void generate( Teuchos::Array<double>& log_max_energy_grid,
		 Teuchos::Array<Teuchos::Array<double> >& log_energy_grids,
		 const Teuchos::Array<double>& initial_log_max_energy_grid,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 ) const;

  //! Evaluate the log adjoint incoherent cross section on the specified grid
  void evaluateLogCrossSectionOnGrid( 
			     const Teuchos::Array<double>& log_max_energy_grid,
			     const Teuchos::Array<Teuchos::Array<double> >&
			     log_energy_grids,
                             Teuchos::Array<Teuchos::Array<double> >&
			     log_adjoint_incoherent_cross_section ) const;
			     
private:

  // Get the lower log energy limit for a given log max energy
  static double getLowerLogEnergyLimit( const double log_max_energy );

  // Get the upper log energy limit for a given log max energy
  static double getUpperLogEnergyLimit( const double log_max_energy );

  // Get the log energy of the cross section peak for a given log max energy
  static double getLogEnergyOfCrossSectionPeak( const double log_max_energy );

  // Evaluate the differential adjoint incoherent cross section (dc/dx)
  double evaluateDifferentialAdjointIncoherentCrossSection(
	  const double inverse_energy_gain_ratio, 
	  const Utility::AdjointKleinNishinaDistribution& distribution ) const;

  // Evaluate the log of the adjoint incoherent cross section
  double evaluateLogAdjointIncoherentCrossSection( 
					       const double log_max_energy, 
					       const double log_energy ) const;

  // The min table energy
  static double min_table_energy;

  // The max table energy
  static double max_table_energy;
  
  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;

  // The quadrature kernel
  Utility::GaussKronrodQuadratureKernel d_quadrature_kernel;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.hpp
//---------------------------------------------------------------------------//
