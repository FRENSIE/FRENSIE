//---------------------------------------------------------------------------//
//!
//! \file   Utility_WattDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Watt distribution class declaration. Modified by Alex Robinson
//!         to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WATT_DISTRIBUTION_HPP
#define UTILITY_WATT_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_OneDDistributionPropertyTreeConverter.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

/*! Watt distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareWattDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
                                  private OneDDistributionPropertyTreeConverter<UnitAwareWattDistribution<IndependentUnit,DependentUnit>,UnitAwareOneDDistribution<IndependentUnit,DependentUnit> >
{
  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

  // Typedef for base type
  typedef UnitAwareOneDDistribution<IndependentUnit,DependentUnit> BaseType;

  // The distribution multiplier quantity type
  typedef typename BaseType::DepQuantity DistMultiplierQuantity;

  // The distribution normalization quantity type
  typedef typename BaseType::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistMultiplierQuantity>
  typedef QuantityTraits<DistMultiplierQuantity> DMQT;

public:

  //! The distribution type
  typedef UnitAwareWattDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputInverseIndepQuantity = InverseIndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareWattDistribution(
                  const InputIndepQuantityA incident_energy =
                  ThisType::getDefaultIncidentEnergy<InputIndepQuantityA>(),
                  const InputIndepQuantityB a_parameter =
                  ThisType::getDefaultAParameter<InputIndepQuantityB>(),
                  const InputInverseIndepQuantity b_parameter =
                  ThisType::getDefaultBParameter<InputInverseIndepQuantity>(),
                  const InputIndepQuantityC restriction_energy =
                  ThisType::getDefaultRestrictionEnergy<InputIndepQuantityC>(),
                  const double constant_multiplier =
                  ThisType::getDefaultConstantMultiplier() );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareWattDistribution( const UnitAwareWattDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareWattDistribution fromUnitlessDistribution( const UnitAwareWattDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareWattDistribution& operator=( const UnitAwareWattDistribution& dist_instance );

  //! Destructor
  ~UnitAwareWattDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Return a sample from the distribution
  IndepQuantity sample() const override;

  //! Return a sample from the distribution
  static IndepQuantity sample( const IndepQuantity incident_energy,
			       const IndepQuantity a_parameter,
			       const InverseIndepQuantity b_parameter,
			       const IndepQuantity restriction_energy );

  //! Return a random sample from the distribution and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
                                        const IndepQuantity incident_energy,
                                        const IndepQuantity a_parameter,
                                        const InverseIndepQuantity b_parameter,
                                        const IndepQuantity restriction_energy,
                                        DistributionTraits::Counter& trials );

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const override;

  //! Return the distribution type name
  static std::string typeName( const bool verbose_name,
                               const bool use_template_params = false,
                               const std::string& delim = std::string() );

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

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
  bool operator==( const UnitAwareWattDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareWattDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareWattDistribution( const UnitAwareWattDistribution<void,void>& unitless_dist_instance, int );

  //! Return the distribution type name
  std::string getTypeNameImpl( const bool verbose_name ) const override;

  //! Process the data that was extracted the stream
  void fromStreamImpl( VariantList& distribution_data ) override;

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default incident energy
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultIncidentEnergy()
  { return QuantityTraits<InputIndepQuantity>::one(); }

  //! Get the default a parameter
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultAParameter()
  { return QuantityTraits<InputIndepQuantity>::one(); }

  //! Get the default b parameter
  template<typename InputInverseIndepQuantity>
  static InputInverseIndepQuantity getDefaultBParameter()
  { return QuantityTraits<InputInverseIndepQuantity>::one(); }

  //! Get the default restriction energy
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultRestrictionEnergy()
  { return QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default constant multiplier
  static double getDefaultConstantMultiplier()
  { return 1.0; }

private:

  // Calculate the normalization constant of the distribution
  void calculateNormalizationConstant();

  // Verify that the shape parameters are valid
  static void verifyValidShapeParameters( IndepQuantity& incident_energy,
                                          IndepQuantity& a_parameter,
                                          InverseIndepQuantity& b_parameter,
                                          IndepQuantity& restriction_energy,
                                          DistMultiplierQuantity& multiplier );

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
  friend class UnitAwareWattDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = WATT_DISTRIBUTION;

  // The incident energy value key (used in property trees)
  static const std::string s_incident_energy_value_key;

  // The incident energy min match string (used when reading property trees)
  static const std::string s_incident_energy_value_min_match_string;

  // The a parameter value key (used in property trees)
  static const std::string s_a_parameter_value_key;

  // The a parameter min match string (used when reading property trees)
  static const std::string s_a_parameter_value_min_match_string;

  // The b parameter value key (used in property trees)
  static const std::string s_b_parameter_value_key;

  // The b parameter min match string (used when reading property trees)
  static const std::string s_b_parameter_value_min_match_string;

  // The restriction energy value key (used in property trees)
  static const std::string s_restriction_energy_value_key;

  // The restriction energy min match string (used when reading prop. trees)
  static const std::string s_restriction_energy_value_min_match_string;

  // The distribution multiplier value key (used in property trees)
  static const std::string s_multiplier_value_key;

  // The distribution multiplier min match string (used when reading prop. trees)
  static const std::string s_multiplier_value_min_match_string;

  // The incident neutron energy of the distribution
  IndepQuantity d_incident_energy;

  // The a_parameter of the distribution
  IndepQuantity d_a_parameter;

  // The b_parameter of the distribution
  InverseIndepQuantity d_b_parameter;

  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;

  // The distribution multiplier
  DistMultiplierQuantity d_multiplier;

  // The distribution normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The Watt distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareWattDistribution<void,void> WattDistribution;

/*! Partial specialization of Utility::TypeNameTraits for unit aware
 * watt distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<typename IndependentUnit,typename DependentUnit>
struct TypeNameTraits<UnitAwareWattDistribution<IndependentUnit,DependentUnit> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return UnitAwareWattDistribution<IndependentUnit,DependentUnit>::typeName( true, true  );
  }
};

/*! Specialization of Utility::TypeNameTraits for watt distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<WattDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return WattDistribution::typeName( true, false ); }
};

} // end Utility namespace

BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwareWattDistribution, 0 );
BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( WattDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_WattDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_WATT_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_WattDistribution.hpp
//---------------------------------------------------------------------------//
