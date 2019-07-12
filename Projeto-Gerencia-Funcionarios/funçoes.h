#ifndef FUNÁOES_H_INCLUDED
#define FUNÁOES_H_INCLUDED
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
void criarblocos();
void cadastro();
void consulta();
void menu();
void alterasalario();
void excluir();
void criarblocos ()
{
    ofstream lista ("lista.txt", ios::out | ios::trunc);
    funcionario funcionariovazio = {0,' ',' ',' ',' ',0.0};
    if (lista.fail())
    {
        cerr << "Lista nao aberto"<<endl;
    };
    for(int i=0; i<100; i++)
    {
        lista.write((const char*)(&funcionariovazio),sizeof(funcionario));
    };
    lista.close();
    if(lista.is_open())
    {
        cerr << "Lista nao fechado"<<endl;
    }
    cout<< "Arquivos preparados com sucesso!" << endl;
    menu();
};
void cadastro()
{
    int i;
    funcionario funcionarionovo;
    ofstream lista("lista.txt", ios::out | ios::ate );
    if(lista.fail())
    {
        cerr << "Lista nao aberto"<<endl;
    }
    cout << "Digite o id do funcionario: " << endl;
    cin >> funcionarionovo.id;
    while (funcionarionovo.id > 0 && funcionarionovo.id <= 100)
    {
        cout << "Digite o nome do funcionario " << funcionarionovo.id << ": " << endl;
        cin >> funcionarionovo.nome;
        cout << "Digite o sexo do funcionario " << funcionarionovo.id << "(M/F): " << endl;
        cin >> funcionarionovo.sexo;
        cout << "Digite o local do funcionario " << funcionarionovo.id << ": " << endl;
        cin >> funcionarionovo.local;
        cout << "Digite o cargo do funcionario " << funcionarionovo.id << ": " << endl;
        cin >> funcionarionovo.cargo;
        cout << "Digite o sal·rio do funcionario " << funcionarionovo.id << ":" << endl;
        cin >> funcionarionovo.salario;
        lista.seekp((funcionarionovo.id - 1)*sizeof(funcionario));
        lista.write((const char*)(&funcionarionovo), sizeof(funcionario));
        cout << "Deseja cadastrar outro funcionario? (1-sim)" << endl;
        cin >> i;
        if (i!=1)
            break;
        cout << "Digite o id do funcionario: " << endl;
        cin >> funcionarionovo.id;
    }
    lista.close();
    if(lista.is_open())
    {
        cerr << "Lista nao fechado" <<endl;;
    }
    menu();
};
void consulta(){
    funcionario funcionariolista;
    ifstream lista("lista.txt", ios::in );
    if (lista.fail()){
        cerr<< "Lista nao aberto";
    }
    cout << setiosflags(ios::left) <<setw(7) << "ID" << setw(20)
    << "Nome" << setw(5) << "Sexo" << setw(15) << "Local"
    << setw(20) << "Cargo" << resetiosflags(ios::left)<<setw(10) << "Salario" << endl;

    lista.read((char *)(&funcionariolista),sizeof(funcionario));
    while(lista && !lista.eof()){
        if (funcionariolista.id != 0){
            cout<<setiosflags(ios::left)
            <<setw(7)<< funcionariolista.id << setw(20) << funcionariolista.nome << setw(5) << funcionariolista.sexo
            << setw(15) << funcionariolista.local << setw(20) << funcionariolista.cargo << resetiosflags(ios::left)<<setw(10)<< setprecision(2)
            << setiosflags(ios::fixed)<<setiosflags(ios::showpoint)<<funcionariolista.salario<<endl;
        }
            lista.read((char *)(&funcionariolista),sizeof(funcionario));
    }
    cout << endl;
    lista.close();
    if (lista.is_open()){
        cerr << "Lista nao fechado"<<endl;
    }
    menu();
}
void menu(){
    cout << "1-Preparar novo arquivo"<<endl;
    cout << "2-Cadastrar funcionario" << endl;
    cout << "3-Consultar funcionarios cadastrados"<< endl;
    cout << "4-Alterar salario ja cadastrado" << endl;
    cout << "5-Excluir funcionario"<<endl;
    cout << "Qualquer outro-Fechando programa"<<endl;
    cout << "Escolha uma opcao valida: "<<endl;
    int n;
    cin>> n;
    switch (n){
        case 1: criarblocos();
                    break;
        case 2: cadastro();
        break;
        case 3:consulta();
        break;
        case 4:alterasalario();
        break;
        case 5:excluir();
        break;
        default: cout<< "Encerrando programa..."<<endl;
        break;
    }
}
void alterasalario(){
    funcionario funcionarionovo,funcionarioalterado;
    fstream lista("lista.txt", ios::in | ios::out | ios::ate );
    if(lista.fail())
    {
        cerr << "Lista nao aberto"<<endl;
    }
    cout << "Digite o id do funcionario: " << endl;
    cin >> funcionarionovo.id;
    while (funcionarionovo.id > 0 && funcionarionovo.id <= 100)
    {
        cout << "Digite o novo sal·rio do funcionario " << funcionarionovo.id << ":" << endl;
        cin >> funcionarionovo.salario;
        lista.seekg((funcionarionovo.id - 1)*sizeof(funcionario));
        float salario= funcionarionovo.salario;
            lista.read((char *)(&funcionarionovo),sizeof(funcionario));
        lista.seekp((funcionarionovo.id - 1)*sizeof(funcionario));
        funcionarioalterado=funcionarionovo;
        funcionarionovo= {0,' ',' ',' ',' ',0.0};
        funcionarioalterado.salario=salario;
        lista.write((const char*)(&funcionarionovo), sizeof(funcionario));
        lista.write((const char*)(&funcionarioalterado), sizeof(funcionario));
        cout << "Deseja alterar o salario de outro funcionario? (1-sim)" << endl;
        int i;
        cin >> i;
        if (i!=1)
            break;
        cout << "Digite o id do funcionario: " << endl;
        cin >> funcionarionovo.id;
    }
    lista.close();
    if(lista.is_open())
    {
        cerr << "Lista nao fechado" <<endl;;
    }
    menu();
};
void excluir(){
    funcionario funcionarionovo= {0,' ',' ',' ',' ',0.0};
    ofstream lista("lista.txt", ios::out | ios::ate );
    if(lista.fail())
    {
        cerr << "Lista nao aberto"<<endl;
    }
    cout << "Digite o id do funcionario: " << endl;
    cin >> funcionarionovo.id;
     while (funcionarionovo.id > 0 && funcionarionovo.id <= 100)
    {
        lista.seekp((funcionarionovo.id - 1)*sizeof(funcionario));
        funcionarionovo.id=0;
        lista.write((const char*)(&funcionarionovo), sizeof(funcionario));
                cout << "Deseja excluir outro funcionario? (1-sim)" << endl;
        int i;
        cin >> i;
        if (i!=1)
            break;
        cout << "Digite o id do funcionario: " << endl;
        cin >> funcionarionovo.id;
    }
    lista.close();
    if(lista.is_open())
    {
        cerr << "Lista nao fechado" <<endl;;
    }
    menu();
}
#endif // FUNÁOES_H_INCLUDED
