#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

// Abhimanyu-Chakravyuh's
bool canCross(const vector<int>& enemy_powers, int i, int curr_power, int behind, int skips, int recharges, int start_power) {
    if (i == 11) return true;  // Base case: Reached the last circle

    bool check = false;

    // Option 1: Recharge if allowed and current power is less than initial power
    if (recharges > 0 && curr_power < start_power) {
        check = canCross(enemy_powers, i, start_power, behind, skips, recharges - 1, start_power) || check;
    }

    // Option 2: Deal with regenerating enemy attacking from behind
    if (curr_power >= behind) {
        curr_power -= behind;  // Reduce power by behind enemy's attack
        behind = 0;  // Clear the behind threat
    } else {
        return false;  // Lose if behind enemy is too strong
    }

    // Option 3: Skip the current enemy if skips are available
    if (skips > 0) {
        check = canCross(enemy_powers, i + 1, curr_power, behind, skips - 1, recharges, start_power) || check;
    }

    // Option 4: Fight the current enemy if power is enough
    if (curr_power >= enemy_powers[i]) {
        if (i == 2 || i == 6) {  // Enemies in circle 3 and 7 regenerate once
            behind = enemy_powers[i] / 2;
        }
        check = canCross(enemy_powers, i + 1, curr_power - enemy_powers[i], behind, skips, recharges, start_power) || check;
    }

    return check;
}

int main() {
    vector<int> k(11);  // Array to store enemy powers for each circle

    // Input enemy powers
    for (int i = 0; i < 11; ++i) {
        cin >> k[i];
    }

    int power, skip, recharge;
    // Input Abhimanyu's initial power, available skips, and recharges
    cin >> power >> skip >> recharge;

    int behind = 0;  // Initialize no threat from behind initially

    // Output result: Can Abhimanyu cross or not?
    if (canCross(k, 0, power, behind, skip, recharge, power)) {
        cout << "YES (Abhimanyu can cross the Chakrvyuh)" << endl;
    } else {
        cout << "NO (Abhimanyu cannot cross the Chakrvyuh)" << endl;
    }

    return 0;
}


//Test case: 1 

// enemyPower = {0, 5, 3, 7, 8, 6, 4, 9, 10, 2, 5}
// power = 10
// a = 2
// b = 1
// Answer: Abhimanyu cannot cross the Chakrvyuh

// Test case: 2

// enemyPower = {0, 2, 3, 2, 5, 4, 6, 2, 1, 7, 3}
// power = 15
// a = 3
// b = 1
// Answer: Abhimanyu can cross the Chakrvyuh
