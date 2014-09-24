//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonDataFluorescence.hpp
//! \author Alex Robinson
//! \brief  PhotonDataFluorescence class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PHOTON_DATA_FLUORESCENCE_HPP
#define FACEMC_PHOTON_DATA_FLUORESCENCE_HPP

// Std Lib Includes
#include <map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

class PhotonDataFluorescence
{

protected:

  //! Constructor
  PhotonDataFluorescence( unsigned int atomic_number,
			  double energy_min,
			  double energy_max );

  //! Destructor
  ~PhotonDataFluorescence()
  { /* ... */ }

public:

  //! Return the shell with a vacancy after a photoelectric event
  unsigned int getPhotoelectricVacancyShell( const double energy,
					     const double cdf_value ) const;

  /*! Return the probability of a radiative transition for a vacancy in the 
   * shell of interest
   */
  double getShellRadiativeTransitionProbability( 
					      const unsigned int shell ) const;

  /*! Return the new vacancy shell and the emitted photon energy after
   * a radiative transition
   */
  Utility::Pair<unsigned int, double> getShellRadiativeTransitionData( 
						const unsigned int shell,
						const double cdf_value ) const;

  /*! Return the new vacancy shells and the emmitted electron energy after
   * a nonradiative transition
   */
  Utility::Trip<unsigned int, unsigned int, double> 
  getShellNonradiativeTransitionData( const unsigned int shell,
				      const double cdf_value ) const;

private:

  //@{
  //! Typedefs
  typedef Teuchos::ArrayRCP<Utility::Trip<double,double,double> > CrossSectionArray;
  typedef Teuchos::ArrayRCP<Utility::Trip<double, unsigned int, double> > RadiativeTransitionArray;
  typedef Teuchos::ArrayRCP<Utility::Quad<double, unsigned int, unsigned int, double> > NonradiativeTransitionArray;
  typedef std::map<unsigned int, CrossSectionArray> PhotoelectricShellMap;
  typedef std::map<unsigned int, RadiativeTransitionArray> RadiativeTransitionMap;
  typedef std::map<unsigned int, NonradiativeTransitionArray> NonradiativeTransitionMap;
  typedef std::map<unsigned int, double> ShellMap;
  //@}

  //-------------------------------------------------------------------------//
  // Photoelectric Effect Data
  //-------------------------------------------------------------------------//
  
  // Total Integrated photoelectric cross section
  CrossSectionArray d_total_integrated_photoelectric_cross_section;

  // Integrated photoelectric cross section for each shell
  PhotoelectricShellMap d_shell_integrated_photoelectric_cross_section;
  
  //-------------------------------------------------------------------------//
  // Shell Radiative Transition Data
  //-------------------------------------------------------------------------//

  // Total radiative transition probability for each shell
  ShellMap d_total_radiative_transition_probability;

  // Radiative transition data for each shell
  RadiativeTransitionMap d_radiative_transitions;

  //-------------------------------------------------------------------------//
  // Shell Nonradiative Transition Data
  //-------------------------------------------------------------------------//

  // Nonradiative transition data for each shell
  NonradiativeTransitionMap d_nonradiative_transitions;

  //-------------------------------------------------------------------------//
  // Shell Binding Energy Data
  //-------------------------------------------------------------------------//
  
  // Electron shell binding energy
  ShellMap d_electron_shell_binding_energy;

};

} // end MonteCarlo namespace

#endif // end FACEMC_PHOTON_DATA_FLUORESCENCE_HPP

//---------------------------------------------------------------------------//
//end MonteCarlo_PhotonDataFluorescence.hpp
//---------------------------------------------------------------------------//
