//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellRelaxationModel.hpp
//! \author Alex Robinson
//! \brief  Subshell relaxation model base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_RELAXATION_MODEL_HPP
#define MONTE_CARLO_SUBSHELL_RELAXATION_MODEL_HPP

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

//! Subshell relaxation class
class SubshellRelaxationModel
{
public:

  //! Constructor
  SubshellRelaxationModel( const Data::SubshellType vacancy_subshell );

  //! Destructor
  ~SubshellRelaxationModel()
  { /* ... */ }

  //! Relax the shell
  virtual void relaxSubshell(
                   const ParticleState& particle,
                   const double min_photon_energy,
                   const double min_electron_energy,
                   ParticleBank& bank,
                   Data::SubshellType& new_primary_vacancy_shell,
		   Data::SubshellType& new_secondary_vacancy_shell ) const = 0;

  //! Return the subshell that contains the vacancy
  Data::SubshellType getVacancySubshell() const;

private:

  // The vacancy subshell
  Data::SubshellType d_vacancy_subshell;
};

// Return the subshell that contains the vacancy
inline Data::SubshellType SubshellRelaxationModel::getVacancySubshell() const
{
  return d_vacancy_subshell;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_RELAXATION_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellRelaxationModel.hpp
//---------------------------------------------------------------------------//
