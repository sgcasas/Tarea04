
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
using namespace std;
bool validar_orden(const vector<float>& vec){
    for(size_t i = 1; i < vec.size(); ++i){
        if(vec[i] < vec[i-1]){
            return false;
        }
    }
    return true;
}
// ================= BUCKET SORT =================
void bucketSort(vector<float>& arr){
    int n = arr.size();

    float maxVal = *max_element(arr.begin(), arr.end());
    float minVal = *min_element(arr.begin(), arr.end());

    float range = (maxVal - minVal) / n;

    vector<vector<float>> buckets(n);

    for(float num : arr){
        int idx = (num - minVal) / range;

        if(idx == n)
            idx--;

        buckets[idx].push_back(num);
    }

    for(int i = 0; i < n; i++){
        sort(buckets[i].begin(), buckets[i].end());
    }

    int index = 0;

    for(int i = 0; i < n; i++){
        for(float num : buckets[i]){
            arr[index++] = num;
        }
    }
}
int main(){
    vector<float> numbers;
    ifstream in("datos.txt");
    float num;
    while(in >> num){
        numbers.push_back(num);
    }
    in.close();


    cout << "Vector (size): " << numbers.size() << "\n";
    cout << "Vector (size): " << numbers.size() << endl;
    auto start = chrono::high_resolution_clock::now();
    // Aqui debe ir el algoritmo de ordenamiento...
    // std::sort
    sort(numbers.begin(), numbers.end());

    // Timsort (Python, no existe nativo en C++)
    // stable_sort(numbers.begin(), numbers.end());

    // Bucket Sort
    // bucketSort(numbers);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Tiempo: " << duration.count() << " mili." << endl;
    cout << "Ordenado: " << (validar_orden(numbers) ? "Si" : "No") << endl;
    return 0;
}
