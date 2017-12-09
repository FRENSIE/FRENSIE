//---------------------------------------------------------------------------//
//!
//! \file   Utility_TwoDDistributionHelpers.hpp
//! \author Alex Robinson
//! \brief  Two-dimensional distribution helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TWO_D_DISTRIBUTION_HELPERS_HPP
#define UTILITY_TWO_D_DISTRIBUTION_HELPERS_HPP

// FRENSIE Includes
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ExplicitDistributionTemplateInstantiationMacros.hpp"
#include "Utility_DistributionSerializationHelpers.hpp"

/*! Declare that a two-d distribution class is an abstract base class
 *
 * This macro must be called from the global namespace. In order to serialize 
 * base two-d distribution class pointers (e.g. 
 * std::shared_ptr<Utility::TwoDDistribution>,  
 * std::unique_ptr<Utility::TwoDDistribution>, etc.) we need to register
 * them as abstract base classes with the boost::serialization extended
 * RTTI system. Calling this macro handles the registration.
 * \ingroup two_d_distributions
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION2( FullName ) \
  __BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION_IMPL__(          \
    __DIST_FORWARD+AS_SINGLE_ARG__(Utility::FullName<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>), \
    template<typename PrimaryIndependentUnit,typename SecondaryIndependentUnit,typename DependentUnit> )

/*! Declare the version of the distribution class
 *
 * The boost::serialization system allows for versioning of serializable
 * classes. As the classes change, the version number can be used to 
 * provide backwards compatibility with older archives.
 * \ingroup two_d_distributions
 */
#define BOOST_DISTRIBUTION2_CLASS_VERSION( FullName, Version ) \
  __BOOST_DISTRIBUTION_CLASS_VERSION_IMPL__( Version,                   \
    template<typename PrimaryIndependentUnit, typename SecondaryIndependentUnit, typename DependentUnit> \
    struct version<Utility::FullName<IndependentUnit,DependentUnit> > )

/*! Declare the GUID (key) of a distribution class
 *
 * The GUID or key must be declared for a concrete distribution class
 * when support for serializing instances of it through a base class pointer
 * is required. The GUID declared will be used by the 
 * boost::serialization extended RTTI system.
 * \ingroup two_d_distributions
 */
#define BOOST_DISTRIBUTION2_CLASS_EXPORT_KEY2( BaseName )                \
  __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__(                       \
     template<typename PrimaryIndependentUnit, typename SecondaryIndependentUnit, typename DependentUnit> \
     struct guid_defined<Utility::UnitAware##BaseName<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string( "UnitAware"#BaseName"<" )+Utility::typeName<PrimaryIndependentUnit>()+","+Utility::typeName<SecondaryIndependentUnit>()+","+Utility::typeName<DependentUnit>()+">", \
     template<typename PrimaryIndependentUnit, typename SecondaryIndependentUnit, typename DependentUnit> \
     struct guid_impl<Utility::UnitAware##BaseName<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string(#BaseName),       \
              template<>                    \
              struct guid_impl<Utility::UnitAware##BaseName<void,void,void> > )

/*! Register the distribution class GUID
 * 
 * This macro must be called after calling one of the
 * BOOST_DISTRIBUTION2_CLASS_EXPORT_KEY2 macros. The 
 * BOOST_DISTRIBUTION2_CLASS_EXPORT_KEY2 macros simply declare the GUID
 * associated with a distribution type while this macro actually registers
 * the GUID with the boost::serialization extended RTTI system.
 * \ingroup two_d_distributions
 */
#define BOOST_DISTRIBUTION2_CLASS_EXPORT_IMPLEMENT( FullName )   \
  __BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_IMPL__(               \
    __DIST_FORWARD_AS_SINGLE_ARG__(Utility::FullName<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>), \
    template<typename PrimaryIndependentUnit, typename SecondaryIndependentUnit, typename DependentUnit> )

#endif // end UTILITY_TWO_D_DISTRIBUTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_TwoDDistributionHelpers.hpp
//---------------------------------------------------------------------------//
