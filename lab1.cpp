#include <iostream>
#include <cmath>
using namespace std;

#define MAX 10   // maximum number of vertices in polygon

// Function to multiply two 3x3 matrices
void multiplyMatrix(float a[3][3], float b[3][3], float result[3][3]) {
    float temp[3][3] = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                temp[i][j] += a[i][k] * b[k][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result[i][j] = temp[i][j];
}

// Apply transformation matrix to polygon points
void applyTransformation(float points[MAX][3], int n, float transform[3][3]) {
    for (int i = 0; i < n; i++) {
        float x = points[i][0];
        float y = points[i][1];
        points[i][0] = x * transform[0][0] + y * transform[1][0] + transform[2][0];
        points[i][1] = x * transform[0][1] + y * transform[1][1] + transform[2][1];
    }
}

// Print polygon points
void printPoints(float points[MAX][3], int n) {
    cout << "\nPolygon vertices:\n";
    for (int i = 0; i < n; i++)
        cout << "(" << points[i][0] << ", " << points[i][1] << ")\n";
}

int main() {
    int n;
    float points[MAX][3]; // polygon vertices

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter coordinates of vertices (x y):\n";
    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][1];
        points[i][2] = 1; // homogeneous coordinate
    }

    int choice;
    do {
        cout << "\n2D Transformations Menu:\n";
        cout << "1. Translation\n2. Scaling\n3. Rotation\n4. Reflection\n5. Shearing\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        float transform[3][3] = {0};

        switch (choice) {
            case 1: { // Translation
                float tx, ty;
                cout << "Enter translation factors (tx ty): ";
                cin >> tx >> ty;
                float T[3][3] = {
                    {1, 0, 0},
                    {0, 1, 0},
                    {tx, ty, 1}
                };
                applyTransformation(points, n, T);
                printPoints(points, n);
                break;
            }
            case 2: { // Scaling
                float sx, sy;
                cout << "Enter scaling factors (sx sy): ";
                cin >> sx >> sy;
                float S[3][3] = {
                    {sx, 0, 0},
                    {0, sy, 0},
                    {0, 0, 1}
                };
                applyTransformation(points, n, S);
                printPoints(points, n);
                break;
            }
            case 3: { // Rotation
                float angle;
                cout << "Enter rotation angle (in degrees): ";
                cin >> angle;
                angle = angle * M_PI / 180; // convert to radians
                float R[3][3] = {
                    {cos(angle), sin(angle), 0},
                    {-sin(angle), cos(angle), 0},
                    {0, 0, 1}
                };
                applyTransformation(points, n, R);
                printPoints(points, n);
                break;
            }
            case 4: { // Reflection
                int axis;
                cout << "Reflect about: 1.X-axis  2.Y-axis  3.Origin : ";
                cin >> axis;
                float Rx[3][3] = {
                    {1, 0, 0},
                    {0, -1, 0},
                    {0, 0, 1}
                };
                float Ry[3][3] = {
                    {-1, 0, 0},
                    {0, 1, 0},
                    {0, 0, 1}
                };
                float Ro[3][3] = {
                    {-1, 0, 0},
                    {0, -1, 0},
                    {0, 0, 1}
                };
                if (axis == 1) applyTransformation(points, n, Rx);
                else if (axis == 2) applyTransformation(points, n, Ry);
                else applyTransformation(points, n, Ro);
                printPoints(points, n);
                break;
            }
            case 5: { // Shearing
                float shx, shy;
                cout << "Enter shearing factors (shx shy): ";
                cin >> shx >> shy;
                float Sh[3][3] = {
                    {1, shy, 0},
                    {shx, 1, 0},
                    {0, 0, 1}
                };
                applyTransformation(points, n, Sh);
                printPoints(points, n);
                break;
            }
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}