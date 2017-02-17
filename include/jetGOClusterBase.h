#ifndef JETGOCLUSTERBASE_H
#define JETGOCLUSTERBASE_H

//cpp dependencies
#include <vector>

//fastjet dependencies
#include "fastjet/ClusterSequence.hh"

//include dependencies

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

  std::vector<fastjet::PseudoJet> inConstituent_;
  std::vector<fastjet::PseudoJet> outConstituent_;
  std::vector<fastjet::PseudoJet> outJet_;
 public:
  jetGOClusterBase();

  void setConstituentPtCut(double ptCut){constituentPtCut_ = ptCut;}
  void setConstituentEtaCutLow(double etaCut){constituentEtaCutLow_ = etaCut;}
  void setConstituentEtaCutHi(double etaCut){constituentEtaCutHi_ = etaCut;}

  void setJetR(double jetR){jetR_ = jetR;}
  void setJetPtCut(double ptCut){jetPtCut_ = ptCut;}
  void setJetEtaCutLow(double etaCut){jetEtaCutLow_ = etaCut;}
  void setJetEtaCutHi(double etaCut){jetEtaCutHi_ = etaCut;}  

  void setConstituents(std::vector<fastjet::PseudoJet> inConstituent){inConstituent_ = inConstituent;}

  bool runClustering();

  std::vector<fastjet::PseudoJet> getInitConstituents(){return inConstituent_;}
  std::vector<fastjet::PseudoJet> getFinalConstituents(){return outConstituent_;}
  std::vector<fastjet::PseudoJet> getFinalJets(){return outJet_;}
};

#endif
