#include <iostream>
#include <queue>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <stack>
#include <string>

using namespace std;

// Exercise class definition
class Exercise {
private:
    string name;
    int duration; // Duration in minutes
    int caloriesBurned;

public:
    Exercise(string n = "", int d = 0, int c = 0) : name(n), duration(d), caloriesBurned(c) {}

    string getName() const { return name; }
    int getDuration() const { return duration; }
    int getCaloriesBurned() const { return caloriesBurned; }

    void setName(const string& n) { name = n; }
    void setDuration(int d) { duration = d; }
    void setCaloriesBurned(int c) { caloriesBurned = c; }

    // Overload the comparison operator for priority_queue
    bool operator<(const Exercise& other) const {
        return duration < other.duration;
    }
};

// Activity class definition
class Activity {
private:
    string description;
    string date; // Date in YYYY-MM-DD format

public:
    Activity(string d = "", string dt = "") : description(d), date(dt) {}

    string getDescription() const { return description; }
    string getDate() const { return date; }

    void setDescription(const string& d) { description = d; }
    void setDate(const string& dt) { date = dt; }
};

// ExerciseNode class definition
class ExerciseNode {
public:
    Exercise data;
    ExerciseNode* next;
    ExerciseNode* prev;
    ExerciseNode(const Exercise& item) : data(item), next(nullptr), prev(nullptr) {}
};

// DoublyLinkedList class definition
class DoublyLinkedList {
private:
    ExerciseNode* head;
    ExerciseNode* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList();
    void insert(const Exercise& item);
    void display() const;
    void editExercise(const string& name);
    void deleteExercise(const string& name);
};

DoublyLinkedList::~DoublyLinkedList() {
    ExerciseNode* current = head;
    while (current != nullptr) {
        ExerciseNode* next = current->next;
        delete current;
        current = next;
    }
}

void DoublyLinkedList::insert(const Exercise& item) {
    ExerciseNode* newNode = new ExerciseNode(item);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::display() const {
    ExerciseNode* temp = head;
    while (temp != nullptr) {
        cout << temp->data.getName() << " - Duration: " << temp->data.getDuration()
             << " mins, Calories Burned: " << temp->data.getCaloriesBurned() << endl;
        temp = temp->next;
    }
}

void DoublyLinkedList::editExercise(const string& name) {
    ExerciseNode* temp = head;
    while (temp != nullptr) {
        if (temp->data.getName() == name) {
            int duration, caloriesBurned;
            cout << "Enter new duration: ";
            cin >> duration;
            cout << "Enter new calories burned: ";
            cin >> caloriesBurned;
            temp->data.setDuration(duration);
            temp->data.setCaloriesBurned(caloriesBurned);
            cout << "Exercise updated successfully." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Exercise not found." << endl;
}

void DoublyLinkedList::deleteExercise(const string& name) {
    ExerciseNode* temp = head;
    while (temp != nullptr) {
        if (temp->data.getName() == name) {
            if (temp->prev) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            } else {
                tail = temp->prev;
            }
            delete temp;
            cout << "Exercise deleted successfully." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Exercise not found." << endl;
}

// ActivityNode class definition
class ActivityNode {
public:
    Activity data;
    ActivityNode* next;
    ActivityNode(const Activity& item) : data(item), next(nullptr) {}
};

// CircularLinkedList class definition
class CircularLinkedList {
private:
    ActivityNode* tail;

public:
    CircularLinkedList() : tail(nullptr) {}
    ~CircularLinkedList();
    void insert(const Activity& item);
    void display() const;
};

CircularLinkedList::~CircularLinkedList() {
    if (tail) {
        ActivityNode* current = tail->next;
        while (current != tail) {
            ActivityNode* next = current->next;
            delete current;
            current = next;
        }
        delete tail;
    }
}

void CircularLinkedList::insert(const Activity& item) {
    ActivityNode* newNode = new ActivityNode(item);
    if (!tail) {
        tail = newNode;
        tail->next = tail;
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
}

void CircularLinkedList::display() const {
    if (!tail) return;
    ActivityNode* temp = tail->next;
    do {
        cout << temp->data.getDescription() << " on " << temp->data.getDate() << endl;
        temp = temp->next;
    } while (temp != tail->next);
}

// PriorityQueue class definition
class PriorityQueue {
private:
    priority_queue<Exercise> heap;

public:
    void push(const Exercise& item) {
        heap.push(item);
    }

    Exercise pop() {
        if (heap.empty()) {
            throw runtime_error("Priority queue is empty");
        }
        Exercise top = heap.top();
        heap.pop();
        return top;
    }

    bool isEmpty() const {
        return heap.empty();
    }

    void display() const {
        // Create a temporary copy of the heap to display its contents
        priority_queue<Exercise> tempHeap = heap;
        while (!tempHeap.empty()) {
            Exercise item = tempHeap.top();
            cout << item.getName() << " - Duration: " << item.getDuration()
                 << " mins, Calories Burned: " << item.getCaloriesBurned() << endl;
            tempHeap.pop();
        }
    }
};

// UserProfile class definition
class UserProfile {
private:
    string username;
    int dailyCalorieGoal;
    int caloriesBurnedToday;
    DoublyLinkedList exerciseHistory;
    PriorityQueue exerciseGoals;

public:
    UserProfile(string name) : username(name), dailyCalorieGoal(0), caloriesBurnedToday(0) {}

    string getUsername() const { return username; }
    void setDailyCalorieGoal(int goal) { dailyCalorieGoal = goal; }
    int getDailyCalorieGoal() const { return dailyCalorieGoal; }
    void logExercise(const Exercise& exercise) {
        exerciseHistory.insert(exercise);
        caloriesBurnedToday += exercise.getCaloriesBurned();
    }

    void addExerciseGoal(const Exercise& exercise) {
        exerciseGoals.push(exercise);
    }

    void displayHistory() const {
        exerciseHistory.display();
    }

    void displayGoals() const {
        exerciseGoals.display();
    }

    void displayProgress() const {
        cout << "Calories burned today: " << caloriesBurnedToday
             << "/" << dailyCalorieGoal << " (Goal)" << endl;
    }

    void resetDailyProgress() {
        caloriesBurnedToday = 0;
    }

    void deleteExercise(const string& name) {
        exerciseHistory.deleteExercise(name);
    }
};

// FitnessTrackerSystem class definition
class FitnessTrackerSystem {
private:
    CircularLinkedList activities; // Circular Linked List to store daily activities
    stack<Exercise> undoStack; // Stack to store undo actions
    stack<Exercise> redoStack; // Stack to store redo actions
    unordered_map<string, UserProfile*> userProfiles;
    UserProfile* currentUser;

public:
    FitnessTrackerSystem() : currentUser(nullptr) {}
    ~FitnessTrackerSystem() {
        for (auto& pair : userProfiles) {
            delete pair.second;
        }
    }

    void displayExercises() const;
    void addExercise();
    void logActivity();
    void undoAction();
    void redoAction();
    void viewPredefinedExercises() const;
    void createUserProfile(const string& username);
    void switchUser(const string& username);
    void setDailyCalorieGoal();
    void viewProgress() const;
    void resetDailyProgress();
};

void FitnessTrackerSystem::displayExercises() const {
    if (currentUser) {
        currentUser->displayHistory();
    } else {
        cout << "No user is currently logged in." << endl;
    }
}

void FitnessTrackerSystem::addExercise() {
    if (!currentUser) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    string name;
    int duration, caloriesBurned;

    cout << "Enter exercise name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter duration (in minutes): ";
    cin >> duration;
    cout << "Enter calories burned: ";
    cin >> caloriesBurned;

    Exercise exercise(name, duration, caloriesBurned);
    currentUser->logExercise(exercise);
    undoStack.push(exercise);
    while (!redoStack.empty()) {
        redoStack.pop();
    }

    cout << "Exercise added successfully." << endl;
}

void FitnessTrackerSystem::logActivity() {
    string description, date;

    cout << "Enter activity description: ";
    cin.ignore();
    getline(cin, description);
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    Activity activity(description, date);
    activities.insert(activity);

    cout << "Activity logged successfully." << endl;
}

void FitnessTrackerSystem::undoAction() {
    if (!undoStack.empty()) {
        Exercise lastExercise = undoStack.top();
        undoStack.pop();
        redoStack.push(lastExercise);
        currentUser->deleteExercise(lastExercise.getName());
        cout << "Undid the last action: " << lastExercise.getName() << " removed." << endl;
    } else {
        cout << "No actions to undo." << endl;
    }
}

void FitnessTrackerSystem::redoAction() {
    if (!redoStack.empty()) {
        Exercise lastExercise = redoStack.top();
        redoStack.pop();
        undoStack.push(lastExercise);
        currentUser->logExercise(lastExercise);
        cout << "Redid the last action: " << lastExercise.getName() << " added back." << endl;
    } else {
        cout << "No actions to redo." << endl;
    }
}

void FitnessTrackerSystem::viewPredefinedExercises() const {
    cout << "Predefined Exercises:" << endl;
    // Placeholder for predefined exercises; can be replaced with actual predefined data.
    cout << "1. Running - 30 mins, 300 calories" << endl;
    cout << "2. Cycling - 45 mins, 400 calories" << endl;
    cout << "3. Swimming - 60 mins, 500 calories" << endl;
}

void FitnessTrackerSystem::createUserProfile(const string& username) {
    if (userProfiles.find(username) != userProfiles.end()) {
        cout << "Username already exists." << endl;
    } else {
        UserProfile* profile = new UserProfile(username);
        userProfiles[username] = profile;
        currentUser = profile;
        cout << "User profile created and switched to " << username << "." << endl;
    }
}

void FitnessTrackerSystem::switchUser(const string& username) {
    auto it = userProfiles.find(username);
    if (it != userProfiles.end()) {
        currentUser = it->second;
        cout << "Switched to user " << username << "." << endl;
    } else {
        cout << "User profile not found." << endl;
    }
}

void FitnessTrackerSystem::setDailyCalorieGoal() {
    if (!currentUser) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    int goal;
    cout << "Enter daily calorie goal: ";
    cin >> goal;
    currentUser->setDailyCalorieGoal(goal);
    cout << "Daily calorie goal set to " << goal << " calories." << endl;
}

void FitnessTrackerSystem::viewProgress() const {
    if (currentUser) {
        currentUser->displayProgress();
    } else {
        cout << "No user is currently logged in." << endl;
    }
}

void FitnessTrackerSystem::resetDailyProgress() {
    if (currentUser) {
        currentUser->resetDailyProgress();
        cout << "Daily progress reset." << endl;
    } else {
        cout << "No user is currently logged in." << endl;
    }
}

int main() {
    FitnessTrackerSystem system;

    int choice;
    do {
        cout << "\nFitness Tracker System Menu:\n";
        cout << "1. Display Exercises\n";
        cout << "2. Add Exercise\n";
        cout << "3. Log Activity\n";
        cout << "4. Undo Action\n";
        cout << "5. Redo Action\n";
        cout << "6. View Predefined Exercises\n";
        cout << "7. Create User Profile\n";
        cout << "8. Switch User\n";
        cout << "9. Set Daily Calorie Goal\n";
        cout << "10. View Progress\n";
        cout << "11. Reset Daily Progress\n";
        cout << "12. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayExercises();
                break;
            case 2:
                system.addExercise();
                break;
            case 3:
                system.logActivity();
                break;
            case 4:
                system.undoAction();
                break;
            case 5:
                system.redoAction();
                break;
            case 6:
                system.viewPredefinedExercises();
                break;
            case 7: {
                string username;
                cout << "Enter new username: ";
                cin >> username;
                system.createUserProfile(username);
                break;
            }
            case 8: {
                string username;
                cout << "Enter username to switch: ";
                cin >> username;
                system.switchUser(username);
                break;
            }
            case 9:
                system.setDailyCalorieGoal();
                break;
            case 10:
                system.viewProgress();
                break;
            case 11:
                system.resetDailyProgress();
                break;
            case 12:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}