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
#include <Teuchos_Array.hpp>

namespace DataGen{

//! The adjoint incoherent cross section grid generator
class AdjointIncoherentGridGenerator
{

public:

  //! Constructor
  AdjointIncoherentGridGenerator()
  { /* ... */ }

  //! Destructor
  virtual ~AdjointIncoherentGridGenerator()
  { /* ... */ }
  
  //! Set the min table energy (default is 0.0001 MeV)
  static void setMinTableEnergy( const double min_energy );

  //! Get the min table energy
  static double getMinTableEnergy();

  //! Set the max table energy (default is 20.0 MeV)
  static void setMaxTableEnergy( const double max_energy );

  //! Get the max table energy
  static double getMaxTableEnergy();

  //! Get the max table energy nudge factor
  static double getNudgedMaxTableEnergy();

  //! Set the energy to max energy nudge factor
  static void setEnergyToMaxEnergyNudgeFactor( const double factor );

  //! Get the energy to max energy nudge factor
  static double getEnergyToMaxEnergyNudgeFactor();

  //! Generate the bilinear grid
  virtual void generate( 
	     Teuchos::Array<double>& energy_grid,
	     Teuchos::Array<Teuchos::Array<double> >& max_energy_grids,
	     Teuchos::Array<Teuchos::Array<double> >& cross_section) const = 0;

  //! Generate a max energy grid at the desired energy
  virtual void generate( Teuchos::Array<double>& max_energy_grid,
			 Teuchos::Array<double>& cross_section,
			 const double energy ) const = 0;

private:
  
  // The min table energy
  static double s_min_table_energy;

  // The max table energy (highest energy grid point)
  static double s_max_table_energy;

  // The max table energy increase factor
  static const double s_max_table_energy_nudge_factor;

  // The max table energy (highest max energy grid point)
  static double s_nudged_max_table_energy;

  // The energy to max energy nudge factor
  static double s_energy_to_max_energy_nudge_factor;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.hpp
//---------------------------------------------------------------------------//
