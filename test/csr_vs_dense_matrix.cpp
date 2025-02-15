#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <memory>

#include "dense_matrix.hpp"
#include "csr_matrix.hpp"

using namespace std;

// Максимальный размер матрицы
const int MAX_SIZE = 1000;

csr_matrix<double> generate_csr(int n, double density, mt19937& gen, uniform_real_distribution<double>& dist) {
    map<pair<size_t, size_t>, double> dok;
    const int target_nonzero = max(1, static_cast<int>(n*n*density));

    // Генерация только уникальных элементов
    while(dok.size() < static_cast<size_t>(target_nonzero)) {
        int row = gen() % n;
        int col = gen() % n;
        dok[{static_cast<size_t>(row), static_cast<size_t>(col)}] = dist(gen);
    }

    return csr_matrix<double>(
        static_cast<size_t>(n),
        static_cast<size_t>(n),
        dok
    );
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
    for(int n = 50; n <= MAX_SIZE; n += 50) { // Ограничение до 1000
        sizes.push_back(n);
    }

    vector<double> densities = {0.01, 0.05, 0.1, 0.2, 0.5, 1.0};

    outfile << "MatrixType,Size,Density,NonZero,TimeMicrosec,Iterations\n";

    // ======== Dense Matrix ========
    for(int n : sizes) {
        // Оптимизированное создание матрицы
        vector<double> flat_data(n*n);
        generate(flat_data.begin(), flat_data.end(), [&]() { return dist_val(gen); });
        auto dense = make_unique<dense_matrix<double>>(n, n, move(flat_data));

        vector<double> vec(n);
        generate(vec.begin(), vec.end(), [&]() { return dist_val(gen); });

        int iterations = max(1, 10000/n);
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

            int iterations = max(1, 10000/n);
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
