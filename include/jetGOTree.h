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
  TTree* jetGOTree_p = 0;

  const static unsigned int nMaxJet_ = 500;
  Int_t nJt_;
  Float_t jtPt_[nMaxJet_];
  Float_t jtPhi_[nMaxJet_];
  Float_t jtEta_[nMaxJet_];

  bool isInit = false;

 public:
  jetGOTree();

  bool initJetGOTree(const std::string fileName);
  bool fillJetGOTree(std::vector<fastjet::PseudoJet> inJet);
  bool writeJetGOTree(std::string newName = "");
  bool cleanJetGOTree();
};

#endif
