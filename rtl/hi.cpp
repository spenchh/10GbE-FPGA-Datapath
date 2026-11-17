#include <iostream>
#include <string>

int main() {
    int a;
    std::string b_str;

    std::cout << "Enter in two nums: ";
    std::cin >> a;

    // std::ws skips the leftover newline from pressing Enter after 'a'
    std::getline(std::cin >> std::ws, b_str);
    int b = std::stoi(b_str);

    std::cout << "Here: " << a + b << '\n';

    return 0;
}
