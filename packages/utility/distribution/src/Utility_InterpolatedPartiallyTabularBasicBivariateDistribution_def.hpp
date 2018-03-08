//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedPartiallyTabularBasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular basic bivariate dist. class
//!         declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

BOOST_SERIALIZATION_DISTRIBUTION5_EXPORT_IMPLEMENT( UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution );

namespace Utility{

// Default constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution()
{ 
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution(
     const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
     const std::vector<std::shared_ptr<const BaseUnivariateDistributionType> >&
     secondary_distributions,
     const double fuzzy_boundary_tol,
     const double relative_error_tol,
     const double error_tol )
  : BaseType( primary_indep_grid,
              secondary_distributions,
              fuzzy_boundary_tol,
              relative_error_tol,
              error_tol )
{ 
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Method for placing the object in an output stream
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamTabularDistImpl( os,
                                 "InterpolatedPartiallyTabularBasicBivariateDistribution",
                                 std::make_pair( "interp", TwoDInterpPolicy::name() ),
                                 std::make_pair( "sampling", TwoDSamplePolicy::name() ) );
}

// Save the distribution to an archive
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DIST( Utility::UnitAwareInterpolatedPartiallyTabularBasicBivariateDistribution, void, void, void );

#endif // end UTILITY_INTERPOLATED_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedPartiallyTabularBasicBivariateDistribution_def.hpp
//---------------------------------------------------------------------------//
