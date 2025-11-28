#include<iostream>
#include<string>
#include<sstream>
#include"voting_v2_Model.h"
#include"json.hpp"
#include<fstream>
using namespace std;
using json = nlohmann::json;

vector<int> generate_weights(vector<Contestant> contestants,Voter voter);
string regionToString(Regions r);
string partyToString(Parties p);


void write_json(
    const vector<Contestant>& contestants,
    const vector<int>& vote_count,
    const json& votes_log,
    const Contestant& winner,
    string filename = "voting_full_results.json"
) {
    json j;

    j["total_voters"] = votes_log.size();
    j["votes"] = votes_log;

    j["contestants"] = json::array();
    for (size_t i = 0; i < contestants.size(); i++) {
        j["contestants"].push_back({
            {"name", contestants[i].name},
            {"age", contestants[i].age},
            {"region", regionToString(contestants[i].region)},
            {"party", partyToString(contestants[i].political_affliation)},
            {"in_office", contestants[i].in_office},
            {"votes", vote_count[i]}
        });
    }

    j["winner"] = {
        {"name", winner.name},
        {"votes", vote_count[
            max_element(vote_count.begin(), vote_count.end()) - vote_count.begin()
        ]}
    };

    ofstream file(filename);
    file << j.dump(4);
    file.close();

    cout << "[+] Full JSON log written to " << filename << endl;
}

int main(){
    vector<Voter> voters = generate_voters();
    vector<Contestant> contestants = generate_contestants();

    cout << "=====================" << endl;
    cout << "  CONTESTANTS" << endl;
    cout << "=====================" << endl;

    for (size_t i = 0; i < contestants.size(); i++) {
        const Contestant& c = contestants[i];
        cout << i+1 << ". " << c.name
            << " | Age: " << c.age
            << " | Region: " << regionToString(c.region)
            << " | Party: " << partyToString(c.political_affliation)
            << " | Likeability: " << c.likeability
            << " | In Office: " << (c.in_office ? "Yes" : "No")
            << endl;
    }

    random_device rd;
    mt19937 gen(rd());

    vector<int> vote_count(contestants.size(), 0);

    json votes_log = json::array();

    for (const Voter& voter:voters)
    {
        vector<int> weights = generate_weights(contestants,voter);
        discrete_distribution<> distr(weights.begin(),weights.end());

        int chosen_index = distr(gen);
        vote_count[chosen_index]++;

        const Contestant& chosen = contestants[chosen_index];

        votes_log.push_back({
            {"voters_name",voter.name},
            {"voter_region",regionToString(voter.region)},
            {"voter_party",partyToString(voter.political_affliation)},
            {"voted_for",chosen.name},
            {"Contestant_Region",regionToString(chosen.region)},
            {"Contestant Party",partyToString(chosen.political_affliation)}
        });
        

    }

    cout << "\n=====================\n";
    cout << "   FINAL RESULTS\n";
    cout << "=====================\n";

    // Print results
    for (size_t i = 0; i < contestants.size(); i++)
    {
        cout << contestants[i].name 
        << " (" << partyToString(contestants[i].political_affliation)
        << ", " << regionToString(contestants[i].region)
        << ") = " << vote_count[i] << " votes\n";

    }

    // Find winner
    int max_votes = -1;
    int winner_index = -1;

    for (size_t i = 0; i < vote_count.size(); i++)
    {
        if (vote_count[i] > max_votes)
        {
            max_votes = vote_count[i];
            winner_index = i;
        }
    }

    cout << "\n=====================\n";
    cout << "       WINNER\n";
    cout << "=====================\n";

    cout << "[+] " << contestants[winner_index].name 
     << " (" << partyToString(contestants[winner_index].political_affliation)
     << ") wins with " << max_votes << " votes!" << endl;
    
    Contestant winner = contestants[winner_index];
    write_json(contestants,vote_count,votes_log,winner);

    return 0;
}


vector<int> generate_weights(vector<Contestant> contestants,Voter voter){
    vector<int> weights;
    weights.reserve(contestants.size());

    for (const Contestant& c: contestants )
    {
        int age_difference = abs(c.age - voter.age);
        bool in_same_party = c.political_affliation == voter.political_affliation;
        bool in_same_region = c.region == voter.region;

        int weight = 0;

        weight += c.likeability;

        if (in_same_party)
        {
            weight += 50;
        }

        if (in_same_region)
        {
            weight += 40;
        }

        if (age_difference <= 5) weight +=20;
        else if (age_difference <= 10) weight += 10;
        else if (age_difference <= 20) weight += 5;
        else                           weight += 1;

        if (c.in_office)
        {
            weight +=30;
        }
        
        if (weight < 1) weight = 1;

        weights.push_back(weight);
        
    }

    return weights;
    
}

string regionToString(Regions r) {
    switch (r) {
        case Western: return "Western";
        case Central: return "Central";
        case Nyanza: return "Nyanza";
        case Coastal: return "Coastal";
        case Rift_Valley: return "Rift Valley";
        case Nairobi: return "Nairobi";
        case Northern: return "Northern";
        case North_Eastern: return "North Eastern";
    }
    return "Unknown";
}

string partyToString(Parties p) {
    switch (p) {
        case UDA: return "UDA";
        case DAP: return "DAP";
        case DPK: return "DPK";
        case FORD: return "FORD";
        case ODM: return "ODM";
    }
    return "Unknown";
}

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

vector<Contestant> user_generated_contestants(){
    vector<Contestant> contestants;
    string input_string;
    int no_of_contestants;

    cout << "No of contestants: ";
    getline(cin,input_string);
    stringstream(input_string) >> no_of_contestants;

    for (size_t i = 0; i < no_of_contestants; i++)
    {
        string name,region_str,party_str,in_office_str;
        int age,likeability;
        bool in_office;
        Regions region;
        Parties party;

        cout << "Contestant full name: ";
        getline(cin,name);

        cout << "Contestants Age: ";
        getline(cin,input_string);
        stringstream(input_string) >> age;

        cout << "Region:[Western,Central,Nyanza,Coastal,Rift_Valley,Nairobi,Northern,North_Eastern] ";
        getline(cin,region_str);

        cout << "Party:[UDA,DAP,DPK,FORD,ODM,] ";
        getline(cin,party_str);

        cout << "How much is is likeable(0-100): ";
        getline(cin,input_string);
        stringstream(input_string) >> likeability;

        cout << "Are they in office?(y/n) ";
        getline(cin,in_office_str);

        region = getRegion(region_str);
        party  = getParty(party_str);
        in_office = getOfficeBoolean(in_office_str);

        Contestant cont = Contestant(name,age,region,party,likeability,in_office);
        contestants.push_back(cont);

    }
    
    return contestants;
}

Regions getRegion(const string& r){
    if (r == "Western") return Western;
    if (r == "Central") return Central;
    if (r == "Nyanza") return Nyanza;
    if (r == "Coastal") return Coastal;
    if (r == "Rift Valley" || r == "Rift_Valley") return Rift_Valley;
    if (r == "Nairobi") return Nairobi;
    if (r == "Northern") return Northern;
    if (r == "North Eastern" || r == "North_Eastern") return North_Eastern;

    return Nairobi;
    
}

Parties getParty(const string& p){
    if (p == "UDA") return UDA;
    if (p == "DAP") return DAP;
    if (p == "ODM") return ODM;
    if (p == "DPK") return DPK;
    if (p == "FORD") return FORD;

    return DAP;
}

bool getOfficeBoolean(const string& b ){
    if (b == "yes") return true;
    if (b == "no") return false;

    return false;
}

