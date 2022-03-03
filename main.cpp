//nous sommes le binome mohamed amine houidi et houssem jmal 1info1
#include <vector>
#include<set>
#include<map>
#include <string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include <sys/types.h>
#include <dirent.h>
using namespace std;
int w=0; //variable globale
int x=1;// par defaut  version 1 de l analyseur
int k=1;// par defaut  version 1 de l indexeur

multimap<int ,string> invertMap(map <string,int> entre)
{
	multimap<int ,string> resu;
	map<string ,int> ::iterator k;
		for(k=entre.begin();k!=entre.end();k++)
        {
         resu.insert(pair <int,string>(k->second,k->first));
        }
	return resu;
}

/*cest la classe occurence */

class occurence {
public:
string mot;
int nbre;

occurence(){};
occurence(string a,int b):mot(a),nbre(b)
{}

int get_nbre()const{return nbre;}
string get_mot()const {return mot;}
void set_nbre(int a){nbre=a;}
void set_mot( string a){mot=a;}

};

//l utilisation du polymorphisme voici classe mere qui est classe abstraite
class analyse
{
public:
virtual  vector<occurence> analyser ()=0;
virtual ~analyse();
};

analyse::~analyse(){}



/*c est la classe analyseur */

class analyseur:public analyse{
    protected:
vector<string> a;
public:
analyseur(vector<string> r)
{
    for(unsigned int i=0;i<r.size();i++)
          a.push_back(r[i]);

}
 vector<occurence> analyser ();
 ~analyseur();

};


//----------------------------------------------------------

 vector<occurence>  analyseur::analyser ()
{int k=0;;
map <string,int> c;
set<string> b;
occurence v;
vector< occurence > m;
map <string,int>::iterator q;
for(unsigned int i=0;i<a.size();i++)
{ if(b.count(a[i])==0)
         {b.insert(a[i]) ;
          c[a[i]] =1;
         }
         else
             c[a[i]]++;

}

m.reserve(c.size());
for(q =c.begin();q!=c.end();q++)

    {
    v.set_mot(q->first);
    v.set_nbre(q->second);
    m.push_back(v);
    k++;
    }
  return m;
}
//msg


class analyseur1:public analyse {
vector<string> a;
public :
    analyseur1(vector<string> r)
{
    for(unsigned int i=0;i<r.size();i++)
          a.push_back(r[i]);

}
~analyseur1();
 vector<occurence> analyser ();

};
analyseur1::~analyseur1(){}
vector<occurence> analyseur1::analyser (){
vector<occurence> c;
set <string> b;
vector<string> ::iterator i;
 occurence v;
for(unsigned int i=0;i<a.size();i++)
    {if(b.count(a[i])==0)
             { b.insert(a[i]);
               occurence v(a[i],1);
               c.push_back(v) ;


             }
        else
        {       for(unsigned j=0;j<c.size();j++)
                        if (c[j].mot==a[i])
                            {
                                c[j].set_nbre(c[j].get_nbre()+1);
                                break;

                             }
        }
   }
return c;
}



//---------class lecture-----------------

class lecture{
    public:
string const chemin;
lecture(string f):chemin(f){}
vector<string> extraire();
};
vector<string> lecture::extraire(){
    string a;
    vector<string>v;
ifstream f(chemin.c_str());
if(f)
{while(f>>a)
   v.push_back(a);
}
else
    cout<<"--> Cette fichier n existe pas ressayer svp  \n";

return v;
}
analyseur::~analyseur()
{
}


//class index----------------------------------------

class index_m
{


public:
     multimap<string,occurence>biblio;
    index_m()
    {
       biblio={};
    }
    virtual void indexer (vector<occurence>,string chemin)=0;
    virtual ~index_m();
};
index_m::~index_m()
{
}

class index1:public index_m {
    public:
        ~index1();
index1()
{
    biblio={};
}

void indexer (vector<occurence>,string chemin);
};
index1::~index1()

{

};


void index1:: indexer (vector<occurence>txt,string chemin )
{
 multimap<string,occurence>::iterator k;
 bool g=true;
 for (k=biblio.begin();k!=biblio.end();k++)
    {if(k->first==chemin)
    {
        cout<<"--> Cette fichier  existe deja dans votre bibliotheque ! \n";
        g=false;
        break;
    }
    }
if(g==true)
   {for( unsigned int i=0;i<txt.size();i++)


           {


            biblio.insert(pair <string,occurence>(chemin,txt[i])); //pour stocker la resultat d une fichier  dans la bibliotheque general}
        }
}

}
//---------fonction fichier_vide--------------
//verifier si le fichier est vide ou non

bool fichier_vide(string chemin)
{ string ligne,ch="";
bool resultat =true;
        ifstream f(chemin.c_str());
        while(getline(f,ligne))
        {
            ch+=ligne;
            if(ch.length()>0)
                {resultat=false;
                  break;
                }


        }
 return resultat;
}

class couple{
    public:
occurence occ;
string chemin;

};
class index2:public index_m
{
       public:
            ~index2();
           vector<couple> biblio;
           index2()
           {
              biblio={};
           }
           void indexer (vector<occurence>,string chemin);

};
index2::~index2()
{

};

void index2:: indexer (vector<occurence>txt,string chemin )
{
couple co;

   for( unsigned int i=0;i<txt.size();i++)
        {
        co.occ=txt[i];
        co.chemin=chemin;
         biblio.push_back(co);
         }

}


//-----------------fonction tovector pour convertir une chaine en un vector de string---------

   vector<string>  tovector(string ch)
 { ch=ch+" ";
     string j="";
vector<string> requete;
    for (int i=0;i<100;i++)
    {
        if( ch[i]!=' ')
           j+=ch[i] ;
        else
        {
            requete.push_back(j);
            j="";
        }

    }

    return requete;
 }

 //-------------class ordonnanceur pour trier les fichiers selon ls scores apres une requete donnee par l utilisateur ------
 //scorocc et scorbinaire sont deux methodes de cette classe

class ordonnanceur{
public:
index1 bibli;
public:

void scoreocc(string );
void scorebinaire(string  );

};

// ---------------methode scoreocc ------------------------------

void ordonnanceur::scoreocc(string ch)
{vector<string>  requete=tovector(ch);
multimap<string,occurence> ::iterator i;
multimap<int,string> res;
map<string,int> scor;
map<string,int> ::iterator v;
multimap<int,string> affich;
multimap<int,string> ::reverse_iterator  k;
set<string> panier_de_fihiers;
for (i=bibli.biblio.begin();i!=bibli.biblio.end();i++)
      {   if(panier_de_fihiers.count(i->first)==0)
                 {
                  panier_de_fihiers.insert(i->first);
                  scor.insert(pair <string,int>(i->first,0));
                  }
      }
 for (unsigned int j=0;j<requete.size();j++){
    for (i=bibli.biblio.begin();i!=bibli.biblio.end();i++)
    {
        if(requete[j]==(i->second).mot)
                    scor [i->first]=scor[i->first]+(i->second).nbre  ;

    }
 }
affich= invertMap(scor);//inversion du map vers un multimap en inversant la cle et la valeur  pour avoir la propriete du tri du multimap selon la clé;
if(::w==0)



{for( k=affich.rbegin() ;k!=affich.rend();k++)
    cout<<"\n"<<k->second<<" a un score "<<k->first<<endl;
}
else {
        int n=0;
    for( k=affich.rbegin() ;k!=affich.rend();k++)
    {
        n++;
    cout<<"\n"<<k->second<<" a un score "<<k->first<<endl;
    if(n==::w)
        break;

    }
}
}

//----------methode scorebinaire---------------

void ordonnanceur::scorebinaire(string ch)
{vector<string>  requete=tovector(ch);
multimap<string,occurence> ::iterator i;
multimap<int,string> res;
map<string,int> scor;
map<string,int> ::iterator v;
multimap<int,string> affich;
multimap<int,string> ::reverse_iterator k;
set<string> panier_de_fihiers;
for (i=bibli.biblio.begin();i!=bibli.biblio.end();i++)
      {   if(panier_de_fihiers.count(i->first)==0)
                 {panier_de_fihiers.insert(i->first);
                  scor.insert(pair <string,int>(i->first,0));
                  }


      }



 for ( unsigned int j=0;j<requete.size();j++){
    for (i=bibli.biblio.begin();i!=bibli.biblio.end();i++)

    {
        if(requete[j]==(i->second).mot)
                   {
                    scor [i->first]=scor[i->first]+1 ;
                    }

    }
}
affich= invertMap(scor);
if(::w==0)
{

for(  k=affich.rbegin();k!=affich.rend();k++)
    cout<<"\n"<<k->second<<" a un score "<<k->first<<endl;
}
else
{int n=0;
    for( k=affich.rbegin() ;k!=affich.rend();k++)
    {
        n++;
    cout<<"\n"<<k->second<<" a un score "<<k->first<<endl;
    if(n==::w)
        break;
}
}
}

//fct to_multimap
//-------------fonction de  conversion de  vector to multimap
multimap<string,occurence> to_multimap(vector<couple> a)
{multimap<string,occurence>  resultat;
    for(unsigned int i=0;i<a.size();i++)
    {
    resultat.insert(pair<string,occurence>(a[i].chemin,a[i].occ));
    }
    return resultat;
}


//conversion reciproque
//fct qui transmet les elts d un multimap dans un vector
vector<couple> reciproque (multimap<string,occurence> a)
{vector<couple>  resultat;
couple c;
multimap<string,occurence>::iterator i;
    for( i=a.begin();i!=a.end();i++)
    { c.chemin=i->first;
    c.occ=i->second;
    resultat.push_back(c);
    }
    return resultat;
}

//fct read_directory
//mettre les fichiers d un dossier dans un vecteur

vector<string>read_directory(const std::string& name)
{ vector <string> v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
    return v;
}

//------------------------------------------------------------------------------
int main()
{    unsigned int n;
int s=0;
clock_t t_analyseur,req;
string f,m;
vector<occurence>occ;
vector<occurence>::iterator k;
vector <string>texte;
 index1 exemple ;
 index2 exemple2;

multimap<string,occurence>::iterator j;
multimap<string,occurence> resultat;

  ifstream  flux("configuration_precedente.txt"),flu("biblio.txt");
if ( flux)
{int s=0,n;
string h;
while(getline(flux,h))
{  s++;
    if(s==2)
    {istringstream(h) >> n;
        ::k=n;
    }

    else
    {istringstream(h) >> n;
        ::x=n;
    }
}
}

else
    {ofstream flux("configuration_precedente.txt",ios::app);
    flux<<1<<"\n"<<1;


        //sinon faire la creation du fichier
    flux.close();
    }
if ( flu)
{string r,h,c;
 int n;

 while( getline(flu,h))
 {

     s++;
  if(s%3==2)
  {
         r=h;

  }
  else
    if(s%3==1)
          {
          c=h;

          }
  else
  {            istringstream(h) >> n;
             occurence v(r,n);
              exemple.biblio.insert(pair <string,occurence>(c,v));
             // exemple2.biblio.push_back()
  }
 }
}
else
{
    ofstream flu("biblio.txt",ios::app);     //sinon faire la creation du fichier
    flu.close();

}



retour:
while (1)
{  cout<<"     ----------------------Menu Principale-----------------------\n\n";
cout<<   "           * Ajouter un fichier en tapant ---------------------1 \n" ;
cout<<   "           * Supprimer un fichier en tapant ------------------ 2 \n" ;
cout<<   "           * Donner votre requete en tapant ------------------ 3\n" ;
cout<<   "           * Configurer en tapant ---------------------------- 4\n" ;
cout<<   "           * Afficher votre bibliotheque en tapant ----------- 5\n" ;
cout<<   "           * Afficher une statistique de vos donnees en tapant 6\n" ;
cout<<   "           * Sauvegarder la configuration en  tapant-----------7\n ";//l utilasateur peut sauvegarder la configuration apres qu'il quitte et de cette maniere ils seront par defaut pour la prochaine visite
cout<<   "          * Quitter  et Sauvegarder en tapant --------------- 0 \n";
cin>>n;
switch (n)
{
case 0:
    {
         ofstream flux ("biblio.txt");
        for(j=exemple.biblio.begin();j!=exemple.biblio.end();j++)

        {flux<<j->first<<"\n";
         flux<<j->second.mot<<"\n"<<j->second.nbre<<"\n";

         }

         return 0;
    }

case 1 :
{      int n,s;

     while(1)
    {s=0;
        do
        {
            if(s>0)
              //  cout<<"erreur de saisie\n";
            s++;
     cout<<"              ->menu d'ajout des fichiers<-\n\n ";
    cout<<"        *Ajouter un seul fichier en tapant -----------------1\n";
    cout<<"         *Ajouter un nom de dossier en tapant----------------2\n";
    cout<<"         *Ajouter plusieurs fichier d un seul coup en tapant 3\n";
    cout<<"         *Retour au menu principal en tapant-----------------0\n" ;
     cin>>n;
        }
        while((n!=0)&&(n!=1)&&(n!=2)&&(n!=3));

    switch(n)
    {
    case 0:
             {goto retour;
             break;}

     case 1:
    {
    cout<<"Donner le chemin du fichier a ajouter: ";
    cin>>f;
        t_analyseur=clock();
    if(fichier_vide(f)==false) //verifier si le fichier est vide ou non
    {lecture file(f);
    texte=file.extraire();
    analyseur n(texte);
    analyseur1 m(texte);
    analyse *ana1=&n;
    analyse *ana2=&m;
    index_m *ind1=&exemple;
    index_m *ind2=&exemple2;

    if(::x==1)
    { cout<<" --> Analyse en cours avec la version 1 <--\n ";
    occ=ana1->analyser();
    }
    else
    { cout<<" --> Analyse en cours avec la version 2 <-- \n";
        occ=ana2->analyser();
    }

   if(::k==2)
    {
             cout<<"--> Indexation en cours avec la version 2 <--\n ";
             exemple2.biblio=reciproque(exemple.biblio);
             ind2->indexer(occ,f);
             cout<<"\n";
             cout<<"votre bibliotheque est de type vector!"<<endl;
             exemple.biblio={};
             exemple.biblio=to_multimap(exemple2.biblio);

                  }
                 else
                 {


                   cout<<"--> Indexation en cours avec la version 1 <--\n ";
                    ind1->indexer(occ,f);
                     cout<<"--> votre bibliotheque est de type multimap! \n\n";

                  }

                  }
                   else
                      cout<<"--> Impossible d'ajouter ce fichier car il est vide ou n'existe pas \n\n";
                     t_analyseur=clock()-t_analyseur;
                     cout<<"ca prend "<< t_analyseur<<"ms pour analyser et indexer votre fichier\n";

               break;
    }
     case 2:
        {vector<std::string> panier;
        string f;

        cout<<"donner le nom de votre dossier : ";
        cin>>f;
        t_analyseur=clock();
/*if((m=opendir(f))==NULL)
{
    cout<<"le dossier n'existe pas \n";
    break;
}*/
   panier=read_directory(f);


         panier.erase(panier.begin() , panier.begin() + 2);
         for(unsigned int j=0;j<panier.size();j++)

                             panier[j]=f+"\\"+panier[j];



if(::k==2)
{
     cout<<"--> Indexation en cours avec la version 2 <--\n ";
     cout<<"votre bibliotheque est de type vector!"<<endl;
}
else
{
     cout<<"--> Indexation en cours avec la version 1 <--\n ";
     cout<<"--> votre bibliotheque est de type multimap! \n";

}
if(::x==1)
                                    cout<<" --> Analyse en cours avec la version 1 <--\n ";
                            else
                                     cout<<" --> Analyse en cours avec la version 2 <-- \n";

  for(unsigned int j=0;j<panier.size();j++)
                        {


                             if(fichier_vide(panier[j])==false) //verifier si le fichier est vide ou non
                              {lecture file(panier[j]);
                               texte=file.extraire();
                                analyseur n(texte);
                                analyseur1 m(texte);

                                analyse *ana1=&n;
                                analyse *ana2=&m;
                                index_m *ind1=&exemple;
                                index_m *ind2=&exemple2;

                                if(::x==1)
                                   {
                                     occ=ana1->analyser();
                                     }
                                 else
                                     {
                                       occ=ana2->analyser();
                                      }

                                if(::k==2)
                                         {


                                                 exemple2.biblio=reciproque(exemple.biblio);
                                                 ind2->indexer(occ,panier[j]);
                                                 exemple.biblio={};
                                                  exemple.biblio=to_multimap(exemple2.biblio);

                                            }
                                           else

                                                   ind1->indexer(occ,panier[j]);



                                            }
                                             else
                                                     cout<<"--> Impossible d'ajouter ce fichier car il est vide ou n'existe pas \n";

 }
        t_analyseur=clock()-t_analyseur;
         cout<<"ca prend "<< t_analyseur<<"ms pour analyser et indexer " <<panier.size()<<" fichier(s)\n";


 break;
                     }





        case 3: {
                         char ch[100];
                         string f;
                           if(::x==1)
                                    cout<<" --> Analyse en cours avec la version 1 <--\n ";
                            else
                                     cout<<" --> Analyse en cours avec la version 2 <-- \n";
    if(::k==2)
{
     cout<<"--> Indexation en cours avec la version 2 <--\n ";
     cout<<"votre bibliotheque est de type vector!"<<endl;
}
else
{
     cout<<"--> Indexation en cours avec la version 1 <--\n ";
     cout<<"--> votre bibliotheque est de type multimap! \n\n";

}
                          cout<<"entrer vos fichier en un seul coup  separes par un espace :\n";
                             cin.ignore();
                             cin.getline(ch,sizeof(ch));
                              f=ch ;
                          t_analyseur=clock();


                          vector<string> panier=tovector(f);
                          for(unsigned int j=0;j<panier.size();j++)
                        {


                             if(fichier_vide(panier[j])==false) //verifier si le fichier est vide ou non
                              {lecture file(panier[j]);
                               texte=file.extraire();
                                analyseur n(texte);
                                analyseur1 m(texte);

                                analyse *ana1=&n;
                                analyse *ana2=&m;
                                index_m *ind1=&exemple;
                                index_m *ind2=&exemple2;

                                if(::x==1)
                                   {
                                     occ=ana1->analyser();
                                     }
                                 else
                                     {
                                       occ=ana2->analyser();
                                      }

                                if(::k==2)
                                         {
                                                 exemple2.biblio=reciproque(exemple.biblio);
                                                 ind2->indexer(occ,panier[j]);
                                                 cout<<"\n";
                                                 exemple.biblio={};
                                                  exemple.biblio=to_multimap(exemple2.biblio);

                                            }
                                           else
                                           {


                                                   ind1->indexer(occ,panier[j]);

                                              }

                                            }
                                             else
                                                     cout<<"--> Impossible d'ajouter ce fichier car il est vide ou n'existe pas \n\n";



 }






        t_analyseur=clock()-t_analyseur;
         cout<<"ca prend "<< t_analyseur<<"ms pour analyser et indexer votre fichier\n";
        break;
                     }



    }
    }
    break;
}
case 2:
{
     while(1)
    {int s=0;
    int n;
 if(exemple.biblio.size()==0)
    {
        cout<<"votre bibliotheque est vide\n";
        break;
    }
        do
    {
        if(s>0)
            cout<<"erreur de saisie\n";
            s=1;
cout<<"          ---->menu supprimer<------------\n\n";
cout<<"             *Suprimer un element de votre bibliotheque tapant------------ 1\n";
cout<<"             *Suprimer tous les  elements de votre bibliotheque tapant---- 2\n";
cout<<"             *Retourner au menu principale-------------------------------- 0\n";

cin >>n;
    }
    while((n!=0)&&(n!=1)&&(n!=2));

switch(n)
{

case 0:
    goto retour;
case 1:
    {cout<<"Donnez le nom du Fichier a supprimer : ";
    cin>>f;
    bool h=false;
    for(j=exemple.biblio.begin();j!=exemple.biblio.end();j++)
    {
        if (f==j->first)
             {h=true;    //le fichier existe
             break;
              }
    }

    if(h==true)
    {
    exemple.biblio.erase(f);
    cout<<"votre operation  effectuee avec succes\n";
    break;
    }


    else
         {
            cout<<"impossible de supprimer cet fichier  car il n'existe pas dans votre bibliotheque \n";
            break;
}
break;
    }
case 2:
      {
           exemple.biblio.clear();
          break;

      }
}
    }
    break;
}

case 3:
{  req=clock();
    if(exemple.biblio.size()!=0)
   {char ch[200];
   string s;
   cout<<"Donner votre requete :  ";
   req=clock()-req;
   cin.ignore();
   cin.getline(ch,sizeof(ch));
   s=ch ;
   while(s.size()==0)
    {
   cout<<"---> Vous devez entrer une chaine non vide\n";
   cout<<"Donner votre requete :  ";
   cin.ignore();
   cin.getline(ch,sizeof(ch));
   s=ch ;
    }//Cette fichier
   ordonnanceur ord;
   ord.bibli=exemple;
   int q,v=0;

do
{
   if(v>0)
   {
       cout<<"erreur de saisie\n";
   }
    v++;
   cout<<"   Tapez 1 si vous voulez le tri des resultats sera selon l'ordonnancement par Occurence \n";
   cout<<"   Tapez 2 si vous voulez le tri des resultats sera selon l'ordonnancement par Binaire\n";
   cout<<"   Tapez 0 si vous voulez annuler \n";
   cin>>q;
}
while((q!=1)&&(q!=2)&&(q!=0));
req=clock();
if(q==1)
{
 cout<<"  Resultat selon l ordonnancement par occurence :\n";
 ord.scoreocc(s);
 req=clock()-req;
  cout<<"ca prend " <<req<<" ms pour faire entrer une requete et affichier  la resultat\n";
  break;

}
if(q==2)
 {
 cout<<"\n  Resultat selon l'ordonnancement par binaire :\n";
 ord.scorebinaire(s);
  req=clock()-req;
  cout<<"ca prend " <<req<<" ms pour faire entrer une requete et affichier  la resultat\n";
  break;

 }
 if (q==0)
    goto retour;
 req=clock()-req;
 cout<<"ca prend " <<req<<" ms pour faire entrer une requete et affichier  la resultat\n";
 break;
 }
 else
 {   req=clock()-req;
 cout<<"ca prend " <<req<<" ms pour faire entrer une requete et affichier  la resultat\n";
     cout<<"votre bibliotheque est vide\n";
     break;
 }
}
case 6:
        {
            while (1)
            {   cout<<"    -----------Menu Statistique---------\n";
                cout<<"    Afficher le nombre de tous les mots de votre bibliotheque en tapant - 1\n";
                cout<<"    Afficher le nbre  des  mots distincts de votre index en tapant ------ 2\n";
                cout<<"    Afficher le nbre de fichier de votre bibliotheque en tapant --------- 3\n";
                cout<<"    Revenir au menu principal en tapant --------------------------------- 0\n";

                int n;
                cin>>n;
                switch (n)
                {case 1:

                     {
                         int s=0;
                         for(j=exemple.biblio.begin();j!=exemple.biblio.end();j++)
                             s+=j->second.nbre;

                    cout<<"     Le nombre total des mots de votre bibliotheque est  "<<s<<"\n";
                     break;}
                case 2:
                     {set <string> distinct;
                    set <string> ::iterator i ;

                   for(j=exemple.biblio.begin();j!=exemple.biblio.end();j++)
                     distinct.insert(j->second.mot);
                 cout<<"     Le nombre total des mots distincts de votre bibliotheque est "<<distinct.size()<<"\n";
                 break;
                     }
                case 3:
                    {set <string> distinct;
                    set <string> ::iterator i ;

                   for(j=exemple.biblio.begin();j!=exemple.biblio.end();j++)
                     distinct.insert(j->first);
                 cout<<"     Le nombre total des fichiers de votre bibliotheque  est "<<distinct.size()<<"\n";
                 break;
                    }
                case 0:
                     goto retour;
                default:
                     {cout <<"Erreur de saisie \n";
                     break;
                     }

            }
        }
        }

case 4 :
    {
      while(1)
      {  cout<<"     ------------ Menu  Configuration ----------\n\n";
          cout<<"      Modifier le nombre de fichiers de la resultat  en tapant 1\n";
          cout<<"      Changer la version de l analyseur en tapant ------------ 2\n";
          cout<<"      Changer la version de l indexeur en tapant ------------- 3\n";
           cout<<"      Revenir au menu principale en tapant ------------------- 0\n";
           int n;
           cin>>n;
           switch(n)
           {
           case 0:
              goto retour;

           case 1:
           {
               do
               {
               cout<<"   Donner le nombre de fichiers que vous voulez afficher dans la resultat: "; //resultat du score sera selon ce nbre
               cin>>::w;
               }
               while (::w<=0);
               break;


           }
           case 2:
               {
                   do
            {int n=0;
                cout<<"   Entrer la version de l'analyseur voulue 1 ou 2 \n";
                cin>>n;

                switch(n)
                {
                    case 1:
                        {
                            cout<<"Tu as choisi  la 1ere version de l'analyseur\n";
                            ::x=1;
                            break;
                        }
                    case 2:
                        {
                            cout<<"Tu as choisi  la 2eme  version de l'analyseur\n";
                            ::x=2;
                            break;
                        }

                }
                break;
            }while(n!=1&&n!=2);
            break;
               }

            case 3:
                {int n;
                do
                {
                cout<<"   Entrer la version de l'indexeur voulue 1 ou 2\n";
                cin>>n;
                switch(n)
                {
                    case 1:
                        {
                            cout<<"Tu as choisi  la 1ere version de l'indexeur\n";
                            ::k=1;
                            break;
                        }
                    case 2:
                        {
                            cout<<"Tu as choisi  la 2eme  version de l'indexeur\n";
                            ::k=2;
                            break;
                        }
                    default :
                        {
                            cout<<"Erreur de saisie/n";
                        break;
                        }


                }

                }
                while(n!=1&&n!=2);
           }
      }
    }
    }

case 5:
    {  while(1)
       {int n;
       cout<<"     ------Menu affichage-----\n";
       cout<<"      Si vous voulez afficher votre index tapez ---------- 1\n";
       cout<<"      Si vous voulez afficher vos fichiers seulement tapez 2\n";
       cout<<"      Si vous voulez revenir au menu principal tapez ----- 0\n";
       cin>>n;
       switch (n)
   {
      case 0:
          {
              goto retour;
          }

       case 1:
       { if(exemple.biblio.size()==0)
       {
           cout<<" --> Votre bibliotheque est vide ! \n";
           break;
       }

            for(j=exemple.biblio.begin();j!=exemple.biblio.end();j++)
                  cout<<j->first<<":("<<j->second.mot<<","<<j->second.nbre<<")"<<"\n";

break;
       }


   case 2:
    { set <string> distinct;
      set <string> ::iterator i ;
      if(exemple.biblio.size()==0)
       {
           cout<<" --> Votre bibliotheque est vide ! \n";
           break;
       }

        for(j=exemple.biblio.begin();j!=exemple.biblio.end();j++)
                 distinct.insert(j->first);
        for (i=distinct.begin();i!=distinct.end();i++)
            cout<<*i<<"\n";
            break;

    }
default:
         {  cout<<"->erreur de saisi<-\n";
             break;

}
}
}
}


case 7:
    {ofstream flux ("configuration_precedente.txt");
    flux<<::x<<"\n";
        flux<<::k<<"\n";



cout<<"vos parametres de configuration  sauvegardes avec  succes\n";
break;
}
}
}
return 0;
}
