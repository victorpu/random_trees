#include "dataset.h"
#include<fstream>//ifstream
#include<sstream>//istringstream
#include<iostream>//
#include<vector>
#include<string>
using namespace std;

void split(const string& line, vector<string>& tokens) {
	tokens.resize(0);
	istringstream linestream(line);
	while(linestream) {
		string token;
		if(getline(linestream, token, ',')) {
			tokens.push_back(token);
		} else {
			break;
		}
	}
}

double str2double(const string& str) {
	istringstream ss(str);
	double value;
	ss >> value;
	return value;
}

int str2int(const string& str) {
	istringstream ss(str);
	int value;
	ss >> value;
	return value;
}

DataSet::DataSet() { }

DataSet* DataSet::load_csv(const string& filename){
	DataSet* data = new DataSet();
	vector< vector<double> >& attrs =data->attributes_;
    vector<int>& labels = data->labels_;
		
	ifstream infile;
	infile.open(filename.c_str());
	while(infile){
		string line;
		if(!getline(infile,line)) break;
		vector<string> tokens;
		split(line, tokens);
		labels.push_back(str2int(tokens[0]));
		attrs.push_back(vector<double>());
		for(int i=1; i<tokens.size(); ++i) {
			attrs.back().push_back(str2double(tokens[i]));
		}
	}
	infile.close();
	
	return data;
}


DataSet* DataSet::boostraped_set(const DataSet& original_dataset){
	DataSet* new_dataset = new DataSet();
	vector< vector<double> >& attrs =new_dataset->attributes_;
    vector<int>& labels = new_dataset->labels_;
	int s=original_dataset.size();
	for(int i=0; i<s; ++i){
		int r=rand()%s;
		attrs.push_back(original_dataset.attributes_[r]);
		labels.push_back(original_dataset.labels_[r]);		
	}	
	return new_dataset;
}

void DataSet::print(){
	//DataSet* DataSet::load_csv("data.csv") data;//Is this declaration right?
	cout<<"Print attributes_:"<<endl;
	for(int i=0;i<attributes_.size();++i){
		for(int j=0;j<attributes_[i].size();++j){
			if(j>0){
				cout<<" ";
			}
			cout<<attributes_[i][j];
		}
		cout<<endl;
	}
	
	cout<<"Print labels_:"<<endl;
	for(int i=0;i<labels_.size();++i){
		if(i>0){
			cout<<" ";
		}
		cout<<labels_[i];
	}
	cout<<endl;
	
}
