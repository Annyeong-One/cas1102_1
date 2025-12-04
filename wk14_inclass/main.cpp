#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

class Player {
protected:
    float fatigue_level = 0.0f; // 0.0 (fresh) to 1.0 (exhausted)
    std::string playerName;
    
public:
    // Base parameterized constructor
    Player(const std::string& name) : playerName(name) {
        std::cout << "\nPlayer registered: " << name << "." << std::endl;
    }
    
    // Base destructor
    virtual ~Player() {
        std::cout << "Base destructor: Player removed from system." << std::endl;
    }
    
    // Setter method for fatigue level
    void updateFatigue(float exertion_factor) {
        fatigue_level = std::min(1.0f, std::max(0.0f, fatigue_level + (exertion_factor * 0.1f)));
        
        std::cout << "--> Fatigue now: " << std::fixed << std::setprecision(1) << (fatigue_level * 100.0f) << "%" << std::endl;
    }

    // TASK 1: Implement the virtual base functions in the Player class.
    // (1) shootingSuccessRate:
    //     - Calculates the base rate using a standard formula and fatigue penalty.
    //     - Formula: 0.5 * base_skill * (1 - fatigue_level)
    //     - Return type: float
    //
    // (2) tackleSuccessRate:
    //     - Calculates the base rate, applying a less severe penalty for tackling.
    //     - Formula: base_skill * (1.0f - (0.5f * fatigue_level))
    //     - Return type: float
    virtual float shootingSuccessRate(int base_skill){
        return 0.5f * static_cast<float>(base_skill) * (1.0f - fatigue_level);
    }

    virtual float tackleSuccessRate(int base_skill){
        return static_cast<float>(base_skill) * (1.0f - (0.5f * fatigue_level));
    }
    
    // TASK 2: Implement the two overloaded checkEnergy base functions in the Player class.
    // (1) Overload for stamina (int):
    //     - Calculates the effective stamina based on the full impact of fatigue.
    //     - Formula: effective_stamina = base_stamina * (1 - fatigue_level)
    //
    // (2) Overload for hydration (float):
    //     - Calculates the effective hydration based on the reduced impact of fatigue (0.5x).
    //     - Formula: effective_hydration = base_hydration * (1.0f - (0.5f * fatigue_level))
    
    void checkEnergy (int base_stamina){
        float effective_stamina = static_cast<float>(base_stamina) * (1.0f - fatigue_level);

        std::cout << "Energy check -- Stamina: " << effective_stamina << " (Fatigue: " << std::fixed << std::setprecision(1) << (fatigue_level * 100.0f) << "%)" << std::endl;
    }
    
    void checkEnergy (float base_hydration){
        float effective_hydration = base_hydration * (1.0f - (0.5f * fatigue_level));

        std::cout << "Energy check -- Hydration: " << std::fixed << std::setprecision(2) << effective_hydration << "%" << std::endl;
    }
    
    // Getter method
    const std::string& getPlayerName() const { return playerName; }
};


// TASK 3: Defender as a public derived class of Player
// - Complete the class definition to inherit publicly from Player.
// - Write the parameterized constructor that passes the name to the base class.

class Defender : public Player {
public:
    Defender(const std::string& name) : Player(name) {
        std::cout << "Derived: Defender assigned." << std::endl;
    }
    
    // TASK 4: Override virtual base functions for Defender specialization.
    // (1) shootingSuccessRate:
    //     - Applies a positional penalty for non-attacking roles.
    //     - Formula: specialized_rate = base_rate x 0.8
    //
    // (2) tackleSuccessRate:
    //     - Applies a large tactical bonus reflective of a primary defensive duty.
    //     - Formula: specialized_rate = base_rate x 1.5
    
    float shootingSuccessRate (int base_skill) {
        float base_rate = Player::shootingSuccessRate(base_skill);
        float specialized_rate = base_rate * 0.8f;

        std::cout << "Success rate -- Shooting (Defender): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }
    
    float tackleSuccessRate (int base_skill) {
        float base_rate = Player::tackleSuccessRate(base_skill);
        float specialized_rate = base_rate * 1.5f;

        std::cout << "Success rate -- Tackle (Defender): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }
    
    // TASK 5: Bring the base function overloads available in the Defender class.
    /* Write down the code here */
    using Player::checkEnergy;

};


// TASK 6: Striker as a public derived class of Player
// - Complete the class definition to inherit publicly from Player.
// - Write the parameterized constructor that passes the name to the base class.

class Striker : public Player {
public:
    Striker(const std::string& name) : Player(name) {
        std::cout << "Derived: Striker assigned." << std::endl;
    }
    
    // TASK 7: Override virtual base functions for Striker specialization.
    // (1) shootingSuccessRate:
    //     - Applies a high positional bonus, which reflects the primary scoring duty.
    //     - Formula: specialized_rate = base_rate x 2
    //
    // (2) tackleSuccessRate:
    //     - Applies a high penalty reflective of low defensive contribution.
    //     - Formula: specialized_rate = base_rate x 0.5
    
    float shootingSuccessRate (int base_skill) {
        float base_rate = Player::shootingSuccessRate(base_skill);
        float specialized_rate = base_rate * 2.0f;

        std::cout << "Success rate -- Shooting (Striker): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }
    
    float tackleSuccessRate (int base_skill) {
        float base_rate = Player::tackleSuccessRate(base_skill);
        float specialized_rate = base_rate * 0.5f;

        std::cout << "Success rate -- Tackle (Striker): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }
    
    // TASK 8: Bring the base function overloads available in the Striker class.
    /* Write down the code here */
    using Player::checkEnergy;
};


int main() {
    int base_skill_value = 60;
    int base_stamina_value = 90;
    float base_hydration_value = 95.0f;
        
    // TASK 9:
    // - Create a Defender object pointer with the name "Minjae Kim" by using the 'new' keyword.
    // - Check the object's energy (stamina and hydration) based on the provided base values.
    // - Check the object's tackle success rate based on the base_skill_value.
    
    Defender* mjkim = new Defender("Minjae Kim");
    mjkim->checkEnergy(base_stamina_value);
    mjkim->checkEnergy(base_hydration_value);
    mjkim->tackleSuccessRate(base_skill_value);
    
    std::cout << "\n[Action -- Heavy run]" << std::endl;
    // TASK 10:
    // - Update fatigue level to 0.5 (using the updateFatigue method).
    // - Check the object's new energy (stamina and hydration) based on the base values.
    // - Check the new tackle success rate based on the base_skill_value (it should be lower).
    // - Finally, delete the object using the 'delete' keyword.

    mjkim->updateFatigue(0.5f);
    mjkim->checkEnergy(base_stamina_value);
    mjkim->checkEnergy(base_hydration_value);
    mjkim->tackleSuccessRate(base_skill_value);
    delete mjkim;
    
    // TASK 11:
    // - Create a Striker object pointer with the name "Heungmin Son" by using the 'new' keyword.
    // - Check the object's energy (stamina and hydration) based on the provided base values.
    // - Check the object's shooting success rate based on the base_skill_value.
    
    Striker* hmson = new Striker("Heungmin Son"); 
    hmson->checkEnergy(base_stamina_value);
    hmson->checkEnergy(base_hydration_value);
    hmson->shootingSuccessRate(base_skill_value);
    
    std::cout << "\n[Action -- Moderate sprint]" << std::endl;
    // TASK 12:
    // - Update fatigue level to 0.3 (using the updateFatigue method).
    // - Check the object's new energy (stamina and hydration) based on the base values.
    // - Check the new shooting success rate based on the base_skill_value (it should be lower).
    // - Finally, delete the object using the 'delete' keyword.
    
    hmson->updateFatigue(0.3f);
    hmson->checkEnergy(base_stamina_value);
    hmson->checkEnergy(base_hydration_value);
    hmson->shootingSuccessRate(base_skill_value);
    delete hmson;
    
    return 0;
}
