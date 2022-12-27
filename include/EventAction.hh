//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  Cube Balloon Flight
//  Created: Mar 2, 2022 by Camden Ertley
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

    private:      
      // methods
      G4double BroadenEnergy(const G4String& type, G4double energy);

      // data members
      G4int  fScintHCID = -1;
  };
                     
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

    
