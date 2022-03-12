#include <iostream>
#include "TaskTracker.h"


using namespace std;

int main() {

    std::cout << "............................ Test 1 ............................\n\n";

    {
        auto PrintTasksInfo = [](TasksInfo tasks_info){
            cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
                 ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
                 ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
                 ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
        };

        TeamTasks tasks;
        tasks.AddNewTask("Ilia");
        for (int i = 0; i < 3; ++i) {
            tasks.AddNewTask("Ivan");
        }
        cout << "Ilia's tasks: ";
        PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
        cout << "Ivan's tasks: ";
        PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

        TasksInfo updated_tasks, untouched_tasks;

        tie(updated_tasks, untouched_tasks) =
                tasks.PerformPersonTasks("Ivan", 2);
        cout << "Updated Ivan's tasks: ";
        PrintTasksInfo(updated_tasks);
        cout << "Untouched Ivan's tasks: ";
        PrintTasksInfo(untouched_tasks);

        tie(updated_tasks, untouched_tasks) =
                tasks.PerformPersonTasks("Ivan", 2);
        cout << "Updated Ivan's tasks: ";
        PrintTasksInfo(updated_tasks);
        cout << "Untouched Ivan's tasks: ";
        PrintTasksInfo(untouched_tasks);
    }

    std::cout << "\n\n............................ Test 2 ............................\n\n";

    {
        auto PrintTasksInfo = [](const TasksInfo &tasks_info){
            if (tasks_info.count(TaskStatus::NEW)) {
                std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
            }
            if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
                std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
            }
            if (tasks_info.count(TaskStatus::TESTING)) {
                std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
            }
            if (tasks_info.count(TaskStatus::DONE)) {
                std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
            }
        };

        auto PrintCurrTasksInfo = [&PrintTasksInfo](const TasksInfo &updated_tasks, const TasksInfo &untouched_tasks){
            std::cout << "Updated: [";
            PrintTasksInfo(updated_tasks);
            std::cout << "] ";

            std::cout << "Untouched: [";
            PrintTasksInfo(untouched_tasks);
            std::cout << "] ";

            std::cout << std::endl;
        };

        TeamTasks tasks;
        TasksInfo updated_tasks;
        TasksInfo untouched_tasks;

        std::cout << "Alice" << std::endl;

        for (auto i = 0; i < 5; ++i) {
            tasks.AddNewTask("Alice");
        }
        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

        for (auto i = 0; i < 5; ++i) {
            tasks.AddNewTask("Alice");
        }
        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
                                                                       2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);

        PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
        PrintCurrTasksInfo(updated_tasks,
                           untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
        std::cout << std::endl;

        std::cout << "\nJack" << std::endl;

        tasks.AddNewTask("Jack");

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

        tasks.AddNewTask("Jack");

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

        tasks.AddNewTask("Jack");

        PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
        std::cout << std::endl;

        std::cout << "\nLisa" << std::endl;

        for (auto i = 0; i < 5; ++i) {
            tasks.AddNewTask("Lisa");
        }

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

        for (auto i = 0; i < 5; ++i) {
            tasks.AddNewTask("Lisa");
        }

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
        PrintCurrTasksInfo(updated_tasks,
                           untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
        std::cout << std::endl;

        tasks.AddNewTask("Lisa");

        PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

        PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
        std::cout << std::endl;

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
        PrintCurrTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]
    }

    return 0;
}
