//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  August 2023 Balloon Flight Campaign
//  (V1) Created: Mar 2, 2022 by Camden Ertley
//  (V2) Created: September 23, 2022 by Camden Ertley
//  (V3) Modified: Dec 26, 2022 by Karla Onate Melecio
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1


#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4UserLimits.hh"
#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4AssemblyVolume.hh"

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  class DetectorMessenger;

  //****************************************************************************
  /// Detector construction class to define materials and geometry.
  ///
  //****************************************************************************
  class DetectorConstruction : public G4VUserDetectorConstruction
  {
    public:
      DetectorConstruction();
      ~DetectorConstruction() override;

      // methods from base class
      G4VPhysicalVolume* Construct() override;
      void ConstructSDandField() override;
      
      // set methods
      void SetOverlapFlag( G4bool flag ) {fCheckOverlaps = flag;};          
      void SetZenithAngle( G4double zang );          
      void SetAzimuthAngle( G4double aang );          
      void SetPolarizationAngle( G4double pang );          
      void UpdateGeometry();

    private:
      // methods
      void DefineMaterials();
      G4VPhysicalVolume* DefineVolumes();
    
      // data members
      DetectorMessenger* fDetMessenger = nullptr;   // messenger

      G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps

      G4VPhysicalVolume* fPhysicalModule = nullptr;
      G4VPhysicalVolume* fPhysicalCollimator = nullptr;
      
      G4double fZenithAngle = 0.;
      G4double fAzimuthAngle = 0.;
      G4double fPolarizationAngle = 0.;
  };
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

