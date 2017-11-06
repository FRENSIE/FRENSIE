//---------------------------------------------------------------------------//
//!
//! \file   Utility_DiscreteDistribution.hpp
//! \author Alex Robinson
//! \brief  Discrete distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DISCRETE_DISTRIBUTION_HPP
#define UTILITY_DISCRETE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

/*! The unit-aware discrete distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit,typename DependentUnit>
class UnitAwareDiscreteDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>
{

private:

  // Typedef for base type
  typedef UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit> BaseType;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

public:

  //! This distribution type
  typedef UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Default Constructor
  UnitAwareDiscreteDistribution();

  //! Basic Constructor (potentially dangerous)
  UnitAwareDiscreteDistribution(
			const std::vector<double>& independent_values,
			const std::vector<double>& dependent_values,
			const bool interpret_dependent_values_as_cdf = false );

  //! CDF constructor
  template<typename InputIndepQuantity>
  UnitAwareDiscreteDistribution(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<double>& cdf_values );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareDiscreteDistribution(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<InputDepQuantity>& dependent_quantities );


  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareDiscreteDistribution( const UnitAwareDiscreteDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareDiscreteDistribution fromUnitlessDistribution( const UnitAwareDiscreteDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareDiscreteDistribution& operator=( const UnitAwareDiscreteDistribution& dist_instance );

  //! Destructor
  ~UnitAwareDiscreteDistribution()
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

  //! Return a random sample and sampled index from the distribution
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const override;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the distribution in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
			    const double random_number,
			    const IndepQuantity max_indep_var ) const override;


  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const override;

  //! Return the distribution type name
  static std::string typeName( const bool verbose_name,
                               const bool use_template_params = false,
                               const std::string& delim = std::string() );

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
  bool operator==( const UnitAwareDiscreteDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareDiscreteDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareDiscreteDistribution( const UnitAwareDiscreteDistribution<void,void>& unitless_dist_instance, int );

  //! Return the distribution type name
  std::string getDistributionTypeName( const bool verbose_name,
                                       const bool lowercase ) const override;

  // Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      unsigned& sampled_bin_index ) const;

  // Initialize the distribution
  void initializeDistribution(
			  const std::vector<double>& independent_values,
			  const std::vector<double>& dependent_values,
			  const bool interpret_dependent_values_as_cdf );

  // Initialize the distribution from a cdf
  template<typename InputIndepQuantity>
  void initializeDistributionFromCDF(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<double>& cdf_values );

  // Initialize the distribution
  template<typename InputIndepQuantity,typename InputDepQuantity>
  void initializeDistribution(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<InputDepQuantity>& dependent_quantities );

  // Reconstruct original distribution
  void reconstructOriginalDistribution(
		     std::vector<IndepQuantity>& independent_quantities,
		     std::vector<DepQuantity>& dependent_quantities ) const;

  // Reconstruct original distribution w/o units
  void reconstructOriginalUnitlessDistribution(
			      std::vector<double>& independent_values,
			      std::vector<double>& dependent_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
		                 const std::vector<double>& unitless_values,
				 std::vector<Quantity>& quantities );

  // Set the independent values
  static void extractIndependentValues( const Utility::Variant& indep_data,
                                        std::vector<double>& independent_values );

  // Set the independent values
  static void extractIndependentValuesFromNode( const Utility::PropertyTree& indep_data,
                                                std::vector<double>& independent_values );

  // Set the dependent values
  static void extractDependentValues( const Utility::Variant& dep_data,
                                      std::vector<double>& dependent_values );

  // Set the dependent values
  static void extractDependentValuesFromNode( const Utility::PropertyTree& dep_data,
                                              std::vector<double>& dependent_values );

  // Verify that the values are valid
  static void verifyValidValues( const std::vector<double>& independent_values,
                                 const std::vector<double>& dependent_values );

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
  friend class UnitAwareDiscreteDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = DISCRETE_DISTRIBUTION;

  // The distribution (first = independent value, second = CDF)
  std::vector<std::pair<IndepQuantity,double> > d_distribution;

  // The distribution normalization constant
  DepQuantity d_norm_constant;
};

/*! The discrete distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareDiscreteDistribution<void,void> DiscreteDistribution;

/*! Partial specialization of Utility::TypeNameTraits for unit aware
 * discrete distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<typename IndependentUnit,typename DependentUnit>
struct TypeNameTraits<UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::typeName( true, true  );
  }
};

/*! Specialization of Utility::TypeNameTraits for discrete distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<DiscreteDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return DiscreteDistribution::typeName( true, false ); }
};
  
} // end Utility namespace

BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwareDiscreteDistribution, 0 );
BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( DiscreteDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_DiscreteDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_DISCRETE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution.hpp
//---------------------------------------------------------------------------//
