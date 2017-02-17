JETGOPATH=$(PWD)

CXX = g++
CXXFLAGS = -Wall -O2 -Wextra -Wno-unused-local-typedefs -std=c++11 -Werror -Wno-deprecated-declarations
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

INCLUDE = -I /opt/local/include -I $(JETGOPATH) 
FASTJET = `/Users/cfmcginn/Packages/FastJet/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins`
ROOT = `root-config --cflags --glibs`

MKDIR_BIN = mkdir -p $(JETGOPATH)/bin

all: mkdirBin jetGOReadHEPMC_TEST

mkdirBin:
	$(MKDIR_BIN)

jetGOReadHEPMC_TEST: src/jetGOReadHEPMC_TEST.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(FASTJET) $(ROOT) -o bin/jetGOReadHEPMC_TEST.exe src/jetGOReadHEPMC_TEST.C

clean:
	sh bashDir/clean.sh || true
	rmdir bin || true