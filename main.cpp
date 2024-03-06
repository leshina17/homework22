#include <iostream>
#include <random>

const int max_size=3;
using namespace std;

void matrix_random(double** arr, double* b, int n){
    int min, max;
    cout << "write min and max: ";
    cin >> min;
    cin >> max;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            arr[i][j]=dist(gen);;
        }
    } 
    for (int i=0; i<n; i++){
        b[i]=dist(gen);
    }
}

void print_matrix(double** arr, double* b, int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << arr[i][j] << " ";
        }
        cout << " |x " << i << "|" << b[i] << endl; //строка завершается символом перехода на новую строчку
    }
}

void matrix_write(double** arr, double* b, int n){
    cout << "write elements: " << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << "matrix:[" << i+1 << "][" << j+1 << "]: ";
            cin >> arr[i][j];
        }
    } //ввод чисел
    cout << "write vector b: " << endl;
    for (int i=0; i<n; i++){
        cout << "b[" << i+1 << "]:";
        cin >> b[i];
    }
}

void checka(double** arr, double* x, double* check, int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            check[i]+=arr[i][j]*x[j];
        }
    }
}

void pogresha(double** arr, double* check, double* pogresh, int n){
    for (int i=0; i<n; i++){
        pogresh[i]=arr[i][n]-check[i];
    }
}

void forward(double** arr, double* b, int n){
    for (int i=0; i<n; i++){
        if (arr[i][i]==0){
            for (int k=i+1; k<n; k++){
                if (arr[k][i]!=0){
                    swap(arr[k], arr[i]);
                    swap(b[k], b[i]);
                    break;
                }
            }
        }
        for (int k=i+1; k<n; k++){
            double dot=arr[k][i]/arr[i][i];
            for (int j=i; j<n; j++){
                arr[k][j]-=dot*arr[i][i];
            }
            b[k]-=dot*b[i];
        }
    }
}

void back(double** arr, double* b, double* x, int n){
    for (int i=n-1; i>=0; i--){
        double k=b[i];
        for (int j=i+1; j<n; j++){
            k-=arr[i][j]*x[j];
        }
        x[i]=k/arr[i][i];
    }
}

void vector_nev(double** arr, double* b, double* x, double* nev, int n){
    for (int i=0; i<n; i++){
        nev[i]=b[i];
        for (int j=0; j<n; j++){
            nev[i]-=arr[i][j]*x[j];
        }
    }
}

void print_vector_nev(double* nev, int n){
    for (int i=0; i<n; i++){
        cout << "U" << i+1 << "=" << nev[i] << endl;
    }
}

int main(){
    int n;
    cout << "what size is it?";
    cin >> n;
    if (n>max_size){
        cout << "error" << endl;
        return 1;
    }
    double** arr = new double*[n];
    for (int i=0; i<n; i++){
        arr[i]=new double[n];
    }// создала дв. массив 
    double* b = new double[n]; // вектор b
    double* x= new double[n]; // решение
    double* nev=new double[n];
    double* check=new double[n];
    double* pogresh=new double[n];
    
    double** arr_copy=new double*[n];
    for (int i=0; i<n; i++){
        arr_copy[i]=new double[n];
        for (int j=0; j<n; j++){
            arr[i][j]=arr_copy[i][j];
        }
    }
    
    double* b_copy=new double[n];
    for (int i=0; i<n; i++){
        b[i]=b_copy[i];
    }
    
    int c;
    cout<<"1, if you want to write; 2, if you want random"<<endl;
    cin>>c;
    if (c==2){
        matrix_random(arr, b, n);
        print_matrix(arr, b, n);
    }
    if (c==1){
        matrix_write(arr, b, n);
        print_matrix(arr, b, n);
    }
    else 
        cout << "error";
    
    forward(arr, b, n);
    back(arr, b, x, n);
    cout << "RESULT: " << endl;
    for (int i=0; i<n; i++){
        cout << "x" << i+1 << "=" << x[i] << " " << endl;
    }
    
    checka (arr, x, check, n);
    cout << " " << endl;
    
    pogresha(arr, check, pogresh, n);
    cout << "CHECK: " << endl;
    for (int i=0; i<n; i++){
        cout << pogresh[i] << endl;
    }
    delete[] check;
    delete[] pogresh;
    
    for (int i=0; i<max_size; i++){
        delete[] arr[i];
        delete[] arr_copy[i];
    }
    delete[] arr;
    delete[] b;
    delete[] x;
    delete[] arr_copy;
    delete[] b_copy;
    
    return 0;
}