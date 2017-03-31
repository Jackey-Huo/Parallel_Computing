#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <utility>

inline void disp_3_dim_matrix( double *** data, int x_dim, int y_dim, int z_dim )
{
    for(int z = 0; z < z_dim; ++z)
    {
        for(int y = 0; y < y_dim; ++y)
        {
            for(int x = 0; x < x_dim; ++x)
            {
                printf("%lf ", data[x][y][z]);
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

    double ***data, ***grid;

    printf("please input t_steps, x_dim, y_dim, z_dim: \n");

    scanf("%d %d %d %d", &t_steps, &x_dim, &y_dim, &z_dim);


    // allocate memery for data
    data = (double ***)malloc(sizeof(double **) * x_dim);
    grid = (double ***)malloc(sizeof(double **) * x_dim);
    for( int i = 0; i < x_dim; ++i )
    {
        data[i] = (double **)malloc(sizeof(double *) * y_dim);
        grid[i] = (double **)malloc(sizeof(double *) * y_dim);
        for( int j = 0; j < y_dim; ++j )
        {
            data[i][j] = (double *)malloc(sizeof(double) * z_dim);
            grid[i][j] = (double *)malloc(sizeof(double) * z_dim);
        }
    }

    // read data to the 3-dim array
    printf("please input the data(sequence sorted by x, y, z): \n");
    for( int z = 0; z < z_dim; ++z )
    {
        for(int y = 0; y < y_dim; ++y)
        {
            for(int x = 0; x < x_dim; ++x)
            {
                scanf("%lf", &data[x][y][z]);
            }
        }
    }


    printf("down! starting calculate\n");

    double tmp;

    for(int t=0; t < t_steps; t++)
    {
        for(int z=1; z < z_dim-1; z++)
        {
            for(int y=1; y < y_dim-1; y++)
            {
                for (int x=1; x < x_dim-1; x++)
                {
                    tmp = 0.0;
                    tmp += data[x-1][y][z];
                    tmp += data[x+1][y][z];
                    tmp += data[x][y-1][z];
                    tmp += data[x][y+1][z];
                    tmp += data[x][y][z-1];
                    tmp += data[x][y][z+1];
                    tmp /= 6.0;

                    grid[x][y][z] = tmp;
                }
            }
        }
        std::swap<double ***>(grid, data);
    }

    disp_3_dim_matrix(data, x_dim, y_dim, z_dim);

    return 0;

}

