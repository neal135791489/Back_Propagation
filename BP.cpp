#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

double sigmoid(double x)
{
    double returnValue;
    returnValue = 1 / (1 + exp(-x));
    return returnValue;
}
int main(){
    double w[5][5] = 
    {{0, 0, 1, -1, 0}, 
    {0, 0, -1, 1, 0},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0}};
    int pos[6][2] = 
    {{0, 2}, 
    {0, 3}, 
    {1, 2},
    {1, 3},
    {2, 4},
    {3, 4}};
    double theta[5] = {0, 0, 1, 1, 1};
    int x[4][2] = 
    {{0, 0},
    {0, 1},
    {1, 0},
    {1, 1}};
    int t[4] = {0, 1, 1, 0};
    double learningRate = 10, diff = 1;
    //learning
    while(diff > 0.01){ 
        double deltaW[5][5] = {0}, deltaTheta[5] = {0};
        diff = 0; 
        for(int ex = 0; ex < 4; ex++){
            double net[5] = {0}, sigma[5] = {0};
            //(1)
            for(int i = 2; i < 4; i++){
                for(int j = 0; j < 2; j++){
                    net[i] += (w[j][i] * x[ex][j]);
                }
                net[i] -= theta[i];
                net[i] = sigmoid(net[i]);
                printf("H%d:%f\n", i+1, net[i]);
            }
            //(2)
            for(int j = 2; j < 4; j++){
                net[4] += (w[j][4] * net[j]);
            }
            net[4] -= theta[4];
            net[4] = sigmoid(net[4]);
            printf("Y:%f\n", net[4]);
            diff += 0.5 * pow(t[ex] - net[4], 2); 
            //(3)
            sigma[4] = net[4] * (1 - net[4]) * (t[ex] - net[4]);
            printf("Sigma5:%f\n", sigma[4]);
            //(4)
            for(int i = 2; i < 4; i++){
                sigma[i] = net[i] * (1 - net[i]) * w[i][4] * sigma[4]; 
                printf("Sigma%d:%f\n", i+1, sigma[i]);
            }
            //(5)
            for(int i = 2; i < 4; i++){
                deltaW[i][4] += learningRate * sigma[4] * net[i];
                printf("deltaW[%d][5]:%f\n", i+1, deltaW[i][4]);
            }
            deltaTheta[4] += (0 - learningRate) * sigma[4];
            printf("deltaTheta[5]:%f\n", deltaTheta[4]);
            //(6)
            for(int i = 2; i < 4; i++){
                for(int j = 0; j < 2; j++){
                    deltaW[j][i] += learningRate * sigma[i] * x[ex][j];
                    printf("deltaW[%d][%d]:%f\n", j+1, i+1, deltaW[j][i]);
                }
                deltaTheta[i] += (0 - learningRate) * sigma[i];
                printf("deltaTheta[%d]:%f\n", i+1, deltaTheta[i]);
            }
        }
        //update
        for(int i = 0; i < 6; i++){
            w[pos[i][0]][pos[i][1]] += deltaW[pos[i][0]][pos[i][1]];
            printf("w[%d][%d]:%f\n", pos[i][0]+1, pos[i][1]+1, w[pos[i][0]][pos[i][1]]);
        }
        for(int i = 2; i <= 4; i++){
            theta[i] += deltaTheta[i];
            printf("theta[%d]:%f\n", i+1, theta[i]);
        }
        printf("diff:%f\n", diff);
    }
    //test
    double testNet[5] = {0};
    int inputX[2];
    printf("Input two digit into XOR(please separate with a space):\n");
    scanf("%d %d", &inputX[0], &inputX[1]);
    for(int i = 2; i < 4; i++){
        for(int j = 0; j < 2; j++){
            testNet[i] += (w[j][i] * inputX[j]);
        }
        testNet[i] -= theta[i];
        testNet[i] = sigmoid(testNet[i]);
    }
    for(int j = 2; j < 4; j++){
        testNet[4] += (w[j][4] * testNet[j]);
    }
    testNet[4] -= theta[4];
    testNet[4] = sigmoid(testNet[4]);
    printf("Y:%f\n", testNet[4]);
    printf("output:");
    if(testNet[4] < 0.5){
        printf("0\n");
    }
    else{
        printf("1\n");
    }
}
