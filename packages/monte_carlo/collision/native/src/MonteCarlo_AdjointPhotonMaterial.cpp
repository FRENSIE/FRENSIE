//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  Adjoint photon material class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotonMaterial::AdjointPhotonMaterial(
                   const ModuleTraits::InternalMaterialHandle id,
                   const double density,
                   const AdjointPhotoatomNameMap& adjoint_photoatom_name_map,
                   const Teuchos::Array<double>& adjoint_photoatom_fractions,
                   const Teuchos::Array<std::string>& adjoint_photoatom_names )
  : d_id( id ),
    d_number_density( density ),
    d_atoms( adjoint_photoatom_fractions.size() )
{
  // Make sure the id is valid
  testPrecondition( id != ModuleTraits::invalid_internal_material_handle );
  // Make sure the density is valid
  testPrecondition( density != 0.0 );
  // Make sure the fraction values are valid (all positive or all negative)
  testPrecondition( areFractionValuesValid(adjoint_photoatom_fractions.begin(),
					   adjoint_photoatom_fractions.end()));
  testPrecondition( adjoint_photoatom_fractions.size() ==
                    adjoint_photoatom_names.size() );

  // Copy the photoatoms that make up this material
  for( unsigned i = 0u; i < adjoint_photoatom_fractions.size(); ++i )
  {
    d_atoms[i].first = adjoint_photoatom_fractions[i];

    AdjointPhotoatomNameMap::const_iterator atom =
      adjoint_photoatom_name_map.find( adjoint_photoatom_names[i] );

    TEST_FOR_EXCEPTION( atom == adjoint_photoatom_name_map.end(),
			std::logic_error,
			"Error: atom " << adjoint_photoatom_names[i] <<
			" has not been loaded!" );

    d_atoms[i].second = atom->second;
  }

  // Convert weight fractions to atom fractions
  if( d_atoms.front().first < 0.0 )
  {
    convertWeightFractionsToAtomFractions<Utility::FIRST,Utility::SECOND>(
				     d_atoms.begin(),
                                     d_atoms.end(),
                                     d_atoms.begin(),
                                     d_atoms.end(),
				     &AdjointPhotonMaterial::getAtomicWeight );
  }
  else // Normalize the atom fractions
  {
    normalizeFractionValues<Utility::FIRST>( d_atoms.begin(), d_atoms.end() );
  }

  // Convert the mass density to a number density
  if( density < 0.0 )
  {
    d_number_density =
      convertMassDensityToNumberDensity<Utility::FIRST,Utility::SECOND>(
				     -1.0*density,
                                     d_atoms.begin(),
                                     d_atoms.end(),
                                     d_atoms.begin(),
                                     d_atoms.end(),
				     &AdjointPhotonMaterial::getAtomicWeight );
  }

  // Convert the atom fractions to isotopic number densities
  scaleAtomFractionsByNumberDensity<Utility::FIRST>( d_number_density,
						     d_atoms.begin(),
						     d_atoms.end() );
}

// Return the material id
ModuleTraits::InternalMaterialHandle AdjointPhotonMaterial::getId() const
{
  return d_id;
}

// Return the number density (atom/b-cm)
double AdjointPhotonMaterial::getNumberDensity() const
{
  return d_number_density;
}

// Check if the energy corresponds to a line energy reaction
bool AdjointPhotonMaterial::doesEnergyHaveLineEnergyReaction(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  bool has_line_energy_reaction = false;

  for( size_t i = 0; i < d_atoms.size(); ++i )
  {
    if( d_atoms[i].second->doesEnergyHaveLineEnergyReaction( energy ) )
    {
      has_line_energy_reaction = true;

      break;
    }
  }

  return has_line_energy_reaction;
}

// Return the macroscopic total cross section (1/cm)
double AdjointPhotonMaterial::getMacroscopicTotalCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( size_t i = 0; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getTotalCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic total cs at the desired line energy (1/cm)
double AdjointPhotonMaterial::getMacroscopicTotalLineEnergyCrossSection(
                                                     const double energy) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( size_t i = 0; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getTotalLineEnergyCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic total forward cross section (1/cm)
double AdjointPhotonMaterial::getMacroscopicTotalForwardCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( size_t i = 0; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getTotalForwardCrossSection( energy );
  }

  return cross_section;
}

// Return the macroscopic absorption cross section (1/cm)
double AdjointPhotonMaterial::getMacroscopicAbsorptionCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( size_t i = 0; i < d_atoms.size(); ++i )
  {
    cross_section +=
      d_atoms[i].first*d_atoms[i].second->getAbsorptionCrossSection( energy );
  }

  return cross_section;
}

// Return the adjoint weight factor
double AdjointPhotonMaterial::getAdjointWeightFactor(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;

  double macroscopic_total_forward_cross_section =
    this->getMacroscopicTotalForwardCrossSection( energy );

  if( macroscopic_total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getMacroscopicTotalCrossSection( energy )/
      this->getMacroscopicTotalForwardCrossSection( energy );
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPrecondition( weight_factor > 0.0 );

  return weight_factor;
}

// Return the adjoint line energy weight factor
double AdjointPhotonMaterial::getAdjointLineEnergyWeightFactor(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;

  double macroscopic_total_forward_cross_section =
    this->getMacroscopicTotalForwardCrossSection( energy );

  if( macroscopic_total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getMacroscopicTotalLineEnergyCrossSection( energy )/
      this->getMacroscopicTotalForwardCrossSection( energy );
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPostcondition( weight_factor >= 0.0 );

  return weight_factor;
}

// Return the survival probability
double AdjointPhotonMaterial::getSurvivalProbability( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;

  double total_cross_section =
    this->getMacroscopicTotalCrossSection( energy );

  // Find the energy bin index
  if( total_cross_section > 0.0 )
  {
    survival_prob = 1.0 -
      this->getMacroscopicAbsorptionCrossSection( energy )/total_cross_section;
  }
  else
    survival_prob = 1.0;
  
  // Make sure the survival probability is valid
  testPostcondition( !ST::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Return the macroscopic cross section (1/cm) for a specific reaction
double AdjointPhotonMaterial::getMacroscopicReactionCrossSection(
                          const double energy,
                          const AdjointPhotoatomicReactionType reaction ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    cross_section += d_atoms[i].first*
      d_atoms[i].second->getReactionCrossSection( energy, reaction );
  }

  return cross_section;
}

// Collide with an adjoint photon
void AdjointPhotonMaterial::collideAnalogue(
                                            AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  unsigned atom_index =
    this->sampleCollisionAtom( adjoint_photon.getEnergy() );

  d_atoms[atom_index].second->collideAnalogue( adjoint_photon, bank );
}

// Collide with an adjoint photon and survival bias
void AdjointPhotonMaterial::collideSurvivalBias(
                                            AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  unsigned atom_index =
    this->sampleCollisionAtom( adjoint_photon.getEnergy() );

  d_atoms[atom_index].second->collideSurvivalBias( adjoint_photon, bank );
}

// Collide with an adjoint photon at a line energy
void AdjointPhotonMaterial::collideAtLineEnergy(
                                            AdjointPhotonState& adjoint_photon,
                                            ParticleBank& bank ) const
{
  // Make sure the particle is a probe
  testPrecondition( adjoint_photon.isProbe() );
  // Make sure there are line energy reactions at the particle's energy
  testPrecondition( this->doesEnergyHaveLineEnergyReaction( adjoint_photon.getEnergy() ) );
  
  unsigned atom_index =
    this->sampleCollisionAtomAtLineEnergy( adjoint_photon.getEnergy() );

  d_atoms[atom_index].second->collideAtLineEnergy( adjoint_photon, bank );
}

// Get the atomic weight from an atom pointer
double AdjointPhotonMaterial::getAtomicWeight(
      const Utility::Pair<double,Teuchos::RCP<const AdjointPhotoatom> >& pair )
{
  return pair.second->getAtomicWeight();
}

// Sample the atom that is collided with
unsigned AdjointPhotonMaterial::sampleCollisionAtom(
                                                    const double energy ) const
{
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    this->getMacroscopicTotalCrossSection( energy );

  double partial_total_cs = 0.0;

  unsigned collision_atom_index = std::numeric_limits<unsigned>::max();

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    partial_total_cs +=
      d_atoms[i].first*d_atoms[i].second->getTotalCrossSection( energy );

    if( scaled_random_number < partial_total_cs )
    {
      collision_atom_index = i;

      break;
    }
  }

  // Make sure a collision index was found
  testPostcondition( collision_atom_index !=
                     std::numeric_limits<unsigned>::max() );

  return collision_atom_index;
}

// Sample the atom that is collided with at a line energy
unsigned AdjointPhotonMaterial::sampleCollisionAtomAtLineEnergy(
                                                    const double energy ) const
{
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    this->getMacroscopicTotalLineEnergyCrossSection( energy );

  double partial_total_cs = 0.0;

  unsigned collision_atom_index = std::numeric_limits<unsigned>::max();

  for( unsigned i = 0u; i < d_atoms.size(); ++i )
  {
    partial_total_cs +=
      d_atoms[i].first*d_atoms[i].second->getTotalLineEnergyCrossSection( energy );

    if( scaled_random_number < partial_total_cs )
    {
      collision_atom_index = i;

      break;
    }
  }

  // Make sure a collision index was found
  testPostcondition( collision_atom_index !=
                     std::numeric_limits<unsigned>::max() );

  return collision_atom_index;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonMaterial.cpp
//---------------------------------------------------------------------------//
