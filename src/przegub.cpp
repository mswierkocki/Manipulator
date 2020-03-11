#include "Przegub.h"

Wektor Przegub::ObliczPolozenie(Wektor P){
  Wektor T(dlugosc, 0);
  float rad = kat*3.14/180;
  float R[2][2];
  R[0][0] = cos(rad);
  R[0][1] = -sin(rad);
  R[1][0] = sin(rad);
  R[1][1] = cos(rad);
  T = T+P;

  return Wektor((R[0][0]*T.x)+(R[0][1]*T.y),(R[1][0]*T.x)+(R[1][1]*T.y));//zwrocenie wartosci przeksztalcenia

}
