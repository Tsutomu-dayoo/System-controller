//
//  main.cpp
//  PID sample1
//
//  Created by 山口勉 on 2018/06/26.
//  Copyright © 2018年 山口勉. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>

using namespace std;

#define st 0.01
#define g 9.8

void update(void);
void OneDimention(void);
double initilization(double x[3]);
double adbsolution(double r[3],double rt[3]);

int main(void){
    
    update();
    //OneDimention();
    //initilization();
}

class Ball{
    double m; //ボールの重さ
    double l; //ボール半径
    double F;
public:
    Ball(double x,double y):m(x),l(y){}
    double force(double tau);
    double acceleration(double tau);
    
};

double Ball::force(double tau){
    double f = 0.0;
    
    f = tau / l;
    
    return f;
}

double Ball::acceleration(double tau){
    double a;
    tau = abs(tau);
    
    a = tau / (m * l);
    
    return a;
}

double initilization(double x[3]){
    int i;
    for(i = 0;i<3;i++){
        x[i] = 0.0;
    }
    return x[3];
}

double adbsolution(double r[3],double rt[3]){
    int i;
    
    double d[3] = {0.0,0.0,0.0};
    double abs = 0.0;
    
    for(i=0;i<3;i++){
        d[i] = rt[i] - r[i];
    }
    abs = sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]);
    
    return abs;
}

void update(){

    double Kp = 3000.0;
    double Ki = 1.0;
    double Kd = 1.0;
    
    double p[3] = {0.0,0.0,0.0}; //初期位置
    double p_p[3] = {0.0,0.0,0.0}; //1ステップ前の位置
    double tp[3] = {7.0,5.0,0.0}; //目標位置
    double p_hat[3] = {0.0,0.0,0.0};//単位ベクトル
    
    double abs = 0.0;//絶対値
    
   // double f[2] = { 0.0 , 0.0 }; //ボールにかかる力
    double v[3] = {0.0,0.0,0.0}; //ボールの初期速度
    double v_p[3] = {0.0,0.0,0.0};//1ステップ前
    //double a[3] = {0.0,0.0,0.0};//ボールの加速度
    double a_p[3] = {0.0,0.0,0.0};
    
    double tau = 0.0;
    
    int i,j;
    
    //initilization(p);
    Ball ball(5.0,0.1);
    ///*
    abs = adbsolution(p,tp); //２点間の絶対値の算出
    for(j=0;j<3;j++){
        p_hat[j] = (tp[j] - p[j]) / abs; //進行方向の単位ベクトル
    }
    //*/
   
    for(i = 0;i < 1000;i+=1){
        
        //abs = adbsolution(p,tp); //２点間の絶対値の算出
        for(j = 0;j < 3;j++){
            //p_hat[j] = (tp[j] - p[j]) / abs; //進行方向の単位ベクトル
            if(p[0] < tp[0]){
                p_hat[0] = p_hat[1] = (tp[j] - p[j]) / abs;
            }
            else if(p[0] > tp[0]){
                p_hat[0] = p_hat[1] = (tp[j] - p[j]) / abs;
            }
            
            tau = Kp * (tp[j] - p[j]) + Ki * 0.5 * (tp[j] - p[j]) * st - Kd * (p[j] - p_p[j]) / st;
            //cout << tau << "\n" << endl;
            //a[j] = tau / 0.5;
            v[j] = 0.5 * (ball.acceleration(tau) * p_hat[j] + a_p[j]) * st;
            p[j] += 0.5 * (v[j] + v_p[j]) * st;
            
            v_p[j] = v[j];
            p_p[j] = p[j];
            //a_p[j] = a[j];
            a_p[j] = ball.acceleration(tau) * p_hat[j];
            
        }
        
        cout << "(" << p[0] << "," << p[1] << ")\n" << endl;
        //cout << "(" << p_hat[0] << "," << p_hat[1] << ")\n" << endl;
        //cout << "(" << v[0] << "," << v[1] << ")\n" << endl;
        //cout << "//" <<endl;
        
    }
    
}

void OneDimention(){
    double Kp = 800.0,Ki = 0.0,Kd = 0.0;
    
    double x_t = 5.0,x = 0.0,x_p = 0.0;
    double a = 0.0,a_p = 0.0;
    double v = 0.0, v_p = 0.0;
    double f = 0.0;
    
    double m = 0.5;
    
    int i;
    
    for(i = 0;i<1000;i++){
        f = Kp * (x_t - x) + Kd * ((x - x_p) / st) - Ki * 0.5 * (x_t - x) * st;
        a = f / m;
        v = 0.5 * (a + a_p) * st;
        x += 0.5 * (v + v_p) * st;
        
        a_p = a;
        v_p = v;
        x_p = x;
        
        //cout << f << "\n" << endl;
        cout << x <<  "  /  " << f << "\n" << endl;
    }
}
