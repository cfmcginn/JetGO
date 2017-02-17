#include "include/globalDoDebug.h"

#include "include/jetGOReadHEPMC.h"
#include "src/jetGOReadHEPMC.C"

#include "include/jetGOClusterBase.h"
#include "src/jetGOClusterBase.C"

#include "include/jetGOTree.h"
#include "src/jetGOTree.C"

//fastjet dependencies
#include "fastjet/PseudoJet.hh"

int jetGOReadHEPMC_TEST(const std::string testFile, std::string treeFileName = "testTree")
{
  unsigned int nEvt = 0;
  jetGOReadHEPMC test(testFile);

  jetGOTree outTree;
  outTree.initJetGOTree(treeFileName);

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  while(test.getNextEvent()){
    std::vector<fastjet::PseudoJet> eventConstituents = test.returnConstituents();

    jetGOClusterBase clusterJet;
    clusterJet.setConstituents(eventConstituents);

    if(!clusterJet.runClustering()){
      std::cout << "Jet clustering failed. return 1" << std::endl;
      return 1;
    }

    std::vector<fastjet::PseudoJet> eventJets = clusterJet.getFinalJets();
    outTree.fillJetGOTree(eventJets);

    if(eventJets.size() != 0) std::cout << "Leading jet pt: " << eventJets.at(0).pt() << std::endl;

    nEvt++;
  }

  outTree.writeJetGOTree();
  outTree.cleanJetGOTree();

  return 0;
}

int main(int argc, char *argv[])
{
  if(argc != 2 && argc != 3){
    std::cout << "Usage ./bin/jetGOReadHEPMC_TEST.exe <inHEPFile> <outTreeFile opt>" << std::endl;
    std::cout << "Number of args given (need 2-3): " << argc << std::endl;
    for(int iter = 0; iter < argc; iter++){
      std::cout << "  argv[" << iter << "]: " << argv[iter] << std::endl;
    }
    return -1;
  }

  int retVal = -1;

  if(argc == 2) jetGOReadHEPMC_TEST(argv[1]);
  else if(argc == 3) jetGOReadHEPMC_TEST(argv[1], argv[2]);

  return retVal;
}
