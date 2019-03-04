#include <bits/stdc++.h>
#define _GLIBCXX_DEBUG

using namespace std;

template <class T>
struct MyVector : vector<T> {
  MyVector() : vector<T>() { }
  MyVector( int n ) : vector<T>(n) { }
  T &operator [] ( int i )      { return vector<T>::at(i); }
  T operator [] ( int i ) const { return vector<T>::at(i); }
};

/** ���� � ����� ���� ������ ���� int[] � vector<int> ������������ MyVector<int>,
    �� ������� ��� range check error-� */
MyVector<int> b(10), a;

int main() {
	MyVector<int> a(50);
	for (int i = 1; i <= 600; i++) a[i] = i;
	cout << a[500] << "\n";
}