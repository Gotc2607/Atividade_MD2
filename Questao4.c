#include <stdio.h>

// Função para calcular o MDC com exibição de passos (Algoritmo de Euclides)
int mdcComPassos(int a, int b) {
    int resto;
    printf("   Executando Algoritmo de Euclides para mdc(%d, %d):\n", a, b);

    // >>> ALTERAÇÃO [1] - Linha 10 <<<
    // O que foi alterado: A condição `b != 0` foi adicionada ao `while`.
    // Por quê: Esta é a condição de parada fundamental do Algoritmo de Euclides. O loop
    // continua executando as divisões sucessivas até que o resto (que se torna o novo 'b')
    // seja zero. O último divisor não nulo é o MDC.
    while (b != 0) {
        resto = a % b;
        printf("   - Passo: %d mod %d = %d\n", a, b, resto);
        a = b;

        // >>> ALTERAÇÃO [2] - Linha 14 <<<
        // O que foi alterado: O valor de `b` agora recebe o `resto`.
        // Por quê: Este é o passo de atualização do algoritmo. O divisor anterior ('b') se
        // torna o novo dividendo, e o resto da divisão ('resto') se torna o novo divisor
        // para a próxima iteração.
        b = resto;
    }
    printf("   - Resultado MDC: %d\n", a);
    return a;
}

// Função para calcular o inverso modular usando o Algoritmo de Euclides Estendido
int inversoModular(int a, int m) {
    // >>> ALTERAÇÃO [3] - Linha 23 <<<
    // O que foi alterado: Uma verificação `if (mdcComPassos(a, m) != 1)` foi inserida.
    // Por quê: O inverso modular de 'a' (mod m) só existe se 'a' e 'm' forem primos entre si,
    // ou seja, se o máximo divisor comum entre eles for 1. Esta linha garante essa
    // condição essencial antes de prosseguir com o cálculo, evitando erros.
    if (mdcComPassos(a, m) != 1) {
        printf("\n   ERRO: O inverso modular de %d (mod %d) nao existe.\n", a, m);
        return -1; // Retorna um valor de erro
    }
    
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    // >>> ALTERAÇÃO [4] - Linha 36 <<<
    // O que foi alterado: A linha `x1 += m0` foi adicionada dentro de um `if`.
    // Por quê: O Algoritmo de Euclides Estendido pode retornar um coeficiente de Bézout (o inverso)
    // que é negativo. Matematicamente, o resultado está correto, mas em criptografia e aritmética
    // modular, geralmente se trabalha com o menor representante positivo. Somar o módulo ('m0')
    // ao resultado negativo o converte para seu equivalente positivo.
    if (x1 < 0) {
        x1 += m0;
    }
    return x1;
}

// Função para calcular potência modular (exponenciação por quadratura)
long long powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        // >>> ALTERAÇÃO [5] - Linha 45 <<<
        // O que foi alterado: Uma verificação `if (exp % 2 == 1)` foi inserida.
        // Por quê: Esta é a lógica central do método de exponenciação binária (ou por quadratura).
        // Ele decompõe o expoente em potências de 2. Se o bit menos significativo do expoente
        // for 1 (ou seja, se o expoente for ímpar), a base atual é multiplicada pelo resultado
        // acumulado. Isso garante que a potência final seja calculada corretamente e de forma otimizada.
        if (exp % 2 == 1) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        exp >>= 1; // Equivale a exp = exp / 2
    }
    return res;
}

int main() {
    printf("--- QUESTAO 04 (BONUS): DIVISAO E POTENCIACAO MODULAR ---\n");
    int H = 7, G = 3, Zn = 11, x = 10, n1 = 13;
    printf("Valores de entrada definidos:\n H=%d, G=%d, Zn=%d, x=%d, n1=%d\n\n", H, G, Zn, x, n1);

    printf("1. Calculando a divisao modular: (%d / %d) mod %d\n", H, G, Zn);
    
    // >>> ALTERAÇÃO [6] - Linha 72 <<<
    // O que foi alterado: A variável `inverso` recebe o resultado da chamada da função `inversoModular`.
    // Por quê: Para realizar a divisão modular (H / G), primeiro precisamos encontrar o inverso
    // modular de G. Esta linha executa a chamada à função que implementa o Algoritmo de
    // Euclides Estendido para obter esse inverso.
    int inverso = inversoModular(G, Zn);
    
    if (inverso == -1) {
        return 1;
    }

    int a = (long long)H * inverso % Zn;
    printf("\n2. Fazendo a multiplicacao modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);

    printf("\n3. Calculando a potencia modular: %d^%d mod %d\n", a, x, n1);

    // >>> ALTERAÇÃO [7] - Linha 78 <<<
    // O que foi alterado: A variável `resultado` recebe o resultado da chamada da função `powMod`.
    // Por quê: Esta é a segunda parte do problema. Após encontrar o valor de 'a' (resultado da
    // divisão modular), precisamos calcular a^x mod n1. Esta linha chama a função de
    // exponenciação modular otimizada para obter o resultado final da congruência.
    long long resultado = powMod(a, x, n1);

    printf("\n--------------------------------------------------\n");
    printf("Sendo %d o inverso de %d (mod %d).\n", inverso, G, Zn);
    printf("Valor final da congruencia: %lld\n", resultado);
    printf("--------------------------------------------------\n");

    return 0;
}