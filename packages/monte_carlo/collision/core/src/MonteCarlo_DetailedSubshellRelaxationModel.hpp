//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedSubshellRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Detailed subshell relaxation model class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_SUBSHELL_RELAXATION_MODEL_HPP
#define MONTE_CARLO_DETAILED_SUBSHELL_RELAXATION_MODEL_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_SubshellRelaxationModel.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

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
       const std::vector<Data::SubshellType>& primary_transition_vacancy_shells,
       const std::vector<Data::SubshellType>& secondary_transition_vacancy_shells,
       const std::vector<double>& outgoing_particle_energies,
       const std::vector<double>& transition_pdf_or_cdf,
       const bool interpret_as_cdf = true );

  //! Destructor
  ~DetailedSubshellRelaxationModel()
  { /* ... */ }

  //! Relax the shell
  void relaxSubshell( const ParticleState& particle,
                      const double min_photon_energy,
                      const double min_electron_energy,
		      ParticleBank& bank,
		      Data::SubshellType& new_primary_vacancy_shell,
		      Data::SubshellType& new_secondary_vacancy_shell ) const;

private:

  // Generate a fluorescence photon
  void generateFluorescencePhoton( const ParticleState& particle,
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
  std::unique_ptr<Utility::DiscreteDistribution> d_transition_distribution;

  // The outgoing partial energies
  std::vector<double> d_outgoing_particle_energies;

  // The transition vacancy shells (first = primary, second = secondary)
  std::vector<std::pair<Data::SubshellType,Data::SubshellType> >
  d_transition_vacancy_shells;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_SUBSHELL_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedSubshellRelaxationModel.hpp
//---------------------------------------------------------------------------//
