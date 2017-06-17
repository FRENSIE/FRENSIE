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

namespace Utility{

/*! isConstIterator partial specialization for pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<T*> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for const pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<const T*> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<T*>
{
  //! The pointer const iterator type
  typedef const T* type;
};

/*! constIterator specialization for const pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<const T*>
{
  //! The pointer const iterator type
  typedef const T* type;
};

/*! nonConstIterator specialization for pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstITerator<T*>
{
  //! The pointer iterator type
  typedef T* type;
};

/*! nonConstIterator specialization for pointer type
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<const T*>
{
  //! The pointer iterator type
  typedef T* type;
};

/*! isConstIterator specialization for std::string::iterator
 * \ingroup iterator_type_traits
 */
template<>
struct isConstIterator<std::string::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator specialization for std::string::const_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct isConstIterator<std::string::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator specialization for std::string::iterator
 * \ingroup iterator_type_traits
 */
template<>
struct constIterator<std::string::iterator>
{
  //! The std::string const iterator type
  typedef std::string::const_iterator type;
};

/*! constIterator specialization for const std::string::iterator
 * \ingroup iterator_type_traits
 */
template<>
struct constIterator<std::string::const_iterator>
{
  //! The std::string const iterator type
  typedef std::string::const_iterator type;
};

/*! nonConstIterator specialization for std::string::iterator
 * \ingroup iterator_type_traits
 */
template<>
struct nonConstIterator<std::string::iterator>
{
  //! The std::string iterator type
  typedef std::string::iterator type;
};

/*! nonConstIterator specialization for std::string::const_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct nonConstIterator<std::string::const_iterator>
{
  //! The std::string iterator type
  typedef std::string::iterator type;
};

/*! isConstIterator specialization for std::string::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct isConstIterator<std::string::reverse_iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator specialization for std::string::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct isConstIterator<std::string::const_reverse_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator specialization for std::string::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct constIterator<std::string::reverse_iterator>
{
  //! The std::string const reverse_iterator type
  typedef std::string::const_reverse_iterator type;
};

/*! nonConstIterator specialization for std::string::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct nonConstIterator<std::string::reverse_iterator>
{
  //! The std::string reverse iterator type
  typedef std::string::reverse_iterator type;
};

/*! constIterator specialization for std::string::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct constIterator<std::string::const_reverse_iterator>
{
  //! The std::string const reverse iterator type
  typedef std::string::const_reverse_iterator type;
};

/*! nonConstIterator specialization for std::string::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<>
struct nonConstIterator<std::string::const_reverse_iterator>
{
  //! The std::string reverse iterator type
  typedef std::string::reverse_iterator type;
};

/*! isConstIterator partial specialization for std::array::iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct isConstIterator<typename std::array<T,N>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::array::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct isConstIterator<typename std::array<T,N>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::array::iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct constIterator<typename std::array<T,N>::iterator>
{
  //! The std::array const iterator type
  typedef typename std::array<T,N>::const_iterator type;
};

/*! constIterator partial specialization for std::array::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct constIterator<typename std::array<T,N>::const_iterator>
{
  //! The std::array const iterator type
  typedef typename std::array<T,N>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::array::iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct nonConstIterator<typename std::array<T,N>::iterator>
{
  //! The std::array iterator type
  typedef typename std::array<T,N>::iterator type;
};
  
/*! nonConstIterator partial specialization for std::array::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct nonConstIterator<typename std::array<T,N>::const_iterator>
{
  //! The std::array iterator type
  typedef typename std::array<T,N>::iterator type;
};

/*! isConstIterator partial specialization for std::array::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct isConstIterator<typename std::array<T,N>::reverse_iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::array::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct isConstIterator<typename std::array<T,N>::const_reverse_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::array::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct constIterator<typename std::array<T,N>::reverse_iterator>
{
  //! The std::array const reverse iterator type
  typedef typename std::array<T,N>::const_reverse_iterator type;
};

/*! constIterator partial specialization for std::array::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct constIterator<typename std::array<T,N>::const_reverse_iterator>
{
  //! The std::array const reverse iterator type
  typedef typename std::array<T,N>::const_reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::array::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct nonConstIterator<typename std::array<T,N>::reverse_iterator>
{
  //! The std::array reverse iterator type
  typedef typename std::array<T,N>::reverse_iterator type;
};
  
/*! nonConstIterator partial specialization for std::array::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T, size_t N>
struct nonConstIterator<typename std::array<T,N>::const_reverse_iterator>
{
  //! The std::array reverse iterator type
  typedef typename std::array<T,N>::reverse_iterator type;
};

/*! isConstIterator partial specialization for std::vector::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::vector<T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::vector::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::vector<T>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::vector::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::vector<T>::iterator>
{
  //! The std::vector const iterator type
  typedef typename std::vector<T>::const_iterator type;
};

/*! constIterator partial specialization for std::vector::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::vector<T>::const_iterator>
{
  //! The std::vector const iterator type
  typedef typename std::vector<T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::vector::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::vector<T>::iterator>
{
  //! The std::vector iterator type
  typedef typename std::vector<T>::iterator type;
};

/*! nonConstIterator partial specialization for std::vector::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::vector<T>::const_iterator>
{
  //! The std::vector iterator type
  typedef typename std::vector<T>::iterator type;
};

/*! isConstIterator partial specialization for std::vector::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::vector<T>::reverse_iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::vector::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::vector<T>::const_reverse_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::vector::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::vector<T>::reverse_iterator>
{
  //! The std::vector const reverse iterator type
  typedef typename std::vector<T>::const_reverse_iterator type;
};

/*! constIterator partial specialization for std::vector::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::vector<T>::const_reverse_iterator>
{
  //! The std::vector const reverse iterator type
  typedef typename std::vector<T>::const_reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::vector::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::vector<T>::reverse_iterator>
{
  //! The std::vector reverse iterator type
  typedef typename std::vector<T>::reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::vector::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::vector<T>::const_reverse_iterator>
{
  //! The std::vector reverse iterator type
  typedef typename std::vector<T>::reverse_iterator type;
};

/*! isConstIterator partial specialization for std::list::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::list<T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::list::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::list<T>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::list::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::list<T>::iterator>
{
  //! The std::list const iterator type
  typedef typename std::list<T>::const_iterator type;
};

/*! constIterator partial specialization for std::list::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::list<T>::const_iterator>
{
  //! The std::list const iterator type
  typedef typename std::list<T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::list::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::list<T>::iterator>
{
  //! The std::list iterator type
  typedef typename std::list<T>::iterator type;
};

/*! nonConstIterator partial specialization for std::list::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::list<T>::const_iterator>
{
  //! The std::list iterator type
  typedef typename std::list<T>::iterator type;
};

/*! isConstIterator partial specialization for std::list::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::list<T>::reverse_iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::list::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::list<T>::const_reverse_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::list::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::list<T>::reverse_iterator>
{
  //! The std::list const reverse iterator type
  typedef typename std::list<T>::const_reverse_iterator type;
};

/*! constIterator partial specialization for std::list::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::list<T>::const_reverse_iterator>
{
  //! The std::list const reverse iterator type
  typedef typename std::list<T>::const_reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::list::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::list<T>::reverse_iterator>
{
  //! The std::list reverse iterator type
  typedef typename std::list<T>::reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::list::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::list<T>::const_reverse_iterator>
{
  //! The std::list reverse iterator type
  typedef typename std::list<T>::reverse_iterator type;
};

/*! isConstIterator partial specialization for std::forward_list::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::forward_list<T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::forward_list::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::forward_list<T>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::forward_list::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::forward_list<T>::iterator>
{
  //! The std::forward_list const iterator type
  typedef typename std::forward_list<T>::const_iterator type;
};

/*! constIterator partial specialization for std::forward_list::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::forward_list<T>::const_iterator>
{
  //! The std::forward_list const iterator type
  typedef typename std::forward_list<T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::forward_list::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::forward_list<T>::iterator>
{
  //! The std::forward_list iterator type
  typedef typename std::forward_list<T>::iterator type;
};

/*! nonConstIterator partial specialization for std::forward_list::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::forward_list<T>::const_iterator>
{
  //! The std::forward_list iterator type
  typedef typename std::forward_list<T>::iterator type;
};

/*! isConstIterator partial specialization for std::deque::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::deque<T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::deque::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::deque<T>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::deque::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::deque<T>::iterator>
{
  //! The std::deque const iterator type
  typedef typename std::deque<T>::const_iterator type;
};

/*! constIterator partial specialization for std::deque::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::deque<T>::const_iterator>
{
  //! The std::deque const iterator type
  typedef typename std::deque<T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::deque::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::deque<T>::iterator>
{
  //! The std::deque iterator type
  typedef typename std::deque<T>::iterator type;
};

/*! nonConstIterator partial specialization for std::deque::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::deque<T>::const_iterator>
{
  //! The std::deque iterator type
  typedef typename std::deque<T>::iterator type;
};

/*! isConstIterator partial specialization for std::deque::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::deque<T>::reverse_iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::deque::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::deque<T>::const_reverse_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::deque::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::deque<T>::reverse_iterator>
{
  //! The std::deque const reverse iterator type
  typedef typename std::deque<T>::const_reverse_iterator type;
};

/*! constIterator partial specialization for std::deque::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::deque<T>::const_reverse_iterator>
{
  //! The std::deque const reverse iterator type
  typedef typename std::deque<T>::const_reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::deque::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::deque<T>::reverse_iterator>
{
  //! The std::deque reverse iterator type
  typedef typename std::deque<T>::reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::deque::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::deque<T>::const_reverse_iterator>
{
  //! The std::deque reverse iterator type
  typedef typename std::deque<T>::reverse_iterator type;
};

/*! isConstIterator partial specialization for std::set::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::set<T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::set::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::set<T>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::set::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::set<T>::iterator>
{
  //! The std::set const iterator type
  typedef typename std::set<T>::const_iterator type;
};

/*! constIterator partial specialization for std::set::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::set<T>::const_iterator>
{
  //! The std::set const iterator type
  typedef typename std::set<T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::set::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::set<T>::iterator>
{
  //! The std::set iterator type
  typedef typename std::set<T>::iterator type;
};

/*! nonConstIterator partial specialization for std::set::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::set<T>::const_iterator>
{
  //! The std::set iterator type
  typedef typename std::set<T>::iterator type;
};

/*! isConstIterator partial specialization for std::set::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::set<T>::reverse_iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::set::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::set<T>::const_reverse_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::set::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::set<T>::reverse_iterator>
{
  //! The std::set const reverse iterator type
  typedef typename std::set<T>::const_reverse_iterator type;
};

/*! constIterator partial specialization for std::set::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::set<T>::const_reverse_iterator>
{
  //! The std::set const reverse iterator type
  typedef typename std::set<T>::const_reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::set::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::set<T>::reverse_iterator>
{
  //! The std::set reverse iterator type
  typedef typename std::set<T>::reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::set::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::set<T>::const_reverse_iterator>
{
  //! The std::set reverse iterator type
  typedef typename std::set<T>::reverse_iterator type;
};

/*! isConstIterator partial specialization for std::unordered_set::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::unordered_set<T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::unordered_set::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct isConstIterator<typename std::unordered_set<T>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::unordered_set::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::unordered_set<T>::iterator>
{
  //! The std::unordered_set const iterator type
  typedef typename std::unordered_set<T>::const_iterator type;
};

/*! constIterator partial specialization for std::unordered_set::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct constIterator<typename std::unordered_set<T>::const_iterator>
{
  //! The std::unordered_set const iterator type
  typedef typename std::unordered_set<T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::unordered_set::iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::unordered_set<T>::iterator>
{
  //! The std::unordered_set iterator type
  typedef typename std::unordered_set<T>::iterator type;
};

/*! nonConstIterator partial specialization for std::unordered_set::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename T>
struct nonConstIterator<typename std::unordered_set<T>::const_iterator>
{
  //! The std::unordered_set iterator type
  typedef typename std::unordered_set<T>::iterator type;
};

/*! isConstIterator partial specialization for std::map::iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct isConstIterator<typename std::map<Key,T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::map::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct isConstIterator<typename std::map<Key,T>::const_iterator> : public std::true_type
{ /* ... */ };

/*! constIterator partial specialization for std::map::iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct constIterator<typename std::map<Key,T>::iterator>
{
  //! The std::map const iterator type
  typedef typename std::map<Key,T>::const_iterator type;
};

/*! constIterator partial specialization for std::map::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct constIterator<typename std::map<Key,T>::const_iterator>
{
  //! The std::map const iterator type
  typedef typename std::map<Key,T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::map::iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct nonConstIterator<typename std::map<Key,T>::iterator>
{
  //! The std::map iterator type
  typedef typename std::map<Key,T>::iterator type;
};

/*! nonConstIterator partial specialization for std::map::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct nonConstIterator<typename std::map<Key,T>::const_iterator>
{
  //! The std::map iterator type
  typedef typename std::map<Key,T>::iterator type;
};

/*! isConstIterator partial specialization for std::map::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct isConstIterator<typename std::map<Key,T>::reverse_iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::map::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct isConstIterator<typename std::map<Key,T>::const_reverse_iterator> : public std::true_type
{ /* ... */ };
  
/*! constIterator partial specialization for std::map::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct constIterator<typename std::map<Key,T>::reverse_iterator>
{
  //! The std::map const reverse iterator type
  typedef typename std::map<Key,T>::const_reverse_iterator type;
};

/*! constIterator partial specialization for std::map::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct constIterator<typename std::map<Key,T>::const_reverse_iterator>
{
  //! The std::map const reverse iterator type
  typedef typename std::map<Key,T>::const_reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::map::reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct nonConstIterator<typename std::map<Key,T>::reverse_iterator>
{
  //! The std::map reverse iterator type
  typedef typename std::map<Key,T>::reverse_iterator type;
};

/*! nonConstIterator partial specialization for std::map::const_reverse_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct nonConstIterator<typename std::map<Key,T>::const_reverse_iterator>
{
  //! The std::map reverse iterator type
  typedef typename std::map<Key,T>::reverse_iterator type;
};

/*! isConstIterator partial specialization for std::unordered_map::iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct isConstIterator<typename std::unordered_map<Key,T>::iterator> : public std::false_type
{ /* ... */ };

/*! isConstIterator partial specialization for std::unordered_map::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct isConstIterator<typename std::unordered_map<Key,T>::const_iterator> : public std::true_type
{ /* ... */ };
  
/*! constIterator partial specialization for std::unordered_map::iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct constIterator<typename std::unordered_map<Key,T>::iterator>
{
  //! The std::unordered_map const iterator type
  typedef typename std::unordered_map<Key,T>::const_iterator type;
};

/*! constIterator partial specialization for std::unordered_map::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct constIterator<typename std::unordered_map<Key,T>::const_iterator>
{
  //! The std::unordered_map const iterator type
  typedef typename std::unordered_map<Key,T>::const_iterator type;
};

/*! nonConstIterator partial specialization for std::unordered_map::iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct nonConstIterator<typename std::unordered_map<Key,T>::iterator>
{
  //! The std::unordered_map iterator type
  typedef typename std::unordered_map<Key,T>::iterator type;
};

/*! nonConstIterator partial specialization for std::unordered_map::const_iterator
 * \ingroup iterator_type_traits
 */
template<typename Key, typename T>
struct nonConstIterator<typename std::unordered_map<Key,T>::const_iterator>
{
  //! The std::unordered_map iterator type
  typedef typename std::unordered_map<Key,T>::iterator type;
};
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_IteratorTypeTraits.hpp
//---------------------------------------------------------------------------//
