#include <iostream>
#include <stdio.h>
#include <math.h>
#define e 0.001
#include <sstream>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
#include <iomanip>
#include <stdlib.h>


#define maxiter 500
using namespace std;



int roots(double *a,int n,double *wr,double *wi)
{
    double sq,b2,c,disc;
    int i,m,numroots;

    m = n;
    numroots = 0;
    while (m > 1) {
        b2 = -0.5*a[m-2];
        c = a[m-1];
        disc = b2*b2-c;
        if (disc < 0.0) {
            sq = sqrt(-disc);
            wr[m-2] = b2;
            wi[m-2] = sq;
            wr[m-1] = b2;
            wi[m-1] = -sq;
            numroots+=2;
        }
        else {
            sq = sqrt(disc);
            wr[m-2] = fabs(b2)+sq;
            if (b2 < 0.0) wr[m-2] = -wr[m-2];
            if (wr[m-2] == 0)
                wr[m-1] = 0;
            else {
                wr[m-1] = c/wr[m-2];
                numroots+=2;
            }
            wi[m-2] = 0.0;
            wi[m-1] = 0.0;
        }
        m -= 2;
    }
    if (m == 1) {
       wr[0] = -a[0];
       wi[0] = 0.0;
       numroots++;
    }
    return numroots;
}

void deflate(double *a,int n,double *b,double *quad,double *err)
{
    double r,s;
    int i;

    r = quad[1];
    s = quad[0];

    b[1] = a[1] - r;

    for (i=2;i<=n;i++){
        b[i] = a[i] - r * b[i-1] - s * b[i-2];
    }
    *err = fabs(b[n])+fabs(b[n-1]);
}

void find_quad(double *a,int n,double *b,double *quad,double *err, int *iter)
{
    double *c,dn,dr,ds,drn,dsn,eps,r,s;
    int i;

    c = new double [n+1];
    c[0] = 1.0;
    r = quad[1];
    s = quad[0];
    eps = 1e-15;
    *iter = 1;

    do {
        if (*iter > maxiter) break;
        if (((*iter) % 200) == 0) {
            eps *= 10.0;
		}
		b[1] = a[1] - r;
		c[1] = b[1] - r;

		for (i=2;i<=n;i++){
			b[i] = a[i] - r * b[i-1] - s * b[i-2];
			c[i] = b[i] - r * c[i-1] - s * c[i-2];
		}
		dn=c[n-1] * c[n-3] - c[n-2] * c[n-2];
		drn=b[n] * c[n-3] - b[n-1] * c[n-2];
		dsn=b[n-1] * c[n-1] - b[n] * c[n-2];

        if (fabs(dn) < 1e-10) {
            if (dn < 0.0) dn = -1e-8;
            else dn = 1e-8;
        }
        dr = drn / dn;
        ds = dsn / dn;
		r += dr;
		s += ds;
        (*iter)++;
    } while ((fabs(dr)+fabs(ds)) > eps);
    quad[0] = s;
    quad[1] = r;
    *err = fabs(ds)+fabs(dr);
    delete [] c;
}

void diff_poly(double *a,int n,double *b)
{
    double coef;
    int i;

    coef = (double)n;
    b[0] = 1.0;
    for (i=1;i<n;i++) {
        b[i] = a[i]*((double)(n-i))/coef;
    }
}


void recurse(double *a,int n,double *b,int m,double *quad,
    double *err,int *iter)
{
    double *c,*x,rs[2],tst,e1,e2;

    if (fabs(b[m]) < 1e-16) m--;
    if (m == 2) {
        quad[0] = b[2];
        quad[1] = b[1];
        *err = 0;
        *iter = 0;
        return;
    }
    c = new double [m+1];
    x = new double [n+1];
    c[0] = x[0] = 1.0;
    rs[0] = quad[0];
    rs[1] = quad[1];
    *iter = 0;
    find_quad(b,m,c,rs,err,iter);
    tst = fabs(rs[0]-quad[0])+fabs(rs[1]-quad[1]);
    if (*err < 1e-12) {
        quad[0] = rs[0];
        quad[1] = rs[1];
    }

    if (((*iter > 5) && (tst < 1e-4)) || ((*iter > 20) && (tst < 1e-1))) {
        diff_poly(b,m,c);
        recurse(a,n,c,m-1,rs,err,iter);
        quad[0] = rs[0];
        quad[1] = rs[1];
    }
    delete [] x;
    delete [] c;
}

void get_quads(double *a,int n,double *quad,double *x)
{
    double *b,*z,err,tmp;
    double xr,xs;
    int iter,i,m;

    if ((tmp = a[0]) != 1.0) {
        a[0] = 1.0;
        for (i=1;i<=n;i++) {
            a[i] /= tmp;
        }
    }
    if (n == 2) {
        x[0] = a[1];
        x[1] = a[2];
        return;
    }
    else if (n == 1) {
        x[0] = a[1];
        return;
    }
    m = n;
    b = new double [n+1];
    z = new double [n+1];
    b[0] = 1.0;
    for (i=0;i<=n;i++) {
        z[i] = a[i];
        x[i] = 0.0;
    }
    do {
        if (n > m) {
            quad[0] = 3.14159e-1;
            quad[1] = 2.78127e-1;
        }
        do {
            for (i=0;i<5;i++) {
                find_quad(z,m,b,quad,&err,&iter);
                if ((err > 1e-7) || (iter > maxiter)) {
                    diff_poly(z,m,b);
                    recurse(z,m,b,m-1,quad,&err,&iter);
                }
                deflate(z,m,b,quad,&err);
                if (err < 0.001) break;
                quad[0] = (8) - 4.0;
                quad[1] = (8) - 4.0;
            }
            if (err > 0.01) {
                cout << "Error! Error de convergencia en cuadratica x^2 + r*x + s." << endl;
                cout << "Ingresar nuevo valor para 'r': ";
                cin >> quad[1];
                cout << "Ingresar nuevo valor para 's' ( 0 to exit): ";
                cin >> quad[0];
                if (quad[0] == 0) exit(1);
            }
        } while (err > 0.01);
        x[m-2] = quad[1];
        x[m-1] = quad[0];
        m -= 2;
        for (i=0;i<=m;i++) {
            z[i] = b[i];
        }
    } while (m > 2);
    if (m == 2) {
        x[0] = b[1];
        x[1] = b[2];
    }
    else x[0] = b[1];
    delete [] z;
    delete [] b;
}
void Derivacion(float matriz1[][2], float matriz2[][2],int l){
    int x;
    for(x=0; x<l;x++){
        matriz2[x][0]=matriz1[x][0]*matriz1[x][1];
        matriz2[x][1]=matriz1[x][1]-1;
        }
    }

float magia(float matriz1[][2],float tolerancia, int largo){
    int x;
    int c=0;
    float polinomio = 0;
    for(x=0 ; x<largo;x++){
            if(matriz1[x][1]!=0){polinomio = polinomio+ matriz1[x][0]*pow(tolerancia,matriz1[x][1]);}
            else{
                polinomio=polinomio+matriz1[x][0];
            }
    }
    return polinomio;


    }
/*void Haciendocte(int matriz[][2],int p){
    int l;
    //Reduciendo la expresion en un grado, puesto que una de las raices es 0
    //Se supone que en la otra matriz estan las soluciones
    for(l=0;l<p;l++){
        matriz[l][1]=matriz[l][1]-1;

    }

}*/
void CalculodeDivisores(float arreglo[],float arreglo2[],float matriz[][2],float grado,int largo){
    int i;
    int k;
    int calculo=0;

    for(k=0;k<largo;k++){
            if(matriz[k][1]==0){
                calculo=matriz[k][0];
                break;
            }
    }

    int a=0;
    int resto=0;
    for(i=1;i<=calculo;i++){
        resto=calculo%i;
        if(resto==0){
            arreglo[a]=float(i);
            a++;
        }
    }
    for(i=0;i<largo;i++){
        if(matriz[i][1]==grado){
                calculo=int(matriz[i][0]);
                break;
        }
    }
    int b=0;
    for(i=1;i<=calculo;i++){
        resto=calculo%i;
        if(resto==0){
            arreglo2[b]=float(i);
            b++;
        }
    }
}


void EncontrarCtes(float matriz[][2],int largo){
    //Agregar procedimiento de raiz 0
    int t=0,m=0,j=-1;
    for(t=0;t<largo;t++){
        if(matriz[t][1]==0){
            //Existe por
            j=1;
        }


    }
    if(j!=1){
    int l;
            for(l=0;l<largo;l++){
                if(matriz[l][1]!=-1){
                        matriz[l][1]=matriz[l][1]-1;}

                }EncontrarCtes(matriz,largo);}

}

int Contador(float arreglo[],int a){
    int i=0,cont=0;
    for(i=0;i<a;i++){
        if(arreglo[i]!=0){
            cont++;
        }
        else{
            break;
        }
    }
    return cont;
}

void Rellenedador0(float Soluciones[],float p,float g){
    int i;
    //l=0;
    for(i=0;i<(p-g);i++){
            Soluciones[i]=0;

    }

}

void RellenarPRaices(float arreglo[],float arreglo2[],float arreglo3[],int a,int b,int c){
    int d=0,i=0,j=0;
    for(i=0;i<a;i++){
        for(j=0;j<b;j++){
                    arreglo3[d]=(arreglo[i])/(arreglo2[j]);
                    d++;
                    arreglo3[d]=((arreglo[i])/(arreglo2[j]))*(-1);
                    d++;
        }
    }
}

float  BusquedaDelMayorGrado(float matriz[][2],int c){
    int r=0,cont=-1;
    float countsup=0;
    /*while(r==0){
            if(matriz[cont][1]!=-1){
                r++;
            }
            cont++;
    }*/
    for(r=0;r<c;r++){
            if(matriz[r][1]>=countsup){
                    countsup=matriz[r][1];

            }
        }
        return countsup;

}
void ReduccionSemejanzas(float matriz[][2]){
    int cont=-1,position;
    float countsup=0,suma;
    int r=0;
    while(r==0){
            if(matriz[cont][1]==-1){
                r++;
            }
            cont++;
    }
    for(r=0;r<cont;r++){
            if(matriz[r][1]>countsup){
                    countsup=matriz[r][1];
            }
    }
    for(r=1;r<=countsup;r++){
        position=-1;
        suma=0;
        for(int i=0;i<cont;i++){
            if(matriz[i][1]==r){
                    suma=suma+matriz[i][0];
                    matriz[i][1]=-1;
                    if(position==-1){
                            position=i;
                    }
            }
        }

        if(position!=-1){
                matriz[position][0]=suma;
                matriz[position][1]=r;

        }

    }
    for(int i=0;i<cont;i++){
            if(matriz[i][0]==0){
                matriz[i][1]=-1;
                }
        }
    }

void CorrerCosas(float matriz[][2],int p){
    int r=0,cont=-1,a=0;
    float matriz2[p][2];
    for(r=0;r<p;r++){
        matriz2[r][1]=-1;}

    for(r=0;r<p;r++){
            if(matriz[r][1]!=-1){
                matriz2[a][0]=matriz[r][0];
                matriz2[a][1]=matriz[r][1];
                a++;
            }

    }
    for(r=0;r<p;r++){
        matriz[r][0]=matriz2[r][0];
        matriz[r][1]=matriz2[r][1];
    }

}

int LargoOriginalMatriz(float matriz[][2]){
    int r=0,cont=-1,a=0;
    while(r==0){
            if(matriz[cont][1]==-1){
                r++;
            }
            cont++;
    }
    return cont;

}

void OrdenadorDeGrados(float matriz[][2],int g,float l){
    float matriz2[g][2];
    int i,j,a=0;
    float mayor=l,z=0;

    for(i=0;i<g;i++){
        matriz2[i][1]=-1;
    }
    for(i=0;i<g;i++){
        matriz2[i][0]=matriz[i][0];
        matriz2[i][1]=matriz[i][1];
    }
    for(z=mayor;z>0;z--){
        for(j=0;j<g;j++){
            if(matriz2[j][1]==z){
                    matriz[a][0]=matriz2[j][0];
                    matriz[a][1]=matriz2[j][1];
                    a++;
                }
        }
    }
}

bool Ruffini(float matriz[][2],int l,float a){
    int i=0;
    float k=float(matriz[0][0]);
    for(i=1;i<l;i++){
            if(matriz[i][1]!=-1){
            k=(k*a)+float(matriz[i][0]);}
    }
    //return k;
    if(k==0){
        return true;
    }
    else{
        return false;
    }

}
int Reduccion(float matriz[][2],float arreglo2[],int p,int l,float a,int j){
    int i=0;
    float arreglo[l];
    //for(i=0;i<l;i++){
    arreglo[i]=(matriz[i][0]);

    //}
    float k=matriz[0][0];
    for(i=1;i<l;i++){
            if(matriz[i][1]!=-1){
            k=(k*a)+(matriz[i][0]);
            arreglo[i]=k;}

    }
    //return k;
    cout<<"probando: "<<a<<endl;
    if(k==0){
        cout<<"si es raiz: "<<endl;
        arreglo2[j]=a;
        for(i=0;i<l;i++){
                matriz[i][1]=matriz[i][1]-1;
                matriz[i][0]=(arreglo[i]);

        }
        j++;
        return j;
    }
    else{
        cout<<"no lo es"<<endl;
        return j;
    }

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
     vector<float> Prueba;

    // Initialize vector with strings using push_back
    // command


    float array[100][2];
    float maxC;
    float maxG;
    int libre=0;




    int y=0,x,z;
    for (x=0;x<20;x++){
        for(z=0;z<2;z++){
                array[x][z]=-1;

        }
    }
    float dematriz[100][2];
    for (x=0;x<20;x++){
        for(z=0;z<2;z++){
            dematriz[x][z]=-1;
        }}





 float xsupuesto = -5;

      string reader = "4x**7+8x**6+9x**5+9x**4+5x**3+x**2";
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
                //cout<< "Numero que multiplica X: "<< "1" <<endl;
                array[x][0]=1;
                x++;}
        else{
            //cout<< "Numero que multiplica X: "<< reader.substr (multiplicadorcut,potenciador - multiplicadorcut)<<endl;
            array[x][0]=atof(reader.substr (multiplicadorcut,potenciador - multiplicadorcut).c_str());
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
                //cout<< "Numero que multiplica X: "<<reader.substr (multiplicadorcut,potenciador - multiplicadorcut)<<endl;
                array[x][0]=atof(reader.substr (multiplicadorcut,potenciador - multiplicadorcut).c_str());
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
                array[x][0]=atof(reader.substr (multiplicadorcut,potenciador - multiplicadorcut).c_str());
                array[x][0]=array[x][0]*-1;
                x++;}}

            counter = potenciador + 1;


//cout <<"X potencia a: "<< reader.substr(tempcut ,potenciador2 - tempcut )<<endl;
array[x-1][1]=atof(reader.substr(tempcut ,potenciador2 - tempcut ).c_str());



//cout << endl;


}



cout << endl;
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

if(valorfinal!=0){
    array[x][0]=float(valorfinal);
    array[x][1]=0;}

//cout<<endl;

//int divisoresC[valorfinal];






y=LargoOriginalMatriz(array);

float GradoOriginal;
GradoOriginal=BusquedaDelMayorGrado(array,y);

float Soluciones[int(GradoOriginal)];


#define f(x) pow(x,3)+ pow(x,2) - 4*x+ 1
#define df(x) 3*x*x + 2*x - 4

CorrerCosas(array,y);


EncontrarCtes(array,y);


float GradoActual;
GradoActual=BusquedaDelMayorGrado(array,y);

//cout<<"el grado es: "<<GradoActual<<endl;

//cout<<"La funcion ordenada es: ";
OrdenadorDeGrados(array,y,GradoActual);


//cout<<endl;

//cout<<"numero anterior:"<<endl;
/*for(x=0;x<y;x++){
        if(array[x][1]!=-1){
            cout<<" "<<array[x][0];
        }
}
cout<<endl;

cout<<"grado:"<<endl;
for(x=0;x<y;x++){
        if(array[x][1]!=-1){
            cout<<" "<<array[x][1];
        }
}*/

//cout<<endl;
libre=int(GradoOriginal-GradoActual);
//cout<<endl;

if(GradoOriginal>GradoActual){
    Rellenedador0(Soluciones,GradoOriginal,GradoActual);
}

 {double a[21],x[21],wr[21],wi[21],quad[2],err,t;
    int n,iter,i,numr;


    //cout << "Ingrese grado del polinomio (1 <= n <= 20): ";
    //cin >> n;
    n = GradoActual;
    if ((n < 1) || (n > 20)) {
        cout << "Error! Como maximo el grado debe ser 20: n = " << n << endl;
        return 1;
    }

    //cout << "Ingresar coeficientes,de mayor a menor" << endl;

    for (i=0;i<=n;i++) {

        //cout << "C[" << n-i << "] * x^" << n-i << " : "<<endl;
        bool flag=0;
        for(int j=0;j<y;j++){
                if(array[j][1]==(n-i)){
                        flag=1;
                        //cout<<"se activo la bandera: "<<n-i<<endl;
                        if(flag==1){
                                a[i]=double(array[j][0]);
                                //cout<<i<<" "<<a[i]<<endl;
                                break;

                                }


                }
                else{
                    //cout<<"no se activo"<<n-i<<endl;
                    a[i]=0;
                    //cout<<i<<" "<<a[i]<<endl;
                }
    }

        //cin >> a[i];
        if (a[0] == 0) {
            cout << "Error! El grado del polinomio no puede ser 0." << endl;
            return 0;
        }
    }
    if (a[n] == 0) {
        cout << "Error! La constante no puede ser 0." << endl;
        return 0;
    }

    quad[0] = 2.71828e-1;
    quad[1] = 3.14159e-1;

    get_quads(a,n,quad,x);
    numr = roots(x,n,wr,wi);

    cout << endl << "Raices (" << (numr+libre) << " encontradas):" << endl;

    cout.setf(ios::showpoint|ios::showpos|ios::left|ios::scientific);
    cout.precision(15);
    for (i=0;i<n;i++) {
        if ((wr[i] != 0.0) || (wi[i] != 0.0))
            cout << wr[i] << " " << wi[i] << "I" << endl;
    }
    if(libre>0){
        for(i=0;i<libre;i++){
        cout<<" "<<"0"<<endl;}
            }
    }
    cout<<"======Integrantes========"<<endl;
    cout<<"Mauricio Vargas"<<endl;
    cout<<"Angel Toloza"<<endl;
    cout<<"Mathias Caceres"<<endl;
 return 0;}
