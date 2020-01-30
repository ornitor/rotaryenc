


float   valorFinal[8][2] = 
{
    10.00, 40.94,
    20.00, 50.50,
    30.00, 59.81,
    40.00, 68.56,
    50.00, 76.56,
    60.00, 84.50,
    70.00, 91.69,
    90.00, 100.00
};


float estimadoPWM(float tempi)
{
   for(int i=0;i<8;i++){
        if(valorFinal[i][1] > tempi){
              return valorFinal[i-1][0] + (valorFinal[i][0] - valorFinal[i-1][0])*(tempi - valorFinal[i-1][1])/(valorFinal[i][1] - valorFinal[i-1][1]);
        }
   }
}


float overtab[3][3] = {
    100, 70, 74.37,
    150, 70,  78.50,
    200, 70, 81.87
/*    Temperatura Partida 44.00
 : 0.00
tempo chegada:144  Atraso:118
1 tempMax: 81.87 targetTemp:70.00*/

};
