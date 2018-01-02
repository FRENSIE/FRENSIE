//---------------------------------------------------------------------------//
//!
//! \file   Utility_IArchivableObject_def.hpp
//! \author Alex Robinson
//! \brief  IArchivable object base class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_IARCHIVABLE_OBJECT_DEF_HPP
#define UTILITY_IARCHIVABLE_OBJECT_DEF_HPP

// Boost Includes
#include <boost/serialization/nvp.hpp>

namespace Utility{

namespace Details{

/*! The input archive creator
 *
 * This class should never be used directly
 */
class IArchiveCreator
{
  
public:

  //! Constructor
  IArchiveCreator()
  { /* ... */ }

  //! Destructor
  virtual ~IArchiveCreator()
  { /* ... */ }

  //! Create an input archive
  static void create(
             const boost::filesystem::path& archive_name_with_path,
             std::unique_ptr<std::istream>& oarchive_stream,
             std::unique_ptr<boost::archive::polymorphic_iarchive>& oarchive );
};

} // end Details namespace

// Load the archived object
/*! \details The file extension will be used to determine the archive type
 * (e.g. .xml, .txt, .bin, .h5fa)
 */
template<typename DerivedType>
void IArchivableObject<DerivedType>::loadFromFile( const boost::filesystem::path& archive_name_with_path )
{
  // Create the input archive
  std::unique_ptr<std::istream> iarchive_stream;
  std::unique_ptr<boost::archive::polymorphic_iarchive> iarchive;

  Details::IArchiveCreator::create( archive_name_with_path, iarchive_stream, iarchive );

  // Load the derived type from the archive
  (*iarchive) >> boost::serialization::make_nvp( this->getIArchiveName(), *dynamic_cast<DerivedType*>(this) );

  // Ensure that the archive destructor is called before the stream destructor
  iarchive.reset();
}
  
} // end Utility namespace

#endif // end UTILITY_IARCHIVABLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_IArchivableObject_def.hpp
//---------------------------------------------------------------------------//
