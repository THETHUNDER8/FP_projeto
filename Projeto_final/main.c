#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_ESTUDANTES 5000
#define MAX_ATIVIDADES 200
#define MAX_INSCRICOES 10000
#define TAMANHO 80

typedef struct
{
    int ID_participante;
    char nome[TAMANHO];
    int escola;
    int NIF;
    char email[TAMANHO];
    int contacto;
} t_participantes;

typedef struct
{
    int dia,mes,ano;
} t_data;
typedef struct
{
    int hora,minuto;
} t_hora;
typedef struct
{
    int ID_atividade;
    char designacao_atividade[TAMANHO];
    t_data data_atividade;
    t_hora hora_atividade;
    char local_atividade[TAMANHO];
    int tipo_atividade;
    int AE_organizadora;
    float valor_inscricao;
} t_atividade;

typedef struct
{
    int ID_inscricao;
    int ID_participante_inscricao;
    int ID_atividade_inscricao;
    int valor_pago;
    t_data data_inscricao;
    t_hora inscricao;

} t_inscricao;


int registar_participante(t_participantes v_participante[],int numero_alunos);
void consultar_participantes(t_participantes v_participante[],int numero_participantes);
int resgistar_atividade(t_atividade v_atividade[],int numero_atividades);
void consultar_atividades(t_atividade v_atividade[],int numero_atividades);
void registar_inscricao();
void consultar_incricoes();
void estatisticas();
void n_atividades_associacao();
void percentagem_inscricoes_escola();
void horizonte_temporal();
void gravar_ficheiro();
void ler_ficherio();
float ler_numero(char *texto,int min, int max);
char ler_string(char *texto,char *string);
int menu_opcoes();
char confirma_saida();

int main()
{
    int op,total_participantes=0,total_atividades=0;
    char sair;
    t_participantes v_participante[MAX_ESTUDANTES];
    t_atividade v_atividade[MAX_ATIVIDADES];
    setlocale(LC_ALL,"Portuguese");
    do
    {
        op=menu_opcoes();
        fflush(stdin);
        switch(op)
        {
        case 1:
            if(total_participantes>=MAX_ESTUDANTES)
            {
                system("cls");
                printf("\nERRO:numero de estudantes ultrapassado!");
            }
            else
                total_participantes=registar_participante(v_participante,total_participantes);
            getchar();
            system("cls");
            break;
        case 2:
            if (total_participantes == 0)
            {
                system("cls");
                printf("\nErro: Nao foram inseridos Participantes!\n");
            }
            else
                consultar_participantes(v_participante,total_participantes);
            getchar();
            system("cls");
            break;
        case 3:
            if(total_atividades>=MAX_ATIVIDADES)
            {
                system("cls");
                printf("\nERRO:Numero de atividades ultrapassado!");
            }
            else
                total_atividades=resgistar_atividade(v_atividade, total_atividades);
            getchar();
            system("cls");
            break;
        case 4:
            if (total_atividades == 0)
            {
                system("cls");
                printf("\nErro: Nao foram inseridas atividades!\n");
            }
            else
                consultar_atividades(v_atividade, total_atividades);
            getchar();
            system("cls");
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 0:
            sair=confirma_saida();
            break;
        }
    }
    while(sair!='S');

    return 0;
}

int registar_participante(t_participantes v_participante[],int numero_participantes)
{
    char string[TAMANHO]= {'\0'};
    v_participante[numero_participantes].ID_participante=numero_participantes;
    ler_string("\nInsira o nome do participante:",string);
    strcpy(v_participante[numero_participantes].nome, string);
    v_participante[numero_participantes].escola=ler_numero("\n1-ESTG|2-ESECS|3-ESAD|4-ESTM|5-ESSLei\nInsira a escola a que pretence:",1,5);
    v_participante[numero_participantes].NIF=ler_numero("\nInsira o o NIF do participante:",100000000,999999999);
    ler_string("\nInsira o email do participante:",string);
    strcpy(v_participante[numero_participantes].email, string);
    v_participante[numero_participantes].contacto=ler_numero("\nInsira o contacto do participante:",900000000,999999999);
    numero_participantes=numero_participantes+1;
    getchar();
    return numero_participantes;
}
void consultar_participantes(t_participantes v_participante[],int numero_participantes)
{
    int indice;
    system("cls");
    printf("\nDados dos Participantes\n");
    for (indice = 0; indice < numero_participantes; indice++)
    {
        printf("\n ID do Participante:%d\n Nome:%s\n Escola(1-ESTG|2-ESECS|3-ESAD|4-ESTM|5-ESSLei):%d\n NIF:%d\n Email:%s\n Contacto:%d\n", v_participante[indice].ID_participante,v_participante[indice].nome, v_participante[indice].escola
               ,v_participante[indice].NIF,v_participante[indice].email,v_participante[indice].contacto);
               printf("*************************************");
    };
}

int resgistar_atividade(t_atividade v_atividade[],int numero_atividades)
{
    char string[TAMANHO]= {'\0'};
    v_atividade[numero_atividades].ID_atividade=numero_atividades;
    ler_string("\nInsira a designação da atividade:",string);
    strcpy(v_atividade[numero_atividades].designacao_atividade, string);
    v_atividade[numero_atividades].data_atividade.dia=ler_numero("\nDia :",1,31);
    v_atividade[numero_atividades].data_atividade.mes=ler_numero("\nMes :",1,12);
    v_atividade[numero_atividades].data_atividade.ano=ler_numero("\nAno :",2023,2050);
    v_atividade[numero_atividades].hora_atividade.hora=ler_numero("\nHora :",0,23);
    v_atividade[numero_atividades].hora_atividade.minuto=ler_numero("\nMinutos :",0,59);
    ler_string("\nInsira o local da atividade:",string);
    strcpy(v_atividade[numero_atividades].local_atividade, string);
    v_atividade[numero_atividades].tipo_atividade=ler_numero("\n1-Académica|2-Lazer|3-Cultura|4-Desporto|5-Formação|6-Outra\nInsira o tipo de atividade :",1,6);
    v_atividade[numero_atividades].AE_organizadora=ler_numero("\n1-AE-ESTG|2-AE-ESECS|3-AE-ESAD|4-AE-ESTM|5-AE-ESSLei\nInsira a Associação de Estudantes organizadora da atividade:",1,5);
    v_atividade[numero_atividades].valor_inscricao=ler_numero("\nValor da inscrição:",0,999);
    numero_atividades=numero_atividades+1;
    getchar();
    return numero_atividades;
}
void consultar_atividades(t_atividade v_atividade[],int numero_atividades)//erro no valor da atividade passa um float com mais de 2 casas decimais
{
    int indice;
    system("cls");
    printf("\nConsultar Atividades\n");
    for (indice = 0; indice < numero_atividades; indice++)
    {
        printf("\n ID da Atividade:%d\n Designação da atividade:%s\n Data da atividade:%d-%d-%d\n Hora da atividade:%d:%d\n Local da Atividade:%s\n Tipo de atividade(1-Académica|2-Lazer|3-Cultura|4-Desporto|5-Formação|6-Outra):%d\n AE-Organizadora(1-AE-ESTG|2-AE-ESECS|3-AE-ESAD|4-AE-ESTM|5-AE-ESSLei):%d\n Valor da Inscrição:%2f\n ",
               v_atividade[indice].ID_atividade,v_atividade[indice].designacao_atividade,v_atividade[indice].data_atividade.dia, v_atividade[indice].data_atividade.mes,v_atividade[indice].data_atividade.ano
               ,v_atividade[indice].hora_atividade.hora,v_atividade[indice].hora_atividade.minuto,v_atividade[indice].local_atividade,v_atividade[indice].tipo_atividade,v_atividade[indice].AE_organizadora,v_atividade[indice].valor_inscricao);
        printf("*************************************");
    };
}

/*
void registar_inscricao();
void consultar_incricoes();
void estatisticas();
void n_atividades_associacao();
void percentagem_inscricoes_escola();
void horizonte_temporal();*/
/*void gravar_ficheiro()
{
     FILE *ficheiro;
    ficheiro=fopen("alunos.dat","Wb");
    if(ficheiro==NULL)
        printf("Nao foi possivel criar o ficherio");
    else
        {
            fwrite(&numero_alunos,sizeof(int),1,ficheiro);
            fwrite(vetor_alunos,sizeof(t_aluno),numero_alunos,ficheiro);
            fclose(ficheiro);
            printf("\nEscrita dos dados de %d alunos me ficheiros com sucesso",numero_alunos);
        }
}*/
/*void ler_ficherio()
{
     int numero_alunos, numero_alunos_lido;
    FILE *ficheiro;
    ficheiro=fopen("alunos.dat","rb");
    if(ficheiro==NULL)
        printf("Nao foi possivel abrir o ficheiro!");
    else{
        fread(&numero_alunos,sizeof(int),1,ficheiro);
        numero_alunos_lido=fread(vetor_alunos,sizeof(t_aluno),numero_alunos,ficherio);
        fclose(ficheiro);
        if(numero_alunos_lido!=numero_alunos)
        {
            numero_alunos=0;
            printf("ERRO na leiruta de dados do ficheiro!");
        }
        else {
            printf("\nLeirura dos dados de %d alunos de ficheiro com sucesso.",numero_alunos);
        }
        return numero_alunos;
    }
}*/
float ler_numero(char *texto,int min, int max)
{
    float num;
    do
    {
        printf("%s",texto);
        fflush(stdin);
        scanf("%f", &num);
        if(num<min || num>max)
        {
            system("cls");
            printf("ERRO:numero invalido\nInsira um numero entre %d e %d",min,max);
            getchar();
        }
    }
    while(num<min || num>max);
    return num;
}
char ler_string(char *texto,char *dados)
{

    printf(" %s",texto);
    fflush(stdin);
    scanf("%80[^\n]s", dados);

    return dados;
}

int menu_opcoes()
{
    int opcao;
    do
    {
        printf("1-Registar Participante\n");
        printf("2-Consultar Participante\n");
        printf("3-Registar Atividade\n");
        printf("4-Consultar Atividade\n");
        printf("5-Resistar Inscrição\n");
        printf("6-Consultar Inscrição\n");
        printf("7-Estatisticas\n");
        printf("0-Sair\n");
        printf("Opcção:");
        scanf("%d",&opcao);
        if (opcao<0 ||opcao>7)
        {
            system("cls");
            printf("\nERRO:Opção invalida\n");
            getchar();
        }
    }
    while(opcao<0 ||opcao>7);
    return opcao;
}

char confirma_saida()
{
    char confirma;
    do
    {
        system("cls");
        printf("\nDeseja mesmo sair");
        printf("\nS-sim     N-não\n");
        scanf(" %c", &confirma);
        confirma=toupper(confirma);
        if(confirma!='S' && confirma!='N')
        {
            system("cls");
            printf("\nERRO:Opção invalida\n");
            getchar();
        }
    }
    while(confirma!='S' && confirma!='N');
    return confirma;
}
