void sample01() 
{
    // Load the geometry library and initialize the geometry handler
    gSystem->Load("libGeom");
    new TGeoManager( "sample01", "Simple geometry used for verification of FRENSIE results against MCNP." );

    // Material Definition Form:
    // TGeoMaterial( "name", A, Z, Density )
    // TGeoMedium( "name", Index, TGeoMaterial )

    // Light Water ( rho = 0.995 g/cm^3 )
    TGeoMaterial* H2O_mat = new TGeoMaterial( "mat_1", 1, 1, -0.995 );
    TGeoMedium* H2O_med = new TGeoMedium( "med_1", 1, H2O_mat );

    // Void
    TGeoMaterial* void_mat = new TGeoMaterial( "void_mat", 0, 0, 0 );
    TGeoMedium* void_med = new TGeoMedium( "void_med", 2, void_mat );

    // Graveyard
    TGeoMaterial* terminal_mat = new TGeoMaterial( "graveyard", 0, , 0 );
    TGeoMedium* terminal_med = new TGeoMedium( "graveyard", 3, terminal_mat );

    // Volume Definition Form:
    // MakeSphere( "name", TGeoMedium, Minimum_Radius, Maximum_Radius )

    // Light Water Sphere of radius 20cm
    TGeoVolume *H2O_Sphere = gGeoManager->MakeSphere( "H2O_Sphere", H2O_medium, 0.0, 20.0 );
    H2O_Sphere->SetUniqueID(1);

    // Void Cube of Side Height 50cm
    TGeoVolume *void_geom = geom->MakeBox("void_geom", void_med, 25., 25., 25.);
    void_geom->SetUniqueID(2);

    // Graveyard Cube of Side Height 55cm
    TGeoVolume *terminal_geom = geom->MakeBox("terminal_geom", terminal_med, 27.5, 27.5, 27.5);
    terminal_geom->SetUniqueID(3);
}



