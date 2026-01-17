#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <windows.h>

#define NUMERO_DE_PALAVRAS 245366
#define NUMERO_DE_LETRAS 6
// 11139 palavrasDe6Letras

using namespace std;

char palavrasDe6Letras[NUMERO_DE_PALAVRAS][NUMERO_DE_LETRAS + 1];

int gerarPosicaoDaPalavraSecreta(){
    srand(time(nullptr));
    int posicaoDaPalavraSecreta = (rand() % 8) + (rand() % 10 * 10) + (rand() % 4 * 100) + (rand() % 2 * 1000) + (rand() % 2 * 10000);
    return posicaoDaPalavraSecreta;
}

void feedbackTentativa(char tentativa[NUMERO_DE_LETRAS + 1], char palavraSecreta[NUMERO_DE_LETRAS + 1]){
    for (int j = 0; j < NUMERO_DE_LETRAS; j++){
        for (int j2 = 0; j2 < NUMERO_DE_LETRAS; j2++){
            if (tentativa[j] == palavraSecreta[j]){
                cout << "O";
                break;
            }
            else if (tentativa[j] == palavraSecreta[j2] && j != j2){
                cout << "X";
                break;
            }
            else {
                cout << "_";
            }
        }
    }
}

bool validaTentativa(char tentativa[NUMERO_DE_LETRAS + 1]){
    for(int i=0; i < NUMERO_DE_LETRAS; i++){
        if((tentativa[i] < 'a' || tentativa[i] > 'z') && (tentativa[i] < 'A' || tentativa[i] > 'Z')){
            cout<<"Tentativa inválida, insira apenas letras por favor: ";
            return false;
        }
    }
    return true;
}

void telaDeInicio()
{
    cout << "===========================================================================================\n"; 
    cout << "                                    JOGO TERMO  \n"; 
    cout << "===========================================================================================\n"; 
    cout << "Regras:\n"; 
    cout << " - Você tem 10 tentativas.\n"; 
    cout << " - Cada palavra deve ter 6 letras.\n"; 
    cout << " - Para letras corretas o símbolo \'O\' aparecerá logo abaixo do caractere\n"; 
    cout << " - Para letras certas na posição errada o símbolo \'X\' aparecerá logo abaixo do caractere.\n"; 
    cout << " - Para Letras incorretas o símbolo \'_\' aparecerá logo abaixo do caractere.\n"; 
    cout << "===========================================================================================\n"; 
    cout << "Pressione ENTER para começar.\n"; cin.ignore(); // espera apertar ENTER
}

void armazenarPalavras(char palavrasDe6Letras[][NUMERO_DE_LETRAS + 1]) {
    ifstream arquivo("../palavras_da_lingua_portuguesa.txt");
    if (!arquivo) {
        cout << "Erro ao abrir arquivo\n";
        return;
    }

    char palavraTemporaria[47];
    int posicaoDaPalavra = 0;

    while (posicaoDaPalavra < NUMERO_DE_PALAVRAS &&
           arquivo.getline(palavraTemporaria, 47)){
        int j = 0;
        for (; palavraTemporaria[j] != '\0'; j++);
        if (j == NUMERO_DE_LETRAS) {
            for (int posicaoDaLetra = 0; posicaoDaLetra < NUMERO_DE_LETRAS; posicaoDaLetra++) {
                palavrasDe6Letras[posicaoDaPalavra][posicaoDaLetra] =
                    palavraTemporaria[posicaoDaLetra];
            }
            palavrasDe6Letras[posicaoDaPalavra][NUMERO_DE_LETRAS] = '\0';
            posicaoDaPalavra++;
        }
    }
}

int main(){

    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    armazenarPalavras(palavrasDe6Letras);

    int posicaoDaPalavraSecreta = gerarPosicaoDaPalavraSecreta();
    char palavraSecreta[NUMERO_DE_LETRAS + 1];
    for (int j = 0; j < NUMERO_DE_LETRAS; j++){
        palavraSecreta[j] = palavrasDe6Letras[posicaoDaPalavraSecreta][j];
    }
    palavraSecreta[NUMERO_DE_LETRAS] = '\0';

    telaDeInicio();

    char tentativa[NUMERO_DE_LETRAS + 1];
    for (int turno = 1; turno <= 10; turno++){
        cin.getline(tentativa, NUMERO_DE_LETRAS + 1);
        if (validaTentativa(tentativa) == false){
            turno--;
            continue;
        }
        feedbackTentativa(tentativa, palavraSecreta);
    }    

    return 0;
}
