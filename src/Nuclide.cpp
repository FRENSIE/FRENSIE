//---------------------------------------------------------------------------//
//!
//! \file   Nuclide.cpp
//! \author Alex Robinson
//! \brief  The nuclide class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <stdexcept>

// FACEMC Includes
#include "Nuclide.hpp"
#include "NuclearReactionFactory.hpp"
#include "RandomNumberGenerator.hpp"
#include "SearchAlgorithms.hpp"
#include "InterpolationPolicy.hpp"
#include "ExceptionTestMacros.hpp"

namespace FACEMC{

// Initialize the static member data
boost::unordered_set<NuclearReactionType> Nuclide::absorption_reaction_types =
  Nuclide::setDefaultAbsorptionReactionTypes();

// Set the default absorption reaction types
boost::unordered_set<NuclearReactionType> 
Nuclide::setDefaultAbsorptionReactionTypes()
{
  boost::unordered_set<NuclearReactionType> absorption_reaction_type;
  absorption_reaction_type.insert( N__CAPTURE_REACTION );
  absorption_reaction_type.insert( N__GAMMA_REACTION ); // start capture
  absorption_reaction_type.insert( N__P_REACTION );
  absorption_reaction_type.insert( N__D_REACTION );
  absorption_reaction_type.insert( N__T_REACTION );
  absorption_reaction_type.insert( N__HE3_REACTION );
  absorption_reaction_type.insert( N__ALPHA_REACTION );
  absorption_reaction_type.insert( N__2ALPHA_REACTION );
  absorption_reaction_type.insert( N__3ALPHA_REACTION );
  absorption_reaction_type.insert( N__2P_REACTION );
  absorption_reaction_type.insert( N__P_ALPHA_REACTION );
  absorption_reaction_type.insert( N__T_2ALPHA_REACTION );
  absorption_reaction_type.insert( N__D_2ALPHA_REACTION );
  absorption_reaction_type.insert( N__P_D_REACTION );
  absorption_reaction_type.insert( N__P_T_REACTION );
  absorption_reaction_type.insert( N__D_ALPHA_REACTION ); // end capture

  return absorption_reaction_type;
}

// Set the nuclear reaction types that will be considered as absorption
void Nuclide::setAbsorptionReactionTypes( 
	 const Teuchos::Array<NuclearReactionType>& absorption_reaction_types )
{
  Nuclide::absorption_reaction_types.clear();
  
  Nuclide::absorption_reaction_types.insert( absorption_reaction_types.begin(),
					     absorption_reaction_types.end() );
}

// Add nuclear reaction types that will be considered as absorption
void Nuclide::addAbsorptionReactionTypes( 
	 const Teuchos::Array<NuclearReactionType>& absorption_reaction_types )
{
  for( unsigned i = 0; i < absorption_reaction_types.size(); ++i )
    Nuclide::absorption_reaction_types.insert( absorption_reaction_types[i] );
}

// Constructor
Nuclide::Nuclide( const std::string& name,
		  const unsigned atomic_number,
		  const unsigned atomic_mass_number,
		  const unsigned isomer_number,
		  const double atomic_weight_ratio,
		  const double temperature,
		  const XSSNeutronDataExtractor& raw_nuclide_data )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_mass_number( atomic_mass_number ),
    d_isomer_number( isomer_number ),
    d_atomic_weight_ratio( atomic_weight_ratio ),
    d_temperature( temperature ),
    d_energy_grid(),
    d_total_cross_section( raw_nuclide_data.extractEnergyGrid().size() ),
    d_absorption_cross_section( raw_nuclide_data.extractEnergyGrid().size() )
{
  // Create a deep copy of the energy grid
  d_energy_grid.deepCopy( raw_nuclide_data.extractEnergyGrid() );

  // Create the nuclear reaction factory
  NuclearReactionFactory reaction_factory( 
				 d_name,
				 d_atomic_weight_ratio,
				 d_temperature,
				 d_energy_grid.getConst(),
				 raw_nuclide_data.extractElasticCrossSection(),
				 raw_nuclide_data.extractMTRBlock(),
				 raw_nuclide_data.extractLQRBlock(),
				 raw_nuclide_data.extractTYRBlock(),
				 raw_nuclide_data.extractLSIGBlock(),
				 raw_nuclide_data.extractSIGBlock(),
				 raw_nuclide_data.extractLANDBlock(),
				 raw_nuclide_data.extractANDBlock(),
				 raw_nuclide_data.extractLDLWBlock(),
				 raw_nuclide_data.extractDLWBlock() );

  // Create the standard scattering reactions
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >
    standard_scattering_reactions;
  reaction_factory.createScatteringReactions( standard_scattering_reactions );
  reaction_factory.createFissionReactions( standard_scattering_reactions );

  // Create the standard absorption reactions
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >
    standard_absorption_reactions;
  reaction_factory.createAbsorptionReactions( standard_absorption_reactions );
  
  // Place the reactions in the appropriate group
  boost::unordered_map<NuclearReactionType,
		       Teuchos::RCP<NuclearReaction> >::const_iterator
    reaction_type_pointer, end_reaction_type_pointer;

  reaction_type_pointer = standard_scattering_reactions.begin();
  end_reaction_type_pointer = standard_scattering_reactions.end();

  while( reaction_type_pointer != end_reaction_type_pointer )
  {
    if(Nuclide::absorption_reaction_types.count(reaction_type_pointer->first))
      d_absorption_reactions.insert( *reaction_type_pointer );
    else
      d_scattering_reactions.insert( *reaction_type_pointer );

    ++reaction_type_pointer;
  }

  reaction_type_pointer = standard_absorption_reactions.begin();
  end_reaction_type_pointer = standard_absorption_reactions.end();

  while( reaction_type_pointer != end_reaction_type_pointer )
  {
    if(Nuclide::absorption_reaction_types.count(reaction_type_pointer->first))
      d_absorption_reactions.insert( *reaction_type_pointer );
    else
      d_miscellaneous_reactions.insert( *reaction_type_pointer );

    ++reaction_type_pointer;
  }

  // Calculate the total absorption cross section
  calculateTotalAbsorptionCrossSection();
  
  // Calculate the total cross section
  calculateTotalCrossSection();

  // Make sure the calculated total cross section is valid
  testPostcondition( isCalculatedTotalCrossSectionValid( 
			       d_total_cross_section,
			       raw_nuclide_data.extractTotalCrossSection() ) );
}

// Return the nuclide name
const std::string& Nuclide::getName() const
{
  return d_name;
}

// Return the atomic number of the nuclide
unsigned Nuclide::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the atomic mass number of the nuclide
unsigned Nuclide::getAtomicMassNumber() const
{
  return d_atomic_mass_number;
}

// Return the nuclear isomer number of the nuclide
unsigned Nuclide::getIsomerNumber() const
{
  return d_isomer_number;
}
  
// Return the atomic weight ratio
double Nuclide::getAtomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Return the temperature of the nuclide (in MeV)
double Nuclide::getTemperature() const
{
  return d_temperature;
}
  
// Return the total cross section at the desired energy
double Nuclide::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  if( energy < d_energy_grid[d_energy_grid.size()-1] )
  {
    unsigned lower_bin_index =
      Search::binaryLowerBoundIndex( d_energy_grid.begin(), 
				     d_energy_grid.end(),
				     energy );

    return LinLin::interpolate( d_energy_grid[lower_bin_index],
				d_energy_grid[lower_bin_index+1],
				energy,
				d_total_cross_section[lower_bin_index],
				d_total_cross_section[lower_bin_index+1] );
  }
  else if( energy == d_energy_grid[d_energy_grid.size()-1] )
    return d_total_cross_section.back();
  else // energy > d_energy_grid[d_energy_grid.size()-1]
    return 0.0;
}

// Return the total absorption cross section at the desired energy
double Nuclide::getAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  if( energy < d_energy_grid[d_energy_grid.size()-1] )
  {
    unsigned lower_bin_index =
      Search::binaryLowerBoundIndex( d_energy_grid.begin(), 
				     d_energy_grid.end(),
				     energy );

    return LinLin::interpolate( d_energy_grid[lower_bin_index],
				d_energy_grid[lower_bin_index+1],
				energy,
				d_absorption_cross_section[lower_bin_index],
				d_absorption_cross_section[lower_bin_index+1]);
  }
  else if( energy == d_energy_grid[d_energy_grid.size()-1] )
    return d_absorption_cross_section.back();
  else // energy > d_energy_grid[d_energy_grid.size()-1]
    return 0.0;
}
 
// Return the survival probability at the desired energy
double Nuclide::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  double survival_prob = 1.0 - this->getAbsorptionCrossSection( energy )/
    this->getTotalCrossSection( energy );

  // Make sure the survival probability is valid
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );
  
  return survival_prob;
}

// Return the cross section for a specific nuclear reaction
double Nuclide::getReactionCrossSection( 
				     const double energy,
				     const NuclearReactionType reaction ) const
{
  switch( reaction )
  {
  case N__TOTAL_REACTION:
    return getTotalCrossSection( energy );
  default:
    boost::unordered_map<NuclearReactionType,
			 Teuchos::RCP<NuclearReaction> >::const_iterator
      nuclear_reaction;
    
    nuclear_reaction = d_scattering_reactions.find( reaction );
    
    if( nuclear_reaction != d_scattering_reactions.end() )
      return nuclear_reaction->second->getCrossSection( energy );
    
    nuclear_reaction = d_absorption_reactions.find( reaction );

    if( nuclear_reaction != d_absorption_reactions.end() )
      return nuclear_reaction->second->getCrossSection( energy );
    
    nuclear_reaction = d_miscellaneous_reactions.find( reaction );

    if( nuclear_reaction != d_miscellaneous_reactions.end() )
      return nuclear_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for the nuclide, return 0
      return 0.0;
  }
}
  
// Collide with a neutron
void Nuclide::collideAnalogue( NeutronState& neutron, 
			       ParticleBank& bank ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  double total_cross_section = 
    this->getTotalCrossSection( neutron.getEnergy() );

  double absorption_cross_section = 
    this->getAbsorptionCrossSection( neutron.getEnergy() );

  // Check if absorption occurs
  if( random_number*total_cross_section < absorption_cross_section )
  {
    sampleAbsorptionReaction( random_number*absorption_cross_section, 
			      neutron, 
			      bank );
    // Set the neutron as gone regardless of the reaction that occured.
    neutron.setAsGone(); 
  }
  else
  {
    sampleScatteringReaction( random_number*(total_cross_section - 
					     absorption_cross_section), 
			      neutron, 
			      bank );
  }
}

// Collide with a neutron and survival bias
void Nuclide::collideSurvivalBias( NeutronState& neutron, 
				   ParticleBank& bank) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  double total_cross_section = 
    this->getTotalCrossSection( neutron.getEnergy() );

  double scattering_cross_section = total_cross_section - 
    this->getAbsorptionCrossSection( neutron.getEnergy() );

  double survival_prob = scattering_cross_section/total_cross_section;
  
  // Multiply the neutrons weight by the survival probability
  if( survival_prob > 0.0 )
  {
    neutron.multiplyWeight( scattering_cross_section/total_cross_section );

    sampleScatteringReaction( random_number*scattering_cross_section,
			    neutron,
			    bank );
  }
  else
    neutron.setAsGone();
}

// Calculate the total absorption cross section
void Nuclide::calculateTotalAbsorptionCrossSection()
{
  // Make sure the absorption cross section is sized correctly
  testPrecondition( d_absorption_cross_section.size() == d_energy_grid.size());
  
  boost::unordered_map<NuclearReactionType,
		       Teuchos::RCP<NuclearReaction> >::const_iterator
    reaction_type_pointer, end_reaction_type_pointer;

  end_reaction_type_pointer = d_absorption_reactions.end();
  
  for( unsigned i = 0; i < d_absorption_cross_section.size(); ++i )
  {
    d_absorption_cross_section[i] = 0.0; 
      
    reaction_type_pointer = d_absorption_reactions.begin();

    while( reaction_type_pointer != end_reaction_type_pointer )
    {
      d_absorption_cross_section[i] += 
	reaction_type_pointer->second->getCrossSection( d_energy_grid[i] );

      ++reaction_type_pointer;
    }
  }
}

// Calculate the total cross section
void Nuclide::calculateTotalCrossSection()
{
  // Make sure the total cross section is sized correctly
  testPrecondition( d_total_cross_section.size() == d_energy_grid.size() );

  boost::unordered_map<NuclearReactionType,
		       Teuchos::RCP<NuclearReaction> >::const_iterator
    reaction_type_pointer, end_reaction_type_pointer;

  end_reaction_type_pointer = d_scattering_reactions.end();
  
  for( unsigned i = 0; i < d_total_cross_section.size(); ++i )
  {
    d_total_cross_section[i] = d_absorption_cross_section[i]; 
      
    reaction_type_pointer = d_scattering_reactions.begin();

    while( reaction_type_pointer != end_reaction_type_pointer )
    {
      d_total_cross_section[i] += 
	reaction_type_pointer->second->getCrossSection( d_energy_grid[i] );

      ++reaction_type_pointer;
    }
  }
}

// Check that the total cross section is valid
bool Nuclide::isCalculatedTotalCrossSectionValid(
                   Teuchos::Array<double>& calculated_total_cross_section,
	           Teuchos::ArrayView<const double> table_total_cross_section )
{
  if( calculated_total_cross_section.size() !=
      table_total_cross_section.size() )
    return false;
  
  bool valid = true;
  double rel_error;
  for( unsigned i = 0u; i < calculated_total_cross_section.size(); ++i )
  {
    rel_error = ST::magnitude( calculated_total_cross_section[i] - 
			       table_total_cross_section[i] )/
      std::max( ST::magnitude( calculated_total_cross_section[i] ),
		ST::magnitude( table_total_cross_section[i] ) );
    
    if( rel_error > 5e-9 )
    {
      valid = false;
      std::cout << i << ": " << rel_error << std::endl;
    }
  }

  return valid;
}

// Sample a scattering reaction
// NOTE: The scaled random number must be a random number multiplied by the
//       total scattering cross section
void Nuclide::sampleScatteringReaction( const double scaled_random_number,
					NeutronState& neutron,
					ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;
    
    boost::unordered_map<NuclearReactionType,
			 Teuchos::RCP<NuclearReaction> >::const_iterator
      nuclear_reaction, nuclear_reaction_end;
    
    nuclear_reaction = d_scattering_reactions.begin();
    nuclear_reaction_end = d_scattering_reactions.end();
    
    while( nuclear_reaction != nuclear_reaction_end )
    {
      partial_cross_section += 
	nuclear_reaction->second->getCrossSection( neutron.getEnergy() );

      if( scaled_random_number < partial_cross_section )
	break;
      
      ++nuclear_reaction;
    }

    TEST_FOR_EXCEPTION( nuclear_reaction == nuclear_reaction_end,
			std::runtime_error,
			"The nuclear reaction type could not be sampled." );

    nuclear_reaction->second->react( neutron, bank );
}

// Sample an absorption reaction
// NOTE: The scaled random number must be a random number multiplied by the
//       total absorption cross section
void Nuclide::sampleAbsorptionReaction( const double scaled_random_number,
					NeutronState& neutron,
					ParticleBank& bank ) const
{
  double partial_cross_section = 0.0;
    
    boost::unordered_map<NuclearReactionType,
			 Teuchos::RCP<NuclearReaction> >::const_iterator
      nuclear_reaction, nuclear_reaction_end;
    
    nuclear_reaction = d_absorption_reactions.begin();
    nuclear_reaction_end = d_absorption_reactions.end();
    
    while( nuclear_reaction != nuclear_reaction_end )
    {
      partial_cross_section += 
	nuclear_reaction->second->getCrossSection( neutron.getEnergy() );

      if( scaled_random_number < partial_cross_section )
	break;
      
      ++nuclear_reaction;
    }

    TEST_FOR_EXCEPTION( nuclear_reaction == nuclear_reaction_end,
			std::runtime_error,
			"The nuclear reaction type could not be sampled." );

    nuclear_reaction->second->react( neutron, bank );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end Nuclide.cpp
//---------------------------------------------------------------------------//
