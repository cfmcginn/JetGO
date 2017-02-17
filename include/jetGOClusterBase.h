#ifndef JETGOCLUSTERBASE_H
#define JETGOCLUSTERBASE_H

//cpp dependencies
#include <vector>

//fastjet dependencies
#include "fastjet/ClusterSequence.hh"

//include dependencies
#include "include/globalDoDebug.h"
#include "include/jetGOBase.h"
#include "src/jetGOBase.C"

class jetGOClusterBase
{
 private:
  double constituentPtCut_ = 0.;
  double constituentEtaCutLow_ = -100.;
  double constituentEtaCutHi_ = 100.;

  fastjet::JetAlgorithm jetAlgo_ = fastjet::antikt_algorithm;
  double jetR_ = 0.4;

  double jetPtCut_ = 15.;
  double jetEtaCutLow_ = -100.;
  double jetEtaCutHi_ = 100.;

  bool clusteringSuccess_ = false;

  jetGOBase constituents_;
  jetGOBase jets_;

 public:
  jetGOClusterBase();

  void setConstituentPtCut(double ptCut){constituentPtCut_ = ptCut;}
  void setConstituentEtaCutLow(double etaCut){constituentEtaCutLow_ = etaCut;}
  void setConstituentEtaCutHi(double etaCut){constituentEtaCutHi_ = etaCut;}

  void setJetR(double jetR){jetR_ = jetR;}
  void setJetAlgo(fastjet::JetAlgorithm algo){jetAlgo_ = algo;}

  void setJetPtCut(double ptCut){jetPtCut_ = ptCut;}
  void setJetEtaCutLow(double etaCut){jetEtaCutLow_ = etaCut;}
  void setJetEtaCutHi(double etaCut){jetEtaCutHi_ = etaCut;}  

  void setConstituents(std::vector<fastjet::PseudoJet> inConstituent);

  bool runClustering();

  std::vector<fastjet::PseudoJet> getInitConstituents(){return constituents_.getUncutPseudoJet();}
  std::vector<fastjet::PseudoJet> getFinalConstituents(){return constituents_.getCutPseudoJet();}
  std::vector<fastjet::PseudoJet> getInitJets(){return jets_.getUncutPseudoJet();}
  std::vector<fastjet::PseudoJet> getFinalJets(){return jets_.getCutPseudoJet();}
};

#endif
