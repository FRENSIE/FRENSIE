//---------------------------------------------------------------------------//
//!
//! \file   Utility_SmartPtr.hpp
//! \author Alex Robinson
//! \brief  Std library smart pointer helper functions and classes
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SMART_PTR_HPP
#define UTILITY_SMART_PTR_HPP

// Std Lib Includes
#include <memory>
#include <map>

namespace boost{

namespace serialization{

template<typename T>
struct shared_ptr_void_conversion_helper
{
  static inline std::shared_ptr<void> convert(
                                     const std::shared_ptr<T>& shared_pointer )
  { return std::static_pointer_cast<void>( shared_pointer ); }
};

template<typename T>
struct shared_ptr_void_conversion_helper<const T>
{
  static inline std::shared_ptr<void> convert(
                               const std::shared_ptr<const T>& shared_pointer )
  {
    return std::const_pointer_cast<void>(
                      std::static_pointer_cast<const void>( shared_pointer ) );
  }
};

template<template<class> class SPT>
class shared_ptr_helper;

/*! \brief Partial specialization of boost::serialization::shared_ptr_helper 
 * for std::shared_ptr
 *
 * The generic boost::serialization::shared_ptr_helper definition does not
 * appear to work for std::shared_ptr. At line 182 of 
 * boost/serialization/shared_ptr_helper an attempt is made to insert a
 * std::pair<const void*,std::shared_ptr<const T> > into a 
 * std::map<const void*,std::shared_ptr<void> >. An implicit conversion from
 * std::pair<const void*,std::shared_ptr<const T> > to 
 * std::pair<const void*,std::shared_ptr<void> > does not exist, which causes
 * a compilation error. We fix this in the specialization by doing 
 * explicit casts to the correct types.
 */
template<>
class shared_ptr_helper<std::shared_ptr>
{
  typedef std::map<const void*, std::shared_ptr<void> > object_shared_pointer_map;

  object_shared_pointer_map* m_o_sp;

#if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS) || defined(BOOST_MSVC)
public:
#else
    template<class Archive, class U>
    friend void boost::serialization::load( Archive & ar,
                                            std::shared_ptr<U> &t,
                                            const unsigned int file_version );
#endif

  struct non_polymorphic
  {
    template<class U>
    static const boost::serialization::extended_type_info* 
    get_object_type(U & )
    {
      return &boost::serialization::singleton<
        typename boost::serialization::type_info_implementation< U >::type
        >::get_const_instance();
    }
  };

  struct polymorphic
  {
    template<class U>
    static const boost::serialization::extended_type_info* 
    get_object_type(U & u){
      return boost::serialization::singleton<
        typename boost::serialization::type_info_implementation< U >::type
        >::get_const_instance().get_derived_extended_type_info(u);
    }
  };

public:

  template<class T>
  void reset(std::shared_ptr< T > & s, T * t)
  {
    if(NULL == t){
      s.reset();
      return;
    }

    const boost::serialization::extended_type_info* this_type =
      &boost::serialization::type_info_implementation< T >::type::get_const_instance();

    // get pointer to the most derived object's eti.  This is effectively
    // the object type identifer
    typedef typename mpl::if_<is_polymorphic< T >,polymorphic,non_polymorphic>::type type;

    const boost::serialization::extended_type_info* true_type =
      type::get_object_type(*t);

    // note:if this exception is thrown, be sure that derived pointer
    // is either registered or exported.
    if(NULL == true_type)
    {
      boost::serialization::throw_exception(
                    boost::archive::archive_exception(
                    boost::archive::archive_exception::unregistered_class,
                    this_type->get_debug_info() ) );
    }

    // get void pointer to the most derived type
    // this uniquely identifies the object referred to
    // oid = "object identifier"
    const void* oid = void_downcast( *true_type, *this_type, t );
    
    if(NULL == oid)
    {
      boost::serialization::throw_exception(
                boost::archive::archive_exception(
                    boost::archive::archive_exception::unregistered_cast,
                    true_type->get_debug_info(),
                    this_type->get_debug_info() ) );
    }

    // make tracking array if necessary
    if(NULL == m_o_sp)
      m_o_sp = new object_shared_pointer_map;

    typename object_shared_pointer_map::iterator i = m_o_sp->find(oid);

    // if it's a new object
    if(i == m_o_sp->end())
    {
      s.reset(t);
      
      std::pair<typename object_shared_pointer_map::iterator, bool> result;

      result = m_o_sp->insert(std::make_pair(oid, shared_ptr_void_conversion_helper<T>::convert(s)));
      BOOST_ASSERT(result.second);
    }
    // if the object has already been seen
    else
    {
      s = std::shared_ptr<T>(i->second, t);
    }
  }

  shared_ptr_helper()
    : m_o_sp(NULL)
  { /* ... */ }
  
  virtual ~shared_ptr_helper()
  {
    if(NULL != m_o_sp)
      delete m_o_sp;
  }
};

} // end serialization namespace

} // end boost namespace

// Boost Includes
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>

#endif // end UTILITY_SMART_PTR_HPP

//---------------------------------------------------------------------------//
// end Utility_SmartPtr.hpp
//---------------------------------------------------------------------------//

