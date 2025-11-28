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
vector<Contestant> user_generated_contestants();
Regions getRegion(const string& r);
Parties getParty(const string& p);
bool getOfficeBoolean(const string& b );