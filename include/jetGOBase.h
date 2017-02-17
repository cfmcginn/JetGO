#ifndef JETGOBASE_H
#define JETGOBASE_H

//cpp dependencies
#include <vector>

//fastjet dependencies
#include "fastjet/PseudoJet.hh"

//include dependencies
#include "include/globalDoDebug.h"

class jetGOBase
{
 private:
  double ptCut_ = 0.;
  double etaCutLow_ = -100.;
  double etaCutHi_ = 100.;

  bool cutsApplied = false;

  std::vector<fastjet::PseudoJet> uncutPseudoJet_;
  std::vector<fastjet::PseudoJet> cutPseudoJet_;
 public:
  jetGOBase();
  jetGOBase(std::vector<fastjet::PseudoJet> inJet);

  void setPtCut(double ptCut);
  void setEtaCutLow(double etaCut);
  void setEtaCutHi(double etaCut);

  bool cutPseudoJets();
  void setPseudoJets(std::vector<fastjet::PseudoJet> inJet);

  std::vector<fastjet::PseudoJet> getUncutPseudoJet(){return uncutPseudoJet_;}
  std::vector<fastjet::PseudoJet> getCutPseudoJet();
};

#endif
