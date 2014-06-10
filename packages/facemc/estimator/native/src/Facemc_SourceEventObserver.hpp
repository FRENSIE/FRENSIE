//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_SourceEventObserver.hpp
//! \author Alex Robinson
//! \brief  Source event observer base class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_SOURCE_EVENT_OBSERVER_HPP
#define FACEMC_SOURCE_EVENT_OBSERVER_HPP

namespace Facemc{

//! The source event observer base class
class SourceEventObserver{

public:

  //! Constructor 
  SourceEventObserver( const Estimator::idType id );

  //! Destructor
  virtual ~SourceEventObserver();

  //! Update the observer 
  void update( const ParticleState& particle ) = 0;

private:

  Estimator::idType d_id;
};

} // end Facemc namespace

#endif // end FACEMC_SOURCE_EVENT_OBSERVER

//---------------------------------------------------------------------------//
// end Facemc_SourceEventObserver.hpp
//---------------------------------------------------------------------------//
