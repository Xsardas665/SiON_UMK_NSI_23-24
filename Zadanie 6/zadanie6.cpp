#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <tuple>
#include <climits>

static inline double Func(std::string_view function, double argument){
    if (function == "sin") return sin(argument);
    if (function == "cos") return cos(argument);
    if (function == "tan") return tan(argument);
    if (function == "exp") return exp(argument);
    if (function == "log") return log(argument);
    if (function == "sqrt") return sqrt(argument);
    return 0.0;
}

std::tuple<double, double, double, std::uint32_t> Bisect(std::string_view function_name, double interval_start, double interval_stop, double delta, double epsilon, std::uint32_t max)
{
    const double ya = Func(function_name, interval_start);
    double yb = Func(function_name, interval_stop);

    if (std::signbit(ya) == std::signbit(yb)) {
        std::cout << "Error: sign(f(a)) == sign(f(b))" << "\n";
        return std::make_tuple(0.0, 0.0, 0.0, 0);
    }

    double c = 0.0;
    double yc = 0.0;
    double err = 0.0;

    for (std::uint32_t k = 1; k <= max; ++k) {
        c = interval_start + (interval_stop - interval_start) * 0.5;
        yc = Func(function_name, c);
        err = std::abs((interval_stop - interval_start) * 0.5);

        if ((err < delta) || (std::abs(yc) < epsilon)) {
            return std::make_tuple(c, err, yc, k);
        }

        if (std::signbit(yb) == std::signbit(yc)) {
            interval_stop = c;
            yb = yc;
        } else {
            interval_start = c;
        }
    }
    return std::make_tuple(c, err, yc, max);
}

int main(const int argc, const char* const* const argv)
{
    std::vector<const char*> args(argv + 1, std::next(argv, (std::ptrdiff_t)(argc)));

    const std::string_view function_name = args[0];
    const double interval_start = atof(args[1]);
    const double interval_stop = atof(args[2]);
    const double delta = atof(args[3]);
    const double epsilon = atof(args[4]);
    const std::size_t iterations_maximum = atoi(args[5]);
    const auto result = Bisect(function_name, interval_start, interval_stop, delta, epsilon, iterations_maximum);

    if (std::get<3>(result) != -1) {
        std::cout << "Root found:             " << std::get<0>(result) << "\n";
        std::cout << "Error estimate:         " << std::get<1>(result) << "\n";
        std::cout << "Function value at root: " << std::get<2>(result) << "\n";
        std::cout << "Number of iterations:   " << std::get<3>(result) << "\n";
    }

    return 0;
}