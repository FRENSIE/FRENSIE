//---------------------------------------------------------------------------//
//!
//! \file   Utility_HybridElasticDistribution.hpp
//! \author Luke Kersting
//! \brief  Hybrid elastic distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HYBRID_ELASTIC_HPP
#define UTILITY_HYBRID_ELASTIC_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! The hybrid elastic distribution class declaration
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
class UnitAwareHybridElasticDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
                                     public ParameterListCompatibleObject<UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> >
{

  // Only allow construction when the independent unit dimensionless
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, dimensionless_type );

private:

  // The unnormalized cdf quantity
  typedef typename QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

  // The slope unit traits
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::InverseUnit>::type> SlopeUnitTraits;

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

  // Typedef for QuantityTraits<UnnormCDFQuantity>
  typedef QuantityTraits<UnnormCDFQuantity> UCQT;

public:

  //! This distribution type
  typedef UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareHybridElasticDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareHybridElasticDistribution(
                    const Teuchos::Array<double>& independent_cutoff_values,
                    const Teuchos::Array<double>& dependent_cutoff_values,
                    const Teuchos::Array<double>& independent_discrete_values,
                    const Teuchos::Array<double>& dependent_discrete_values,
                    const double& cutoff_angle_cosine,
                    const double& cutoff_cross_section_ratio );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareHybridElasticDistribution(
        const Teuchos::Array<InputIndepQuantity>& independent_cutoff_values,
        const Teuchos::Array<InputDepQuantity>& dependent_cutoff_values,
        const Teuchos::Array<InputIndepQuantity>& independent_discrete_values,
        const Teuchos::Array<InputDepQuantity>& dependent_discrete_values,
        const InputIndepQuantity& cutoff_angle_cosine,
        const double& cutoff_cross_section_ratio );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareHybridElasticDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareHybridElasticDistribution fromUnitlessDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareHybridElasticDistribution& operator=(
                           const UnitAwareHybridElasticDistribution& dist_instance );

  //! Destructor
  ~UnitAwareHybridElasticDistribution()
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

  //! Return the cutoff bound of the distribution independent variable
  IndepQuantity getCutoffBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Return the cutoff cross section ratio for the distribution
  double getCutoffCrossSectionRatio() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwareHybridElasticDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareHybridElasticDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int );

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

  // Initialize the distribution
  void initializeDistributionsFromRawData(
                    const Teuchos::Array<double>& independent_cutoff_values,
                    const Teuchos::Array<double>& dependent_cutoff_values,
                    const Teuchos::Array<double>& independent_discrete_values,
                    const Teuchos::Array<double>& dependent_discrete_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeCutoffDistribution(
                  const Teuchos::Array<InputIndepQuantity>& independent_values,
                  const Teuchos::Array<InputDepQuantity>& dependent_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDiscreteDistribution(
                  const Teuchos::Array<InputIndepQuantity>& independent_values,
                  const Teuchos::Array<InputDepQuantity>& dependent_values );

  // Reconstruct original distributions
  void reconstructOriginalDistributions(
                 Teuchos::Array<IndepQuantity>& independent_cutoff_values,
                 Teuchos::Array<DepQuantity>& dependent_cutoff_values,
                 Teuchos::Array<IndepQuantity>& independent_discrete_values,
                 Teuchos::Array<DepQuantity>& dependent_discrete_values ) const;

  // Reconstruct original distributions w/o units
  void reconstructOriginalUnitlessDistributions(
                      Teuchos::Array<double>& independent_cutoff_values,
                      Teuchos::Array<double>& dependent_cutoff_values,
                      Teuchos::Array<double>& independent_discrete_values,
                      Teuchos::Array<double>& dependent_discrete_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
                                 const Teuchos::Array<double>& unitless_values,
                                 Teuchos::Array<Quantity>& quantitites );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
                                      unsigned& sampled_bin_index ) const;

  // Return a random sample of the moment preserving discrete distribution using the random number and record the bin index
  IndepQuantity sampleDiscrete( double random_number,
                                unsigned& sampled_bin_index ) const;

  // Return a random sample of the cutoff tabular distribution using the random number and record the bin index
  IndepQuantity sampleCutoff( double random_number,
                              unsigned& sampled_bin_index ) const;

  // All possible instantiations are friends
  template<typename FriendInterpolationPolicy,
           typename FriendIndepUnit,
           typename FriendDepUnit>
  friend class UnitAwareHybridElasticDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = HYBRID_ELASTIC_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf,
  // fourth = pdf slope): both the pdf and cdf are left unnormalized to
  // prevent altering the grid with log interpolation
  typedef Teuchos::Array<Quad<IndepQuantity,UnnormCDFQuantity,DepQuantity,SlopeQuantity> > DistributionArray;
  DistributionArray d_cutoff_distribution;

  // The distribution (first = independent value, second = CDF)
  Teuchos::Array<Pair<IndepQuantity,double> > d_discrete_distribution;

  // The discrete normalization constant
  DistNormQuantity d_discrete_norm_constant;

  // The cutoff normalization constant
  DistNormQuantity d_cutoff_norm_constant;

  // The unormalized CDF value a the cutoff angle cosine
  UnnormCDFQuantity d_max_cutoff_cdf;

  // The cutoff angle cosine between the tabular and discrete distributions
  IndepQuantity d_cutoff_mu;

  // The ratio of the cutoff cross section to the total cross section at the energy of the distribution
  double d_cutoff_cross_section_ratio;

  /* Parameter for rescaling the random number to sample the
   * moment preserving discrete peak ( 1/(1 - cutoff_cs_ratio) )
   */
  double d_scaling_parameter;
};

/*! The hybrid elastic distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy> using HybridElasticDistribution =
  UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::HybridElasticDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename InterpolationPolicy>
class TypeNameTraits<Utility::HybridElasticDistribution<InterpolationPolicy> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Hybrid Elastic " << InterpolationPolicy::name() << " Distribution";

    return iss.str();
  }
  static std::string concreteName(
            const Utility::HybridElasticDistribution<InterpolationPolicy>& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareHybridElasticDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files
 */
template<typename InterpolationPolicy, typename U, typename V>
class TypeNameTraits<Utility::UnitAwareHybridElasticDistribution<InterpolationPolicy,U,V> >
{
  public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Unit-Aware Hybrid Elastic " << InterpolationPolicy::name()
        << " Distribution ("
        << Utility::UnitTraits<U>::symbol() << ","
        << Utility::UnitTraits<V>::symbol() << ")";

    return iss.str();
  }
  static std::string concreteName( const Utility::UnitAwareHybridElasticDistribution<InterpolationPolicy,U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "Utility_HybridElasticDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HYBRID_ELASTIC_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HybridElasticDistribution.hpp
//---------------------------------------------------------------------------//endent_discrete_values,
