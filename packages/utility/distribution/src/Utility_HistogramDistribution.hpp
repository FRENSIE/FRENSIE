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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The unit-aware histogram distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareHistogramDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>
{

private:

  // Typedef for base type
  typedef UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit> BaseType;

  // The unnormalized cdf quantity
  typedef typename QuantityTraits<typename BaseType::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

  // The distribution normalization quantity type
  typedef typename BaseType::DistNormQuantity DistNormQuantity;

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
  typedef UnitAwareHistogramDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareHistogramDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareHistogramDistribution( const std::vector<double>& bin_boundaries,
				  const std::vector<double>& bin_values,
				  const bool interpret_dependent_values_as_cdf = false );

  //! CDF constructor
  template<typename InputIndepQuantity>
  UnitAwareHistogramDistribution(
		      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<double>& cdf_values );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareHistogramDistribution(
		      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<InputDepQuantity>& bin_values );

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
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const override;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
			    const double random_number,
			    const IndepQuantity max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const override;

  //! Return the distribution type name
  static std::string getDistributionTypeName( const bool verbose_name = true,
                                              const bool lowercase = false );

  //! Check if the type name matches the distribution type name
  static bool doesTypeNameMatch( const std::string type_name );

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is, const std::string& delims ) override;

  //! Method for initializing the object from an input stream
  using IStreamableObject::fromStream;

  //! Method for converting the type to a property tree
  Utility::PropertyTree toPropertyTree( const bool inline_data ) const override;

  //! Method for converting the type to a property tree
  using PropertyTreeCompatibleObject::toPropertyTree;

  //! Method for initializing the object from a property tree
  void fromPropertyTree( const Utility::PropertyTree& node,
                         std::vector<std::string>& unused_children ) override;

  //! Method for converting to a property tree
  using PropertyTreeCompatibleObject::fromPropertyTree;

  //! Equality comparison operator
  bool operator==( const UnitAwareEquiprobableBinDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareEquiprobableBinDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareHistogramDistribution( const UnitAwareHistogramDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Initialize the distribution
  void initializeDistribution( const std::vector<double>& bin_boundaries,
			       const std::vector<double>& bin_values,
			       const bool interpret_dependent_values_as_cdf );

  // Initialize the distribution from a cdf
  template<typename InputIndepQuantity>
  void initializeDistributionFromCDF(
		  const std::vector<InputIndepQuantity>& bin_boundaries,
		  const std::vector<double>& cdf_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDistribution(
		  const std::vector<InputIndepQuantity>& bin_boundaries,
		  const std::vector<InputDepQuantity>& bin_values );

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
		                 const std::vector<double>& unitless_values,
				 std::vector<Quantity>& quantities );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      unsigned& sampled_bin_index ) const;

  // Verify that the distribution type is discrete
  static void verifyDistributionType( const Utility::Variant& type_data );

  // Set the independent values
  static void extractIndependentValues( const Utility::Variant& indep_data,
                                        std::vector<double>& independent_values );

  // Set the independent values
  static void extractIndependentValues( const Utility::PropertyTree& indep_data,
                                        std::vector<double>& independent_values );

  // Set the dependent values
  static void extractDependentValues( const Utility::Variant& dep_data,
                                      std::vector<double>& dependent_values );

  // Set the dependent values
  static void extractDependentValues( const Utility::PropertyTree& dep_data,
                                      std::vector<double>& dependent_values );

  // Verify that the values are valid
  static void verifyValidValues( const std::vector<double>& independent_values,
                                 const std::vector<double>& dependent_values );

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareHistogramDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = HISTOGRAM_DISTRIBUTION;

  // The distribution (first = bin_min, second = bin_PDF, third = bin_CDF)
  // Note: The bin_CDF value is the value of the CDF at the lower bin boundary
  typedef std::vector<std::tuple<IndepQuantity,DepQuantity,UnnormCDFQuantity> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The histogram distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareHistogramDistribution<void,void> HistogramDistribution;

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_HistogramDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution.hpp
//---------------------------------------------------------------------------//
