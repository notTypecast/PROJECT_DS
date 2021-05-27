/* Accepts lambda function F
 * Runs function and times it, then returns the time (in microseconds)
 */
template <typename F, typename T>
std::time_t utils::timer::timeit(F funcToTime) {
    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    // execute desired function passed as an argument
    funcToTime();
    // stop timer
    auto stop = std::chrono::high_resolution_clock::now();
    // calculate duration, cast to microseconds
    auto duration = std::chrono::duration_cast<T>(stop-start);

    return duration.count();
}