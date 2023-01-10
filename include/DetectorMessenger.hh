//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  August 2023 Balloon Flight Campaign
//  (V1) Created: Mar 2, 2022 by Camden Ertley
//  (V2) Created: September 23, 2022 by Camden Ertley
//  (V3) Same V1
//
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file DetectorMessenger.cc
/// \brief Definition of the DetectorMessenger class

#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  class DetectorConstruction;

  //****************************************************************************
  /// Detector Messenger Class
  ///
  //****************************************************************************
  class DetectorMessenger: public G4UImessenger
  {
    public:
      DetectorMessenger( DetectorConstruction* );
      ~DetectorMessenger() override;

      // methods from base class
      void SetNewValue(G4UIcommand*, G4String) override;
      
    private:
      // data members
      DetectorConstruction* fDetectorConstruction = nullptr;
      
      G4UIdirectory* fUSERDir = nullptr;
      G4UIdirectory* fDetDir = nullptr;
      
      G4UIcmdWithABool* fOverlapCmd = nullptr;

      G4UIcmdWithADoubleAndUnit* fZenithCmd = nullptr;
      G4UIcmdWithADoubleAndUnit* fAzimuthCmd = nullptr;
      G4UIcmdWithADoubleAndUnit* fPolarizationCmd = nullptr;

      G4UIcmdWithoutParameter* fUpdateCmd = nullptr;
  };

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
