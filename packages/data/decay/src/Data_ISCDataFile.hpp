//---------------------------------------------------------------------------//
//!
//! \file   Data_ISCDataFile.cpp
//! \author CJ Solomon
//! \brief  ISC Data File
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ISC_DATA_FILE_HPP
#define DATA_ISC_DATA_FILE_HPP

namespace data {

class ISCDataFile {
public:

  enum FileType {
    TXT=0,
    BIN=1,
    XML=2
  };

  virtual void Save(const std::string& filename, const unsigned int type) const = 0;
  virtual void Load(const std::string& filename, const unsigned int type) = 0;

private:
};

} // end namespace data

#endif // DATA_ISC_DATA_FILE_HPP

//---------------------------------------------------------------------------//
// end Data_ISCDataFile.cpp
//---------------------------------------------------------------------------//
