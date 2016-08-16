//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronGridGenerator.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron grid generator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_HPP
#define DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_HPP

namespace DataGen{

//! The adjoint electron cross section grid generator
class AdjointElectronGridGenerator
{

public:

  //! Set the min table energy (default is 0.00001 MeV)
  static void setMinTableEnergy( const double min_energy );

  //! Get the min table energy
  static double getMinTableEnergy();

  //! Set the max table energy (default is 20.0 MeV)
  static void setMaxTableEnergy( const double max_energy );

  //! Get the max table energy
  static double getMaxTableEnergy();

  //! Generate the bilinear grid
  virtual void generate(
	     std::vector<double>& energy_grid,
	     std::vector<std::vector<double> >& max_energy_grids,
	     std::vector<std::vector<double> >& cross_section) const = 0;

  //! Generate a max energy grid at the desired energy
  virtual void generate( std::vector<double>& max_energy_grid,
			 std::vector<double>& cross_section,
			 const double energy ) const = 0;

private:

  // The min table energy
  static double s_min_table_energy;

  // The max table energy (highest energy grid point)
  static double s_max_table_energy;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronGridGenerator.hpp
//---------------------------------------------------------------------------//
