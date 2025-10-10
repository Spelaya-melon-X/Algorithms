#include <algorithm>
#include <cctype>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace lab_bigint {
class bigint {
private:
    std::vector<unsigned> digits;

    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    int get_digit(size_t i) const {
        return (i < digits.size()) ? digits[i] : 0;
    }

public:
    [[maybe_unused]] bigint(unsigned int number = 0) {
        if (number == 0) {
            digits.push_back(0);
        } else {
            while (number != 0) {
                digits.push_back(number % BASE);
                number /= BASE;
            }
        }
    }

    explicit bigint(const std::string &line) {
        for (auto it = line.rbegin(); it != line.rend(); ++it) {
            digits.push_back(*it - '0');
        }
        remove_leading_zeros();
    }

    [[nodiscard]] std::string to_string() const {
        std::string number_in_string;
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            number_in_string.push_back(static_cast<char>(*it + '0'));
        }
        return number_in_string;
    }

    explicit operator unsigned() const {
        unsigned number = 0;
        unsigned position = 1;
        for (size_t index = 0; index < digits.size(); ++index) {
            number += digits[index] * position;
            position *= BASE;
        }
        return number;
    }

    bigint operator++(int) {
        bigint old = *this;
        ++(*this);
        return old;
    }

    bigint operator--(int) {
        bigint old = *this;
        --(*this);
        return old;
    }

    bigint &operator++() {
        for (size_t index = 0; index < digits.size(); ++index) {
            if (++digits[index] < BASE) {
                return *this;
            }
            digits[index] = 0;
        }
        digits.push_back(1);
        return *this;
    }

    bigint &operator--() {
        bool borrow = true;
        for (size_t digitIndex = 0; digitIndex < digits.size() && borrow;
             ++digitIndex) {
            if (digits[digitIndex] == 0) {
                digits[digitIndex] = BASE - 1;
            } else {
                digits[digitIndex] -= 1;
                borrow = false;
            }
        }

        remove_leading_zeros();

        return *this;
    }

    friend bigint operator+(const bigint &lhs, const bigint &rhs) {
        bigint total;
        total.digits.clear();
        unsigned shift = 0;
        size_t maximum_size = std::max(lhs.digits.size(), rhs.digits.size());
        for (size_t i = 0; i < maximum_size; ++i) {
            int digit_a = lhs.get_digit(i);
            int digit_b = rhs.get_digit(i);
            unsigned sum = digit_a + digit_b + shift;
            total.digits.push_back(sum % BASE);
            shift = sum / BASE;
        }
        if (shift) {
            total.digits.push_back(shift);
        }
        return total;
    }

    friend bigint operator-(const bigint &minuend, const bigint &subtrahend) {
        bigint difference = minuend;
        [[maybe_unused]] unsigned borrowAmount = 0;
        for (size_t digitIndex = 0; digitIndex < difference.digits.size();
             ++digitIndex) {
            unsigned currentSubtrahend = (digitIndex < subtrahend.digits.size())
                                             ? subtrahend.digits[digitIndex]
                                             : 0;
            unsigned tempDifference = difference.digits[digitIndex] -
                                      currentSubtrahend - borrowAmount;

            if (tempDifference >= BASE) {
                tempDifference += BASE;
                borrowAmount = 1;
            } else {
                borrowAmount = 0;
            }
            difference.digits[digitIndex] = tempDifference;
        }

        difference.remove_leading_zeros();
        return difference;
    }

    friend bigint &operator+=(bigint &lhs, const bigint &rhs) {
        lhs = lhs + rhs;
        return lhs;
    }

    friend bigint &operator-=(bigint &lhs, const bigint &rhs) {
        lhs = lhs - rhs;
        return lhs;
    }

    friend bool operator==(const bigint &lhs, const bigint &rhs) {
        return lhs.digits == rhs.digits;
    }

    friend bool operator<(const bigint &lhs, const bigint &rhs) {
        size_t lhsLength = lhs.digits.size();
        size_t rhsLength = rhs.digits.size();

        if (lhsLength != rhsLength) {
            return lhsLength < rhsLength;
        }
        while (lhsLength--) {
            if (lhs.digits[lhsLength] != rhs.digits[lhsLength]) {
                return lhs.digits[lhsLength] < rhs.digits[lhsLength];
            }
        }
        return false;
    }

    friend bool operator>(const bigint &lhs, const bigint &rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const bigint &lhs, const bigint &rhs) {
        return !(lhs < rhs);
    }

    friend bool operator<=(const bigint &lhs, const bigint &rhs) {
        return !(lhs > rhs);
    }

    friend std::ostream &
    operator<<(std::ostream &output_stream, const bigint &big_integer) {
        for (size_t index = big_integer.digits.size(); index-- > 0;) {
            output_stream << big_integer.digits[index];
        }
        return output_stream;
    }

    friend std::istream &
    operator>>(std::istream &input_stream, bigint &number) {
        std::string input_string;
        input_stream >> input_string;
        number = bigint(input_string);
        return input_stream;
    }
};

}  // namespace lab_bigint