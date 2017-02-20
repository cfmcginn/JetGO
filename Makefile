JETGOPATH=$(PWD)

#std-c++11
CXX = g++
CXXFLAGS = -Wall -O2 -Wextra -Wno-unused-local-typedefs  -Werror -Wno-deprecated-declarations -std=c++11
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

INCLUDE = -I /opt/local/include -I $(JETGOPATH) 
FASTJET = `/net/hisrv0001/home/cfmcginn/Packages/FastJet/fastjet-build/bin/fastjet-config --cxxflags --libs --plugins`
#ROOT = `root-config --cflags --glibs`
ROOT = -pthread -std=c++1y -m64 -I/Users/cfmcginn/Packages/ROOT6/root6-build/include -L/Users/cfmcginn/Packages/ROOT6/root6-build/lib -lGui -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lpthread -lm -ldl

MKDIR_BIN = mkdir -p $(JETGOPATH)/bin

all: mkdirBin jetGOReadHEPMC_TEST

mkdirBin:
	$(MKDIR_BIN)

jetGOReadHEPMC_TEST: src/jetGOReadHEPMC_TEST.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(FASTJET) $(ROOT) -o bin/jetGOReadHEPMC_TEST.exe src/jetGOReadHEPMC_TEST.C

clean:
	sh bashDir/clean.sh || true
	rmdir bin || true