#include <stdio.h>
#include <math.h>

// Função para calcular potência, necessária para sigma(N)
long long power(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

int main() {
    int n;
    printf("Digite um inteiro N (1 a 100000): ");
    scanf("%d", &n);

    if (n < 1 || n > 100000) {
        printf("Numero fora do intervalo permitido.\n");
        return 1;
    }
    
    printf("\n1. Fatoracao Prima de N = %d (Trial Division)\n", n);
    
    long long tau_n = 1;
    long long sigma_n = 1;
    int temp_n = n;

    for (int i = 2; i * i <= temp_n; i++) {
        if (temp_n % i == 0) {
            int count = 0;
            while (temp_n % i == 0) {
                temp_n /= i;
                count++;
            }
            printf("   - Fator primo encontrado: %d, Expoente: %d\n", i, count);
            tau_n *= (count + 1);
            sigma_n *= (power(i, count + 1) - 1) / (i - 1);
        }
    }
    
    if (temp_n > 1) { // Se sobrou um fator primo
        printf("   - Fator primo encontrado: %d, Expoente: 1\n", temp_n);
        tau_n *= 2;
        sigma_n *= (temp_n + 1);
    }
    
    printf("\n2. Calculos Intermediarios\n");
    printf("   - Calculo de tau(N): %lld\n", tau_n);
    printf("   - Calculo de sigma(N): %lld\n", sigma_n);

    double razao = (double)sigma_n / tau_n;
    
    printf("\n3. Resultado Final\n");
    printf("   - A Razao de Eficiencia de %d e: %.2f\n", n, razao);
    
    return 0;
}