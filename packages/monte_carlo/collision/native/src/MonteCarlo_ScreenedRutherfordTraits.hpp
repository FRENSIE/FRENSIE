//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordTraits.hpp
//! \author Luke Kersting
//! \brief  Screened Rutherford traits
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCREENED_RUTHERFORD_TRAITS_HPP
#define MONTE_CARLO_SCREENED_RUTHERFORD_TRAITS_HPP

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

namespace MonteCarlo{

//! Screened Rutherford traits
class ScreenedRutherfordTraits
{

public:

  //! Typedef for the this type
  typedef ScreenedRutherfordTraits ThisType;

  //! Constructor
  ScreenedRutherfordTraits( const unsigned atomic_number,
                            const bool seltzer_modification_on = true );

  //! Destructor
  virtual ~ScreenedRutherfordTraits()
  { /* ... */ }


  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Set the atomic number
  void setAtomicNumber( unsigned atomic_number );

  //! Set the Seltzer modification of eta on (on by default)
  void setSeltzerModificationOn();

  //! Set the Seltzer modification of eta off (on by default)
  void setSeltzerModificationOff();

  //! Return if the the Seltzer modification of eta on (on by default)
  bool isSeltzerModificationOn() const;

  //! Evaluate Moliere's atomic screening constant
  double evaluateMoliereScreeningConstant( const double energy ) const;

  //! Evaluate Moliere's atomic screening constant
  static double evaluateMoliereScreeningConstant(
                                    const double energy,
                                    const unsigned atomic_number,
                                    const bool seltzer_modification_on = true );

  // The change scattering angle cosine below which the screened Rutherford distribution is used
  static double delta_mu_peak;

  // The scattering angle cosine above which the screened Rutherford distribution is used
  static double mu_peak;

private:

  // Set the screening parameters
  void setScreeningParameters();

  // A parameter for moliere's screening factor  ( 1/2 * (fsc/0.885)**2 )
  static double s_screening_param1;

  // A parameter for moliere's screening factor ( 3.76 * fsc**2 )
  static double s_screening_param2;

  // The atomic number ( Z )
  unsigned d_atomic_number;

  // A parameter for moliere's screening factor  ( 1/2 * (fsc/0.885)**2 * Z**(2/3) )
  double d_screening_param1;

  // A parameter for moliere's screening factor ( 3.76 * (fsc * Z )**2 )
  double d_screening_param2;

  // Seltzer modification of the moliere scareening constant on/off (on by default)
  bool d_seltzer_modification_on;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SCREENED_RUTHERFORD_TRAITS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordTraits.hpp
//---------------------------------------------------------------------------//
