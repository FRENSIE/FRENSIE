//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution.hpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP
#define TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Vector.hpp"

namespace Utility{

/*! The unit-aware equiprobable bin distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareEquiprobableBinDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>					     
{

private:

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

public:

  //! This distribution type
  typedef UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

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

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      unsigned& sampled_bin_index ) const;

  // Initialize the distribution
  void initializeDistribution( const std::vector<double>& bin_boundaries );

  // Initialize the distribution
  template<typename InputIndepQuantity>
  void initializeDistribution(
		    const std::vector<InputIndepQuantity>& bin_boundaries );

  // Verify that the distribution type is correct
  static void verifyDistributionType( const Utility::Variant& type_data );

  // Set the bin boundaries
  static void extractBinBoundaries( const Utility::Variant& bin_boundary_data,
                                    std::vector<double>& bin_boundaries );

  // Set the bin boundaries
  static void extractBinBoundaries(
                                const Utility::PropertyTree& bin_boundary_data,
                                std::vector<double>& bin_boundaries );

  // Verify that the bin boundaries are valid
  static void verifyValidBinBoundaries(
                                   const std::vector<double>& bin_boundaries );

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareEquiprobableBinDistribution;

  // The disribution type
  static const OneDDistributionType distribution_type =
    EQUIPROBABLE_BIN_DISTRIBUTION;

  // The distribution
  std::vector<IndepQuantity> d_bin_boundaries;
};

/*! The equiprobable bin distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareEquiprobableBinDistribution<void,void> EquiprobableBinDistribution;

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_EquiprobableBinDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end EQUIPROBABLE_BIN_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution.hpp
//---------------------------------------------------------------------------//
