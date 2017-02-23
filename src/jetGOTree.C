//include dependencies
#include "include/jetGOTree.h"
#include "include/checkMakeDir.h"

//ROOT dependencies
#include "TMath.h"
#include "TDatime.h"
#include "TLorentzVector.h"

jetGOTree::jetGOTree()
{
  return;
}


bool jetGOTree::initWriteJetGOTree(const std::string fileName, const std::string branchName)
{
  std::string constructedPath = getFileName(fileName);

  treeFile_p = new TFile(constructedPath.c_str(), "RECREATE");
  fileIsNewed = true;

  return initWriteJetGOTree(branchName);
}


bool jetGOTree::initWriteJetGOTree(TFile* inTreeFile_p, const std::string branchName = "jt")
{
  treeFile_p = inTreeFile_p;
  return initWriteJetGOTree(branchName);
}


bool jetGOTree::initWriteJetGOTree(const std::string branchName = "jt")
{
  if(isInitWrite || isInitRead) return false;
  isInitWrite = true;

  treeFile_p->cd();
  jetGOTree_p = new TTree("jetGOTree", "jetGOTree");

  std::string capBranchName = branchName.substr(0, 1);
  std::string lowerAlpha = "abcdefghijklmnopqrstuvwxyz";
  std::string upperAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  
  if(lowerAlpha.find(capBranchName) != std::string::npos){
    capBranchName = upperAlpha.substr(lowerAlpha.find(capBranchName), 1);
  }
  capBranchName = capBranchName + branchName.substr(1, branchName.size()-1);

  std::string nJtStr1 = "n" + capBranchName;
  std::string nJtStr2 = nJtStr1 + "/I";

  std::string jtPtStr1 = branchName + "Pt";
  std::string jtPtStr2 = jtPtStr1 + "[" + nJtStr1 + "]/F";

  std::string jtPhiStr1 = branchName + "Phi";
  std::string jtPhiStr2 = jtPhiStr1 + "[" + nJtStr1 + "]/F";

  std::string jtEtaStr1 = branchName + "Eta";
  std::string jtEtaStr2 = jtEtaStr1 + "[" + nJtStr1 + "]/F";

  jetGOTree_p->Branch(nJtStr1.c_str(), &nJt_, nJtStr2.c_str());
  jetGOTree_p->Branch(jtPtStr1.c_str(), jtPt_, jtPtStr2.c_str());
  jetGOTree_p->Branch(jtPhiStr1.c_str(), jtPhi_, jtPhiStr2.c_str());
  jetGOTree_p->Branch(jtEtaStr1.c_str(), jtEta_, jtEtaStr2.c_str());

  return true;
}


std::string jetGOTree::getFileName(std::string inFileName)
{  
  std::string tempFileName = inFileName;
  std::string constructedPath = "";

  while(tempFileName.find("/") != std::string::npos){
    constructedPath = constructedPath + tempFileName.substr(0, tempFileName.find("/")+1);
    tempFileName.replace(0, tempFileName.find("/")+1, "");

    if(!checkDir(constructedPath)){
      std::cout << "Path component \'" << constructedPath << "\' of full path \'" << inFileName << "\' does not exist, creating..." << std::endl;
      checkMakeDir(constructedPath);
    }
  }

  if(tempFileName.find(".root") != std::string::npos) tempFileName.replace(tempFileName.find(".root"), 5, "");

  TDatime* date = new TDatime();
  tempFileName = tempFileName + "_" + std::to_string(date->GetDate()) + ".root";

  if(constructedPath.size() != 0) constructedPath = constructedPath + "/";
  constructedPath = constructedPath + tempFileName;

  unsigned int fileIter = 1;
  while(checkFile(constructedPath)){
    std::string newFileExt = "_" + std::to_string(fileIter) + ".root";

    if(constructedPath.substr(constructedPath.size() - 7, 1).find("_") != std::string::npos) constructedPath.replace(constructedPath.find(".root")-2, 7, "");
    else constructedPath.replace(constructedPath.find(".root"), 5, "");

    constructedPath = constructedPath  + newFileExt;
    fileIter++;
  }

  return constructedPath;
}

bool jetGOTree::fillJetGOTree(std::vector<fastjet::PseudoJet> inJet)
{
  if(!isInitWrite) return false;

  treeFile_p->cd();
  nJt_ = 0;

  for(unsigned int iter = 0; iter < TMath::Min((unsigned int)inJet.size(), (unsigned int)nMaxJet_); iter++){
    jtPt_[nJt_] = inJet.at(iter).pt();
    jtPhi_[nJt_] = inJet.at(iter).phi_std();
    jtEta_[nJt_] = inJet.at(iter).eta();

    nJt_++;
  }

  jetGOTree_p->Fill();

  return true;
}

bool jetGOTree::writeJetGOTree(std::string newName)
{
  if(!isInitWrite) return false;

  treeFile_p->cd();
  jetGOTree_p->Write(newName.c_str(), TObject::kOverwrite);

  return true;
}


bool jetGOTree::initReadJetGOTree(TFile* inTreeFile_p, const std::string treeName, const std::string branchName)
{
  treeFile_p = inTreeFile_p;
  initReadJetGOTree(treeName, branchName);
  return true;
}

bool jetGOTree::initReadJetGOTree(const std::string treeName, const std::string branchName)
{
  jetGOTree_p = (TTree*)treeFile_p->Get(treeName.c_str());  
  nEntries = jetGOTree_p->GetEntries();

  std::string capBranchName = branchName.substr(0, 1);
  std::string lowerAlpha = "abcdefghijklmnopqrstuvwxyz";
  std::string upperAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  if(lowerAlpha.find(capBranchName) != std::string::npos){
    capBranchName = upperAlpha.substr(lowerAlpha.find(capBranchName), 1);
  }
  capBranchName = capBranchName + branchName.substr(1, branchName.size()-1);

  std::string nJtStr1 = "n" + capBranchName;
  std::string jtPtStr1 = branchName + "Pt";
  std::string jtPhiStr1 = branchName + "Phi";
  std::string jtEtaStr1 = branchName + "Eta";

  jetGOTree_p->SetBranchStatus("*", 0);
  jetGOTree_p->SetBranchStatus(nJtStr1.c_str(), 1);
  jetGOTree_p->SetBranchStatus(jtPtStr1.c_str(), 1);
  jetGOTree_p->SetBranchStatus(jtPhiStr1.c_str(), 1);
  jetGOTree_p->SetBranchStatus(jtEtaStr1.c_str(), 1);

  jetGOTree_p->SetBranchAddress(nJtStr1.c_str(), &nJt_);
  jetGOTree_p->SetBranchAddress(jtPtStr1.c_str(), jtPt_);
  jetGOTree_p->SetBranchAddress(jtPhiStr1.c_str(), jtPhi_);
  jetGOTree_p->SetBranchAddress(jtEtaStr1.c_str(), jtEta_);

  return true;
}


bool jetGOTree::getNextEvent()
{
  if(currentEntry >= nEntries) return false;

  jetGOTree_p->GetEntry(currentEntry);  

  currentEntry++;
  return true;
}


std::vector<fastjet::PseudoJet> jetGOTree::getEventJet()
{
  std::vector<fastjet::PseudoJet> outJet;

  for(unsigned int iter = 0; iter < (unsigned int)nJt_; iter++){
    TLorentzVector lorJet;
    lorJet.SetPtEtaPhiM(jtPt_[iter], jtEta_[iter], jtPhi_[iter], 0);

    fastjet::PseudoJet jet(lorJet.Px(), lorJet.Py(), lorJet.Pz(), lorJet.E());
    outJet.push_back(jet);
  }

  return outJet;
}


bool jetGOTree::cleanJetGOTree()
{
  if(!isInitWrite && !isInitRead) return false;

  if(isInitWrite){
    isInitWrite = false;
    
    treeFile_p->cd();
    delete jetGOTree_p;
    
    if(fileIsNewed){
      treeFile_p->Close();
      delete treeFile_p;
      fileIsNewed = false;
    }
  }
  else if(isInitRead){
    nEntries = -1;
    currentEntry = 0;
  }

  return true;
}
