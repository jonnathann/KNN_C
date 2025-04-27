#ifndef DATA_UTILS_H
#define DATA_UTILS_H

struct DATA
{
    double *features;
    int label;
    int num_dimensions;
};

struct DATA* data_copy_structure(double *feat, int lb, int length_data, int num_dim);
void free_data_structure(struct DATA* data, int length_data);

#endif
