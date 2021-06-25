//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramDistribution.hpp
//! \author Alex Robinson
//! \brief  Histogram distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The unit-aware histogram distribution class
 * \ingroup univariate_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareHistogramDistribution : public UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Typedef for base type
  typedef UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // The unnormalized cdf quantity
  typedef typename QuantityTraits<typename BaseType::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

  // The distribution normalization quantity type
  typedef typename BaseType::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistNormQuantity>
  typedef QuantityTraits<DistNormQuantity> DNQT;

public:

  //! This distribution type
  typedef UnitAwareHistogramDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Basic constructor (potentially dangerous)
  UnitAwareHistogramDistribution( const std::vector<double>& bin_boundaries =
                                  ThisType::getDefaultBinBoundaries<double>(),
				  const std::vector<double>& bin_values =
                                  ThisType::getDefaultBinValues<double>(),
				  const bool interpret_dependent_values_as_cdf =
                                  false );

  // Basic view constructor
  UnitAwareHistogramDistribution(
                        const Utility::ArrayView<const double>& bin_boundaries,
                        const Utility::ArrayView<const double>& bin_values,
                        const bool interpret_dependent_values_as_cdf = false );

  //! CDF constructor
  template<typename InputIndepQuantity>
  UnitAwareHistogramDistribution(
		      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<double>& cdf_values );

  //! CDF view constructor
  template<typename InputIndepQuantity>
  UnitAwareHistogramDistribution(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const double>& cdf_values );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareHistogramDistribution(
                      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<InputDepQuantity>& bin_values );

  //! View constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareHistogramDistribution(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const InputDepQuantity>& bin_values );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareHistogramDistribution( const UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareHistogramDistribution fromUnitlessDistribution( const UnitAwareHistogramDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareHistogramDistribution& operator=(
			 const UnitAwareHistogramDistribution& dist_instance );

  //! Destructor
  ~UnitAwareHistogramDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample and bin index from the distribution
  IndepQuantity sampleAndRecordBinIndex( size_t& sampled_bin_index ) const override;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
			    const double random_number,
			    const IndepQuantity max_indep_var ) const override;

  //! Return a random sample from the corresponding CDF in a sub range with a minimum
  IndepQuantity sampleInSubrange( const IndepQuantity min_indep_var,
                                  const IndepQuantity max_indep_var ) const;

    //! Return a sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
			    const double random_number,
			    const IndepQuantity min_indep_var,
          const IndepQuantity max_indep_var ) const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  UnivariateDistributionType getDistributionType() const override;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwareHistogramDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareHistogramDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareHistogramDistribution( const UnitAwareHistogramDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default bin boundaries
  template<typename InputIndepQuantity>
  static std::vector<InputIndepQuantity> getDefaultBinBoundaries()
  { return std::vector<InputIndepQuantity>({Utility::QuantityTraits<InputIndepQuantity>::zero(),Utility::QuantityTraits<InputIndepQuantity>::one()}); }
  
  //! Get the default bin values
  template<typename InputDepQuantity>
  static std::vector<InputDepQuantity> getDefaultBinValues()
  { return std::vector<InputDepQuantity>({Utility::QuantityTraits<InputDepQuantity>::one()}); }

private:

  // Initialize the distribution
  void initializeDistribution(
                        const Utility::ArrayView<const double>& bin_boundaries,
                        const Utility::ArrayView<const double>& bin_values,
                        const bool interpret_dependent_values_as_cdf );

  // Initialize the distribution from a cdf
  template<typename InputIndepQuantity>
  void initializeDistributionFromCDF(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const double>& cdf_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDistribution(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const InputDepQuantity>& bin_values );

  // Reconstruct original distribution
  void reconstructOriginalDistribution(
			 std::vector<IndepQuantity>& bin_boundaries,
			 std::vector<DepQuantity>& bin_values ) const;

  // Reconstruct original distribution w/o units
  void reconstructOriginalUnitlessDistribution(
			      std::vector<double>& bin_boundaries,
			      std::vector<double>& bin_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
                       const Utility::ArrayView<const double>& unitless_values,
                       std::vector<Quantity>& quantities );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      size_t& sampled_bin_index ) const;

  // Verify that the values are valid
  template<typename InputIndepQuantity, typename InputDepQuantity>
  static void verifyValidValues(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values,
        const bool cdf_bin_values );

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareHistogramDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type = HISTOGRAM_DISTRIBUTION;

  // The distribution (first = bin_min, second = bin_PDF, third = bin_CDF)
  // Note: The bin_CDF value is the value of the CDF at the lower bin boundary
  typedef std::vector<std::tuple<IndepQuantity,DepQuantity,UnnormCDFQuantity> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The histogram distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
typedef UnitAwareHistogramDistribution<void,void> HistogramDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwareHistogramDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_STANDARD_KEY( HistogramDistribution );

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_HistogramDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution.hpp
//---------------------------------------------------------------------------//
