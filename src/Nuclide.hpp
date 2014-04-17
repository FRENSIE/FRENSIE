//---------------------------------------------------------------------------//
//!
//! \file   Nuclide.hpp
//! \author Alex Robinson
//! \brief  The nuclide class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLIDE_HPP
#define NUCLIDE_HPP

namespace FACEMC{

/*! The nuclide class
 * \details This is the base class for all nuclides. No fission data is
 * maintained in the base class.
 */
class Nuclide
{

public:

  // Constructor
  Nuclide( const unsigned atomic_number,
	   const unsigned atomic_mass_number,
	   const unsigned isomer_number,
	   const double atomic_weight_ratio,
	   const double temperature,
	   const Teuchos::ArrayView<const int>& energy_grid,
	   const Teuchos::ArrayView<const int>& absorption_cross_section,
	   const Teuchos::RCP<NuclearReaction>& elastic_scattering_reaction,
	   const Teuchos::Array<Teuchos::RCP<NuclearReaction> >&
	   non_elastic_reactions );
  

  // Destructor
  virtual ~Nuclide()
  { /* ... */ }

private:

  // The atomic number of the nuclide
  unsigned d_atomic_number;
  
  // The atomic mass number
  unsigned d_atomic_mass_number;

  // The nuclear isomer number
  unsigned d_isomer_number;

  // The weight of the nucleus in neutron masses
  double d_atomic_weight_ratio;
  
  // The temperature of the nuclide (MeV)
  double d_temperature;

  // The incoming energy grid for all nuclide cross sections
  Teuchos::Array<double> d_energy_grid;

  // The microscopic total cross sections
  Teuchos::Array<double> d_total_cross_section;

  // The microscopic absorption cross section
  // Note: absorption is (n,0n) + Sum_x(n,xnf)
  Teuchos::Array<double> d_absorption_cross_section;

  // The elastic scattering interaction data (including micro cross section)
  Teuchos::RCP<NuclearReaction> d_elastic_scattering_reaction;
  
  // All nuclear interactions (other than elastic scattering)
  Teuchos::Array<Teuchos::RCP<NuclearReaction> > d_nuclear_reactions;
};

} // end FACEMC namespace

#endif // end NUCLIDE_HPP

//---------------------------------------------------------------------------//
// end Nuclide.hpp
//---------------------------------------------------------------------------//
