//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindow.cpp
//! \author Alex Robinson
//! \brief  The weight window class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_WeightWindow.hpp"

namespace MonteCarlo{

//! The default weight window
class DefaultWeightWindow : public WeightWindow
{

public:

  //! Constructor
  DefaultWeightWindow();

  //! Destructor
  ~DefaultWeightWindow()
  { /* ... */ }

  //! Update the particle state and bank by passing through the weight window
  void updateParticleState( ParticleState&, ParticleBank& ) const final override
  { /* ... */ }

private:

  // Serialize the collision forcer data to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( WeightWindow ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Return the default weight window
std::shared_ptr<const WeightWindow> WeightWindow::getDefault()
{
  return std::shared_ptr<const WeightWindow>( new DefaultWeightWindow );
}
  
} // end MonteCarlo namespace

BOOST_CLASS_VERSION( MonteCarlo::DefaultWeightWindow, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DefaultWeightWindow, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( DefaultWeightWindow, MonteCarlo );

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::WeightWindow );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::DefaultWeightWindow );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindow.cpp
//---------------------------------------------------------------------------//
