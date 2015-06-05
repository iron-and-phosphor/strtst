#include "connector.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]){
	string ip = "localhost";
	int port = 3720;
	string game_file = "game02.txt";

	if(argc == 4){
		ip = argv[1];
		port = atol(argv[2]);
		game_file = argv[3];
	}else if(argc == 2){
		game_file = argv[1];
	}else{
		printf("use: [ip addr] [port] [name game file]\n");
		exit(-1);
	}

int player1 = connect(ip,port);
	int player2 = connect(ip,port);
	int current_player = 0;
	int turn_counter = 0;
	int turn_locator = 0;
	string line;
	string input;
	string recv;
	ifstream myfile (game_file);
	if(myfile.is_open()){
		while(getline(myfile,line)){
			if(turn_counter >= turn_locator){
				cout << "how many turns forward? :";
				cin >> input;
				if(input.length() > 0) turn_locator += stoi(input); 
				else turn_locator += 2;
			}
			if(line.at(1) == '<' || line.at(1) == '>'){
				if(line.at(0) == '4') current_player = player1;
				else current_player = player2;
				if(line.at(1) == '>') {
					sendln(current_player, line.substr(3));
					turn_counter++;
				} else {
					recv = receiveln(current_player);
					if(line.substr(3) == recv)
						cout << "[ OK ]" << line << "\tserv:"<< recv << endl;
					else cout << "[FAIL]" << line << "\tserv:"<< recv << endl;

				}
			}
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 
	
	//disconnect(player1);
	//disconnect(player2);	
}
