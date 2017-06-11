#include <RecoMuon/DetLayers/src/MuonGEMDetLayerGeometryBuilder.h>

#include <DataFormats/MuonDetId/interface/GEMDetId.h>
#include <Geometry/CommonDetUnit/interface/GeomDet.h>
#include <RecoMuon/DetLayers/interface/MuRingForwardDoubleLayer.h>
#include <RecoMuon/DetLayers/interface/MuRodBarrelLayer.h>
#include <RecoMuon/DetLayers/interface/MuDetRing.h>
#include <RecoMuon/DetLayers/interface/MuDetRod.h>

#include <Utilities/General/interface/precomputed_value_sort.h>
#include <Geometry/CommonDetUnit/interface/DetSorting.h>
#include "Utilities/BinningTools/interface/ClusterizingHistogram.h"

#include <FWCore/MessageLogger/interface/MessageLogger.h>

#include <iostream>

using namespace std;

MuonGEMDetLayerGeometryBuilder::~MuonGEMDetLayerGeometryBuilder() {
}

// Builds the forward (first) and backward (second) layers
// Builds etaPartitions (for rechits)
pair<vector<DetLayer*>, vector<DetLayer*> > 
MuonGEMDetLayerGeometryBuilder::buildEndcapLayers(const GEMGeometry& geo) {
  
  vector<DetLayer*> result[2];
	
  for (int endcap = -1; endcap<=1; endcap+=2) {
    int iendcap = (endcap==1) ? 0 : 1; // +1: forward, -1: backward
      
    for(int station = GEMDetId::minStationId; station <= GEMDetId::maxStationId; ++station) {      
	  
      for (int layer = GEMDetId::minLayerId; layer <= GEMDetId::maxLayerId; ++layer) {
	MuRingForwardDoubleLayer* ringLayer = buildLayer(endcap, station, layer, geo);          

	if (ringLayer) result[iendcap].push_back(ringLayer);
	
      }
    }
  }
  pair<vector<DetLayer*>, vector<DetLayer*> > res_pair(result[0], result[1]); 

  return res_pair;
}

MuRingForwardDoubleLayer* 
MuonGEMDetLayerGeometryBuilder::buildLayer(int endcap, int station, int layer, const GEMGeometry& geo) {

  const std::string metname = "Muon|RecoMuon|RecoMuonDetLayers|MuonGEMDetLayerGeometryBuilder";
  MuRingForwardDoubleLayer * result = 0;

  vector<const ForwardDetRing*> frontRings, backRings;

  for (int roll = GEMDetId::minRollId; roll <= GEMDetId::maxRollId; ++roll) {
    if (layer == 0 && roll > 0) continue;// no rolls at layer 0; superChamber
    if (layer > 0 && roll == 0) continue;// no need to make chambers
    vector<const GeomDet*> frontDets, backDets;
        
    for (int chamber = GEMDetId::minChamberId+1; chamber <= GEMDetId::maxChamberId; ++chamber ) {
      GEMDetId gemId(endcap, 1, station, layer, chamber, roll);

      const GeomDet* geomDet = geo.idToDet(gemId);
	
      if (geomDet !=0) {
	bool isInFront = isFront(gemId);
	if(isInFront)
	  {
	    frontDets.push_back(geomDet);
	  }
	else 
	  {
	    backDets.push_back(geomDet);
	  }
	LogTrace(metname) << "get GEM Endcap roll "
			  << gemId
			  << (isInFront ? "front" : "back ")
			  << " at R=" << geomDet->position().perp()
			  << ", phi=" << geomDet->position().phi()
			  << ", Z=" << geomDet->position().z();
      }
    }

    if (frontDets.size()!=0) {
      frontRings.push_back(makeDetRing(frontDets));
      LogTrace(metname) << "New front ring with " << frontDets.size()
			<< " chambers at z="<< frontRings.back()->position().z();
    }
    if (backDets.size()!=0) {
      backRings.push_back(makeDetRing(backDets));
      LogTrace(metname) << "New back ring with " << backDets.size()
			<< " chambers at z="<< backRings.back()->position().z();
    }
  }
  
  
  if(backRings.size()!=0 && frontRings.size()!=0) result = new MuRingForwardDoubleLayer(frontRings, backRings);
  else result = 0;
  if(result != 0){
    LogTrace(metname) << "New MuRingForwardLayer with " << frontRings.size()
		      << " and " << backRings.size()
		      << " rings, at Z " << result->position().z()
		      << " R1: " << result->specificSurface().innerRadius()
		      << " R2: " << result->specificSurface().outerRadius();
    std::cout << "New MuRingForwardLayer with " << frontRings.size()
	      << " and " << backRings.size()
	      << " rings, at Z " << result->position().z()
	      << " R1: " << result->specificSurface().innerRadius()
	      << " R2: " << result->specificSurface().outerRadius() <<std::endl;
  }
  return result;

}

bool MuonGEMDetLayerGeometryBuilder::isFront(const GEMDetId & gemId)
{

  bool result = false;
  int chamber = gemId.chamber();

  if(chamber%2 == 0) result = !result;

  return result;
}

MuDetRing * MuonGEMDetLayerGeometryBuilder::makeDetRing(vector<const GeomDet*> & geomDets)
{
  const std::string metname = "Muon|RecoMuon|RecoMuonDetLayers|MuonGEMDetLayerGeometryBuilder";

  precomputed_value_sort(geomDets.begin(), geomDets.end(), geomsort::DetPhi());
  MuDetRing * result = new MuDetRing(geomDets);
  LogTrace(metname) << "New MuDetRing with " << geomDets.size()
		    << " chambers at z="<< result->position().z()
		    << " R1: " << result->specificSurface().innerRadius()
		    << " R2: " << result->specificSurface().outerRadius();
  return result;
}
