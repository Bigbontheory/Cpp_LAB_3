#include <iostream>
#include <iomanip>
#include <string>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include "TriangleMatrix.hpp"
#include "DiagonalMatrix.hpp"
#include "DynamicArray.hpp"

void printAnyMatrix(const IMatrix<double>* mat, int id) {
    if (!mat) return;
    std::cout << "\n[ID: " << id << "] Size: " << mat->get_rows() << "x" << mat->get_cols() << "\n";
    for (int i = 0; i < mat->get_rows(); ++i) {
        for (int j = 0; j < mat->get_cols(); ++j) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << mat->get(i, j) << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    // Хранилище указателей на матрицы (используем твой DynamicArray)
    DynamicArray<IMatrix<double>*> storage;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n=== MATRIX UI (Count: " << storage.get_size() << ") ===\n";
        std::cout << "1. Create Matrix (General, Square, Triangle, Diagonal)\n";
        std::cout << "2. View Matrix by ID\n";
        std::cout << "3. Common Operations (Add, Mult Scalar, Norm)\n";
        std::cout << "4. Specific Operations (Row Ops, Trace, Type)\n";
        std::cout << "5. Delete Matrix\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) break;

        try {
            switch (choice) {
            case 1: { // СОЗДАНИЕ
                int type, n, m;
                std::cout << "Select Type (1:Gen, 2:Sq, 3:Tri, 4:Diag): ";
                std::cin >> type;

                IMatrix<double>* newMat = nullptr;
                if (type == 1) {
                    std::cout << "Rows & Cols: "; std::cin >> n >> m;
                    newMat = new Matrix<double>(n, m);
                }
                else if (type == 2) {
                    std::cout << "Size: "; std::cin >> n;
                    newMat = new SquareMatrix<double>(n);
                }
                else if (type == 3) {
                    int t; std::cout << "Size: "; std::cin >> n;
                    std::cout << "0:Lower, 1:Upper: "; std::cin >> t;
                    newMat = new TriangleMatrix<double>(n, (t == 0 ? TriangleType::Lower : TriangleType::Upper));
                }
                else if (type == 4) {
                    std::cout << "Size: "; std::cin >> n;
                    newMat = new DiagonalMatrix<double>(n);
                }

                if (newMat) {
                    std::cout << "Enter values:\n";
                    for (int i = 0; i < newMat->get_rows(); ++i) {
                        for (int j = 0; j < newMat->get_cols(); ++j) {
                            double val;
                            std::cout << "  [" << i << "][" << j << "]: "; std::cin >> val;
                            newMat->set(i, j, val);
                        }
                    }
                    int idx = storage.get_size();
                    storage.resize(idx + 1);
                    storage.set(idx, newMat);
                    std::cout << "Matrix added with ID: " << idx << "\n";
                }
                break;
            }

            case 2: { // ПРОСМОТР
                int id; std::cout << "Enter ID: "; std::cin >> id;
                if (id >= 0 && id < storage.get_size()) printAnyMatrix(storage.get(id), id);
                else std::cout << "Invalid ID!\n";
                break;
            }

            case 3: { // ОБЩИЕ ОПЕРАЦИИ (есть у всех через IMatrix)
                int id1; std::cout << "Enter ID: "; std::cin >> id1;
                IMatrix<double>* m = storage.get(id1);

                int op; std::cout << "1: Add, 2: Mult Scalar, 3: Norm: "; std::cin >> op;
                if (op == 1) {
                    int id2; std::cout << "Enter second ID: "; std::cin >> id2;
                    IMatrix<double>* res = m->add(storage.get(id2));
                    int idx = storage.get_size();
                    storage.resize(idx + 1);
                    storage.set(idx, res);
                    std::cout << "Result saved as ID: " << idx << "\n";
                }
                else if (op == 2) {
                    double s; std::cout << "Scalar: "; std::cin >> s;
                    IMatrix<double>* res = m->mult_scalar(s);
                    int idx = storage.get_size();
                    storage.resize(idx + 1);
                    storage.set(idx, res);
                    std::cout << "Result saved as ID: " << idx << "\n";
                }
                else if (op == 3) {
                    std::cout << "Norm: " << m->norm() << "\n";
                }
                break;
            }

            case 4: { // СПЕЦИФИЧНЫЕ ОПЕРАЦИИ (только то, что есть в .hpp)
                int id; std::cout << "Enter ID: "; std::cin >> id;
                IMatrix<double>* m = storage.get(id);

                // 1. Проверка на Matrix (включая SquareMatrix) для Row Ops
                auto* gen = dynamic_cast<Matrix<double>*>(m);
                if (gen) {
                    int rowOp; std::cout << "Row Ops (1:Swap, 2:Scale, 3:AddRow, 0:Skip): "; std::cin >> rowOp;
                    if (rowOp == 1) { int r1, r2; std::cin >> r1 >> r2; gen->swap_rows(r1, r2); }
                    else if (rowOp == 2) { int r; double s; std::cin >> r >> s; gen->scale_row(r, s); }
                    else if (rowOp == 3) { int r1, r2; double s; std::cin >> r1 >> r2 >> s; gen->add_row(r1, r2, s); }
                }

                // 2. Проверка на SquareMatrix для trace()
                auto* sq = dynamic_cast<SquareMatrix<double>*>(m);
                if (sq) std::cout << "Trace: " << sq->trace() << "\n";

                // 3. Проверка на TriangleMatrix для get_type()
                auto* tri = dynamic_cast<TriangleMatrix<double>*>(m);
                if (tri) std::cout << "Triangle Type: " << (tri->get_type() == TriangleType::Lower ? "Lower" : "Upper") << "\n";

                // 4. Проверка на DiagonalMatrix (у неё только get_size)
                auto* diag = dynamic_cast<DiagonalMatrix<double>*>(m);
                if (diag) std::cout << "Diagonal Size: " << diag->get_size() << "\n";

                break;
            }

            case 5: { // УДАЛЕНИЕ
                int id; std::cout << "Enter ID: "; std::cin >> id;
                if (id >= 0 && id < storage.get_size()) {
                    delete storage.get(id);
                    storage.set(id, nullptr); // Чтобы не было висячего указателя
                    std::cout << "Memory cleared.\n";
                }
                break;
            }
            }
        }
        catch (const std::exception& e) {
            std::cout << "Runtime Error: " << e.what() << "\n";
        }
    }

    // Очистка при выходе
    for (int i = 0; i < storage.get_size(); ++i) {
        delete storage.get(i);
    }
    return 0;
}