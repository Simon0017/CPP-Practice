#include<iostream>
#include<string>
#include"voting_v2_Model.h"
using namespace std;

vector<int> generate_weights(vector<Contestant> contestants,Voter voter);
string regionToString(Regions r);
string partyToString(Parties p);

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

    for (const Voter& voter:voters)
    {
        vector<int> weights = generate_weights(contestants,voter);
        discrete_distribution<> distr(weights.begin(),weights.end());

        int chosen_index = distr(gen);
        vote_count[chosen_index]++;

    

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
