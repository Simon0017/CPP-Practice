#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<random>
using namespace std;
enum Regions{
    Western,
    Central,
    Nyanza,
    Coastal,
    Rift_Valley,
    Nairobi,
    Northern,
    North_Eastern
};

enum Parties{
    UDA,
    DAP,
    DPK,
    FORD,
    ODM,
};

struct Contestant
{
    string name;
    int age;
    Regions region;
    Parties political_affliation;
    int likeability;
    bool in_office;

    Contestant(string name,int age,Regions region,Parties political_affliation , int likeabilty, bool in_office);
};

struct Voter
{
    string name;
    int age;
    Regions region;
    Parties political_affliation;

    Voter(string name,int age,Regions region,Parties political_affliation);
};


const string  firstnames[30] = {
    "John", "Mary", "Peter", "Grace", "Samuel",
    "Esther", "Daniel", "Elizabeth", "Paul", "Susan",
    "David", "Joyce", "James", "Margaret", "Joseph",
    "Ruth", "Andrew", "Sarah", "Michael", "Rebecca",
    "Benjamin", "Lydia", "Jonathan", "Rose", "Mark",
    "Ann", "Stephen", "Naomi", "Kevin", "Jane"
};

const string lastnames[30] = {
    // Luhya
    "Wanyama", "Barasa", "Shikuku", "Nangila", "Mabonga",

    // Kikuyu
    "Kamau", "Wanjiku", "Njoroge", "Mwangi", "Kariuki",

    // Luo
    "Odhiambo", "Ochieng", "Otieno", "Okoth", "Achieng",

    // Kalenjin
    "Kiptoo", "Cheruiyot", "Kiplagat", "Kipchumba", "Chebet",

    // Kamba
    "Mutiso", "Musyoka", "Ndunda", "Muema", "Muli",

    // Kisii
    "Ongeri", "Nyambane", "Mogaka", "Muthoni", "Kimathi"
};

std::map<Regions,int> region_voter_limits = {
    {Western,1000},
    {Central,900},
    {Nyanza,800},
    {Rift_Valley,600},
    {Coastal,500},
    {Nairobi,400},
    {Northern,200},
    {North_Eastern,150},
};

vector<Voter> generate_voters();
vector<Contestant> generate_contestants();

Contestant::Contestant(string name,int age,Regions region,Parties political_affliation , int likeabilty, bool in_office){
    this->name = name;
    this->age = age;
    this->region = region;
    this->political_affliation = political_affliation;
    this->likeability = likeability;
    this->in_office = in_office;
}

Voter::Voter(string name,int age,Regions region,Parties political_affliation){
    this->name = name;
    this->age = age;
    this->region = region;
    this->political_affliation = political_affliation;
}


vector<Voter> generate_voters(){
    vector<Voter> voters;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> name_distr(0,29);
    uniform_int_distribution<> age_distr(18,85);
    uniform_int_distribution<> party_distr(UDA,ODM);

    for (auto &pair:region_voter_limits)
    {
        Regions region = pair.first;
        int limit = pair.second;


        for (int i = 0; i < limit; i++)
        {
            string full_name = firstnames[name_distr(gen)] + " " + lastnames[name_distr(gen)];
            Voter voter = Voter(full_name,age_distr(gen),region,(Parties)party_distr(gen));

            voters.push_back(voter);
        }
        
    }

    return voters;
    
}

vector<Contestant> generate_contestants(){
    vector<Contestant> contestants;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> name_distr(0,29);
    uniform_int_distribution<> age_distr(18,85);
    uniform_int_distribution<> party_distr(UDA,ODM);
    uniform_int_distribution<> in_office_distr(0,1);
    uniform_int_distribution<> likeability_distr(1,100);
    uniform_int_distribution<> region_disr(Western,North_Eastern);

    
    // size of contestors = 7
    for (int i = 0; i < 10; i++)
    {
        string name = firstnames[name_distr(gen)] + " " + lastnames[name_distr(gen)];
        int age = age_distr(gen);
        Regions region = (Regions)region_disr(gen);
        Parties party = (Parties)party_distr(gen);
        int likeablity  = likeability_distr(gen);
        bool in_office = in_office_distr(gen);

        Contestant cont = Contestant(name,age,region,party,likeablity,in_office);

        contestants.push_back(cont);
    }
    
    return contestants;
}