//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnivariateDistributionHelpers.hpp
//! \author Alex Robinson
//! \brief  One-dimensional distribution helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_HELPERS_HPP
#define UTILITY_ONE_D_DISTRIBUTION_HELPERS_HPP

// FRENSIE Includes
#include "Utility_TypeNameTraits.hpp"
#include "Utility_ExplicitDistributionTemplateInstantiationMacros.hpp"
#include "Utility_DistributionSerializationHelpers.hpp"

/*! Declare that a distribution class is an abstract base class
 *
 * This macro must be called from the global namespace. In order to serialize 
 * base distribution class pointers (e.g. 
 * std::shared_ptr<Utility::UnivariateDistribution>, 
 * std::unique_ptr<Utility::TabularUnivariateDistribution>, etc.) we need to register
 * them as abstract base classes with the boost::serialization extended
 * RTTI system. Calling this macro handles the registration.
 * \ingroup univariate_distributions
 */
#define BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION1( FullName ) \
  __BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION_IMPL__(  \
    __DIST_FORWARD_AS_SINGLE_ARG__(Utility::FullName<IndependentUnit,DependentUnit>), \
    template<typename IndependentUnit, typename DependentUnit> )

/*! Declare the version of the distribution class
 *
 * The boost::serialization system allows for versioning of serializable
 * classes. As the classes change, the version number can be used to 
 * provide backwards compatibility with older archives.
 * \ingroup univariate_distributions
 */
#define BOOST_DISTRIBUTION1_CLASS_VERSION( FullName, Version ) \
  __BOOST_DISTRIBUTION_CLASS_VERSION_IMPL__( Version,                   \
            template<typename IndependentUnit, typename DependentUnit> \
            struct version<Utility::FullName<IndependentUnit,DependentUnit> > )

/*! Declare the version of the distribution class
 *
 * Use this macro to declare the distribution class version number instead
 * of the BOOST_DISTRIBUTION1_CLASS_VERSION macro when the distribution class
 * has an extra template parameter (e.g. Utility::TabularDistribution).
 * \ingroup univariate_distributions
 */
#define BOOST_DISTRIBUTION1_CLASS_VERSION_EXTRA( FullName, ExtraType, ExtraName, Version ) \
  __BOOST_DISTRIBUTION_CLASS_VERSION_IMPL__( Version,                   \
            template<ExtraType __##ExtraName##__, typename IndependentUnit, typename DependentUnit> \
            struct version<Utility::FullName<__##ExtraName##__,IndependentUnit,DependentUnit> > )
  
/*! Declare the GUID (key) of a distribution class
 *
 * The GUID or key must be declared for a concrete distribution class
 * when support for serializing instances of it through a base class pointer
 * is required. The GUID declared will be used by the 
 * boost::serialization extended RTTI system.
 * \ingroup univariate_distributions
 */
#define BOOST_DISTRIBUTION1_CLASS_EXPORT_KEY2( BaseName )                \
  __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__(                       \
     template<typename IndependentUnit, typename DependentUnit> \
     struct guid_defined<Utility::UnitAware##BaseName<IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string( "UnitAware"#BaseName"<" )+Utility::typeName<IndependentUnit>()+","+Utility::typeName<DependentUnit>()+">", \
                 template<typename IndependentUnit, typename DependentUnit> \
                 struct guid_impl<Utility::UnitAware##BaseName<IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string(#BaseName),       \
                 template<>                    \
                 struct guid_impl<Utility::UnitAware##BaseName<void,void> > )

/*! Declare the GUID (key) of a distribution class
 *
 * This macro should be used instead of the 
 * BOOST_DISTRIBUTION1_CLASS_EXPORT_KEY2 macro when a distribution class
 * has an extra template parameter (e.g. Utility::TabularDistribution).
 * \ingroup univariate_distributions
 */
#define BOOST_DISTRIBUTION1_CLASS_EXPORT_KEY2_EXTRA( BaseName, ExtraType, ExtraName  ) \
  __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__(                       \
     template<ExtraType ExtraName, typename IndependentUnit, typename DependentUnit> \
     struct guid_defined<Utility::UnitAware##BaseName<ExtraName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string( "UnitAware"#BaseName"<" )+(Utility::typeName<ExtraName,IndependentUnit,DependentUnit>())+">", \
     template<ExtraType ExtraName, typename IndependentUnit, typename DependentUnit> \
     struct guid_impl<Utility::UnitAware##BaseName<ExtraName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string(#BaseName"<")+Utility::typeName<ExtraName>()+">", \
         template<ExtraType ExtraName>                    \
         struct guid_impl<Utility::UnitAware##BaseName<ExtraName,void,void> > )

/*! Declare the GUID (key) of a distribution class
 *
 * This macro should be used instead of the 
 * BOOST_DISTRIBUTION1_CLASS_EXPORT_KEY2 macro when a distribution class
 * has an extra integer template parameter (e.g. Utility::PowerDistribution).
 * \ingroup univariate_distributions
 */
#define BOOST_DISTRIBUTION1_CLASS_EXPORT_KEY2_EXTRA_INT( BaseName, ExtraIntType, ExtraIntName  ) \
  __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__(                       \
     template<ExtraIntType ExtraIntName, typename IndependentUnit, typename DependentUnit> \
     struct guid_defined<Utility::UnitAware##BaseName<ExtraIntName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string( "UnitAware"#BaseName"<" )+Utility::toString(ExtraIntName)+","+(Utility::typeName<IndependentUnit,DependentUnit>())+">", \
     template<ExtraIntType ExtraIntName, typename IndependentUnit, typename DependentUnit> \
     struct guid_impl<Utility::UnitAware##BaseName<ExtraIntName,IndependentUnit,DependentUnit> > ) \
  __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( std::string(#BaseName"<")+Utility::toString(ExtraIntName)+">", \
         template<ExtraIntType ExtraIntName>                    \
         struct guid_impl<Utility::UnitAware##BaseName<ExtraIntName,void,void> > )

/*! Register the distribution class GUID
 * 
 * This macro must be called after calling one of the
 * BOOST_DISTRIBUTION1_CLASS_EXPORT_KEY2 macros. The 
 * BOOST_DISTRIBUTION1_CLASS_EXPORT_KEY2 macros simply declare the GUID
 * associated with a distribution type while this macro actually registers
 * the GUID with the boost::serialization extended RTTI system.
 * \ingroup univariate_distributions
 */
#define BOOST_DISTRIBUTION1_CLASS_EXPORT_IMPLEMENT( FullName )   \
  __BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_IMPL__(               \
    __DIST_FORWARD_AS_SINGLE_ARG__(Utility::FullName<IndependentUnit,DependentUnit>),\
    template<typename IndependentUnit, typename DependentUnit> )

/*! Register the distribution class GUID
 *
 * This macro should be called instead of the 
 * BOOST_DISTRIBUTION1_CLASS_EXPORT_IMPLEMENT when the distribution class
 * has an extra template parameter.
 * \ingroup univariate_distributions
 */
#define BOOST_DISTRIBUTION1_CLASS_EXPORT_IMPLEMENT_EXTRA( FullName, ExtraType, ExtraName  ) \
  __BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_IMPL__(               \
    __DIST_FORWARD_AS_SINGLE_ARG__(Utility::FullName<ExtraName,IndependentUnit,DependentUnit>), \
    template<ExtraType ExtraName, typename IndependentUnit, typename DependentUnit> )

#endif // end UTILITY_ONE_D_DISTRIBUTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnivariateDistributionHelpers.hpp
//---------------------------------------------------------------------------//
