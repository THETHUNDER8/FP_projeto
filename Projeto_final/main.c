#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_ESTUDANTES 5000
#define MAAX_ATIVIDADES 200
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
    char tipo_atividade[TAMANHO];
    char AE_organizadora[TAMANHO];
    int valor_inscricao;
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
void consultar_participantes();
void resgistar_atividade();
void consultar_atividades();
void registar_inscricao();
void consultar_incricoes();
void estatisticas();
void n_atividades_associacao();
void percentagem_inscricoes_escola();
void horizonte_temporal();
void gravar_ficheiro();
void ler_ficherio();
int ler_numero(char *texto,int min , int max);
char ler_string(char *texto,char *string);
int menu_opcoes();
char confirma_saida();

int main()
{
    int op,total_participantes=0;
    char sair;
    t_participantes v_participante[MAX_ESTUDANTES];
    setlocale(LC_ALL,"Portuguese");
    do
    {
        op=menu_opcoes();
        fflush(stdin);
        switch(op)
        {
        case 1:
            if(total_participantes>=MAX_ESTUDANTES)
                printf("\nERRO:numero de estudantes ultrapassado!");
            else
            {
                total_participantes=registar_participante(v_participante,total_participantes);
            }
            getchar();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
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
    char string[TAMANHO]={'\0'};
        v_participante[numero_participantes].ID_participante=numero_participantes;
        v_participante[numero_participantes].nome=ler_string("\nInsira o nome do participante:",string);
        v_participante[numero_participantes].escola=ler_numero("\n1-ESTG\t2-ESECS\t3-ESAD\t4-ESTM\t5-ESSLei\nInsira a escola a que pretence:",1,5);
        v_participante[numero_participantes].NIF=ler_numero("\nInsira o o NIF do participante:",100000000,999999999);
        v_participante[numero_participantes].email=ler_string("\nInsira o email do participante:",string);
        v_participante[numero_participantes].contacto=ler_numero("\nInsira o contacto do participante:",900000000,999999999);
        numero_participantes=numero_participantes+1;
    return numero_participantes;
}
void consultar_participantes()
{

}
/*void resgistar_atividade();
void consultar_atividades();
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
void ler_ficherio()
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
}
int ler_numero(char *texto,int min , int max)
{
    do
    {
        printf("%s",texto);
        fflush(stdin);
        scanf("%d", &num);
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
char ler_string(char *texto,char *string)
{
    do{
        printf(" %s",texto);
        fflush(stdin);
        scanf("%80[^\n]s", string);
    }while

        return string;
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
