#include <stdio.h>
#include <math.h>

// Função auxiliar para calcular potência, necessária para a fórmula de sigma(N)
long long power(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

int main() {

    printf("Integrantes do Grupo:\n");
    printf("Giovani de Oliveira Teodoro Coelho - 241032500\n");
    printf("Luiz Henrique Pallavicini - 241012329\n\n");

    int n;
    printf("--- QUESTAO 03: A RAZAO DE EFICIENCIA DE UM NUMERO ---\n");
    
    // --- CORREÇÃO APLICADA AQUI ---
    // A mensagem foi corrigida para refletir o limite real de validação do programa (100000),
    // que interpreta o provável erro de digitação "105" no PDF como "10^5".
    printf("Digite um unico inteiro N (1 <= N <= 100000): ");
    scanf("%d", &n);

    // Validação da entrada
    if (n < 1 || n > 100000) {
        printf("Erro: O numero N esta fora do intervalo permitido [1, 100000].\n");
        return 1;
    }

    printf("\nAnalisando o numero: %d\n", n);
    printf("--------------------------------------------------\n");

    int temp_n = n;
    long long tau_n = 1;   // tau(N) armazena o número de divisores
    long long sigma_n = 1; // sigma(N) armazena a soma dos divisores

    // Passo 1: Fatoração Prima utilizando Trial Division [cite: 115]
    printf("1. FATORACAO PRIMA (N = p1^a1 * p2^a2 * ...):\n");
    printf("   Lista de fatores primos e seus expoentes:\n"); // [cite: 122]

    for (int i = 2; i * i <= temp_n; i++) {
        if (temp_n % i == 0) {
            int count = 0;
            while (temp_n % i == 0) {
                temp_n /= i;
                count++;
            }
            printf("   - Fator: %d, Expoente (a): %d\n", i, count);
            // Aplicando a fórmula: tau(N) = (a1+1)*(a2+1)*...
            tau_n *= (count + 1);
            // Aplicando a fórmula: sigma(N) = (p1^(a1+1)-1)/(p1-1) * ...
            sigma_n *= (power(i, count + 1) - 1) / (i - 1);
        }
    }

    // Se sobrou um número > 1, ele também é um fator primo
    if (temp_n > 1) {
        printf("   - Fator: %d, Expoente (a): 1\n", temp_n);
        tau_n *= 2;
        sigma_n *= (temp_n + 1);
    }
    printf("--------------------------------------------------\n");

    // Passo 2: Exibição dos Cálculos Intermediários de tau e sigma [cite: 117]
    printf("2. CALCULOS INTERMEDIARIOS:\n");
    printf("   - Calculo de tau(N) (numero de divisores): %lld\n", tau_n);
    printf("   - Calculo de sigma(N) (soma dos divisores): %lld\n", sigma_n); // [cite: 124]
    printf("--------------------------------------------------\n");

    // Passo 3: Cálculo da Razão de Eficiência
    double razao = 0.0;
    if (tau_n != 0) {
        razao = (double)sigma_n / tau_n; // [cite: 107]
    }
    printf("3. RESULTADO FINAL (Razao de Eficiencia):\n"); // [cite: 125]
    printf("   Razao(%d) = sigma(%d) / tau(%d) = %lld / %lld\n", n, n, n, sigma_n, tau_n);
    // Saída formatada como número real com duas casas decimais [cite: 110]
    printf("\n   >> A Razao de Eficiencia de %d e: %.2f\n", n, razao);
    printf("--------------------------------------------------\n");

    return 0;
}