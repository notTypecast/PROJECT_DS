template <typename F>
std::time_t utils::timer::timeit(F funcToTime) {
    auto start = std::chrono::high_resolution_clock::now();
    funcToTime();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

    return duration.count();
}