#include "include/globalDoDebug.h"
#include "include/jetGOClusterBase.h"

jetGOClusterBase::jetGOClusterBase()
{
  return;
}

bool jetGOClusterBase::runClustering()
{
  if(inConstituent_.size() == 0) return false;

  outConstituent_.clear();

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  for(unsigned int iter = 0; iter < inConstituent_.size(); iter++){
    if(inConstituent_.at(iter).pt() < constituentPtCut_) continue;
    if(inConstituent_.at(iter).eta() < constituentEtaCutLow_) continue;
    if(inConstituent_.at(iter).eta() > constituentEtaCutHi_) continue;

    outConstituent_.push_back(inConstituent_.at(iter));
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  if(outConstituent_.size() == 0) return false;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  fastjet::JetDefinition jetDef(jetAlgo_, jetR_);
  fastjet::ClusterSequence cs(outConstituent_, jetDef);

  outJet_ = fastjet::sorted_by_pt(cs.inclusive_jets());  

  unsigned int jetPos = 0;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  while(outJet_.size() > jetPos){
    bool eraseBool = false;
    if(outJet_.at(jetPos).pt() < jetPtCut_) eraseBool = true;
    else if(outJet_.at(jetPos).eta() < jetEtaCutLow_) eraseBool = true;
    else if(outJet_.at(jetPos).eta() > jetEtaCutHi_) eraseBool = true;

    if(eraseBool) outJet_.erase(outJet_.begin()+jetPos);
    else jetPos++;
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  return true;
}
