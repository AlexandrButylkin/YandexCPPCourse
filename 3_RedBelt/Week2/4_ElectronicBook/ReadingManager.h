#ifndef TASK_5_READINGMANAGER_H
#define TASK_5_READINGMANAGER_H

#include <vector>
#include <map>

class ReadingManager {
public:

    ReadingManager() : users_page_count_(MAX_USER_COUNT_, -1), pages_users_counts(MAX_PAGE_COUNT_) {}

    void Read(int user_id, int page_count);
    double Cheer(int user_id);


private:
    void UpdatePages(size_t start_page, size_t end_page);

    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    std::vector<int> users_page_count_;
    std::vector<int> pages_users_counts;
};


#endif //TASK_5_READINGMANAGER_H
