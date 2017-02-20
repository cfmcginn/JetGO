#ifndef JETGOTREE_H
#define JETGOTREE_H

//cpp dependencies
#include <iostream>
#include <vector>
#include <string>

//include dependencies
#include "include/globalDoDebug.h"
#include "include/checkMakeDir.h"

//fastjet dependencies
#include "fastjet/PseudoJet.hh"

//ROOT dependencies
#include "TFile.h"
#include "TTree.h"

class jetGOTree{
 private:
  TFile* treeFile_p = 0;
  bool fileIsNewed = false;
  TTree* jetGOTree_p = 0;

  const static unsigned int nMaxJet_ = 50000;
  Int_t nJt_;
  Float_t jtPt_[nMaxJet_];
  Float_t jtPhi_[nMaxJet_];
  Float_t jtEta_[nMaxJet_];

  bool isInitWrite = false;
  bool isInitRead = false;

  unsigned int nEntries = -1;
  unsigned int currentEntry = 0;

 public:
  jetGOTree();

  bool initWriteJetGOTree(const std::string fileName, const std::string branchName);
  bool initWriteJetGOTree(TFile* inTreeFile_p, const std::string branchName);
  bool initWriteJetGOTree(const std::string branchName);
  bool fillJetGOTree(std::vector<fastjet::PseudoJet> inJet);
  bool writeJetGOTree(std::string newName = "");

  bool initReadJetGOTree(TFile* inTreeFile_p, const std::string treeName, const std::string branchName);
  bool initReadJetGOTree(const std::string treeName, const std::string branchName);

  bool getNextEvent();
  std::vector<fastjet::PseudoJet> getEventJet();

  bool cleanJetGOTree();
};

#endif
