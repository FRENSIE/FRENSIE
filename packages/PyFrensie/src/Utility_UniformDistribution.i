//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.i
//! \author Alex Robinson
//! \brief  The uniform distribution swig interface file. Note that units
//!         will not be enabled in the interface.
//!
//---------------------------------------------------------------------------//

%{
#include "Utility_UniformDistribution.hpp"
%}

%ignore Utility::UnitAwareUniformDistribution<void,void>::getDistributionType;
%ignore Utility::UnitAwareUniformDistribution<void,void>::fromUnitlessDistribution;
%ignore Utility::UnitAwareUniformDistribution<void,void>::ThisType;
%ignore Utility::UnitAwareUniformDistribution<void,void>::IndepQuantity;
%ignore Utility::UnitAwareUniformDistribution<void,void>::InverseIndepQuantity;
%ignore Utility::UnitAwareUniformDistribution<void,void>::DepQuantity;
%import "Utility_UniformDistribution.hpp"

%extend Utility::UnitAwareUniformDistribution<void,void> {
%template(CreateUniformDistribution) Utility::UnitAwareUniformDistribution::UnitAwareUniformDistribution<double,double>;
};

%template(UniformDistribution) Utility::UnitAwareUniformDistribution<void,void>;



