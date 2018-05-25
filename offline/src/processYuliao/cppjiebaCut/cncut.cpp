 ///
 /// @file    cncut.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-25 09:55:20
 ///
 
#include"cppjieba/Jieba.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
//const char* const DICT_PATH = "/usr/local/include/cppjieba/dict/jieba.dict.utf8";
//const char* const HMM_PATH = "/usr/local/include/cppjieba/dict/hmm_model.utf8";
//const char* const USER_DICT_PATH = "/usr/local/include/cppjieba/dict/user.dict.utf8";
//const char* const IDF_PATH = "/usr/local/include/cppjieba/dict/idf.utf8";
//const char* const STOP_WORD_PATH = "/usr/local/include/cppjieba/dict/stop_words.utf8";
int main()
{
//	cppjieba::Jieba jieba(DICT_PATH,
//			HMM_PATH,
//			USER_DICT_PATH,
//			IDF_PATH,
//			STOP_WORD_PATH);
	using namespace meihao;
	vector<string> words;
	vector<string> nocharWords;
	string s = "他来到了网易杭研大厦";
	cout<<"Cut with HMM"<<endl;
	jieba.Cut(s,words,true);
	cout<<limonp::Join(words.begin(),words.end(),"/")<<endl;
	
	s = "我是中国人，我叫梅浩";
	stringstream ss(s);
	jieba.Cut(s,words,true);
	for(auto& elem:words)
	{
		cout<<elem<<" ";
		if(elem!="，")
			nocharWords.push_back(elem);
	}
	cout<<endl;
	for(auto& elem:nocharWords)
		cout<<elem<<" ";
	cout<<endl;
	return 0;
}
