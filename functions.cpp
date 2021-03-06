#include "functions.h"

void con_bin(string name,string binario)
{

    short num;
    short int num_bi[8];
    //cout << name << "\n\n";

    fstream doc (name.c_str(), fstream :: in);
    char carac;

    if (!doc.fail()){
        fstream bi (binario.c_str(), fstream ::out | fstream::binary);

        doc.get(carac);
        do{

            num = int (carac);

            //cout << num << "\t\t" << carac << "\t\t";

            for (int i = 7; i >= 0 ;i--){
                //cout << num%2 << "\n";
                if (num%2 > 0){
                    num_bi[i] = 1;
                    num /=2;
                }
                else {
                    num_bi[i] = 0;
                    num /=2;
                }
            }
            //for (int i = 0; i < 8 ;i++) cout << num_bi[i];
            //cout << endl;

            for (int i = 0; i < 8 ;i++) bi << num_bi[i];
            doc.get(carac);

        }while (!doc.eof());
        bi.close();
    }
    else cout << "ERROR!! En la lectura del archivo\n\n\n";

    doc.close();
}

void metodo_1_codi(string name, short n,string save){

    fstream doc (name.c_str(), fstream :: in | fstream::ate);

    char carac;
    long long int num_caracteres = doc.tellg();
    int s1,s0,step;
    doc.seekg(0);
    //cout << carac << "\t " << num_caracteres << " HOLA\n\n\n";

    if (!doc.fail()){
        fstream codi(save.c_str(), fstream ::out | fstream::binary);

        for (int i = 0; i < n;i++){
            doc.get(carac);
            if (carac == '0') codi << '1';
            else if (carac == '1') codi << '0';
        }

        while(true){
            s1 = 0;
            s0 = 0;
            num_caracteres = doc.tellg();
            num_caracteres -= n;
            //cout << "\n\n"<< num_caracteres <<"\n\n";
            doc.seekg(num_caracteres);
            for (int a = 0; a < n;a++){
                doc.get(carac);
                if (carac == '0') s0 ++;
                else if (carac == '1') s1++;
            }


            if (s1 == s0){
                for (int a = 0; a < n;a++){
                    doc.get(carac);
                    if (carac == '0') codi << '1';
                    else if (carac == '1') codi << '0';
                    if (doc.eof()) break;
                }
            }
            else if (s0 > s1){
                step = 0;
                for (int a = 0; a < n;a++){
                    if (step != 1){
                        doc.get(carac);
                        codi << carac;
                        step++;
                    }
                    else {
                        doc.get(carac);
                        if (carac == '0') codi << '1';
                        else if (carac == '1') codi << '0';
                        step = 0;
                    }
                    if (doc.eof()) break;
                }
            }
            else if(s1>s0){
                step = 0;
                for (int a = 0; a < n;a++){
                    if (step != 2){
                        doc.get(carac);
                        codi << carac;
                        step++;
                    }
                    else {
                        doc.get(carac);
                        if (carac == '0') codi << '1';
                        else if (carac == '1') codi << '0';
                        step = 0;
                    }
                    if (doc.eof()) break;
                }
            }

            if (doc.eof()) break;
        }
        codi.close();
    }
    else cout << "ERROR!! En la lectura del archivo\n\n\n";

    doc.close();
    remove (name.c_str());
}

void metodo_1_deco(string name, short n,string bi)
{
    fstream doc (name.c_str(), fstream :: in);

    char carac;
    int s1,s0,step;
    //cout << carac << "\t " << num_caracteres << " HOLA\n\n\n";
    int vec[n];

    if (!doc.fail()){
        fstream codi(bi.c_str(), fstream ::out | fstream::binary);

        for (int i = 0; i < n;i++){
            doc.get(carac);
            if (carac == '0') {
                codi << '1';
                vec[i] = 1;
            }
            else if (carac == '1') {
                codi << '0';
                vec[i] = 0;
            }
        }

        while (true){

            s1 = 0;
            s0 = 0;
            for (int a = 0; a < n;a++){
                if (vec[a] == 0) s0 ++;
                else if (vec[a] == 1) s1++;
            }
            if (s1 == s0){
                for (int a = 0; a < n;a++){
                    doc.get(carac);
                    if (carac == '0') {
                        codi << '1';
                        vec[a] = 1;
                    }
                    else if (carac == '1') {
                        codi << '0';
                        vec[a] = 0;
                    }
                    if (doc.eof()) break;
                }
            }
            else if (s0 > s1){
                step = 0;
                for (int a = 0; a < n;a++){
                    if (step != 1){

                        doc.get(carac);
                        codi << carac;
                        if (carac == '0') vec[a] = 0;
                        else if (carac == '1') vec[a] = 1;
                        step++;
                    }
                    else {

                        doc.get(carac);
                        if (carac == '0') {
                            codi << '1';
                            vec[a] = 1;
                        }
                        else if (carac == '1') {
                            codi << '0';
                            vec[a] = 0;
                        }
                        step = 0;
                    }
                    if (doc.eof()) break;
                }
            }
            else if(s1>s0){
                step = 0;
                for (int a = 0; a < n;a++){
                    if (step != 2){

                        doc.get(carac);
                        codi << carac;
                        if (carac == '0') vec[a] = 0;
                        else if (carac == '1') vec[a] = 1;
                        step++;
                    }
                    else {

                        doc.get(carac);
                        if (carac == '0') {
                            codi << '1';
                            vec[a] = 1;
                        }
                        else if (carac == '1') {
                            codi << '0';
                            vec[a] = 0;
                        }
                        step = 0;
                    }
                    if (doc.eof()) break;
                }
            }
            //cout << doc.tellg() << "\n";
            if (doc.eof()) break;
        }
        codi.close();
    }
    else cout << "ERROR!! En la lectura del archivo \n\n\n";

    doc.close();
    remove (name.c_str());
}

void bin_tex(string name, string deco)
{
    fstream doc(name.c_str(), fstream :: in);

    fstream de(deco.c_str(), fstream ::out);

    char carac;
    int mul,num;
    int vec[8];   

    while(true){
        mul = 128;
        num = 0;
        for (int a = 0; a < 8;a++){
            doc.get(carac);
            if (carac == '0') vec[a] = 0;
            else if (carac == '1') vec[a] = 1;
        }

        if(doc.eof()) break;

        for (int a = 0; a < 8;a++){
            if (vec[a] == 1) {
                num += mul;
            }
            mul /= 2;
        }
        carac = char(num);
        cout << carac;
        de << carac;

    };

    doc.close();
    de.close();

   remove (name.c_str());

}

void cambio(string save, string name)
{
    fstream doc(save.c_str(), fstream::in);
    fstream cambio(name.c_str(), fstream ::out | fstream::binary);

    char carac;
    int mul,num;
    int vec[8];

    while(true){
        mul = 128;
        num = 0;
        for (int a = 0; a < 8;a++){
            doc.get(carac);
            if (carac == '0') vec[a] = 0;
            else if (carac == '1') vec[a] = 1;
        }

        if(doc.eof()) break;

        for (int a = 0; a < 8;a++){
            if (vec[a] == 1) {
                num += mul;
            }
            mul /= 2;
        }

        if (num == 26) num =45;

        //cout << num << "\t\t" << char (num) << "\n";
        carac = char(num);
        cout << carac;
        cambio << carac;

    }
    doc.close();
    cambio.close();

    remove(save.c_str());
}

void retorno(string name_24, string save)
{
    fstream doc(name_24.c_str(), fstream::in | fstream::ate);
    fstream retorno(save.c_str(), fstream ::out | fstream::binary);

    int num_car = doc.tellg();
    doc.seekg(0);

    cout<<num_car << "\n\n";

    char carac;
    int num, cont = 0;
    int vec[8];

    // EL TRUCO ESTA QUE CUADNO EL NUMERO ES NEGATIVO SE LE ADICIONAN 256

    while(cont != num_car){
        //cout << "Hola";
        doc.get(carac);
        //if (carac == char (26)) cout << "AQUI ES HPPPP";
        num = int(carac);
        if (num < 0)num += 256;
        cout << num << "\t\t";

        for (int i = 7; i >= 0 ;i--){
            //cout << num%2 << "\n";
            if (num%2 > 0){
                vec[i] = 1;
                num /=2;
            }
            else {
                vec[i] = 0;
                num /=2;
            }
        }

        //for (int i = 0; i < 8 ;i++) cout << vec[i];
        cout << "\t\t" << carac << endl;

        for (int i = 0; i < 8 ;i++) retorno << vec[i];

        //cout << "\t" << doc.tellg() << "\n";
        cont++;
    }
    doc.close();
    retorno.close();
}

/*_____________________________________________________________________________________________________

METODO 2  */

void metodo_2_codi(string name, int n, string save)
{
    fstream doc (name.c_str(), fstream :: in);

    fstream codi(save.c_str(), fstream ::out | fstream::binary);

    char vec[n];

    while (!doc.eof()){

        for (int i = 0; i < n; i++){
            if (doc.eof()) break;
            doc.get(vec[i]);
        }

        codi << vec[n-1];

        for (int i = 0; i < n-1; i++) codi << vec[i];
    }

    doc.close();
    codi.close();
    remove(name.c_str());
}

void metodo_2_deco(string name, int n, string bi)
{
    fstream doc (name.c_str(), fstream :: in);
    fstream deco(bi.c_str(), fstream ::out | fstream::binary);
    char vec[n];
    while (!doc.eof()){
        for (int i = 0; i < n; i++){
            if (doc.eof()) break;
            doc.get(vec[i]);
            //cout << vec[i];
        }
        //cout << "\t\t" << vec[1];
        deco << vec[1];
        for (int i = 2; i < n; i++){
            deco << vec[i];
            //cout << vec[i];
        }
        //cout << vec[0] << endl;
        deco << vec[0];
    }
    doc.close();
    deco.close();
    //remove(name.c_str());
}







//while (true) {
//    //cout << num_caracteres << "\t\t";
//    num_caracteres += n ;
//    //cout << num_caracteres << "\t\t" << final << "\t";


//    if (num_caracteres > final) {
//        int dif = num_caracteres - final;
//        num_caracteres = final;
//        n -= dif;
//    }

//    doc.seekg(num_caracteres);

//    doc.get(carac);

//    codi << carac;

//    num_caracteres -= n - 2;
//    doc.seekg(num_caracteres);

//    for (int i = 1;i < n;i++ ){

//        //cout << i << "\t";

//        doc.get(carac);
//        codi << (carac);
//    }

//    num_caracteres = doc.tellg();


//    if (num_caracteres == -1) break;
//    //cout << endl;
//}
