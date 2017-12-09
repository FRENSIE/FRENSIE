//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularBivariateDistribution.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_InterpolatedTabularBivariateDistributionImplBase.hpp"

namespace Utility{

namespace {

//! Helper class used to construct a cdf interpolation policy
template<typename YProcessingTag, typename XProcessingTag>
struct CDFInterpolationHelper
{ /* ... */ };

//! Helper class used to construct a LinLinLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLinLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLog CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLog CDFInterpPolicy;
};
  
} // end local namespace

/*! The unit-aware inteprolated fully tabular bivariate distribution
 * \ingroup two_d_distribution
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedFullyTabularBivariateDistribution : public UnitAwareInterpolatedTabularBivariateDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{

private:

  // The parent distribution type
  typedef UnitAwareInterpolatedTabularBivariateDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;

  // The base univariate distribution type (UnitAwareTabularOneDDist)
  typedef typename ParentType::BaseUnivariateDistributionType BaseUnivariateDistributionType;

  // Typedef for QuantityTraits<double>
  typedef typename ParentType::QT QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename ParentType::PIQT PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename ParentType::SIQT SIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename ParentType::ISIQT ISIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef typename ParentType::DQT DQT;

  // The CDF interpolation policy
  typedef typename CDFInterpolationHelper<typename TwoDInterpPolicy::SecondIndepVarProcessingTag,typename TwoDInterpPolicy::FirstIndepVarProcessingTag>::CDFInterpPolicy CDFInterpPolicy;
  
public:
  
  //! The primary independent quantity type
  typedef typename ParentType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename ParentType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename ParentType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The dependent quantity type
  typedef typename ParentType::DepQuantity DepQuantity;

  //! The distribution type
  typedef typename ParentType::DistributionType DistributionType;

  //! Constructor
  UnitAwareInterpolatedFullyTabularBivariateDistribution(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedFullyTabularBivariateDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareTabularUnivariateDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Raw constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB,
           template<typename T, typename... Args> class SubarrayB,
           template<typename T, typename... Args> class ArrayC,
           template<typename T, typename... Args> class SubarrayC>
  UnitAwareInterpolatedFullyTabularBivariateDistribution(
       const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
       const ArrayB<SubarrayB<SecondaryIndepQuantity> >& secondary_indep_grids,
       const ArrayC<SubarrayC<DepQuantity> >& dependent_values );

  //! Destructor
  ~UnitAwareInterpolatedFullyTabularBivariateDistribution()
  { /* ... */ }

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF 
  SecondaryIndepQuantity sampleSecondaryConditionalExact(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;
};

/*! \brief The interpolated fully tabular bivariate distribution 
 * (unit-agnostic)
 * \ingroup bivariate_distributions
 */
template<typename TwoDInterpPolicy> using InterpolatedFullyTabularBivariateDistribution =
  UnitAwareInterpolatedFullyTabularBivariateDistribution<TwoDInterpPolicy,void,void,void>;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InterpolatedFullyTabularBivariateDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularBivariateDistribution.hpp
//---------------------------------------------------------------------------//
