#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <utility>

inline void disp_3_dim_matrix( double *data, int x_dim, int y_dim, int z_dim )
{
    double * data_t = data;
    for(int z = 0; z < z_dim; ++z)
    {
        for(int y = 0; y < y_dim; ++y)
        {
            for(int x = 0; x < x_dim; ++x)
            {
                printf("%lf ", *data_t++);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
    return;
}

int main()
{
    int t_steps;
    int z_dim, y_dim, x_dim;

    printf("please input t_steps, x_dim, y_dim, z_dim: \n");

    scanf("%d %d %d %d", &t_steps, &x_dim, &y_dim, &z_dim);

    // allocate memory for data and grid
    double * data = (double *)malloc(x_dim * y_dim * z_dim * sizeof(double));
    double * grid = (double *)malloc(x_dim * y_dim * z_dim * sizeof(double));

    // read data to the 3-dim array
    printf("please input the data(sequence sorted by x, y, z): \n");
    double * data_t = data;
    double * grid_t = grid;
    for( int z = 0; z < z_dim; ++z )
        for(int y = 0; y < y_dim; ++y)
            for(int x = 0; x < x_dim; ++x)
            {
                scanf("%lf", data_t++);
                *(grid_t++) = *data_t;
            }

    printf("down! starting calculate\n");


    double tmp, tmp_0, tmp_1, tmp_2;
    int index_0, index_1, index_2, index_3, index_4, index_5, index_6;
    // change divide into multiplication to save time
    double divide_by_six = 1.0 / 6.0;

    for(int t=0; t < t_steps; t++)
    {
        for(int z=1; z < z_dim-1; z++)
        {
            for(int y=1; y < y_dim-1; y++)
            {
                for (int x=1; x < x_dim-1; x++)
                {
                    // calculate 6 index
                    index_0 = (y_dim * z + y) * x_dim + x;
                    index_1 = (y_dim * z + y) * x_dim + x-1;
                    index_2 = (y_dim * z + y) * x_dim + x+1;
                    index_3 = (y_dim * z + y-1) * x_dim + x;
                    index_4 = (y_dim * z + y+1) * x_dim + x;
                    index_5 = (y_dim * (z-1) + y) * x_dim + x;
                    index_6 = (y_dim * (z+1) + y) * x_dim + x;

                    // reduce dependence
                    tmp_0 = data[index_1] + data[index_2];
                    tmp_1 = data[index_3] + data[index_4];
                    tmp_2 = data[index_5] + data[index_6];
                    tmp = tmp_0 + tmp_1 + tmp_2;
                    tmp *= divide_by_six;

                    grid[index_0] = tmp;
                }
            }
        }
        std::swap<double *>(grid, data);
    }

    disp_3_dim_matrix(data, x_dim, y_dim, z_dim);

    return 0;
}



