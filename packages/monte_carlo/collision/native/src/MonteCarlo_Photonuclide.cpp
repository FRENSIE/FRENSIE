//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photonuclide.cpp
//! \author Alex Robinson
//! \brief  The photonuclide class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_Photonuclide.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Return the photonuclide name
const std::string& Photonuclide::getName() const
{
  return "";
}

// Return the atomic number of the photonuclide
unsigned Photonuclide::getAtomicNumber() const
{
  return 0u;
}

// Return the atomic mass number of the photonuclide
unsigned Photonuclide::getAtomicMassNumber() const
{
  return 0u;
}

// Return the nuclear isomer number of the photonuclide
unsigned Photonuclide::getIsomerNumber() const
{
  return 0u;
}
  
// Return the atomic weight ratio
double Photonuclide::getAtomicWeightRatio() const
{
  return 0.0;
}

// Return the temperature of the photonuclide (in MeV)
double Photonuclide::getTemperature() const
{
  return 0.0;
}

// Return the total cross section at the desired energy
double Photonuclide::getTotalCrossSection( const double energy ) const
{
  return 0.0;
}

// Return the total absorption cross section at the desired energy
double Photonuclide::getAbsorptionCrossSection( const double energy ) const
{
  return 0.0;
}
  
// Return the survival probability at the desired energy
double Photonuclide::getSurvivalProbability( const double energy ) const
{
  return 0.0;
}

// Return the cross section for a specific photonuclear reaction
double Photonuclide::getReactionCrossSection( 
				const double energy,
				const PhotonuclearReactionType reaction ) const
{
  return 0.0;
}

// Collide with a photon
void Photonuclide::collideAnalogue( PhotonState& photon, 
				    ParticleBank& bank ) const
{

}

// Collide with a photon and survival bias
void Photonuclide::collideSurvivalBias( PhotonState& photon, 
					ParticleBank& bank ) const
{

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Photonuclide.cpp
//---------------------------------------------------------------------------//
