//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Estimator.i
//! \author Luke Kersting
//! \brief  The Estimator classes interface file
//!
//---------------------------------------------------------------------------//

%{
// FRENSIE Includes
#include "PyFrensie_PythonTypeTraits.hpp"

#include "Geometry_InfiniteMediumModel.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "Geometry_InfiniteMediumNavigator.hpp"

#include "Utility_Mesh.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_TetMesh.hpp"

#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_Estimator.hpp"
#include "MonteCarlo_EntityEstimator.hpp"
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_StandardSurfaceEstimator.hpp"
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"

using namespace MonteCarlo;
%}

// C++ STL support
%include <stl.i>
%include <std_string.i>
%include <std_shared_ptr.i>
%include <std_set.i>
%include <std_map.i>
%include <std_vector.i>
%include <std_except.i>

// Include typemaps support
%include <typemaps.i>

// Import the Geometry.Geometry__init__.i file
%import "Geometry.Geometry__init__.i"

// Mesh handling
%import "Utility.Mesh.i"

// Include the ArrayView support
%include "PyFrensie_Array.i"

// Import the PyFrensie_ArraySharedPtr.i
%include "PyFrensie_ArraySharedPtr.i"

// Add a few general typedefs
typedef unsigned int uint32_t;

// Add some general templates
%template(LongUnsignedVector) std::vector<long unsigned int>;
%template(IntVector) std::vector<int>;

// Add some general typemaps
%apply long unsigned int { const Geometry::Model::EntityId };


// ---------------------------------------------------------------------------//
// Add EstimatorContributionMultiplierPolicy support
// ---------------------------------------------------------------------------//

%include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

// ---------------------------------------------------------------------------//
// Add ParticleHistoryObserver support
// ---------------------------------------------------------------------------//

// Add typemaps for converting unsigned long long to and from Python int
%typemap(in) const unsigned long long num_histories ( unsigned long long temp ){
  temp = PyInt_AsUnsignedLongLongMask( $input );
  $1 = temp;
}

%typemap(typecheck, precedence=70) (const unsigned long long) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

%shared_ptr( MonteCarlo::ParticleHistoryObserver )
%include "MonteCarlo_ParticleHistoryObserver.hpp"

// ---------------------------------------------------------------------------//
// Add Estimator support
// ---------------------------------------------------------------------------//

// Extend the Estimator class to handle ParticleType enum as int
%extend MonteCarlo::Estimator
{
  // Set the particle types that can contribute to the estimator
  void setParticleTypes( const std::vector<int>& particle_types_int )
  {
    std::vector<MonteCarlo::ParticleType> particle_types;

    particle_types.resize(particle_types_int.size());
    for( unsigned i = 0; i < particle_types_int.size(); ++i )
    {
      particle_types[i] =
        MonteCarlo::convertIntToParticleType(particle_types_int[i]);
    }

    $self->setParticleTypes( particle_types );
  }

  // Get the particle types that can contribute to the estimator
  PyObject* getParticleTypes()
  {
    const std::set<ParticleType>& particle_types = $self->getParticleTypes();

    std::set<int> raw_particle_types( particle_types.begin(),
                                      particle_types.end() );

    return PyFrensie::convertToPython( raw_particle_types );
  }

  // Set response functions
  void setResponseFunctions( PyObject* raw_response_functions )
  {
    std::vector< std::shared_ptr< MonteCarlo::ParticleResponse const > > response_functions;

    bool conversion_success;

    CONVERT_PYOBJECT_TO_VECTOR_OF_BASE_SHARED_PTR( raw_response_functions, response_functions, SWIGTYPE_p_std__shared_ptrT_ParticleResponse_const_t, conversion_success );

    if( conversion_success )
    {
      $self->setResponseFunctions( response_functions );
    }
    // SWIG will throw a runtime error
    else
      PyErr_SetString( PyExc_RuntimeError,
                       "Could not convert Pyobject to a vector of ParticleResponse shared_ptrs." );
  }

};

%ignore *::setParticleTypes;
%ignore *::getParticleTypes;
%ignore *::setResponseFunctions;

%template(ParticleResponseVector) std::vector< std::shared_ptr< ParticleResponse const >,std::allocator< std::shared_ptr< ParticleResponse const > > >;

// Add a typemap for std::map<std::string,std::vector<double> >& processed data
%typemap(in,numinputs=0) std::map<std::string,std::vector<double> >& processed_data (std::map<std::string,std::vector<double> > temp) "$1 = &temp;"

%typemap(argout) std::map<std::string,std::vector<double> >& processed_data {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::set<uint64_t>& entity_ids
%typemap(in,numinputs=0) std::set<uint64_t>& entity_ids (std::set<uint64_t> temp) "$1 = &temp;"

%typemap(argout) std::set<uint64_t>& entity_ids {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions
%template(ObserverPhaseSpaceDimensionVector) std::vector<MonteCarlo::ObserverPhaseSpaceDimension>;

%typemap (in,numinputs=0) std::vector<MonteCarlo::ObserverPhaseSpaceDimension>& discretized_dimensions (std::vector<MonteCarlo::ObserverPhaseSpaceDimension> temp) "$1 = &temp;"

%typemap(argout) std::vector<MonteCarlo::ObserverPhaseSpaceDimension>& discretized_dimensions {
  %append_output(swig::from( *$1 ));
}

// Add a typemap for std::vector<double>& bin_data
%typemap (in,numinputs=0) std::vector<double>& bin_data (std::vector<double> temp) "$1 = &temp;"

%typemap(argout) std::vector<double>& bin_data {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::vector<unsigned>& bin_data
%typemap (in,numinputs=0) std::vector<unsigned>& bin_data (std::vector<unsigned> temp) "$1 = &temp;"

%typemap(argout) std::vector<unsigned>& bin_data {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::vector<std::set<uint32_t> >& bin_data
%typemap (in,numinputs=0) std::vector<std::set<uint32_t> >& bin_data (std::vector<std::set<uint32_t> > temp) "$1 = &temp;"

%typemap(argout) std::vector<std::set<uint32_t> >& bin_data {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%shared_ptr( MonteCarlo::Estimator )
%include "MonteCarlo_Estimator.hpp"

// Add setDiscretization function templates
%template(setEnergyDiscretization) MonteCarlo::Estimator::setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION, std::vector<double> >;
%template(setTimeDiscretization) MonteCarlo::Estimator::setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION, std::vector<double> >;
%template(setSourceEnergyDiscretization) MonteCarlo::Estimator::setDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, std::vector<double> >;
%template(setSourceTimeDiscretization) MonteCarlo::Estimator::setDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION, std::vector<double> >;
%template(setCollisionNumberDiscretization) MonteCarlo::Estimator::setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, std::vector<unsigned> >;
%template(setCosineDiscretization) MonteCarlo::Estimator::setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION, std::vector<double> >;
%template(setSourceIdDiscretization) MonteCarlo::Estimator::setDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION, std::vector<std::set<uint32_t> > >;

// Add getDiscretization function templates
%template(getEnergyDiscretization) MonteCarlo::Estimator::getDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION, std::vector<double> >;
%template(getTimeDiscretization) MonteCarlo::Estimator::getDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION, std::vector<double> >;
%template(getSourceEnergyDiscretization) MonteCarlo::Estimator::getDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, std::vector<double> >;
%template(getSourceTimeDiscretization) MonteCarlo::Estimator::getDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION, std::vector<double> >;
%template(getCollisionNumberDiscretization) MonteCarlo::Estimator::getDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, std::vector<unsigned> >;
%template(getCosineDiscretization) MonteCarlo::Estimator::getDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION, std::vector<double> >;
%template(getSourceIdDiscretization) MonteCarlo::Estimator::getDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION, std::vector<std::set<uint32_t> > >;

// ---------------------------------------------------------------------------//
// Add EntityEstimator support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::EntityEstimator )
%include "MonteCarlo_EntityEstimator.hpp"

// ---------------------------------------------------------------------------//
// Add StandardEntityEstimator support
// ---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::StandardEntityEstimator )
%include "MonteCarlo_StandardEntityEstimator.hpp"

// ---------------------------------------------------------------------------//
// Add StandardSurfaceEstimator support
// ---------------------------------------------------------------------------//

%ignore MonteCarlo::StandardSurfaceEstimator::StandardSurfaceEstimator;
%ignore *::printSummary;

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>& surface_ids }

%shared_ptr( MonteCarlo::StandardSurfaceEstimator )
%include "MonteCarlo_StandardSurfaceEstimator.hpp"

// ---------------------------------------------------------------------------//
// Add StandardCellEstimator support
// ---------------------------------------------------------------------------//

%ignore MonteCarlo::StandardCellEstimator::StandardCellEstimator;
%ignore *::printSummary;

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::StandardCellEstimator::CellIdType>& cell_ids }

%shared_ptr( MonteCarlo::StandardCellEstimator)
%include "MonteCarlo_StandardCellEstimator.hpp"

// ---------------------------------------------------------------------------//
// Add SurfaceCurrentEstimator support
// ---------------------------------------------------------------------------//

// The weight multiplied surface current estimator
%pre_template_setup_helper( SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedSurfaceCurrentEstimator )

// The weight and energy multiplied surface current estimator
%pre_template_setup_helper( SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedSurfaceCurrentEstimator )

%shared_ptr( MonteCarlo::SurfaceCurrentEstimator )
%include "MonteCarlo_SurfaceCurrentEstimator.hpp"

// The weight multiplied surface current estimator
%post_template_setup_helper( SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedSurfaceCurrentEstimator )

// The weight and energy multiplied surface current estimator
%post_template_setup_helper( SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedSurfaceCurrentEstimator )

// ---------------------------------------------------------------------------//
// Add SurfaceFluxEstimator support
// ---------------------------------------------------------------------------//

// The weight multiplied surface flux estimator
%pre_template_setup_helper( SurfaceFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedSurfaceFluxEstimator )

// The weight and energy multiplied surface flux estimator
%pre_template_setup_helper( SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedSurfaceFluxEstimator )

%include "MonteCarlo_SurfaceFluxEstimator.hpp"

// The weight multiplied surface flux estimator
%post_template_setup_helper( SurfaceFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedSurfaceFluxEstimator )

// The weight and energy multiplied surface flux estimator
%post_template_setup_helper( SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedSurfaceFluxEstimator )

// ---------------------------------------------------------------------------//
// Add CellPulseHeightEstimator support
// ---------------------------------------------------------------------------//

// The weight multiplied cell pulse height estimator
%pre_template_setup_helper( CellPulseHeightEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedCellPulseHeightEstimator )

// The weight and energy multiplied cell pulse height estimator
%pre_template_setup_helper( CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedCellPulseHeightEstimator )

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::CellPulseHeightEstimator< MonteCarlo::WeightMultiplier >::CellIdType>& entity_ids }

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::CellPulseHeightEstimator< MonteCarlo::WeightAndEnergyMultiplier >::CellIdType>& entity_ids }

%include "MonteCarlo_CellPulseHeightEstimator.hpp"

// The weight multiplied cell pulse height estimator
%post_template_setup_helper( CellPulseHeightEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedCellPulseHeightEstimator )

// The weight and energy multiplied cell pulse height estimator
%post_template_setup_helper( CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedCellPulseHeightEstimator )

// ---------------------------------------------------------------------------//
// Add CellTrackLengthFluxEstimator support
// ---------------------------------------------------------------------------//

// The weight multiplied cell track length flux estimator
%pre_template_setup_helper( CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedCellTrackLengthFluxEstimator )

// The weight and energy multiplied cell track length flux estimator
%pre_template_setup_helper( CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedCellTrackLengthFluxEstimator )

%include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"

// The weight multiplied cell track length flux estimator
%post_template_setup_helper( CellTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedCellTrackLengthFluxEstimator )

// The weight and energy multiplied cell track length flux estimator
%post_template_setup_helper( CellTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedCellTrackLengthFluxEstimator )


// ---------------------------------------------------------------------------//
// Add CellCollisionFluxEstimator support
// ---------------------------------------------------------------------------//

// The weight multiplied cell collision flux estimator
%pre_template_setup_helper( CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedCellCollisionFluxEstimator )

// The weight and energy multiplied cell collision flux estimator
%pre_template_setup_helper( CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedCellCollisionFluxEstimator )

%include "MonteCarlo_CellCollisionFluxEstimator.hpp"

// The weight multiplied cell collision flux estimator
%post_template_setup_helper( CellCollisionFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedCellCollisionFluxEstimator )

// The weight and energy multiplied cell collision flux estimator
%post_template_setup_helper( CellCollisionFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedCellCollisionFluxEstimator )


// ---------------------------------------------------------------------------//
// Add MeshTrackLengthFluxEstimator support
// ---------------------------------------------------------------------------//

// The weight multiplied cell collision flux estimator
%pre_template_setup_helper( MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedMeshTrackLengthFluxEstimator )

// The weight and energy multiplied cell collision flux estimator
%pre_template_setup_helper( MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator )

%include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"

// The weight multiplied cell collision flux estimator
%post_template_setup_helper( MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>, WeightMultipliedMeshTrackLengthFluxEstimator )

// The weight and energy multiplied cell collision flux estimator
%post_template_setup_helper( MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultipliedMeshTrackLengthFluxEstimator )

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator.i
//---------------------------------------------------------------------------//
