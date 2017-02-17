#include "include/jetGOBase.h"

jetGOBase::jetGOBase(){return;}

jetGOBase::jetGOBase(std::vector<fastjet::PseudoJet> inJet)
{
  setPseudoJets(inJet);
  return;
}

void jetGOBase::setPtCut(double ptCut)
{
  ptCut_ = ptCut;
  cutsApplied = false;
  return;
}

void jetGOBase::setEtaCutLow(double etaCut)
{
  etaCutLow_ = etaCut;
  cutsApplied = false;
  return;
}

void jetGOBase::setEtaCutHi(double etaCut)
{
  etaCutHi_ = etaCut;
  cutsApplied = false;
  return;
}

void jetGOBase::setPseudoJets(std::vector<fastjet::PseudoJet> inJet)
{
  uncutPseudoJet_ = inJet;
  cutPseudoJet_.clear();
  return;
}

bool jetGOBase::cutPseudoJets()
{
  if(uncutPseudoJet_.size() == 0) return false;

  cutPseudoJet_.clear();

  for(unsigned iter = 0; iter < uncutPseudoJet_.size(); iter++){
    if(uncutPseudoJet_.at(iter).pt() < ptCut_) continue;
    if(uncutPseudoJet_.at(iter).eta() < etaCutLow_) continue;
    if(uncutPseudoJet_.at(iter).eta() > etaCutHi_) continue;

    cutPseudoJet_.push_back(uncutPseudoJet_.at(iter));
  }

  cutsApplied = true;

  return true;
}

std::vector<fastjet::PseudoJet> jetGOBase::getCutPseudoJet()
{
  if(!cutsApplied) cutPseudoJets();

  return cutPseudoJet_;
}
