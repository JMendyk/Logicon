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
        public:
        	//get Gate from json
	        void from_json(const json& j, Gate& g)
			//get json from Gate
	        void to_json(const Gate& g, json& j)
        
    };
} // namespace Logicon

#endif //LOGICON_DATA_H
