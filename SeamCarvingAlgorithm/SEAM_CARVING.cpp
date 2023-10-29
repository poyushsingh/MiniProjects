#include <iostream>
#include <fstream>

using namespace std;

void fill_grad_grid(int H, int W, int ***rgb, int **grad_grid)
{
    int rx, gx, bx, sqrx, ry, gy, by, sqry;
    // grad_grid[0][0]
    rx = rgb[0][W - 1][0] - rgb[0][1][0];
    gx = rgb[0][W - 1][1] - rgb[0][1][1];
    bx = rgb[0][W - 1][2] - rgb[0][1][2];
    sqrx = (rx * rx) + (gx * gx) + (bx * bx);

    ry = rgb[H - 1][0][0] - rgb[1][0][0];
    gy = rgb[H - 1][0][1] - rgb[1][0][1];
    by = rgb[H - 1][0][2] - rgb[1][0][2];
    sqry = (ry * ry) + (gy * gy) + (by * by);

    grad_grid[0][0] = (sqrx + sqry);

    // grad_grid[0][W-1]
    rx = rgb[0][0][0] - rgb[0][W - 2][0];
    gx = rgb[0][0][1] - rgb[0][W - 2][1];
    bx = rgb[0][0][2] - rgb[0][W - 2][2];
    sqrx = (rx * rx) + (gx * gx) + (bx * bx);

    ry = rgb[1][2][0] - rgb[H - 1][2][0];
    gy = rgb[1][2][1] - rgb[H - 1][2][1];
    by = rgb[1][2][2] - rgb[H - 1][2][2];
    sqry = (ry * ry) + (gy * gy) + (by * by);

    grad_grid[0][W - 1] = (sqrx + sqry);

    // grad_grid[H-1][0]
    rx = rgb[H - 1][1][0] - rgb[H - 1][W - 1][0];
    gx = rgb[H - 1][1][1] - rgb[H - 1][W - 1][1];
    bx = rgb[H - 1][1][2] - rgb[H - 1][W - 1][2];
    sqrx = (rx * rx) + (gx * gx) + (bx * bx);

    ry = rgb[H - 2][0][0] - rgb[0][0][0];
    gy = rgb[H - 2][0][1] - rgb[0][0][1];
    by = rgb[H - 2][0][2] - rgb[0][0][2];
    sqry = (ry * ry) + (gy * gy) + (by * by);

    grad_grid[H - 1][0] = (sqrx + sqry);

    // grad_grid[H-1][W-1]
    rx = rgb[H - 1][0][0] - rgb[H - 1][W - 2][0];
    gx = rgb[H - 1][0][1] - rgb[H - 1][W - 2][1];
    bx = rgb[H - 1][0][2] - rgb[H - 1][W - 2][2];
    sqrx = (rx * rx) + (gx * gx) + (bx * bx);

    ry = rgb[0][W - 1][0] - rgb[H - 2][W - 1][0];
    gy = rgb[0][W - 1][1] - rgb[H - 2][W - 1][1];
    by = rgb[0][W - 1][2] - rgb[H - 2][W - 1][2];
    sqry = (ry * ry) + (gy * gy) + (by * by);

    grad_grid[H - 1][W - 1] = (sqrx + sqry);

    int row;
    // from 0_1 to 0_W-2
    row = 0;
    for (int j = 1; j < W - 1; j++)
    {

        rx = rgb[row][j - 1][0] - rgb[row][j + 1][0];
        gx = rgb[row][j - 1][1] - rgb[row][j + 1][1];
        bx = rgb[row][j - 1][2] - rgb[row][j + 1][2];
        sqrx = (rx * rx) + (gx * gx) + (bx * bx);

        ry = rgb[H - 1][j][0] - rgb[1][j][0];
        gy = rgb[H - 1][j][1] - rgb[1][j][1];
        by = rgb[H - 1][j][2] - rgb[1][j][2];
        sqry = (ry * ry) + (gy * gy) + (by * by);

        grad_grid[row][j] = (sqrx + sqry);
    }

    // from H-1_1 to H-1_W-1
    row = H - 1;
    for (int j = 1; j < W - 1; j++)
    {

        rx = rgb[row][j - 1][0] - rgb[row][j + 1][0];
        gx = rgb[row][j - 1][1] - rgb[row][j + 1][1];
        bx = rgb[row][j - 1][2] - rgb[row][j + 1][2];
        sqrx = (rx * rx) + (gx * gx) + (bx * bx);

        ry = rgb[row - 1][j][0] - rgb[0][j][0];
        gy = rgb[row - 1][j][1] - rgb[0][j][1];
        by = rgb[row - 1][j][2] - rgb[0][j][2];
        sqry = (ry * ry) + (gy * gy) + (by * by);

        grad_grid[row][j] = (sqrx + sqry);
    }

    int column;
    // from 1_0 to H-2_0
    column = 0;
    for (int i = 1; i < H - 1; i++)
    {
        rx = rgb[i][column + 1][0] - rgb[i][W - 1][0];
        gx = rgb[i][column + 1][1] - rgb[i][W - 1][1];
        bx = rgb[i][column + 1][2] - rgb[i][W - 1][2];
        sqrx = (rx * rx) + (gx * gx) + (bx * bx);

        ry = rgb[i - 1][column][0] - rgb[i + 1][column][0];
        gy = rgb[i - 1][column][1] - rgb[i + 1][column][1];
        by = rgb[i - 1][column][2] - rgb[i + 1][column][2];
        sqry = (ry * ry) + (gy * gy) + (by * by);

        grad_grid[i][column] = (sqrx + sqry);
    }

    // from 1_W-1 to H-2_W-1
    column = W - 1;
    for (int i = 1; i < H - 1; i++)
    {
        rx = rgb[i][column - 1][0] - rgb[i][0][0];
        gx = rgb[i][column - 1][1] - rgb[i][0][1];
        bx = rgb[i][column - 1][2] - rgb[i][0][2];
        sqrx = (rx * rx) + (gx * gx) + (bx * bx);

        ry = rgb[i - 1][column][0] - rgb[i + 1][column][0];
        gy = rgb[i - 1][column][1] - rgb[i + 1][column][1];
        by = rgb[i - 1][column][2] - rgb[i + 1][column][2];
        sqry = (ry * ry) + (gy * gy) + (by * by);

        grad_grid[i][column] = (sqrx + sqry);
    }

    // from 1_1 to H-2_W-2
    for (int i = 1; i < H - 1; i++)
    {
        for (int j = 1; j < W - 1; j++)
        {
            rx = rgb[i][j - 1][0] - rgb[i][j + 1][0];
            gx = rgb[i][j - 1][1] - rgb[i][j + 1][1];
            bx = rgb[i][j - 1][2] - rgb[i][j + 1][2];
            sqrx = (rx * rx) + (gx * gx) + (bx * bx);

            ry = rgb[i - 1][j][0] - rgb[i + 1][j][0];
            gy = rgb[i - 1][j][1] - rgb[i + 1][j][1];
            by = rgb[i - 1][j][2] - rgb[i + 1][j][2];
            sqry = (ry * ry) + (gy * gy) + (by * by);

            grad_grid[i][j] = (sqrx + sqry);
        }
    }
}

void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_)
{

    int **dp;
    dp = new int *[H]; // Dynamic Allocation of 2D DP array
    for (int i = 0; i < H; i++)
    {
        dp[i] = new int[W];
    }

    int **grad_grid;
    grad_grid = new int *[H]; // Dynamic Allocation of 2D GRADIENT GRID array
    for (int i = 0; i < H; i++)
    {
        grad_grid[i] = new int[W];
    }

    // VERTICAL SEAMING
    while (W > W_)
    {

        fill_grad_grid(H, W, rgb, grad_grid);

        for (int j = 0; j < W; j++)
        {
            dp[0][j] = grad_grid[0][j];
        }

        for (int i = 1; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                int left = grad_grid[i][j];
                int up = grad_grid[i][j];
                int right = grad_grid[i][j];

                up += dp[i - 1][j];
                if (j - 1 >= 0)
                    left += dp[i - 1][j - 1];
                else
                    left += 1e9;
                if (j + 1 < W)
                    right += dp[i - 1][j + 1];
                else
                    right += 1e9;

                dp[i][j] = min(up, min(left, right));
            }
        }

        int mini = 1e9;
        for (int j = 0; j < W; j++)
        {
            if (dp[H - 1][j] < mini)
            {
                mini = j;
            }
        }

        for (int j = 0; j < W - 1; j++)
        {
            rgb[H - 1][j][0] = rgb[H - 1][j + 1][0];
            rgb[H - 1][j][1] = rgb[H - 1][j + 1][1];
            rgb[H - 1][j][2] = rgb[H - 1][j + 1][2];
        }

        int localminindex = mini;
        for (int i = H - 2; i >= 0; i--)
        {
            int minl = localminindex;
            int minr = localminindex;

            if (localminindex - 1 >= 0 && dp[i][localminindex - 1] < dp[i][localminindex])
            {
                minl = (localminindex - 1);
            }

            if (localminindex + 1 < W && dp[i][localminindex + 1] < dp[i][localminindex])
            {
                minr = (localminindex + 1);
            }

            if (dp[i][minl] < dp[i][minr])
            {
                localminindex = minl;
            }
            else
            {
                localminindex = minr;
            }

            for (int j = localminindex; j < W - 1; j++)
            {
                rgb[i][j][0] = rgb[i][j + 1][0];
                rgb[i][j][1] = rgb[i][j + 1][1];
                rgb[i][j][2] = rgb[i][j + 1][2];
            }
        }

        W--;
    }

    // HORIZONTAL SEAMING
    while (H > H_)
    {

        fill_grad_grid(H, W_, rgb, grad_grid);

        for (int i = 0; i < H; i++)
        {
            dp[i][0] = grad_grid[i][0];
        }

        for (int i = 1; i < W_; i++)
        {
            for (int j = 0; j < H; j++)
            {
                int left = grad_grid[j][i];
                int up = grad_grid[j][i];
                int right = grad_grid[j][i];

                up += dp[j][i - 1];
                if (j - 1 >= 0)
                    left += dp[j - 1][i - 1];
                else
                    left += 1e9;
                if (j + 1 < H)
                    right += dp[j + 1][i - 1];
                else
                    right += 1e9;

                dp[j][i] = min(up, min(left, right));
            }
        }

        int mini = 1e9;
        for (int i = 0; i < H; i++)
        {
            if (dp[i][W_ - 1] < mini)
            {
                mini = i;
            }
        }

        for (int i = mini; i < H - 1; i++)
        {
            rgb[i][W_ - 1][0] = rgb[i + 1][W_ - 1][0];
            rgb[i][W_ - 1][1] = rgb[i + 1][W_ - 1][1];
            rgb[i][W_ - 1][2] = rgb[i + 1][W_ - 1][2];
        }

        int localminindex = mini;
        for (int j = W_ - 2; j >= 0; j--)
        {
            int minl = localminindex;
            int minr = localminindex;

            if (localminindex - 1 >= 0 && dp[localminindex - 1][j] < dp[localminindex][j])
            {
                minl = (localminindex - 1);
            }

            if (localminindex + 1 < H && dp[localminindex + 1][j] < dp[localminindex][j])
            {
                minr = (localminindex + 1);
            }

            if (dp[minl][j] < dp[minr][j])
            {
                localminindex = minl;
            }
            else
            {
                localminindex = minr;
            }

            for (int i = localminindex; i < H - 1; i++)
            {
                rgb[i][j][0] = rgb[i + 1][j][0];
                rgb[i][j][1] = rgb[i + 1][j][1];
                rgb[i][j][2] = rgb[i + 1][j][2];
            }
        }

        H--;
    }

    delete[] dp;
    delete[] grad_grid;
}

int main()
{
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file); // ifstream-This data type represents the input file
                                    // stream and is used to read information from files.
    int H, W, C;
    fin >> H >> W >> C;

    int ***rgb;
    rgb = new int **[H];
    for (int i = 0; i < H; ++i)
    {
        rgb[i] = new int *[W];
        for (int j = 0; j < W; ++j)
        {
            rgb[i][j] = new int[C];
            for (int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();

    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;

    solve(rgb, H, W, C, H_, W_, C_);

    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);

    fout << H_ << " " << W_ << " " << C_ << endl;
    for (int i = 0; i < H_; ++i)
    {
        for (int j = 0; j < W_; ++j)
        {
            for (int k = 0; k < C_; ++k)
            {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();

    return 0;
}
