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
