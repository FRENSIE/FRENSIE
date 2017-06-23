//---------------------------------------------------------------------------//
//!
//! \file   Utility_IteratorTypeTraits.hpp
//! \author Alex Robinson
//! \brief  Iterator type traits class specializations
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

// FRENSIE Includes
#include "Utility_IteratorTypeTraitsDecl.hpp"
#include "Utility_TypeTraits.hpp"

namespace Utility{

/*! IsConstIterator partial specialization for all const iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct IsConstIterator<Iterator,typename std::enable_if<IsPointerToConst<typename std::iterator_traits<Iterator>::pointer>::value>::type> : public std::true_type
{ /* ... */ };

/*! IsConstIterator partial specialization for all non-const iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct IsConstIterator<Iterator,typename std::enable_if<!IsPointerToConst<typename std::iterator_traits<Iterator>::pointer>::value>::type> : public std::false_type
{ /* ... */ };

/*! ConstIterator partial specialization for pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct ConstIterator<T*>
{
  //! The pointer const iterator type
  typedef const T* type;
};

/*! ConstIterator partial specialization for pointer-to-const type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct ConstIterator<const T*>
{
  //! The pointer const iterator type
  typedef const T* type;
};

/*! ConstIterator partial specialization for reverse_iterator of pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct ConstIterator<std::reverse_iterator<T*> >
{
  //! The pointer const iterator type
  typedef std::reverse_iterator<const T*> type;
};

/*! ConstIterator partial specialization for reverse_iterator of pointer-to-const type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct ConstIterator<std::reverse_iterator<const T*> >
{
  //! The pointer const iterator type
  typedef std::reverse_iterator<const T*> type;
};

/*! NonConstIterator specialization for pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct NonConstIterator<T*>
{
  //! The pointer iterator type
  typedef T* type;
};

/*! NonConstIterator specialization for pointer-to-const type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct NonConstIterator<const T*>
{
  //! The pointer iterator type
  typedef T* type;
};

/*! NonConstIterator specialization for reverse_iterator of pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct NonConstIterator<std::reverse_iterator<T*> >
{
  //! The pointer iterator type
  typedef std::reverse_iterator<T*> type;
};

/*! NonConstIterator specialization for reverse_iterator of pointer-to-const type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct NonConstIterator<std::reverse_iterator<const T*> >
{
  //! The pointer iterator type
  typedef std::reverse_iterator<T*> type;
};

/*! ConstIterator partial specialization for std::string iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::iterator>::value>::type>
{
  //! The std::string const_iterator type
  typedef typename std::string::const_iterator type;
};

/*! ConstIterator partial specialization for std::string const iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::const_iterator>::value>::type>
{
  //! The std::string const_iterator type
  typedef typename std::string::const_iterator type;
};

/*! ConstIterator partial specialization for std::string reverse iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::reverse_iterator>::value>::type>
{
  //! The std::string const_reverse_iterator type
  typedef typename std::string::const_reverse_iterator type;
};

/*! ConstIterator partial specialization for std::string const reverse iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::const_reverse_iterator>::value>::type>
{
  //! The std::string const_iterator type
  typedef typename std::string::const_reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::string iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::iterator>::value>::type>
{
  //! The std::string iterator type
  typedef typename std::string::iterator type;
};

/*! NonConstIterator partial specialization for std::string const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::const_iterator>::value>::type>
{
  //! The std::string iterator type
  typedef typename std::string::iterator type;
};

/*! NonConstIterator partial specialization for std::string reverse iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::reverse_iterator>::value>::type>
{
  //! The std::string reverse_iterator type
  typedef typename std::string::reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::string const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,std::string::const_reverse_iterator>::value>::type>
{
  //! The std::string iterator type
  typedef typename std::string::reverse_iterator type;
};

/*! ConstIterator partial specialization for std::vector iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::vector const_iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::vector const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::vector const_iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::vector reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value>::type>
{
  //! The std::vector const_iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator type;
};

/*! ConstIterator partial specialization for std::vector const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value>::type>
{
  //! The std::vector const_iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::vector iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::vector iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! NonConstIterator partial specialization for std::vector const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::vector iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! NonConstIterator partial specialization for std::vector reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value>::type>
{
  //! The std::vector iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::vector const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::vector<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value>::type>
{
  //! The std::vector iterator type
  typedef typename std::vector<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator type;
};

/*! ConstIterator partial specialization for std::list iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::list const_iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::list const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::list const_iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::list reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value>::type>
{
  //! The std::list const_iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator type;
};

/*! ConstIterator partial specialization for std::list const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value>::type>
{
  //! The std::list const_iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::list iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::list iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! NonConstIterator partial specialization for std::list const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::list iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! NonConstIterator partial specialization for std::list reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value>::type>
{
  //! The std::list iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::list const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::list<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value>::type>
{
  //! The std::list iterator type
  typedef typename std::list<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator type;
};

/*! ConstIterator partial specialization for std::forward_list iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::forward_list const_iterator type
  typedef typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::forward_list const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::forward_list const_iterator type
  typedef typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! NonConstIterator partial specialization for std::forward_list iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::forward_list iterator type
  typedef typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! NonConstIterator partial specialization for std::forward_list const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::forward_list iterator type
  typedef typename std::forward_list<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! ConstIterator partial specialization for std::deque iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::deque const_iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::deque const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::deque const_iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::deque reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value>::type>
{
  //! The std::deque const_iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator type;
};

/*! ConstIterator partial specialization for std::deque const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value>::type>
{
  //! The std::deque const_iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::deque iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::deque iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! NonConstIterator partial specialization for std::deque const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_iterator>::value>::type>
{
  //! The std::deque iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::iterator type;
};

/*! NonConstIterator partial specialization for std::deque reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value>::type>
{
  //! The std::deque iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::deque const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::deque<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator>::value>::type>
{
  //! The std::deque iterator type
  typedef typename std::deque<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator type;
};

/*! ConstIterator partial specialization for std::set iterator types
 *
 * The iterator and const_iterator types are the same with std::set. In 
 * addition, the std::map const_iterator types are the same as the
 * std::set iterator and const_iterator types. This partial specialization
 * will be invoked when using a std::map const_iterator type.
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::set<typename std::iterator_traits<Iterator>::value_type>::iterator>::value>::type>
{
  //! The std::set const_iterator type
  typedef typename std::set<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::set reverse_iterator types
 *
 * The reverse_iterator and const_reverse_iterator types are the same with
 * std::set. In addition, the std::map const_reverse_iterator types are the 
 * same as the std::set reverse_iterator and const_reverse_iterator types. This
 * partial specialization will be invoked when using a std::map 
 * const_reverse_iterator type.
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::set<typename std::iterator_traits<Iterator>::value_type>::reverse_iterator>::value>::type>
{
  //! The std::set const_iterator type
  typedef typename std::set<typename std::iterator_traits<Iterator>::value_type>::const_reverse_iterator type;
};

/*! ConstIterator partial specialization for std::map iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator>::value>::type>
{
  //! The std::map const_iterator type
  typedef typename std::map<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::map reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::reverse_iterator>::value>::type>
{
  //! The std::map const_iterator type
  typedef typename std::map<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::map iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator>::value>::type>
{
  //! The std::map iterator type
  typedef typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator type;
};

/*! NonConstIterator partial specialization for std::map const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_iterator>::value>::type>
{
  //! The std::map iterator type
  typedef typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator type;
};

/*! NonConstIterator partial specialization for std::map reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::reverse_iterator>::value>::type>
{
  //! The std::map iterator type
  typedef typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::reverse_iterator type;
};

/*! NonConstIterator partial specialization for std::map const_reverse_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_reverse_iterator>::value>::type>
{
  //! The std::map iterator type
  typedef typename std::map<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::reverse_iterator type;
};

/*! ConstIterator partial specialization for std::unordered_set iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::unordered_set<typename std::conditional<IsHashable<typename std::iterator_traits<Iterator>::value_type>::value,typename std::iterator_traits<Iterator>::value_type,void*>::type>::iterator>::value>::type>
{
  //! The std::unordered_set const_iterator type
  typedef typename std::unordered_set<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::unordered_set const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::unordered_set<typename std::conditional<IsHashable<typename std::iterator_traits<Iterator>::value_type>::value,typename std::iterator_traits<Iterator>::value_type,void*>::type>::const_iterator>::value>::type>
{
  //! The std::unordered_set const_iterator type
  typedef typename std::unordered_set<typename std::iterator_traits<Iterator>::value_type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::unordered_map iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::unordered_map<typename std::conditional<IsHashable<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type>::value,typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,void*>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator>::value>::type>
{
  //! The std::unordered_map const_iterator type
  typedef typename std::unordered_map<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_iterator type;
};

/*! ConstIterator partial specialization for std::unordered_map const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct ConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::unordered_map<typename std::conditional<IsHashable<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type>::value,typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,void*>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_iterator>::value>::type>
{
  //! The std::unordered_map const_iterator type
  typedef typename std::unordered_map<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_iterator type;
};

/*! NonConstIterator partial specialization for std::unordered_map iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::unordered_map<typename std::conditional<IsHashable<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type>::value,typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,void*>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator>::value>::type> 
{
  //! The std::unordered_map iterator type
  typedef typename std::unordered_map<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator type;
};

/*! NonConstIterator partial specialization for std::unordered_map const_iterator types
 * \ingroup iterator_type_traits
 */
template<typename Iterator>
struct NonConstIterator<Iterator,typename std::enable_if<std::is_same<Iterator,typename std::unordered_map<typename std::conditional<IsHashable<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type>::value,typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,void*>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::const_iterator>::value>::type> 
{
  //! The std::unordered_map iterator type
  typedef typename std::unordered_map<typename std::remove_const<typename std::tuple_element<0,typename std::iterator_traits<Iterator>::value_type>::type>::type,typename std::tuple_element<1,typename std::iterator_traits<Iterator>::value_type>::type>::iterator type;
};
 
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_IteratorTypeTraits.hpp
//---------------------------------------------------------------------------//
