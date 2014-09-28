#ifndef _DATASET_H_
#define _DATASET_H_

#include <string>
#include <vector>
#include <fstream>
//#include "librf/discrete_dist.h"

using namespace std;

namespace randomforest {

class DataSet {
    public:
        // Empty constructor
        DataSet();
        // Named constructor - load from csv file with labelled data
        static DataSet* load_csv_and_labels(const string& data,
                                                    const string& labels,
                                                    bool header = false,
                                                    const string& delim =",");
        // Named constructor - unlabelled data
        static DataSet* load_unsupervised(const string& data,
                                              unsigned int* seed,
                                              bool header = false,
                                              const string& delim =",");													
		/* Named constructor - boostrap a DataSet(with replacement) from an 
		existing DataSet, this dataset has the same size as the existing one.*/
        static DataSet* boostraped_set(const DataSet&);	

		
        // permute a variable's instances (shuffle)
        void permute(int var, unsigned int * seed);
        // Get a particular instance's label
        unsigned char label(int i) const{
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
          return attributes_[attr][i];
        }
        void write_csv(ostream& out, bool header, const string& delim);
		//useful when we want to write the boostrapped DataSet into a CSV file.
    private:
        // Load from csv file for labelled data
        DataSet(const string& csv_data, const string& labels,
                    bool header=false, const string& delim=",");
        // Load csv for unlabelled data
        DataSet(const string& csv_data, unsigned int* seed,
                    bool header=false, const string& delim=",");
        // Get a subset of an existing instance set
        DataSet(const DataSet&);
        void load_labels(istream& in);
        void load_csv(istream& in, bool header, const string& delim);
        void create_dummy_var_names(int n);//x1,x2,...,xn
		
		// List of Attribute Lists, access is attributes_ [attribute] [instance]
        vector< vector<float> > attributes_;
        // List of true labels, access is labels_ [instance]
        vector<unsigned char> labels_;
};

}  // namespace
#endif
