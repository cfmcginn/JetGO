#include "include/globalDoDebug.h"
#include "include/jetGOClusterBase.h"


jetGOClusterBase::jetGOClusterBase()
{
  return;
}

void jetGOClusterBase::setConstituents(std::vector<fastjet::PseudoJet> inConstituent)
{
  constituents_.setPseudoJets(inConstituent);

  return;
}

bool jetGOClusterBase::runClustering()
{
  constituents_.setPtCut(constituentPtCut_);
  constituents_.setEtaCutLow(constituentEtaCutLow_);
  constituents_.setEtaCutHi(constituentEtaCutHi_);

  if(!constituents_.cutPseudoJets()) return false;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  fastjet::JetDefinition jetDef(jetAlgo_, jetR_);
  fastjet::ClusterSequence cs(constituents_.getCutPseudoJet(), jetDef);

  jets_.setPtCut(jetPtCut_);
  jets_.setEtaCutLow(jetEtaCutLow_);
  jets_.setEtaCutHi(jetEtaCutHi_);
  jets_.setPseudoJets(fastjet::sorted_by_pt(cs.inclusive_jets()));
  if(!jets_.cutPseudoJets()) return false;
  
  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  return true;
}
