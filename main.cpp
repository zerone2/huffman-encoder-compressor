#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <windows.h>

#include "huffmanCompress.h"

using namespace std;


int main()
{
	char filename[30];
	char* context;
	int originSize, encodedSize;
	int a;
	clock_t start, finish;
	Huffman H;
	string encodedFile;

	cout << "==Compressor Ready==\n" << endl;
	cout << "name of the file to compress : ";
	cin >> filename;
	start = clock();
	ifstream input(filename);
	ifstream input2(filename);
	if (!input || !input2)
	{
		cout << "ifstream failed" << endl;
		cout << "check out that you typed write file, this program will be terminated after 3sec" << endl;
		Sleep(3000);
		return 0;
	}
	input.unsetf(ios_base::skipws);	//공백문자를 무시하지 않는다.
	input2.unsetf(ios_base::skipws);

	vector< pair<char, int> > huffman_freq = H.createFreq(input);	//파일 빈도수 만들기
	Huffman::pHuffNode hTree = H.compressTree(huffman_freq);
	map<char, string> huffKeyMap = H.makeKeyMap(hTree);
	vector < pair<char, string> > key_vec = H.writeKeyMap(huffKeyMap);	//인코딩 맵 생성해서 벡터에 저장
	string t = H.encode(input2, huffKeyMap);	//문자열를 키 형태로 변환해서 저장.

	originSize = H.getFileSize(filename);		//원래 파일의 사이즈
	encodedFile = (string)strtok_s(filename, ".", &context) + ".huf";

	H.makeFile(encodedFile, t, key_vec);		//압축파일 만들기
	encodedSize = H.getFileSize(encodedFile);	//압축된 후의 파일 사이즈

	finish = clock();

	cout << "\nExecution time: +/- " << ((double)(finish - start)) / CLOCKS_PER_SEC << "s\n";
	cout << "Before Compress : " << filename << ".txt / " << originSize << "byte  "
		<< "&&  After Compress : " << encodedFile << " / " << encodedSize << "byte" << endl;
	cout << "\n압축률 : " << ((double)encodedSize / (double)originSize) * 100 << "%";

	cin >> a;
	return 0;
}