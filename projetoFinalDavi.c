#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif


int larguraTerminal();
int tamanhoSemANSI(const char *texto);
void printCentralizado(const char *texto);
void limpar(void);
void cabecalho(void);
void opcoes(void);
void creditos(void);
int pause(void);
void inputCentralizado(const char *texto, char *formato, void *variavel);

void verificarBissexto(void);
void pesoIdeal(void);
void converterTemperatura(void);
void verificarNumero(void);
void verificarTriangulo(void);
void verificarTemperatura(void);
void calcularSalario(void);
void maiorNumero(void);
void verificarNota(void);
void verificacao5(void);
void consumoKwh(void);
void verificarImposto(void);
void idade(void);
void mediaAleatoria(void);
void calcularSoma(void);
void contar(void);
void calcularMedia(void);
void muliplo5e3(void);
void intParaHoras(void);
void calcularPreco(void);
void diaUtil(void);
void conceito(void);
void preco(void);
void cursos(void);
void calcularEconomia(void);
void calculadoraSimples(void); 
void adivinharNumero(void);
void desenharQuadradoCompleto(void);
void desenharQuadradoVazado(void);


int main() {
    int opcaoEscolhida;

    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= 0x0004;
        SetConsoleMode(hOut, dwMode);
    }
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
    setvbuf(stdout, NULL, _IONBF, 0);

    do {
        limpar();
        cabecalho();
        opcoes();

        inputCentralizado("Escolha uma opcao: ", "%d", &opcaoEscolhida);

        limpar();

        switch (opcaoEscolhida) {
            case 0:
                limpar();
                creditos();
                break;
            case 1:
                cabecalho();
                pesoIdeal();           
                break;
            case 2:
                cabecalho();
                converterTemperatura();
                break;
            case 3:
                cabecalho();
                verificarNumero();      
                break;
            case 4:
                cabecalho();
                verificarTriangulo();   
                break;
            case 5:
                cabecalho();
                verificarTemperatura(); 
                break;
            case 6:
                cabecalho();
                calcularSalario();       
                break;
            case 7:
                cabecalho();
                maiorNumero();          
                break;
            case 8:
                cabecalho();
                verificarNota();        
                break;
            case 9:
                cabecalho();
                verificacao5();        
                break;
            case 10:
                cabecalho();
                consumoKwh();            
                break;
            case 11:
                cabecalho();
                verificarImposto();    
                break;
            case 12:
                cabecalho();
                idade();                 
                break;
            case 13:
                cabecalho();
                mediaAleatoria();      
                break;
            case 14:
                cabecalho();
                calcularSoma();         
                break;
            case 15:
                cabecalho();
                contar();            
                break;
            case 16:
                cabecalho();
                calcularMedia();        
                break;
            case 17:
                cabecalho();
                muliplo5e3();            
                break;
            case 18:
                cabecalho();
                intParaHoras();            
                break;
            case 19:
                cabecalho();
                calcularPreco();            
                break;
            case 20:
                cabecalho();
                diaUtil();            
                break;
            case 21:
                cabecalho();
                conceito();            
                break;
            case 22:
                cabecalho();
                preco();        
                break;
            case 23:
                cabecalho();
                cursos();            
                break;
            case 24:
                cabecalho();
                verificarBissexto();           
                break;
            case 25:
                cabecalho();
                calcularEconomia();           
                break;
            case 26:
                cabecalho();
                calculadoraSimples();           
                break;
            case 27:
                cabecalho();
                adivinharNumero();           
                break;
            case 28:
                cabecalho();
                desenharQuadradoCompleto();           
                break;
            case 29:
                cabecalho();
                desenharQuadradoVazado();           
                break;

            default:
                printCentralizado("Alternativa invalida\n");
                break;
        }
        if(opcaoEscolhida != 0){
            pause();

        }
    } while (opcaoEscolhida != 0);
    return 0;
}


void inputCentralizado(const char *texto, char *formato, void *variavel) {
    int largura = larguraTerminal();
    int tamanho = tamanhoSemANSI(texto);
	int i;
    int espacos = (largura - tamanho) / 2;
    if (espacos < 0) espacos = 0;
	
    int ret;
    do {
        for ( i = 0; i < espacos; i++) printf(" ");
        printf("%s", texto);
        fflush(stdout);

        ret = scanf(formato, variavel);

        if (ret != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printCentralizado("Entrada invalida!");
        } else {
            int c = getchar();
            if (c != '\n' && c != EOF) {
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }
    } while (ret != 1);
}

int larguraTerminal() {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return columns;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    #endif
}

int tamanhoSemANSI(const char *texto) {
    int tamanho = 0;
    int i = 0;

    while (texto[i]) {
        if (texto[i] == '\033') {  
            while (texto[i] && texto[i] != 'm') i++;
            if (texto[i] == 'm') i++;
        } else {
            tamanho++;
            i++;
        }
    }
    return tamanho;
}

void printCentralizado(const char *texto) {
    int largura = larguraTerminal();
    int tamanho = tamanhoSemANSI(texto);
	int i;
    int espacos = (largura - tamanho) / 2;
    if (espacos < 0) espacos = 0;

    for ( i = 0; i < espacos; i++)
        printf(" ");

    printf("%s\n", texto);
}

void limpar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void cabecalho() {
    printCentralizado("\033[32m               .__          __                     .___                        .___.__                     \033[0m");
    printCentralizado("\033[32m  ______ ____ |  |   _____/  |_  ___________    __| _/____     ____  ____   __| _/|__| ____   ____  ______\033[0m");
    printCentralizado("\033[32m /  ___// __ \\|  | _/ __ \\   __\\/  _ \\_  __ \\  / __ |/ __ \\  _/ ___\\/  _ \\ / __ | |  |/ ___\\ /  _ \\/  ___/\033[0m");
    printCentralizado("\033[32m \\___ \\\\  ___/|  |_\\  ___/|  | (  <_> )  | \\/ / /_/ \\  ___/  \\  \\__(  <_> ) /_/ | |  / /_/  >  <_> )___ \\ \033[0m");
    printCentralizado("\033[32m/____  >\\___  >____/\\___  >__|  \\____/|__|    \\____ |\\___  >  \\___  >____/\\____ | |__\\___  / \\____/____  >\033[0m");
    printCentralizado("\033[32m      \\/     \\/          \\/                         \\/    \\/       \\/           \\/   /_____/            \\/  \033[0m");
}

void opcoes() {
    printCentralizado("==========================================================================================================");
    printCentralizado("|      Sair \033[32m[0]\033[0m                         Calcular Peso ideal \033[32m[1]\033[0m                 Converter temperatura \033[32m[2]\033[0m  |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Verificar Numero \033[32m[3]\033[0m             Veririficar Triangulo \033[32m[4]\033[0m               Verifcar Temperatura \033[32m[5]\033[0m   |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Calcular Salario \033[32m[6]\033[0m             Maior Numero \033[32m[7]\033[0m                        Verificar nota \033[32m[8]\033[0m         |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      E multiplo de 5 \033[32m[9]\033[0m              Calcular conta de energia \033[32m[10]\033[0m          Verificar imposto \033[32m[11]\033[0m     |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Faixa etaria \033[32m[12]\033[0m                Calcular Media arbitraria \033[32m[13]\033[0m          Calcular Soma \033[32m[14]\033[0m         |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Contar ate 10 \033[32m[15]\033[0m               Calcular media \033[32m[16]\033[0m                     Multiplo de 5 e 3 \033[32m[17]\033[0m     |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Inteiro para hora \033[32m[18]\033[0m           Calcular Preco \033[32m[19]\033[0m                     verificar dia util \033[32m[20]\033[0m    |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Verificar conceito \033[32m[21]\033[0m          Verificar preco \033[32m[22]\033[0m                    Cursos \033[32m[23]\033[0m                |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Verificar ano bissexto \033[32m[24]\033[0m      Calcular economia \033[32m[25]\033[0m                  Calculadora simples \033[32m[26]\033[0m   |");
    printCentralizado("|----------------------------------------------------------------------------------------------------------|");
    printCentralizado("|      Adivinhar numero \033[32m[27]\033[0m            Quadrado completo \033[32m[28]\033[0m                  Quadrado vazado \033[32m[29]\033[0m       |");
    printCentralizado("==========================================================================================================");
}

void creditos() {
    printCentralizado("\033[32m                                                  .___       ___.                                                \033[0m");
    printCentralizado("\033[32m                               _____ _____     __| _/____   \\_ |__ ___.__.                                      \033[0m");
    printCentralizado("\033[32m                              /     \\\\__  \\   / __ |/ __ \\   | __ <   |  |                                      \033[0m");
    printCentralizado("\033[32m                             |  Y Y  \\/ __ \\_/ /_/ \\  ___/   | \\_\\ \\___  |                                      \033[0m");
    printCentralizado("\033[32m                             |__|_|  (____  /\\____ |\\___  >  |___  / ____|                                      \033[0m");
    printCentralizado("\033[32m                                   \\/     \\/      \\/    \\/       \\/\\/                                           \033[0m");
    printCentralizado("\033[32m    .___           .__  .__            _____  _____            ___.                        .__                  \033[0m");
    printCentralizado("\033[32m  __| _/____ ___  _|__| |  |__  __ ___/ ____\\/ ____\\____   ____\\_ |__ _____    ____   ____ |  |__   ___________ \033[0m");
    printCentralizado("\033[32m / __ |\\__  \\\\  \\/ /  | |  |  \\|  |  \\   __\\\\   __\\/ __ \\ /    \\| __ \\\\__  \\ _/ __ \\_/ ___\\|  |  \\_/ __ \\_  __ \\\033[0m");
    printCentralizado("\033[32m/ /_/ | / __ \\\\   /|  | |   Y  \\  |  /|  |   |  | \\  ___/|   |  \\ \\_\\ \\/ __ \\\\  ___/\\  \\___|   Y  \\  ___/|  | \\/\033[0m");
    printCentralizado("\033[32m\\____ |(____  /\\_/ |__| |___|  /____/ |__|   |__|  \\___  >___|  /___  (____  /\\___  >\\___  >___|  /\\___  >__|   \033[0m");
    printCentralizado("\033[32m     \\/     \\/               \\/                        \\/     \\/    \\/     \\/     \\/     \\/     \\/     \\/       \033[0m");
}

int pause() {
    int c;
    printCentralizado("Pressione \033[32mENTER\033[0m para continuar");
    while ((c = getchar()) != '\n' && c != EOF);
    return 0;
}


void verificarBissexto() {
    int ano;

    inputCentralizado("digite um ano: ", "%d", &ano);

    if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) {
        printCentralizado("ano bissexto");
    } else {
        printCentralizado("nao e um ano bissexto");
    }
}

void pesoIdeal() {
    float altura, peso;

    inputCentralizado("Qual sua altura: ", "%f", &altura);

    peso = (72.7 * altura) - 58;

    char buf[100];
    sprintf(buf, "Seu peso ideal: %.2f", peso);
    printCentralizado(buf);
}

void converterTemperatura() {
    float tempCelsius, tempFahrenheit;

    inputCentralizado("digite a temperatura em celsius: ", "%f", &tempCelsius);

    tempFahrenheit = (9.0 / 5.0) * tempCelsius + 32;

    char buf[100];
    sprintf(buf, "a temperatura em fahrenheit e: %.2f", tempFahrenheit);
    printCentralizado(buf);
}

void verificarNumero() {
    float numero;
    int numeroInteiro;

    inputCentralizado("qual o numero: ", "%f", &numero);

    if (numero > 0) {
        printCentralizado("Seu numero e positivo");
    } else if (numero < 0) {
        printCentralizado("Seu numero e negativo");
    } else {
        printCentralizado("Seu numero e zero");
    }

    numeroInteiro = (int) numero;

    if (numeroInteiro % 2 == 0) {
        printCentralizado("e par");
    } else {
        printCentralizado("e impar");
    }
}

void verificarTriangulo() {
    float lado1, lado2, lado3;

    inputCentralizado("qual o tamanho do primeiro lado: ", "%f", &lado1);
    inputCentralizado("qual o tamanho do segundo lado: ", "%f", &lado2);
    inputCentralizado("qual o tamanho do terceiro lado: ", "%f", &lado3);

    if (lado1 == 0 || lado2 == 0 || lado3 == 0) {
        printCentralizado("um dos lados e zero, nao pode formar um triangulo");
        return;
    }

    if (lado1 + lado2 > lado3 && lado1 + lado3 > lado2 && lado2 + lado3 > lado1) {

        if (lado1 == lado2 && lado2 == lado3) {
            printCentralizado("e um triangulo equilatero");
        }  
        else if (lado1 != lado2 && lado1 != lado3 && lado2 != lado3) {
            printCentralizado("e um triangulo escaleno");
        }  
        else {
            printCentralizado("e um triangulo isoceles");
        }

    } else {
        printCentralizado("nao pode formar um triangulo valido");
    }
}

void verificarTemperatura() {
    float temperatura;

    inputCentralizado("temperatura em graus celsius: ", "%f", &temperatura);

    if (temperatura < 15.0) {
        printCentralizado("esta frio");
    }  
    else if (temperatura >= 15.0 && temperatura <= 25.0) {
        printCentralizado("esta agradavel");
    }  
    else {
        printCentralizado("esta quente");
    }
}

void calcularSalario() {
    float totalVendido, comissao, salarioBase = 1200.00;

    inputCentralizado("quanto voce vendeu: ", "%f", &totalVendido);

    comissao = totalVendido / 10.0;

    char buf[100];
    sprintf(buf, "seu salario bruto e: %.2f", salarioBase + comissao);
    printCentralizado(buf);
    sprintf(buf, "sua comissao e: %.2f", comissao);
    printCentralizado(buf);
}

void maiorNumero() {
    int num1, num2;

    inputCentralizado("qual o primeiro numero: ", "%d", &num1);
    inputCentralizado("qual o segundo numero: ", "%d", &num2);

    if (num1 > num2) {
        char buf[80];
        sprintf(buf, "o numero maior e: %d", num1);
        printCentralizado(buf);
    }  
    else if (num2 > num1) {
        char buf[80];
        sprintf(buf, "o numero maior e: %d", num2);
        printCentralizado(buf);
    }  
    else {
        printCentralizado("sao iguais");
    }
}

void verificarNota() {
    float nota;

    inputCentralizado("nota de 0 a 100: ", "%f", &nota);

    if (nota >= 0 && nota < 60) {
        printCentralizado("Voce tirou F");
    }  
    else if (nota >= 60 && nota < 70) {
        printCentralizado("Voce tirou D");
    }  
    else if (nota >= 70 && nota < 80) {
        printCentralizado("Voce tirou C");
    }  
    else if (nota >= 80 && nota < 90) {
        printCentralizado("Voce tirou B");
    }  
    else if (nota >= 90 && nota <= 100) {
        printCentralizado("Voce tirou A");
    }  
    else {
        printCentralizado("nota invalida");
    }
}

void verificacao5() {
    int numero;

    inputCentralizado("digite um numero: ", "%d", &numero);

    if (numero % 5 == 0) {
        printCentralizado("e multiplo de 5");
    } else {
        printCentralizado("nao e multiplo de 5");
    }
}

void consumoKwh() {
    float consumo, valor;
    
    inputCentralizado("qual seu consumo: ", "%f", &consumo);

    if (consumo <= 100) {
        valor = consumo * 0.50;
    } else if (consumo <= 200) {
        valor = consumo * 0.70;
    } else {
        valor = consumo * 0.90;
    }

    char buf[100];
    sprintf(buf, "voce tem q pagar: %.2f", valor);
    printCentralizado(buf);
}

void verificarImposto() {
    float salario;

    inputCentralizado("qual seu salario: ", "%f", &salario);

    if (salario < 2000.00) {
        printCentralizado("isento de imposto");
    } else {
        printCentralizado("paga imposto");
    }
}

void idade() {
    int ida;

    inputCentralizado("qual sua idade: ", "%d", &ida);

    if (ida < 18) {
        printCentralizado("voce e menor");
    } else if (ida < 60) {
        printCentralizado("voce e adulto");
    } else {
        printCentralizado("voce e idoso");
    }
}

void mediaAleatoria() {
    int num, soma = 0, quantidade = 0;
    float media;

    do {
        inputCentralizado("Digite um numero (0 encerra): ", "%d", &num);

        if (num != 0) {
            soma += num;
            quantidade++;
        }
    } while (num != 0);

    if (quantidade > 0) {
        media = (float)soma / quantidade;
        char buf[120];
        sprintf(buf, "soma: %d", soma);
        printCentralizado(buf);
        sprintf(buf, "Quantidade: %d", quantidade);
        printCentralizado(buf);
        sprintf(buf, "Media: %.2f", media);
        printCentralizado(buf);
    } else {
        printCentralizado("numero invalido.");
    }
}

void calcularSoma() {
    int n, i = 1, soma = 0;

    inputCentralizado("Digite N (valor positivo): ", "%d", &n);

    while (n <= 0) {
        printCentralizado("Entrada invalida! Digite um numero inteiro positivo:");
        inputCentralizado("Digite N (valor positivo): ", "%d", &n);
    }

    while (i <= n) {
        soma += i;
        i++;
    }

    char buf[100];
    sprintf(buf, "Soma: %d", soma);
    printCentralizado(buf);
}

void contar(){
	int i;
    printCentralizado("Contando:");
    for ( i = 1; i <= 10; i++) {
        char buf[80];
        sprintf(buf, "Contagem: %d", i);
        printCentralizado(buf);
        #ifdef _WIN32
            Sleep(1000); 
        #else
            sleep(1);    
        #endif
    }
}

void calcularMedia() {
    float nota1, nota2, nota3, nota4, media;

    inputCentralizado("qual a sua primeira nota: ", "%f", &nota1);
    while (nota1 < 0) {
        printCentralizado("Entrada invalida! Digite um numero valido:");
        inputCentralizado("qual a sua primeira nota: ", "%f", &nota1);
    }

    inputCentralizado("qual a sua segunda nota: ", "%f", &nota2);
    while (nota2 < 0) {
        printCentralizado("Entrada invalida! Digite um numero valido:");
        inputCentralizado("qual a sua segunda nota: ", "%f", &nota2);
    }

    inputCentralizado("qual a sua terceira nota: ", "%f", &nota3);
    while (nota3 < 0) {
        printCentralizado("Entrada invalida! Digite um numero valido:");
        inputCentralizado("qual a sua terceira nota: ", "%f", &nota3);
    }

    inputCentralizado("qual a sua quarta nota: ", "%f", &nota4);
    while (nota4 < 0) {
        printCentralizado("Entrada invalida! Digite um numero valido:");
        inputCentralizado("qual a sua quarta nota: ", "%f", &nota4);
    }

    media = (nota1 + nota2 + nota3 + nota4) / 4.0;

    char buf[120];
    sprintf(buf, "sua media e: %.2f", media);
    printCentralizado(buf);

    if (media >= 8) {
        printCentralizado("voce esta aprovado");
    } else if (media >= 6 && media < 8) {
        printCentralizado("voce esta de recuperacao");
    } else {
        printCentralizado("voce esta reprovado");
    }
}

void muliplo5e3() {
    int num;

    inputCentralizado("Digite um numero: ", "%d", &num);

    if (num % 3 == 0 && num % 5 == 0) {
        printCentralizado("e multiplo de 3 e 5");
    } else {
        printCentralizado("Nao e multiplo de 3 e 5");
    }
}

void intParaHoras() {
    int segundos, horas, minutos, resto;

    inputCentralizado("Digite o total de segundos: ", "%d", &segundos);
    while (segundos < 0) {
        printCentralizado("Entrada invalida! Digite um valor inteiro positivo:");
        inputCentralizado("Digite o total de segundos: ", "%d", &segundos);
    }

    horas = segundos / 3600;
    resto = segundos % 3600;
    minutos = resto / 60;
    resto %= 60;

    char buf[100];
    sprintf(buf, "Tempo: %dh:%dm:%ds", horas, minutos, resto);
    printCentralizado(buf);
}

void calcularPreco() {  
    char produto[50];
    int quantidade;
    float preco, total;

    inputCentralizado("Digite produto: ", "%49s", produto);

    inputCentralizado("Digite a quantidade: ", "%d", &quantidade);
    while (quantidade < 0) {
        printCentralizado("Valor invalido! Digite um numero inteiro positivo:");
        inputCentralizado("Digite a quantidade: ", "%d", &quantidade);
    }

    inputCentralizado("Digite o preco: ", "%f", &preco);
    while (preco < 0) {
        printCentralizado("Valor invalido! Digite um preco valido:");
        inputCentralizado("Digite o preco: ", "%f", &preco);
    }

    total = quantidade * preco;
    char buf[120];
    sprintf(buf, "Produto: %s - Total: R$ %.2f", produto, total);
    printCentralizado(buf);
}

void diaUtil() {
    int dia;

    inputCentralizado("Digite o numero do dia (1 a 7): ", "%d", &dia);
    while (dia < 1 || dia > 7) {
        printCentralizado("Entrada invalida! Digite um numero de 1 a 7:");
        inputCentralizado("Digite o numero do dia (1 a 7): ", "%d", &dia);
    }

    switch (dia) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            printCentralizado("Dia util");
            break;
        case 1:
        case 7:
            printCentralizado("Fim de semana");
            break;
        default:
            printCentralizado("Dia invalido");
            break;
    }
}

void conceito() {
    char conceito;

    inputCentralizado("Digite o conceito (A, B, C, D, E): ", " %c", &conceito);
    while (strchr("ABCDEabcde", conceito) == NULL) {
        printCentralizado("Entrada invalida! Digite A, B, C, D ou E:");
        inputCentralizado("Digite o conceito (A, B, C, D, E): ", " %c", &conceito);
    }

    switch (toupper(conceito)) {
        case 'A': printCentralizado("Excelente"); break;
        case 'B': printCentralizado("Bom"); break;
        case 'C': printCentralizado("Regular"); break;
        case 'D': printCentralizado("Ruim"); break;
        case 'E': printCentralizado("Pessimo"); break;
        default: printCentralizado("Conceito invalido"); break;
    }
}

void preco() {
    int codigo;

    inputCentralizado("Digite o codigo do produto (101, 102, 103): ", "%d", &codigo);

    switch (codigo) {
        case 101: printCentralizado("Produto 101 - Preco: R$ 10.00"); break;
        case 102: printCentralizado("Produto 102 - Preco: R$ 20.00"); break;
        case 103: printCentralizado("Produto 103 - Preco: R$ 30.00"); break;
        default: printCentralizado("Codigo nao encontrado"); break;
    }
}

void cursos() {
    int curso_opt;

    printCentralizado("Menu:");
    printCentralizado("1 - ADS");
    printCentralizado("2 - SI");
    printCentralizado("3 - CC");
    printCentralizado("4 - EngSoft");
    inputCentralizado("Digite o numero do curso: ", "%d", &curso_opt);

    while (curso_opt < 1 || curso_opt > 4) {
        printCentralizado("Entrada invalida! Digite um numero de 1 a 4:");
        inputCentralizado("Digite o numero do curso: ", "%d", &curso_opt);
    }

    switch (curso_opt) {
        case 1: printCentralizado("Analise e Desenvolvimento de Sistemas - 2,5 a 3 anos"); break;
        case 2: printCentralizado("Sistemas de InformaÃ§Ã£o - 4 anos"); break;
        case 3: printCentralizado("Ciencia da Computacao - 4 anos"); break;
        case 4: printCentralizado("Engenharia de Software - 5 anos"); break;
        default: printCentralizado("Curso nÃ£o reconhecido"); break;
    }
}

void calcularEconomia() {
    float valorMensal;
    float total = 0;
    int mes;

    inputCentralizado("Digite o valor economizado por mes: ", "%f", &valorMensal);

    if (valorMensal <= 0) {
        printCentralizado("O valor deve ser maior que zero");
        return;
    }

    for ( mes = 1; mes <= 12; mes++) {
        total += valorMensal;
    }

    char resultado[100];
    sprintf(resultado, "Total economizado em 12 meses: R$ %.2f", total);
    printCentralizado(resultado);
}

void calculadoraSimples() {
    float a, b, resultado;
    char op;
    char msg[100];

    inputCentralizado("Digite o primeiro numero: ", "%f", &a);
    inputCentralizado("Digite o segundo numero: ", "%f", &b);
    inputCentralizado("Operacao (+, -, *, /): ", " %c", &op);

    switch (op) {
        case '+':
            resultado = a + b;
            break;
        case '-':
            resultado = a - b;
            break;
        case '*':
            resultado = a * b;
            break;
        case '/':
            if (b == 0) {
                printCentralizado("Erro: divisao por zero!");
                return;
            }
            resultado = a / b;
            break;
        default:
            printCentralizado("Operacao invalida!");
            return;
    }

    sprintf(msg, "Resultado: %.2f", resultado);
    printCentralizado(msg);
}

void adivinharNumero() {
    int baixo = 1, alto = 100, meio;
    char resposta;
    char msg[100];

    printCentralizado("Pense em um numero de 1 a 100");

    while (baixo < alto) {
        meio = (baixo + alto) / 2;

        sprintf(msg, "Seu numero e maior que %d (s/n): ", meio);
        inputCentralizado(msg, " %c", &resposta);

        if (resposta == 's' || resposta == 'S') {
            baixo = meio + 1;
        } else {
            alto = meio;
        }
    }

    sprintf(msg, "Seu numero e %d!", baixo);
    printCentralizado(msg);
}

void desenharQuadradoCompleto() {
       int num;
    char linha[300];
    int i;

    inputCentralizado("Digite um numero: ", "%d", &num);

    if (num <= 0) {
        printCentralizado("O numero deve ser maior que zero");
        return;
    }

    for ( i = 1; i <= num; i++) {
        int j;
        linha[0] = '\0';

        for (j = 1; j <= num; j++) {
            strcat(linha, "*");
        }

        printCentralizado(linha);
    }
}

void desenharQuadradoVazado() {
    int num;
    char linha[300];
	int i;
    inputCentralizado("Digite um numero: ", "%d", &num);

    if (num <= 1) {
        printCentralizado("O numero deve ser maior que 1");
        return;
    }

    for ( i = 1; i <= num; i++) {
        int j;
        linha[0] = '\0';

        if (i == 1 || i == num) {
            for (j = 1; j <= num; j++) {
                strcat(linha, "*");
            }
        } else {
            for (j = 1; j <= num; j++) {
                if (j == 1 || j == num) {
                    strcat(linha, "*");
                } else {
                    strcat(linha, " ");
                }
            }
        }

        printCentralizado(linha);
    }
}