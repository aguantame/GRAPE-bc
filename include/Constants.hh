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
  
  //--------------------------------------------------------------
  // Scintillator Elements and Array
  //--------------------------------------------------------------
  constexpr auto kScint_Xsize = 12.5*mm;
  constexpr auto kScint_Ysize = 12.5*mm;
  constexpr auto kScint_Zsize = 12.5*mm;

  // there are .875*mm between the scint cases
  constexpr auto kScint_Xpitch = 23.495*mm;
  constexpr auto kScint_Ypitch = 23.495*mm;
  constexpr auto kScint_Zpitch = 21.844*mm;



  constexpr auto kNumScint_X = 7;
  constexpr auto kNumScint_Y = 7;
  constexpr auto kNumScint_Z = 5;

  constexpr auto kNumScint = kNumScint_X * kNumScint_Y * kNumScint_Z;

  // Calibration source
  constexpr auto kCal_Rmin = 0.0*mm;
  constexpr auto kCal_Rmax = 5.0*mm;
  constexpr auto kCal_Zsize = 10.0*mm;

  //--------------------------------------------------------------
  // Optical Interface and Readout Board
  //--------------------------------------------------------------

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


  //--------------------------------------------------------------
  // Detector Elements
  //--------------------------------------------------------------
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
  constexpr auto kDet_Gap = kScint_Zpitch -
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



  //--------------------------------------------------------------
  // DAQ Container - Electronics
  //--------------------------------------------------------------

  //! Scintillator wrap  (adds ~2.05 mm in xyz)
  constexpr auto kDAQ_ENCL_Thickness = 11.1125*mm;
  constexpr auto kDAQ_ENCL_BOT_Thickness = 6.32*mm;

  constexpr auto kDAQ_ENCL_Xsize = 255.59*mm;
  constexpr auto kDAQ_ENCL_Ysize = 255.59*mm;
  constexpr auto kDAQ_ENCL_Zsize = 177.8*mm;

  constexpr auto kDAQ_ENCL_Hole_Xsize = kDAQ_ENCL_Xsize - 2*kDAQ_ENCL_Thickness;
  constexpr auto kDAQ_ENCL_Hole_Ysize = kDAQ_ENCL_Xsize - 2*kDAQ_ENCL_Thickness;
  constexpr auto kDAQ_ENCL_Hole_Zsize = kDAQ_ENCL_Zsize + 2*kDAQ_ENCL_BOT_Thickness;


  // DetModule Interface Board (MIB)
  constexpr auto kMIB_Xsize = 152.0;
  constexpr auto kMIB_Ysize = 152.0;
  constexpr auto kMIB_Zsize = 1.5*mm;
  constexpr auto kMIB_Zoffset = 2.7*mm;


  // Analog Power Board (APB)
  constexpr auto kAPB_Xsize = 1.2*mm;
  constexpr auto kAPB_Ysize = 25.0*mm;
  constexpr auto kAPB_Zsize = 38.1*mm;
  constexpr auto kAPB_Zoffset = 4.0*mm; // baseplate offset

  constexpr auto kAPB_X_Pitch = 21.1*mm;
  constexpr auto kAPB_Y_Pitch = 34.0*mm;
  

  // APB - MIB Connectors (Samtech Cable Connectors?)
  constexpr auto kNumAPB = 6;
  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;
  constexpr auto kAPB_Con_Pitch = 96.7*mm;
  constexpr auto kAPB_Con_Xsize = 24.8*mm; //size of inner shield cutouts
  constexpr auto kAPB_Con_Ysize = 4.9*mm; //size of inner shield cutouts
  constexpr auto kAPB_Con_Zsize = 3.8*mm; //size of inner shield cutouts

  // DAQ - Inner Shield Connectors (Samtech Cable Connectors?)
  constexpr auto kNumSHOLES = 6;
  constexpr auto kDAQ_INR_SHOLES_Xsize = 23.0*mm; //size of inner shield cutouts
  constexpr auto kDAQ_INR_SHOLES_Ysize = 76.2*mm; //size of inner shield cutouts
  constexpr auto kDAQ_INR_SHOLES_Zsize = 9.1*mm; //size of inner shield cutouts


  //--------------------------------------------------------------
  // Instrument Structural Compenents
  //--------------------------------------------------------------

  //--------------------------------------------------------------
  // Inner Enclosure Base Plates 
  // Copper > Tin > Lead > Aluminum
  //--------------------------------------------------------------
  // Inner shield Z-offset
  constexpr auto kINNER_SHLD_Zoffset = 95.3*mm;

  // Inner Enclosure (ENCL) Base Plate - Aluminum
  constexpr auto kENCL_Thickness = 1.5875*mm;
  constexpr auto kENCL_Bot_Xsize = 226.1*mm; //162.0*mm;
  constexpr auto kENCL_Bot_Ysize = 162.0*mm;
  constexpr auto kENCL_Bot_Zsize = kENCL_Thickness;

  //--------------------------------------------------------------
  // (SHCU) Inner Shield Base Plate - Copper
  //--------------------------------------------------------------
  constexpr auto kSHCU_Thickness = 2.066*mm;
  constexpr auto kSHCU_Bot_Xsize = 226.1*mm; //kENCL_Bot_Xsize + 2.0*kENCL_Thickness;
  constexpr auto kSHCU_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness;
  constexpr auto kSHCU_Bot_Zsize = kSHCU_Thickness;


  //--------------------------------------------------------------
  // (SHSN) Inner Shield Base Plate - Tin
  //--------------------------------------------------------------
  constexpr auto kSHSN_Thickness = 0.9906*mm;
  constexpr auto kSHSN_Bot_Xsize = 226.1*mm; //kENCL_Bot_Xsize + 2.0*kENCL_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHSN_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHSN_Bot_Zsize = kSHSN_Thickness;


  //--------------------------------------------------------------
  // (SHPB) Inner Shield Base Plate - Lead
  //--------------------------------------------------------------
  constexpr auto kSHPB_Thickness = 4.4958*mm;
  constexpr auto kSHPB_Bot_Xsize = 226.1*mm; //kENCL_Bot_Xsize + 2.0*kENCL_Thickness + 2.0*kSHSN_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHPB_Bot_Ysize = kENCL_Bot_Ysize + 2.0*kENCL_Thickness + 2.0*kSHSN_Thickness + 2.0*kSHCU_Thickness;
  constexpr auto kSHPB_Bot_Zsize = kSHPB_Thickness;

  //--------------------------------------------------------------
  // Enclosure (ENCL) Top
  //--------------------------------------------------------------
  // bottom layer of top enclosure is 4.4958
  constexpr auto kENCL_Top_Xsize = 23.5*mm;
  constexpr auto kENCL_Top_Ysize = 23.5*mm;
  constexpr auto kENCL_Top_Zsize = 6.32*mm;

  // Enclosure top holes begin 9.815mm from edge
  constexpr auto kENCL_Top_Hole_Xsize = kScint_Case_Top_Xsize;
  constexpr auto kENCL_Top_Hole_Ysize = kScint_Case_Top_Ysize;
  constexpr auto kENCL_Top_Hole_Zsize = 2*kENCL_Top_Zsize;

  constexpr auto kENCL_Top_Zoffset = 0.75*mm;

  //--------------------------------------------------------------
  // Enclosure (ENCL) Top Edge
  //--------------------------------------------------------------
  constexpr auto kENCL_TopEdge_Xsize = 181.864*mm;
  constexpr auto kENCL_TopEdge_Ysize = 181.864*mm;
  constexpr auto kENCL_TopEdge_Zsize = kENCL_Top_Zsize;

  // there are 2.695mm of space between the scint case tops
  constexpr auto kENCL_TopEdge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kENCL_TopEdge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kENCL_TopEdge_Hole_Zsize = 2*kENCL_TopEdge_Zsize;

  //--------------------------------------------------------------
  // MIB Plate
  //--------------------------------------------------------------
  constexpr auto kMIBP_Xsize = kScint_Xpitch;
  constexpr auto kMIBP_Ysize = kScint_Ypitch;
  constexpr auto kMIBP_Zsize = 10.5*mm;

  // holes
  constexpr auto kMIBP_Hole_Xsize = kScint_Case_Bot_Xsize;
  constexpr auto kMIBP_Hole_Ysize = kScint_Case_Bot_Ysize;
  constexpr auto kMIBP_Hole_Zsize = 2*kMIBP_Zsize;

  constexpr auto kMIBP_Zoffset = 1.5*mm;

  //--------------------------------------------------------------
  // MIB Plate Edge
  //--------------------------------------------------------------
  constexpr auto kMIBP_Edge_Xsize = 255.6*mm;//kENCL_Bot_Xsize;
  constexpr auto kMIBP_Edge_Ysize = 255.6*mm;//kENCL_Bot_Ysize;
  constexpr auto kMIBP_Edge_Zsize = 6.35*mm;

  constexpr auto kMIBP_Edge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kMIBP_Edge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kMIBP_Edge_Hole_Zsize = 2*kMIBP_Edge_Zsize;

  //--------------------------------------------------------------
  // Bus Board Mounts
  //--------------------------------------------------------------
  constexpr auto kMIBP_Mount_Xsize = 255.6*mm;//kENCL_Bot_Xsize;
  constexpr auto kMIBP_Mount_Ysize = 255.6*mm;//kENCL_Bot_Ysize;
  constexpr auto kMIBP_Mount_Zsize = 4.4958*mm;

  constexpr auto kMIBP_Mount_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kMIBP_Mount_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kMIBP_Mount_Hole_Zsize = 2*kMIBP_Mount_Zsize;


  //--------------------------------------------------------------
  // DETECTOR Column
  //--------------------------------------------------------------
  constexpr auto kDetColumn_Xsize = kScint_Xpitch;
  constexpr auto kDetColumn_Ysize = kScint_Ypitch;
  constexpr auto kDetColumn_Zsize = 
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kScint_Case_Top_Zsize;

  //--------------------------------------------------------------
  // Detector Shield Sides
  //--------------------------------------------------------------
  constexpr auto kSHAL_Thickness = 8.89*mm;
  constexpr auto kSHLD_Side2_Thickness =  kSHAL_Thickness;//kSHCU_Thickness + kSHSN_Thickness + kSHPB_Thickness + kENCL_Thickness;


  //--------------------------------------------------------------
  // Enclosure (SHAL) Side - Aluminum
  //--------------------------------------------------------------
  constexpr auto kSHAL_Side1_Xsize = kSHAL_Thickness;
  constexpr auto kSHAL_Side1_Ysize = kENCL_TopEdge_Ysize;
  constexpr auto kSHAL_Side1_Zsize = 101.65*mm - kENCL_Top_Zsize;


  constexpr auto kSHAL_Side2_Xsize = kENCL_TopEdge_Ysize - 2*kSHAL_Thickness;
  constexpr auto kSHAL_Side2_Ysize = kSHAL_Thickness;
  constexpr auto kSHAL_Side2_Zsize = kSHAL_Side1_Zsize;

  //--------------------------------------------------------------
  // Enclosure (SHCU) Side - Copper
  //--------------------------------------------------------------
  constexpr auto kSHCU_Side1_Xsize = kSHCU_Thickness;
  constexpr auto kSHCU_Side1_Ysize = kENCL_TopEdge_Ysize;
  constexpr auto kSHCU_Side1_Zsize = 101.65*mm;


  constexpr auto kSHCU_Side2_Xsize = kENCL_TopEdge_Ysize + 2*kSHLD_Side2_Thickness;
  constexpr auto kSHCU_Side2_Ysize = kSHCU_Thickness;
  constexpr auto kSHCU_Side2_Zsize = kSHCU_Side1_Zsize;


  //--------------------------------------------------------------
  // Enclosure (SHSN) Side - Tin
  //--------------------------------------------------------------
  constexpr auto kSHSN_Side1_Xsize = kSHSN_Thickness;
  constexpr auto kSHSN_Side1_Ysize = kENCL_TopEdge_Ysize;
  constexpr auto kSHSN_Side1_Zsize = 101.65*mm;


  constexpr auto kSHSN_Side2_Xsize = kENCL_TopEdge_Ysize + 2*kSHLD_Side2_Thickness;
  constexpr auto kSHSN_Side2_Ysize = kSHSN_Thickness;
  constexpr auto kSHSN_Side2_Zsize = kSHSN_Side1_Zsize;


  //--------------------------------------------------------------
  // Enclosure (SHPB) Side - Lead
  //--------------------------------------------------------------
  constexpr auto kSHPB_Side1_Xsize = kSHPB_Thickness;
  constexpr auto kSHPB_Side1_Ysize = kENCL_TopEdge_Ysize;
  constexpr auto kSHPB_Side1_Zsize = 101.65*mm;


  constexpr auto kSHPB_Side2_Xsize = kENCL_TopEdge_Ysize + 2*kSHLD_Side2_Thickness;
  constexpr auto kSHPB_Side2_Ysize = kSHPB_Thickness;
  constexpr auto kSHPB_Side2_Zsize = kSHPB_Side1_Zsize;

  //--------------------------------------------------------------
  // Enclosure (ENCL) Side
  //--------------------------------------------------------------
  constexpr auto kENCL_Side1_Xsize = kENCL_Thickness;
  constexpr auto kENCL_Side1_Ysize = kENCL_TopEdge_Ysize;
  constexpr auto kENCL_Side1_Zsize = 101.65*mm;


  constexpr auto kENCL_Side2_Xsize = kENCL_TopEdge_Ysize + 2*kSHLD_Side2_Thickness;
  constexpr auto kENCL_Side2_Ysize = kENCL_Thickness;
  constexpr auto kENCL_Side2_Zsize = kENCL_Side1_Zsize;

 //--------------------------------------------------------------
  // Power Container - Electronics
  //--------------------------------------------------------------

  constexpr auto kPower_ENCL_Thickness = 6.32*mm;

  constexpr auto kPower_ENCL_Xsize = 255.59*mm;
  constexpr auto kPower_ENCL_Ysize = 255.59*mm;
  constexpr auto kPower_ENCL_Zsize = 54.00*mm;

  constexpr auto kPower_ENCL_Hole_Xsize = kPower_ENCL_Xsize - 2*kPower_ENCL_Thickness;
  constexpr auto kPower_ENCL_Hole_Ysize = kPower_ENCL_Xsize - 2*kPower_ENCL_Thickness;
  constexpr auto kPower_ENCL_Hole_Zsize = kPower_ENCL_Zsize + 2*kPower_ENCL_Thickness;


  //--------------------------------------------------------------
  // PAYLOAD MODULE
  //--------------------------------------------------------------
  constexpr auto kPayload_Module_Xsize = 255.6*mm;
  constexpr auto kPayload_Module_Ysize = 255.6*mm;
  constexpr auto kPayload_Module_Zsize = 344.1*mm;


  //--------------------------------------------------------------
  // DETECTOR MODULE
  //--------------------------------------------------------------
  constexpr auto kDet_Module_Xsize = 255.6*mm;
  constexpr auto kDet_Module_Ysize = 255.6*mm;
  constexpr auto kDet_Module_Zsize = 112.3*mm;
  			  //     kSHPB_Bot_Zsize +
				  // kSHSN_Bot_Zsize +
          //         kENCL_Bot_Zsize +
          //         kAPB_Zoffset +
          //         kAPB_Zsize +
          //         kAPB_MIB_Zoffset +
          //         kMIB_Zsize +
          //         kDetColumn_Zsize;


  //--------------------------------------------------------------
  // DAQ MODULE (EBOX1) : (Connectors, Asics, FPGA, InnerShield)
  //--------------------------------------------------------------
  constexpr auto kDAQ_Module_Xsize = 255.6*mm;
  constexpr auto kDAQ_Module_Ysize = 255.6*mm;
  constexpr auto kDAQ_Module_Zsize = 177.8*mm;


  //--------------------------------------------------------------
  // POWER MODULE (EBOX2) : (Computer, Power Supplies, etc.)
  //--------------------------------------------------------------
  constexpr auto kPower_Module_Xsize = 255.6*mm;
  constexpr auto kPower_Module_Ysize = 255.6*mm;
  constexpr auto kPower_Module_Zsize = 54.0*mm;



  //--------------------------------------------------------------
  // WORLD
  //--------------------------------------------------------------
  constexpr auto kWorld_Xsize = 5.0*m;
  constexpr auto kWorld_Ysize = 5.0*m;
  constexpr auto kWorld_Zsize = 5.0*m;


}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
