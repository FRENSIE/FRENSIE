//---------------------------------------------------------------------------//
//!
//! \file   Nuclide.hpp
//! \author Alex Robinson
//! \brief  The nuclide class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLIDE_HPP
#define NUCLIDE_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// FACEMC Includes
#include "XSSNeutronDataExtractor.hpp"
#include "NuclearReaction.hpp"

namespace FACEMC{

/*! The nuclide class
 * \details This is the base class for all nuclides. No fission data is
 * maintained in the base class.
 */
class Nuclide
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  Nuclide( const std::string& name,
	   const unsigned atomic_number,
	   const unsigned atomic_mass_number,
	   const unsigned isomer_number,
	   const double atomic_weight_ratio,
	   const double temperature,
	   const XSSNeutronDataExtractor& raw_nuclide_data );
  

  //! Destructor
  virtual ~Nuclide()
  { /* ... */ }

  //! Return the nuclide name
  const std::string& getName() const;

  //! Return the atomic number of the nuclide
  unsigned getAtomicNumber() const;

  //! Return the atomic mass number of the nuclide
  unsigned getAtomicMassNumber() const;

  //! Return the nuclear isomer number of the nuclide
  unsigned getIsomerNumber() const;
  
  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;

  //! Return the temperature of the nuclide (in MeV)
  double getTemperature() const;
  
  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;
  
  //! Return the survival probability at the desired energy
  double getSurvivalProbability( const double energy ) const;

  //! Return the cross section for a specific nuclear reaction
  double getReactionCrossSection( const double energy,
				  const NuclearReactionType reaction ) const;

  //! Collide with a neutron
  void collideAnalogue( NeutronState& neutron, ParticleBank& bank ) const;

  //! Collide with a neutron and survival bias
  void collideSurvivalBias( NeutronState& neutron, ParticleBank& bank ) const;

private:

  // The nuclide name
  std::string d_name;

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
  Teuchos::ArrayRCP<double> d_energy_grid;

  // The microscopic total cross sections
  Teuchos::Array<double> d_total_cross_section;

  // The microscopic absorption cross section
  // Note: absorption is (n,0n) + Sum_x(n,xnf)
  Teuchos::Array<double> d_absorption_cross_section;

  // The nuclear reactions
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >
  d_nuclear_reactions;
};

} // end FACEMC namespace

#endif // end NUCLIDE_HPP

//---------------------------------------------------------------------------//
// end Nuclide.hpp
//---------------------------------------------------------------------------//
