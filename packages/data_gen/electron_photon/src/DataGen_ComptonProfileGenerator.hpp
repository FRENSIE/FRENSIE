//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ComptonProfileGenerator.hpp
//! \author Alex Robinson
//! \brief  The Compton profile generator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_COMPTON_PROFILE_GENERATOR_HPP
#define DATA_GEN_COMPTON_PROFILE_GENERATOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Map.hpp"
#include "Utility_Vector.hpp"

namespace DataGen{

//! The Compton profile generator
class ComptonProfileGenerator
{

public:

  //! Get the default generator
  static std::shared_ptr<ComptonProfileGenerator> getDefaultGenerator( const unsigned atomic_number );

  //! Constructor
  ComptonProfileGenerator()
  { /* ... */ }

  //! Destructor
  virtual ~ComptonProfileGenerator()
  { /* ... */ }

  /*! Generate the compton profiles for each subshell
   *
   * The momentum grid must be in units of me*e^2/h_bar (not me*c units) and
   * the half profiles must be in units of h_bar/(me*e^2) (not 1/(me*c) units).
   */
  virtual void generateHalfProfiles(
                     std::vector<std::vector<double> >& subshell_half_profiles,
                     std::vector<double>& union_half_momentum_grid ) const = 0;
};
  
} // end DataGen namespace

#endif // end DATA_GEN_COMPTON_PROFILE_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ComptonProfileGenerator.hpp
//---------------------------------------------------------------------------//
