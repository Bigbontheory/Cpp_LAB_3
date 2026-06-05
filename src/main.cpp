#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include "TriangleMatrix.hpp"
#include "DiagonalMatrix.hpp"
#include "SparseMatrix.hpp"
#include "DynamicArray.hpp"
#include "Vector.hpp"

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

void fillStandardMatrix(IMatrix<double>* mat) {
    std::cout << "Enter values:\n";
    for (int i = 0; i < mat->get_rows(); ++i) {
        for (int j = 0; j < mat->get_cols(); ++j) {
            double val;
            std::cout << "  [" << i << "][" << j << "]: ";
            std::cin >> val;
            mat->set(i, j, val);
        }
    }
}

void fillSparseMatrix(IMatrix<double>* mat) {
    int nz_count;
    std::cout << "Enter number of non-zero elements: ";
    std::cin >> nz_count;
    std::cout << "Enter [row] [col] [value] for each element:\n";
    for (int k = 0; k < nz_count; ++k) {
        int r, c;
        double val;
        std::cout << "  Element " << k + 1 << ": ";
        std::cin >> r >> c >> val;
        mat->set(r, c, val);
    }
}

void handleCreateMatrix(DynamicArray<IMatrix<double>*>& storage, DynamicArray<std::string>& matrixTypes) {
    int type;
    std::cout << "Select Type (1:General, 2:Square, 3:Triangle, 4:Diagonal, 5:Sparse): ";
    std::cin >> type;

    IMatrix<double>* newMat = nullptr;
    std::string typeName = "Unknown";

    if (type == 1) {
        int n, m;
        std::cout << "Rows & Cols: "; std::cin >> n >> m;
        newMat = new Matrix<double>(n, m);
        typeName = "General";
        fillStandardMatrix(newMat);
    }
    else if (type == 2) {
        int n;
        std::cout << "Size: "; std::cin >> n;
        newMat = new SquareMatrix<double>(n);
        typeName = "Square";
        fillStandardMatrix(newMat);
    }
    else if (type == 3) {
        int n, t;
        std::cout << "Size: "; std::cin >> n;
        std::cout << "Select subtype (0:Lower, 1:Upper): "; std::cin >> t;

        if (t == 0) {
            newMat = new TriangleMatrix<double>(n, TriangleMatrix<double>::TriangleType::Lower);
            typeName = "TriangleLower";
        }
        else {
            newMat = new TriangleMatrix<double>(n, TriangleMatrix<double>::TriangleType::Upper);
            typeName = "TriangleUpper";
        }
        fillStandardMatrix(newMat);
    }
    else if (type == 4) {
        int n;
        std::cout << "Size: "; std::cin >> n;
        newMat = new DiagonalMatrix<double>(n);
        typeName = "Diagonal";
        fillStandardMatrix(newMat);
    }
    else if (type == 5) {
        int n, m;
        std::cout << "Rows & Cols: "; std::cin >> n >> m;
        newMat = new SparseMatrix<double>(n, m);
        typeName = "Sparse";
        fillSparseMatrix(newMat);
    }

    if (newMat) {
        int idx = storage.get_size();
        storage.resize(idx + 1);
        storage.set(idx, newMat);

        matrixTypes.resize(idx + 1);
        matrixTypes.set(idx, typeName);

        std::cout << "Matrix added with ID: " << idx << " (" << typeName << ")\n";
    }
}

void handleViewMatrix(const DynamicArray<IMatrix<double>*>& storage) {
    int id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    if (id >= 0 && id < storage.get_size() && storage.get(id) != nullptr) {
        printAnyMatrix(storage.get(id), id);
    }
    else {
        std::cout << "Invalid ID or matrix deleted!\n";
    }
}

void handleCommonOperations(DynamicArray<IMatrix<double>*>& storage, DynamicArray<std::string>& matrixTypes) {
    int id1;
    std::cout << "Enter ID: ";
    std::cin >> id1;
    if (id1 < 0 || id1 >= storage.get_size() || storage.get(id1) == nullptr) {
        std::cout << "Invalid ID!\n";
        return;
    }

    IMatrix<double>* m = storage.get(id1);
    int op;
    std::cout << "1: Add, 2: Mult Scalar, 3: Norm: ";
    std::cin >> op;

    if (op == 1) {
        int id2;
        std::cout << "Enter second ID: ";
        std::cin >> id2;
        if (id2 < 0 || id2 >= storage.get_size() || storage.get(id2) == nullptr) {
            std::cout << "Invalid second ID!\n";
            return;
        }

        IMatrix<double>* res = m->add(storage.get(id2));
        int idx = storage.get_size();
        storage.resize(idx + 1);
        storage.set(idx, res);

        matrixTypes.resize(idx + 1);
        matrixTypes.set(idx, "GeneralResult");

        std::cout << "Result saved as ID: " << idx << "\n";
    }
    else if (op == 2) {
        double s;
        std::cout << "Scalar: ";
        std::cin >> s;
        IMatrix<double>* res = m->mult_scalar(s);
        int idx = storage.get_size();
        storage.resize(idx + 1);
        storage.set(idx, res);

        matrixTypes.resize(idx + 1);
        matrixTypes.set(idx, matrixTypes.get(id1));

        std::cout << "Result saved as ID: " << idx << "\n";
    }
    else if (op == 3) {
        std::cout << "Norm: " << m->norm() << "\n";
    }
}

void handleSpecificOperations(DynamicArray<IMatrix<double>*>& storage, const DynamicArray<std::string>& matrixTypes) {
    int id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    if (id < 0 || id >= storage.get_size() || storage.get(id) == nullptr) {
        std::cout << "Invalid ID!\n";
        return;
    }

    IMatrix<double>* m = storage.get(id);
    std::string currentType = matrixTypes.get(id);

    if (currentType == "General") {
        Matrix<double>* gen = static_cast<Matrix<double>*>(m);
        int rowOp;
        std::cout << "Row Ops (1:Swap, 2:Scale, 3:AddRow, 0:Skip): ";
        std::cin >> rowOp;
        if (rowOp == 1) { int r1, r2; std::cin >> r1 >> r2; gen->swap_rows(r1, r2); }
        else if (rowOp == 2) { int r; double s; std::cin >> r >> s; gen->scale_row(r, s); }
        else if (rowOp == 3) { int r1, r2; double s; std::cin >> r1 >> r2 >> s; gen->add_row(r1, r2, s); }
    }
    else if (currentType == "Square") {
        SquareMatrix<double>* sq = static_cast<SquareMatrix<double>*>(m);
        std::cout << "Trace: " << sq->trace() << "\n";
    }
    else if (currentType == "TriangleLower") {
        std::cout << "Triangle Type: Lower\n";
    }
    else if (currentType == "TriangleUpper") {
        std::cout << "Triangle Type: Upper\n";
    }
    else if (currentType == "Diagonal") {
        DiagonalMatrix<double>* diag = static_cast<DiagonalMatrix<double>*>(m);
        std::cout << "Diagonal Size: " << diag->get_size() << "\n";
    }
    else if (currentType == "Sparse") {
        SparseMatrix<double>* sparse = static_cast<SparseMatrix<double>*>(m);
        std::cout << "Sparse Matrix stored elements (non-zero): " << sparse->get_data_size() << "\n";
    }
    else {
        std::cout << "No specific operations for this matrix type.\n";
    }
}

void handleDeleteMatrix(DynamicArray<IMatrix<double>*>& storage) {
    int id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    if (id >= 0 && id < storage.get_size() && storage.get(id) != nullptr) {
        delete storage.get(id);
        storage.set(id, nullptr);
        std::cout << "Memory cleared.\n";
    }
    else {
        std::cout << "Invalid ID or already deleted.\n";
    }
}

void handleCreateVector(DynamicArray<Vector<double>*>& vecStorage) {
    int n;
    std::cout << "Enter Vector size: ";
    std::cin >> n;

    Vector<double>* newVec = new Vector<double>(n);
    std::cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i) {
        double val;
        std::cout << "  [" << i << "]: ";
        std::cin >> val;
        newVec->set(val, i);
    }

    int idx = vecStorage.get_size();
    vecStorage.resize(idx + 1);
    vecStorage.set(idx, newVec);
    std::cout << "Vector added with ID: " << idx << "\n";
}

void handleViewVector(const DynamicArray<Vector<double>*>& vecStorage) {
    int id;
    std::cout << "Enter Vector ID: ";
    std::cin >> id;
    if (id >= 0 && id < vecStorage.get_size() && vecStorage.get(id) != nullptr) {
        Vector<double>* v = vecStorage.get(id);
        std::cout << "\n[Vector ID: " << id << "] Size: " << v->get_size() << "\n[ ";
        for (int i = 0; i < v->get_size(); ++i) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << v->get(i) << " ";
        }
        std::cout << "]\n";
    }
    else {
        std::cout << "Invalid Vector ID or vector deleted!\n";
    }
}

void handleVectorOperations(DynamicArray<Vector<double>*>& vecStorage) {
    int id1;
    std::cout << "Enter Vector ID: ";
    std::cin >> id1;
    if (id1 < 0 || id1 >= vecStorage.get_size() || vecStorage.get(id1) == nullptr) {
        std::cout << "Invalid ID!\n";
        return;
    }

    Vector<double>* v1 = vecStorage.get(id1);
    int op;
    std::cout << "1: Add, 2: Subtract, 3: Mult Scalar, 4: Dot Product, 5: Norm: ";
    std::cin >> op;

    if (op == 1 || op == 2 || op == 4) {
        int id2;
        std::cout << "Enter second Vector ID: ";
        std::cin >> id2;
        if (id2 < 0 || id2 >= vecStorage.get_size() || vecStorage.get(id2) == nullptr) {
            std::cout << "Invalid second ID!\n";
            return;
        }
        Vector<double>* v2 = vecStorage.get(id2);

        if (op == 1) {
            Vector<double>* res = new Vector<double>(*v1 + *v2);
            int idx = vecStorage.get_size();
            vecStorage.resize(idx + 1);
            vecStorage.set(idx, res);
            std::cout << "Result saved as Vector ID: " << idx << "\n";
        }
        else if (op == 2) {
            Vector<double>* res = new Vector<double>(*v1 - *v2);
            int idx = vecStorage.get_size();
            vecStorage.resize(idx + 1);
            vecStorage.set(idx, res);
            std::cout << "Result saved as Vector ID: " << idx << "\n";
        }
        else if (op == 4) {
            std::cout << "Dot Product: " << v1->dot(*v2) << "\n";
        }
    }
    else if (op == 3) {
        double s;
        std::cout << "Scalar: ";
        std::cin >> s;
        Vector<double>* res = new Vector<double>(*v1 * s);
        int idx = vecStorage.get_size();
        vecStorage.resize(idx + 1);
        vecStorage.set(idx, res);
        std::cout << "Result saved as Vector ID: " << idx << "\n";
    }
    else if (op == 5) {
        std::cout << "Norm: " << v1->norm() << "\n";
    }
}

void handleDeleteVector(DynamicArray<Vector<double>*>& vecStorage) {
    int id;
    std::cout << "Enter Vector ID: ";
    std::cin >> id;
    if (id >= 0 && id < vecStorage.get_size() && vecStorage.get(id) != nullptr) {
        delete vecStorage.get(id);
        vecStorage.set(id, nullptr);
        std::cout << "Vector memory cleared.\n";
    }
    else {
        std::cout << "Invalid ID or already deleted.\n";
    }
}

void printMenu(int matrixCount, int vectorCount) {
    std::cout << "\n=== MATRIX & VECTOR UI (Matrices: " << matrixCount << ", Vectors: " << vectorCount << ") ===\n";
    std::cout << "--- Matrices ---\n";
    std::cout << "1. Create Matrix\n";
    std::cout << "2. View Matrix by ID\n";
    std::cout << "3. Common Matrix Operations (Add, Mult Scalar, Norm)\n";
    std::cout << "4. Specific Matrix Operations\n";
    std::cout << "5. Delete Matrix\n";
    std::cout << "--- Vectors ---\n";
    std::cout << "6. Create Vector\n";
    std::cout << "7. View Vector by ID\n";
    std::cout << "8. Vector Operations (Add, Sub, Mult Scalar, Dot, Norm)\n";
    std::cout << "9. Delete Vector\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    DynamicArray<IMatrix<double>*> storage;
    DynamicArray<std::string> matrixTypes;
    DynamicArray<Vector<double>*> vectorStorage;
    int choice = -1;

    while (choice != 0) {
        printMenu(storage.get_size(), vectorStorage.get_size());
        if (!(std::cin >> choice)) break;

        try {
            switch (choice) {
            case 1: handleCreateMatrix(storage, matrixTypes); break;
            case 2: handleViewMatrix(storage); break;
            case 3: handleCommonOperations(storage, matrixTypes); break;
            case 4: handleSpecificOperations(storage, matrixTypes); break;
            case 5: handleDeleteMatrix(storage); break;
            case 6: handleCreateVector(vectorStorage); break;
            case 7: handleViewVector(vectorStorage); break;
            case 8: handleVectorOperations(vectorStorage); break;
            case 9: handleDeleteVector(vectorStorage); break;
            case 0: break;
            default: std::cout << "Unknown choice!\n"; break;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Runtime Error: " << e.what() << "\n";
        }
    }

    for (int i = 0; i < storage.get_size(); ++i) {
        delete storage.get(i);
    }

    for (int i = 0; i < vectorStorage.get_size(); ++i) {
        delete vectorStorage.get(i);
    }

    return 0;
}