#include <MyList/MyList.hpp>
#include <iostream>

int main() {
    List<int> this_list;
    this_list.push_back(1337);
    this_list.push_back(1337);
    this_list.push_back(1337);
    this_list.push_back(1337);

    for (auto it = this_list.begin(); it != this_list.end(); ++it)
        std::cout << *it << " ";
}