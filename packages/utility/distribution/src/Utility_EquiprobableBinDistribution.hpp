//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution.hpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_HPP
#define UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

/*! The unit-aware equiprobable bin distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareEquiprobableBinDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>
{
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
  typedef UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareEquiprobableBinDistribution();

  //! Basic constructor (potentially dangerous)
  explicit UnitAwareEquiprobableBinDistribution( const std::vector<double>& bin_boundaries);

  //! Constructor
  template<typename InputIndepQuantity>
  explicit UnitAwareEquiprobableBinDistribution( const std::vector<InputIndepQuantity>& bin_boundaries );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareEquiprobableBinDistribution(
      const UnitAwareEquiprobableBinDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareEquiprobableBinDistribution fromUnitlessDistribution( const UnitAwareEquiprobableBinDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareEquiprobableBinDistribution& operator=(
		   const UnitAwareEquiprobableBinDistribution& dist_instance );

  //! Destructor
  ~UnitAwareEquiprobableBinDistribution()
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

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample and sampled index from the corresponding CDF
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const override;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
                            const double random_number,
			    const IndepQuantity max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return a random sample from the distribution and the sampled index
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
  bool operator==( const UnitAwareEquiprobableBinDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareEquiprobableBinDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareEquiprobableBinDistribution( const UnitAwareEquiprobableBinDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  //! Return the distribution type name
  std::string getDistributionTypeName( const bool verbose_name,
                                       const bool lowercase ) const override;

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      unsigned& sampled_bin_index ) const;

  // Initialize the distribution
  void initializeDistribution( const std::vector<double>& bin_boundaries );

  // Initialize the distribution
  template<typename InputIndepQuantity>
  void initializeDistribution(
		    const std::vector<InputIndepQuantity>& bin_boundaries );

  // Verify that the bin boundaries are valid
  static void verifyValidBinBoundaries(
                                   const std::vector<double>& bin_boundaries );

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
  friend class UnitAwareEquiprobableBinDistribution;

  // The disribution type
  static const OneDDistributionType distribution_type =
    EQUIPROBABLE_BIN_DISTRIBUTION;

  // The bin boundary values key (used in property trees)
  static const std::string s_bin_boundary_values_key;

  // The bin boundary values min match string (used when reading prop. trees)
  static const std::string s_bin_boundary_min_match_string;

  // The distribution
  std::vector<IndepQuantity> d_bin_boundaries;
};

/*! The equiprobable bin distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareEquiprobableBinDistribution<void,void> EquiprobableBinDistribution;

/*! Partial specialization of Utility::TypeNameTraits for unit aware
 * equiprobable bin distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<typename IndependentUnit,typename DependentUnit>
struct TypeNameTraits<UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::typeName( true, true  );
  }
};

/*! Specialization of Utility::TypeNameTraits for equiprobable bin distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<EquiprobableBinDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return EquiprobableBinDistribution::typeName( true, false ); }
};

} // end Utility namespace

BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwareEquiprobableBinDistribution, 0 );
BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( EquiprobableBinDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_EquiprobableBinDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution.hpp
//---------------------------------------------------------------------------//
