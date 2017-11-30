//---------------------------------------------------------------------------//
//!
//! \file   Utility_MaxwellFissionDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution class declaration. Modified by Alex
//!         Robison to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP
#define UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>
#include <boost/units/dimensionless_type.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_OneDDistributionPropertyTreeConverter.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

/*! The unit-aware Maxwell fission distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareMaxwellFissionDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
                                            private OneDDistributionPropertyTreeConverter<UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>,UnitAwareOneDDistribution<IndependentUnit,DependentUnit> >
{
  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

  // Typedef for base type
  typedef UnitAwareOneDDistribution<IndependentUnit,DependentUnit> BaseType;

  // The distribution multiplier unit traits typedef
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<1,-2>::type>::type> DistMultiplierUnitTraits;

  // The distribution multiplier quantity type
  typedef typename DistMultiplierUnitTraits::template GetQuantityType<double>::type DistMultiplierQuantity;

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

  //! This distribution type
  typedef UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareMaxwellFissionDistribution(
                 const InputIndepQuantityA incident_energy =
                 ThisType::getDefaultIncidentEnergy<InputIndepQuantityA>(),
                 const InputIndepQuantityB nuclear_temperature =
                 ThisType::getDefaultNuclearTemperature<InputIndepQuantityB>(),
                 const InputIndepQuantityC restriction_energy =
                 ThisType::getDefaultRestrictionEnergy<InputIndepQuantityC>(),
                 const double constant_multiplier =
                 ThisType::getDefaultConstantMultiplier() );
  
  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareMaxwellFissionDistribution( const UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareMaxwellFissionDistribution fromUnitlessDistribution( const UnitAwareMaxwellFissionDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareMaxwellFissionDistribution& operator=( const UnitAwareMaxwellFissionDistribution& dist_instance );

  //! Destructor
  ~UnitAwareMaxwellFissionDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const IndepQuantity incident_energy,
			       const IndepQuantity nuclear_temperature,
			       const IndepQuantity restriction_energy );

  //! Return a random sample from the distribution and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
                                       const IndepQuantity incident_energy,
                                       const IndepQuantity nuclear_temperature,
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
  bool operator==( const UnitAwareMaxwellFissionDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareMaxwellFissionDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareMaxwellFissionDistribution( const UnitAwareMaxwellFissionDistribution<void,void>& unitless_dist_instance, int );

  //! Return the distribution type name
  std::string getTypeNameImpl( const bool verbose_name ) const override;

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default incident energy
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultIncidentEnergy()
  { return QuantityTraits<InputIndepQuantity>::one(); }

  //! Get the default nuclear temperature
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultNuclearTemperature()
  { return QuantityTraits<InputIndepQuantity>::one(); }

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
                                          IndepQuantity& nuclear_temp,
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
  friend class UnitAwareMaxwellFissionDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = MAXWELLFISSION_DISTRIBUTION;

  // The incident energy value key (used in property trees)
  static const std::string s_incident_energy_value_key;

  // The incident energy min match string (used when reading property trees)
  static const std::string s_incident_energy_value_min_match_string;

  // The nuclear temperature value key (used in property trees)
  static const std::string s_nuclear_temp_value_key;

  // The nuclear temperature min match string (used when reading prop. trees)
  static const std::string s_nuclear_temp_value_min_match_string;

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

  // The nuclear temperature of the distribution
  IndepQuantity d_nuclear_temperature;

  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;

  // The distribution multiplier
  DistMultiplierQuantity d_multiplier;

  // The distribution normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The Maxwell fission distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareMaxwellFissionDistribution<void,void> MaxwellFissionDistribution;

/*! Partial specialization of Utility::TypeNameTraits for unit aware
 * maxwell fission distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<typename IndependentUnit,typename DependentUnit>
struct TypeNameTraits<UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::typeName( true, true  );
  }
};

/*! Specialization of Utility::TypeNameTraits for maxwell fission distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<MaxwellFissionDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return MaxwellFissionDistribution::typeName( true, false ); }
};

} // end Utility namespace

BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwareMaxwellFissionDistribution, 0 );
BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( MaxwellFissionDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_MaxwellFissionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution.hpp
//---------------------------------------------------------------------------//
