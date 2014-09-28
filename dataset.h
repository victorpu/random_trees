#ifndef _DATASET_H_
#define _DATASET_H_

#include <string>
#include <vector>

class DataSet {
    public:
        // Empty constructor
	 	DataSet();
		
        // Named constructor - load from csv file:
		//   (1) there is no header;
		//   (2) the first column is y;
		//   (3) there is no missing value;
		//   (4) delimiter is always ','.
        static DataSet* load_csv(const string& filename);
		
        // boostrap a DataSet(with replacement) from an existing DataSet, this
		// dataset has the same size as the existing one.
        static DataSet* boostraped_set(const DataSet& original_dataset);	
		
        // permute an attribute's instances (shuffle)
        void permute(int attr);
		
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
		
		//useful when we want to write the boostrapped DataSet into a CSV file.
        void write_csv(const string& output_filename);
		
    private:		
		// X, access is attributes_ [attribute] [instance]
        vector< vector<double> > attributes_;
        // List of true labels, access is labels_ [instance]
        vector<int> labels_;
};
#endif
