#include <stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>  

#define QTD_CACHE 32
#define QTD_RAM 256
#define QTD_TAG 27
#define QTD_LINE 5

using namespace std;

struct CACHE {
    string tag;
    string line;
    string data;
};

struct RAM {
    string address;
    string data;
};

RAM ram[QTD_RAM];
CACHE cache[QTD_CACHE];

//write ram data
int write_ram_data(){
    for(int i=0;i<QTD_RAM;i++)
        cout << "ADD: " << ram[i].address 
        << " DATA: " << ram[i].data 
        << endl;
}

//write cache data
int write_cache_data(){
    for(int i=0;i<QTD_CACHE;i++)       
        cout << "TAG: " << cache[i].tag 
        << " LINE: " << cache[i].line 
        << " DATA: " << cache[i].data 
        << endl;
}

//load cache
void load_cache(){
    for(int i=0;i<QTD_CACHE;i++){
        bitset<QTD_LINE> bit (i);
        cache[i].line = bit.to_string();
        cache[i].tag = "";
        cache[i].data = "";
    }
}

string get_address_binary(string address){
    //get hex address and convert to binary
    bitset<QTD_CACHE> ads_bin (stol(address, nullptr, 16));
    //convert binary to string
    return ads_bin.to_string();
}

int get_line_index(string line){
    //convert line part to binary
    bitset<QTD_LINE> bit_index(line);
    //convert binary line to int
    return (int)bit_index.to_ulong();
}

//search if given address is into cache
int search_cache(string address){    
    string add = get_address_binary(address);
      
    //get tag part of full address
    string tag = add.substr(0 , add.length()-QTD_LINE);

    //get line part of full address
    string line =  add.substr(add.length()-QTD_LINE , add.length());

    //get line index
    int i = get_line_index(line);

    //cout << "ADD: " << address << " TAG: " << tag << " LINE: " << line << endl;

    //if tag matches return the index (line)
    if(tag == cache[i].tag){
        return i;
    }
    
    return -1;
}

void insert_cache(string address){
    string add = get_address_binary(address);
      
    //get tag part of full address
    string tag = add.substr(0 , add.length()-QTD_LINE);

    //get line part of full address
    string line =  add.substr(add.length()-QTD_LINE , add.length());

    //get line index
    int i = get_line_index(line); 

    cache[i].tag = tag;
    cache[i].data = "RANDOM DATA";
}

int main(){   
    //load_cache
    load_cache();

    int hit = 0;
    int miss = 0;

    string address;
    int index;

    // read trace
    while (cin >> address){

        //check if adress is into cache
        index = search_cache(address);

        //if it is, hit!
        if(index != -1){
            hit++;
        }    
        //else, insert adress into cache, miss!          
        else {
            insert_cache(address);
            miss++;
        }
    }
    
    cout << "HIT: " << hit 
    << " MISS: " << miss << endl
    << "HIT RATE: " << 100*(hit/(hit+miss)) << "%"
    << endl;

    cout << endl << endl << endl;
    write_cache_data();

    return 0;
}
