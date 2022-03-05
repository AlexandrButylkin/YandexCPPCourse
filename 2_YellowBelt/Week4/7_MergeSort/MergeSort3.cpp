template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_begin + 1 < range_end) {

        std::vector<typename RandomIt::value_type> vec_start(
                range_begin,
                range_end
        );

        RandomIt it1 = vec_start.begin() + (vec_start.end() - vec_start.begin()) / 3;
        RandomIt it2 = it1 + (vec_start.end() - vec_start.begin()) / 3;

        MergeSort(vec_start.begin(), it1);
        MergeSort(it1, it2);

        std::vector<typename RandomIt::value_type> vec;

        std::merge(
                vec_start.begin(),
                it1,
                it1,
                it2,
                back_inserter(vec)
        );

        MergeSort(it2, vec_start.end());

        std::merge(
                vec.begin(),
                vec.end(),
                it2,
                vec_start.end(),
                range_begin
        );

    }
}