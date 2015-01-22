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
#include "Utility_InterpolationPolicy.hpp"

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
  template<typename InterpPolicy>
  void generate( Teuchos::Array<double>& energy_grid,
		 Teuchos::Array<Teuchos::Array<double> >& max_energy_grids,
		 const Teuchos::Array<double>& initial_energy_grid,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 );

  //! Generate a max energy at the desired energy
  template<typename InterpPolicy>
  void generate( Teuchos::Array<double>& max_energy_grid,
		 const double energy,
		 const double convergence_tol = 0.001,
		 const double absolute_diff_tol = 1e-12,
		 const double distance_tol = 1e-14 );

  //! Evaluate the log adjoint incoherent cross section on the specified grid
  template<typename InterpPolicy>
  void evaluateCrossSectionOnGrid( 
			     const Teuchos::Array<double>& energy_grid,
			     const Teuchos::Array<Teuchos::Array<double> >&
			     max_energy_grids,
                             Teuchos::Array<Teuchos::Array<double> >&
			     adjoint_incoherent_cross_section );
			     
private:

  // The min table energy
  static double min_table_energy;

  // The max table energy
  static double max_table_energy;
  
  // The adjoint incoherent cross section evaluator
  AdjointIncoherentCrossSectionEvaluator d_adjoint_incoherent_cross_section;

  
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.hpp
//---------------------------------------------------------------------------//
