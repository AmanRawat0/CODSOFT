#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class RecommendationSystem {
public:
    void addUserPreferences(const std::string& user, const std::vector<std::string>& preferences) {
        userPreferences[user] = preferences;
    }

    std::vector<std::string> recommend(const std::string& user) {
        std::map<std::string, int> itemScores;

        for (size_t i = 0; i < userPreferences[user].size(); ++i) {
            const std::string& pref = userPreferences[user][i];
            for (std::map<std::string, std::vector<std::string> >::iterator it = userPreferences.begin(); it != userPreferences.end(); ++it) {
                const std::string& otherUser = it->first;
                const std::vector<std::string>& otherPrefs = it->second;

                if (otherUser != user && std::find(otherPrefs.begin(), otherPrefs.end(), pref) != otherPrefs.end()) {
                    for (size_t j = 0; j < otherPrefs.size(); ++j) {
                        const std::string& item = otherPrefs[j];
                        if (std::find(userPreferences[user].begin(), userPreferences[user].end(), item) == userPreferences[user].end()) {
                            itemScores[item]++;
                        }
                    }
                }
            }
        }

        std::vector<std::pair<std::string, int> > scoredItems(itemScores.begin(), itemScores.end());
        std::sort(scoredItems.begin(), scoredItems.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });

        std::vector<std::string> recommendations;
        for (size_t i = 0; i < scoredItems.size(); ++i) {
            recommendations.push_back(scoredItems[i].first);
        }
        return recommendations;
    }

private:
    std::map<std::string, std::vector<std::string> > userPreferences;
};

int main() {
    RecommendationSystem rs;
    std::string userName;
    int numUsers = 3;

    for (int i = 1; i <= numUsers; ++i) {
        std::cout << "Enter name of user " << i << ": ";
        std::string name;
        std::cin >> name;

        std::vector<std::string> preferences;
        std::cout << "How many web series did " << name << " watch? ";
        int count;
        std::cin >> count;
        std::cin.ignore();

        for (int j = 0; j < count; ++j) {
            std::string series;
            std::cout << "Enter web series " << j + 1 << ": ";
            std::getline(std::cin, series);
            preferences.push_back(series);
        }

        rs.addUserPreferences(name, preferences);
    }

    std::cout << "\nEnter the name of the user who wants recommendations: ";
    std::cin >> userName;

    std::vector<std::string> recommendations = rs.recommend(userName);

    std::cout << "\nRecommended web series for " << userName << ":\n";
    if (recommendations.empty()) {
        std::cout << "No recommendations available based on current data.\n";
    } else {
        for (size_t i = 0; i < recommendations.size(); ++i) {
            std::cout << "- " << recommendations[i] << '\n';
        }
    }

    return 0;
}