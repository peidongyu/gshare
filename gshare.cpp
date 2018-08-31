// Tyler Townsend
// 11/28/2017
// EEL 4768
//
// ===========================================
// Project 2: Globally Shared Branch Predictor
// ===========================================

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <ctype.h>

class gshare {
	private:
		// Gshare PC Bits (GPB) to index gshare table this corresponds to M
		// Global Register History Bits (RB) this corresponds to N
		// GHB maintains the global history buffer
		// The vector holds branch prediction table.
		int GPB;
		int RB;
		long long unsigned int GHB;
		std::vector<long long unsigned int> bpTable;

		int correct;
		int mispredict;

		// This function returns taken or not-taken based on 2-Bit prediction
		char state(int value) {
			if (value >=2)
				return 'T';
			return 'N';
		}

		// This function takes in a bitState (The prediction: 0 -3) and 
		// the outcome of the branch instruction then returns the updated
		// state based off the prediction.
		int increment(int bitState, char outcome) {		
			if (outcome == 'T') {
				if(bitState == 3)
					return bitState;
				return bitState + 1;
			} else {
				if(bitState == 0)
					return bitState;
				return bitState - 1;
			}
		}

		// Funtion that updates the global history buffer
		void updateGHB (char outcome) {
			// First remove last bit (LRU state)
			GHB =GHB/2;
			// Clear MSB by performing bitwise AND operation with 011...1
			// If the path is not taken, then all is done, otherwise append 1
			// with bitwise OR operation of 100...0 and GHB.
			GHB = GHB & ((long long unsigned int)pow(2,RB -1), -1);
			if (outcome == 'N')
				return;
			GHB = GHB | (long long unsigned int)pow(2, RB - 1);
		}

		// Initialize all class variables
		void set_params(int GPB, int RB) {
			this->GPB = GPB;
			this->RB = RB;
			GHB = 0;
			correct = 0;
			mispredict = 0;

			// set size of history table
			long long unsigned int tableSize = (long long unsigned int)pow(2,GPB);
			for (int j = 0; j< tableSize; j++){
				bpTable.push_back(2);
			}
		}

	public:
		gshare(int GPB, int RB) {
			set_params(GPB, RB);
		}
		
		// Function that updates the correct and mispredictions.
		int branch_predict(long long unsigned int pc, char outcome) {
			// Pad on 0's to the same length of GPB
			long long unsigned int MGHB = GHB*(long long unsigned int)pow(2, GPB-RB);
			long long unsigned int MPC = pc%(long long unsigned int)pow(2, GPB);
			long long unsigned int index = MGHB ^ MPC;

			if (state(bpTable.at(index))==outcome) {
				correct++;
				bpTable.at(index)=increment(bpTable.at(index), outcome);
			} else {
				mispredict++;
				bpTable.at(index)=increment(bpTable.at(index), outcome);
			}
			updateGHB(outcome);
		}

		// Remove the last two bits as they are always 0
		long long unsigned int parseAddress (std::string address) {
			long long unsigned int newAddress = std::strtoull(address.c_str(), 0, 16);
			newAddress = newAddress/4;
			return newAddress;
		}

		double get_predict_rate() {
			return (double)(correct/(correct + mispredict))*100.00;
		}

		double get_mispredict_rate() {
			return (double)(mispredict)/((double)(correct + mispredict))*100.00; 	
		}
};

// Driver method
int main(int argc, char *argv[]) {
	//Implementing argument command line
	if (argc != 4) {
		std::cout<<"Proper Useage: "<< std::endl
		<< argv[0]
		<<" <GPB>" << "<RV>"
		<<"<TRACE_FILE>"<<std::endl;
		exit (EXIT_FAILURE);
	}

	int GPB = atoi(argv[1]);
	int RB = atoi(argv[2]);
	std::string fileName = argv[3];

	std::ifstream myFile;
	myFile.open(fileName.c_str());
	char outcome;
	std::string address;

	gshare g(GPB, RB);

	// While the file still has lines, continue updating the cache
	if(myFile.is_open()) {
		while (myFile >> address >> outcome) {
			g.branch_predict(g.parseAddress(address), toupper(outcome));
		}
		myFile.close();
	} else {
		std::cout<<"The file <"<<fileName<<"> could not be opened!"<<std::endl;
		exit (EXIT_FAILURE);
	}

	std::cout<<GPB<<std::setw(10)<<RB<<std::setw(20);
	std::cout<<std::setprecision(4)<<g.get_mispredict_rate()<<std::setw(20)<<std::endl;

	return 0;
}
