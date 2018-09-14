//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleTracker.i
//! \author Luke Kersting
//! \brief  The ParticleTracker class interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

%template(LongUnsignedSet) std::set<unsigned long>;

// ---------------------------------------------------------------------------//
// Add ParticleTracker support
// ---------------------------------------------------------------------------//

%ignore MonteCarlo::ParticleTracker::ParticleTracker();
%ignore *::reduceData;
%ignore *::printSummary;

%extend MonteCarlo::ParticleTracker
{
  // Get the data map
  PyObject* getHistoryData() const
  {
    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    $self->getHistoryData(history_map);

    return PyFrensie::Details::convertMapToPython( history_map );
  }
};

%ignore *::getHistoryData;

%shared_ptr(MonteCarlo::ParticleTracker)
%include "MonteCarlo_ParticleTracker.hpp"

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleTracker.i
//---------------------------------------------------------------------------//
