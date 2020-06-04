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

#include "Utility_SampleMomentHistogram.hpp"
#include "Utility_Mesh.hpp"
#include "Utility_StructuredHexMesh.hpp"
#include "Utility_TetMesh.hpp"

#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleHistoryObserver.hpp"
#include "MonteCarlo_DiscretizableParticleHistoryObserver.hpp"
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

#include "MonteCarlo_ParticleResponse.hpp"
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

// Import the MonteCarlo_ParticleResponse.hpp
%shared_ptr(MonteCarlo::ParticleResponse)
%import "MonteCarlo_ParticleResponse.hpp"

// Add a few general typedefs
typedef unsigned int uint32_t;
typedef long unsigned int uint64_t;

// Add some general templates
%template(LongUnsignedVector) std::vector<long unsigned int>;
%template(IntVector) std::vector<int>;

// Add some general typemaps
%apply long unsigned int { const Geometry::Model::EntityId };

//---------------------------------------------------------------------------//
// Add SampleMomentHistogram support
//---------------------------------------------------------------------------//

// Add a typemap for std::vector<HistogramValueType>& values
%typemap(out) const std::vector<Utility::SampleMomentHistogram<double>::HistogramValueType>&
{
  $result = PyFrensie::convertToPython( *$1 );

  if( !$result )
    SWIG_fail;
}

%typemap(in,numinputs=0) std::vector<Utility::SampleMomentHistogram<double>::HistogramValueType>& values (std::vector<double> temp) "$1 = &temp;"

%typemap(argout) std::vector<Utility::SampleMomentHistogram<double>::HistogramValueType>& values {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::vector<DensityValueType>& values
%typemap(in,numinputs=0) std::vector<Utility::SampleMomentHistogram<double>::DensityValueType>& values (std::vector<double> temp) "$1 = &temp;"

%typemap(argout) std::vector<Utility::SampleMomentHistogram<double>::DensityValueType>& values {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%ignore *::clear;
%ignore *::reset;
%ignore *::setBinBoundaries;
%ignore *::addRawScore;
%ignore *::mergeHistograms;

%include "Utility_SampleMomentHistogram.hpp" 

%template(SampleMomentHistogram) Utility::SampleMomentHistogram<double>; 

//---------------------------------------------------------------------------//
// Add EstimatorContributionMultiplierPolicy support
//---------------------------------------------------------------------------//

%include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"

//---------------------------------------------------------------------------//
// Add ParticleHistoryObserver support
//---------------------------------------------------------------------------//

// Add typemaps for converting uint64_t to and from Python int
%typemap(in) const uint64_t num_histories ( uint64_t temp ){
  temp = PyInt_AsUnsignedLongLongMask( $input );
  $1 = temp;
}

%typemap(typecheck, precedence=70) (const uint64_t) {
  $1 = (PyInt_Check($input)) ? 1 : 0;
}

%shared_ptr( MonteCarlo::ParticleHistoryObserver )
%include "MonteCarlo_ParticleHistoryObserver.hpp"

//---------------------------------------------------------------------------//
// Add observer discretization support
//---------------------------------------------------------------------------//

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

%shared_ptr( MonteCarlo::DiscretizableParticleHistoryObserver )
%include "MonteCarlo_DiscretizableParticleHistoryObserver.hpp"

// Add setDiscretization function templates
%template(setEnergyDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION, std::vector<double> >;
%template(setTimeDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION, std::vector<double> >;
%template(setSourceEnergyDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::setDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, std::vector<double> >;
%template(setSourceTimeDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::setDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION, std::vector<double> >;
%template(setCollisionNumberDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, std::vector<unsigned> >;
%template(setCosineDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION, std::vector<double> >;
%template(setSourceIdDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::setDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION, std::vector<std::set<uint32_t> > >;

// Add getDiscretization function templates
%template(getEnergyDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::getDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION, std::vector<double> >;
%template(getTimeDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::getDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION, std::vector<double> >;
%template(getSourceEnergyDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::getDiscretization<MonteCarlo::OBSERVER_SOURCE_ENERGY_DIMENSION, std::vector<double> >;
%template(getSourceTimeDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::getDiscretization<MonteCarlo::OBSERVER_SOURCE_TIME_DIMENSION, std::vector<double> >;
%template(getCollisionNumberDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::getDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION, std::vector<unsigned> >;
%template(getCosineDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::getDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION, std::vector<double> >;
%template(getSourceIdDiscretization) MonteCarlo::DiscretizableParticleHistoryObserver::getDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION, std::vector<std::set<uint32_t> > >;

//---------------------------------------------------------------------------//
// Add Estimator support
//---------------------------------------------------------------------------//

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

    CONVERT_PYOBJECT_TO_VECTOR_OF_BASE_SHARED_PTR( raw_response_functions, response_functions, SWIGTYPE_p_std__shared_ptrT_MonteCarlo__ParticleResponse_t, conversion_success );

    if( conversion_success )
    {
      $self->setResponseFunctions( response_functions );
    }
    // SWIG will throw a runtime error
    else
    {
      PyErr_SetString( PyExc_RuntimeError,
                       "Could not convert Pyobject to a vector of ParticleResponse shared_ptrs." );
    }
  }

  //! Set the sample moment histogram bins
  void setSampleMomentHistogramBins( PyObject* raw_bin_boundaries )
  {
    std::shared_ptr<const std::vector<double> > bin_boundaries =
      std::make_shared<std::vector<double> >( PyFrensie::convertFromPython<std::vector<double> >( raw_bin_boundaries ) );

    $self->setSampleMomentHistogramBins( bin_boundaries );
  }

  // //! Get the total sample moment histogram
  // Utility::SampleMomentHistogram<double> getTotalSampleMomentHistogram( const size_t response_function_index )
  // {
  //   Utility::SampleMomentHistogram<double> histogram;

  //   $self->getTotalSampleMomentHistogram( response_function_index, histogram );

  //   return histogram;
  // }
};

%ignore *::setParticleTypes;
%ignore *::getParticleTypes;
%ignore *::setResponseFunctions;
%ignore *::setSampleMomentHistogramBins;
//%ignore *::getTotalSampleMomentHistogram;

// Add a typemap for Utility::SampleMomentHistogram<double>& histogram
%typemap(in,numinputs=0) Utility::SampleMomentHistogram<double>& histogram (Utility::SampleMomentHistogram<double> temp) "$1 = &temp;"

%typemap(argout) Utility::SampleMomentHistogram<double>& histogram {
  %append_output(SWIG_NewPointerObj((new Utility::SampleMomentHistogram< double >(*$1)), SWIGTYPE_p_Utility__SampleMomentHistogramT_double_t, SWIG_POINTER_OWN |  0 ));
}

// Add a typemap for std::map<std::string,std::vector<double> >& processed_data
%typemap(in,numinputs=0) std::map<std::string,std::vector<double> >& processed_data (std::map<std::string,std::vector<double> > temp) "$1 = &temp;"

%typemap(argout) std::map<std::string,std::vector<double> >& processed_data {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::map<std::string,std::vector<double> >& processed_snapshots
%typemap(in,numinputs=0) std::map<std::string,std::vector<double> >& processed_snapshots (std::map<std::string,std::vector<double> > temp) "$1 = &temp;"

%typemap(argout) std::map<std::string,std::vector<double> >& processed_snapshots {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::vector<uint64_t>& history_values
%typemap(in,numinputs=0) std::vector<uint64_t>& history_values (std::vector<uint64_t> temp) "$1 = &temp;"

%typemap(argout) std::vector<uint64_t>& history_values {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::vector<double>& sampling_times
%typemap(in,numinputs=0) std::vector<double>& sampling_times (std::vector<double> temp) "$1 = &temp;"

%typemap(argout) std::vector<double>& sampling_times {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::vector<double>& moments
%typemap(in,numinputs=0) std::vector<double>& moments (std::vector<double> temp) "$1 = &temp;"

%typemap(argout) std::vector<double>& moments {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

// Add a typemap for std::set<uint64_t>& entity_ids
%typemap(in,numinputs=0) std::set<uint64_t>& entity_ids (std::set<uint64_t> temp) "$1 = &temp;"

%typemap(argout) std::set<uint64_t>& entity_ids {
  %append_output(PyFrensie::convertToPython( *$1 ));
}

%shared_ptr( MonteCarlo::Estimator )
%include "MonteCarlo_Estimator.hpp"

//---------------------------------------------------------------------------//
// Add EntityEstimator support
//---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::EntityEstimator )
%include "MonteCarlo_EntityEstimator.hpp"

//---------------------------------------------------------------------------//
// Add StandardEntityEstimator support
//---------------------------------------------------------------------------//

%shared_ptr( MonteCarlo::StandardEntityEstimator )
%include "MonteCarlo_StandardEntityEstimator.hpp"

//---------------------------------------------------------------------------//
// Add StandardSurfaceEstimator support
//---------------------------------------------------------------------------//

%ignore MonteCarlo::StandardSurfaceEstimator::StandardSurfaceEstimator;
%ignore *::printSummary;

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>& surface_ids }

%shared_ptr( MonteCarlo::StandardSurfaceEstimator )
%include "MonteCarlo_StandardSurfaceEstimator.hpp"

//---------------------------------------------------------------------------//
// Add StandardCellEstimator support
//---------------------------------------------------------------------------//

%ignore MonteCarlo::StandardCellEstimator::StandardCellEstimator;
%ignore *::printSummary;

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::StandardCellEstimator::CellIdType>& cell_ids }

%shared_ptr( MonteCarlo::StandardCellEstimator)
%include "MonteCarlo_StandardCellEstimator.hpp"

//---------------------------------------------------------------------------//
// Helper macro for the pre-include estimator class python interface
//---------------------------------------------------------------------------//
%define %pre_estimator_setup_helper( ESTIMATOR_NAME )

// The weight multiplied ESTIMATOR_NAME
%pre_template_setup_helper( ESTIMATOR_NAME<MonteCarlo::WeightMultiplier>, WeightMultiplied ## ESTIMATOR_NAME )

// The weight and energy multiplied ESTIMATOR_NAME
%pre_template_setup_helper( ESTIMATOR_NAME<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultiplied ## ESTIMATOR_NAME )

// The weight and charge multiplied ESTIMATOR_NAME
%pre_template_setup_helper( ESTIMATOR_NAME<MonteCarlo::WeightAndChargeMultiplier>, WeightAndChargeMultiplied ## ESTIMATOR_NAME )

%enddef

//---------------------------------------------------------------------------//
// Helper macro for the post-include estimator class python interface
//---------------------------------------------------------------------------//
%define %post_estimator_setup_helper( ESTIMATOR_NAME )

// The weight multiplied ESTIMATOR_NAME
%post_template_setup_helper( ESTIMATOR_NAME<MonteCarlo::WeightMultiplier>, WeightMultiplied ## ESTIMATOR_NAME )

// The weight and energy multiplied ESTIMATOR_NAME
%post_template_setup_helper( ESTIMATOR_NAME<MonteCarlo::WeightAndEnergyMultiplier>, WeightAndEnergyMultiplied ## ESTIMATOR_NAME )

// The weight and charge multiplied ESTIMATOR_NAME
%post_template_setup_helper( ESTIMATOR_NAME<MonteCarlo::WeightAndChargeMultiplier>, WeightAndChargeMultiplied ## ESTIMATOR_NAME )

%enddef

//---------------------------------------------------------------------------//
// Add SurfaceCurrentEstimator support
//---------------------------------------------------------------------------//

// The multiplied surface current estimators
%pre_estimator_setup_helper( SurfaceCurrentEstimator )

%shared_ptr( MonteCarlo::SurfaceCurrentEstimator )
%include "MonteCarlo_SurfaceCurrentEstimator.hpp"

// The multiplied surface current estimators
%post_estimator_setup_helper( SurfaceCurrentEstimator )

//---------------------------------------------------------------------------//
// Add SurfaceFluxEstimator support
//---------------------------------------------------------------------------//

// The multiplied surface flux estimators
%pre_estimator_setup_helper( SurfaceFluxEstimator )

%include "MonteCarlo_SurfaceFluxEstimator.hpp"

// The multiplied surface flux estimators
%post_estimator_setup_helper( SurfaceFluxEstimator )

//---------------------------------------------------------------------------//
// Add CellPulseHeightEstimator support
//---------------------------------------------------------------------------//

// The multiplied cell pulse height estimators
%pre_estimator_setup_helper( CellPulseHeightEstimator )

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::CellPulseHeightEstimator< MonteCarlo::WeightMultiplier >::CellIdType>& entity_ids }

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::CellPulseHeightEstimator< MonteCarlo::WeightAndEnergyMultiplier >::CellIdType>& entity_ids }

%apply std::vector<long unsigned int>& INPUT { const std::vector<MonteCarlo::CellPulseHeightEstimator< MonteCarlo::WeightAndChargeMultiplier >::CellIdType>& entity_ids }

%include "MonteCarlo_CellPulseHeightEstimator.hpp"

// The multiplied cell pulse height estimators
%post_estimator_setup_helper( CellPulseHeightEstimator )

//---------------------------------------------------------------------------//
// Add CellTrackLengthFluxEstimator support
//---------------------------------------------------------------------------//

// The multiplied cell track length flux estimators
%pre_estimator_setup_helper( CellTrackLengthFluxEstimator )

%include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"

// The multiplied cell track length flux estimators
%post_estimator_setup_helper( CellTrackLengthFluxEstimator )

//---------------------------------------------------------------------------//
// Add CellCollisionFluxEstimator support
//---------------------------------------------------------------------------//

// The multiplied cell collision flux estimators
%pre_estimator_setup_helper( CellCollisionFluxEstimator )

%include "MonteCarlo_CellCollisionFluxEstimator.hpp"

// The multiplied cell collision flux estimators
%post_estimator_setup_helper( CellCollisionFluxEstimator )


//---------------------------------------------------------------------------//
// Add MeshTrackLengthFluxEstimator support
//---------------------------------------------------------------------------//

// The multiplied cell collision flux estimators
%pre_estimator_setup_helper( MeshTrackLengthFluxEstimator )

%include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"

// The multiplied cell collision flux estimators
%post_estimator_setup_helper( MeshTrackLengthFluxEstimator )

//---------------------------------------------------------------------------//
// end MonteCarlo_Estimator.i
//---------------------------------------------------------------------------//
