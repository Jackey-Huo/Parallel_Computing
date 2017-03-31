#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <utility>

inline double calcu_avg( double *** data, int x, int x_dim, int y, int y_dim, int z, int z_dim )
{
    double up, down, right, left, front, back;
    int counter = 0;

    z-1 >= 0     ? up    = data[x][y][z-1] , ++counter : up    = 0.0;
    z+1 < z_dim  ? down  = data[x][y][z+1] , ++counter : down  = 0.0;
    x-1 >= 0     ? right = data[x-1][y][z] , ++counter : right = 0.0;
    x+1 < x_dim  ? left  = data[x+1][y][z] , ++counter : left  = 0.0;
    y+1 < y_dim  ? front = data[x][y+1][z] , ++counter : front = 0.0;
    y-1 >= 0     ? back  = data[x][y-1][z] , ++counter : back  = 0.0;

    return (up + down + right + left + front + back) / double(counter);

}

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

    for(int t=0; t < t_steps; t++)
    {
        for(int z=0; z < z_dim; z++)
        {
            for(int y=0; y < y_dim; y++)
            {
                for (int x=0; x < x_dim; x++)
                {
                    grid[x][y][z] = calcu_avg( data, x, x_dim, y, y_dim, z, z_dim );
                }
            }
        }
        std::swap<double ***>(grid, data);
    }

    disp_3_dim_matrix(data, x_dim, y_dim, z_dim);

    return 0;

}

