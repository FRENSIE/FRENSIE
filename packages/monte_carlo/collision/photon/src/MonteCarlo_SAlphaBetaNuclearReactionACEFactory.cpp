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
#include "Utility_DesignByContract.hpp"
#include "MonteCarlo_NeutronScatteringReaction.hpp"

namespace MonteCarlo{

// Constructor
SAlphaBetaNuclearReactionACEFactory::SAlphaBetaNuclearReactionACEFactory( 
	 const std::string& table_name,
	 const double atomic_weight_ratio,
	 const double temperature,
	 const std::shared_ptr<const std::vector<double> >& energy_grid,
	 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
	 const Data::XSSSabDataExtractor& sab_nuclide_data,
   const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
   grid_searcher,
   const SimulationProperties& properties  ) :
	   NeutronNuclearReactionACEFactory( table_name,
	                              atomic_weight_ratio,
	                              temperature,
	                              energy_grid,
                                grid_searcher,
                                properties,
	                              raw_nuclide_data )
{
  // Create the scattering distribution factory
  SAlphaBetaNuclearScatteringDistributionACEFactory 
    scattering_dist_factory( table_name,
			                       atomic_weight_ratio,
			                       raw_nuclide_data,
			                       sab_nuclide_data );
	
  // Create a map of the reaction types and the corresponding cross section
  std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >
    reaction_cross_section;
  setSAlphaBetaCrossSectionMap( sab_nuclide_data,
                                reaction_cross_section );
	
	// Create a map of the reaction types and the upper energy limits
	std::unordered_map<NuclearReactionType, double> upper_energy_limits;
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
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
  sab_reactions ) const
{
  sab_reactions.insert( d_s_alpha_beta_reactions.begin(),
			       d_s_alpha_beta_reactions.end() );
}

// Update the reaction threshold map with the new reactions
void SAlphaBetaNuclearReactionACEFactory::setSAlphaBetaCrossSectionMap( 
  const Data::XSSSabDataExtractor& sab_nuclide_data,
  std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
    reaction_cross_section )
{
  // Inelastic cross-section
  NuclearReactionType reaction_type = convertMTNumberToNuclearReactionType( 1004u );
  reaction_cross_section[reaction_type] = 
    sab_nuclide_data.extractInelasticCrossSection();
  
  // Elastic cross-section
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    reaction_cross_section[convertMTNumberToNuclearReactionType( 1002u )] = 
      sab_nuclide_data.extractElasticCrossSection();
  }
}

// Update the reaction upper threshold index map
void SAlphaBetaNuclearReactionACEFactory::setSAlphaBetaUpperEnergyLimitMap( 
       const Data::XSSSabDataExtractor& sab_nuclide_data,
       std::unordered_map<NuclearReactionType, double>& upper_energy_limits )
{
  // Inelastic upper energy limit
  upper_energy_limits[convertMTNumberToNuclearReactionType( 1004u )] =
    sab_nuclide_data.extractInelasticEnergyGrid().back();
    
  // Elastic upper energy limit
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    upper_energy_limits[convertMTNumberToNuclearReactionType( 1002u )] =
      sab_nuclide_data.extractElasticEnergyGrid().back();
  }
}

// Initialize the S(alpha,beta) reactions
void SAlphaBetaNuclearReactionACEFactory::initializeSAlphaBetaReactions(  
    const double temperature,
    const Data::XSSSabDataExtractor& sab_nuclide_data,
    std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
      reaction_cross_section,
    const SAlphaBetaNuclearScatteringDistributionACEFactory& 
      scattering_dist_factory )
{
  // Create the S(alpha,beta) reactions
  std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >::const_iterator
    reaction_xs, reaction_xs_end;

  reaction_xs = reaction_cross_section.begin();
  reaction_xs_end = reaction_cross_section.end();

  NuclearReactionType reaction_type;

  std::shared_ptr<NuclearScatteringDistribution<NeutronState,NeutronState> > 
    scattering_distribution;
    
  std::unordered_map<NuclearReactionType,std::vector<double> >
      reaction_cross_section_arrays;
      
  // Append the S(alpha,beta) data with the threshold data point from the
  //   standard reaction and update the standard reaction data
  while( reaction_xs != reaction_xs_end )
  {
    reaction_type = reaction_xs->first;
  
    reaction_cross_section_arrays[reaction_type] = reaction_cross_section[reaction_type];
    
    std::vector<double> sab_energy_grid_array;
    std::shared_ptr<std::vector<double> > energy_grid;


    // Add the S(alpha,beta) cutoff energy to the elastic scattering reaction:
    if( reaction_type == MonteCarlo::SALPHABETA_N__N_INELASTIC_REACTION ||
        reaction_type == MonteCarlo::SALPHABETA_N__N_ELASTIC_REACTION )
    {
      Utility::ArrayView<const double> sab_energy_grid;
      std::vector<double> sab_energy_grid_array;
      
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
        std::dynamic_pointer_cast<MonteCarlo::NeutronScatteringReaction>(d_scattering_reactions[parent_reaction_type])->setSABCutoffEnergy(sab_cutoff_energy);
      }

       std::vector<double> internal_grid( sab_energy_grid);

      internal_grid.push_back( sab_cutoff_energy + 1.0e-9 );
      reaction_cross_section_arrays[reaction_type].push_back( 0.0 );

      energy_grid.reset( new std::vector<double> (internal_grid) );
    }
    
    // Construct the reactions
    reaction_type = reaction_xs->first;
    
    std::shared_ptr<NeutronNuclearReaction>& reaction = d_s_alpha_beta_reactions[reaction_type];
      
    scattering_dist_factory.createSAlphaBetaScatteringDistributions(
      reaction_type,
      scattering_distribution );
    
    std::shared_ptr<std::vector<double> > cross_section( new std::vector<double>(reaction_cross_section_arrays[reaction_type]) );
    NeutronScatteringReaction* neutron_scattering_update = new NeutronScatteringReaction(
            energy_grid, cross_section, 0u, reaction_type, 0.0, temperature, 1u,
            scattering_distribution);
    NeutronNuclearReaction* test= (NeutronNuclearReaction*)neutron_scattering_update;

    reaction.reset( test);
    
    ++reaction_xs;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
