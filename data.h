//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_DATA_H
#define LOGICON_DATA_H

namespace Logicon {
    /**
     * @brief Representing data in JSON format.
     *
     * Class behaves like a map of various types, converts passed values to JSON objects and vice versa.
     * Allows to store values such as: labels, image paths, descriptions, positions of buttons, data about GBlocks etc.
     */
    class Data {
        
        void from_json(const json& j, Gate& g){
        	//Gate
        	g.id = j.at("id").get<ID>();
        	g.gateType = j.at("type").get<GATE_TYPE>();
        	int n = g.getInputsCount();
        	for(int i=0;i<n;i++) g.setInputState(j["inputs"][i]["state"]);
        	int m = g.getOutputsCount();
        	for(int i=0;i<m;i++) g.setOutputState(j["outputs"][i]["state"]);
        	//Delay
        	
		}
		
        void to_json(const Gate& g, json& j){
        	//Gate
        	j ["id"] = g.id
			j ["type"] = g.gateType;
        	int n = g.getInputsCount();
        	for(int i=0;i<n;i++) j["inputs"][i]["state"] = g.getInputState(i);
        	int m = g.getOutputsCount();
        	for(int i=0;i<m;i++) j["outputs"][i]["state"] = g.getOutputState(i);
        	//Delay
        	j ["delay"] = g.getDelay();
        	j ["signals"] = g.getDelayList();
		}
        
    };
} // namespace Logicon

#endif //LOGICON_DATA_H
