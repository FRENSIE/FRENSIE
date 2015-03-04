//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DelayedNeutronEmissionDistribution.hpp
//! \author Alex Robinson
//! \brief  The delayed neutron emission distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_HPP
#define MONTE_CARLO_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The delayed neutron emission distribution class 
class DelayedNeutronEmissionDistribution : public NuclearScatteringDistribution<NeutronState,NeutronState>
{
  
public:

  //! Constructor
  DelayedNeutronEmissionDistribution( 
      const double atomic_weight_ratio,
      const Teuchos::Array<double>& precursor_group_decay_consts,
      const Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >& 
      precursor_group_prob_distributions,
      const Teuchos::Array<Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > >&
      precursor_group_emission_distributions );

  //! Destructor
  ~DelayedNeutronEmissionDistribution()
  { /* ... */ }

  //! Randomly "scatter" the neutron
  void scatterParticle( const NeutronState& incoming_neutron,
		        NeutronState& outgoing_neutron,
			const double temperature ) const;

protected:

  //! Sample the emission time (s)
  double sampleEmissionTime( const double group_decay_constant ) const;

private:

  // The delayed neutron precursor group decay constants
  Teuchos::Array<double> d_precursor_group_decay_consts;
  
  // The delayed neutron precursor group probability distributions
  Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >
  d_precursor_group_prob_distributions;

  // The delayed neutron precursor group energy distributions
  Teuchos::Array<Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > >
  d_precursor_group_emission_distributions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DELAYED_NEUTRON_EMISSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DelayedNeutronEmissionDistribution.hpp
//---------------------------------------------------------------------------//
