//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonDataBasic.hpp
//! \author Alex Robinson
//! \brief  PhotonDataBasic class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PHOTON_DATA_BASIC_HPP
#define FACEMC_PHOTON_DATA_BASIC_HPP

// Std Lib Includes
#include <map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

class PhotonDataBasic
{

protected:

  //! Constructor
  PhotonDataBasic( unsigned int atomic_number,
		   double energy_min,
		   double energy_max );

  //! Destructor
  ~PhotonDataBasic()
  { /* ... */ }

  //! Return the atomic number of the element stored
  unsigned int getAtomicNumber() const;

  //! Return the atomic weight of the element stored
  double getAtomicWeight() const;

  //! Return the total cross section for a given energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the non absorption probability for a given energy
  double getNonabsorptionProbability( const double energy ) const;

public:
  
  //! Return the integrated coherent cross section for a given energy
  double getCoherentCrossSection( const double energy ) const;

  //! Return the form factor cdf value for a given argument
  double getFormFactorCDF( const double argument ) const;

  //! Return the form factor argument for a given cdf value
  double getFormFactorArgument( const double cdf_value ) const;

  //! Return the integrated incoherent cross section for a given energy
  double getIncoherentCrossSection( const double energy ) const;

  //! Return the scattering function for a given argument
  double getScatteringFunction( const double argument ) const;

  //! Return the integrated photoelectric cross section for a given energy
  double getPhotoelectricCrossSection( const double energy ) const;

  //! Return the integrated pair production cross section for a given energy
  double getPairProductionCrossSection( const double energy ) const;

  //! Return the integrated triplet production cross section for a given energy
  double getTripletProductionCrossSection( const double energy ) const;

private:

  //@{
  //! Typedefs
  typedef Teuchos::ArrayRCP<Utility::Trip<double,double,double> > CrossSectionArray;
  typedef Teuchos::ArrayRCP<Utility::Quad<double,double,double,double> > FormFactorArray;
  typedef std::map<unsigned int,double> ShellMap;
  //@}
  
  // Atomic Number
  unsigned int d_atomic_number;

  // Atomic Weight
  double d_atomic_weight;

  //-------------------------------------------------------------------------//
  // Coherent Scattering Data
  //-------------------------------------------------------------------------//

  // Integrated coherent cross section
  CrossSectionArray d_integrated_coherent_cross_section;

  // Coherent cross section form factor
  FormFactorArray d_form_factor;

  //-------------------------------------------------------------------------//
  // Incoherent Scattering Data
  //-------------------------------------------------------------------------//
  
  // Integrated incoherent cross section
  CrossSectionArray d_integrated_incoherent_cross_section;

  // Incoherent cross section scattering function
  CrossSectionArray d_scattering_function;

  //-------------------------------------------------------------------------//
  // Photoelectric Effect Data
  //-------------------------------------------------------------------------//
  
  // Integrated photoelectric cross section
  CrossSectionArray d_integrated_photoelectric_cross_section;

  //-------------------------------------------------------------------------//
  // Pair Production Data
  //-------------------------------------------------------------------------//
  
  // Integrated pair production cross section
  CrossSectionArray d_integrated_pair_production_cross_section;

  //-------------------------------------------------------------------------//
  // Triplet Production Data
  //-------------------------------------------------------------------------//
  
  // Integrated triplet production cross section
  CrossSectionArray d_integrated_triplet_production_cross_section;

};

} // end MonteCarlo namespace

#endif // end FACEMC_PHOTON_DATA_BASIC_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonDataBasic.hpp
//---------------------------------------------------------------------------//

