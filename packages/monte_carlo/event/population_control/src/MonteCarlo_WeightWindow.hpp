//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindow.hpp
//! \author Philip Britt
//! \brief  Weight window class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WEIGHT_WINDOW_HPP
#define MONTE_CARLO_WEIGHT_WINDOW_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_PopulationControl.hpp"


namespace MonteCarlo{

//! An actual weight window object.
struct WeightWindow{
  double upper_weight;
  double survival_weight;
  double lower_weight;
};

//! The weight window base class
class WeightWindowBase: public PopulationControl
{

public:

  //! Constructor
  WeightWindowBase()
  { /* ... */ }

  //! Destructor
  ~WeightWindowBase()
  { /* ... */ }

  void checkParticleWithPopulationController( ParticleState& particle, 
                                              ParticleBank& bank) const;

  protected:

  virtual std::shared_ptr<WeightWindow> getWeightWindow( ParticleState& particle ) const = 0;

  virtual bool isParticleInWeightWindowDiscretization( ParticleState& particle ) const = 0;

  private:

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::WeightWindow, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::WeightWindow );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, WeightWindow );

#endif // end MONTE_CARLO_WEIGHT_WINDOW_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindow.hpp
//---------------------------------------------------------------------------//
