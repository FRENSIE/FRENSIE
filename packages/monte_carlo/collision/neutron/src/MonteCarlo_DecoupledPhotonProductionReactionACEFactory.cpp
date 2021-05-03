//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronNuclearReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.hpp"
#include "MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_InterpolationPolicy.hpp"

namespace MonteCarlo{

// Constructor
/*! \details All blocks from the ACE file will be stored.
 * \param[in] raw_nuclide_data The necessary data blocks will be extracted
 * using the data extractor.
 */
DecoupledPhotonProductionReactionACEFactory::DecoupledPhotonProductionReactionACEFactory(
          const std::string& table_name,
          const double atomic_weight_ratio,
          const double temperature,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const SimulationProperties& properties,
          const Data::XSSNeutronDataExtractor& raw_nuclide_data )
  : NeutronNuclearReactionACEFactory( table_name,
                                      atomic_weight_ratio,
                                      temperature,
                                      energy_grid,
                                      grid_searcher,
                                      properties,
                                      raw_nuclide_data )
{
  // Create the scattering distribution factory
  PhotonProductionNuclearScatteringDistributionACEFactory
    photon_production_dist_factory( table_name,
                                    atomic_weight_ratio,
                                    raw_nuclide_data );

  // Extract the required blocks
  Utility::ArrayView<const double> mtrp_block =
    raw_nuclide_data.extractMTRPBlock();
  Utility::ArrayView<const double> lsigp_block =
    raw_nuclide_data.extractLSIGPBlock();
  Utility::ArrayView<const double> sigp_block =
    raw_nuclide_data.extractSIGPBlock();

  // Create a map of the reaction types and their table ordering
  std::unordered_map<unsigned,unsigned> reaction_ordering;
  DecoupledPhotonProductionReactionACEFactory::createReactionOrderingMap(
                                                           mtrp_block,
                                                           reaction_ordering );

  // Parse the SIGP data and create the necessary data maps
  std::unordered_map<unsigned,Utility::ArrayView<const double> > yield_energy_map;
  std::unordered_map<unsigned,Utility::ArrayView<const double> > yield_values_map;
  std::unordered_map<unsigned,std::shared_ptr<std::vector<double> > > xs_based_map;
  std::unordered_map<unsigned,unsigned> threshold_energy_map;
  std::unordered_map<unsigned,NuclearReactionType> base_reaction_type_map;

  DecoupledPhotonProductionReactionACEFactory::parseSIGP(
                                                     table_name,
                                                     energy_grid->size(),
                                                     lsigp_block,
                                                     sigp_block,
                                                     reaction_ordering,
                                                     yield_energy_map,
                                                     yield_values_map,
                                                     xs_based_map,
                                                     threshold_energy_map,
                                                     base_reaction_type_map );

  // Construct a map of required base reaction classes
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> > base_reaction_map;

  DecoupledPhotonProductionReactionACEFactory::constructBaseReactionMap(
                                                    base_reaction_type_map,
                                                    base_reaction_map,
                                                    yield_energy_map );

  // Construct a map of photon MT numbers to yield distributions
  DecoupledPhotonProductionReactionACEFactory::constructMTPYieldDistributions(
                                                        yield_energy_map,
                                                        yield_values_map );

  // Construct a map of photon MT numbers to yield distributions
  DecoupledPhotonProductionReactionACEFactory::constructMTYieldArrays(
                                                      base_reaction_type_map,
                                                      yield_energy_map );

  // Construct the total neutron cross section
  DecoupledPhotonProductionReactionACEFactory::createTotalReaction(
                                   raw_nuclide_data.extractTotalCrossSection(),
                                   energy_grid,
                                   grid_searcher,
                                   temperature );

  // Create the yield based photon production reactions
  this->initializeYieldBasedPhotonProductionReactions(
                                              base_reaction_type_map,
                                              temperature,
                                              yield_energy_map,
                                              base_reaction_map,
                                              properties,
                                              photon_production_dist_factory );

  // Create the cross section based photon production reactions
  this->initializeCrossSectionBasedPhotonProductionReactions(
                                              base_reaction_type_map,
                                              temperature,
                                              threshold_energy_map,
                                              xs_based_map,
                                              energy_grid,
                                              grid_searcher,
                                              properties,
                                              photon_production_dist_factory );
}

// Create the photon production reactions
void DecoupledPhotonProductionReactionACEFactory::createPhotonProductionReactions(
      std::unordered_map<unsigned,std::shared_ptr<const DecoupledPhotonProductionReaction> >&
      photon_production_reactions ) const
{
  photon_production_reactions.insert( d_photon_production_reactions.begin(),
			       d_photon_production_reactions.end() );
}

// Create the total reaction for weight normalization
void DecoupledPhotonProductionReactionACEFactory::createTotalReaction(
          const Utility::ArrayView<const double>& total_xs_block,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const double temperature )
{
  std::shared_ptr<const std::vector<double> > total_cross_section(
                                   new std::vector<double>( total_xs_block ) );

  d_total_reaction.reset( new NeutronAbsorptionReaction( energy_grid,
                                                         total_cross_section,
                                                         0u,
                                                         grid_searcher,
                                                         N__TOTAL_REACTION,
                                                         0.0,
							 temperature ) );
}

// Create the reaction type ordering map
void DecoupledPhotonProductionReactionACEFactory::createReactionOrderingMap(
        const Utility::ArrayView<const double>& mtrp_block,
        std::unordered_map<unsigned,unsigned>& reaction_ordering )

{
  unsigned reaction;

  for( unsigned i = 0; i < mtrp_block.size(); ++i )
  {
    reaction = static_cast<unsigned>( mtrp_block[i] );

    reaction_ordering[reaction] = i;
  }
}

// Parse the SIGP to create the yield energy map, yield values, xs map, and
//   threshold energy map
void DecoupledPhotonProductionReactionACEFactory::parseSIGP(
  const std::string& table_name,
  const size_t energy_grid_size,
  const Utility::ArrayView<const double>& lsigp_block,
  const Utility::ArrayView<const double>& sigp_block,
  const std::unordered_map<unsigned,unsigned>& reaction_ordering,
  std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
  std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_values_map,
  std::unordered_map<unsigned,std::shared_ptr<std::vector<double> > >& xs_based_map,
  std::unordered_map<unsigned,unsigned>& threshold_energy_map,
  std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map )
{
  std::unordered_map<unsigned,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = reaction_ordering.begin();
  end_reaction = reaction_ordering.end();

  unsigned cs_index;
  unsigned cs_array_size;
  unsigned energy_array_size;

  while( reaction != end_reaction )
  {
    cs_index = static_cast<unsigned>( lsigp_block[reaction->second] ) - 1u;

    if ( static_cast<unsigned>( sigp_block[cs_index] ) == 13u )
    {
      threshold_energy_map[reaction->first] =
        static_cast<unsigned>( sigp_block[cs_index + 1u] );

      // Convert to C-style index
      if( threshold_energy_map[reaction->first] > 0u )
        --threshold_energy_map[reaction->first];

      cs_array_size = static_cast<unsigned>( sigp_block[cs_index + 2u] );

      FRENSIE_LOG_TAGGED_WARNING("DecoupledPhotonProductionReactionACEFactory",
                                 "SIGP reaction " << reaction->first <<
                                 " specifies a threshold energy index of "
                                 << threshold_energy_map[reaction->first] <<
                                 " and a cross section size of "
                                 << cs_array_size << ", which implies an "
                                 "energy grid of size "
                                 << threshold_energy_map[reaction->first] + cs_array_size <<
                                 ". The expected energy grid size is "
                                 << energy_grid_size << "!" << " While this "
                                 "is not expected to have an impact on a "
                                 "simulation, you may want to contact the "
                                 "data evaluators.");

      std::shared_ptr<std::vector<double> >& cross_section =
	                                    xs_based_map[reaction->first];

      cross_section.reset( new std::vector<double>(
                                sigp_block( cs_index + 3u, cs_array_size ) ) );

      base_reaction_type_map[reaction->first] =
        MonteCarlo::convertMTNumberToNuclearReactionType( reaction->first/1000u );
    }
    else if ( static_cast<unsigned>( sigp_block[cs_index] ) == 12u  ||
              static_cast<unsigned>( sigp_block[cs_index] ) == 16u )
    {
      TEST_FOR_EXCEPTION( static_cast<unsigned>( sigp_block[cs_index + 2u] ) != 0,
                          std::runtime_error,
                          "multiple interpolation regions were defined "
                          "in the ACE table for MT " << reaction->first <<
                          "." );

      energy_array_size =  static_cast<unsigned>( sigp_block[cs_index + 3u] );

      yield_energy_map[reaction->first] =
        sigp_block( cs_index + 4u, energy_array_size );

      yield_values_map[reaction->first] =
        sigp_block( cs_index + 4u + energy_array_size, energy_array_size );

      base_reaction_type_map[reaction->first] =
        MonteCarlo::convertMTNumberToNuclearReactionType( reaction->first/1000u );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "MFTYPE was found to be " <<
                       static_cast<unsigned>( sigp_block[cs_index + 2u] ) <<
                       " which is not equal to 12, 13, or 16 (only allowable"
                       " entries).");
    }
    ++reaction;
  }
}

// Create the base reaction map
void DecoupledPhotonProductionReactionACEFactory::constructBaseReactionMap(
  std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >& base_reaction_map,
  std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map )
{
  std::unordered_map<unsigned,Utility::ArrayView<const double> >::const_iterator
    reaction, end_reaction;
  reaction = yield_energy_map.begin();
  end_reaction = yield_energy_map.end();

  std::shared_ptr<NeutronNuclearReaction> base_reaction;

  while( reaction != end_reaction )
  {
    this->getReactionFromReactionType(
                          base_reaction_type_map.find(reaction->first)->second,
                          base_reaction );
    base_reaction_map[base_reaction_type_map.find(reaction->first)->second] =
                                                                 base_reaction;

    ++reaction;
  }
}

// Construct a map of photon MT numbers to yield distributions
void DecoupledPhotonProductionReactionACEFactory::constructMTPYieldDistributions(
	     const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
	     const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_values_map )
{
  std::unordered_map<unsigned,Utility::ArrayView<const double> >::const_iterator
    iter_reaction, end_reaction;
  iter_reaction = yield_energy_map.begin();
  end_reaction = yield_energy_map.end();

  while( iter_reaction != end_reaction )
  {
    unsigned reaction_type = iter_reaction->first;

    std::shared_ptr<Utility::UnivariateDistribution> tabular_yield_pointer(
        new Utility::TabularDistribution<Utility::LinLin>(
                              yield_energy_map.find(reaction_type)->second,
                              yield_values_map.find(reaction_type)->second ) );

    d_mtp_yield_distributions_map[reaction_type] = tabular_yield_pointer;

	  ++iter_reaction;
  }
}

// Construct a map of base reaction types to yield distribution arrays
void DecoupledPhotonProductionReactionACEFactory::constructMTYieldArrays(
       const std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
       const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map )
{
  std::unordered_map<unsigned,Utility::ArrayView<const double> >::const_iterator
    iter_reaction, end_reaction;
  iter_reaction = yield_energy_map.begin();
  end_reaction = yield_energy_map.end();

  while( iter_reaction != end_reaction )
  {
    unsigned reaction_type = iter_reaction->first;

    NuclearReactionType base_reaction_type =
                            base_reaction_type_map.find(reaction_type)->second;

    d_mt_yield_distributions[base_reaction_type].push_back(
                  d_mtp_yield_distributions_map.find(reaction_type)->second );

	  ++iter_reaction;
  }
}

// Initialize the yield based photon production reactions
void DecoupledPhotonProductionReactionACEFactory::initializeYieldBasedPhotonProductionReactions(
       const std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
       const double temperature,
       const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
       const std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >& base_reaction_map,
       const SimulationProperties& properties,
       PhotonProductionNuclearScatteringDistributionACEFactory& photon_production_dist_factory )
{
  std::unordered_map<unsigned,Utility::ArrayView<const double> >::const_iterator
    iter_reaction, end_reaction;
  iter_reaction = yield_energy_map.begin();
  end_reaction = yield_energy_map.end();

  std::shared_ptr<const NuclearScatteringDistribution<NeutronState,PhotonState> >
    photon_production_distribution;

  while( iter_reaction != end_reaction )
  {
    unsigned reaction_type = iter_reaction->first;

    std::shared_ptr<const DecoupledPhotonProductionReaction>& reaction =
                    d_photon_production_reactions[reaction_type];

    photon_production_dist_factory.createScatteringDistribution(
						     reaction_type,
                                                     properties,
						     photon_production_distribution );

    reaction.reset( new DecoupledYieldBasedPhotonProductionReaction(
		  base_reaction_type_map.find(reaction_type)->second,
		  reaction_type,
		  temperature,
		  d_mt_yield_distributions[base_reaction_type_map.find(reaction_type)->second],
		  d_mtp_yield_distributions_map[reaction_type],
		  base_reaction_map.find(base_reaction_type_map.find(reaction_type)->second)->second,
		  photon_production_distribution,
		  d_total_reaction ) );

	  ++iter_reaction;
  }

}

// Initialize the yield based photon production reactions
void DecoupledPhotonProductionReactionACEFactory::initializeCrossSectionBasedPhotonProductionReactions(
  const std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
  const double temperature,
  const std::unordered_map<unsigned,unsigned>& threshold_energy_map,
  const std::unordered_map<unsigned,std::shared_ptr<std::vector<double> > >& xs_based_map,
  const std::shared_ptr<const std::vector<double> >& energy_grid,
  const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
  grid_searcher,
  const SimulationProperties& properties,
  PhotonProductionNuclearScatteringDistributionACEFactory& photon_production_dist_factory )
{
  std::unordered_map<unsigned,unsigned>::const_iterator
    iter_reaction, end_reaction;
  iter_reaction = threshold_energy_map.begin();
  end_reaction = threshold_energy_map.end();

  std::shared_ptr<const NuclearScatteringDistribution<NeutronState,PhotonState> >
    photon_production_distribution;

  while( iter_reaction != end_reaction )
  {
    unsigned reaction_type = iter_reaction->first;

    std::shared_ptr<const DecoupledPhotonProductionReaction>& reaction =
                    d_photon_production_reactions[reaction_type];

    photon_production_dist_factory.createScatteringDistribution(
						     reaction_type,
                                                     properties,
						     photon_production_distribution );

    reaction.reset( new DecoupledCrossSectionBasedPhotonProductionReaction(
		  base_reaction_type_map.find(reaction_type)->second,
		  reaction_type,
		  temperature,
		  threshold_energy_map.find(reaction_type)->second,
		  energy_grid,
		  xs_based_map.find(reaction_type)->second,
                  grid_searcher,
		  photon_production_distribution,
		  d_total_reaction,
		  std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >() ) );

    ++iter_reaction;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearReactionACEFactory.cpp
//---------------------------------------------------------------------------//
