#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<map>
using namespace std;

struct Contestant
{
    string name;
    int age;
};

struct Voter
{
    string name;
};

std::vector<Contestant> get_contestants(){
    std::vector<Contestant> contestants = {
        {"Lammens",22},
        {"De ligt",25},
        {"Yoro",19},
        {"Shaw",30},
        {"Casemiro",32},
        {"Bruno",31},
        {"Mbuemo",26}
    };

    return contestants;

}

std::vector<Voter> get_voters(){
    std::vector<Voter> voters = {
        {"Alice"}, {"Bob"}, {"Charlie"}, {"David"}, {"Eve"},
        {"Frank"}, {"Grace"}, {"Hannah"}, {"Isaac"}, {"Jack"},
        {"Karen"}, {"Leo"}, {"Mia"}, {"Nathan"}, {"Olivia"},
        {"Paul"}, {"Quincy"}, {"Rachel"}, {"Sam"}, {"Tina"},
        {"Uma"}, {"Victor"}, {"Wendy"}, {"Xander"}, {"Yara"},
        {"Zane"}, {"Abby"}, {"Brian"}, {"Clara"}, {"Derek"}
    };

    return voters;
}

void voting(){
    auto contestants = get_contestants();
    auto voters = get_voters();

    int contestants_size = contestants.size();
    std::random_device rd; //random device
    std::mt19937 gen(rd()); //engine
    std::uniform_int_distribution<> dist(0,contestants_size -1); //distribution

    // Map contestant index → votes
    std::map<int, int> votes;

    // initialize all vote counts to 0
    for (int i = 0; i < contestants_size; i++) {
        votes[i] = 0;
    }


    for (Voter voter:voters)
    {
        int random_choice = dist(gen);
        votes[random_choice]++; //count vote
        Contestant voter_choice = contestants[random_choice]; 
        cout<< "[+] Voter: "<< voter.name << " has voted for " << voter_choice.name  <<endl;

        
    }

    cout<< "\n\n";


    // Det winner
    int winner_index = -1;
    int max_votes = -1;

    for (const auto& pair:votes)
    {
        int idx = pair.first;
        int count = pair.second;


        cout <<"[+]" << contestants[idx].name << " received " << count << " votes.\n";

        if (count > max_votes)
        {
            max_votes = count;
            winner_index = idx;
        }
        
    }

    cout << "\n===========================\n";
    cout << "[*]Winner: " << contestants[winner_index].name
         << " with " << max_votes << " votes!\n";
    cout << "===========================\n";
    
    
};
