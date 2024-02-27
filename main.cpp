/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PwmOut.h"
#include "ThisThread.h"
#include "Thread.h"
#include "mbed.h"


// Blinking rate in milliseconds
#define ORDEN     8

Thread hilo_filtro;
void filtro(void);

int j;
double Uk;
double Xk[ORDEN];
double num[ORDEN+1]= {0.005069883484836,  0.029358162747516,   0.110743791265797,   
                      0.219340680905496,  0.270974963192709,   0.219340680905496,
                      0.110743791265797,  0.029358162747516,   0.005069883484836};
double s;

AnalogIn U(A0);

PwmOut   Yk(D3);
DigitalOut Verificar(D2);

int main()
{
    hilo_filtro.start(filtro);
    Yk.period_ms(1);
    while (true) {
    }
}

void filtro (void)
{
    while(true)
    {
        Verificar = 1;
        Uk = U;
        s = Uk*num[0];
        for (j=0;j<ORDEN;j++)
        {
            s += num[j+1] * Xk[j];
        }
        Yk.write(s);

        for(j=ORDEN-1; j>0; j--)
        {
            Xk[j] = Xk[j-1];
        }
        Xk[0] = Uk;
        Verificar =0;
        ThisThread::sleep_for(1ms);

    }


}


