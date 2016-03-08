//---------------------------------------------------------------------------//
//!
//! \file   water_sphere.c
//! \author Alex Robinson
//! \brief  Geometry for Neutron water sphere at 293.6K verification problem
//!
//---------------------------------------------------------------------------//

void water_sphere()
{
  // Set up manager of the geometry world
  gSystem->Load( "libGeom" );
  
  TGeoManager* geom = new TGeoManager( 
                 "water_sphere",
                 "Geometry for the neutron water sphere at 293.6K test prob.");
  
  // Create the water material
  TGeoMaterial* water = new TGeoMaterial( "mat_1", 1, 1, -1.0 );
  TGeoMedium* med_1 = new TGeoMedium( "med_1", 1, water );

  // Create the void material
  TGeoMaterial* void_mat = new TGeoMaterial( "void", 0, 0, 0 );
  TGeoMedium* void_med = new TGeoMedium( "void_med", 2, void_mat );

  // Create the graveyard 
  TGeoMaterial* graveyard_mat = new TGeoMaterial( "graveyard", 0, 0, 0 );
  TGeoMedium* graveyard_med = new TGeoMedium( "graveyard", 3, graveyard_mat );

  // Create the water volume
  TGeoVolume* water_sphere_volume = 
    geom->MakeSphere( "SPHERE", med_1, 0.0, 3.0 );
  
  water_sphere_volume->SetUniqueID( 1 );

  // Create the void volume
  TGeoVolume* void_cube_volume = geom->MakeBox( 
                                             "CUBE", void_med, 6.5, 6.5, 6.5 );
  
  void_cube_volume->SetUniqueID( 2 );

  // Create the graveyard volume
  TGeoVolume* graveyard_volume = geom->MakeBox( 
                                   "GRAVEYARD", graveyard_med, 7.0, 7.0, 7.0 );

  graveyard_volume->SetUniqueID( 3 );

  // Place the water sphere inside of the void cube
  void_cube_volume->AddNode( water_sphere_volume, 1 );

  // Place the void cube inside of the graveyard
  graveyard_volume->AddNode( void_cube_volume, 1 );
  geom->SetTopVolume( graveyard_volume );

  // Close the geometry
  geom->SetTopVisible();
  geom->CloseGeometry();

  // Draw the geometry
  // graveyard_volume->Draw();

  // Export the geometry
  geom->Export( "water_sphere.root" );
  
  // Finished
  exit(0);
}

//---------------------------------------------------------------------------//
// end water_sphere.c
//---------------------------------------------------------------------------//
