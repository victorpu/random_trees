#ifndef _DATASET_H_
#define _DATASET_H_

#include <string>
#include <vector>

// For example:
// if line == "ab,cd,e,12,xy", then
// tokens will be ["ab", "cd", "e", "12", "xy"]
void split(const std::string& line, std::vector<std::string>& tokens);

double str2double(const std::string& str);
int str2int(const std::string& str);

class DataSet {
    public:
        // Empty constructor
	 	DataSet();
		
        // Named constructor - load from csv file:
		//   (1) there is no header;
		//   (2) the first column is y;
		//   (3) there is no missing value;
		//   (4) delimiter is always ','.
        static DataSet* load_csv(const std::string& filename);
		
        // using boostrap (with replacement) to generate a DataSet from an 
		// existing DataSet, this dataset has the same size as the existing one.
        static DataSet* boostraped_set(const DataSet& original_dataset);	
		
        // Get a particular instance's label
        int label(int i) const{
          return labels_[i];
        }
        // Number of instances
        unsigned int size() const {
            return labels_.size();
        }
        // Number of attributes
        unsigned int num_attributes() const {
          return attributes_.size();
        }

        // Get a particular instance's attribute
        float get_attribute(int i, int attr) const {
          return attributes_[i][attr];
        }
		
		void print();
    private:
		// X, access is attributes_ [attribute] [instance]
        std::vector< std::vector<double> > attributes_;
        // List of true labels, access is labels_ [instance]
        std::vector<int> labels_;
};
#endif
