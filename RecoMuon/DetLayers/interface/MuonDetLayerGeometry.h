#ifndef DetLayers_MuonDetLayerGeometry_h
#define DetLayers_MuonDetLayerGeometry_h

/** \class MuonDetLayerGeometry
 *
 *  Provide access to the DetLayers of muon detectors.
 *
 *  \author N. Amapane - CERN
 *  
 *  \modified by R. Radogna & C. Calabria & A. Sharma
 *  \modified by D. Nash
 */

#include "DataFormats/DetId/interface/DetId.h"
#include "TrackingTools/DetLayers/interface/DetLayerGeometry.h"
#include <vector>
#include <map>

class DetLayer;

class MuonDetLayerGeometry : public DetLayerGeometry{
 public:

  /// Constructor
  MuonDetLayerGeometry();

  friend class MuonDetLayerGeometryESProducer;  

  /// Destructor
  virtual ~MuonDetLayerGeometry();

  /// return the DT DetLayers (barrel), inside-out
  const std::vector<const DetLayer*>& allDTLayers() const;

  /// return the CSC DetLayers (endcap), -Z to +Z
  const std::vector<const DetLayer*>& allCSCLayers() const;

  /// return the forward (+Z) CSC DetLayers, inside-out
  const std::vector<const DetLayer*>& forwardCSCLayers() const;

  /// return the backward (-Z) CSC DetLayers, inside-out
  const std::vector<const DetLayer*>& backwardCSCLayers() const;

/////////////////////////////// GEMs

  /// return the GEM DetLayers (endcap), -Z to +Z
  const std::vector<const DetLayer*>& allGEMLayers() const;

  /// return the forward (+Z) GEM DetLayers, inside-out
  const std::vector<const DetLayer*>& forwardGEMLayers() const;

  /// return the backward (-Z) GEM DetLayers, inside-out
  const std::vector<const DetLayer*>& backwardGEMLayers() const;

  /// return the forward (+Z) GEM SuperChambers, inside-out
  const std::vector<const DetLayer*>& forwardGEMSuperChambers() const;

  /// return the backward (-Z) GEM SuperChambers, inside-out
  const std::vector<const DetLayer*>& backwardGEMSuperChambers() const;
//////////////////////////////


/////////////////////////////// ME0s

  /// return the ME0 DetLayers (endcap), -Z to +Z
  const std::vector<const DetLayer*>& allME0Layers() const;

  /// return the forward (+Z) ME0 DetLayers, inside-out
  const std::vector<const DetLayer*>& forwardME0Layers() const;

  /// return the backward (-Z) ME0 DetLayers, inside-out
  const std::vector<const DetLayer*>& backwardME0Layers() const;

//////////////////////////////

  /// return all RPC DetLayers, order: backward, barrel, forward
  const std::vector<const DetLayer*>& allRPCLayers() const;

  /// return the barrel RPC DetLayers, inside-out
  const std::vector<const DetLayer*>& barrelRPCLayers() const;

  /// return the endcap RPC DetLayers, -Z to +Z
  const std::vector<const DetLayer*>& endcapRPCLayers() const;

  /// return the forward (+Z) RPC DetLayers, inside-out
  const std::vector<const DetLayer*>& forwardRPCLayers() const;

  /// return the backward (-Z) RPC DetLayers, inside-out
  const std::vector<const DetLayer*>& backwardRPCLayers() const;

  /// return all layers (DT+CSC+RPC+GEM), order: backward, barrel, forward
  const std::vector<const DetLayer*>& allLayers() const;

  /// return all barrel DetLayers (DT+RPC), inside-out
  const std::vector<const DetLayer*>& allBarrelLayers() const;

  /// return all endcap DetLayers (CSC+RPC+GEM+ME0), -Z to +Z
  const std::vector<const DetLayer*>& allEndcapLayers() const;
 
  /// return all forward (+Z) layers (CSC+RPC+GEM+ME0), inside-out
  const std::vector<const DetLayer*>& allForwardLayers() const;

  /// return all backward (-Z) layers (CSC+RPC+GEM+ME0), inside-out
  const std::vector<const DetLayer*>& allBackwardLayers() const;
    
/////////////////////////////// GEMs

  /// return all endcap DetLayers (CSC+GEM), -Z to +Z
  const std::vector<const DetLayer*>& allEndcapCscGemLayers() const;

  /// return all endcap DetLayers (CSC+GEM), -Z to +Z
  const std::vector<const DetLayer*>& allCscGemForwardLayers() const;

  /// return all endcap DetLayers (CSC+GEM), -Z to +Z
  const std::vector<const DetLayer*>& allCscGemBackwardLayers() const;

//////////////////////////////


/////////////////////////////// ME0s

  /// return all endcap DetLayers (CSC+ME0), -Z to +Z
  const std::vector<const DetLayer*>& allEndcapCscME0Layers() const;

  /// return all endcap DetLayers (CSC+ME0), -Z to +Z
  const std::vector<const DetLayer*>& allCscME0ForwardLayers() const;

  /// return all endcap DetLayers (CSC+ME0), -Z to +Z
  const std::vector<const DetLayer*>& allCscME0BackwardLayers() const;

//////////////////////////////
  
  /// return the DetLayer which correspond to a certain DetId
  virtual const DetLayer* idToLayer(const DetId& detId) const override;

 private:
  /// Add CSC layers 
  /// csclayers.first=forward (+Z), csclayers.second=backward (-Z)
  /// both vectors are ASSUMED to be sorted inside-out
  void addCSCLayers(const std::pair<std::vector<DetLayer*>, std::vector<DetLayer*> >& csclayers);

  //. Add DT layers; dtlayers is ASSUMED to be sorted inside-out
  void addDTLayers(const std::vector<DetLayer*>& dtlayers);

  /// Add RPC layers
  /// endcapRPCLayers.first=forward (+Z), endcapRPCLayers.second=backward (-Z)
  /// All three vectors are ASSUMED to be sorted inside-out
  void addRPCLayers(const std::vector<DetLayer*>& barrelRPCLayers, const std::pair<std::vector<DetLayer*>, std::vector<DetLayer*> >& endcapRPCLayers);

/////////////////////////////// GEMs

  /// Add GEM layers 
  /// gemlayers.first=forward (+Z), gemlayers.second=backward (-Z)
  /// both vectors are ASSUMED to be sorted inside-out
  void addGEMLayers(const std::pair<std::vector<DetLayer*>, std::vector<DetLayer*> >& gemlayers);
//////////////////////////////


/////////////////////////////// ME0s

  /// Add ME0 layers 
  /// gemlayers.first=forward (+Z), gemlayers.second=backward (-Z)
  /// both vectors are ASSUMED to be sorted inside-out
  void addME0Layers(const std::pair<std::vector<DetLayer*>, std::vector<DetLayer*> >& gemlayers);

//////////////////////////////

  
  DetId makeDetLayerId(const DetLayer* detLayer) const;
  
  void sortLayers();

  std::vector<const DetLayer*> cscLayers_fw;
  std::vector<const DetLayer*> cscLayers_bk;
  std::vector<const DetLayer*> cscLayers_all;

/////////////////////////////// GEMs

  std::vector<const DetLayer*> gemLayers_fw;
  std::vector<const DetLayer*> gemLayers_bk;
  std::vector<const DetLayer*> gemLayers_all;
  std::vector<const DetLayer*> gemSuperChambers_fw;
  std::vector<const DetLayer*> gemSuperChambers_bk;

/////////////////////////////// ME0s

  std::vector<const DetLayer*> me0Layers_fw;
  std::vector<const DetLayer*> me0Layers_bk;
  std::vector<const DetLayer*> me0Layers_all;

//////////////////////////////
  //////////////////////////////
  std::vector<const DetLayer*> rpcLayers_all;
  std::vector<const DetLayer*> rpcLayers_endcap;
  std::vector<const DetLayer*> rpcLayers_fw;
  std::vector<const DetLayer*> rpcLayers_bk;
  std::vector<const DetLayer*> rpcLayers_barrel;
  std::vector<const DetLayer*> dtLayers;
  std::vector<const DetLayer*> allForward;
  std::vector<const DetLayer*> allBackward;
  std::vector<const DetLayer*> allEndcap;
  std::vector<const DetLayer*> allBarrel;
  std::vector<const DetLayer*> allDetLayers;

/////////////////////////////// GEMs

  std::vector<const DetLayer*> allEndcapCscGem;
  std::vector<const DetLayer*> allCscGemForward;
  std::vector<const DetLayer*> allCscGemBackward;

//////////////////////////////
         

/////////////////////////////// ME0s

  std::vector<const DetLayer*> allEndcapCscME0;
  std::vector<const DetLayer*> allCscME0Forward;
  std::vector<const DetLayer*> allCscME0Backward;

//////////////////////////////
    

  std::map<DetId,const DetLayer*> detLayersMap;
};
#endif

