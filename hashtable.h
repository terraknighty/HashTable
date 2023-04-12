#include <cstdlib>
#include <iostream>
using namespace std;

class HashTable {
    int* table;
    int N;
    int count;
    // Linear Probing
    // Since our key is an integer, we will use it as its own hashcode
    int hash_code(int key) {
        return key;
    }

    // This hash table uses a MAD compression function
    // where a = 59, b = 17, p = 509
    int compress(int code) {
        // TODO
        int a = 59, b = 17, p = 509;
        int aib = a*code + b;
        aib %= p;
        aib %= N;
        return aib;

    }

    // Using the knowledge that a hash function is composed of two portions
    int hashfn(int key) {
        return compress(hash_code(key));
    }

public:
    HashTable(int N) {
        // TODO
        count = 0;
        table = (int*) calloc(N, sizeof(int));
        this->N = N;
    }

    int insert(int key) {
        // TODO
        int collision = 0;
        if(count == N){
            return -1;
        }
        if(table[hashfn(key)] == key){
            return -1;
        }

        int pos = hashfn(key);
        while(table[pos] > 0){
            pos++;
            pos %= N;
            collision++;
            if(table[pos] == key){
                return -1;
            }
        }

        table[pos] = key;
        count++;
        return collision;
    }


    int search(int key) {
        // TODO
        int check = 0;
        int pos = hashfn(key);
        while(table[pos] != key){
            if(check == N - 1 || table[pos] == 0){
                return -1;
            }
            if(table[pos] == -1){
                continue;
            }
            pos++;
            pos %= N;
            check++;
        }

        return check;
    }

    int remove(int key){
        int delete_pos = hashfn(key);
        int check = 0;
        while(table[delete_pos] != key){
            if(check == N){
                return -1;
            }
            delete_pos++;
            delete_pos %= N;
            check++;
        }
        table[delete_pos] = -1;
        count--;
        // 1. Check if right is 0
        // 2. Check if left is -1, if so left = 0
        if (table[delete_pos + 1] == 0 && delete_pos < N-1){
            table[delete_pos] = 0;
            while(table[delete_pos - 1] == -1 ){
                if(count == 0){
                    break;
                }
                delete_pos--;
                table[delete_pos] = 0;
                if(delete_pos == 0){
                    delete_pos = N;
                }
            }
        }
        if(count == 0){
            for(int i = 0; i < N; i++){
                table[i] = 0;
            }
        }
        return check;
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << i << "\t";
        }
        cout << "\n";
        for (int i = 0; i < N; i++) {
            cout << table[i] << "\t";
        }
        cout << "\n";
    }

};