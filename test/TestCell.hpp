//---------------------------------------------------------------------------//
// \file   TestCell.hpp
// \author Alex Robinson
// \brief  "White Box" Cell class testing class
//---------------------------------------------------------------------------//

#ifndef TEST_CELL_HPP
#define TEST_CELL_HPP

// Std Lib Includes
#include <string>

// FACEMC Includes
#include "Cell.hpp"
#include "Surface.hpp"

class TestCell : public FACEMC::Cell
{
public:
  TestCell()
    : FACEMC::Cell()
  { /* ... */ }

  TestCell( std::string &cell_definition )
    : FACEMC::Cell( cell_definition )
  { /* ... */ }

  virtual ~TestCell()
  { /* ... */ }
  
  // Allow public access to the Cell protected member functions
  using FACEMC::Cell::simplifyCellDefinitionString;
  using FACEMC::Cell::assignSurfaces;
  using FACEMC::Cell::calculateVolumeAndSurfaceAreas;
  using FACEMC::Cell::calculatePolyhedralCellVolumeAndSurfaceAreas;
  using FACEMC::Cell::calculatePolygonIntersectionPoints;
  using FACEMC::Cell::testIntersectionPoint;
  using FACEMC::Cell::createPolygon;
  using FACEMC::Cell::initializePolygon;
  using FACEMC::Cell::calculatePolygonArea;
  using FACEMC::Cell::calculatePolygonVolumeContribution;
  using FACEMC::Cell::calculateRotationallySymmetricCellVolumeAndSurfaceAreas;
  using FACEMC::Cell::calculateVolumeAndSurfaceAreasUsingMonteCarlo;
  using FACEMC::Cell::calculateBoundingBox;
  using FACEMC::Cell::getSurfaceArray;
};

#endif // end TEST_CELL_HPP

//---------------------------------------------------------------------------//
// end TestCell.hpp
//---------------------------------------------------------------------------//


