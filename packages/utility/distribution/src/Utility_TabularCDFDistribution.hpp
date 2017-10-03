//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularCDFDistribution.hpp
//! \author Luke Kersting
//! \brief  Tabular CDF distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_CDF_DISTRIBUTION_HPP
#define UTILITY_TABULAR_CDF_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_CosineInterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! The interpolated distribution class declaration
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
class UnitAwareTabularCDFDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
                                     public ParameterListCompatibleObject<UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> >
{

private:

  //! The inverse interpolation policy
  typedef typename Utility::InverseInterpPolicy<InterpolationPolicy>::InterpPolicy InverseInterp;

  // The unnormalized cdf quantity
  typedef typename QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

  // The slope unit traits
  typedef UnitTraits<typename UnitTraits<DependentUnit>::InverseUnit> SlopeUnitTraits;

  // The slope quantity
  typedef typename SlopeUnitTraits::template GetQuantityType<double>::type SlopeQuantity;

  // The distribution normalization quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistNormQuantity>
  typedef QuantityTraits<DistNormQuantity> DNQT;

public:

  //! This distribution type
  typedef UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareTabularCDFDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareTabularCDFDistribution(
                        const Teuchos::Array<double>& independent_values,
                        const Teuchos::Array<double>& dependent_values,
                        const bool interpret_dependent_values_as_cdf = false );

  //! CDF constructor
  template<typename InputIndepQuantity>
  UnitAwareTabularCDFDistribution(
              const Teuchos::Array<InputIndepQuantity>& independent_values,
              const Teuchos::Array<double>& cdf_values );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareTabularCDFDistribution(
                  const Teuchos::Array<InputIndepQuantity>& independent_values,
                  const Teuchos::Array<InputDepQuantity>& dependent_values );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareTabularCDFDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareTabularCDFDistribution fromUnitlessDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareTabularCDFDistribution& operator=(
                           const UnitAwareTabularCDFDistribution& dist_instance );

  //! Destructor
  ~UnitAwareTabularCDFDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample and bin index from the distribution
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample from the distribution in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
                                     const double random_number,
                                     const IndepQuantity max_indep_var ) const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Return if the distribution was continuous from a CDF
  bool wasContructedFromCDF() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwareTabularCDFDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareTabularCDFDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

  //! Test if the independent variable is compatible with Lin processing
  bool isIndepVarCompatibleWithProcessingType(
                                        const LinIndepVarProcessingTag ) const;
  
  //! Test if the independent variable is compatible with Log processing
  bool isIndepVarCompatibleWithProcessingType(
                                        const LogIndepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Lin processing
  bool isDepVarCompatibleWithProcessingType(
                                          const LinDepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Log processing
  bool isDepVarCompatibleWithProcessingType(
                                          const LogDepVarProcessingTag ) const;

private:

  // Calculate the processed slope
  SlopeQuantity calculateProcessedSlope(
                                    const IndepQuantity indep_var_0,
                                    const IndepQuantity indep_var_1,
                                    const UnnormCDFQuantity cdf_var_0,
                                    const UnnormCDFQuantity cdf_var_1 ) const;

  // Initialize the distribution
  void initializeDistributionFromRawData(
                              const Teuchos::Array<double>& independent_values,
                              const Teuchos::Array<double>& dependent_values );

  // Initialize the distribution from a cdf
  template<typename InputIndepQuantity>
  void initializeDistributionFromCDF(
                  const Teuchos::Array<InputIndepQuantity>& independent_values,
                  const Teuchos::Array<double>& cdf_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDistribution(
                  const Teuchos::Array<InputIndepQuantity>& independent_values,
                  const Teuchos::Array<InputDepQuantity>& dependent_values );

  // Reconstruct original distribution
  void reconstructOriginalDistribution(
                         Teuchos::Array<IndepQuantity>& independent_values,
                         Teuchos::Array<DepQuantity>& dependent_values ) const;

  // Reconstruct original CDF distribution
  void reconstructOriginalCDFDistribution(
                         Teuchos::Array<IndepQuantity>& independent_values,
                         Teuchos::Array<double>& cdf_values ) const;

  // Reconstruct original distribution w/o units
  void reconstructOriginalUnitlessDistribution(
                              Teuchos::Array<double>& independent_values,
                              Teuchos::Array<double>& dependent_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
                                 const Teuchos::Array<double>& unitless_values,
                                 Teuchos::Array<Quantity>& quantitites );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
                                      unsigned& sampled_bin_index ) const;

  // All possible instantiations are friends
  template<typename FriendInterpolationPolicy,
           typename FriendIndepUnit,
           typename FriendDepUnit>
  friend class UnitAwareTabularCDFDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = TABULAR_CDF_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf,
  // fourth = pdf slope): both the pdf and cdf are left unnormalized to
  // prevent altering the grid with log interpolation
  typedef Teuchos::Array<Quad<IndepQuantity,UnnormCDFQuantity,DepQuantity,SlopeQuantity> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  DistNormQuantity d_norm_constant;

  // Interpret the dependent values as cdf values
  bool d_interpret_dependent_values_as_cdf;
};

/*! The tabular cdf distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy> using TabularCDFDistribution =
  UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::TabularCDFDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename InterpolationPolicy>
class TypeNameTraits<Utility::TabularCDFDistribution<InterpolationPolicy> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Tabular CDF " << InterpolationPolicy::name() << " Distribution";

    return iss.str();
  }
  static std::string concreteName(
            const Utility::TabularCDFDistribution<InterpolationPolicy>& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareTabularCDFDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files
 */
template<typename InterpolationPolicy, typename U, typename V>
class TypeNameTraits<Utility::UnitAwareTabularCDFDistribution<InterpolationPolicy,U,V> >
{
  public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Unit-Aware Tabular CDF " << InterpolationPolicy::name()
        << " Distribution ("
        << Utility::UnitTraits<U>::symbol() << ","
        << Utility::UnitTraits<V>::symbol() << ")";

    return iss.str();
  }
  static std::string concreteName( const Utility::UnitAwareTabularCDFDistribution<InterpolationPolicy,U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "Utility_TabularCDFDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TABULAR_CDF_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularCDFDistribution.hpp
//---------------------------------------------------------------------------//
