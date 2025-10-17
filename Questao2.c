#include <stdio.h>

// Função para calcular o MDC (necessária para o MMC)
long long mdc(long long a, long long b) {
    while (b) {
        a %= b;
        long long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

// Função para calcular o MMC
long long mmc(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a * b) / mdc(a, b);
}

int main() {
    int n;
    printf("Digite o numero de chaves entre 1 e 10(N): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 10) {
        printf("Numero de chaves invalido.\n");
        return 1;
    }

    long long ciclos[10];
    printf("Digite os %d ciclos de ativacao: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &ciclos[i]);
    }
    
    // Começa com o primeiro ciclo
    long long resultado_mmc = ciclos[0];
    
    // Calcula o MMC iterativamente com os outros ciclos
    for (int i = 1; i < n; i++) {
        resultado_mmc = mmc(resultado_mmc, ciclos[i]);
        // Se o MMC parcial já ultrapassar 50, não há necessidade de continuar
        if (resultado_mmc > 50) {
            break;
        }
    }
    
    printf("\nCalculando o MMC de todos os ciclos...\n");
    printf("MMC calculado: %lld\n", resultado_mmc);
    
    if (resultado_mmc > 0 && resultado_mmc <= 50) {
        printf("\nO primeiro ano futuro em que todas as chaves podem ser utilizadas e: %lld\n", resultado_mmc);
    } else {
        printf("\nNao e possivel sincronizar todas as chaves dentro do limite de 50 anos.\n");
    }
    
    return 0;
}
