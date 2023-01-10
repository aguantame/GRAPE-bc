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
/// \file Constants.hh
/// \brief Definition of the Constants class


#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{
  //****************************************************************************
  /// Constants to define geometry.
  ///
  //****************************************************************************
  constexpr auto kNumKeep = 8;
  
  constexpr auto kDim = 245;
  constexpr auto kNumC = 145;
  constexpr auto kNumP = 100; //! not including tagged sources
  
  //--------------------------------------------------------
  // Scintillator Elements and Array
  //--------------------------------------------------------
  constexpr auto kScint_Xsize = 12.5*mm;
  constexpr auto kScint_Ysize = 12.5*mm;
  constexpr auto kScint_Zsize = 12.5*mm;

  constexpr auto kScint_Xpitch = 21.1*mm;
  constexpr auto kScint_Ypitch = 21.1*mm;
  constexpr auto kScint_Zpitch = 21.84*mm; //! based on avg measurements
  // constexpr auto kScint_Zpitch = 17.5*mm;


  constexpr auto kNumScint_X = 7;
  constexpr auto kNumScint_Y = 7;
  constexpr auto kNumScint_Z = 5;

  constexpr auto kNumScint = kNumScint_X * kNumScint_Y * kNumScint_Z;

  // Calibration source
  constexpr auto kCal_Rmin = 0.0*mm;
  constexpr auto kCal_Rmax = 5.0*mm;
  constexpr auto kCal_Zsize = 10.0*mm;

  //--------------------------------------------------------
  // Optical Interface and Readout Board
  //--------------------------------------------------------

  // Optical Pad
  constexpr auto kOpticalPad_Xsize = kScint_Xsize;
  constexpr auto kOpticalPad_Ysize = kScint_Ysize;
  constexpr auto kOpticalPad_Zsize = 1.0*mm;

  // SiPM (Hamamatsu S13361-3050NE-04)
  constexpr auto kSiPM_Xsize = 13.0*mm;
  constexpr auto kSiPM_Ysize = 13.0*mm;
  constexpr auto kSiPM_Zsize = 1.35*mm;

  // SiPM Power Board
  constexpr auto kSiPM_PCB_Xsize = kSiPM_Xsize;
  constexpr auto kSiPM_PCB_Ysize = kSiPM_Xsize;
  constexpr auto kSiPM_PCB_Zsize = 1.57*mm;


  //--------------------------------------------------------
  // Detector Elements
  //--------------------------------------------------------
  //! Individual Det Assembly
  constexpr auto kDetAssembly_Zsize = kScint_Zsize + kOpticalPad_Zsize + kSiPM_Zsize + kSiPM_PCB_Zsize;
  
  //! Scintillator wrap  (adds ~2.05 mm in xyz)
  constexpr auto kDetWrap_Thickness = 1.025*mm;

  constexpr auto kDetWrap_Xsize = kSiPM_Xsize + 2*kDetWrap_Thickness;
  constexpr auto kDetWrap_Ysize = kSiPM_Ysize + 2*kDetWrap_Thickness;
  constexpr auto kDetWrap_Zsize = kDetAssembly_Zsize + 2*kDetWrap_Thickness;

  constexpr auto kDetWrap_Hole_Xsize = kSiPM_Xsize;
  constexpr auto kDetWrap_Hole_Ysize = kSiPM_Ysize;
  constexpr auto kDetWrap_Hole_Zsize = kDetAssembly_Zsize;

  constexpr auto kWrappedDetAssembly_Zsize = kScint_Zsize + kOpticalPad_Zsize + kSiPM_Zsize + kSiPM_PCB_Zsize + 2*kDetWrap_Thickness;

  //! SiPM Gap (5.07 mm without wrap based on drawings)
  constexpr auto kDet_Gap = 21.84 -
                           (kScint_Zsize + 
                            kOpticalPad_Zsize + 
                            kSiPM_Zsize + 
                            kSiPM_PCB_Zsize + 
                            kDetWrap_Thickness); //! Where does the 107 come from?

  constexpr auto kDetElement_Xsize = kSiPM_Xsize;
  constexpr auto kDetElement_Ysize = kSiPM_Ysize;
  constexpr auto kDetElement_Zsize = 
                  kScint_Zsize +
                  kOpticalPad_Zsize +
                  kSiPM_Zsize +
                  kSiPM_PCB_Zsize +
                  kDet_Gap;

  //! Vertical Circuit Boards (VCB)
  constexpr auto kVCB_Thickness = 0.7874*mm;

  //   constexpr auto kVCB_XYsize = 14.224*mm;
  constexpr auto kfullVCB_Zsize = 110.998*mm;
  constexpr auto kVCB_Zsize = 110.998*mm;
  // constexpr auto kVCB_Zsize = kfullVCB_Zsize - (kfullVCB_Zsize - (kNumScint_Z *kScint_Zpitch));
  constexpr auto kVCB_Side1_Xsize = kVCB_Thickness;
  constexpr auto kVCB_Side1_Ysize = kSiPM_Ysize + 2*kDetWrap_Thickness;
  constexpr auto kVCB_Side1_Zsize = kVCB_Zsize;
  // constexpr auto kVCB_Side1_Zsize = kDetElement_Zsize * kNumScint_Z;

  constexpr auto kVCB_Side2_Xsize = kSiPM_Xsize + 2*kDetWrap_Thickness;
  constexpr auto kVCB_Side2_Ysize = kVCB_Thickness;
  constexpr auto kVCB_Side2_Zsize = kVCB_Side1_Zsize;   


  // Detector Housing (115*mm assembled height without pins)
  constexpr auto kScint_Case_Thickness = 1.91*mm;

  constexpr auto kScint_Case_Top_Xsize = 20.8*mm;
  constexpr auto kScint_Case_Top_Ysize = 20.8*mm;
  constexpr auto kScint_Case_Top_Zsize = 7.20*mm;

  constexpr auto kScint_Case_Bot_Xsize = 20.8*mm;
  constexpr auto kScint_Case_Bot_Ysize = 20.8*mm;
  constexpr auto kScint_Case_Bot_Zsize = 8.20*mm;

  constexpr auto kScint_Case_Xsize = 22.62*mm;
  constexpr auto kScint_Case_Ysize = 22.62*mm;
  constexpr auto kScint_Case_Zsize = 99.60*mm;

  constexpr auto kScint_Case_Hole_Xsize = kScint_Case_Xsize - 2*kScint_Case_Thickness;
  constexpr auto kScint_Case_Hole_Ysize = kScint_Case_Ysize - 2*kScint_Case_Thickness;
  constexpr auto kScint_Case_Hole_Zsize = 2*kScint_Case_Zsize + 2*kScint_Case_Thickness;

// O-Ring (rectangular shape assumed)
  constexpr auto kORing_Thickness = 1.5*mm;

  constexpr auto kORing_Xsize = kScint_Case_Hole_Xsize;
  constexpr auto kORing_Ysize = kScint_Case_Hole_Xsize;
  constexpr auto kORing_Zsize = kORing_Thickness;

  constexpr auto kORing_Hole_Xsize = kSiPM_Xsize + 2*kDetWrap_Thickness + 2*kVCB_Thickness;
  constexpr auto kORing_Hole_Ysize = kSiPM_Ysize + 2*kDetWrap_Thickness + 2*kVCB_Thickness;
  constexpr auto kORing_Hole_Zsize = 2*kORing_Zsize + 2*kORing_Thickness;



  //--------------------------------------------------------
  // Electronics
  //--------------------------------------------------------



  // Module Interface Board (MIB)
  constexpr auto kMIB_Xsize = 152.0;
  constexpr auto kMIB_Ysize = 152.0;
  constexpr auto kMIB_Zsize = 1.5*mm;

  // Analog Power Board (APB)
  constexpr auto kAPB_Xsize = 1.5*mm;
  constexpr auto kAPB_Ysize = 147.0*mm;
  constexpr auto kAPB_Zsize = 120.0*mm;
  constexpr auto kAPB_Zoffset = 4.0*mm; // baseplate offset

  // APB - MIB Connectors
  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;
  constexpr auto kAPB_Con_Xsize = 5.0*mm;
  constexpr auto kAPB_Con_Ysize = 75.0*mm;
  constexpr auto kAPB_Con_Zsize = 10.0*mm;

  //--------------------------------------------------------
  // Instrument Structural Compenents
  //--------------------------------------------------------

  // Enclosure (ENCL) Base Plate 
  constexpr auto kENCL_Thickness = 5.0*mm;
  constexpr auto kENCL_Bot_Xsize = 162.0*mm;
  constexpr auto kENCL_Bot_Ysize = 162.0*mm;
  constexpr auto kENCL_Bot_Zsize = kENCL_Thickness;

  //--------------------------------------------------------
  // Shield (SHCU) Base Plate - Copper
  //--------------------------------------------------------
  constexpr auto kSHCU_Thickness = 2.0*mm;
  constexpr auto kSHCU_Bot_Xsize = kENCL_Bot_Xsize + 2.0*kENCL_Thickness;
  constexpr auto kSHCU_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness;
  constexpr auto kSHCU_Bot_Zsize = kSHCU_Thickness;


  //--------------------------------------------------------
  // Shield (SHSN) Base Plate - Tin
  //--------------------------------------------------------
  constexpr auto kSHSN_Thickness = 1.0*mm;
  constexpr auto kSHSN_Bot_Xsize = kENCL_Bot_Xsize + 2.0*kENCL_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHSN_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHSN_Bot_Zsize = kSHSN_Thickness;



  //--------------------------------------------------------
  // Shield (SHPB) Base Plate - Lead
  //--------------------------------------------------------
  constexpr auto kSHPB_Thickness = 4.5*mm;
  constexpr auto kSHPB_Bot_Xsize = kENCL_Bot_Xsize + 2.0*kENCL_Thickness + 2.0*kSHSN_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHPB_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness + 2.0*kSHSN_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHPB_Bot_Zsize = kSHPB_Thickness;

  //--------------------------------------------------------
  // Enclosure (ENCL) Top
  //--------------------------------------------------------
  constexpr auto kENCL_Top_Xsize = kScint_Xpitch;
  constexpr auto kENCL_Top_Ysize = kScint_Ypitch;
  constexpr auto kENCL_Top_Zsize = 7.5*mm;

  constexpr auto kENCL_Top_Hole_Xsize = kScint_Case_Top_Xsize;
  constexpr auto kENCL_Top_Hole_Ysize = kScint_Case_Top_Ysize;
  constexpr auto kENCL_Top_Hole_Zsize = 2*kENCL_Top_Zsize;

  constexpr auto kENCL_Top_Zoffset = 0.75*mm;

  //--------------------------------------------------------
  // Enclosure (ENCL) Top Edge
  //--------------------------------------------------------
  constexpr auto kENCL_TopEdge_Xsize = kENCL_Bot_Xsize;
  constexpr auto kENCL_TopEdge_Ysize = kENCL_Bot_Ysize;
  constexpr auto kENCL_TopEdge_Zsize = kENCL_Top_Zsize;

  constexpr auto kENCL_TopEdge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kENCL_TopEdge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kENCL_TopEdge_Hole_Zsize = 2*kENCL_TopEdge_Zsize;

  //--------------------------------------------------------
  // MIB Plate
  //--------------------------------------------------------
  constexpr auto kMIBP_Xsize = kScint_Xpitch;
  constexpr auto kMIBP_Ysize = kScint_Ypitch;
  constexpr auto kMIBP_Zsize = 10.5*mm;

  // holes
  constexpr auto kMIBP_Hole_Xsize = kScint_Case_Bot_Xsize;
  constexpr auto kMIBP_Hole_Ysize = kScint_Case_Bot_Ysize;
  constexpr auto kMIBP_Hole_Zsize = 2*kMIBP_Zsize;

  constexpr auto kMIBP_Zoffset = 1.5*mm;

  //--------------------------------------------------------
  // MIB Plate Edge
  //--------------------------------------------------------
  constexpr auto kMIBP_Edge_Xsize = kENCL_Bot_Xsize;
  constexpr auto kMIBP_Edge_Ysize = kENCL_Bot_Ysize;
  constexpr auto kMIBP_Edge_Zsize = kMIBP_Zsize;

  constexpr auto kMIBP_Edge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kMIBP_Edge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kMIBP_Edge_Hole_Zsize = 2*kMIBP_Edge_Zsize;

  //--------------------------------------------------------
  // DETECTOR Column
  //--------------------------------------------------------
  constexpr auto kDetColumn_Xsize = kScint_Xpitch;
  constexpr auto kDetColumn_Ysize = kScint_Ypitch;
  constexpr auto kDetColumn_Zsize = 
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kScint_Case_Top_Zsize;

  //--------------------------------------------------------
  // MODULE
  //--------------------------------------------------------
  constexpr auto kModule_Xsize = kENCL_Bot_Xsize + 2*kENCL_Thickness + 2*kSHSN_Thickness + 2*kSHPB_Thickness;
  constexpr auto kModule_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness + 2*kSHSN_Thickness + 2*kSHPB_Thickness;
  constexpr auto kModule_Zsize = 
  			      kSHPB_Bot_Zsize +
				  kSHSN_Bot_Zsize +
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kDetColumn_Zsize;

  //--------------------------------------------------------
  // Enclosure (ENCL) Side
  //--------------------------------------------------------
  constexpr auto kENCL_Side1_Xsize = kENCL_Thickness;
  constexpr auto kENCL_Side1_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
  constexpr auto kENCL_Side1_Zsize = 
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kENCL_Top_Zoffset +
                  kENCL_Top_Zsize;

  constexpr auto kENCL_Side2_Xsize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
  constexpr auto kENCL_Side2_Ysize = kENCL_Thickness;
  constexpr auto kENCL_Side2_Zsize = kENCL_Side1_Zsize;

  //--------------------------------------------------------
  // Enclosure (SHCU) Side - Copper
  //--------------------------------------------------------
  constexpr auto kSHCU_Side1_Xsize = kSHCU_Thickness;
  constexpr auto kSHCU_Side1_Ysize = kSHCU_Bot_Ysize + 2*kSHCU_Thickness;
  constexpr auto kSHCU_Side1_Zsize = 
                  kSHCU_Bot_Zsize +
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kENCL_Top_Zoffset +
                  kENCL_Top_Zsize;

  constexpr auto kSHCU_Side2_Xsize = kSHCU_Bot_Ysize + 2*kSHCU_Thickness;
  constexpr auto kSHCU_Side2_Ysize = kSHCU_Thickness;
  constexpr auto kSHCU_Side2_Zsize = kSHCU_Side1_Zsize;


  //--------------------------------------------------------
  // Enclosure (SHSN) Side - Tin
  //--------------------------------------------------------
  constexpr auto kSHSN_Side1_Xsize = kSHSN_Thickness;
  constexpr auto kSHSN_Side1_Ysize = kSHSN_Bot_Ysize + 2*kSHSN_Thickness;
  constexpr auto kSHSN_Side1_Zsize = 
                  kSHSN_Bot_Zsize +
                  kSHCU_Bot_Zsize +
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kENCL_Top_Zoffset +
                  kENCL_Top_Zsize;

  constexpr auto kSHSN_Side2_Xsize = kSHSN_Bot_Ysize + 2*kSHSN_Thickness;
  constexpr auto kSHSN_Side2_Ysize = kSHSN_Thickness;
  constexpr auto kSHSN_Side2_Zsize = kSHSN_Side1_Zsize;


  //--------------------------------------------------------
  // Enclosure (SHPB) Side - Lead
  //--------------------------------------------------------
  constexpr auto kSHPB_Side1_Xsize = kSHPB_Thickness;
  constexpr auto kSHPB_Side1_Ysize = kSHPB_Bot_Ysize + 2*kSHPB_Thickness;
  constexpr auto kSHPB_Side1_Zsize = 
                  kSHPB_Bot_Zsize +
                  kSHSN_Bot_Zsize +
                  kSHCU_Bot_Zsize +
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kENCL_Top_Zoffset +
                  kENCL_Top_Zsize;

  constexpr auto kSHPB_Side2_Xsize = kSHPB_Bot_Ysize + 2*kSHPB_Thickness;
  constexpr auto kSHPB_Side2_Ysize = kSHPB_Thickness;
  constexpr auto kSHPB_Side2_Zsize = kSHPB_Side1_Zsize;

  //--------------------------------------------------------
  // WORLD
  //--------------------------------------------------------
  constexpr auto kWorld_Xsize = 5.0*m;
  constexpr auto kWorld_Ysize = 5.0*m;
  constexpr auto kWorld_Zsize = 5.0*m;


}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
