#include <stdio.h>

// Função para calcular o MDC (máximo divisor comum) com passo a passo
long long mdc(long long a, long long b) {
    printf("\n Iniciando Calculo do MDC(%lld, %lld) pelo Algoritmo de Euclides:\n", a, b);
    long long resto;
    long long original_a = a;
    long long original_b = b;

    while (b != 0) {
        resto = a % b;
        printf("      - Passo: %lld mod %lld = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    printf(" Resultado final do MDC(%lld, %lld) e: %lld\n", original_a, original_b, a);
    return a;
}

// Função para calcular o MMC (mínimo múltiplo comum)
long long mmc(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    long long divisor = mdc(a, b);
    // Para evitar overflow com números grandes
    long long resultado = (a / divisor) * b; 
    printf("\nCalculando MMC(%lld, %lld): (%lld * %lld) / %lld = %lld\n", 
            a, b, a, b, divisor, resultado);
    return resultado;
}

int main() {
    int n;

    printf("Integrantes do Grupo:\n");
    printf("Giovani de Oliveira Teodoro Coelho - 241032500\n");
    printf("Luiz Henrique Pallavicini - 241012329\n\n");

    printf(" PROGRAMA: CHAVES PERIODICAS \n");
    printf("Este programa calcula o primeiro ano em que TODAS as chaves podem ser usadas simultaneamente.\n");
    printf("Cada chave tem um ciclo de ativacao (em anos) e todas comecam no ano 0.\n");
    printf("O limite maximo de ano considerado e 50.\n\n");

    //Entrada do número de chaves 
    printf("Digite o numero de chaves (entre 1 e 10): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 10) {
        printf("Erro: Numero de chaves invalido. Deve estar entre 1 e 10.\n");
        return 1;
    }

    long long ciclos[10];
    printf("\nAgora digite os ciclos de ativacao de cada chave.\n");
    printf("Cada ciclo representa de quantos em quantos anos a chave pode ser usada.\n");
    printf("Os valores devem estar entre 2 e 20.\n\n");

    //Lendo e validando os ciclos de cada chave
    for (int i = 0; i < n; i++) {
        long long ciclo_atual;
        while (1) {
            printf("Ciclo da chave %d: ", i + 1);
            scanf("%lld", &ciclo_atual);
            
            if (ciclo_atual >= 2 && ciclo_atual <= 20) {
                ciclos[i] = ciclo_atual;
                printf("Ciclo %d registrado: %lld anos.\n", i + 1, ciclo_atual);
                break;
            } else {
                printf("O ciclo deve estar entre 2 e 20. Tente novamente.\n");
            }
        }
    }

    // Exibe os ciclos informados 
    printf("\nResumo dos ciclos informados:\n");
    for (int i = 0; i < n; i++) {
        printf("  - Chave %d: ciclo de %lld anos\n", i + 1, ciclos[i]);
    }

    printf("\n CALCULO DO ANO DE SINCRONIZACAO \n");

    // Calcula o MMC de todos os ciclos 
    long long resultado_mmc = ciclos[0];
    for (int i = 1; i < n; i++) {
        printf("Calculando MMC acumulado entre %lld e proximo ciclo %lld...\n", resultado_mmc, ciclos[i]);
        resultado_mmc = mmc(resultado_mmc, ciclos[i]);
        printf("MMC ate agora: %lld\n", resultado_mmc);
    }
    


    // Resultado final
    printf("\n RESULTADO FINAL \n");
    
    if (resultado_mmc > 0 && resultado_mmc <= 50) {
        printf("O primeiro ano futuro em que todas as chaves podem ser usadas simultaneamente e: %lld\n", resultado_mmc);
    } else {
        printf("O MMC final e %lld, que esta fora do limite de 50 anos.\n", resultado_mmc);
        printf("Nao e possivel sincronizar todas as chaves dentro do limite de 50 anos.\n");
    }

    return 0;
}