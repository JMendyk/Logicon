//
// Created by rufus on 11.12.17.
//

#include "data.h"

namespace Logicon{
	void Data::from_json(const json& j, Gate& g){
        	//Gate
        	g.id = j.at("id").get<ID>();
        	g.gateType = j.at("type").get<GATE_TYPE>();
        	int n = g.getInputsCount();
        	for(int i=0;i<n;i++) g.setInputState(j["inputs"][i]["state"]);
        	int m = g.getOutputsCount();
        	for(int i=0;i<m;i++) g.setOutputState(j["outputs"][i]["state"]);
        	//Delay
        	Tick Jdelay = j.at("delay").get<Tick>();
        	std::list<State> Jsignals = j.at("signals").get< std::list<State> >();
        	g.setDelay( Jdelay );
        	g.setDelayList( Jsignals );
        	//Switch and input
        	bool Jclicked = j.at("STATE_FLAG").get< bool >();
        	g.setClicked(Jclicked);
        	//Clock
        	Tick JonPeriod = j.at("onPeriod").get < Tick >();
        	Tick JoffPeriod = j.at("offPeriod").get < Tick >();
        	Tick Jphase = = j.at("phase").get < Tick >();
        	g.changeSettings(JonPeriod, JoffPeriod, Jphase);
		}
		
        void Data::to_json(const Gate& g, json& j){
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
        	//Switch and input
        	j ["STATE_FLAG"] = g.isClicked();
        	//Clock
        	j ["onPeriod"] = g.getOnPeriod();
        	j ["offPeriod"] = g.getOffPeriod();
        	j ["phase"] = g.getPhase();
		}
} // namespace Logicon
