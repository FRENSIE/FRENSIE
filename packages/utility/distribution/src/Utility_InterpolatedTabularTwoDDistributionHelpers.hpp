//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularTwoDDistributionHelpers.hpp
//! \author Alex Robinson
//! \brief  The interpolated tabular two-dimensional dist. helper class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_HPP
#define UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_HPP

// FRENSIE Includes
#include "Utility_PartiallyTabularTwoDDistribution.hpp"
#include "Utility_FullyTabularTwoDDistribution.hpp"

namespace Utility{

//! The interpolated tabular two-dimensional dist. base implementation class
template<typename TwoDInterpPolicy, typename Distribution>
class UnitAwareInterpolatedTabularTwoDDistributionImplBase : public Distribution{

protected:

  // The parent distribution type
  typedef Distribution ParentType;

  // The base one-dimensional distribution type
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

  // Typedef for QuantityTrais<double>
  typedef typename ParentType::QT QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename ParentType::PIQT PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename ParentType::SIQT SIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename ParentType::ISIQT ISIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef typename ParentType::DQT DQT;

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
  UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                                        const DistributionType& distribution );
  
  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedTabularTwoDDistributionImplBase(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions );
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareInterpolatedTabularTwoDDistributionImplBase()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditional(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const;

  //! Return the upper bound of the conditional distribution
  SecondaryIndepQuantity getUpperBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return the lower bound of the conditional distribution
  SecondaryIndepQuantity getLowerBoundOfConditionalIndepVar(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Test if the distribution is continuous in the primary dimension
  bool isPrimaryDimensionContinuous() const;
};

//! The interpolated tabular two-d dist. impl. class (fully tabular)
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit,
         bool FullyTabular>
class UnitAwareInterpolatedTabularTwoDDistributionImpl : public UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{

private:

  // The parent distribution type
  typedef UnitAwareInterpolatedTabularTwoDDistributionImplBase<UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;

  // The base one-dimensional distribution type
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

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
  UnitAwareInterpolatedTabularTwoDDistributionImpl(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedTabularTwoDDistributionImpl(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareInterpolatedTabularTwoDDistributionImpl()
  { /* ... */ }

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF 
  SecondaryIndepQuantity sampleSecondaryConditionalExact(
                    const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const;

  //! Return a random sample and record the number of trials
  SecondaryIndepQuantity sampleSecondaryConditionalExactAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndex(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& sampled_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;
};

//! The interpolated tabular two-d dist. impl. class (partiall tabular)
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedTabularTwoDDistributionImpl<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit,false> : public UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,UnitAwarePartiallyTabularTwoDDistributionImpl<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{

private:

  // The parent distribution type
  typedef UnitAwareInterpolatedTabularTwoDDistributionImplBase<UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;

  // The base one-dimensional distribution type
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

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
  UnitAwareInterpolatedTabularTwoDDistributionImpl(
                                         const DistributionType& distribution )
    : ParentType( distribution )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedTabularTwoDDistributionImpl(
                const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                const ArrayB<std::shared_ptr<const BaseOneDDistributionType> >&
                secondary_distributions )
    : ParentType( primary_indep_grid, secondary_distributions )
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareInterpolatedTabularTwoDDistributionImpl()
  { /* ... */ }
};
  
} // end Utility namespace

#endif // end UTILITY_INTERPOLATED_TABULAR_TWO_D_DISTRIBUTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularTwoDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
