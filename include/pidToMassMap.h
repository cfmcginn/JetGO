#ifndef PIDTOMASSMAP_H
#define PIDTOMASSMAP_H

#include <map>
#include <cmath>

class pidToMassMap{
 private:
  std::map<int, double> pdgIDMassMap =
    {
      //leptons
      {11, .000510998928},
      {12, 0.},
      {13, .1056583715},
      {14, 0.},
      {15, 1776.82},
      {16, 0.},
      //gauge bosons
      {22, 0.},
      {23, 91.1876},
      {24, 80.385},
      //mesons
      {111, .13957018},
      {211, .1349766},
      {221, .547862},
      {311, .497614},
      {321, .493677},
      //baryons
      {2112, .939565379},
      {2212, .938272046},
    };
 public:
  pidToMassMap(){return;}

  double getMassFromPID(int pid){
    auto search = pdgIDMassMap.find(std::abs(pid));
    if(search != pdgIDMassMap.end()) return search->second;
    else return -1.;
  }

};

#endif
