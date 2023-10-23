#include <iostream>
#include <vector>


const int M = 1000003;
typedef std::vector<std::vector<unsigned long long>> type_m;


type_m multiplyMatrix(const type_m& first_matrix, const type_m& second_matrix){
    int size = first_matrix.size();
    type_m res(size, std::vector<unsigned long long>(size, 0));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){
                res[i][j] += (first_matrix[i][k] * second_matrix[k][j]) % M;
                res[i][j] %= M;
            }
        }
    }
    return res;
}

type_m powerMatrix(const type_m& matrix, unsigned long long n){
    if(n == 0){
        type_m id_matrix(matrix.size(), std::vector<unsigned long long>(matrix.size(), 0));
        for(int i = 0; i < matrix.size(); i++){
            id_matrix[i][i] = 1;
        }
        return id_matrix;
    }
    if(n == 1){
        return matrix;
    }
    if(n % 2 == 0){
        type_m first_matrix = powerMatrix(matrix, n / 2);
        return multiplyMatrix(first_matrix, first_matrix);
    }
    else{
        type_m first_matrix = powerMatrix(matrix, (n - 1) / 2);
        return multiplyMatrix(multiplyMatrix(first_matrix, first_matrix), matrix);
//        type_mx = multiplyMatrix(first_matrix, first_matrix);
//        return multiplyMatrix(x , matrix);
    }
}



int main() {
    unsigned long long n;
    std::cin >> n;
    type_m a = {
            {0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1}
    };
    type_m b = {
            {0},
            {0},
            {0},
            {0},
            {1}
    };

    type_m c = powerMatrix(a, n - 1);
    type_m res = multiplyMatrix(c, b);

    std::cout << res[4][0] << std::endl;

    return 0;

}


