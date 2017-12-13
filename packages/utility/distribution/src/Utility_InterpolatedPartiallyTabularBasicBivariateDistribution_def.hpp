//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedPartiallyTabularBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular basic bivariate dist. class
//!         declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

BOOST_SERIALIZATION_DISTRIBUTION4_EXPORT_IMPLEMENT( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution );

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedPartiallyTabularBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedPartiallyTabularBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions )
  : BaseType( primary_indep_grid, secondary_distributions )
{ 
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Method for placing the object in an output stream
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareInterpolatedPartiallyTabularBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamTabularDistImpl( os, "InterpolatedPartiallyTabularBasicBivariateDistribution" );
}

// Save the distribution to an archive
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedPartiallyTabularBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedPartiallyTabularBivariateDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LinLinLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LinLogLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LinLinLog,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LinLogLog,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LogLinLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LogLogLin,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LogLinLog,void,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<Utility::LogLogLog,void,void,void> );

#endif // end UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedPartiallyTabularBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
