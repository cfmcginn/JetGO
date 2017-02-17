//class header
#include "include/jetGOReadHEPMC.h"

//include cpp dependencies
#include <fstream>
#include <iostream>

//include dependencies
#include "include/checkMakeDir.h"


jetGOReadHEPMC::jetGOReadHEPMC(std::string inFileName)
{
  inFileName_ = inFileName;

  if(!checkFile(inFileName_)){
    std::cout << "Input \'" << inFileName_ << "\' is not valid. Return" << std::endl;
    return;
  }

  inFile_.open(inFileName_.c_str());

  return;
}


bool jetGOReadHEPMC::getNextEvent()
{
  outConstituent_.clear();
  bool newEvent = false;
  std::string tempStr;

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  while(std::getline(inFile_, tempStr)){
    std::string tempStr2 = tempStr;

    if(isParticleLine(tempStr)){
      newEvent = true;

      if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

      std::vector<std::string> tempStrVect;

      while(tempStr.size() != 0){
	if(tempStr.substr(0,1).find(" ") != std::string::npos) tempStr = tempStr.replace(0, 1, "");

	if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;
	
	unsigned int spacePos = 0;
	while(tempStr.substr(spacePos,1).find(" ") == std::string::npos){
	  spacePos++;
	  if(spacePos == tempStr.size()) break;
	}

	if(spacePos != 0) tempStrVect.push_back(tempStr.substr(0, spacePos));

	tempStr = tempStr.replace(0, spacePos+1, "");
      }

      if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << ", \'" << tempStr2 << "\'" << std::endl;
      
      //Fill out output constituents
      if(tempStrVect.at(1).find("1") != std::string::npos && tempStrVect.at(1).size() == 1) continue;
      if(tempStrVect.at(1).find("2") != std::string::npos && tempStrVect.at(1).size() == 1) continue;

      if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

      if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << ", constituent \'" << std::stof(tempStrVect.at(3)) << "\', \'" << std::stof(tempStrVect.at(4)) << "\', \'" << std::stof(tempStrVect.at(5)) << "\', \'" << std::stof(tempStrVect.at(6)) << std::endl;

      fastjet::PseudoJet constituent(std::stof(tempStrVect.at(3)), std::stof(tempStrVect.at(4)), std::stof(tempStrVect.at(5)), std::stof(tempStrVect.at(6)));

      if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;
      if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << ", constituent pt \'" << constituent.pt() << "\'" << std::endl;

      outConstituent_.push_back(constituent);
    }
    else if(newEvent) break;
  }

  if(globalDoDebug) std::cout << __FILE__ << ", " << __LINE__ << std::endl;

  return newEvent;
}


bool jetGOReadHEPMC::isCharLine(std::string line, std::string startChar)
{
  std::string startChar2 = startChar+" ";

  if(line.size() == 0) return false;
  if(line.substr(0, 1).find(startChar.c_str()) != std::string::npos){
    if(line.size() == 1) return true;
    else if(line.substr(0, 2).find(startChar2.c_str()) != std::string::npos) return true;
  }
  
  return false;
}

bool jetGOReadHEPMC::isEventLine(std::string line){return isCharLine(line, "E");}
bool jetGOReadHEPMC::isParticleLine(std::string line){return isCharLine(line, "P");}


