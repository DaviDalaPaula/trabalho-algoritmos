#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <windows.h>

#define NUMERO_DE_PALAVRAS 245366
#define NUMERO_DE_LETRAS 6 // 11139 palavrasDe6Letras

using namespace std;

char palavrasDe6Letras[NUMERO_DE_PALAVRAS][NUMERO_DE_LETRAS + 1];

int gerarPosicaoDaPalavraSecreta(int numeroDePalavrasDe6Letras){
    srand(time(nullptr));
    int posicaoDaPalavraSecreta = rand() % numeroDePalavrasDe6Letras;
    return posicaoDaPalavraSecreta;
}

void feedbackTentativa(char tentativa[NUMERO_DE_LETRAS + 1], char palavraSecreta[NUMERO_DE_LETRAS + 1]){
    for (int j = 0; j < NUMERO_DE_LETRAS; j++){
        bool naoExiste = true;
        for (int j2 = 0; j2 < NUMERO_DE_LETRAS; j2++){
            if (tentativa[j] == palavraSecreta[j]){
                cout << "O";
                naoExiste = false;
                break;
            }
            else if (tentativa[j] == palavraSecreta[j2] && j != j2){
                cout << "X";
                naoExiste = false;
                break;
            }
        }
        if (naoExiste == true){
            cout << "_";
        }
    }
    cout << endl;
}

bool acertou(char tentativa[NUMERO_DE_LETRAS + 1], char palavraSecreta[NUMERO_DE_LETRAS + 1]){
    bool ganhou = true;
    for (int j = 0; j < NUMERO_DE_LETRAS; j++){
        if (tentativa[j] != palavraSecreta[j]){
            ganhou = false;
        }
    }
    return ganhou;    
}

bool validaTentativaPeloIntervalo(char tentativa[NUMERO_DE_LETRAS + 1]){
    for(int i=0; i < NUMERO_DE_LETRAS; i++){
        if(tentativa[i] < 'a' || tentativa[i] > 'z'){
            return false;
        }
    }
    return true;
}

bool validaTentativaPelaExistencia(char tentativa[NUMERO_DE_LETRAS + 1], char palavrasDe6Letras[][NUMERO_DE_LETRAS + 1], int numeroDePalavrasDe6Letras){
    for(int i=0; i < numeroDePalavrasDe6Letras; i++){
        int contaLetrasIguais = 0;
        for(int j=0; j < NUMERO_DE_LETRAS; j++){
            if(tentativa[j] == palavrasDe6Letras[i][j]){
                contaLetrasIguais++;
            }
        }
        if (contaLetrasIguais == NUMERO_DE_LETRAS){
            return true;
        }
    }
    return false;
}

void tornarTodasAsLetrasMinusculas(char tentativa[NUMERO_DE_LETRAS + 1]){
    for (int j = 0; j < NUMERO_DE_LETRAS; j++){
        tentativa[j] = tolower(tentativa[j]);
    }
}

void telaDeInicio(){
    cout << "===========================================================================================\n"; 
    cout << "                                    JOGO TERMO  \n"; 
    cout << "===========================================================================================\n"; 
    cout << "Regras:\n"; 
    cout << " - Você tem 10 tentativas.\n"; 
    cout << " - Cada palavra deve ter 6 letras (SEM ACENTOSanc).\n"; 
    cout << " - Para letras corretas o símbolo \'O\' aparecerá logo abaixo do caractere\n"; 
    cout << " - Para letras certas na posição errada o símbolo \'X\' aparecerá logo abaixo do caractere.\n"; 
    cout << " - Para Letras incorretas o símbolo \'_\' aparecerá logo abaixo do caractere.\n"; 
    cout << "===========================================================================================\n"; 
    cout << "Pressione ENTER para começar"; 
    cin.ignore();
}

int armazenarPalavras(char palavrasDe6Letras[][NUMERO_DE_LETRAS + 1]){
    ifstream arquivo("../palavras_da_lingua_portuguesa.txt");
    if (!arquivo) {
        cout << "Erro ao abrir arquivo\n";
        return 0;
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
    return posicaoDaPalavra;
}

void gerarPalavraSecreta(char palavraSecreta[NUMERO_DE_LETRAS + 1], char palavrasDe6Letras[][NUMERO_DE_LETRAS + 1], int posicaoDaPalavraSecreta){
    for (int j = 0; j < NUMERO_DE_LETRAS; j++){
        palavraSecreta[j] = palavrasDe6Letras[posicaoDaPalavraSecreta][j];
    }
    palavraSecreta[NUMERO_DE_LETRAS] = '\0';
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    int numeroDePalavrasDe6Letras = armazenarPalavras(palavrasDe6Letras);
    int posicaoDaPalavraSecreta = gerarPosicaoDaPalavraSecreta(numeroDePalavrasDe6Letras);
    char palavraSecreta[NUMERO_DE_LETRAS + 1];
    gerarPalavraSecreta(palavraSecreta, palavrasDe6Letras, posicaoDaPalavraSecreta);
    telaDeInicio();

    char tentativa[NUMERO_DE_LETRAS + 1];
    for (int turno = 1; turno <= 10; turno++){
        cout << "Tentativa " << turno << ": \n";
        cin.getline(tentativa, 20);
        tornarTodasAsLetrasMinusculas(tentativa);
        if (validaTentativaPeloIntervalo(tentativa) == false || validaTentativaPelaExistencia(tentativa, palavrasDe6Letras, numeroDePalavrasDe6Letras) == false){
            turno--;
            cout << "Tentativa inválida. Tente novamente." << endl;
            continue;
        }
        else {
            feedbackTentativa(tentativa, palavraSecreta);
        }
        if (acertou(tentativa, palavraSecreta) == true){
            cout << "Parabéns, você acertou!";
            break;
        }
        else if (turno == 10){
            cout << "Parabéns, você errou feio!\n";
            cout << "A palavra secreta era: " << palavraSecreta;
        }
    }    

    return 0;
}
