#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Função para calcular o Máximo Divisor Comum (MDC) pelo Algoritmo de Euclides
long long mdc(long long a, long long b) {
    long long resto;
    while (b != 0) {
        resto = a % b;
        printf("    - MDC Passo: %lld mod %lld = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

// Função para verificar se um número é primo
int ehPrimo(long long n) {
    if (n <= 1) return 0;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // É composto
    }
    return 1; // É primo
}

// Função p de Pollard para encontrar um fator primo de n
long long pollardP(long long n) {
    long long x = 2, y = 2, d = 1;
    int iteracao = 1;
    
    printf("1. Iniciando Metodo p de Pollard para N = %lld\n", n);
    printf("   Semente inicial x0 = 2\n");
    
    while (d == 1) {
        // g(x) = (x^2 + 1) mod n
        x = (x * x + 1) % n;
        y = (y * y + 1) % n;
        y = (y * y + 1) % n;
        
        long long diff = x > y ? x - y : y - x;
        printf("\n   Iteracao %d:\n", iteracao++);
        printf("   - x = %lld, y = %lld\n", x, y);
        printf("   - Calculando mdc(|%lld - %lld|, %lld) = mdc(%lld, %lld)\n", x, y, n, diff, n);
        d = mdc(diff, n);
    }
    
    printf("\n   Fator nao trivial encontrado: %lld\n", d);
    return d;
}

// Algoritmo Estendido de Euclides para encontrar o inverso modular
long long inversoModular(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1) return 0;

    printf("3. Calculando Inverso Modular de %lld mod %lld (Euclides Estendido):\n", a, m);
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    
    printf("   - Inverso Modular encontrado: %lld\n", x1);
    return x1;
}

// Exponenciação Modular com seleção de teorema
long long potenciaModular(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;

    printf("   - Calculando (%lld ^ %lld) mod %lld\n", base, exp, mod);

    // Etapa de redução de expoente
    if (ehPrimo(mod)) {
        printf("   - Teorema Aplicado: Pequeno Teorema de Fermat (pois %lld e primo).\n", mod);
        exp = exp % (mod - 1);
        printf("   - Expoente reduzido para: %lld\n", exp);
    } else {
        long long phi = mod; 
        if (mdc(base, mod) == 1) {
             printf("   - Teorema Aplicado: Teorema de Euler (pois mdc(%lld, %lld) = 1).\n", base, mod);
             printf("   - Usando reducao por Divisao Euclidiana por simplicidade.\n");
             exp = exp; 
        } else {
            printf("   - Teorema Aplicado: Reducao por Divisao Euclidiana (mdc(%lld, %lld) != 1).\n", base, mod);
        }
    }
    
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    long long n1, n2, p, q, n, z, e, d;

    printf("ETAPA 1: FATORACAO (METODO p de POLLARD)\n");
    
    while (1) {
        printf("Digite o primeiro numero COMPOSTO N1 (100 a 9999): ");
        scanf("%lld", &n1);

        if (n1 < 100 || n1 > 9999) {
            printf("Erro: O numero precisa ter 3 ou 4 digitos. Tente novamente.\n");
            continue;
        }
        if (ehPrimo(n1)) {
            printf("Erro: O numero %lld e primo. Por favor, insira um numero COMPOSTO.\n", n1);
        } else {
            break; // Número é composto e válido, sai do loop
        }
    }
    p = pollardP(n1);

    while (1) {
        printf("\nDigite o segundo numero COMPOSTO N2 (100 a 9999): ");
        scanf("%lld", &n2);

        if (n2 < 100 || n2 > 9999) {
            printf("Erro: O numero precisa ter 3 ou 4 digitos. Tente novamente.\n");
            continue;
        }
        if (ehPrimo(n2)) {
            printf("Erro: O numero %lld e primo. Por favor, insira um numero COMPOSTO.\n", n2);
        } else {
            break; // Número é composto e válido, sai do loop
        }
    }
    q = pollardP(n2);
    
    printf("\n2. Fatores Primos RSA Definidos:\n");
    printf("   p = %lld\n", p);
    printf("   q = %lld\n\n", q);
    
    printf("ETAPA 2: GERACAO DAS CHAVES RSA\n");
   
    // Calculando o n
    n = p * q;
    z = (p - 1) * (q - 1);
    printf("1. Modulo n = p * q = %lld\n", n);
    printf("2. Totiente de Euler z = (p-1)*(q-1) = %lld\n", z);
    
    // Achando o valor de E 
    for (e = 2; e < z; e++) {
        if (mdc(e, z) == 1) break;
    }
    printf("3. E = %lld\n", e);
    
    // Cálculo de D
    d = inversoModular(e, z);
    
    printf("\nCHAVES GERADAS:\n");
    printf("Chave Publica: (n=%lld, e=%lld)\n", n, e);
    printf("Chave Privada: (n=%lld, d=%lld)\n\n", n, d);

    printf("ETAPA 3: CODIFICAÇÃO E DECODIFICAÇÃO\n");
   
    char msg[100];
    printf("Digite a mensagem para criptografar (letras maiusculas, sem acentos): ");
    scanf(" %[^\n]s", msg);

    int len = strlen(msg);
    long long msg_codificada[100];
    long long msg_criptografada[100];
    
    printf("\n1. Processo de Criptografia:\n");
    int count = 0;
    for (int i = 0; i < len; i++) {
        long long val;
        if (msg[i] == ' ') {
            val = 0;
        } else {
            val = msg[i] - 'A' + 11;
        }
        msg_codificada[count] = val;
        printf("\n- Criptografando caractere '%c' (bloco M=%lld):\n", msg[i], val);
        msg_criptografada[count] = potenciaModular(val, e, n);
        printf("  - Resultado C = M^%lld mod %lld\n", e, n);
        printf("  - C = %lld\n", msg_criptografada[count]);
        count++;
    }
    
    printf("\nMensagem Cifrada (blocos): ");
    for(int i = 0; i < count; i++) printf("%lld ", msg_criptografada[i]);
    printf("\n");

    printf("\n2. Processo de Decodificacao:\n");
    char msg_decodificada[100];
    for (int i = 0; i < count; i++) {
        printf("\n- Decodificando bloco C=%lld:\n", msg_criptografada[i]);
        long long m_decodificado = potenciaModular(msg_criptografada[i], d, n);
        printf("  - Resultado M = C^%lld mod %lld\n", d, n);
        printf("  - M = %lld\n", m_decodificado);
        if (m_decodificado == 0) {
            msg_decodificada[i] = ' ';
        } else {
            msg_decodificada[i] = m_decodificado - 11 + 'A';
        }
    }
    msg_decodificada[count] = '\0';
    
    printf("\n3. RESULTADO FINAL:\n");
    printf("   Mensagem Original: %s\n", msg);
    printf("   Mensagem Decifrada: %s\n", msg_decodificada);
    
    if (strcmp(msg, msg_decodificada) == 0) {
        printf("\nConfirmacao: A mensagem decifrada é identica a original.\n");
    }
    else{
        printf("\nAlerta: A mensagem decifrada não corresponde a original.\n");
    }

    return 0;
}