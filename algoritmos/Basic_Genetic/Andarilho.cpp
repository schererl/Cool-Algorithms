#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>  
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <time.h> 
using namespace std;

struct Way
{
    int id;
    float lat;
    float log;
};


const vector<string> explode(const string& s, const char& c);
Way* ReadWay(char* argv, int &road);
string ReplaceAll(string str, const string& from, const string& to);
int GetDistance(Way a, Way b);
int GetRoad(int road);
int TotalDistance(Way *way, int road);
void ChangeTrip(Way *way, Way* cp, int road);
void PrintTrip(Way *way, int road);
void Start(Way *way,int road);


int main(int argc, char **argv)
{
    if(argc < 2)
    {
        cout << "./run NomeArq.txt" << endl;
        return -1;
    }
    srand( (unsigned)time(NULL) );
    int road, start_city;
    Way *way = ReadWay(argv[1], road);
    Start(way, road);
    cout << "total road: " << road << endl;
    cout << "distance trip: " << TotalDistance(way, road) << endl;
    int modificacoes = 0;
    Way *cp = (Way *)malloc(road * sizeof(Way));
    while(true)
    {
         
        ChangeTrip(way, cp, road);
        if(TotalDistance(way, road) > TotalDistance(cp, road))
        {
            
            modificacoes++;
            memcpy(way, cp, road * sizeof(Way));
            if(modificacoes > 5)
            {
                cout << "changed trip: " << TotalDistance(cp, road) << endl;
                modificacoes = 0;
            }
        }
        //free(cp);
            
    }   
    
}

void Start(Way *way,int road)
{
    for(int i = 0; i < road; i++)
    {
        int city = i;
        int change_city = GetRoad(road);
        if(change_city >= road) continue;
        
        Way tmp = way[city];
        way[city] = way[change_city];
        way[change_city] = tmp;
    }
}

void ChangeTrip(Way *way, Way* cp, int road)
{
    memcpy(cp, way, road * sizeof(Way));
    for(int i = 0; i < road; i++)
    {
        if(rand() % 100 > 0.5) continue;
        
        int city = i;
        int change_city = GetRoad(road);
        if(change_city >= road) continue;
        Way tmp = cp[city];
        cp[city] = cp[change_city];
        cp[change_city] = tmp;
    }
}


int TotalDistance(Way *way, int road)
{
    int total_distance = 0;
    int city = 0;
    int next_city = 1;
    while(city < road)
    {
        
        total_distance += GetDistance(way[city], way[next_city]);
        city++;
        next_city++;
    }
    return total_distance;
}


int GetRoad(int road)
{
    return rand() % road;
}

int GetDistance(Way a, Way b)
{
    return sqrt(pow(( b.lat - a.lat ), 2) + pow((b.log - a.log),2)); 
}

//read data file
Way* ReadWay(char* argv, int &road)
{
    ifstream file(argv);
    string buff;
    getline(file, buff);
    road = stoi(buff);

    Way *way = (Way *)malloc(road * sizeof(Way));
    int index = 0;
    while(getline(file, buff))
    {
        vector<string> buff_vet{explode(buff, ' ')};
        buff = buff_vet[2];
        buff = ReplaceAll(buff, std::string("Cid"), std::string(""));
        
        Way tmp;
        tmp.id =  stoi(buff);
        tmp.lat = stof(buff_vet[0]);
        tmp.log = stof(buff_vet[1]);
        
        way[tmp.id-1] = tmp;
        //index++;
    }

    return way;
}

const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<std::string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n;
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}


void PrintTrip(Way *way, int road)
{
    for(int i = 0; i < road;i++)
    {
        cout << way[i].id << " ";
    }
    cout << endl;
}


string ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); 
    }
    return str;
}