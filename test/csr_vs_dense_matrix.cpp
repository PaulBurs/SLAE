#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <memory>
#include "../include/dense_matrix.hpp"
#include "../include/csr_matrix.hpp"

using namespace std;

// Функция для генерации CSR матрицы без промежуточного map
csr_matrix<double> generate_csr(int n, double density, mt19937& gen, uniform_real_distribution<double>& dist) {
    map<pair<size_t, size_t>, double> dok;
    const int target_nonzero = max(1, static_cast<int>(n*n*density));

    // Гарантируем генерацию ровно target_nonzero элементов
    while(dok.size() < static_cast<size_t>(target_nonzero)) {
        size_t row = gen() % n;
        size_t col = gen() % n;
        dok[{col, row}] = dist(gen);  // Обратите внимание на порядок (col, row)
    }

    return csr_matrix<double>(n, n, dok);
}

int main() {
    ofstream outfile("./data.txt");
    if (!outfile.is_open()) {
        cerr << "File error!" << endl;
        return 1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist_val(0.0, 1.0);

    vector<int> sizes;
    for(int n = 50; n <= 1000; n += 50) {
        sizes.push_back(n);
    }

    vector<double> densities = {0.01, 0.05, 0.1, 0.2, 0.5, 1.0};

    outfile << "MatrixType,Size,Density,NonZero,TimeMicrosec,Iterations\n";

    // ======== Dense Matrix ========
    for(int n : sizes) {
        // Генерация данных построчно с немедленным использованием
        unique_ptr<dense_matrix<double>> dense;
        {
            vector<vector<double>> data;
            data.reserve(n);
            for(int i = 0; i < n; ++i) {
                data.emplace_back(n);
                generate(data.back().begin(), data.back().end(), [&]() { return dist_val(gen); });
            }
            dense = make_unique<dense_matrix<double>>(n, n, data);
        } // data уничтожается здесь

        vector<double> vec(n);
        generate(vec.begin(), vec.end(), [&]() { return dist_val(gen); });

        int iterations = max(1, 1000/n);
        auto start = chrono::high_resolution_clock::now();
        for(int k = 0; k < iterations; ++k) {
            volatile auto result = *dense * vec;
        }
        auto duration = chrono::duration_cast<chrono::microseconds>(
            chrono::high_resolution_clock::now() - start).count();

        outfile << "Dense," << n << ",1.0," << n*n << ","
                << duration << "," << iterations << "\n";

        cout << "dense_matrix " << n << "x" << n << " - done." << endl;
    }

    // ======== CSR Matrix ========
    for(int n : sizes) {
        for(double density : densities) {
            auto csr = generate_csr(n, density, gen, dist_val);

            vector<double> vec(n);
            generate(vec.begin(), vec.end(), [&]() { return dist_val(gen); });

            int iterations = max(1, 1000/n);
            auto start = chrono::high_resolution_clock::now();
            for(int k = 0; k < iterations; ++k) {
                volatile auto result = csr * vec;
            }
            auto duration = chrono::duration_cast<chrono::microseconds>(
                chrono::high_resolution_clock::now() - start).count();

            outfile << "CSR," << n << "," << density << ","
                    << csr.get_size_x() * csr.get_size_y() * density << ","
                    << duration << "," << iterations << "\n";

            cout << "csr_matrix " << n << "x" << n
                 << " (density = " << density << ") - done." << endl;
        }
    }

    outfile.close();
    cout << "Benchmark completed. Results saved to ./data.txt" << endl;
    return 0;
}
