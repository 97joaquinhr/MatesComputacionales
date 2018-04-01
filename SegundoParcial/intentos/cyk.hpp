#ifndef CYK_HPP
#define CYK_HPP

#include <vector>
#include <set>
#include <iostream>
#include <iterator>

#include "grammar.hpp"

namespace MB
{

class cyk_parser
{
public:
    cyk_parser(const MB::grammar& grammar)
        : grammar_(grammar)
    {
    }

    template <class InputIt>
    bool parse(InputIt begin, InputIt end)
    {
        return parse(begin, end, nullptr);
    }

    template <class InputIt>
    bool parse(InputIt begin, InputIt end, std::ostream& os)
    {
        return parse(begin, end, &os);
    }

private:
    template <class InputIt>
    bool parse(InputIt begin, InputIt end, std::ostream *os)
    {
        std::vector<std::string> str;
        std::copy(begin, end, std::back_inserter(str));
        const size_t len = str.size();
        std::vector<std::vector<std::set<std::string> > > table(len,
                std::vector<std::set<std::string> >(len));
        unsigned int i, j, k;

        // Populate main diagonal
        i = 0;
        for (const std::string& c : str) {
            std::vector<MB::rule::const_ptr> rules;
            grammar_.get_rules_for_symbol(c, std::back_inserter(rules));
            for (MB::rule::const_ptr r : rules) {
                table[i][i].insert(r->left());
            }
            i++;
        }
        // Populate upper-right triangle
        for (i = 1; i < len; i++) {
            for (j = i; j < len; j++) {
                for (k = j - i; k < j; k++) {
                    std::vector<std::pair<std::string, std::string> > product;
                    MB::detail::cartesian_product(table[j - i][k].begin(), table[j - i][k].end(),
                            table[k + 1][j].begin(),
                            table[k + 1][j].end(), std::back_inserter(product));
                    std::vector<MB::rule::const_ptr> rules;
                    grammar_.get_rules_for_symbols(product.begin(), product.end(),
                            std::back_inserter(rules));
                    for (MB::rule::const_ptr r : rules) {
                        table[j - i][j].insert(r->left());
                    }
                }
            }
        }
        if (os) {
            // Print the table
            for (i = 0; i < len; i++) {
                k = 0;
                for (j = len - i - 1; j < len; j++) {
                    std::copy(table[k][j].begin(), table[k][j].end(),
                            std::ostream_iterator<std::string>(*os, " "));
                    ++k;
                    *os << '\t';
                }
                *os << '\n';
            }
            for (const std::string& c : str) {
                *os << c << '\t';
            }
            *os << '\n';
        }

        // Successful if the start symbol is in the top-right cell
        return table[0][len - 1].find(grammar_.get_start_left()) != table[0][len - 1].end();
    }

private:
    const MB::grammar& grammar_;
};

} // namespace MB

#endif // CYK_HPP
