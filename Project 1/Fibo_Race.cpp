#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

// Fibo function
long long fibo(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fibo(n - 1) + fibo(n - 2);
}

int main()
{
    ofstream outputFile("cpp_data.txt");
    outputFile << "Number\tFibonacci Value\tTime (seconds)" << endl;

    int n = 51;

    // Table header format
    cout << setw(10) << left << "Number"
         << setw(20) << left << "Fibonacci Value"
         << setw(15) << left << "Time (seconds)" << endl;
    cout << "----------------------------------------------" << endl;

    for (int i = 1; i <= n; i++)
    {
        time_t start = time(nullptr);
        long long result = fibo(i);
        time_t end = time(nullptr);
        cout << setw(15) << left << i
             << setw(20) << left << result
             << setw(20) << left << (end - start) << endl;
        outputFile << i << "\t" << result << "\t" << (end - start) << endl;
    }
    outputFile.close();

    return 0;
}
