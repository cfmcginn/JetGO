//include dependencies
#include "include/jetGOTree.h"

//ROOT dependencies
#include "TMath.h"
#include "TDatime.h"

jetGOTree::jetGOTree()
{
  return;
}

bool jetGOTree::initJetGOTree(const std::string fileName)
{
  if(isInit) return false;
  isInit = true;

  std::string tempFileName = fileName;
  std::string constructedPath = "";

  while(tempFileName.find("/") != std::string::npos){
    constructedPath = constructedPath + tempFileName.substr(0, tempFileName.find("/")+1);
    tempFileName.replace(0, tempFileName.find("/")+1, "");

    if(!checkDir(constructedPath)){
      std::cout << "Path component \'" << constructedPath << "\' of full path \'" << fileName << "\' does not exist, creating..." << std::endl;

      checkMakeDir(constructedPath);
    }
  }
  
  if(tempFileName.find(".root") != std::string::npos) tempFileName.replace(tempFileName.find(".root"), 5, "");

  TDatime* date = new TDatime();
  tempFileName = tempFileName + std::to_string(date->GetDate()) + ".root";

  constructedPath = constructedPath + "/" + tempFileName;

  treeFile_p = new TFile(constructedPath.c_str(), "RECREATE");
  jetGOTree_p = new TTree("jetGOTree", "jetGOTree");

  jetGOTree_p->Branch("nJt", &nJt_, "nJt/I");
  jetGOTree_p->Branch("jtPt", jtPt_, "jtPt[nJt]/F");
  jetGOTree_p->Branch("jtPhi", jtPhi_, "jtPhi[nJt]/F");
  jetGOTree_p->Branch("jtEta", jtEta_, "jtEta[nJt]/F");

  return true;
}


bool jetGOTree::fillJetGOTree(std::vector<fastjet::PseudoJet> inJet)
{
  if(!isInit) return false;

  treeFile_p->cd();
  nJt_ = 0;

  for(unsigned int iter = 0; iter < TMath::Miniumum(inJet.size(), nMaxJet_); iter++){
    jtPt_[nJt_] = inJet.at(iter).pt();
    jtPhi_[nJt_] = inJet.at(iter).phi();
    jtEta_[nJt_] = inJet.at(iter).eta();

    nJt_++;
  }

  return true;
}

bool jetGOTree::writeJetGOTree()
{
  if(!isInit) return false;

  treeFile_p->cd();
  jetGOTree_p->Write("", TObject::kOverwrite);

  return true;
}

bool jetGOTree::cleanJetGOTree()
{
  if(!isInit) return false;
  isInit = false;

  treeFile_p->cd();
  delete jetGOTree_p;

  treeFile_p->Close();
  delete treeFile_p;

  return false;
}
