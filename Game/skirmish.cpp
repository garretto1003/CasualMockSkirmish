#include "warrior.h"
#include "print.h"

#include <sstream>
#include <vector>

/**
 * @brief print_header prints header for current turn.
 * @param currentTeam = current attacking team
 * @param turn = current simulation turn
 */

void print_header(unsigned int currentTeam, unsigned int turn) {
    std::stringstream oSS;

    switch (currentTeam) {
        case 0: {
            oSS << "Team Red -- Turn " << turn;
            print(oSS.str(), RED);
            print();
            break;
        }
        case 1: {
            oSS << "Team Blue -- Turn " << turn;
            print(oSS.str(), BLUE);
            print();
            break;
        }
    }
}

/**
 * @brief start_skirmish runs a skirmish simulation.
 * @param team_red  = team red warriors
 * @param team_blue = team blue warriors
 */

void start_skirmish(std::vector<Warrior*> team_red, std::vector<Warrior*> team_blue) {
    unsigned int turn = 0;

    // Simulation prints current turn until one team has no warriors left.
    while(team_red.size() > 0 && team_blue.size() > 0) {
        switch (turn % 2) {
            case 0: { // Team Red attacks
                // Print header.
                print_header(turn % 2, turn);

                // Random attacking and defending warriors are selected at random.
                unsigned int random_red_warrior  = rand() % team_red.size();
                unsigned int random_blue_warrior = rand() % team_blue.size();

                std::stringstream attackEventOSS;

                // Append first part of event message before red warrior attacks to string stream.
                attackEventOSS << "Red " << team_red[random_red_warrior]->get_type()
                               << " " << team_red[random_red_warrior]->get_name()
                               << " (HP: " << team_red[random_red_warrior]->get_health()
                               << ") attacks Blue " << team_blue[random_blue_warrior]->get_type()
                               << " " << team_blue[random_blue_warrior]->get_name()
                               << " (HP: " << team_blue[random_blue_warrior]->get_health()
                               << ") " << std::flush;

                // Get boolean to determine if the attack is hit or miss.
                bool is_successful_attack = team_red[random_red_warrior]->attack(team_blue[random_blue_warrior]);

                // Append attack result to string stream.
                if (is_successful_attack) {
                    attackEventOSS << "and lands a blow (-" << team_red[random_red_warrior]->get_attack_damage()
                                   << "). " << std::flush;
                } else {
                    attackEventOSS << "and misses (-0). " << std::flush;
                }

                // Append defending warrior's health result to string stream.
                attackEventOSS << "Blue " << team_blue[random_blue_warrior]->get_type()
                               << " " << team_blue[random_blue_warrior]->get_name()
                               << " (HP: " << team_blue[random_blue_warrior]->get_health()
                               << ")" << std::endl;

                // Print string stream.
                print(attackEventOSS.str());

                // Remove warrior from defending team if they died.
                if (!team_blue[random_blue_warrior]->is_alive()) {
                    team_blue.erase(team_blue.begin() + random_blue_warrior);
                }

                break;
            } case 1: { // Team Blue attacks
                // Print header.
                print_header(turn % 2, turn);

                // Random attacking and defending warriors are selected at random.
                unsigned int random_blue_warrior = rand() % team_blue.size();
                unsigned int random_red_warrior  = rand() % team_red.size();

                std::stringstream attackEventOSS;

                // Append first part of event message before blue warrior attacks to string stream.
                attackEventOSS << "Blue " << team_blue[random_blue_warrior]->get_type()
                               << " " << team_blue[random_blue_warrior]->get_name()
                               << " (HP: " << team_blue[random_blue_warrior]->get_health()
                               << ") attacks Red " << team_red[random_red_warrior]->get_type()
                               << " " << team_red[random_red_warrior]->get_name()
                               << " (HP: " << team_red[random_red_warrior]->get_health()
                               << ") " << std::flush;

                // Get boolean to determine if the attack is hit or miss.
                bool is_successful_attack = team_blue[random_blue_warrior]->attack(team_red[random_red_warrior]);

                // Append attack result to string stream.
                if (is_successful_attack) {
                    attackEventOSS << "and lands a blow (-" << team_blue[random_blue_warrior]->get_attack_damage()
                                   << "). " << std::flush;
                } else {
                    attackEventOSS << "and misses (-0). " << std::flush;
                }

                // Append defending warrior's health result to string stream.
                attackEventOSS << "Red " << team_red[random_red_warrior]->get_type()
                               << " " << team_red[random_red_warrior]->get_name()
                               << " (HP: " << team_red[random_red_warrior]->get_health()
                               << ")" << std::endl;

                // Print string stream.
                print(attackEventOSS.str());

                // Remove warrior from defending team if they died.
                if (!team_red[random_red_warrior]->is_alive()) {
                    team_red.erase(team_red.begin() + random_red_warrior);
                }

                break;
            }
        }

        // Proceed to next turn.
        ++turn;
    }

    // Print winning team.
    if (team_red.size() > 0) {
        print("Team Red Wins!", RED);
    } else {
        print("Team Blue Wins!", BLUE);
    }
}
