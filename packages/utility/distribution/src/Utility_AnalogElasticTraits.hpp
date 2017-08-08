//---------------------------------------------------------------------------//
//!
//! \file   Utility_AnalogElasticTraits.hpp
//! \author Luke Kersting
//! \brief  The Analog elastic electron traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ANALOG_ELASTIC_TRAITS_HPP
#define UTILITY_ANALOG_ELASTIC_TRAITS_HPP

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

namespace Utility{

//! Electron elastic traits
class AnalogElasticTraits
{

public:

  //! Typedef for the this type
  typedef AnalogElasticTraits ThisType;

  //! Constructor
  AnalogElasticTraits( const unsigned atomic_number,
                            const bool seltzer_modification_on = true );

  //! Destructor
  virtual ~AnalogElasticTraits()
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

} // end Utility namespace

#endif // end UTILITY_ANALOG_ELASTIC_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_AnalogElasticTraits.hpp
//---------------------------------------------------------------------------//
