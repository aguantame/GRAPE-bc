//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  Basic set-up : No Tagged Sources
//  (V1) Created: Mar 2, 2022 by Camden Ertley
//  (V2) Created: September 23, 2022 by Camden Ertley
//  (V3) Modified: Dec 26, 2022 by Karla Onate Melecio
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "Constants.hh"
#include "ScintSD.hh"



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  DetectorConstruction::DetectorConstruction()
  {
    fDetMessenger = new DetectorMessenger(this);
  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  DetectorConstruction::~DetectorConstruction()
  {
    delete fDetMessenger;
  }  

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  G4VPhysicalVolume* DetectorConstruction::Construct()
  {
    // Define materials 
    DefineMaterials();
    
    // Define volumes
    return DefineVolumes();
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void DetectorConstruction::DefineMaterials()
  { 
    // Materials defined using NIST Manager
    // https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html
    auto nistManager = G4NistManager::Instance();

    //======================================================
    // define elements
    //======================================================
    auto isotopes = true;
    G4Element* eH  = nistManager -> FindOrBuildElement( "H" , isotopes ); // 1
    // G4Element* eBe = nistManager -> FindOrBuildElement( "Be", isotopes ); // 4
    G4Element* eC  = nistManager -> FindOrBuildElement( "C" , isotopes ); // 6
    G4Element* eO  = nistManager -> FindOrBuildElement( "O" , isotopes ); // 8
    G4Element* eF  = nistManager -> FindOrBuildElement( "F" , isotopes ); // 9
    G4Element* eMg = nistManager -> FindOrBuildElement( "Mg", isotopes ); // 12
    G4Element* eAl = nistManager -> FindOrBuildElement( "Al", isotopes ); // 13
    G4Element* eSi = nistManager -> FindOrBuildElement( "Si", isotopes ); // 14
    G4Element* eCl = nistManager -> FindOrBuildElement( "Cl", isotopes ); // 17
    G4Element* eTi = nistManager -> FindOrBuildElement( "Ti", isotopes ); // 22
    G4Element* eCr = nistManager -> FindOrBuildElement( "Cr", isotopes ); // 24
    G4Element* eMn = nistManager -> FindOrBuildElement( "Mn", isotopes ); // 25
    G4Element* eFe = nistManager -> FindOrBuildElement( "Fe", isotopes ); // 26
    G4Element* eNi = nistManager -> FindOrBuildElement( "Ni", isotopes ); // 28
    G4Element* eCu = nistManager -> FindOrBuildElement( "Cu", isotopes ); // 29
    G4Element* eZn = nistManager -> FindOrBuildElement( "Zn", isotopes ); // 30
    G4Element* eGa = nistManager -> FindOrBuildElement( "Ga", isotopes ); // 31
    G4Element* eBr = nistManager -> FindOrBuildElement( "Br", isotopes ); // 35
    G4Element* eSn = nistManager -> FindOrBuildElement( "Sn", isotopes ); // 50
    // G4Element* eI  = nistManager -> FindOrBuildElement( "I" , isotopes ); // 53
    // G4Element* eCs = nistManager -> FindOrBuildElement( "Cs", isotopes ); // 55
    G4Element* eGd = nistManager -> FindOrBuildElement( "Gd", isotopes ); // 30
    G4Element* eAu = nistManager -> FindOrBuildElement( "Au", isotopes ); // 79
    G4Element* ePb = nistManager -> FindOrBuildElement( "Pb", isotopes ); // 82

    //======================================================
    // Define Elements and Materials
    //======================================================
    

    // G4 materials and elements
    nistManager -> FindOrBuildMaterial("G4_Galactic");
    nistManager -> FindOrBuildMaterial("G4_AIR");
    nistManager -> FindOrBuildMaterial("G4_Pb");
    nistManager -> FindOrBuildMaterial("G4_Si");
    nistManager -> FindOrBuildMaterial("G4_Sn");
    nistManager -> FindOrBuildMaterial("G4_Cu");


    // ALUMINUM 6061
    auto mAl6061 = new G4Material( "Aluminum6061", 2.6989*g/cm3, 9 );
      mAl6061 -> AddElement( eSi,  0.60*perCent );
      mAl6061 -> AddElement( eFe,  0.70*perCent );
      mAl6061 -> AddElement( eCu,  0.30*perCent );
      mAl6061 -> AddElement( eMn,  0.15*perCent );
      mAl6061 -> AddElement( eMg,  1.00*perCent );
      mAl6061 -> AddElement( eCr,  0.20*perCent );
      mAl6061 -> AddElement( eZn,  0.25*perCent );
      mAl6061 -> AddElement( eTi,  0.15*perCent );
      mAl6061 -> AddElement( eAl, 96.65*perCent );

     //----------------------------------
     // PCB Epoxy
     //----------------------------------
     auto mPCB_Epoxy = new G4Material( "PCB_Epoxy", 1.125*g/cm3, 3 );
       mPCB_Epoxy -> AddElement( eC, 15 );
       mPCB_Epoxy -> AddElement( eH, 44 );
       mPCB_Epoxy -> AddElement( eO,  7 );
 
     //----------------------------------
     // PCB Fiberglass
     //----------------------------------
     auto mPCB_FiberGlass = new G4Material( "PCB_FiberGlass", 2.65*g/cm3, 1 );
       mPCB_FiberGlass -> AddMaterial( nistManager->FindOrBuildMaterial( "G4_SILICON_DIOXIDE" ), 1 );

     //----------------------------------
     // NEMA G10 (from advanced examples)
     //----------------------------------
     auto mG10 = new G4Material( "G10", 1.850*g/cm3, 3 );
       mG10 -> AddMaterial( mPCB_FiberGlass, 77.3*perCent );
       mG10 -> AddMaterial( mPCB_Epoxy,      14.7*perCent );
       mG10 -> AddElement(  eCl,              8.0*perCent );

     //----------------------------------
     // NEMA FR4 (from advanced examples) - used in vertical columns
     //----------------------------------
     auto mFR4 = new G4Material( "FR4", 1.850*g/cm3, 4 );
       mFR4 -> AddMaterial( mPCB_FiberGlass, 61.3*perCent );
       mFR4 -> AddMaterial( mPCB_Epoxy,      14.7*perCent );
       mFR4 -> AddElement(  eBr,              8.0*perCent );
       mFR4 -> AddElement(  eO,              16.0*perCent );

     //----------------------------------
     // PC Baord 80% G10 circuit board, 20% generic electronics
     //----------------------------------
     auto mPCB = new G4Material( "PCB_Mat", 1.8*g/cm3, 7 );
       mPCB -> AddMaterial( mG10, 80.0*perCent );
       mPCB -> AddElement(  eSi,   8.0*perCent );
       mPCB -> AddElement(  eCu,   6.0*perCent );
       mPCB -> AddElement(  eAl,   3.0*perCent );
       mPCB -> AddElement(  eFe,   1.0*perCent );
       mPCB -> AddElement(  eSn,   1.0*perCent );
       mPCB -> AddElement(  ePb,   1.0*perCent );

     //----------------------------------
     //! Vetical Baord 90% FR4 circuit board, 10% copper, gold, nickel
     //! 10% arbitrary; density is a guess
     //----------------------------------
     auto mVCB = new G4Material( "VCB_Mat", 1.9*g/cm3, 4 );
       mVCB -> AddMaterial( mFR4, 90.0*perCent );
       mVCB -> AddElement(  eCu,   6.0*perCent );
       mVCB -> AddElement(  eAu,   3.0*perCent );
       mVCB -> AddElement(  eNi,   1.0*perCent );


     //----------------------------------
     // SiPM (Hamamatsu S13361-3050AE-04)
     //----------------------------------
     // Bisphenol A which is the basis of each epoxy [G4SiPM toolkit].
     auto mSiPM_Epoxy = new G4Material( "BisphenolA", 1.2*g/cm3, 3);
       mSiPM_Epoxy -> AddElement( eSi, 15 );
       mSiPM_Epoxy -> AddElement( eH,  16 );
       mSiPM_Epoxy -> AddElement( eO,   2 );

     auto mSiPM_Sensor = new G4Material( "SiPM_Sensor", 1.2*g/cm3, 5 ); // density is a guess
       mSiPM_Sensor -> AddMaterial( mSiPM_Epoxy, 60.1*perCent );
       mSiPM_Sensor -> AddElement( eSi, 36.9*perCent );
       mSiPM_Sensor -> AddElement( eCu,  1.0*perCent );
       mSiPM_Sensor -> AddElement( eSn,  1.0*perCent );
       mSiPM_Sensor -> AddElement( ePb,  1.0*perCent );

     auto mSiPM_PCB = new G4Material( "SiPM_PCB", 1.983*g/cm3, 5 );
       mSiPM_PCB -> AddMaterial( mFR4, 94.0*perCent);
       mSiPM_PCB -> AddElement( eFe,    1.0*perCent );
       mSiPM_PCB -> AddElement( eCu,    3.0*perCent );
       mSiPM_PCB -> AddElement( eSn,    1.0*perCent );
       mSiPM_PCB -> AddElement( ePb,    1.0*perCent );

     auto mSiPM = new G4Material( "SiPM_Mat", 4.0*g/cm3, 2 ); // density is a guess, sensor ~1g (1.3 cm x 1.3 cm x .135 cm)
       mSiPM -> AddMaterial( mSiPM_PCB,    66.7*perCent );
       mSiPM -> AddMaterial( mSiPM_Sensor, 33.3*perCent );


    // Delrin
    auto mDelrin = new G4Material( "Delrin", 1.415*g/cm3, 3 );
      mDelrin -> AddElement( eH , 2 );
      mDelrin -> AddElement( eC , 1 );
      mDelrin -> AddElement( eO , 1 );
    
    // Connector
    auto mConnector = new G4Material( "ConnectorMaterial", 5.158*g/cm3, 2 );
      mConnector -> AddElement( eCu , 50.*perCent );
      mConnector -> AddMaterial( mDelrin , 50.*perCent );
      

    // Gigahertz Optik ODM98 Optical Diffuse Material
    // http://www.gigahertz-optik.de/476-1-ODM98+Specification.html
    auto mODM = new G4Material( "ODM", 1.5*g/cm3, 2 );
      mODM -> AddElement( eC, 24.0183*perCent );
      mODM -> AddElement( eF, 75.9817*perCent );

     //----------------------------------
     // Optical Pad (EJ-560, guess it's Methyl phenyl silicone)
     //----------------------------------
     auto mOpticalPad = new G4Material( "OpticalPad_Mat", 1.03*g/cm3, 4 );
       mOpticalPad -> AddElement( eC, 22 );
       mOpticalPad -> AddElement( eH, 34 );
       mOpticalPad -> AddElement( eSi, 4 );
       mOpticalPad -> AddElement( eO,  3 );

    //----------------------------------
    //! Detectors Wrapping (1.025*mm thick)
    //! Volumne (6 x (12.5 mm x 12.5 mm x 1.025 mm)) = 1302 mm
    //! 4 Teflon : 1 Kapton
    //! Kapton = 1.42 g/cm^3 ; Teflon = 2.2 g/cm^3 -> total = 2.005 g/cm^3
    //----------------------------------
    auto mDetectorWrap = new G4Material( "Reflective_Wrap", 2.005*g/cm3, 2 );
      mDetectorWrap -> AddMaterial( nistManager -> FindOrBuildMaterial("G4_TEFLON"), 75.*perCent);
      mDetectorWrap -> AddMaterial( nistManager -> FindOrBuildMaterial("G4_KAPTON"), 25.*perCent);
    
    //! O-Ring butyl-rubber used as placeholder for Buna-N (C7H9N1) 
    nistManager -> FindOrBuildMaterial("G4_RUBBER_BUTYL");
  

    //! Column Housing (3D-printed Nylon-12) pre-defined Nylon-11-Rilsan used as substitute
    nistManager -> FindOrBuildMaterial("G4_NYLON-11_RILSAN");

     //------------------------------------------------------
     // Scintillators
     //------------------------------------------------------
    // PLASTIC ( Nist G4_PLASTIC_SC_VINYLTOLUENE ? )
    auto mPlastic = nistManager->FindOrBuildMaterial( "G4_PLASTIC_SC_VINYLTOLUENE" );
      // auto birk = 0.0159*g/(cm2*MeV) / mPlastic->GetDensity();// Craun & Smith NIM 80 (1970)
      mPlastic -> GetIonisation() -> SetBirksConstant(0.154*mm/MeV); // original


    // STILBENE  ( Nist G4_STILBENE ? )
    auto mStilbene = nistManager -> FindOrBuildMaterial( "G4_STILBENE" );
      // auto birk = 0.00955*g/(cm2*MeV) / mStilbene->GetDensity();// Craun & Smith NIM 80 (1970)
      // auto birk = 0.113*mm/MeV; // Papadopoulos NIM 401
      mStilbene -> GetIonisation() -> SetBirksConstant(0.098*mm/MeV);
    
    // p-TERPHENYL  ( Nist G4_TERPHENYL ? )
    auto mTerphenyl = nistManager -> FindOrBuildMaterial( "G4_TERPHENYL" );
      mTerphenyl -> GetIonisation() -> SetBirksConstant(0.098*mm/MeV); // needs updated
   
    // GAGG  ( Gd3Al2Ga3O12 )
    auto mGAGG = new G4Material( "GAGG", 6.67*g/cm3, 4 );
      mGAGG -> AddElement( eGa,  3 );
      mGAGG -> AddElement( eAl,  2 );
      mGAGG -> AddElement( eGd,  3 );
      mGAGG -> AddElement( eO , 12 );
      mGAGG -> GetIonisation() -> SetBirksConstant(0.008*mm/MeV); // needs updated
      // https://indico.cern.ch/event/642256/contributions/2958340/attachments/1654921/2648752/CALOR2018_GAGG_Dormenev.pdf

    //------------------------------------------------------
    // Print materials list
    //------------------------------------------------------
    //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
  {
    //======================================================
    // Cleanup old geometry
    //======================================================
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    //======================================================
    // Materials
    //======================================================
    auto mVacuum = G4Material::GetMaterial("G4_Galactic");
    // auto mAir = G4Material::GetMaterial("G4_AIR");
    auto mPb = G4Material::GetMaterial("G4_Pb");
    auto mSn = G4Material::GetMaterial("G4_Sn");
    auto mCu = G4Material::GetMaterial("G4_Cu");
    
    auto mNylon = G4Material::GetMaterial( "G4_NYLON-11_RILSAN" );
    auto mDetectorWrap = G4Material::GetMaterial( "Reflective_Wrap" );
    auto mAl6061 = G4Material::GetMaterial( "Aluminum6061" );
    auto mVCB = G4Material::GetMaterial( "VCB_Mat" );
    auto mPCB = G4Material::GetMaterial( "PCB_Mat" );
    auto mConnector = G4Material::GetMaterial( "ConnectorMaterial" );
    auto mSiPM = G4Material::GetMaterial( "SiPM_Mat" );
    auto mOPad = G4Material::GetMaterial( "OpticalPad_Mat" );
    auto mODM = G4Material::GetMaterial( "ODM" );
    auto mORing = G4Material::GetMaterial( "G4_RUBBER_BUTYL" );

    auto mScintC = G4Material::GetMaterial("GAGG");
    auto mScintS = G4Material::GetMaterial("G4_TERPHENYL");
    auto mScintCal = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    //======================================================
    // Volumes
    //======================================================


    //------------------------------------------------------
    // World
    //------------------------------------------------------
    // SOLID VOLUME
    auto world_X = kWorld_Xsize;
    auto world_Y = kWorld_Ysize;
    auto world_Z = kWorld_Zsize;

    auto world_S = new G4Box(
                  "World_S",            // its name
                  world_X/2,            // its X dimension 
                  world_Y/2,            // its Y dimension 
                  world_Z/2);           // its Z dimension 

    // LOGICAL VOLUME
    auto world_LV = new G4LogicalVolume(
                  world_S,              // its solid
                  mVacuum,              // its material
                  "World_LV");          // its name

    // PHYSICAL VOLUME
    auto world_PV = new G4PVPlacement(
                  0,                    // no rotation
                  G4ThreeVector(),      // at (0,0,0)
                  world_LV,             // its logical volume
                  "World_PV",           // its name
                  0,                    // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
    
    
    //------------------------------------------------------
    // Instrument
    //------------------------------------------------------

    //----------------------------------
    // Payload Module
    //----------------------------------
    // SOLID VOLUME
    auto pyld_mod_X = kPayload_Module_Xsize;
    auto pyld_mod_Y = kPayload_Module_Ysize;
    auto pyld_mod_Z = kPayload_Module_Zsize;

    auto pyld_module_S = new G4Box(
                  "Payload_Module_S",           // its name
                  pyld_mod_X/2,              // its X dimension 
                  pyld_mod_Y/2,              // its Y dimension
                  pyld_mod_Z/2);             // its Z dimension

    // LOGICAL VOLUME
    auto pyld_module_LV = new G4LogicalVolume(
                  pyld_module_S,             // its solid
                  mVacuum,              // its material
                  "Payload_Module_LV");         // its name

    // PHYSICAL VOLUME
    // auto pyld_mod_Xpos = 0.0*mm;
    auto pyld_mod_Xpos = 0.0*mm;
    auto pyld_mod_Ypos = (kENCL_Side1_Zsize/2 - kScint_Zsize/2)*std::sin( fZenithAngle );
    auto pyld_mod_Zpos = pyld_mod_Z/2*std::cos( fZenithAngle ) + pyld_mod_X/2*(std::cos( fAzimuthAngle ) + std::sin( fAzimuthAngle ))*std::sin( fZenithAngle );
    auto pyld_mod_Pos = G4ThreeVector( pyld_mod_Xpos, pyld_mod_Ypos, pyld_mod_Zpos );
    auto pyld_mod_RotMat = new G4RotationMatrix();
    pyld_mod_RotMat -> setTheta( fZenithAngle );
    pyld_mod_RotMat -> setPsi( fAzimuthAngle );

    fPhysicalModule = new G4PVPlacement(
                  pyld_mod_RotMat,           // its rotation
                  pyld_mod_Pos,              // its position
                  pyld_module_LV,            // its logical volume
                  "Payload_Module_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    
    //----------------------------------
    // Detector Module
    //----------------------------------
    // SOLID VOLUME
    auto det_mod_X = kDet_Module_Xsize;
    auto det_mod_Y = kDet_Module_Ysize;
    auto det_mod_Z = kDet_Module_Zsize;

    auto det_module_S = new G4Box(
                  "Det_Module_S",           // its name
                  det_mod_X/2,              // its X dimension 
                  det_mod_Y/2,              // its Y dimension
                  det_mod_Z/2);             // its Z dimension

    // LOGICAL VOLUME
    auto det_module_LV = new G4LogicalVolume(
                  det_module_S,             // its solid
                  mVacuum,              // its material
                  "Det_Module_LV");         // its name

    // PHYSICAL VOLUME
    // auto det_mod_Xpos = 0.0*mm;
    auto det_mod_Xpos = 0.0*mm;
    auto det_mod_Ypos = 0.0*mm;
    auto det_mod_Zpos = kPayload_Module_Zsize/2 - kDet_Module_Zsize/2;
    auto det_mod_Pos = G4ThreeVector( det_mod_Xpos, det_mod_Ypos, det_mod_Zpos );
    auto det_mod_RotMat = new G4RotationMatrix();
    det_mod_RotMat -> setTheta( fZenithAngle );
    det_mod_RotMat -> setPsi( fAzimuthAngle );

    new G4PVPlacement(
                  det_mod_RotMat,           // its rotation
                  det_mod_Pos,              // its position
                  det_module_LV,            // its logical volume
                  "Det_Module_PV",          // its name
                  pyld_module_LV,             // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // DAQ Module
    //----------------------------------
    // SOLID VOLUME
    auto daq_mod_X = kDAQ_Module_Xsize;
    auto daq_mod_Y = kDAQ_Module_Ysize;
    auto daq_mod_Z = kDAQ_Module_Zsize;

    auto daq_module_S = new G4Box(
                  "DAQ_Module_S",           // its name
                  daq_mod_X/2,              // its X dimension 
                  daq_mod_Y/2,              // its Y dimension
                  daq_mod_Z/2);             // its Z dimension

    // LOGICAL VOLUME
    auto daq_module_LV = new G4LogicalVolume(
                  daq_module_S,             // its solid
                  mVacuum,              // its material
                  "DAQ_Module_LV");         // its name

    // PHYSICAL VOLUME
    // auto daq_mod_Xpos = 0.0*mm;
    auto daq_mod_Xpos = 0.0*mm;
    auto daq_mod_Ypos = 0.0*mm;
    auto daq_mod_Zpos = det_mod_Zpos - kDet_Module_Zsize/2 - kDAQ_Module_Zsize/2;
    auto daq_mod_Pos = G4ThreeVector( daq_mod_Xpos, daq_mod_Ypos, daq_mod_Zpos );
    auto daq_mod_RotMat = new G4RotationMatrix();
    daq_mod_RotMat -> setTheta( fZenithAngle );
    daq_mod_RotMat -> setPsi( fAzimuthAngle );

    new G4PVPlacement(
                  daq_mod_RotMat,           // its rotation
                  daq_mod_Pos,              // its position
                  daq_module_LV,            // its logical volume
                  "DAQ_Module_PV",          // its name
                  pyld_module_LV,             // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Power Module
    //----------------------------------
    // SOLID VOLUME
    auto pwr_mod_X = kPower_Module_Xsize;
    auto pwr_mod_Y = kPower_Module_Ysize;
    auto pwr_mod_Z = kPower_Module_Zsize;

    auto pwr_module_S = new G4Box(
                  "Power_Module_S",           // its name
                  pwr_mod_X/2,              // its X dimension 
                  pwr_mod_Y/2,              // its Y dimension
                  pwr_mod_Z/2);             // its Z dimension

    // LOGICAL VOLUME
    auto pwr_module_LV = new G4LogicalVolume(
                  pwr_module_S,             // its solid
                  mVacuum,              // its material
                  "Power_Module_LV");         // its name

    // PHYSICAL VOLUME
    // auto pwr_mod_Xpos = 0.0*mm;
    auto pwr_mod_Xpos = 0.0*mm;
    auto pwr_mod_Ypos = 0.0*mm;
    auto pwr_mod_Zpos = daq_mod_Zpos - kDAQ_Module_Zsize/2 - kPower_Module_Zsize/2;
    auto pwr_mod_Pos = G4ThreeVector( pwr_mod_Xpos, pwr_mod_Ypos, pwr_mod_Zpos );
    auto pwr_mod_RotMat = new G4RotationMatrix();
    pwr_mod_RotMat -> setTheta( fZenithAngle );
    pwr_mod_RotMat -> setPsi( fAzimuthAngle );

    new G4PVPlacement(
                  pwr_mod_RotMat,           // its rotation
                  pwr_mod_Pos,              // its position
                  pwr_module_LV,            // its logical volume
                  "Power_Module_PV",          // its name
                  pyld_module_LV,             // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Power / Computer Module
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //----------------------------------
      // Enclosure 3: Power Supply/Computer Container
      //----------------------------------
      // SOLID VOLUME
      auto Power_ENCL_X = kPower_ENCL_Xsize;
      auto Power_ENCL_Y = kPower_ENCL_Ysize;
      auto Power_ENCL_Z = kPower_ENCL_Zsize;
  
      G4VSolid* Power_ENCL_S = new G4Box(
                    "Power_ENCL_S",         // its name
                    Power_ENCL_X/2,         // its X dimension
                    Power_ENCL_Y/2,         // its Y dimension
                    Power_ENCL_Z/2);        // its Z dimension
  
      // Hole
      auto Power_ENCL_Hole_X = kPower_ENCL_Hole_Xsize;
      auto Power_ENCL_Hole_Y = kPower_ENCL_Hole_Ysize;
      auto Power_ENCL_Hole_Z = kPower_ENCL_Hole_Zsize;
  
      auto Power_ENCL_Hole_S = new G4Box(
                    "Power_ENCL_S",         // its name
                    Power_ENCL_Hole_X/2,         // its X dimension
                    Power_ENCL_Hole_Y/2,         // its Y dimension
                    Power_ENCL_Hole_Z/2);        // its Z dimension
  
      auto Power_ENCL_Hole_Xpos = 0.0*mm;
      auto Power_ENCL_Hole_Ypos = 0.0*mm;
      auto Power_ENCL_Hole_Zpos = Power_ENCL_Hole_Z/2 - Power_ENCL_Z/2  + kPower_ENCL_Thickness;
      auto Power_ENCL_Hole_pos = G4ThreeVector( Power_ENCL_Hole_Xpos, Power_ENCL_Hole_Ypos, Power_ENCL_Hole_Zpos );
      Power_ENCL_S = new G4SubtractionSolid( 
                    "Power_ENCL_S",         // its name
                    Power_ENCL_S,           // starting solid
                    Power_ENCL_Hole_S,      // solid to be subtracted
                    0,                    // its rotation
                    Power_ENCL_Hole_pos );  // its position
  
  
      // LOGICAL VOLUME
      auto Power_ENCL_LV = new G4LogicalVolume(
                    Power_ENCL_S,           // its solid
                    mAl6061,                 // its material
                    "Power_ENCL_LV");       // its name
  
      // PHYSICAL VOLUME
      auto Power_ENCL_Xpos = 0.0*mm;
      auto Power_ENCL_Ypos = 0.0*mm;
      auto Power_ENCL_Zpos = 0.0*mm;
      auto Power_ENCL_Pos = G4ThreeVector( Power_ENCL_Xpos, Power_ENCL_Ypos, Power_ENCL_Zpos );
  
      new G4PVPlacement(
                    0,                    // its rotation
                    Power_ENCL_Pos,         // its position
                    Power_ENCL_LV,          // its logical volume
                    "Power_ENCL_PV",        // its name
                    pwr_module_LV,        // its mother  volume
                    false,                // no boolean operation
                    0,                    // copy number
                    fCheckOverlaps);      // checking overlaps 


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // DAQ Module
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      //----------------------------------
      // Enclosure 2: DAQ Container
      //----------------------------------
      // SOLID VOLUME
      auto DAQ_ENCL_X = kDAQ_ENCL_Xsize;
      auto DAQ_ENCL_Y = kDAQ_ENCL_Ysize;
      auto DAQ_ENCL_Z = kDAQ_ENCL_Zsize;
  
      G4VSolid* DAQ_ENCL_S = new G4Box(
                    "DAQ_ENCL_S",         // its name
                    DAQ_ENCL_X/2,         // its X dimension
                    DAQ_ENCL_Y/2,         // its Y dimension
                    DAQ_ENCL_Z/2);        // its Z dimension
  
      // Hole
      auto DAQ_ENCL_Hole_X = kDAQ_ENCL_Hole_Xsize;
      auto DAQ_ENCL_Hole_Y = kDAQ_ENCL_Hole_Ysize;
      auto DAQ_ENCL_Hole_Z = kDAQ_ENCL_Hole_Zsize;
  
      auto DAQ_ENCL_Hole_S = new G4Box(
                    "DAQ_ENCL_S",         // its name
                    DAQ_ENCL_Hole_X/2,         // its X dimension
                    DAQ_ENCL_Hole_Y/2,         // its Y dimension
                    DAQ_ENCL_Hole_Z/2);        // its Z dimension
  
      auto DAQ_ENCL_Hole_Xpos = 0.0*mm;
      auto DAQ_ENCL_Hole_Ypos = 0.0*mm;
      auto DAQ_ENCL_Hole_Zpos = DAQ_ENCL_Hole_Z/2 - DAQ_ENCL_Z/2  + kDAQ_ENCL_BOT_Thickness;
      auto DAQ_ENCL_Hole_pos = G4ThreeVector( DAQ_ENCL_Hole_Xpos, DAQ_ENCL_Hole_Ypos, DAQ_ENCL_Hole_Zpos );
      DAQ_ENCL_S = new G4SubtractionSolid( 
                    "DAQ_ENCL_S",         // its name
                    DAQ_ENCL_S,           // starting solid
                    DAQ_ENCL_Hole_S,      // solid to be subtracted
                    0,                    // its rotation
                    DAQ_ENCL_Hole_pos );  // its position
  
  
      // LOGICAL VOLUME
      auto DAQ_ENCL_LV = new G4LogicalVolume(
                    DAQ_ENCL_S,           // its solid
                    mAl6061,                 // its material
                    "DAQ_ENCL_LV");       // its name
  
      // PHYSICAL VOLUME
      auto DAQ_ENCL_Xpos = 0.0*mm;
      auto DAQ_ENCL_Ypos = 0.0*mm;
      auto DAQ_ENCL_Zpos = 0.0*mm;
      auto DAQ_ENCL_Pos = G4ThreeVector( DAQ_ENCL_Xpos, DAQ_ENCL_Ypos, DAQ_ENCL_Zpos );
  
      new G4PVPlacement(
                    0,                    // its rotation
                    DAQ_ENCL_Pos,         // its position
                    DAQ_ENCL_LV,          // its logical volume
                    "DAQ_ENCL_PV",        // its name
                    daq_module_LV,        // its mother  volume
                    false,                // no boolean operation
                    0,                    // copy number
                    fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Module Interface Board (MIB)
    //----------------------------------
    
    // Solid Volume
    auto MIB_X = kMIB_Xsize;
    auto MIB_Y = kMIB_Ysize;
    auto MIB_Z = kMIB_Zsize;

    auto MIB_S = new G4Box(
                  "MIB_S",              // its name
                  MIB_X/2,              // its X dimension 
                  MIB_Y/2,              // its Y dimension
                  MIB_Z/2);             // its Z dimension
    
    // Logical Volume     
    auto MIB_LV = new G4LogicalVolume(
                  MIB_S,                // its solid
                  mPCB,                  // its material
                  "MIB_LV");            // its name

    auto MIB_Xpos = 0.0*mm;
    auto MIB_Ypos = 0.0*mm;
    auto MIB_Zpos = kDAQ_Module_Zsize/2 - kMIB_Zoffset - MIB_Z/2; 
    // APB_Con_Zpos + APB_Con_Z/2 + kAPB_MIB_Zoffset + MIB_Z/2;
    auto MIB_Pos = G4ThreeVector( MIB_Xpos, MIB_Ypos, MIB_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIB_Pos,              // its position
                  MIB_LV,               // its logical volume
                  "MIB_PV",             // its name
                  daq_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Base Plate
    //----------------------------------
    // Solid Volume
    auto ENCL_Bot_X = kENCL_Bot_Xsize;
    auto ENCL_Bot_Y = kENCL_Bot_Ysize;
    auto ENCL_Bot_Z = kENCL_Bot_Zsize;

    auto ENCL_Bot_S = new G4Box(
                  "ENCL_Bot_S",         // its name
                  ENCL_Bot_X/2,         // its X dimension 
                  ENCL_Bot_Y/2,         // its Y dimension
                  ENCL_Bot_Z/2);        // its Z dimension
    
    // Logical Volume
    auto ENCL_Bot_LV = new G4LogicalVolume(
                  ENCL_Bot_S,           // its solid
                  mAl6061,              // its material
                  "ENCL_Bot_LV");       // its name

    // Pysical Volume
    auto ENCL_Bot_Xpos = 0.0*mm;
    auto ENCL_Bot_Ypos = 0.0*mm;
    auto ENCL_Bot_Zpos = -kDAQ_Module_Zsize/2 + kINNER_SHLD_Zoffset + kENCL_Bot_Zsize/2;
    auto ENCL_Bot_Pos = G4ThreeVector( ENCL_Bot_Xpos, ENCL_Bot_Ypos, ENCL_Bot_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Bot_Pos,         // its position
                  ENCL_Bot_LV,          // its logical volume
                  "ENCL_Bot_PV",        // its name
                  daq_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // Base Shield - Lead 
    //----------------------------------
    // Solid Volume
    auto SHPB_Bot_X = kSHPB_Bot_Xsize;
    auto SHPB_Bot_Y = kSHPB_Bot_Ysize;
    auto SHPB_Bot_Z = kSHPB_Bot_Zsize;

    auto SHPB_Bot_S = new G4Box(
                  "SHPB_Bot_S",         // its name
                  SHPB_Bot_X/2,         // its X dimension 
                  SHPB_Bot_Y/2,         // its Y dimension
                  SHPB_Bot_Z/2);        // its Z dimension
    
    // Logical Volume
    auto SHPB_Bot_LV = new G4LogicalVolume(
                  SHPB_Bot_S,           // its solid
                  mPb,                  // its material
                  "SHPB_Bot_LV");       // its name

    // Pysical Volume
    auto SHPB_Bot_Xpos = 0.0*mm;
    auto SHPB_Bot_Ypos = 0.0*mm;
    auto SHPB_Bot_Zpos = ENCL_Bot_Zpos + kENCL_Bot_Zsize/2 + kSHPB_Bot_Zsize/2; //155.6*mm
    auto SHPB_Bot_Pos = G4ThreeVector( SHPB_Bot_Xpos, SHPB_Bot_Ypos, SHPB_Bot_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHPB_Bot_Pos,         // its position
                  SHPB_Bot_LV,          // its logical volume
                  "SHPB_Bot_PV",        // its name
                  daq_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Base Shield - Tin 
    //----------------------------------
    // Solid Volume
    auto SHSN_Bot_X = kSHSN_Bot_Xsize;
    auto SHSN_Bot_Y = kSHSN_Bot_Ysize;
    auto SHSN_Bot_Z = kSHSN_Bot_Zsize;

    auto SHSN_Bot_S = new G4Box(
                  "SHSN_Bot_S",         // its name
                  SHSN_Bot_X/2,         // its X dimension 
                  SHSN_Bot_Y/2,         // its Y dimension
                  SHSN_Bot_Z/2);        // its Z dimension
    
    // Logical Volume
    auto SHSN_Bot_LV = new G4LogicalVolume(
                  SHSN_Bot_S,           // its solid
                  mSn,                  // its material
                  "SHSN_Bot_LV");       // its name

    // Pysical Volume
    auto SHSN_Bot_Xpos = 0.0*mm;
    auto SHSN_Bot_Ypos = 0.0*mm;
    auto SHSN_Bot_Zpos = SHPB_Bot_Zpos + kSHPB_Bot_Zsize/2 + kSHSN_Bot_Zsize/2;
    auto SHSN_Bot_Pos = G4ThreeVector( SHSN_Bot_Xpos, SHSN_Bot_Ypos, SHSN_Bot_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHSN_Bot_Pos,         // its position
                  SHSN_Bot_LV,          // its logical volume
                  "SHSN_Bot_PV",        // its name
                  daq_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Base Shield - Copper 
    //----------------------------------
    // Solid Volume
    auto SHCU_Bot_X = kSHCU_Bot_Xsize;
    auto SHCU_Bot_Y = kSHCU_Bot_Ysize;
    auto SHCU_Bot_Z = kSHCU_Bot_Zsize;

    auto SHCU_Bot_S = new G4Box(
                  "SHCU_Bot_S",         // its name
                  SHCU_Bot_X/2,         // its X dimension 
                  SHCU_Bot_Y/2,         // its Y dimension
                  SHCU_Bot_Z/2);        // its Z dimension
    
    // Logical Volume
    auto SHCU_Bot_LV = new G4LogicalVolume(
                  SHCU_Bot_S,           // its solid
                  mCu,                  // its material
                  "SHCU_Bot_LV");       // its name

    // Pysical Volume
    auto SHCU_Bot_Xpos = 0.0*mm;
    auto SHCU_Bot_Ypos = 0.0*mm;
    auto SHCU_Bot_Zpos = SHSN_Bot_Zpos + kSHSN_Bot_Zsize/2 + kSHCU_Bot_Zsize/2;
    auto SHCU_Bot_Pos = G4ThreeVector( SHCU_Bot_Xpos, SHCU_Bot_Ypos, SHCU_Bot_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHCU_Bot_Pos,         // its position
                  SHCU_Bot_LV,          // its logical volume
                  "SHCU_Bot_PV",        // its name
                  daq_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

   //----------------------------------
    // Analog Power Boards
    //----------------------------------
    // Solid Volume
    auto APB_X = kAPB_Xsize;
    auto APB_Y = kAPB_Ysize;
    auto APB_Z = kAPB_Zsize;

    auto APB_S = new G4Box(
                  "APB_S",              // its name
                  APB_X/2,              // its X dimension 
                  APB_Y/2,              // its Y dimension
                  APB_Z/2);             // its Z dimension

    // Logical Volume
    auto APB_LV = new G4LogicalVolume(
                  APB_S,                // its solid
                  mPCB,                  // its material
                  "APB_LV");            // its name

    auto APB_Xnum = kNumAPB;
    auto APB_Xpitch = kAPB_X_Pitch;
    auto APB_Xoffset = ( kScint_Xpitch * (kNumAPB) / 2 );
    auto APB_Xpos = 0.0*mm;
    auto APB_Ypos = 0.0*mm;
    auto APB_Zpos = ENCL_Bot_Zpos - ENCL_Bot_Z/2 - kAPB_Zoffset - APB_Z/2;
    auto APB_Pos = G4ThreeVector();

    for (auto row = 0; row<APB_Xnum; row++) {
      APB_Xpos =  ( row * APB_Xpitch ) - APB_Xoffset;
      APB_Pos = G4ThreeVector( APB_Xpos, APB_Ypos, APB_Zpos );

      new G4PVPlacement(
                  0,                    // its rotation
                  APB_Pos,              // its position
                  APB_LV,               // its logical volume
                  "APB_PV",             // its name
                  daq_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
    }



    //----------------------------------
    // APB Connectors
    //----------------------------------
    // Solid Volume
    auto APB_Con_Side1_X = kAPB_Con_Xsize;
    auto APB_Con_Side1_Y = kAPB_Con_Ysize;
    auto APB_Con_Side1_Z = kAPB_Con_Zsize;

    auto APB_Con_Side1_S = new G4Box(
                  "APB_Con_Side1_S",       // its name
                  APB_Con_Side1_X/2,       // its X dimension 
                  APB_Con_Side1_Y/2,       // its Y dimension
                  APB_Con_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto APB_Con_Side1_LV = new G4LogicalVolume(
                  APB_Con_Side1_S,         // its solid
                  mConnector,              // its material
                  "APB_Con_Side1_LV");     // its name

    // Pysical Volume

    auto APB_Con_Side1_Xpos = 0.0*mm;
    auto APB_Con_Side1_Ypos = 0.0*mm;
    auto APB_Con_Side1_Zpos =  MIB_Zpos - MIB_Z/2 - APB_Con_Side1_Z/2; 
    auto APB_Con_Side1_Pos = G4ThreeVector();

    auto APB_Con_Side_Num = 2;

    APB_Con_Side1_Xpos = MIB_X/2 - APB_Con_Side1_X/2;
    auto APB_Con_Pitch = MIB_Y/2;
    for (auto row = 0; row<APB_Con_Side_Num; row++) {
      APB_Con_Side1_Ypos =  ( row * (APB_Con_Pitch + APB_Con_Side1_Y/2)) - MIB_Y/4;
      APB_Con_Side1_Pos = G4ThreeVector( APB_Con_Side1_Xpos, APB_Con_Side1_Ypos, APB_Con_Side1_Zpos );

      new G4PVPlacement(
                    0,                    // its rotation
                    APB_Con_Side1_Pos,       // its position
                    APB_Con_Side1_LV,        // its logical volume
                    "APB_Con_Side1_PV",      // its name
                    daq_module_LV,            // its mother  volume
                    false,                // no boolean operation
                    0,                    // copy number
                    fCheckOverlaps);      // checking overlaps
    } 

    APB_Con_Side1_Xpos = -MIB_X/2 + APB_Con_Side1_X/2;
    APB_Con_Side1_Ypos = 0.0*mm;
    for (auto row = 0; row<APB_Con_Side_Num; row++) {
      APB_Con_Side1_Ypos =  ( row * (APB_Con_Pitch + APB_Con_Side1_Y/2)) - MIB_Y/4;
      APB_Con_Side1_Pos = G4ThreeVector( APB_Con_Side1_Xpos, APB_Con_Side1_Ypos, APB_Con_Side1_Zpos );

      new G4PVPlacement(
                    0,                    // its rotation
                    APB_Con_Side1_Pos,       // its position
                    APB_Con_Side1_LV,        // its logical volume
                    "APB_Con_Side1_PV",      // its name
                    daq_module_LV,            // its mother  volume
                    false,                // no boolean operation
                    0,                    // copy number
                    fCheckOverlaps);      // checking overlaps 
    }

    // Connector Side2
    auto APB_Con_Side2_X = kAPB_Con_Ysize;
    auto APB_Con_Side2_Y = kAPB_Con_Xsize;
    auto APB_Con_Side2_Z = kAPB_Con_Zsize;

    auto APB_Con_Side2_S = new G4Box(
                  "APB_Con_Side2_S",       // its name
                  APB_Con_Side2_X/2,       // its X dimension 
                  APB_Con_Side2_Y/2,       // its Y dimension
                  APB_Con_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto APB_Con_Side2_LV = new G4LogicalVolume(
                  APB_Con_Side2_S,         // its solid
                  mConnector,              // its material
                  "APB_Con_Side2_LV");     // its name

    // Pysical Volume
    auto APB_Con_Side2_Xpos = 0.0*mm;
    auto APB_Con_Side2_Ypos = 0.0*mm;
    auto APB_Con_Side2_Zpos =  MIB_Zpos - MIB_Z/2 - APB_Con_Side2_Z/2; 
    auto APB_Con_Side2_Pos = G4ThreeVector();

    // auto APB_Con_Side2_Xnum = 2;
    // auto APB_Con_Side2_Xpitch = APB_Xpitch;
    // for (auto row = 0; row<APB_Con_Side2_Xnum; row++) {
    //   APB_Con_Xpos =  ( row * APB_Con_Side2_Xpitch ) - APB_Con_Side2_Xoffset;
    //   APB_Con_Pos = G4ThreeVector( APB_Con_Side2_Xpos, APB_Con_Side2_Ypos, APB_Con_Side2_Zpos );

    APB_Con_Side2_Ypos = MIB_Y/2 - APB_Con_Side2_Y/2;
    APB_Con_Side2_Pos = G4ThreeVector( APB_Con_Side2_Xpos, APB_Con_Side2_Ypos, APB_Con_Side2_Zpos );


    new G4PVPlacement(
                  0,                    // its rotation
                  APB_Con_Side2_Pos,       // its position
                  APB_Con_Side2_LV,        // its logical volume
                  "APB_Con_Side2_PV",      // its name
                  daq_module_LV,           // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    APB_Con_Side2_Ypos = -MIB_Y/2 + APB_Con_Side2_Y/2;
    APB_Con_Side2_Pos = G4ThreeVector( APB_Con_Side2_Xpos, APB_Con_Side2_Ypos, APB_Con_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  APB_Con_Side2_Pos,       // its position
                  APB_Con_Side2_LV,        // its logical volume
                  "APB_Con_Side2_PV",      // its name
                  daq_module_LV,           // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


        
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Detector Module
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //----------------------------------
    // MIB Plate Mount
    //----------------------------------
    // Solid Volume
    auto MIBP_Mount_X = kMIBP_Mount_Xsize;
    auto MIBP_Mount_Y = kMIBP_Mount_Ysize;
    auto MIBP_Mount_Z = kMIBP_Mount_Zsize;

    G4VSolid* MIBP_Mount_S;
    MIBP_Mount_S = new G4Box(
                  "MIBP_Mount_S",        // its name
                  MIBP_Mount_X/2,        // its X dimension 
                  MIBP_Mount_Y/2,        // its Y dimension
                  MIBP_Mount_Z/2);       // its Z dimension
                          
    // Hole
    auto MIBP_Mount_Hole_X = kMIBP_Mount_Hole_Xsize;
    auto MIBP_Mount_Hole_Y = kMIBP_Mount_Hole_Ysize;
    auto MIBP_Mount_Hole_Z = kMIBP_Mount_Hole_Zsize;

    auto MIBP_Mount_Hole_S = new G4Box(
                  "MIBP_Mount_Hole_S",   // its name
                  MIBP_Mount_Hole_X/2,   // its X dimension
                  MIBP_Mount_Hole_Y/2,   // its Y dimension
                  MIBP_Mount_Hole_Z/2);  // its Z dimension

    auto MIBP_Mount_Hole_pos = G4ThreeVector( 0., 0., 0. );
    MIBP_Mount_S = new G4SubtractionSolid( 
                  "MIBP_Mount_S",        // its name
                  MIBP_Mount_S,          // starting solid
                  MIBP_Mount_Hole_S,     // solid to be subtracted
                  0,                    // its rotation
                  MIBP_Mount_Hole_pos ); // its position

    // Logical Volume
    auto MIBP_Mount_LV = new G4LogicalVolume(
                  MIBP_Mount_S,          // its solid
                  mODM,              // its material
                  "MIBP_Mount_LV");      // its name

    auto MIBP_Mount_Xpos = 0.0*mm;
    auto MIBP_Mount_Ypos = 0.0*mm;
    auto MIBP_Mount_Zpos = -kDet_Module_Zsize/2 + MIBP_Mount_Z/2;
    auto MIBP_Mount_Pos = G4ThreeVector( MIBP_Mount_Xpos, MIBP_Mount_Ypos, MIBP_Mount_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Mount_Pos,        // its position
                  MIBP_Mount_LV,         // its logical volume
                  "MIBP_Mount_PV",       // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
     

    //----------------------------------
    // MIB Plate Edge
    //----------------------------------
    // Solid Volume
    auto MIBP_Edge_X = kMIBP_Edge_Xsize;
    auto MIBP_Edge_Y = kMIBP_Edge_Ysize;
    auto MIBP_Edge_Z = kMIBP_Edge_Zsize;

    G4VSolid* MIBP_Edge_S;
    MIBP_Edge_S = new G4Box(
                  "MIBP_Edge_S",        // its name
                  MIBP_Edge_X/2,        // its X dimension 
                  MIBP_Edge_Y/2,        // its Y dimension
                  MIBP_Edge_Z/2);       // its Z dimension
                          
    // Hole
    auto MIBP_Edge_Hole_X = kMIBP_Edge_Hole_Xsize;
    auto MIBP_Edge_Hole_Y = kMIBP_Edge_Hole_Ysize;
    auto MIBP_Edge_Hole_Z = kMIBP_Edge_Hole_Zsize;

    auto MIBP_Edge_Hole_S = new G4Box(
                  "MIBP_Edge_Hole_S",   // its name
                  MIBP_Edge_Hole_X/2,   // its X dimension
                  MIBP_Edge_Hole_Y/2,   // its Y dimension
                  MIBP_Edge_Hole_Z/2);  // its Z dimension

    auto MIBP_Edge_Hole_pos = G4ThreeVector( 0., 0., 0. );
    MIBP_Edge_S = new G4SubtractionSolid( 
                  "MIBP_Edge_S",        // its name
                  MIBP_Edge_S,          // starting solid
                  MIBP_Edge_Hole_S,     // solid to be subtracted
                  0,                    // its rotation
                  MIBP_Edge_Hole_pos ); // its position

    // Logical Volume
    auto MIBP_Edge_LV = new G4LogicalVolume(
                  MIBP_Edge_S,          // its solid
                  mAl6061,              // its material
                  "MIBP_Edge_LV");      // its name

    auto MIBP_Edge_Xpos = 0.0*mm;
    auto MIBP_Edge_Ypos = 0.0*mm;
    auto MIBP_Edge_Zpos = MIBP_Mount_Zpos + MIBP_Mount_Z/2 + MIBP_Edge_Z/2;
    auto MIBP_Edge_Pos = G4ThreeVector( MIBP_Edge_Xpos, MIBP_Edge_Ypos, MIBP_Edge_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Edge_Pos,        // its position
                  MIBP_Edge_LV,         // its logical volume
                  "MIBP_Edge_PV",       // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Array Side Enclosure - Aluminum
    //----------------------------------
    // Solid Volume
    auto SHAL_Side1_X = kSHAL_Side1_Xsize;
    auto SHAL_Side1_Y = kSHAL_Side1_Ysize;
    auto SHAL_Side1_Z = kSHAL_Side1_Zsize;

    auto SHAL_Side1_S = new G4Box(
                  "SHAL_Side1_S",       // its name
                  SHAL_Side1_X/2,       // its X dimension 
                  SHAL_Side1_Y/2,       // its Y dimension
                  SHAL_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHAL_Side1_LV = new G4LogicalVolume(
                  SHAL_Side1_S,         // its solid
                  mAl6061,              // its material
                  "SHAL_Side1_LV");     // its name

    // Pysical Volume
    auto SHAL_Side1_Xpos = 0.0*mm;
    auto SHAL_Side1_Ypos = 0.0*mm;
    auto SHAL_Side1_Zpos = MIBP_Edge_Zpos - MIBP_Edge_Z/2 + kSHPB_Side1_Zsize/2;
    auto SHAL_Side1_Pos = G4ThreeVector();

    SHAL_Side1_Xpos = kENCL_TopEdge_Xsize/2 - SHAL_Side1_X/2;
    SHAL_Side1_Pos = G4ThreeVector( SHAL_Side1_Xpos, SHAL_Side1_Ypos, SHAL_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHAL_Side1_Pos,       // its position
                  SHAL_Side1_LV,        // its logical volume
                  "SHAL_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHAL_Side1_Xpos = -kENCL_TopEdge_Xsize/2 + SHAL_Side1_X/2;
    SHAL_Side1_Pos = G4ThreeVector( SHAL_Side1_Xpos, SHAL_Side1_Ypos, SHAL_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHAL_Side1_Pos,       // its position
                  SHAL_Side1_LV,        // its logical volume
                  "SHAL_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
    

    //----------------------------------
    // Side1 Shield - Lead
    //----------------------------------
    // Solid Volume
    auto SHPB_Side1_X = kSHPB_Side1_Xsize;
    auto SHPB_Side1_Y = kSHPB_Side1_Ysize;
    auto SHPB_Side1_Z = kSHPB_Side1_Zsize;

    auto SHPB_Side1_S = new G4Box(
                  "SHPB_Side1_S",       // its name
                  SHPB_Side1_X/2,       // its X dimension 
                  SHPB_Side1_Y/2,       // its Y dimension
                  SHPB_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHPB_Side1_LV = new G4LogicalVolume(
                  SHPB_Side1_S,         // its solid
                  mPb,              // its material
                  "SHPB_Side1_LV");     // its name

    // Pysical Volume
    auto SHPB_Side1_Xpos = 0.0*mm;
    auto SHPB_Side1_Ypos = 0.0*mm;
    auto SHPB_Side1_Zpos =  MIBP_Edge_Zpos + MIBP_Edge_Z/2 + kSHPB_Side1_Zsize/2; 
    auto SHPB_Side1_Pos = G4ThreeVector();

    SHPB_Side1_Xpos = -SHAL_Side1_Xpos + SHAL_Side1_X/2 + SHPB_Side1_X/2;
    SHPB_Side1_Pos = G4ThreeVector( SHPB_Side1_Xpos, SHPB_Side1_Ypos, SHPB_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHPB_Side1_Pos,       // its position
                  SHPB_Side1_LV,        // its logical volume
                  "SHPB_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHPB_Side1_Xpos = SHAL_Side1_Xpos - SHAL_Side1_X/2 - SHPB_Side1_X/2;
    SHPB_Side1_Pos = G4ThreeVector( SHPB_Side1_Xpos, SHPB_Side1_Ypos, SHPB_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHPB_Side1_Pos,       // its position
                  SHPB_Side1_LV,        // its logical volume
                  "SHPB_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Side1 Shield - Tin
    //----------------------------------
    // Solid Volume
    auto SHSN_Side1_X = kSHSN_Side1_Xsize;
    auto SHSN_Side1_Y = kSHSN_Side1_Ysize;
    auto SHSN_Side1_Z = kSHSN_Side1_Zsize;

    auto SHSN_Side1_S = new G4Box(
                  "SHSN_Side1_S",       // its name
                  SHSN_Side1_X/2,       // its X dimension 
                  SHSN_Side1_Y/2,       // its Y dimension
                  SHSN_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHSN_Side1_LV = new G4LogicalVolume(
                  SHSN_Side1_S,         // its solid
                  mSn,              // its material
                  "SHSN_Side1_LV");     // its name

    // Pysical Volume
    auto SHSN_Side1_Xpos = 0.0*mm;
    auto SHSN_Side1_Ypos = 0.0*mm;
    auto SHSN_Side1_Zpos = SHPB_Side1_Zpos;
    auto SHSN_Side1_Pos = G4ThreeVector();

    SHSN_Side1_Xpos = - SHPB_Side1_Xpos + SHPB_Side1_X/2 + SHSN_Side1_X/2;
    SHSN_Side1_Pos = G4ThreeVector( SHSN_Side1_Xpos, SHSN_Side1_Ypos, SHSN_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHSN_Side1_Pos,       // its position
                  SHSN_Side1_LV,        // its logical volume
                  "SHSN_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHSN_Side1_Xpos = SHPB_Side1_Xpos - SHPB_Side1_X/2 - SHSN_Side1_X/2;
    SHSN_Side1_Pos = G4ThreeVector( SHSN_Side1_Xpos, SHSN_Side1_Ypos, SHSN_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHSN_Side1_Pos,       // its position
                  SHSN_Side1_LV,        // its logical volume
                  "SHSN_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // Side1 Shield - Copper
    //----------------------------------
    // Solid Volume
    auto SHCU_Side1_X = kSHCU_Side1_Xsize;
    auto SHCU_Side1_Y = kSHCU_Side1_Ysize;
    auto SHCU_Side1_Z = kSHCU_Side1_Zsize;

    auto SHCU_Side1_S = new G4Box(
                  "SHCU_Side1_S",       // its name
                  SHCU_Side1_X/2,       // its X dimension 
                  SHCU_Side1_Y/2,       // its Y dimension
                  SHCU_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHCU_Side1_LV = new G4LogicalVolume(
                  SHCU_Side1_S,         // its solid
                  mCu,              // its material
                  "SHCU_Side1_LV");     // its name

    // Pysical Volume
    auto SHCU_Side1_Xpos = 0.0*mm;
    auto SHCU_Side1_Ypos = 0.0*mm;
    auto SHCU_Side1_Zpos = SHPB_Side1_Zpos;
    auto SHCU_Side1_Pos = G4ThreeVector();

    SHCU_Side1_Xpos = - SHSN_Side1_Xpos + SHSN_Side1_X/2 + SHCU_Side1_X/2;
    SHCU_Side1_Pos = G4ThreeVector( SHCU_Side1_Xpos, SHCU_Side1_Ypos, SHCU_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHCU_Side1_Pos,       // its position
                  SHCU_Side1_LV,        // its logical volume
                  "SHCU_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHCU_Side1_Xpos = SHSN_Side1_Xpos - SHSN_Side1_X/2 - SHCU_Side1_X/2;
    SHCU_Side1_Pos = G4ThreeVector( SHCU_Side1_Xpos, SHCU_Side1_Ypos, SHCU_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHCU_Side1_Pos,       // its position
                  SHCU_Side1_LV,        // its logical volume
                  "SHCU_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // Side1 Plate
    //----------------------------------
    // Solid Volume
    auto ENCL_Side1_X = kENCL_Side1_Xsize;
    auto ENCL_Side1_Y = kENCL_Side1_Ysize;
    auto ENCL_Side1_Z = kENCL_Side1_Zsize;

    auto ENCL_Side1_S = new G4Box(
                  "ENCL_Side1_S",       // its name
                  ENCL_Side1_X/2,       // its X dimension 
                  ENCL_Side1_Y/2,       // its Y dimension
                  ENCL_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto ENCL_Side1_LV = new G4LogicalVolume(
                  ENCL_Side1_S,         // its solid
                  mAl6061,              // its material
                  "ENCL_Side1_LV");     // its name

    // Pysical Volume
    auto ENCL_Side1_Xpos = 0.0*mm;
    auto ENCL_Side1_Ypos = 0.0*mm;
    auto ENCL_Side1_Zpos = SHPB_Side1_Zpos;
    auto ENCL_Side1_Pos = G4ThreeVector();

    ENCL_Side1_Xpos = - SHCU_Side1_Xpos + SHCU_Side1_X/2 + ENCL_Side1_X/2;
    ENCL_Side1_Pos = G4ThreeVector( ENCL_Side1_Xpos, ENCL_Side1_Ypos, ENCL_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side1_Pos,       // its position
                  ENCL_Side1_LV,        // its logical volume
                  "ENCL_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    ENCL_Side1_Xpos = SHCU_Side1_Xpos - SHCU_Side1_X/2 - ENCL_Side1_X/2;
    ENCL_Side1_Pos = G4ThreeVector( ENCL_Side1_Xpos, ENCL_Side1_Ypos, ENCL_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side1_Pos,       // its position
                  ENCL_Side1_LV,        // its logical volume
                  "ENCL_Side1_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Array Side Enclosure - Aluminum
    //----------------------------------
    // Solid Volume
    auto SHAL_Side2_X = kSHAL_Side2_Xsize;
    auto SHAL_Side2_Y = kSHAL_Side2_Ysize;
    auto SHAL_Side2_Z = kSHAL_Side2_Zsize;

    auto SHAL_Side2_S = new G4Box(
                  "SHAL_Side2_S",       // its name
                  SHAL_Side2_X/2,       // its X dimension 
                  SHAL_Side2_Y/2,       // its Y dimension
                  SHAL_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHAL_Side2_LV = new G4LogicalVolume(
                  SHAL_Side2_S,         // its solid
                  mAl6061,              // its material
                  "SHAL_Side2_LV");     // its name

    // Pysical Volume
    auto SHAL_Side2_Xpos = 0.0*mm;
    auto SHAL_Side2_Ypos = 0.0*mm;
    auto SHAL_Side2_Zpos = SHAL_Side1_Zpos;
    auto SHAL_Side2_Pos = G4ThreeVector();

    SHAL_Side2_Ypos = kENCL_TopEdge_Ysize/2 - SHAL_Side2_Y/2;
    SHAL_Side2_Pos = G4ThreeVector( SHAL_Side2_Xpos, SHAL_Side2_Ypos, SHAL_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHAL_Side2_Pos,       // its position
                  SHAL_Side2_LV,        // its logical volume
                  "SHAL_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHAL_Side2_Ypos = - kENCL_TopEdge_Ysize/2 + SHAL_Side2_Y/2;
    SHAL_Side2_Pos = G4ThreeVector( SHAL_Side2_Xpos, SHAL_Side2_Ypos, SHAL_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHAL_Side2_Pos,       // its position
                  SHAL_Side2_LV,        // its logical volume
                  "SHAL_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps       

    //----------------------------------
    // Side2 Shield - Lead
    //----------------------------------
    // Solid Volume
    auto SHPB_Side2_X = kSHPB_Side2_Xsize;
    auto SHPB_Side2_Y = kSHPB_Side2_Ysize;
    auto SHPB_Side2_Z = kSHPB_Side2_Zsize;

    auto SHPB_Side2_S = new G4Box(
                  "SHPB_Side2_S",       // its name
                  SHPB_Side2_X/2,       // its X dimension 
                  SHPB_Side2_Y/2,       // its Y dimension
                  SHPB_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHPB_Side2_LV = new G4LogicalVolume(
                  SHPB_Side2_S,         // its solid
                  mPb,              // its material
                  "SHPB_Side2_LV");     // its name

    // Pysical Volume
    auto SHPB_Side2_Xpos = 0.0*mm;
    auto SHPB_Side2_Ypos = 0.0*mm;
    auto SHPB_Side2_Zpos = SHPB_Side1_Zpos;
    auto SHPB_Side2_Pos = G4ThreeVector();

    SHPB_Side2_Ypos = - SHAL_Side2_Ypos + SHAL_Side2_Y/2 + SHPB_Side2_Y/2;
    SHPB_Side2_Pos = G4ThreeVector( SHPB_Side2_Xpos, SHPB_Side2_Ypos, SHPB_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHPB_Side2_Pos,       // its position
                  SHPB_Side2_LV,        // its logical volume
                  "SHPB_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHPB_Side2_Ypos = SHAL_Side2_Ypos - SHAL_Side2_Y/2 - SHPB_Side2_Y/2;
    SHPB_Side2_Pos = G4ThreeVector( SHPB_Side2_Xpos, SHPB_Side2_Ypos, SHPB_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHPB_Side2_Pos,       // its position
                  SHPB_Side2_LV,        // its logical volume
                  "SHPB_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // Side2 Shield - Tin
    //----------------------------------
    // Solid Volume
    auto SHSN_Side2_X = kSHSN_Side2_Xsize;
    auto SHSN_Side2_Y = kSHSN_Side2_Ysize;
    auto SHSN_Side2_Z = kSHSN_Side2_Zsize;

    auto SHSN_Side2_S = new G4Box(
                  "SHSN_Side2_S",       // its name
                  SHSN_Side2_X/2,       // its X dimension 
                  SHSN_Side2_Y/2,       // its Y dimension
                  SHSN_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHSN_Side2_LV = new G4LogicalVolume(
                  SHSN_Side2_S,         // its solid
                  mSn,              // its material
                  "SHSN_Side2_LV");     // its name

    // Pysical Volume
    auto SHSN_Side2_Xpos = 0.0*mm;
    auto SHSN_Side2_Ypos = 0.0*mm;
    auto SHSN_Side2_Zpos = SHPB_Side1_Zpos;
    auto SHSN_Side2_Pos = G4ThreeVector();

    SHSN_Side2_Ypos = - SHPB_Side2_Ypos + SHPB_Side2_Y/2 + SHSN_Side2_Y/2;
    SHSN_Side2_Pos = G4ThreeVector( SHSN_Side2_Xpos, SHSN_Side2_Ypos, SHSN_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHSN_Side2_Pos,       // its position
                  SHSN_Side2_LV,        // its logical volume
                  "SHSN_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHSN_Side2_Ypos = SHPB_Side2_Ypos - SHPB_Side2_Y/2  - SHSN_Side2_Y/2;
    SHSN_Side2_Pos = G4ThreeVector( SHSN_Side2_Xpos, SHSN_Side2_Ypos, SHSN_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHSN_Side2_Pos,       // its position
                  SHSN_Side2_LV,        // its logical volume
                  "SHSN_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Side2 Shield - Copper
    //----------------------------------
    // Solid Volume
    auto SHCU_Side2_X = kSHCU_Side2_Xsize;
    auto SHCU_Side2_Y = kSHCU_Side2_Ysize;
    auto SHCU_Side2_Z = kSHCU_Side2_Zsize;

    auto SHCU_Side2_S = new G4Box(
                  "SHCU_Side2_S",       // its name
                  SHCU_Side2_X/2,       // its X dimension 
                  SHCU_Side2_Y/2,       // its Y dimension
                  SHCU_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto SHCU_Side2_LV = new G4LogicalVolume(
                  SHCU_Side2_S,         // its solid
                  mCu,              // its material
                  "SHCU_Side2_LV");     // its name

    // Pysical Volume
    auto SHCU_Side2_Xpos = 0.0*mm;
    auto SHCU_Side2_Ypos = 0.0*mm;
    auto SHCU_Side2_Zpos = SHPB_Side1_Zpos;
    auto SHCU_Side2_Pos = G4ThreeVector();

    SHCU_Side2_Ypos = - SHSN_Side2_Ypos + SHSN_Side2_Y/2 + SHCU_Side2_Y/2;
    SHCU_Side2_Pos = G4ThreeVector( SHCU_Side2_Xpos, SHCU_Side2_Ypos, SHCU_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHCU_Side2_Pos,       // its position
                  SHCU_Side2_LV,        // its logical volume
                  "SHCU_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    SHCU_Side2_Ypos = SHSN_Side2_Ypos - SHSN_Side2_Y/2 - SHCU_Side2_Y/2;
    SHCU_Side2_Pos = G4ThreeVector( SHCU_Side2_Xpos, SHCU_Side2_Ypos, SHCU_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SHCU_Side2_Pos,       // its position
                  SHCU_Side2_LV,        // its logical volume
                  "SHCU_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // Side2 Plate
    //----------------------------------
    // Solid Volume
    auto ENCL_Side2_X = kENCL_Side2_Xsize;
    auto ENCL_Side2_Y = kENCL_Side2_Ysize;
    auto ENCL_Side2_Z = kENCL_Side2_Zsize;

    auto ENCL_Side2_S = new G4Box(
                  "ENCL_Side2_S",       // its name
                  ENCL_Side2_X/2,       // its X dimension 
                  ENCL_Side2_Y/2,       // its Y dimension
                  ENCL_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto ENCL_Side2_LV = new G4LogicalVolume(
                  ENCL_Side2_S,         // its solid
                  mAl6061,              // its material
                  "ENCL_Side2_LV");     // its name

    // Pysical Volume
    auto ENCL_Side2_Xpos = 0.0*mm;
    auto ENCL_Side2_Ypos = 0.0*mm;
    auto ENCL_Side2_Zpos = SHPB_Side1_Zpos;
    auto ENCL_Side2_Pos = G4ThreeVector();

    ENCL_Side2_Ypos = -SHCU_Side2_Ypos + SHCU_Side2_Y/2 + ENCL_Side2_Y/2;
    ENCL_Side2_Pos = G4ThreeVector( ENCL_Side2_Xpos, ENCL_Side2_Ypos, ENCL_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side2_Pos,       // its position
                  ENCL_Side2_LV,        // its logical volume
                  "ENCL_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    ENCL_Side2_Ypos = SHCU_Side2_Ypos - SHCU_Side2_Y/2 - ENCL_Side2_Y/2;
    ENCL_Side2_Pos = G4ThreeVector( ENCL_Side2_Xpos, ENCL_Side2_Ypos, ENCL_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side2_Pos,       // its position
                  ENCL_Side2_LV,        // its logical volume
                  "ENCL_Side2_PV",      // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     //----------------------------------
    // Top Plate Edge
    //----------------------------------
    // Solid Volume
    auto ENCL_TopEdge_X = kENCL_TopEdge_Xsize;
    auto ENCL_TopEdge_Y = kENCL_TopEdge_Ysize;
    auto ENCL_TopEdge_Z = kENCL_TopEdge_Zsize;

    G4VSolid* ENCL_TopEdge_S;
    ENCL_TopEdge_S = new G4Box(
                  "ENCL_TopEdge_S",     // its name
                  ENCL_TopEdge_X/2,     // its X dimension 
                  ENCL_TopEdge_Y/2,     // its Y dimension
                  ENCL_TopEdge_Z/2);    // its Z dimension


    // Hole
    auto ENCL_TopEdge_Hole_X = kENCL_TopEdge_Hole_Xsize;
    auto ENCL_TopEdge_Hole_Y = kENCL_TopEdge_Hole_Ysize;
    auto ENCL_TopEdge_Hole_Z = kENCL_TopEdge_Hole_Zsize;

    auto ENCL_TopEdge_Hole_S = new G4Box(
                  "ENCL_TopEdge_Hole_S",     // its name
                  ENCL_TopEdge_Hole_X/2,     // its X dimension
                  ENCL_TopEdge_Hole_Y/2,     // its Y dimension
                  ENCL_TopEdge_Hole_Z/2);    // its Z dimension

    auto ENCL_TopEdge_Hole_pos = G4ThreeVector( 0., 0., 0. );
    ENCL_TopEdge_S = new G4SubtractionSolid( 
                  "ENCL_TopEdge_S",     // its name
                  ENCL_TopEdge_S,       // starting solid
                  ENCL_TopEdge_Hole_S,  // solid to be subtracted
                  0,                    // its rotation
                  ENCL_TopEdge_Hole_pos );   // its position

    // Logical Volume
    auto ENCL_TopEdge_LV = new G4LogicalVolume(
                  ENCL_TopEdge_S,       // its solid
                  mAl6061,              // its material
                  "ENCL_TopEdge_LV");   // its name

    auto ENCL_TopEdge_Xpos = 0.0*mm;
    auto ENCL_TopEdge_Ypos = 0.0*mm;
    auto ENCL_TopEdge_Zpos = ENCL_Side1_Zpos + ENCL_Side1_Z/2 - ENCL_TopEdge_Z/2;
    auto ENCL_TopEdge_Pos = G4ThreeVector( ENCL_TopEdge_Xpos, ENCL_TopEdge_Ypos, ENCL_TopEdge_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_TopEdge_Pos,     // its position
                  ENCL_TopEdge_LV,      // its logical volume
                  "ENCL_TopEdge_PV",    // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
  

    //----------------------------------
    // Detector Column
    //----------------------------------
    // SOLID VOLUME
    auto detColumn_X = kDetColumn_Xsize;
    auto detColumn_Y = kDetColumn_Ysize;
    auto detColumn_Z = kDetColumn_Zsize;

    auto detColumn_S = new G4Box(
                  "DetColumn_S",        // its name
                  detColumn_X/2,        // its X dimension 
                  detColumn_Y/2,        // its Y dimension
                  detColumn_Z/2);             // its Z dimension

    // LOGICAL VOLUME
    auto detColumn_C_LV = new G4LogicalVolume(
                  detColumn_S,          // its solid
                  mVacuum,              // its material
                  "DetColumn_LV");      // its name

    auto detColumn_S_LV = new G4LogicalVolume(
                  detColumn_S,          // its solid
                  mVacuum,              // its material
                  "DetColumn_LV");      // its name
    
     auto detColumn_Cal_LV = new G4LogicalVolume(
                   detColumn_S,          // its solid
                   mVacuum,              // its material
                   "DetColumn_LV");      // its name

    // PHYSICAL VOLUME
    auto detColumn_offsetX = ( kScint_Xpitch * (kNumScint_X-1) / 2 );
    auto detColumn_offsetY = ( kScint_Ypitch * (kNumScint_Y-1) / 2 );
    auto detColumn_Xpos = 0.0*mm;
    auto detColumn_Ypos = 0.0*mm;
    auto detColumn_Zpos = -kDet_Module_Zsize/2 - kMIB_Zoffset -kMIB_Zsize + detColumn_Z/2;
    auto detColumn_Pos = G4ThreeVector( detColumn_Xpos, detColumn_Ypos, detColumn_Zpos );

    // G4cout << G4endl;
    // G4cout << "--> Column Positions:" << G4endl;
    auto copyNum = 0;
    for (auto col = 0; col<kNumScint_Y; col++) {
      for (auto row = 0; row<kNumScint_X; row++) {
        detColumn_Xpos =  ( row * kScint_Xpitch ) - detColumn_offsetX;
        detColumn_Ypos = -( col * kScint_Ypitch ) + detColumn_offsetY;

        detColumn_Pos = G4ThreeVector( detColumn_Xpos, detColumn_Ypos, detColumn_Zpos );

        // G4cout << "----> Copy Number: " << copyNum;
        // G4cout << " (" << detColumn_Xpos << ", " << detColumn_Ypos << ")" << G4endl;

        if ( (row == 0) || (row == kNumScint_X-1) ) { // Calorimeter
          new G4PVPlacement(
                  0,                    // its rotation
                  detColumn_Pos,        // its position
                  detColumn_C_LV,       // its logical volume
                  "DetColumn_PV",       // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;

        }

        else if ( (col == 0) || (col == kNumScint_Y-1) ) { // Calorimeter
          new G4PVPlacement(
                  0,                    // its rotation
                  detColumn_Pos,        // its position
                  detColumn_C_LV,       // its logical volume
                  "DetColumn_PV",       // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;

        }

        else { // Plastic
          new G4PVPlacement(
                  0,                    // its rotation
                  detColumn_Pos,        // its position
                  detColumn_S_LV,       // its logical volume
                  "DetColumn_PV",       // its name
                  det_module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;

        }

      }
    }

    //----------------------------------
    // MIB Plate
    //----------------------------------
    // Solid Volume
    auto MIBP_X = kMIBP_Xsize;
    auto MIBP_Y = kMIBP_Ysize;
    auto MIBP_Z = kMIBP_Zsize;

    G4VSolid* MIBP_S;
    MIBP_S = new G4Box(
                  "MIB_Plate_S",        // its name
                  MIBP_X/2,             // its X dimension 
                  MIBP_Y/2,             // its Y dimension
                  MIBP_Z/2);            // its Z dimension
                          
    // Hole
    auto MIBP_Hole_X = kMIBP_Hole_Xsize;
    auto MIBP_Hole_Y = kMIBP_Hole_Ysize;
    auto MIBP_Hole_Z = kMIBP_Hole_Zsize;

    auto MIBP_Hole_S = new G4Box(
                  "MIBP_Hole_S",        // its name
                  MIBP_Hole_X/2,        // its X dimension
                  MIBP_Hole_Y/2,        // its Y dimension
                  MIBP_Hole_Z/2);       // its Z dimension

    auto MIBP_Hole_pos = G4ThreeVector( 0., 0., 0. );
    MIBP_S = new G4SubtractionSolid( 
                  "MIBP_Hole_S",        // its name
                  MIBP_S,               // starting solid
                  MIBP_Hole_S,          // solid to be subtracted
                  0,                    // its rotation
                  MIBP_Hole_pos );      // its position

    // Logical Volume
    auto MIBP_LV = new G4LogicalVolume(
                  MIBP_S,               // its solid
                  mAl6061,              // its material
                  "MIB_Plate_LV");      // its name
    auto MIBP_Xpos = 0.0*mm;
    auto MIBP_Ypos = 0.0*mm;
    auto MIBP_Zpos = -detColumn_Z/2 + kMIBP_Zoffset + MIBP_Z/2;
    auto MIBP_Pos = G4ThreeVector( MIBP_Xpos, MIBP_Ypos, MIBP_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Pos,             // its position
                  MIBP_LV,              // its logical volume
                  "MIB_Plate_PV",       // its name
                  detColumn_C_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Pos,             // its position
                  MIBP_LV,              // its logical volume
                  "MIB_Plate_PV",       // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Pos,             // its position
                  MIBP_LV,              // its logical volume
                  "MIB_Plate_PV",       // its name
                  detColumn_Cal_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps               

    //----------------------------------
    // Scintillator Case
    //----------------------------------
    // Solid Volume
    auto SCINT_Case_X = kScint_Case_Xsize;
    auto SCINT_Case_Y = kScint_Case_Ysize;
    auto SCINT_Case_Z = kScint_Case_Zsize;

    G4VSolid* SCINT_Case_S;
    SCINT_Case_S = new G4Box(
                  "Scint_Case_S",       // its name
                  SCINT_Case_X/2,       // its X dimension
                  SCINT_Case_Y/2,       // its Y dimension
                  SCINT_Case_Z/2);      // its Z dimension


    // Hole
    auto SCINT_Case_Hole_X = kScint_Case_Hole_Xsize;
    auto SCINT_Case_Hole_Y = kScint_Case_Hole_Ysize;
    auto SCINT_Case_Hole_Z = 2*kScint_Case_Zsize;

    auto SCINT_Case_Hole_S = new G4Box(
                  "SCINT_Case_Hole_S",  // its name
                  SCINT_Case_Hole_X/2,  // its X dimension
                  SCINT_Case_Hole_Y/2,  // its Y dimension
                  SCINT_Case_Hole_Z/2); // its Z dimension

    auto SCINT_Case_Hole_pos = G4ThreeVector( 0., 0., 0. );
    SCINT_Case_S = new G4SubtractionSolid( 
                  "SCINT_Case_Hole_S",  // its name
                  SCINT_Case_S,         // starting solid
                  SCINT_Case_Hole_S,    // solid to be subtracted
                  0,                    // its rotation
                  SCINT_Case_Hole_pos );// its position

    // Logical Volume
    auto SCINT_Case_LV = new G4LogicalVolume(
                  SCINT_Case_S,         // its solid
                  mNylon,               //! its material
                  "Scint_Case_LV");     // its name

    // Physical Volume
    auto SCINT_Case_Xpos = 0.0*mm;
    auto SCINT_Case_Ypos = 0.0*mm;
    auto SCINT_Case_Zpos = MIBP_Zpos + MIBP_Z/2 + SCINT_Case_Z/2;
    auto SCINT_Case_Pos = G4ThreeVector( SCINT_Case_Xpos, SCINT_Case_Ypos, SCINT_Case_Zpos );
   
    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Pos,       // its position
                  SCINT_Case_LV,        // its logical volume
                  "Scint_Case_PV",      // its name
                  detColumn_C_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Pos,       // its position
                  SCINT_Case_LV,        // its logical volume
                  "Scint_Case_PV",      // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   SCINT_Case_Pos,       // its position
                   SCINT_Case_LV,        // its logical volume
                   "Scint_Case_PV",      // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // Scintillator Case Bot
    //----------------------------------
    // Solid Volume
    auto SCINT_Case_Bot_X = kScint_Case_Bot_Xsize;
    auto SCINT_Case_Bot_Y = kScint_Case_Bot_Ysize;
    auto SCINT_Case_Bot_Z = kScint_Case_Bot_Zsize;

    G4VSolid* SCINT_Case_Bot_S;
    SCINT_Case_Bot_S = new G4Box(
                  "Scint_Case_Bot_S",   // its name
                  SCINT_Case_Bot_X/2,   // its X dimension
                  SCINT_Case_Bot_Y/2,   // its Y dimension
                  SCINT_Case_Bot_Z/2);  // its Z dimension

    auto SCINT_Case_Bot_Hole_Zpos = -SCINT_Case_Bot_Z/2 + kScint_Case_Thickness/2 + SCINT_Case_Hole_Z/2;
    auto SCINT_Case_Bot_Hole_pos = G4ThreeVector( 0., 0., SCINT_Case_Bot_Hole_Zpos );
    SCINT_Case_Bot_S = new G4SubtractionSolid( 
                  "Scint_Case_Bot_S",   // its name
                  SCINT_Case_Bot_S,     // starting solid
                  SCINT_Case_Hole_S,    // solid to be subtracted
                  0,                    // its rotation
                  SCINT_Case_Bot_Hole_pos );  // its position

    // Logical Volume
    auto SCINT_Case_Bot_LV = new G4LogicalVolume(
                  SCINT_Case_Bot_S,     // its solid
                  mNylon,                 // its material
                  "Scint_Case_Bot_LV"); // its name

    // Physical Volume
    auto SCINT_Case_Bot_Xpos = 0.0*mm;
    auto SCINT_Case_Bot_Ypos = 0.0*mm;
    auto SCINT_Case_Bot_Zpos = SCINT_Case_Zpos - SCINT_Case_Z/2 - SCINT_Case_Bot_Z/2;
    auto SCINT_Case_Bot_Pos = G4ThreeVector( SCINT_Case_Bot_Xpos, SCINT_Case_Bot_Ypos,SCINT_Case_Bot_Zpos );
   
    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Bot_Pos,   // its position
                  SCINT_Case_Bot_LV,    // its logical volume
                  "Scint_Case_Bot_PV",  // its name
                  detColumn_C_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Bot_Pos,   // its position
                  SCINT_Case_Bot_LV,    // its logical volume
                  "Scint_Case_Bot_PV",  // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   SCINT_Case_Bot_Pos,   // its position
                   SCINT_Case_Bot_LV,    // its logical volume
                   "Scint_Case_Bot_PV",  // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // Scintillator Case Top
    //----------------------------------
    // Solid Volume
    auto SCINT_Case_Top_X = kScint_Case_Top_Xsize;
    auto SCINT_Case_Top_Y = kScint_Case_Top_Ysize;
    auto SCINT_Case_Top_Z = kScint_Case_Top_Zsize;

    G4VSolid* SCINT_Case_Top_S;
    SCINT_Case_Top_S = new G4Box(
                  "Scint_Case_Top_S",   // its name
                  SCINT_Case_Top_X/2,   // its X dimension
                  SCINT_Case_Top_Y/2,   // its Y dimension
                  SCINT_Case_Top_Z/2);  // its Z dimension

    auto SCINT_Case_Top_Hole_Zpos = SCINT_Case_Top_Z/2 - kScint_Case_Thickness/2 - SCINT_Case_Hole_Z/2;
    auto SCINT_Case_Top_Hole_pos = G4ThreeVector( 0., 0., SCINT_Case_Top_Hole_Zpos );
    SCINT_Case_Top_S = new G4SubtractionSolid( 
                  "Scint_Case_Top_S",   // its name
                  SCINT_Case_Top_S,     // starting solid
                  SCINT_Case_Hole_S,    // solid to be subtracted
                  0,                    // its rotation
                  SCINT_Case_Top_Hole_pos );  // its position

    // Logical Volume
    auto SCINT_Case_Top_LV = new G4LogicalVolume(
                  SCINT_Case_Top_S,     // its solid
                  mNylon,                 // its material
                  "Scint_Case_Top_LV"); // its name

    // Physical Volume
    auto SCINT_Case_Top_Xpos = 0.0*mm;
    auto SCINT_Case_Top_Ypos = 0.0*mm;
    auto SCINT_Case_Top_Zpos = SCINT_Case_Zpos + SCINT_Case_Z/2 + SCINT_Case_Top_Z/2;
    auto SCINT_Case_Top_Pos = G4ThreeVector( SCINT_Case_Top_Xpos, SCINT_Case_Top_Ypos,SCINT_Case_Top_Zpos );
   
    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Top_Pos,   // its position
                  SCINT_Case_Top_LV,    // its logical volume
                  "Scint_Case_Top_PV",  // its name
                  detColumn_C_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Top_Pos,   // its position
                  SCINT_Case_Top_LV,    // its logical volume
                  "Scint_Case_Top_PV",  // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   SCINT_Case_Top_Pos,   // its position
                   SCINT_Case_Top_LV,    // its logical volume
                   "Scint_Case_Top_PV",  // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Side1 Vertical Board (VCB)
    //----------------------------------
    // Solid Volume
    auto VCB_Side1_X = kVCB_Side1_Xsize;
    auto VCB_Side1_Y = kVCB_Side1_Ysize;
    auto VCB_Side1_Z = kVCB_Side1_Zsize;

    auto VCB_Side1_S = new G4Box(
                  "VCB_Side1_S",       // its name
                  VCB_Side1_X/2,       // its X dimension 
                  VCB_Side1_Y/2,       // its Y dimension
                  VCB_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto VCB_Side1_LV = new G4LogicalVolume(
                  VCB_Side1_S,         // its solid
                  mVCB,              // its material
                  "VCB_Side1_LV");     // its name

    // Pysical Volume
    auto VCB_Side1_Xpos = 0.0*mm;
    auto VCB_Side1_Ypos = 0.0*mm;
    // auto VCB_Side2_Zpos = SCINT_Case_Zpos/2 + SCINT_Case_Z/2 - VCB_Side2_Z/2 - kScint_Case_Thickness/2;
    auto VCB_Side1_Zpos = kScint_Case_Thickness/2;
    auto VCB_Side1_Pos = G4ThreeVector();

    
    VCB_Side1_Xpos = VCB_Side1_Y/2 + kVCB_Thickness/2;
    VCB_Side1_Pos = G4ThreeVector( VCB_Side1_Xpos, VCB_Side1_Ypos, VCB_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side1_Pos,       // its position
                  VCB_Side1_LV,        // its logical volume
                  "VCB_Side1_PV",      // its name
                  detColumn_C_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side1_Pos,       // its position
                  VCB_Side1_LV,        // its logical volume
                  "VCB_Side1_PV",      // its name
                  detColumn_S_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side1_Pos,       // its position
                  VCB_Side1_LV,        // its logical volume
                  "VCB_Side1_PV",      // its name
                  detColumn_Cal_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps     

    VCB_Side1_Xpos = -VCB_Side1_Y/2 - kVCB_Thickness/2;
    VCB_Side1_Pos = G4ThreeVector( VCB_Side1_Xpos, VCB_Side1_Ypos, VCB_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side1_Pos,       // its position
                  VCB_Side1_LV,        // its logical volume
                  "VCB_Side1_PV",      // its name
                  detColumn_C_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps     

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side1_Pos,       // its position
                  VCB_Side1_LV,        // its logical volume
                  "VCB_Side1_PV",      // its name
                  detColumn_S_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps       

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side1_Pos,       // its position
                  VCB_Side1_LV,        // its logical volume
                  "VCB_Side1_PV",      // its name
                  detColumn_Cal_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps   

    //----------------------------------
    // Side2 Vertical Board (VCB)
    //----------------------------------
    // Solid Volume
    auto VCB_Side2_X = kVCB_Side2_Xsize;
    auto VCB_Side2_Y = kVCB_Side2_Ysize;
    auto VCB_Side2_Z = kVCB_Side2_Zsize;

    auto VCB_Side2_S = new G4Box(
                  "VCB_Side2_S",       // its name
                  VCB_Side2_X/2,       // its X dimension 
                  VCB_Side2_Y/2,       // its Y dimension
                  VCB_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto VCB_Side2_LV = new G4LogicalVolume(
                  VCB_Side2_S,         // its solid
                  mVCB,              // its material
                  "VCB_Side2_LV");     // its name

    // Pysical Volume
    auto VCB_Side2_Xpos = 0.0*mm;
    auto VCB_Side2_Ypos = 0.0*mm;
    auto VCB_Side2_Zpos = kScint_Case_Thickness/2;
    auto VCB_Side2_Pos = G4ThreeVector();

    VCB_Side2_Ypos = VCB_Side2_X/2 + kVCB_Thickness/2;
    VCB_Side2_Pos = G4ThreeVector( VCB_Side2_Xpos, VCB_Side2_Ypos, VCB_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side2_Pos,       // its position
                  VCB_Side2_LV,        // its logical volume
                  "VCB_Side2_PV",      // its name
                  detColumn_C_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps
    
    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side2_Pos,       // its position
                  VCB_Side2_LV,        // its logical volume
                  "VCB_Side2_PV",      // its name
                  detColumn_S_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side2_Pos,       // its position
                  VCB_Side2_LV,        // its logical volume
                  "VCB_Side2_PV",      // its name
                  detColumn_Cal_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps

    VCB_Side2_Ypos = -VCB_Side2_X/2 - kVCB_Thickness/2;
    VCB_Side2_Pos = G4ThreeVector( VCB_Side2_Xpos, VCB_Side2_Ypos, VCB_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side2_Pos,       // its position
                  VCB_Side2_LV,        // its logical volume
                  "VCB_Side2_PV",      // its name
                  detColumn_C_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side2_Pos,       // its position
                  VCB_Side2_LV,        // its logical volume
                  "VCB_Side2_PV",      // its name
                  detColumn_S_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  VCB_Side2_Pos,       // its position
                  VCB_Side2_LV,        // its logical volume
                  "VCB_Side2_PV",      // its name
                  detColumn_Cal_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // Column O-ring
    //----------------------------------
    // Solid Volume
    auto ORing_X = kORing_Xsize;
    auto ORing_Y = kORing_Ysize;
    auto ORing_Z = kORing_Zsize;

    G4VSolid* ORing_S;
    ORing_S = new G4Box(
                  "ORing_S",       // its name
                  ORing_X/2,       // its X dimension
                  ORing_Y/2,       // its Y dimension
                  ORing_Z/2);      // its Z dimension


    // Hole
    auto ORing_Hole_X = kORing_Hole_Xsize;
    auto ORing_Hole_Y = kORing_Hole_Ysize;
    auto ORing_Hole_Z = 2*kORing_Zsize;

    auto ORing_Hole_S = new G4Box(
                  "ORing_Hole_S",  // its name
                  ORing_Hole_X/2,  // its X dimension
                  ORing_Hole_Y/2,  // its Y dimension
                  ORing_Hole_Z/2); // its Z dimension

    auto ORing_Hole_pos = G4ThreeVector( 0., 0., 0. );
    ORing_S = new G4SubtractionSolid( 
                  "ORing_Hole_S",  // its name
                  ORing_S,         // starting solid
                  ORing_Hole_S,    // solid to be subtracted
                  0,                    // its rotation
                  ORing_Hole_pos );// its position

    // Logical Volume
    auto ORing_LV = new G4LogicalVolume(
                  ORing_S,         // its solid
                  mORing,               //! its material
                  "ORing_LV");     // its name

    // Physical Volume
    auto ORing_Xpos = 0.0*mm;
    auto ORing_Ypos = 0.0*mm;
    auto ORing_Zpos = 0.0*mm;
    auto ORing_Pos = G4ThreeVector( ORing_Xpos, ORing_Ypos, ORing_Zpos );
   
    new G4PVPlacement(
                  0,                    // its rotation
                  ORing_Pos,       // its position
                  ORing_LV,        // its logical volume
                  "ORing_PV",      // its name
                  detColumn_C_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  ORing_Pos,       // its position
                  ORing_LV,        // its logical volume
                  "ORing_PV",      // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   ORing_Pos,       // its position
                   ORing_LV,        // its logical volume
                   "ORing_PV",      // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // Enclosure Top/Support Frame
    //----------------------------------
    // Solid Volume
    auto ENCL_Top_X = kENCL_Top_Xsize;
    auto ENCL_Top_Y = kENCL_Top_Ysize;
    auto ENCL_Top_Z = kENCL_Top_Zsize;

    G4VSolid* ENCL_Top_S;
    ENCL_Top_S = new G4Box(
                  "ENCL_Top_S",         // its name
                  ENCL_Top_X/2,         // its X dimension
                  ENCL_Top_Y/2,         // its Y dimension
                  ENCL_Top_Z/2);        // its Z dimension


    // Holes
    auto ENCL_Top_Hole_X = kENCL_Top_Hole_Xsize;
    auto ENCL_Top_Hole_Y = kENCL_Top_Hole_Ysize;
    auto ENCL_Top_Hole_Z = kENCL_Top_Hole_Zsize;

    auto ENCL_Top_Hole_S = new G4Box(
                  "ENCL_Top_Hole_S",    // its name
                  ENCL_Top_Hole_X/2,    // its X dimension
                  ENCL_Top_Hole_Y/2,    // its Y dimension
                  ENCL_Top_Hole_Z/2);   // its Z dimension

    auto ENCL_Top_Hole_pos = G4ThreeVector( 0., 0., 0. );
    ENCL_Top_S = new G4SubtractionSolid( 
                  "ENCL_Top_S",         // its name
                  ENCL_Top_S,           // starting solid
                  ENCL_Top_Hole_S,      // solid to be subtracted
                  0,                    // its rotation
                  ENCL_Top_Hole_pos );  // its position

    // Logical Volume
    auto ENCL_Top_LV = new G4LogicalVolume(
                  ENCL_Top_S,           // its solid
                  mAl6061,              // its material
                  "ENCL_Top_LV");       // its name

    // Physical Volume
    auto ENCL_Top_Xpos = 0.0*mm;
    auto ENCL_Top_Ypos = 0.0*mm;
    auto ENCL_Top_Zpos = SCINT_Case_Zpos + SCINT_Case_Z/2 + kENCL_Top_Zoffset + ENCL_Top_Z/2;
    auto ENCL_Top_Pos = G4ThreeVector( ENCL_Top_Xpos, ENCL_Top_Ypos, ENCL_Top_Zpos );
    
    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Top_Pos,         // its position
                  ENCL_Top_LV,          // its logical volume
                  "ENCL_Top_PV",        // its name
                  detColumn_C_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Top_Pos,         // its position
                  ENCL_Top_LV,          // its logical volume
                  "ENCL_Top_PV",        // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   ENCL_Top_Pos,         // its position
                   ENCL_Top_LV,          // its logical volume
                   "ENCL_Top_PV",        // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Detector Element
    //----------------------------------
    // SOLID VOLUME
    auto detElement_X = kDetElement_Xsize;
    auto detElement_Y = kDetElement_Ysize;
    auto detElement_Z = kDetElement_Zsize;

    auto detElement_S = new G4Box(
                  "DetElement_S",        // its name
                  detElement_X/2,        // its X dimension 
                  detElement_Y/2,        // its Y dimension
                  detElement_Z/2);       // its Z dimension

    // LOGICAL VOLUME
    auto detElement_C_LV = new G4LogicalVolume(
                  detElement_S,          // its solid
                  mVacuum,               // its material
                  "DetElement_LV");      // its name

    auto detElement_S_LV = new G4LogicalVolume(
                  detElement_S,          // its solid
                  mVacuum,               // its material
                  "DetElement_LV");      // its name

     auto detElement_Cal_LV = new G4LogicalVolume(
                   detElement_S,          // its solid
                   mVacuum,               // its material
                   "DetElement_LV");      // its name


    // PHYSICAL VOLUME
    auto detElement_Xpos = 0.0*mm;
    auto detElement_Ypos = 0.0*mm;
    auto detElement_Zpos = 0.0*mm;
    auto detElement_Pos = G4ThreeVector( detElement_Xpos, detElement_Ypos, detElement_Zpos );

    // G4cout << G4endl;
    // G4cout << "--> Element Positions:" << G4endl;
    copyNum = 0;
    for (auto ele = 0; ele<kNumScint_Z; ele++) {
      detElement_Zpos = VCB_Side1_Zpos + kVCB_Side1_Zsize/2 - kScint_Case_Thickness/2 - ele * detElement_Z - detElement_Z/2;

      detElement_Pos = G4ThreeVector( detElement_Xpos, detElement_Ypos, detElement_Zpos );

      // G4cout << "----> Copy Number: " << copyNum;
      // G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;

      new G4PVPlacement(
                  0,                    // its rotation
                  detElement_Pos,       // its position
                  detElement_C_LV,      // its logical volume
                  "DetElement_PV",      // its name
                  detColumn_C_LV,       // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
      copyNum++;
    }

    copyNum = 0;
    for (auto ele = 0; ele<kNumScint_Z; ele++) {
      detElement_Zpos = VCB_Side1_Zpos + kVCB_Side1_Zsize/2 - kScint_Case_Thickness/2 - ele * detElement_Z - detElement_Z/2;

      detElement_Pos = G4ThreeVector( detElement_Xpos, detElement_Ypos, detElement_Zpos );

      // G4cout << "----> Copy Number: " << copyNum;
      // G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;

      if (ele < kNumScint_Z-1) {
        new G4PVPlacement(
                  0,                    // its rotation
                  detElement_Pos,       // its position
                  detElement_S_LV,      // its logical volume
                  "DetElement_PV",      // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
        copyNum++;
      }
      else {
        new G4PVPlacement(
                  0,                    // its rotation
                  detElement_Pos,       // its position
                  detElement_C_LV,      // its logical volume
                  "DetElement_PV",      // its name
                  detColumn_S_LV,       // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
        copyNum++;
      }
    }

     copyNum = 0;
     for (auto ele = 0; ele<kNumScint_Z; ele++) {
       detElement_Zpos = VCB_Side1_Zpos + kVCB_Side1_Zsize/2 - kScint_Case_Thickness/2 - ele * detElement_Z - detElement_Z/2;

       detElement_Pos = G4ThreeVector( detElement_Xpos, detElement_Ypos, detElement_Zpos );

       // G4cout << "----> Copy Number: " << copyNum;
       // G4cout << " (" << detElement_Xpos << ", " << detElement_Ypos << ", " << detElement_Zpos << ")" << G4endl;

       if (ele == 3) {
         new G4PVPlacement(
                   0,                    // its rotation
                   detElement_Pos,       // its position
                   detElement_S_LV,      // its logical volume
                   "DetElement_PV",      // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   copyNum,              // copy number
                   fCheckOverlaps);      // checking overlaps 
         copyNum++;
       }
       else if (ele < kNumScint_Z-1) {
         new G4PVPlacement(
                   0,                    // its rotation
                   detElement_Pos,       // its position
                   detElement_S_LV,      // its logical volume
                   "DetElement_PV",      // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   copyNum,              // copy number
                   fCheckOverlaps);      // checking overlaps 
         copyNum++;
       }
       else {
         new G4PVPlacement(
                   0,                    // its rotation
                   detElement_Pos,       // its position
                   detElement_C_LV,      // its logical volume
                   "DetElement_PV",      // its name
                   detColumn_Cal_LV,       // its mother  volume
                   false,                // no boolean operation
                   copyNum,              // copy number
                   fCheckOverlaps);      // checking overlaps 
         copyNum++;
       }
     }


      //----------------------------------
      // Detector Element Wrapping 
      //----------------------------------
      // SOLID VOLUME
      auto detWrap_X = kDetWrap_Xsize;
      auto detWrap_Y = kDetWrap_Ysize;
      auto detWrap_Z = kDetWrap_Zsize;
  
      G4VSolid* detWrap_S = new G4Box(
                    "detWrap_S",         // its name
                    detWrap_X/2,         // its X dimension
                    detWrap_Y/2,         // its Y dimension
                    detWrap_Z/2);        // its Z dimension
  
      // Hole
      auto detWrap_Hole_X = kDetWrap_Hole_Xsize;
      auto detWrap_Hole_Y = kDetWrap_Hole_Ysize;
      auto detWrap_Hole_Z = kDetWrap_Hole_Zsize;
  
      auto detWrap_Hole_S = new G4Box(
                    "detWrap_S",         // its name
                    detWrap_Hole_X/2,         // its X dimension
                    detWrap_Hole_Y/2,         // its Y dimension
                    detWrap_Hole_Z/2);        // its Z dimension
  
      auto detWrap_Hole_Xpos = 0.0*mm;
      auto detWrap_Hole_Ypos = 0.0*mm;
      auto detWrap_Hole_Zpos = - detWrap_Hole_Z/2 + detWrap_Z/2  - kDetWrap_Thickness;
      auto detWrap_Hole_pos = G4ThreeVector( detWrap_Hole_Xpos, detWrap_Hole_Ypos, detWrap_Hole_Zpos );
      detWrap_S = new G4SubtractionSolid( 
                    "detWrap_S",         // its name
                    detWrap_S,           // starting solid
                    detWrap_Hole_S,      // solid to be subtracted
                    0,                    // its rotation
                    detWrap_Hole_pos );  // its position
  
  
      // LOGICAL VOLUME
      auto detWrap_LV = new G4LogicalVolume(
                    detWrap_S,           // its solid
                    mDetectorWrap,                 // its material
                    "detWrap_LV");       // its name
  
      // PHYSICAL VOLUME
      auto detWrap_Xpos = 0.0*mm;
      auto detWrap_Ypos = 0.0*mm;
      auto detWrap_Zpos = detElement_Z/2 - detWrap_Z/2 + kDetWrap_Thickness;
      auto detWrap_Pos = G4ThreeVector( detWrap_Xpos, detWrap_Ypos, detWrap_Zpos );
  
      new G4PVPlacement(
                    0,                    // its rotation
                    detWrap_Pos,         // its position
                    detWrap_LV,          // its logical volume
                    "detWrap_PV",        // its name
                    detElement_C_LV,    // its mother  volume
                    false,                // no boolean operation
                    0,                    // copy number
                    fCheckOverlaps);      // checking overlaps 
      new G4PVPlacement(
                    0,                    // its rotation
                    detWrap_Pos,         // its position
                    detWrap_LV,          // its logical volume
                    "detWrap_PV",        // its name
                    detElement_S_LV,    // its mother  volume
                    false,                // no boolean operation
                    0,                    // copy number
                    fCheckOverlaps);      // checking overlaps 
      new G4PVPlacement(
                    0,                    // its rotation
                    detWrap_Pos,         // its position
                    detWrap_LV,          // its logical volume
                    "detWrap_PV",        // its name
                    detElement_Cal_LV,    // its mother  volume
                    false,                // no boolean operation
                    0,                    // copy number
                    fCheckOverlaps);      // checking overlaps 
  


    //----------------------------------
    // Scintillator
    //----------------------------------
    // SOLID VOLUME
    auto scint_X = kScint_Xsize;
    auto scint_Y = kScint_Ysize;
    auto scint_Z = kScint_Zsize;

    auto scint_S = new G4Box(
                  "Scint_S",            // its name
                  scint_X/2,            // its X dimension
                  scint_Y/2,            // its Y dimension
                  scint_Z/2);           // its Z dimension

    // LOGICAL VOLUME
    auto scintC_LV = new G4LogicalVolume(
                  scint_S,              // its solid
                  mScintC,              // its material
                  "ScintC_LV");         // its name

    auto scintS_LV = new G4LogicalVolume(
                  scint_S,              // its solid
                  mScintS,              // its material
                  "ScintS_LV");         // its name

    // PHYSICAL VOLUME
    auto scint_Xpos = 0.0*mm;
    auto scint_Ypos = 0.0*mm;
    auto scint_Zpos = detElement_Z/2 - scint_Z/2;
    auto scint_Pos = G4ThreeVector( scint_Xpos, scint_Ypos, scint_Zpos );


    new G4PVPlacement(
                  0,                    // its rotation
                  scint_Pos,            // its position
                  scintC_LV,            // its logical volume
                  "Det_C_PV",           // its name
                  detElement_C_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  scint_Pos,            // its position
                  scintS_LV,            // its logical volume
                  "Det_S_PV",           // its name
                  detElement_S_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //  //----------------------------------
    //  // Calibration Source Housing
    //  //----------------------------------
    //  // SOLID VOLUME
    //  auto calHouse_X = kScint_Xsize;
    //  auto calHouse_Y = kScint_Ysize;
    //  auto calHouse_Z = kScint_Zsize;

    //  G4VSolid* calHouse_S = new G4Box(
    //                "CalHouse_S",         // its name
    //                calHouse_X/2,         // its X dimension
    //                calHouse_Y/2,         // its Y dimension
    //                calHouse_Z/2);        // its Z dimension

    //  // Hole
    //  auto calHouse_Hole_Rmin = kCal_Rmin;
    //  auto calHouse_Hole_Rmax = kCal_Rmax;
    //  auto calHouse_Hole_Z = kCal_Zsize;

    //  auto calHouse_Hole_S = new G4Tubs(
    //                "CalHouse_Hole_S",    // its name
    //                calHouse_Hole_Rmin,   // its minimum radius 
    //                calHouse_Hole_Rmax,   // its maximum radius
    //                calHouse_Hole_Z/2,    // its Z dimension
    //                0.*deg,               // its starting segment angle
    //                360.*deg);            // its ending segment angle

    //  auto calHouse_Hole_Xpos = 0.0*mm;
    //  auto calHouse_Hole_Ypos = 0.0*mm;
    //  auto calHouse_Hole_Zpos = calHouse_Hole_Z/2 - calHouse_Z/2;
    //  auto calHouse_Hole_pos = G4ThreeVector( calHouse_Hole_Xpos, calHouse_Hole_Ypos, calHouse_Hole_Zpos );
    //  calHouse_S = new G4SubtractionSolid( 
    //                "calHouse_S",         // its name
    //                calHouse_S,           // starting solid
    //                calHouse_Hole_S,      // solid to be subtracted
    //                0,                    // its rotation
    //                calHouse_Hole_pos );  // its position


    //  // LOGICAL VOLUME
    //  auto calHouse_LV = new G4LogicalVolume(
    //                calHouse_S,           // its solid
    //                mODM,                 // its material
    //                "CalHouse_LV");       // its name

    //  // PHYSICAL VOLUME
    //  auto calHouse_Xpos = 0.0*mm;
    //  auto calHouse_Ypos = 0.0*mm;
    //  auto calHouse_Zpos = detElement_Z/2 - calHouse_Z/2;
    //  auto calHouse_Pos = G4ThreeVector( calHouse_Xpos, calHouse_Ypos, calHouse_Zpos );

    //  new G4PVPlacement(
    //                0,                    // its rotation
    //                calHouse_Pos,         // its position
    //                calHouse_LV,          // its logical volume
    //                "CalHouse_PV",        // its name
    //                detElement_Cal_LV,    // its mother  volume
    //                false,                // no boolean operation
    //                0,                    // copy number
    //                fCheckOverlaps);      // checking overlaps 

    //  //----------------------------------
    //  // Calibration Source
    //  //----------------------------------
    //  // SOLID VOLUME
    //  auto cal_Rmin = kCal_Rmin;
    //  auto cal_Rmax = kCal_Rmax;
    //  auto cal_Z    = kCal_Zsize;

    //  auto cal_S = new G4Tubs(
    //                "Cal_S",              // its name
    //                cal_Rmin,             // its minimum radius 
    //                cal_Rmax,             // its maximum radius
    //                cal_Z/2,              // its Z dimension
    //                0.*deg,               // its starting segment angle
    //                360.*deg);            // its ending segment angle

    //  // LOGICAL VOLUME
    //  auto cal_LV = new G4LogicalVolume(
    //                cal_S,              // its solid
    //                mScintCal,            // its material
    //                "Cal_LV");            // its name

    //  // PHYSICAL VOLUME
    //  auto cal_Xpos = 0.0*mm;
    //  auto cal_Ypos = 0.0*mm;
    //  auto cal_Zpos = calHouse_Zpos - calHouse_Z/2 + cal_Z/2 ;
    //  // auto cal_Zpos = scint_Zpos - scint_Z/2 + cal_Z/2;
    //  auto cal_Pos = G4ThreeVector( cal_Xpos, cal_Ypos, cal_Zpos );

    //  new G4PVPlacement(
    //                0,                    // its rotation
    //                cal_Pos,              // its position
    //                cal_LV,               // its logical volume
    //                "Cal_PV",             // its name
    //                detElement_Cal_LV,    // its mother  volume
    //                false,                // no boolean operation
    //                0,                    // copy number
    //                fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // Optical Pad
    //----------------------------------
    // Solid Volume
    auto OPad_X = kOpticalPad_Xsize;
    auto OPad_Y = kOpticalPad_Ysize;
    auto OPad_Z = kOpticalPad_Zsize;

    auto OPad_S = new G4Box(
                  "OPad_S",              // its name
                  OPad_X/2,              // its X dimension
                  OPad_Y/2,              // its Y dimension
                  OPad_Z/2);             // its Z dimension
                          
    // Logical Volume
    auto OPad_LV = new G4LogicalVolume(
                  OPad_S,                // its solid
                  mOPad,                 // its material
                  "OPad_LV");            // its name

    // Physical Volume
    auto OPad_Xpos = 0.0*mm;
    auto OPad_Ypos = 0.0*mm;
    auto OPad_Zpos = scint_Zpos - scint_Z/2 - OPad_Z/2;
    auto OPad_Pos = G4ThreeVector( OPad_Xpos, OPad_Ypos, OPad_Zpos );
    
    new G4PVPlacement(
                  0,                    // its rotation
                  OPad_Pos,             // its position
                  OPad_LV,              // its logical volume
                  "OPad_PV",            // its name
                  detElement_C_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  OPad_Pos,             // its position
                  OPad_LV,              // its logical volume
                  "OPad_PV",            // its name
                  detElement_S_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   OPad_Pos,             // its position
                   OPad_LV,              // its logical volume
                   "OPad_PV",            // its name
                   detElement_Cal_LV,      // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // SiPM
    //----------------------------------
    // Solid Volume
    auto SiPM_X = kSiPM_Xsize;
    auto SiPM_Y = kSiPM_Ysize;
    auto SiPM_Z = kSiPM_Zsize;

    auto SiPM_S = new G4Box(
                  "SiPM_S",              // its name
                  SiPM_X/2,              // its X dimension
                  SiPM_Y/2,              // its Y dimension
                  SiPM_Z/2);             // its Z dimension
                          
    // Logical Volume
    auto SiPM_LV = new G4LogicalVolume(
                  SiPM_S,                // its solid
                  mSiPM,                 // its material
                  "SiPM_LV");            // its name

    // Physical Volume
    auto SiPM_Xpos = 0.0*mm;
    auto SiPM_Ypos = 0.0*mm;
    auto SiPM_Zpos = OPad_Zpos - OPad_Z/2 - SiPM_Z/2;
    auto SiPM_Pos = G4ThreeVector( SiPM_Xpos, SiPM_Ypos, SiPM_Zpos );
    
    new G4PVPlacement(
                  0,                    // its rotation
                  SiPM_Pos,             // its position
                  SiPM_LV,              // its logical volume
                  "SiPM_PV",            // its name
                  detElement_C_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SiPM_Pos,             // its position
                  SiPM_LV,              // its logical volume
                  "SiPM_PV",            // its name
                  detElement_S_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   SiPM_Pos,             // its position
                   SiPM_LV,              // its logical volume
                   "SiPM_PV",            // its name
                   detElement_Cal_LV,      // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // SiPM PCB
    //----------------------------------
    // Solid Volume
    auto SiPM_PCB_X = kSiPM_PCB_Xsize;
    auto SiPM_PCB_Y = kSiPM_PCB_Ysize;
    auto SiPM_PCB_Z = kSiPM_PCB_Zsize;

    auto SiPM_PCB_S = new G4Box(
                  "SiPM_PCB_S",          // its name
                  SiPM_PCB_X/2,          // its X dimension 
                  SiPM_PCB_Y/2,          // its Y dimension
                  SiPM_PCB_Z/2);         // its Z dimension
                          
    // Logical Volume
    auto SiPM_PCB_LV = new G4LogicalVolume(
                  SiPM_PCB_S,            // its solid
                  mPCB,                   // its material
                  "SiPM_PCB_LV");        // its name

    // Physical Volume
    auto SiPM_PCB_Xpos = 0.0*mm;
    auto SiPM_PCB_Ypos = 0.0*mm;
    auto SiPM_PCB_Zpos = 0.0*mm;
    auto SiPM_PCB_Pos = G4ThreeVector();

    // Top
    SiPM_PCB_Zpos = SiPM_Zpos - SiPM_Z/2 - SiPM_PCB_Z/2;
    SiPM_PCB_Pos = G4ThreeVector( SiPM_PCB_Xpos, SiPM_PCB_Ypos, SiPM_PCB_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  SiPM_PCB_Pos,         // its position
                  SiPM_PCB_LV,          // its logical volume
                  "SiPM_PCB_PV",        // its name
                  detElement_C_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SiPM_PCB_Pos,         // its position
                  SiPM_PCB_LV,          // its logical volume
                  "SiPM_PCB_PV",        // its name
                  detElement_S_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

     new G4PVPlacement(
                   0,                    // its rotation
                   SiPM_PCB_Pos,         // its position
                   SiPM_PCB_LV,          // its logical volume
                   "SiPM_PCB_PV",        // its name
                   detElement_Cal_LV,      // its mother  volume
                   false,                // no boolean operation
                   0,                    // copy number
                   fCheckOverlaps);      // checking overlaps 

    //======================================================
    // Visualization attributes
    //======================================================
     G4Color red(0.9843, 0.0000, 0.0275, 1.0);
     G4Color red_orange(0.9843, 0.3098, 0.0275, 1.0);
     G4Color orange(0.9843, 0.5294, 0.0314, 1.0);
     G4Color yellow_orange(0.9922, 0.7647, 0.0353, 1.0);
     G4Color yellow(0.9922, 1.0000, 0.0431, 1.0);
     G4Color yellow_green(0.3412, 0.7725, 0.0235, 1.0);
     G4Color green(0.0745, 0.5412, 0.0118, 1.0);
     G4Color blue_green(0.0745, 0.7451, 0.7059, 1.0);
     G4Color blue(0.0745, 0.3098, 0.7647, 1.0);
     G4Color blue_violet(0.3608, 0.0000, 0.5020, 1.0);
     G4Color violet(0.5020, 0.0000, 0.5020, 1.0);
     G4Color red_violet(0.7647, 0.0000, 0.5020, 1.0);
  
    world_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    det_module_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    daq_module_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    pwr_module_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    pyld_module_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detColumn_C_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detColumn_S_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detColumn_Cal_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );    
    SCINT_Case_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    SCINT_Case_Top_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    SCINT_Case_Bot_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detElement_C_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detElement_S_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detElement_Cal_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );

    auto check_VisAtt = new G4VisAttributes( violet );
    // SCINT_Case_LV ->   SetVisAttributes( check_VisAtt );
    // SCINT_Case_Top_LV->SetVisAttributes( check_VisAtt );
    // SCINT_Case_Bot_LV->SetVisAttributes( check_VisAtt );


    auto wrap_VisAtt = new G4VisAttributes( orange );
    wrap_VisAtt -> SetVisibility( true );
    detWrap_LV -> SetVisAttributes( wrap_VisAtt );

    auto metal_VisAtt = new G4VisAttributes( G4Color::Gray() );
    metal_VisAtt -> SetVisibility( true );
    ENCL_Bot_LV -> SetVisAttributes( metal_VisAtt );
    ENCL_Side1_LV -> SetVisAttributes( metal_VisAtt );
    ENCL_Side2_LV -> SetVisAttributes( metal_VisAtt );
    ENCL_Top_LV -> SetVisAttributes( metal_VisAtt );
    ENCL_TopEdge_LV -> SetVisAttributes( metal_VisAtt );
    MIBP_LV -> SetVisAttributes( metal_VisAtt );
    MIBP_Edge_LV -> SetVisAttributes( metal_VisAtt );

    auto pc_VisAtt = new G4VisAttributes( green );
    pc_VisAtt -> SetVisibility( true );
    APB_LV -> SetVisAttributes( pc_VisAtt );
    MIB_LV -> SetVisAttributes( pc_VisAtt );
    SiPM_PCB_LV -> SetVisAttributes( pc_VisAtt );
    VCB_Side2_LV -> SetVisAttributes( pc_VisAtt );
    VCB_Side1_LV -> SetVisAttributes( pc_VisAtt );

    auto con_VisAtt = new G4VisAttributes( yellow );
    APB_Con_Side1_LV -> SetVisAttributes( con_VisAtt );
    APB_Con_Side2_LV -> SetVisAttributes( con_VisAtt );
    
    auto pmt_VisAtt = new G4VisAttributes( G4Color::White() );
    pmt_VisAtt -> SetVisibility( true );
    SiPM_LV -> SetVisAttributes( pmt_VisAtt );


    auto scintC_VisAtt = new G4VisAttributes( blue );
    scintC_VisAtt -> SetVisibility(true);
    scintC_LV -> SetVisAttributes(scintC_VisAtt);
    // scintC_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );

    auto scintS_VisAtt = new G4VisAttributes( red );
    scintS_VisAtt -> SetVisibility(true);
    scintS_LV -> SetVisAttributes(scintS_VisAtt);
    // scintS_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );

     auto opad_VisAtt = new G4VisAttributes( blue_green );
     opad_VisAtt -> SetVisibility( true );
     OPad_LV -> SetVisAttributes( opad_VisAtt );

     auto Oring_VisAtt = new G4VisAttributes( G4Color::Black()  );
     ORing_LV -> SetVisAttributes(Oring_VisAtt);
     // calHouse_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );

    


    //======================================================
    // Step Limits
    //======================================================
    auto maxStep = 0.5*kScint_Xsize;
    auto stepLimit = new G4UserLimits( maxStep );
    scintC_LV->SetUserLimits( stepLimit );
    scintS_LV->SetUserLimits( stepLimit );




	G4cout << " " << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "World Volume Dimensions: " << G4endl;
	G4cout << "           dX: kWorld_Xsize      = " << kWorld_Xsize << " m" << G4endl;
	G4cout << "           dY: kWorld_Ysize      = " << kWorld_Ysize << " m" << G4endl;
	G4cout << "           dZ: kWorld_Zsize      = " << kWorld_Zsize << " m" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Scintillator Element Dimensions: " << G4endl;
	G4cout << "           dX: kScint_Xsize      = " << kScint_Xsize << " mm" << G4endl;
	G4cout << "           dY: kScint_Ysize      = " << kScint_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kScint_Zsize      = " << kScint_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Scintillator Pitch: " << G4endl;
	G4cout << "           dX: kScint_Xpitch     = " << kScint_Xpitch << " mm" << G4endl;
	G4cout << "           dY: kScint_Ypitch     = " << kScint_Ypitch << " mm" << G4endl;
	G4cout << "           dZ: kScint_Zpitch     = " << kScint_Zpitch << " mm" << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Scintillator Array Dimensions: " << G4endl;
	G4cout << "          N_x: kNumScint_X       = " << kNumScint_X << G4endl;
	G4cout << "          N_y: kNumScint_Y       = " << kNumScint_Y << G4endl;
	G4cout << "          N_z: kNumScint_Z       = " << kNumScint_Z << G4endl;		
	G4cout << "        N_tot: kNumScint         = " << kNumScint   << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Optical Pad Dimensions: " << G4endl;
	G4cout << "           dX: kOpticalPad_Xsize = " << kOpticalPad_Xsize << " mm" << G4endl;
	G4cout << "           dY: kOpticalPad_Ysize = " << kOpticalPad_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kOpticalPad_Zsize = " << kOpticalPad_Zsize << " mm" << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "SiPM Dimensions: " << G4endl;
	G4cout << "           dX: kSiPM_Xsize       = " << kSiPM_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSiPM_Ysize       = " << kSiPM_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSiPM_Zsize       = " << kSiPM_Zsize << " mm" << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "SiPM Power Board Dimensions: " << G4endl;
	G4cout << "           dX: kSiPM_PCB_Xsize   = " << kSiPM_PCB_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSiPM_PCB_Ysize   = " << kSiPM_PCB_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSiPM_PCB_Zsize   = " << kSiPM_PCB_Zsize << " mm" << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "SiPM Gap Size: " << G4endl;
	G4cout << "          Gap: kDet_Gap          = " << kDet_Gap << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Detector Element Dimensions: " << G4endl;
	G4cout << "           dX: kDetElement_Xsize = " << kDetElement_Xsize << " mm" << G4endl;
	G4cout << "           dY: kDetElement_Ysize = " << kDetElement_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kDetElement_Zsize = " << kDetElement_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Scintillator Case Thickness: " << G4endl;
	G4cout << "      Thickness: kScint_Case_Thickness = " << kScint_Case_Thickness << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Scintillator Case Dimensions - TOP: " << G4endl;
	G4cout << "           dX: kScint_Case_Top_Xsize = " << kScint_Case_Top_Xsize << " mm" << G4endl;
	G4cout << "           dY: kScint_Case_Top_Ysize = " << kScint_Case_Top_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kScint_Case_Top_Zsize = " << kScint_Case_Top_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Scintillator Case Dimensions - BOTTOM: " << G4endl;
	G4cout << "           dX: kScint_Case_Bot_Xsize = " << kScint_Case_Bot_Xsize << " mm" << G4endl;
	G4cout << "           dY: kScint_Case_Bot_Ysize = " << kScint_Case_Bot_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kScint_Case_Bot_Zsize = " << kScint_Case_Bot_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Scintillator Case Dimensions: " << G4endl;
	G4cout << "           dX: kScint_Case_Xsize = " << kScint_Case_Xsize << " mm" << G4endl;
	G4cout << "           dY: kScint_Case_Ysize = " << kScint_Case_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kScint_Case_Zsize = " << kScint_Case_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Module Interface Board (MIB) Dimensions: " << G4endl;
	G4cout << "           dX: kMIB_Xsize = " << kMIB_Xsize << " mm" << G4endl;
	G4cout << "           dY: kMIB_Ysize = " << kMIB_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kMIB_Zsize = " << kMIB_Zsize << " mm" << G4endl;
	G4cout << "          Gap: kAPB_MIB_Zoffset = " << kAPB_MIB_Zoffset << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Analog Power Board (APB) Dimensions: " << G4endl;
	G4cout << "           dX: kAPB_Xsize = " << kAPB_Xsize << " mm" << G4endl;
	G4cout << "           dY: kAPB_Ysize = " << kAPB_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kAPB_Zsize = " << kAPB_Zsize << " mm" << G4endl;
	G4cout << "          Gap: kAPB_Zoffset = " << kAPB_Zoffset << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "APB-MIB Connector Dimensions: " << G4endl;
	G4cout << "           dX: kAPB_Con_Xsize = " << kAPB_Con_Xsize << " mm" << G4endl;
	G4cout << "           dY: kAPB_Con_Ysize = " << kAPB_Con_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kAPB_Con_Zsize = " << kAPB_Con_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Base Plate (Al) Dimensions: " << G4endl;
	G4cout << "           dX: kENCL_Bot_Xsize = " << kENCL_Bot_Xsize << " mm" << G4endl;
	G4cout << "           dY: kENCL_Bot_Ysize = " << kENCL_Bot_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kENCL_Bot_Zsize = " << kENCL_Bot_Zsize << " mm" << G4endl;	
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Base Plate (Sn) Dimensions: " << G4endl;
	G4cout << "           dX: kSHSN_Bot_Xsize = " << kSHSN_Bot_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSHSN_Bot_Ysize = " << kSHSN_Bot_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSHSN_Bot_Zsize = " << kSHSN_Bot_Zsize << " mm" << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Base Plate (Pb) Dimensions: " << G4endl;
	G4cout << "           dX: kSHPB_Bot_Xsize = " << kSHPB_Bot_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSHPB_Bot_Ysize = " << kSHPB_Bot_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSHPB_Bot_Zsize = " << kSHPB_Bot_Zsize << " mm" << G4endl;	


	G4cout << "*********************************************************" << G4endl;
	G4cout << "Detector Column Dimensions: " << G4endl;
	G4cout << "           dX: kDetColumn_Xsize = " << kDetColumn_Xsize << " mm" << G4endl;
	G4cout << "           dY: kDetColumn_Ysize = " << kDetColumn_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kDetColumn_Zsize = " << kDetColumn_Zsize << " mm" << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Module Dimensions: " << G4endl;
	G4cout << "           dX: kDet_Module_Xsize = " << kDet_Module_Xsize << " mm" << G4endl;
	G4cout << "           dY: kDet_Module_Ysize = " << kDet_Module_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kDet_Module_Zsize = " << kDet_Module_Zsize << " mm" << G4endl;		
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Enclose Side1 (Al) Dimensions: " << G4endl;
	G4cout << "           dX: kENCL_Side1_Xsize = " << kENCL_Side1_Xsize << " mm" << G4endl;
	G4cout << "           dY: kENCL_Side1_Ysize = " << kENCL_Side1_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kENCL_Side1_Zsize = " << kENCL_Side1_Zsize << " mm" << G4endl;			
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Enclose Side1 (Sn) Dimensions: " << G4endl;
	G4cout << "           dX: kSHSN_Side1_Xsize = " << kSHSN_Side1_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSHSN_Side1_Ysize = " << kSHSN_Side1_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSHSN_Side1_Zsize = " << kSHSN_Side1_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Enclose Side1 (Pb) Dimensions: " << G4endl;
	G4cout << "           dX: kSHPB_Side1_Xsize = " << kSHPB_Side1_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSHPB_Side1_Ysize = " << kSHPB_Side1_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSHPB_Side1_Zsize = " << kSHPB_Side1_Zsize << " mm" << G4endl;	
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Enclose Side2 (Al) Dimensions: " << G4endl;
	G4cout << "           dX: kENCL_Side2_Xsize = " << kENCL_Side2_Xsize << " mm" << G4endl;
	G4cout << "           dY: kENCL_Side2_Ysize = " << kENCL_Side2_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kENCL_Side2_Zsize = " << kENCL_Side2_Zsize << " mm" << G4endl;			
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Enclose Side2(Sn) Dimensions: " << G4endl;
	G4cout << "           dX: kSHSN_Side2_Xsize = " << kSHSN_Side2_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSHSN_Side2_Ysize " << kSHSN_Side2_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSHSN_Side2_Zsize " << kSHSN_Side2_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Enclose Side2 (Pb) Dimensions: " << G4endl;
	G4cout << "           dX: kSHPB_Side2_Xsize = " << kSHPB_Side2_Xsize << " mm" << G4endl;
	G4cout << "           dY: kSHPB_Side2_Ysize = " << kSHPB_Side2_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kSHPB_Side2_Zsize = " << kSHPB_Side2_Zsize << " mm" << G4endl;
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Vertical Board Side1 Dimensions: " << G4endl;
	G4cout << "           dX: kVCB_Side1_Xsize = " << kVCB_Side1_Xsize << " mm" << G4endl;
	G4cout << "           dY: kVCB_Side1_Ysize = " << kVCB_Side1_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kVCB_Side1_Zsize = " << kVCB_Side1_Zsize << " mm" << G4endl;	
	G4cout << "*********************************************************" << G4endl;
	G4cout << "Vertical Board Side2 Dimensions: " << G4endl;
	G4cout << "           dX: kVCB_Side2_Xsize = " << kVCB_Side2_Xsize << " mm" << G4endl;
	G4cout << "           dY: kVCB_Side2_Ysize = " << kVCB_Side2_Ysize << " mm" << G4endl;
	G4cout << "           dZ: kVCB_Side2_Zsize = " << kVCB_Side2_Zsize << " mm" << G4endl;	
	
	
				
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "W Shield - Type A: " << G4endl;
// 	G4cout << "           dX: " << ShieldA_WShield_dX << " mm" << G4endl;
// 	G4cout << "           dY: " << ShieldA_WShield_dY << " mm" << G4endl;
// 	G4cout << "           dZ: " << ShieldA_WShield_dZ << " mm" << G4endl;
// 	G4cout << " " << G4endl;
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "Sn Shield - Type B: " << G4endl;
// 	G4cout << "           dX: " << ShieldB_SnShield_dX << " mm" << G4endl;
// 	G4cout << "           dY: " << ShieldB_SnShield_dY << " mm" << G4endl;
// 	G4cout << "           dZ: " << ShieldB_SnShield_dZ << " mm" << G4endl;
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "W Shield - Type B: " << G4endl;
// 	G4cout << "           dX: " << ShieldB_WShield_dX << " mm" << G4endl;
// 	G4cout << "           dY: " << ShieldB_WShield_dY << " mm" << G4endl;
// 	G4cout << "           dZ: " << ShieldB_WShield_dZ << " mm" << G4endl;		
// 	G4cout << " " << G4endl;
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "Sn Shield - Type C: " << G4endl;
// 	G4cout << "           dX: " << ShieldC_SnShield_dX << " mm" << G4endl;
// 	G4cout << "           dY: " << ShieldC_SnShield_dY << " mm" << G4endl;
// 	G4cout << "           dZ: " << ShieldC_SnShield_dZ << " mm" << G4endl;
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "W Shield - Type C: " << G4endl;
// 	G4cout << "           dX: " << ShieldC_WShield_dX << " mm" << G4endl;
// 	G4cout << "           dY: " << ShieldC_WShield_dY << " mm" << G4endl;
// 	G4cout << "           dZ: " << ShieldC_WShield_dZ << " mm" << G4endl;		
// 	G4cout << " " << G4endl;
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "Sn Shield - Type D: " << G4endl;
// 	G4cout << "           dX: " << ShieldD_SnShield_dX << " mm" << G4endl;
// 	G4cout << "           dY: " << ShieldD_SnShield_dY << " mm" << G4endl;
// 	G4cout << "           dZ: " << ShieldD_SnShield_dZ << " mm" << G4endl;
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "W Shield - Type D: " << G4endl;
// 	G4cout << "           dX: " << ShieldD_WShield_dX << " mm" << G4endl;
// 	G4cout << "           dY: " << ShieldD_WShield_dY << " mm" << G4endl;
// 	G4cout << "           dZ: " << ShieldD_WShield_dZ << " mm" << G4endl;						
// 	G4cout << " " << G4endl;
// 	G4cout << "*********************************************************" << G4endl;
// 	G4cout << "FRAM Plate: " << G4endl;
// 	G4cout << "           dX: " << FRAM_X << " mm" << G4endl;
// 	G4cout << "           dY: " << FRAM_Y << " mm" << G4endl;
// 	G4cout << "           dZ: " << FRAM_Z << " mm" << G4endl;
// 	G4cout << "            X: " << FRAM_Xpos << " mm" << G4endl;
// 	G4cout << "            Y: " << FRAM_Ypos << " mm" << G4endl;
// 	G4cout << "            Z: " << FRAM_Zpos << " mm" << G4endl;
// 
// 












    //======================================================
    // Print some information
    //======================================================
    G4ThreeVector TopCenter = G4ThreeVector( 0., 0., (det_mod_Zpos + det_mod_Z/2) );
    // G4RotationMatrix TopCenter_rot = G4RotationMatrix( 0., fZenithAngle, 0. );
    // TopCenter.transform( TopCenter_rot );

    // G4ThreeVector ColimatorHole = G4ThreeVector( 0., 0., (collimator_Zpos - collimator_Z/2 + ELC1_Z + BLC_Z - BLC_Slot_Z) );
    // G4RotationMatrix ColimatorHole_rot = G4RotationMatrix( 0., fZenithAngle, 0. );
    // TopCenter.transform( TopCenter_rot );

    G4cout << G4endl;
    G4cout << "------ Instrument Dimensions: " << G4endl;
    G4cout << "           X: " << det_mod_X/mm << " mm" << G4endl;
    G4cout << "           Y: " << det_mod_Y/mm << " mm" << G4endl;
    G4cout << "           Z: " << det_mod_Z/mm << " mm" << G4endl;

    G4cout << "------ Center of Top of Instrument: " << G4endl;
    G4cout << "           X: " << TopCenter.x()/mm << " mm" << G4endl;
    G4cout << "           Y: " << TopCenter.y()/mm << " mm" << G4endl;
    G4cout << "           Z: " << TopCenter.z()/mm << " mm" << G4endl;

    // G4cout << "------ Collimator Hole Position:" << G4endl;
    // G4cout << "           X: " << ColimatorHole.x()/mm << " mm" << G4endl;
    // G4cout << "           Y: " << ColimatorHole.y()/mm << " mm" << G4endl;
    // G4cout << "           Z: " << ColimatorHole.z()/mm << " mm" << G4endl;

    // G4cout << G4endl;
    // G4cout << G4endl;


    //======================================================
    // Always return the physical World
    //======================================================
    return world_PV;
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void DetectorConstruction::ConstructSDandField()
  {
    auto SDManager = G4SDManager::GetSDMpointer();
    auto LVS = G4LogicalVolumeStore::GetInstance();

    //----------------------------------
    // Sensitive detectors
    //----------------------------------
    auto scint_SD = new ScintSD( "grapeDet" );
    SDManager->AddNewDetector( scint_SD );
    LVS->GetVolume("ScintC_LV")->SetSensitiveDetector( scint_SD );
    LVS->GetVolume("ScintS_LV")->SetSensitiveDetector( scint_SD );

  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void DetectorConstruction::SetZenithAngle( G4double zang )
  {
    if (fZenithAngle != zang) {
      fZenithAngle = zang;

      auto Xpos = 0.0*mm;
      auto Ypos = (kENCL_Side1_Zsize/2 - kScint_Zsize/2)*std::sin( fZenithAngle );
      auto Zpos = kDet_Module_Zsize/2*std::cos( fZenithAngle ) + kDet_Module_Xsize/2*(std::cos( fAzimuthAngle ) + std::sin( fAzimuthAngle ))*std::sin( fZenithAngle );
      auto Pos = G4ThreeVector( Xpos, Ypos, Zpos );
      auto RotMat = new G4RotationMatrix();
      RotMat -> setTheta( fZenithAngle );
      RotMat -> setPsi( fAzimuthAngle );

      if (fPhysicalModule) {
        fPhysicalModule->SetRotation(RotMat);
        fPhysicalModule->SetTranslation(Pos);
        G4cout
          << G4endl 
          << "----> The zenith angle is " << fZenithAngle/deg << " deg" << G4endl;
      
        UpdateGeometry();
      } else {
          G4cout
            << G4endl
            << "-->  WARNING from SetZenithAngle : "
            << "fPhysicalModule" << " not found" << G4endl;
      }

    }
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void DetectorConstruction::SetAzimuthAngle( G4double aang )
  {
    if (fAzimuthAngle != aang) {
      fAzimuthAngle = aang;

      auto Xpos = 0.0*mm;
      auto Ypos = (kENCL_Side1_Zsize/2 - kScint_Zsize/2)*std::sin( fZenithAngle );
      auto Zpos = kDet_Module_Zsize/2*std::cos( fZenithAngle ) + kDet_Module_Xsize/2*(std::cos( fAzimuthAngle ) + std::sin( fAzimuthAngle ))*std::sin( fZenithAngle );
      auto Pos = G4ThreeVector( Xpos, Ypos, Zpos );
      auto RotMat = new G4RotationMatrix();
      RotMat -> setTheta( fZenithAngle );
      RotMat -> setPsi( fAzimuthAngle );
    
      if (fPhysicalModule) {
        fPhysicalModule->SetRotation(RotMat);
        fPhysicalModule->SetTranslation(Pos);
        G4cout
          << G4endl 
          << "----> The azimuth angle is " << fAzimuthAngle/deg << " deg" << G4endl;
      
        UpdateGeometry();
      } else {
          G4cout
            << G4endl
            << "-->  WARNING from SetZenithAngle : "
            << "fPhysicalModule" << " not found" << G4endl;
      }

    } 
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void DetectorConstruction::SetPolarizationAngle( G4double pang )
  {
    
    if (fPolarizationAngle != pang) {
      fPolarizationAngle = pang;

      auto RotMat = new G4RotationMatrix();
      RotMat -> setPhi( fPolarizationAngle );

      if (fPhysicalCollimator) {
        fPhysicalCollimator->SetRotation(RotMat);
        G4cout
          << G4endl 
          << "----> The polarization angle is " << fPolarizationAngle/deg << " deg" << G4endl;
      
        UpdateGeometry();
      } else {
          G4cout
            << G4endl
            << "-->  WARNING from SetPolarizationAngle : "
            << "fPhysicalCollimator" << " not found" << G4endl;
      }
    }
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void DetectorConstruction::UpdateGeometry()
  {
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    G4RunManager::GetRunManager()->ReinitializeGeometry();
  }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
