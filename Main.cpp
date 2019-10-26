#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Matrix.h"
#include "Vector.h"
#include "Base.h"
#include "catch.hpp"
#include "string.h"

using namespace mat_vec;
using namespace std;

TEST_CASE("Vec Constructors", "[Vector]") {
    Vector vecA(10, 3);
    Vector vecB = vecA;
    REQUIRE(vecA[2] == 3);
    REQUIRE(vecB[8] == 3);

    Vector vecC(0);
    Vector vecD = vecC;
}

TEST_CASE( "Vector test", "[Vector]" ) {
    Vector vecA(10, 3);
    vecA[3] = 8;
    REQUIRE(vecA[3] == 8);
    REQUIRE(vecA.size() == 10);

    Vector vecB(5);
    bool check1 = vecA == vecB;
    bool check2 = vecA != vecB;
    REQUIRE(check1 != check2);

    const Vector vecC(3, 3);
    const Vector vecD(3, 5);
    check1 = vecC == vecD;
    check2 = vecC != vecD;
    REQUIRE(vecC[2] == 3);
    REQUIRE(!check1);
    REQUIRE(check2);
}

TEST_CASE( "Vector normal", "[Vector]" ) {
    Vector vecA(10);
    int vecSetA[10] = {2, 4, 2, 4, 2, 4, 2, 4, 2, 4};
    for(int i = 0; i < 10; ++i)
        vecA[i] = vecSetA[i];
    REQUIRE( vecA.norm() == 10 );

    Vector vecB(10);
    double vecSetB[10] = {0.2, 0.4, 0.2, 0.4, 0.2, 0.4, 0.2, 0.4, 0.2, 0.4};
    for(int i = 0; i < 10; ++i)
        vecB[i] = vecSetB[i];
    Vector vecC = vecA.normalized();
    bool check1 = vecB == vecC;
    vecA.normalize();
    bool check2 = vecA != vecB;
    REQUIRE(check1);
    REQUIRE(!check2);
}

TEST_CASE( "Vector +-", "[Vector]" ) {
    Vector vecA(3);
    int vecSetA[3] = {2, 4, 2};
    for(int i = 0; i < 3; ++i)
        vecA[i] = vecSetA[i];


    Vector vecB(3);
    double vecSetB[3] = {4, 8, 4};
    for(int i = 0; i < 3; ++i)
        vecB[i] = vecSetB[i];

    Vector vecC = vecA;

    bool check1 = vecA + vecA == vecB;
    vecA += vecA;
    bool check2 = vecA == vecB;
    REQUIRE(check1);
    REQUIRE(check2);

    vecA -= vecB;
    check1 = vecB - vecA == vecB;
    REQUIRE(check1);
}

TEST_CASE( "Vector * / const", "[Vector]" ) {
    Vector vecA(3);
    int vecSetA[3] = {2, 4, 2};
    for(int i = 0; i < 3; ++i)
        vecA[i] = vecSetA[i];

    Vector vecC(3);

    Vector vecB(3);
    double vecSetB[3] = {4, 8, 4};
    for(int i = 0; i < 3; ++i)
        vecB[i] = vecSetB[i];

    vecC = vecA;

    bool check1 = vecA * 2 == vecB;
    bool check2 = 2 * vecA == vecB;
    REQUIRE(check1);
    REQUIRE(check2);
    vecA *= 2;
    check1 = vecA == vecB;
    REQUIRE(check1);

    check1 = vecA / 2 == vecC;
    REQUIRE(check1);
    vecA /= 2;
    check1 = vecA == vecC;
    REQUIRE(check1);
}

TEST_CASE( "Vector ^ Vector", "[Vector]" ) {
    Vector vecA(3);
    int vecSetA[3] = {2, 4, 2};
    for(int i = 0; i < 3; ++i)
        vecA[i] = vecSetA[i];

    Vector vecB(3);
    double vecSetB[3] = {2, 1, 2};
    for(int i = 0; i < 3; ++i)
        vecB[i] = vecSetB[i];

    Vector vecC(3, 4);

    bool check1 = (vecA ^ vecB) == vecC;
    REQUIRE(check1);
    vecA ^= vecB;
    check1 = vecA == vecC;
    REQUIRE(check1);
}

TEST_CASE( "Vector * Vector", "[Vector]" ) {
    Vector vecA(3);
    int vecSetA[3] = {2, 4, 2};
    for(int i = 0; i < 3; ++i)
        vecA[i] = vecSetA[i];

    Vector vecB(3);
    double vecSetB[3] = {2, 1, 2};
    for(int i = 0; i < 3; ++i)
        vecB[i] = vecSetB[i];

    REQUIRE((vecA * vecB) == 12);
}

TEST_CASE("Mat Constructors", "[Matrix]") {
    Matrix MatA(10, 10, 3);
    Matrix MatB = MatA;
    Matrix MatC(3);
    REQUIRE(MatA[2] == 3);
    REQUIRE(MatB[8] == 3);

    Matrix MatD(0);
    Matrix MatE = MatD;
    Matrix MatF(0, 0, 3);
}

TEST_CASE( "Determinant test0", "[Matrix]" ) {
    Matrix matA(2);
    int matSet[4] = {4, 8, 2, 3};
    for(int i = 0; i < 4; ++i)
        matA[i] = matSet[i];
    REQUIRE( matA.det() == -4 );
}

TEST_CASE( "Determinant test1", "[Matrix]" ) {
    Matrix matA(5);
    int matSet[25] = {1,2,3,4,5, 3,4,5,6,7, 5,6,7,8,9, 7,8,9,10,11, 9,10,11,12,13};
    for(int i = 0; i < 25; ++i)
        matA[i] = matSet[i];
    REQUIRE( matA.det() == 0);
}

TEST_CASE( "Matrix const op + -", "[Matrix]") {
    Matrix matA(2);
    int ASet[4] = {1, 0, 0, 1};
    for(int i = 0; i < 4; ++i)
        matA[i] = ASet[i];

    Matrix matB(2);
    int BSet[4] = {4, 8, 2, 3};
    for(int i = 0; i < 4; ++i)
        matB[i] = BSet[i];

    Matrix matC = matA + matB;

    bool check = matC == matA;
    REQUIRE(!check);

    matA += matB;
    REQUIRE( matA[0] == 5);
    REQUIRE( matA[1] == 8);
    REQUIRE( matA[2] == 2);
    REQUIRE( matA[3] == 4);

    check = matC != matA;
    REQUIRE(!check);

    matA -= matC;
    Matrix matD(2);

    check = matA == matD;
    REQUIRE(check);
}

TEST_CASE( "Matrix create", "[Matrix]") {
    Matrix matA(2, 3, 0);
    int ASet[6] = {1, 0, 0, 1, 1, 0};
    for(int i = 0; i < 6; ++i)
        matA[i] = ASet[i];

    Matrix matB(3, 2, 0);
    int BSet[6] = {1, 0, 1, 0, 1, 0};
    for(int i = 0; i < 6; ++i)
        matB[i] = BSet[i];

    bool check1 = matA == matB;
    bool check2 = matA != matB;
    REQUIRE(check1 != check2);

    Matrix matC = matB;
    Matrix matD(3);
    matD = matD.eye(3);

    matA.reshape(3, 2);

    check1 = matB == matC;
    check2 = matA != matC;
    REQUIRE(check1 == check2);

    const Matrix matE(3);
    double EElem = matE[5];
    REQUIRE(EElem == 0);
}

TEST_CASE( "Matrix Const op * /", "[Matrix]") {
    Matrix matA(2, 3, 0);
    int ASet[6] = {1, 0, 1, 2, 2, 0};
    for(int i = 0; i < 6; ++i)
        matA[i] = ASet[i];

    Matrix matB(2, 3, 0);
    int BSet[6] = {1, 0, 1, 0, 1, 0};
    for(int i = 0; i < 6; ++i)
        matB[i] = BSet[i];

    Matrix matC(2, 3, 0);
    int CSet[6] = {0, 0, 0, 2, 1, 0};
    for(int i = 0; i < 6; ++i)
        matC[i] = CSet[i];

    bool check1 = matA - matB == matC;
    matA -= matB;
    bool check2 = matA == matC;
    REQUIRE(check1 == check2);

    Matrix matD(7);
    matD = matC;
    matD *= 2;
    Matrix matG = matC;
    matG = matC * 2;
    check1 = (matD == matG);
    REQUIRE(check1);
    matG /= 2;
    matC = matD / 2;
    check2 = (matG == matC);
    REQUIRE(check2);
}

TEST_CASE( "Matrix Reshape transpose", "[Matrix]") {
    Matrix matA(2, 3, 0);
    int ASet[6] = {1, 0, 0, 1, 1, 0};
    for(int i = 0; i < 6; ++i)
        matA[i] = ASet[i];

    Matrix matB(3, 2, 0);
    int BSet[6] = {1, 0, 0, 1, 1, 0};
    for(int i = 0; i < 6; ++i)
        matB[i] = BSet[i];

    matB.reshape(2, 3);

    bool check1 = matA == matB;
    REQUIRE(check1);

    Matrix matC(3, 3, 0);
    int Cset[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    for(int i = 0; i < 9; ++i)
        matC[i] = Cset[i];

    Matrix matD = matC.transposed();

    bool check2 = matD == matC;
    REQUIRE(check2);
}

TEST_CASE( "Matrix Transpose", "[Matrix]") {
    Matrix matA(2, 3, 0);
    int ASet[6] = {1, 0, 0, 1, 1, 0};
    for (int i = 0; i < 6; ++i)
        matA[i] = ASet[i];

    Matrix matB(2, 3, 0);
    int BSet[6] = {1, 0, 1, 0, 1, 0};
    for (int i = 0; i < 6; ++i)
        matB[i] = BSet[i];

    matB.transpose();

    bool check1 = matA == matB;
    REQUIRE(check1);
}

TEST_CASE( "Matrix Multiplication", "[Matrix]") {
    Matrix matA(2, 2, 0);
    int ASet[4] = {1, 2, 3, 4};
    for (int i = 0; i < 6; ++i)
        matA[i] = ASet[i];

    Matrix matB(2, 2, 0);
    int BSet[4] = {5, 6, 7, 8};
    for (int i = 0; i < 4; ++i)
        matB[i] = BSet[i];

    Matrix matC = matB * matA;

    Matrix matD(2);
    int DSet[4] = {19, 22, 43, 50};
    for (int i = 0; i < 4; ++i)
        matD[i] = DSet[i];

    bool check2 = matC == matD;

    matB *= matA;

    bool check1 = matD == matB;
    REQUIRE(check1);
    REQUIRE(check2);
}

TEST_CASE( "Matrix Inverse", "[Matrix]") {
    Matrix matC(3, 3, 0);
    int Cset[9] = {3, 0, 2, 2, 0, -2, 0, 1, 1};
    for(int i = 0; i < 9; ++i)
        matC[i] = Cset[i];

    Matrix matD = matC.inv();

    double Bset[9] = {0.2, 0.2, 0, -0.2, 0.3, 1, 0.2, -0.3, 0};
    for(int i = 0; i < 9; ++i)
        matC[i] = Bset[i];

    bool check1 = matD == matC;
    REQUIRE(check1);

    auto size = matC.shape();
    REQUIRE(size.first == size.second);
}

TEST_CASE( "Matrix * Vector", "[Matrix, Vector]") {
    Matrix matA(3);
    int matSetA[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < 9; ++i)
        matA[i] = matSetA[i];

    Vector vecA(3);
    int vecSetA[3] = {2, 1, 3};
    for(int i = 0; i < 3; ++i)
        vecA[i] = vecSetA[i];

    Vector vecB(3);
    int vecSetB[3] = {13, 31, 49};
    for(int i = 0; i < 3; ++i)
        vecB[i] = vecSetB[i];

    bool check = (vecA * matA) == vecB;
    REQUIRE(check);
    check = (matA * vecA) == vecB;
    REQUIRE(check);
    vecA *= matA;
    check = vecA == vecB;
    REQUIRE(check);
}

TEST_CASE( "Matrix Multiplication harder", "[Matrix]") {
    Matrix matA(2, 3, 0);
    int ASet[6] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; ++i)
        matA[i] = ASet[i];

    Matrix matB(3, 2, 0);
    int BSet[6] = {7, 8, 9, 10, 11, 12};
    for (int i = 0; i < 6; ++i)
        matB[i] = BSet[i];

    Matrix matC = matB * matA;

    Matrix matD(2);
    int DSet[4] = {58, 64, 139, 154};
    for (int i = 0; i < 4; ++i)
        matD[i] = DSet[i];

    bool check2 = matC == matD;

    matB *= matA;

    bool check1 = matD == matB;
    REQUIRE(check1);
    REQUIRE(check2);
}