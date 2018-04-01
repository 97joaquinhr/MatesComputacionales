#include <fstream>
#include <iostream>

#include "grammar.hpp"
#include "cyk.hpp"

int main()
{
    std::string filename = "cyk.dat";
    std::ifstream ifs(filename);
    if (ifs) {
        MB::grammar grammar(ifs);
        std::string sentence[] = {"b", "a", "a", "b", "a"};
        const size_t len = sizeof(sentence) / sizeof(sentence[0]);
        bool success = MB::cyk_parser(grammar).parse(sentence, sentence + len, std::cout);
        std::cout << "Success: " << std::boolalpha << success << '\n';
    }
    else {
        std::cerr << "Couldn't open " << filename << " for reading\n";
    }
}
