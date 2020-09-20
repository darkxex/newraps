#include <iostream>
#include <stdio.h>
#include <math.h>
#define e 0.001
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

void Derivacion(int matriz1[][2], int matriz2[][2]){
    int x;
    int c=0;
    for(x=0 ; x<100;x++){
        if(matriz1[x][0]>0){
            c++;
        }
    }
    for(x=0; x<c;x++){
        matriz2[x][0]=matriz1[x][0]*matriz1[x][1];
        matriz2[x][1]=matriz1[x][1]-1;


    }
    }
float magia(int matriz1[][2],float tolerancia){
    int x;
    int c=0;
    float polinomio = 0;
    for(x=0 ; x<20;x++){
         polinomio = polinomio+ matriz1[x][0]*pow(tolerancia,matriz1[x][1]);
    }
    return polinomio;


    }
    void eliminar(int n, float a[])
{int i,j,k;
 for(i=0;i<n;i++)
  for(j=i+1;j<n;j++)
   if(a[i]==a[j])
   {for(k=j;k>n-1;k++)
    {a[k]=a[k+1];
    n=n-1;
    j=i;
   }
}
}
void ordenar(int n, float a[])
{int i, j;
float temp;
for(i=0;i<n;i++)
 for(j=n-1;j>=i;j--)
  if(a[j-1]>a[j])
  {temp=a[j-1];
   a[j-1]=a[j];
   a[j]=temp;
  }
}
std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}
double round(double x, int n){
	int d = 0;
	if((x * pow(10, n + 1)) - (floor(x * pow(10, n))) > 4) d = 1;
	x = (floor(x * pow(10, n)) + d) / pow(10, n);
	return x;
}
void replace(std::string& subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}// funcion reemplazar una palabra por otra, por cada vez que la encuentra

// for string delimiter
vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}



int main(int argc, char** argv)
{


    int array[100][2];
    int x,z;
    for (x=0;x<20;x++){
        for(z=0;z<2;z++){
                array[x][z]=0;

        }
    }
    int dematriz[100][2];
    for (x=0;x<20;x++){
        for(z=0;z<2;z++){
            dematriz[x][z]=0;
        }}





 float xsupuesto = 0.02;

      string reader = "x**3 + x**2 + 3";
        if(argv[1] != NULL)
        {
         reader = argv[1];

        }
        else{
            cout<<"Como no has ingresado argumento se va a ejecutar el polinomio de muestra ("<<reader<<")"<<endl;
        }


    cout<<"Leyendo: " << reader<< endl;
    //cout<<"***************************************"<< endl;
    replace (reader," ","");
    reader = " " + reader + " ";
    replace(reader,"X","x");
    replace(reader,"-"," - "); //cada vez que encuentre un - agrega espacio a la izquierda y la dereccha
    replace(reader,"+"," + "); //cada vez que encuentre un + agrega espacio a la izquierda y la dereccha
    replace(reader,"x ","x**1 ");

    string extras = reader;
    int counter = 0;
    int potenciador,potenciador2;
    int masmenos, masmenos2;
    int tempcut;
    int multiplicador,multiplicadorcut;
    x=0;
            while ( counter != -1){  // cada vez que encuentre un x** para avanzar
                    potenciador = reader.find("x**",counter); // empieza a buscarlo en 0
            tempcut = potenciador + 3;
            potenciador2 = reader.find(" ",potenciador);
            masmenos = reader.rfind("-",potenciador); //buscar el signo menos derecha a izquierda

            masmenos2 = reader.rfind("+",potenciador); // buscar el signo mas de derecha a izquirda


            if (potenciador2 == -1){
                    potenciador2 = reader.length();
            break;
            }
            if(masmenos == -1 && masmenos2 == -1 ){
        //cout<< "signo:" << "+"<<endl;
        multiplicador = reader.rfind (" ",potenciador);
        multiplicadorcut = multiplicador+1;

        if( multiplicadorcut == potenciador){
               // cout<< "Numero que multiplica X: "<< "1" <<endl;
                array[x][0]=1;
                x++;}
        else{
            //cout<< "Numero que multiplica X: "<< reader.substr (multiplicadorcut,potenciador - multiplicadorcut)<<endl;
            array[x][0]=atoi(reader.substr (multiplicadorcut,potenciador - multiplicadorcut).c_str());
            x++;

        }
    }
    else if(masmenos2 > masmenos){
            //cout<< "signo:" << "+"<<endl;
            multiplicador = reader.rfind (" ",potenciador);
            multiplicadorcut = multiplicador+1;
            if( multiplicadorcut == potenciador){
                 //cout<< "Numero que multiplica X: "<< "1" <<endl;
                 array[x][0]=1;
                 x++;
                 }
            else{
               // cout<< "Numero que multiplica X: "<<reader.substr (multiplicadorcut,potenciador - multiplicadorcut)<<endl;
                array[x][0]=atoi(reader.substr (multiplicadorcut,potenciador - multiplicadorcut).c_str());
                x++;
                }}
    else {
            //cout<< "signo:" << "-"<<endl;
            multiplicador = reader.rfind (" ",potenciador);
            multiplicadorcut = multiplicador+1;
            if( multiplicadorcut == potenciador)
                { //cout<< "Numero que multiplica X: "<< "1" <<endl;
                array[x][0]=-1;
                x++;}
            else
                {//cout<< "Numero que multiplica X: "<< reader.substr (multiplicadorcut,potenciador - multiplicadorcut)<<endl;
                array[x][0]=atoi(reader.substr (multiplicadorcut,potenciador - multiplicadorcut).c_str());
                array[x][0]=array[x][0]*-1;
                x++;}}

            counter = potenciador + 1;


//cout <<"X potencia a: "<< reader.substr(tempcut ,potenciador2 - tempcut )<<endl;
array[x-1][1]=atoi(reader.substr(tempcut ,potenciador2 - tempcut ).c_str());



//cout << endl;


}



//cout << endl;
//cout <<"**********************************"<< endl;
   int valorfinal = 0;
   string final = "";
    string delimiter = " ";

    string tester =  " +" + reader;

    vector<string> v = split (tester, delimiter);
     for(int x = 0;x < v.size();x++)
     {
         if (v[x].find("x**") != -1)
         {
            v[x] = "0";
         }

         stringstream intValue( v[x]);

    int number = 0;
    intValue >> number;

         //cout<< "Constante: "<< v[x] << endl;
         final = final + v[x];
         if (v[x - 1] == "-")
         {valorfinal = valorfinal - number;}
         else
         {valorfinal = valorfinal + number;}

     }
//cout<< "Valor final de constantes: "<< valorfinal<<endl;
array[x][0]=valorfinal;






#define f(x) pow(x,3)+ pow(x,2) - 4*x+ 1
#define df(x) 3*x*x + 2*x - 4



   /* float x0,x1,f0,f1,df0;
    int i=0;
     //precisión
    x0 = -2;
    do{

        f0=f(x0);
        df0=df(x0);
        x1=x0-(f0/df0);
        f1=f(x1);
        x0=x1;
        i++;
        printf("No of iteration=%d\t",i);
        printf("root=%f\t",x1);
        printf("value of function=%f\n",f1);
       }while (fabs(f1)>e);*/



//cout<<endl;
//}//Aqui se experimento la impresion de los datos que acompañan a x y los grados ,respectivamente array[x][0] y array[x][1]}
 for(x=0;x<20;x++){
 //   cout<<" "<<array[x][0];
    }
//cout<<endl;
 Derivacion(array,dematriz);
 for(x=0;x<20;x++){
   // cout<<" "<<array[x][1];

 }
//cout<<endl;
for(x=0;x<20;x++){
    //    cout<<" "<<dematriz[x][0];

}
//cout<<endl;
for(x=0;x<20;x++){

   // cout<<" "<<dematriz[x][1];
}
//cout<<endl;
//cout << "magia polinomio: "<< magia(array,xsupuesto)<<endl;
//cout << "magia derivada: "<< magia(dematriz,xsupuesto)<<endl;
//cout<<"Prueba 1 de eliminar Define: "<<endl;
//pow(x,3)+ pow(x,2) - 4*x+ 1

cout<<"****************************************"<<endl;
vector<float> colour;
float despues ;
string antes = "";
string antes2 = "";
int contadorx = 0;
  for (float x = -50;x<50;x=x+0.1)

    {float x0,x1,f0,f1,df0;
    int i=0;
     //precisión
    x0 = x;
    do{

        f0=magia(array,x0);
        df0=magia(dematriz,x0);
        x1=x0-(f0/df0);
        f1=magia(array,x1);
        x0=x1;
        i++;
      //  printf("No of iteration=%d\t",i);
    //printf("root=%f\t",x1);
      // printf("value of function=%f\n",f1);
       }while (fabs(f1)>e);
 //printf("root=%f\t",x1);

 string temp = Convert(round(x1,1));
  //cout << "tester "<< temp << endl;
 if (antes != temp )
 {antes = temp;

 contadorx++;
  //cout<< contadorx<<" "<<x1<<endl;
  if (temp != "nan")
 colour.push_back(x1);

 }



 }
 std::sort(colour.begin(), colour.end());
//std::sort(arreglof, arreglof + 100, std::greater<float>());
 for(int x = 0;x<colour.size();x++)
{
string temp2 = Convert(round(colour[x],1));
 if (antes2 != temp2 )
 {antes2 = temp2;



  //cout<< contadorx<<" "<<x1<<endl;
 if (colour[x] <0.000005 && colour[x] > 0)
  {
      colour[x] = 0;
  }

cout<<" Raiz Real: "<<colour[x]<<endl;
 }


/*
if (despues != colour[x])
 {
  cout<<"despues: " << despues<< " colour " << colour[x]<<endl;

if (x >0){
    if (round(colour[x],2) == round(colour[x - 1],2))
{

    colour[x] = NULL;

}
              }

  if (colour[x] != NULL)
  {
       if (colour[x] <0.000005 && colour[x] > 0)
  {
      colour[x] = 0;
  }
      cout<< "Raices Reales: " <<colour[x]<<endl;}

despues = colour[x];
 }
*/



}
cout<<"****************************************"<<endl;

 return 0;}
