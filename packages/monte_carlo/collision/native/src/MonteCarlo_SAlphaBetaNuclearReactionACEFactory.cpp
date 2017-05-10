//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclearReactionACEFactory.cpp
//! \author Eli Moll
//! \brief  S(alpha,beta) nuclear reaction factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SAlphaBetaNuclearReactionACEFactory.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_NeutronScatteringReaction.hpp"

namespace MonteCarlo{

// Constructor
SAlphaBetaNuclearReactionACEFactory::SAlphaBetaNuclearReactionACEFactory( 
	 const std::string& table_name,
	 const double atomic_weight_ratio,
	 const double temperature,
	 const Teuchos::ArrayRCP<const double>& energy_grid,
	 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
	 const Data::XSSSabDataExtractor& sab_nuclide_data ) :
	   NuclearReactionACEFactory( table_name,
	                              atomic_weight_ratio,
	                              temperature,
	                              energy_grid,
	                              raw_nuclide_data )
{
  // Create the scattering distribution factory
  SAlphaBetaNuclearScatteringDistributionACEFactory 
    scattering_dist_factory( table_name,
			                       atomic_weight_ratio,
			                       raw_nuclide_data,
			                       sab_nuclide_data );
	
  // Create a map of the reaction types and the corresponding cross section
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
    reaction_cross_section;
  setSAlphaBetaCrossSectionMap( sab_nuclide_data,
                                reaction_cross_section );
	
	// Create a map of the reaction types and the upper energy limits
	boost::unordered_map<NuclearReactionType, double> upper_energy_limits;
	setSAlphaBetaUpperEnergyLimitMap( sab_nuclide_data,
	                                  upper_energy_limits );

	// Initialize the S(alpha,beta) reactions
	initializeSAlphaBetaReactions( temperature,
	                               sab_nuclide_data,
	                               reaction_cross_section,
	                               scattering_dist_factory );
}

// Create the S(alpha,beta) reactions
void SAlphaBetaNuclearReactionACEFactory::createSAlphaBetaReactions(
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
  sab_reactions ) const
{
  sab_reactions.insert( d_s_alpha_beta_reactions.begin(),
			       d_s_alpha_beta_reactions.end() );
}

// Update the reaction threshold map with the new reactions
void SAlphaBetaNuclearReactionACEFactory::setSAlphaBetaCrossSectionMap( 
  const Data::XSSSabDataExtractor& sab_nuclide_data,
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
    reaction_cross_section )
{
  // Inelastic cross-section
  NuclearReactionType reaction_type = convertUnsignedToNuclearReactionType( 1004u );
  reaction_cross_section[reaction_type] = 
    sab_nuclide_data.extractInelasticCrossSection();
  
  // Elastic cross-section
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    reaction_cross_section[convertUnsignedToNuclearReactionType( 1002u )] = 
      sab_nuclide_data.extractElasticCrossSection();
  }
}

// Update the reaction upper threshold index map
void SAlphaBetaNuclearReactionACEFactory::setSAlphaBetaUpperEnergyLimitMap( 
       const Data::XSSSabDataExtractor& sab_nuclide_data,
       boost::unordered_map<NuclearReactionType, double>& upper_energy_limits )
{
  // Inelastic upper energy limit
  upper_energy_limits[convertUnsignedToNuclearReactionType( 1004u )] =
    sab_nuclide_data.extractInelasticEnergyGrid().back();
    
  // Elastic upper energy limit
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    upper_energy_limits[convertUnsignedToNuclearReactionType( 1002u )] =
      sab_nuclide_data.extractElasticEnergyGrid().back();
  }
}

// Initialize the S(alpha,beta) reactions
void SAlphaBetaNuclearReactionACEFactory::initializeSAlphaBetaReactions(  
    const double temperature,
    const Data::XSSSabDataExtractor& sab_nuclide_data,
    boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
      reaction_cross_section,
    const SAlphaBetaNuclearScatteringDistributionACEFactory& 
      scattering_dist_factory )
{
  // Create the S(alpha,beta) reactions
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >::const_iterator
    reaction_xs, reaction_xs_end;

  reaction_xs = reaction_cross_section.begin();
  reaction_xs_end = reaction_cross_section.end();

  NuclearReactionType reaction_type;

  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > 
    scattering_distribution;
    
  boost::unordered_map<NuclearReactionType,Teuchos::Array<double> >
      reaction_cross_section_arrays;
      
  

 
  // Append the S(alpha,beta) data with the threshold data point from the
  //   standard reaction and update the standard reaction data
  while( reaction_xs != reaction_xs_end )
  {
    reaction_type = reaction_xs->first;
  
    reaction_cross_section_arrays[reaction_type] = reaction_cross_section[reaction_type];
    
    Teuchos::Array<double> sab_energy_grid_array;
    Teuchos::ArrayRCP<double> energy_grid;

    /*  
    if( reaction_type == MonteCarlo::SALPHABETA_N__N_INELASTIC_REACTION ||
        reaction_type == MonteCarlo::SALPHABETA_N__N_ELASTIC_REACTION )
    {
      unsigned index;
      double energy;
      double energy_xs;
      
      Teuchos::ArrayView<const double> sab_energy_grid;
      Teuchos::Array<double> sab_energy_grid_array;
      
      NuclearReactionType parent_reaction_type;
      
      // It appears that every reaction for S(alpha,beta) actually takes the
      //  place of the elastic neutron/neutron scattering reaction. This does
      //  not correspond to their naming structure of elastic and inelastic.
      //  That is to say, all S(alpha,beta) reactions have the standard
      //  (n,n) elastic reaction as their parent...
      
      if( reaction_type == MonteCarlo::SALPHABETA_N__N_INELASTIC_REACTION )
      {
        parent_reaction_type = MonteCarlo::N__N_ELASTIC_REACTION;
        sab_energy_grid = sab_nuclide_data.extractInelasticEnergyGrid();
      }
      else
      {
        parent_reaction_type = MonteCarlo::N__N_ELASTIC_REACTION;
        sab_energy_grid = sab_nuclide_data.extractElasticEnergyGrid();
      }
      
      index = Utility::Search::binaryUpperBoundIndex( d_energy_grid.begin(),
                                                      d_energy_grid.end(),
                                                      sab_energy_grid.back() );
                                                                                                  
      Teuchos::Array<double> internal_grid( sab_energy_grid );
    
      if( d_scattering_reactions.find(parent_reaction_type) != d_scattering_reactions.end() )
      {
        d_scattering_reactions[parent_reaction_type]->updateThresholdEnergyIndex( index );
        energy = d_energy_grid[index];
        energy_xs = 
          d_scattering_reactions[parent_reaction_type]->getCrossSection( energy );
      
        internal_grid.push_back( energy );
        reaction_cross_section_arrays[reaction_type].push_back( energy_xs );
      }
      
      sab_energy_grid_array = internal_grid;
      energy_grid.deepCopy( sab_energy_grid_array );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error, "Error: reaction type " << 
        reaction_type << " is not an acceptable S(a,b) reaction type." );
    }
    */

    // Add the S(alpha,beta) cutoff energy to the elastic scattering reaction:
    if( reaction_type == MonteCarlo::SALPHABETA_N__N_INELASTIC_REACTION ||
        reaction_type == MonteCarlo::SALPHABETA_N__N_ELASTIC_REACTION )
    {
      Teuchos::ArrayView<const double> sab_energy_grid;
      Teuchos::Array<double> sab_energy_grid_array;
      
      NuclearReactionType parent_reaction_type;

      if( reaction_type == MonteCarlo::SALPHABETA_N__N_INELASTIC_REACTION )
      {
        parent_reaction_type = MonteCarlo::N__N_ELASTIC_REACTION;
        sab_energy_grid = sab_nuclide_data.extractInelasticEnergyGrid();
      }
      else
      {
        parent_reaction_type = MonteCarlo::N__N_ELASTIC_REACTION;
        sab_energy_grid = sab_nuclide_data.extractElasticEnergyGrid();
      }

      double sab_cutoff_energy = sab_energy_grid.back();

      std::cout << "S(alpha,beta) Cutoff Energy in Factory: " << sab_cutoff_energy << std::endl;

      if( d_scattering_reactions.find(parent_reaction_type) != d_scattering_reactions.end() )
      {
        d_scattering_reactions[parent_reaction_type]->setSABCutoffEnergy( sab_cutoff_energy );
      }

      Teuchos::Array<double> internal_grid( sab_energy_grid );

      internal_grid.push_back( sab_cutoff_energy + 1.0e-9 );
      reaction_cross_section_arrays[reaction_type].push_back( 0.0 );

      energy_grid.deepCopy( internal_grid );
    }
    
    // Construct the reactions
    reaction_type = reaction_xs->first;
    
    Teuchos::RCP<NuclearReaction>& reaction =
      d_s_alpha_beta_reactions[reaction_type];
      
    scattering_dist_factory.createSAlphaBetaScatteringDistributions(
      reaction_type,
      scattering_distribution );
    
    Teuchos::ArrayRCP<double> cross_section;
    cross_section.deepCopy( reaction_cross_section_arrays[reaction_type] );
      
    reaction.reset( new NeutronScatteringReaction(
      reaction_type,
      temperature,
      0.0,
      1u,
      0u,
      energy_grid,
      cross_section,
      scattering_distribution ) );
    
    ++reaction_xs;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
