# include "data_utils.h"
# include <stdlib.h>

struct DATA* data_copy_structure(double *feat, int lb, int length_data, int num_dim)
{
    struct DATA* data = (struct DATA*)malloc(length_data * sizeof(struct DATA));

    for(int i = 0; i < length_data; i++)
    {
        data[i].num_dimensions = num_dim;
        data[i].features = (double*)malloc(num_dim * sizeof(double));
        data[i].label = lb;

        for(int j = 0; j < num_dim; j++)
        {
            data[i].features[j] = feat[i * num_dim + j];
        }
    }

    return data;
}

void free_data_structure(struct DATA* data, int length_data)
{
    for (int i = 0; i < length_data; i++)
    {
        free(data[i].features);
    }
    free(data);
}
