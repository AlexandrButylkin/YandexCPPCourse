#include "ReadingManager.h"

void ReadingManager::Read(int user_id, int page_count) {
    UpdatePages(users_page_count_[user_id] + 1, page_count + 1);
    users_page_count_[user_id] = page_count;
}

double ReadingManager::Cheer(int user_id) {
    const int pages_count = users_page_count_[user_id];
    if(pages_count == -1){
        return 0;
    }

    const int user_count = pages_users_counts[0];
    if(user_count == 1){
        return 1;
    } else {
        return (user_count - pages_users_counts[pages_count]) * 1.0
               / (user_count - 1);
    }
}

void ReadingManager::UpdatePages(size_t start_page, size_t end_page){
    for(size_t i = start_page; i < end_page; ++i){
        ++pages_users_counts[i];
    }
}