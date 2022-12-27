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
/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include "G4GeneralParticleSource.hh"


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{


  //****************************************************************************
  // Constructor
  //****************************************************************************
  ActionInitialization::ActionInitialization()
  {}


  //****************************************************************************
  // Destructor
  //****************************************************************************
  ActionInitialization::~ActionInitialization()
  {}


  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ActionInitialization::BuildForMaster() const
  {
    SetUserAction(new RunAction);
  }


  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ActionInitialization::Build() const
  {
    PrimaryGeneratorAction* prim = new PrimaryGeneratorAction();
    SetUserAction(prim);

    RunAction* run = new RunAction();
    SetUserAction(run);

    EventAction* event = new EventAction();
    SetUserAction(event);
  }  

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
