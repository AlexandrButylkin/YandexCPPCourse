#ifndef INC_4_TASKTRACKER_TASKTRACKER_H
#define INC_4_TASKTRACKER_TASKTRACKER_H

#include<map>
#include <vector>
#include <string>
#include <tuple>

enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

using TasksInfo = std::map<TaskStatus, int>;

TaskStatus Next(TaskStatus task_status);
void RemoveZeros(TasksInfo &tasks_info);

class TeamTasks final {
public:
    const TasksInfo &GetPersonTasksInfo(const std::string &person) const;
    void AddNewTask(const std::string &person);
    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string &person, int task_count);

private:
    std::map<std::string, TasksInfo> data;
};


#endif //INC_4_TASKTRACKER_TASKTRACKER_H
