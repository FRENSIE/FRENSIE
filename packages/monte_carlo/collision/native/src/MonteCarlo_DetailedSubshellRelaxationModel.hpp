//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedSubshellRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Detailed subshell relaxation model class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_SUBSHELL_RELAXATION_MODEL_HPP
#define MONTE_CARLO_DETAILED_SUBSHELL_RELAXATION_MODEL_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// Boost Includes
#include <boost/scoped_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellRelaxationModel.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! Detailed subshell relaxation model class
 * \details This model accounts for all possible transitions to fill a 
 * vacancy in the initial shell.
 */
class DetailedSubshellRelaxationModel : public SubshellRelaxationModel
{
  
public:

  //! Constructor
  DetailedSubshellRelaxationModel( 
       const Data::SubshellType vacancy_subshell,
       const Teuchos::Array<Data::SubshellType>& primary_transition_vacancy_shells,
       const Teuchos::Array<Data::SubshellType>& secondary_transition_vacancy_shells,
       const Teuchos::Array<double>& outgoing_particle_energies,
       const Teuchos::Array<double>& transition_pdf_or_cdf,
       const bool interpret_as_cdf = true );

  //! Destructor
  ~DetailedSubshellRelaxationModel()
  { /* ... */ }

  //! Relax the shell
  void relaxSubshell( const ParticleState& particle,
		      ParticleBank& bank,
		      Data::SubshellType& new_primary_vacancy_shell,
		      Data::SubshellType& new_secondary_vacancy_shell ) const;

private:

  // Generate a fluorescence photon
  void generateFluorescencePhoton( 
			       const ParticleState& particle,
			       const double new_photon_energy,
			       ParticleBank& bank ) const;

  // Generate an Auger electron
  void generateAugerElectron( const ParticleState& particle,
			      const double new_electron_energy,
			      ParticleBank& bank ) const;

  // Sample emission direction
  void sampleEmissionDirection( double& angle_cosine,
				double& azimuthal_angle ) const;
				   
  // The transition distribution (also stores the outgoing particle energies )
  boost::scoped_ptr<Utility::DiscreteDistribution> d_transition_distribution;

  // The outgoing partiel energies
  Teuchos::Array<double> d_outgoing_particle_energies;

  // The transition vacancy shells (first = primary, second = secondary)
  Teuchos::Array<Utility::Pair<Data::SubshellType,Data::SubshellType> > 
  d_transition_vacancy_shells;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_SUBSHELL_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedSubshellRelaxationModel.hpp
//---------------------------------------------------------------------------//
