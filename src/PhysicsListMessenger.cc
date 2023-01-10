//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  August 2023 Balloon Flight Campaign
//  (V1) Created: Mar 2, 2022 by Camden Ertley
//  (V2) Created: September 23, 2022 by Camden Ertley
//  (V3) same as V2
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file PhysicsListMessenger.cc
/// \brief Definition of the PhysicsListMessenger class

#include "PhysicsListMessenger.hh"
#include "PhysicsList.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  PhysicsListMessenger::PhysicsListMessenger( PhysicsList* phy )
  : fPhysicsList(phy)
  { 
    fPhyDir = new G4UIdirectory( "/user/phy/" );
    fPhyDir -> SetGuidance( "Physics list control." );
    
    fPListCmd = new G4UIcmdWithAString("/user/phy/setPhysics",this);
    fPListCmd->SetGuidance("Set modular physics list builder.");
    fPListCmd->SetParameterName("PList",false);
    fPListCmd->AvailableForStates(G4State_PreInit);

    fListCmd = new G4UIcmdWithoutParameter("/user/phy/listPhysics",this);
    fListCmd->SetGuidance("Available Physics Lists");
    fListCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  PhysicsListMessenger::~PhysicsListMessenger() {
    delete fPListCmd;
    delete fListCmd;
    delete fPhyDir;
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void PhysicsListMessenger::SetNewValue( G4UIcommand* command,G4String newValue) 
  {
    if( command == fPListCmd ) {
      if(fPhysicsList) {
        fPhysicsList->SetPhysicsList(newValue);
      } else {
        G4cout << "### PhysicsListMessenger WARNING: "
               << " /user/phy/setPhysics UI command is not available "
               << "for reference Physics List" << G4endl;
      }

    } else if( command == fListCmd ) {
      if(fPhysicsList) {
        fPhysicsList->List();
      } else { 
        G4cout << "### PhysicsListMessenger WARNING: "
               << " /user/phy/ListPhysics UI command is not available "
               << "for reference Physics List" << G4endl;
      }
    }
  }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%