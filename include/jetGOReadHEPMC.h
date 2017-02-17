#ifndef JETGOREADHEPMC_H
#define JETGOREADHEPMC_H

//cpp dependencies
#include <vector>
#include <fstream>
#include <string>
#include <map>

//fastjet dependencies
#include "fastjet/ClusterSequence.hh"

class jetGOReadHEPMC{
 private:
  //PID-Mass map in GeV, in order of increasing PID, mass taken from PDG 2014
  std::map<int, double> pdgIDMassMap = 
    {
      //leptons
      {11, .000510998928},
      {12, 0.},
      {13, .1056583715},
      {14, 0.},
      {15, 1776.82},
      {16, 0.},
      
      //gauge bosons
      {22, 0.},
      {23, 91.1876},
      {24, 80.385},
      
      //mesons
      {111, .13957018},
      {211, .1349766},
      {221, .547862},
      {311, .497614},
      {321, .493677},
      
      //baryons
      {2112, .939565379},
      {2212, .938272046},
    };


  std::string inFileName_;
  std::ifstream inFile_;
  bool endOfFile_ = false;
  std::vector<fastjet::PseudoJet> outConstituent_;

  bool isCharLine(std::string line, std::string startChar);
  bool isEventLine(std::string line);
  bool isParticleLine(std::string line);
 public:
  jetGOReadHEPMC(std::string inFileName);
  bool getNextEvent();
  std::vector<fastjet::PseudoJet> returnConstituents(){return outConstituent_;}
};

#endif
