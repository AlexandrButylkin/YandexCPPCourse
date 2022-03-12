#include "TaskTracker.h"

TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

void RemoveZeros(TasksInfo &tasks_info) {
    auto beg = tasks_info.begin();
    auto end = tasks_info.end();

    while (beg != end) {
        if (beg->second == 0) {
            beg = tasks_info.erase(beg);
        } else {
            ++beg;
        }
    }
}


const TasksInfo& TeamTasks::GetPersonTasksInfo(const std::string &person) const {
    return data.at(person);
}

void TeamTasks::AddNewTask(const std::string &person) {
    ++data[person][TaskStatus::NEW];
}

std::tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const std::string &person, int task_count) {

    TasksInfo updated_tasks, untouched_tasks;
    TasksInfo& tasks = data[person];

    for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
        updated_tasks[Next(status)] = std::min(task_count, tasks[status]);
        task_count -= updated_tasks[Next(status)];
    }

    for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
        untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
        tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
    }
    tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

    RemoveZeros(updated_tasks);
    RemoveZeros(untouched_tasks);
    RemoveZeros(data.at(person));

    return {updated_tasks, untouched_tasks};

}