//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HDF5FileHandler.hpp
//! \author Alex Robinson
//! \brief  HDF5 file handler wrapper base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HDF5_FILE_HANDLER_HPP
#define MONTE_CARLO_HDF5_FILE_HANDLER_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

/*! The MonteCarlo package hdf5 file handler wrapper base class
 * \details This class is a light wrapper around the lower level
 * Utility::HDF5FileHandler class. When caching information from a MonteCarlo
 * simulation it is often necessary to interact with an HDF5 file. Depending
 * on the info that is being cached, there may be one or multiple wrappers
 * interacting with the HDF5 file. This wrapper class ensures that the
 * HDF5 file is handled appropriately depending on the number of interacting
 * wrappers (ownership vs. sharing). 
 */
class HDF5FileHandler
{

public:

  //! Enum for file operations
  enum FileOps{
    OVERWRITE_FILE = 0,
    APPEND_FILE,
    READ_ONLY_FILE
  };

  //! Constructor (file ownership)
  HDF5FileHandler( const std::string& hdf5_file_name,
                   const FileOps file_op = OVERWRITE_HDF5_FILE );

  //! Constructor (file sharing)
  HDF5FileHandler( const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  virtual ~HDF5FileHandler();

protected:

  //! Access the HDF5 file
  Utility::HDF5FileHandler& getHDF5File();

  //! Access the HDF5 file
  const Utility::HDF5FileHandler& getHDF5File() const;

private:

  // The HDF5 file handler
  std::shared_ptr<Utility::HDF5FileHandler> d_hdf5_file;

  // The ownership flag
  bool d_hdf5_file_ownership;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HDF5FileHandler.hpp
//---------------------------------------------------------------------------//
