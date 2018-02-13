#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

void show_matrix(int **matrix, int x, int y)
{
        if (matrix == nullptr)
                {
                cout << "matrix is empty" << endl;
                return;
                }
        for (int i = 0; i < x; i++)
        {
                for (int j = 0; j < y; j++) cout << setw(4) << matrix[i][j];
                cout << endl;
        }
}

void delete_matrix(int **&matrix, int x)
{
        for (int i = 0; i < x; i++) delete[] matrix[i];
        delete[] matrix;
}

int **create_matrix(int **&matrix, int x, int y)
{
        matrix = new int *[x];
        for (int i = 0; i < x; i++) matrix[i] = new int[y];
        return matrix;
}

void fill_matrix(int **&matrix, int &x, int &y, int argc, char *argv[])
{
        int z = 0;
        bool arg = false;
        string matrix_size;
        while (z < strlen(argv[1]))
        {
                if (argv[1][z] == 'x' || argv[1][z] == 'X')
                {
                        arg = true;
                        matrix_size = "";
                        z++;
                }
                if (arg == false && (argv[1][z] >= '0' && argv[1][z] <= '9'))
                {
                        matrix_size = argv[1][z];
                        x = x * 10 + atoi(matrix_size.c_str());   // Конвертирует строку в стиле С++ в строку в стиле С.
                }
                 else if (arg == true && (argv[1][z] >= '0' && argv[1][z] <= '9'))
                {
                        matrix_size = argv[1][z];
                        y = y * 10 + atoi(matrix_size.c_str());
                }
                z++;
                 }
        z = 0;
        if (x != 0 && y != 0)
                {
                matrix = create_matrix(matrix, x, y);
                for (int i = 0; i < x; i++)
                        for (int j = 0; j < y; j++) matrix[i][j] = 0;
                if (argc > 3)
                        {
                        for (int i = 0, k = 2; i < x; i++)
                                for (int j = 0; j < y; j++, k++)
                                        {
                                        if (k < argc) matrix[i][j] = atoi(argv[k]);
                                }
                }
                else if (argc == 3)
                        {
                        string number;
                        for (int i = 0; i < x && argv[2][z] != '\0'; i++)
                                {
                                for (int j = 0; j < y && argv[2][z] != '\0'; j++)
                                        {
                                        int a = 1;
                                        if (argv[2][z] == '-')
                                                {
                                                a = -1;
                                                z++;
                                                }
                                        while (argv[2][z] >= '0' && argv[2][z] <= '9')
                                        {
                                                number = argv[2][z];
                                                matrix[i][j] = matrix[i][j] * 10 + atoi(number.c_str());
                                                z++;
                                                number = "";
                                        }
                                             matrix[i][j] *= a;
                                        z++;
                                }
                        }
                }
        } else
                cout << "incorrect size! matrix can't be created" << endl;
}

void summ_matrix(int **&matrix, int x, int y)
{
        if (matrix == nullptr)
        {
                cout << "matrix is empty" << endl;
                return;
        }
        int **matrix_sum = create_matrix(matrix_sum, x, y);
         cout << "please enter matrix:" << x << "x" << y << endl;
        for (int i = 0; i < x; i++)
                for (int j = 0; j < y; j++) cin >> matrix_sum[i][j];

        for (int i = 0; i < x; i++)
                for (int j = 0; j < y; j++) matrix[i][j] = matrix[i][j] + matrix_sum[i][j];
        for (int i = 0; i < x; i++)
        {
                for (int j = 0; j < y; j++) cout << setw(4) << matrix[i][j];
                cout << endl;
        }
        delete_matrix(matrix_sum, x);
}

void multiply_matrix(int **&matrix, int &x, int &y)
{
        if (matrix == nullptr)
        {
                cout << "matrix is empty" << endl;
                return;
        }
          string matrix_size;
        int x_m = 0;
        int y_m = 0;
        int z = 0;
        bool arg = false;
        cout << "please enter size matrix" << endl;
        cin >> matrix_size;

          while (z < matrix_size.size())
        {
                if (matrix_size[z] == 'x' || matrix_size[z] == 'X')
                {
                        arg = true;
                        
                        z++;
                }
                if (arg == false && (matrix_size[z] >= '0' && matrix_size[z] <= '9'))
                {
                  
                        x_m = x_m * 10 + atoi(matrix_size.c_str());   // Конвертирует строку в стиле С++ в строку в стиле С.
                }
                 else if (arg == true && (matrix_size[z] >= '0' && matrix_size[z] <= '9'))
                {
                   
                        y_m = y_m * 10 + atoi(matrix_size.c_str());
                }
                z++;
                 }
        z = 0;

        if (y != x_m || y_m == 0)
        {
                cout << "wrong size" << endl;
                return;
        }
        else
        {
        int **matrix1 = create_matrix(matrix1, x_m, y_m);
        int **matrix_m = create_matrix(matrix_m, x, y_m);
        for (int i = 0; i < x_m; i++)
                for (int j = 0; j < y_m; j++) cin >> matrix1[i][j];
        for (int i = 0; i < x; i++)
                for (int j = 0; j < y_m; j++) matrix_m[i][j] = 0;
        for (int i = 0; i < x; i++)
                for (int j = 0; j < y_m; j++)
                                for (int p = 0; p < y; p++)
                                        matrix_m[i][j] += matrix[i][p] * matrix1[p][j];
                delete_matrix(matrix, x);
                delete_matrix(matrix1, x);
                x = x;
                y = y_m;
                   matrix = nullptr;
                matrix = matrix_m;
        }
}

void transpose_matrix(int **&matrix, int &x, int &y)
{
        if (matrix == nullptr)
        {
                cout << "matrix is empty" << endl;
                return;
        }
        int **matrix_t = create_matrix(matrix_t, y, x);
        for (int i = 0; i < y; i++)
                for (int j = 0; j < x; j++) matrix_t[i][j] = matrix[j][i];
        delete_matrix(matrix, x);
        matrix = nullptr;
        matrix = matrix_t;
        swap(x, y);
}

void save_to_file(int **matrix, int x, int y)
{
        ofstream fout("matrix.txt");
        fout << x << setw(4) << y << endl;
        for (int i = 0; i < x; i++)
        {
                for (int j = 0; j < y; j++) fout << matrix[i][j] << setw(4);
                fout << endl;
        }
        fout.close();
}

void load_from_file(int **&matrix, int &x, int &y)
{
        string road_to_file;
        cout << "please enter road to file" << endl;
        cin >> road_to_file;
        ifstream fin(road_to_file.c_str());
        if (!fin.is_open())
        {
                cout << "file cant open";
                return;
        }
          }
        fin >> x >> y;
        if (matrix != nullptr) delete_matrix(matrix, x);
        matrix = new int *[x];
        for (int i = 0; i < x; i++) matrix[i] = new int[y];

        for (int i = 0; i < x; i++)
                for (int j = 0; j < y; j++) fin >> matrix[i][j];
        fin.close();
}

void sort_mm(int *&mm, int x, int y) {
        for (int i = 0; i < x * y; i++)
                for (int j = 0; j < x * y; j++) {
                        if (mm[j] > mm[i]) swap(mm[j], mm[i]);
                }
}

void snake_sort(int **&matrix, int x, int y)
{
        int *mm = new int[x * y];
        for (int i = 0, k = 0; i < x; i++)
                for (int j = 0; j < y; j++) mm[k++] = matrix[i][j];
        sort_mm(mm, x, y);

 for (int i = 0, k = 0; i < y; i++)
                for (int j = 0; j < x; j++) {
                        if (i % 2 == 0 || i == 0)
                                matrix[j][i] = mm[k++];
                        else if (i % 2 == 1)
                                matrix[x - j - 1][i] = mm[k++];
                }
        delete[] mm;
}

void sort_a(int **&matrix, int x, int y)
{
        int *mm = new int[x * y];
        for (int i = 0, k = 0; i < x; i++)
                for (int j = 0; j < y; j++) mm[k++] = matrix[i][j];
        sort_mm(mm, x, y);
        for (int i = 0, k = 0; i < x; i++)
                for (int j = 0; j < y; j++) matrix[i][j] = mm[k++];

        delete[] mm;
}

void sort_e(int **&matrix, int x, int y)
{
        int *mm = new int[x * y];
        for (int i = 0, k = 0; i < x; i++)
                for (int j = 0; j < y; j++) mm[k++] = matrix[i][j];
        sort_mm(mm, x, y);

        int u = 0;
        int count;
        int t = 0;
        int z = 0;
        int l = x;
        int f = y;
        while (l > 0 && f > 0)
        {
                if ((((l + f) * 2) - 4) > 0 && l > 1 && f > 1)
                        count = (((l + f) * 2) - 4);
                else if ((((l + f) * 2) - 4) > 0 && l == 1)
                        count = f;
                else if ((((l + f) * 2) - 4) > 0 && f == 1)
                        count = l;
                else if ((((l + f) * 2) - 4) == 0)
                        count = 1;
                for (int i = z, j = t, k = 0; k < count; k++)
                {
                        if (j < (y - 1) - t && i == 0 + z)
                        {
                                matrix[i][j++] = mm[u++];
                                continue;
                        }
                        else if (i < (x - 1) - z && j == (y - 1) - t)
                        {
                                matrix[i++][j] = mm[u++];
                                continue;
                        }
                         else if (j > t && i == (x - 1) - z)
                        {
                                matrix[i][j--] = mm[u++];
                                continue;
                        }
                         else if (i > z && j == 0 + t)
                        {
                                matrix[i--][j] = mm[u++];
                                continue;
                        }
                         else if (i == j && count == 1)
                        {
                                matrix[i][j++] = mm[u++];
                                continue;
                        }
                }
                t++;
                z++;
                l -= 2;
                f -= 2;
        }
        
        delete[] mm;
}

void matrix_sort(int **&matrix, int x, int y)
{
        char choise;
        cout << "pleae choise sort variant" << endl;
        cout << "s: snake sort" << endl;
        cout << "e: snail sort" << endl;
        cout << "a: classic sort" << endl;

        cin >> choise;
        switch (choise)
        {
                case 's':
                        snake_sort(matrix, x, y);
                        break;
                case 'e':
                        sort_e(matrix, x, y);
                        break;
                case 'a':
                        sort_a(matrix, x, y);
                        break;
        }
}

void print_menu()
{
        cout << endl;
        cout << "choise operation" << endl;
        cout << "1: show matrix" << endl;
        cout << "2: add up matrix" << endl;
        cout << "3: multiply matrix" << endl;
        cout << "4: transpose matrix" << endl;
        cout << "5: save the matrix to a file" << endl;
        cout << "6: load matrix from file" << endl;
        cout << "7: sort matrix" << endl;
        cout << "8: exit" << endl;
        cout << endl;
}

int main(int argc, char *argv[])
{
        int **matrix = nullptr;
        int x = 0;
        int y = 0;
         if (argc >= 2) fill_matrix(matrix, x, y, argc, argv);
        int choice_exit;
        while (1)
        {
                int choice;
                print_menu();
                cin >> choice;
                switch (choice)
                {
                        case 1:
                                show_matrix(matrix, x, y);
                                break;
                        case 2:
                                summ_matrix(matrix, x, y);
                                break;
                        case 3:
                                multiply_matrix(matrix, x, y);
                                break;
                        case 4:
                                transpose_matrix(matrix, x, y);
                                break;
                        case 5:
                                save_to_file(matrix, x, y);
                                break;
                                case 6:
                                load_from_file(matrix, x, y);
                                break;
                        case 7:
                                matrix_sort(matrix, x, y);
                                break;
                        case 8:
                                return 0;
                }
        }
        return 0;
}

