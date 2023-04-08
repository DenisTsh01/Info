#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
class Iointerface{
    virtual istream &citire(istream &in)=0;
    virtual ostream &afisare(ostream &out)const=0;
};
class Vac:public Iointerface{
protected:
    int pret;
    int temp;
public:
    Vac(){
        this->pret=0;
        this->temp=0;
    }
    Vac(int pret,int temp){
        this->pret=pret;
        this->temp = temp;
    }
    Vac(const Vac &v){
        this->pret=v.pret;
        this->temp=v.pret;
    }
    Vac &operator=(const Vac &v){
        if(this!=&v)
        {
            this->pret=v.pret;
            this->temp=v.pret;
            return *this;
        }
    }


    istream &citire(istream &in){
        cout<<"Pret: ";in>>this->pret;
        cout<<"Temperatura optima: ";in>>this->temp;

        return in;
    }
    ostream &afisare(ostream &out)const
    {   out<<"Pretul este: "<<this->pret;
        out<<"Temperatura este: "<<this->temp;

        return out;
    }

    friend istream &operator>>(istream &in,Vac &v){return v.citire(in);}
    friend ostream &operator<<(ostream &out,const Vac &v){return v.afisare(out);}

    ~Vac(){}
};
class Gripa:virtual public Vac{
protected: string tulpina;
            bool ok;
public:


    Gripa():Vac(){
        this->tulpina="Nu";
        this->ok=0;
    }
    Gripa(string t,bool ok):Vac(pret,temp){
        this->tulpina = t;
        this->ok = ok;
    }
    Gripa (const Gripa &g):Vac(g){

        this->tulpina=g.tulpina;
        this->ok=g.ok;
    }
    Gripa &operator=(const Gripa &g){
        if(this!=&g){
            Vac::operator=(g);
            this->tulpina=g.tulpina;
            this->ok=g.ok;
            return *this;
        }
    }
    istream &citire(istream &in){
        Vac::citire(in);
        cout<<"Tulpina: ";in>>this->tulpina;
        cout<<"E recomandat ? (1/0): "; in>>this->ok;
        return in;
    }
    ostream &afisare(ostream &out)const{
        Vac::afisare(out);
        out<<"Tulpina: "<<this->tulpina;
        out<<"Este recomandata ?"<<this->ok;
        return out;
    }


    ~Gripa(){}
};

class Hepa:virtual public Vac{
protected: char tip;
    string mod;
public:


    Hepa():Vac(){
        this->tip='A';
        this->mod="muschi";
    }
    Hepa(char tip,string mod):Vac(pret,temp){
        this->tip = tip;
        this->mod = mod;
    }
    Hepa (const Hepa &g):Vac(g){

        this->tip=g.tip;
        this->mod=g.mod;
    }
    Hepa &operator=(const Hepa &g){
        if(this!=&g){
            Vac::operator=(g);
            this->tip=g.tip;
            this->mod=g.mod;
            return *this;
        }
    }
    istream &citire(istream &in){
        Vac::citire(in);
        cout<<"Tip hepatita: ";in>>this->tip;
        cout<<"Cum a fost facuta vaccinarea ? (intramuscular, subcutanat, intradermic): "; in>>this->mod;
        return in;
    }
    ostream &afisare(ostream &out)const{
        Vac::afisare(out);
        out<<"Tip hepatita: "<<this->tip;
        out<<"Cum a fost facuta vaccinarea : "<<this->mod;
        return out;
    }


    ~Hepa(){}
};

class Cov:virtual public Vac{
protected: vector <string> reactii;
    vector <string> medicamente;
    int m ;
    int r ;
    int eficienta;
public:


    Cov():Vac(){

        this->eficienta=0;
    }
    Cov(vector <string> reactii,vector <string> medicamente,int ef,int r, int m):Vac(pret,temp){
        this->reactii= reactii;
        this->medicamente = medicamente;
        this->eficienta = ef;
        this->r =r;
        this->m = m;
    }
    Cov (const Cov &g):Vac(g){
        this->reactii=g.reactii;
        this->medicamente=g.reactii;
        this->eficienta=g.eficienta;
        this->m=g.m;
        this->r=g.r;

    }
    Cov &operator=(const Cov &g){
        if(this!=&g){
            Vac::operator=(g);
            this->reactii=g.reactii;
            this->medicamente=g.reactii;
            this->eficienta=g.eficienta;
            this->m=g.m;
            this->r=g.r;
        }
    }
    istream &citire(istream &in){
        this->medicamente.clear();
        this->reactii.clear();
        Vac::citire(in);
        string reactie;
        cout<<"Numar reactii adverse: ";in>>this->r;
        cout<<"Citeste reactii adverse: ";
        for (int i = 0 ; i <this->r ; i++)
        {   in>>reactie;
            this->reactii.push_back(reactie);
        }
        cout<<"Numar medicamente interzise: ";in>>this->m;
        cout<<"Citeste medicamente interzise: ";
        for (int i = 0 ; i < this->m ; i++)
        {   in>>reactie;
            this->medicamente.push_back(reactie);
        }
        cout<<"Rata eficienta: "; in>>this->eficienta;
        return in;
    }
    ostream &afisare(ostream &out)const{
        Vac::afisare(out);
       out<<"Rata eficienta: "<<this->eficienta;
       out<<"Reactii adverse: ";
        for (int i = 0 ; i < this->r ; i++)
        {
            out<<this->reactii[i]<< " ";
        }
        out<<"Medicamente interzise: ";
        for (int i = 0 ; i < this->m ; i++)
        {
            out<<this->medicamente[i]<< " ";
        }

        return out;
    }



    ~Cov(){this->medicamente.clear();this->reactii.clear();}
};

class Comanda:public Iointerface{
protected:

    const int idcom;
    int nrtip;
    static int contorID;
    vector <string> tip;
    vector <int> buc;
public:
    Comanda():idcom(contorID++){
        this->nrtip=0;
    }

    Comanda(int nr,vector <string> t, vector <int> b):idcom(contorID++){
        this->nrtip=nr;
        this->tip=t;
        this->buc=b;
    }
    Comanda(const Comanda &c):idcom(c.contorID++){
        this->nrtip=c.nrtip;
        this->tip=c.tip;
        this->buc=c.buc;
    }
    Comanda &operator=(const Comanda &c){
        if(this!=&c)
        {
            this->buc.clear();
            this->tip.clear();
            this->nrtip=c.nrtip;
            this->tip=c.tip;
            this->buc=c.buc;


        }

    }
    istream &citire(istream &in){
        this->tip.clear();this->buc.clear();

        cout<<"Cate tipuri diferite de vaccin doriti? max 3: ";
        in>>this->nrtip;
        cout<<"Citeste tipul si apoi introduceti numarul de doze dorite.";
        for (int i = 0 ; i <this->nrtip;i++)
        {
            string model;
            int cant;
            cout<<"Tip: ";
            in>>model;
            cout<<"Cantitate pentru "<<model<<" :";
            in>>cant;
            this->tip.push_back(model);
            this->buc.push_back(cant);

        }

        return in;
    }
    ostream &afisare(ostream &out)const{

        for (int i ; i < this->nrtip ;i++)
        {
            out<<" cantitate: "<<this->buc[i]<<"vaccinuri pentru: "<< this->tip[i];
            out<<endl;
        }

        return out;
    }
    friend istream &operator>>(istream &in,Comanda &c){return c.citire(in);}
    friend ostream &operator<<(ostream &out,const Comanda &c){return c.afisare(out);}
    ~Comanda(){this->buc.clear();this->tip.clear();}

    int getID() const{return this->idcom;}
//    float getPretPerVaccin( ){
//
//        float rezultat=0;
//        float pret_baza = 0;
//
//
//            return rezultat;}
};

int Comanda::contorID=0;
int main() {
    vector <Comanda> lista_comenzi;
    vector <Vac*> depozit;
//    Cov v;
//    cin>>v;
//    cout<<v;
    while(true) {
        int comanda;
        cout<<"Apasa 1 pentru a adauga un vaccin."<<endl;

        cout<<"Citeste comanda: ";

        cin>>comanda;
        switch (comanda) {

            case 1:{string model;
                cout<<"Ce model de vaccin doriti sa adaugati (Gria,Cov,Hepa): ";
                cin>>model;
                if (model=="Gripa"){Gripa g; cin>>g; depozit.push_back(new Gripa(g)); cout<<endl<<g<<endl;}
                    if (model=="Cov"){Cov c; cin>>c; depozit.push_back(new Cov(c));  cout<<endl<<c<<endl;}
                    if (model=="Hepa"){Hepa h; cin>>h; depozit.push_back(new Hepa(h)); cout<<endl<<h<<endl; }

            break;}
            case 2:{
                    for(int i = 0; i<depozit.size();i++)
                    cout<<depozit[i]<<" ";
            break;}
            case 3:{
                Comanda d;
                cin>>d;
                lista_comenzi.push_back(d);
            break;}
            case 4:{
                int index;
                cout<<"Introdu numarul comenzii pe care vrei sa o afisezi: ";
                cin>>index;
                for(int i = 0; i< lista_comenzi.size();i++)
                {
                    if(lista_comenzi[i].getID()==index)
                        cout<<&lista_comenzi[i];
                }
                break;}

        }


    break;}
    return 0;
}
