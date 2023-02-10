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
/// \file ScintHit.cc
/// \brief Implementation of the ScintHit class

#include "ScintHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{
  G4ThreadLocal G4Allocator<ScintHit>* ScintHitAllocator = nullptr;

  //****************************************************************************
  // Constructor
  //****************************************************************************
  ScintHit::ScintHit()
  {}

  //****************************************************************************
  // Destructor
  //****************************************************************************
  ScintHit::~ScintHit() {}

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ScintHit::Draw()
  {}

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ScintHit::Print()
  {}

  //****************************************************************************
  // Operator
  //****************************************************************************
  G4bool ScintHit::operator==(const ScintHit& right) const
  {
    return ( this == &right ) ? true : false;
  }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
