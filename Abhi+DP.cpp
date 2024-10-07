#include <bits/stdc++.h>
using namespace std;

//Abhimanyu's Chakravyuh

// DP memo table
int dp[11][111][11][11]; // circles, power, skips, recharges

bool canCrossDP(const vector<int>& enemy_powers, int i, int curr_power, int skips, int recharges, int start_power) {
    // Base case: If Abhimanyu can cross the Last circle
    if (i == 11) return true;
    
    // Check if the current state has already been computed
    if (dp[i][curr_power][skips][recharges] != -1) {
        return dp[i][curr_power][skips][recharges];
    }
    
    // Assume this state is initially false
    bool check = false;
    
    // Option 1: Recharge if available and not already at max power
    if (recharges > 0 && curr_power < start_power) {
        check = canCrossDP(enemy_powers, i, start_power, skips, recharges - 1, start_power) || check;
    }
    
    // Option 2: Skip the current enemy if skips are available
    if (skips > 0) {
        check = canCrossDP(enemy_powers, i + 1, curr_power, skips - 1, recharges, start_power) || check;
    }
    
    // Option 3: Fight the current enemy if Abhimanyu has enough power
    if (curr_power >= enemy_powers[i]) {
        int behind_attack = 0;
        
        // Handle regeneration for enemies at circle 3 and 7
        if (i == 2 || i == 6) {
            behind_attack = enemy_powers[i] / 2;
        }
        
        // Recursively check the next circle and consider behind attack if applicable
        if (curr_power - enemy_powers[i] >= behind_attack) {
            check = canCrossDP(enemy_powers, i + 1, curr_power - enemy_powers[i] - behind_attack, skips, recharges, start_power) || check;
        }
    }
    
    // Store the result in the dp table and return
    return dp[i][curr_power][skips][recharges] = check;
}

int main() {
    vector<int> enemy_powers(11);

    // Input: enemy powers in the circles
    for (int i = 0; i < 11; ++i) {
        cin >> enemy_powers[i];
    }

    int player_power, skip, recharge;
    cin >> player_power >> skip >> recharge;

    // Initialize the DP table with -1
    memset(dp, -1, sizeof(dp));

    // Check if Abhimanyu can cross the Chakravyuha
    if (canCrossDP(enemy_powers, 0, player_power, skip, recharge, player_power)) {
        cout << "YES (Abhimanyu can cross the Chakrvyuh)" << endl;
    } else {
        cout << "NO (Abhimanyu cannot cross the Chakrvyuh)" << endl;
    }

    return 0;
}
