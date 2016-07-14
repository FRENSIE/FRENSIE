void bare_geom() 
{
    // Load the geometry library and initialize the geometry handler
    gSystem->Load("libGeom");
    new TGeoManager( "U_sphere", "Simple geometry used for verification of FaceMC results against MCNP." );

//---------------------------------------------------------------------------//
    // Material Definitions
    // TGeoMaterial( "name", A, Z, Density )
    // TGeoMedium( "name", Index, TGeoMaterial )
//---------------------------------------------------------------------------//

    // HEU (95% enriched) Uranium Metal ( rho = 18.9 g/cm^3 )
    TGeoMaterial *U_mat = new TGeoMaterial( "mat_1", 1, 1, -18.9 );
    TGeoMedium *U_med = new TGeoMedium( "med_1", 1, U_mat );

    // Void
    TGeoMaterial *void_mat = new TGeoMaterial( "void_mat", 0, 0, 0 );
    TGeoMedium *void_med = new TGeoMedium( "void_med", 2, void_mat );

    // Graveyard
    TGeoMaterial *terminal_mat = new TGeoMaterial( "graveyard", 0, 0, 0 );
    TGeoMedium *terminal_med = new TGeoMedium( "graveyard", 3, terminal_mat );

//---------------------------------------------------------------------------//
    // Volume Definition Form:
    // MakeSphere( "name", TGeoMedium, Minimum_Radius, Maximum_Radius )
//---------------------------------------------------------------------------//

    // Subcritical Bare Reactor of radius 5cm
    TGeoVolume *U_Sphere = gGeoManager->MakeSphere( "U_Sphere", U_med, 0.0, 5 );
    U_Sphere->SetUniqueID(1);

    // Void Cube of Side Height 20cm
    TGeoVolume *void_geom = gGeoManager->MakeBox("void_geom", void_med, 10., 10., 10.);
    void_geom->SetUniqueID(2);

    // Graveyard Cube of Side Height 25cm
    TGeoVolume *terminal_geom = gGeoManager->MakeBox("terminal_geom", terminal_med, 12.5, 12.5, 12.5);
    terminal_geom->SetUniqueID(3);
    gGeoManager->SetTopVolume( terminal_geom );

//---------------------------------------------------------------------------//
    // Heirarchy (Volume) Definitions
    // AddNode( Daughter_Node, Copy_Number )
//---------------------------------------------------------------------------//
    
    // Adding that the uranium sphere is a daughter of the void
    void_geom->AddNode( U_Sphere, 1 );

    // Adding that the void is a daughter of the graveyard
    terminal_geom->AddNode( void_geom, 1 );

//---------------------------------------------------------------------------//
    // Export and Drawing Capabilities
//---------------------------------------------------------------------------//

  // Close the geometry
  gGeoManager->CloseGeometry();
  gGeoManager->SetTopVisible();
  
  // Draw the geometry in an X-Window
  terminal_geom->Draw();
  
  gGeoManager->Export("bare_geom.root");
}  // end sample
//---------------------------------------------------------------------------//
// end sample01.C
//---------------------------------------------------------------------------//


