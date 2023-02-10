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
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"

#include "ScintHit.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  class PrimaryGeneratorAction;
  class RunAction;

  //****************************************************************************
  /// Event action class
  ///
  //****************************************************************************
  class EventAction : public G4UserEventAction
  {
    public:
      EventAction();
      ~EventAction() override;

      // methods from base class
      void  BeginOfEventAction(const G4Event* ) override;
      void    EndOfEventAction(const G4Event* ) override;

      // methods
      std::vector<G4String>& GetPhys() {return fPhysType; }


    private:      
      // methods
      G4double BroadenEnergy(const G4String& type, G4double energy);

      // data members
      G4int  fScintHCID = -1;

      std::vector<G4String> fPhysType;
  };
                     
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

    
