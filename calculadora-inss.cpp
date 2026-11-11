/*
Nome do programa......: Calculadora INSS 2026
Descricao do Programa.: Calculo da contribuicao do INSS
                       utilizando quatro faixas salariais,
                       com entrada manual dos parametros.
Autor.................: Enhazo
Data de criacao.......: 09/11/2026 as 08:11
Data de Atualizacao...: 09/11/2026
*/
// converti pelo flowgorthm
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <ctime>
#include <windows.h>
#include <locale.h>

using namespace std;

// monta o cabecalho e ve qual saudacao combina com a hora de agora
void cabecalho()
{
    time_t agora = time(NULL);
    tm* tempoLocal = localtime(&agora);
    int hora = (tempoLocal != NULL) ? tempoLocal->tm_hour : 12;

    cout << "\033[36m+------------------------------------------------------+\033[0m" << endl;
    cout << "\033[36m|\033[1m                 CALCULADORA INSS 2026                \033[0m\033[36m|\033[0m" << endl;
    cout << "\033[36m|------------------------------------------------------|\033[0m" << endl;
    cout << "\033[36m|\033[0m ";

    if (hora >= 5 && hora < 12) {
        cout << "Bom dia!";
    } else if (hora >= 12 && hora < 18) {
        cout << "Boa tarde!";
    } else {
        cout << "Boa noite!";
    }

    cout << " Seja bem-vindo ao programa!                   \033[36m|\033[0m" << endl;
    cout << "\033[36m+------------------------------------------------------+\033[0m" << endl;
}

int main()
{
    // arruma o console pra portugues e utf-8 igual nos outros programas
    if (__GNUC__ <= 9) {
        setlocale(LC_ALL, "Portuguese_Brazil");
    } else {
        SetConsoleOutputCP(CP_UTF8);
    }

    cout << fixed << setprecision(2); // deixa os dinheiro com duas casas certinho

    double max = 0; // teto maximo usado na conta, nao e o salario inteiro se passar dele
    double fum = 0, fduo = 0, ftri = 0; // limite da primeira, segunda e terceira faixa
    double aum = 0, aduo = 0, atri = 0, afor = 0; // aliquota de cada uma das quatro faixas
    double pdduo = 0, pdtri = 0, pdfor = 0; // parcela pra deduzir da segunda faixa pra frente

    // pega os parametros primeiro pra nao ter que ficar digitando tudo a cada salario
    cout << "Digite o teto maximo (2026: R$ 8.475,55): ";
    cin >> max;

    cout << "Digite o valor maximo da primeira faixa (2026: R$ 1.621,00): ";
    cin >> fum;

    cout << "Digite a aliquota da primeira faixa (2026: 0.075): ";
    cin >> aum;

    cout << "Digite o valor maximo da segunda faixa (2026: R$ 2.902,84): ";
    cin >> fduo;

    cout << "Digite a aliquota da segunda faixa (2026: 0.090): ";
    cin >> aduo;

    cout << "Digite a parcela a deduzir da segunda faixa (2026: R$ 24,32): ";
    cin >> pdduo;

    cout << "Digite o valor maximo da terceira faixa (2026: R$ 4.354,27): ";
    cin >> ftri;

    cout << "Digite a aliquota da terceira faixa (2026: 0.120): ";
    cin >> atri;

    cout << "Digite a parcela a deduzir da terceira faixa (2026: R$ 111,40): ";
    cin >> pdtri;

    cout << "Digite a parcela a deduzir da quarta faixa (2026: R$ 198,49): ";
    cin >> pdfor;

    cout << "Digite a aliquota da quarta faixa (2026: 0.140): ";
    cin >> afor;

    // se digitou letra no meio dos numeros ja avisa que deu ruim
    if (cin.fail())
    {
        cout << "Erro: Digite somente valores numericos!" << endl;
        system("pause");
        return 1;
    }

    // confere se as faixas tao na ordem e se as aliquotas e deducoes fazem sentido
    if (max <= 0 || fum <= 0 || fduo <= fum ||
        ftri <= fduo || ftri > max ||
        aum < 0 || aduo < 0 || atri < 0 || afor < 0 ||
        aum > 1 || aduo > 1 || atri > 1 || afor > 1 ||
        pdduo < 0 || pdtri < 0 || pdfor < 0)
    {
        cout << "Erro: Parametros das faixas invalidos!" << endl;
        system("pause");
        return 1;
    }

    // looping pra calcular outro salario sem perder os parametros la de cima
    for (char op = 's'; op == 's' || op == 'S'; )
    {
        double sal = 0, base = 0; // sal = salario bruto, base = valor que vai entrar na conta
        double desc = 0, salf = 0; // desc = desconto do inss, salf = salario depois do desconto

        system("cls"); // limpesa na tela pra nao ficar tudo amontoado
        cabecalho(); // chama o cabecalho com a saudacao do horario

        cout << "\nEsse programa calculara sua contribuicao do INSS." << endl;
        cout << "\nDigite seu salario bruto: R$ ";
        cin >> sal;

        // se o usuario mandou letra limpa o cin pra proxima leitura nao dar pau junto
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nErro: Digite um valor numerico!" << endl;
        }
        else if (sal <= 0)
        {
            cout << "\nErro: Digite um salario valido maior que zero." << endl;
        }
        else
        {
            // se ganhou mais que o teto usa so o teto na conta, o resto fica fora
            if (sal > max) {
                base = max;
            } else {
                base = sal;
            }

            // vai olhando em qual faixa caiu pra usar a aliquota e tirar a parcela certa
            if (base <= fum)
            {
                desc = base * aum; // na primeira faixa nao tem parcela pra deduzir
            }
            else
            {
                if (base <= fduo)
                {
                    desc = base * aduo - pdduo;
                }
                else
                {
                    if (base <= ftri)
                    {
                        desc = base * atri - pdtri;
                    }
                    else
                    {
                        desc = base * afor - pdfor;
                    }
                }
            }

            // tira so o inss do salario original, nao da base limitada pelo teto
            salf = sal - desc;

            // mostra os resultado tudo bunitinho pro usuario ver quanto sobrou
            cout << "\n============================================" << endl;
            cout << "              RESULTADO DO INSS             " << endl;
            cout << "============================================" << endl;
            cout << "Salario bruto: R$ " << sal << endl;
            cout << "Base de calculo: R$ " << base << endl;
            cout << "Desconto do INSS: R$ " << desc << endl;
            cout << "Salario liquido: R$ " << salf << endl;
            cout << "============================================" << endl;
        }

        // pergunta se quer rodar denovo, o op que manda no for la de cima
        cout << "\nDeseja rodar o programa novamente? (S/N): ";
        cin >> op;

        // fica pedindo ate digitar s ou n pra nao encerrar por qualquer tecla
        while (op != 's' && op != 'S' && op != 'n' && op != 'N')
        {
            cout << "Opcao invalida! Digite S ou N: ";
            cin >> op;
        }
    }

    // tela de despedida pra fechar com um pouco de frufru
    system("cls");
    cout << "\033[31m+------------------------------------------------------+\033[0m" << endl;
    cout << "\033[31m|\033[1m             PROGRAMA ENCERRADO. ATE LOGO!             \033[0m\033[31m|\033[0m" << endl;
    cout << "\033[31m+------------------------------------------------------+\033[0m" << endl;

    system("pause");
    return 0; // acabou tudo certo, vlw flw
}

