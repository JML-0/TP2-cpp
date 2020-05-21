// TP2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <assert.h>
#include <algorithm>
#include "contact.h"

using namespace std;

/*
 * Ajoute un contact dans la liste
 */
void addContact(Contact C) 
{ 
    if (contactExist(C->name, C->firstName) || getName(C->Nums[0]))
    {
        cout << "Ce contact ou numero existe deja !\n";
        return;
    }
    Contacts.push_back(C);
    cout << C->name << " " << C->firstName << " a ete ajoute.\n";
}

/*
 * Vérifie si un contact existe (firstName && name)
 */
bool contactExist(string name, string firstName)
{
    for (list<Contact>::iterator i = Contacts.begin(); i != Contacts.end(); i++)
        if ((*i)->firstName == firstName && (*i)->name == name)
            return true;
    return false;
}

/*
 * Retourn un contact si le numero existe dans la liste de contacts
 */
Contact getName(string num)
{
    for (list<Contact>::iterator i = Contacts.begin(); i != Contacts.end(); i++)
        for (vector<string>::iterator j = (*i)->Nums.begin(); j != (*i)->Nums.end(); j++)
            if (*j == num)
                return (*i);
    return NULL;
}

/*
 * Crée un contact
 */
Contact createContact(string name, string firstName, vector<string> Nums)
{
    Contact newContact(new Contact_);
    newContact->name        = name;
    newContact->firstName   = firstName;
    newContact->Nums        = Nums;

    return newContact;
}

/*
 * Rechercher un contact
 */
void findContact()
{
    auto result = find_if(Contacts.cbegin(), Contacts.cend(), [](const Contact& C)
    {
        return C->name == nameContact && C->firstName == firstNameContact;   /*Fonction lambda*/
    });

    if (result != Contacts.cend())
        displayContact((*result));      /*Affiche le contact*/
    else
        cout << nameContact << " " << firstNameContact << " n'existe pas.\n";
}

/*
 * Supprime un contact
 */
void deleteContact(Contact C)
{
    if (Contacts.empty()) return;

    C->Nums.clear();        /*Supprime les numéros*/
    Contacts.remove(C);     /*Puis le contact*/

    cout << C->name << " " << C->firstName << " a ete supprime.\n";
    free(C);
}

/*
 * Modifie un contact
 */
void editContact(Contact C)
{
    cout << "1 - Modifier le nom\n";
    cout << "2 - Modifier le prenom\n";
    cout << "3 - Modifier un numero de telephone\n";
    cout << "4 - Ajouter un numero de telephone\n";
    cout << "5 - Supprimer un numero de telephone\n";
    cout << "6 - Retourner au menu principal\n";

    string name, firstName, num;
    vector<string>::iterator it;

    int t = 0;
    cin >> t;

    switch (t)
    {
    case 1:                                                                             /*Modifier le nom*/
        cout << "Nouveau nom : "; cin >> name;
        C->name = name;
        cout << "Nom modifie avec succes\n";
        editContact(C);
        break;
    case 2:                                                                             /*Modifier le prenom*/
        cout << "Nouveau prenom : "; cin >> firstName;
        C->firstName = firstName;
        cout << "Prenom modifie avec succes\n";
        editContact(C);
        break;
    case 3:                                                                             /*Modifier un numero*/
        cout << "Liste des numeros :\n";
        for (vector<string>::iterator i = C->Nums.begin(); i != C->Nums.end(); i++)     
            cout << "- " << *i << endl;

        cout << "Quel numero souhaitez-vous modifier ? "; cin >> num;
        it = find(C->Nums.begin(), C->Nums.end(), num);
        if (it != C->Nums.end())
        {
            cout << "Nouveau numero : "; cin >> num;
            C->Nums[it - C->Nums.begin()] = num;
            cout << "Numero modifie avec succes.\n";
        }
        else
            cout << "Numero introuvable.\n";
        editContact(C);
        break;
    case 4:                                                                             /*Ajouter un numero*/
        cout << "Nouveau numero : "; cin >> num;
        if (getName(num))
        {
            cout << "Ce numero existe deja\n";
            break;
        }
        C->Nums.push_back(num);
        cout << "Numero ajoute avec succes.\n";
        editContact(C);
        break;
    case 5:                                                                             /*Supprimer un numero*/
        cout << "Liste des numeros :\n";
        for (vector<string>::iterator i = C->Nums.begin(); i != C->Nums.end(); i++)
            cout << "- " << *i << endl;

        cout << "Quel numero souhaitez-vous supprimer ? "; cin >> num;
        it = find(C->Nums.begin(), C->Nums.end(), num);
        if (it != C->Nums.end())
        {
            C->Nums.erase(C->Nums.begin() + (it - C->Nums.begin()));
            cout << "Numero supprime avec succes.\n";
        }
        else
            cout << "Numero introuvable.\n";
        editContact(C);
        break;
    default:
        break;
    }
}

/*
 * Affiche un contact
 */
void displayContact(Contact C)
{
    cout << "--\n";
    cout << "Nom : " << C->name << endl;
    cout << "Prenom : " << C->firstName << endl;
    cout << "Numeros : \n";

    for (vector<string>::iterator i = C->Nums.begin(); i != C->Nums.end(); i++)
        cout << "- " << *i << endl;

    cout << "\nPour supprimer ce contact, appuyez sur la touche S, pour le modifier, M\n";
    string t;
    cin >> t;

    if (t == "S") deleteContact(C);
    if (t == "M") editContact(C);
}

/*
 * Affiche les contacts
 */
void displayContacts()
{
    Contacts.sort(compByName);
    for (list<Contact>::iterator i = Contacts.begin(); i != Contacts.end(); i++)
    {
        cout << "--\n";
        cout << "Nom : "    << (*i)->name << endl;
        cout << "Prenom : " << (*i)->firstName << endl;
        cout << "Numeros : \n";

        for (vector<string>::iterator j = (*i)->Nums.begin(); j != (*i)->Nums.end(); j++)
            cout << "- " << *j << endl;
    }
}

/*
 * Affiche les contacts un par un
 */
void displayContacts1By1()
{
    Contacts.sort(compByName);
    for (list<Contact>::iterator i = Contacts.begin(); i != Contacts.end(); i++)
    {
        cout << "--\n";
        cout << "Nom : "    << (*i)->name << endl;
        cout << "Prenom : " << (*i)->firstName << endl;
        cout << "Numeros : \n";

        for (vector<string>::iterator j = (*i)->Nums.begin(); j != (*i)->Nums.end(); j++)
            cout << "- " << *j << endl;
        
        cout << "Appuyez sur la touche S pour afficher le contact suivant.\n";

        string t;
        cin >> t;

        if (t != "S") break;
    }
}

/*
 * Tris alphabetique par nom
 */
bool compByName(Contact &a, Contact &b) { return a->name < b->name; }

/*
 * Tris alphabetique par prenom
 */
bool compByFirstName(Contact& a, Contact& b) { return a->firstName < b->firstName; }

void addAppelAbs(string num)
{
    AppelAbs ap;
    ap.num = num;
    ap.date = time(0);
    AppAbs.push_back(ap);
}

void addAppelES(string num, bool entrant)
{
    AppelES ap;
    ap.num = num;
    ap.date = time(0);
    ap.AppelEntrant = entrant;
    AppES.push_front(ap);
}


int main()
{
    cout << "1 - Afficher les contacts\n";
    cout << "2 - Afficher les contacts 1 par 1\n";
    cout << "3 - Ajouter un contact\n";
    cout << "4 - Rechercher un contact\n";
    cout << "5 - Consulter les appels en absences\n";
    cout << "6 - Consulter les appels en entrant/sortant\n";
    cout << "7 - Ajouter un appel en absence (pour tester)\n";
    cout << "8 - Ajouter un appel en entrant/sortant (pour tester)\n";

    string name, firstName, num, j;
    vector<string> nums;
    Contact newContact(0), contact(0);
    char cm[26];

    int t = 0;
    cin >> t;

    switch (t)
    {
    case 1:
        displayContacts();
        main();
        break;
    case 2:
        displayContacts1By1();
        main();
        break;
    case 3:
        cout << "Nom : ";                   cin >> name;
        cout << "Prenom : ";                cin >> firstName;
        cout << "Numero de telephone : ";   cin >> num;
        nums.push_back(num);

        newContact = createContact(name, firstName, nums);
        addContact(newContact);
        main(); /*affiche de nouveau le menu*/
        break;
    case 4:
        cout << "Nom : ";    cin >> nameContact;
        cout << "Prenom : "; cin >> firstNameContact;
        findContact();
        main();
    case 5:
        if (!AppAbs.size()) 
        {
            cout << "0 appel en absence.\n";
            main();
        }
        cout << AppAbs.size() << " appels en absence.\n";
        cout << "Souhaitez-vous consulter les appels en absences ? (Y/N)"; cin >> j;
        
        if (j == "N") main();

        for (list<AppelAbs>::iterator i = AppAbs.begin(); i != AppAbs.end(); i++)
        {
            contact = getName(i->num);

            ctime_s(cm, sizeof cm, &i->date);

            if (contact != 0) /* numero présent dans la liste de contact */
                cout << "- Appel en absence de " << contact->name << " " << contact->firstName << " le " << cm << endl;
            else
                cout << "- Appel en absence du " << i->num << " le " << cm << endl;
        }
        cout << endl;
        AppAbs.clear();

        main();
        break;
    case 6:
        if (!AppES.size())
        {
            cout << "0 appel entrant/sortant.\n";
            main();
        }
        cout << AppES.size() << " appels en entrant/sortant.\n";
        cout << "Souhaitez-vous consulter les appels entrant/sortant ? (Y/N)"; cin >> j;

        if (j == "N") main();

        for (list<AppelES>::iterator i = AppES.begin(); i != AppES.end(); i++)
        {
            contact = getName(i->num);

            ctime_s(cm, sizeof cm, &i->date);

            if (contact != 0) /* numero présent dans la liste de contact */
                if (i->AppelEntrant)
                    cout << "- Appel entrant de " << contact->name << " " << contact->firstName << " le " << cm << endl;
                else
                    cout << "- Appel sortant de " << contact->name << " " << contact->firstName << " le " << cm << endl;
            else
                if (i->AppelEntrant)
                    cout << "- Appel entrant du " << i->num << " le " << cm << endl;
                else
                    cout << "- Appel sortant du " << i->num << " le " << cm << endl;
        }
        cout << endl;
        AppES.clear();

        main();
        break;
    case 7:
        cout << "Numero : "; cin >> num;
        addAppelAbs(num);
        cout << "Appel en absence ajoute avec succes.\n";
        main();
        break;
    case 8:
        cout << "Numero : "; cin >> num;
        cout << "Type d'appel (E:entrant/S:sortant) : "; cin >> j;
        if (j == "E")
        {
            addAppelES(num, true);
            cout << "Appel entrant ajoute avec succes.\n";
        }
        else if (j == "S")
        {
            addAppelES(num, false);
            cout << "Appel sortant ajoute avec succes.\n";
        }
        else
            main();
        
        main();
        break;
    default:
        break;
    }
}