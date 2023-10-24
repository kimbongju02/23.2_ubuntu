#include <iostream>
#include <vector>

using namespace std;

int main(){
	int n, m;
	cout << "행 수: ";
	cin >> n;
	cout << "열 수: ";
	cin >> m;

	vector<vector<int>> matrix1(n, vector<int>(m));
	vector<vector<int>> matrix2(n, vector<int>(m));
	vector<vector<int>> result(n, vector<int>(m));
	
	cout << "첫 번째 행렬 요소: \n";
	for(int i=0; i<n; i++){
		for (int j=0; j<m; j++){
			cin >> matrix1[i][j];
		}
	}

	cout << "두 번째 행렬 요소: \n";
        for(int i=0; i<n; i++){
                for (int j=0; j<m; j++){
                        cin >> matrix2[i][j];
                }
        }

        for(int i=0; i<n; i++){
                for (int j=0; j<m; j++){
                        result[i][j] = matrix1[i][j] + matrix2[i][j];
                }
        }

	cout << "두 행렬의 합:\n";
    	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < m; j++) {
            		cout << result[i][j] << " ";
        	}
        	cout << "\n";
    	}

	return 0;
}
