//---------------------------------------------------------------------------//
//!
//! \file   Utility_DistributionSerializationHelpers.hpp
//! \author Alex Robinson
//! \brief  Distribution serialization helper macro definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DISTRIBUTION_SERIALIZATION_HELPERS_HPP
#define UTILITY_DISTRIBUTION_SERIALIZATION_HELPERS_HPP

// Boost Includes
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>

#define __BOOST_DISTRIBUTION_CLASS_VERSION_IMPL__( _N, ... )    \
namespace boost{                                      \
namespace serialization{                            \
                                                    \
  __VA_ARGS__                                                           \
  {                                                                     \
    typedef mpl::int_<_N> type;                                         \
    typedef mpl::integral_c_tag tag;                                    \
    BOOST_STATIC_CONSTANT(int, value = version::type::value);           \
    BOOST_MPL_ASSERT((                                                  \
                      boost::mpl::less<                                 \
                      boost::mpl::int_<_N>,                             \
                      boost::mpl::int_<256> >                           \
                    ));                                                 \
  };                                                                    \
}                                                                       \
}

#define __BOOST_DISTRIBUTION_CLASS_DECL_GUID_DEFINED__( ... ) \
namespace boost{                                              \
namespace serialization{                                              \
  __VA_ARGS__ : public boost::mpl::true_                                  \
  { /* ... */ };                                                        \
}                                                                       \
}

#define __BOOST_DISTRIBUTION_CLASS_GUID_IMPL__( GUID, ... )     \
namespace boost{                                              \
namespace serialization{                                    \
namespace ext{                                                        \
  __VA_ARGS__                                                           \
  {                                                                     \
    static inline const char* call()                                    \
    { return (GUID).c_str(); }                                          \
  };                                                                    \
}  \
}  \
}

#define __BOOST_SERIALIZATION_ASSUME_ABSTRACT_DISTRIBUTION_IMPL__( DistributionType, ... ) \
namespace boost{                                                      \
namespace serialization{                                              \
                                                                      \
  __VA_ARGS__                                                          \
  struct is_abstract<DistributionType> : boost::true_type              \
  { /* ... */ };                                                       \
                                                                       \
  __VA_ARGS__                                                          \
  struct is_abstract<const DistributionType> : boost::true_type        \
  { /* ... */ };                                                       \
}                                                                      \
}

#define __BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_IMPL__( DistributionType, ... ) \
namespace boost{                                              \
namespace archive{                                          \
namespace detail{                                         \
namespace extra_detail{ \
  __VA_ARGS__                                                           \
  struct init_guid<DistributionType>                                    \
  {                                                                     \
    static const guid_initializer<DistributionType>& g;                 \
  };                                                                    \
                                                                        \
  __VA_ARGS__                                                           \
  const guid_initializer<DistributionType>& init_guid<DistributionType>::g = \
    ::boost::serialization::singleton<guid_initializer<DistributionType> >::get_mutable_instance().export_guid(); \
}                                                                       \
}                                                                       \
}                                                                       \
}

#define __DIST_FORWARD_AS_SINGLE_ARG__( ... ) __VA_ARGS__

/*! Finalize the registration of the distribution class GUID
 *
 * This macro must be called from the constructors of the distribution class
 * to finalize the GUID registration process. Because the distribution
 * classes are templates the GUID registration singleton that is used
 * in the registration process won't get instantiated until the first
 * instance of the distribution has been created.
 * \ingroup one_d_distributions
 * \ingroup two_d_distributions
 */
#define BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ... )  \
  const auto& __guid_initializer__ = boost::archive::detail::extra_detail::init_guid<__VA_ARGS__>::g

#endif // end UTILITY_DISTRIBUTION_SERIALIZATION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_DistributionSerializationHelpers.hpp
//---------------------------------------------------------------------------//
