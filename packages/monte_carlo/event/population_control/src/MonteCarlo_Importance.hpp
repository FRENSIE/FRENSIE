//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Importance.hpp
//! \author Philip Britt
//! \brief  Importance class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_HPP
#define MONTE_CARLO_IMPORTANCE_HPP

// FRENSIE Includes
#include "MonteCarlo_PopulationControl.hpp"


namespace MonteCarlo{

//! The importance base class
class Importance: public PopulationControl
{

public:

  //! Constructor
  Importance()
  { /* ... */ }

  //! Destructor
  virtual ~Importance()
  { /* ... */ }

  void checkParticleWithPopulationController( ParticleState& particle, 
                                              ParticleBank& bank) const;

  virtual double getImportance( ParticleState& particle ) const = 0;

  virtual bool isParticleInImportanceDiscretization( ParticleState& particle ) const = 0;

private:

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    // Serialize the base class data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( PopulationControl );
  }

};

} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::Importance, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT( MonteCarlo::Importance );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, Importance );

#endif // end MONTE_CARLO_WEIGHT_WINDOW_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Importance.hpp
//---------------------------------------------------------------------------//
