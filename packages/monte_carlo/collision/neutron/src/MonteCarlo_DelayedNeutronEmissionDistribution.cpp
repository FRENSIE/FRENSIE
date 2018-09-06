//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DelayedNeutronEmissionDistribution.cpp
//! \author Alex Robinson
//! \brief  The delayed neutron emission distribution class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DelayedNeutronEmissionDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The atomic weight ratio corresponds to the fissioning isotope.
 */
DelayedNeutronEmissionDistribution::DelayedNeutronEmissionDistribution(
      const double atomic_weight_ratio,
      const std::vector<double>& precursor_group_decay_consts,
      const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
      precursor_group_prob_distributions,
      const std::vector<std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> > >&
      precursor_group_emission_distributions )
  : NuclearScatteringDistribution<NeutronState,NeutronState>( atomic_weight_ratio ),
    d_precursor_group_decay_consts( precursor_group_decay_consts ),
    d_precursor_group_prob_distributions( precursor_group_prob_distributions ),
    d_precursor_group_emission_distributions(
				       precursor_group_emission_distributions )
{
  // Make sure the group data is valid
  testPrecondition( precursor_group_decay_consts.size() > 0 );
  testPrecondition( precursor_group_decay_consts.size() ==
		    precursor_group_prob_distributions.size() );
  testPrecondition( precursor_group_decay_consts.size() ==
		    precursor_group_emission_distributions.size() );
}

// Randomly "scatter" the neutron
void DelayedNeutronEmissionDistribution::scatterParticle(
				          const NeutronState& incoming_neutron,
					  NeutronState& outgoing_neutron,
					  const double temperature ) const
{
  // Sample the precursor group that generates the neutron
  unsigned precursor_group;

  double partial_cdf = 0.0;

  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  for( unsigned i = 0u; i < d_precursor_group_prob_distributions.size(); ++i )
  {
    partial_cdf += d_precursor_group_prob_distributions[i]->evaluate(
						incoming_neutron.getEnergy() );

    if( random_number < partial_cdf )
    {
      precursor_group = i;

      break;
    }
  }

  // Sample the emission time
  double emission_time =
    sampleEmissionTime( d_precursor_group_decay_consts[precursor_group] );

  // Sample the state after emission
  d_precursor_group_emission_distributions[precursor_group]->scatterParticle(
							      incoming_neutron,
							      outgoing_neutron,
							      temperature );

  // Set the new neutron time
  outgoing_neutron.setTime( incoming_neutron.getTime() + emission_time );
}

// Sample the emission time (s)
/*! \details The decay constant must have units of 1/s.
 */
double DelayedNeutronEmissionDistribution::sampleEmissionTime(
				      const double group_decay_constant ) const
{
  return -log(1.0 - Utility::RandomNumberGenerator::getRandomNumber<double>())/
    group_decay_constant;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DelayedNeutronEmissionDistribution.cpp
//---------------------------------------------------------------------------//

