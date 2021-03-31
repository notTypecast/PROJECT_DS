template <typename T>
void utils::swap(T &item1, T &item2) {
    T tmp = item1;
    item1 = item2;
    item2 = tmp;
}
